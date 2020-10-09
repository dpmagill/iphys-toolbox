function ROIMSIR_OutputValidate(FirstReadTF, ROIOut_FR, ROIOut_SR, VideoReadConfig_FrameIdx_FR, ... 
             RowToReturnFullLinIdx_FR, ExpectedBehaviorTestTF) %#codegen
%ROIMSIR_OutputValidate    Validate output arguments in function ROIMSIR.
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
%    Validate output arguments in function ROIMSIR.
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
%See note where warning() is used.
coder.extrinsic('warning');

%Call function as extrinsic so that stack trace can be displayed
coder.extrinsic('error');


%%%%%% For first-read operations %%%%%%

if FirstReadTF

    %Assert empty size for ROIOut_SR as this variable not used in first-read operations
    assert( all( size(ROIOut_SR) == [0, 4] ) ); 
    
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
            ['Internal Error (ROIMSIR, code 29): ROI-modification operations assigned a value', ...
             ' of zero for an ROI. ROI accuracy may be affected. The frame index of', ...
             ' corresponding frame is: ', ...
             sprintf( '%d', int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ... 
             '. Detected within function ROIMSIR in function ROIMSIR_OutputValidate.'] ...
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
       (ROIOut_FR(3) < 20 || ROIOut_FR(4) < 20)

        %Note: function warning() not available for code generation, so it must have previously
        %been declared as extrinsic.
        %Function fprintf can not be used as a substitute for warning() in this case because 
        %fprintf can not accept variable-length arguments.        
        warning( ...
            'Component:InternalError', ...
            ['Potential Internal Error (ROIMSIR, code 30): ROI-modification operations', ...
             ' assigned a size value for an ROI that is below 20 pixels, which is likely', ...
             ' inaccurate. ROI accuracy may be affected. The frame index of corresponding', ...
             ' frame is: ',  ...
             sprintf( '%d', int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ... 
             '. Detected within function ROIMSIR in function ROIMSIR_OutputValidate.'] ...
        );             
    end 
 
    %Check whether ROI type not int16 because other functions are implemented to accept values of  
    %this type. 
    %A non-matching type would be due to an implementation error.
    if ~ isa(ROIOut_FR(1, 1), 'int16')
 
        %Throw error
        %Called as extrinsic so that stack trace can be displayed.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 31): ROI assigned type other than int16 during', ...
             ' ROI-modification operations. Occurred during first-read operations in frame', ...
             ' index ', ...
             sprintf( '%d', int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ...
             '. Detected within function ROIMSIR in function ROIMSIR_OutputValidate.'] ...            
        );           
    end
    
    
%%%%%% For second-read operations %%%%%%    

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
            ['Potential Internal Error (ROIMSIR, code 32): ROI-modification operations', ...
             ' assigned a size value for an ROI that is below 20 pixels, which is likely', ...
             ' inaccurate. ROI accuracy may be affected. Occurred during the second-read', ... 
             ' operations. Detectedwithin function ROIMSIR in function', ...
             ' ROIMSIR_OutputValidate.'] ...
        );          
    end
    
    %Check if ROI type not int16 because other functions are implemented to accept values of this 
    %type. 
    %A non-matching type would be due to an implementation error.
    if ~ isa(ROIOut_SR(1, 1), 'int16')
        
        %Throw error
        %Called as extrinsic so that stack trace can be displayed.
        error( ...
            'Component:InternalError', ...
            ['Internal Error (ROIMSIR, code 33): ROI assigned type other than int16. Occurred', ...
             ' during ROI-modification operations during the second read. Detected within', ... 
             ' function ROIMSIR in function ROIMSIR_OutputValidate.'] ...
        );
    end
end


end %end function

