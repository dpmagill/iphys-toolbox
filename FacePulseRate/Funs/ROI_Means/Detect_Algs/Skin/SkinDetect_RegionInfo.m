function [RegionIndices, NRegions, RegionNPixels, Centroids] = SkinDetect_RegionInfo(IsSkinMask)
         %#codegen
%SkinDetect_RegionInfo   Find connected regions in skin-segmentation mask and return pixel indices, 
%                        centroids, and other region information.                
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinDetect_PartitionRegions.
%
%
%    Code Generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.
%
%    Compiled file: 
%
%     - The compiled file included in folder FacePulseRate (SkinDetect_RegionInfo_mex.mexw64)    
%       only compatible on Windows platforms. 
%     - This function uses a bounded variable size for variable NPixelsEachRegion_SingleCode to 
%       improve efficiency. Ensure that this input does not exceed these bounds.
%
%
%    Description
%    -----------
%
%    Find connected regions in skin-segmentation mask and return pixel indices corresponding to 
%    each region, the cetroid of each region, and other region information.
%
%    Regarding the centroids, they will be used as part of the skin-detection algorithm to select 
%    one region considered as the skin-detection (see function SkinDetect_SelectRegion).
%    Additionally, centroids of all regions, including those will be rejected, will be used for
%    diagnostic purposes on the output video. Centroids for use on the output video are recorded by  
%    function SkinDetect_RecordDiagnosticData.
%
%    Different code is used depending on whether code generation is used. This is because function 
%    bwconncomp returns a struct with different fields depending on whether code generation is 
%    used.
%
% 
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code generation not running %%%%%%

if coder.target('MATLAB')  
    
    
    %%%%%% --- Find connected regions and return information about each region %%%%%%

    %Group pixels into connected regions, using the connection criteria of 8, which is the default   
    %setting for function regionprops.
    %M regions x 1 non-scalar struct, where M is the number of regions, with two fields,  
    %PixelIdxList and Centroid. Within each row of field PixelIdxList, P x 1 column vector, where P  
    %is the number of pixels in a given region, of type double. Within each row of field Centroid,  
    %1 x 2 row vector of type double.
    RegionIndicesTmp = regionprops(IsSkinMask, 'PixelIdxList', 'Centroid');

    %Number of regions
    %Scalar; type int32.
    NRegions = int32( numel(RegionIndicesTmp) );

    %Number of pixels per region
    %N x 1 column vector, where N is the number of regions; type double.
    RegionNPixels = zeros(NRegions, 1, 'single');

    for i = 1 : NRegions

        RegionNPixels(i) = numel( RegionIndicesTmp(i).PixelIdxList );    
    end   
    
    %%%%%% --- Convert centroid values from struct to matrix %%%%%%        

    %Convert from struct, where both X and Y stored in the same column, to matrix, where X and Y 
    %are in separate columns. 
    %Specify type int16 for use in other functions.

    Centroids = zeros(NRegions, 2, 'int16');

    for i = 1 : NRegions

        %Note: RegionIndices.Centroid is a N x 1 non-scalar struct, where N equals the number of 
        %regions. Each row contains the pixel indices of a given region.    
        Centroids(i, :) = RegionIndicesTmp(i).Centroid;
    end

    %Remove 'Centroid' field from struct:

    %This is removed to reduce the size of the inputs to the compiled function 
    %SkinDetect_RejectRegions. If function SkinDetect is run as a compiled function, than this 
    %reduction should not increase efficiency as the value would be passed by reference.
    %Note: function rmfield could be used, but, to keep code compatible for code generation if this
    %code were to be reconfigured for that purpose, function rmfield is not used.

    %Preallocate non-scalar struct with only field PixelIdxList
    RegionIndices = ...
        struct( ...
            'PixelIdxList', repmat({uint32(0)}, NRegions, 1) ...
            );

    %Assign values from old struct
    for i = 1 : NRegions

        RegionIndices(i).PixelIdxList = RegionIndicesTmp(i).PixelIdxList;
    end    

    %If no regions present or no centroids present 
    %Assign output indicating no regions are available.
    %If a region(s) exists but there are no centroids, assign the output for regions as if no 
    %regions exist. This will simplify the use of these outputs in other functions.
    if NRegions == 0 || all(Centroids == 0, 'all')
 
        %Number of regions
        NRegions = int32(0);
        
        %Number of pixels in each region output
        RegionNPixels = zeros(0, 1, 'single');

        %Pixel indices output
        RegionIndices = ...
            struct( ...
                'PixelIdxList', repmat({zeros(0, 1, 'uint32')}, 0, 1) ...
            );

        %Centroids output
        Centroids = zeros(0, 2, 'int16');
    end

    
%%%%%% Code generation running %%%%%%    
    
else 
    
    %%%%%% --- Code generation settings %%%%%%

    %Specify inlining for faster code execution
    coder.inline('always');

    %Declare variable-size variables:

    %                                              Upp. Bounds    Var. Size (T/F)
    coder.varsize('ConnComp.RegionIndices',        [inf, 1],      [1, 0]);    
    coder.varsize('ConnComp.RegionLengths',        [400, 1],      [1, 0]);
    coder.varsize('RegionNPixels',                 [400, 1],      [1, 0]);
    coder.varsize('RegionIndices',                 [400, 1],      [1, 0]); 
    coder.varsize('RegionIndices.PixelIdxList',    [inf, 1],      [1, 1]);
    coder.varsize('Centroids_Struct',              [400, 1],      [1, 0]);
    coder.varsize('RegionIndices_Double',          [inf, 1],      [1, 0]);
    coder.varsize('RegionEndIndex',                [400, 1],      [1, 0]);
    coder.varsize('Centroids_Double',              [400, 2],      [1, 0]);    
    coder.varsize('Centroids_Single',              [400, 2],      [1, 0]);

    %%%%%% --- Find connected regions and return pixel indices and pixel counts corresponding to each region %%%%%%

    %Group pixels into connected regions, using the connection criteria of 8, which is the default   
    %setting for function bwconncomp.     
    ConnComp = bwconncomp(IsSkinMask);

    %Output indicating the number of pixels in each region
    %Convert to type single for use in other functions.
    %M regions x 1 column vector; type single.
    RegionNPixels = single(ConnComp.RegionLengths);

    %Output indicating number of regions
    %Scalar; type int32.
    NRegions = int32( numel(RegionNPixels) );

    %Prevent dynamic memory allocation from colon operator by asserting maximum value
    assert(NRegions <= 400);
    
    %Preallocate non-scalar struct output for linear indices of pixels in each region
    %M regions x 1 non-scalar struct. Elements of type uint32.
    RegionIndices = ...
        coder.nullcopy( ...
            struct( ...
                'PixelIdxList', repmat( {zeros(0, 1, 'uint32')}, NRegions, 1 ) ...
            ) ...
        );
    
    %%%%%% --- Return centroids of connected regions %%%%%%

    %The centroids of each region
    %Pass output from function bwconncomp to function.
    %M regions x 1 non-scalar struct. Elements of type double.
    Centroids_Struct = regionprops(ConnComp, 'Centroid');

    %Number of centroids
    %Note: sometimes, the number of centroids may be less than the number of regions.
    %This might occur if one or more regions were quite small.
    NCentroids = int32( numel(Centroids_Struct) );
    
    %%%%%% --- Return region indices and centroids output %%%%%%

    %If at least 1 region and at least one centroid
    %Note: sometimes, one or more regions can be present while no centroids exist. This might occur 
    %if the region(s) are quite small.
    if NRegions > 0 && NCentroids > 0                            
        
        %Preallocate centroids output
        %Use type int16 for use in other functions.
        %M regions by 2 matrix; type int32.
        Centroids = coder.nullcopy( zeros(NCentroids, 2, 'int16') );
                              
        %Initialize the last linear index of the ith region
        RegionEndIndex_ith = int32(0);
        
        %Loop across regions
        %Set Centroids_Struct_Length, the length of Centroids_Struct.Centroid, as the maximum 
        %iteration because sometimes the length of Centroids_Struct.Centroid can be less than the 
        %length of RegionIndices.PixelIdxList. 
        for i = 1 : NCentroids

            %The number of pixels in the ith region
            %Cast to type int32.
            %Scalar; type int32.
            NRegions_ith = int32( RegionNPixels(i) );            
            
            %The first linear index of the ith region
            %Scalar; type int32.
            RegionBeginIndex_ith = RegionEndIndex_ith + 1;        
                                  
            %The last linear index of the ith region:
            %Scalar; type int32.
            RegionEndIndex_ith = NRegions_ith + RegionEndIndex_ith;
                       
            %Assign pixel indices output
            %Assign the pixel linear indices of a region to its corresponding row in the non-scalar 
            %struct.
            %Also cast from type double to type uint32. Although this casting increases 
            %computational time, this casting would be conducted anyway in function 
            %SkinDetect_RecordDiagnosticData. By casting now, the indices can be used in some
            %functions with a smaller type size.

            %Preallocate pixel indices for the ith region
            RegionIndices(i).PixelIdxList = coder.nullcopy( zeros(NRegions_ith, 1, 'uint32') );
            
            %Initialize index for pixel indices
            ElementIdx = int32(0);
            
            %Loop across pixels indices of ith region
            for j = RegionBeginIndex_ith : RegionEndIndex_ith                
                
                ElementIdx = ElementIdx + 1;
                
                %Cast to type uint32.
                %M regions x 1 non-scalar struct. Elements of type uint32.
                RegionIndices(i).PixelIdxList(ElementIdx) = ...
                    uint32( ...
                        ConnComp.RegionIndices(j, 1) ...
                    );                
            end    

            %Assign centroids output
            %Assign the centroids of a region to its corresponding row in the matrix. 
            for j = 1 : 2
                
                %Cast to type uint32.
                %M regions x 2 matrix; type int16.
                Centroids(i, j) = Centroids_Struct(i).Centroid(j); 
            end
        end           
 
        %If the length of RegionIndices.PixelIdxList (NRegions) is greater than the length of 
        %Centroids_Struct.Centroid (Centroids_Struct_Length).
        %As the previous loop only iterated to the length of Centroids_Struct.Centroid, more 
        %iterations will be required to finish looping across RegionIndices.PixelIdxList. 
        if NRegions > NCentroids 

            %Loop across remaining regions
            for i = NCentroids + 1 : NRegions

                %The number of pixels in the ith region
                %Cast to type int32.
                %Scalar; type int32.
                NRegions_ith = int32( RegionNPixels(i) );                        
                
                %The first linear index of the ith region
                %Scalar; type int32.
                RegionBeginIndex_ith = RegionEndIndex_ith + 1;        

                %The last linear index of the ith region
                %Scalar; type int32.
                RegionEndIndex_ith = NRegions_ith + RegionEndIndex_ith;
                
                %Assign pixel indices output
                %Assign the pixel linear indices of a region to its corresponding row in the non-scalar 
                %struct.                            

                %Preallocate pixel indices for the ith region
                RegionIndices(i).PixelIdxList = ...
                    coder.nullcopy( zeros(NRegions_ith, 1, 'uint32') );                
                
                %Initialize index for pixel indices
                ElementIdx = int32(0);
                
                %Loop across pixels indices of ith region               
                for j = RegionBeginIndex_ith : RegionEndIndex_ith                      
                    
                    ElementIdx = ElementIdx + 1;
                    
                    %Cast to type uint32.
                    %M regions x 1 non-scalar struct. Elements of type uint32.
                    RegionIndices(i).PixelIdxList(ElementIdx) = ...
                        uint32( ...
                            ConnComp.RegionIndices(j, 1) ...
                        );
                end    
            end                          
        end    
    
    %No regions present or no centroids present 
    %Assign output indicating no regions are available.
    %If a region(s) exists but there are no centroids, assign the output for regions as if no 
    %regions exist. This will simplify the use of these outputs in other functions.
    else

        %Number of regions
        NRegions = int32(0);
        
        %Number of pixels in each region output
        RegionNPixels = zeros(0, 1, 'single');

        %Pixel indices output
        %Note: this must be a 1 x 1 struct in order for elements to be of type uint32 rather than
        %of type double.
        RegionIndices = ...
            coder.nullcopy( ...
                struct( ...
                    'PixelIdxList', repmat({zeros(0, 1, 'uint32')}, 1, 1) ...
                ) ...
            );

        %Centroids output
        Centroids = zeros(0, 2, 'int16');
    end
end


end %end function


%=================================================================================================
%Code-generation and build script
%=================================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(SkinDetect_RegionInfo_mex) of the function.

%{

%Note: at present, a separate compiled version of this function is not used as it is compiled 
%within function SkinDetect.


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

codegen SkinDetect_RegionInfo.m -report -config cfg -args {IsSkinMaskCode}

%}        
        


