function PulseRateConfigAndData = PulseRate_External(PulseRateConfigAndData, FrameTimestamp)
%PulseRate_External   Adapt provided external pulse rate measurements for comparison to pulse rate
%                     detected from face.
%                      
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function PulseRate.
%
%
%    Description
%    -----------
%
%    Adapt provided external pulse rate measurements for comparison to the pulse rate detected from 
%    the face.                 
%
%    -- Validation performed previously in function validateToolboxesArguments --
%
%    - If PulseRateConfigAndData.ExternallyMeasured is a cell array, PulseRateBlockTimestamps  
%      should be non-empty. Also, PulseRateBlockTimestamps / 2 should be greater than one and equal   
%      to the number of cells in the cell arrary.
%    - If PulseRateConfigAndData.ExternallyMeasured is not a cell array, PulseRateBlockTimestamps 
%      should be empty. 
%    - If PulseRateConfigAndData.ExternallyMeasured is not a cell array, it should be a row- or 
%      column-vector.
%    - If PulseRateConfigAndData.ExternallyMeasured is a cell array, the length across all cells  
%      should be less than or equal to the sum of the durations of each timestamp set.
%    - For both a cell and non-cell array, its length should be less than or equal to the duration
%      of the video.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.

   
%%%%%% Calculate mean of externally-measured pulse rate by block and by window %%%%%%

%%%%%% --- Loop preparation %%%%%%

%Struct to hold mean externally-measured pulse rate by block and by window
%Each row represents a block.
%The vector within each row contains the pulse rates by window.
PRExternal = ...
    struct( ...
        'ByWindow', cell(PulseRateConfigAndData.nBlocks, 1) ...
    );

%PulseRateConfigAndData.ExternallyMeasured is entered by user either as a vector or a cell array.
%A vector indicates blocks are not used; here, this case is treated as 1 block.
%A cell array indicates blocks are used; in this case, there must be more than one block/cell as
%this was validated by function validateToolboxesArguments.
%Whether a vector or cell array is used affects the calculation operation. 

%PulseRateConfigAndData.ExternallyMeasured is not a cell array
%Note: In this case, PulseRateConfigAndData.nBlocks should equal 1.
if ~ iscell(PulseRateConfigAndData.ExternallyMeasured)

    ExternallyMeasured_isCellArrayTF = false;

%PulseRateConfigAndData.ExternallyMeasured is a cell array  
%Note: In this case, PulseRateConfigAndData.nBlocks should be > 1.
else

    ExternallyMeasured_isCellArrayTF = true;       
end

%Loop across blocks
for i = 1 : PulseRateConfigAndData.nBlocks

    %Determine duration (in seconds) of each window in ith block
    %Used to extract externally-measured pulse rate data.
    windowDurations_ithBlock = ...
        round( ...
            FrameTimestamp(PulseRateConfigAndData.Block(i).windowsEndIdx) - ...
            FrameTimestamp(PulseRateConfigAndData.Block(i).windowsStartIdx) ...
        ); 

    %Loop preallocation for ith block
    PRExternal(i).ByWindow = zeros(length(windowDurations_ithBlock), 1);

    %Max index of externally-measured pulse rate
    if ~ ExternallyMeasured_isCellArrayTF %not cell array

        ExternalMaxIdx_ith = length(PulseRateConfigAndData.ExternallyMeasured);

    else %cell array

        ExternalMaxIdx_ith = length(PulseRateConfigAndData.ExternallyMeasured{i});
    end

    %Initiate start index for jth window
    ExtractStart_jthWindow = 1;

    %Loop across windows of ith block
    for j = 1 : PulseRateConfigAndData.Block(i).nWindows

        %Break loop if the start index equals or exceeds the maximum index of the 
        %externally-measured pulse rate variable.
        %This should not occur routinely and is included for robustness.
        if ExtractStart_jthWindow >= ExternalMaxIdx_ith %max index of externally-measured pulse rate

            %Exit loop
            break
        end

        %End index of jth window
        %Whichever is less: the incremental index 
        %(ExtractStart_jthWindow + windowDurations_ithBlock(j)) or the max index available
        %(ExternalMaxIdx_ith).
        ExtractEnd_jthWindow = ...
            min( ...
                ExtractStart_jthWindow + windowDurations_ithBlock(j), ...
                ExternalMaxIdx_ith ... max index of externally-measured pulse rate
            );

        %Extract externally-measured pulse rate corresponding to jth window of ith block:

        %Not cell array 
        %(1 block present)
        if ~ ExternallyMeasured_isCellArrayTF

            DataExternal_jthWindow = ...
                PulseRateConfigAndData.ExternallyMeasured(ExtractStart_jthWindow : ExtractEnd_jthWindow);

        %Cell array
        %(More than 1 block present)
        else

            DataExternal_jthWindow = ...
                PulseRateConfigAndData.ExternallyMeasured{i}(ExtractStart_jthWindow : ExtractEnd_jthWindow);                               
        end

        %Mean of jth window of ith block
        PRExternal(i).ByWindow(j) = mean(DataExternal_jthWindow);

        %Advance start index for next iteration of loop
        ExtractStart_jthWindow = ExtractEnd_jthWindow + 1;             

    end %end jth window
end %end ith block


%%%%%% Assign window pulse rates %%%%%%

PulseRateConfigAndData.PulseRate.PulseRate_External = PRExternal;
          

%%%%%% Assign window pulse rates to correspond to frames %%%%%%

%Preallocate vector to which the pulse rates for each frame will be assigned
%The frames will be assigned the pulse rate of the corresponding window.
%Use type single for memory conservation.
PulseRateConfigAndData.PulseRate.PulseRateExpanded_External = ...
    NaN(length(FrameTimestamp), 1, 'single');

%Loop across blocks
for i = 1 : PulseRateConfigAndData.nBlocks
    
    %Loop across windows to assign pulse rates to frames
    for j = 1 : PulseRateConfigAndData.Block(i).nWindows

        %Assign the pulse rates of the jth window to corresponding frames 
        %Also convert to type single for memory conservation.
        %Note: PulseRateConfigAndData.Block values assigned in function PulseRateAlgorithms.
        PulseRateConfigAndData.PulseRate.PulseRateExpanded_External( ...
            PulseRateConfigAndData.Block(i).windowsStartIdx(j) : PulseRateConfigAndData.Block(i).windowsEndIdx(j) ...
        ) = ...
            single( ...
                repmat( ...
                    PRExternal(i).ByWindow(j), ... mean external pulse rate for jth window
                    length(                    ... rows: repeat by length of jth window
                        PulseRateConfigAndData.Block(i).windowsStartIdx(j) : ...
                        PulseRateConfigAndData.Block(i).windowsEndIdx(j) ...
                    ), ...
                    1 ... column: 1 column
                ) ...                   
            );            
    end 
end


end %end function

