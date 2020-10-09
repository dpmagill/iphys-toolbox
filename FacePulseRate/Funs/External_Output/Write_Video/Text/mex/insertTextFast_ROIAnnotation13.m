function VidFrameCrop = insertTextFast_ROIAnnotation13(VidFrameCrop, Text) %#codegen
%insertTextFast_ROIAnnotation13   Code generation for function insertText for an image cropped to 
%                                 the size of the ROI annotation with font size 13.                             
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_ROIAnnotation.
%
%    Code generation: This function intended only for code generation (C language).
%
%    Compiled file: 
%
%     - The compiled file included in folder FacePulseRate    
%       (insertTextFast_ROIAnnotation13_mex.mexw64) only compatible on Windows platforms. 
%     - This function uses bounded variable sizes for input variables to improve efficiency. Ensure 
%       that the input variables do not exceed these bounds.
    

%Specify inlining for faster code execution
coder.inline('always');

%Declare variable-size variables
%Specify bounds to prevent dynamic memory allocation.
%                            Upp. Bounds     Var. Size (T/F)
coder.varsize('Text',        [1, 125],       [0, 1]);


%Note: function insertTextNoValidation is a custom version of function insertText with 
%input validation removed for efficiency.
VidFrameCrop = ...
    insertTextNoValidation( ...
        VidFrameCrop,                ...
        [1, 29],                     ... [X, Y] coordinates: bottom-left (as specified by argument AnchorPoint) of indexed area
                                     ... Y-coordinate should equal TextBoxMaxRowSize
        Text,                        ... text
        'Font', 'Consolas',          ... font type
        'FontSize', 13,              ... font size; must be compile-time constant
        'BoxColor', [189, 233, 255], ... box background color: light blue
        'AnchorPoint', 'LeftBottom'  ... [X, Y] coordinates position relative to text 
     );

 
end %end function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(insertTextFast_ROIAnnotation13_mex) of the function.

%{

%%%%%% Modify function files for performance %%%%%%

%Before running code generation, input validation was removed from the file for function 
%insertText. The modified file was saved as insertTextNoValidation.p, which is located in folder
%'Validation_Removed'. The code is obscured (as p-code) to comply with the Matlab licensing 
%agreement, which does not permit the distribution of Matlab source code. To permit code generation 
%from the p-code, the statement coder.allowpcode('plain') was included in insertTextNoValidation.m 
%before obfuscation. DPM possesses the un-obfuscated files.

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%                        Example Code    Upp. Bounds   Var. Size (T/F)  Type
TextCode = coder.typeof( ' ',            [1, 125],     [0, 1] );        %char
               
   
%%%%%% Specify fixed-size input arguments %%%%%%

VidFrameCropCode = zeros(29, 550, 3, 'uint8'); %uint8


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
cfg.DynamicMemoryAllocation = 'off'; %disabled to improve efficiency as all variables have bounded size


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
%vector. As function setbuildargs will be evaluated from text, use double ' quotes for  each
%character vector to maintain the charater vector,
%e.g., {''-Ofast'' ''-fsingle-precision-constant''}.

setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})';

%Assign to code-generation configuration object
cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen insertTextFast_ROIAnnotation13.m -report -config cfg -args {VidFrameCropCode, TextCode}

%}


