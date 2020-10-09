function [videoFReader, FrameIdxFromStart, FrameIdx, EndTimeSpecified, StartTime, EndTime, ...
          TimestampTolerance, FrameTimestampUntrimmed, NFrames] = ...
             VideoReadConfig_Setup_Vision(Video_InputFile, VidObj, StartTime, EndTime, ...
                 VidObjNumFrames)
%VideoReadConfig_Setup_Vision   Specify settings for video reading for use with video reader 
%                               vision.VideoFileReader.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function VideoReadConfig_Setup.
%
%
%    Description
%    -----------
%
%    Specify settings for video reading for use with video reader vision.VideoFileReader. For 
%    settings for use with video reader VideoReader, see function 
%    VideoReadConfig_Setup_VideoReader. The settings include the start and end times, querying 
%    timestamps, determining the frame rate, and assigning frame indices.
% 
%    Two versions of frame indices are established. One counts the number of frames since the
%    beginning of the video (when the timestamp equals about 0) and the other counts the number of
%    frames since StartTime.
%
%    -- Note on variables trimmed after first-read operations -- 
%
%    The trimming operations depend upon which video reader is used. This description corresponds 
%    to video reader vision.VideoFileReader.
%
%    Several variables will be trimmed after the first read operations (in function  
%    ROIMeans_FirstRead_Trim) because the video will have then been read through to EndTime, which 
%    is the only way to accurately determine the frame index. The variables to be trimmed are 
%    NFrames, FrameIdxFromStart, and FrameIdx. Also, the vector of timestamps used during the first 
%    (FrameTimestampUntrimmed) read may be longer than EndTime. When the first read completes, it  
%    can be determined whether EndTime exceeds the length of the video, in which case EndTime will 
%    be reduced. FrameTimestampUntrimmed will then be trimmed to EndTime and renamed 
%    FrameTimestamp; FrameTimestampUntrimmed will no longer be used. This operation also takes 
%    place in function ROIMeans_FirstRead_Trim.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Retrieve timestamps from input video %%%%%%

%Full path for ffprobe.exe, which is used to retrive the timestamps for the input video
%Local function.
ffprobePath = getffprobePath();

%Display notification message
message = '\nRetrieving timestamps from input video ...\n';

%Display message
fprintf(message);

%Display message immediately
drawnow(); 

%Timestamps for the entire video
%Note: getFrameTimestamps is a custom function located within folder 'FacePulseRate'.
%The function definition for getFrameTimestamps is located at the bottom of this script.
FrameTimestampFull = getFrameTimestamps(ffprobePath, Video_InputFile, EndTime);


%%%%%% Adjust max timestamp for compatibility with Matlab video readers %%%%%%

%As noted in the Matlab documentation, the property VidObj.Duration will sometimes have an
%inaccurate video endtime. In some cases, the video length could actually be longer, resulting
%in timestamps that exceed VidObj.Duration. If VidObj.CurrentTime is set with a time that
%exceeds VidObj.Duration, even if it actually exists, an error will be thrown. 

FrameTimestampFull = FrameTimestampFull(FrameTimestampFull < VidObj.Duration);  


%%%%%% Adjust timestamps to sync with Matlab video readers %%%%%%

%Sometimes, the first video timestamp from the Matlab video readers is one behind the first
%video timestamp from ffmpeg. 

%Read the first frame of the video with a Matlab video reader to aquire the first timestamp.
read(VidObj, 1);

%Remove timestamp(s) lower than the first timestamp from the Matlab video reader
FrameTimestampFull = FrameTimestampFull(FrameTimestampFull > VidObj.CurrentTime);


%%%%%% Remove timestamps once timestamps are not in chronological order %%%%%%

%Description:

%Timestamps in non-chronological should be removed because they can interfere with operations
%that depend upon their being in chronological order. These typically occur near the end of the 
%video. 

%The method used to extract timestamps, implemented in function videoframets_FacePulseRate,
%although fast, is not able to determine which timestamps are not in chronological order 
%because many timestamps are returned in non-chronological order as a result of the reading 
%method. As many timestamps are not in chronological order as a result of the reading method, 
%they have to be sorted, which obscures the original order of the timestamps, which could  
%indicate which timestamps were originally not in chronlogical order. To handle timestamps 
%that may potentially not be in chronological order, remove the last 3 timestamps as the  
%non-chronological issue typically only occurs at the end of the video.

%Remove last three timestamps.
FrameTimestampFull = FrameTimestampFull(1 : length(FrameTimestampFull) - 3);


%%%%%% Adjust max frame index for compatibility with Matlab video readers %%%%%%

%System object VideoReader (named VidObj here) will throw an error if the frame index used as
%an argument to read() is greater than the maximum frame index known to it, which is indicated 
%by VidObj.NumFrames. Prevent this error from being thrown by capping the frame index at the
%maximum frame index known to VideoReader.

if length(FrameTimestampFull) > VidObjNumFrames

    FrameTimestampFull = FrameTimestampFull(1 : VidObjNumFrames);
end


%%%%%% Remove timestamps that do not fall between StartTime and EndTime %%%%%%

%Logical index of timestamps between StartTime and EndTime
FramesToRetainLogIdx = FrameTimestampFull > StartTime & FrameTimestampFull < EndTime;

%Remove timestamps not between StartTime and EndTime
FrameTimestampUntrimmed = FrameTimestampFull(FramesToRetainLogIdx);


%%%%%% Frame index counted by starting at StartTime %%%%%%

%Assign frame index FrameIdxFromStart, where 1 corresponds to StartTime. 
%This index is used for most indexing purposes throughout function FacePulseRate.
%Note that a different frame index, FrameIdx, is used in situations where the absolute frame 
%index, i.e, where 1 corresponds to time = 0, is needed. If StartTime does not equal 0,  
%FrameIdxFromStart will differ from FrameIdx.

%Length of frames to be processed
%Specify type int32 for protection against floating-point gaps. 
%Note: updated after the first read operations; see note at top of vision.VideoFileReader 
%section.
NFrames = int32( length(FrameTimestampUntrimmed) );

%Frame index starting from StartTime
%Specify type int32 for protection against floating-point gaps.
%Note: updated after the first read operations; see note at top of vision.VideoFileReader 
%section.
FrameIdxFromStart = int32(1) : NFrames;


%%%%%% Frame index counted by starting from beginning of video

%Assign frame index FrameIdx, where 1 corresponds to time = 0. 
%This index is used for limited purposes throughout function FacePulseRate. It is the frame 
%index displayed on the output video and on warning messages. It is also used when indexing  
%into the input video when function read() is used (this function is not used when the video  
%reader is vision.VideoFileReader).
%Note that a different frame index, FrameIdxFromStart, where 1 corresponds to StartTime, is  
%used more often. If StartTime does not equal 0, FrameIdxFromStart will differ from FrameIdx. 

%Number of frames from the beginning of the video until StartTime, which will be skipped 
FirstFrameToProcessIdx = find(FramesToRetainLogIdx, 1, 'first') - 1;

%Frame index starting from beginning
%Shift the index by the number of frames to be skipped.
%Specify type int32 for protection against floating-point gaps.
%Note: updated after the first read operations; see note at top of vision.VideoFileReader 
%section.    
FrameIdx = ...
    int32( ...
        (1 : NFrames) + FirstFrameToProcessIdx ...
    );

   
%%%%%% Modify StartTime and EndTime based upon timestamps recorded %%%%%%

EndTimeSpecified = EndTime;    
StartTime = FrameTimestampUntrimmed(1);

%Note: updated after the first read operations in case the specified end time EndTimeSpecified
%exceeds the length of the video.
EndTime = FrameTimestampUntrimmed(end);


%%%%%% Set timestamp tolerance %%%%%% 

%Set tolerance for comparing timestamps. This tolerance is used by function
%ROIMeans_SecondRead_SkinDetect when reading non-consecutive frames with video reader 
%VideoReader to check that the frames read match the timestamps expected. This check is made to
%guard against implementation errors that are more likely when reading non-consecutive frames 
%and because function read(), which is a method of VideoReader, sometimes reads frames that do
%not correspond to the timestamp expected.

%In addition to using tolerance to facilitate equality between floating-point numbers,
%the tolerance is also set to allow timestamps in close proximity, but not the same, to be
%considered equal. Close proximity is used because VidObj.CurrentTime does not always return 
%the same timestamp for a given frame; a tolerance permits the timestamps in FrameTimestamp to 
%match slighly varying VidObj.CurrentTime timestamps. To set tolerance, use the minimum 
%difference found between timestamps. There may bit of overlap between frames, but this
%tolerance has been found necessary to avoid false negatives.

%Note: the minimum gap between timestamps should not be used because this could potentially
%equal zero. The maximum gap is not used in case it is excessively large.
%Specify type double for adequate precision.

TimestampTolerance = ...
    double( ...
        median( diff(FrameTimestampUntrimmed) ) ...
    );


%%%%%% Initialize vision.VideoFileReader system object for reading video %%%%%%     

%Note: the code for vision.VideoFileReader is taken from OpenCV.

videoFReader = ...
    vision.VideoFileReader( ...
        Video_InputFile,               ... specify media file to read
        'VideoOutputDataType', 'uint8' ... output type
   );    

end %end main function


%=============================================================================================
%Local functions 
%=============================================================================================


%=============================================================================================
function ffprobePath = getffprobePath()
%getffprobePath.  Return full path for the ffprobe executable file.


%For Windows
if ispc()

    %Return all directories within Matlab search path
    %These will be separated with a semicolon.
    SearchPaths = matlabpath();

    %Convert to string array
    SearchPathStrings = strsplit( string(SearchPaths), ';' );

    %Find directory with executable
    SearchPath_FacePulseRate = ...
        SearchPathStrings( ...
            contains(SearchPathStrings, "FacePulseRate\Funs\General\ffmpeg\win64\bin") ...
        );

    %Concatenate directory with file name
    ffprobePath = [char(SearchPath_FacePulseRate), '\ffprobe.exe'];

%For MacOS
elseif ismac()

    %Return all directories within Matlab search path
    %These will be separated with a semicolon.
    SearchPaths = matlabpath();

    %Convert to string array
    SearchPathStrings = ...
        strsplit( ...
            string(SearchPaths), ...
            ';' ... delimiter
        );

    %Return logical index indicating directory with executable
    SearchPath_FacePulseRate = ...
        SearchPathStrings( ...
            contains(SearchPathStrings, "FacePulseRate/Funs/General/ffmpeg/mac/bin") ...
        );

    %Concatenate directory with file name
    ffprobePath = [char(SearchPath_FacePulseRate), '/ffprobe'];                
end   


end %end local function

