function FrameCropped_Markers = ...
             insertMarkerFast(FrameCropped_Markers, MarkerPointsXY_Cropped, MarkerSize) %#codegen
%insertMarkerFast   Code-generation for function insertMarker for inserting green and white stars.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_SkinDetectDiagnosis.
%
%
%    Code Generation
%    ---------------
%
%    This function intended only for code generation (C language).
%
%    Compiled file: 
%
%    The compiled file included in folder FacePulseRate (insertMarkerFast_mex.mexw64) only  
%    compatible on Windows platforms.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in a commercial  
%    licensing, please contact the author.


%Specify inlining for faster code execution
coder.inline('always');


%Specify variable-size output arguments 
%                                     Upp. Bounds     Var. Size (T/F)
coder.varsize('FrameCropped_Markers', [inf, inf, 3],  [1, 1, 0]);


%Insert marker shapes to cropped frame
%Note: function insertMarkerNoValidation is a custom version of function insertMarker with input
%validation and unused options removed for efficiency.
FrameCropped_Markers = ...
    insertMarkerNoValidation(FrameCropped_Markers,     ... specify image where marker annotation inserted
        MarkerPointsXY_Cropped,    ... [X, Y] marker origins; Nmarkers-by-2 matrix 
        '*',                       ... marker type (star)
        'color', [0,   255, 0;     ... colors of markers [green, white]
                  255, 255, 255],  ...
        'size', MarkerSize);       %   size of markers


end %end function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(insertMarkerFast_mex) of the function.

%{

%%%%%% Modify function files for performance %%%%%%

%Before running code generation, input validation was removed from the file for function 
%insertMarker. The modified file was saved as insertMarkerNoValidation.p, which is located in 
%folder 'Validation_Removed'. The code is obscured (as p-code) to comply with the Matlab licensing 
%agreement, which does not permit the distribution of Matlab source code. To permit code generation 
%from the p-code, the statement coder.allowpcode('plain') was included in 
%insertMarkerNoValidation.m before obfuscation. DPM possesses the un-obfuscated files.


%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%                                          Example Code                  Upp. Bounds      Var. Size (T/F)  Type
FrameCropped_MarkersCode   = coder.typeof( zeros(500, 500, 3, 'uint8'),  [inf, inf, 3],   [1, 1, 0] );     %uint8
                    

%%%%%% Specify fixed-size input arguments %%%%%%

MarkerPointsXY_CroppedCode = zeros(2, 2, 'int16');                                            
MarkerSizeCode             = double(1);                                                                  


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

codegen insertMarkerFast.m -report -config cfg -args {FrameCropped_MarkersCode, MarkerPointsXY_CroppedCode, MarkerSizeCode}

%}



