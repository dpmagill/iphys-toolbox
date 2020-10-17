function [ROIOut_FR, ROIOut_SR, InterpolatedLinIdx_FR, InterpolatedLinIdx_SR, ...
          ROIOutBeforeFrameByFrameSmoothing_FR, ROIOutBeforeFrameByFrameSmoothing_SR, ...
          ROIOutNoResize_FR, ROIMatchSizeData] = ...          
             ROIMSIR(BlockFullLinIdx_In, ROI, Timestamp, HasROI_TF, ...
                 ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...
                 ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, ...
                 ROIGeneralConfig_ROIWidthResizeFactor, ROIGeneralConfig_ROIHeightResizeFactor, ...                 
                 FaceDetectConfig_ROIFaceSmoothingWindow, FaceDetectConfig_ROIFaceSecondary1TF, ...
                 FaceDetectConfig_ROIFaceSecondary2TF, SkinDetectConfig_ROISkinSmoothingWindow, ...
                 ROIGeneralConfig_ROIFinalSmoothingWindows, VidObjWidth, VidObjHeight, ...
                 ExpectedBehaviorTestTF, FirstReadTF, FirstCallTF, VideoReadConfig_FrameIdx_FR, ... 
                 RowToReturnFullLinIdx_FR, ROIMSIR_FirstFrameLinIdx_FR, ROINoMods, ROINoResize, ...
                 ROIMatchSizeData, SecondReadPostProcessingTF) %#codegen                                                            
%ROIMSIR   Modify ROI(s) size and position by matching size across algorithms, ROI-detection   
%          smoothing, interpolation, frame-by-frame smoothing, and resizing.                                        
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions ROIMeans_FirstRead_TakeMeans and 
%    ROIMeans_SecondRead.
%
%
%    Code Generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.
%
%    Compiled file: The compiled file included in folder FacePulseRate (ROIMSIR_mex.mexw64) only    
%    compatible on Windows platforms.     
%
%
%    Description
%    -----------
%
%    The size and position of ROI(s) are modified to increase stability and accuracy across frames.
%    By increasing stability, fluctuations in size and position that could introduce artifacts to 
%    the pulse rate algorithms are reduced. Accuracy is improved by allowing the ROIs of nearby  
%    frames to influence the size and position of a given frame. This assumption is that it is less 
%    likely for a group of ROIs to be inaccurate than a single ROI to be inaccurate. Additionally,
%    frames without an ROI from a detection are interpolated. Some frames may not have an ROI if 
%    the detection algorithms were skipped for certain frames for efficiency (see function 
%    ROIMeans_FirstRead_DetermineSkipFrame) or if none of the detection algorithms were successful
%    for some frames.
%
%    ROI(s) to be returned are processed differently depending on whether they (1) correspond to a
%    detection or whether they (2) do not correspond a detection, in which case interpolation
%    will be conducted.  
%
%    (1) ROI(s) to be returned that correspond to detection(s): 
%   
%      If the ROI(s) to be returned correspond to face-detection algorithm or skin-detection 
%      algorithm detection(s), four modications are made:
%
%      (i) Size matching (function ROIMSIR_MatchSize): if the ROI(s) do not correspond to a primary 
%      face-detection algorithm detection, the size of the ROI is matched to the size of primary   
%      face-detection algorithm ROIs to increase stability of size of ROIs across frames. 
%
%      (ii) Detection smoothing (function ROIMSIR_DetectionSmooth): the ROI(s) are smoothed with 
%      nearby ROIs that correspond to face-detection algorithm detections to reduce outliers. 
%      Nearby ROIs that correspond to skin-detection algorithm detections are not used because 
%      face-detection algorithm detections tend to be more accurate. Detection smoothing is used to  
%      increase stability and accuracy of ROI position and size across frames.
%
%      (iii) Frame-by-frame smoothing (function ROIMSIR_FrameByFrameSmooth): the ROI(s) are 
%      smoothed with all nearby ROIs regardless of whether the ROIs correspond to detections. These 
%      nearby ROIs will have size matching and detection smoothing applied to them to increase  
%      their stability and accuracy. Frame-by-frame smoothing conducts a finer level of adjustments  
%      compared to size matching and detection smoothing. Frame-by-frame smoothing, like detection  
%      smoothing, is intended to increase stability and accuracy of ROI position and size across 
%      frames.
%
%      (iv) ROI resizing (function ROIResize): ROI resizing resizes ROIs according to  
%      ROIWidthResizeFactor and ROIHeightResizeFactor, which are arguments to function 
%      FacePulseRate. The values of these arguments are specified to maximize facial skin and 
%      minimize non-skin within the ROI.
%    
%    (2) ROI(s) to be returned that do not correspond to detection(s):
%
%      If an ROI does not correspond to a detection, which indicates either the frame was skipped 
%      or no detection was made, three opertions will be conducted:
%
%      (i) Interpolation (function ROIMSIR_Interpolate): The ROI(s) are interpolated from nearby    
%      ROIs that correspond to detections. These nearby ROIs will have size matching and detection    
%      smoothing applied to them to increase their stability and accuracy before being used in   
%      interpolation. (The size matching and detection smoothing applied to nearby ROIs is only    
%      conducted for the purpose of interpolation, and these nearby ROIs are not returned as 
%      output).
%
%      (ii) Frame-by-frame smoothing (function ROIMSIR_FrameByFrameSmooth): see descripton provided 
%      above.
%
%      (iii) ROI resizing (function ROIResize): see descripton provided above.    
%
%      Note: 
%
%      If fewer than two ROIs within the ROI block (BlockFullLinIdx_In) correspond to a detection, 
%      then interpolation is not possible as the interpolation method used is linear interpolation, 
%      which requires at least two points to draw upon. 
%
%      If exactly one ROI within the ROI block corresponds to a detection, then the ROI output 
%      depends upon whether the function is called during the first-read (FirstReadTF == true) or
%      second-read operations. If called during the first-read operations, then the output ROIs are
%      assignd the values of the one ROI that corresponds to a detection. If called during the
%      second-read operations, then the output ROIs are assigned the dimensions of the full frame. 
%      The output of the second-read operations is different from the output of the first-read
%      operations in this case because the ROI block is expected to be larger during the   
%      second-read operations, and it is assumed that basing the values of all ROIs on one ROI may   
%      likely lead to inaccuracies. 
%
%      In the case that no ROIs within the ROI block correspond to a detection, then the output 
%      ROIs are assigned the dimensions of the full frame.
%
%      In the event that the full frame dimensions are assigned, then Frame-by-frame smoothing and
%      ROI resizing are not conducted.
%
%    -- Implementation Differences between First-Read and Second-Read Operations --
%
%    FirstReadTF == true indicates that the function is being called during the first-read 
%    operations (specifically, by function ROIMeans_FirstRead_TakeMeans). FirstReadTF == false 
%    indicates that the function is being called during the second-read operations (specifically, 
%    by function ROIMeans_SecondRead). Different implementations are used depending on this
%    argument. Different implementations are used for four reasons. 
%
%    (1) During the first-read operations, the ROIs corresponding to a single frame (ROIOut_FR and
%    ROIOutBeforeFrameByFrameSmoothing_FR) are returned. During the second-read operations, the 
%    ROIs corresponding to a multiple frames (ROIOut_SR and ROIOutBeforeFrameByFrameSmoothing_SR)
%    are returned. As multiple ROIs are processed during second-read operations, a vectorized 
%    implementation is used during second-read operations. For the single ROIs returned during
%    first-read operations, a vectorized implementation was observed to add additional overhead.
%    The function is called potentially thousands of times during first-read operations, so the
%    accummulation of this overhead became noticable. Consequently, the first-read implementation
%    was designed without vectorization for operations where vectorization would not be relevant.
%
%    (2) During the first-read, but not the second-read, operations, the function is called   
%    sequentially (frame-by-frame) (see function ROIMeans_FirstRead_TakeMeans). When called  
%    sequentially, a positive feedback loop was observed to develop that resulted in noticable 
%    oscillations of ROI values. The feedback loop developed because the values of ROIs previously   
%    returned reentered as input on each call (although the first-read operations return the ROIs
%    for only a single frame on each call, a block of ROIs is used as input to conduct the 
%    operations). This feedback loop is analogous to the feedback loop that develops between a 
%    microphone and a speaker. Consequently, the first-read implementation takes steps to remove
%    the cause of the feedback loop. Specifically, ROI values that were returned previously do not
%    reenter the function. To use ROIs values that were not returned previously, a variable 
%    (ROINoMods) is used that holds ROI values that were not returned by the function.
%    
%    (3) During second-read operations, the function is applied to the same ROIs on two occassions
%    (second-read pre-processing and second-read post-processing) (see function
%    ROIMeans_SecondRead). Because the same ROIs are processed twice by the function, the 
%    second-read implementation takes steps to avoid applying the same operations to the same ROIs
%    if the state of the ROIs did not change between the pre-processing and post-processing steps.  
%    The argument SecondReadPreProcessingTF indicates whether the function is being called during 
%    the pre-processing or post-processing step. During the first-read operations, the value of
%    SecondReadPreProcessingTF is not relevant.
%
%    (4) To increase efficiency of the compiled version of function ROIMSIR (ROIMSIR_mex), ROIMSIR 
%    was developed so that the first-read operations take an execution path separate from the 
%    second-read operations. Separate execution paths were developed so that Matlab code generation  
%    can make separate functions for each path (termed "function specialization") if doing so  
%    increases efficiency. Function specialization can increase efficiency when some versions of
%    variables can use static, rather than dynamic, memory allocation or if some versions of 
%    variables can used fixed, rather than variable, sizes. 
%
%    To facilitate function specialization, the execution path of the first-read operations was  
%    developed such that variable BlockFullLinIdx_FR is always a fixed-length. If always a fixed
%    length, dynamic memory allocation can be avoided and fixed-size variables can be utilized in  
%    the compiled function. Moreover, many variables along the execution will be assigned with the
%    length of this variable, so they, too, can avoid dynamic memory allocation and utlize 
%    fixed-size variables in the compiled function.
%  
%    To further discourage dymanic memory allocation and utilize fixed-size variables, a  
%    fixed-length ROI block row of 229 is used for first-read operations. The value 229 corresponds
%    to the length of the frame cache (see function ROIMeans_FirstRead_TakeMeans) multipled by two 
%    with 1 added (115 * 2 + 1).
%
%    Second-read operations require a variable-length version of BlockFullLinIdx_FR 
%    (BlockFullLinIdx_SR), so second-read operations use a separate execution path to accommodate 
%    this and avoid placing this requirement on  first-read operations. Note that although 
%    first-read and second-read operations use separate execution paths using different variable 
%    sizes, they actually undergo the same operations in most cases.  
%
%    -- Internal Error Checking --
%
%    During development, small changes to the implementation can result in bugs that can be 
%    difficult to detect intially and to trace. To detect such bugs immediately and indicate their
%    origin, several checks are implemented in this function and the functions it calls. The
%    warnings and errors thrown from these bugs use the message identifier "internal error", which
%    indicates an implementation error rather than an error resulting from user input. 
%
%    Because this function may be compiled, the function stack trace displayed on the command 
%    window will not be able to identify which of the functions called within ROIMSIR threw the 
%    error or warning. Given this, as well as the large number of potential error or warning 
%    messages within the function, each error and warning will display a unique code for better 
%    identification.
%
%
%    Note
%    ----
%
%    Intended only when input variable ROI uses integer types as rounding is not conducted. For 
%    modification for use with floating-point types, rounding would be necessary as ROI values 
%    should be integers.
%
%
%    Inputs
%    ------
%
%        BlockFullLinIdx_In = Linear index corresponding to frame index of block of frames used in 
%                             operations. A block of frames is used as input even if the output
%                             consists of ROIs corresponding to a single frame. 299 x 1 in first 
%                             read and M x 1 in second read; type int32.
%        ROI                = ROI matrix. M x 4; type int16. 
%        Timestamp          = Timestamp for each frame. Column vector; type single.                                        
%        HasROI_TF          = Struct with information regarding ROIs. See file 
%                             ROIMeans_ROIVarsSetup. Scalar struct.
%        VidObjWidth        = Frame width in pixels. Scalar; type int16.
%        VidObjHeight       = Frame height in pixels. Scalar; type int16.
%        FirstReadTF        = Logical value where true indicates that the function is being called 
%                             during the first-read operations (by function
%                             ROIMeans_FirstRead_TakeMeans) and false indicates the function is  
%                             being called during second-read operations (by function
%                             ROIMeans_SecondRead). If true, a one-row ROI is returned as output;
%                             otherwise, an ROI with an arbitrary number of rows can be returned. 
%                             Scalar; type logical.
%        SecondReadPostProcessingTFCode = Logical value where true indicates that the function is  
%                             being called during the second-read operations post-processing step
%                             and false indicates otherwise. When FirstReadTF == false and 
%                             SecondReadPostProcessingTFCode == true, the function is being called
%                             during the second-read operations pre-processing step. Scalar; type 
%                             logical.
%        ROIGeneralConfig_MatchSmoothInterpolateResize_DiffMax = Maximum distance permitted between
%                             an interpolated ROI and the previous ROI. Scalar; type int16.                           
%        ROIGeneralConfig_ROIWidthResizeFactor = Amount by which to resize width. Argument to  
%                             function FacePulseRate. Scalar; type double.                             
%        ROIGeneralConfig_ROIHeightResizeFactor = Amount by which to resize width. Argument to  
%                             function FacePulseRate Scalar; type double.
%        FaceDetectConfig_ROIFaceSecondary1TF = Logical value indicating whether the secondary #1
%                             face-detection algorithm is enabled. Argument to function 
%                             FacePulseRate. Scalar; type logical.
%        FaceDetectConfig_ROIFaceSecondary2TF = Logical value indicating whether the secondary #2
%                             face-detection algorithm is enabled. Argument to function 
%                             FacePulseRate. Scalar; type logical.
%        FaceDetectConfig_ROIFaceSmoothingWindow = Amount by which to smooth ROI position for ROIs
%                             corresponding to face-detection algorithm detections. Argument to  
%                             function FacePulseRate. Scalar; type double.                                                         
%        SkinDetectConfig_ROISkinSmoothingWindow = Amount by which to smooth ROI position for ROIs
%                             corresponding to skin-detection algorithm detections. Argument to  
%                             function FacePulseRate. Scalar; type double.           
%        ROIGeneralConfig_ROIFinalSmoothingWindows = Amounts by which to smooth ROI position and 
%                             size, respectively. Argument to function FacePulseRate. 1 x 2; type 
%                             int32.  
%        ExpectedBehaviorTestTF = Whether testing is enabled to determine whether ROI widths and 
%                             heights are below a certain value after various steps of the 
%                             operations. If below the value, this may indicate that the 
%                             implementation is not behaving as expected. Occasionally, however,
%                             widths or heights may be below the value in the absence of an
%                             implementation issue. If a width or height is below the value, a
%                             warning is displayed. This option is intended to be enabled only 
%                             during testing. Otherwise, to increase efficiency and avoid the 
%                             display of unnecessary warnings, it should be disabled.
%
%        The following inputs are relevant only during the first-read operations:
%
%        RowToReturnFullLinIdx_FR = Frame index of the block of ROIs to be used in operations.  
%                                   Note that, within this function, another variable 
%                                   (RowToReturnBlockLinIdx_FR) is assigned to act as an index of   
%                                   this variable itself; for example, if RowToReturnFullLinIdx_FR  
%                                   contains values 300 : 500, RowToReturnBlockLinIdx_FR would    
%                                   contain values 1 : 300. Scalar; type int32.
%        ROINoMods                = ROI matrix without ROI values previously returned by the  
%                                   function. This variable is used to prevent a positive feedback 
%                                   loop (see notes at top of file). Size is same as input "ROI";
%                                   type int16.
%        ROINoResize              = ROI matrix with ROIOutNoResize_FR values previously returned by   
%                                   the function. These ROIs received all operations in the current
%                                   function except resizing. Size is same as input "ROI"; type 
%                                   int16.
%        ROIMSIR_FirstFrameLinIdx_FR = Frame index indicating the first frame that was called by  
%                                   the function. This index will be used by helper function                            
%                                   ROIMSIR_FrameByFrameSmooth. Scalar; type int32.     
%        VideoReadConfig_FrameIdx_FR = Frame index for use in warning and error messages (see notes  
%                                   at top of file regarding internal errors). Column vector; type 
%                                   int32.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%% %%%%%%%%%%%%%%%%
%%% Setup %%%%%%%%%
%%%%%%%%%%%%%%%%%%%          


%%%%%% Code-generation settings %%%%%%

%Specify inlining for faster code execution
coder.inline('always');

%Call function as extrinsic so that stack trace can be displayed
coder.extrinsic('error');


%%%%%% Declare and initialize variables %%%%%%

%Note: regarding "coder.nullcopy", see Matlab documentation topic "Eliminate Redundant Copies  
%of Variables in Generated Code".

%%%%%% --- Variables in first-read operations %%%%%%

%Declare variable-size variables:

%                                                      Upp. Bounds  Var. Size (T/F)
coder.varsize('NoPrevCallsBlock_ROIDetections_FR',     [229, 4],    [1, 0]);

%Initialize variables:

%Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
%variable were to change, the constant would need to be modified. 

ROIOutBeforeFrameByFrameSmoothing_FR = coder.nullcopy( zeros(1, 4, 'int16') );
InterpolatedLinIdx_FR                = int32(0); %note: 0 will be indication that interpolation not conducted
ROIOutNoResize_FR                    = coder.nullcopy( zeros(1, 4, 'int16') );
ROINoResizeBlock_FR                  = coder.nullcopy( zeros(229, 4, 'int16') );
RowToReturnBlockLinIdx_FR            = int32(0); %scalar needed here
TimestampBlock_FR                    = coder.nullcopy( zeros(229, 1, 'single') );
TimestampBlockDetections_FR          = coder.nullcopy( zeros(229, 1, 'single') ); 
ROINoPrevCallsBlock_FR               = coder.nullcopy( zeros(229, 4, 'int16') );
NoPrevCallsBlock_ROIDetections_FR    = coder.nullcopy( zeros(0, 4, 'int16') );
ROIBlock_FR                          = coder.nullcopy( zeros(229, 4, 'int16') );
ROIBlockDetectionFaceLinIdx_FR       = coder.nullcopy( zeros(229, 1, 'int32') );
NDetectionsFace_FR                   = coder.nullcopy( zeros(1, 1, 'int32') );
ROIBlockDetectionSkinLinIdx_FR       = coder.nullcopy( zeros(229, 1, 'int32') );
NDetectionsSkin_FR                   = coder.nullcopy( zeros(1, 1, 'int32') );
ROIBlockDetectionFaceSkinLinIdx_FR   = coder.nullcopy( zeros(229, 1, 'int32') );
NDetectionsFaceSkin_FR               = coder.nullcopy( zeros(1, 1, 'int32') );
ROIBlockNoDetectionFaceSkinLinIdx_FR = coder.nullcopy( zeros(229, 1, 'int32') );
NNoDetectionsFaceSkin_FR             = coder.nullcopy( zeros(1, 1, 'int32') );

%%%%%% --- Variables in second-read operations %%%%%%

%Declare variable-size variables:

%                                                       Upp. Bounds  Var. Size (T/F)
coder.varsize('ROIOut_SR',                              [inf, 4],    [1, 0]); 
coder.varsize('InterpolatedLinIdx_SR',                  [inf, 1],    [1, 0]);
coder.varsize('ROIOutBeforeFrameByFrameSmoothing_SR',   [inf, 4],    [1, 0]);
coder.varsize('ROIBlock_SR',                            [inf, 4],    [1, 0]);
coder.varsize('ROINoPrevCallsBlock_SR',                 [inf, 4],    [1, 0]);
coder.varsize('NoPrevCallsBlock_ROIDetections_SR',      [inf, 4],    [1, 0]);
coder.varsize('BlockFullLinIdx_SR',                     [inf, 1],    [1, 0]);
coder.varsize('TimestampBlock_SR',                      [inf, 1],    [1, 0]);
coder.varsize('TimestampBlockDetections_SR',            [inf, 1],    [1, 0]);
coder.varsize('ROIBlockDetectionFaceLinIdx_SR',         [inf, 1],    [1, 0]);  
coder.varsize('ROIBlockDetectionSkinLinIdx_SR',         [inf, 1],    [1, 0]);       
coder.varsize('ROIBlockDetectionFaceSkinLinIdx_SR',     [inf, 1],    [1, 0]);  
coder.varsize('ROIBlockNoDetectionFaceSkinLinIdx_SR',   [inf, 1],    [1, 0]); 

%Initialize variables:

ROIOut_FR                            = coder.nullcopy( zeros(1, 4, 'int16') );
ROIOut_SR                            = coder.nullcopy( zeros(0, 4, 'int16') );
ROIOutBeforeFrameByFrameSmoothing_SR = coder.nullcopy( zeros(0, 4, 'int16') );
InterpolatedLinIdx_SR                = coder.nullcopy( zeros(0, 1, 'int32') );
BlockFullLinIdx_SR                   = coder.nullcopy( zeros(0, 1, 'int32') ); 
TimestampBlock_SR                    = coder.nullcopy( zeros(0, 1, 'single') );
TimestampBlockDetections_SR          = coder.nullcopy( zeros(0, 1, 'single') );
ROINoPrevCallsBlock_SR               = coder.nullcopy( zeros(0, 4, 'int16') );
NoPrevCallsBlock_ROIDetections_SR    = coder.nullcopy( zeros(0, 4, 'int16') );
ROIBlock_SR                          = coder.nullcopy( zeros(0, 4, 'int16') );
ROIBlockDetectionFaceLinIdx_SR       = coder.nullcopy( zeros(0, 1, 'int32') );
NDetectionsFace_SR                   = coder.nullcopy( zeros(1, 1, 'int32') );
ROIBlockDetectionSkinLinIdx_SR       = coder.nullcopy( zeros(0, 1, 'int32') );
NDetectionsSkin_SR                   = coder.nullcopy( zeros(1, 1, 'int32') );
ROIBlockDetectionFaceSkinLinIdx_SR   = coder.nullcopy( zeros(0, 1, 'int32') );
NDetectionsFaceSkin_SR               = coder.nullcopy( zeros(1, 1, 'int32') );
ROIBlockNoDetectionFaceSkinLinIdx_SR = coder.nullcopy( zeros(0, 1, 'int32') );
NNoDetectionsFaceSkin_SR             = coder.nullcopy( zeros(1, 1, 'int32') );

                   
%%%%%% C-language optimation %%%%%%

%If called during first-read operations
if FirstReadTF 

    %Assign BlockFullLinIdx_FR with fixed length of 229.  

    %Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
    %variable were to change, the constant would need to be modified.     
    
    %If length of BlockFullLinIdx_In == 229
    if length(BlockFullLinIdx_In) == 229
 
        %Use indexing as a way to declare fixed length to code generation.
        %229 x 1 column vector; type int32.
        BlockFullLinIdx_FR = BlockFullLinIdx_In(1 : 229);       
        
        %Assert fixed size
        assert( all(size(BlockFullLinIdx_FR) == [229, 1]) );
       
    %If length of BlockFullLinIdx_In less than 229, make adjustments 
    %Length only less than 229 during the final 228 frames of the portion of the video to be 
    %processed.            
    else
        
        %Note: ROIMSIR_Optimize is a custom function located within folder 'FacePulseRate'.
        [BlockFullLinIdx_FR, ROI, ROINoMods, ROINoResize, HasROI_TF, ...
         VideoReadConfig_FrameIdx_FR, Timestamp] = ...   
            ROIMSIR_Optimize(BlockFullLinIdx_In, ROI, ROINoMods, ROINoResize, HasROI_TF, ...
                VideoReadConfig_FrameIdx_FR, Timestamp);                  
    end
    
%If called during second-read operations
else

    BlockFullLinIdx_SR = BlockFullLinIdx_In;
    
    %Assign zero-valued variables for code-generation purposes   
    %Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
    %variable were to change, the constant would need to be modified. 
    BlockFullLinIdx_FR = coder.nullcopy( zeros(229, 1, 'int32') ); 
end


%%%%%% Implementation-specific setup %%%%%%

%This function uses different implementations depending on whether the function is called during 
%the first-read operations (by function ROIMeans_FirstRead_TakeMeans) or during the second-read 
%operations (by function ROIMeans_SecondRead).

%%%%%% --- First-read setup %%%%%%

%Use implementation for first-read operations. See notes at top of file.

if FirstReadTF     

    %%%%%% >>>>>> Validate first-read inputs %%%%%%
    
    %Validate whether input ROI is type int16.
    %Must be an integer type because no rounding is conducted.
    %Should be type int16 because the function is implemented to assign values of this type.
    %A non-matching type would be due to an implementation error.
    if ~ isa( ROI(1, 1), 'int16' )
 
        %Throw error
        %Called as extrinsic so that stack trace can be displayed.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 1): ROI assigned type other than int16 during', ...
             ' ROI-modification operations. Occurred during first-read operations in', ...
             ' frame index ', ...
             sprintf( '%d', int32( VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ...
             '. Detected within function ROIMSIR.'] ...            
        );        
    end    
    
    %Validate whether input ROINoMods is type int16.
    %Must be an integer type because no rounding is conducted.
    %Should be type int16 because the function is implemented to assign values of this type.
    %A non-matching type would be due to an implementation error.
    if ~ isa( ROINoMods(1, 1), 'int16' )
 
        %Throw error 
        %Called as extrinsic so that stack trace can be displayed.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 2): Variable ROINoMods assigned type other than', ...
             ' int16 during ROI-modification operations. Occurred during first-read operations', ...
             ' in frame index ', ... 
             sprintf( '%d', int32( VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ...
             '. Detected within function ROIMSIR.'] ...            
        );          
    end  
    
    %%%%%% >>>>>> Assign additional first-read variables %%%%%%

    %Assign variables only used during first-read (not second-read) operations:

    %Index to length of ROI block. 
    %Also rename to "ROINoPrevCallsBlock_FR" to make the name more applicable because modications   
    %will be applied.    
    %229 x 4; type int16.
    ROINoPrevCallsBlock_FR = ROINoMods(BlockFullLinIdx_FR, 1 : 4);    

    %Index to length of ROI block. 
    %229 x 4; type int16.    
    ROINoResizeBlock_FR = ROINoResize(BlockFullLinIdx_FR, 1 : 4);    
    
    %Linear index of target frame converted to align with length of ROI block rather than full 
    %frame index.
    %Scalar; type int32.
    %Note: constant 115 assumes that the length of BlockFullLinIdx == 229. If the length of this 
    %variable were to change, the constant would need to be modified.  
    %Note: General indexing version (this is not used to discourage dynamic memory allocation): 
    %RowToReturnBlockLinIdx_FR = RowToReturnFullLinIdx_FR - BlockFullLinIdx_FR(1) + 1;
    RowToReturnBlockLinIdx_FR = int32(115);
    
    %Confirm that RowToReturnBlockLinIdx_FR == 115
    %Only in the case of an implementation error would this not be the case.
    if RowToReturnFullLinIdx_FR - BlockFullLinIdx_FR(1) + 1 ~= 115
        
        %Throw error
        %Called as extrinsic so that stack trace can be displayed.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 2.5): The block index of the row-to-return does', ...
             '  not equal 115.', ...
             ' The frame index of the frame is: ', ...
             sprintf( '%d', int32( VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR) ) ), ... 
             '. Detected within function ROIMSIR.'] ...
        );     
    end             
    
    %Assign variables common to first-read and second-read operations:
    
    %Note: Of these variables, the same form of variables are used in the second-read operations   
    %(they would have the "_SR" suffix), but, unlike the variables in the second-read, the   
    %variables used in the first-read are of fixed length.
    
    %ROIMSIR_AssignVars is a custom function located within folder 'FacePulseRate'
    [ROIBlock_FR, ROIBlockDetectionFaceLinIdx_FR, NDetectionsFace_FR, ...
     ROIBlockDetectionSkinLinIdx_FR, NDetectionsSkin_FR, ROIBlockDetectionFaceSkinLinIdx_FR, ...     
     NDetectionsFaceSkin_FR, ROIBlockNoDetectionFaceSkinLinIdx_FR, NNoDetectionsFaceSkin_FR, ...
     TimestampBlock_FR, TimestampBlockDetections_FR] = ...    
        ROIMSIR_AssignVars(BlockFullLinIdx_FR, ROI, HasROI_TF, Timestamp, FirstReadTF);

    %%%%%% >>>>>> Validation of additional first-read variables %%%%%%

    %Check whether HasROI_TF indicates detection for current frame but the ROI of the current frame  
    %contains zeros.
    %If a detection is present but the ROI values are zeros, this likely indicates an  
    %implementation error in function ROIMeans_FirstRead_TakeMeans. 
    %Note: IsMember is a custom function located within folder 'FacePulseRate'.
    if IsMember( ... if current frame corresponds to a detection detection
            RowToReturnBlockLinIdx_FR, ...
            ROIBlockDetectionFaceSkinLinIdx_FR, ...
            NDetectionsFaceSkin_FR ...
       ) && ... 
       ( ROINoPrevCallsBlock_FR(RowToReturnBlockLinIdx_FR, 1) == 0 || ... ROI of current frame contains zeros 
         ROINoPrevCallsBlock_FR(RowToReturnBlockLinIdx_FR, 2) == 0 || ...       
         ROINoPrevCallsBlock_FR(RowToReturnBlockLinIdx_FR, 3) == 0 || ...
         ROINoPrevCallsBlock_FR(RowToReturnBlockLinIdx_FR, 4) == 0 )  ...         
    

        %Throw error
        %Called as extrinsic so that stack trace can be displayed.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 3): The current frame appears to have a detection', ...
             ' but the ROINoMods input corresponding to the current frame contains a value of', ...
             ' zero. The frame index of the frame is: ', ...
             sprintf( '%d', int32( VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ... 
             '. Detected within function ROIMSIR.'] ...
        );     
    end            
    
%%%%%% --- Second-read setup %%%%%%    
    
%Use implementation for second-read operations. See notes at top of file.   

else

    %%%%%% >>>>>> Validate second-read inputs %%%%%%
    
    %Check whether type int16.
    %Must be an integer type because no rounding is conducted.
    %Should be type int16 because the function is implemented to assign values of this type.
    %A non-matching type would be due to an implementation error.
    if ~ isa(ROI(1, 1), 'int16')

        %Throw error
        %Called as extrinsic so that stack trace can be displayed.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 4): Variable ROI not type int16. Occurred during', ...
             ' ROI-modification operations during the second read. Detected within function', ... 
             ' ROIMSIR.'] ...
        );
    end   
    
    %%%%%% >>>>>> Handle case where no detections are present in ROIs to be processed %%%%%%

    %Operations cannot continue if no detections are present in the span of ROIs to be processed 
    %(the span of ROIs is indicated by the index BlockFullLinIdx_In).
    
    %Check whether at least one detection is present in span
    %Note: if there are not any face detections, there also will not be any skin detections as the 
    %skin-detection algorithm cannot be enabled without a certain number of face detections.
    if ~ ( any(HasROI_TF.FacePrimary(BlockFullLinIdx_In))    || ... primary face-detection algorithm
           any(HasROI_TF.FaceSecondary1(BlockFullLinIdx_In)) || ... secondary #1 face-detection algorithm
           any(HasROI_TF.FaceSecondary2(BlockFullLinIdx_In))    ... secondary #2 face-detection algorithm
         )
     
        %Assign output for second-read operations when no detection is present in span:
        
        %Note: in first-read operations, cases where no detections are available in the ROI block 
        %are handled in function ROIMSIR_InterpolateFR.
        
        %Note: function ROIMSIR_OutputIfNoDetections_SecondRead is a custom function located within
        %folder 'FacePulseRate'.
        [ROIOut_SR, ROIOutBeforeFrameByFrameSmoothing_SR, InterpolatedLinIdx_SR] = ...
            ROIMSIR_OutputIfNoDetections_SecondRead(BlockFullLinIdx_In, VidObjWidth, VidObjHeight);
                          
        %Exit function
        return
    end
    
    %%%%%% >>>>>> Assign additional second-read variables %%%%%%
    
    %Compared to first-read operations, the second-read operations do not need to use unmodified 
    %ROIs. The use of unmodified ROIs is only needed during the first-read operations because the
    %input of first-read operations is dependent on the output of previous calls; using unmodified 
    %ROIs prevents a positive feedback loop from developing (see note at top). However, this
    %dependency is not present for second-read operations, so unmodified ROIs are not needed.
    %Therefore, use modified ROIs (ROI) where the first-read operations uses unmodified ROIs
    %(ROINoMods). To keep variable names consistent across first-read and second-read operations, 
    %keep the name "ROINoMods" even though these ROIs have been modified.
    %M x 4 matrix; type int16.
    ROINoMods = ROI;

    %Assign ROIs from ROINoMods that will be used in most operations.
    %As with the rationale above, name the variable "ROINoPrevCallsBlock_SR" to be consistent with
    %first-read operations although the ROIs will have been the result of previous calls to the 
    %function (i.e., modified).
    %M x 4 matrix; type int16.
    ROINoPrevCallsBlock_SR = ROI(BlockFullLinIdx_SR, 1 : 4);        
    
    %Assign variables common to first-read and second-read operations:

    %Note: Of these variables, the same form of variables are used in the first-read operations   
    %(they would have the "_FR" suffix), but, unlike the variables in the first-read, the variables  
    %used in the second-read operations are of variable length.
    
    %ROIMSIR_AssignVars is a custom function located within folder 'FacePulseRate'
    [ROIBlock_SR, ROIBlockDetectionFaceLinIdx_SR, NDetectionsFace_SR, ...
     ROIBlockDetectionSkinLinIdx_SR, NDetectionsSkin_SR, ROIBlockDetectionFaceSkinLinIdx_SR, ...      
     NDetectionsFaceSkin_SR, ROIBlockNoDetectionFaceSkinLinIdx_SR, NNoDetectionsFaceSkin_SR, ...
     TimestampBlock_SR, TimestampBlockDetections_SR] = ...     
        ROIMSIR_AssignVars(BlockFullLinIdx_SR, ROI, HasROI_TF, Timestamp, FirstReadTF);            
end


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Match sizes ROIs to be more consistent across algorithms %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Match sizes of ROIs that correspond to detections to be more consistent across detection
%algorithms.

%Note: ROIMSIR_MatchSize is a custom function located within folder 'FacePulseRate'.

%First-read operations
if FirstReadTF

    %229 x 4 row vector; type int16.
    [ROINoPrevCallsBlock_FR, ROIMatchSizeData] = ...
        ROIMSIR_MatchSize(ROINoMods, ROINoPrevCallsBlock_FR, HasROI_TF, ...
            ROIBlockDetectionSkinLinIdx_FR, NDetectionsSkin_FR, ...
            ROIBlockDetectionFaceSkinLinIdx_FR, NDetectionsFaceSkin_FR, BlockFullLinIdx_FR, ... 
            VidObjWidth, VidObjHeight, FirstReadTF, SecondReadPostProcessingTF, ...
            FaceDetectConfig_ROIFaceSecondary1TF, FaceDetectConfig_ROIFaceSecondary2TF, ...
            VideoReadConfig_FrameIdx_FR, RowToReturnFullLinIdx_FR, ROIMatchSizeData, ...
            ExpectedBehaviorTestTF, FirstCallTF);           

%Second-read operations        
else

    %Note: during the second-read operations, the following arguments are entered but not used:
    %VideoReadConfig_FrameIdx_FR and RowToReturnFullLinIdx_FR.
    
    %Note: 0 was previously assigned to variable RowToReturnFullLinIdx_FR. 
 
    %M x 4 matrix; type int16.
    [ROINoPrevCallsBlock_SR, ROIMatchSizeData] = ...
        ROIMSIR_MatchSize(ROINoMods, ROINoPrevCallsBlock_SR, HasROI_TF, ...
            ROIBlockDetectionSkinLinIdx_SR, NDetectionsSkin_SR, ...
            ROIBlockDetectionFaceSkinLinIdx_SR, NDetectionsFaceSkin_SR,...
            BlockFullLinIdx_SR, VidObjWidth, VidObjHeight, FirstReadTF, ...
            SecondReadPostProcessingTF, FaceDetectConfig_ROIFaceSecondary1TF, ...
            FaceDetectConfig_ROIFaceSecondary2TF, VideoReadConfig_FrameIdx_FR, ...
            RowToReturnFullLinIdx_FR, ROIMatchSizeData, ExpectedBehaviorTestTF, FirstCallTF);        
end


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% ROI-detection smoothing %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Smooth ROIs that correspond to face-detection and skin-detection algorithm detections to help  
%remove the effect of false positives and to add stability. False positives may be reduced because   
%they sometimes occur as outliers, and smoothing should reduce the effect of outliers. Increasing   
%stability across ROIs may help keep the ROI more oriented on the same area of the face, which may  
%help increase accuracy of pulse rate calculations. Smooth with a moving mean. 

%In addition to smoothing the ROI matrix, also assign a new matrix where only ROIs that correspond
%to detections are included (NoPrevCallsBlock_ROIDetections_FR).

%Note: ROIMSIR_DetectionSmooth is a custom function located within folder 'FacePulseRate'.
  
%First-read operations
if FirstReadTF
       
    [ROINoPrevCallsBlock_FR,              ... 229 x 4 matrix; type int16
     NoPrevCallsBlock_ROIDetections_FR] = ... N detections (:229) x 4 matrix; type int16
        ROIMSIR_DetectionSmooth(ROINoPrevCallsBlock_FR, ROIBlockDetectionFaceLinIdx_FR, ...
            NDetectionsFace_FR, ROIBlockDetectionSkinLinIdx_FR, NDetectionsSkin_FR, ...
            ROIBlockDetectionFaceSkinLinIdx_FR, NDetectionsFaceSkin_FR, VidObjWidth, ...
            VidObjHeight, FaceDetectConfig_ROIFaceSmoothingWindow, ...
            SkinDetectConfig_ROISkinSmoothingWindow, FirstReadTF, SecondReadPostProcessingTF, ...
            VideoReadConfig_FrameIdx_FR, RowToReturnFullLinIdx_FR, ExpectedBehaviorTestTF);             
        
%Second-read operations        
else
 
    %Note: during the second-read operations, the following arguments are entered but not used:
    %VideoReadConfig_FrameIdx_FR and RowToReturnFullLinIdx_FR.
    
    %Note: 0 was previously assigned to variable RowToReturnFullLinIdx_FR.     

    [ROINoPrevCallsBlock_SR,              ... M x 4 matrix; type int16
     NoPrevCallsBlock_ROIDetections_SR] = ... N detections x 4 matrix; type int16
        ROIMSIR_DetectionSmooth(ROINoPrevCallsBlock_SR, ROIBlockDetectionFaceLinIdx_SR, ...
            NDetectionsFace_SR, ROIBlockDetectionSkinLinIdx_SR, NDetectionsSkin_SR, ...
            ROIBlockDetectionFaceSkinLinIdx_SR, NDetectionsFaceSkin_SR, VidObjWidth, ...
            VidObjHeight, FaceDetectConfig_ROIFaceSmoothingWindow, ...
            SkinDetectConfig_ROISkinSmoothingWindow, FirstReadTF, SecondReadPostProcessingTF, ...
            VideoReadConfig_FrameIdx_FR, RowToReturnFullLinIdx_FR, ExpectedBehaviorTestTF);             
end


%% %%%%%%%%%%%%%%%%%%
%%% Interpolation %%%
%%%%%%%%%%%%%%%%%%%%%

%Interpolate or extrapolate ROI(s) that do not have a corresponding face-detection or 
%skin-detection algorithm detection.

%Smooth ROIs that correspond to face-detection and skin-detection algorithm detections to help  
%remove the effect of false positives and to add stability. False positives may be reduced because   
%they sometimes occur as outliers, and smoothing should reduce the effect of outliers. Increasing  
%stability across ROIs may help keep the ROI more oriented on the same area of the face, which may 
%help increase accuracy of pulse rate calculations. Smooth with a moving mean.

%Note: in the first-read condition, tildes (~) indicate output arguments only used in second-read 
%operations; in the second-read condition, tildes indicate output arguments only used in first-read 
%operations.

%Note: ROIMSIR_Interpolate is a custom function located within folder 'FacePulseRate'.

%First-read operations
if FirstReadTF        
    
    [ROIOut_FR,             ... 1 x 4 row vector; type int16
     ~, ...
     InterpolatedLinIdx_FR, ... scalar; type int32
     ~] = ... 
        ROIMSIR_Interpolate(ROINoPrevCallsBlock_FR, NoPrevCallsBlock_ROIDetections_FR, ...
            BlockFullLinIdx_FR, ROIBlockDetectionFaceSkinLinIdx_FR, NDetectionsFaceSkin_FR, ...
            ROIBlockNoDetectionFaceSkinLinIdx_FR, NNoDetectionsFaceSkin_FR, TimestampBlock_FR, ...
            TimestampBlockDetections_FR, ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...
            ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, VidObjWidth, VidObjHeight, FirstReadTF, ...
            VideoReadConfig_FrameIdx_FR, ROINoResizeBlock_FR, RowToReturnFullLinIdx_FR, ...
            RowToReturnBlockLinIdx_FR, ROIMSIR_FirstFrameLinIdx_FR, ExpectedBehaviorTestTF);                                                  
        
%Second-read operations       
else
 
    %Note: during the second-read operations, the following arguments are entered but not used:
    %VideoReadConfig_FrameIdx_FR, ROINoResizeBlock_FR, RowToReturnFullLinIdx_FR,  
    %RowToReturnBlockLinIdx_FR, and ROIMSIR_FirstFrameLinIdx_FR.
    
    %Note: zero(s) were previously assigned for variables ROINoPrevCallsBlock_FR_Single,  
    %RowToReturnFullLinIdx_FR, RowToReturnBlockLinIdx_FR, and ROIMSIR_FirstFrameLinIdx_FR.

    [~, ...
     ROIOut_SR,               ... M x 4 matrix; type int16
     ~, ...
     InterpolatedLinIdx_SR] = ... M x 1 column vector; type int32
        ROIMSIR_Interpolate(ROINoPrevCallsBlock_SR, NoPrevCallsBlock_ROIDetections_SR, ... 
            BlockFullLinIdx_SR, ROIBlockDetectionFaceSkinLinIdx_SR, NDetectionsFaceSkin_SR, ...
            ROIBlockNoDetectionFaceSkinLinIdx_SR, NNoDetectionsFaceSkin_SR, TimestampBlock_SR, ...
            TimestampBlockDetections_SR, ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...
            ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, VidObjWidth, VidObjHeight, FirstReadTF, ...
            VideoReadConfig_FrameIdx_FR, ROINoResizeBlock_FR, RowToReturnFullLinIdx_FR, ...
            RowToReturnBlockLinIdx_FR, ROIMSIR_FirstFrameLinIdx_FR, ExpectedBehaviorTestTF);                            
end


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Frame-by-frame smoothing %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Smooth with nearby frames regardless of whether a face-detection or skin-detection algorithm
%detection is present in a given nearby frame. That is, include nearby frames even if they have
%been interpolated or extrapolated rather than contain an ROI from a detection. This criteria 
%differs from the detection-smoothing conducted previously.
%The objective is to increase stability in position (X- and Y-coordinates) and size (width and 
%height) across frames. The stability should better reflect actual head movements rather than
%sudden movements caused by extraneous factors, such as differences in ROIs due to the use of
%different algorithms or artifacts introduced by the previous smoothing and interpolation 
%operations. At the same time, over-smoothing should be avoided to allow the ROI to be responsive 
%to actual head movements across frames.

%Also return ROIs ROIOutBeforeFrameByFrameSmoothing(_FR/_SR) not modified by frame-by-frame 
%smoothing or resizing. The two operations that occured prior to these, size matching and detection 
%smoothing, are present. This permits diagnosis of false positives or false negatives resulting 
%from size matching and detection smoothing. The ROIs of these coordinates will be superimposed on 
%the output video for assessment. Note: the final ROIs differ from these only as a result of 
%receiving frame-by-frame smoothing and resizing. Hence, the final ROIs can be inspected to 
%diagnose false positives or false negatives resulting from frame-by-frame smoothing and resizing.

%Note: in the first-read condition, tildes (~) indicate output arguments only used in second-read 
%operations; in the second-read condition, tildes indicate output arguments only used in first-read 
%operations.

%Note: ROIMSIR_FrameByFrameSmooth is a custom function located within folder 'FacePulseRate'.

%For first-read operations 
if FirstReadTF                      
    
    [ROIOut_FR,                            ... 1 x 4 row vector; type int16
     ~, ...
     ROIOutBeforeFrameByFrameSmoothing_FR, ... 1 x 4 row vector; type int16
     ~] = ...
        ROIMSIR_FrameByFrameSmooth(ROIOut_FR, ROIOut_SR, ROINoPrevCallsBlock_FR, ...
            NoPrevCallsBlock_ROIDetections_FR, ROINoResizeBlock_FR, BlockFullLinIdx_FR, ...
            ROIBlockDetectionFaceSkinLinIdx_FR, NDetectionsFaceSkin_FR, ...
            ROIBlockNoDetectionFaceSkinLinIdx_FR, NNoDetectionsFaceSkin_FR, ROIBlock_FR, ...  
            TimestampBlock_FR, TimestampBlockDetections_FR, ...
            ROIGeneralConfig_ROIFinalSmoothingWindows, VidObjWidth, VidObjHeight, ...
            FirstReadTF, VideoReadConfig_FrameIdx_FR, RowToReturnFullLinIdx_FR, ...
            RowToReturnBlockLinIdx_FR, ROIMSIR_FirstFrameLinIdx_FR, ...
            ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...
            ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, ExpectedBehaviorTestTF);                        

%Second-read operations post-processing step       
elseif SecondReadPostProcessingTF
    
    %In the second-read operations, smooth ROIs near the beginning of the video based on recent  
    %skin-detection algorithm ROI detections made in the second read. To avoid smoothing ROIs   
    %twice, only smooth during the post-processing step (not the pre-processing step).
    
    %Note: checking whether the ROI was assigned as the full frame is not needed during the 
    %second-read operations because, if that were the case, function ROIMSIR would have already
    %exitted before this point is reached (see function ROIMSIR_OutputIfNoDetections_SecondRead).

    %Note: during the second-read operations, the following arguments are entered but not used:
    %ROINoResizeBlock_FR, VideoReadConfig_FrameIdx_FR, RowToReturnFullLinIdx_FR,  
    %RowToReturnBlockLinIdx_FR, ROIMSIR_FirstFrameLinIdx_FR.
    
    %Note: 0 was previously assigned for variables RowToReturnFullLinIdx_FR,
    %RowToReturnBlockLinIdx_FR, and ROIMSIR_FirstFrameLinIdx_FR.  
    
    [~, ...
     ROIOut_SR,                              ... M x 4 matrix; type int16
     ~, ...
     ROIOutBeforeFrameByFrameSmoothing_SR] = ... M x 4 matrix; type int16    
        ROIMSIR_FrameByFrameSmooth(ROIOut_FR, ROIOut_SR, ROINoPrevCallsBlock_SR, ...
            NoPrevCallsBlock_ROIDetections_SR, ROINoResizeBlock_FR, BlockFullLinIdx_SR, ... 
            ROIBlockDetectionFaceSkinLinIdx_SR, NDetectionsFaceSkin_SR, ...
            ROIBlockNoDetectionFaceSkinLinIdx_SR, NNoDetectionsFaceSkin_SR, ROIBlock_SR, ...
            TimestampBlock_SR, TimestampBlockDetections_SR, ...            
            ROIGeneralConfig_ROIFinalSmoothingWindows, VidObjWidth, VidObjHeight, FirstReadTF, ...
            VideoReadConfig_FrameIdx_FR, RowToReturnFullLinIdx_FR, RowToReturnBlockLinIdx_FR, ...
            ROIMSIR_FirstFrameLinIdx_FR, ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...
            ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, ExpectedBehaviorTestTF);                            
end


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Change size of ROI(s) according to ROIWidthResizeFactor and ROIHeightResizeFactor %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%ROIWidthResizeFactor and ROIHeightResizeFactor are arguments to function FacePulseRate.

%Only apply size adjustments to ROIs once. To do so, apply when the call is from the first read or 
%when the call is from second read during the post-processing (but not pre-processing) step.
%Note: during the first read, called by function ROIMeans_FirstRead_TakeMeans; during the second  
%read, called by function ROIMeans_SecondRead.    

%Function ROIResize scales ROI as specified and also prevents scaled ROI from exceeding frame
%dimensions.

%Note: ROIResize is a custom function located within folder 'FacePulseRate'.

%For calls during first read
if FirstReadTF

    %1 x 4 row vector; int16.
    ROIOutNoResize_FR = ROIOut_FR;

    %If at least one ROI within the block corresponds to a detection
    %Otherwise, the ROI will have been assigned as the full frame dimensions (see function
    %ROIMSIR_InterpolateFR).
    if NDetectionsFaceSkin_FR ~= 0 
      
        %Resize the ROI
        %1 x 4 row vector; int16.
        ROIOut_FR = ...
            ROIResize( ...
                ROIOut_FR,                              ... ROI(s) to adjust; type int16
                int32(1),                               ... ROI index (1 entered if only 1 ROI); 
                                                        ... type int32.
                ROIGeneralConfig_ROIWidthResizeFactor,  ... Width resizing scale factor; type 
                                                        ... double
                ROIGeneralConfig_ROIHeightResizeFactor, ... Height resizing scale factor; type 
                                                        ... double.
                VidObjWidth,                            ... To keep adjustment within frame 
                                                        ... dimensions; type int16.
                VidObjHeight                            ...             
            );
    end
    
%For call during the second read post-processing step    
elseif SecondReadPostProcessingTF

    %Note: checking whether the ROI was assigned as the full frame is not needed during the 
    %second-read operations because, if that were the case, function ROIMSIR would have already
    %exitted before this point is reached (see function ROIMSIR_OutputIfNoDetections_SecondRead).       
        
    FramesToAdjust = int32(1) : size(ROIOut_SR, 1);

    %Resize the ROI
    %M x 4 matrix; int16.
    ROIOut_SR = ...
        ROIResize( ...
            ROIOut_SR,                              ... ROI(s) to adjust; type int16
            FramesToAdjust,                         ... ROI index (1 entered if only 1 ROI);  
                                                    ... type int32.
            ROIGeneralConfig_ROIWidthResizeFactor,  ... Width resizing scale factor; type 
                                                    ... double.
            ROIGeneralConfig_ROIHeightResizeFactor, ... Height resizing scale factor; type 
                                                    ... double.
            VidObjWidth,                            ... To keep adjustment within frame  
                                                    ... dimensions; type int16.
            VidObjHeight                            ...             
        );                
end


%% %%%%%%%%%%%%%%%%%%%%%%
%%% Output validation %%%
%%%%%%%%%%%%%%%%%%%%%%%%%

%Validate output arguments.
%This validation provides a safeguard against unexpected errors that may arise from implementation
%changes.

%Note: ROIMSIR_OutputValidate is a custom function located within folder 'FacePulseRate'.
ROIMSIR_OutputValidate(FirstReadTF, ROIOut_FR, ROIOut_SR, VideoReadConfig_FrameIdx_FR, ...
    RowToReturnFullLinIdx_FR, ExpectedBehaviorTestTF);
    

end %end function 


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(ROIMSIR_mex) of the function.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%Specify struct variable-size element properties
Element1 = ...
    coder.typeof(false(500, 1), ... example code
                 [inf, 1],      ... upper bounds
                 [1, 0]         ... variable size (T/F)
    );

%Struct with variable-size elements
%Note: the number, names, and order of fields are compile-time constants.

HasROI_TFCode = ...
    struct( ...  
        'FacePrimary',                      Element1, ...
        'FacePrimaryAttempted',             Element1, ...
        'SkinNotPresent_Pri',               Element1, ...
        'ProfileEyesPresent_Pri',           Element1, ...
        'FaceSecondary1',                   Element1, ...
        'FaceSecondary1Attempted',          Element1, ...
        'SkinNotPresent_Sec1',              Element1, ...
        'ProfileEyesPresent_Sec1',          Element1, ...
        'FaceSecondary2',                   Element1, ...
        'FaceSecondary2Attempted',          Element1, ...
        'SkinNotPresent_Sec2',              Element1, ...
        'ProfileEyesPresent_Sec2',          Element1, ...
        'Skipped',                          Element1, ...
        'Skin',                             Element1, ...
        'SkinAttempted',                    Element1, ...
        'SkinNotPresent_Skin',              Element1, ...
        'Interpolated',                     Element1, ...      
        'AdjustedBecauseLowSkinProportion', Element1, ...
        'ROISpecifiedByArgument',           Element1, ...
        'ROIIgnoreByArgument',              Element1 ...
    );

%                                               Example Code               Upp. Bounds  Var. Size (T/F)  Type
BlockFullLinIdx_InCode          = coder.typeof( zeros(500, 1, 'int32'),    [inf, 1],    [1, 0] );        %int32
ROICode                         = coder.typeof( zeros(500, 4, 'int16'),    [inf, 4],    [1, 0] );        %int16
TimestampCode                   = coder.typeof( zeros(500, 1, 'single'),   [inf, 1],    [1, 0] );        %single 
VideoReadConfig_FrameIdx_FRCode = coder.typeof( zeros(1, 500, 'int32'),    [1, inf],    [0, 1] );        %int32
ROINoModsCode                   = coder.typeof( zeros(500, 4, 'int16'),    [inf, 4],    [1, 0] );        %int16
ROINoResizeCode                 = coder.typeof( zeros(500, 4, 'int16'),    [inf, 4],    [1, 0] );        %int16
          
      
%%%%%% Specify fixed-size input arguments %%%%%%

ROIGeneralConfig_ROIMSIR_DiffMaxDetectionCode = int16(0);
ROIGeneralConfig_ROIMSIR_DiffMaxAdjacentCode  = int16(0);
ROIGeneralConfig_ROIWidthResizeFactorCode     = double(0);
ROIGeneralConfig_ROIHeightResizeFactorCode    = double(0);
FaceDetectConfig_ROIFaceSmoothingWindowCode   = double(0);
FaceDetectConfig_ROIFaceSecondary1TFCode      = false;
FaceDetectConfig_ROIFaceSecondary2TFCode      = false;
SkinDetectConfig_ROISkinSmoothingWindowCode   = double(0);
ROIGeneralConfig_ROIFinalSmoothingWindowsCode = zeros(1, 2, 'int32');
VidObjWidthCode                               = int16(0);         
VidObjHeightCode                              = int16(0);
ExpectedBehaviorTestTFCode                    = false;
FirstReadTFCode                               = false;
FirstCallTFCode                               = false;  
RowToReturnFullLinIdx_FRCode                  = int32(0);
FirstFrameMSIRLinIdx_FRCode                   = int32(0);
SecondReadPostProcessingTFCode                = false;                           

ROIMatchSizeDataCode = ...
    struct( ...
        'SumW_Pri', single(0), ...
        'SumH_Pri', single(0), ...
        'AlgN_Pri', single(0), ...
        'ROIMeanWidthPri', single(0), ...
        'ROIMeanHeightPri', single(0), ...
        'SumW_Sec1', single(0), ... 
        'SumH_Sec1', single(0), ...
        'AlgN_Sec1', single(0), ...
        'ROIMeanWidthSec1', single(0), ...
        'ROIMeanHeightSec1', single(0), ...
        'SumW_Sec2', single(0), ...
        'SumH_Sec2', single(0), ...
        'AlgN_Sec2', single(0), ...
        'ROIMeanWidthSec2', single(0), ...
        'ROIMeanHeightSec2', single(0), ...
        'SumW_Skin', single(0), ...
        'SumH_Skin', single(0), ...
        'AlgN_Skin', single(0), ...
        'ROIMeanWidthSkin', single(0), ...
        'ROIMeanHeightSkin', single(0) ... 
    );        


%%%%%% Set configurations to increase performance %%%%%%

%Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic 
%"Optimization Strategies"

cfg = coder.config('mex');
cfg.GlobalDataSyncMethod = 'NoSync';
cfg.ConstantInputs = 'IgnoreValues';
cfg.ExtrinsicCalls = true; %permit extrinsic calls to permit functions warning() and error() to operate
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

%Argument buildInfo: this variable is assign by the caller (the codegen command executed below) and 
%is not present in the base workspace.

%Second argument: specify a cell array of compiler-specific flags, where each flag is a character 
%vector. As function setbuildargs will be evaluated from text, use double ' quotes for each
%character vector to maintain the charater vector,
%e.g., {''-Ofast'' ''-fsingle-precision-constant''}.

setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})';

%Assign to code-generation configuration object
cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen ROIMSIR.m -report -config cfg -args {BlockFullLinIdx_InCode, ROICode, TimestampCode, HasROI_TFCode, ROIGeneralConfig_ROIMSIR_DiffMaxDetectionCode, ROIGeneralConfig_ROIMSIR_DiffMaxAdjacentCode, ROIGeneralConfig_ROIWidthResizeFactorCode, ROIGeneralConfig_ROIHeightResizeFactorCode, FaceDetectConfig_ROIFaceSmoothingWindowCode, FaceDetectConfig_ROIFaceSecondary1TFCode, FaceDetectConfig_ROIFaceSecondary2TFCode, SkinDetectConfig_ROISkinSmoothingWindowCode, ROIGeneralConfig_ROIFinalSmoothingWindowsCode, VidObjWidthCode, VidObjHeightCode, ExpectedBehaviorTestTFCode, FirstReadTFCode, FirstCallTFCode, VideoReadConfig_FrameIdx_FRCode, RowToReturnFullLinIdx_FRCode, FirstFrameMSIRLinIdx_FRCode, ROINoModsCode, ROINoResizeCode, ROIMatchSizeDataCode, SecondReadPostProcessingTFCode}
                
%}

