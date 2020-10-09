function [SkinRGBMeans_i, IsNotSkin_PixelColor_Packed_i, AdjustedBecauseLowSkinProportionTF_i, ...
          ROIAdjusted_i, Mean_Y_of_YCbCr_i, Mean_L_of_LAB_i] = ...
             ROIMeans_TakeMeans(i, VidFrame, ROI, SkinSegmentConfig, ...
                 PulseRateConfigAndData_ControlLuminanceTF, ...                 
                 PulseRateConfigAndData_ControlLuminanceColorspace, OutputConfig_WriteVideoTF, ...
                 OutputConfig_WriteVideoShowSkinSegmentTF, VideoReadConfig_FrameIdx, ...
                 VideoReadConfig_VidObjWidth, VideoReadConfig_VidObjHeight, ...
                 ROIGeneralConfig_ROIMSIR_FirstFrameIdx, FirstReadTF) %#codegen                              
%ROIMeans_TakeMeans   Apply skin-segmentation to, and then calculate the RGB means and the  
%                     luminance mean from, the ROI of a frame. 
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions ROIMeans_FirstRead and 
%    ROIMeans_SecondRead_TakeMeans.
%
%
%    Code Generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.
%
%    Although this function has been prepared for code generation, testing has indicated that, for 
%    the current implementation of the function, the Matlab code performs better than the  
%    compiled C executable. Hence, the Matlab code version is used in function FacePulseRate.   
%
%
%    Description
%    -----------
%
%    First, crop the video frame to the ROI and break it into colorspace channels. Then, apply skin 
%    segmentation if it is enabled. Finally, take the means of the color channels. If skin
%    segmentation is enabled, only pixels classified as skin will be included in the means. 
%
%    The means are taken from the R, G, and B channels and either the L channel of the LAB 
%    colorspace or the Y channel of the YCbCr colorspace. The R, G, and B means are used to 
%    estimate pulse rate in function PulseRate. The Y and L channels represent luminance; the mean
%    from one of these channels will be used in function PulseRate to control pulse rate for 
%    variations in luminance across frames.
%
%    If an ROI (rather than the entire frame) is used, determine the proportion of pixels 
%    classified as skin within the ROI to the number of pixels within the ROI. To attempt to 
%    increase the accuracy of the ROI, if the proportion is below a threshold, replace the ROI with 
%    the ROI from a previous frame. If the ROI is replaced, return the ROI used as a replacement
%    (ROIAdjusted_i) and return flag AdjustedBecauseLowSkinProportionTF_i as true.
%
%    Compress and store the skin-segmentation mask for later use in function WriteFaceVideo for
%    displaying skin-segmentation results. This prevents the computational time associated with
%    rerunning skin-segmentation operations in function WriteFaceVideo.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code-generation settings %%%%%%

%Call function as extrinsic so that stack trace can be displayed
coder.extrinsic('error');

%Declare variable-size variables:

%                                  Upp. Bounds    Var. Size (T/F)
coder.varsize('IsSkinMask',        [inf, inf],    [1, 1]);
coder.varsize('ROIAdjusted_i',     [1, 4],        [1, 0]);
coder.varsize('Mean_Y_of_YCbCr_i', [1, 1],        [1, 0]);
coder.varsize('Mean_L_of_LAB_i',   [1, 1],        [1, 0]);


%%%%%% Crop video frame to ROI and conduct skin segmentation %%%%%% 

% - Crop video frame to ROI and return the cropped frame in R, G, B, and Y color channels. 
% - If skin segmentation is enabled, also return a skin-segmentation mask.
% - If skin segmentation is disabled, the Y color channel will be returned as empty.

%Local function.
[IsSkinMask, TrueCount_i, IsSkinMaskAnyTF, YROI_Single, AdjustedBecauseLowSkinProportionTF_i, ...
 ROIAdjusted_i, RROI_Uint8, GROI_Uint8, BROI_Uint8, IsNotSkin_PixelColor_Packed_i, nRows_ROI, ... 
 nCols_ROI] = ...
    CropAndSkinSegment(i, VidFrame, SkinSegmentConfig, ROIGeneralConfig_ROIMSIR_FirstFrameIdx, ...
        ROI, VideoReadConfig_FrameIdx, OutputConfig_WriteVideoTF, ...       
        OutputConfig_WriteVideoShowSkinSegmentTF, VideoReadConfig_VidObjWidth, ...
        VideoReadConfig_VidObjHeight, FirstReadTF); 


%%%%%% Take means of color channels %%%%%% 

% - Take means of red, green, and blue color channels of ROI.
% - Return luminance mean from either the LAB colorspace or the YCbCr colorspace, depending on
%   argument PulseRateConfigAndData.ControlLuminanceColorspace.
% - If skin segmentation is enabled, pixels classified as non-skin will be excluded from the means.

%Local function.
[SkinRGBMeans_i, Mean_Y_of_YCbCr_i, Mean_L_of_LAB_i] = ...
    TakeMeans(SkinSegmentConfig, IsSkinMaskAnyTF, IsSkinMask, TrueCount_i, RROI_Uint8, ...
        GROI_Uint8, BROI_Uint8, nRows_ROI, nCols_ROI, ...
        PulseRateConfigAndData_ControlLuminanceTF, ...
        PulseRateConfigAndData_ControlLuminanceColorspace, YROI_Single);
        
    
end %end main function


%=============================================================================================
%Local functions 
%=============================================================================================


%=============================================================================================
function [IsSkinMask, TrueCount_i, IsSkinMaskAnyTF, YROI_Single, ...
          AdjustedBecauseLowSkinProportionTF_i, ROIAdjusted_i, RROI_Uint8, GROI_Uint8, ... 
          BROI_Uint8, IsNotSkin_PixelColor_Packed_i, nRows_ROI, nCols_ROI] = ...
             CropAndSkinSegment(i, VidFrame, SkinSegmentConfig, ...
                 ROIGeneralConfig_ROIMSIR_FirstFrameIdx, ROI, VideoReadConfig_FrameIdx, ...
                 WriteVideoTF, WriteVideoShowSkinSegmentTF, VideoReadConfig_VidObjWidth, ...
                 VideoReadConfig_VidObjHeight, FirstReadTF)                                 
%CropAndSkinSegment.  Crop the frame to the ROI and return a skin-segmentation mask.  
%
%    Description:
%
%    The frame is cropped to the ROI and broken down into the R, G, and B color channels. These
%    color channels are returned. 
%
%    If skin segmentation is enabled, a logical matrix (IsSkinMask) is returned where pixels 
%    classified as skin are true. This mask corresponds to an ROI if an ROI is available; 
%    otherwise, the mask will correspond to the full frame. If skin segmentation is enabled, the
%    Y color channel will also be returned.
%    
%    If an ROI (rather than the entire frame) is used, determine the proportion of pixels 
%    classified as skin within the ROI to the number of pixels within the ROI. To attempt to 
%    increase the accuracy of the ROI, if the proportion is below a threshold, replace the ROI with 
%    the ROI from a previous frame. If the ROI is replaced, return the ROI used as a replacement
%    (ROIAdjusted_i) and return flag AdjustedBecauseLowSkinProportionTF_i as true.
%
%    Finally, the skin-segmentation mask in a compressed form (a packed binary image) is returned   
%    to be used in function WriteFaceVideo for superimposing the mask on the output video.


%%%%%% Code generation settings %%%%%%

%Inline function
coder.inline('always');

%Declare variable-size variables:

%                                              Upp. Bounds    Var. Size (T/F)
coder.varsize('SkinSegmentMask_LocalRange',    [1, 1],        [1, 1]);
coder.varsize('IsNotSkin_PixelColor_Packed_i', [200, 5000],   [1, 1]);


%%%%%% Initialize values %%%%%%
    
IsSkinMask                           = logical([]);
AdjustedBecauseLowSkinProportionTF_i = false; 
ROIAdjusted_i                        = zeros(0, 4, 'int16');
YROI_Single                          = single([]);
TrueCount_i                          = uint32(0); 


%%%%%% Crop frame to ROI and separate by color channels %%%%%%

%Crop ROI from frame if frame has ROI. Otherwise, use full frame as ROI. 
    
%Dimensions of cropped frame
%Scalars; int32.
%Note: int32 is the specified input type for some mex functions.
x_ROI_int16 = ROI(i, 1);
y_ROI_int16 = ROI(i, 2);
nRows_ROI   = int32( ROI(i, 4) );
nCols_ROI   = int32( ROI(i, 3) );    

%Assert values to prevent dynamic memory allocation where the colon operator is used
assert(nRows_ROI < 5001);
assert(nCols_ROI < 5001);

%Crop frame to ROI and separate by color channel
%Local function.
[RROI_Uint8, GROI_Uint8, BROI_Uint8] = ...
    CropSeparateChannels(VidFrame, x_ROI_int16, y_ROI_int16, nRows_ROI, nCols_ROI, ...
        VideoReadConfig_VidObjWidth, VideoReadConfig_VidObjHeight);
    

%%%%%% Segment skin %%%%%%

%If skin segmentation enabled
if SkinSegmentConfig.SkinSegmentTF

    %Arguments to function SkinSegmentMask, which returns skin segmentation mask:

    % - Specify that tailored thresholds should be used
    %   TailoredThresholdsTF is true to provide greater accuracy and because tailored thresholds      
    %   have previously been set (by function SkinSegment_SetThresholds).  
    TailoredThresholdsTF = true;

    % - Return the Y channel of the YCbCr colorspace
    ReturnYTF = true;

    % - Do not return the Cb and Cr channels of the YCbCr colorspace
    ReturnCbCrTF = false;

    % - Do not return the H or S channels of the HSV colorspace
    ReturnHSTF = false;

    % - Whether to return a count of pixels classified as skin 
    CountTrueTF = true;

    % - Do not use severe tailored thresholds
    TailoredThresholdsSevereTF = false;  

    % - MorphCloseSevereTF is set as false to avoid false negatives (at the expense of false 
    %   positives). 
    MorphCloseSevereTF = false; 

    % - Set as variable rather than constant for code-generation purposes
    SkinSegmentMask_LocalRange = logical([]);

    %Note: for details on the arguments specified by SkinSegmentConfig.Args, see file
    %SkinSegment_ConfigSetup.m. 

    %Note: SkinSegmentMask is a custom function located within folder FacePulseRate.
    [IsSkinMask,     ... Skin-segmentation mask; M x N matrix, type logical
     TrueCount_i,    ... Count of pixels classified as skin; scalar, type uint32   
     YROI_Single] =  ... Y channel of YCbCr colorspace; M x N matrix, type single
        SkinSegmentMask( ...
            RROI_Uint8,                              ... Bounded frame separated by channel; type 
                                                     ... uint8.
            GROI_Uint8, ...
            BROI_Uint8, ... 
            single([]),                              ... Unused arguments     
            single([]), ...
            single([]), ...
            single([]), ...                                
            single([]), ... 
            SkinSegmentMask_LocalRange, ...  
            nRows_ROI,                               ... Number of rows of an input matrix; type 
                                                     ... int32.      
            nCols_ROI,                               ... Number of columns of an input matrix; type 
                                                     ... int32. 
            CountTrueTF,                             ... Whether to return a count of pixels  
                                                     ... classified as skin.
            TailoredThresholdsTF,                    ... Whether to use thresholds that are 
                                                     ... tailored.
            ReturnYTF,                               ... Whether to return Y channel of the YCbCr 
                                                     ... colorspace.
            ReturnCbCrTF,                            ... Whether to return Cb and Cr channels of  
                                                     ... the YCbCr colorspace. 
            ReturnHSTF,                              ... Whether to return the H and S channels of 
                                                     ... the HSV colorspace.  
            TailoredThresholdsSevereTF,              ... Whether to use severe tailored thresholds            
            MorphCloseSevereTF,                      ... Whether the morphological close operation   
                                                     ... will be conducted with a high level of 
                                                     ... severity.
            int32(-1),                               ... Optional X-coordinate offset; use -1 to  
                                                     ... ignore; type int32.
            int32(-1),                               ... Optional Y-coordinate offset; use -1 to 
                                                     ... ignore; type int32.                                                 
            SkinSegmentConfig.Args,                  ... Configurations
            SkinSegmentConfig.UseCompiledFunctionsTF ... Whether to use compiled functions 
        );


    %%%%%% Adjust ROI if proportion of pixels classified as skin in ROI is below threshold %%%%%%

    %The ROI is considered valid if the proportion of pixels classified as skin exceeds a specified
    %threshold. The proportion is calculated by inspecting the skin-segmentation mask, which  
    %corresponds to the location of the ROI. Specifically, from the skin-segmentation mask, the   
    %number of elements classified as true is divided by the total number of elements. This 
    %calculation is conducted by function ConfirmSkinPresent. This function returns a true / false
    %determination on whether the proportion exceeded the specified threshold 
    %(SkinSegmentConfig.ConfirmSkin).    
    
    %If the ROI is considered invalid, it will be replaced with an ROI from a previous frame to 
    %attempt to increase accuracy. The ROI will come from a few frames back because it has been 
    %observed that the proportion threshold is typically activated several frames after the ROI 
    %began to drift from the face. 

    %Specify condition for skin-color proportion check
    FaceAlgorithm = 'm'; %indication to use the threshold for use with taking means  

    %Note: 'ConfirmSkinPresent' is a custom function located within folder 'FacePulseRate'.
    SkinColorTF = ... true/false indication on whether the proportion is above the threshold
        ConfirmSkinPresent( ...
            SkinSegmentConfig, ... data and configurations
            FaceAlgorithm, ... 
            IsSkinMask, ...
            single(TrueCount_i), ...
            nRows_ROI, ...
            nCols_ROI ...        
        );

    %If the proportion is considered valid
    if SkinColorTF 
        
        %Flag that the ROI was not replaced
        AdjustedBecauseLowSkinProportionTF_i = false; 

        %Assign empty values
        ROIAdjusted_i = zeros(0, 4, 'int16');

    %If the proportion is considered invalid
    else

        %The number of frames back from which to retrieve a replacement ROI
        FramesBack = int32(4);

        %Conditions when a previous ROI is available for retrieval:

        %During the first-read operations, a previous frame will not be available if the current 
        %frame  is near the first frame where ROI operations began  
        %(ROIGeneralConfig.ROIMSIR_FirstFrameIdx). During second-read operations, a previous frame 
        %will not be available if the current frame is near the beginning of the video. Note that, 
        %perhaps counterintuitively, the second-read operations begin at the beginning of the video 
        %whereas the first-read operations begin farther into the video.

        %Initialize flag that a previous ROI is available for retrieval
        ReplaceROIOK = false;

        %Current frame read during first-read operations        
        if FirstReadTF

            if i >= ROIGeneralConfig_ROIMSIR_FirstFrameIdx + FramesBack 

                ReplaceROIOK = true;
            end        

        %Current frame read during second-read operations           
        else
             if i - FramesBack > 0

                ReplaceROIOK = true;
            end                
        end   

        %If a previous ROI can be retrieved, replace the current ROI with a previous ROI 
        if ReplaceROIOK

            %Indicate that ROI was adjusted for display on output video
            %Note: annotation superimposed on output video by function 
            %WriteFaceVideo_ROIAnnotation.
            AdjustedBecauseLowSkinProportionTF_i = true;                                   

            %Frame index of replacement ROI
            FrameIdx_Replacement = i - FramesBack;

            %Replace the ith ROI coordinates with the ROI of a previous frame
            %1 x 4 row vector; type int16.                
            ROIAdjusted_i = ROI(FrameIdx_Replacement, :);       

            %Check if any value of the previous ROI is zero
            %The operations of this function were intended to prevent values of zero, so such a   
            %value is likely due to an implementation error in this function. 
            if ROIAdjusted_i(1) == 0 || ...
               ROIAdjusted_i(2) == 0 || ...
               ROIAdjusted_i(3) == 0 || ...
               ROIAdjusted_i(4) == 0

                %Display error indicating frame index
                error(...
                    'Component:InternalError', ...
                    ['Internal Error: An ROI adjustment operation assigned a value of zero', ...
                     ' for an ROI. ROI accuracy may be affected. The frame index of the', ...
                     ' corresponding frame is: ', ...
                     sprintf( '%d', int32( VideoReadConfig_FrameIdx(FrameIdx_Replacement) ) ), ...
                     '.'] ...
                );              
            end

            %Determine the number of rows and columns of adjusted ROI
            %Scalars; int32.
            %Note: int32 is the specified input type for some mex functions.
            nRows_ROI = int32( ROIAdjusted_i(4) );
            nCols_ROI = int32( ROIAdjusted_i(3) );         

            %Assert values to prevent dynamic memory allocation where the colon operator is used
            assert(nRows_ROI < 5001);
            assert(nCols_ROI < 5001);        

            %Crop frame using new ROI and separate by color channel
            %Local function.
            [RROI_Uint8, GROI_Uint8, BROI_Uint8] = ...
                CropSeparateChannels(VidFrame, ROIAdjusted_i(1), ROIAdjusted_i(2), nRows_ROI, ...
                     nCols_ROI, VideoReadConfig_VidObjWidth, VideoReadConfig_VidObjHeight);   

            %Segment skin within new ROI:

            %Note: SkinSegmentMask is a custom function located within folder FacePulseRate.
            [IsSkinMask, ... M x N matrix; type logical 
             TrueCount_i,  ... Count of pixels classified as skin; scalar, type uint32   
             YROI_Single] =  ... M x N matrix; type single
                SkinSegmentMask( ...
                    RROI_Uint8, ... 
                    GROI_Uint8, ...
                    BROI_Uint8, ... 
                    single([]), ...                               
                    single([]), ...
                    single([]), ...
                    single([]), ...                                
                    single([]), ...
                    SkinSegmentMask_LocalRange, ...  
                    nRows_ROI, ...     
                    nCols_ROI, ... 
                    CountTrueTF, ...
                    TailoredThresholdsTF, ...
                    ReturnYTF, ... 
                    ReturnCbCrTF, ...  
                    ReturnHSTF, ... 
                    TailoredThresholdsSevereTF, ...
                    MorphCloseSevereTF, ... 
                    int32(-1), ...
                    int32(-1), ...             
                    SkinSegmentConfig.Args, ...
                    SkinSegmentConfig.UseCompiledFunctionsTF ... 
                ); 

        %If a previous ROI cannot be retrieved    
        else

            AdjustedBecauseLowSkinProportionTF_i = false;

            %Assign empty values
            ROIAdjusted_i = zeros(0, 4, 'int16');      
        end
    end %end skin-proportion check
end

%%%%%% Store skin-segmentation mask for later use in writing video %%%%%%    

%Compress and store the output from function SkinSegmentMask to structs for later use in function 
%WriteFaceVideo for displaying skin segmentation results. This prevents the computational time 
%associated with rerunning function SkinSegmentMask in that function.

%If video writing is enabled and showing skin segmentation on output video is enabled
if WriteVideoTF && WriteVideoShowSkinSegmentTF 

    %Note: ROIMeans_TakeMeans_StoreMaskForVideoWrite is a custom function located within folder 
    %'FacePulseRate'.
    IsNotSkin_PixelColor_Packed_i = ...         
        ROIMeans_TakeMeans_StoreMaskForVideoWrite(IsSkinMask);

else
    
    IsNotSkin_PixelColor_Packed_i = uint32([]);
    
end %end if video writing is enabled and showing skin segmentation on output video is enabled


%%%%%% Determine whether there is at least one unsegmented pixel in ROI %%%%%%

%This flag will be used to determine whether to take the means.
IsSkinMaskAnyTF = TrueCount_i > 0;    
    
    
end %end local function


%=============================================================================================
function [SkinRGBMeans_i, Mean_Y_of_YCbCr_i, Mean_L_of_LAB_i] = ...
             TakeMeans(SkinSegmentConfig, IsSkinMaskAnyTF, IsSkinMask, TrueCount, RROI_Uint8, ...
                 GROI_Uint8, BROI_Uint8, nRows_ROI, nCols_ROI, ...
                 PulseRateConfigAndData_ControlLuminanceTF, ...
                 PulseRateConfigAndData_ControlLuminanceColorspace, LuminanceMatrix_Single)
%TakeMeans.  Take the R, G, and B means of the RGB colorspace and the luminance mean.  
%
%    Description:
%
%    --- RGB Means ---
%
%    Take the R, G, and B means from the either the portion of the frame that corresponds to the 
%    ROI or, if an ROI was not identified, the entire frame.
%
%    If skin segmentation is enabled, the means will be taken from vectors RUint8, GUint8, BUint8, 
%    which contain the pixels classified as skin. Otherwise, the means will be taken from the 
%    three-dimensional array AreaToTakeMean, where the R, G, and B channels are still in their 
%    concatenated form.
%
%   --- Luminance Means ---
%
%    Take the luminance mean from the either the portion of the frame that corresponds to the ROI
%    or, if an ROI was not identified, the entire frame. The luminance mean is used to control the
%    RGB means for luminance variation across frames during the pulse rate operations (see function
%    PulseRate). The use of the luminance means to control for luminance variation was adapted from
%    Madan et al. (2018).
%
%    Take the luminance mean either from the Y channel of the YCbCr colorspace or the L channel of 
%    the LAB colorspace. The colorspace to be used is specified by 
%    PulseRateConfigAndData.ControlLuminanceColorspace, which is an argument to function
%    FacePulseRate. Using the YCbCr colorspace is more efficient because the frame (or portion of)
%    was previously converted to the YCbCr colorspace during the skin-segmentation operations. The
%    LAB colorspace might be used for closer adherance to the colorspace used by Madan et al. 
%    (2018).                   
%
%    References:
%
%    Madan, C. R., Harrison, T., & Mathewson, K. E. (2018). Noncontact measurement of emotional and 
%    physiological changes in heart rate from a webcam. Psychophysiology, 55(4), e13005.       


%%%%%% Code generation settings %%%%%%

%Inline function
coder.inline('always');

%Declare variable-size variables:

%                                    Upp. Bounds    Var. Size (T/F)
coder.varsize('Mean_Y_of_YCbCr_i',   [1, 1],        [1, 0]);
coder.varsize('Mean_L_of_LAB_i',     [1, 1],        [1, 0]);


%%%%%% Initialize variables %%%%%%

%Note: Type double is assigned because required for regression in pulse rate operations.

Mean_Y_of_YCbCr_i = zeros(0, 1, 'double');
Mean_L_of_LAB_i   = zeros(0, 1, 'double');


%%%%%% Take means %%%%%%

%%%%%% --- Apply skin segmentation mask %%%%%%

%If skin segmentation enabled
if SkinSegmentConfig.SkinSegmentTF 

    %Take mean of each color channel where IsSkinMask is true.

    %If at least one pixel in ROI classified as skin
    if IsSkinMaskAnyTF

        %If the L channel of the LAB colorspace will be used as the luminance channel
        %Note: this code block has not yet been optimized for C-code generation.
        if PulseRateConfigAndData_ControlLuminanceColorspace == 'L' 
            
            %Convert from RGB to LAB colorspace
            %M x N x 3 array; type double.
            LABROI_Double = rgb2lab( cat(3, RROI_Uint8, GROI_Uint8, BROI_Uint8) );                 
            
            %Extract L color channel and cast to type single       
            LuminanceMatrix_Single = single( LABROI_Double(:, :, 1) );            
        end        
        
        %Take means 
        
        %If code generationg running or if compiled functions not enabled
        if  ~ coder.target('MATLAB') || ... code generation running
            ~ SkinSegmentConfig.UseCompiledFunctionsTF %compiled not functions enabled       
        
            %Note: IndexAndMean_LogIdx is a custom function located within folder 'FacePulseRate'. 
            [SkinRGBMeans_i,        ... 1 x 3 row vector; type double.
             SkinLuminanceMean_i] = ... Scalar; type double.
                IndexAndMean_LogIdx( ...
                    RROI_Uint8, GROI_Uint8, BROI_Uint8,        ... Color channels of type uint8
                    LuminanceMatrix_Single,                    ... Luminance channel of type single
                    IsSkinMask,                                ... Logical matrix; type logical
                    nRows_ROI,                                 ... Dimension of one of the input 
                                                               ... matrices.
                    nCols_ROI,                                 ... Number of pixels classified as 
                                                               ... skin.
                    TrueCount, ...
                    PulseRateConfigAndData_ControlLuminanceTF); %  Whether to take luminance mean 
                
        %If code generation not running and compiled functions enabled        
        else

            %Note: IndexAndMean_LogIdx is a custom function located within folder 'FacePulseRate'. 
            [SkinRGBMeans_i,        ... 1 x 3 row vector; type double.
             SkinLuminanceMean_i] = ... Scalar; type double.
                IndexAndMean_LogIdx_mex( ...
                    RROI_Uint8, GROI_Uint8, BROI_Uint8,        ... Color channels of type uint8
                    LuminanceMatrix_Single,                    ... Luminance channel of type single
                    IsSkinMask,                                ... Logical matrix; type logical
                    nRows_ROI,                                 ... Dimension of one of the input 
                                                               ... matrices.
                    nCols_ROI,                                 ... Number of pixels classified as 
                                                               ... skin.
                    TrueCount, ...
                    PulseRateConfigAndData_ControlLuminanceTF); %  Whether to take luminance mean            
        end
        
        %Assign luminance mean
        if PulseRateConfigAndData_ControlLuminanceColorspace == 'Y' 
            
            Mean_Y_of_YCbCr_i = SkinLuminanceMean_i;
            
        else %PulseRateConfigAndData_ControlLuminanceColorspace == 'L' 
            
            Mean_L_of_LAB_i = SkinLuminanceMean_i;
        end
        
    %All pixels in ROI are segmentated
    else

        %Assign NaN
        %1 x 3 row vector; type double.
        %Note: before pulse rate operations are conducted, function PulseRate will interpolate
        %values assigned NaN.            
        SkinRGBMeans_i = nan(1, 3, 'double');
        
        %Assign NaN
        %Scalar; type double.
        %Note: before pulse rate operations are conducted, function  
        %PulseRate_ControlForLuminance will interpolate values assigned NaN.
        Mean_Y_of_YCbCr_i = nan(1, 1, 'double');
        Mean_L_of_LAB_i   = nan(1, 1, 'double');
    end
    
%%%%%% --- Do not apply skin segmentation mask %%%%%%    
    
%Skin segmentation disabled
%Note: this code block has not yet been optimized for C-code generation
else 

    %Number of elements 
    NElements = double(nRows_ROI * nCols_ROI);
    
    %Take RGB means
    %1 x 3 row vector; type double.
    SkinRGBMeans_i = coder.nullcopy( zeros(1, 3, 'double') );
        
    SkinRGBMeans_i(1) = sum(RROI_Uint8) / NElements; 
    SkinRGBMeans_i(2) = sum(GROI_Uint8) / NElements;
    SkinRGBMeans_i(3) = sum(BROI_Uint8) / NElements;
    
    %%%%%% >>>>>> Take the luminance mean %%%%%%
    
    %If taking the luminance mean is enabled
    if PulseRateConfigAndData_ControlLuminanceTF

        %Take the mean of the luminance channel (Y) of the YCbCr colorspace:
        
        %If Y is used as the luminance channel
        if PulseRateConfigAndData_ControlLuminanceColorspace == 'Y'
        
            %Convert frame to YCbCr colorspace
            %M x N array; type uint8.
            YCbCrROI_Uint8 = rgb2ycbcr( cat(3, RROI_Uint8, GROI_Uint8, BROI_Uint8) );

            %Extract Y color channel
            %M x N matrix; type uint8.
            YROI_Uint8 = YCbCrROI_Uint8(:, :, 1);

            %Take mean
            %Type double
            %Note: functions sum() and numel() return type double when the input is an integer 
            %type, which is the case.
            %Scalar; type double.
            Mean_Y_of_YCbCr_i = sum(YROI_Uint8) / NElements; 

        %Take the mean of the luminance channel (L) of the LAB colorspace:
        
        %If L is used as the luminance channel 
        else %PulseRateConfigAndData_ControlLuminanceColorspace == 'L'        
            
            %Convert from RGB to LAB colorspace
            %M x N x 3 array; type double.
            LABROI_Double = rgb2lab( cat(3, RROI_Uint8, GROI_Uint8, BROI_Uint8) );

            %Extract L color channel        
            LROI_Double = LABROI_Double(:, :, 1);

            %Take mean
            %Scalar; type double.
            Mean_L_of_LAB_i = sum(LROI_Double) / NElements;            
        end
    end
end


end %end local function


%=============================================================================================
function [RROI_Uint8, GROI_Uint8, BROI_Uint8] = ...
             CropSeparateChannels(VidFrame, x_ROI_int16, y_ROI_int16, nRows_ROI, nCols_ROI, ...
                 nCols_Full_int16, nRows_Full_int16)                
%CropSeparateChannels  Crop the input frame and separate it into its colorspace channels.
%
%    Note: 
%
%    The parfor-loop is slower than a for-loop when run in Matlab code, so use the parfor-loop only  
%    for code generation.


%%%%%% Code-generation settings %%%%%%

%Inline function
coder.inline('always');


%%%%%% Code generation running %%%%%%

%If code generation running
if ~ coder.target('MATLAB') 

    %Cast to int32 to prevent overflow when converting to linear index
    %Scalars; type int32.
    nCols_Full = int32(nCols_Full_int16); 
    nRows_Full = int32(nRows_Full_int16);
    
    %X and Y-coordinates to crop to
    %Cast to int32 to prevent overflow when converting to linear index.
    %Scalars; type int32.
    x_crop = int32( x_ROI_int16 ); 
    y_crop = int32( y_ROI_int16 ); 

    %Preallocate channel matrices:
    
    %Red channel
    %M x N matrix; type uint8.
    RROI_Uint8 = coder.nullcopy( zeros(nRows_ROI, nCols_ROI, 'uint8') );
    
    %Green channel
    %M x N matrix; type uint8.
    GROI_Uint8 = coder.nullcopy( zeros(nRows_ROI, nCols_ROI, 'uint8') );
    
    %Blue channel
    %M x N matrix; type uint8.
    BROI_Uint8 = coder.nullcopy( zeros(nRows_ROI, nCols_ROI, 'uint8') );

    %Crop offsets
    %Scalars; type int32.
    %Note: the step prevents repeated subtraction by one in the parfor loop.
    ColOffset = x_crop - 1;
    RowOffset = y_crop - 1;    
    
    %Number of elements in one color channel of the full frame
    %Scalar; type int32.
    NPageElements = nCols_Full * nRows_Full;
    
    %Number multiplied by 2
    %Scalar; type int32.
    NPageElementsBy2 = NPageElements * 2;
    
    %Crop to ROI and separate by color channel:
    
    %Loop across columns
    parfor i = 1 : nCols_ROI 

        %Adjust column index to align with coordinate plane of full frame
        iFull = i + ColOffset;
        
        %Loop across rows
        for j = 1 : nRows_ROI             
            
            %Adjust row index to align with coordinate plane of full frame
            jFull = j + RowOffset;
            
            %Convert from subscript indices to a linear index for more efficient indexing
            %Scalar; type int32.
            %Note: In compiled C code, the faster indexing outweighs the cost of this conversion.
            LinIdxFull = jFull + (iFull - 1) * nRows_Full;
            
            %Red channel element:
            
            %Extract value from full frame                      
            jth = VidFrame(LinIdxFull); %#ok<PFBNS>

            %Insert value into bounded frame
            RROI_Uint8(j, i) = jth;

            %Green channel element:
            
            %Extract value from full frame
            jth = VidFrame(LinIdxFull + NPageElements); 

            %Insert value into bounded frame
            GROI_Uint8(j, i) = jth;

            %Blue channel element:
            
            %Extract value from full frame
            jth = VidFrame(LinIdxFull + NPageElementsBy2);

            %Insert value into bounded frame
            BROI_Uint8(j, i) = jth;
        end       
    end

    
%%%%%% Code generation not running %%%%%%   

else 

    %Crop ROI from frame
    %M x N x 3 array; type uint8.
    VidFrame = ...
        VidFrame( ...
            y_ROI_int16 : y_ROI_int16 + int16(nRows_ROI - 1), ... rows
            x_ROI_int16 : x_ROI_int16 + int16(nCols_ROI - 1), ... columns
            :                                                 ... pages
        ); 
    
    %Separate by color channel
    %M x N matrices; type uint8.
    RROI_Uint8 = VidFrame(:, :, 1); %Red channel
    GROI_Uint8 = VidFrame(:, :, 2); %Green channel
    BROI_Uint8 = VidFrame(:, :, 3); %Blue channel
end


end %end local function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(ROIMeans_TakeMeans_mex) of the function.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%                                            Example Code                    Upp. Bounds       Var. Size (T/F)    Type
VidFrameCode                 = coder.typeof( zeros(500, 500, 3, 'uint8'),    [inf, inf, 3],    [1, 1, 0] );       %uint8 
ROICode                      = coder.typeof( zeros(500, 4, 'int16'),         [inf, 4],         [1, 0] );          %int16
VideoReadConfig_FrameIdxCode = coder.typeof( zeros(1, 500, 'int32'),         [1, inf],         [0, 1] );          %uint32
         
      
%%%%%% Specify fixed-size input arguments %%%%%%

iCode                                                 = int32(0);
PulseRateConfigAndData_ControlLuminanceTFCode         = false;
PulseRateConfigAndData_ControlLuminanceColorspaceCode = ' ';
WriteVideoTFCode                                      = false;
WriteVideoShowSkinSegmentTFCode                       = false;
ROIGeneralConfig_ROIMSIR_FirstFrameIdxCode            = int32(0);
VideoReadConfig_VidObjWidthCode                       = int16(0);
VideoReadConfig_VidObjHeightCode                      = int16(0);
FirstReadTFCode                                       = false;

%Struct with fixed-size fields
%Note: the order and names of fields are compile-time constants.

SkinSegmentConfigCode = ...
    struct( ...
        'SkinSegmentTF', false, ... Whether skin segmentation enabled
        'SkinSegmentSeverityFactor', double(0), ... For tuning severity of skin segmentation
        'MorphCloseSEMediumWidth', double(0), ... Width of structuring element for medium 
                                              ... morphological close before tuning.
        'MorphCloseSELargeWidth', double(0), ... Width of structuring element for large 
                                             ... morphological close before tuning.        
        'UseCompiledFunctionsTF', false, ... Whether to use compiled functions        
        'Args', ... Arguments to fuction SkinSegmentMask 
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
        ), ... 
        'TailoredData', ... Tailored skin-segmentation settings
        struct( ...
            ... Properties determining whether SkinSegment_SetThresholds will be called in function
            ... ROIMeans_FirstRead:
            'OpsReadyTF', false, ...
            'RecentThresholdOpsFrameIdx', int32(0), ...
            'ThresholdOpsInterval', int32(0), ...
            'ThresholdOpsRunCurrentFrameTF', false, ...
            ... Arguments to function SkinSegment_SetThresholds, which sets thresholds for the
            ... "tailored" option used by function SkinSegmentMask:
            'SkinColorSamples_NThreshold', double(0), ...
            'RangePercentile_YCbCrH', zeros(1, 2, 'double'), ...
            'RangePercentile_S', zeros(1, 2, 'double'), ...
            'SkinColorSamples_HighNThreshold', double(0), ...
            'SkinColorSamples_HighNThresholdPassedTF', false, ...
            'RangePercentileHighN_YCbCrH', zeros(1, 2, 'double'), ...
            'RangePercentileHighN_S', zeros(1, 2, 'double'), ...
            'RangePercentileSev_YCbCrH', zeros(1, 2, 'double'), ...
            'RangePercentileSev_S', zeros(1, 2, 'double') ...
        ), ...
        ... Values used by function ConfirmSkinPresent depending on the argument 
        ... PixelColorThresholdsType:
        'ConfirmSkin', ... 
        struct( ...
            'ProportionThresholdPrimary',    single(0), ...
            'ProportionThresholdSecondary1', single(0), ...
            'ProportionThresholdSecondary2', single(0), ...
            'ProportionThresholdSkin',       single(0), ...
            'ProportionThresholdMeans',      single(0)  ...
        ), ...
        'OverSegmentedCheck', ...
        struct( ...
            'CheckTF',                          false, ...
            'ProportionThresholdPrimary',       single(0), ...
            'ProportionThresholdSecondary1',    single(0), ...
            'ProportionThresholdSecondary2',    single(0), ...
            'FramesLowSkinProportionThreshold', double(0), ...
            'NFramesLowSkinProportionStatus',   double(0), ...
            'MorphReductionAmount',             double(0), ...
            'NMorphReductionLimit',             int32(0), ...
            'NMorphReductions',                 int32(0), ... 
            'DarknessThreshold',                single(0), ...
            'BelowDarknessThresholdTF',         false, ...
            'NFramesYSingleMean',               single(0), ...
            'PixelColorsAdjustedTF',            false, ...
            'ColorThresAdjustTo',               zeros(1, 9, 'single') ...                  
        ) ...
    );       


%%%%%% Set configurations to increase performance %%%%%%

%Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic 
%"Optimization Strategies"

cfg = coder.config('mex');
cfg.GlobalDataSyncMethod = 'NoSync';
cfg.ConstantInputs = 'IgnoreValues';
cfg.ExtrinsicCalls = true; %true to permit display of errors
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

codegen ROIMeans_TakeMeans.m -report -config cfg -args {iCode, VidFrameCode, ROICode, SkinSegmentConfigCode, PulseRateConfigAndData_ControlLuminanceTFCode, PulseRateConfigAndData_ControlLuminanceColorspaceCode, WriteVideoTFCode, WriteVideoShowSkinSegmentTFCode, VideoReadConfig_FrameIdxCode, VideoReadConfig_VidObjWidthCode, VideoReadConfig_VidObjHeightCode, ROIGeneralConfig_ROIMSIR_FirstFrameIdxCode, FirstReadTFCode}
                
%}