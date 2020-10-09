function VidFrame = ...
             insertTextFast_Font13LT(VidFrame, TextXY, Text, textColor, BoxColor) %#codegen
%insertTextFast_Font13LT   Code-generation version of insertText function using font size of 13 and
%                          positioned such that the [X, Y] coordinates are to the left-top relative 
%                          to the text.                          
%                                      
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function WriteFaceVideo_SkinDetectDiagnosis.
% 
%    Code generation: This function only intended to be used for code generation (C-language).
%
%    Compiled file: The compiled file included in folder FacePulseRate    
%    (insertTextFast_Font13LT_mex.mexw64) only compatible on Windows platforms.


%Note: in this case, using the same variable name for the input and output arguments results in
%faster code execution. This may be because the variable is passed by reference rather than value. 

%Specify inlining for faster code execution
coder.inline('always');

%Specify variable output arguments for use in compilation
%                                  Upp. Bounds       Var. Size (T/F)
coder.varsize('VidFrame',          [inf, inf, 3],    [1, 1, 0]);

%Insert text labels on the video frame
%Note: function insertTextNoValidation is a custom version of function insertText with 
%input validation removed for efficiency.
VidFrame = ...
    insertTextNoValidation(VidFrame, ... specify image where text annotation inserted
        TextXY,                      ... [X, Y] coordinates for M regions: M-by-2 matrix
        Text,                        ... text for M regions: M-by-1 cell array
        'TextColor', textColor,      ... colors for M regions: M-by-3 matrix
        'FontSize', 13,              ... font size; must be constant for code generation.
        'BoxOpacity', 0.5,           ... background opacity: 1 indicates a solid color
        'BoxColor', BoxColor,        ... Note: white has been observed to cause unexpected colors to appear.
        'AnchorPoint', 'LeftTop');   %   [X, Y] coordinates position relative to text; must be  
                                     %   constant for code generation.
                                                                       
end %end function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(insertTextFast_Font13LT_mex) of the function.

%{

%%%%%% Modify function files for performance %%%%%%

%Before running code generation, input validation was removed from the file for function 
%insertText. The modified file was saved as insertTextNoValidation.p, which is located in folder
%'Validation_Removed'. The code is obscured (as p-code) to comply with the Matlab licensing 
%agreement, which does not permit the distribution of Matlab source code. To permit code generation 
%from the p-code, the statement coder.allowpcode('plain') was included in insertTextNoValidation.m 
%before obfuscation. 


%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%Specify cell array element properties
%Note: the cell array will have the following properties:
%   :inf×1 homogeneous cell 
%        base: 1×:inf char
Element1 = ...
    coder.typeof('',      ... example code
                 [1 inf], ... upper bounds
                 [0, 1]   ... variable size (T/F)
    );

%                                  Example Code                  Upp. Bounds      Var. Size (T/F)  Type
VidFrameCode       = coder.typeof( zeros(500, 500, 3, 'uint8'),  [inf, inf, 3],   [1, 1, 0] );     %uint8
TextXYCode         = coder.typeof( zeros(5, 2, 'int16'),         [inf, 2],        [1, 0] );        %int16
TextCode           = coder.typeof( {Element1},                   [inf, 1],        [1, 0] );        %cell; elements: char
textColorCode      = coder.typeof( zeros(5, 3),                  [inf, 3],        [1, 0] );        %double
            

%%%%%% Specify fixed-size input arguments %%%%%%

BoxColorCode       = double([1, 1, 1]); %double


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

codegen insertTextFast_Font13LT.m -report -config cfg -args {VidFrameCode, TextXYCode, TextCode, textColorCode, BoxColorCode}

%}



