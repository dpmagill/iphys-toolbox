function ROIResize = ...
             ROIResize(ROI, ROIsToResizeLinIdx, ROIWidthResizeFactor, ROIHeightResizeFactor, ...
                 VidObjWidth, VidObjHeight) %#codegen
%ROIResize   Resize ROI(s) according to specifed scaling factors.
%            
%   Helper function to function FacePulseRate.
%   Within function FacePulseRate, called by functions ROIMeans_FirstRead, 
%   ROIMeans_FirstRead_CollectSkinColorSamples, ROIMeans_FirstRead_SetBoundingBoxes,  
%   ROIMeans_SecondRead_SkinDetect, ROIMSIR, ROIMSIR_Interpolate, and ROIMSIR_FrameByFrameSmooth. 
%
%
%   Code Generation
%   ---------------
%
%   Can be called as a Matlab function or used for C-language code generation.
%
%
%   Description
%   -----------
%
%   Resize the width and height of ROIs (ROI(:, 3 : 4)) of specified frames (ROIsToResizeLinIdx)   
%   by specified scaling factors (ROIWidthResizeFactor and ROIHeightResizeFactor). After modifying 
%   the width and height, adjust the upper-left X- and Y-coordinates (ROI(:, 1 : 2)) so that they
%   are located at half the width and half the height from the unmodified centerpoint; by making 
%   this adjustment, the resizing will have expanded from the centerpoint rather than from the
%   upper-left corner. Then, adjust the ROI values so that none exceed the frame dimensions 
%   (VidObjWidth and VidObjHeight).
%
%   Inputs:
%
%      ROI                     = ROI matrix (multiple ROIs) or row vector (one ROI).
%                                The columns in the ROI matrix or row vector indicate X-upper-left   
%                                corner, Y-upper-left corner width, and height, in pixels. Note
%                                that X refers to column indexing and Y refers to row indexing;
%                                because Y refers to row indexing, Y == 0 is located at the top,
%                                rather than the bottom, of the plane.
%      ROIsToResizeLinIdx      = Linear index corresponding to the ROI matrix indicating ROIs to
%                                resize. Index can be non-consecutive. If resizing one ROI (a row
%                                vector), specify 1 for this argument.
%      ROIWidthResizeFactor    = Width resizing factor.
%      ROIHeightResizeFactor   = Height resizing factor.
%      VidObjWidth             = Frame width (pixels). 
%      VidObjHeight            = Frame height (pixels).
%
%   Output:
%
%      ROIResize               = Resized ROI matrix (multiple ROIs) or row vector (one ROI).                                
%
%   -- Note -- 
%
%   Intended only for use with integer types as rounding is not conducted. For modification for use 
%   with floating-point types, rounding would be necessary as ROI values should be integers.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Input validation %%%%%%

%Validate whether input ROI is type int16.
%Must be an integer type because no rounding is conducted.
%Should be type int16 because the function is implemented to assign values of this type.
%A non-matching type would be due to an implementation error.
assert( isa(ROI(1, 1), 'int16') );


%%%%%% Running in code generation %%%%%%

%When running in code generation, use for-loops. When running in Matlab code, use vectorization.

if ~ coder.target ('MATLAB') %code generation running
 
    %Inline function
    coder.inline('always');

    NROIs = numel(ROIsToResizeLinIdx);

    %Preallocate output
    ROIResize = coder.nullcopy( zeros(NROIs, 4, 'int16') );
    
    %Cast resizing factors to type single for efficiency
    ROIWidthResizeFactor_Single  = single(ROIWidthResizeFactor);
    ROIHeightResizeFactor_Single = single(ROIHeightResizeFactor);

    for i = 1 : NROIs

        %%%%%% --- Resize width(s) and height(s) %%%%%% 

        %Convert to index of input ROI
        ii = ROIsToResizeLinIdx(i);

        ROI_width_ith = int16( single( ROI(ii, 3) ) * ROIWidthResizeFactor_Single );
        ROIResize(i, 3) = ROI_width_ith;

        ROI_height_ith = int16( single( ROI(ii, 4) ) * ROIHeightResizeFactor_Single );
        ROIResize(i, 4) = ROI_height_ith;

        %%%%%% Adjust X- and Y-coordinates %%%%%%

        %Adjust the upper-left X- and Y-coordinates (ROI(:, 1 : 2)) so that they are located at half the
        %width and half the height from the unmodified centerpoint; by making this adjustment, the resizing 
        %will have expanded from the centerpoint rather than from the upper-left corner.
        %Optimize division by 2 by bit-wise operations.

        %Find centerpoint
        centerX = ROI(ii, 1) + bitshift( ROI(ii, 3), -1 );
        centerY = ROI(ii, 2) + bitshift( ROI(ii, 4), -1 );

        %Assign new X- and Y-coordinates
        %Expand from centerpoint based upon new height and width    
        ROIResize(i, 1) = centerX - bitshift(ROI_width_ith, -1); 
        ROIResize(i, 2) = centerY - bitshift(ROI_height_ith, -1); 
    end    
 
    %%%%%% --- Modify new ROI dimensions that exceed frame dimensions %%%%%%  

    %Function ROIAdjustIfExceedsFrameDims verifies if adjusted ROIs are within frame dimensions and, if 
    %not, adjusts the ROI values to conform to frame dimensions.

    %Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder 'FacePulseRate'.
    ROIResize = ROIAdjustIfExceedsFrameDims(ROIResize, VidObjWidth, VidObjHeight);          

    
%%%%%% Code generation not running %%%%%%    
    
else
    
    %%%%%% --- Resize width(s) and height(s) %%%%%%

    %Multiply width by specified width scale factor  
    ROI_width_adjust = ROI(ROIsToResizeLinIdx, 3) .* ROIWidthResizeFactor;  

    %Multiply height by specified height scale factor
    ROI_height_adjust = ROI(ROIsToResizeLinIdx, 4) .* ROIHeightResizeFactor;       

    %%%%%% --- Adjust X- and Y-coordinates %%%%%%

    %Adjust the upper-left X- and Y-coordinates (ROI(:, 1 : 2)) so that they are located at half the
    %width and half the height from the unmodified centerpoint; by making this adjustment, the resizing 
    %will have expanded from the centerpoint rather than from the upper-left corner.

    %Find centerpoint
    %Note: ROIFindCenterPoint is a custom function located within folder 'FacePulseRate'.
    [ROISpecifiedFrames_center_X, ROISpecifiedFrames_center_Y] = ...
        ROIFindCenterPoint(ROI, ROIsToResizeLinIdx);

    %Expand from centerpoint
    ROI_upperleft_X_adjust = ROISpecifiedFrames_center_X - ROI_width_adjust  / 2; 
    ROI_upperleft_Y_adjust = ROISpecifiedFrames_center_Y - ROI_height_adjust / 2; 

    %Concatenate
    ROIResize = ...
        [ROI_upperleft_X_adjust, ROI_upperleft_Y_adjust, ...
         ROI_width_adjust, ROI_height_adjust];

    %%%%%% --- Modify new ROI dimensions that exceed frame dimensions %%%%%%  

    %Function ROIAdjustIfExceedsFrameDims verifies if adjusted ROIs are within frame dimensions and, if 
    %not, adjusts the ROI values to conform to frame dimensions.

    %Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder 'FacePulseRate'.
    ROIResize = ...
        ROIAdjustIfExceedsFrameDims(ROIResize, VidObjWidth, VidObjHeight);
end


end %end function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(ROIResize_mex) of the function.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%                                      Example Code               Upp. Bounds   Var. Size (T/F)  Type
ROICode                = coder.typeof( zeros(500, 4, 'int16'),    [inf, 4],     [1, 0] );        %int16
ROIsToResizeLinIdxCode = coder.typeof( zeros(1, 500, 'int32'),   [1, inf],     [0, 1] );        %int32
          
                     
%%%%%% Specify fixed-size input arguments %%%%%%

ROIWidthResizeFactorCode  = double(0);
ROIHeightResizeFactorCode = double(0);
VidObjWidthCode           = int16(0);         
VidObjHeightCode          = int16(0);
                  

%%%%%% Set configurations to increase performance %%%%%%

%Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic 
%"Optimization Strategies"

cfg = coder.config('mex');
cfg.GlobalDataSyncMethod = 'NoSync';
cfg.ConstantInputs = 'IgnoreValues';
cfg.ExtrinsicCalls = true; %permit to show assert error
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

codegen ROIResize.m -report -config cfg -args {ROICode, ROIsToResizeLinIdxCode, ROIWidthResizeFactorCode, ROIHeightResizeFactorCode, VidObjWidthCode, VidObjHeightCode}
                
%}
