function [VideoFileWriter, OutputFile_OnlyVideo, cleanupObj1, cleanupObj2] = ...
             WriteFaceVideo_InitializeWriter(WriteVideoNoSoundTF, WriteVideoName, FS)
%WriteFaceVideo_InitializeWriter   Initialize the video writer for the output video.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function WriteFaceVideo.  
%
%
%    Description
%    -----------
%
%    Initialize the video writer for the output video.
%
%    If audio is enabled, create a temporary folder in which to save the initial file and append
%    the file name of the initial file (append '_TEMP.mp4'). Saving the temporary file to a folder 
%    labeled as temporary with a different name is intended to make users aware that this file is 
%    temporary. Later, if the compression is successful, the function that handles the call to 
%    ffmpeg (function WriteFaceVideo_CombineOutputVideoAndAudio will delete the folder and files 
%    as they are no longer needed. If unsucessful, this folder and file will remain.
%
%    Note: 
%
%    If WriteVideoNoSoundTF was specified as false, function validateToolboxesArguments checked 
%    whether the audio in the input file had a supported sample rate. If it did not, 
%    WriteVideoNoSoundTF was switched to true.  
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Output video without audio %%%%%% 

%If output video is specified not to contain audio
if WriteVideoNoSoundTF

    OutputFile_OnlyVideo = WriteVideoName;
   
    
%%%%%% Output video with audio %%%%%%

else
      
    %%%%%% --- Save inititial/temp file to temp folder %%%%%%
    
    %If audio is enabled, create a temporary folder in which to save the initial file and append
    %the file name of the initial file (append '_TEMP.mp4'). Saving the temporary file to a folder 
    %labeled as temporary with a different name is intended to make users aware that this file is 
    %temporary. Later, if the compression is successful, the function that handles the call to 
    %ffmpeg (function WriteFaceVideo_CombineOutputVideoAndAudio will delete the folder and files 
    %as they are no longer needed. If unsucessful, this folder and file will remain.     
               
    %%%%%% >>>>>> Create temporary folder %%%%%%

    %Directory of temporary folder for system
    pathParent = tempdir();

    %Directory of new folder within temporary folder
    pathToUse = [pathParent, 'FacePulseRate'];

    %Create the temporary folder
    %Suppress the warning that the folder already exists. The folder might already exist if  
    %function FacePulseRate was previously called but terminated before the temporary file was 
    %deleted. Note that mkdir() will not overwrite the existing folder. 
    [~, ~, ~] = ... tildes to the suppress the warning
        mkdir(pathToUse); 

    %%%%%% >>>>>> Determine temporary file name %%%%%%

    %Extract only the name of WriteVideoName
    [~, nameToUse, ~] = fileparts(WriteVideoName);

    %Assign the path, name, and extension to be used for the video-only file
    OutputFile_OnlyVideo = [pathToUse, filesep(), nameToUse, '_TEMP.mp4'];
                
end %end prepartion of video with audio 


%%%%%% Initiate video writer %%%%%%

%System object vision.VideoFileWriter is used rather than VideoWriter as it is faster.
    
VideoFileWriter = ...
    vision.VideoFileWriter(...
        OutputFile_OnlyVideo,  ... output file name
        'FrameRate', FS,       ... output file frame rate
        'FileFormat', 'MPEG4', ...
        'Quality', 65          ... influences file size
    );
    
%Setup cleanup object to release and destruct VideoFileWriter if function WriteFaceVideo is 
%interrupted (e.g., by an error being thrown or, more likely, by use of ctrl+c). If VideoFileWriter 
%is not released, the video may remain locked by the operating system, preventing it from being 
%rewritten. The cleanup object is passed to function WriteFaceVideo, so it will be activated when  
%WriteFaceVideo terminates. 
cleanupObj1 = onCleanup( @()release(VideoFileWriter) );

%Setup cleanup object to delete video if function WriteFaceVideo is interrupted
%This will also delete the video if WriteFaceVideo successfully terminates. 
%Note: before completion, the video is stored in a temporary folder.
cleanupObj2 = onCleanup( @()WriteFaceVideo_DeleteTempVid(OutputFile_OnlyVideo) );


end %end function


