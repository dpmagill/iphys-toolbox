function [IsSkinMask, TrueCount, YBounded_Single, CbBounded_Single, CrBounded_Single, ...
          HBounded_Single, SBounded_Single, IsSkinMask_Range] = ...
             SkinSegmentMask_Ops(RBounded_Uint8, GBounded_Uint8, BBounded_Uint8, YSingle, ...
                 CbSingle, CrSingle, HSingle, SSingle, IsSkinMask_Range, NRows_Matrix, ...
                 NCols_Matrix, CountTrueTF, TailoredThresholdsTF, ReturnYTF, ReturnCbCrTF, ...  
                 ReturnHSTF, TailoredThresholdsSevereTF, MorphCloseSevereTF, XOffset, YOffset, ...
                 SkinSegmentArgs) %#codegen                                                                                                                                                         
%SkinSegmentMask_Ops   Return logical matrix, or skin-segmentation mask, where pixels classified as  
%                      skin are true.
%                                              
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function SkinSegmentMask.
%
%
%    Code generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.
%
%    Compiled file: The compiled file included in folder FacePulseRate 
%    (SkinSegmentMask_Ops_mex.mexw64) only compatible on Windows platforms.       
%
%
%    Description
%    -----------
%
%    -- Combined Use of YCbCr and HSV Colorspaces for Pixel-Color Thresholds --
%
%    The combined used of the YCbCr and HSV colorspaces is based on ...
%    (1) Dahmani et al. (2020), who found that using both improved skin classification compared to
%        the use of either alone.
%    (2) The observation that using only the YCbCr colorspace did not permit enough diversity of
%        individual differences in skin color. Specifically, Y-minimum and Cr-minimum must be at 
%        least as low as the defaults to avoid oversegmentation in individuals with darker average
%        skin colors when ambient illumination is rather low. However, these defaults also permit 
%        pixel values from objects that should be segmented out; for example, the Cr-minimum at 
%        this level permits pixel values from overhead lamps. Applying the HSV thresholds in 
%        addition to the YCbCr thresholds segmented out these extraneous objects.
%
%    -- YCbCr Pixel-Color Thresholds -- 
%
%    YCbCr color thresholds in use:
%
%    - Y-channel minimum
%    - Y-channel maximum (tailored-thresholds only)
%    - Cb-channel minimum
%    - Cb-channel maximum 
%    - Cr-channel minimum
%    - Cr-channel maximum 
%
%    Apply color thresholds to individual pixels from the luminance (Y), Cb chroma (Cb), and Cr 
%    chroma (Cr) channels of the YCbCr colorspace.
%
%    Use either the generic YCbCr color thresholds or tailored YCbCr color thresholds. The use of
%    tailored thresholds is specified by argument TailoredThresholdsTF. However, generic thresholds
%    are used when TailoredThresholdsTF is true if the criterion for using tailored thresholds has
%    not been satisfied, which is indicated by DontUseTailoredTF == true. 
%
%        Generic Thresholds
%
%    The YCbCr generic color thresholds (SkinSegmentArgs.YCbCrThresholdsGeneric) are used when
%    TailoredThresholdsTF is set to false. Thresholds include a Y-channel minimum, Cb-channel 
%    minimum and maximum, Cr-channel minimum and maximum, and Cb-to-Cr ratio minimum and maximum.
%    
%    The threshold values are set by an argument, SkinSegmentYCbCrThresholdsGeneric, to function 
%    FacePulseRate. If the argument is not specified, default values are used. The default Y, Cb,  
%    and Cr minimums and maximums are based on a consultation of the values provided in iphys 
%    toolbox (McDuff & Blackford, 2019). These values were modified somewhat as a result of  
%    testing. The Cb-to-Cr ratio minimum and maximum and not used in iphys toolbox; these values 
%    were developed through testing.
%     
%    Function SkinSegment_ConfigSetup sets the values for SkinSegmentArgs.YCbCrThresholdsGeneric
%    based on argument SkinSegmentThresholdsGenericYCbCr.    
%
%    Within the current function, the YCbCr generic threshold operations are conducted by function  
%    SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold.
%
%        Tailored Thresholds
%
%    The YCbCr tailored thresholds (SkinSegmentArgs.YCbCrThresholdsGeneric) are used when
%    TailoredThresholdsTF is set to true. The threshold values are set based upon skin-color  
%    samples collected from the input video. The threshold types include those used in the generic
%    thresholds as well as a Y-channel maximum. The Y-channel maximum may be more sensitive than
%    other thresholds to individual differences in facial colors. Due to this sensitivity, this
%    value is not used for generic thresholds but is used for tailored thresholds as tailored
%    thresholds are based upon the face in the video.
%
%    The skin-color samples are collected from the input video. For details on the collection of 
%    skin-color samples, see function ROIMeans_FirstRead_CollectSkinColorSamples. Before a
%    sample is collected by function ROIMeans_FirstRead_CollectSkinColorSamples, function 
%    ROIMeans_FirstRead_CollectSkinColorSamples calls function SkinSegmentMask to attempt to 
%    isolate pixel colors corresponding to skin. When SkinSegmentMask is called by function 
%    ROIMeans_FirstRead_CollectSkinColorSamples samples, TailoredThresholdsTF is set to false; that 
%    is, generic thresholds are used. As tailored thresholds are based upon skin-color samples that
%    were filtered by the generic thresholds, the tailored thresholds can be expected to be more
%    stringent compared to the generic thresholds. The term "sample" refers to two values taken 
%    from each YCbCr color channel of skin-segmented ROI. Specifically, the the minimum and maximum
%    color values are taken from each channel. 
%    
%    Skin-color samples used for tailored YCbCr thresholds are collected by function 
%    ROIMeans_FirstRead_CollectSkinColorSamples, which is called by function ROIMeans_FirstRead. 
%    For details on the collection of skin-color samples, see function 
%    ROIMeans_FirstRead_CollectSkinColorSamples. 
%
%    After a certain number of samples has been collected, the samples are used to set the tailored 
%    threshold values. The setting of thresholds from skin-color samples is conduted by function
%    SkinSegment_SetThresholds. The number of samples required to set the tailored threshold 
%    values, SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold, is specified by function 
%    SkinSegment_ConfigSetup. This value can only be modified by adjusting the code within this
%    function. 
%
%    It has been observed that if the skin-color samples are too heavily concentrated within a 
%    particular portion of the video, the thresholds that come from them can be too restrictive. 
%    This is likey because samples limited to a brief portion of the video do not contain a
%    sufficient level enough heterogeneity to reflect the color variations across the video. To 
%    address this restrictiveness, the thresholds are reset periodically. Specifically, the 
%    thresholds are reset after a specified number of frames has elapsed since the thresholds were 
%    last set or reset. This number of frames is specified by 
%    SkinSegmentConfig.TailoredData.ThresholdOpsInterval, which is set by function
%    SkinSegment_ConfigSetup. This value can only be modified by adjusting the code within function
%    SkinSegment_ConfigSetup.
%
%    Although resetting the thresholds addresses the lack of heterogeneity across most of the 
%    video, heterogeneity may still be unacceptably low between the first setting of the thresholds
%    and the first resetting of the thresholds. This may occur if the skin-color samples are
%    collected within close proximity. One condition that causes samples to be collected within 
%    close proximity is a low frame-skipping rate (ROIGeneralConfig.ROISkipFrameThreshold; see
%    function ROIGeneralConfig_Setup). To increase the heterogeneity in this case, the number of 
%    skin-color samples required before the first thresholds are set 
%    (SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold) is increased when the  
%    frame-skipping rate is relatively low (see funtion SkinSegment_ConfigSetup). 
%
%    Before the required number of skin-color samples has been collected, generic thresholds are
%    used in place of tailored thresholds. If argument TailoredThresholdsTF is set to true, 
%    specifying that tailored thresholds should be used, generic thresholds will be used if the 
%    required number of samples has not been collected. Within the current function, the flag
%    DontUseTailoredTF is set to true in this case to indicate that generic thresholds should be  
%    used in place of tailored thresholds.
%    
%    For each skin-color sample, minimums and maximums are taken from each colorspace channel. 
%    These values are set aside until the thresholds are to be set or reset. When setting or 
%    resetting occurs, percentiles are applied to these values to extract the values at lower and
%    upper percentiles. The value at the lower percentile becomes the lower threshold and the
%    value at the upper percentile becomes the upper percentile. For example, suppose the lower and 
%    upper percentiles are specified as 1.5 and 98.5, respecively. From all skin-color samples
%    previously collected, the sample values from each channel that occur at the 1.5th percentile  
%    and 98.5th percentile become the lower the upper thresholds, respectively. One point of 
%    confusion may be that the terms "minimum" and "maximum" are used for two purposes here.
%    The first use is in taking the minimum and maximum of each skin-color sample. These minimums
%    and maximums are set aside until the percentiles are applied. When the percentiles are 
%    applied, the lower percentile becomes the lower threshold and the upper percentile becomes the
%    upper threshold. Although the terms "upper" and "lower" and used to refer to these thresholds
%    for clarity, the terms "minimum" and "maximum" would also be appropriate. That is, the lower,
%    or minimum, threshold is selected from a collection of minimum values; the upper, or maximum,
%    threshold is selected from a collection of maximum values.
%
%    One set of percentiles is used for the Y, Cb, Cr, Cb-to-Cr ratio, and H thresholds, and a 
%    separate set of percentiles is used for the S thresholds. A separate set of percentiles is 
%    used for the S thresholds because it has been observed that a wider range is appropriate for
%    the S color channel. These percentiles are specified by function SkinSegmentConfig_Setup. The
%    percentiles can be modified only by adjusting the code within SkinSegmentConfig_Setup.
%
%    Within the current function, the YCbCr tailored threshold operations are conducted by function  
%    SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold.
%
%    -- HSV Pixel-Color Thresholds --
%  
%    HSV color thresholds in use:
%
%    - H-channel maximum
%    - S-channel minimum
%    - S-channel maximum (tailored-thresholds only)
%
%    Apply color thresholds to individual pixels from the hue (H) and saturation (S) channels of  
%    the HSV colorspace.
%    
%    Use either the generic HSV color thresholds or tailored HSV color thresholds. The use of
%    tailored thresholds is specified by argument TailoredThresholdsTF. However, generic 
%    thresholds are used when TailoredThresholdsTF is true if the criterion for using tailored 
%    thresholds has not been satisfied, which is indicated by DontUseTailoredTF == true.
%
%        Generic Thresholds
%
%    The HSV generic color thresholds (SkinSegmentArgs.HSVThresholdsGeneric) are used when
%    TailoredThresholdsTF is set to false. Thresholds include an H-channel maximum and an S-channel
%    minimum.
%    
%    The threshold values are set by an argument, SkinSegmentThresholdsGenericHSV, to function 
%    FacePulseRate. If the argument is not specified, default values are used. The default H and S  
%    minimums and maximums are based on testing by DPM. 
%     
%    Function SkinSegment_ConfigSetup sets the values for SkinSegmentArgs.HSVThresholdsGeneric
%    based on argument SkinSegmentThresholdsGenericHSV.    
%
%    Within the current function, the HSV generic threshold operations are conducted by function  
%    SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold.
%
%        Tailored Thresholds
%
%    The H and S tailored color thresholds (SkinSegmentArgs.HSThresholdsTailored) are used when
%    TailoredThresholdsTF is set to true. The combination of a maximum for the H channel and a  
%    minimum and a maximum for the S channel is based on Dahmani et al. (2020). 
%    
%    As with the tailored YCbCr thresholds, these thresholds are set based upon skin-color samples 
%    collected from the input video. The process of setting the H and S tailored thresholds is  
%    identical to the process of setting the tailored YCbCr thresholds. 
%
%    If argument TailoredThresholdsTF is specified as true but the required number of samples has
%    not been acquired, the H and S tailored thresholds will not be used. As with the tailored 
%    YCbCr thresholds, the flag DontUseTailoredTF will be set to true to cause the H and S tailored 
%    thresholds not to be used.
%
%    Within the current function, the H and S tailored threshold operations are conducted by   
%    function SkinSegmentMask_Threshold_Colors, which is called by function 
%    SkinSegmentMask_Threshold.
%
%    -- Low- and High-Severity Tailored Thresholds -- 
%
%    When TailoredThresholdsSevereTF == true, high-severity thresholds are used when conducting
%    segmentation with the tailored YCbCr and HSV thresholds. High-severity thresholds are used for 
%    applications where the priority is to reduce false positives (pixels incorrectly classified as
%    skin) at the expense of a greater number false negatives (pixels incorrectly classified as 
%    non-skin). When false, low-severity thresholds are used. Low-severity thresholds are used for 
%    applications where a balance is desired between false positives and false negatives.     
%
%    -- Local-Range Pixel Threshold -- 
%
%    The local-range pixel threshold classifies pixels based upon the homogeneity of color values
%    of nearby, or local, pixels. When the local range is relatively homogeneous rather than
%    heterogeneous, the value of the local range will be lower. A relatively homogeneous color 
%    range of a given pixel is used as a heuristic of a pixel corresponding to skin. This is based  
%    on the assumption that true skin tends to occur in regions of homogeneous color. When the 
%    local range of a pixel falls below a specified threshold (SkinSegmentArgs.HThresholdTailored), 
%    the pixel is classified as skin.
%
%    The threshold for local range is a static value; that is, it is not set by assessment of color 
%    samples. The threshold value is set by function SkinSegmentConfig_Setup. The value can only be 
%    modified by adjusting the code within SkinSegmentConfig_Setup. The effectiveness of the value 
%    used was established through testing. 
%
%    Within the current function, the local-range pixel threshold operations are conducted by   
%    function SkinSegmentMask_Threshold_Range, which is called by function 
%    SkinSegmentMask_Threshold.
%
%    -- Morphological Close of Patchy Regions -- 
%
%    Following the application of these thresholds, a two-dimensional logical matrix is assigned 
%    where pixels that satisfied all thresholds are classified as true and pixels that did not are
%    classified as false. A morphological close operation is then applied to the logical matrix. 
%    The morphological close tends to fill in classification holes, where a hole is loosely defined 
%    as a region of pixels classified as true that are enclosed by pixels classified as false.  
%    Holes are filled in based on the assumption that true skin tends to be distributed in the face  
%    in contiguous, rather than patchy, regions.
%    
%    The morphological close fills in holes only below a certain shape and size, which are   
%    determined by the shape and size of the morphological structuring element, such that many 
%    holes are not filled. Otherwise, large regions classified as true -- which are assumed to be 
%    regions of skin -- may be erroneously filled. For a description on the choice of structuring 
%    element used, see function SkinSegmentMask_MorphClose. 
%
%    Within the current function, the morphological close operations are conducted by function  
%    SkinSegmentMask_Threshold_MorphClose, which is called by function SkinSegmentMask_Threshold.
%
%    -- Return Skin-Segmentation Mask Without Performing Colorspace Conversion --
%
%    To return a skin-segmentation mask without performing colorspace conversion, the colorspaces
%    needed for skin-segmentation can be entered as input. These include YSingle, CbSingle, 
%    CrSingle, HSingle, and SSingle. If all of these color channels are non-empty, colorspace
%    conversion will not be performed.
%
%    Additionally, IsSkinMask_Range, a skin-segmentation based upon the local range, can also be
%    be entered as input. 
%
%    A case where these may be entered is where skin segmentation is first run with either tailored
%    thresholds on or off and it is desired to rerun the skin segmentation using tailored or non-
%    tailored thresholds. In this case, the color channels and IsSkinMask_Range would have been
%    assigned previously and can be reused.
%
%    -- Color Channel Return Values --
%
%    The H and S channels of the HSV colorspace and the Y, Cb, and Cr channels of the YCbCr 
%    colorspace are assigned during the operations of function SkinSegmentMask_Threshold. For 
%    efficiency, these channels can be returned for reuse by other functions within function 
%    FacePulseRate. One use of these values by another function is to periodically reset the color  
%    thresholds (YCbCrThresholds_Tailored, HSThresholds_Tailored) used by the current function;  
%    this is conducted by function SkinSegment_SetThresholds. To return these channels for reuse by
%    other functions, the values are assigned to matrices, which are quite large due to the number 
%    of pixels processed. Assignment to these large matrices may incur additional processing time. 
%    To avoid this processing time when values are not to be reused, whether the channels are 
%    returned can be controlled by arguments. 
%
%    Argument ReturnYTF determines whether the Y channel is returned. Argument ReturnCbCrTF 
%    determines whether the Cb and Cr channels are returned. Argument ReturnHSTF determines whether 
%    the H and S channels are returned.    
%          
%
%    Notes
%    -----
%
%    For detailed descriptions of the implementation of settings used in this function, see 
%    function SkinSegmentConfig_Setup, which sets the settings.
%
%    To view an image segmented with the skin-segmentation mask returned by this function, run the
%    following code. The resulting image will be segmented in the same manner it is segmented in
%    function FacePulseRate.
%    SkinSegmented =        ... Segmented image
%        AreaToSegment .*   ... Original image prior to segmentation
%        uint8(IsSkinMask); %   Segmentation mask
%
%
%    Requires
%    --------
%
%        - Image Processing Toolbox (when non-compiled functions are used)
%
%
%    References
%    ----------
%
%    For helpful Matlab documentation on image segmentation operations, see the Matlab  
%    documentation topic "image segmentation".
%
%    Dahmani, D., Cheref, M., & Larabi, S. (2020). Zero-sum game theory model for segmenting skin 
%    regions. Image and Vision Computing, 103925.
%
%    McDuff, D., & Blackford, E. (2019, July). iphys: An open non-contact imaging-based 
%    physiological measurement toolbox. In 2019 41st Annual International Conference of the IEEE 
%    Engineering in Medicine and Biology Society (EMBC) (pp. 6521-6524). IEEE.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code generation specifications %%%%%%

%Inline function
coder.inline('always');

%Declare variables:
%                              Upp. Bounds    Var. Size (T/F)
coder.varsize('TrueCount',     [1, 1],        [1, 0]);


%%%%%% Parse input arguments %%%%%%

%Note: SkinSegmentMask_ParseArgs is a custom function located within folder FacePulseRate.
[RangeNeighborhoodWidth, RangeThreshold, DontUseTailoredTF, YCbCrThresholds_Generic, ...
 YCbCrThresholds_Tailored, HSThresholds_Generic, HSThresholds_Tailored, ...
 MorphCloseNeighborhoodWidth, NElements_Matrix] = ...
    SkinSegmentMask_ParseArgs(SkinSegmentArgs, TailoredThresholdsSevereTF, MorphCloseSevereTF, ...
        NRows_Matrix, NCols_Matrix);


%%%%%% Apply pixel-color and pixel-color local range thresholds %%%%%%

%Apply individual pixel-color and pixel-color local range thresholds to assign a skin-segmentation 
%mask.

%Note: SkinSegmentMask_Threshold is a custom function located within folder FacePulseRate.
[IsSkinMask, YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single, ...
 SBounded_Single, IsSkinMask_Range] = ...
    SkinSegmentMask_Threshold(RBounded_Uint8, GBounded_Uint8, BBounded_Uint8, YSingle, ...
        CbSingle, CrSingle, HSingle, SSingle, IsSkinMask_Range, NRows_Matrix, NCols_Matrix, ...
        NElements_Matrix, YCbCrThresholds_Generic, TailoredThresholdsTF, DontUseTailoredTF, ...
        YCbCrThresholds_Tailored, ReturnYTF, ReturnCbCrTF, HSThresholds_Generic, ...
        HSThresholds_Tailored, ReturnHSTF, RangeNeighborhoodWidth, RangeThreshold, XOffset, ...
        YOffset);
                    
                                                         
%%%%%% Morphologically close skin-segmentation mask regions with patchy classifications %%%%%%

%Note: SkinSegmentMask_MorphClose is a custom function located within folder FacePulseRate.
IsSkinMask = ...
    SkinSegmentMask_MorphClose(IsSkinMask, NRows_Matrix, MorphCloseSevereTF, ...
        MorphCloseNeighborhoodWidth);

    
%%%%%% Count the number of pixels classified as skin (true) %%%%%%

%If returning a count of the pixels classified as true is enabled
if CountTrueTF
            
    TrueCount = uint32(0);
    
    for i = 1 : NElements_Matrix
        
        if IsSkinMask(i)
        
            TrueCount = TrueCount + 1; 
        end
    end
    
else
    
    TrueCount = zeros(0, 1, 'uint32');
end


end %end function

      
%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(SkinSegmentMask_Ops_mex) of the function.

%{

%%%%%% Modify function files for performance %%%%%%

%Before running code generation, input validation was removed from the files for the 
%following functions:
% - \Program Files\MATLAB\R2020a\toolbox\images\images\bwpack.m
% - \Program Files\MATLAB\R2020a\toolbox\images\images\bwunpack.m
% - \Program Files\MATLAB\R2020a\toolbox\images\images\+images\+internal\+coder\morphop.m 

%Specifically, in these files, the following validation functions were commented out:
% - narginchk
% - validateattributes

%Note: Seperate files for these functions with these changes could not be made because code  
%generation for these functions expects specific file names. Hence, after code generation, the  
%input validation was added back to the files.
%Note: as these files are located in 'Program Files', admin access is required to edit them.


%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%                                             Example Code                 Upp. Bounds  Var. Size (T/F)  Type
RUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8
GUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8
BUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8
YSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single                      
CbSingleCode                  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single
CrSingleCode                  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single
HSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single                                 
SSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single 
IsSkinMask_RangeCode          = coder.typeof( false(500, 500),             [inf, inf],  [1, 1] );        %logical           
                 
                    
%%%%%% Specify fixed-size input arguments %%%%%%

NRows_MatrixCode               = int32(0);
NCols_MatrixCode               = int32(0);
CountTrueTFCode                = false;
TailoredThresholdsTFCode       = false;
ReturnYTFCode                  = false;
ReturnCbCrTFCode               = false;
ReturnHSTFCode                 = false;
TailoredThresholdsSevereTFCode = false;
MorphCloseSevereTFCode         = false;
XOffsetCode                    = int32(0);
YOffsetCode                    = int32(0);

%Struct with fixed-size fields
%Note: the order and names of fields are compile-time constants.

SkinSegmentArgsCode = ...                                                                                              
    struct( ...
        'SkinColorSamples_NThresholdPassedTF', false, ...
        'YCbCrThresholdsGeneric', zeros(1, 7, 'single'), ...
        'HSThresholdsGeneric', zeros(1, 2, 'single'), ...
        'YCbCrThresholdsTailored', zeros(1, 8, 'single'), ...
        'YCbCrThresholdsTailored_Sev', zeros(1, 8, 'single'), ...
        'HSThresholdsTailored', zeros(1, 3, 'single'), ...
        'HSThresholdsTailored_Sev', zeros(1, 3, 'single'), ...
        'RangeSEWidth', int16(0), ...
        'RangeThreshold', uint8(0), ...
        'MorphCloseSEMediumWidth_Tuned', int16(0), ...
        'MorphCloseSELargeWidth_Tuned', int16(0) ...   
    );                                                                   


%%%%%% Set configurations to increase performance %%%%%%

%Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic 
%"Optimization Strategies"

cfg = coder.config('mex');
cfg.GlobalDataSyncMethod = 'NoSync';
cfg.ConstantInputs = 'IgnoreValues';
cfg.ExtrinsicCalls = false; 
cfg.SaturateOnIntegerOverflow = false;
cfg.IntegrityChecks = false;
cfg.ResponsivenessChecks = false;


%%%%%% Specify flags to minGW compiler to optimize execution speed %%%%%%

%For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

%The flags are specified as part of the code-generation configuration object. A custom function,
%setbuildargs, is used to specify these flags. For details on the function implementation, see the 
%function file, which is located within folder FacePulseRate. This custom function is based upon 
%Matlab guidance found in
%https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function

%setbuildargs will be evaluated from text within the code-generation object, so it is converted to 
%a character vector prior to execution of the codegen command.

%%%%%% --- Specify the flags as arguments to function setbuildargs %%%%%%

%Argument buildInfo: this variable is assign by the caller (the codegen command executed 
%below) and is not present in the base workspace.

%Second argument: specify a cell array of compiler-specific flags, where each flag is a 
%character vector. As function setbuildargs will be evaluated from text, use double ' quotes for 
%each character vector to maintain the charater vector,
%e.g., {''-Ofast'' ''-fsingle-precision-constant''}.

setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})';

%Assign to code-generation configuration object
cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen SkinSegmentMask_Ops.m -report -config cfg -args {RUint8Code, GUint8Code, BUint8Code, YSingleCode, CbSingleCode, CrSingleCode, HSingleCode, SSingleCode, IsSkinMask_RangeCode, NRows_MatrixCode, NCols_MatrixCode, CountTrueTFCode, TailoredThresholdsTFCode, ReturnYTFCode, ReturnCbCrTFCode, ReturnHSTFCode, TailoredThresholdsSevereTFCode, MorphCloseSevereTFCode, XOffsetCode, YOffsetCode, SkinSegmentArgsCode}
             
%}




