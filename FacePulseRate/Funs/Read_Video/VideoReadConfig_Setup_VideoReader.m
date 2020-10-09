function [videoFReader, FrameIdxFromStart, FrameIdx, StartTime, EndTime, TimestampTolerance, ...
          FrameTimestampUntrimmed, NFrames] = ...          
             VideoReadConfig_Setup_VideoReader(VidObj, StartTime, EndTime, VidObjNumFrames, FS)
%VideoReadConfig_Setup_VideoReader   Specify settings for video reading for use with video reader 
%                                    VideoReader.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function VideoReadConfig_Setup.
%
%
%    Description
%    -----------
%
%    Specify settings for video reading for use with video reader VideoReader. For 
%    settings for use with video reader vision.VideoFileReader, see function 
%    VideoReadConfig_Setup_Vision. The settings include the start and end times, querying 
%    timestamps, determining the frame rate, and assigning frame indices.
%    
%    Two versions of frame indices are established. One counts the number of frames since the
%    beginning of the video (when the timestamp equals about 0) and the other counts the number of
%    frames since StartTime.
%
%    -- Note on variables trimmed after first-read operations -- 
%
%    The trimming operations depend upon which video reader is used. This description corresponds 
%    to video reader VideoReader.
%
%    Several variables will be trimmed after the first read operations (in function 
%    ROIMeans_FirstRead_Trim) because the video will have been read through to EndTime, which is
%    the only way to accurately determine the frame index. The variables to be trimmed are NFrames,
%    FrameIdxFromStart, and FrameIdx.
%
%    -- Note on generality of timestamps used by VideoReader --
%
%    When VideoReader is used for seeking, it should use its own timestamps (rather than those 
%    obtained from external function, such as ffprobe) for seeking because it has been observed 
%    that VideoReader uses some timestamps that do not correspond to those provided from external
%    sources.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Preallocate vector to hold frame timestamps %%%%%%

%The variable has the suffix "untrimmed" because the length will need to be trimmed to the 
%final length before used as input to some functions. Trimming is conducted once the portion of 
%the video to be processed is read. The video is first read in function ROIMeans_FirstRead, and 
%the trimming occurs there. 
%Type double required for some operations. At the end of the file, separate variables will be
%assigned with separate precision.
FrameTimestampUntrimmed = nan(VidObjNumFrames, 1, 'double');


%%%%%% Frame index counted by starting at StartTime %%%%%%

%Assign frame index FrameIdxFromStart, where 1 corresponds to StartTime. 
%This index is used for most indexing purposes throughout function FacePulseRate.
%Note that a different frame index, FrameIdx, is used in situations where the absolute frame 
%index, i.e, where 1 corresponds to time = 0, is needed. If StartTime does not equal 0,  
%FrameIdxFromStart will differ from FrameIdx.  

%Length of frames to be processed
%Specify type int32 for protection against floating-point gaps.
%Note: updated after the first read operations; see note at top of VideoReader section.
NFrames = int32( length(FrameTimestampUntrimmed) );

%Frame index starting from StartTime
%Specify type int32 for protection against floating-point gaps.
%Note: updated after the first read operations; see note at top of VideoReader section.
FrameIdxFromStart = int32(1) : NFrames;


%%%%%% Frame index counted by starting from beginning of video %%%%%%

%Assign frame index FrameIdx, where 1 corresponds to time = 0. 
%This index is used for limited purposes throughout function FacePulseRate. It is the frame 
%index displayed on the output video and on warning messages. It is also used when indexing  
%into the input video when function read() is used (this function is not used when the video  
%reader is vision.VideoFileReader).
%Note that a different frame index, FrameIdxFromStart, where 1 corresponds to StartTime, is  
%used more often. If StartTime does not equal 0, FrameIdxFromStart will differ from FrameIdx.

%Assume that the user intends the first frame to be processed to be where the timestamp is 
%greater than or equal to StartTime rather than anytime before StartTime. 

%Read through frames to find the frame index that corresponds to the timestamp greater than or
%equal to StartTime.
%Because frames could have been dropped during recording and because the video may use a 
%variable frame rate, the timestamp cannot be assumed to be an increment of (1 / frame rate). 
%Hence, start reading a generous time before StartTime.

%Index at which to begin search for index corresponding to greater than or equal to StartTime
iBegin = max( round(StartTime * FS - FS * 3), 1 );

i = iBegin;

%Reset time of VideoReader
VidObj.CurrentTime = 0;

breakWhileTF = false;

%Search through frames until the index is found
while ~ breakWhileTF

    %Read ith frame
    read(VidObj, i);

    %If timestamp (VidObj.CurrentTime) where search begins is greater than StartTime, no   
    %timestamp will be identified. Set index to 1.
    if i == iBegin && VidObj.CurrentTime > StartTime

        i = 1;

        break
    end  

    %End search once timestamp is greater than or equal to StartTime
    if VidObj.CurrentTime < StartTime

        i = i + 1;  
    else

       breakWhileTF = true;
    end
end

%Assign frame index counting from beginning of video
%Specify type int32 for protection against floating-point gaps.
%Note: updated after the first read operations; see note at top of VideoReader section.
FrameIdx = ...
    int32( ...
        (1 : NFrames) + (i - 1) ...
    );


%%%%%% Set timestamp tolerance %%%%%% 

%Set tolerance for comparing timestamps. This tolerance is used by function
%ROIMeans_SecondRead_SkinDetect when reading non-consecutive frames with video reader 
%VideoReader to check that the frames read match the timestamps expected. This check is made to
%guard against implementation errors that are more likely when reading non-consecutive frames 
%and because function read(), which is a method of VideoReader, sometimes reads frames that do
%not correspond to the timestamp expected.


%In addition to using tolerance to facilitate equality between floating-point numbers, the
%tolerance is also set to allow timestamps in close proximity, but not the same, to be
%considered equal. Close proximity is used because VidObj.CurrentTime does not always return 
%the same timestamp for a given frame; a tolerance permits the timestamps in FrameTimestamp to 
%match slighly varying VidObj.CurrentTime timestamps. To set tolerance, use the minimum
%difference found between timestamps. There may bit of overlap between frames, but this
%tolerance has been found necessary to avoid false negatives.

SampleTimestamps = zeros(5, 1);

for i = 1 : 5

    read(VidObj, i);   

    SampleTimestamps(i) = VidObj.CurrentTime;
end

%Use the median gap between timestamps.
%Note: the minimum gap between timestamps should not be used because this could potentially
%equal zero. The maximum gap is not used in case it is excessively large.
%Specify type double for adequate precision.
TimestampTolerance = ...
    double( ...
        median( diff(SampleTimestamps) ) ...
    ); 


%%%%%% Assign empty value for vision.VideoFileReader system object %%%%%%

videoFReader = [];    


end %end function

