function VidFrameROI = ...
             WriteFaceVideo_MaskOverlay(VidFrameROI, Transparency, IsSkinMask_Inverted, Color, ...
                 nRows, nCols) %#codegen             
%WriteFaceVideo_MaskOverlay   Overlay color on image indicating pixels corresponding to inverted 
%                             skin-segmentation mask.
%   
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_OverlaySkinSegmentation. 
%
%
%    Code Generation
%    ---------------
% 
%    Can be called as a Matlab function or used for C-language code generation.
%
%    Compiled file: The compiled file included in folder FacePulseRate 
%    (WriteFaceVideo_MaskOverlay_mex.mexw64) only compatible on Windows platforms.    
%
%
%    Description
%    -----------
%
%    Overlay color on image indicating pixels corresponding to inverted skin-segmentation mask. 
%                             
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Setup %%%%%%

%Mask colors per channel
%Scalars; type uint8.
RColor = uint8( Color(1) );
GColor = uint8( Color(2) );
BColor = uint8( Color(3) );

%Convert to opacity
%Scalar; type double.
%Note: previously, variable Transparency entered the function as type double and it was cast to
%type single. However, it was observed that Matlab introduced an optimization whereby it was cast
%to single on each iteration of the loop below. To prevent this, Transparency enters the function
%as type single.
Opacity = 1 - double(Transparency); 

%Opacity values per channel
%Local function.
%Scalars; type uint8.
[RColorOpac, GColorOpac, BColorOpac] = ReturnOpacityValue(RColor, GColor, BColor, Opacity);
    

%%%%%% Code generation running %%%%%%

%Use a for-loop version for code generation and a vectorized version for Matlab code.

if ~ coder.target('MATLAB')

    %Number of elements in inverted skin-segmentation mask
    %Cast to type int32 to prevent integer overflow.
    %Scalar; int32.
    NEl = int32(nRows) * int32(nCols); 
  
    %Loop index for page 3 (the blue channel)
    NEl2 = NEl * 2; 

    %Loop across pixels
    for i = 1 : NEl

        %Convert to mask pixel if IsSkinMask_Inverted(i) is true (non-skin)
        if IsSkinMask_Inverted(i)

            %Cast video frame element from type uint8 to a floating-point type to permit
            %multiplication by a decimal (Transparency). Cast to type single for efficiency.             

            %Red channel:

            VidFrameROI(i) = ...
                uint8( floor( single(VidFrameROI(i)) * Transparency ) ) + RColorOpac;

            %Green channel:

            idx = i + NEl;

            VidFrameROI(idx) = ...
                uint8( floor( single(VidFrameROI(idx)) * Transparency ) ) + GColorOpac;

            %Blue channel:

            idx = i + NEl2;

            VidFrameROI(idx) = ...
                uint8( floor( single(VidFrameROI(idx)) * Transparency ) ) + BColorOpac;
        end
    end

    
%%%%%% Code generation not running %%%%%%    

else
    
    %Separate RGB color channels
    Red   = VidFrameROI(:, :, 1);
    Green = VidFrameROI(:, :, 2);
    Blue  = VidFrameROI(:, :, 3);

    %Insert overlay color to mask:

    %Red page
    Red(IsSkinMask_Inverted) = ...
        Red(IsSkinMask_Inverted) * double(Transparency)  ... Original pixels * transparency where 
                                                         ... mask true.
        + RColorOpac;                                    %   Color of mask * opacity.

    %Green page    
    Green(IsSkinMask_Inverted) = ...
        Green(IsSkinMask_Inverted) * double(Transparency) ... 
        + GColorOpac;

    %Blue Page
    Blue(IsSkinMask_Inverted) = ...
        Blue(IsSkinMask_Inverted) * double(Transparency) ... 
        + BColorOpac;


    %Concatenate color channels
    VidFrameROI = cat(3, Red, Green, Blue); 
end


end %end main function


%=============================================================================================
%Local Functions
%=============================================================================================


%=============================================================================================
function [RColorOpac, GColorOpac, BColorOpac] = ...
             ReturnOpacityValue(RColor, GColor, BColor, Opacity)
%ReturnOpacityValue   Return the R, G, and B opacity values.         
%
%    Description:
%
%    Return the R, G, and B opacity values.  
%
%    Multiply the specified mask colors by the specified opacity. Then, subtract 1 in order to 
%    prevent integer overflow. Note: if all calculations were conducted in floating point, the 
%    maximum value any pixel could receive would be 255. However, rounding introduced by the use of 
%    integers results in occassional values above 255, which wrap in compiled C.


%Prevent inlining
%It has been observed that code generation makes an optimization by inserting the subtraction
%performed here into the loop, which results in the subtraction occurring on each iteration. Attemp
%to prevent this optimization by restricting inlining.
coder.inline('never');


%Scalars; type uint8.

RColorOpac = RColor * Opacity - 1;
GColorOpac = GColor * Opacity - 1;
BColorOpac = BColor * Opacity - 1;


end %end local function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(WriteFaceVideo_MaskOverlay_mex) of the function.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%                                             Example Code                 Upp. Bounds     Var. Size (T/F)  Type
VidFrameROICode               = coder.typeof( zeros(500, 500, 3, 'uint8'), [inf, inf, 3],  [1, 1, 0] );     %uint8
IsSkinMaskCode                = coder.typeof( false(500, 500),             [inf, inf],     [1, 1] );        %logical


%%%%%% Specify fixed-size input arguments %%%%%%

TransparencyCode = single(0);
ColorCode        = zeros(1, 3, 'double');                                                                
nRowsCode        = uint16(0);
nColsCode        = uint16(0);


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

setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast'' ''-fsingle-precision-constant''})';

%Assign to code-generation configuration object
cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen WriteFaceVideo_MaskOverlay.m -report -config cfg -args {VidFrameROICode, TransparencyCode, IsSkinMaskCode, ColorCode, nRowsCode, nColsCode}
             
%}
