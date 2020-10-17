function [MakeMorphLessSevereTF, MakeColorThresLessSevereTF, MorphCloseSEMediumWidth_Tuned, ...
          MorphCloseSELargeWidth_Tuned, SkinSegmentSeverityFactor, LowSkinProportionTF, ...
          FramesLowSkinProportionCounter, YSingleMean, FramesYSingleMeanCounter] = ...                             
             SkinSegment_OversegmentationCheck(ProportionSkin, ProportionSkin_AlgName, ...
                 YSingle_OversegmentationCheck, FramesLowSkinProportionStatus, ...
                 FramesLowSkinProportionCounter, FramesYSingleMean, FramesYSingleMeanCounter, ...
                 SkinSegmentConfig)                                                 
%SkinSegment_OversegmentationCheck   Determine whether over-segmentation appears to be present and,
%                                    if so, adjust the skin-segmentation settings to be less 
%                                    severe.                                   
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead.
%    
%
%    Description
%    -----------
%
%    If the proportion of pixels classified as skin within an ROI is low across many frames, the
%    skin-segmentation settings may be oversegmenting the ROIs. Function 
%    SkinSegment_OversegmentationCheck will determine (1) whether oversegmentation is present  
%    and/or (2) whether oversegmentation is likely present due to dark ROIs. If oversegmentation is 
%    present, flag MakeMorphLessSevereTF will be returned as true. If oversegmentation is likely 
%    present due to dark ROIs, both flags MakeMorphLessSevereTF and MakeColorThresLessSevereTF will  
%    be returned as true. These flags signal function SkinSegment_OversegmentationCheck_Reduce to   
%    reduce the severity of various skin-segmentation settings. Different settings are modified   
%    depending on whether flag MakeMorphLessSevereTF and/or flag MakeColorThresLessSevereTF is 
%    returned as true.
%
%    -- Presence of Oversegmentation --
%
%    Oversegmentation will be considered present if ROIs chronically have a low proportion of
%    pixels classified as skin across frames. That is, a single frame with a low proportion of 
%    pixels classified as skin will not be considered oversegmentation. 
%
%    The threshold at which a skin proportion is considered to be low for a single given frame  
%    varies by the face-detection algorithm that returned the ROI. For example, the threshold under 
%    which a skin proportion is considered low for an ROI returned by the primary face-detection 
%    algorithm is specified by SkinSegmentConfig.OverSegmentedCheck.ProportionThresholdPrimary 
%    whereas the threshold used for an ROI returned by the secondary #1 algorithm is specified by
%    specified by SkinSegmentConfig.OverSegmentedCheck.ProportionThresholdSecondary1. For details 
%    on the thresholds, see function SkinSegment_ConfigSetupOversegmentation.
%
%    For a certain number of frames back 
%    (SkinSegmentConfig.OverSegmentedCheck.NFramesLowSkinProportionStatus), vector 
%    PreviousFramesStatus will contain a logical value for each frame indicating whether the frame 
%    contained a low proportion of pixels classified as skin. Oversegmentation will be considered 
%    present if the proportion of frames with a true value is above a specified threshold 
%    (SkinSegmentConfig.OverSegmentedCheck.FramesLowSkinProportionThreshold). 
%
%    If oversegmentation is considered present, the function will set a flag,   
%    MakeMorphLessSevereTF, that indicates the severity should be reduced for the morphological   
%    close operations conducted by skin segmentation (see function SkinSegmentMask). The function
%    will also calculate new settings for the morphological close. The modifications to the
%    morphological close operations are specified by 
%    SkinSegmentConfig.OverSegmentedCheck.MorphReductionAmount, which was assigned by function
%    SkinSegment_ConfigSetupOversegmentation. For details on how making the making the 
%    morphological close operations less severe reduces oversegmentation, see section 
%    "Oversegmentation Remedy 1: Reduce Severity of Morphological Close".    
%
%    Flag MakeMorphLessSevereTF and the new settings are input to function  
%    SkinSegment_OversegmentationCheck_Reduce, which will assign the new settings to the 
%    skin-segmentation settings struct (SkinSegmentConfig). Note that morphological close 
%    operations will also be made less severe if the ROIs are consired dark (see section "Likely
%    presence of oversegmentation due to dark ROIs").    
%    
%    It is possible to reduce the severity of the morphological close several times. To prevent 
%    potential undersegmentation, the severity of the morphological close settings can only be 
%    reduced a maximum number of times (SkinSegmentConfig.OverSegmentedCheck.NMorphReductionLimit). 
%
%    After each occassion that the severity of the morphological close is reduced, the elements of  
%    vector PreviousFramesStatus will be reset (changed to false) to let evidence of
%    oversegmentation accumulate before the severity can be reduced again. The intention of giving 
%    time for evidence accumulation is to prevent undersegmentation that might occur if the  
%    morphological close settings were reduced again prematurely. This resetting is made by
%    function SkinSegment_OversegmentationCheck_Reduce.      
%
%        Determining Whether a Single ROI has a Low Proportion of Skin
%
%    To determine whether the proportion of pixels classified as skin within an ROI is low, only 
%    ROIs from face-detection algorithm attempts are assessed. Only face-detection attempts, and  
%    not skin-detection attempts, are used because the ROIs from face-detection algorithms tend to 
%    contain a more predictable proportion of skin. This is because the face-detection algorithms  
%    target specific areas of the face (for example, the default primary face-detection algorithm 
%    targets a frontal orientation), whereas the skin-detection algorithm can detect skin from any 
%    part of the body, resulting in highly variable proportions of skin. More preditable 
%    proportions of skin allow proportion thresholds to be set (see function 
%    SkinSegment_ConfigSetupOversegmentation) that can more accurately guage whether 
%    oversegmentation has occurred. 
%          
%    The proportion assessed here comes from both successful and unsuccessful ROIs, the distinction 
%    being that unsuccessful ROIs were rejected by function FaceDetect_ROIValidate. Proportions  
%    from rejected ROIs are assessed because oversegmentation can cause ROIs to fail the checks by 
%    FaceDetect_ROIValidate. Specifically, FaceDetect_ROIValidate will reject ROIs that contain a 
%    low proportion of skin because this is used as a heuristic that the ROI is inaccurate. 
%
%    ROIs assessed here will have at least passed the first criterion of function  
%    FaceDetect_ROIValidate, which requires the result from a face-detection algorithm to have one 
%    and only one ROI. Requiring at least one ROI to be returned assists the current function in   
%    avoiding triggering an oversegmentation determination for a stretch of frames where no    
%    detection was able to be made. In such a case, it may be fairly easy for a low proportion of  
%    skin to be present; for example, the individual in the video could have turned around, 
%    resulting in no skin pixels present for a stretch of frames. In this case, even a relatively 
%    long stretch of frames with a low proportion of skin (perhaps 0) would not be an indication of 
%    oversegmentation because the high proportion of segmentation is valid.
%
%    -- Likely Presence of Oversegmentation Due to Dark ROIs --
%
%    ROIs that are darker than usual could be the cause of oversegmentation. ROI are darker than
%    usual when there is inadequate brightness of the area of the face. Cases of inadequate 
%    brightness of the face are often the result of video cameras automatically reducing their 
%    brightness or exposure when a bright light source is present in an area of the frame other 
%    than the face. For example, lamps, windows, and solid white objects, including clothing, can 
%    sometimes lead to a video automatically reducing the brightness of the face.
%
%    To determine whether the ROIs are too dark, the mean brightness level across frames will be 
%    assessed. To do so, the mean of the Y-colorspace will be taken from each ROI a specified 
%    number of frames back (SkinSegmentConfig.OverSegmentedCheck.NFramesYSingleMean) and stored in 
%    vector FramesYSingleMean. The mean is then taken across all means in the vector. 
%    FramesYSingleMean is initialized with values of the highest possible Y value (235) to prevent
%    the mean across frames from appearing low before a sufficient number of ROI means have been 
%    collected. For example, this might occur if the vector were initialized with zeros.
%
%    If the ROIs are determined to be dark, the function will set flag 
%    SkinSegmentConfig.OverSegmentedCheck.DarknessThreshold as true. In turn, flag 
%    MakeColorThresLessSevereTF will be set as true, which indicates that the pixel-color 
%    thresholds should be made less severe.  For details on how making the making the pixel-color 
%    thresholds less severe reduces oversegmentation, see section "Oversegmentation remedy 2: 
%    Reduce severity of pixel-color thresholds". Flag MakeColorThresLessSevereTF is input to   
%    function SkinSegment_OversegmentationCheck_Reduce, which will assign new settings to the
%    skin-segmentation settings struct (SkinSegmentConfig). The new settings are specified by
%    SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo, which was assigned by function
%    SkinSegment_ConfigSetupOversegmentation.
%
%    Additionally, a determination that ROIs are too dark will result in flag MakeMorphLessSevereTF  
%    being set as true. As mentioned previously, flag MakeMorphLessSevereTF will result in the 
%    morphological close operations becoming less severe. The morphological close operations are
%    made less severe in addition to making the pixel-color thresholds less severe because the 
%    amount by which the pixel-color thresolds are reduced is somewhat arbitrary. By also reducing  
%    the severity of the morphological close operations, there can be greater certainty that 
%    oversegmentation caused by dark ROIs will be reduced.    
%     
%    A determination of a low proportion of skin across frames (see section 
%    "Presence of Oversegmentation") is not used as a prerequisite for modifying skin-segmentation
%    settings in the case of dark ROIs. In the case of dark ROIs, a low proprotion of skin across
%    frames is assumed. This assumption is made because making a determination of a low proportion  
%    of skin across frames is dependent on thresholds (e.g., 
%    SkinSegmentConfig.OverSegmentedCheck.ProportionThresholdPrimary) that may sometimes be too 
%    conservative; that is, these thresholds sometimes may not detect a low proportion of skin 
%    across frames. These thresholds are intentionally conservative in order to avoid  
%    undersegmentation as a result of making settings less severe. However, when ROIs are dark,
%    oversegmentation almost always results, so using thresholds to check for a low proportion of 
%    skin is not considered necessary.
%
%    Although the default pixel-color thresholds could be set lower to avoid oversegmentation in 
%    dark conditions, this has been found to result in lowered segmentation accuracy when  
%    conditions are not dark, so they are only lowered when dark ROIs are detected. 
%
%    Like the check for oversegmentation (see section "Presence of oversegmentation"), ROIs checked
%    for darkness only come from ROIs returned from face-detection algorithms. As ROIs returned
%    from face-detection algorithms tend to be more acccurate than ROIs returned from the 
%    skin-detection algorithm, this helps ensure that the ROIs actually correspond to the face. 
%
%    -- Oversegmentation Remedy 1: Reduce Severity of Morphological Close --    
%        
%    The severity of the pixel-color thresholds is reduced when flag MakeMorphLessSevereTF is true.
%    The severity of the pixel-color thresholds is reduced when either oversegmentation is
%    considered present (FramesLowSkinProportionTF) or when the ROIs are considered too dark
%    (ROIsDarkTF).
%
%    The following settings are modified to reduce the severity of morphological close:
%
%    - SkinSegmentConfig.Args.MorphCloseSEMediumWidth_Tuned
%
%    - SkinSegmentConfig.Args.MorphCloseSELargeWidth_Tuned
%
%    The severity of the morphological close operations can be reduced multiple times. It can be 
%    reduced up to the number of times specified by 
%    SkinSegmentConfig.OverSegmentedCheck.NMorphReductionLimit. The number of times it can be 
%    reduced is capped to prevent undersegmentation.
%
%    To reduce the severity of the morphological close, the size of structuring element used for   
%    the morphological close operations conducted by function SkinSegmentMask is decreased. As the   
%    size of the of the structuring element decreases, the severity of segmentation decreases. The
%    morphological close increases segmentation by segmenting out pixels that neighbor pixels that
%    fall above or below individual thresholds (e.g.,  
%    SkinSegmentConfig.Args.YCbCrThresholdsGeneric; SkinSegmentConfig.Args.RangeThreshold; etc.). 
%    Neighbors are segmented out based on the heuristic that areas of skin or non-skin reside in 
%    contiguous areas (for a description of this heuristic, see the description in function 
%    SkinSegmentMask).
%      
%    Oversegmenting may be caused by settings other than the severity of the morphological close,
%    but adjusting the severity of the morphological close is perhaps the most general remedy to
%    address oversegmentation. The other way to reduce oversegmentation involves reducing the
%    individual segmentation thresholds, but success in reducing oversegmentation by reducing these
%    depends on knowlegde of which specific threshold led to oversegmentation. In contrast, 
%    reducing the morphological-close severity usually leads to a reduction in oversegmentation 
%    despite the cause. However, reducing the morphological close size sometimes will not noticably
%    reduce oversegmentation. This will occur if a large number of pixels in a given frame fall 
%    below one or more individual thresholds. In this case, the reducing the severity of the
%    morphological close may not noticably reduce segmentation because the morphological close only
%    reduces the number of neighbor-pixels segmented; reducing the morphological close does not 
%    affect pixels that fall outside of individual thresholds. To partly address this limitation, 
%    method 2 (reducing the severity of the pixel-color thresholds) is performed in addition to 
%    reducing the severity of the morphological close if the conditions are found to be 
%    darker-than-usual. These individual thresholds are only modified in dark conditions, because,
%    otherwise, undersegmentation can result.
%
%    The severity of the morphological close is reduced by decreasing the value of     
%    SkinSegmentConfig.SkinSegmentSeverityFactor. SkinSegmentSeverityFactor is an argument to  
%    function FacePulseRate that can be used to tune the size of the morphological close. This 
%    value, in turn, decreases the values of SkinSegmentConfig.MorphCloseSEMediumWidth and  
%    SkinSegmentConfig.MorphCloseSELargeWidth. In turn, this decreases the values of  
%    SkinSegmentConfig.Args.MorphCloseSEMediumWidth_Tuned and 
%    SkinSegmentConfig.Args.MorphCloseSELargeWidth_Tuned. Finally, these values result in less
%    severe segmentation by function SkinSegmentMask.
% 
%    -- Oversegmentation Remedy 2: Reduce Severity of Pixel-Color Thresholds -- 
%
%    The severity of the pixel-color thresholds is reduced when flag MakeColorThresLessSevereTF is
%    true. This flag is set as true when the ROIs are considered too dark. Note that the severity 
%    of the pixel-color thresholds will not be reduced when oversegmentation is considered present
%    but the ROIs are not considered too dark.
%
%    The following settings are modified to reduce the severity of pixel-color thresholds:
%
%    - SkinSegmentConfig.Args.YCbCrThresholdsGeneric
%
%    - SkinSegmentConfig.Args.YCbCrThresholdsTailored
%
%    - SkinSegmentConfig.Args.YCbCrThresholdsTailored_Sev
%
%    The severity of the pixel-color thresholds can be reduced only once (in contrast to the 
%    severity of the morphological close, which can be reduced multiple times). Therefore, if the 
%    severity of the pixel-color thresholds has already been reduced, it will not be reduced again.
%
%    The severity of the pixel-color thresholds is made when the mean Y-colorspace pixel value 
%    across ROIs is below a specified threshold 
%    (SkinSegmentConfig.OverSegmentedCheck.DarknessThreshold).          
%
%    The pixel-color thresholds are reduced to address the specific case of ROIs being darker than  
%    usual, which occurs when there is inadequate brightness of the face. Cases of inadequate 
%    brightness of the face are often the result of video cameras automatically reducing their 
%    brightness or exposure when a bright light source is present in an area of the frame other 
%    than the face. For example, lamps, windows, and solid white objects, including clothing, can 
%    sometimes lead to a video automatically reducing the brightness of the face.
%
%    When ROIs are darker than usual, some pixel-color thresholds can oversegment skin. It should 
%    be noted that the default pixel-color thresholds are set to avoid oversegmentation based on an 
%    individual's skin color, but dark conditions can still result in the skin colors of some 
%    individuals becoming oversegmented under the default thresholds. Although the default 
%    pixel-color thresholds could be set lower to avoid oversegmentation in dark conditions, this 
%    has been found to result in lowered segmentation accuracy when conditions are not dark, so 
%    they are only lowered when darker-than-usual ROIs are detected.           
%    
%    The tailored pixel-color thresholds are updated periodically by function 
%    SkinSegment_SetThresholds. SkinSegment_SetThresholds will not increase the tailored 
%    pixel-color thresholds if the value are modified to be less severe. Specifically, it will not 
%    increase the values if flag SkinSegmentConfig.OverSegmentedCheck.BelowDarknessThresholdTF is 
%    true.
% 
%    The severity of the generic and tailored pixel-color thresholds is reduced by reassigning them    
%    to specified values. The thresholds are assigned to the values specified by 
%    SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo (see function
%    SkinSegment_ConfigSetupOversegmentation).   
%
%    -- Starting over of function ROIMeans_FirstRead --
%
%    When the severity of skin-segmentation is to be reduced either by flag MakeMorphLessSevereTF
%    or MakeColorThresLessSevereTF, function ROIMeans_FirstRead is started over. This ensures that
%    any frames that came before a determination that skin-segmentation settings should be reduced 
%    can benefit from the modified settings.
%
%    To start over function ROIMeans_FirstRead, function SkinSegment_OversegmentationCheck_Reduce
%    calls function ROIMeans_FirstRead, which starts from the first frame to be processed. Because
%    SkinSegment_OversegmentationCheck_Reduce is called within function ROIMeans_FirstRead,
%    ROIMeans_FirstRead is called recursively. To facilitate the variables used by function 
%    SkinSegment_OversegmentationCheck being persistent across recursive calls, many variables are
%    assigned to struct SkinSegmentConfig. This struct is used as input to function 
%    ROIMeans_FirstRead to achieve persistence. 
%
%    -- Diagnostics --
%
%    Function SkinSegment_OversegmentationCheck prints a message to the command window every time
%    the severity of the morphological close or pixel-color thresholds are made less severe.
%
%    The legend of the output video indicates how many times the severity of the morphological  
%    close was reduced (SkinSegmentConfig.OverSegmentedCheck.NMorphReductions). It also indicates 
%    whether the severity of pixel-color thresholds was reduced 
%    (SkinSegmentConfig.OverSegmentedCheck.BelowDarknessThresholdTF).
%     
%    These can help diagnose whether SkinSegment_OversegmentationCheck appropriately reduced the 
%    severity of settings.
%
%   -- Note --
%
%    A copy of this description is located in function SkinSegment_ConfigSetupOversegmentation.    
%
%
%    Selected Inputs
%    ---------------
%
%    Note: SkinSegmentConfig.OverSegmentedCheck is assigned by function
%    SkinSegment_ConfigSetupOversegmentation.
%
%    ProportionSkin                                       = The proportion of an ROI from a 
%                                                           face-detection attempt that is 
%                                                           classified as skin.
%
%    FramesLowSkinProportionStatus                        = Column vector corresponding to a range
%                                                           of previous frames indicating whether
%                                                           a frame was below the skin-proportion
%                                                           threshold. This vector is used to
%                                                           calculate the frames-low-skin 
%                                                           proportion, which indicates the
%                                                           proportion of frames within this vector
%                                                           that were below the skin-proportion
%                                                           threshold.
%
%    FramesLowSkinProportionCounter                       = Position in vector 
%                                                           FramesLowSkinProportionStatus
%                                                           corresponding to the current frame.                                                            
%
%    FramesYSingleMean                                    = Column vector corresponding to a range
%                                                           of previous frames containing the
%                                                           Y-colorspace means of each frame. This 
%                                                           vector is used to calculate the 
%                                                           Y-colorspace mean across frames in 
%                                                           order to determine whether the
%                                                           pixel-color thresholds should be made
%                                                           less severe.
%
%    FramesYSingleMeanCounter                             = Position in vector FramesYSingleMean                                                           
%                                                           corresponding to the current frame.
%
%    FramesLowSkinProportionThreshold                     = Threshold for the proportion of frames 
%                                                           out of a given number of previous 
%                                                           frames that had a proportion of skin  
%                                                           below the skin-proportion threshold.  
%                                                           When this threshold is exceeded, 
%                                                           oversegmentation is considered present 
%                                                           and flag ReduceSeverityTF is returned 
%                                                           as true, indicating that the severity 
%                                                           of skin segmentation should be reduced.
%
%    SkinSegmentConfig.OverSegmentedCheck.NMorphReductionLimit = The maximum number of times the 
%                                                           severity of the morphological close can 
%                                                           be reduced.
%
%    SkinSegmentConfig.OverSegmentedCheck.NMorphReductions = Count of the number of times the 
%                                                           severity of the morphological close has 
%                                                           been reduced.          
%
%    ProportionSkin_AlgName                               = Face-detection algorithm type that 
%                                                           returned the ROI corresponding to  
%                                                           ProportionSkin; scalar, type character.
%                                                           The type of algorithm determines which
%                                                           proportion threshold is used.
%
%    SkinSegmentConfig.SkinSegmentSeverityFactor          = A factor that can modify the severity
%                                                           of the morphological close. By default, 
%                                                           it is 1. If oversegmentation is  
%                                                           determined, this number is reduced.                                                                                                                                                                                    
%
%    SkinSegmentConfig.OverSegmentedCheck.MorphReductionAmount = The amount by which to reduce 
%                                                           SkinSegmentPixelMorphSize, which 
%                                                           controls the severity of skin
%                                                           segmentation.
%
%    -- Skin-proportion thresholds --
% 
%    Thresholds under which the skin proportion is considered low. Different thresholds are used 
%    because the algorithms are expected to have different typical proportions. For details on how
%    these thresholds were set, see function SkinSegment_ConfigSetupOversegmentation.
%
%    SkinSegmentConfig.OverSegmentedCheck.ProportionThresholdPrimary    = Threshold for ROIs 
%                                                                         returned by the primary 
%                                                                         face-detection algorithm.
%
%    SkinSegmentConfig.OverSegmentedCheck.ProportionThresholdSecondary1 = Threshold for ROIs 
%                                                                         returned by the secondary 
%                                                                         #1 face-detection 
%                                                                         algorithm.
%
%    SkinSegmentConfig.OverSegmentedCheck.ProportionThresholdSecondary2 = Threshold for ROIs 
%                                                                         returned by the secondary 
%                                                                         #2 face-detection 
%                                                                         algorithm.     
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.    


%%%%%% Input validation %%%%%%

%ProportionSkin should not equal -1. If -1, this would indicate an implementation error. If -1, 
%this would indicate that no proportion was calculated. No proportion would be calculated if a 
%face-detection algorithm did not return an ROI or if a face-detection algorithm returned more than 
%one ROI. 
assert(ProportionSkin ~= -1);


%%%%%% Check whether ROIs are likely oversegmented due to chronic darkness %%%%%%    
    
%Check whether ROIs are likey oversegmented because of chronic darkness of ROIs. Whether the ROIs
%are actually oversegmented (a chronic low proportion of skin across frames) is not checked because
%it is assumed that if chronic darkness is present then oversegmentation will also be present.

%Note: SkinSegment_OversegmentationCheck_Dark is a custom function located within folder
%'FacePulseRate'.
[ROIsDarkTF, MakeColorThresLessSevereTF, YSingleMean, FramesYSingleMeanCounter] = ...
    SkinSegment_OversegmentationCheck_Dark(YSingle_OversegmentationCheck, FramesYSingleMean, ...
        FramesYSingleMeanCounter, SkinSegmentConfig);    


%%%%%% Check whether ROIs are oversegmented %%%%%%

%Oversegmentation is determined by chronic low skin proportion across frames.

%Note: SkinSegment_OversegmentationCheck_LowSkin is a custom function located within folder
%'FacePulseRate'.
[FramesLowSkinProportionTF, LowSkinProportionTF, FramesLowSkinProportionCounter] = ...
    SkinSegment_OversegmentationCheck_LowSkin(ProportionSkin, ProportionSkin_AlgName, ...
        FramesLowSkinProportionStatus, FramesLowSkinProportionCounter, SkinSegmentConfig);
 

%%%%%% Set flag to reduce the severity of the morphological close settings %%%%%%

%Set flag to signal that the severity of the morphological close operations should be reduced. This 
%flag is set either if dark ROIs are considered present (ROIsDarkTF) or if oversegmentation is
%considered present (FramesLowSkinProportionTF). The flag is not set to true if the severity of the
%morphological close settings has been reduced the maximum number of times
%(SkinSegmentConfig.OverSegmentedCheck.NMorphReductionLimit).

%Note: if the morphological close settings are modified, then the modified settings are assigned to  
%the struct used by skin-segmentation operations, SkinSegmentConfig, by function 
%SkinSegment_OversegmentationCheck_Reduce.

%%%%%% --- The severity of the morphological close has not been reduced the maximum number of times %%%%%%

if SkinSegmentConfig.OverSegmentedCheck.NMorphReductions < ...
   SkinSegmentConfig.OverSegmentedCheck.NMorphReductionLimit 
   
    %Flag to reduce the severity of the morphological close operations
    %This flag will be true either if dark ROIs are considered present (ROIsDarkTF) or if 
    %oversegmentation is considered present (FramesLowSkinProportionTF).
    MakeMorphLessSevereTF = ROIsDarkTF || FramesLowSkinProportionTF;        
    
    %If the morphological close operations are to be made less severe
    if MakeMorphLessSevereTF

        %%%%%% >>>>>> Reduce structuring element sizes to reduce morph close severity %%%%%%        

        %Note: struct SkinSegmentConfig will be reassigned to these values by function
        %SkinSegment_OversegmentationCheck_Reduce.         
        
        %Previous structing element size factor
        %Scalar; type double.
        %Note: SkinSegmentSeverityFactor is an argument to function FacePulseRate.
        SkinSegmentSeverityFactor = SkinSegmentConfig.SkinSegmentSeverityFactor;

        %New structing element size factor
        %Scalar; type double.
        SkinSegmentSeverityFactor = ...
            SkinSegmentSeverityFactor - SkinSegmentConfig.OverSegmentedCheck.MorphReductionAmount;       

        %Tune the widths according to the reduced SkinSegmentSeverityFactor:     
        
        %For details on these settings, see function SkinSegment_ConfigSetupMaskArgs.
        %Specify type int16 because type int16 expected by compiled version of function 
        %SkinSegmentMask.

        %Structuring element for medium-size morphological close
        MorphCloseSEMediumWidth_Tuned = ...
            int16( ...
                round( ...
                    SkinSegmentConfig.MorphCloseSEMediumWidth * ...     
                    SkinSegmentConfig.SkinSegmentSeverityFactor ... 
                ) ...           
            );

        %Structuring element for large-size morphological close
        MorphCloseSELargeWidth_Tuned = ...
            int16( ...
                round( ...
                    SkinSegmentConfig.MorphCloseSELargeWidth * ...       
                    SkinSegmentConfig.SkinSegmentSeverityFactor ...                         
                ) ...
            );
  
    else

        SkinSegmentSeverityFactor     = [];
        MorphCloseSEMediumWidth_Tuned = [];
        MorphCloseSELargeWidth_Tuned  = [];        
    end
    
%%%%%% --- The severity of the morphological close has been reduced the maximum number of times %%%%%%

else
    
    MakeMorphLessSevereTF         = false; 
    SkinSegmentSeverityFactor     = [];
    MorphCloseSEMediumWidth_Tuned = [];
    MorphCloseSELargeWidth_Tuned  = [];    
end
    

end %end function

