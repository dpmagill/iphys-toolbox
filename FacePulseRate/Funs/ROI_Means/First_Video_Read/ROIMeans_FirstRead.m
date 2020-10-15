function [ROIGeneralConfig, VideoReadConfig, ROI, ROIDiagnostic, SkinSegmentConfig, ...
          SkinSegmentMasks, PulseRateConfigAndData, SkinDetectConfig, HasROI_TF, ...
          ROIMatchSizeData] = ...          
             ROIMeans_FirstRead(ROIGeneralConfig, FaceDetectConfig, VideoReadConfig, ROI, ...
                 ROIForBBox, ROIDiagnostic, SkinSegmentConfig, SkinSegmentMasks, ...  
                 PulseRateConfigAndData, HasROI_TF, ROIMatchSizeData, SkinDetectConfig, ...
                 OutputConfig)               
%ROIMeans_FirstRead   Take the ROI means of each frame for later use in pulse rate operations.  
%   
%   Helper function to function FacePulseRate. 
%
%
%   Description
%   -----------
%
%   Take the ROI means of each frame for later use in pulse rate operations. To do so, for each 
%   frame, find a frontal or profile face ROI with face-detection algorithm(s) or a facial-skin ROI 
%   with the skin-detection algorithm. Then, modify the ROI for stability and accuracy and apply 
%   skin segmentation to the ROI. FInally, take and store the means of the ROI for later use in  
%   pulse-rate operations.
%
%
%   List of Operations
%   ------------------
%
%   The following operations are conducted in support of taking the ROI means of each frame:
%
%   - The use of a detection algorithm may be skipped to improve efficiency (see function
%     ROIMeans_FirstRead_DetermineSkipFrame).
%
%   - A bounding box is determined for each frame to bound the scanning performed by the 
%     face-detection algorithm(s) and the skin-detection algorithm (see function 
%     ROIMeans_FirstRead_SetBoundingBoxes). Using a bounding box reduces the computational time of   
%     the algorithms and may reduce false positives by restricting the area scanned to that where a
%     face is most likely to be detected. The position of the bounding box is determined based upon
%     the trajectory of previous face movements, and the size is based upon the number of frames 
%     that have elapsed since a detection was last made.
%
%   - A frontal or profile face ROI for each frame is determined based upon a face-detection 
%     algorithm or a skin-detection algorithm unless skipped for efficiency (see function 
%     ROIMeans_FirstRead_AlgSelector). These ROIs are used when taking the means that will be used 
%     for calculating pulse rate (the means are taken later in function 
%     ROIMeans_FirstRead_TakeMeans).  
%
%   - Skin-color samples are collected for use in skin segmentation and the skin-detection 
%     algorithm (see function ROIMeans_FirstRead_CollectSkinColorSamples).
%
%   - Timestamps are recorded for each frame if function readFrame is used rather than 
%     vision.VideoFileWriter. Otherwise, timestamps would have been previously collected by  
%     function VideoReadConfig_Setup. Timestamps are used in functions  
%     ROIMeans_FirstRead_ExtrapolateROI, ROIMSIR, and ROIFrameByFrameSmooth for interpolation, in  
%     function ROIMeans_SecondRead_SkinDetect for seeking, in function PulseRate for pulse rate   
%     calculation, in function TableOutput for writing timestamps to csv, and in function   
%     WriteFaceVideo for displaying timestamps on the output video file, which is written by 
%     function WriteFaceVideo. 
%
%   - The position and size of each ROI are modified to increase accuracy through matching sizes
%     across detection algorithms, detection smoothing, frame-by-frame smoothing, and resizing (see
%     function ROIMSIR, which is called by function ROIMeans_FirstRead_TakeMeans). Frames without a 
%     corresponding ROI are interpolated from nearby frames. A frame may not have a corresponding 
%     ROI due to either no ROI detection being present or frame skipping used for efficiency.  
%
%   - If an ROI contains a low proportion of pixels classified as skin, the ROI is replaced in 
%     favor of the ROI from the previous frame (see function TakeMeans, which is called by function 
%     ROIMeans_FirstRead_TakeMeans).
%
%   - If an ROI that represents a facial profile (as returned by a face-detection algorithm that
%     targets the profile orientation of the face) occurs in a frame in which a pair of eyes is
%     detected, the ROI is discarded (see function FaceDetect_ROIValidate, which called within 
%     function ROIMeans_FirstRead_AlgSelector). It is assumed that a pair of eyes should not be  
%     detectable if the face is in a profile orientation.
%
%   - A check will be conducted to determine whether the skin-segmentation algorithm appears to be
%     oversegmenting ROIs. If so, some skin-segmentation settings will be changed to reduce the
%     severity of segmentation in subsequent operations (see function 
%     SkinSegment_OversegmentationCheck). This check also attempts to modify segmentation settings 
%     in response to dark conditions. Then, the current function (ROIMeans_FirstRead) will start  
%     over so that the modified settings can be applied to all frames of the video. 
%     ROIMeans_FirstRead starts over by a recursive call to itself (see function 
%     SkinSegment_OversegmentationCheck_Reduce).     
%
%   - The means from the RGB (red, green, blue) colorspace are taken from each ROI (see function  
%     TakeMeans, which is called by function ROIMeans_FirstRead_TakeMeans). These means are used 
%     later to calculate pulse rate (in function PulseRate, which is not called by the current 
%     function).
%
%   - The luminance mean is taken from each ROI (see function TakeMeans, which is called by  
%     function ROIMeans_FirstRead_TakeMeans). The luminance means from ROIs can be used to control  
%     the ROI means for luminance variations across frames when the pulse rate is calculated. The  
%     luminance mean is from either the L channel of the LAB colorspace or the Y channel of the   
%     YCbCr colorspace.
%
%   - Diagnostic information from many of the above steps is recorded for later display on the 
%     output video file. This information can be used to fine-tune configuration settings. 
%
%
%   Uses of Frame Cache
%   -------------------
%
%   A number of operations depend on settings that are not assigned until data from a specified 
%   number of frames have been collected (see function ROIGeneralConfig_Setup). These settings 
%   apply to tailored skin segmentation, the skin-detection algorithm (function SkinDetect), the  
%   ROI-adjustment operations (function ROIMSIR), and the taking of means (ROIMeans_TakeMeans). 
%   Consequently, these operations will not begin until a sufficient number of frames has elapsed 
%   to collect the data (the precise number of frames needed varies by video depending on the ease 
%   of collecting some data; see ROIMeans_FirstRead_CollectSkinColorSamples). 
%
%   To reduce the number of frames that need to be reread because settings were not assigned when 
%   they were read by the video reader, read frames are temporarily assigned to a cache of a 
%   limited length, which can store about a couple hundred frames (see function 
%   ROIMeans_FirstRead_TakeMeans). The operations are applied to frames from the cache rather than
%   directly from the video reader to provide additional time for the settings to be assigned.
%   However, it is expected that some frames, near the beginning of the video, will enter and leave 
%   the cache before the settings are assigned. These frames will be reread and processed by  
%   function ROIMeans_SecondRead. The "SecondRead" portion of this function name refers to frames 
%   being reread). Because some frames are processed the first time they are read and  others are
%   processed the second time they are read, a distinction is made in FacePulseRate between frames
%   read during "first-read operations" and "second-read operations". Frames processed by the
%   current function are considered to be processed during first-read operations.    
%
%   The presence of a frame cache, beside being used to increase efficiency, as previously 
%   described, is also used to increase the accuracy of ROI-adjustment operations (function 
%   ROIMSIR). Specifically, these operations index the frame in the middle of the frame cache,
%   rather than the beginning, to be able to base smoothing and other adjustment operations on data
%   for frames both before and after the frame.
%
%
%   Recursion
%   ---------
% 
%   Note the function may call itself under some conditions (see function 
%   SkinSegment_OversegmentationCheck_Reduce).
%
%
%   License
%   -------
%
%   Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%   licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%   licensing, please contact the author.
 
            
%%%%%% Display notification message %%%%%%  

%If skin-detection algorithm enabled
if SkinDetectConfig.ROISkinTF
    
    SkinDetectionText = ' and skin-detection';
else
    
    SkinDetectionText = '';
end

message = ['\nDetermining ROIs with face-detection', SkinDetectionText, ' algorithms ...\n'];

%Display message
fprintf(message);

%Display message immediately
drawnow(); 


%%%%%% Extract some configuration settings for faster evaluation where used %%%%%%

EndTime      = VideoReadConfig.EndTime;      %type double
FrameIdx     = VideoReadConfig.FrameIdx;     %type int32
VidObj       = VideoReadConfig.VidObj;       %VideoReader system object          
VidObjWidth  = VideoReadConfig.VidObjWidth;  %type int16
VidObjHeight = VideoReadConfig.VidObjHeight; %type int16


%%%%%% Bounding box setup %%%%%%

%Set value for function ROIMeans_FirstRead_SetBoundingBoxes. 
%Value is adjusted according to frame dimensions to maintain similar magnitude across videos with
%different dimensions.
%Use floating point during calculation.
%Specify type int16, as this is the type used for ROIs.
SetBoundingBoxes_DiffMax = ...
    int16( ...
        single(VideoReadConfig.VidObjWidth) * single(VideoReadConfig.VidObjHeight) / 41472 ...     
    );
        

%%%%%% Face-detection setup %%%%%%

%Starting value for profile-eyes test
%See function FaceDetect_ConfigSetup for details.
ProfileEyesIdx = FaceDetectConfig.ProfileEyesIdx;


%%%%%% Variables for the oversegmentation check %%%%%%

%See function SkinSegment_OversegmentationCheck.

%If the oversegmentation check and adjustment are enabled
OverSegmentedCheckTF = SkinSegmentConfig.OverSegmentedCheck.CheckTF;

if OverSegmentedCheckTF

    %Note: these variables are only used in a nested function; for them to be persistent in the  
    %main function, they must be accessed in the main function. The assignment here acts as that 
    %accessing.

    %Column vector; type logical.
    FramesLowSkinProportionStatus = ...
        false(SkinSegmentConfig.OverSegmentedCheck.NFramesLowSkinProportionStatus, 1); 

    %Counter for variable FramesLowSkinProportionStatus
    %Scalar; type int16.
    FramesLowSkinProportionCounter = int16(1);

    %Column vector; type single.
    FramesYSingleMean = repmat(235, SkinSegmentConfig.OverSegmentedCheck.NFramesYSingleMean, 1);

    %Counter for variable FramesYSingleMean
    %Scalar; type int16.
    FramesYSingleMeanCounter = int16(1);
end


%%%%%% Thresholds for tailored skin segmentation and the skin-detection algorithm %%%%%%

%Note: these variables are only used in a nested function; for them to be persistent in the main 
%function, they must be accessed in the main function. The assignment here acts as that accessing.

%Initialize flag indicating that color processing should be expedited for tailored skin 
%segmentation and the skin-detection algorithm.
%See function FaceDetect_AlgOrder, which is within function ROIMeans_FirstRead_AlgSelector.
ExpediteColorThresholdsTF = false;

%%%%%% --- Tailored skin-segmentation setup %%%%%%

%Note: these variables are only used in a nested function; for them to be persistent in the main 
%function, they must be accessed in the main function. The assignment here acts as that accessing.

%Initialize flag for message from function SkinSegment_SetThresholds displays, which changes after
%the first call.
FirstCallTF_SetSkinSegmentThresholds = true;

%Preallocate matrix for use in tailoring skin-segmentation color thresholds:

%This matrix will be filled by data from function ROIMeans_FirstRead_CollectSkinColorSamples, which 
%is called by function ROIMeans_FirstRead.
%This matrix will later be an input to function SkinSegment_SetThresholds, where the data will be 
%processed for use. The processed data will be used to set tailored thresholds in function
%SkinSegmentMask_Threshold, which is called by function SkinSegmentMask.
%Use type single for memory conservation and faster evaluation where used.

%For each frame, the following elements will be collected:
%   [ith frame Y min,           ith frame Y max, ...
%    ith frame Cb min,          ith frame Cb max, ...
%    ith frame Cr min,          ith frame Cr max, ...
%    ith frame Cb-Cr ratio min, ith frame Cb-Cr ratio max, ...
%    ith frame H max,           ith frame S min, ...
%    ith frame S max]
DataForTailoredSkinSegmentation = nan(VideoReadConfig.NFrames, 11, 'single');

%%%%%% --- Skin-detection algorithm setup %%%%%% 

%Note: these variables are only used in a nested function; for them to be persistent in the main 
%function, they must be accessed in the main function. The assignment here acts as that accessing.

%Initialize flag for message from function SkinDetect_SetThresholds displays, which changes after
%the first call.
FirstCallTF_SetSkinDetectThresholds = true;

%Initialize flag used to determine size of skin-detection bounding box
IncreaseSkinBBoxFactorStartIdx = 0;

%Preallocate struct for use in determining the color thresholds for the skin-detection algorithm:

%This struct will be filled by data from function ROIMeans_FirstRead_CollectSkinColorSamples, which
%is called by the current function.
%This struct will later be an input to function SkinDetect_SetThresholds, which is called by the
%current function, where the data will be processed for use.
%The processed data will be used for the thresholds in function SkinDetect.
%Specify type double for RGB means as function SkinDetect_RGBProbSkinTrain uses operations that
%require type double.
%Specify type single for YCbCr means for memory conservation and faster evaluation where used.

DataForSkinDetection = ...
    struct( ...
        'RGBMeans',   nan(VideoReadConfig.NFrames, 3), ...
        'YCbCrMeans', nan(VideoReadConfig.NFrames, 3, 'single') ...
    );


%%%%%% ROI-means operations setup %%%%%%

%Setup ROI-means operations, which are conducted by function ROIMeans_FirstRead_Take means, which 
%is called by nested function TakeMeans_Ops)

%Setup function clean up object
%Function ROIMeans_FirstRead_TakeMeans, which is called within nested function TakeMeans_Ops, uses
%persistent variables. There is a procedure within ROIMeans_FirstRead_TakeMeans to remove the
%persistence once the last frame has been processed. However, some conditions may prevent this 
%procedure from occurring. For example, these include an error being thrown, the use of ctrl+c, or 
%the case where no frames are ultimately processed by ROIMeans_FirstRead_TakeMeans. To help ensure
%the persistence of the variables is removed, have the current function complete a cleanup 
%operation to remove the persistence in the event of an error, ctrl+c, or the case of no frames
%being processed by ROIMeans_FirstRead_TakeMeans. Removing the persistence frees the large quantity 
%of memory allocated to the frame cache used within ROIMeans_FirstRead_TakeMeans. To remove
%persistence, unlock the function 'ROIMeans_FirstRead_TakeMeans'. Unlocking the function also  
%allows any new code changes to take effect.
cleanupObj = onCleanup( @()munlock('ROIMeans_FirstRead_TakeMeans') );

%Initialize index used for ROI-means operations
%ii indicates the frame iteration for ROI-means operations. The index lags behind the index i,
%which indicates the current frame read. Counter faciliates assignment of frames to the frame
%cache.
%Specify type int32 for protection against floating-point gaps.
%Note: This variable is only used in a nested function; for it to be persistent in the main  
%function, it must be accessed in the main function. The assignment here acts as that accessing.
ii = int32(0);


%%%%%% Video reading setup %%%%%%

%Initialize flag permitting frames to be read
%This is set to false once the last frame to be processed has been read but before ROI-means 
%operations (see function ROIMeans_FirstRead_Take means, which is called by nested function 
%TakeMeans_Ops) have completed.
ContinueFrameReadTF = true;

%Initialize flag indicating whether the maximum frame index has been set
MaxFrameIdx_SetTF = false;

%System object VideoReader (named VidObj here) will throw an error if the frame index used as an
%argument to read() is greater than the maximum frame index known to it, which is indicated by
%VidObj.NumFrames. Prevent this error from being thrown by capping the frame index at the maximum
%frame index known to VideoReader.
%Type int32.
IdxDoNotExceed = VideoReadConfig.FrameIdxDoNotExceed;

%%%%%% --- Progress notifications setup %%%%%%

%Note: progress notifications are displayed to command window by function LoopProgressNotification.

%Frames in loop for progress notifications
%Note: type of variables is already single for faster evaluation.
if VideoReadConfig.UseVisionTF %if reader is vision.VideoFileReader
    
    %Frame index 
    Notifications_FrameIdx = VideoReadConfig.FrameIdx; %int32
    
else %if reader is VideoReader
    
    %Frame index
    %Estimate the number of frames in loop as this is not known in advance (see function
    %VideoReadConfig).
    %Specify type int32 for protection against floating-point gaps.
    Notifications_FrameIdx = ...
        int32( ...
            1 : VideoReadConfig.FS * (VideoReadConfig.EndTime - VideoReadConfig.StartTime) ...
        );
end

%Frame interval to elapse between each notification message
%Specify type int32 for protection against floating-point gaps.
Notifications_Interval = int32(1000);

%Initialize loop counter for progress notifications 
%Specify type int32 for protection against floating-point gaps.
Notifications_LoopCounter = int32(0);

%Record start time for progress notifications 
Notifications_LoopStartTime = tic; 


%%%%%% Read frames with system object vision.VideoFileReader %%%%%%

if VideoReadConfig.UseVisionTF
    
    %Extract vision.VideoFileReader system object
    videoFReader = VideoReadConfig.videoFReader;

    %Initialize flag indicating whether seeking to StartTime has completed
    SeekCompletedTF = false;

    %Initialize frame index that counts frames from the beginning of the video
    %Only used for seeking to StartTime.
    %Specify type int32 for protection against floating-point gaps.
    FromBeginningIdx = int32(0);

    %Specify type int32 for protection against floating-point gaps.
    FrameIdxMax_Specified = int32( length(VideoReadConfig.FrameTimestampUntrimmed_Single) );
    
    %Initialize frame index that counts frames from StartTime, which may be later than the
    %beginning of the video.
    %Used for all operations except seeking to StartTime.
    %Specify type int32 for protection against floating-point gaps.
    i = int32(0);

    %Initialize end-of-file flag
    EndOfFileTF = false;
    
    %Loop through frames up to index of last timestamp recorded in function ROIMeans_FirstRead
    while ii < VideoReadConfig.MaxFrameIdx

        %Determine whether to continue reading frames
        if i >= FrameIdxMax_Specified            || ... Maximum index according to EndTime
           FrameIdx(max(i, 1)) == IdxDoNotExceed || ... Maximum index function read() can handle; 
                                                    ... for robustness.
           EndOfFileTF                              %   Whether a frame exists in the next frame 
                                                    %   according to vision.VideoFileReader.
      
            ContinueFrameReadTF = false;
            
            %Set the maximum iteration for ROI-means operations
            if ~ MaxFrameIdx_SetTF
 
                VideoReadConfig.MaxFrameIdx = i;
                
                MaxFrameIdx_SetTF = true;
            end 
            
            %If ROI-means operations never began, exit loop now
            %Otherwise, infinite loop.
            if ~ ROIGeneralConfig.ROIMeansOperationsReadyFirstReadTF
                
                break
            end
        end
  
        %Read frame
        if ContinueFrameReadTF
        
            %Read ith frame         
            [VidFrame,      ... M x N x 3 array; type uint8
             EndOfFileTF] = ... Logical flag indicating whether the last frame in file has been 
                            ... read.
                videoFReader();
            
            %%%%%% --- Seek to frame corresponding to StartTime %%%%%%

            %System object vision.VideoFileReader can only start reading at the beginning of the 
            %video, whereas system object VideoReader can start reading at a specified location.  
            %However, vision.VideoFileReader is faster. To take advantage of the speed of  
            %vision.VideoFileReader, it is used when StartTime is close to the beginning of the 
            %video (as specified by visionThreshold). As vision.VideoFileReader starts reading from 
            %the beginning of the video, which may be different from StartTime, seek up to the 
            %frame corresponding to StartTime.

            %Seek if StartTime has not been reached
            if ~ SeekCompletedTF

                %Initialize frame index that counts frames from the beginning of the video (rather
                %than from from StartTime, which is where i begins). This is needed as
                %vision.VideoFileReader always starts reading from the beginning of the video.
                %Only used for seeking to StartTime.
                FromBeginningIdx = FromBeginningIdx + 1;

                %Go to next frame until the frame index counted from beginning of video 
                %(FromBeginningIdx) equals the frame index corresponding to StartTime 
                %(FrameIdx(1)).
                if FromBeginningIdx ~= FrameIdx(1) 

                    %Go to next frame
                    continue 

                else

                    %Indicate seeking completed
                    SeekCompletedTF = true;
                end
            end
            
            %%%%%% --- Frame corresponding to StartTime reached: Begin operations %%%%%%

            %Advance index       
            i = i + 1;        

            %Face-detection and skin-detection operations
            %Nested function.
            Detection_Ops();
            
            %If returning from all recursive calls to the current function (ROIMeans_FirstRead)
            %See function SkinSegment_OversegmentationCheck_Reduce.            
            if ROIGeneralConfig.ReturnAllTF
                
                break
            end
        end       

        %Conduct ROI-means operations
        % - ROI size matching, detection smoothing, interpolation, frame-by-frame smoothing, and 
        %   resizing (see function ROIMSIR)
        % - Take ROI means (see function ROIMeans_TakeMeans)
        %Nested function.
        TakeMeans_Ops();         
        
    end %end vision.VideoFileReader frame loop 

    %Reset vision.VideoFileReader video reader
    %Note: vision.VideoFileReader can also be reset by function 
    %SkinSegment_OversegmentationCheck_Reduce if function ROIMeans_FirstRead is called recursively.
    release(videoFReader);

    
%%%%%% Read frames with system object VideoReader %%%%%%

else
    
    %Note: Function readFrame can be considerably faster than function read().
    
    %Set the CurrentTime property of system object VideoRead a value just before (earlier) than the
    %timestamp corresponding to the frame to be read. This is because readFrame reads the frame  
    %corresponding to the next, not the current, timestamp. Note that the timestamp used to set 
    %CurrentTime does not need to correspond to an actual timestamp; it can be any non-negative 
    %value. Set back by a magnitude of at least 10e-5; otherwise, the precision will be below that   
    %which VideoReader can recognize. 
    %Note: VidObj.CurrentTime requires type double.
    VidObj.CurrentTime = max(VideoReadConfig.StartTime - 10e-5, 0);

    %Initialize index
    %Specify type int32 for protection against floating-point gaps.
    i = int32(0);

    %Record start time for progress notifications 
    Notifications_LoopStartTime = tic;

    %Loop through frames up to last timestamp recorded in function ROIMeans_FirstRead
    while ii < VideoReadConfig.MaxFrameIdx     
             
        if VidObj.CurrentTime >= EndTime           || ... Maximum timestamp according to EndTime             
           FrameIdx( max(i, 1) ) >= IdxDoNotExceed || ... Maximum index function read() can handle; 
                                                      ... for robustness.
           ~ hasFrame(VidObj)                         %   Whether a frame exists in the next frame 
                                                      %   according to VideoReader.

            ContinueFrameReadTF = false;

            %Set the maximum iteration for ROI-means operations
            if ~ MaxFrameIdx_SetTF %value not yet set
            
                VideoReadConfig.MaxFrameIdx = i;
                
                MaxFrameIdx_SetTF = true;
            end
            
            %If ROI-means operations never began, exit loop now
            %Otherwise, infinite loop.
            if ~ ROIGeneralConfig.ROIMeansOperationsReadyFirstReadTF
                
                break
            end
        end
      
        if ContinueFrameReadTF

            %Read the frame corresponding to the frame after the current time
            %Type uint8.
            VidFrame = readFrame(VidObj);

            %Advance index       
            i = i + 1;        

            %Record timestamp       
            %Type double assigned for use where high precsision required.
            %Type single assigned for use where high precision is not needed for faster evaluation.
            Timestamp = VidObj.CurrentTime;
            VideoReadConfig.FrameTimestampUntrimmed_Double(i) = Timestamp;
            VideoReadConfig.FrameTimestampUntrimmed_Single(i) = single(Timestamp);                    
 
            %Face-detection and skin-detection operations
            %Nested function.
            Detection_Ops();
            
            %If returning from all recursive calls to the current function (ROIMeans_FirstRead)
            %See function SkinSegment_OversegmentationCheck_Reduce.
            if ROIGeneralConfig.ReturnAllTF
                
                break
            end
        end
        
        %Conduct ROI-means operations
        % - ROI size matching, detection smoothing, interpolation, frame-by-frame smoothing, and 
        %   resizing (see function ROIMSIR)
        % - Take ROI means (see function ROIMeans_TakeMeans)
        %Nested function.
        TakeMeans_Ops();
    end       
end %end VideoReader 
 

%%%%%% Post-processing operations %%%%%%

%If not returning from recursive calls to the current function (ROIMeans_FirstRead)         
%See function SkinSegment_OversegmentationCheck_Reduce.
if ~ ROIGeneralConfig.ReturnAllTF

    %Note: 'ROIMeans_FirstRead_PostProcess' is a custom function located within folder 
    %'FacePulseRate'.
    [VideoReadConfig, ROI, HasROI_TF, ROIDiagnostic, SkinSegmentConfig, PulseRateConfigAndData, ...
     ROIGeneralConfig, DataForSkinDetection, DataForTailoredSkinSegmentation] = ...    
        ROIMeans_FirstRead_PostProcess(HasROI_TF, VideoReadConfig, ROI, ROIDiagnostic, ...
            SkinSegmentConfig, SkinDetectConfig, ROIGeneralConfig, PulseRateConfigAndData, ...
            DataForSkinDetection, DataForTailoredSkinSegmentation);    

    %If this is the first recursive call to the current function (ROIMeans_FirstRead).
    %See function SkinSegment_OversegmentationCheck_Reduce.
    if ROIGeneralConfig.RecursiveTF    

        %Flag to return from all recursive calls to the current function
        ROIGeneralConfig.ReturnAllTF = true;
    end
end

%=================================================================================================
%Nested functions 
%=================================================================================================
 

%=================================================================================================
function Detection_Ops()
%Detection_Ops   Conduct ROI detection using face-detection algorithms and the skin-detection
%                algorithm.
%
%   A nested function is used to increase readibility as code is shared between the video readers
%   VideoReader and vision.VideoFileReader. An alternative is a local function; however, such a 
%   local function would be most efficient if it could avoid reassigning variables in their
%   entirety on each iteration. Rather, it should reassign only the element of the variable that it
%   modified on a given iteration. Implementing this would require avoiding assigning the variable
%   as output because this output would overwrite the entire variable; instead, only the element
%   modified should be reassigned. Doing so might require more difficult-to-read code than using a
%   nested function, which shares its workspace with the main function. This disadvantage of the
%   nested function is that it increases the number of lines to be read in a single file.
  

%%%%%% Progress notification %%%%%%

%Display progress notification message at intervals of frames

%Note: include the following statement immediately before loop: LoopStartTime = tic

%Note: 'LoopProgressNotification' is a custom function located within folder 'FacePulseRate'.
Notifications_LoopCounter = ...
    LoopProgressNotification(Notifications_Interval, Notifications_FrameIdx, i, ...
        Notifications_LoopStartTime, Notifications_LoopCounter); 


%%%%%% Set thresholds from skin-color samples %%%%%%

%Set the tailored skin-segmentation thresholds and the skin-detection algorithm thresholds from
%skin-color samples.

%Note: 'ROIMeans_FirstRead_SetThresholds' is a custom function located within folder 
%'FacePulseRate'.
[SkinSegmentConfig, SkinDetectConfig, FirstCallTF_SetSkinSegmentThresholds, ...
    FirstCallTF_SetSkinDetectThresholds] = ...
    ROIMeans_FirstRead_SetThresholds(i, DataForTailoredSkinSegmentation, HasROI_TF, ...
        SkinSegmentConfig, SkinDetectConfig, DataForSkinDetection, ...
        FirstCallTF_SetSkinSegmentThresholds, FirstCallTF_SetSkinDetectThresholds);


%%%%%% Determine whether to skip frame %%%%%%

%Note: 'ROIMeans_FirstRead_DetermineSkipFrame' is a custom function located within folder 
%'FacePulseRate'.
HasROI_TF.Skipped(i) = ...
    ROIMeans_FirstRead_DetermineSkipFrame(i, HasROI_TF, ROIGeneralConfig, FaceDetectConfig);

%If an ROI was specified by argument ROISpecifiedByArgument for the ith frame, function 
%ROIMeans_FirstRead_DetermineSkipFrame will have marked the frame to be skipped 
%(HasROI_TF.Skipped(i) == true) so that detection algorithms do not reassign the ROI. Also, 
%function ROIMSIR will not interpolate ROIs where an ROI is assigned by ROISpecifiedByArgument. 

%Skip frame if true
if HasROI_TF.Skipped(i)

    %Skip frame
    return              
end


%%%%%% Assign bounding box(es) for ith frame %%%%%%

%In function ROIMeans_FirstRead_SetBoundingBoxes, an algorithm is used to attempt to reduce the 
%size of the bounding box while having its size and position favorable to accurate face detections.    
%For a given frame, when the bounding box is set, the position of the head is only known for 
%previous frames but not the current frame. The algorithm takes into account the size of previous
%face detections and apparent movement of the face across previous frames to predict the size and
%position of the bounding box. See function ROIMeans_FirstRead_SetBoundingBoxes for details.

%Assign bounding box(es) for ith frame
%Bounding boxes are type int16.
%Note: 'ROIOrientOnFace_SetBoundingBoxes' is a custom function located within folder 
%'FacePulseRate'.
[UseBoundingBoxFaceTF, BoundingBoxFace, SkinBBoxAvailableTF, BoundingBoxSkin, ...
 ROIForBoundingBoxSkin_FR, IncreaseSkinBBoxFactorStartIdx] = ...
    ROIMeans_FirstRead_SetBoundingBoxes(i, ROIForBBox, HasROI_TF, FaceDetectConfig, ...
        SkinDetectConfig, ROIGeneralConfig, VideoReadConfig, SetBoundingBoxes_DiffMax, ...
        IncreaseSkinBBoxFactorStartIdx);                    

    
%%%%%% Skin-detection algorithm setup for ith frame %%%%%%

%Determine whether to activate the skin-detection algorithm for ith frame
%Once activated, it remains activated for remaining frames.
%Note: this flag will be reset if function ROIMeans_FirstRead is called recursively (see function 
%SkinSegment_OversegmentationCheck_Reduce).
if ~ SkinDetectConfig.SkinDetectionReadyTF 

    %Set flag indicating whether the skin-detection algorithm can be activated
    %Note: this flag and flags SkinDetectConfig.Thresholds.SetTF and 
    %SkinSegmentConfig.TailoredData.OpsReadyTF will be reset if function ROIMeans_FirstRead is 
    %called recursively (see function SkinSegment_OversegmentationCheck_Reduce).                                              
    SkinDetectConfig.SkinDetectionReadyTF = ...
        SkinBBoxAvailableTF &&                     ... A skin bounding box was able to be produced; 
                                                   ... assigned in function 
                                                   ... ROIMeans_FirstRead_SetBoundingBoxes.
        SkinDetectConfig.Thresholds.SetTF &&       ... The thresholds have been set for the 
                                                   ... skin-detection algorithm.
        SkinSegmentConfig.TailoredData.OpsReadyTF; %   The thresholds have been set for tailored   
                                                   %   skin segmentation, which is required for the  
                                                   %   skin-detection algorithm. 

    %If activated, display notification message                                                   
    if SkinDetectConfig.SkinDetectionReadyTF                                               
         
        message = '\n       Skin-detection algorithm activated.';

        %Display message on command window
        fprintf(message);

        %Display message immediately
        drawnow();        
    end
end


%%%%%% Determine whether to expedite the setting of color thresholds %%%%%%

%Determine whether to expedite the setting of color thresholds used by tailored skin segmentation
%and the skin-detection algorithm.

%Note: 'ROIMeans_FirstRead_ExpediteThresholds' is a custom function located within folder 
%'FacePulseRate'.
ExpediteColorThresholdsTF = ...
    ROIMeans_FirstRead_ExpediteThresholds(i, SkinSegmentConfig, SkinDetectConfig);                         
       

%%%%%% Scan frame with face-detection algorithm(s) and the skin-detection algorithm %%%%%% 

%Scan with one or more algorithms
%This funtion applies each face-detection algorithm and the skin-detection algorithm in turn. An  
%algorithm is run only if the previous algorithm did not make a detection. The order in which the
%face-detection algorithms are run changes dynamically.
%Also, if a primary face-detection algorithm detection is made, the YCbCr and RGB matrices from the
%ROI are returned to record color data used to set the thresholds for tailored skin segmentation 
%and the skin-detection algorithm.

%Note: 'ROIMeans_FirstRead_AlgSelector' is a custom function located within folder 'FacePulseRate'. 
[ROISuccessful, FacePrimaryAttemptedTF_ith, FacePrimaryTF_ith, SkinNotPresent_Pri_ith, ...
 ProfileEyesPresent_Pri_ith, FaceSecondary1AttemptedTF_ith, FaceSecondary1TF_ith, ...          
 SkinNotPresent_Sec1_ith, ProfileEyesPresent_Sec1_ith, FaceSecondary2AttemptedTF_ith, ...
 FaceSecondary2TF_ith, SkinNotPresent_Sec2_ith, ProfileEyesPresent_Sec2_ith, ...
 BBox_Scan_FaceAlg_ith, YSingle, CbSingle, CrSingle, RUint8, GUint8, BUint8, HSingle, SSingle, ...
 IsSkinMask_LocalRange, NRows_Matrix, NCols_Matrix, ROIDiagnostic_ROISkin_ith, SkinTF_ith, ...
 SkinAttemptedTF_ith, SkinNotPresent_Skin_ith, ProfileEyesIdx, ProportionSkin_AlgName, ...
 ProportionSkin, YSingle_OversegmentationCheck, OversegmentationCheckReady] = ...
    ROIMeans_FirstRead_AlgSelector(i, ROIGeneralConfig, FaceDetectConfig, UseBoundingBoxFaceTF, ...
        BoundingBoxFace, VidFrame, VideoReadConfig, SkinSegmentConfig, HasROI_TF, ...
        SkinDetectConfig, OutputConfig, BoundingBoxSkin, ROIForBoundingBoxSkin_FR, ...
        ExpediteColorThresholdsTF, ProfileEyesIdx);              

%Store detection results:

%If ROI successfully detected
if FacePrimaryTF_ith    || ... primary face-detection algorithm
   FaceSecondary1TF_ith || ... secondary #1 face-detection algorithm
   FaceSecondary2TF_ith || ... secondary #2 face-detection algorithm
   SkinTF_ith              %   skin-detection algorithm

    %Type int16.
    ROI(i, :) = ROISuccessful;         
        
    %Optionally adjust size of ROI used for subsequent bounding boxes
    %If the size of the ROI is adjusted, the size of the subsequent bounding boxes will be adjusted
    %because their sizes are based on the sizes of the ROIs.
    %Only used for face-detection algorithm detections (not skin-detection algorithm detections).   
    if ~ SkinTF_ith
    
        %Adjustment factor to use
        %The factors were specified as arguments to function FacePulseRate.
        %Note: these categories are mutually exclusive: only one is true. One of these must be true
        %if ROISuccessful not empty and if SkinTF_ith is not true.
        %Type double for compatibility with type int16, which is the type of the ROIs.
        if FacePrimaryTF_ith

            ROISizeAdjustmentFactor = FaceDetectConfig.ROIFace_ChangeFactorROIPrimary;

        elseif FaceSecondary1TF_ith

            ROISizeAdjustmentFactor = FaceDetectConfig.ROIFace_ChangeFactorROISecondary1; 

        else %FaceSecondary2TF_ith

            ROISizeAdjustmentFactor = FaceDetectConfig.ROIFace_ChangeFactorROISecondary2; 
        end    

        %Resize the ROI:
        
        %Use compiled function       
        if ROIGeneralConfig.UseCompiledFunctionsTF           
 
            %Function ROIResize scales ROI as specified and also prevents scaled ROI from exceeding
            %frame dimensions.
            %Type int16.
            %Note: ROIResize is a custom compiled function located within folder 'FacePulseRate'.
            %For source code, see file ROIResize.m.
            ROIForBBox(i, :) = ...
                ROIResize_mex( ...
                    ROISuccessful,           ... ROI to adjust; type int16
                    int32(1),                ... ROI index (1 entered if only 1 ROI); type int32
                    ROISizeAdjustmentFactor, ... Width resizing scale factor; type double
                    ROISizeAdjustmentFactor, ... Height resizing scale factor; type double
                    VidObjWidth,             ... To keep adjustment within frame dimensions; type 
                                             ... int16.
                    VidObjHeight             ...             
                );         
            
        %Do not use compiled function
        else
            
            %Type int16.
            %Note: ROIResize is a custom function located within folder 'FacePulseRate'.
            ROIForBBox(i, :) = ...
                ROIResize( ...
                    ROISuccessful, ... 
                    1, ... 
                    ROISizeAdjustmentFactor, ... 
                    ROISizeAdjustmentFactor, ... 
                    VidObjWidth, ... 
                    VidObjHeight ...             
                );            
        end
    end     

    %Record ROI coordinates for reference before size matching, smoothing, interpolation,
    %and resizing.
    %The non-modified ROIs will be displayed on the output video to diagnose false positives or 
    %false negatives that may have been caused by size matching, smoothing, interpolation, and
    %resizing.
    %Convert from type int16 to type uint16 because signed operations not conducted with this
    %variable.
    ROIDiagnostic.ROI_NonSmoothed(i, :) = uint16(ROISuccessful);            
end

HasROI_TF.FacePrimaryAttempted(i)    = FacePrimaryAttemptedTF_ith;
HasROI_TF.FacePrimary(i)             = FacePrimaryTF_ith;
HasROI_TF.SkinNotPresent_Pri(i)      = SkinNotPresent_Pri_ith;
HasROI_TF.ProfileEyesPresent_Pri(i)  = ProfileEyesPresent_Pri_ith;
HasROI_TF.FaceSecondary1Attempted(i) = FaceSecondary1AttemptedTF_ith;
HasROI_TF.FaceSecondary1(i)          = FaceSecondary1TF_ith;
HasROI_TF.SkinNotPresent_Sec1(i)     = SkinNotPresent_Sec1_ith;
HasROI_TF.ProfileEyesPresent_Sec1(i) = ProfileEyesPresent_Sec1_ith;
HasROI_TF.FaceSecondary2Attempted(i) = FaceSecondary2AttemptedTF_ith;
HasROI_TF.FaceSecondary2(i)          = FaceSecondary2TF_ith;
HasROI_TF.SkinNotPresent_Sec2(i)     = SkinNotPresent_Sec2_ith;
HasROI_TF.ProfileEyesPresent_Sec2(i) = ProfileEyesPresent_Sec2_ith;
HasROI_TF.Skin(i)                    = SkinTF_ith;
HasROI_TF.SkinAttempted(i)           = SkinAttemptedTF_ith;
HasROI_TF.SkinNotPresent_Skin(i)     = SkinNotPresent_Skin_ith;

%Assign ROI diagnostics from skin-detection algorithm:

if SkinAttemptedTF_ith

    %Note: struct ROIDiagnostic was preallocated by function SkinDetect_PreallocateDiagnosticData.

    ROIDiagnostic.BBox_Scan.SkinAlg(i, :)       = ROIDiagnostic_ROISkin_ith.BBox_Scan_SkinAlg;    
    ROIDiagnostic.ROISkin.RegionAnyAvailable(i) = ROIDiagnostic_ROISkin_ith.RegionAnyAvailable;

    %If the display of skin-detection algorithm diagnostics on the output video is enabled
    if OutputConfig.WriteVideoShowROISkinDiagnosisTF
    
        ROIDiagnostic.ROISkin.RegionSkinROIAttempted(i)              = ROIDiagnostic_ROISkin_ith.RegionSkinROIAttempted;
        ROIDiagnostic.ROISkin.ProportionSkinPixelsTooLow(i)          = ROIDiagnostic_ROISkin_ith.ProportionSkinPixelsTooLow;
        ROIDiagnostic.ROISkin.RegionBoundaries(i).SelectedLinIdx     = ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx;
        ROIDiagnostic.ROISkin.RegionBoundaries(i).CandidateLinIdx    = ROIDiagnostic_ROISkin_ith.RegionBoundaries_CandidateLinIdx;
        ROIDiagnostic.ROISkin.RegionBoundaries(i).RejectedLinIdx     = ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx;
        ROIDiagnostic.ROISkin.RegionCentroids(i).SelectedXY          = ROIDiagnostic_ROISkin_ith.RegionCentroids_SelectedXY;
        ROIDiagnostic.ROISkin.RegionCentroids(i).CandidateXY         = ROIDiagnostic_ROISkin_ith.RegionCentroids_CandidateXY;
        ROIDiagnostic.ROISkin.RegionCentroids(i).RejectedXY          = ROIDiagnostic_ROISkin_ith.RegionCentroids_RejectedXY;
        ROIDiagnostic.ROISkin.PredictedROI_center(i, :)              = ROIDiagnostic_ROISkin_ith.PredictedROI_center;
        ROIDiagnostic.ROISkin.RegionScores(i).SelectedRGBProb        = ROIDiagnostic_ROISkin_ith.RegionScores_SelectedRGBProb;
        ROIDiagnostic.ROISkin.RegionScores(i).CandidateRGBProb       = ROIDiagnostic_ROISkin_ith.RegionScores_CandidateRGBProb;
        ROIDiagnostic.ROISkin.RegionScores(i).RejectedRGBProb        = ROIDiagnostic_ROISkin_ith.RegionScores_RejectedRGBProb;
        ROIDiagnostic.ROISkin.RegionScores(i).SelectedYCbCrZ         = ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ;
        ROIDiagnostic.ROISkin.RegionScores(i).CandidateYCbCrZ        = ROIDiagnostic_ROISkin_ith.RegionScores_CandidateYCbCrZ;
        ROIDiagnostic.ROISkin.RegionScores(i).RejectedYCbCrZ         = ROIDiagnostic_ROISkin_ith.RegionScores_RejectedYCbCrZ;
        ROIDiagnostic.ROISkin.RegionRankings(i).CandidateHi2Lo       = ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo;
        ROIDiagnostic.ROISkin.RegionCrSDScores(i).RejectedCrSDLinIdx = ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSDLinIdx;
        ROIDiagnostic.ROISkin.RegionCrSDScores(i).RejectedCrSD       = ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSD;
        ROIDiagnostic.ROISkin.RegionNPixels(i).RejectedN             = ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedN;
        ROIDiagnostic.ROISkin.RegionNPixels(i).RejectedLowNTF        = ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedLowNTF;
    end
end

%Record coordinates of the bounding boxes used to bound scanning by the detection algorithms:

%The bounding boxes will be displayed on the output video for diagnosis. Ideally, the bounding 
%boxes should be large enough to capture the face at all times, which will allow a detection to be
%made by an algorithm. However, to reduce processing time, the bounding box should not be too much  
%larger than than the face. To strike a balance between allowing a detection and reducing 
%processing time, the size should be somewhat larger than then last known position of the face to  
%anticipate head movement from frame to frame. Specifically, for a given frame, when the bounding 
%box is set, the position of the head is only known for previous frames but not the current frame,    
%so the bounding box must be made large enough to allow for movement from the immediately previous 
%frame to the current frame. See function ROIMeans_FirstRead_SetBoundingBoxes for details on the
%method used to aniticipate the position of the head in the current frame.
%Type uint16 as signed operations not conducted with this variable.
ROIDiagnostic.BBox_Scan.FaceAlg(i, :) = BBox_Scan_FaceAlg_ith;


%%%%%% Record skin-color samples for use in tailored skin segmentation and skin detection %%%%%%

%Record skin-color samples that will be processed later to set color thresholds for use in tailored  
%skin segmentation and the skin-detection algorithm. Setting the thresholds is conducted by 
%functions SkinSegment_SetThresholds and SkinDetect_SetThresholds.

%Only collect colors from primary face-detection algorithm as the primary algorithm is assumed to 
%contain the least false positives. Also, the ROI of the primary algorithm is expected to be 
%comprised almost entirely of pixels corresponding to skin because it is assumed that the 
%Viola-Jones face detector specified will detect the face in a frontal orientation (the default
%Viola-Jones face detector for the primary algorithm detects frontal orientations, but this can be
%changed by specifying argument ROIFacePrimaryXML to function FacePulseRate). If the specified  
%secondary face-detection algorithms detect profile orientations (the default secondary #1 
%algorithm detects profile orientations, but this can be changed by specifying argument 
%ROIFaceSecondary1XML to function FacePulseRate), pixels that do not correspond to skin may be 
%incorrectly collected. 

%Record only if skin segmentation enabled.
%Note: when an ROI is completely segmented by skin segmentation, color values will be returned as
%NaN. These values will be ignored during the setting of color thresholds.
if HasROI_TF.FacePrimary(i) && ...
   SkinSegmentConfig.SkinSegmentTF 
    
    %%%%%% --- Extract color samples %%%%%%

    %If compiled functions enabled
    if ROIGeneralConfig.UseCompiledFunctionsTF
        
        %Note: 'ROIMeans_FirstRead_CollectSkinColorSamples_mex' is a custom compiled function  
        %located within folder 'FacePulseRate'. For source, see function
        %ROIMeans_FirstRead_CollectSkinColorSamples.m.
        [ithPrimaryROIRGBMeans, ithPrimaryROIYCbCrMeans, ithPrimaryROIYCbCrHSMinsMaxs] = ...          
            ROIMeans_FirstRead_CollectSkinColorSamples_mex(YSingle, CbSingle, CrSingle, RUint8, ...
                 GUint8, BUint8, HSingle, SSingle, IsSkinMask_LocalRange, NRows_Matrix, ...
                 NCols_Matrix, SkinSegmentConfig.Args, SkinSegmentConfig.UseCompiledFunctionsTF);                 
         
    %If compiled functions not enabled         
    else
        
        %Note: 'ROIMeans_FirstRead_CollectSkinColorSamples' is a custom function located within 
        %folder 'FacePulseRate'.        
        [ithPrimaryROIRGBMeans, ithPrimaryROIYCbCrMeans, ithPrimaryROIYCbCrHSMinsMaxs] = ...          
            ROIMeans_FirstRead_CollectSkinColorSamples(YSingle, CbSingle, CrSingle, RUint8, ...
                GUint8, BUint8, HSingle, SSingle, IsSkinMask_LocalRange, NRows_Matrix, ...
                NCols_Matrix, SkinSegmentConfig.Args, SkinSegmentConfig.UseCompiledFunctionsTF);        
    end

    %%%%%% --- Assign color samples %%%%%%
    
    %Assign color samples from primary face-detection ROI of ith frame to variables used to set
    %color thresholds. These samples will be used to set thresholds for tailored skin segmentation  
    %and the face-detection algorithm. Color samples used to set tailored skin-segmentation  
    %thresholds will be processed by function SkinSegment_SetThresholds. Color samples used to set   
    %skin-detection algorithm thresolds will be processed by function SkinDetect_SetThresholds.
        
    %%%%%% >>>>>> Assign color samples for tailored skin segmentation %%%%%%
    
    %ROI YCbCr and HS mins and maxes
    %[min(Y), max(Y), min(Cb), max(Cb), min(Cr), max(Cr), min(CbCrRatio), max(CbCrRatio), ...
    % max(H), min(S), max(S)]. 
    %Type single.
    DataForTailoredSkinSegmentation(i, :) = ithPrimaryROIYCbCrHSMinsMaxs;            

    %%%%%% >>>>>> Assign color samples for the skin-detection algorithm %%%%%%
    
    %ROI RGB means
    %[mean(R), mean(G), mean(B)].   
    %Type double.
    DataForSkinDetection.RGBMeans(i, :) = ithPrimaryROIRGBMeans;

    %ROI YCbCr means
    %[mean(Y), mean(Cb), mean(Cr)].
    %Type single.
    DataForSkinDetection.YCbCrMeans(i, :) = ithPrimaryROIYCbCrMeans;

end %end recording of skin colors


%%%%%% Over-segmentation check %%%%%%  
         
%Reduce the severity of skin-segmentation settings if it appears they are causing oversegmentation.

if OverSegmentedCheckTF &&    ... if the oversegmentation check and adjustment are enabled
   OversegmentationCheckReady ... if a face-detection ROI proportion available
                    
    %Note: SkinSegment_OversegmentationCheck is a custom function located within folder 
    %'FacePulseRate'.
    [MakeMorphLessSevereTF,          ... Flag to reduce the severity of the morphological close
     MakeColorThresLessSevereTF,     ... Flag to reduce the severity of pixel-color thresholds 
     MorphCloseSEMediumWidth_Tuned,  ... Adjusted severity setting; scalar, type int16
     MorphCloseSELargeWidth_Tuned,   ... Adjusted severity setting; scalar, type int16
     SkinSegmentSeverityFactor,      ... Adjusted severity setting; scalar, type double 
     LowSkinProportionTF,            ... Whether the skin proportion was low for the ith frame;
                                     ... scalar, type logical.
     FramesLowSkinProportionCounter, ... Counter corresponding to FramesLowSkinProportionStatus; 
                                     ... scalar, type int16.                                     
     YSingleMean,                    ... The mean of the Y colorspace for the ith frame; scalar, 
                                     ... type double.
     FramesYSingleMeanCounter] =     ... Counter corresponding to FramesYSingleMean; 
                                     ... scalar, type int16. 
        SkinSegment_OversegmentationCheck(ProportionSkin, ProportionSkin_AlgName, ...
            YSingle_OversegmentationCheck, FramesLowSkinProportionStatus, ...
            FramesLowSkinProportionCounter, FramesYSingleMean, FramesYSingleMeanCounter, ...
            SkinSegmentConfig);           
    
    %Update status of previous frames:
    
    %If the morphological close settings have not been reduced the maximum number of times
    %Note: this flag is set by function SkinSegment_OversegmentationCheck_Reduce. 
    if SkinSegmentConfig.OverSegmentedCheck.NMorphReductions < ... 
       SkinSegmentConfig.OverSegmentedCheck.NMorphReductionLimit    
    
        %Whether a frame is below the skin-proportion threshold
        %Column vector; type logical.
        FramesLowSkinProportionStatus(FramesLowSkinProportionCounter) = LowSkinProportionTF;
    end    
    
    %If the pixel-color thresholds have not been reduced previously
    %Note: this flag is set by function SkinSegment_OversegmentationCheck_Reduce. 
    if ~ SkinSegmentConfig.OverSegmentedCheck.PixelColorsAdjustedTF
    
        %Whether a frame is below the darkness threshold    
        %Column vector; type single.        
        FramesYSingleMean(FramesYSingleMeanCounter) = YSingleMean;    
    end
    
    %%%%%% --- If the severity of settings is to be reduced %%%%%%
    
    if MakeMorphLessSevereTF || MakeColorThresLessSevereTF

        %Function SkinSegment_OversegmentationCheck_Reduce will apply the reductions of the 
        %severity of skin-segmentation settings assigned by function
        %SkinSegment_OversegmentationCheck (for a discussion of the settings assigned, see function   
        %SkinSegment_OversegmentationCheck). Then, in order to have the modifications to settings 
        %apply to all frames, start function ROIMeans_FirstRead from the beginning. To start it  
        %from the beginning, it will be called by SkinSegment_OversegmentationCheck_Reduce. Some
        %settings previously assigned within ROIMeans_FirstRead, such as those regarding the 
        %modified skin-segmentation settings, will not reassigned during the call, but most other 
        %settings and variables will be reassigned.  
       
        %Note: SkinSegment_OversegmentationCheck_Reduce calls ROIMeans_FirstRead; as   
        %SkinSegment_OversegmentationCheck_Reduce is called by ROIMeans_FirstRead,
        %ROIMeans_FirstRead is called recursively.
         
        %Assign empty input if videoFReader not used
        if ~ VideoReadConfig.UseVisionTF
            
            videoFReader = [];
        end
        
        %Note: SkinSegment_OversegmentationCheck_Reduce is a custom function located within folder 
        %'FacePulseRate'.        
        [ROIGeneralConfig, VideoReadConfig, ROI, ROIDiagnostic, SkinSegmentConfig, ...
         SkinSegmentMasks, PulseRateConfigAndData, SkinDetectConfig, HasROI_TF, ...
         ROIMatchSizeData] = ...        
            SkinSegment_OversegmentationCheck_Reduce(MakeMorphLessSevereTF, ...
                MakeColorThresLessSevereTF,MorphCloseSEMediumWidth_Tuned, ... 
                MorphCloseSELargeWidth_Tuned, SkinSegmentSeverityFactor, videoFReader, ...
                ROIGeneralConfig, FaceDetectConfig, VideoReadConfig, SkinSegmentConfig, ...
                SkinSegmentMasks, PulseRateConfigAndData, SkinDetectConfig, OutputConfig);                                               
    end
end


end %end nested function


%=================================================================================================
function TakeMeans_Ops()
%TakeMeans_Ops   Conduct ROI modifications, apply skin segmentation, and take means for pulse-rate
%                operations for a frame.
%
%    Description:
%
%    For each frame, once ROI-means operations are ready (when
%    ROIGeneralConfig.ROIMeansOperationsReadyFirstReadTF is true; see function 
%    ROIMeans_FirstRead_TakeMeans for details), conduct ROI modification operations to improve 
%    accuracy. Specifically, if a frame contains a detection, conduct size matching, detection 
%    smoothing, frame-by-frame smoothing, and resizing according to arguments ROIWidthResizeFactor 
%    and ROIHeightResizeFactor. If a frame does not have a detection, conduct many of the same 
%    operations but interpolate the ROI from nearby ROIs. Then, apply skin segmentation to the ROI 
%    and then take the RGB and luminance means of the ROI. Adjust the ROI coordinates to those of 
%    the previous frame if the proportion of pixels classified as skin is below the specified 
%    threshold.
%
%    The ROI-means operations lag behind the frame-reading iterations in order for enough frames to 
%    elapse foroperations to be ready (for details, see function ROIMeans_FirstRead_TakeMeans).
%    Whereas the frame reading iteration uses index i, the ROI-means operations use index ii, which
%    lags behind index i.


%%%%%% Conduct ROI-means operations for iith frame %%%%%%

%Note: 'ROIMeans_FirstRead_TakeMeans' is a custom function located within folder 'FacePulseRate'.
[ii, ROIOut_ii, ROIMatchSizeData, ROIOutBeforeFrameByFrameSmoothing_ii, InterpolatedLinIdx_ii, ...
 ROIGeneralConfig, SkinRGBMeans_ii, IsNotSkin_PixelColor_Packed_ii, ...
 AdjustedBecauseLowSkinProportionTF_ii, ROIAdjusted_ii, Y_of_YCbCr_ii, L_of_LAB_ii] = ...  
    ROIMeans_FirstRead_TakeMeans(i, ii, ContinueFrameReadTF, VidFrame, ROI, HasROI_TF, ...  
        ROIMatchSizeData, SkinSegmentConfig, FaceDetectConfig, SkinDetectConfig, ...
        ROIGeneralConfig, PulseRateConfigAndData, VideoReadConfig, OutputConfig);

   
%%%%%% Assign ROI-means operations output from iith frame to variables %%%%%%                  

%Assign output from iith iteration to variables 
%The assignment is not made within function ROIMeans_FirstRead_TakeMeans because this would result
%in the variables being entirely reassigned on each iteration; by making the assignment outside the
%function, only the iith element of each variable is reassigned on each iteration.

%If ROI-means operations were conduced
if ROIGeneralConfig.ROIMeansOperationsReadyFirstReadTF   
    
    %Assign modified ROI
    %Type int16
    ROI(ii, :) = ROIOut_ii; 
    
    %Record ROIs not modified by frame-by-frame smoothing or resizing, two of the operations 
    %conducted in function ROIMSIR. The two operations that occured prior to these, size matching 
    %and detection smoothing, are present. This permits diagnosis of false positives or false 
    %negatives resulting from size matching and detection smoothing. The ROI coordinates will be  
    %superimposed on the output video for assessment.
    %Note: the final ROIs differ from these only as a result of receiving frame-by-frame smoothing 
    %and resizing. Hence, the final ROIs can be inspected to diagnose false positives or false   
    %negatives resulting from frame-by-frame smoothing and resizing. 
    %Convert from type int16 to type uint16 because signed operations not conducted with this
    %variable.
    ROIDiagnostic.ROI_NonFinalSmoothed(ii, :) = uint16(ROIOutBeforeFrameByFrameSmoothing_ii); 
    
    %Record use of interpolation for use below in function ROIMeans_TakeMeans
    %This value will also be output, where it will be assigned on a persistent basis to struct 
    %HasROI_TF; HasROI_TF is not assigned as output here to avoid inefficiency that would otherwise  
    %result from reassiging the entire variable on each iteration.
    %0 indicates the iith ROI was not interpolated
    if InterpolatedLinIdx_ii ~= 0

        HasROI_TF.Interpolated(InterpolatedLinIdx_ii) = true;
    end
 
    %Assign RGB mean
    %Type double.
    PulseRateConfigAndData.ColorData.SkinRGBMeans(ii, :) = SkinRGBMeans_ii;     
        
    %If the ROI from the previous frame was used due to a low proportion of pixels classified as
    %skin within the ROI.
    if AdjustedBecauseLowSkinProportionTF_ii

        %Logical value indicating that the ROI from the previous frame was used
        HasROI_TF.AdjustedBecauseLowSkinProportion(ii) = AdjustedBecauseLowSkinProportionTF_ii;  
        
        %Assign adjusted value to ROI matrix
        %Type int16
        ROI(ii, :) = ROIAdjusted_ii;
    end

    %Assign the binary-packed inverted skin-segmentation mask that corresponds to the ROI.
    %These values will be used in function WriteFaceVideo to display the skin-segmentation mask on
    %the output video.
    if SkinSegmentConfig.SkinSegmentTF        
        
        %Inverted skin-segmentation mask as binary-packed image
        %Matrix; type uint32.
        SkinSegmentMasks(ii).IsNotSkin_PixelColor_Packed = IsNotSkin_PixelColor_Packed_ii;                
    end

    %If controlling ROI RGB means for luminance is enabled
    if PulseRateConfigAndData.ControlLuminanceTF

        %Luminance mean is specified to be from YCbCr colorspace
        %Y is the luminance channel of the YCbCr colorspace.
        if PulseRateConfigAndData.ControlLuminanceColorspace == 'Y'

            %Assign luminance mean
            %Type double.            
            PulseRateConfigAndData.ColorData.SkinLuminanceMeans.Y_of_YCbCr(ii) = Y_of_YCbCr_ii;

        %Luminance mean is specified to be from LAB colorspace
        %L is the luminance channel of the LAB colorspace.
        elseif PulseRateConfigAndData.ControlLuminanceColorspace == 'L'

            %Assign luminance mean
            %Type double.            
            PulseRateConfigAndData.ColorData.SkinLuminanceMeans.L_of_LAB(ii) = L_of_LAB_ii;
        end        
    end
end


end %end nested function
    

end %end main function

