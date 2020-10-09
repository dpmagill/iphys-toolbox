function WriteFaceVideo_CombineOutputVideoAndAudio(OutputConfig, OutputFile_OnlyVideo, ...
             VideoReadConfig)
%WriteFaceVideo_CombineOutputVideoAndAudio   Combine output video and output audio and write to 
%                                            file.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo.
%
%
%    Description
%    -----------
%
%    Combine output video and output audio and write to file.                                           
%
%    Audio writing has been implemented to support input video with a variable frame rate (VFR).
%    The output video is constant frame rate (CFR), as that is the only option provided by video
%    writers from Matlab toolboxes. If the output is CFR but the input is VFR, the CFR video may be
%    shorter as variable spacing is not used between frames. To map the input audio to the output
%    video, the input audio is intentionally time-distorted to map to the same time-distortions as
%    the output video. To do so, the audio samples are separated into bins according to the
%    timestamps of the original video. The bins are then spaced in a CFR manner, which should  
%    correspond to the spacing of the output video. The intentional distortion should not be 
%    noticeable; on the other hand, not mapping the audio to the output video could become 
%    noticable after several minutes as differences in spacing accumulate.
%
%    Note: For audio writing, function audiowrite is used rather than the audio functionality in  
%    function vision.VideoFileWriter because setting the audio option on vision.VideoFileWriter
%    prevents it from compressing the video sufficiently. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Determine whether to include audio in output video based on supported sample rates %%%%%%

%Note: whether input audio has a supported sample rate is also checked in function 
%validateToolboxesArguments, so if supported sample rates are modified, modify the checking in that
%function as well.

%Supported sample rates (Hz) for function audiowrite when writing mp4 files
AudioWriteSupportHz = [44100, 48000];  

%Determine the sample rate of audio in input video file
AudioInfo = audioinfo(VideoReadConfig.Video_InputFile); %audio information
AudioSampleRate = AudioInfo.SampleRate; %sample rate

%Check whether sample rate supported
AudioWriteSupportHzTF = ismember(AudioSampleRate, AudioWriteSupportHz);


%%%%%% Audio sample rate not supported: Do not include audio in output file %%%%%%

%If input audio sample rate not supported
if ~ AudioWriteSupportHzTF 

    %Display warning
    warning( ...
        ['Audio sampling rate of input video not supported. Supported sampling rates (Hz): ', ...
         num2str(AudioWriteSupportHz), '. Audio will not be included in output video.'] ...
     );

    %Move video-only file from temporary folder to file specified by WriteVideoName:
    
    %MoveStatus == 1 indicates success.
    MoveStatus = ...
        movefile( ...
            OutputFile_OnlyVideo,        ... Path and file name to move
            OutputConfig.WriteVideoName, ... Path and file name to write to (file name can differ 
                                         ... from that being moved). 
            'f'                          ... Force operation
        );

    %If file move unsuccessful    
    if ~ MoveStatus

        %Do not delete temporary files or folder.
        %Display warning message indicating temporary folder location where temporary files can be
        %found.

        %Directory of temporary folder
        [path, ~, ~] = fileparts(OutputFile_OnlyVideo); 

        warning(['Find video-only file in ', path, '.']);
    end   
  
    
%%%%%% Audio sample rate supported: Include audio in output file %%%%%%
else    
    
    
    %%%%%% Display notification message %%%%%%

    message = '\nAdding audio to output video...\n';         
    fprintf(message);
    drawnow(); %display message immediately

    
    %%%%%% Extract some variables from struct %%%%%%

    %Note: the indexes that will be used for indexing audio samples get quite large: into the 
    %hundreds of millions. At these high numbers, enough precision can be lost that the space 
    %between two consecutive integers is greater than one, which can cause errors. To help mitigate 
    %this, use type double.
    
    FrameTimestamp = VideoReadConfig.FrameTimestamp_Double;
    FS             = VideoReadConfig.FS;
    
    
    %%%%%% Read audio from input video %%%%%%

    %%%%%% --- Prepare the indices specifying the beginning of each audio sample bin %%%%%%

    %Determine audio sample indices that mark the first audio sample to use for each frame; these
    %indices mark the start of the audio bin to be paired with each frame.
    %Assume audio samples corresponding to a given frame begin immediately after the timestamp of
    %the previous frame.
    %Round to integer for indexing.       

    %Because it is assumed that a given frame's timestamp corresponds to the end of the audio
    %samples for the frame, the audio sample index denoting the first audio sample for the frame
    %should correspond to an earlier time. For all other frames, the earlier time is specifed as 
    %the timestamp of the previous frame. As a previous frame does not exist for the first frame,
    %estimate when the first audio sample begins; to estimate, subtract from the timestamp the
    %average duration for a frame, which is calculated by the inverse of the frame rate (FS); 
    %multiply this time by the audio sampling rate to determine the audio sample index. It might be 
    %noted that the index of the first audio sample of the input file is 1; hence, the index 1 
    %might be appropriate if the StartTime is 0; however, if the StartTime is different from 0, the 
    %index of the first audio sample will not be 1; for this reason, the index of the first audio 
    %sample is estimated as previously described.  

    %Determine beginning audio sample index for bin of first frame
    %To avoid a zero or negative index in case the estimation of the first audio sample is 
    %inaccurate, set the index to 1 if the estimated index is less than one (the max() function is
    %used for this purpose).
    AudioIdxBinsBegin_1stFrame = ...
        max( 1, round( ( FrameTimestamp(1) - (1 / FS) ) * AudioSampleRate ) );

    %Determine beginning audio sample indices for bins of remaining frames
    %Note the the timestamps are shifted such that, for example, the timestamp corresponding to the
    %first frame is used to indicate where to start extracting audio samples for the second frame, 
    %the second frame indicates where to start extracting for the third frame, etc. 1 is added to
    %each index so that the index corresponds to the time immediately after the timestamp of the
    %previous frame.
    AudioIdxBinsBegin_OtherFrames = ...
        round( ...
            FrameTimestamp(1 : end - 1) * AudioSampleRate ...            
         ) + 1;

    %Beginning audio sample indices for bins of all frames
    %Convert to integer type to increase safety when indexing.
    AudioIdxBinsBegin = ...
        uint64( ...
            [AudioIdxBinsBegin_1stFrame; AudioIdxBinsBegin_OtherFrames] ...
        );

    %%%%%% --- Prepare the indices specifying the end of each audio sample bin %%%%%%

    %Determine audio sample indices that mark the last audio sample to use for each frame; these
    %indices mark the end of the audio bin to be paired with each frame.
    %Assume audio ends at timestamp of current frame. Multiply this timestamp by the audio sampling 
    %rate to determine the audio sample index.
    %Round to integer for use as index and convert to integer type to increase safety of index.
    AudioIdxBinsEnd = ...
        uint64( ...
            round(FrameTimestamp * AudioSampleRate) ...
        );
        
    %{ 
    
    %%%%%% --- Make bin size consistent across frames %%%%%%

    (Previous implementation)
    
    %Make the sizes of indices consistent across frames
    %In other words, the number of indices between the beginning sample index and the ending sample
    %index should be the same for each frame. Do so by making the sizes equal to the smallest size;
    %remove portions of indices that exceed this size; remove portions by subtracting from the   
    %ending indices.
    %Note: this step was part of a previous implementation where the vision.VideoFileWriter system
    %object was used to write audio in addition to video; vision.VideoFileWriter requires that each
    %set of audio samples be the same size. vision.VideoFileWriter is not used to write audio in
    %the current implementation (audiowrite does this instead), but this step is retained in case
    %compatibility with vision.VideoFileWriter is needed at a future time. 
    AudioIdxBinsEnd = ...
        AudioIdxBinsEnd - ( (AudioIdxBinsEnd - AudioIdxBinsBegin) - ...
                           min(AudioIdxBinsEnd - AudioIdxBinsBegin) );           

    %}

    %%%%%% --- Read audio %%%%%%

    %Start reading at the first specified audio index
    %Stop reading at whichever is less, the last specified audio index or the end of the audio data.
    %Without attempting to read the audio, it is unknown how many actual samples there are in the 
    %audio data (note: audinfo.TotalSamples is sometimes greater than the actual number of 
    %samples). First, try to read the video up to the last index specified. If an error is thrown, 
    %assume that the specified index exceeded the maximum actual index and try again using the 
    %'inf' option, which specifies to read up to the last available audio sample.

    %Sometimes the index exceeds the maximum but a warning is thrown rather than an error. To 
    %suppress the warning in this case, the following warning suppression is specified.
    warning('off', 'MATLAB:audiovideo:audioread:incompleteRead');

    %In the event of fewer audio samples than expected (in which case, either an error or warning 
    %is thrown), the section "Pad end of audio if necessary" adjusts variables as needed.

    %For memory conservation, specify type "native", which may be a type that uses a smaller 
    %number of bytes compared to the default, double.
 
    %Index argument must be type double.    
    
    try   

        audio = ...
            audioread( ...
                VideoReadConfig.Video_InputFile, ...
                double(                    ... argument must be type double
                    [AudioIdxBinsBegin(1), ... first specified audio index         
                     AudioIdxBinsEnd(end)] ... last specified audio index
                ), ...
                'native' ...
            );

    %Assume the last specified index exceeded the available samples
    %Specify the 'inf' option.

    catch    
        
        audio = ...
            audioread( ...
                VideoReadConfig.Video_InputFile, ...                
                    [double(AudioIdxBinsBegin(1)), ... first specified audio index            
                     double(inf)],                 ... maximum audio index in the audio data
                    'native' ...
            );
    end


    %%%%%% Write audio %%%%%%

    %%%%%% --- Pad end of audio if fewer audio samples then expected %%%%%%

    %Note: this will always be the case if the catch above is entered.
    %Sometimes the try is successful but there are still fewer samples then expected because
    %audioread will sometimes throw a warning rather than an error.

    %Expected length 
    AudioLengthExpected = AudioIdxBinsEnd(end) - AudioIdxBinsBegin(1) + 1;

    %Actual length
    AudioLengthActual = length(audio);

    %Pad end of audio data if actual maximum index less than specified maximum index
    if AudioLengthActual     ... actual length
       < AudioLengthExpected %   expected length

        %Difference between actual and expected number of samples
        NSampleDeficit = AudioLengthExpected - AudioLengthActual; 

        %Padding to be inserted
        audioPadding = ...
            zeros(NSampleDeficit, ... samples needed to extend into last frame
                size(audio, 2),   ... number of audio channels
                'like', audio);   ... match type of audio in input file

        %Assign padding to end of audio data
        audio = [audio; audioPadding];
    end

    %%%%%% --- Shift indices of audio samples %%%%%%

    %If StartTime is greater than 0, due to the audio having been extracted at the first specified 
    %audio index rather than 1, the SampleBegin and SampleEnd indices may no longer align with the 
    %audio samples. Shift the indices by the difference between the first AudioIdxBinsBegin index  
    %and 1 to align. For AudioIdxBinsBegin, this will result in AudioIdxBinsBegin(1) == 1.

    %Length of shift
    IdxShift = AudioIdxBinsBegin(1) - 1;

    %Shift samples
    AudioIdxBinsBegin = AudioIdxBinsBegin - IdxShift; 
    AudioIdxBinsEnd   = AudioIdxBinsEnd   - IdxShift;

    %%%%%% --- Shrink/stretch audio indices to conform to constant-frame-rate output video %%%%%%

    %The audio bin indices used to extract audio were based upon FrameTimestamp, which might be
    %spaced at a variable-frame rate. The output video, however, is always written at a constant
    %frame rate, which is the only option from vision.VideoFileWriter. To sync the original audio
    %to the constant-frame rate output video, change the spacing of the audio bins to be constant.

    %Query output video to get duration
    VidOutputObj = VideoReader(OutputFile_OnlyVideo); %audio information
    Duration = VidOutputObj.Duration; 

    %Assign audio matrix to match duration of output video:
    OutputAudioLength = ceil(Duration * AudioSampleRate);

    OutputAudio = ...
        zeros( ...
            OutputAudioLength, ...
            size(audio, 2), ... match number of audio channels (columns) as audio data read
            'like',         ... use same type as audio data read
            audio ...
        );

    %Specify constant spacing interval for audio samples
    ConstantSpacingInterval = round(AudioSampleRate / FS);

    %Assign audio to correspond with constant-frame-rate video timing
    %Specify integer type for safe index.
    for i = uint64(1 : length(FrameTimestamp))

        %Extract ith audio bin from audio that was read
        AudioIthFrame = ...
            audio(AudioIdxBinsBegin(i) : AudioIdxBinsEnd(i), :);

        %Row index of OutputAudio to insert ith audio bin
        %When i == 1, (i - 1) equals 0; this results in the first index being 1.
        RowIdx = ...
            (i - 1) * ConstantSpacingInterval + 1 : ... 
            (i - 1) * ConstantSpacingInterval + size(AudioIthFrame, 1);

        %Insert ith audio bin
        OutputAudio(RowIdx, :) = AudioIthFrame;
    end

    %%% --- Normalize audio data %%%%%%

    %Normalize audio data to be within +/- 1 (inclusive) 
    %Otherwise, function audiowrite will truncate values. 
    %This action is recommended in the function documentation.

    %Find most extreme value
    OutputAudioMax = max(abs(OutputAudio), [], 'all');

    %Normalize
    OutputAudio = OutputAudio / OutputAudioMax;

    %%% --- Write audio to temporary output file %%%%%%

    %Temporary audio file path and name
    %This path is located in the system's temporary folder.
    OutputFile_OnlyAudio = [OutputFile_OnlyVideo(1 : end - 4), 'Audio.mp4'];

    %Write audio to temporary audio-only output file
    audiowrite( ...
        OutputFile_OnlyAudio, ... output audio file name
        OutputAudio,          ... audio data
        AudioSampleRate       ... audio sample rate 
    );


    %%%%%% Write final output file by combining temporary video and audio files %%%%%%

    %Simply combine the video and the audio in the same media container
    %Use the ffmpeg executable, called through the command prompt.
    %See https://superuser.com/questions/277642/how-to-merge-audio-and-video-file-in-ffmpeg

    %Notes on Windows Command Prompt:
    %All commands must be sent in the same call. This is because each subsequent call opens a new
    %command prompt.
    %It has been observed that the "&" operator, which is used in the command prompt to separate
    %commands, is unsuccessful when sent by Matlab.  Hence, "&" should be avoided.

    %Name for output file
    OutputFile_VideoAndAudio = OutputConfig.WriteVideoName;

    %Assign full path for ffmpeg executable file
    %Local function.
    ffmpegExePath = getffmpegPath();

    %Specify command to call ffmpeg in command prompt  
    %Notes:
    %- -y indicates to suppress warning regarding overwriting an existing file
    %- -i indicates each input file
    %- -c copy indicates to combine the video and audio without reencoding
    %- the last entry is the output file
    ffmpegCommand = ...
        ['"', ffmpegExePath ,'"', ...
         ' -y -i ', OutputFile_OnlyVideo, ' -i ', OutputFile_OnlyAudio, ' -c copy ', ...
           OutputFile_VideoAndAudio];

    %Call ffmpeg in command prompt 
    %The first output argument is a status value communicated by the command prompt.  
    %status == 0 indicates success.  However, it is possible for the command prompt to indicate
    %success when the application did not complete the desired operation.
    %The second output argument contains information regarding the operation passed from the
    %application. It can be quite verbose, so it is suppressed.
    %The Matlab system will remain busy until output is returned; that is, Matlab will wait until
    %output is returned to continue.
    [status, ~] = ...
        system(ffmpegCommand);

    %%% --- Verify call to ffmpeg was successful %%%%%%

    %If the call to the executable appears does not appear to be successful, use temporary 
    %video-only file as final output file.
    %To consider successful, verify success message from command prompt and verify combined video
    %and audio file was produced.
    %Command prompt indicates success by status == 0. 
    %Verification of output file only checks whether a file name with the same name as that 
    %specified exists. If a different file with the same name happens to be present already, 
    %verification will still come back true even if the file was not written.
    ffmpegCallSuccessfulTF = ...
        status == 0 &&                    ... command prompt return value indicates success
        isfile(OutputFile_VideoAndAudio); %   output file exists

    %If call to ffmpeg was successful
    if ffmpegCallSuccessfulTF

        %Delete temporary files and folder
        %Local function.
        DeleteTemporary(OutputFile_OnlyVideo, ... video file to delete
            OutputFile_OnlyAudio);            %   audio file to delete

    %If call to ffmpeg was not successful
    else

        %Display warning message indicating addition of audio was not successful     
        warning(['Combining audio and video output not successful. ', ...
                 'Output file contains video only.']);   

        %Move video-only file to file specified by OutputFile_VideoAndAudio
        %MoveStatus == 1 indicates success.
        MoveStatus = ...
            movefile( ...
                OutputFile_OnlyVideo,     ... Path and file name to move
                OutputFile_VideoAndAudio, ... Path and file name to write to (file name can differ 
                                          ... from that being moved). 
                'f'                       ... Force operation
            );

        %If file move successful
        if MoveStatus

            %Delete temporary audio-only file and folder
            %As the video-only file was moved out of the temporary folder, there is no temporary
            %video-only file in the temporary folder to delete.
            %Local function.
            DeleteTemporary([],        ... video file to delete
                OutputFile_OnlyAudio); %   audio file to delete

        %If file move unsuccessful    
        else
      
            %Show warning
            warning('Writing to output video unsuccessful');
            
            %Previously, the following message was shown. However, it will not longer be accurate
            %as the file in OutputFile_OnlyVideo is now automatically deleted either if function
            %WriteFaceVideo is interrupted or once function WriteFaceVideo successfully terminates.
            %The deletion is carried out by the destruction of object cleanupObj2, which is
            %constructed by function WriteFaceVideo_InitializeWriter. The main purpose of this
            %object is to delete the temporary video if function WriteFaceVideo is uninterrupted to
            %avoid leaving the file in the temporary folder. Leaving the file in the temporary
            %folder is undesired because it takes up space and the contents of the video may be 
            %confidential. Ideally, the object would only be destroyed if the function is 
            %interrupted and not if it terminates successfully. Because it is destroyed on 
            %successful termination, the video cannot be saved in the case for which the warning
            %below is used.
            %
            %{
            
            %Delete temporary audio-only file but not video-only file or temporary folder.            
            %Local function.
            DeleteTemporary([],        ... video file to delete
                OutputFile_OnlyAudio); %   audio file to delete
            
            %Display warning message indicating temporary folder location where temporary  
            %video-only file can be found.
            %Directory of temporary folder
            [path, ~, ~] = fileparts(OutputFile_OnlyVideo); 

            warning(['Find video-only file in ', path, '.']);
            
            %}           
        end         
    end     
end


end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================    
function DeleteTemporary(OutputFile_OnlyVideo, OutputFile_OnlyAudio)
%DeleteTemporary.    Delete temporary media files.


%Use try-catch statements in case file or folders cannot be deleted.

%Delete temporary video-only output file
try             
    delete(OutputFile_OnlyVideo);
catch

end

%Delete temporary audio-only output file
try              
    delete(OutputFile_OnlyAudio);
catch

end

%Delete the temporary directory
try    
    %Directory of temporary folder
    [path, ~, ~] = fileparts(OutputFile_OnlyVideo);

    rmdir(path);
catch

end   


end %end local function


%=============================================================================================
function ffmpegPath = getffmpegPath()
%getffmpegPath.  Return full path for the ffmpeg executable file.


%For Windows
if ispc()

    %Return all directories within Matlab search path
    %These will be separated with a semicolon.
    SearchPaths = matlabpath();

    %Convert to string array
    SearchPathStrings = strsplit(string(SearchPaths), ';');

    %Find directory with executable
    SearchPath_FacePulseRate = ...
        SearchPathStrings( ...
            contains(SearchPathStrings, "FacePulseRate\Funs\General\ffmpeg\win64\bin") ...
        );

    %Concatenate directory with file name
    ffmpegPath = [char(SearchPath_FacePulseRate), '\ffmpeg.exe'];

%For MacOS
elseif ismac()

    %Return all directories within Matlab search path
    %These will be separated with a semicolon.
    SearchPaths = matlabpath();

    %Convert to string array
    SearchPathStrings = strsplit(string(SearchPaths), ';');

    %Find directory with executable
    SearchPath_FacePulseRate = ...
        SearchPathStrings( ...
            contains(SearchPathStrings, "FacePulseRate/Funs/General/ffmpeg/mac/bin") ...
        );

    %Concatenate directory with file name
    ffmpegPath = [char(SearchPath_FacePulseRate), '/ffmpeg'];                
end  


end %end local function