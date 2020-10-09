function [ROI, ROIDiagnostic, HasROI_TF] = ...
             ROIMeans_SecondRead_SkinDetect(VideoReadConfig, ROI, ROIDiagnostic, ... 
                 ROIGeneralConfig, SkinDetectConfig, HasROI_TF, SkinSegmentConfig, OutputConfig)               
%ROIMeans_SecondRead_SkinDetect  Conduct the skin-detection algorithm for any frames where the 
%                                first-read operations were not ready to submit frames to the 
%                                skin-detection algorithm. 
%                                 
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_SecondRead.
%
%
%    Description
%    -----------
%
%    Conduct the skin-detection algorithm (function SkinDetect) for any frames where the first-read 
%    operations were not ready to submit frames to the skin-detection algorithm. These frames come 
%    temporally before the frames on which operations were conducted by the first read. 
%
%    Note: for frames that were ready to receive the skin-detection algorithm within the first-read 
%    operations, function SkinDetect was called by function ROIMeans_FirstRead_AlgSelector.  
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Display notification message %%%%%%

message = ...
    ['\n\nDetecting ROIs with skin-detection algorithm for frames near beginning', ...
     '\nof video where the skin-detection algorithm was not previously applied ...\n'];

%Display message      
fprintf(message);

%Display message immediately
drawnow(); 


%%%%%% Prepare for operations %%%%%%

%Flag to function SkinDetect that function is not called from first read
FirstReadTF = false; 

%Initialize flag used to determine size of skin-detection bounding box
IncreaseSkinBBoxFactorStartIdx = -1;

%%%%%% --- Prep frame list %%%%%% 

%Only apply the algorithm or post-processing to frames that came before the skin-detection 
%algorithm could be applied during the first video read (in function ROIMeans_FirstRead). The index  
%of frames that were processed in the first video read begins on the index of the first call to 
%function ROIMeans_TakeMeans (by function ROIMeans_FirstRead_TakeMeans). The index of the first   
%call is specified by ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx (see function
%ROIGeneralConfig_Setup for details).

%Specify frame that occurred before the first call to function ROIMeans_TakeMeans by function 
%ROIMeans_FirstRead_TakeMeans. If no call was made to function ROIMeans_TakeMeans by function
%ROIMeans_FirstRead_TakeMeans ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx specifies 
%the final frame of the video to be processed (see function ROIGeneralConfig_Setup for details).
MaxFrameToProcessLinIdx = ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx;

%Also determine frames to loop through based on value specified by ROISkinSkipFrameThreshold. 
%Specifically, check whether there are a certain number of frames, as specified by 
%ROISkinSkipFrameThreshold, on either side of the current frame with no detections. This makes
%the submission of frames to the skin-detection algorithm more conservative, which is designed to 
%reduce false positives and reduce computations.

%Logical vector with length of frames index that indicates, for each frame, whether a face was 
%detected by a face-detection algorithm or a frame was skipped in function ROIMeans_FirstRead.
%Note: frame skipping is mainly used for computational efficiency, but it is also used when frames 
%are specified to be ignored by ROIIgnoreByArgument or when ROIs are specified for specified frames 
%by argument ROISpecifyByArgument. ROIIgnoreByArgument and ROISpecifyByArgument are arguments to
%function FacePulseRate.
FaceDetectionOrSkipped = ...
    HasROI_TF.FacePrimary    | ... face detected
    HasROI_TF.FaceSecondary1 | ...
    HasROI_TF.FaceSecondary2 | ... 
    HasROI_TF.Skipped;         %   frame skipped

%Specify the number of frames without face detections to have passed before activating the skin-
%detection algorithm.
%Divide by two because the threshold will be applied to both sides of each frame.
%Type int32.
ROISkinSkipFrameThreshold_adjusted = ...
    SkinDetectConfig.ROISkinSkipFrameThreshold_adjusted / int32(2);   

%Number of frames   
%Value reused in loop and used later in video reading process.
%Type int32.
NFrames = VideoReadConfig.NFrames;             

%Preallocate logical index to indicate which frames will be scanned by the skin-detection
%algorithm.
%This vector is also passed to function SkinDetect.
FramesToProcessLogIdx = false(NFrames, 1);

%Loop through FaceDetectionOrSkipped vector to determine which frames meet threshold for having
%skin-detection algorithm applied.
%The various min and max functions are for handling the edge cases.
for i = 1 : NFrames

    %Apply threshold (number of non-zeros will equal zero if enough frames on both sides of given
    %frame do not have detections).
    if nnz( ...
            FaceDetectionOrSkipped( ...
                max( 1, i - min(i, ROISkinSkipFrameThreshold_adjusted) ) : ...
                i + min(NFrames - i, ROISkinSkipFrameThreshold_adjusted) ...
            ) ...
       ) == 0   

        %If meets threshold, mark frame to be scanned
        FramesToProcessLogIdx(i) = true;
    end
end

%Specify frames not to be processed because they were processed in the first video read
if MaxFrameToProcessLinIdx ~= length(FramesToProcessLogIdx)

    FramesToProcessLogIdx(MaxFrameToProcessLinIdx + 1 : end) = false;    
end

%Linear index of frames to scan with skin-detection algorithm
%Transpose to row vector for use in frame-reading loop.
%Specify type int32 for protection against floating-point gaps.
FramesToProcessLinIdx_SR = ...
    int32( ...
        find(FramesToProcessLogIdx)' ...
    );

%If there is at least one frame to be processed
if ~ isempty(FramesToProcessLinIdx_SR)

    %Mark that detections will be attempted by algorithm for these frames
    HasROI_TF.SkinAttempted(FramesToProcessLogIdx) = true; 

    %%%%%% --- Setup progress notifications %%%%%%

    %Assign arguments to the function that displays progress notifications, 
    %LoopProgressNotification.
    
    %Note: "SR" indicates this argument is only used during the second-read (not the first-read) 
    %operations.
    
    %Interval to elapse between each notification message
    %Specify type int32 for protection against floating-point gaps.
    Notifications_Interval_SR = int32(500);    
    
    %Initialize loop counter for progress notifications
    %Specify type int32 for protection against floating-point gaps.
    Notifications_LoopCounter_SR = int32(0);

    %Record start time for progress notifications 
    Notifications_LoopStartTime_SR = tic; 


    %%%%%% Use system object vision.VideoFileReader for video reading %%%%%%

    if VideoReadConfig.UseVisionTF

        %Extract vision.VideoFileReader system object
        videoFReader = VideoReadConfig.videoFReader;

        %Initialize flag indicating whether seeking to StartTime has completed
        SeekCompletedTF = false;

        %Initialize frame index that counts frames from the beginning of the video
        %Only used for seeking to StartTime.
        %Specify type int32 for protection against floating-point gaps.
        FromBeginningIdx = int32(0);

        FrameIdxMax_Specified = FramesToProcessLinIdx_SR(end);

        %Initialize frame index that counts frames from StartTime, which may be later than the
        %beginning of the video.
        %Used for all operations except seeking to StartTime.
        %Specify type int32 for protection against floating-point gaps.
        i = int32(0);

        %Initialize end-of-file flag
        EndOfFileTF = false;

        %Loop through frames up to index of last timestamp 
        %Note: the last timestamp was verified by function ROIMeans_FirstRead_Trim.
        while i < FrameIdxMax_Specified && ...
              ~ EndOfFileTF %verify that frame exists for next frame 

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
                %Type int32.
                FromBeginningIdx = FromBeginningIdx + 1;

                %Go to next frame until the frame index counted from beginning of video 
                %(FromBeginningIdx) equals the frame index corresponding to StartTime 
                %(FrameIdx(1)).
                if FromBeginningIdx ~= VideoReadConfig.FrameIdx(1) 

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

            %%%%%% --- Conduct operations for ith frame if marked for assessment %%%%%%
            if any(FramesToProcessLinIdx_SR == i)

                %Call skin-detection algorithm operations
                %Nested function.
                AlgOps();
            end
        end %end vision.VideoFileReader frame loop 
        
        %Reset vision.VideoFileReader
        release(videoFReader);

        
    %%%%%% Use system object VideoReader for video reading %%%%%%

    else

        %Frame-reading description:

        %Both functions read(VidObj, i) and readFrame(VidObj) use system object VideoReader.
        %When frames are read consecutively, readFrame() is faster than read().
        %When frames need to be read non-consecutively, it may still be faster to use function
        %readFrame() to read consecutively, reading all frames but ignoring the output of frames in 
        %gaps between the non-consecutive frames of interest. Using this method with readFrame,
        %readFrame is faster than function read() until the gap between non-consecutive frames 
        %reaches about 12; this is the case even though readFrame() would have read about 12 times 
        %as many frames. After this point, read() begins to have a performance advantage. To 
        %optimize reading, readFrame() is used when the average gap between frames is lower than a 
        %specified threshold. A lower specified threshold value favors read() and a higher value 
        %favors readFrame(). All frames to be processed are divided into blocks of nearby frames;  
        %at the beginning of each block, the average frame gap is calculated for the block and  
        %compared to the threshold, which determines whether read() or readFrame() will be used for 
        %the block.

        %There is considerable overhead when initializing each reading loop for readFrame().  
        %Specifically, the overhead comes from manually setting the system object's current time  
        %(e.g., VidObj.CurrentTime = time), which typically occurs when initializing the  
        %readFrame() loop. Manually setting the current time is longer than actually reading 
        %several frames. To reduce this overhead, the threshold specified is set lower than 12,  
        %favoring read() more. Additionally, the implementation of dividing frames into blocks is  
        %specially designed to reduce initialization overhead: instead of initializing before each 
        %frame, initializing is conducted once for a block of frames.

        %Extract some video properties from struct for performance
        VidObj = VideoReadConfig.VidObj; %VideoReader system object
        FrameIdx = VideoReadConfig.FrameIdx; %type int32
        
        %Note: the values in FrameTimestamp were assigned during the first read by 
        %VidObj.CurrentTime. VidObj.CurrentTime will also be used in the current function, and its
        %values will sometimes be compared to those in FrameTimestamp. To ensure a match is
        %correctly detected when comparisons are made, the type (i.e., type double) should not be 
        %changed between the time when values were assigned to FrameTimestamp and when they are 
        %used here. Even converting to single and converting back to double will result in  
        %different bit patterns.
        FrameTimestamp = VideoReadConfig.FrameTimestamp_Double;

        %Size of frame blocks
        FrameBlocksSizeSpecified = 20;

        %The threshold to determine whether to use function read() or function readFrame()
        %The threshold is based upon the mean size of gaps between frames in a given block.
        gapLengthsMeanThreshold = 5;

        %Max frame index
        %Type int32
        FramesToProcessLinIdxLast = FramesToProcessLinIdx_SR(end);

        %Initialize flag indicating incorrect frame read 
        ReadIncorrectTF = false;

        %Initialize frame index
        %Specify type int32 for protection against floating-point gaps.
        i = int32(0);

        %Loop across frames until the last frame in FramesToProcessLinIdxLast is processed.
        %Both nonconsectutive and consecutive looping are conducted to optimize advantages of 
        %functions read() and readFrame(), respectively.
        while i < FramesToProcessLinIdxLast    

            %Determine remaining indices to be used for processing
            %Type int32.
            FramesToProcessLinIdx_Remaining = ...
                FramesToProcessLinIdx_SR(FramesToProcessLinIdx_SR > i);

            %Set block size
            %Use whatever is smaller, the specified block size (FrameBlocksSize) or the number of
            %remaining indices.
            FrameBlocksSize = ...
                min( FrameBlocksSizeSpecified, length(FramesToProcessLinIdx_Remaining) );

            %Set the next index to be used for processing
            %Find the value of FramesToUseLinIdx that is nearest to i given that it is larger than 
            %i.  
            %Type int32.
            i = FramesToProcessLinIdx_Remaining(1);

            %Set indices corresponding to block
            %Type int32.
            FramesToProcessLinIdx_Block = ...
                FramesToProcessLinIdx_Remaining( ...
                    FramesToProcessLinIdx_Remaining >= i & ...
                    FramesToProcessLinIdx_Remaining <= ...
                    FramesToProcessLinIdx_Remaining(FrameBlocksSize) ...
                );

            %Determine the sizes of gaps between indices within block
            %Type int32.
            gapLengths = diff(FramesToProcessLinIdx_Block); 

            %Find the mean gap size within block
            %Type double.
            gapLengthsMean = sum(gapLengths) / numel(gapLengths);       

            %If mean gap size above threshold, use function read() for block
            if gapLengthsMean > gapLengthsMeanThreshold

                %Flag to use function read()
                UseReadTF = true;

            %If mean gap size equal to or less that threshold, use function readFrame() for block
            else

                %Flag to use function readFrame()
                UseReadTF = false;        
            end

            %Use function read()
            if UseReadTF 
    
                %Read ith frame
                %Type uint8.
                %Note: the timestamp in system object VidObj is updated to that of the frame read.
                VidFrame = read( VidObj, FrameIdx(i) ); 

                %The correct frame was read by function read(), as verified by timestamp   
                if abs( VidObj.CurrentTime - FrameTimestamp(i) ) ... 
                   < VideoReadConfig.TimestampTolerance 

                    %Call skin-detection algorithm operations
                    %Nested function.
                    AlgOps();             

                %The incorrect frame was read by function read()          
                else

                    %Set flag to enter while loop that contains readFrame(), which does experience 
                    %the issue of reading incorrect frames.
                    %readFrame() will redo the read for this frame.
                    ReadIncorrectTF = true;              
                end           
            end %end use of function read()

            %Use function readFrame()
            if ~ UseReadTF || ReadIncorrectTF

                %First iteration flag
                FirstIterationTF = true;

                %Break while loop flag
                BreakWhileTF = false;

                %Loop across frames 
                while ~ BreakWhileTF

                    %If first iteration
                    if FirstIterationTF

                        %Set the CurrentTime property of system object VideoRead a value just 
                        %before (earlier) than the timestamp corresponding to the frame to be read.   
                        %This is because readFrame reads the frame corresponding to the next, not
                        %the current, timestamp. Note that the timestamp used to set CurrentTime 
                        %does not need to correspond to an actual timestamp; it can be any 
                        %non-negative value. Set back by a magnitude of at least 10e-5; otherwise,
                        %the precision will be below that which VideoReader can recognize.
                        %Note: VidObj.CurrentTime requires type double.                  
                                                
                        %Set VidObj.CurrentTime to slightly earlier time if doing so does not 
                        %result in a negative number                   
                        if FrameTimestamp(i) > 10e-5
                        
                            TimestampBackOne = max( FrameTimestamp(i) - 10e-5, 0 );
                           
                        %Set VidObj.CurrentTime to 0   
                        else
                         
                            TimestampBackOne = 0;
                        end 
                                          
                        %Set the system object to the specified timestamp              
                        %Setting the time of the system object is resourse intensive, so only set 
                        %the time if not already at the specified timestamp.
                        if ~ ( ...
                                abs(VidObj.CurrentTime - TimestampBackOne) ... 
                                < VideoReadConfig.TimestampTolerance ...
                             )

                            %Note: VidObj.CurrentTime must be set with type double
                            VidObj.CurrentTime = double(TimestampBackOne);   
                        end

                        FirstIterationTF = false; 
                    end

                    %Read ith frame
                    %Type uint8.
                    %Note: the timestamp in system object VidObj is updated to that of the frame 
                    %read.
                    VidFrame = readFrame(VidObj);             
                 
                    %Verify that timestamp matches recorded timestamp in FrameTimestamp 
                    %Note: the timestamps in FrameTimestamp were assigned by function 
                    %ROIMeans_FirstRead.
                    %Note: use a tolerance for testing equality because type floating point and 
                    %because the timestamp returned by system object VideoReader for a given frame  
                    %can vary between reads (e.g., the timestamp for frame i returned by  
                    %VideoReader during a different function may be slightly different than the 
                    %timestamp returned by VideoReader during the current read). However, this
                    %difference in timestamps has not been observed to result in different frames
                    %being read and, therefore, is not considered problematic. By using a
                    %tolerance, timestamps that differ slightly but correspond to the same frame
                    %will be considered equivalent. The purpose of the current test is to
                    %determine whether the timestamps are not equivalent according to the 
                    %tolerance. In this case, the problem most likely lies with the implementation
                    %of the current function rather than with the VideoReader.
                    if ~ ( ...
                             abs( VidObj.CurrentTime - FrameTimestamp(i) ) ...
                             < VideoReadConfig.TimestampTolerance ...
                       )
  
                        %Display warning
                        warning( ...
                            'Component:InternalError', ...
                            ['Internal Error: Internal timestamp inconsistency during skin', ...
                             ' ROI detection. Timestamp discrepancy greater than tolerance.', ...
                             ' Discrepancy between timestamps: ', ...
                              num2str(VidObj.CurrentTime - FrameTimestamp(i)), ' sec.', ...
                             ' Aborting skin ROI detection.'] ...
                        );

                        %Exit function
                        %Note: If timestamps not aligned, ROIs could be assigned to non-matching 
                        %frames. This warning might occur when the correct frame is read but the 
                        %tolerance is not sufficiently large to account for variance in timestamps 
                        %returned by VideoReader across reads. The tolerance is set in function 
                        %VideoReadConfig_Setup.
                        return
                    end           

                    %Only process frames corresponding to indices in FramesToUseLinIdx
                    if any(FramesToProcessLinIdx_SR == i) 

                        %Call skin-detection algorithm operations
                        %Nested function.
                        AlgOps();            
                    end                           

                    %Only advance index if one or more iterations to be conducted in current while 
                    %loop. Otherwise, the index will be advanced at the top of the highest-level 
                    %while loop.
                    if i ~= FramesToProcessLinIdx_Block(end)  

                        %Set index of next frame to be read
                        i = i + 1;

                    %Exit current while loop and head to highest-level while loop
                    else

                        %Set flag to break current while loop
                        BreakWhileTF = true;
                    end           
                end       
            end %end loop with function readFrame()  
        end %end high-level VideoReader frame-reading loop
    end %end frame reading for vision.VideoFileReader or VideoReader
end 

    
%=============================================================================================
%Nested functions 
%============================================================================================= 


%=============================================================================================
function AlgOps()
%AlgOps    Conduct skin-detection algorithm operations.
 

%%%%%% Set bounding box %%%%%%

%If a certain number of frames occur where no skin-detection algorithm detection is made (despite 
%being attempted), enlarge bounding box. The most likely case for no skin detection being made is  
%that the area of the frame corresponding to the bounding box was completely segmented; this may  
%indicate that the bounding box is not sufficiently large to capture a portion of the face at that 
%time.

%If a certain number of assessed frames have no detections, within a specified number of frames 
%back, enlarge bounding box.
%Note: SkinDetect_SetBoundingBoxScale is a custom function located within folder 'FacePulseRate'. 
[ROISkin_BoundingBoxEnlargementFactor, IncreaseSkinBBoxFactorStartIdx] = ...
    SkinDetect_SetBoundingBoxScale(i, HasROI_TF, SkinDetectConfig, ...
        IncreaseSkinBBoxFactorStartIdx);    

%Assign bounding box:

%Use compiled function       
if ROIGeneralConfig.UseCompiledFunctionsTF
    
    %Note: ROIResize is a custom compiled function located within folder 'FacePulseRate'. For 
    %source code, see file ROIResize.m.
    BoundingBoxSkin = ...
        ROIResize_mex( ...
            ROI(i, :),                            ... ROI to be adjusted; type int16
            int32(1),                             ... ROI index (1 entered if only 1 ROI); type 
                                                  ... int32.  
            ROISkin_BoundingBoxEnlargementFactor, ... Width resizing scale factor; type double 
            ROISkin_BoundingBoxEnlargementFactor, ... Height resizing scale factor; type double 
            VideoReadConfig.VidObjWidth,          ... To keep adjustment within frame dimensions; 
                                                  ... type int16. 
            VideoReadConfig.VidObjHeight          ...           
        );

%Do not use compiled function
else
    
    %Note: ROIResize is a custom function located within folder 'FacePulseRate'. 
    BoundingBoxSkin = ...
        ROIResize( ...
            ROI(i, :), ... 
            int32(1), ... 
            ROISkin_BoundingBoxEnlargementFactor, ... 
            ROISkin_BoundingBoxEnlargementFactor, ... 
            VideoReadConfig.VidObjWidth, ... 
            VideoReadConfig.VidObjHeight ...           
        );    
end   


%%%%%% Call skin-detection algorithm %%%%%%

%ith ROI
ROI_SR_ith = ROI(i, :);

%Argument not used during second-read operations
%Note: although it might be desiable to use varargin for this argument, varargin is not used to
%maintain code-generation compatibility in function SkinDetect.        
ROIForBoundingBoxSkin_FR = zeros(1, 4, 'int16');
   
%Compiled functions enabled
if SkinDetectConfig.UseCompiledFunctionsTF 

    %Note: SkinDetect_mex is a custom compiled function located within folder 'FacePulseRate'. For
    %source code, see file SkinDetect.m.
    [ROI_Selected_ith, SkinTF_ith, SkinNotPresent_Skin_ith, ROIDiagnostic_ROISkin_ith,  ~] = ...
        SkinDetect_mex(i, VidFrame, VideoReadConfig.VidObjWidth, VideoReadConfig.VidObjHeight, ...
            SkinSegmentConfig, ROIGeneralConfig, SkinDetectConfig, ...
            OutputConfig.WriteVideoShowROISkinDiagnosisTF, BoundingBoxSkin, FirstReadTF, ...
            ROIForBoundingBoxSkin_FR, ROI_SR_ith, FramesToProcessLinIdx_SR, ...
            Notifications_Interval_SR, Notifications_LoopStartTime_SR, ...
            Notifications_LoopCounter_SR);

%Compiled functions not enabled
else

    %Note: SkinDetect is a custom function located within folder 'FacePulseRate'.
    [ROI_Selected_ith, SkinTF_ith, SkinNotPresent_Skin_ith, ROIDiagnostic_ROISkin_ith,  ~] = ...
        SkinDetect(i, VidFrame, VideoReadConfig.VidObjWidth, VideoReadConfig.VidObjHeight, ...
            SkinSegmentConfig, ROIGeneralConfig, SkinDetectConfig, ...
            OutputConfig.WriteVideoShowROISkinDiagnosisTF, BoundingBoxSkin, FirstReadTF, ...
            ROIForBoundingBoxSkin_FR, ROI_SR_ith, FramesToProcessLinIdx_SR, ...
            Notifications_Interval_SR, Notifications_LoopStartTime_SR, ...
            Notifications_LoopCounter_SR);
end
                   
%The detection can be unsuccessful for the following reasons:
% - The bounding box did not contain a skin region.
% - The portion of the frame submitted to the skin-detection algorithm was completely segmented by 
%   the skin-segmentation algorithm.
% - All regions within the portion of the frame submitted to the skin-detection algorithm were
%   rejected.
% - Rejected by function ConfirmSkinPresent.

%Indicate whether the detection was not successful because the ROI did not pass the threshold 
%applied by function ConfirmSkinPresent.
%Note: If true, then SkinTF_ith will be false. However, SkinTF_ith can be false without 
%HasROITF_SkinNotPresent_ith being true.
HasROI_TF.SkinNotPresent_Skin(i) = SkinNotPresent_Skin_ith; 

%If skin-detection algorithm detection successfully made detection  
if SkinTF_ith
    
    %Assign detected ROI
    ROI(i, :) = ROI_Selected_ith;
    
    %Consider the skin-detection algorithm successful for the ith frame
    HasROI_TF.Skin(i) = true;        
    
    %Overwrite the interpolation status in case the ROI had been interpolated previously 
    HasROI_TF.Interpolated(i) = false; 
    
    %Record the detected ROI before ROI modifications to be conducted by function ROIMSIR
    ROIDiagnostic.ROI_NonSmoothed(i, :) = ROI_Selected_ith;
end    

%Assign ROI diagnostics from skin-detection algorithm:

%Note: struct ROIDiagnostic was preallocated by function SkinDetect_PreallocateDiagnosticData.

ROIDiagnostic.BBox_Scan.SkinAlg(i, :)                        = ROIDiagnostic_ROISkin_ith.BBox_Scan_SkinAlg;
ROIDiagnostic.ROISkin.RegionAnyAvailable(i)                  = ROIDiagnostic_ROISkin_ith.RegionAnyAvailable;

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

end %end nested function
  
    
end %end main function

