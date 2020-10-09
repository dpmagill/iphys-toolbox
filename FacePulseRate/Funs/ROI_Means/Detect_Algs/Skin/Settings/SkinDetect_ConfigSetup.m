function [SkinDetectConfig, ROIDiagnostic] = ...
             SkinDetect_ConfigSetup(ROI, UseCompiledFunctionsTF, SkinSegmentConfig, ...       
                 ROIGeneralConfig, VideoReadConfig, ROIDiagnostic)                
%SkinDetect_ConfigSetup     Setup configuration properties for the skin-detection algorithm.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ValidateAndConfigure.
%
%
%    Description
%    -----------
%
%    Setup configuration properties for the skin-detection algorithm. These properties are used to 
%    fine tune the steps of the skin-detection algorithm. 
%
%    The skin-detection algorithm, or portions of it, is used in two places in function 
%    FacePulseRate. First, a portion of it (function ConfirmSkinPresent_SkinDetectReject) is used 
%    by function ConfirmSkinPresent for additional verification of the ROIs returned by a 
%    face-detection algorithm (see function FaceDetect). Second, the full algorithm (function
%    SkinDetect) is used to determine an ROI for frames where the face-detection algorithm(s) were 
%    not successful (see functions ROIMeans_FirstRead_AlgSelector and 
%    ROIMeans_SecondRead_SkinDetect). 
%     
%    Some inputs to the skin-detection algorithm can be entered as arguments to function 
%    FacePulseRate. Other inputs are defined only in the current function.                       
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Initialization and visualization of configuration struct %%%%%%

%Note: the order and names of fields within this struct must match the order and names of field
%used in compiled functions SkinDetect_mex and ConfirmSkinPresent_SkinDetectReject_mex. 

SkinDetectConfig = ... 
    struct( ...
        'ROISkinTF', false, ...
        'Thresholds', ...
        struct( ...   
            'SetTF', false, ...
            'SkinColorSamples_NThreshold', double(0), ...
            'SkinColorSamples_NThresholdPassedTF', false, ...
            'SkinColorSamples_HighNThreshold', double(0), ... 
            'SkinColorSamples_HighNThresholdPassedTF', false, ...
            'SkinColorSamples_HighNThresholdIdx', int32(0), ... 
            'ColorThreshold', zeros(1, 3, 'single'), ...
            'ColorThresholdHighN', zeros(1, 3, 'single'), ...
            'RecentThresholdOpsFrameIdx', int32(0), ...
            'ThresholdOpsInterval', int32(0), ...
            'ThresholdOpsRunCurrentFrameTF', false, ...
            'ColorSDThreshold', single(0), ...
            'RGBProbTheta', zeros(4, 1, 'double'), ...
            'YCbCrMeanOfMeans', zeros(1, 3, 'single'), ...
            'YCbCrStdDevOfMeans', zeros(1, 3, 'single'), ...
            'RegionNThreshold', single(0) ...
        ), ...
        'ROISkinSkipFrameThreshold', int32(0), ...
        'ROISkin_BoundingBoxGrowthThreshold', int32(0), ...
        'ROISkin_BoundingBoxGrowthFactor', double(0), ...
        'ROISkin_InitialBoundingBoxScale', double(0), ...
        'ROISkinRegionMinSizeFactor', single(0), ...
        'ROISkinRegionProximityWeight', double(0), ...
        'ROISkinSmoothingWindow', double(0), ...
        'PartitionColInterval', int16(0), ...
        'PartitionRowInterval', int16(0), ...
        'SkinDetectionReadyTF', false, ...
        'ROISkin_BoundingBoxEnlargementFactor', double(0), ...
        'ROISkinSkipFrameThreshold_adjusted', int32(0), ...
        'UseCompiledFunctionsTF', false ...
    );           


%%%%%% Enable skin-detection algorithm %%%%%%

SkinDetectConfig.ROISkinTF = true;


%%%%%% Misc configurations %%%%%%

%See function SkinDetect for a description of these flags.

%For some variables, specify type single for faster evaluation where used.
%For some variables, specify type double to facilitate calculations with ROI variables, which are
%type int16.
%For some variables, specify type uint32 to facilitate interaction with the frame index, which is
%type int32.

ROISkinSkipFrameThreshold = .75;
ROISkin_BoundingBoxGrowthThreshold = 1;   
ROISkin_BoundingBoxGrowthFactor = 1.2;
ROISkin_BoundingBoxEnlargementFactor = 2.5;
ROISkinRegionMinSizeFactor = 1;
ROISkinRegionProximityWeight = 2;
ROISkinSmoothingWindow = 50; 

SkinDetectConfig.ROISkinSkipFrameThreshold            = int32(ROISkinSkipFrameThreshold);
SkinDetectConfig.ROISkin_BoundingBoxGrowthThreshold   = int32(ROISkin_BoundingBoxGrowthThreshold); 
SkinDetectConfig.ROISkin_BoundingBoxGrowthFactor      = double(ROISkin_BoundingBoxGrowthFactor);
SkinDetectConfig.ROISkin_BoundingBoxEnlargementFactor = double(ROISkin_BoundingBoxEnlargementFactor);
SkinDetectConfig.ROISkinRegionMinSizeFactor           = single(ROISkinRegionMinSizeFactor);
SkinDetectConfig.ROISkinRegionProximityWeight         = double(ROISkinRegionProximityWeight);
SkinDetectConfig.ROISkinSmoothingWindow               = double(ROISkinSmoothingWindow);
SkinDetectConfig.UseCompiledFunctionsTF               = UseCompiledFunctionsTF;

%Specify the number of frames without face detections to have passed before activating the skin-
%detection algorithm.
%This this value is adjusted by frame rate to make the value consistent across videos with
%different frame rates.
%Specify type uint32 to facilitate interaction with the frame index, which is type uint32.
SkinDetectConfig.ROISkinSkipFrameThreshold_adjusted = ...
    int32( ...
        VideoReadConfig.FS * double(SkinDetectConfig.ROISkinSkipFrameThreshold) ...
    );


%%%%%% Color thresholds %%%%%%
 
%Setup color thresholds for use in the skin-detection algorithm.                                       

%Note: SkinDetect_ConfigSetupColorThresholds is a custom function located within folder 
%'FacePulseRate'.
SkinDetectConfig = SkinDetect_ConfigSetupColorThresholds(SkinDetectConfig, ROIGeneralConfig);
  

%%%%%% Calculate the minimum pixel count threshold for regions %%%%%%

%The minimum pixel count threshold is a function of frame size, the specified minimum width and
%height for ROI box size, a constant determined through testing, and a scaling factor
%(ROISkinRegionMinSizeFactor) that can be adjusted as needed. The minimum width and height of ROI
%box size is determined by arguments (ROIMinWidthProportion, ROIMinHeightProportion) to function 
%FacePulseRate. The scaling factor is also specified as an argument to function FacePulseRate. 
%These parameters should be able to adjust to frame size and the distance of the individual to the 
%camera.    
%Type single for faster evaluation where used.
SkinDetectConfig.Thresholds.RegionNThreshold = ... minimum pixel count for a region
    round( ... round to integer
        ( single(VideoReadConfig.VidObjWidth) * ROIGeneralConfig.ROIMinWidthProportion ) * ...
        ( single(VideoReadConfig.VidObjHeight) * ROIGeneralConfig.ROIMinHeightProportion ) ...
        / 506 * single(SkinDetectConfig.ROISkinRegionMinSizeFactor) ...
    );


%%%%%% Calculate the row and column intervals to determine the sizes of partitions %%%%%%

%The row and column intervals for partitioning are functions of frame size, the specified minimum
%width and height for ROI box size, and a constant determined through testing. The minimum width 
%and height of ROI box size is determined by arguments (ROIMinWidthProportion, 
%ROIMinHeightProportion) specified in function FacePulseRate. 
%Specify type int16 for faster evaluation where used.
SkinDetectConfig.PartitionColInterval = ...  
    int16( ...
        ( single(VideoReadConfig.VidObjWidth) * ROIGeneralConfig.ROIMinWidthProportion ) / 2.9 ...
    );

SkinDetectConfig.PartitionRowInterval = ...    
    int16( ...
        ( single(VideoReadConfig.VidObjHeight) * ROIGeneralConfig.ROIMinHeightProportion ) / 3.4 ...
    );       


%%%%%% Whether the skin-detection algorithm is ready for processing %%%%%%

%Assigned in function ROIMeans_FirstRead.

%Note: this flag will be reset if function ROIMeans_FirstRead is called recursively (see function
%SkinSegment_OversegmentationCheck_Reduce).

SkinDetectConfig.SkinDetectionReadyTF = false;


%%%%%% Assign variables for skin-detection algorithm diagnostics %%%%%%

%%%%%% --- Preallocate struct for skin-detection algorithm diagnosis %%%%%%

%Note: SkinDetect_PreallocateDiagnosticData is a custom function located within folder 
%'FacePulseRate'.
ROIDiagnostic.ROISkin = SkinDetect_PreallocateDiagnosticData(ROI, SkinDetectConfig);


%%%%%% Validate settings %%%%%%

%Validate window size for smoothing arguments, which can be up to FrameCacheMaxFrames * 2 - 1. 
WindowSizeMax = ROIGeneralConfig.FrameCacheMaxFrames * 2 - 1;

if SkinDetectConfig.ROISkinSmoothingWindow > WindowSizeMax 

    %Throw exception
    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: The maximum window value is ', num2str(WindowSizeMax), ' for input', ...
             ' arguments ROIFaceSmoothingWindow, ROISkinSmoothingWindow, and' ...
             ' ROIFinalSmoothingWindows.'] ...
        );       
    
    throw(ME)
end

%Skin-detection color thresholds
if ~ (SkinDetectConfig.Thresholds.ColorThreshold(1) >= 0 && ...
      SkinDetectConfig.Thresholds.ColorThreshold(1) <= 1)

    ME = ...
        MException( ...
            'Component:Argument', ...
             ['Error: SkinClassifyRegionColorThresholds(1) should be neither less than', ...
              ' 0 nor greater than 1.'] ...
        );
    
    throw(ME);
end

%Argument mismatch
if SkinDetectConfig.ROISkinTF && ~ SkinSegmentConfig.SkinSegmentTF 
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: If ROISkinTF = true, SkinSegmentTF must also be true.' ...
        );
    
    throw(ME);
end


end %end function

