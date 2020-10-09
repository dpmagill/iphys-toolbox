function FacePulseRate_CompletionMessage(VideoReadConfig, FunctionStartTime)
%FacePulseRate_CompletionMessage   Display completion message when function FacePulseRate has
%                                  completed operations.
%
%    Helper function to function FacePulseRate.
%
%    Copyright (c) Douglas Magill(dpmdpm@vt.edu), June, 2020. Licensed under the MIT License and  
%    the Responsible AI License (RAIL).


%Display function completion message:

message = '\nOperation completed for file:';

fprintf(message);
fprintf('\n    '); %new line, indent

%Write a directory without escape characters
fprintf('%s\n', string(VideoReadConfig.Video_InputFile)); 

%Display message immediately
drawnow();

%Calculate elapsed time for function and convert to min/sec format:

%Stop timer
FunctionTimeElapsed = toc(FunctionStartTime); 

%Find number of full minutes 
FunctionTimeElapsed_Minutes = floor(FunctionTimeElapsed / 60);    

%Seconds that don't fall completely into a full minute; round to integer
FunctionTimeElapsed_Sec = round( rem(FunctionTimeElapsed, 60) ); 

%Combine minutes and seconds
FunctionTimeElapsed_MinSec = ...
    [num2str(FunctionTimeElapsed_Minutes), ' min, ', ...
     num2str(FunctionTimeElapsed_Sec), ' sec']; 

%Display elsapsed time for function and ratio of processing length to input video length
fprintf( ...
    ['\n    Total time elapsed: ', FunctionTimeElapsed_MinSec, ...
     '\n    Ratio of processing length to input video length: ', ... 
     num2str( ...
        FunctionTimeElapsed / (max(VideoReadConfig.FrameTimestamp_Single) - ...
        min(VideoReadConfig.FrameTimestamp_Single)) ...
     ), ...
     '\n'] ...
);
     
%Display message immediately    
drawnow(); 


end %end function

