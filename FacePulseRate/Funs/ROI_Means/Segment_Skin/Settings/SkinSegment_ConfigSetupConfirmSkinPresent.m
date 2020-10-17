function SkinSegmentConfig = SkinSegment_ConfigSetupConfirmSkinPresent(SkinSegmentConfig)
%SkinSegment_ConfigSetupConfirmSkinPresent   Set settings for function ConfirmSkinSegment.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinSegment_ConfigSetup.  
%
%
%    Description
%    -----------
%
%    Function ConfirmSkinPresent determines whether there is a sufficient proportion of pixels 
%    classified as skin within an ROI to consider the ROI valid. Function ConfirmSkinPresent makes
%    a verification for any ROI returned by a detection algorithm (see functions 
%    FaceDetect_ROIValidate and SkinDetect_ROIValidate) and also verifies the final ROI before  
%    means are taken for pulse rate operations (see function ROIMeans_TakeMeans_ROIValidate).
%      
%    In the current function, the minimum proportion of pixels classified as skin within an ROI to 
%    consider the ROI valid is set. If an ROI contains a proportion above this threshold, it will 
%    be considered valid and the ROI will continue to be used. If the proportion is below the 
%    threshold, an ROI will be considered invalid and the ROI will not be used further. The minimum 
%    proportion threshold is set according to the detection algorithm that returned the ROI or the 
%    stage of ROI processing.
%
%    Note that in addition to the skin-segmentation thresholds set here, some skin-detection 
%    algorithm thresholds are also used by function ConfirmSkinPresent to verify the presence of  
%    skin (see function ConfirmSkinPresent_SkinDetectReject for the use of skin-detection 
%    thresholds in function ConfirmSkinPresent and see function SkinDetect_ConfigSetup for the 
%    assignment of the thresholds).
%
%    -- Proportion Thresholds --
%
%    Regarding proportion thresholds for face-detection algorithms, the proportions should be 
%    smaller for a given face-detection algorithm if less skin area is expected to be present, on
%    average, in the ROI it returns. If the ROI of a detection algorithm may have less skin area 
%    if ... 
%    (1) The ROI returned by the detection algorithm tends to be relatively large
%    (2) The ROI returned by the detection algorithm targets a profile orientation of the face. A 
%        profile orientation would be expected to have less skin present than a frontal orientation. 
% 
%    Note that the skin-segmentation settings in effect for some of the checks are more severe than
%    the skin-segmentation settings in effect when writing frames to the output video. 
%    Consequently, if using the output video to calibrate the proportion thresholds, note that 
%    proportions in some checks will be lower than what appears in the video. The checks in which
%    skin-segmentation settings are more severe than those found in the output video include ...
%    - Primary face-detection algorithm
%    - Secondary #1 face-detection algorithm
%    - Secondary #2 face-detection algorithm 
%    - Skin-detection algorithm
%
%    The remaining check, ROIMeans_TakeMeans, is conducted using the same level of 
%    skin-segmentation severity as that used for the skin segmentation displayed in the output 
%    video -- in fact, the skin segmentation from ROIMeans_TakeMeans is what is displayed in the 
%    output video.   
%
%    The threshold used when the ROI is in the final stage of processing (processed by function
%    ROIMeans_TakeMeans) is set relatively low because, at that point, the ROI would have undergone
%    several adjustements (see function ROIMSIR) that may have made the ROI value more accurate.  
%
%    Ultimately, the values of the thresholds should be determined based upon empirical testing 
%    that strikes an acceptable balance between the false negative rate (the rate of incorrectly  
%    considering an ROI invalid) and the false positive rate (the rate of incorrectly considering 
%    an ROI valid). An increase or descrease in the false negative rate can be inferred by  
%    considering the proportions of detections returned out of attempts. Function 
%    ConfirmSkinPresent will prevent detections from being used when the ROI is considered invalid, 
%    reducing the proportions of detections returned out of attempts. When a video is known not to 
%    contain erroneous detections (through visual inspection of the video output), different 
%    minimum thresholds can be trialled and the resulting detections-out-of-attempts proportions 
%    compared to determine an acceptable level of false negatives. The detections-out-of-attempts  
%    proportions are superimposed on the output videos in the legend. An increase or decrease in 
%    the false positive rate can be inferred by trialling different thresholds and assessing, 
%    through visual inspection of the output video, the number of erroneous ROI detections (ROI
%    detections are superimposed on the output video as black boxes).
%
%    In addition the detections-out-of-attempts proportions, the characters '[R]' are added to the  
%    ROI annotation of a frame of the output video when an ROI was rejected by function 
%    SkinDetect_PartitionRegions. 
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%Minimim proportion thresholds:

%ROIs returned by the primary face-detection algorithm
SkinSegmentConfig.ConfirmSkin.ProportionThresholdPrimary = single(.08);

%ROIs returned by the secondary #1 face-detection algorithm 
SkinSegmentConfig.ConfirmSkin.ProportionThresholdSecondary1 = single(.04);

%ROIs returned by the secondary #2 face-detection algorithm 
SkinSegmentConfig.ConfirmSkin.ProportionThresholdSecondary2 = single(.05);

%ROIs returned by the skin-detection algorithm 
SkinSegmentConfig.ConfirmSkin.ProportionThresholdSkin = single(.06);

%ROI processing by function ROIMeans_TakeMeans
SkinSegmentConfig.ConfirmSkin.ProportionThresholdMeans = single(.05);


end %end function

