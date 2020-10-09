function SkipIthFrameTF = ...
             ROIMeans_FirstRead_DetermineSkipFrame(i, HasROI_TF, ROIGeneralConfig, ...
                 FaceDetectConfig)                
%ROIMeans_FirstRead_DetermineSkipFrame   Determine whether the face-detection algorithm(s) and the
%                                        skin-detection algorithm should not be conducted for a  
%                                        given frame to increase computational efficiency.
%                                       
%   Helper function to function FacePulseRate. 
%   Within function FacePulseRate, called by function ROIMeans_FirstRead.
%
%
%   Description
%   -----------
%
%   For some frames, the face-detection and skin-detection algorithms are skipped to increase
%   computational efficiency as the algorithms are resource intensive. For these frames, although 
%   the algorithms are skipped, the frames are still read and other operations, such as the ROI
%   means operations and the recording of timestamps, are conducted. For skipped frames, ROIs will 
%   be interpolated from nearby frames (see function ROIMSIR).
%
%   To balance computational efficiency with accuracy, frames are not skipped if, within a 
%   specified number of frames back, detection attempts have not been successful.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.
   

%%%%%% Check against frame-skipping threshold %%%%%%

%ROIFaceSkipFrameThreshold, an argument to function FacePulseRate, specifies the number of frames
%that should elapse between the application of detection algorithms. This threshold was modified 
%during the setup of function FacePulseRate (in function ROIGeneralConfig_Setup) to make the number
%of frames that should elapse vary depending on the frame rate, such that more frames should elapse 
%when the frame rate is higher. 

%If no face-detection algorithms were successful on the last frame on which they were applied, the
%face-detection and skin-detection algorithms will not be skipped for the current frame. This is
%implemented to reduce gaps between face-detection algorithms. If the skin-detection algorithm was  
%successful but the face-detection algorithms were not successful, the detection algorithms will
%not be skipped in order to maintain the frequency of face-detection algorithm detections as these
%detections are considered more accurate than skin-detection algorithm detections.

%Check whether there is a detection by any face-detection algorithm within the specified number of
%frames back.
%Note: max() functions inserted to avoid 0 and negative integers.
ROISkipFrameThreshold_adjusted = ROIGeneralConfig.ROISkipFrameThreshold_adjusted;

SkipIthFrameTF = ...
    any( ... any primary algorithm detection
        HasROI_TF.FacePrimary( ...
            max(1, i - ROISkipFrameThreshold_adjusted) : ... specified number of previous frames
            max(1, i - 1)                                ... immediately previous frame
        ) ...
    ) || ... 
    any( ... any secondary #1 algorithm detection
        HasROI_TF.FaceSecondary1( ...
            max(1, i - ROISkipFrameThreshold_adjusted) : ... specified number of previous frames
            max(1, i - 1)                                ... immediately previous frame
        ) ...
    ) || ...
    any( ... any secondary #2 algorithm detection
        HasROI_TF.FaceSecondary2( ...
            max(1, i - ROISkipFrameThreshold_adjusted) : ... specified number of previous frames
            max(1, i - 1)                                ... immediately previous frame
        ) ...
    );


%%%%%% Don't skip if local ratio of detections to attempts is low %%%%%%

%Don't skip if there has recently been a number of instances where face-detection algorithm 
%detections were not successful. Although the previous step did not permit skipping if the last
%face-detection attemp was unsuccessful, it did not consider the number of unsuccessful attempts 
%across a wider range of frames. If the ratio of detections to attemps across a range of frames is 
%below a specified thresold, don't skip. This is implemented to increase the likelihood of 
%obtaining a face detection in spans where it is more difficult to obtain face detections, with the
%objective of maintaining the frequency of face-detection algorithm detections. As in the previous
%step, only face-detection algorithm detections, rather than skin-detection algorithm detections,
%are considered because face-detection algorithm detections are considered more accurate.

if SkipIthFrameTF

    %Specify number of frames back to check
    FramesBack = 25;

    if i > FramesBack

        %Ratio of detections to attempts across specified number of frames back

        LinIdx = i - FramesBack : i - 1;

        DetectsToAttemptsRatio = ...
            nnz(                                    ... number of detections
                 HasROI_TF.FacePrimary(   LinIdx) | ...
                 HasROI_TF.FaceSecondary1(LinIdx) | ...
                 HasROI_TF.FaceSecondary2(LinIdx)   ...
            ) / ... 
            nnz( ~ HasROI_TF.Skipped(LinIdx) ); %   number of attempts

        %Don't skip if below threshold
        if DetectsToAttemptsRatio < FaceDetectConfig.DetectsToAttemptsRatioThreshold

            SkipIthFrameTF = false;
        end
    end 
end


%%%%%% Skip ith frame if specified by argument ROIIgnoreByArgument %%%%%%

%ROIIgnoreByArgument, which is an argument to function FacePulseRate, specifies frame indices 
%where the face-detection and skin-detection algorithms should not be used. Not using these
%algorithms is implemented by skipping the corresponding frames.

if HasROI_TF.ROIIgnoreByArgument(i)
    
    SkipIthFrameTF = true;
end


%%%%%% Skip operations if ith ROI specified by argument ROISpecifiedByArgument %%%%%%

%ROISpecifiedByArgument, which is an argument to function FacePulseRate, specifies ROI(s) for   
%specified frames indices. As these specified ROIs should not be overwritten by the face-detection 
%algorithm or skin-detection algorithm, the corresponding frames are skipped.

%If ROI specified for ith frame
if HasROI_TF.ROISpecifiedByArgument(i)
    
    SkipIthFrameTF = true;
end


end %end function

