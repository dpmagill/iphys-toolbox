function SkinDetectConfig = ...
             SkinDetect_ConfigSetupColorThresholds(SkinDetectConfig, ROIGeneralConfig)
%SkinDetect_ConfigSetupColorThresholds   Setup color thresholds for use in the skin-detection
%                                        algorithm.
%                      
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinDetect_ConfigSetup. 
%
%
%    Description
%    -----------
%
%    Setup color thresholds for use in the skin-detection algorithm.                                       
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Color thresholds %%%%%%

%RGB and YCbCr color thresholds
%The thresholds are specified by SkinClassifyRegionColorThresholds, which is an argument to 
%function FacePulseRate.
%A 1-by-3 row vector specifying the minimum RGB probability, the maximum Cb z-score, and the 
%maximum Cr z-score.
%Specify type single for faster evaluation where used.

SkinDetectConfig.Thresholds.ColorThreshold = single( [.36, 9, 9.5] );  
     
%When a large number of skin-color samples are available:
SkinDetectConfig.Thresholds.ColorThresholdHighN = single( [.36, 6.5, 7.25] );

%Cr color standard deviation threshold
%The threshold is specified by SkinClassifyRegionColorSDThreshold, which is an argument to function 
%FacePulseRate.
%Skin tends to have a low standard deviation, so this threshold aims to reduce regions that have a
%standard deviation higher than would be expected for skin. Hair was the primary target.
%The lips and nostrils are also affected.
%A 1-by-1 vector specifying the maximum standard deviation for Cr.
%Specify type single for faster evaluation where used.

SkinClassifyRegionColorSDThreshold = 9;

SkinDetectConfig.Thresholds.ColorSDThreshold = single(SkinClassifyRegionColorSDThreshold); 
           

%%%%%% YCbCr overall-means, YCbCr frame-mean standard deviations, and RGB theta parameters %%%%%%  

%YCbCr overall means and frame-mean standard deviations:

%YCbCr overall means and frame-mean standard deviations used by the specified thresholds are 
%collected from the ROIs of the primary face-detection algorithm. Data to calculate the overall 
%means and frame-mean standard deviations are only collected from the primary face-detection   
%algorithm because the primary algorithm is assumed to be the most reliable face-detection  
%algorithm. Also, if the primary algorithm is an algorithm that detects frontal-orientation (which 
%is the case for the default setting), rather than profile-orientation, it may contain fewer 
%non-face pixels than otherwise. The data include YCbCr frame-means from the 
%primary-algorithm-detected ROI of each frame. These means are collected by function 
%ROIMeans_FirstRead_CollectSkinColorSamples, which is called by function ROIMeans_FirstRead for 
%each frame with a primary detection. 
 
%YCbCr overall means and frame-mean standard deviations are calculated from the frame-means by   
%function SkinDetect_SetThresholds, which is called by function ROIMeans_FirstRead.  

%Overall YCbCr means 
%Will be assigned by function SkinDetect_SetThresholds.
SkinDetectConfig.Thresholds.YCbCrMeanOfMeans = []; 

%Standard deviations of YCbCr frame-means 
%Will be assigned by function SkinDetect_SetThresholds.
SkinDetectConfig.Thresholds.YCbCrStdDevOfMeans = []; 

%RGB probability theta paramaters:

%Theta parameters are calculated by function SkinDetect_RGBProbSkinTrain using RGB ROI-means as 
%well as external RGB means for robustness (for details, see the function file for 
%SkinDetect_RGBProbSkinTrain). 
%As with YCbCr frame-means, RGB ROI-means are only collected from frames with a primary 
%face-detection algorithm detection and are collected by function 
%ROIMeans_FirstRead_CollectSkinColorSamples. SkinDetect_RGBProbSkinTrain is called by function 
%SkinDetect_SetThresholds, which is called by function ROIMeans_FirstRead.

%RGB probability theta paramaters
%Will be assigned by function SkinDetect_SetThresholds.
SkinDetectConfig.Thresholds.RGBProbTheta = [];


%%%%%% Flag that thresholds have set %%%%%%

%The thresholds are set in function SkinDetect_SetThresholds, which is called once the minimum 
%number of color samples is available. This function is called by function ROIMeans_FirstRead. The 
%minimum number of skin-color samples is specified by 
%SkinDetectConfig.Thresholds.SkinColorSamples_NThreshold (see below). For details on the collection
%of skin-color samples, see function ROIMeans_FirstRead_CollectSkinColorSamples.

%Note: this flag will be reset if function ROIMeans_FirstRead is called recursively (see function
%SkinSegment_OversegmentationCheck_Reduce).

SkinDetectConfig.Thresholds.SetTF = false;


%%%%%% Minimum number of skin-color samples to activate the skin-detection algorithm %%%%%%

%Skin-color samples are collected by function ROIMeans_FirstRead_CollectSkinColorSamples, which is
%called by function ROIMeans_FirstRead. For details on the collection of skin-color samples, see
%function ROIMeans_FirstRead_CollectSkinColorSamples. 

%A certain number of skin-color samples is required to begin setting color thresholds. A minimum is
%set to avoid the thresholds from being too conservative. If there are fewer skin-color samples 
%than this threshold, the skin-detection algorithm will not be run.

%In order to prevent the standard deviations of the color samples, which are used in the skin-
%classification algorithm, from becoming too narrow, increase the number of required samples if the
%skipping threshold is less than 4 frames. Skipping frames helps increase the diversity of the
%color samples, increasing the standard deviation to the expected range; if skipping is lower than
%4 frames, increase the number of samples collected to increase the diversity.

%Specify minimum number of skin-color samples required to use region colors:

%If skipping thresholds is at least 4 frames
if ROIGeneralConfig.ROISkipFrameThreshold_adjusted >= 4
    
    SkinDetectConfig.Thresholds.SkinColorSamples_NThreshold = 250;
  
%If skipping thresholds is less than 4 frames    
else
    
    SkinDetectConfig.Thresholds.SkinColorSamples_NThreshold = ...
        250 + ...   
        (4 - ROIGeneralConfig.ROISkipFrameThreshold_adjusted) * 250;
end
     
%Whether the number of skin-color samples exceeds the specified threshold
%To be determined by function SkinDetect_SetThresholds.
SkinDetectConfig.Thresholds.SkinColorSamples_NThresholdPassedTF = false;  

%High number of samples:

%When there is a greater number of skin-color samples collected, narrow the thresholds. 
%When there is a greater number of skin-color samples, the standard deviations of color samples may  
%become more expansive, requiring more narrow thresholds to reduce false positives (classifying  
%non-skin as skin).
SkinDetectConfig.Thresholds.SkinColorSamples_HighNThreshold = 750; 

%Flag indicating whether the threshold is met
%To be assigned by function SkinDetect_SetThresholds.
SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdPassedTF = false;

%Flag indicating at which frame index the number of skin-color samples was equal to or greater
%than SkinDetectConfig.Thresholds.SkinColorSamples_HighNThreshold.
%This value is used when writing the output video (see function 
%WriteFaceVideo_LegendSetupTextSkinDetect). This value is reassigned by function 
%SkinDetect_SetThresholds.
SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdIdx = int32(0);


%%%%%% Settings for periodically resetting the thresholds %%%%%%%

%Setting the thresholds for the skin-detection algorithm occurs once the minimum number of   
%skin-color samples has been collected. The thresholds are reset periodically at specified  
%intervals to update them with additional data from skin-color samples; the skin samples are 
%collected continuously as the video elapses. Thresholds are reset at intervals because skin colors  
%from a given face may vary slighty across the duration of the video. This variation can occur due  
%to factors such as varying head positions, flushing of the skin, and other environmental  
%conditions. Testing has indicated that if the thresholds were set only once at the beginning of   
%the video, the thresholds may be too conserative at later segments of the video.

%Setting of the thresholds is conducted by function SkinDetect_SetThresholds. 
%SkinDetect_SetThresholds is called by function ROIMeans_FirstRead_SetThresholds, which is called 
%by function ROIMeans_FirstRead.  

%%%%%% --- Linear index of frame at which thresholds were last set %%%%%%

%Within function ROIMeans_FirstRead, the thresholds are reset periodically. This index indicates
%the frame index at which the thresholds were last set and is used to determine when to reset the 
%thresholds. The interval between the thresholds being set is specified by
%SkinDetectConfig.Thresholds.ThresholdOpsInterval.

%Specify type int32 for protection against floating-point gaps. 
SkinDetectConfig.Thresholds.RecentThresholdOpsFrameIdx = int32([]);

%%%%%% --- Interval at which thresholds resetting will occur %%%%%%

%See above.

%Specify type int32 for protection against floating-point gaps.
SkinDetectConfig.Thresholds.ThresholdOpsInterval = int32(1500);

%%%%%% --- Flag indicating that the thresholds should be reset in the current frame %%%%%%

%Reset periodically during function ROIMeans_FirstRead. See above.
SkinDetectConfig.Thresholds.ThresholdOpsRunCurrentFrameTF = false;


end %end function

