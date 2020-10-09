function [RegionRGBMeans, region_Z_Y, region_Z_Cb, region_Z_Cr, region_SD_Cr] = ...
             SkinDetect_RegionMetrics(RegionIndices, NRegions, RegionNPixels_Single, ...
                 RBounded_Uint8, GBounded_Uint8, BBounded_Uint8, YBounded_Single, ...
                 CbBounded_Single, CrBounded_Single, MeanOfMeansY, MeanOfMeansCb, ...
                 MeanOfMeansCr, StdDevOfMeansY, StdDevOfMeansCb, StdDevOfMeansCr) %#codegen                 
%SkinDetect_RegionMetrics   Calculate region RGB means and YCbCr Z-Scores within the skin-detection
%                           algorithm. 
%                                                               
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function SkinDetect_RejectRegions.
%
%
%    Code Generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.
%
%    This function uses a bounded variable size for variable NPixelsEachRegion_SingleCode to  
%    improve efficiency. Ensure that this input does not exceed these bounds.
% 
%
%    Description
%    -----------
%
%    Calculate region RGB means and YCbCr Z-Scores within the skin-detection algorithm.
%
%    See the file for function SkinDetect for additional description.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code generation specifications %%%%%%

%Specify inlining for faster code execution
coder.inline('always');

%Declare variable-size variables:

%Note: Improve efficiency by capping row length at 400 to prevent dynamic memory allocation.

%                               Upp. Bounds  Var. Size (T/F)
coder.varsize('region_M_R',     [400, 1],    [1, 0]);
coder.varsize('region_M_G',     [400, 1],    [1, 0]);
coder.varsize('region_M_B',     [400, 1],    [1, 0]);
coder.varsize('RegionRGBMeans', [400, 3],    [1, 0]);
coder.varsize('region_Z_Y',     [400, 1],    [1, 0]);
coder.varsize('region_Z_Cb',    [400, 1],    [1, 0]);
coder.varsize('region_Z_Cr',    [400, 1],    [1, 0]);
coder.varsize('region_SD_Cr',   [400, 1],    [1, 0]);


%%%%%% Preallocate variables %%%%%%

%Preallocate matrix to store R, G, and B means for each region
region_M_R = coder.nullcopy( zeros(NRegions, 1, 'double') );
region_M_G = coder.nullcopy( zeros(NRegions, 1, 'double') );
region_M_B = coder.nullcopy( zeros(NRegions, 1, 'double') );

%Preallocate vectors to store Y, Cb, and Cr z-scores for each region    
region_Z_Y  = coder.nullcopy( zeros(NRegions, 1, 'single') );
region_Z_Cb = coder.nullcopy( zeros(NRegions, 1, 'single') );
region_Z_Cr = coder.nullcopy( zeros(NRegions, 1, 'single') );

%Preallocate vector to store Cr standard deviation for each region
region_SD_Cr = coder.nullcopy( zeros(NRegions, 1, 'single') );


%%%%%% Take calculations across regions %%%%%%

%If called during code generation
%If called during code generation, use a parallel for loop (parfor), but use a for loop otherwise.
%The parallel for loop increases the performance of compiled-C code but decreases the performance 
%of Matlab code.
if ~ coder.target('MATLAB') 
 
    %Prevent dynamic memory allocation from colon operator by asserting length
    assert(NRegions <= 400);    
    
    %Loop across regions
    parfor i = 1 : NRegions

        %Local function
        [region_M_R(i), region_M_G(i), region_M_B(i), region_Z_Y(i), region_Z_Cb(i), ...
         region_Z_Cr(i), region_SD_Cr(i)] = ...
            Ops(i, RegionIndices, RegionNPixels_Single, RBounded_Uint8, ...
                GBounded_Uint8, BBounded_Uint8, YBounded_Single, CbBounded_Single, ...
                CrBounded_Single, MeanOfMeansY, MeanOfMeansCb, MeanOfMeansCr, StdDevOfMeansY, ...
                StdDevOfMeansCb, StdDevOfMeansCr);
    end

%Not called during code generation    
else

    %Loop across regions
    for i = 1 : NRegions

        %Local function
        [region_M_R(i), region_M_G(i), region_M_B(i), region_Z_Y(i), region_Z_Cb(i), ...
         region_Z_Cr(i), region_SD_Cr(i)] = ...
            Ops(i, RegionIndices, RegionNPixels_Single, RBounded_Uint8, ...
                GBounded_Uint8, BBounded_Uint8, YBounded_Single, CbBounded_Single, ...
                CrBounded_Single, MeanOfMeansY, MeanOfMeansCb, MeanOfMeansCr, StdDevOfMeansY, ...
                StdDevOfMeansCb, StdDevOfMeansCr);
    end    
end
 
%%%%%% --- Concatenate R, G, and B means %%%%%% 

RegionRGBMeans = [region_M_R, region_M_G, region_M_B];


end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function [region_M_R_ith, region_M_G_ith, region_M_B_ith, region_Z_Y_ith, region_Z_Cb_ith, ...
          region_Z_Cr_ith, region_SD_Cr_ith] = ...
             Ops(i, RegionIndices, RegionNPixels_Single, RBounded_Uint8, ...
                 GBounded_Uint8, BBounded_Uint8, YBounded_Single, CbBounded_Single, ...
                 CrBounded_Single, MeanOfMeansY, MeanOfMeansCb, MeanOfMeansCr, StdDevOfMeansY, ...
                 StdDevOfMeansCb, StdDevOfMeansCr)
%Ops   Take means, z-scores, and a standard deviation of the ith region.  
%
%    Description:
%
%    - Take the means of the R, G, and B channels of the ith region.
%
%    - Take the z-scores of the Y, Cb, and Cr channels of the ith region.
%
%      The z-score for a region is calculated by subtracting its mean from the reference mean and
%      dividing by the reference standard deviation. The reference mean and standard deviation are
%      from skin-color samples collected from ROIs of the video (see function 
%      ROIMeans_FirstRead_CollectSkinColorSamples).
%
%    - Take the standard deviation of the Cr channel of the ith region.
%
%    Use integer arithmetic rather than floating-point arithmetic for efficiency if overflow will
%    not occur.
%
%    Note: Different implements are used for code generation and Matlab code.


%%%%%% Extract linear indices of ith region %%%%%% 

%Note: RegionIndices.PixelIdxList is a N x 1 non-scalar struct, where N equals the number of
%regions. Each row contains the pixel indices of a given region.
%P x 1 column vector; type double.
RegionIndices_ithregion = RegionIndices(i).PixelIdxList;

    
%%%%%% If called during code generation %%%%%%

%If called during code generation, use for loop; if using Matlab code, use vectorization.

if ~ coder.target('MATLAB') %if code generation

    %Inline function
    coder.inline('always');

    %Denominator for ith region 
    %Scalar; type single.
    RegionNPixels_Single_ith = RegionNPixels_Single(i);

    %%%%%% --- Optimized by integer arithmetic %%%%%%
    
    %Use algorithm optimized by integer arithmetic if all indices less than specified length
    if RegionNPixels_Single_ith < 15686000

        %Accumulators for ith region
        %Scalars; type uint32 or single.
        SumR_uint32 = uint32(0);
        SumG_uint32 = uint32(0);
        SumB_uint32 = uint32(0);
        SumY        = single(0);
        SumCb       = single(0);
        SumCr       = single(0);
        
        %Loop across elements, j, corresponding to ith region index 
        for j = 1 : RegionNPixels_Single_ith

            %jth element of ith region index
            %Scalar; type uint32.
            jj = RegionIndices_ithregion(j);

            %RGB colorspace sums
            %Cast to type uint32 for efficiency.
            %Scalars; type uint32.
            SumR_uint32 = SumR_uint32 + uint32( RBounded_Uint8(jj) );
            SumG_uint32 = SumG_uint32 + uint32( GBounded_Uint8(jj) );
            SumB_uint32 = SumB_uint32 + uint32( BBounded_Uint8(jj) );

            %YCbCr colorspace sums
            %Scalars; type single.
            SumY  = SumY  + YBounded_Single(jj);    
            SumCb = SumCb + CbBounded_Single(jj);    
            SumCr = SumCr + CrBounded_Single(jj);
        end 
        
        %%%%%% >>>>>> Take RGB means of ith region %%%%%% 

        %Take means and cast to type double for output.
        %Scalars; type double.

        %Red channel mean
        region_M_R_ith = double( single(SumR_uint32) / RegionNPixels_Single_ith );

        %Green channel mean
        region_M_G_ith = double( single(SumG_uint32) / RegionNPixels_Single_ith );

        %Blue channel mean
        region_M_B_ith = double( single(SumB_uint32) / RegionNPixels_Single_ith );    
        
    %%%%%% --- Not optimized by integer arithmetic %%%%%%        
        
    else

        %Accumulators for ith region
        %Scalars; type single.
        SumR  = single(0);
        SumG  = single(0);
        SumB  = single(0);
        SumY  = single(0);
        SumCb = single(0);
        SumCr = single(0);        
        
        %Loop across elements, j, corresponding to ith region index 
        for j = 1 : RegionNPixels_Single_ith

            %jth element of ith region index
            %Scalar; type uint32.
            jj = RegionIndices_ithregion(j);
            
            %RGB colorspace sums
            %Cast to type uint32 for efficiency.
            %Scalars; type single.
            SumR = SumR + single( RBounded_Uint8(jj) );
            SumG = SumG + single( GBounded_Uint8(jj) );
            SumB = SumB + single( BBounded_Uint8(jj) );

            %YCbCr colorspace sums
            %Scalars; type single.
            SumY  = SumY  + YBounded_Single(jj);    
            SumCb = SumCb + CbBounded_Single(jj);    
            SumCr = SumCr + CrBounded_Single(jj);
        end 
        
        %%%%%% >>>>>> Take RGB means of ith region %%%%%% 

        %Take means and cast to type double for output.
        %Scalars; type double.

        %Red channel mean
        region_M_R_ith = double( SumR / RegionNPixels_Single_ith );

        %Green channel mean
        region_M_G_ith = double( SumG / RegionNPixels_Single_ith );

        %Blue channel mean
        region_M_B_ith = double( SumB / RegionNPixels_Single_ith );
    end   

    %%%%%% --- Take YCbCr z-scores and Cr standard deviation of ith region %%%%%%    

    %Scalars; type single.
    
    %ith region YCbCr z-scores:   
    
    %Y channel z-score
    region_Z_Y_ith = ...
        ( SumY / RegionNPixels_Single_ith - MeanOfMeansY ) / ...
        StdDevOfMeansY;                                                

    %Cb channel z-score
    region_Z_Cb_ith = ...
        ( SumCb / RegionNPixels_Single_ith - MeanOfMeansCb ) / ...
        StdDevOfMeansCb;  

    %Cr channel mean
    region_M_Cr_ith = SumCr / RegionNPixels_Single_ith;
    
    %Cr channel z-score
    region_Z_Cr_ith = (region_M_Cr_ith - MeanOfMeansCr) / StdDevOfMeansCr;
        
    %ith region Cr standard deviation:
    
    %If more than 1 pixel for the region 
    if RegionNPixels_Single_ith > 1
       
        %Initialize accumulator
        SumSquares = single(0);
        
        for j = 1 : RegionNPixels_Single_ith
            
            jj = RegionIndices_ithregion(j);
            
            Deviation = CrBounded_Single(jj) - region_M_Cr_ith;
            
            %Note: use multiply rather than ^2 for efficiency
            Deviation = Deviation * Deviation;
            
            SumSquares = SumSquares + Deviation;
        end
        
        %Cr channel standard deviation       
        region_SD_Cr_ith = sqrt( SumSquares / (RegionNPixels_Single_ith - 1) );

    else

        region_SD_Cr_ith = single(0);       
    end    

    
%%%%%% Using Matlab Code %%%%%%

else

    %Note: sum() / numel() shows better performance than mean().
    
    %%%%%% --- Take RGB means of ith region %%%%%%    

    %Scalars; type double.
    
    %Denominator
    RegionNPixels_Double_ith = RegionNPixels_Double(i);
 
    %Red channel mean
    region_M_R_ith = sum( RBounded_Uint8(RegionIndices_ithregion) ) / RegionNPixels_Double_ith;

    %Green channel mean
    region_M_G_ith = sum( GBounded_Uint8(RegionIndices_ithregion) ) / RegionNPixels_Double_ith;

    %Blue channel mean
    region_M_B_ith = sum( BBounded_Uint8(RegionIndices_ithregion) ) / RegionNPixels_Double_ith;

    %%%%%% --- Take YCbCR z-scores and Cr standard deviation of ith region %%%%%% 

    %Scalars; type single.
    
    %Denominator
    RegionNPixels_Single_ith = RegionNPixels_Single(i);

    %ith region YCbCr z-scores:
    
    %Y channel z-score
    region_Z_Y_ith  = ( ...
                          sum( YBounded_Single(RegionIndices_ithregion) ) / ... 
                          RegionNPixels_Single_ith - MeanOfMeansY ...                                       
                     ) ...
                     / StdDevOfMeansY;                                                

    %Cb channel z-score             
    region_Z_Cb_ith = ( ...
                          sum( CbBounded_Single(RegionIndices_ithregion) ) / ...
                          RegionNPixels_Single_ith - MeanOfMeansCb ...                              
                     ) ...              
                     / StdDevOfMeansCb;  

    %Cr channel mean           
    region_M_Cr_ith = sum( CrBounded_Single(RegionIndices_ithregion) ) / RegionNPixels_Single_ith;

    %Cr channel z-score
    region_Z_Cr_ith = (region_M_Cr_ith - MeanOfMeansCr) / StdDevOfMeansCr;                                                                                      

    %ith region Cr standard deviation:             
                 
    %If more than 1 pixel for the region 
    if RegionNPixels_Single_ith > 1

        %Cr channel standard deviation
        region_SD_Cr_ith = ...
            sqrt( ...
                sum( ...
                    ( ...                       
                        CrBounded_Single(RegionIndices_ithregion) - ...
                        region_M_Cr_ith ...
                    ) .^ single(2) ...
                ) / (RegionNPixels_Single_ith - 1) ...
            );     

    else

        region_SD_Cr_ith = single(0);       
    end        
end


end %end local function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(SkinDetect_RegionMetrics_mex) of the function.

%Note: at present, a separate compiled version of this function is not used as it is compiled 
%within function SkinDetect.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

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

%Input Argument                           Example Code                 Upp. Bounds     Var. Size (T/F)  Type
RegionNPixels_SingleCode  = coder.typeof( zeros(50, 1, 'single'),      [400, 1],       [1, 0] );        %single
RUint8Code                = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8
GUint8Code                = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8
BUint8Code                = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8
YSingleCode               = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single
CbSingleCode              = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single
CrSingleCode              = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single


%%%%%% Specify fixed-size input arguments %%%%%%

%                       Example Code                                                                 
NRegionsCode          = int32(1);                                                                  
MeanOfMeansYCode      = single(1);                                                                  
MeanOfMeansCbCode     = single(1);                                                                  
MeanOfMeansCrCode     = single(1);                                                                    
StdDevOfMeansYCode    = single(1);                                                                 
StdDevOfMeansCbCode   = single(1);                                                                   
StdDevOfMeansCrCode   = single(1);                                                                    


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

codegen SkinDetect_RegionMetrics.m -report -config cfg -args {RegionIndicesCode, NRegionsCode, RegionNPixels_SingleCode, RUint8Code, GUint8Code, BUint8Code, YSingleCode, CbSingleCode, CrSingleCode, MeanOfMeansYCode, MeanOfMeansCbCode, MeanOfMeansCrCode, StdDevOfMeansYCode, StdDevOfMeansCbCode, StdDevOfMeansCrCode}

%}




