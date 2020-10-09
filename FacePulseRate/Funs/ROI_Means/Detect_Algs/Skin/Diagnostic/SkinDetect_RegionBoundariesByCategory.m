function RegionBoundaries = ...
             SkinDetect_RegionBoundariesByCategory(RegionSelectedAnyTF, NRegionsCandidate, ...
                 NRegionsRejected, RegionSelectedLinIdx, RegionIndices, RegionsCandidateLinIdx, ...
                 RegionsRejectedLinIdx, VidObjHeight, BoundingBoxSkin, RegionNPixels, ...        
                 nRows_IsSkinMask, nCols_IsSkinMask) %#codegen
%SkinDetect_RegionBoundariesByCategory   Return linear indices of thickened boundaries for the 
%                                        regions of each category (selected, candidate, rejected). 
%                                                                                                  
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function SkinDetect_RecordDiagnosticData.
% 
%
%    Code Generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.
%
%    Compiled file: The compiled file included in folder FacePulseRate    
%    (SkinDetect_RegionBoundariesByCategory_mex.mexw64) only compatible on Windows platforms.
%
%
%    Description
%    -----------
%
%    Return a linear index of thickened region boundaries for later use for displaying regions on 
%    output video. The boundaries are thickened for better visibility on output video.
%
%    This function acts as a wrapper function to function SkinDetect_RegionBoundaries to facilitate
%    the use of a parallel for loop.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.          


%%%%%% Code-generation settings %%%%%

%Inline function
coder.inline('always');

%Declare variable-size variables:

%                                        Upp. Bounds   Var. Size (T/F)
coder.varsize('RegionBoundaries',        [1, 3],       [0, 0]);
coder.varsize('RegionBoundaries{:}',     [inf, 1],     [1, 0]); 

%Preallocate variables:

%Column 1 = selected region linear indices
%Column 2 = candidate region(s) linear indices
%Column 3 = rejected region(s) linear indices

Elements = coder.nullcopy( zeros(0, 1, 'uint32') );
RegionBoundaries = coder.nullcopy( {Elements, Elements, Elements} );
      

%%%%%% Return the linear indices of thickened boundaries for regions %%%%%

%If called during code generation
%If called during code generation, use a parallel for loop (parfor), but use a for loop otherwise.
%The parallel for loop increases the performance of compiled-C code but decreases the performance 
%of Matlab code.
if ~ coder.target('MATLAB') 
   
    %Loop across categories (selected, candidate, rejected)
    %Use a maximum of 3 threads.
    parfor (i = 1 : 3, 3)

        %RegionBoundaries{i} = M x 1 column vector; type uint32.
        %Local function.
        RegionBoundaries{i} = ...
            Ops(i, RegionSelectedAnyTF, NRegionsCandidate, NRegionsRejected, ...
                RegionSelectedLinIdx, RegionIndices, RegionsCandidateLinIdx, ...
                RegionsRejectedLinIdx, VidObjHeight, BoundingBoxSkin, RegionNPixels, ...
                nRows_IsSkinMask, nCols_IsSkinMask);                                                          
    end
 
%Not called during code generation    
else
    
    %Loop across categories (selected, candidate, rejected)
    for i = 1 : 3

        %RegionBoundaries{i} = M x 1 column vector; type uint32.
        %Local function.
        RegionBoundaries{i} = ...
            Ops(i, RegionSelectedAnyTF, NRegionsCandidate, NRegionsRejected, ...
                RegionSelectedLinIdx, RegionIndices, RegionsCandidateLinIdx, ...
                RegionsRejectedLinIdx, VidObjHeight, BoundingBoxSkin, RegionNPixels, ...
                nRows_IsSkinMask, nCols_IsSkinMask);                  
    end   
end        
    

end %end main function 


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function RegionBoundaries_ith = ...
             Ops(i, RegionSelectedAnyTF, NRegionsCandidate, NRegionsRejected, ...
                 RegionSelectedLinIdx, RegionIndices, RegionsCandidateLinIdx, ...
                 RegionsRejectedLinIdx, VidObjHeight, BoundingBoxSkin, RegionNPixels, ...
                 nRows_IsSkinMask, nCols_IsSkinMask)                         
%Ops   Return regions boundary indices for ith category (selected, candidate, or rejected).
  

%%%%%% Code-generation settings %%%%%

%Inline function
coder.inline('always');

%Declare variable-size variables:

%                                        Upp. Bounds   Var. Size (T/F)
coder.varsize('RegionBoundaries_ith',    [inf, 1],     [1, 0]);

%Preallocate vector for regions boundary indices
RegionBoundaries_ith = coder.nullcopy( zeros(0, 1, 'uint32') );             
    

%%%%%% Switch by category %%%%%%

switch i

    %Note: SkinDetect_RegionBoundaries is a custom function located within folder 'FacePulseRate'.

    %Selected region
    case 1

        %If there is a selected region
        if RegionSelectedAnyTF

            %Scalar; type uint16.
            NRegions = uint16(1);
            
        else
            
            %Scalar; type uint16.
            NRegions = uint16(0);
        end
        
        %P pixels x 1 column vector; type uint32.
        RegionBoundaries_ith = ...
            SkinDetect_RegionBoundaries(RegionSelectedLinIdx, NRegions, RegionIndices, ...
                RegionNPixels, BoundingBoxSkin, VidObjHeight, nRows_IsSkinMask, nCols_IsSkinMask);                     

    %Candidate regions
    case 2

        %P pixels x 1 column vector; type uint32.
        RegionBoundaries_ith = ...
            SkinDetect_RegionBoundaries(RegionsCandidateLinIdx, NRegionsCandidate, ...
                RegionIndices, RegionNPixels, BoundingBoxSkin, VidObjHeight, nRows_IsSkinMask, ...
                nCols_IsSkinMask);

    %Rejected regions
    case 3

        %P pixels x 1 column vector; type uint32.
        RegionBoundaries_ith = ...
            SkinDetect_RegionBoundaries(RegionsRejectedLinIdx, NRegionsRejected, ...
                RegionIndices, RegionNPixels, BoundingBoxSkin, VidObjHeight, nRows_IsSkinMask, ...
                nCols_IsSkinMask);           
end     


end %end local function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(SkinDetect_RegionBoundariesByCategory_mex) of the function.

%Note: at present, a separate compiled version of this function is not used as it is compiled 
%within function SkinDetect.

%{
      
%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%Specify element properties of RegionIndices.PixelIdxList
Element1 = ...
    coder.typeof(double(0), ... example code
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

%Input Argument                            Example Code                 Upp. Bounds     Var. Size (T/F)  Type
RegionSelectedLinIdxCode   = coder.typeof( zeros(400, 1, 'uint32'),     [400, 1],       [1, 0] );        %uint32
RegionsCandidateLinIdxCode = coder.typeof( zeros(400, 1, 'uint32'),     [400, 1],       [1, 0] );        %uint32
RegionsRejectedLinIdxCode  = coder.typeof( zeros(400, 1, 'uint32'),     [400, 1],       [1, 0] );        %uint32
RegionNPixelsCode          = coder.typeof( zeros(400, 1, 'single'),     [400, 1],       [1, 0] );        %single
IsSkinMaskCode             = coder.typeof( false(500, 500),             [inf, inf],     [1, 1] );        %logical

%%%%%% Specify fixed-size input arguments %%%%%%

%                            Example Code                                                                 
RegionSelectedAnyTFCode    = false;
RegionsCandidateAnyTFCode  = false;
RegionsRejectedAnyTFCode   = false;  
VidObjHeight_SingleCode    = single(0);
BoundingBoxSkin_SingleCode = zeros(1, 4, 'single');


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

setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast'' ''-fsingle-precision-constant''})';

%Assign to code-generation configuration object
cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen SkinDetect_RegionBoundariesByCategory.m -report -config cfg -args {RegionSelectedAnyTFCode, RegionsCandidateAnyTFCode, RegionsRejectedAnyTFCode, RegionSelectedLogIdxCode, RegionIndicesCode, RegionsCandidateLogIdxCode, RegionsRejectedLogIdxCode, VidObjHeight_SingleCode, BoundingBoxSkin_SingleCode, RegionNPixelsCode, IsSkinMaskCode}

%}