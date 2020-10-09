function FrameTimeStamps_Imported = ...
             getFrameTimestamps(ffprobeEXE, Video_InputFile, EndTime)
%getFrameTimestamps   Retrieve the timestamps of a video.
%
%   Helper function to function FacePulseRate. 
%   Within function FacePulseRate, called by function VideoReadConfig_Setup_Vision.
%   
%
%   Description
%   -----------
%   
%   Retrieve the timestamps of a video.
%
%   Code adapted from function videoframets (v0.1) copyright (c) 2017 David Bulkin. videoframets 
%   was obtained from the Matlab File Exchange. The license for this file is included in 
%   FacePulseRate.
%
%   The current implementation has been designed to increase execution speed.
%   
%
%   ______________________________________________________________________________________________
%   Description from function videoframets:
%
%   ts = VIDEOFRAMETS(ffmpeg_path,videofile) returns the timestamps (ts) in seconds of 
%   each video frame in a video file (videofile) using ffmpeg.exe. The location of 
%   ffmpeg.exe must be specified (ffmpeg_path; i.e. it can not just reside on the 
%   matlab path).
%
%   VIDEOFRAMETS(ffmpeg_path,videofile,ffmpeg_textfile) will store the raw output 
%   produced by ffmpeg in the text file 'ffmpeg_textfile'
%
%   FFMPEG is freely available can be downloaded from: 
%       <a href="matlab:web('http://ffmpeg.org/')">http://ffmpeg.org/</a>
%
%   Tested on Windows, with ffmpeg 2.5.2 and 3.2.2
%       I think this should work on OSX/UNIX, because the pipe to file commands are
%       the same, but I haven't tested it.
%
%   EXAMPLE:
%       ffpath='C:\ffmpeg\bin'
%       vidfile='D:\videos\somevideo.mpeg'
%       ts=videoframets(ffpath,somevideo);
%       hist(1./diff(ts),1000);  %this shows a distribution of the actual frame rates
%       
%   Notes on why this is useful:
%     VIDEOFRAMETS attempts to solve an issue with quantitative video analysis. While 
%   mpeg video is recorded with a fixed framerate, in reality, video frames often 
%   deviate from this value. [I think this is due to delays in the encoder, for 
%   instance if the computer recording video is under excessive load, frames will come 
%   in slower]. If frames often come in a little bit slower than expected (empirical 
%   framerate < nominal framerate), the problem compounds over the course of a video: 
%   if a user assumes a fixed framerate the data at the end of the video will be 
%   greatly mismatched from reality.
%     This presents a tremendous problem to time locked video analysis. Matlab's 
%   VideoReader offers a practical solution: VideoReader objects contain a property 
%   that identifies/sets the current time in the video. This is generally a practical 
%   solution to the problem (note: when used with the newer .readFrame method rather 
%   than the older .read method). However, this has some limitations: 
%       1: It is often useful to know the number of frames and the corresponding 
%       timestamps at the onset of video analysis (although a rough estimate is 
%       obtainable using the .FrameRate and .Duration properties of VideoReader, 
%       typically adequate for initializing variables). 
%       2: The performance of vision.VideoFileReader is often orders of magnitude 
%       faster than VideoReader (from personal measurements, speed improvements 
%       depend on codec), and seems to work more reliably with a wider set of video 
%       files. However, vision.VideoFileReader offers no strategy for assessing 
%       frame times. Using VideoReader for timing and vision.VideoFileReader for frame 
%       data is impractical because it sacrifices the advantages of using the 
%       vision.VideoFileReader function
%       3: It may be useful to some users to get timing information only, for instance 
%       if performing video analysis elsewhere. 
%
%     The times of frames are stored in the MPEG file using presentation timestamps 
%   (PTS; frequently used for alignment of video and auditory streams). While these 
%   are inaccessible to the high level Matlab coder, the tool ffmpeg readily provides 
%   their values, and runs pretty quickly (in testing, 50 seconds for a 20 minute 
%   MPEG file, while VideoReader gets the same information in about 6 minutes).
%
%   a few notes on the ffmpeg command:
%       1: It's apparently quicker to have ffmpeg pipe the output to a text file and 
%       have matlab read the text file, rather than to just have matlab read the output
%       from system (that's really surprising to me!). It's actually orders of 
%       magnitude faster (?)
%
%       2: in my tests with ffmpeg, I found that ffmpeg's showinfo surprisingly seems to 
%       put its output into the stderr output (i.e. use 2> rather than >)...this took me
%       FOREVER to figure out!
%
%   See also: VideoReader vision.VideoFileReader
%  ______________________________________________________________________________________________
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Read timestamps from input video and write to file with ffprobe.exe %%%%%% 

%Assign name for temporary file in which to have ffmpeg write timestamps
txtFile = [tempname, '.txt'];

%Command line arguments for ffprobe.exe:

% <filename>                     = Path of ffprobe.exe.
% -i <filename>                  = Path of input file. 
% -select_streams                = Stream to read (v = video; a = audio). Specify only video so
%                                  that audio timestamps are not read.
% -read_intervals <start>%<end>  = Read only this interval (seconds). This saves processing time    
%                                  when the length of the input video to be assessed does not  
%                                  extend to the end of the video.
% -show_entries packet=pts_time  = Print desciption of each packet. pts_time = presentation
%                                  timestamp.
% -print_format csv              = When printing, separate output with commas.
% >> <filename>                  = Path of file to write to.

%For ffprobe documentation, see https://ffmpeg.org/ffprobe.html.

%Description of alternative commands:

%Option 1, which is used, does not return timestamps in chronological order but is faster than
%options 2 and 3. The timestamps can simply be sorted later to put in chronolgical order. However,
%one benefit of having chronological order returned is that, sometimes, the last couple frames, as
%encoded in the video, are not in chronological order, and not having to sort frames allows these
%frames to be identified. Being able to identify these frames can be used to omit them. To overcome
%this issue with option 1, it might be considered to simply delete the last 2 or 3 frames to remove
%any frames that may potentially not be in chronological order. This action is taken for function
%FacePulseRate outside of this function.

%All three options shown here are faster than the implementation in function videoframetsOriginal,
%which uses ffmpeg.exe rather than ffprobe, as used here.

%Option 1: Faster but timestamps not in chronological order   
ffm_line = ...  
    ['"', ffprobeEXE, '"',                    ... ffprobe executable location
     ' -i ', '"', Video_InputFile, '"',       ... input video location
     ' -select_streams v:0',                  ... only assess video, not audio
     ' -read_intervals 0%', num2str(EndTime), ... span to read: from 0 sec to EndTime
     ' -show_entries packet=pts_time',        ... return presentation timestamp for each packet
     ' -print_format csv=print_section=0',    ... print format: csv = comma-separated 
                                              ...               print_section=0 = no labels
     ' >>', txtFile];                         %   output file location
  
%Options 2 and 3: Slower but timestamps in chronological order
%{

%Option 2: More verbose
ffm_line = ...  
    ['"', ffprobeEXE, '"',                   ... ffprobe executable location
    ' -i ', '"', Video_InputFile, '"',       ... input video location
    ' -select_streams v:0',                  ... only assess video, not audio
    ' -read_intervals 0%', num2str(EndTime), ... span to read: from 0 sec to EndTime
    ' -show_frames',                         ... return information for each frame 
    ' -print_format csv',                    ... return in comma-separated form
    ' >>', txtFile];                         %   output file location
  
%Option 3: Less verbose
ffm_line = ...  
    ['"', ffprobeEXE, '"',                   ... ffprobe executable location
    ' -i ', '"', Video_InputFile, '"',       ... input video location
    ' -select_streams v:0',                  ... only assess video, not audio
    ' -read_intervals 0%', num2str(EndTime), ... span to read: from 0 sec to EndTime
    ' -show_frames',                         ... return information for each frame
    ' -of default=nokey=0'                   ... do not return the label for each piece of information
    ' -print_format csv',                    ... return in comma-separated form
    ' >>', txtFile];                         %   output file location
%}

%Call ffprobe.exe through command line 
%The first output argument is a status value communicated by the command prompt.  
%status == 0 indicates success.  However, it is possible for the command prompt to indicate success
%when the application did not complete the desired operation.
%The second output argument contains information regarding the operation passed from the
%application. It can be verbose, so it is suppressed.
%The Matlab system will remain busy until output is returned; that is, Matlab will wait until 
%output is returned to continue.
[status, ~] = system(ffm_line);

%Check for problem from ffprobe or command line
if status ~= 0
    
    ME = ...
        MException('Component:External', ...
             ['\nError: A problem occurred while attempting to retrieve timestamps.', ...
              '\nRestarting Matlab may help.']);
    
    throw(ME)
end
    

%%%%%% Import timestamps from temporary file %%%%%%

%Read file
%Note: with the current command to ffprobe, only numbers are printed to the txt file.
%If a different command is used that causes a mix of numbers and strings to be printed, function
%load() will not work; in such a case, use function readtable().
FrameTimeStamps_Imported = load(txtFile);

%Sort to chronological order
%Only needed with output from option 1.
FrameTimeStamps_Imported = sort(FrameTimeStamps_Imported); 


%%%%%% Delete temporary file %%%%%%

try 
    
    delete(txtFile)
    
catch
    
end


end %end function

