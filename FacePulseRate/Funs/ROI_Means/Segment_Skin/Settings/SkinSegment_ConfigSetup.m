function [SkinSegmentConfig, SkinSegmentMasks] = ...
             SkinSegment_ConfigSetup(VideoReadConfig, SkinSegmentThresholdsGenericYCbCr, ...
                 SkinSegmentThresholdsGenericHSV, DetectVerifyPercentilesYCbCrH, ...
                 DetectVerifyPercentilesS, SkinSegmentSeverityFactor, OversegmentationCheckTF, ...
                 ROIGeneralConfig, UseCompiledFunctionsTF)                                                 
%SkinSegment_ConfigSetup    Setup configuration struct for use in skin-segmentation functions.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ValidateAndConfigure.
%
%
%    Description
%    -----------
%
%    Setup a configuration struct for holding settings of the skin-segmentation functions. 
%
%    The skin-segmentation functions include SkinSegmentMask, SkinSegment_SetThresholds,  
%    ConfirmSkinPresent, and SkinSegment_OversegmentationCheck. 
%
%    - SkinSegmentMask conducts the skin-segmentation operations.  
%    - SkinSegment_SetThresholds sets the thresholds used by SkinSegmentMask. 
%    - ConfirmSkinPresent returns a true/false value on whether an ROI contains skin based upon 
%      skin-segmentation operations. This is used to filter out ROIs that may be inaccurate.
%    - SkinSegment_OversegmentationCheck determines whether ROIs may be oversegmented. If so, this
%      function reduces the severity of settings that affect various skin-segmentation settings.
%
%    Skin segmentation affects a wide range of operations:
%
%    - Determines, in part, the validity of ROIs returned by the face- and skin-detection
%      algorithms through function ConfirmSkinPresent. As a result, settings tuned here can affect
%      whether ROIs returned from detection algorithms are accepted.
%    - Segments the bounding box before the skin-detection algorithm takes place (see function
%      SkinDetect_PartitionRegions). The settings tuned here can result in the bounding box being
%      completely segmented, resulting in no regions for the skin-detection algorithm to assess.
%    - Segments the ROI from which means are taken that are used directly to calculate pulse rate.
%
%    Because of the large impact of skin segmentation on the ROI placement (the first two points
%    above), the output video displays annotations that may help diagnose ROI misplacement as a
%    result of skin-segmentation settings (see function WriteFaceVideo).
%
%    Some settings assigned here were assigned as arguments or defaults to function FacePulseRate.
%    Other settings are assigned according to code contained in the current function. Descriptions 
%    of the settings and their uses are provided throughout this function.
%
%    For an overview of skin-segmentation operations, see function SkinSegmentMask.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Initialization and visualization of configuration struct %%%%%%

%The struct containing skin-segmentation settings is initialized here. The struct is intialized 
%with values of zero or false here. Most values will be reassigned later within the function or by
%other functions. The struct is initialized here for two reasons. The first reason is to provide a
%visual overview of the settings. The second reason is that this struct may be used as input to
%compiled (mex) functions. In compiled functions that use the struct as input, the order of the
%fields must be constant. Initializing all fields at once here helps ensure the order of fields is
%constant.

%Note: the order and names of fields within field SkinSegmentConfig.Args must match the order and
%names of field used in compiled functions SkinSegmentMaskOps_mex and 
%ROIMeans_FirstRead_CollectSkinColorSamples_mex. Also, the order and names of struct  
%SkinSegmentConfig must match the order and names of the struct used in compiled function
%SkinDetect_mex. If the struct is modified, one or both of these functions should be modified and
%recompiled.
SkinSegmentConfig = ...
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


%%%%%% Whether skin segmentation is enabled %%%%%%

SkinSegmentConfig.SkinSegmentTF = true;

%If skin segmentation enabled and Image Processing Toolbox not installed
if SkinSegmentConfig.SkinSegmentTF && ~ license('test', 'image_toolbox') 
    
    ME = ...
        MException( ...
            'Component:Toolbox', ...
            'Error: Skin segmentation requires: Image Processing Toolbox.' ...
        );
    
    throw(ME);
end


%%%%%% Extract VidObj from struct %%%%%%

VidObj = VideoReadConfig.VidObj;


%%%%%% Arguments to function SkinSegmentMask %%%%%%

%Set settings used as arguments to function SkinSegmentMask.

%Note: SkinSegment_ConfigSetupMaskArgs is a custom function located within folder 'FacePulseRate'.
SkinSegmentConfig = ...
    SkinSegment_ConfigSetupMaskArgs(SkinSegmentConfig, SkinSegmentSeverityFactor, ...
        SkinSegmentThresholdsGenericYCbCr, SkinSegmentThresholdsGenericHSV, ROIGeneralConfig, ...
        VidObj);
        

%%%%%% Parameters and data for tailored YCbCr and HSV thresholds %%%%%%

%Set settings used to tailor thresholds used as arguments to function SkinSegmentMask.

%Note: SkinSegment_ConfigSetupTailoredThresholds is a custom function located within folder 
%'FacePulseRate'.
SkinSegmentConfig = ...
    SkinSegment_ConfigSetupTailoredThresholds(DetectVerifyPercentilesYCbCrH, ...
        DetectVerifyPercentilesS, SkinSegmentConfig, ROIGeneralConfig);


%%%%%% Detection-verification thresholds to use in function ConfirmSkinPresent %%%%%%

%Set settings for function ConfirmSkinSegment. Function ConfirmSkinPresent determines whether there 
%is a sufficient proportion of pixels classified as skin within an ROI to consider the ROI valid. 
%Function ConfirmSkinPresent makes a verification for any ROI returned by a detection algorithm 
%(see functions FaceDetect and SkinDetect_SelectedRegionROI) and also verifies the final ROI before 
%means are taken for pulse rate operations (see function ROIMeans_TakeMeans).

%Note: SkinSegment_ConfigSetupConfirmSkinPresent is a custom function located within folder 
%'FacePulseRate'.
SkinSegmentConfig = SkinSegment_ConfigSetupConfirmSkinPresent(SkinSegmentConfig);


%%%%%% Over-segmentation check %%%%%%

%Set settings for the over-segmentation check and adjustment.

%Note:  SkinSegment_ConfigSetupOversegmentation is a custom function located within folder 
%'FacePulseRate'.
SkinSegmentConfig = ...
    SkinSegment_ConfigSetupOversegmentation(OversegmentationCheckTF, SkinSegmentConfig, ...
        VideoReadConfig);
    

%%%%%% Flag to indicate use of compiled functions %%%%%%

SkinSegmentConfig.UseCompiledFunctionsTF = UseCompiledFunctionsTF;


%%%%%% Preallocate struct to store skin-segmentation masks from each frame for reuse in output video %%%%%%

%Preallocate struct to store (in packed form) skin segmentation mask for use later in function
%WriteFaceVideo to display skin segmentation results. The values for the struct will be assigned in
%function ROIMeans_TakeMeans_StoreMaskForVideoWrite, which is called by function 
%ROIMeans_TakeMeans.

%Specify type uint16 for memory conservation and type uint32 because it is the required type for 
%binary packing (see implementation details in function ROIMeans_TakeMeans_StoreMaskForVideoWrite).

%Note: brackets are used to specify that the struct should take the form of a non-scalar struct 
%array.

%IsNotSkin_PixelColor_Packed = Skin-segmentation mask as packed binary image. Matrix; type uint32. 

SkinSegmentMasks = ...
    struct( ...
        'IsNotSkin_PixelColor_Packed', ...
        repmat( ...
            { zeros(1, 1, 'uint32') }, ...
            VideoReadConfig.NFrames, ...
            1 ...
        ) ...   
    ); 


end %end function

