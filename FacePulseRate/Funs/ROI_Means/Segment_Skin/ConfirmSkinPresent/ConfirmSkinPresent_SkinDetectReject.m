function SumPixelsPass = ...
             ConfirmSkinPresent_SkinDetectReject(IsSkinMask, RBounded_Uint8, GBounded_Uint8, ...
                 BBounded_Uint8, YBounded_Single, CbBounded_Single, CrBounded_Single, ...
                 NRows_Matrix, NCols_Matrix, SkinDetectConfig) %#codegen               
%ConfirmSkinPresent_SkinDetectReject   Determine the number of pixels that pass the rejection
%                                      procedure from the skin-detection algorithm.
%                                                               
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function ConfirmSkinPresent.
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
%    Use the rejection procedure from the skin-detection algorithm (see functions
%    SkinDetect_RejectRegions and SkinDetect) to refine the skin-segmentation mask (IsSkinMask). 
%    Specifically, partition the mask into regions and exclude regions that do not pass all 
%    rejection thresholds. Then, return the number of remaining pixels classified as skin (true).
%
%    The rejection thresholds used on each region include a minimum pixel count threshold, a
%    probability threshold based on the R, G, and B channels of the ROI, and z-score thresholds
%    based on the Cb and Cr channels of the ROI.
%
%
%    Accuracy
%    --------
%
%    If there are fewer skin-color samples than required for tailored skin segmentation, the 
%    proportion of pixels may be less accurate (less conservative). Whether the required number of 
%    skin-color samples has been satisfied is indicated by 
%    SkinSegmentConfig.TailoredData.OpsReadyTF.
%
%    If there are fewer skin-color samples than required for skin detection (see function 
%    ConfirmSkinPresent_SkinDetectReject), the proportion of pixels may be less accurate (less 
%    conservative. Whether the required number of skin-color samples has been satisfied is 
%    indicated by SkinDetectConfig.Thresholds.SkinColorSamples_NThresholdPassedTF.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Extract information for the rejection thresholds from the skin-detection algorithm %%%%%%

%Thresholds:

%Note: values assigned by function SkinDetectConfig_Setup.

%RGB probability threshold
%Scalar; type single.
ThresholdRGBProb = SkinDetectConfig.Thresholds.ColorThreshold(1);

%Cb and Cr z-score thresholds
%Scalars; type single.
ThresholdZScoreCb = SkinDetectConfig.Thresholds.ColorThreshold(2); 
ThresholdZScoreCr = SkinDetectConfig.Thresholds.ColorThreshold(3);

%Region pixel count threshold
%Scalar; type single.
RegionNThreshold = SkinDetectConfig.Thresholds.RegionNThreshold;

%Theta values for determining RGB probability:

%Note: values assigned by function function SkinDetect_RGBProbSkinTrain.

%4 x 1 column vector; type double.
RGBTheta = SkinDetectConfig.Thresholds.RGBProbTheta;

%Reference means and standard deviations for determining Cb and Cr z-scores for each region:

%Note: values assigned by function SkinDetect_SetThresholds. 

%Scalars; type single.
MeanOfMeansCb   = SkinDetectConfig.Thresholds.YCbCrMeanOfMeans(2);
StdDevOfMeansCb = SkinDetectConfig.Thresholds.YCbCrStdDevOfMeans(2);
MeanOfMeansCr   = SkinDetectConfig.Thresholds.YCbCrMeanOfMeans(3);
StdDevOfMeansCr = SkinDetectConfig.Thresholds.YCbCrStdDevOfMeans(3);


%%%%%% Partition skin-segmentation mask into smaller regions using grid lines %%%%%%

%Note: a similar procedure is conducted in function SkinDetect_PartitionRegions.

%Specify the intervals to use to partition the skin-segmentation mask
%Scalar; type single.
%Note: values assigned by function SkinDetectConfig_Setup.
PartitionColInterval = SkinDetectConfig.PartitionColInterval;
PartitionRowInterval = SkinDetectConfig.PartitionRowInterval; 

%Insert vertical lines:

Col_ith = int16(1);

while Col_ith <= NCols_Matrix
              
    for j = 1 : NRows_Matrix 
        
        IsSkinMask(j, Col_ith) = false;        
    end    
    
    Col_ith = Col_ith + PartitionColInterval;  
end

%Insert horizontal lines: 

for i = 1 : NCols_Matrix

    Row_ith = int16(1);

    while Row_ith <= NRows_Matrix 
        
       IsSkinMask(Row_ith, i) = false;
       
       Row_ith = Row_ith + PartitionRowInterval;         
    end            
end


%%%%%% Find connected regions and return pixel indices and pixel counts corresponding to each region %%%%%%

%Group pixels into connected regions, using the connection criteria of 8, which is the default   
%setting for function bwconncomp.     
ConnComp = bwconncomp(IsSkinMask);

%Output indicating the number of pixels in each region
%M regions x 1 column vector; type double.
RegionNPixels = ConnComp.RegionLengths;

%Output indicating number of regions
%Scalar; type int32.
NRegions = int32( numel(RegionNPixels) );

%Prevent dynamic memory allocation from colon operator by asserting maximum value
assert(NRegions <= 400);


%%%%%% Determine which regions pass the thresholds and count the number of pixels of passing regions %%%%%%

%If no regions present
if NRegions == 0

    SumPixelsPass = int32(0);
    
    return
    
%If at least 1 region present  
else

    %Initialize sum accumulator for total pixels classified as true
    SumPixelsPass = int32(0);
    
    %Initialize the last linear index of the ith region
    RegionEndIndex_ith = int32(0);

    %Loop across regions
    %Set Centroids_Struct_Length, the length of Centroids_Struct.Centroid, as the maximum 
    %iteration because sometimes the length of Centroids_Struct.Centroid can be less than the 
    %length of RegionIndices.PixelIdxList. 
    for i = 1 : NRegions

        %The number of pixels in the ith region
        %Cast to type int32.
        %Scalar; type int32.
        RegionNPixels_single_ith = single( RegionNPixels(i) ); 
        RegionNPixels_int32_ith  = int32( RegionNPixels_single_ith );

        %The first linear index of the ith region
        %Scalar; type int32.
        RegionBeginIndex_ith = RegionEndIndex_ith + 1;        

        %The last linear index of the ith region:
        %Scalar; type int32.
        RegionEndIndex_ith = RegionNPixels_int32_ith + RegionEndIndex_ith;

        %Determine whether the ith region passes the thresholds
        %Local function.
        %Scalar; type logical.
        PassTF = ...
             Ops(RegionBeginIndex_ith, RegionEndIndex_ith, ConnComp, RBounded_Uint8, ...
                 GBounded_Uint8, BBounded_Uint8, YBounded_Single, CbBounded_Single, ...
                 CrBounded_Single, RegionNPixels_single_ith, MeanOfMeansCb, MeanOfMeansCr, ...
                 StdDevOfMeansCb, StdDevOfMeansCr, ThresholdRGBProb, RGBTheta, ...
                 ThresholdZScoreCb, ThresholdZScoreCr, RegionNThreshold);

        %If the ith region passed the thresholds
        if PassTF  
            
            %Sum of pixels across all regions that passed thresholds
            %Scalar; type int32.
            SumPixelsPass = SumPixelsPass + RegionNPixels_int32_ith;
        end
    end           
end


end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function PassTF = ...
             Ops(RegionBeginIndex_ith, RegionEndIndex_ith, ConnComp, RBounded_Uint8, ...
                 GBounded_Uint8, BBounded_Uint8, YBounded_Single, CbBounded_Single, ...
                 CrBounded_Single, RegionNPixels_single_ith, MeanOfMeansCb, MeanOfMeansCr, ...
                 StdDevOfMeansCb, StdDevOfMeansCr, ThresholdRGBProb, RGBTheta, ...
                 ThresholdZScoreCb, ThresholdZScoreCr, RegionNThreshold)
%Ops   Take means and z-scores of the ith region.  
%
%    Description:
%
%    - Take the means of the R, G, and B channels of the ith region.
%
%    - Take the z-scores of the Cb and Cr channels of the ith region.
%
%      The z-score for a region is calculated by subtracting its mean from the reference mean and
%      dividing by the reference standard deviation. The reference mean and standard deviation are
%      from skin-color samples collected from ROIs of the video (see function 
%      ROIMeans_FirstRead_CollectSkinColorSamples).
%
%    Use integer arithmetic rather than floating-point arithmetic for efficiency if overflow will
%    not occur.
%
%    Note: Different implements are used for code generation and Matlab code.    


%Inline function
coder.inline('always');


%%%%%% Determine whether ith region passed pixel-count threshold %%%%%%

%Determine whether (pass/not pass) ith region has a quantity of pixels 
%greater than or equal to the threshold for minimum quantity of pixels.
%Variable specifying threshold (RegionNThreshold) assigned at top.
%Scalar; type logical.
PassTF = RegionNPixels_single_ith > RegionNThreshold;


%%%%%% Determine whether ith region passed color thresholds %%%%%%

if PassTF

    %%%%%% --- Optimized by integer arithmetic %%%%%%

    %Use algorithm optimized by integer arithmetic if all indices less than specified length
    if RegionNPixels_single_ith < 15686000

        %Accumulators for ith region
        %Scalars; type uint32 or single.
        SumR_uint32 = uint32(0);
        SumG_uint32 = uint32(0);
        SumB_uint32 = uint32(0);
        SumY        = single(0);
        SumCb       = single(0);
        SumCr       = single(0);

        %Loop across elements, j, corresponding to ith region index     
        for j = RegionBeginIndex_ith : RegionEndIndex_ith                

            jj = ConnComp.RegionIndices(j, 1);

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
        region_M_R_ith = double( single(SumR_uint32) / RegionNPixels_single_ith );

        %Green channel mean
        region_M_G_ith = double( single(SumG_uint32) / RegionNPixels_single_ith );

        %Blue channel mean
        region_M_B_ith = double( single(SumB_uint32) / RegionNPixels_single_ith );    

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
        for j = RegionBeginIndex_ith : RegionEndIndex_ith                

            jj = ConnComp.RegionIndices(j, 1);

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
        region_M_R_ith = double( SumR / RegionNPixels_single_ith );

        %Green channel mean
        region_M_G_ith = double( SumG / RegionNPixels_single_ith );

        %Blue channel mean
        region_M_B_ith = double( SumB / RegionNPixels_single_ith );
    end   

    %%%%%% --- Take Cb and Cr z-scores of the ith region %%%%%%    

    %Scalars; type single.

    %ith region z-scores:   

    %Cb channel z-score
    region_Z_Cb_ith = ...
        ( SumCb / RegionNPixels_single_ith - MeanOfMeansCb ) / ...
        StdDevOfMeansCb;  

    %Cr channel z-score
    region_Z_Cr_ith = ...
        ( SumCr / RegionNPixels_single_ith - MeanOfMeansCr ) / ...
        StdDevOfMeansCr;  

    %%%%%% --- Calculate RGB probabilities and determine whether threshold passed %%%%%%

    %Concatenate the R, G, and B means
    %1 x 3 row vector; type double.
    RGBMeans_ith = [region_M_R_ith, region_M_G_ith, region_M_B_ith];

    %Return probabilities for ith region that ROI RGB means are skin.
    %To do so, use function SkinDetect_RGBProbSkin. This function is also supplied with theta 
    %parameters, which were calculated from color means across ROIs from the primary face-detection 
    %algorithm and from colors means from external sources. The theta parameters were returned by 
    %function SkinDetect_RGBProbSkinTrain, which was called by function SkinDetect_SetThresholds, 
    %which was called by function ROIMeans_FirstRead_SetThresholds. 

    %Scalar; type double.
    %Note: 'SkinDetect_RGBProbSkin' is a custom function located within folder 'FacePulseRate'.  
    RegionRGBProbSkin = SkinDetect_RGBProbSkin(RGBMeans_ith, RGBTheta);

    %Determine whether (pass/not pass) the region is above the RGB probability threshold.
    %This threshold is specified as an argument (SkinClassifyRegionColorThresholds(1)) to function
    %FacePulseRate.
    %Scalar; type logical.
    PassTF = RegionRGBProbSkin >= ThresholdRGBProb; 

    %%%%%% --- Determine whether passes YCbCr z-score thresholds %%%%%%

    %If the ith region passed the RGB probability thresholds
    if PassTF

        %See notes in function SkinDetect.

        %Skin-detection candidates are rejected if outside thresholds, which are determined by the
        %mean +/- a specified standard deviation. 

        %Determine whether (pass/not pass) the region is within the Cb and Cr thresholds 
        %These thresholds are specified as an argument (SkinClassifyRegionColorThresholds(2 : 3)) 
        %to function FacePulseRate. 
        %Scalar; type logical.
        PassTF = ...
            abs(region_Z_Cb_ith) <= ThresholdZScoreCb && ... compare against Cb z-score threshold
            abs(region_Z_Cr_ith) <= ThresholdZScoreCr;   %   compare against Cr z-score threshold
    end
end


end %end local function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(ConfirmSkinPresent_SkinDetectReject_mex) of the function.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%Input Argument                      Example Code                 Upp. Bounds     Var. Size (T/F)  Type
IsSkinMaskCode       = coder.typeof( zeros(500, 500, 'logical'),  [inf, inf],     [1, 1] );        %logical
RBounded_Uint8Code   = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8
GBounded_Uint8Code   = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8
BBounded_Uint8Code   = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8
YBounded_SingleCode  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single
CbBounded_SingleCode = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single
CrBounded_SingleCode = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single
                

%%%%%% Specify fixed-size input arguments %%%%%%

NRows_MatrixCode = int32(0);
NCols_MatrixCode = int32(0);

SkinDetectConfigCode = ... 
    struct( ...
        'ROISkinTF', false, ...
        'Thresholds', ...
        struct( ...   
            'SetTF', false, ...
            'SkinColorSamples_NThreshold', double(0), ...
            'SkinColorSamples_NThresholdPassedTF', false, ...
            'SkinColorSamples_HighNThreshold', double(0), ... 
            'SkinColorSamples_HighNThresholdPassedTF', false, ...
            'SkinColorSamples_HighNThresholdIdx', int32(0), ... 
            'ColorThreshold', zeros(1, 3, 'single'), ...
            'ColorThresholdHighN', zeros(1, 3, 'single'), ...
            'RecentThresholdOpsFrameIdx', int32(0), ...
            'ThresholdOpsInterval', int32(0), ...
            'ThresholdOpsRunCurrentFrameTF', false, ...
            'ColorSDThreshold', single(0), ...
            'RGBProbTheta', zeros(4, 1, 'double'), ...
            'YCbCrMeanOfMeans', zeros(1, 3, 'single'), ...
            'YCbCrStdDevOfMeans', zeros(1, 3, 'single'), ...
            'RegionNThreshold', single(0) ...
        ), ...
        'ROISkinSkipFrameThreshold', int32(0), ...
        'ROISkin_BoundingBoxGrowthThreshold', int32(0), ...
        'ROISkin_BoundingBoxGrowthFactor', double(0), ...
        'ROISkin_InitialBoundingBoxScale', double(0), ...
        'ROISkinRegionMinSizeFactor', single(0), ...
        'ROISkinRegionProximityWeight', double(0), ...
        'ROISkinSmoothingWindow', double(0), ...
        'PartitionColInterval', int16(0), ...
        'PartitionRowInterval', int16(0), ...
        'SkinDetectionReadyTF', false, ...
        'ROISkin_BoundingBoxEnlargementFactor', double(0), ...
        'ROISkinSkipFrameThreshold_adjusted', int32(0), ...
        'UseCompiledFunctionsTF', false ...
    );                                                         


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

codegen ConfirmSkinPresent_SkinDetectReject.m -report -config cfg -args {IsSkinMaskCode, RBounded_Uint8Code, GBounded_Uint8Code, BBounded_Uint8Code, YBounded_SingleCode, CbBounded_SingleCode, CrBounded_SingleCode, NRows_MatrixCode, NCols_MatrixCode, SkinDetectConfigCode}

%}



                 
                 