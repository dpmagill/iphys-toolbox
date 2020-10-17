function ROIGeneralConfig = ...
             ROIGeneralConfig_Setup(ROIMinWidthProportion, ROIMinHeightProportion, ...
                 ROIWidthResizeFactor, ROIHeightResizeFactor, VideoReadConfig, ...
                 ROIFacePrimaryXML, ROISpecifyByArgument, ROIIgnoreByArgument, ...
                 UseCompiledFunctionsTF)
%ROIGeneralConfig_Setup   Setup configuration settings for general ROI operations.
%                      
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, a member of the general ROI operations group of functions.
%    Called by function ValidateAndConfigure.
%
%
%    Description
%    -----------
%
%    Configures the settings for functions that conduct general ROI operations. 
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Specify the minimum size of an ROI to accept from a face-detection algorithm %%%%%%

%Specify a minimum size if a minimum size was not entered as arguments to function FacePulseRate.
%The minimum size is defined by two proportions, ROIMinWidthProportion and ROIMinHeightProportion.

%Scalars; type double.
%Note: ROIGeneralConfig_Setup_MinROIProportions is a custom function located within folder
%'FacePulseRate'.
[ROIMinWidthProportion, ROIMinHeightProportion] = ...
    ROIGeneralConfig_Setup_MinROIProportions(ROIMinWidthProportion, ROIMinHeightProportion, ...
        ROIFacePrimaryXML, VideoReadConfig);


%%%%%% Specify the number of frames to skip after an face-detection algorithm detection %%%%%%

%Specify the number of frames after a face-detection algorithm detection at which to resume the
%face-detection and skin-detection algorithms. The face-detection and skin-detection algorithms are
%skipped for these frames to increase computational efficiency as the algorithms are resource 
%intensive. For these frames, although the algorithms are skipped, the frames are still read and 
%other operations, such as the ROI means operations and the recording of timestamps, are conducted. 
%For skipped frames, ROIs will be interpolated from nearby frames (see function ROIMSIR). To 
%balance computational efficiency with accuracy, frames are not skipped if, within a specified
%number of frames back, detection attempts have not been successful. 

%If no face-detection algorithms were successful on the last frame on which they were applied, the
%face-detection and skin-detection algorithms will not be skipped for the current frame. This is
%implemented to reduce gaps between face-detection algorithms. If the skin-detection algorithm was  
%successful but the face-detection algorithms were not successful, the detection algorithms will
%not be skipped in order to maintain the frequency of face-detection algorithm detections as these
%detections are considered more accurate than skin-detection algorithm detections.

%Within the first read (see function ROIMeans_FirstRead), function 
%ROIMeans_FirstRead_DetermineSkipFrame uses this value, in part, to determine when to skip frames.
%However, this function takes other factors into consideration. Specifically, if the ratio of 
%detections to attemps across a range of frames is  below a specified thresold, the frame isn not 
%skipped. This is implemented to increase the likelihood of obtaining a face detection in spans 
%where it is more difficult to obtain face detections, with the objective of maintaining the 
%frequency of face-detection algorithm detections. Only face-detection algorithm detections, rather 
%than skin-detection algorithm detections, are considered because face-detection algorithm 
%detections are considered more accurate.

%Specify threshold
ROISkipFrameThreshold = .1667;

%This threshold is modified to make the number of frames that should elapse vary depending on the 
%frame rate, such that more frames should elapse when the frame rate is higher.

%Specify type int32 for protection against floating-point gaps.
ROISkipFrameThreshold_adjusted = ...
    int32( ...
        round( ... 
            VideoReadConfig.FS * ROISkipFrameThreshold ...
        ) ...
    );


%%%%%% ROI modification settings %%%%%%

%ROIs are modified to improve their accuracy by function ROIMSIR (see function ROIMSIR for 
%details). ROIMSIR is called on a frame-by-frame basis during the first read (see function 
%ROIMeans_FirstRead_TakeMeans) and during the pre- and post-processing steps of the second read 
%(see function ROIMeans_SecondRead). To conduct the ROI modifications, several thresholds must 
%first be met (see function ROIMeans_FirstRead_TakeMeans for details).

%%%%%% --- Frame cache settings %%%%%%

%Specify the number of frames to be cached during the first-read operations. Frames are cached
%because ROI modifications are performed using ROI values on either side of each ROI. A greater
%number of ROI values on either side of each ROI may improve the accuracy of these modifications. 
%To permit the modifications to use ROI values from ROIs that came after a given ROI, the ROI
%modifications are performed a lagged distance behind the frames that are read. 

%Notes:

% - Increasing the size of the frame cache increases RAM allocation.

% - If compiled functions are enabled (argument UseCompiledFunctionsTF to function FacePulseRate is 
%   true) ROIMSIR_mex, a compiled function, is used in place of ROIMSIR. To improve the efficiency
%   of ROIMSIR_mex, fixed variable sizes are declared in the function to reduce dynamic memory
%   allocation. This fixed sizes correspond to the value of FrameCacheMaxFrames; specifically, the
%   fixed sizes will equal FrameCacheMaxFrames * 2 - 1. For example, if FrameCacheMaxFrames == 115,   
%   the fixed sizes will equal 229. If the value specified here for FrameCacheMaxFrames is changed,
%   the fixed sizes declared in ROIMSIR_mex will need to be changed (to FrameCacheMaxFrames * 2 - 
%   1) and the function recompiled.

%Specify type int32 for protection against floating-point gaps.
FrameCacheMaxFrames = int32(115);

%%%%%% --- Arguments for function ROIMSIR %%%%%%

ROIFinalSmoothingWindows = [11, 200]; 

%Initialize frame index indicating the frame in which function ROIMSIR was first called during 
%first-read operations. 
%Specify type int32 for protection against floating-point gaps.
ROIMSIR_FirstFrameIdx = int32(0);

%Specify the maximum difference of X- and Y-coordinates between an interpolated ROI and the 
%immediately temporally-previous ROI corresponding to a detection. Used when interpolating ROIs in 
%function ROIMSIR. Value is adjusted according to frame dimensions to maintain similar magnitude 
%across videos with different dimensions.
%Specify type int16, as this is the type use for ROIs.
ROIMSIR_DiffMaxDetection = ...
    int16( ...
        single(VideoReadConfig.VidObjWidth) * single(VideoReadConfig.VidObjHeight) / 131660 ...
    );

%Specify the maximum difference of X- and Y-coordinates between ROIs of adjacent frames when
%interpolating ROIs in function ROIMSIR.
%Value is adjusted according to frame dimensions to maintain similar magnitude across videos with
%different dimensions.
%Specify type int16, as this is the type use for ROIs.
ROIMSIR_DiffMaxAdjacent = ...
    int16( ...
        single(VideoReadConfig.VidObjWidth) * single(VideoReadConfig.VidObjHeight) / 29729 ...
    ); 

%Validate window size for smoothing arguments, which can be up to FrameCacheMaxFrames * 2 - 1. 
WindowSizeMax = FrameCacheMaxFrames * 2 - 1;

if ROIFinalSmoothingWindows(1) > WindowSizeMax || ...
   ROIFinalSmoothingWindows(2) > WindowSizeMax

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


%%%%%% First-read lagged processing settings %%%%%%

%Initialize flag indicating whether certain operations are ready during the first-read operations.
%These operations are conducted at a lag, compared to frame reading, because certain thresholds 
%must first be met to begin the operations (see function ROIMeans_FirstRead_TakeMeans for details).
ROIMeansOperationsReadyFirstReadTF = false;

%ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx indicates the maximum frame index to
%which certain operations (tailored skin segmentation, skin detection, taking ROI means) should be 
%conducted in the second-read operations. If the first-read operations conduct any of these 
%operations, this index will indicate the frame before the frame at which first-read operations 
%began these operations (first-read operations will have conducted operations from the frame after
%the index until the end of the video to be processed). For example, if the first-read operations 
%conducted operations from index 500 to 5000, the maximum index to which second-read operations 
%will conduct operations will be index 499. It is possible that the first-read operations will not
%have conducted these operations on any frame (if certain thresholds were not met). In this case, 
%the maximum frame index for second-read operations will correspond to the final frame of the video 
%to be processed, i.e., the frame that corresponds to EndTime.

%Here, in case the first-operations do not conduct these operations for any frame, the index is
%assigned to the tentative index corresponding to EndTime. This index will be reassigned to the 
%accurate index corresponding to EndTime by function ROIMeans_FirstRead_Trim (the actual index
%corresponding to EndTime can only be known once the first read has completed). If the first-read
%operations do conduct these operations for any frame, the index will be reassigned by function
%ROIMeans_FirstRead_TakeMeans; in this case, ROIMeans_FirstRead_Trim will not make a reassignment.

%Specify type int32 for protection against floating-point gaps.
ROIMeansMaxFrameToProcessSecondReadLinIdx = int32(VideoReadConfig.NFrames);


%%%%%% Initialize flags for recursive calling of function ROIMeans_FirstRead %%%%%% 

%Initialize flag whether ROIMeans_FirstRead is to be called recursively.
%Reassigned by function ROIMeans_FirstRead.
RecursiveTF = false;

%Initialize flag whether to return from all recursive calls to function ROIMeans_FirstRead
%Reassigned by function ROIMeans_FirstRead.
ReturnAllTF = false;

%%%%%% Assign configuration struct %%%%%%

%For some variables, specify type single for faster evaluation where used.
%For other variables, specify type double to facilitate calculations with variables of type int16.

ROIGeneralConfig = ...
    struct( ...
        'ROIMinWidthProportion',                      double(ROIMinWidthProportion), ...                          
        'ROIMinHeightProportion',                     double(ROIMinHeightProportion), ... 
        'ROIWidthResizeFactor',                       double(ROIWidthResizeFactor), ...
        'ROIHeightResizeFactor',                      double(ROIHeightResizeFactor), ...            
        'ROIFinalSmoothingWindows',                   int32(ROIFinalSmoothingWindows), ...
        'ROISkipFrameThreshold_adjusted',             ROISkipFrameThreshold_adjusted, ...
        'ROIMSIR_DiffMaxDetection',                   ROIMSIR_DiffMaxDetection, ...
        'ROIMSIR_DiffMaxAdjacent',                    ROIMSIR_DiffMaxAdjacent, ...        
        'ROIMSIR_FirstFrameIdx',                      ROIMSIR_FirstFrameIdx, ...
        'FrameCacheMaxFrames',                        FrameCacheMaxFrames, ...
        'ROIMeansOperationsReadyFirstReadTF',         ROIMeansOperationsReadyFirstReadTF, ...
        'ROIMeansMaxFrameToProcessSecondReadLinIdx',  ROIMeansMaxFrameToProcessSecondReadLinIdx, ...
        'ROISpecifyByArgument',                       ROISpecifyByArgument, ... 
        'ROIIgnoreByArgument',                        ROIIgnoreByArgument, ...
        'RecursiveTF',                                RecursiveTF, ...
        'ReturnAllTF',                                ReturnAllTF, ...
        'UseCompiledFunctionsTF',                     UseCompiledFunctionsTF ...
    );


end %end function

