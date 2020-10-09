function [ROIOut_FR, ROIOut_SR, InterpolatedLinIdx_FR, InterpolatedLinIdx_SR] = ...
             ROIMSIR_Interpolate(ROINoPrevCallsBlock, NoPrevCallsBlock_ROIDetections, ...
                 BlockFullLinIdx, ROIBlockDetectionFaceSkinLinIdx, NDetectionsFaceSkin, ...
                 ROIBlockNoDetectionFaceSkinLinIdx, NNoDetectionsFaceSkin, TimestampBlock, ...
                 TimestampBlockDetections, ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...
                 ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, VidObjWidth, VidObjHeight, ...
                 FirstReadTF, VideoReadConfig_FrameIdx_FR, ROINoResizeBlock_FR, ...             
                 RowToReturnFullLinIdx_FR, RowToReturnBlockLinIdx_FR, ...
                 ROIMSIR_FirstFrameLinIdx_FR, ExpectedBehaviorTestTF) %#codegen                                                      
%ROIMSIR_Interpolate    Interpolate or extrapolate ROIs for frames without a detection.
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
%    Interpolate or extrapolate X-, Y-coordinate, width, and height of ROI(s) that do not have a 
%    corresponding face-detection or skin-detection algorithm detection. A detection will not be 
%    present if no detection algorithm was able to make a detection or if the frame was skipped.  
%
%    Linear interpolation is used rather than less conservative methods, such as PCHIP, to reduce  
%    sudden fluctuations that do not reflect head movement. For extrapolation, use the 
%    nearest-neighbor method rather than the linear method.
%
%    Custom function Interp conducts most of the interpolation / extrapolation operations. Interp
%    conducts linear interpolation or nearest-neighbor extrapolation. It also conducts various 
%    checks to determine whether ROI appears valid. 
%
%    If there are not at least two ROIs that correspond to detections within the block of frames
%    used, linear interpolation / extrapolation is not possible. In this case, there may be at 
%    least one ROI that corresponds to a detection within the block. If this is the case, assign
%    this ROI in place of interpolation / extrapolation. Otherwise, assign the dimensions of the
%    full frame as the ROI; for example, if the frame dimensions are 720 x 1280, assign the ROI as
%    [1, 1, 1280, 720]. During the second read, if there are not two ROIs that correspond to 
%    detections, the frame dimensions are assigned rather than using a single ROI that corresponds
%    to a detection. This is done because the block size for the second read is quite large, and 
%    the single ROI that corresponds to a detection may not be representative of all frames within
%    the block.
%
%    -- Arguments to Function Interp --
%
%    Note: see function Interp for a description of input validation.
%
%   - TimestampBlockDetections                  = Time points used for interpolation. N-Detections   
%                                                 x 1 column vector; type single.                                                 
%   - NoPrevCallsBlock_ROIDetections            = Values used for interpolation. N-Detections x 4
%                                                 matrix; type int16.
%   - TimestampTarget                           = Time point(s) at which interpolation to be   
%                                                 assigned. For first-read operations, only one 
%                                                 time point used; for second-read operations, many
%                                                 may be used. Scalar or column vector; type 
%                                                 single.
%   - LinearExtrapTF                            = False: use nearest-neighbor rather than linear  
%                                                 method when TimestampTarget is outside of the
%                                                 domain of TimestampBlockDetections (i.e., when
%                                                 extrapolation occurs). See the section below for
%                                                 a description of these checks. Scalar; type 
%                                                 logical.
%   - ValidityChecksTF                          = Flag whether to check whether the interpolated /
%                                                 extrapolated ROI seems reasonable. See function                                                 
%   - ROIGeneralConfig_ROIMSIR_DiffMaxDetection = The threshold specifying the maximum 
%                                                 absolute-value difference between the X- and   
%                                                 Y-coordinates of the interpolated / extrapolated                                                                                        
%                                                 ROI and the ROI corresponding to the    
%                                                 temporally-nearest previous detection. The value
%                                                 for this argument is currently assigned by
%                                                 function ROIGeneralConfig_Setup. Scalar; type
%                                                 int16.
%   - ROINoResizeBlock_Previous                 = ROI X- and Y-coordinates of the previous frames;   
%                                                 checked against threshold                                                   
%                                                 ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent. If size
%                                                 of input is 0 x 2, this check is not conducted.
%                                                 This check is conducted for first-read but not 
%                                                 second-read operations. For second-read 
%                                                 operations, this check is instead conducted after 
%                                                 the call to this function. This is implemented
%                                                 because, during the second-read operations, 
%                                                 there may not be previous frames available at the
%                                                 time the function is called. More specifically,
%                                                 because the second-read ROIs are interpolated
%                                                 at one time within the function, these 
%                                                 interpolated ROIs would not be available for
%                                                 input into function. N x 2 row vector; type 
%                                                 int16. 
%   - ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent  = The threshold specifying the maximum  
%                                                 absolute-value difference between the X- and   
%                                                 Y-coordinates of the interpolated / extrapolated                                                                                      
%                                                 ROI and the ROI of the previous frame. The value
%                                                 for this argument is currently assigned by
%                                                 function ROIGeneralConfig_Setup. Scalar; type 
%                                                 int16. 
%                                                                                                  
%   - VidObjWidth
%   - VidObjHeight 
%
%   -- Checks Enabled by the ValidityChecksTF Argument to Function Interp --
%
%   - Checking whether the difference between an interpolated value and a nearby actual value is
%     within a specified threshold (ROIGeneralConfig_ROIMSIR_DiffMax). If not, this may be an
%     indication of an overshoot; in this case, the interpolated value is changed to the maximum 
%     value specified by the threshold. This check and adjustment are only applied to an 
%     interpolated value corresponding to the X- or Y-coordinate (rather than height or width) of 
%     the ROI. The check is not applied to height or width as testing has indicated that an 
%     overshoot is not as common for height or width. 
%   - Checking whether an interpolated value corresponding to ROI height or width is above 20. If 
%     not, the interpolated value is recalculated by conducting nearest-neighbor extrapolation. A
%     height or width below 20 is considered to be too small for the size of faces expected in a 
%     video.    
%   - Checking whether an interpolated value is within the frame dimensions (minimum of 1 and
%     maximums of VidObjWidth and VidObjHeight). If not, the interpolated value is changed to be
%     bounded by the frame dimensions.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code generation settings %%%%%%

%Inline function
coder.inline('always');

%Call function as extrinsic
%See notes where warning() used.
coder.extrinsic('warning');

%Call function as extrinsic so that stack trace can be displayed
coder.extrinsic('error');

%Declare variables:

%                                         Upp. Bounds  Var. Size (T/F)
coder.varsize('ROIOut_SR',                [inf, 4],    [1, 0]);
coder.varsize('InterpolatedLinIdx_SR',    [inf, 1],    [1, 0]);


%%%%%% Preallocate variables %%%%%%

%Preallocate linear index of interpolated frame
%Note: If not reassigned, 0 will act as a flag to other functions to indicate no ROIs were 
%interpolated.
InterpolatedLinIdx_FR = coder.nullcopy( int32(0) ); 
InterpolatedLinIdx_SR = coder.nullcopy( zeros(0, 1, 'int32') ); 

ROIOut_FR = coder.nullcopy( zeros(1, 4, 'int16') );
ROIOut_SR = coder.nullcopy( zeros(0, 4, 'int16') );


%%%%%% Arguments to function Interp common to first- and second-read operations %%%%%%

%False = use the nearest-neighbor method rather than the linear method for extrapolation.
LinearExtrapTF = false;

%Conduct checks on the validity of the interpolation / extrapolated ROI(s).
ValidityChecksTF = true;


%%%%%% Operations when called from first-read operations %%%%%%      

if FirstReadTF
    
    %Assert row size as zero because this variable not used in first-read operations
    %This may help remove dynamic memory allocation for this variable.
    assert( size(ROIOut_SR, 1) == 0 );
  
    %Note: ROIMSIR_InterpolateFR is a custom function located within folder 'FacePulseRate'.
    [ROIOut_FR,               ... 1 x 4 row vector; type int16
     InterpolatedLinIdx_FR] = ... scalar; type int32
        ROIMSIR_InterpolateFR(ROINoPrevCallsBlock, NoPrevCallsBlock_ROIDetections, ...
            ROIBlockDetectionFaceSkinLinIdx, NDetectionsFaceSkin, TimestampBlock, ...
            TimestampBlockDetections, ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...            
            ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, VidObjWidth, VidObjHeight, ...
            ROINoResizeBlock_FR, RowToReturnFullLinIdx_FR, RowToReturnBlockLinIdx_FR, ...                              
            ROIMSIR_FirstFrameLinIdx_FR, LinearExtrapTF, ValidityChecksTF);    
        
        
%%%%%% Operations when called from second read %%%%%%      

%Note: used during both the pre- and post-processing steps of second-read operations (function 
%ROIMSIR called by function ROIMeans_SecondRead_TakeMeans). During the pre-processing step,  
%interpolate / extrapolate ROIs near the beginning of the video that were not interpolated / 
%extrapolated during the first-read operations. During the post-processing step, interpolate /
%extrapolate ROIs near the beginning of the video based on recent skin-detection algorithm ROI 
%detections.

else 
    
    %Note: ROIMSIR_InterpolateSR is a custom function located within folder 'FacePulseRate'.
    [ROIOut_SR,               ... M x 4 row vector; type int16
     InterpolatedLinIdx_SR] = ... M x 1 column vector; type int32
        ROIMSIR_InterpolateSR(ROINoPrevCallsBlock, NoPrevCallsBlock_ROIDetections, ...
            BlockFullLinIdx, NDetectionsFaceSkin, ROIBlockNoDetectionFaceSkinLinIdx, ...
            NNoDetectionsFaceSkin, TimestampBlock, TimestampBlockDetections, ...
            ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...
            ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, VidObjWidth, VidObjHeight, ...
            LinearExtrapTF, ValidityChecksTF);             
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
            ['Internal Error (ROIMSIR, code 14): ROI-modification operations assigned a value', ...
             ' of zero for an ROI. ROI accuracy may be affected. The frame index of', ...
             ' corresponding frame is: ', ...
             sprintf( '%d', int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ... 
             '. Detected within function ROIMSIR in function ROIMSIR_Interpolate.'] ...
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

        %Note: function warning() not available for code generation; so it must have previously
        %been declared as extrinsic.
        %Function fprintf can not be used as a substitute for warning() in this case because 
        %fprintf can not accept variable-length arguments.     
        warning( ...
            'Component:InternalError', ...
            ['Potential Internal Error (ROIMSIR, code 15): ROI-modification operations', ...
             ' assigned a size value for an ROI that is below 20 pixels, which is likely', ...
             ' inaccurate. ROI accuracy may be affected. The frame index of corresponding', ...
             ' frame is: ', ...
             sprintf( '%d', int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ... 
             '. Detected within function ROIMSIR in function ROIMSIR_Interpolate.'] ...
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
            ['Internal Error (ROIMSIR, code 16): ROI assigned type other than int16 during', ...
             ' ROI-modification operations. Occurred during first-read operations in frame', ...
             ' index ', ...
             sprintf( '%d', int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ...
             '. Detected within function ROIMSIR in function ROIMSIR_Interpolate.'] ...            
        );  
    end

%For second-read operations    
else

    %Check whether any ROI value is zero
    %The operations of this function were intended to prevent values of zero, so such a value is
    %likely due to an implementation error in this function. 
    if any(ROIOut_SR == 0, 'all') 

        %Throw exception
        %Called as extrinsic so that stack trace can be displayed.
        %Note: '%.0f' = floating point with no decimals.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 17): ROI-modification operations assigned a value', ...
             ' of zero for an ROI. ROI accuracy may be affected. The error occurred during', ...
             ' the second-read operations. Detected within function ROIMSIR in function', ...
             ' ROIMSIR_Interpolate.'] ...              
        );  
    end    
    
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
            ['Potential Internal Error (ROIMSIR, code 18): ROI-modification operations', ...
             ' assigned a size value for an ROI that is below 20 pixels, which is likely', ...
             ' inaccurate. ROI accuracy may be affected. Occurred during the second-read', ... 
             ' operations. Detected within function ROIMSIR in function ROIMSIR_Interpolate.'] ...
        );           
    end
    
    %Check if ROI type not int16 because other functions are implemented to accept values of this 
    %type. 
    %A non-matching type would be due to an implementation error.
    if ~ isa( ROIOut_SR(1, 1), 'int16' )
      
        %Throw exception 
        %Called as extrinsic so that stack trace can be displayed.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 19): ROI assigned type other than int16. Occurred', ...
             ' during ROI-modification operations during the second read. Detected within', ... 
             ' function ROIMSIR in function ROIMSIR_Interpolate.'] ...
        );         
    end    
end


end %end main function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Note: this function is not currently used as a compiled function as it is nested within a
%compiled function, ROIMSIR_mex.

%Code-generation and build script used to generate C-language code and create the compiled version 
%(ROIMSIR_Interpolate_mex) of the function.

%{
                

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.
%                                                     Example Code                 Upp. Bounds  Var. Size (T/F)  Type
ROINoPrevCallsBlockCode               = coder.typeof( zeros(500, 4, 'int16'),      [inf, 4],    [1, 0] );        %int16
BlockFullLinIdxCode                   = coder.typeof( zeros(1, 500, 'int32'),      [1, inf],    [0, 1] );        %int32
ROIBlockDetectionFaceSkinLogIdxCode   = coder.typeof( false(500, 1),               [inf, 1],    [1, 0] );        %logical
TimestampBlockCode                    = coder.typeof( zeros(500, 1, 'single'),     [inf, 1],    [1, 0] );        %single  
TimestampBlockDetectionsCode          = coder.typeof( zeros(500, 1, 'single'),     [inf, 1],    [1, 0] );        %single 
ROICode                               = coder.typeof( zeros(500, 4, 'int16'),      [inf, 4],    [1, 0] );        %int16 
VideoReadConfig_FrameIdxCode          = coder.typeof( zeros(1, 500, 'uint32'),     [1, inf],    [0, 1] );        %uint32 
                 

%%%%%% Specify fixed-size input arguments %%%%%%

ROIGeneralConfig_MatchSmoothInterpolateResize_DiffMaxCode = int16(0);
ROIGeneralConfig_ROIWidthResizeFactorCode                 = double(0);
ROIGeneralConfig_ROIHeightResizeFactorCode                = double(0);
VidObjWidthCode                                           = int16(0);         
VidObjHeightCode                                          = int16(0);
FirstReadTFCode                                           = false;
RowToReturnFullLinIdxCode                                 = uint32(0);
RowToReturnBlockLinIdxCode                                = uint32(0);
FirstFrameMSIRLinIdxCode                                  = uint32(0);


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

codegen ROIMSIR_Interpolate.m -config cfg -args {ROINoPrevCallsBlockCode, BlockFullLinIdxCode, ROIBlockDetectionFaceSkinLogIdxCode, TimestampBlockCode, TimestampBlockDetectionsCode, ROICode, ROIGeneralConfig_MatchSmoothInterpolateResize_DiffMaxCode, ROIGeneralConfig_ROIWidthResizeFactorCode, ROIGeneralConfig_ROIHeightResizeFactorCode, VidObjWidthCode, VidObjHeightCode, FirstReadTFCode, VideoReadConfig_FrameIdxCode, RowToReturnFullLinIdxCode, RowToReturnBlockLinIdxCode, FirstFrameMSIRLinIdxCode}
             
%}




             