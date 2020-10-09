function LoopCounter = ...
             LoopProgressNotification(Interval, LoopFrameIdx, i, LoopStartTime, LoopCounter)
%LoopProgressNotification   Display message while running a loop to update user of loop progress.
%
%    Helper function to function FacePulseRate.
%
%
%    Description
%    -----------
%
%    Display message while running a loop to update user of loop progress.
%
%    Inputs:
%
%       Interval             = Interval of frames iterated that should elapse between each 
%                              notification message is displayed.                             
%       LoopFrameIdx         = A vector of frames numbers (can be non-consecutive).     
%       i                    = Current frame number of loop (can be non-consecutive).
%       LoopStartTime        = Start time as measured immediately before and outside of loop (use
%                              statement loop_start_time = tic). 
%       LoopCounter          = Counter.
%
%    Outputs:
%
%       LoopCounter         = Counter.                              
%      
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%Declare function fprintf as extrinsic for code generation for better compatibility
%Uncomment when generating code.
%coder.extrinsic('fprintf')

%Number of frames in loop
LoopNFrames = length(LoopFrameIdx);

%Current loop iteration
%Note: may not equal frame index if frame index is non-consecutive.
LoopCounter = LoopCounter + 1;

%Display notification if specified frame interval elapsed:
%Check index against specified notification interval
% - check whether index of current frame divisible by interval
if rem(LoopCounter, Interval) == 0 

    %Determine time elapsed:
    time_elapsed_loop = toc(LoopStartTime);

    %Convert time elapsed to minutes and seconds format:
    % - find number of full minutes 
    time_elapsed_loop_min = floor(time_elapsed_loop / 60); 
    % - seconds that don't fall completely into a full minute; round to integer      
    time_elapsed_loop_sec = round( rem(floor(time_elapsed_loop), 60) ); 
    % - combine minutes and seconds as string
    % - conversion to integer required to use %d for codegen
    time_elapsed_loop_minsec = ...
        [sprintf('%d', int64(time_elapsed_loop_min)), ' min, ', ...
         sprintf('%d', int64(time_elapsed_loop_sec)), ' sec']; 

    %Estimate time remaining:
    % - determine rate (seconds per frame)
    n_frames_completed = length(LoopFrameIdx(LoopFrameIdx <= i));
    rate = time_elapsed_loop / n_frames_completed;
    % - determine remaining frames
    n_frames_remaining = length(LoopFrameIdx(LoopFrameIdx > i));
    % - multiply remaining frames length by rate
    est_loop_time_remain = n_frames_remaining * rate; 
    
    %Convert estimated time remaining to minutes and seconds format:
    % - find number of full minutes     
    est_loop_time_remain_min = floor(est_loop_time_remain / 60); 
    % - seconds that don't fall completely into a full minute; round to integer  
    est_loop_time_remain_sec = round( rem(floor(est_loop_time_remain), 60) );
    % - combine minutes and seconds as string
    % - conversion to integer required to use %d for codegen 
    est_loop_time_remain_minsec = ...
        [sprintf('%d', int64(est_loop_time_remain_min)), ' min, ', ...
         sprintf('%d', int64(est_loop_time_remain_sec)), ' sec']; 

    %Prepare notification message:
    %(number of frames processesed out of number of frames in loop;
    %time elapsed in loop; estimated time remaing for loop)
    %Conversion to integer required to use %d for codegen.
    message = ...
        ['\n    ...', sprintf('%d', int64(LoopCounter)), ' of ', sprintf('%d', int64(LoopNFrames)), ' frames processed.', ...
         '\n       ', time_elapsed_loop_minsec, ' elapsed. ', est_loop_time_remain_minsec, ' est. remaining.'];
           
    %Display notification message:
    fprintf(message);
    
    %Display immediately
    drawnow(); 

end %end if


end %end function

