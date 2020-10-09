function SkinSegmentConfig = ...
             SkinSegment_ConfigSetupTailoredThresholds(DetectVerifyPercentilesYCbCrH, ...
                 DetectVerifyPercentilesS, SkinSegmentConfig, ROIGeneralConfig)
%SkinSegment_ConfigSetupTailoredThresholds   Set settings used to tailor thresholds used as
%                                            arguments to function SkinSegmentMask.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinSegment_ConfigSetup.
%
%
%    Description
%    -----------
%
%    Set settings used to tailor certain thresholds used as arguments to function SkinSegmentMask.
%    The thresholds that can be tailored include the pixel-color ranges of the YCbCr and HSV 
%    colorspaces.
%                                            
%    -- Collecting skin-color samples for tailoring thresholds --
%
%    Skin-color samples are collected by function ROIMeans_FirstRead_CollectSkinColorSamples, which
%    is called by function ROIMeans_FirstRead. For details on the collection of skin-color samples,
%    see function ROIMeans_FirstRead_CollectSkinColorSamples. 
%
%    A certain number of skin-color samples is required to begin tailoring thresholds from them; a
%    minimum is set to avoid the tailored thresholds from being too conservative. If there are 
%    fewer ROIs than this threshold, skin segmentation will still be run, but generic YCbCr 
%    thresholds will be used in place of tailored YCbCr thresholds even where tailored thresholds 
%    are specified. Also, the H and S thresholds will not be used. The skin-detection algorithm, 
%    which uses tailored thresholds, will not be run as the potentially higher accuracy of tailored 
%    thresholds is considered necessary.
%  
%    -- Periodically resetting the tailored thresholds --
%
%    Setting the thresholds for tailored skin-segmentation occurs once the minimum number of  
%    skin-color samples has been collected. The thresholds are reset periodically at specified 
%    intervals to update them with additional data from skin-color samples; the skin samples are 
%    collected continuously as the video elapses. Thresholds are reset at intervals because skin 
%    colors from a given face may vary slighty across the duration of the video. This variation can 
%    occur due to factors such as varying head positions, flushing of the skin, and other 
%    environmental conditions. Testing has indicated that if the thresholds were set only once at 
%    the beginning of the video, skin segmentation may be too conserative at later segments of the
%    video.    
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% Minimum number of skin-color samples to draw from for tailoring thresholds %%%%%%

%As of the current implementation, skin-color samples come from ROIs from the primary 
%face-detection algorithm. 

%If skipping thresholds is at least 4 frames
if ROIGeneralConfig.ROISkipFrameThreshold_adjusted >= 4
    
    SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold = 125;
  
%If skipping thresholds is less than 4 frames  
%In order to prevent the standard deviations of the color samples, which are used in the skin-
%classification algorithm, from becoming too narrow, increase the number of required samples if the
%skipping threshold is less than 4 frames. Skipping frames helps increase the diversity of the 
%color samples, increasing the standard deviation to the expected range; if skipping is lower than 
%4 frames, increase the number of samples collected to increase the diversity.
else
    
    SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold = ...
        SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold + ...   
        (4 - ROIGeneralConfig.ROISkipFrameThreshold_adjusted) * ...
        SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold;
end 

%Flag indicating whether the threshold is met
%To be assigned by function SkinSegment_SetThresholds.
SkinSegmentConfig.Args.SkinColorSamples_NThresholdPassedTF = false;

 
%%%%%% Flag indicating tailored skin-segmentation is ready %%%%%%

%Flag indicating when tailored skin-segmentation is ready. 
%Tailored skin-segmentation is ready once the tailored thresholds have been set, which is conducted
%by function SkinSegment_SetThresholds. The tailored thresholds can be set by function
%SkinSegment_SetThresholds once flag SkinSegmentConfig.Args.SkinColorSamples_NThresholdPassedTF   
%(see above) is true.

%Note: this flag will be reset if function ROIMeans_FirstRead is called recursively (see function
%SkinSegment_OversegmentationCheck_Reduce).

SkinSegmentConfig.TailoredData.OpsReadyTF = false;


%%%%%% Precentile range from which to accept pixels from skin-color samples %%%%%%

%Determine the range, specified as percentiles, of color values to use from collected color samples 
%to set thresholds:

%Y, Cb, Cr, and H channels percentile range
SkinSegmentConfig.TailoredData.RangePercentile_YCbCrH = [1.75, 98.25]; 

%S channel percentile range
%Testing has suggested that the S-channel range should be wider compared to the other channels.  
SkinSegmentConfig.TailoredData.RangePercentile_S = [.3, 99.7];

%%%%%% --- High number of samples %%%%%%

%Number of ROIs from primary face-detection algorithm at which to narrow thresholds for tailored
%skin segmentation:

%When there is a greater number of skin-color samples, narrow the thresholds.  
%When there is a greater number of skin-color samples, the standard deviations of color samples may  
%become more expansive, requiring more narrow thresholds to reduce false positives (marking 
%non-skin as skin).
SkinSegmentConfig.TailoredData.SkinColorSamples_HighNThreshold = 4000; 

%Flag indicating whether the threshold is met
%To be assigned by function SkinSegment_SetThresholds.
SkinSegmentConfig.TailoredData.SkinColorSamples_HighNThresholdPassedTF = false;

%Y, Cb, Cr, and H channels percentile range
SkinSegmentConfig.TailoredData.RangePercentileHighN_YCbCrH = [3, 97];

%S channel percentile range
SkinSegmentConfig.TailoredData.RangePercentileHighN_S = [.4, 99.6];

%%%%%% --- High severity of tailored thresholds %%%%%%

%For use by functions ConfirmSkinPresent and SkinDetect.

%High-severity thresholds are used for applications where the priority is to reduce false positives 
%(pixels incorrectly classified as skin) at the expense of a greater number false negatives (pixels 
%incorrectly classified as non-skin).

%DetectVerifyPercentilesYCbCrH and DetectVerifyPercentilesS are arguments to function
%FacePulseRate.

%Y, Cb, Cr, and H channels percentile range
SkinSegmentConfig.TailoredData.RangePercentileSev_YCbCrH = DetectVerifyPercentilesYCbCrH; 

%S channel percentile range
%Testing has suggested that the S-channel range should be wider compared to the other channels.  
SkinSegmentConfig.TailoredData.RangePercentileSev_S = DetectVerifyPercentilesS;


%%%%%% Settings for periodically resetting the tailored thresholds %%%%%%%

%Setting of the thresholds is conducted by function SkinSegment_SetThresholds. 
%SkinSegment_SetThresholds is called by function ROIMeans_FirstRead_SetThresholds, which is called 
%by function ROIMeans_FirstRead.  

%%%%%% --- Linear index of frame at which tailored thresholds were last set %%%%%%

%Within function ROIMeans_FirstRead, the tailored thresholds are reset periodically. This index
%indicates the frame index at which the thresholds were last set and is used to determine when to 
%reset the thresholds. The interval between the thresholds being set is specified by
%SkinSegmentConfig.TailoredData.ThresholdOpsInterval.

%Specify type int32 for protection against floating-point gaps. 
SkinSegmentConfig.TailoredData.RecentThresholdOpsFrameIdx = int32([]);

%%%%%% --- Interval at which tailored thresholds resetting will occur %%%%%%

%See above.

%Specify type int32 for protection against floating-point gaps.
SkinSegmentConfig.TailoredData.ThresholdOpsInterval = int32(1500);

%%%%%% --- Flag indicating that the tailored thresholds should be reset in the current frame %%%%%%

%Reset periodically during function ROIMeans_FirstRead. See above.
SkinSegmentConfig.TailoredData.ThresholdOpsRunCurrentFrameTF = false;


end %end function

