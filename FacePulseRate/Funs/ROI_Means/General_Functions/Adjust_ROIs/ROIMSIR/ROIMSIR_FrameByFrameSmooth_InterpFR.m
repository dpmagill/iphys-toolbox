function ROIBlockFrameByFrameSmooth = ...
             ROIMSIR_FrameByFrameSmooth_InterpFR(ROIBlockFrameByFrameSmooth, ...
                FramesBeforeFirstCallTF, FirstFrameMSIRBlockLinIdx_FR, ...
                ROIBlockNoDetectionFaceSkinLinIdx, NNoDetectionsFaceSkin, ...
                PrevToCurrentBlockLinIdx, NPrevToCurrentBlockLinIdx, ...
                NoPrevCallsBlock_ROIDetections, NDetectionsFaceSkin, ...
                VideoReadConfig_FrameIdx_FR, RowToReturnFullLinIdx_FR, TimestampBlock, ...                
                TimestampBlockDetections, ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...                                
                ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, VidObjWidth, VidObjHeight, ...
                ExpectedBehaviorTestTF) %#codegen                                                 
%ROIMSIR_FrameByFrameSmooth_InterpFR    Interpolate frames with unassigned ROIs for frame-by-frame
%                                       smoothing operations during the first-read operations. 
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
%    Description
%    -----------
% 
%    Frame-by-frame smoothing attempts to smooth across all ROIs. An ROI from any previous frame 
%    can be included because all previous frames will have a non-zero ROI. Specifically, previous 
%    frames without a detection would have received an interpolated/exterpolated ROI from a      
%    previous call to function ROIMSIR_FrameByFrameSmooth. Frames that occur after the current 
%    frame that do not have a detection will contain zeros as interpolation / extrapolation has not 
%    yet been performed on them. To remedy this, perform interpolation / extrapolation for the 
%    frames after the current frame that will be included in the smoothing. Any ROIs interpolated /
%    extrapolated here will only be used for the purpose of frame-by-frame smoothing in function
%    ROIMSIR_FrameByFrameSmooth_SmoothFR and will not be assigned to a persistent ROI matrix.
%
%    Interpolate / extrapolate X-coordinate, Y-coordinate, width, and height of the ROIs.
%    Some frames may not contain enough nearby frames for accurate interpolation or extrapolation,
%    so use a method more conservative than PCHIP: the linear method. 
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

%Declare variables and extrinsic functions:

%Note: constant 229 assumes that the length of BlockFullLinIdx == 229. If the length of this 
%variable were to change, the constant would need to be modified.

%                                                         Upp. Bounds  Var. Size (T/F)
coder.varsize('ROIBlockBeforeFirstCallNoDetectionLinIdx', [229, 1],    [1, 0]);
coder.varsize('InterpTheseLinIdx',                        [229, 1],    [1, 0]);

%Declare function as extrinsic
%See notes where warning() used.
coder.extrinsic('warning'); 

%Call function as extrinsic so that stack trace can be displayed
coder.extrinsic('error');


%%%%%% Setup for interpolation / extrapolation %%%%%%

%Preallocate variables:

%Note: regarding "coder.nullcopy", see Matlab documentation topic "Eliminate Redundant Copies of 
%Variables in Generated Code".

ROIBlockBeforeFirstCallNoDetectionLinIdx = coder.nullcopy( zeros(0, 1, 'int32') );

%%%%%% --- Determine frames before first call to function that do no have a detection %%%%%%

%Check whether block contains ROIs of frames for which the current function was not previously
%called. To do so, determine whether any frames in the current block come before the index
%specified by FirstFrameMSIRLinIdx_FR; this index specifies the first frame that was called by the
%function.

%Of these ROIs, if an ROI does not have a detection, it will be zero as the current function did 
%not previously apply interpolation / extrapolation to it. For these ROIs, determine which do not
%have a detection so that interpolation / extrapolation can be applied to them. 

%Determine which of these frames do not have a detection
if FramesBeforeFirstCallTF

    %Linear index of frames before first call that do not have a detection 
    if NNoDetectionsFaceSkin ~= 0

        %Column vector; type int32.
        ROIBlockBeforeFirstCallNoDetectionLinIdx = ...
            ROIBlockNoDetectionFaceSkinLinIdx( ...
                ROIBlockNoDetectionFaceSkinLinIdx < FirstFrameMSIRBlockLinIdx_FR ...
            );           
    end
end

%%%%%% --- Determine frames after current frame that do no have a detection %%%%%%

%These ROIs are zeros because the function has not yet been called for these ROIs, so they could 
%not have been interpolated / extrapolated yet.        

%Linear index of ROIs after current frame that do not have a detection
%Note: SetDiff is a custom function located within folder 'FacePulseRate'.
ROIBlockAfterCurrentNoDetectionFaceSkinLinIdx = ...
    SetDiff(ROIBlockNoDetectionFaceSkinLinIdx, NNoDetectionsFaceSkin, PrevToCurrentBlockLinIdx, ...
        NPrevToCurrentBlockLinIdx);

%%%%%% Interpolation / extrapolation %%%%%%

%If any ROIs need to be interpolated / extrapolated
if ~ isempty(ROIBlockBeforeFirstCallNoDetectionLinIdx) || ...
   ~ isempty(ROIBlockAfterCurrentNoDetectionFaceSkinLinIdx) 

    %%%%%% --- Interpolation / extrapolation %%%%%%

    %Frames to be interpolated / extrapolated
    %Note: the concatenated variable should have values in order from least to greatest.
    InterpTheseLinIdx = ...
        [ROIBlockBeforeFirstCallNoDetectionLinIdx; ...
         ROIBlockAfterCurrentNoDetectionFaceSkinLinIdx];

    %Timestamps within block corresponding to frames to be interpolated / extrapolated 
    %Column vector; type single.
    TimestampInterpThese = TimestampBlock(InterpTheseLinIdx);  

    %NoPrevCallsBlock_ROIDetections = ROIs in block corresponding to frames with a detection. ROIs 
    %                                 are taken from ROINoPrevCallsBlock rather than ROIBlock. This
    %                                 prevents a positive feedback loop from developing across 
    %                                 sequential calls to the function (see note in the file for 
    %                                 function ROIMSIR). 
    %                                 M x 4 matrix; type int16.
  
    %Verify that ROIs to be included in interpolation / extrapolation do not contain zeros (that 
    %is, the ROIs for interpolation, not receiving interpolation; ROIs receiving interpolation will
    %be zero). Interpolation / extrapolation is intended to be conducted only with non-zeros ROIs.    
    %Such a value is likely due to an implementation error in this function.
    
    %Loop across columns
    for i = int32(1) : 4
  
        %Loop across rows
        for j = 1 : NDetectionsFaceSkin

            if NoPrevCallsBlock_ROIDetections(j, i) == 0 
                
                %Throw exception
                %Called as extrinsic so that stack trace can be displayed.
                error( ...
                    'Component:InternalError', ...
                    ['Internal Error (ROIMSIR, code 20): Interpolation operation conducted', ...
                     ' with ROIs that contain zeros at frame ', ...
                     sprintf( '%d', ...
                         int32( VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR) ) ...
                      ), ...
                     '. Smoothing accuracy may be affected. Detected within function ROIMSIR ', ... 
                     ' in function ROIMSIR_FrameByFrameSmooth_Interp.'] ...
                );                
            end
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
       any( NoPrevCallsBlock_ROIDetections(:, 3 : 4) < 20, 'all' )

        %Display warning indicating frame index

        %Note: function warning() not available for code generation, so it must have previously
        %been declared as extrinsic.
        %Function fprintf can not be used as a substitute for warning() in this case because 
        %fprintf can not accept variable-length arguments.       
        warning( ...
            'Component:InternalError', ...
            ['Potential Internal Error (ROIMSIR, code 21): Interpolation operations conducted', ...
             ' with ROIs with size values below 20 pixels, which is likely inaccurate.', ...
             ' ROI accuracy may be affected. The frame index of corresponding frame is: ', ...
             sprintf( '%d', int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ... 
             '. Detected within function ROIMSIR in function', ...
             ' ROIMSIR_FrameByFrameSmooth_Interp.'] ...
        ); 
    end                      

    %Enable validity checks of interpolated / extrapolated ROI(s)
    %Note: see the description in function ROIMSIR_Interpolate.
    ValidityChecksTF = true;
    
    %Enable the use of the linear method for extrapolation.
    %Note: see the description in function ROIMSIR_Interpolate.    
    LinearExtrapTF = true;    
        
    %229 x 4 matrix; type int16
    %Note: for a description of the arguments to function Interp, see the description in 
    %function ROIMSIR_Interpolate.
    %Note: Interp is a custom function located within folder 'FacePulseRate'.
    ROIBlockFrameByFrameSmooth(InterpTheseLinIdx, :) = ... Interp/extrap ROIs
        Interp( ... 
            TimestampBlockDetections,                  ... Time points used for interp/extrap; M x   
                                                       ... 1 column vctor, type single.
            NoPrevCallsBlock_ROIDetections,            ... ROIs used for interp/extrap; M x 4  
                                                       ... matrix, type int16.
            TimestampInterpThese,                      ... Time points at which interp/extrap to be  
                                                       ... assigned; M x 1 column vector, type  
                                                       ... single.
            LinearExtrapTF,                            ... Flag whether to use linear method for 
                                                       ... extrapolation.
            ValidityChecksTF,                          ... Flag whether to check if interpolated /  
                                                       ... extrapolated values seem reasonable. 
            ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ... The threshold specifying the maximum 
                                                       ... absolute-value difference between an 
                                                       ... interpolated / extrapolated value and    
                                                       ... the ROI corresponding to the 
                                                       ... temporally-nearest previous detection. 
            zeros(0, 2, 'int16'),                      ... Empty = do not conduct adjacent ROI 
                                                       ... check.
            int16(0),                                  ... Unused argument for adjacent-ROI check.
            VidObjWidth, ...
            VidObjHeight ...
        );            

    %%%%%% --- X- and Y-coordinates adjacent ROI check and adjustment %%%%%%    
       
    %*** Testing in progress ***

    %Note: a suitable implementation has not yet been identified.

    %{
    
    %Recall that the purpose of interpolating these ROIs is to predict what ROIs function
    %ROIMSIR_Interpolate will return in later calls. As ROIMSIR_Interpolate will conduct adjacent 
    %ROI checks and adjustments, they are conducted here to increase the prediction accuracy. 
    
    %If the linear index of interpolated ROIs includes 1        
    if InterpTheseLinIdx(1) == 1

        %Exclude 1 from the loop as the first ROI cannot be compared to a previous ROI
        Start = int32(2);

    else

        Start = int32(1);
    end

    Interp_Length = int32( length(InterpTheseLinIdx) );
    
    %Assert value to prevent dymanic memory allocation when the colon operator is used
    assert(Interp_Length <= 229);

    ROIBlockFrameByFrameSmoothAdjust = zeros(Interp_Length, 2, 'int16');
    
    %Loop across X-coordinate and Y-coordinate columns
    for i = 1 : 2 

        %Loop across ROI rows corresponding to frames that were interpolated / extrapolated
        for j = Start : Interp_Length 

            jj = InterpTheseLinIdx(j);  

            %Find difference between jjth and jj-1th rows
            %Type int16.
            Diff = ROIBlockFrameByFrameSmooth(jj, i) - ROIBlockFrameByFrameSmooth(jj - 1, i);

            %If difference greater than threshold
            if Diff > ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent   
                
                %Replace with jj-1th plus threshold
                ROIBlockFrameByFrameSmoothAdjust(j, i) = ...
                    ROIBlockFrameByFrameSmooth(jj - 1, i) + ...
                    ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent;        

            %If difference less than negative of threshold
            elseif Diff < -ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent

                %Replace with jj-1th minus threshold
                ROIBlockFrameByFrameSmoothAdjust(j, i) = ...
                    ROIBlockFrameByFrameSmooth(jj - 1, i) - ...
                    ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent;            
            end                                 
        end
    end  
    
    for i = 1 : 2

        for j = Start : Interp_Length

            jj = InterpTheseLinIdx(j);

            ji = ROIBlockFrameByFrameSmoothAdjust(j, i);
            
            if ji ~= 0
                
                ROIBlockFrameByFrameSmooth(jj, i) = ji;
            end
        end
    end   
    
    %}
    
    %*** End testing ***
end   


end %end function

