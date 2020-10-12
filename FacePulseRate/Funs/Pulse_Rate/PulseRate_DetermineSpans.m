function PulseRateConfigAndData = ...
             PulseRate_DetermineSpans(PulseRateConfigAndData, FrameTimestamp_Double, FS)                
%PulseRate_DetermineSpans   Determine the spans of windows for which pulse rate is to be 
%                           calculated.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function PulseRate.
%
%
%    Description
%    -----------
%
%    Determine the spans of windows for which pulse rate is to be calculated. 
%                           
%    The duration of each window is specified by PulseRateWindowDurationSec, which is an argument  
%    to function FacePulseRate.
%
%    If the duration between BlockTimestampStart and BlockTimestampEnd is not exactly divisible by 
%    PulseRateWindowDurationSec, modifications will be made to the duration(s) of the window(s).
%    
%    In the case where more than one windows fit entirely between BlockTimestampStart and 
%    BlockTimestampEnd, the duration of the first and last windows will be enlarged to fill the 
%    span between BlockTimestampStart and BlockTimestampEnd.
%    
%    In the case of one window, the window will be enlarged or reduced to be equal to the span
%    between BlockTimestampStart and BlockTimestampEnd. If the span exceeds the duration of 
%    PulseRateWindowDurationSec, a window may contain frames one less than twice the frames
%    expected to fill the duration specified by PulseRateWindowDurationSec, that is,  
%    2 * (FS * PulseRateWindowDurationSec) - 1; a window will not contain fewer frames than
%    FS * PulseRateWindowDurationSec. If the span between BlockTimestampStart and BlockTimestampEnd  
%    is less than the duration of PulseRateWindowDurationSec, the window will be reduced. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%If blocks not assigned, use first and last timestamp as startpoint and endpoint for a single block
if isempty(PulseRateConfigAndData.BlockTimestamps)
    
    PulseRateConfigAndData.BlockTimestamps = ...
        [FrameTimestamp_Double(1), FrameTimestamp_Double(end)];
end 
    

%%%%%% Rearrange and check that blocks are within first and last timestamp %%%%%%   
   
%Convert the block timestamps to an m-by-2 matrix:   

%Logical index
Col1Idx = repmat([true, false], 1, length(PulseRateConfigAndData.BlockTimestamps) / 2);
Col2Idx = ~ Col1Idx;

%Rearrange to m-by-2
%Type double.
BlockTimestampsMx2(:, 1) = PulseRateConfigAndData.BlockTimestamps(Col1Idx);
BlockTimestampsMx2(:, 2) = PulseRateConfigAndData.BlockTimestamps(Col2Idx);

%Modify starting timestamp of first block to start not sooner than first available timestamp
if BlockTimestampsMx2(1, 1) < FrameTimestamp_Double(1)

    BlockTimestampsMx2(1, 1) = FrameTimestamp_Double(1);        
end

%Modify ending timestamp of last block not to end later than last available timestamp
if BlockTimestampsMx2(end, 2) > FrameTimestamp_Double(end)

    BlockTimestampsMx2(end, 2) = FrameTimestamp_Double(end);        
end

%If any blocks still contain timestamps outside of video timestamps, throw exception.
if any( BlockTimestampsMx2(:) < FrameTimestamp_Double(1) )  || ...
   any( BlockTimestampsMx2(:) > FrameTimestamp_Double(end) )
   
    ME = ...
        MException('Component:pulserate', ...
             ['Error: Blocks specified for pulse rate contain timestamps', ...
              ' not available in input video,']);
          
    throw(ME);       
end    


%%%%%% Loop across blocks %%%%%%

%Specify number of blocks
PulseRateConfigAndData.nBlocks = size(BlockTimestampsMx2, 1);

%Preallocate for loop
PulseRateConfigAndData.Block = ...
    struct( 'nWindows', cell(size(BlockTimestampsMx2, 1), 1), ...
            'windowsStartIdx', cell(size(BlockTimestampsMx2, 1), 1), ...
            'windowsEndIdx', cell(size(BlockTimestampsMx2, 1), 1) ...
    );
        
%Loop across blocks
for i = 1 : size(BlockTimestampsMx2, 1)

    BlockTimestampStart = BlockTimestampsMx2(i, 1); %type double
    BlockTimestampEnd   = BlockTimestampsMx2(i, 2); %type double
    
    %Determine pulse rate windows. See the function description for details. 

    %If block duration is less than the duration of PulseRateConfigAndData.WindowDurationSec, use  
    %block duration as duration of window.
    if BlockTimestampEnd - BlockTimestampStart < PulseRateConfigAndData.WindowDurationSec

        PulseRateWindowDurationSec_ith = BlockTimestampEnd - BlockTimestampStart;
        
    else
        
        PulseRateWindowDurationSec_ith = PulseRateConfigAndData.WindowDurationSec;
    end

    %Specify the length of each window (in frames)
    %Use floor() to round to integer.
    %Type int32.
    windowLength = ...
        int32( ...
            floor( PulseRateWindowDurationSec_ith * double(FS) ) ...
        );

    %Ensure window length does not exceed block frames:
    
    %Type double.
    BlockTimestamps = ...
        FrameTimestamp_Double(...
            FrameTimestamp_Double >= BlockTimestampStart & ...
            FrameTimestamp_Double <= BlockTimestampEnd ...
        );
    
    %Type int32.               
    windowLength = min( int32(length(BlockTimestamps)), windowLength );

    %Determine the number of windows (as integer)
    %The number of windows is based on the number of frames and the specified length of windows.
    %Round down so that if the last window is not a full window, this window will not be included;
    %if this is the case, the second to last window will become enlarged by the size of the last 
    %window. Use windowLength as floating point to permit use of function floor.
    %Type int32.
    nWindows = ...
        int32( ...
            floor( length(BlockTimestamps) / double(windowLength) ) ...
        );

    %Determine the number of frames that didn't fit into a window
    %Type int32.
    remainder = rem( length(BlockTimestamps), windowLength );

    %Distribute the number of frames that didn't fit into a window to first and last windows
    %If all frames fit, distributeFirstWindow and distributeLastWindow will be zero.
    if rem(remainder, 2) == 0  %If number of these windows is even

        %Evenly distribute these windows between the first and last windows
        %Type int32.
        distributeFirstWindow = remainder / 2;
        distributeLastWindow  = remainder / 2;

    else %If number of these windows is odd   

        %Divide these windows by 2 and round to integer; place this number in first window
        %This could result in the first window having more or fewer windows than the last window;
        %which gets more is arbitrary.
        %Type int32.
        distributeFirstWindow = remainder / 2; 

        %Place the remaining number of windows in last window
        %Type int32.
        distributeLastWindow = remainder - distributeFirstWindow;   
    end

    %Assign vector of frame indices of the ending positions of windows
    %This will be a scalar if only one window.
    %Also add the number of windows that didn't fit (which could be none), as determined  
    %previously, into first window.
    %Type int32.
    
    [~, windowsStartIdx1] = min( abs( FrameTimestamp_Double - BlockTimestamps(1) ) );    
    
    windowsEndIdx = ...
        int32( ...
              windowsStartIdx1 - 1  + windowLength + distributeFirstWindow           ... ending frame index of first window
            : windowLength                                                           ... sequence of intervals of windowsLength
            : windowLength * nWindows + windowsStartIdx1 - 1 + distributeFirstWindow ... ending frame index of last window  
        );

    %Add the number of windows (which could be zero) that didn't fit, as determined previously, 
    %to last window (which could also be the only window if only one window).
    windowsEndIdx(end) = windowsEndIdx(end) + distributeLastWindow;

    %Assign vector of frame indices of the starting positions of windows
    %This will be a scalar if only one window.
    %For the first window, the starting frame index is 1.
    %For the other windows (if more than one), the starting frame indices are indices of the ending 
    %positions of the previous windows + 1.  
    %Type int32.
    windowsStartIdx = ...
        int32( ...
            [windowsStartIdx1, windowsEndIdx(1 : length(windowsEndIdx) - 1) + 1] ...
        );
    
    %Assign the number of windows and the starting and ending timestamps for the ith block  
    %Type int32.
    PulseRateConfigAndData.Block(i).nWindows = nWindows;
    PulseRateConfigAndData.Block(i).windowsStartIdx = windowsStartIdx;
    PulseRateConfigAndData.Block(i).windowsEndIdx = windowsEndIdx;
    
end %end for


end %end function

