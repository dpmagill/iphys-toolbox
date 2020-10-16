function BoundariesUncropLinIdx_Uint32 = ...
             SkinDetect_RegionBoundaries(RegionsLinIdx, NRegions, RegionIndices, RegionNPixels, ...
                 ROIForCrop, VidObjHeight, nRows_IsSkinMask_int16, nCols_IsSkinMask_int16) 
                 %#codegen
%SkinDetect_RegionBoundaries   Return linear index of thickened boundaries for specified regions. 
%                                                                                                  
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function SkinDetect_RegionBoundariesByCategory.
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
%    Return a linear index of thickened region boundaries for later use for displaying regions on 
%    output video. The boundaries are thickened for better visibility on output video.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code generation specifications %%%%%%

%Specify inlining for faster code execution
coder.inline('always');

%Declare variables:

%                                                 Upp. Bounds    Var. Size (T/F)
coder.varsize('BoundariesUncropLinIdx_Uint32',    [inf, 1],      [1, 0]);


%%%%%% Setup %%%%%%

%Cast to type uint32 to prevent integer overflow
nRows_IsSkinMask = uint32(nRows_IsSkinMask_int16);
nCols_IsSkinMask = uint32(nCols_IsSkinMask_int16);


%%%%%% Assign logical matrix where pixels corresponding to region pixels are true %%%%%% 

%Assign blank logical matrix
RegionsLogIdx = false(nRows_IsSkinMask, nCols_IsSkinMask); 

%If more than one regions
if NRegions > 1            

    %Loop across regions
    for i = 1 : NRegions

        %Scalar; type uint16.
        ii = RegionsLinIdx(i);

        %Cast from type single to type int32
        RegionNPixels_ith = int32( RegionNPixels(ii) );                       

        %Loop across pixels within the ith region
        for j = 1 : RegionNPixels_ith

            %Scalar; type uint32.
            jj = RegionIndices(ii).PixelIdxList(j);   

            %Reassign jjth pixel as true
            RegionsLogIdx(jj) = true;
        end                     
    end    
    
%If only one region    
%Note: if there is a selected region, it will consist of only 1 region.     
elseif NRegions == 1

    %Scalar; type uint16.
    ii = RegionsLinIdx(1);

    %Cast from type single to type int32
    RegionNPixels_ith = int32( RegionNPixels(ii) );                       

    %Loop across pixels within the ith region
    for j = 1 : RegionNPixels_ith

        %Scalar; type uint32.
        jj = RegionIndices(ii).PixelIdxList(j);   
        
        %Reassign jjth pixel as true
        RegionsLogIdx(jj) = true;
    end  
    
%If no regions  
%Note: this is the least likely case, so it is evaluated last.
else %NRegions == 0    
    
    BoundariesUncropLinIdx_Uint32 = zeros(0, 1, 'uint32');
    
    return
end


%%%%%% Find boundary pixels of specified regions %%%%%% 

%Assign look up table for boundary-finding operations
BoundariesLUT = ...
    coder.const( ...
        logical([ ...
             0     0     0     0     0     0     0     0     0     0     0     0 ...
             0     0     0     0     1     1     1     1     1     1     1     1 ...
             1     1     1     1     1     1     1     1     0     0     0     0 ...
             0     0     0     0     0     0     0     0     0     0     0     0 ...
             1     1     1     1     1     1     1     1     1     1     1     1 ...
             1     1     1     1     0     0     0     0     0     0     0     0 ...
             0     0     0     0     0     0     0     0     1     1     1     1 ...
             1     1     1     1     1     1     1     1     1     1     1     1 ...
             0     0     0     0     0     0     0     0     0     0     0     0 ...
             0     0     0     0     1     1     1     1     1     1     1     1 ...
             1     1     1     1     1     1     1     1     0     0     0     0 ...
             0     0     0     0     0     0     0     0     0     0     0     0 ...
             1     1     1     1     1     1     1     1     1     1     1     1 ...
             1     1     1     1     0     0     0     0     0     0     0     0 ...
             0     0     0     0     0     0     0     0     1     1     1     1 ...
             1     1     1     1     1     1     0     0     1     1     0     0 ...
             0     0     0     0     0     0     0     0     0     0     0     0 ...
             0     0     0     0     1     1     1     1     1     1     1     1 ...
             1     1     1     1     1     1     1     1     0     0     0     0 ...
             0     0     0     0     0     0     0     0     0     0     0     0 ...
             1     1     1     1     1     1     1     1     1     1     0     0 ...
             1     1     0     0     0     0     0     0     0     0     0     0 ...
             0     0     0     0     0     0     0     0     1     1     1     1 ...
             1     1     1     1     1     1     1     1     1     1     1     1 ...
             0     0     0     0     0     0     0     0     0     0     0     0 ...
             0     0     0     0     1     1     1     1     1     1     1     1 ...
             1     1     1     1     1     1     1     1     0     0     0     0 ...
             0     0     0     0     0     0     0     0     0     0     0     0 ...
             1     1     1     1     1     1     1     1     1     1     1     1 ...
             1     1     1     1     0     0     0     0     0     0     0     0 ...
             0     0     0     0     0     0     0     0     1     1     1     1 ...
             1     1     1     1     1     1     1     1     1     1     1     1 ...
             0     0     0     0     0     0     0     0     0     0     0     0 ...
             0     0     0     0     1     1     1     1     1     1     1     1 ...
             1     1     1     1     1     1     1     1     0     0     0     0 ...
             0     0     0     0     0     0     0     0     0     0     0     0 ...
             1     1     1     1     1     1     1     1     1     1     0     0 ...
             1     1     0     0     0     0     0     0     0     0     0     0 ...
             0     0     0     0     0     0     0     0     1     1     1     1 ...
             1     1     1     1     1     1     1     1     1     1     1     1 ...
             0     0     0     0     0     0     0     0     0     0     0     0 ...
             0     0     0     0     1     1     1     1     1     1     1     1 ...
             1     1     0     0     1     1     0     0] ...
        )' ...
    ); 
    
%Return logical matrix where perimeter and hole boundaries of regions are true
%Note: the output argument is equivalent to that produced by bwperim(MatrixLogical) but is faster.
%Note: in this case, using an output name different from the input name results in a faster 
%compiled function compared to using the same name.
BoundariesLogIdx = ...
    bwlookup( ...
        RegionsLogIdx, ...
        BoundariesLUT  ... lookup table
    ); 


%%%%%% Enlarge boundaries for better display %%%%%%

%Enlarge boundaries for display purposes for use in function WriteFaceVideo_SkinDetectDiagnosis.
%Do so by dilation.
%Note: in this case, using an output name different from the input name results in a faster 
%compiled function compared to using the same name.
DilatedBoundariesLogIdx = ...
    imdilate( ...
        BoundariesLogIdx, ...
        true(2)           ... structuring element
    ); 


%%%%%% Adjust coordinates for use in annotating output video %%%%%%

%The coordinates will be used by function WriteFaceVideo_SkinDetectDiagnosis to display the 
%boundaries of regions. 

%As the index returned by function bwperim corresponds to the ROI, but the index will be used for
%the full video frame, the coordinates are adjusted to align with the full frame.      
%Do so by adding back the [X, Y] coordinates that shifted during cropping.

%Also, convert from [X, Y] coordinates to linear index
%As the border pixels are irregularly distributed, a linear index will be more convenient when
%superimposing pixels in the output video.

%Convert to type uint32 for compatibility with output variable
VidObjHeight_uint32 = uint32(VidObjHeight);
ROIForCrop_uint32 = uint32(ROIForCrop);

%Preallocate output variable
BoundariesUncropLinIdx_Uint32 = ...
    coder.nullcopy( zeros(nRows_IsSkinMask * nCols_IsSkinMask, 1, 'uint32') );

counter = uint32(0);

ROIForCrop_WidthMin1 = ROIForCrop_uint32(1) - 1;
ROIForCrop_HeightMin1 = ROIForCrop_uint32(2) - 1;

%Loop across columns of DilatedBoundariesLogIdx 
for i = 1 : nCols_IsSkinMask

    %Loop across rows of DilatedBoundariesLogIdx
    for j = 1 : nRows_IsSkinMask

        %Convert from subscript indices to a linear index for more efficient indexing
        %Scalar; type uint32.
        %Note: In compiled C code, the faster indexing outweighs the cost of this conversion.
        LinIdx = j + (i - 1) * nRows_IsSkinMask;        
        
        %If true value
        if DilatedBoundariesLogIdx(LinIdx) 

            counter = counter + 1;
            
            %Adjust Y-coordinate to align with full frame
            RowIdx_jth = j + ROIForCrop_HeightMin1; 
               
            %Adjust X-coordinate to align with full frame
            ColIdx_ith = i + ROIForCrop_WidthMin1; 
                
            %Convert from [X, Y] coordinates to linear index
            BoundariesUncropLinIdx_Uint32(counter) = ...
                RowIdx_jth + (ColIdx_ith - 1) * VidObjHeight_uint32;                        
        end        
    end
end
    
%Reassign to remove unused rows
BoundariesUncropLinIdx_Uint32 = BoundariesUncropLinIdx_Uint32(1 : counter);
     

end %end function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(SkinDetect_RegionBoundaries_mex) of the function.

%Note: at present, a separate compiled version of this function is not used as it is compiled 
%within function SkinDetect.

%{


%%%%%% Modify function files for performance %%%%%%

%Note: before running code generation, input validation was removed from the files for the 
%following functions:
% - \Program Files\MATLAB\R2020a\toolbox\images\images\bwlookup.m
% - \Program Files\MATLAB\R2020a\toolbox\images\images\+images\+internal\+coder\morphop.m 

%Specifically, in these files, the following validation functions were commented out:
% - narginchk
% - validateattributes

%Note: Seperate files for these functions with these changes could not be made because code 
%generation for these functions expects specific file names. Hence, after code generation, the  
%input validation was added back to the files.
%As these files are located in 'Program Files', admin access is required to edit them.


%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%Input Argument                    Example Code               Upp. Bounds      Var. Size (T/F)  Type
RegionsLinIdxCode  = coder.typeof( zeros(400, 1, 'uint32'),   [inf, 1],        [1, 0] );        %uint32
RegionNPixelsCode  = coder.typeof( zeros(400, 1, 'single'),   [400, 1],        [1, 0] );        %single

%Specify element properties of RegionIndices.PixelIdxList
Element1 = ...
    coder.typeof(uint32(0), ... example code
                 [inf 1],   ... upper bounds
                 [1, 0]     ... variable size (T/F)
    );

%Non-scalar struct
RegionIndicesCode = ... 
    coder.typeof( ...
        struct( ...                                
            'PixelIdxList', ...
             Element1 ...
        ), ...
        [400 1],   ... upper bounds
        [1, 0]     ... variable size (T/F)
    );

                 
%%%%%% Specify fixed-size input arguments %%%%%%

NRegionsCode               = uint16(0);
ROIForCropCode             = zeros(1, 4, 'int16');                                                     
VidObjHeightCode           = int16(0);                                                                 
nRows_IsSkinMask_int16Code = int16(0);
nCols_IsSkinMask_int16Code = int16(0);

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

codegen SkinDetect_RegionBoundariesT.m -report -config cfg -args {RegionsLinIdxCode, NRegionsCode, RegionIndicesCode, RegionNPixelsCode, ROIForCropCode, VidObjHeightCode, nRows_IsSkinMask_int16Code, nCols_IsSkinMask_int16Code}

%}




