function [FrameCropped_BulletPoints] = ...
             insertShapeFast_FilledCircles(FrameCropped_BulletPoints, ...
                 BulletPointsXYR_Cropped) %#codegen
%insertShapeFast_FilledCircles    Code generation for function insertShape for inserting black
%                                 filled circles.
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
%     - The compiled file included in folder FacePulseRate    
%       (insertShapeFast_FilledCircles_mex.mexw64) only compatible on Windows platforms. 
%     - This function uses a bounded variable size for variable BulletPointsXYR_Cropped to improve  
%       efficiency. Ensure that this variable does not exceed these bounds.
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
%For variable 'bulletpointPointsXY', set a bound on the number of rows (which corresponds to the
%number of bullet points) to prevent dynamic memory allocation, which should increase performance.
%                                           Upp. Bounds     Var. Size (T/F)
coder.varsize('FrameCropped_BulletPoints',  [inf, inf, 3],  [1, 1, 0]);
coder.varsize('BulletPointsXYR_Cropped',    [50, 3],        [1, 0]);


%Insert filled circles (bullet points) corresponding to the positions of the text labels
%Note: function insertShapeNoValidation is a custom version of function insertShape with input
%validation and unused options removed for efficiency.
FrameCropped_BulletPoints = ...
    insertShapeNoValidation(FrameCropped_BulletPoints, ... specify image where shape annotation inserted
        'FilledCircle',           ... shape
         BulletPointsXYR_Cropped, ... M-by-3 matrix; row = [X, Y, radius]
         'Color', [0, 0, 0],      ... shape color: black
         'Opacity', 1,            ... opacity of 1 is a solid color
         'SmoothEdges', false);   %   disable anti-aliasing filter to save processing time    


end %end function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(insertShapeFast_FilledCircles_mex) of the function.

%{

%%%%%% Modify function files for performance %%%%%%

%Before running code generation, input validation was removed from the file for function 
%insertShape. The modified file was saved as insertShapeNoValidation.p, which is located in 
%folder 'Validation_Removed'. The code is obscured (a p-code )to comply with the Matlab licensing 
%agreement, which does not permit the distribution of Matlab source code. To permit code generation 
%from the p-code, the statement coder.allowpcode('plain') was included in insertShapeNoValidation.m 
%before obfuscation. DPM possesses the un-obfuscated files.


%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%                                              Example Code                  Upp. Bounds      Var. Size (T/F)  Type
FrameCropped_BulletPointsCode  = coder.typeof( zeros(500, 500, 3, 'uint8'),  [inf, inf, 3],   [1, 1, 0] );     %uint8
BulletPointsXYR_CroppedCode    = coder.typeof( zeros(50, 3, 'int16'),        [50, 3],         [1, 0] );        %int16                  
 

%%%%%% Set configurations to increase performance %%%%%%

%Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic 
%"Optimization Strategies"

%"Optimization Strategies"
cfg = coder.config('mex');
cfg.SaturateOnIntegerOverflow = false;
cfg.IntegrityChecks = false;
%Note: the following options were not changed because they were observed to add a slight increase
%in execution time:
%cfg.GlobalDataSyncMethod = 'NoSync';
%cfg.ConstantInputs = 'IgnoreValues';
%cfg.ResponsivenessChecks = false;


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

%Second argument: specify a cell array of compiler-specific flags, where each flag is a each 
%character vector. As function setbuildargs will be evaluated from text, use double ' quotes for 
%character vector to maintain the charater vector,
%e.g., {''-Ofast'' ''-fsingle-precision-constant''}.

setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})';

%Assign to code-generation configuration object
cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen insertShapeFast_FilledCircles.m -report -config cfg -args {FrameCropped_BulletPointsCode, BulletPointsXYR_CroppedCode}

%}
      


