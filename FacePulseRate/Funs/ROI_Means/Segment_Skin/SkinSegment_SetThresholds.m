function SkinSegmentConfig = ...
             SkinSegment_SetThresholds(SkinSegmentConfig, DataForTailoredSkinSegmentation, ...
                 NSamples, FirstCallTF_SetSkinSegmentThresholds)
%SkinSegment_SetThresholds   Set color thresholds for tailored skin segmentation.
%  
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead_SetThresholds.
%
%
%    Description
%    -----------
%
%    This function sets thresholds used for tailored skin segmentation (see function 
%    SkinSegmentMask) from skin-color samples collected from the input video (see function
%    ROIMeans_FirstRead_CollectSkinColorSamples). Thresholds are set for various color channels, 
%    namely, the Y, Cb, and Cr channels of the YCbCr colorspace and the H and S channels of the HSV 
%    colorspace. The thresholds consist of the minimum and/or maximum color values accepted to 
%    classify a given pixel as skin. Some channels use both minimum and maximum thresholds, 
%    whereas other channels use only the minimum or maximum. Whether one or both is used was based
%    on a considered of how effective the minimum or maximum appeared to be at skin classification
%    (see function SkinSegmentMask for a discussion). The thresholds are assigned to struct 
%    SkinSegmentConfig.Args, which is used by function SkinSegmentMask during tailored 
%    skin-segmentation operations.
%     
%    The current function is called at intervals by function ROIMeans_FirstRead_SetThresholds once  
%    a minimum number ROIs with primary face-detection algorithm detections has been reached. At
%    each interval, the current function resets the previously set thresholds in order to better
%    reflect the current environmental conditions of the video.
%
%    Function SkinSegmentMask conducts tailored skin segmentation when argument  
%    TailoredThresholdsTF to function SkinSegmentMask is true. In this case, the thresholds 
%    assigned by the current function are used for skin-segmentation operations. If 
%    TailoredThresholdsTF is false, SkinSegmentMask conducts generic skin segmentation and does not
%    use the thresholds assigned by the current function. Rather, SkinSegmentMask uses generic
%    thresholds specified by argument SkinSegmentYCbCrThresholdsGeneric to function FacePulseRate. 
%
%    The tailored thresholds assigned by the current function are set from the skin-color samples 
%    according to percentiles, which are specified in struct SkinSegmentConfig and assigned by
%    function SkinSegment_ConfigSetup.
%
%    Before the switch is made from using generic thresholds to using tailored thresholds in 
%    skin-segmentation operations (see the description in function SkinSegmentMask), function 
%    ROIMeans_FirstRead_CollectSkinColorSamples segments out pixels below or above the generic 
%    thresholds in all skin-color samples. As a result, the tailored thresholds, which are drawn 
%    from skin-color samples, cannot be above or below the generic thresholds. However, if the  
%    generic thresholds are modified after FacePulseRate begins, some skin-color samples could 
%    contain pixels outside of the generic thresholds, resulting in tailored thresholds being 
%    outside of the generic thresholds. Currently, the only case where the generic thresholds would 
%    be modified after FacePulseRate begins is if functions SkinSegment_OversegmentationCheck and 
%    SkinSegment_OversegmentationCheck_Reduce modify the generic thresholds (for details, see the
%    descriptions in these functions).     
%
%    -- S channel of HSV colorspace compared to other channels --
%
%    The S channel of the HSV colorspace uses percentiles different from the other channels as the
%    S channel has been observed to be more effective at balancing false negatives (pixels 
%    incorrectly classified as non-skin) and false positives (pixels incorrectly classified as 
%    skin) at wider percentiles compared to the other channels.
%
%    -- High-severity thresholds --
% 
%    Two types of thresholds are set. The first type is used for high-severity color skin 
%    segmentation and the second type is used for low-severity color skin segmentation.
%
%    The high-severity threshold type uses percentiles that are more narrow than those used for the 
%    low-severity thresholds, resulting in more severe skin segmentation. The high-severity type is 
%    used for applications where the priority is to reduce false positives at the expense of a
%    greater number false negatives.
%    
%    The percentiles for the high-severity thresholds are specified by 
%    SkinSegmentConfig.TailoredData.RangePercentileSev_S and 
%    SkinSegmentConfig.TailoredData.RangePercentileSev_YCbCrH. The former stores the percentiles 
%    for the S channel of the HSV colorspace and the latter stores the percentiles for the other
%    channels.
%
%    The high-severity thresholds produced by the current function are assigned to fields
%    SkinSegmentConfig.Args.HSThresholdsTailored_Sev and
%    SkinSegmentConfig.Args.YCbCrThresholdsTailored_Sev. The former stores the thresholds for the 
%    H and S channels of the HSV colorspace and the latter stores the thresholds for the other 
%    channels.
%
%    -- Low-severity thresholds -- 
% 
%    The low-severity threshold type is used for applications where a balance is desired between  
%    false positives and false negatives.
%
%    The low-severity threshold type is divided into two categories, one where a small number of 
%    skin-color samples is available and one where a large number of skin-color samples is 
%    available. Different percentiles are used for these two categories. When a large number of 
%    skin-color samples has been collected, percentiles are used that are more narrow than those
%    used when a small number of percentiles has been collected. For a large number of samples, 
%    more narrow percentiles are used because, through testing, it has been observed that 
%    thresholds become wider as the number of samples increases. This widening could potentially 
%    lead to an unacceptable rate of falese positives. The more narrow percentiles are used to 
%    address this. The number of skin-color samples considered as "large" is specified by 
%    SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold.
%
%    Note that although low-severity thresholds are set according to the number of samples, the
%    high-severity thresholds use the same percentiles regardless of the number of samples. 
%      
%    The percentiles for the low-samples low-severity thresholds are specified by 
%    SkinSegmentConfig.TailoredData.RangePercentile_S and 
%    SkinSegmentConfig.TailoredData.RangePercentile_YCbCrH. 
%
%    The percentiles for the high-samples low-severity thresholds are specified by 
%    SkinSegmentConfig.TailoredData.RangePercentileHighN_S and 
%    SkinSegmentConfig.TailoredData.RangePercentileHighN_YCbCrH.
%
%    The thresholds produced by either of the above percentiles are assigned to fields 
%    SkinSegmentConfig.Args.HSThresholdsTailored and
%    SkinSegmentConfig.Args.YCbCrThresholdsTailored. 
%
%    Inputs (subset):
% 
%        DataForTailoredSkinSegmentation = 
%            A matrix with rows the length of the the number of samples and 11 columns. The columns                                     
%            store the following information for each sample:                                                            
%            [min(Y), max(Y), min(Cb), max(Cb), min(Cr), max(Cr), min(CbCrRatio), max(CbCrRatio), 
%             max(H), min(S), max(S)].                           
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Argument Validation %%%%%%

%If fewer skin-color samples collected than specified, exit function. This is imposed to ensure 
%robust use of ROI colors. For details on the collection of skin-color samples, see function
%ROIMeans_FirstRead_CollectSkinColorSamples. Skin segmentation will still be conducted in function 
%FacePulseRate but generic, rather than tailored, thresholds will be used.

%Determine whether the specified number of skin-color samples has been collected
%For use in other functions.
SkinSegmentConfig.Args.SkinColorSamples_NThresholdPassedTF = ...
    NSamples >= SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold;   

if ~ SkinSegmentConfig.Args.SkinColorSamples_NThresholdPassedTF 
    
    %Exit function
    return
end


%%%%%% Display notification message %%%%%%  

%If first call to current function within function FacePulseRate
if FirstCallTF_SetSkinSegmentThresholds

    message = '\n       Setting thresholds for tailored skin segmentation.';

else
    
    message = '\n       Recalculating thresholds for tailored skin segmentation.';   
end
    
%Display message on command window
fprintf(message);

%Display message immediately
drawnow(); 


%%%%%% Extract the YCbCr and HS skin-color samples %%%%%% 

%Remove rows with NaN
%Rows will have NaN if function ROIMeans_FirstRead_CollectSkinColorSamples did not collect any
%skin-color samples. There are also rows with NaN that were preallocated but not filled. 
%Note: Only one column is checked for NaN because if one column of a row is NaN, the other columns 
%of the row will always be NaN.
DataForTailoredSkinSegmentation = ...
    DataForTailoredSkinSegmentation( ...
        ~ isnan( DataForTailoredSkinSegmentation(:, 1) ), ...
        : ...
    ); 

%Separate the skin-color samples by color channel
%Note: the skin-color samples consists of minimums and maximums of the respective channels.
Y_min_vector         = DataForTailoredSkinSegmentation(:, 1);
Y_max_vector         = DataForTailoredSkinSegmentation(:, 2);
Cb_min_vector        = DataForTailoredSkinSegmentation(:, 3);
Cb_max_vector        = DataForTailoredSkinSegmentation(:, 4);
Cr_min_vector        = DataForTailoredSkinSegmentation(:, 5);
Cr_max_vector        = DataForTailoredSkinSegmentation(:, 6);
CbCrRatio_min_vector = DataForTailoredSkinSegmentation(:, 7);
CbCrRatio_max_vector = DataForTailoredSkinSegmentation(:, 8);
H_max_vector         = DataForTailoredSkinSegmentation(:, 9);
S_min_vector         = DataForTailoredSkinSegmentation(:, 10);
S_max_vector         = DataForTailoredSkinSegmentation(:, 11);


%%%%%% High-severity color thresholds %%%%%%
            
%%%%%% --- Select thresholds based upon specified percentiles %%%%%%

%Y, Cb, Cr, and H channel percentile ranges:
    
%Minimum percentile
rangeMin_YCbCrH = SkinSegmentConfig.TailoredData.RangePercentileSev_YCbCrH(1);

%Maximum percentile
rangeMax_YCbCrH = SkinSegmentConfig.TailoredData.RangePercentileSev_YCbCrH(2);

%S channel percentile range:

%Minimum percentile
rangeMin_S = SkinSegmentConfig.TailoredData.RangePercentileSev_S(1);

%Maximum percentile
rangeMax_S = SkinSegmentConfig.TailoredData.RangePercentileSev_S(2);        

%Set thresholds according to the specified percentiles
SkinSegment_YMin_tailoredThresLower         = prctile(Y_min_vector,         rangeMin_YCbCrH);
SkinSegment_YMax_tailoredThresUpper         = prctile(Y_max_vector,         rangeMax_YCbCrH);
SkinSegment_CbMin_tailoredThresLower        = prctile(Cb_min_vector,        rangeMin_YCbCrH);
SkinSegment_CbMax_tailoredThresUpper        = prctile(Cb_max_vector,        rangeMax_YCbCrH);
SkinSegment_CrMin_tailoredThresLower        = prctile(Cr_min_vector,        rangeMin_YCbCrH);
SkinSegment_CrMax_tailoredThresUpper        = prctile(Cr_max_vector,        rangeMax_YCbCrH);
SkinSegment_CbCrRatioMin_tailoredThresLower = prctile(CbCrRatio_min_vector, rangeMin_YCbCrH);
SkinSegment_CbCrRatioMax_tailoredThresUpper = prctile(CbCrRatio_max_vector, rangeMax_YCbCrH); 
SkinSegment_HMax_tailoredThresUpper         = prctile(H_max_vector,         rangeMax_YCbCrH);
SkinSegment_SMin_tailoredThresLower         = prctile(S_min_vector,         rangeMin_S);
SkinSegment_SMax_tailoredThresUpper         = prctile(S_max_vector,         rangeMax_S);

%%%%%% --- Set thresholds to fixed value if specified %%%%%%

%See the description in function SkinSegment_OversegmentationCheck.

if SkinSegmentConfig.OverSegmentedCheck.BelowDarknessThresholdTF

    %Set fixed thresholds values.
    %Local function.
    [SkinSegment_YMin_tailoredThresLower, SkinSegment_CbMin_tailoredThresLower, ...
     SkinSegment_CbMax_tailoredThresUpper, SkinSegment_CrMin_tailoredThresLower, ...
     SkinSegment_CrMax_tailoredThresUpper, SkinSegment_CbCrRatioMin_tailoredThresLower, ...
     SkinSegment_CbCrRatioMax_tailoredThresUpper, SkinSegment_HMax_tailoredThresUpper, ...
     SkinSegment_SMin_tailoredThresLower] = ...
        SetFixedThresholds(SkinSegment_YMin_tailoredThresLower, ...
            SkinSegment_CbMin_tailoredThresLower, SkinSegment_CbMax_tailoredThresUpper, ...
            SkinSegment_CrMin_tailoredThresLower, SkinSegment_CrMax_tailoredThresUpper, ...
            SkinSegment_CbCrRatioMin_tailoredThresLower, ...
            SkinSegment_CbCrRatioMax_tailoredThresUpper, ...
            SkinSegment_HMax_tailoredThresUpper, SkinSegment_SMin_tailoredThresLower, ...
            SkinSegmentConfig);                   
end
    
%%%%%% --- Assign thresholds to struct %%%%%%

%High-severity YCbCr colorspace thresholds
SkinSegmentConfig.Args.YCbCrThresholdsTailored_Sev = ...
    [SkinSegment_YMin_tailoredThresLower,          SkinSegment_YMax_tailoredThresUpper, ...
     SkinSegment_CbMin_tailoredThresLower,         SkinSegment_CbMax_tailoredThresUpper, ...
     SkinSegment_CrMin_tailoredThresLower,         SkinSegment_CrMax_tailoredThresUpper, ...
     SkinSegment_CbCrRatioMin_tailoredThresLower,  SkinSegment_CbCrRatioMax_tailoredThresUpper];
    
%High-severity HSV colorspace thresholds
SkinSegmentConfig.Args.HSThresholdsTailored_Sev = ...
    [SkinSegment_HMax_tailoredThresUpper, SkinSegment_SMin_tailoredThresLower, ...
     SkinSegment_SMax_tailoredThresUpper];


%%%%%% Low-severity color thresholds %%%%%%

%Determine whether there is a relatively large number of skin-color samples
SkinSegmentConfig.TailoredData.SkinColorSamples_HighNThresholdPassedTF = ...
    NSamples >= SkinSegmentConfig.TailoredData.SkinColorSamples_HighNThreshold;
    
%%%%%% --- Not large number of skin-color samples %%%%%%

if ~ SkinSegmentConfig.TailoredData.SkinColorSamples_HighNThresholdPassedTF
    
    %Y, Cb, Cr, and H channel percentile ranges:
    
    %Minimum percentile
    rangeMin_YCbCrH = SkinSegmentConfig.TailoredData.RangePercentile_YCbCrH(1);
    
    %Maximum percentile
    rangeMax_YCbCrH = SkinSegmentConfig.TailoredData.RangePercentile_YCbCrH(2);

    %S channel percentile range:

    %Minimum percentile
    rangeMin_S = SkinSegmentConfig.TailoredData.RangePercentile_S(1);
    
    %Maximum percentile
    rangeMax_S = SkinSegmentConfig.TailoredData.RangePercentile_S(2);
    
%%%%%% --- Large number of skin-color samples %%%%%%
else   
    
    %Y, Cb, Cr, and H channel percentile ranges:
    
    %Minimum percentile
    rangeMin_YCbCrH = SkinSegmentConfig.TailoredData.RangePercentileHighN_YCbCrH(1);
    
    %Maximum percentile
    rangeMax_YCbCrH = SkinSegmentConfig.TailoredData.RangePercentileHighN_YCbCrH(2);
    
    %S channel percentile range:
    
    %Minimum percentile
    rangeMin_S = SkinSegmentConfig.TailoredData.RangePercentileHighN_S(1);
    
    %Maximum percentile
    rangeMax_S = SkinSegmentConfig.TailoredData.RangePercentileHighN_S(2);        
end

%Set thresholds according to the specified percentiles
SkinSegment_YMin_tailoredThresLower         = prctile(Y_min_vector,         rangeMin_YCbCrH);
SkinSegment_YMax_tailoredThresUpper         = prctile(Y_max_vector,         rangeMax_YCbCrH);
SkinSegment_CbMin_tailoredThresLower        = prctile(Cb_min_vector,        rangeMin_YCbCrH);
SkinSegment_CbMax_tailoredThresUpper        = prctile(Cb_max_vector,        rangeMax_YCbCrH);
SkinSegment_CrMin_tailoredThresLower        = prctile(Cr_min_vector,        rangeMin_YCbCrH);
SkinSegment_CrMax_tailoredThresUpper        = prctile(Cr_max_vector,        rangeMax_YCbCrH);
SkinSegment_CbCrRatioMin_tailoredThresLower = prctile(CbCrRatio_min_vector, rangeMin_YCbCrH);
SkinSegment_CbCrRatioMax_tailoredThresUpper = prctile(CbCrRatio_max_vector, rangeMax_YCbCrH); 
SkinSegment_HMax_tailoredThresUpper         = prctile(H_max_vector,         rangeMax_YCbCrH);
SkinSegment_SMin_tailoredThresLower         = prctile(S_min_vector,         rangeMin_S);
SkinSegment_SMax_tailoredThresUpper         = prctile(S_max_vector,         rangeMax_S);

%%%%%% --- Set thresholds to fixed value if specified %%%%%%

%See the description in function SkinSegment_OversegmentationCheck.

if SkinSegmentConfig.OverSegmentedCheck.BelowDarknessThresholdTF

    %Set fixed thresholds values.
    %Local function.
    [SkinSegment_YMin_tailoredThresLower, SkinSegment_CbMin_tailoredThresLower, ...
     SkinSegment_CbMax_tailoredThresUpper, SkinSegment_CrMin_tailoredThresLower, ...
     SkinSegment_CrMax_tailoredThresUpper, SkinSegment_CbCrRatioMin_tailoredThresLower, ...
     SkinSegment_CbCrRatioMax_tailoredThresUpper, SkinSegment_HMax_tailoredThresUpper, ...
     SkinSegment_SMin_tailoredThresLower] = ...
        SetFixedThresholds(SkinSegment_YMin_tailoredThresLower, ...
            SkinSegment_CbMin_tailoredThresLower, SkinSegment_CbMax_tailoredThresUpper, ...
            SkinSegment_CrMin_tailoredThresLower, SkinSegment_CrMax_tailoredThresUpper, ...
            SkinSegment_CbCrRatioMin_tailoredThresLower, ...
            SkinSegment_CbCrRatioMax_tailoredThresUpper, ...
            SkinSegment_HMax_tailoredThresUpper, SkinSegment_SMin_tailoredThresLower, ...
            SkinSegmentConfig);                   
end

%%%%%% --- Assign thresholds to struct %%%%%%

%Low-severity YCbCr colorspace thresholds
SkinSegmentConfig.Args.YCbCrThresholdsTailored = ...
    [SkinSegment_YMin_tailoredThresLower,          SkinSegment_YMax_tailoredThresUpper, ...
     SkinSegment_CbMin_tailoredThresLower,         SkinSegment_CbMax_tailoredThresUpper, ...
     SkinSegment_CrMin_tailoredThresLower,         SkinSegment_CrMax_tailoredThresUpper, ...
     SkinSegment_CbCrRatioMin_tailoredThresLower,  SkinSegment_CbCrRatioMax_tailoredThresUpper];
    
%Low-severity HSV colorspace thresholds
SkinSegmentConfig.Args.HSThresholdsTailored = ...
    [SkinSegment_HMax_tailoredThresUpper, SkinSegment_SMin_tailoredThresLower, ...
     SkinSegment_SMax_tailoredThresUpper];
       
        
end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function [SkinSegment_YMin_tailoredThresLower, SkinSegment_CbMin_tailoredThresLower, ...
          SkinSegment_CbMax_tailoredThresUpper, SkinSegment_CrMin_tailoredThresLower, ...
          SkinSegment_CrMax_tailoredThresUpper, SkinSegment_CbCrRatioMin_tailoredThresLower, ...
          SkinSegment_CbCrRatioMax_tailoredThresUpper, SkinSegment_HMax_tailoredThresUpper, ...
          SkinSegment_SMin_tailoredThresLower] = ...
              SetFixedThresholds(SkinSegment_YMin_tailoredThresLower, ...
                  SkinSegment_CbMin_tailoredThresLower, SkinSegment_CbMax_tailoredThresUpper, ...
                  SkinSegment_CrMin_tailoredThresLower, SkinSegment_CrMax_tailoredThresUpper, ...
                  SkinSegment_CbCrRatioMin_tailoredThresLower, ...
                  SkinSegment_CbCrRatioMax_tailoredThresUpper, ...
                  SkinSegment_HMax_tailoredThresUpper, SkinSegment_SMin_tailoredThresLower, ...
                  SkinSegmentConfig)          
%SetFixedThresholds   Set fixed thresholds values.
%
%    Description:
%
%    Set fixed thresholds values. These values will be set if 
%    SkinSegmentConfig.OverSegmentedCheck.BelowDarknessThresholdTF is true. Set the values 
%    according to SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo. If an element of
%    SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo is NaN, there is no specified fixed 
%    value for the corresponding threshold, so the threshold will be returned unmodified.
%    
%    For a description of why these thresholds are set as fixed, see function 
%    SkinSegment_OversegmentationCheck.  


%Y-minimum
if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(1) )

    SkinSegment_YMin_tailoredThresLower = ...
        SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(1);
end

%Cb-minimum
if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(2) )

    SkinSegment_CbMin_tailoredThresLower = ...
        SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(2);
end    

%Cb-maximum    
if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(3) )

    SkinSegment_CbMax_tailoredThresUpper = ...
        SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(3);
end    

%Cr-minimum     
if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(4) )

    SkinSegment_CrMin_tailoredThresLower = ...
        SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(4);
end    

%Cr-maximum     
if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(5) )

    SkinSegment_CrMax_tailoredThresUpper = ...
        SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(5);
end

%Cb-to-Cr minimum    
if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(6) )

    SkinSegment_CbCrRatioMin_tailoredThresLower = ...
        SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(6);
end

%Cb-to-Cr maximum    
if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(7) )

    SkinSegment_CbCrRatioMax_tailoredThresUpper = ...
        SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(7);
end

%H maximum    
if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(8) )

    SkinSegment_HMax_tailoredThresUpper = ...
        SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(8);
end

%S minimum   
if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(9) )

    SkinSegment_SMin_tailoredThresLower = ...
        SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(9);
end 
    

end %end local function

