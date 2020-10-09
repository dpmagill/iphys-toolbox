function [RegionMaxPixelIdx, NPixelsMax, NRegions] = ...
             FindLargestRegion(IsSkinMask) %#codegen
%FindLargestRegion   Identify the largest region in the skin-segmentation mask and return the 
%                    linear indices corresponding to its pixels. 
%                 
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function
%    ROIMeans_FirstRead_CollectSkinColorSamples.
%
%
%    Code Generation
%    ---------------
%
%    This function intended only for code generation (C language).
%
%
%    Description
%    -----------
%
%    Identify the largest region in the skin-segmentation mask and return the linear indices 
%    corresponding to its pixels.
%
%    Output:
%
%        RegionMaxPixelIdx = Linear indices corresponding to pixels of the largest region. Type 
%                            int32.
%        NPixelsMax        = The number of pixels in the largest region identified.
%        NRegions          = The number of regions identified.
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

%Specify variable-size variables
%Note: Improve efficiency by capping row length at 400 to prevent dynamic memory allocation.

%                                   Upp. Bounds   Var. Size (T/F)
coder.varsize('CC.RegionLengths',   [400, 1],     [1, 0]); %scalar struct
coder.varsize('RegionEndIndex',     [400, 1],     [1, 0]);
coder.varsize('PixelIdxList',       [1, 400],     [0, 1]); %cell array


%%%%%% Find connected regions %%%%%%

%Scalar struct.
CC = bwconncomp(IsSkinMask);


%%%%%% Find the largest region %%%%%%

%The number of regions identified
%Scalar; type int32.
NRegions = int32( CC.NumObjects );

%Prevent dynamic memory allocation from colon operator by asserting length
assert(NRegions <= 400);

%Initialize index of region with the maximum number of pixels
RegionMaxIdx = int32(0);

%Initialize the number of pixels corresponding to the region with the maximum number of pixels
%Note: this value should be less than the smallest possible value.
NPixelsMax = int32(-1);

%If at least one region identified
if NRegions ~= 0

    %Loop across regions
    for i = 1 : NRegions

        %The number of pixel indices in the ith region
        %Cast from type coder.internal.indexInt to type int32.
        NPixels_ith = int32( CC.RegionLengths(i) ); 

        %Determine whether the ith region is larger than other regions previously iterated
        if NPixels_ith > NPixelsMax

            NPixelsMax = NPixels_ith;

            RegionMaxIdx = i;   
        end           
    end


    %%%%%% Return the pixel indices of the largest region %%%%%%

    %Preallocate the linear index of the first pixel of the ith region
    RegionBeginIndex_ith = coder.nullcopy( int32(0) );
    
    %Initialize the linear index of the last pixel of the ith region
    RegionEndIndex_ith = int32(0);

    %Prevent dynamic memory allocation from colon operator by asserting length
    assert(RegionMaxIdx <= 400);

    %Loop up to index of largest region
    for i = 1 : RegionMaxIdx

        %The number of pixel indices in the ith region
        %Cast from type coder.internal.indexInt to type int32.
        NPixels_ith = int32( CC.RegionLengths(i) );

        %Linear index of the first pixel in the ith region
        RegionBeginIndex_ith = RegionEndIndex_ith + 1; 

        %Linear index of the last pixel in the ith region
        RegionEndIndex_ith = NPixels_ith + RegionEndIndex_ith;  
    end   

    %Preallocate pixel indices for the largest region
    RegionMaxPixelIdx = coder.nullcopy( zeros(CC.RegionLengths(RegionMaxIdx), 1, 'int32') ); 

    %Initialize index for pixel indices of the largest region
    ElementIdx = int32(0);    

    %Loop across pixels indices of ith region
    for j = RegionBeginIndex_ith : RegionEndIndex_ith                

        ElementIdx = ElementIdx + 1;

        %Assign pixel index to cell array
        RegionMaxPixelIdx(ElementIdx) = CC.RegionIndices(j);
    end 
  
%If no regions identified
else
    
    RegionMaxPixelIdx = zeros(1, 1, 'int32');
end


end %end function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(FindLargestRegion_mex) of the function.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%                              Example Code         Upp. Bounds      Var. Size (T/F)  Type
IsSkinMaskCode = coder.typeof( false(500, 500),     [inf, inf],      [1, 1] );        %logical
    
      
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

setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})';

%Assign to code-generation configuration object
cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen FindLargestRegion.m -report -config cfg -args {IsSkinMaskCode}

%}        
        


