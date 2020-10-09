function OutputConfig = ...
             OutputConfig_Setup_VideoWriting(Video_InputFile, WriteVideoDetailedDiagnosticsTF, ...
                 SkinSegmentConfig, SkinDetectConfig)
%OutputConfig_Setup_VideoWriting    Settings for video writing. 
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function OutputConfig_Setup.
%
%
%    Description
%    -----------
%
%    Settings and input validation for video writing. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Video writing settings %%%%%%

WriteVideoTF = true;
WriteVideoNoSoundTF = false;
WriteVideoShowSkinSegmentTF = true;
WriteVideoShowROISkinDiagnosisTF = true;
WriteVideoShowLegendTF = true;

%Output video name:
    
%Remove file extension from path and file name
fileNoExt = Video_InputFile(1 : length(Video_InputFile) - 4);

%Append string and file extension to path and file name
WriteVideoName = [fileNoExt, '_OutVid.mp4'];   

%Adjust settings for flag WriteVideoDetailedDiagnosticsTF: 

if ~ WriteVideoDetailedDiagnosticsTF
    
    WriteVideoShowROISkinDiagnosisTF = false;
end


%%%%%% Validate Settings %%%%%%

%Extract path name
[path, ~, ~] = fileparts(WriteVideoName);

%Extract directory information from input video
listing = dir(path);

%Check wheter file exists
if isempty(listing) 
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: Folder specified for WriteVideoName does not appear to exist.' ...
        );
    
    throw(ME);
end


%WriteVideoShowROISkinDiagnosisTF == true but WriteVideoTF and/or ROISkinTF is false:

if WriteVideoShowROISkinDiagnosisTF && (~ WriteVideoTF || ~ SkinDetectConfig.ROISkinTF)
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: when WriteVideoShowROISkinDiagnosisTF is true', ...
             ' both ROISkinTF and WriteVideoTF should be true.'] ...
        );
    
    throw(ME);
end 


%WriteVideoShowSkinSegmentTF = true but WriteVideoTF = false:

if WriteVideoShowSkinSegmentTF && ~ WriteVideoTF  
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: When WriteVideoShowSkinSegmentTF = true, WriteVideoTF should = true.' ...
        );
    
    throw(ME);
end


%WriteVideoShowSkinSegmentTF = true but SkinSegmentTF = false:

if WriteVideoShowSkinSegmentTF && ~ SkinSegmentConfig.SkinSegmentTF  
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: when WriteVideoShowSkinSegmentTF = true, SkinSegmentTF should = true.');
    
    throw(ME);
end


%Extension of argument WriteVideoName is not .mp4:

%Change extension to .mp4.
if WriteVideoTF && ...
   ~ strcmp('.mp4', WriteVideoName(end - 3 : end))
    
    warning( ...
        'Component:Argument', ...
        ['This function is implemented to produce video output files with'... 
         ' extension .mp4. The file extension will be changed to .mp4.'] ...
     );

    %Change file extension to .mp4
    WriteVideoName(end - 3 : end) = '.mp4';            
end


%Check whether audio writing is supported for audio format:

if ~ WriteVideoNoSoundTF

    %Note: see function WriteFaceVideo_CombineOutputVideoAndAudio.
    
    %Supported sample rates (Hz) for function audiowrite when writing mp4 files
    AudioWriteSupportHz = [44100, 48000];  

    %Determine the sample rate of audio in input video file
    AudioInfo = audioinfo(Video_InputFile); %audio information
    AudioSampleRate = AudioInfo.SampleRate; %sample rate

    %Check whether sample rate supported
    AudioWriteSupportHzTF = ismember(AudioSampleRate, AudioWriteSupportHz);
    
    if ~ AudioWriteSupportHzTF
        
        %Display warning    
        warning( ...
            'Component:Argument', ...
            ['Audio sample rate of input video not supported. Supported sample rates (Hz): ', ...
             num2str(AudioWriteSupportHz), '. Audio will not be included in output video.'] ...
        );
            
        %Change WriteVideoNoSoundTF to true
        WriteVideoNoSoundTF = true;      
    end   
end


%WriteVideoShowSkinSegmentTF:

%SkinSegmentTF == true and WriteVideoTF == true but WriteVideoShowSkinSegmentTF == false
if SkinSegmentConfig.SkinSegmentTF && WriteVideoTF && ~ WriteVideoShowSkinSegmentTF 

    warning( ...
        'Component:Argument', ...
        ['Note: skin segmentation enabled (SkinSegmentTF = true)'... 
         ' but skin segmentation will not be shown on video because'...
         ' Video_ShowSkinSegTF = false. Output other than video will'... 
         ' still use skin segmentation.'] ...
    );  
end


%Check whether output video to be written to is locked by operating system:

%If locked, the likely cause is that a file of the same name is open in another program.

%Intialize video writer    
VideoFileWriter = ...
    vision.VideoFileWriter(...
        WriteVideoName,        ... output file name
        'FrameRate', 30,       ... output file frame rate
        'FileFormat', 'MPEG4', ...
        'Quality', 65          ... influences file size
    );

%Assign a test frame to write to file
VidFrame = ones(1000, 1000, 3, 'uint8');

%If file is locked, then the try will fail
try
    
    %Write test video
    VideoFileWriter(VidFrame);
    
    %Release video writer
    release(VideoFileWriter);
    
    %Delete test video
    delete(WriteVideoName);
    
catch

    %Release video writer
    release(VideoFileWriter);    
    
    %Change back-slash to forward-slash to avoid escaped characters:
    
    WriteVideoName_ForwdSlash = WriteVideoName;
    
    for i = 1 : length(WriteVideoName_ForwdSlash)

        if WriteVideoName_ForwdSlash(i) == '\'

            WriteVideoName_ForwdSlash(i) = '/';
        end   
    end  
    
    %Throw error:
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: File ', WriteVideoName_ForwdSlash, ' appears to be in use by another', ...
             ' program. Please close the file before running FacePulseRate.'] ... 
        );
    
    throw(ME);    
end


%Check audio:

%If WriteVideoNoSoundTF == false, operations within function FacePulseRate will expect audio to be
%present. This block checks whether the input file contains audio; if not, it switches 
%WriteVideoNoSoundTF to false.
if ~ WriteVideoNoSoundTF
     
    try
        
        %Attempt to extract audio information. If audio is not 
        %present, audioinfo will throw an error. 
        audioinfo(Video_InputFile);

    catch

        %Display warning
        warning( ...
            'Component:Argument', ...
            'Unable to detect audio. Audio will not be included in output video.' ...
        );
        
        %If error, switch WriteVideoNoSoundTF to true so that
        %operations do not expect audio.
        WriteVideoNoSoundTF = true;    
    end
end

%Check for characters that could cause issues using operating system shell commands:

%Shell commands used to execute ffmpeg.exe and ffprobe.exe.

%If the characters ',' OR ';' occur at least once in any of the file paths specified by arguments
%This is to support compatibility with the command prompt, which cannot handle these characters.
if ~ isempty( regexp(WriteVideoName, '[,;]', 'Once') )
 
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: file names cannot contain '','' or '';''.' ...
        );
    
    throw(ME);  
end 


%%%%%% Insert video settings into output struct %%%%%%

OutputConfig = ...
    struct( ...     
        'WriteVideoTF',                     WriteVideoTF, ...
        'WriteVideoName',                   WriteVideoName, ...
        'WriteVideoNoSoundTF',              WriteVideoNoSoundTF, ...
        'WriteVideoShowSkinSegmentTF',      WriteVideoShowSkinSegmentTF, ...
        'WriteVideoShowROISkinDiagnosisTF', WriteVideoShowROISkinDiagnosisTF, ...
        'WriteVideoDetailedDiagnosticsTF',  WriteVideoDetailedDiagnosticsTF, ...
        'WriteVideoShowLegendTF',           WriteVideoShowLegendTF ...
    );


end %end function

