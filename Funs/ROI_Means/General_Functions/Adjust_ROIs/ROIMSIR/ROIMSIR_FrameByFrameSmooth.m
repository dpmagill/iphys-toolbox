function [ROIOut_FR, ROIOut_SR, ROIOutBeforeFrameByFrameSmoothing_FirstRead, ...
          ROIOutBeforeFrameByFrameSmoothing_SecondRead] = ...
             ROIMSIR_FrameByFrameSmooth(ROIOut_FR, ROIOut_SR, ROINoPrevCallsBlock, ...
                 NoPrevCallsBlock_ROIDetections, ROINoResizeBlock_FR, BlockFullLinIdx, ...
                 ROIBlockDetectionFaceSkinLinIdx, NDetectionsFaceSkin, ...
                 ROIBlockNoDetectionFaceSkinLinIdx, NNoDetectionsFaceSkin, ROIBlock, ... 
                 TimestampBlock, TimestampBlockDetections, ...
                 ROIGeneralConfig_ROIFinalSmoothingWindows, VidObjWidth, VidObjHeight, ...
                 FirstReadTF, VideoReadConfig_FrameIdx_FR, RowToReturnFullLinIdx_FR, ...
                 RowToReturnBlockLinIdx_FR, ROIMSIR_FirstFrameLinIdx_FR, ...                 
                 ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...
                 ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, ExpectedBehaviorTestTF) %#codegen       
%ROIMSIR_FrameByFrameSmooth    Conduct frame-by-frame smoothing of ROIs.
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
%    Smooth with nearby frames regardless of whether a face-detection or skin-detection algorithm
%    detection is present in a given nearby frame. That is, include nearby frames even if they have
%    been interpolated or extrapolated rather than contain an ROI from a detection. The objective 
%    is to increase stability in position (X- and Y-coordinates) and size (width and height)
%    across frames. The stability should better reflect actual head movements rather than sudden
%    movements caused by extraneous factors, such as differences in ROIs due to the use of
%    different algorithms or artifacts introduced by the previous smoothing and interpolation 
%    operations. At the same time, over-smoothing should be avoided to allow the ROI to be 
%    responsive to actual head movements across frames.
%
%    At the point of the current frame, the final ROI values are known only for previous frames 
%    (ROI values before the current frame in ROIBlock). To conduct frame-by-frame smoothing as if  
%    both previous and later ROI values were known, later ROI values are interpolated / 
%    extrapolated for the purpose of frame-by-frame smoothing. Any ROIs values interpolated /  
%    extrapolated for this purpose are not recorded.
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

%Declare variable-size variables:

%Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
%variable were to change, the constant would need to be modified.

%                                                         Upp. Bounds  Var. Size (T/F)
coder.varsize('FrameByFrameSmoothingWin_XYLinIdx',        [1, 229],    [0, 1]);
coder.varsize('FrameByFrameSmoothingWin_WHLinIdx',        [1, 229],    [0, 1]);


%%%%%% Input validation %%%%%%

%Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
%variable were to change, the constant would need to be modified. If changed to be longer, the  
%bounds on variables FrameByFrameSmoothingWin_XYLinIdx and FrameByFrameSmoothingWin_WHLinIdx should 
%be increased. A low value is currently used to avoid dynamic memory allocation in several 
%variables. The value was determined based upon the maximum length of the frame cache (see function 
%ROIMeans_FirstRead_TakeMeans). An error from these assert statements would likely be due to an
%implementation error because input checking is conducted at the beginning of function
%FacePulseRate.
assert( ROIGeneralConfig_ROIFinalSmoothingWindows(1) <= 229 );
assert( ROIGeneralConfig_ROIFinalSmoothingWindows(2) <= 229 );


%%%%%% Specify smoothing windows %%%%%%

%Specify X- and Y-coordinate smoothing window
%Type int32.
FrameByFrameSmoothingWin_XY = ROIGeneralConfig_ROIFinalSmoothingWindows(1);

%Specify width and height smoothing window
%Type int32.
FrameByFrameSmoothingWin_WH = ROIGeneralConfig_ROIFinalSmoothingWindows(2);

%Smoothing windows for use in first-read operation:

%Assign half value of smoothing widths for use in some operations
%This is only for convenience; the actual smoothing widths remain the same.
%Type int32.
FrameByFrameSmoothingWin_XYHalf = floor( (FrameByFrameSmoothingWin_XY - 1) / 2 );
FrameByFrameSmoothingWin_WHHalf = floor( (FrameByFrameSmoothingWin_WH - 1) / 2 );


%%%%%% Assign variables %%%%%%

%First-read operations
if FirstReadTF
    
    %Record ROIs not smoothed by the frame-by-frame smoothing to diagnose false positives or false  
    %negatives that may have been caused by this smoothing operation. The ROI coordinates will be 
    %superimposed on the output video for assessment.
    %Type int16.
    %1 x 4 row vector; type int16.
    ROIOutBeforeFrameByFrameSmoothing_FirstRead = ROIOut_FR;

    %Variables unused in first-read operations assigned for code generation purposes:
    
    ROIOutBeforeFrameByFrameSmoothing_SecondRead = coder.nullcopy( zeros(0, 4, 'int16') ); 
    
    %Assert row size as zero because this variable not used in first-read operations
    %This may help remove dynamic memory allocation for this variable.
    assert( size(ROIOut_SR, 1) == 0 );    
    
    %If no ROIs within the block correspond to a detection:
    
    %Otherwise, the ROI will have been assigned as the full frame dimensions (see function
    %ROIMSIR_InterpolateFR), and these should not be smoothed.   
    
    if NDetectionsFaceSkin == 0
        
        return
    end      
    
    %Assign previous-to-current-frame block index:
        
    %Type int32.
    %Note: constant 115 assumes that RowToReturnBlockLinIdx_FR == 115. If the value of this
    %variable were to change, the constant would need to be modified.
    PrevToCurrentBlockLinIdx = 1 : int32(115);
 
    %The length of NPrevToCurrentBlockLinIdx.
    %Note: constant 115 assumes that RowToReturnBlockLinIdx_FR == 115. If the value of this
    %variable were to change, the constant would need to be modified.
    %Type int32.
    NPrevToCurrentBlockLinIdx = int32(115);     
    
%Second-read operations
else

    %Record ROIs not smoothed by the frame-by-frame smoothing to diagnose false positives or false  
    %negatives that may have been caused by this smoothing operation. The ROI coordinates will be 
    %superimposed on the output video for assessment.
    %Type int16.
    %M x 4 matrix; type int16.
    ROIOutBeforeFrameByFrameSmoothing_SecondRead = ROIOut_SR;

    %Variables unused in second-read operations assigned for code generation purposes:
    
    ROIOutBeforeFrameByFrameSmoothing_FirstRead = coder.nullcopy( zeros(1, 4, 'int16') );
    
    %Type int32.
    PrevToCurrentBlockLinIdx = 1 : RowToReturnBlockLinIdx_FR;
    
    %The length of NPrevToCurrentBlockLinIdx.
    %Note: constant 115 assumes that RowToReturnBlockLinIdx_FR == 115. If the value of this
    %variable were to change, the constant would need to be modified.
    %Type int32.
    NPrevToCurrentBlockLinIdx = int32(115);    
end

    
%%%%%% First-read operations %%%%%%   

if FirstReadTF

    %Note: the following variables are only used in the first-read operations
    %RowToReturnFullLinIdx  = Linear index of row to return aligned with length of all frames.    
    %RowToReturnBlockLinIdx = Linear index of row to return aligned with length of block.   
    %FirstFrameMSIRLinIdx   = Linear index of ROI processed on first call of functon; aligned with
    %                         length of all frames.          
        
    %To avoid ROIs with zeros entering smoothing operations, interpolation / extrapolation may
    %be required. Linear interpolation / extrapolation requires at least two detections.
    if NDetectionsFaceSkin > 1 
        
        %Note: if a constant-size block is not used (see function ROIMSIR_Optimize), the following
        %checks also need to be conducted:
        %RowToReturnBlockLinIdx_FR > FrameByFrameSmoothingWin_XYHalf    && ... sufficient frames left side
        %RowToReturnBlockLinIdx_FR > FrameByFrameSmoothingWin_WHHalf    && ...
        %RowToReturnBlockLinIdx_FR + FrameByFrameSmoothingWin_XYHalf <= length(BlockFullLinIdx) && ... sufficient frames right side
        %RowToReturnBlockLinIdx_FR + FrameByFrameSmoothingWin_WHHalf <= length(BlockFullLinIdx)        

        %%%%%% --- Determine frames before first call to function that do no have a detection %%%%%%

        %Check whether block contains ROIs of frames for which the current function was not
        %previously called. To do so, determine whether any frames in the current block come before
        %the index specified by FirstFrameMSIRLinIdx; this index specifies the first frame that was
        %called by the function.

        %Of these ROIs, if an ROI does not have a detection, it will be zero as the current 
        %function did not previously apply interpolation / extrapolation to it. These ROIs will be
        %interpolated / extrapolated in function ROIMSIR_FrameByFrameSmooth_Interp.

        %Determine whether any frames in block were not processed by previous calls to the function
        FramesBeforeFirstCallTF = BlockFullLinIdx(1) < ROIMSIR_FirstFrameLinIdx_FR;   

        %Convert linear index of first frame called to align with length of block rather than full 
        %frame index.
        %Type int32.
        FirstFrameMSIRBlockLinIdx = ROIMSIR_FirstFrameLinIdx_FR - BlockFullLinIdx(1) + 1;
        
        %%%%%% --- Preallocate ROI matrix for frame-by-frame smooth %%%%%%

        %Preallocate
        %229 x 4 matrix; type int16.
        %Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of 
        %this variable were to change, the constant would need to be modified.
        ROIBlockFrameByFrameSmooth = coder.nullcopy( zeros(229, 4, 'int16') );
              
        %%%%%% --- Interpolate / extrapolate frames with zeros %%%%%%

        %Frame-by-frame smoothing attempts to smooth across all ROIs. An ROI from any previous  
        %frame can be included because all previous frames will have a non-zero ROI. Specifically, 
        %previous frames without a detection would have received an interpolated/exterpolated ROI       
        %from a previous call to function ROIMSIR_FrameByFrameSmooth. Frames that occur after the  
        %current frame that do not have a detection will contain zeros as interpolation /  
        %extrapolation has not yet been performed on them. To remedy this, perform interpolation /  
        %extrapolation for the frames after the current frame that will be included in the 
        %smoothing. Any ROIs interpolated / extrapolated here will only be used for the purpose of 
        %frame-by-frame smoothing in function ROIMSIR_FrameByFrameSmooth_SmoothFR and will not be 
        %assigned to a persistent ROI matrix.
        
        %229 x 4 matrix; type int16.        
        %Note: ROIMSIR_FrameByFrameSmooth_Interp is a custom function located within folder 
        %'FacePulseRate'.
        ROIBlockFrameByFrameSmooth = ...
            ROIMSIR_FrameByFrameSmooth_InterpFR(ROIBlockFrameByFrameSmooth, ...
                FramesBeforeFirstCallTF, FirstFrameMSIRBlockLinIdx, ...
                ROIBlockNoDetectionFaceSkinLinIdx, NNoDetectionsFaceSkin, ...
                PrevToCurrentBlockLinIdx, NPrevToCurrentBlockLinIdx, ...
                NoPrevCallsBlock_ROIDetections, NDetectionsFaceSkin, ...
                VideoReadConfig_FrameIdx_FR, RowToReturnFullLinIdx_FR, TimestampBlock, ...                
                TimestampBlockDetections, ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...                               
                ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, VidObjWidth, VidObjHeight, ...
                ExpectedBehaviorTestTF); 
                                     
        %%%%%% --- Frame-by-frame smoothing of ROI values %%%%%%   
        
        %1 x 4 row vector; type int16.
        %Note: ROIMSIR_FrameByFrameSmooth_SmoothFR is a custom function located within folder 
        %'FacePulseRate'.
        ROIOut_FR = ...
            ROIMSIR_FrameByFrameSmooth_SmoothFR(ROIOut_FR, ROIBlockFrameByFrameSmooth, ...
                 RowToReturnFullLinIdx_FR, RowToReturnBlockLinIdx_FR, FramesBeforeFirstCallTF, ...
                 FirstFrameMSIRBlockLinIdx, ROIBlockDetectionFaceSkinLinIdx, ...
                 NDetectionsFaceSkin, ROINoPrevCallsBlock, ROINoResizeBlock_FR, ROIBlock, ...
                 PrevToCurrentBlockLinIdx, NPrevToCurrentBlockLinIdx, ...
                 FrameByFrameSmoothingWin_XYHalf, FrameByFrameSmoothingWin_WHHalf,...
                 VideoReadConfig_FrameIdx_FR, ExpectedBehaviorTestTF);                                                                                       
    end   
 
    
%%%%%% Second-read operations %%%%%%   

%To apply smoothing to ROIs only once, the function is called during the second-read operations (by 
%function ROIMeans_SecondRead) only for the post-processing (but not pre-processing) step.    

else
     
    %Number of rows of ROI matrix
    NRows = size(ROIOut_SR, 1);
    
    %Ensure more than one row
    %Note: if a smoothing window is larger than rows available, functions MovMean and movmedian
    %will adjust to actual length.
    %Note: If only one row, Matlab function movmean (not currently used) operates across columns 
    %rather than rows, which is not intended.    
    if NRows > 1

        %%%%%% --- Smooth ROI X- and Y-coordinates with moving mean %%%%%%

        %M x 4 matrix; type int16.               
        %Note: MovMean is a custom function located within folder 'FacePulseRate'.
        ROIOut_SR(:, 1 : 2) = ...
            MovMean( ...
                ROIOut_SR(:, 1 : 2), ...
                FrameByFrameSmoothingWin_XY, ... moving-mean window
                NRows, ... the number or rows of the input matrix
                int32(2) ... the number or columns of the input matrix                
            ); 

        %%%%%% --- Smooth ROI widths and heights %%%%%%

        %Assign unsmoothed widths and heights for later step 
        %M x 2 matrix; type int16.
        ROIWidthHeightPreSmooth = ROIOut_SR(:, 3 : 4);

        %Smooth with moving median to apply strong smoothing to widths and heights:
        
        %M x 4 matrix; type int16.
        ROIOut_SR(:, 3 : 4) = ...
            movmedian( ... returns type double for integer input; converted to type int16 when assigned
                ROIOut_SR(:, 3 : 4), ...
                FrameByFrameSmoothingWin_WH ... moving-median window
            );   

        %Resmooth widths and heights to remove any sudden jumps:  
        
        %Resmooth to reduce sudden changes due to the moving-median smoothing.
        %Use window of 3.
        
        %Smooth with moving mean
        %M x 4 matrix; type int16.
        %Note: MovMean is a custom function located within folder 'FacePulseRate'.
        ROIOut_SR(:, 3 : 4) = ...
            MovMean( ... returns type double for integer input; converted to type int16 when assigned
                ROIOut_SR(:, 3 : 4), ...
                3, ... moving-mean window
                NRows, ... the number or rows of the input matrix
                int32(2) ... the number or columns of the input matrix                  
            );                         
        
        %%%%%% --- Adjust X- and Y-coordinates to correspond to adjustments in widths and heights %%%%%%  

        %Difference between unsmoothed widths and heights and smoothed widths and heights 
        %M x 2 matrix; type int16.
        WidthHeightDiff = ROIWidthHeightPreSmooth - ROIOut_SR(:, 3 : 4);            

        %Take half of the differences
        %M x 2 matrix; type int16.
        %Optimized by bit-wise division.
        %Non-bitwise: WidthHeightDiff = WidthHeightDiff / int16(2);
        WidthHeightDiff = bitshift(WidthHeightDiff, -1);

        %Add the half-differences to the X- and Y-coordinates
        %M x 4 matrix; type int16.
        %Note: if there were negative differences, the half-differences will be subtracted from the
        %X- and Y-coordinates.
        ROIOut_SR(:, 1 : 2) = ROIOut_SR(:, 1 : 2) + WidthHeightDiff;     
    end
end


%%%%%% Adjust ROI(s) that exceed frame dimensions %%%%%%    

%Although it may seem unlikely for the smoothing of ROIs to result in values outside of frame
%dimensions, this might occur when, for example, both the width and the X-coordinate increased or 
%both the height and the Y-coordinate increased.

%First-read operations
if FirstReadTF
    
    %1 x 4 row vector; type int16.
    %Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder 'FacePulseRate'.
    ROIOut_FR = ...
        ROIAdjustIfExceedsFrameDims( ...
            ROIOut_FR, ...
            VidObjWidth, ...
            VidObjHeight ...
        ); 
        
%Second-read operations   
else
    
    %M x 4 matrix; type int16.
    %Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder 'FacePulseRate'.
    ROIOut_SR = ...
        ROIAdjustIfExceedsFrameDims( ...
            ROIOut_SR, ...
            VidObjWidth, ...
            VidObjHeight ...
        ); 
end


%%%%%% Output validation %%%%%%

%For first-read operations
if FirstReadTF
 
    %Assert row size as zero because this variable not used in first-read operations
    %This may help remove dynamic memory allocation for this variable.
    assert( size(ROIOut_SR, 1) == 0 );
    
    %Check whether any ROI value is zero
    %The operations of this function were intended to prevent values of zero, so such a value is
    %likely due to an implementation error in this function. 
    if ROIOut_FR(1) == 0 || ...
       ROIOut_FR(2) == 0 || ...
       ROIOut_FR(3) == 0 || ...
       ROIOut_FR(4) == 0 
   
        %Throw error
        %Called as extrinsic so that stack trace can be displayed.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 24): ROI-modification operations assigned a', ...
             ' value of zero for an ROI. ROI accuracy may be affected. The frame index of', ...
             ' corresponding frame is: ', ...
             sprintf( '%d', int32( VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR) ) ), ... 
             '. Detected within function ROIMSIR in function ROIMSIR_FrameByFrameSmooth.'] ...
        );      
    end
    
    %Check whether the ROI size is unreasonably small
    %Such a small size is likely due to an implementation error in this function.
    %This check is intended to be run when testing new implementations, as small ROI sizes are an
    %indication of a implementation error. As occassional values below 20 may be considered
    %acceptable, this check is not intended for use outside of testing. "Occassional" in this case   
    %might be defined as a few occurances out of 10,000. Flag ExpectedBehaviorTestTF enables the
    %check.    
    if ExpectedBehaviorTestTF && ...
       ( ROIOut_FR(3) < 20 || ROIOut_FR(4) < 20 )

        %Display warning indicating frame index

        %Note: function warning() not available for code generation, so it must have previously
        %been declared as extrinsic.
        %Function fprintf can not be used as a substitute for warning() in this case because 
        %fprintf can not accept variable-length arguments.       
        warning( ...
            'Component:InternalError', ...
            ['Potential Internal Error (ROIMSIR, code 25): ROI-modification operations', ...
             ' assigned a size value for an ROI that is below 20 pixels, which is likely', ...
             ' inaccurate. ROI accuracy may be affected. The frame index of corresponding', ...
             ' frame is: '
             sprintf( '%d', int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ... 
             '. Detected within function ROIMSIR in function ROIMSIR_FrameByFrameSmooth.'] ...
        ); 
    end 

    %Check whether ROI type not int16 because other functions are implemented to accept values of  
    %this type. 
    %A non-matching type would be due to an implementation error.
    if ~ isa( ROIOut_FR(1, 1), 'int16' )

        %Throw error 
        %Called as extrinsic so that stack trace can be displayed.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 26): ROI assigned type other than int16. Occurred', ...
             ' during ROI-modification operations in frame index ', ...
             sprintf( '%d', int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ... 
             '. Occurred during first-read operations. Detected within function ROIMSIR in', ...
             ' function ROIMSIR_FrameByFrameSmooth.'] ...            
        ); 
    end

%For second-read operations    
else

    %Check whether the size of any ROI is unreasonably small
    %Such a small size is likely due to an implementation error in this function.
    %This check is intended to be run when testing new implementations, as small ROI sizes are an
    %indication of a implementation error. As occassional values below 20 may be considered
    %acceptable, this check is not intended for use outside of testing. "Occassional" in this case   
    %might be defined as a few occurances out of 10,000. Flag ExpectedBehaviorTestTF enables the
    %check.    
    if ExpectedBehaviorTestTF && ...
       any( ROIOut_SR(:, 3) < 20 ) || any( ROIOut_SR(:, 4) < 20 )

        %Display warning
        %Note: function warning() not available for code generation, so it must have previously
        %been declared as extrinsic.
        warning( ...
            'Component:InternalError', ...
            ['Potential Internal Error (ROIMSIR, code 27): ROI-modification operations', ...
             ' assigned a size value for an ROI that is below 20 pixels, which is likely', ...
             ' inaccurate. ROI accuracy may be affected. Occurred during the second-read', ... 
             ' operations. Detected within function ROIMSIR in function', ...
             ' ROIMSIR_FrameByFrameSmooth.'] ...
        );
    end
  
    %Check if ROI type not int16 because other functions are implemented to accept values of this 
    %type. 
    %A non-matching type would be due to an implementation error.
    if ~ isa( ROIOut_SR(1, 1), 'int16' )
      
        %Throw error
        %Called as extrinsic so that stack trace can be displayed.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 28): ROI assigned type other than int16. Occurred', ...
             ' during ROI-modification operations during the second read. Detected within', ... 
             ' function ROIMSIR in function ROIMSIR_FrameByFrameSmooth.'] ...
        );
    end    
end


end %end function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Note: this function is not currently used as a compiled function as it is nested within a
%compiled function, ROIMSIR_mex.

%Code-generation and build script used to generate C-language code and create the compiled version 
%(ROIMSIR_FrameByFrameSmooth_mex) of the function.

%{


%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.
%                                                     Example Code                 Upp. Bounds  Var. Size (T/F)  Type
ROIOutCode                            = coder.typeof( zeros(500, 4, 'int16'),      [inf, 4],    [1, 0] );        %int16
ROINoPrevCallsBlockCode               = coder.typeof( zeros(500, 4, 'int16'),      [inf, 4],    [1, 0] );        %int16
BlockFullLinIdxCode                   = coder.typeof( zeros(1, 500, 'int32'),      [1, inf],    [0, 1] );        %int32
ROIBlockDetectionFaceSkinLogIdxCode   = coder.typeof( false(500, 1),               [inf, 1],    [1, 0] );        %logical 
ROIBlockCode                          = coder.typeof( zeros(500, 4, 'int16'),      [inf, 4],    [1, 0] );        %int16
TimestampBlockCode                    = coder.typeof( zeros(500, 1, 'single'),     [inf, 1],    [1, 0] );        %single  
TimestampBlockDetectionsCode          = coder.typeof( zeros(500, 1, 'single'),     [inf, 1],    [1, 0] );        %single 
VideoReadConfig_FrameIdxCode          = coder.typeof( zeros(1, 500, 'uint32'),     [1, inf],    [0, 1] );        %uint32 
                 

%%%%%% Specify fixed-size input arguments %%%%%%

ROIGeneralConfig_ROIFinalSmoothingWindowsCode = zeros(1, 2, 'single');
ROIGeneralConfig_ROIWidthResizeFactorCode     = double(0);
ROIGeneralConfig_ROIHeightResizeFactorCode    = double(0);
VidObjWidthCode                               = int16(0);         
VidObjHeightCode                              = int16(0);
FirstReadTFCode                               = false;
RowToReturnFullLinIdxCode                     = uint32(0);
RowToReturnBlockLinIdxCode                    = uint32(0);
FirstFrameMSIRLinIdxCode                      = uint32(0);


%%%%%% Set configurations to increase performance %%%%%%

%Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic 
%"Optimization Strategies"
cfg = coder.config('mex');
cfg.GlobalDataSyncMethod = 'NoSync';
cfg.ConstantInputs = 'IgnoreValues';
cfg.ExtrinsicCalls = false;
cfg.SaturateOnIntegerOverflow = false;
cfg.IntegrityChecks = false;
cfg.ResponsivenessChecks = false;


%%%%%% Specify flags to minGW compiler to optimize execution speed %%%%%%

%For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

%The flags are specified as part of the code-generation configuration object. A custom function,
%setbuildargs, is used to specify these flags. For details on the function implementation, see the 
%function file, which is located within folder FacePulseRate. This custom function is based upon 
%Matlab guidance found in
%https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function

%setbuildargs will be evaluated from text within the code-generation object, so it is converted to 
%a character vector prior to execution of the codegen command.

%%%%%% --- Specify the flags as arguments to function setbuildargs %%%%%%

%Argument buildInfo: this variable is assign by the caller (the codegen command executed 
%below) and is not present in the base workspace.

%Second argument: specify a cell array of compiler-specific flags, where each flag is a 
%character vector. As function setbuildargs will be evaluated from text, use double ' quotes for 
%each character vector to maintain the charater vector,
%e.g., {''-Ofast'' ''-fsingle-precision-constant''}.

setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})';

%Assign to code-generation configuration object
cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen ROIMSIR_FrameByFrameSmooth.m -config cfg -args {ROIOutCode, ROINoPrevCallsBlockCode, BlockFullLinIdxCode, ROIBlockDetectionFaceSkinLogIdxCode, ROIBlockCode, TimestampBlockCode, TimestampBlockDetectionsCode, ROIGeneralConfig_ROIFinalSmoothingWindowsCode, ROIGeneralConfig_ROIWidthResizeFactorCode, ROIGeneralConfig_ROIHeightResizeFactorCode, VidObjWidthCode, VidObjHeightCode, FirstReadTFCode, VideoReadConfig_FrameIdxCode, RowToReturnFullLinIdxCode, RowToReturnBlockLinIdxCode, FirstFrameMSIRLinIdxCode}
             
%}


