function ROIsProposed = ...
             ROIAdjustIfExceedsFrameDims(ROIsProposed, VidObjWidth, VidObjHeight) %#codegen
%ROIAdjustIfExceedsFrameDims   Verify whether proposed widths and heights of ROIs exceed frame 
%                              dimensions and, if so, modify them to conform to frame dimensions.
%                              
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by functions ROIResize, ROIMeans_FirstRead_Extrapolate,
%    SkinDetect_EnlargeROI, ROIMSIR, ROIMSIR_MatchSize, ROIMSIR_DetectionSmooth,  
%    ROIMSIR_Interpolate, and ROIMSIR_FrameByFrameSmooth.   
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
%    This function verifies that ROIs that have had modifications to their sizes are still within
%    the dimensions of the frame. If not, this function adjusts the dimensions (and, consequently,  
%    the spatial coordinates) to conform to the frame dimensions.
%
%    -- Note -- 
%
%    Intended only for use with integer types as rounding is not conducted. For modification for 
%    use with floating-point types, rounding would be necessary as ROI values should be integers.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Validate inputs %%%%%%

%Exit if empty
if isempty(ROIsProposed)    

    %Exit function
    return
end
    
%Validate whether input ROIsProposed is type int16.
%Must be an integer type because no rounding is conducted.
%Should be type int16 because the function is implemented to assign values of this type.
%A non-matching type would be due to an implementation error.
assert( isa(ROIsProposed(1, 1), 'int16') );


%%%%%% Running in code generation %%%%%%

%When running in code generation, use for-loops. When running in Matlab code, use vectorization.

if ~ coder.target ('MATLAB') %code generation running
 
    %Inline function
    coder.inline('always');
    
    for i = 1 : size(ROIsProposed, 1)

        %%%%%% --- Verify, and adjust if necessary, X-coordinates and widths %%%%%%

        %Adjust left-side X-coordinate if exceeds frame dimensions:

        ROI_left_X_ith = ROIsProposed(i, 1);

        if ROI_left_X_ith < 1

            ROI_left_X_ith     = int16(1); %recent code mod
            ROIsProposed(i, 1) = int16(1);

        elseif ROI_left_X_ith > VidObjWidth

            ROI_left_X_ith     = VidObjWidth; %recent code mod
            ROIsProposed(i, 1) = VidObjWidth;
        end

        %Adjust right-side X-coordinate if exceeds frame dimensions:

        ROI_right_X_ith = ROI_left_X_ith + ROIsProposed(i, 3) - int16(1);

        if ROI_right_X_ith > VidObjWidth

            ROI_right_X_ith    = VidObjWidth;           
            ROIsProposed(i, 3) = ROI_right_X_ith - ROI_left_X_ith + int16(1);

        elseif ROI_right_X_ith < 1 

            ROI_right_X_ith    = int16(1);
            ROI_left_X_ith     = int16(1);
            ROIsProposed(i, 1) = int16(1);
            ROIsProposed(i, 3) = ROI_right_X_ith - ROI_left_X_ith + int16(1);                     
        end

        %Adjust width if exceeds frame dimensions:

        ROI_width_ith = ROI_right_X_ith - ROI_left_X_ith + int16(1);

        if ROI_width_ith > VidObjWidth

            ROI_width_ith = VidObjWidth;

            ROIsProposed(i, 3) = ROI_width_ith;  

        elseif ROI_width_ith < 1

            ROI_width_ith = int16(1);

            ROIsProposed(i, 3) = ROI_width_ith;
        end

        %%%%%% --- Verify, and adjust if necessary, Y-coordinates and heights %%%%%%

        %Adjust top-side Y-coordinate if exceeds frame dimensions:

        ROI_upper_Y_ith = ROIsProposed(i, 2);

        if ROI_upper_Y_ith < 1 

            ROI_upper_Y_ith    = int16(1); %recent code mod
            ROIsProposed(i, 2) = int16(1);    

        elseif ROI_upper_Y_ith > VidObjHeight 

            ROI_upper_Y_ith    = VidObjHeight; %recent code mod
            ROIsProposed(i, 2) = VidObjHeight;
        end  

        %Adjust bottom-side Y-coordinate if exceeds frame dimensions:

        ROI_lower_Y_ith = ROI_upper_Y_ith + ROIsProposed(i, 4) - int16(1);

        if ROI_lower_Y_ith > VidObjHeight

            ROI_lower_Y_ith = VidObjHeight;
            
            ROI_height_ith     = ROI_lower_Y_ith - ROI_upper_Y_ith + int16(1);
            ROIsProposed(i, 4) = ROI_height_ith;

        elseif ROI_lower_Y_ith < 1

            ROI_lower_Y_ith    = int16(1);
            ROI_upper_Y_ith    = int16(1);
            ROIsProposed(i, 2) = int16(1);
            ROIsProposed(i, 4) = ROI_lower_Y_ith - ROI_upper_Y_ith + int16(1);                    
        end  

        %Adjust height value if exceeds frame dimensions:

        ROI_height_ith = ROI_lower_Y_ith - ROI_upper_Y_ith + int16(1);

        if ROI_height_ith > VidObjHeight

            ROI_height_ith = VidObjHeight;

            ROIsProposed(i, 4) = ROI_height_ith;

        elseif ROI_height_ith < 1

            ROI_height_ith = int16(1);

            ROIsProposed(i, 4) = ROI_height_ith;
        end    
    end    
    
    
%%%%%% Code generation not running %%%%%%

else
    
    %%%%%% --- Setup %%%%%%

    %Extract and calculate ROI coordinates:

    ROI_left_X  = ROIsProposed(:, 1);
    ROI_upper_Y = ROIsProposed(:, 2);
    ROI_width   = ROIsProposed(:, 3);
    ROI_height  = ROIsProposed(:, 4);

    ROI_right_X = ROI_left_X + ROI_width - 1;
    ROI_lower_Y = ROI_upper_Y + ROI_height - 1;

    %Initialize modifications flag 
    AnyModifiedTF = false;

    %%%%%% --- Verify, and adjust if necessary, X-coordinates and widths %%%%%%

    %Adjust left-side X-coordinate if exceeds frame dimensions
    if any(ROI_left_X < 1) || any(ROI_left_X > VidObjWidth)

        ROI_left_X(ROI_left_X < 1) = int16(1);

        ROI_left_X(ROI_left_X > VidObjWidth) = VidObjWidth; 

        AnyModifiedTF = true;
    end

    %Adjust right-side X-coordinate if exceeds frame dimensions
    if any(ROI_right_X > VidObjWidth) || any(ROI_right_X < 1)

        ROI_right_X(ROI_right_X > VidObjWidth) = VidObjWidth;

        ROI_right_X(ROI_right_X < 1) = int16(1);

        AnyModifiedTF = true;
    end

    %Adjust width if exceeds frame dimensions:

    %ROI width
    ROI_width = ROI_right_X - ROI_left_X + 1;

    if any(ROI_width > VidObjWidth) || any(ROI_width < 1)

        ROI_width(ROI_width > VidObjWidth) = VidObjWidth;

        ROI_width(ROI_width < 1) = int16(1);

        AnyModifiedTF = true;    
    end

    %%%%%% --- Verify, and adjust if necessary, Y-coordinates and heights %%%%%%

    %Adjust top-side Y-coordinate if exceeds frame dimensions
    if any(ROI_upper_Y < 1) || any(ROI_upper_Y > VidObjHeight)

        ROI_upper_Y(ROI_upper_Y < 1) = int16(1); 

        ROI_upper_Y(ROI_upper_Y > VidObjHeight) = VidObjHeight;

        AnyModifiedTF = true;
    end

    %Adjust bottom-side Y-coordinate if exceeds frame dimensions
    if any(ROI_lower_Y > VidObjHeight) || any(ROI_lower_Y < 1)

        ROI_lower_Y(ROI_lower_Y > VidObjHeight) = VidObjHeight;

        ROI_lower_Y(ROI_lower_Y < 1) = int16(1);

        AnyModifiedTF = true;
    end

    %Adjust height value if exceeds frame dimensions:

    %ROI Height
    ROI_height = ROI_lower_Y - ROI_upper_Y + 1;

    if any(ROI_height > VidObjHeight) || any(ROI_height < 1)

        ROI_height(ROI_height > VidObjHeight) = VidObjHeight;

        ROI_height(ROI_height < 1) = int16(1);

        AnyModifiedTF = true;
    end

    %%%%%% --- Assign output %%%%%%

    %If any modification conducted
    if AnyModifiedTF        

        ROIsProposed = [ROI_left_X, ROI_upper_Y, ROI_width, ROI_height];
    end
end


end %end function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(ROIAdjustIfExceedsFrameDims_mex) of the function.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%                                  Example Code               Upp. Bounds   Var. Size (T/F)  Type
ROIsProposedCode   = coder.typeof( zeros(500, 4, 'int16'),    [inf, 4],     [1, 0] );        %int16
          
      
%%%%%% Specify fixed-size input arguments %%%%%%

VidObjWidthCode  = int16(0);         
VidObjHeightCode = int16(0);
                  

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

codegen ROIAdjustIfExceedsFrameDims.m -report -config cfg -args {ROIsProposedCode, VidObjWidthCode, VidObjHeightCode}
                
%}
