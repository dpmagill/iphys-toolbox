function [RegionPassAllThresholdsTF_LogIdx, RegionNPixels_PassNThresholdTF_LogIdx, ...
          RegionSD_Cr_PassThresholdTF_LogIdx, RegionNPixels, NRegionsPass, RegionRGBProbSkin, ... 
          RegionZ_Y, RegionZ_Cb, RegionZ_Cr, RegionSD_Cr] = ...                             
             SkinDetect_RejectRegions(SkinDetectConfig, RegionIndices, NRegions, RegionNPixels, ...
                 RBounded_Uint8, GBounded_Uint8, BBounded_Uint8, YBounded_Single, ...
                 CbBounded_Single, CrBounded_Single) %#codegen
%SkinDetect_RejectRegions    Apply skin-detection rejection thresholds to partitioned regions. 
%                                  
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function SkinDetect.
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
%    Apply thresholds to regions, which were partitioned by function SkinDetect_PartitionRegions, 
%    to determine which regions to reject. The output of intermediate operations, such as color 
%    z-scores, is returned for reuse by other steps of the skin-detection algorithm.
% 
%    For further discussion, see the description of the skin-detection algorithm in the file of
%    function SkinDetect.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.   


%%%%%% Code-generation settings %%%%%%

%Inline function
coder.inline('always');

%Declare variables:

%Note: set bounds so that these variables do not use dynamic memory allocation, increasing 
%efficiency.

%                                                      Upp. Bounds  Var. Size (T/F)
coder.varsize('RegionYCbCrZ_PassThresholdsTF_LogIdx',  [400, 1],    [1, 0]);
coder.varsize('RegionRGBMeans',                        [400, 3],    [1, 0]);
coder.varsize('RegionRGB_PassThresholdsTF_LogIdx',     [400, 1],    [1, 0]);


%%%%%% Extract information for the rejection thresholds %%%%%%

%Note: values assigned by function SkinDetectConfig_Setup.

%%%%%% --- Color thresholds %%%%%%

%If the color thresholds were based upon a large number of skin-color samples present, narrow some
%color thresholds. Whether there is a large number of skin-color samples present is determined by
%SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdPassedTF. This is conducted because 
%when there is a greater number of ROIs, the standard deviations of color samples may become more  
%expansive, requiring more narrow thresholds to reduce false positives (classifying non-skin as 
%skin). SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdPassedTF is assigned by function
%SkinDetect_SetThresholds. For details on the collection of skin-color samples, see function 
%ROIMeans_FirstRead_CollectSkinColorSamples.

%If there are a large number of skin-color samples 
if SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdPassedTF

    %RGB probability threshold
    %Scalar; type single.
    ThresholdRGBProb = SkinDetectConfig.Thresholds.ColorThresholdHighN(1);

    %Cb and Cr z-score thresholds
    %Scalars; type single.
    ThresholdZScoreCb = SkinDetectConfig.Thresholds.ColorThresholdHighN(2); 
    ThresholdZScoreCr = SkinDetectConfig.Thresholds.ColorThresholdHighN(3);

%If there is not a large number of skin-color samples
else
 
    %RGB probability threshold
    %Scalar; type single.
    ThresholdRGBProb = SkinDetectConfig.Thresholds.ColorThreshold(1);

    %Cb and Cr z-score thresholds
    %Scalars; type single.
    ThresholdZScoreCb = SkinDetectConfig.Thresholds.ColorThreshold(2); 
    ThresholdZScoreCr = SkinDetectConfig.Thresholds.ColorThreshold(3);        
end

%Cr standard deviation threshold
%Scalar; type single.
ThresholdSDCr = SkinDetectConfig.Thresholds.ColorSDThreshold;

%%%%%% --- Region pixel count threshold %%%%%%

%Scalar; type single.
RegionNThreshold = SkinDetectConfig.Thresholds.RegionNThreshold; 

%%%%%% --- Theta values for determining RGB probability %%%%%%

%Note: values assigned by function function SkinDetect_RGBProbSkinTrain.

%4 x 1 column vector; type double.
RGBTheta = SkinDetectConfig.Thresholds.RGBProbTheta;

%%%%%% --- Reference means and standard deviations for determining Y, Cb, and Cr z-scores of each region %%%%%%

%Note: values assigned by function SkinDetect_SetThresholds. 

%Scalars; type single.
MeanOfMeansY    = SkinDetectConfig.Thresholds.YCbCrMeanOfMeans(1);
StdDevOfMeansY  = SkinDetectConfig.Thresholds.YCbCrStdDevOfMeans(1);
MeanOfMeansCb   = SkinDetectConfig.Thresholds.YCbCrMeanOfMeans(2);
StdDevOfMeansCb = SkinDetectConfig.Thresholds.YCbCrStdDevOfMeans(2);
MeanOfMeansCr   = SkinDetectConfig.Thresholds.YCbCrMeanOfMeans(3);
StdDevOfMeansCr = SkinDetectConfig.Thresholds.YCbCrStdDevOfMeans(3);


%%%%%% Apply pixel-count threshold %%%%%%

%Assign a logical vector indicating whether (pass/not pass) the region has a quantity of pixels 
%greater than or equal to the threshold for minimum quantity of pixels.
%Variable specifying threshold (RegionNThreshold) assigned at top.
%M regions x 1 column vector; type logical.
RegionNPixels_PassNThresholdTF_LogIdx = RegionNPixels > RegionNThreshold; 


%%%%%% Calculate region RGB probability and YCbCr z-scores %%%%%%

%%%%%% --- Calculate RGB means and YCbCr z-scores %%%%%%

%Regarding YCbCr z-scores, the z-score for a region is calculated by subtracting its mean from the 
%mean across ROIs identified by the primary face-detection algorithm algorithm and dividing this by  
%the standard deviation of means across ROIs identified by the primary algorithm. The Y-color 
%dimension is not used for the rejected thresholds but is used later for determining the selected  
%skin region out of skin region candidates.

%The means and standard deviations across ROIs were returned as output by function
%SkinDetect_SetThresholds. The linear index of a given region is used to specify the pixels that   
%comprise each region.

%Note: 'SkinDetect_RegionMetrics' is a custom function located within folder 'FacePulseRate'.  
[RegionRGBMeans, ... M regions x 3 matrix; type double
 RegionZ_Y,      ... M regions x 1 column vector; type single
 RegionZ_Cb,     ... M regions x 1 column vector; type single
 RegionZ_Cr,     ... M regions x 1 column vector; type single
 RegionSD_Cr] =  ... M regions x 1 column vector; type single
    SkinDetect_RegionMetrics(RegionIndices, NRegions, RegionNPixels, RBounded_Uint8, ...
        GBounded_Uint8, BBounded_Uint8, YBounded_Single, CbBounded_Single, CrBounded_Single, ...
        MeanOfMeansY, MeanOfMeansCb, MeanOfMeansCr, StdDevOfMeansY, StdDevOfMeansCb, ...  
        StdDevOfMeansCr);   

%%%%%% --- Calculate RGB probabilities; assign logical vector indicating regions that pass thresholds %%%%%%

%Return probabilities for each region that ROI RGB means are skin (as vector with each row  
%referencing a region).
%To do so, use function SkinDetect_RGBProbSkin. This function is also supplied with theta 
%parameters, which were calculated from color means across ROIs from the primary face-detection 
%algorithm and from colors means from external sources. The theta parameters were returned by 
%function SkinDetect_RGBProbSkinTrain, which was called by function SkinDetect_SetThresholds, which 
%was called by function ROIMeans_FirstRead_SetThresholds. 

%M regions x 1 column vector; type double.
%Note: 'SkinDetect_RGBProbSkin' is a custom function located within folder 'FacePulseRate'.  
RegionRGBProbSkin = SkinDetect_RGBProbSkin(RegionRGBMeans, RGBTheta);

%Assign a logical vector indicating whether (pass/not pass) the region is above the RGB probability 
%threshold.
%This threshold is specified as an argument (SkinClassifyRegionColorThresholds(1)) to function
%FacePulseRate.
%M regions x 1 column vector; type logical.
RegionRGB_PassThresholdsTF_LogIdx = RegionRGBProbSkin >= ThresholdRGBProb;

%%%%%% --- Assign logical vector indicating regions that pass YCbCr z-score thresholds %%%%%%

%See notes in function SkinDetect.

%Skin-detection candidates are rejected if outside thresholds, which are determined by the mean +/-
%a specified standard deviation; however, thresholds are only used for Cb and Cr because of greater
%luminance invariance compared to Y.

%Also, skin-detection candidates that pass the thresholds are given more weight toward selection if 
%they are closer to these means; for these weights, Y is used.

%Assign a logical vector indicating whether (pass/not pass) the region is within the CbCr 
%thresholds. These thresholds are specified as an argument (SkinClassifyRegionColorThresholds(2:3))
%to function FacePulseRate. 
%M regions x 1 column vector; type logical.
RegionYCbCrZ_PassThresholdsTF_LogIdx = ...
    abs(RegionZ_Cb) <= ThresholdZScoreCb & ... compare against Cb z-score threshold
    abs(RegionZ_Cr) <= ThresholdZScoreCr;  %   compare against Cr z-score threshold

%%%%%% --- Assign logical vector indicating regions that pass Cr standard deviation threshold %%%%%%

%M regions x 1 column vector; type logical.
RegionSD_Cr_PassThresholdTF_LogIdx = RegionSD_Cr < ThresholdSDCr;


%%%%%% Assign logical vector indicating regions that passed all thresholds %%%%%%

%Assign logical vector indicating whether a region passed all thresholds
%M regions x 1 column vector; type logical.
RegionPassAllThresholdsTF_LogIdx = ...
    RegionNPixels_PassNThresholdTF_LogIdx & ...
    RegionRGB_PassThresholdsTF_LogIdx     & ...
    RegionYCbCrZ_PassThresholdsTF_LogIdx  & ...
    RegionSD_Cr_PassThresholdTF_LogIdx;

%Number of regions that passed the thresholds
%Scalar; type uint16.

%Initialize accumulator
NRegionsPass = uint16(0);

for i = 1 : NRegions

    if RegionPassAllThresholdsTF_LogIdx(i)

        NRegionsPass = NRegionsPass + 1;        
    end
end 
    

end %end function

