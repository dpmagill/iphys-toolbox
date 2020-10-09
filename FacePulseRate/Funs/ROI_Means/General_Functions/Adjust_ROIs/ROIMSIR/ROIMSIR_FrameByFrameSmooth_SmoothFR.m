function ROIOut_FR = ...
             ROIMSIR_FrameByFrameSmooth_SmoothFR(ROIOut_FR, ROIBlockFrameByFrameSmooth, ...
                 RowToReturnFullLinIdx_FR, RowToReturnBlockLinIdx_FR, FramesBeforeFirstCallTF, ...
                 FirstFrameMSIRBlockLinIdx, ROIBlockDetectionFaceSkinLinIdx, ...
                 NDetectionsFaceSkin, ROINoPrevCallsBlock, ROINoResizeBlock_FR, ROIBlock, ...
                 PrevToCurrentBlockLinIdx, NPrevToCurrentBlockLinIdx, ...
                 FrameByFrameSmoothingWin_XYHalf, FrameByFrameSmoothingWin_WHHalf, ...
                 VideoReadConfig_FrameIdx_FR, ExpectedBehaviorTestTF) %#codegen                 
%ROIMSIR_FrameByFrameSmooth_SmoothFR    Frame-by-frame smoothing of ROIs for first-read operations.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function ROIMSIR_FrameByFrameSmooth.
%
%
%    Code Generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.                                                                         
%
%   
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code-generation settings %%%%%%

%Inline function
coder.inline('always');

%Call function as extrinsic
%See notes where warning() used.
coder.extrinsic('warning');
    
%Call function as extrinsic so that stack trace can be displayed
coder.extrinsic('error');

%Declare variables:

%Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
%variable were to change, the constant would need to be modified.

%                                                  Upp. Bounds  Var. Size (T/F)
coder.varsize('FrameByFrameSmoothingWin_XYLinIdx', [1, 229],    [0, 1]);
coder.varsize('FrameByFrameSmoothingWin_WHLinIdx', [1, 229],    [0, 1]);


%%%%%% Input validation %%%%%%

%Confirm that RowToReturnBlockLinIdx_FR == 115
%Only in the case of an implementation error would this not be the case.
if RowToReturnBlockLinIdx_FR ~= 115

    %Throw error
    %Called as extrinsic so that stack trace can be displayed.
    error( ...
        'Component:InternalError', ...
        ['Internal Error (ROIMSIR, code 21.5): The block index of the row-to-return does not', ...
         ' equal 115. The frame index of the frame is: ', ...
         sprintf( '%d', int32( VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ... 
        '. Smoothing accuracy may be affected. Detected within function ROIMSIR in function', ... 
        ' ROIMSIR_FrameByFrameSmooth_SmoothFR.'] ...
    );  

    %Note: if this error is thrown, then find all values of 115 in the code in this file and 
    %replace with the value of RowToReturnBlockLinIdx_FR.
end             


%%%%%% Insert ROIs corresponding to frames before current frame %%%%%%

%If block contains ROIs before first function call to ROIMSIR  
if FramesBeforeFirstCallTF 

    %Insert ROIs corresponding to frames before first function call to ROIMSIR that have a 
    %detection.

    %If at least one ROI in block with a detection
    if NDetectionsFaceSkin > 0

        %Linear index of frames before first call that have a detection
        %Column vector; type double.
        ROIBlockBeforeFirstCallDetectionLinIdx = ...
            ROIBlockDetectionFaceSkinLinIdx( ...
                ROIBlockDetectionFaceSkinLinIdx < FirstFrameMSIRBlockLinIdx ...
            ); 

        %Insert ROIs corresponding to frames before first function call that have a detection. 
        %Type int16.
        %Note: these are not the final version of these ROIs; these ROIs will not be finalized
        %until they are reprocessed in function ROIMeans_SecondRead. They may approximate the final
        %ROIs because they were size-matched and smoothed in functions ROIMSIR_SizeMatch and   
        %ROIMSIR_DetectionSmooth, respectively. 
        %M x 4 matrix; type int16.
        ROIBlockFrameByFrameSmooth(ROIBlockBeforeFirstCallDetectionLinIdx, :) = ...
            ROINoPrevCallsBlock(ROIBlockBeforeFirstCallDetectionLinIdx, :); 
    end                

    %Insert ROIs for frames before current frame that were processed by previous calls
    %These may come from a detection or come from interpolation / extrapolation from a previous
    %call.
    %Note: these are the final version of these ROIs.

    %Assert length to prevent dynamic memory allocation for colon operator
    %Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
    %variable were to change, the constant would need to be modified.
    assert(RowToReturnBlockLinIdx_FR <= 229);
    
    %M x 4 matrix; type int16.    
    ROIBlockFrameByFrameSmooth(FirstFrameMSIRBlockLinIdx : RowToReturnBlockLinIdx_FR - 1, :) = ...
        ROIBlock(FirstFrameMSIRBlockLinIdx(1) : RowToReturnBlockLinIdx_FR - 1, :);               

%If block does not contain ROIs before first function call    
else

    %Insert ROIs for frames before current frame that were returned by previous calls to function
    %ROIMSIR. Use the version of the ROIs that were not resized. The ROIs before resizing are used 
    %because the target ROI has not yet been resized (it will be in the final step of function 
    %ROIMSIR).
    
    %ROIs from previous calls without resizing
    ROINoResizeBlock_Previous = ...
        ROINoResizeBlock_FR( ...
            1 : RowToReturnBlockLinIdx_FR - 1, ...
            : ...
        );
    
    %Insert these ROIs into matrix used in interpolation / extrapolation
    %Note: these are the final version of these ROIs.             
    ROIBlockFrameByFrameSmooth(1 : RowToReturnBlockLinIdx_FR - 1, :) = ...
        ROINoResizeBlock_Previous;                                    
end


%%%%%% Insert ROI corresponding to current frame %%%%%%      

%229 x 4 matrix; type int16.
%Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
%variable were to change, the constant would need to be modified.
ROIBlockFrameByFrameSmooth(RowToReturnBlockLinIdx_FR, 1 : 4) = ROIOut_FR(1 : 4);


%%%%%% Insert ROIs corresponding to frames after current frame that have a detection %%%%%%               

%Insert ROIs corresponding to detections for frames after current frame
%Note: ROIs have only been modified in the current function and not in previous calls to the 
%function; this removes the positive-feedback loop effect (see note in the file for function 
%ROIMSIR). 

%Linear index of detections present in frames after current frame
%Note: SetDiff is a custom function located within folder 'FacePulseRate'.
ROIBlockPostDetectionFaceSkinLinIdx = ...
    SetDiff(ROIBlockDetectionFaceSkinLinIdx, NDetectionsFaceSkin, PrevToCurrentBlockLinIdx, ...
        NPrevToCurrentBlockLinIdx);

%Insert ROIs from detections after current frame 
%M x 4 matrix; type int16.
if ~ isempty(ROIBlockPostDetectionFaceSkinLinIdx)

    ROIBlockFrameByFrameSmooth(ROIBlockPostDetectionFaceSkinLinIdx, :) = ...
        ROINoPrevCallsBlock(ROIBlockPostDetectionFaceSkinLinIdx, :); 
end


%%%%%% Error checking %%%%%%               

%Verify that ROIs to be included in smoothing do not contain zeros
%The smoothing operation is intended to be conducted only on non-zeros ROIs. Such a value is likely
%due to an implementation error in this function.

%Loop across elements
%Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
%variable were to change, the constant would need to be modified.
for i = 1 : int32(4) * int32(229)
           
    if ROIBlockFrameByFrameSmooth(i) == 0 

        %Throw exception
        %Called as extrinsic so that stack trace can be displayed.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 22): Smoothing operation conducted with ROIs', ...
             ' that contain zeros at frame ', ...
             sprintf( '%d', int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ...
             '. Smoothing accuracy may be affected. Detected within function ROIMSIR in', ... 
             ' function ROIMSIR_FrameByFrameSmooth_SmoothFR.'] ...
        );            
    end
end 

%Check whether the ROI size is unreasonably small
%Such a small size is likely due to an implementation error in this function.
%This check is intended to be run when testing new implementations, as small ROI sizes are an
%indication of a implementation error. As occassional values below 20 may be considered
%acceptable, this check is not intended for use outside of testing. "Occassional" in this case   
%might be defined as a few occurances out of 10,000. Flag ExpectedBehaviorTestTF enables the
%check.
if ExpectedBehaviorTestTF && ...
   any( ROIBlockFrameByFrameSmooth(:, 3 : 4) < 20, 'all' ) 

    %Display warning indicating frame index

    %Note: function warning() not available for code generation, so it must have previously been
    %declared as extrinsic.
    %Function fprintf can not be used as a substitute for warning() in this case because fprintf 
    %can not accept variable-length arguments.       
    warning( ...
        'Component:InternalError', ...
        ['Potential Internal Error (ROIMSIR, code 23): Smoothing operations conducted with', ...
         ' ROIs with size values below 20 pixels, which is likely inaccurate. ROI accuracy', ...
         ' may be affected. The frame index of corresponding frame is: ', ...
         sprintf( '%d', int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ... 
         '. Detected within function ROIMSIR in function ROIMSIR_FrameByFrameSmooth_SmoothFR.'] ...         
    ); 
end         


%%%%%% Smooth target ROI X- and Y-coordinates %%%%%%

%Smooth X- and Y-coordinates with mean
%Equivalent to moving-mean smoothing but for a single ROI.

%Linear index of X- and Y-coordinates to smooth
%Row vector; type int32.

%Note: using a constant rather than a variable may prevent dynamic memory allocation from the colon
%operator.
%115 is a constant, which represents RowToReturnBlockLinIdx_FR.

%Assert length to prevent dynamic memory allocation for colon operator
assert(FrameByFrameSmoothingWin_XYHalf < 115);

%Case with variable
%FrameByFrameSmoothingWin_XYLinIdx = ...
%    RowToReturnBlockLinIdx_FR - FrameByFrameSmoothingWin_XYHalf : ...
%    RowToReturnBlockLinIdx_FR + FrameByFrameSmoothingWin_XYHalf;

%Case with constant
FrameByFrameSmoothingWin_XYLinIdx = ...
    115 - FrameByFrameSmoothingWin_XYHalf : ...
    115 + FrameByFrameSmoothingWin_XYHalf;

%Length of vector FrameByFrameSmoothingWin_XYLinIdx
N = FrameByFrameSmoothingWin_XYHalf * int32(2) + int32(1);

%Assert length to prevent dynamic memory allocation for colon operator
assert(N <= 229);

%Columns means of X and Y columns:

%Initialize sum accumulators
%Note: for accumulating across 229 rows, type int32 is not expected to overflow.
SumX = int32(0);
SumY = int32(0);

for j = 1 : N

    jj = FrameByFrameSmoothingWin_XYLinIdx(j);        

    %Convert from subscript indices to a linear index for more efficient indexing
    %Scalar; type int32.
    
    %Accumulate
    %Cast to type int32 to avoid overflow with type int16.
    %Index using a linear index rather than subscripts; In compiled C code, the faster indexing 
    %outweighs the cost of the conversion.
    %Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
    %variable were to change, the constant would need to be modified.
    SumX = SumX + int32( ROIBlockFrameByFrameSmooth(jj) );       %subscript indexing: (j, 1)      
    SumY = SumY + int32( ROIBlockFrameByFrameSmooth(jj + 229) ); %subscript indexing: (j, 2)            
end   

%Take means
ROIOut_FR(1) = SumX / N;
ROIOut_FR(2) = SumY / N;                  


%%%%%% Smooth target ROI width and height %%%%%% 

%%%%%% --- Smooth with moving median to apply strong smoothing to widths and heights %%%%%%

%Assign unsmoothed widths and heights for later step 
%1 x 2 row vector; type int16.
ROIWidthHeightPreSmooth = ROIOut_FR(3 : 4);

%Linear index of width and height to smooth
%Row vector; type int32.

%Note: using a constant rather than a variable may prevent dynamic memory allocation from the colon
%operator.
%115 is a constant, which represents RowToReturnBlockLinIdx_FR.

%Also use assert to prevent dynamic memory allocation from the colon operator.
assert(FrameByFrameSmoothingWin_WHHalf < 115);

%Case with variable
%FrameByFrameSmoothingWin_WHLinIdx = ...
%    RowToReturnBlockLinIdx_FR - FrameByFrameSmoothingWin_WHHalf : ...
%    RowToReturnBlockLinIdx_FR + FrameByFrameSmoothingWin_WHHalf;

%Case with constant
FrameByFrameSmoothingWin_WHLinIdx = ...
    115 - FrameByFrameSmoothingWin_WHHalf : ...
    115 + FrameByFrameSmoothingWin_WHHalf;

%Length of vector FrameByFrameSmoothingWin_WHHalf
WHLinIdx_Length = single( FrameByFrameSmoothingWin_WHHalf * int32(2) + int32(1) ); 

%Smooth width and height with median
%Equivalent to moving-median smoothing but for a single ROI. 
%1 x 4 row vector; type int16.
%Local function.
ROIOut_FR(3 : 4) = ...
    medianByColumn( ... 
        ROIBlockFrameByFrameSmooth(FrameByFrameSmoothingWin_WHLinIdx, 3 : 4), ...
        WHLinIdx_Length, ... number of rows
        2                ... number of columns
    );  

%%%%%% --- Resmooth widths and heights to remove any sudden jumps %%%%%%  

%Resmooth to reduce sudden changes due to the moving-median smoothing.
%Smooth using ROIs from immediately previous ROIs (these ROIs were returned by previous calls to
%function ROIMSIR). Use ROIs from ROINoResizeBlock_FR because these ROIs were not resized; 
%non-resized ROIs are used because the target ROI has not yet been resized (it will be in the final 
%step of function ROIMSIR).
%Use window of 3.    

%Linear index of previous ROIs to include in resmoothing
%1 x 2 row vector; type int32.
%Note: using a constant rather than a variable prevents dynamic memory allocation from the colon
%operator.

%Case with variable
%ResmoothWHLinIdx = RowToReturnBlockLinIdx_FR - 2 : RowToReturnBlockLinIdx_FR - 1;

%Case with constant
ResmoothWHLinIdx = 115 - 2 : 115 - 1;

%Only resmooth if the ROIs in ROINoResizeBlock_FR corresponding to the resmoothing index have been  
%previously processed by the function. Otherwise, the ROIs corresponding to the index might have   
%values of zero. This logical value will only be false on two occassions (two is the length of the 
%resmoothing index)
if ResmoothWHLinIdx(1) >= FirstFrameMSIRBlockLinIdx

    %Preallocate ROI matrix for use in resmoothing
    %3 x 2 matrix; type int16.
    ResmoothWHROIBlock = coder.nullcopy( zeros(3, 2, 'int16') );

    %Insert widths and heights of previous ROIs without resizing into matrix to be used for 
    %resmoothing.
    %Index 1 : 2 assumes two previous ROIs are used.
    ResmoothWHROIBlock(1 : 2, :) = ...
        ROINoResizeBlock_FR( ...
            ResmoothWHLinIdx, ...
            3 : 4 ...
        );   

    %Insert widths and heights of target ROI into matrix to be used for resmoothing
    %Index 3 assumes span of 3.
    ResmoothWHROIBlock(3, :) = ROIOut_FR(3 : 4);                       

    %Remooth target ROI width and height with mean
    %Similar to moving-mean smoothing but for a single ROI.
    %1 x 4 row vector; type int16. 
    for i = 1 : 2

        %Initialize sum accumulator
        %Note: as only three rows are accumulated, type int16 is not expected to overflow. 
        Sum = int16(0);
        
        for j = 1 : 3
 
            %Accumulate
            Sum = Sum + ResmoothWHROIBlock(j, i);           
        end
        
        %Take mean
        ROIOut_FR(i + 2) = Sum / int16(3);        
    end     
end


%%%%%% Adjust X- and Y-coordinates to correspond to adjustments in width and height %%%%%%

%Loop across X and Y columns
for i = 1 : 2
    
    %1 x 4 row vector; type int16.
    ROIOut_FR(i) = ...
        ... Add the half-difference to the X- or Y-coordinate
        ... (If there were a negative difference, this would imply the abs value of the
        ROIOut_FR(i) + ...
        ... Take half of the difference (optimize division by 2 with bit-wise division)
        bitshift( ...
            ... Difference between unsmoothed width and height and smoothed width and height
            ROIWidthHeightPreSmooth(i) - ROIOut_FR(i + 2), ...
            -1 ... 
        );
end


end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function ROIMedian = medianByColumn(ROIs, nRows, nCols)
%medianByColumn   Find the median of each column.
%                                
%    Notes: 
%
%    Adapted from the Matlab function 'median'.
%
%    This function relies on the maximum value of an ROI being 16384. This is because the data type  
%    used for the ROI is int16, which has a maximum value of 32768. In order to allow two variables
%    to be added without exceeding 32768, the maximum value may be half of 32768 (16384). This 
%    constraint is noted in the description of function FacePulseRate; if the current function is 
%    to be removed, the description in function FacePulseRate should be modified.


%Inline function
coder.inline('always');


%Sort by column
ROIs = sort(ROIs, 1); 

%Center row
centerRow = int32( floor(nRows / 2) );     

%Median
ROIMedian = ROIs(centerRow + 1, 1 : nCols);

%If even number of rows
%Optimize multiplication by two using bit-wise division
%Non-optimized: 2 * centerRow == nRows.
if bitshift(centerRow, 1) == nRows
    
    ROIMedian2 = ROIs(centerRow, 1 : nCols);
    
    %Take average of two center rows         
    for i = 1 : nCols       
         
        %Optimize division by two using bit-wise division
        ROIMedian(i) = bitshift( ROIMedian(i) + ROIMedian2(i), -1 );
    end       
end


end %end local function


