function VideoReadConfig = ...
             VideoReadConfig_Setup(Video_InputFile, StartTime, EndTimeSpecified, EndTime)                 
%VideoReadConfig_Setup   Specify settings for video reading operations.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function ValidateAndConfigure.
%
%
%    Description
%    -----------
%
%    Specify settings for video reading. These include determining the video reader to use, setting
%    the start and end times, preallocating or querying timestamps, determining the frame rate, and
%    assigning frame indices. 
%
%    Two video readers are implemented for use in FacePulseRate; one of the two will be selected 
%    for use for all operations based upon certain parameters such as input video compatibility and 
%    start time. The selection of video reader determines whether timestamps are querried in the
%    current function or querried as frames are read by function ROIMeans_FirstRead. Regardless of
%    when timestamps are querried, a timestamp tolerance will be established by the current 
%    function. The tolerance is used when checking the equality of timestamps. A tolerance is used
%    because timestamps are of a floating-point type and because the timestamps returned by video
%    reader VideoReader sometimes vary within an acceptable tolerance.
%    
%    Two versions of frame indices are established. One counts the number of frames since the
%    beginning of the video (when the timestamp equals about 0) and the other counts the number of
%    frames since StartTime.
%
%    Note that various validation checks on the input video were previously conducted by function
%    ValidateAndConfigure_Validate.
%
%    -- Timestamps are video-reader-specific --
%
%    VideoReader is needed when seeking based on timestamps. In such a case, the timestamps used  
%    for seeking must also be collected by VideoReader to ensure the it is working from timestamps 
%    that match its timestamps. Timestamps collected from other sources, such as ffprobe, may not 
%    match the timestamps calculated by VideoReader; if timestamps from other readers are used to  
%    set the start time for VideoReader, the frame at which reading begins may differ from that 
%    intended.
%
%    -- Uses of timestamps --
%
%    - Processing video between StartTime and EndTime.
%    - Adjusting EndTime if EndTime exceeds the duration of the video.
%    - Interpolating and extrapolating ROIs (see functions ROIMeans_FirstRead_ExtrapolateROI, 
%      ROIMSIR, and ROIFrameByFrameSmooth).
%    - Pulse rate algorithms in function PulseRate. 
%    - A column in the output csv file by function TableOutput.
%    - Display on the output video by function WriteFaceVideo.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Specify general settings %%%%%%

%Assign system object for reading video frames
VidObj = VideoReader(Video_InputFile);

%Set frame rate
%Extract input video framerate, round to integer and assign
FS = round(VidObj.FrameRate);  

%Maximum frame index accepted by VideoReader
VidObjNumFrames = VidObj.NumFrames;

%Specify index that should not be exceeded when indexing 
%It has been observed that function readFrame is able to read to a frame further than the maximum
%frame permitted by function read(), even though they share the same system object (VideoReader).
%The end of the frame index is finalized when variables are trimmed (see function 
%ROIMeans_FirstRead_Trim) in function ROIMeans_FirstRead, where the first read takes place.
%Because function ROIMeans_FirstRead uses readFrame for reading, it could read past the maximum
%index permitted by function read(). If it were to finalize the frame index as ending at an index 
%beyond the maximum, this index could potentially be used for indexing by function read() during  
%function ROIMeans_SecondRead_SkinDetect, causing an error to be thrown. To prevent such an error, 
%do not permit function readFrame to read past the maximum index that can be used by function 
%read().
FrameIdxDoNotExceed = int32(VidObjNumFrames);

%Set video frame dimensions
%Specify type int16 for faster evaluation where used.
VidObjWidth  = int16(VidObj.Width);
VidObjHeight = int16(VidObj.Height);

%Initalize the maximum frame index at which frames will be read
%This value is set once function ROIMeans_FirstRead reaches EndTime. The frame index that 
%corresponds to EndTime can only be known with accuracy once EndTime is reached.
MaxFrameIdx = int32(inf);


%%%%%% Specify whether VideoReader or vision.VideoFileReader should be used %%%%%%

%Determine whether to use the vision.VideoFileReader or VideoReader video reader.

%vision.VideoFileReader tends to complete reading faster than VideoReader, so it is perferred.

%Check whether the input video format is supported by vision.VideoFileReader
%Based on documentation for vision.VideoFileReader. If not supported, use VideoReader. Whether the
%input video is supported by VideoReader was checked previously by function 
%ValidateAndConfigure_Validate, as VideoReader supports more video formats than 
%vision.VideoFileReader.

ext = Video_InputFile(end - 2 : end); %file extension

%If vision.VideoFileReader supports format
if ( ispc() && any(strcmp(ext, {'mp4', 'avi'})) ) ||      ... PC platform
   ( ismac() && any(strcmp(ext, {'mp4', 'avi', 'mov'})) ) %   MacOS platform
    
    UseVisionTF = true;
    
else
    
    UseVisionTF = false;
end
    
%If vision.VideoFileReader supports format
if UseVisionTF

    %VideoReader should be used when StartTime is far from the beginning of the video.
    %VideoReader can start reading the video at any point in time, whereas vision.VideoFileReader  
    %can only read from the beginning. vision.VideoFileReader can still be used when the StartTime  
    %is other than the beginning because vision.VideoFileReader can be used to cycle through frames  
    %until the index that corresponds to the desired time. If the duration between the beginning of 
    %the video and StartTime is long, VideoReader might take less time overall because it doesn't   
    %have to cycle through frames. 

    %Select the reader to use based on the cost from vision.VideoFileReader of reading up to 
    %StartTime:
    % - If the video is relatively short, such that the amount of time spend reading up to  
    %   StartTime would be trivial, use vision.VideoFileReader.
    % - Otherwise, determine whether to use vision.VideoFileReader depending on the proportion of  
    %   time between the beginning of the video and StartTime relative to the duration of the video  
    %   to be processed.

    %Specify proportion to use as threshold
    %If the proportion is less than the threshold, vision.VideoFileReader will be used.
    ProportionThreshold = .10;

    %Set flag indicating use of vision.VideoFileReader
    if StartTime < 100 && (EndTime - StartTime) < 100

        UseVisionTF = true;

    else

        UseVisionTF = StartTime / (EndTime - StartTime) < ProportionThreshold;
    end
end
    

%%%%%% Specify settings for video reader vision.VideoFileReader %%%%%% 

%If vision.VideoFileReader is to be used as the video reader
if UseVisionTF

    %Note: VideoReadConfig_Setup_Vision is a custom function located within folder 'FacePulseRate'.
    [videoFReader, FrameIdxFromStart, FrameIdx, EndTimeSpecified, StartTime, EndTime, ...
     TimestampTolerance, FrameTimestampUntrimmed, NFrames] = ...
        VideoReadConfig_Setup_Vision(Video_InputFile, VidObj, StartTime, EndTime, ...
            VidObjNumFrames);
   
    
%%%%%% Specify settings for video reader VideoReader %%%%%% 

%If VideoReader is to be used as the video reader
else

    %Note: VideoReader is a custom function located within folder 'FacePulseRate'.
    [videoFReader, FrameIdxFromStart, FrameIdx, StartTime, EndTime, TimestampTolerance, ...
     FrameTimestampUntrimmed, NFrames] = ...          
        VideoReadConfig_Setup_VideoReader(VidObj, StartTime, EndTime, VidObjNumFrames, FS);

end


%%%%%% Assign variables of different precision for timestamps %%%%%%

%Type double will be used where required for high precision.
%Type single will be used where high precision is not needed for faster evaluation.

FrameTimestampUntrimmed_Double = FrameTimestampUntrimmed;
FrameTimestampUntrimmed_Single = single(FrameTimestampUntrimmed);
    
    
%%%%%% Assign struct %%%%%%

%Specify StartTime EndTime as type double for adequate precision.

VideoReadConfig = ...
    struct( ...
        'Video_InputFile', Video_InputFile, ...
        'FrameIdx', FrameIdx, ...
        'FrameIdxDoNotExceed', FrameIdxDoNotExceed, ...
        'MaxFrameIdx', MaxFrameIdx, ...
        'FrameIdxFromStart', FrameIdxFromStart, ...
        'NFrames', NFrames, ...
        'FrameTimestampUntrimmed_Double', FrameTimestampUntrimmed_Double , ...
        'FrameTimestampUntrimmed_Single', FrameTimestampUntrimmed_Single, ...
        'TimestampTolerance', TimestampTolerance, ...
        'StartTime', double(StartTime), ...
        'EndTimeSpecified', EndTimeSpecified, ...
        'EndTime', double(EndTime), ...
        'FS', FS, ...
        'VidObj', VidObj, ...
        'videoFReader', videoFReader, ...
        'VidObjWidth', VidObjWidth, ...
        'VidObjHeight', VidObjHeight, ...
        'UseVisionTF', UseVisionTF ...
    );


end %end function




