function [SkinSegmentConfig, SkinDetectConfig, FirstCallTF_SetSkinSegmentThresholds, ...
          FirstCallTF_SetSkinDetectThresholds] = ...
             ROIMeans_FirstRead_SetThresholds(i, DataForTailoredSkinSegmentation, HasROI_TF, ...
                 SkinSegmentConfig, SkinDetectConfig, DataForSkinDetection, ...
                 FirstCallTF_SetSkinSegmentThresholds, FirstCallTF_SetSkinDetectThresholds)          
%ROIMeans_FirstRead_SetThresholds   Set the thresholds for tailored skin segmentation and for the
%                                   skin-detection algorithm.
%                                       
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function ROIMeans_FirstRead.
%
%
%    Description
%    -----------
%
%    Set the tailored skin-segmentation thresholds and the skin-detection algorithm thresholds from
%    skin-color samples.
%
%    Setting the thresholds occurs once the minimum number of primary face-detection algorithm ROI 
%    color samples has been collected and repeats at specified intervals.           
%
%    Setting the thresholds is repeated at intervals because the colors if skin within the target 
%    face may vary slighty across the video. Such variation may occur due to varying head  
%    positions, flushing of the skin, and environmental factors. Testing has indicated that if the  
%    thresholds were set only once at the beginning of the video, the thresholds may be too 
%    conserative for use at other portions of the video. When setting the thresholds is repeated,  
%    all color samples previously collected are included in the operation. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% Determine the number of skin-color samples %%%%%%

%In order to set thresholds for skin segmentation and skin detection, the number of skin-color
%samples must be above specified thresholds. The number of samples is also used to determine which
%thresholds to apply.

%Note: as of the current implementation, the number of skin-color samples equals the number of 
%primary face-detection algorithm detections as skin-color samples are collected only from ROIs
%corresponding to primary face-detection algorithm detections. For details, see function
%SkinSegment_ConfigSetupTailoredThresholds or function SkinDetect_ConfigSetup.

NSamples = nnz(HasROI_TF.FacePrimary);


%%%%%% Set tailored skin-segmentation thresholds %%%%%%

%If tailored skin-segmentation thresholds have not yet been set 
if ~ SkinSegmentConfig.TailoredData.OpsReadyTF

    %If the number skin-color samples collected is above the specified threshold. 
    if NSamples >= SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold

        %Set thresholds for the first time at this frame
        SkinSegmentConfig.TailoredData.ThresholdOpsRunCurrentFrameTF = true;
        
        %Set index for use in periodically resetting threholds
        SkinSegmentConfig.TailoredData.RecentThresholdOpsFrameIdx = i;

        %Flag that tailored skin-segmentation thresholds set at least once
        SkinSegmentConfig.TailoredData.OpsReadyTF = true;
    end
    
%Tailored skin-segmentation thresholds have been set at least once   
else 

    %The specified number of frames has elapsed since the thresholds were last set
    if i > SkinSegmentConfig.TailoredData.RecentThresholdOpsFrameIdx + ...
           SkinSegmentConfig.TailoredData.ThresholdOpsInterval

        %Reset the thresholds at this frame
        SkinSegmentConfig.TailoredData.ThresholdOpsRunCurrentFrameTF = true;
        
        %Reset index
        SkinSegmentConfig.TailoredData.RecentThresholdOpsFrameIdx = i;
        
    else
        
        %Do not reset the thresholds at this frame
        SkinSegmentConfig.TailoredData.ThresholdOpsRunCurrentFrameTF = false;        
    end
end

%Set tailored skin-segmentation thresholds by processing skin-color samples
if SkinSegmentConfig.TailoredData.ThresholdOpsRunCurrentFrameTF

    %Note: 'SkinSegment_SetThresholds' is a custom function located within folder 'FacePulseRate'.
    SkinSegmentConfig = ...
        SkinSegment_SetThresholds(SkinSegmentConfig, DataForTailoredSkinSegmentation, ...
             NSamples, FirstCallTF_SetSkinSegmentThresholds);

    %Flag for message from function SkinSegment_SetThresholds displays, which changes after the
    %first call.
    FirstCallTF_SetSkinSegmentThresholds = false;
end


%%%%%% Set skin-detection algorithm thresholds %%%%%%

%Setting the thresholds occurs once the minimum number skin-color samples has been reached.  

%If the skin-detection algorithm is enabled
if SkinDetectConfig.ROISkinTF             

    %If the skin-detection algorithm thresholds have not been set at least once
    if ~ SkinDetectConfig.Thresholds.SetTF 

        %If the number of primary skin-color samples collected is above the specified threshold. 
        if NSamples >= SkinDetectConfig.Thresholds.SkinColorSamples_NThreshold 

            %Set thresholds for the first time at this frame
            SkinDetectConfig.Thresholds.ThresholdOpsRunCurrentFrameTF = true; 

            %Set index for use in periodically resetting threholds
            SkinDetectConfig.Thresholds.RecentThresholdOpsFrameIdx = i;

            %Flag that skin-detection algorithm thresholds set at least once
            SkinDetectConfig.Thresholds.SetTF = true;                 
        end

    %Skin-detection algorithm thresholds have been set at least once   
    else 

        %The specified number of frames has elapsed since the thresholds were last set
        if i > SkinDetectConfig.Thresholds.RecentThresholdOpsFrameIdx + ...
               SkinDetectConfig.Thresholds.ThresholdOpsInterval 

            %Reset the thresholds at this frame
            SkinDetectConfig.Thresholds.ThresholdOpsRunCurrentFrameTF = true;

            %Reset index
            SkinDetectConfig.Thresholds.RecentThresholdOpsFrameIdx = i;

        else

            %Do not reset the thresholds at this frame
            SkinDetectConfig.Thresholds.ThresholdOpsRunCurrentFrameTF = false;        
        end    
    end

    %Set tailored skin-segmentation thresholds by processing skin-color samples
    if SkinDetectConfig.Thresholds.ThresholdOpsRunCurrentFrameTF

       %Note: 'SkinDetect_SetThresholds' is a custom function located within folder 
       %'FacePulseRate'.
       SkinDetectConfig = ...
           SkinDetect_SetThresholds(i, SkinDetectConfig, DataForSkinDetection, NSamples, ...
               FirstCallTF_SetSkinDetectThresholds);

        %Flag for message from function SkinSegment_SetThresholds displays, which changes after the
        %first call.
        FirstCallTF_SetSkinDetectThresholds = false;
    end
end


end %end function

