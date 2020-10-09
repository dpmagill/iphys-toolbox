function [BlockFullLinIdx_FR, ROI, ROINoMods, ROINoResize, HasROI_TF, ...
          VideoReadConfig_FrameIdx_FR, Timestamp] = ...
             ROIMSIR_Optimize(BlockFullLinIdx_In, ROI, ROINoMods, ROINoResize, HasROI_TF, ...
                 VideoReadConfig_FrameIdx_FR, Timestamp) %#codegen
%ROIMSIR_Optimize   Artificially increase the span of BlockFullLinIdx_In to accommodate a fixed  
%                   memory allocation size. 
%                   
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function ROIMSIR.
%
%
%    Code Generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.
%
%
%    Description
%    -----------
%
%    During the first-read operations, artificially increase the span of BlockFullLinIdx_In when it   
%    is less than a specified length so that its length is always fixed. Using a fixed size for 
%    this variable allows many operations to avoid the use of dynamically-allocated memory and use
%    fixed-sized variables, increasing efficiency.        
%
%    -- Overview of Optimization --
%
%    To increase efficiency of the compiled version of function ROIMSIR (ROIMSIR_mex), ROIMSIR was 
%    developed so that the first-read operations take an execution path separate from the 
%    second-read operations. Separate execution paths were developed so that Matlab code generation 
%    can make separate functions for each path (termed "function specialization") if doing so 
%    increases efficiency. Efficiency gains are typically made by reducing instances where dynamic
%    memory allocattion needs to be used and through the use of fixed-sized variables.
%      
%    The execution path of the first-read operations was developed such that variable 
%    BlockFullLinIdx_FR is always a fixed-length. If always a fixed length, dynamic memory 
%    allocation does not need to be used and fixed-size variables can be utilized. Moreover, many 
%    variables along the execution match the length of this variable, so they, too, do not need to  
%    use dynamic memory allocation and can utilize fixed-size variables. Although there is a cost 
%    to the modifications to variables conducted in this function to facilitate fixed-size 
%    variables, this cost only occurs for the final 228 frames of the input video, which is likely
%    a small portion of the input video.    
%
%    Second-read operations require a variable- length version of BlockFullLinIdx_FR 
%    (BlockFullLinIdx_SR), so second-read operations use a separate execution path to accommodate  
%    this and avoid placing this requirement on first-read operations.  However, note that although 
%    first-read and second-read operations use separate execution paths using different variable 
%    sizes, they actually undergo the same operations in most cases. 
%     
%    -- Implementation Safeguards and Notes --
%
%    BlockFullLinIdx_FR indexes into the other input variables, and they should be of a length 
%    long enough to accommodate the increase in the index. However, in case they are not (likely
%    because of an upstream implementation change), the function will verify their length and 
%    increase it if needed. 
%
%    This optimization has only been implemented for first-read operations, where the length of the
%    span is expected to be increased only on the right of (greater than) RowToReturnFullLinIdx. 
%    That is, the portion of the span that will need to be increased will only come at the end of 
%    the video. This optimization is not implemented for extending the span on the left of (less 
%    than) RowToReturnFullLinIdx (at the beginning of the video).  This is not expected to the case
%    because function ROIMeans_FirstRead_TakeMeans is implemented not to call this function until
%    the left-side span is at full length.
%
%    The value 229 seen throughout the function is the number of ROIs used during the first-read 
%    operations. This number is determined by the number of ROIs available ahead of the current 
%    ROI, which is determined by the lag between the frame-reading operations and the ROI-means
%    operations (for details, see the file for function ROIMeans_FirstRead_TakeMeans). 
%    Specifically, to use an equal number of ROIs on either side of the current ROI, the number of
%    ROIs used before the current ROI is kept equal to the number used after, or 
%    (ROIGeneralConfig.ROIMeansOperationsLag - 1) * 2 + 1. If 
%    ROIGeneralConfig.ROIMeansOperationsLag is modified (for an implementation change), the value
%    229 should be increased if ROIGeneralConfig.ROIMeansOperationsLag is made larger; doing so 
%    would allow all the available ROIs to be used. If ROIGeneralConfig.ROIMeansOperationsLag is
%    made smaller, then the value 229 should be decreased; otherwise, there will not be ROIs
%    available where indexed. If the value is changed, function ROIMSIR would need to be 
%    recompiled.
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

%Call function as extrinsic so that stack trace can be displayed
coder.extrinsic('error');


%%%%%% Validate inputs %%%%%%

%The left-side span of BlockFullLinIdx_In should be at full length.
%If not, an implementation error has likely occurred. 

%Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
%variable were to change, the constant would need to be modified.

%Optimize division by 2 by bit-wise division
if min(BlockFullLinIdx_In) < bitshift( (229 + 1), -1 )         

    %Throw exception
    %Called as extrinsic so that stack trace can be displayed.
    error( ...
        'Component:InternalError', ...
        ['Internal Error (ROIMSIR, code 5): BlockFullLinIdx_In not correct size. Detected', ... 
         ' within function ROIMSIR in function ROIMSIR_Optimize.'] ...
    );
end


%%%%%% Increase span of BlockFullLinIdx_FR %%%%%%

%Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
%variable were to change, the constant would need to be modified.

BlockFullLinIdx_FR = coder.nullcopy( zeros(229, 1, 'int32') );

%Build index up from first index of BlockFullLinIdx_In
Idx = int32( BlockFullLinIdx_In(1) ) - 1;

for i = 1 : 229

    Idx = Idx + 1;
    
    BlockFullLinIdx_FR(i) = Idx;   
end


%%%%%% Verify sizes of variables that BlockFullLinIdx_FR indexes and extend if needed %%%%%%

%Some indices of BlockFullLinIdx_FR will now exceed range of input variables to function ROIMSIR.
%To remedy this, increase the length of these input variables. Function ROIMSIR ignores portions of
%variables that were extended this way.

%Note: the extended sizes are not returned as output of ROIMSIR; they are only used within function
%ROIMSIR for the purpose of the optimization.

%Initial measurements:

%Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
%variable were to change, the constant would need to be modified.

BlockFullLinIdx_Max = BlockFullLinIdx_FR(229);

VideoReadConfig_FrameIdx_Length = length(VideoReadConfig_FrameIdx_FR);

%ROI:

ROI_NRow = size(ROI, 1);

if ROI_NRow < BlockFullLinIdx_Max 

    %Extend with zero values; these values will not enter into calculations.
    ROI = [ROI; zeros(BlockFullLinIdx_Max - ROI_NRow, 4, 'int16')];
end

%ROINoMods:

ROINoMods_NRow = size(ROINoMods, 1);

if ROINoMods_NRow < BlockFullLinIdx_Max 

    %Extend with zero values; these values will not enter into calculations.
    ROINoMods = [ROINoMods; zeros(BlockFullLinIdx_Max - ROINoMods_NRow, 4, 'int16')];      
end

%ROINoResize:

ROINoResize_NRow = size(ROINoResize, 1);

if ROINoResize_NRow < BlockFullLinIdx_Max 

    %Extend with zero values; these values will not enter into calculations.
    ROINoResize = [ROINoResize; zeros(BlockFullLinIdx_Max - ROINoResize_NRow, 4, 'int16')];      
end

%VideoReadConfig_FrameIdx:

if VideoReadConfig_FrameIdx_Length < BlockFullLinIdx_Max 

    extendBy = BlockFullLinIdx_Max - VideoReadConfig_FrameIdx_Length;
 
    %Extend with linearly increasing integers; these values will enter into calculations (used 
    %during extrapolation).
    VideoReadConfig_FrameIdx_FR = ...
        [VideoReadConfig_FrameIdx_FR, ...
         VideoReadConfig_FrameIdx_FR(VideoReadConfig_FrameIdx_Length) + 1 : ...
         VideoReadConfig_FrameIdx_FR(VideoReadConfig_FrameIdx_Length) + extendBy];   
end

%Timestamp:

Timestamp_Length = length(Timestamp);

if Timestamp_Length < BlockFullLinIdx_Max 

    %Type single for compatibility with variable Timestamp.
    extendBy = single(BlockFullLinIdx_Max) - VideoReadConfig_FrameIdx_Length;

    %Extend with linearly increasing values of .05; these values will enter into calculations (used 
    %during extrapolation).
    %Note: .05 is used as a quick substitute of the frate rate.
    Timestamp = ...
        [Timestamp; ...
         ( Timestamp(Timestamp_Length) + .05 : ...
           .05 : ...
           Timestamp(Timestamp_Length) + .05 + .05 * (extendBy - 1) ...
         )'];          
end

%HasROI_TF_NRow:

HasROI_TF_NRow = length(HasROI_TF.FacePrimary); %any field could be used here

if HasROI_TF_NRow < BlockFullLinIdx_Max 

    %Extend with false values; these values will indicate that the zero values added above should
    %not be entered into calculations.
   
    %The names and the number of fields are compile-time constants
    HasROI_TF_Names = coder.const( fieldnames(HasROI_TF) );
    NFields         = coder.const( numel(HasROI_TF_Names) );
    
    for i = 1 : NFields
        
        HasROI_TF.(HasROI_TF_Names{i}) = ... 
            [HasROI_TF.(HasROI_TF_Names{i}); ...
             false(BlockFullLinIdx_Max - HasROI_TF_NRow, 1)];
    end
end
    

end %end function

