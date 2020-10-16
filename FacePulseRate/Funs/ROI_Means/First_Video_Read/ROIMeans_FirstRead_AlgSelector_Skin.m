function [SkinAttemptedTF_ith, SkinTF_ith, ROISuccessful, SkinNotPresent_Skin_ith, ...
          ROIDiagnostic_ROISkin_ith] = ...
             ROIMeans_FirstRead_AlgSelector_Skin(i, VidFrame, ROISuccessful, BoundingBoxSkin, ...
                 ROIForBoundingBoxSkin_FR, FacePrimaryTF_ith, FaceSecondary1TF_ith, ...
                 FaceSecondary2TF_ith, HasROI_TF, SkinDetectConfig, VideoReadConfig, ...
                 SkinSegmentConfig, ROIGeneralConfig, OutputConfig)
%ROIMeans_FirstRead_AlgSelector_Skin   Apply the skin-detection algorithm to the ith frame if 
%                                      certain criteria care satisified.
%                                  
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead_AlgSelector. 
%
%
%    Description
%    -----------
%
%    Apply the skin-detection algorithm to the ith frame if certain criteria care satisified.
%                                      
%    The skin-detection algorithm is run if the following two criteria are true.
%
%    (1) SkinDetectConfig.SkinDetectionFirstReadTF is true. This value is true when two conditions  
%        are true:
%        
%        (A) A sufficient number of frames exists to form a bounding box, which is required for the  
%        use of the skin-detection algorithm. A bounding box is required to decrease false   
%        positives and processing time. The determination on whether a sufficient number of frames   
%        have elapsed to use a bounding box is made in function 
%        ROIMeans_FirstRead_SetBoundingBoxes.
%
%        (B) The color data required for the skin-detection algorithm have been processed. The  
%        color data are processed in functions SkinSegment_SetThresholds and  
%        SkinDetect_SetThresholds, which are called in function ROIMeans_FirstRead. In order for 
%        SkinSegment_SetThresholds and SkinDetect_SetThresholds to process data, a sufficient  
%        number of skin-color samples must have been made from which to extract color data. For 
%        details on the collection of skin-color samples, see function 
%        ROIMeans_FirstRead_CollectSkinColorSamples 
%
%    (2) There are no detections from face-detection algorithms within the span specified by  
%        ROISkinSkipFrameThreshold. Additionally, there also may not be any frames skipped by the
%        face-detection algorithms within the span; frame-skipping, implemented to increase 
%        efficiency, is used when a determination is made that the detection rate has been fairly  
%        stable. When either of these is the case, it is assumed that face detections are stable 
%        enough that the skin-detection algorithm is not needed for the ith frame. Limiting the use   
%        of the skin-detection algorithm reduces false positives, which are more likely from the  
%        skin-detection algorithm compared to the face-detection algorithms, and reduces processing 
%        time.           
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Determine whether to run the skin-detection algorithm %%%%%%

%%%%%% --- Determine whether criterion 2 is true: no face-detection detections or skips within span %%%%%%

%Number of frames back without face-detection algorithm detections required to use the 
%skin-detection algorithm. Reducing the use of the skin-detection algorithm decreases false
%positives (as the skin-detection algorithm tends to be less accurate than the face-detection
%algorithms), increases stability (as the skin-detection algorithm may orient to a different
%location than a face-detection algorithm), and decreases computational time (as the skin-
%detection algorithm tends to take more time than the Viola-Jones algorithms).

%Note: it may be advantageous to set the skip threshold for skin-detection (which is set by   
%argument ROISkinSkipFrameThreshold to function FacePulseRate) higher than the threshold used for
%enlarging the bounding box for the face-detection algorithms (which is set by argument
%ROIFace_BoundingBoxGrowthThreshold to function FacePulseRate) to allow the face-detection
%algorithms to search a wider area before using the skin-detection algorithm. Doing so would favor
%ROIs from the face-detection algorithm over ROIs from the skin-detection algorithm; the face-
%detection algorithm might be preferred because it tends to be more reliable and faster than the
%skin-detection algorithm.

NFramesBackToCheck = SkinDetectConfig.ROISkinSkipFrameThreshold_adjusted; 

%Check for face-detection detections or skips within span:

LinIdx = max(i - NFramesBackToCheck, 1) : max(i - 1, 1);

FaceOrSkipDetectedTF = ...
                                               ... Face-detection algorithm detections for ith 
                                               ... frame:
    FacePrimaryTF_ith                       || ... - Primary face-detection algorithm  
    FaceSecondary1TF_ith                    || ... - Secondary #1 face-detection algorithm
    FaceSecondary2TF_ith                    || ... - Secondary #2 face-detection algorithm
                                               ... Face-detection algorithm detections for a
                                               ... specified number of previous frames (note: 
                                               ... HasROI_TF has not yet been updated to reflect 
                                               ... the ith frame): 
    any( HasROI_TF.FacePrimary(   LinIdx) ) || ... - Primary face-detection algorithm  
    any( HasROI_TF.FaceSecondary1(LinIdx) ) || ... - Secondary #1 face-detection algorithm 
    any( HasROI_TF.FaceSecondary2(LinIdx) ) || ... - Secondary #2 face-detection algorithm
    any( HasROI_TF.Skipped(       LinIdx) );   %   Face-detection algorithm(s) skipped for a
                                               %   specified number of previous frames.
   
%%%%%% --- Determine whether criteria 1 and 2 are true %%%%%%

SkinDetectionIthFrameTF = ...
    SkinDetectConfig.SkinDetectionReadyTF && ... Criteria 1: skin-detection color thresholds set
   ~ FaceOrSkipDetectedTF;                   %   Criteria 2: no face-detection algorithm detections 
                                             %   or skips 


%%%%%% Conduct skin-detection algorithm %%%%%%

%If frame meets criteria 1 and 2
if SkinDetectionIthFrameTF 
                     
    %Arguments:
    
    %Mark that detection will be attempted by skin-detection algorithm for this frame
    SkinAttemptedTF_ith = true;  
     
    %Flag to function SkinDetect that function is called from first-read operations
    FirstReadTF = true;
    
    %Arguments not used during first-read operations
    %Note: although it might be desiable to use varargin for such arguments, varargin is not used
    %to maintain code-generation compatibility in function SkinDetect.
    ROI_SR_ith                     = zeros(0, 4, 'int16');
    FramesToProcessLinIdx_SR       = int32(0);
    Notifications_Interval_SR      = int32(0); 
    Notifications_LoopStartTime_SR = uint64(0);
    Notifications_LoopCounter_SR   = int32(0); 
        
    %Call skin-detection algorithm:
    
    %Compiled functions enabled
    if SkinDetectConfig.UseCompiledFunctionsTF 
        
        %Note: SkinDetect_mex is a custom compiled function located within folder 'FacePulseRate'.
        %For source code, see file SkinDetect.m.
        [ROI_Selected_ith, SkinTF_ith, SkinNotPresent_ith, ROIDiagnostic_ROISkin_ith, ~] = ...
            SkinDetect_mex(i, VidFrame, VideoReadConfig.VidObjWidth, ...
                VideoReadConfig.VidObjHeight, SkinSegmentConfig, ROIGeneralConfig,  ...
                SkinDetectConfig, OutputConfig.WriteVideoShowROISkinDiagnosisTF, ...
                BoundingBoxSkin, FirstReadTF, ROIForBoundingBoxSkin_FR, ROI_SR_ith, ...
                FramesToProcessLinIdx_SR, Notifications_Interval_SR, ...
                Notifications_LoopStartTime_SR, Notifications_LoopCounter_SR); 
            
    %Compiled functions not enabled    
    else
        
        %Note: SkinDetect is a custom function located within folder 'FacePulseRate'.
        [ROI_Selected_ith, SkinTF_ith, SkinNotPresent_ith, ROIDiagnostic_ROISkin_ith, ~] = ...         
            SkinDetect(i, VidFrame, VideoReadConfig.VidObjWidth, VideoReadConfig.VidObjHeight, ...
                SkinSegmentConfig, ROIGeneralConfig, SkinDetectConfig, ...
                OutputConfig.WriteVideoShowROISkinDiagnosisTF, BoundingBoxSkin, FirstReadTF, ...
                ROIForBoundingBoxSkin_FR, ROI_SR_ith, FramesToProcessLinIdx_SR, ...
                Notifications_Interval_SR, Notifications_LoopStartTime_SR, ...
                Notifications_LoopCounter_SR);        
    end        
    
    %The detection can be unsuccessful for the following reasons:
    % - The portion of the frame submitted to the skin-detection algorithm was completely 
    %   segmented by the skin-segmentation algorithm.
    % - All regions within the portion of the frame submitted to the skin-detection algorithm were
    %   rejected.
    % - Rejected by function ConfirmSkinPresent.

    %Indicate whether the detection was not successful because the ROI did not pass the threshold 
    %applied by function ConfirmSkinPresent.
    %Note: If true, then SkinTF_ith will be false. However, SkinTF_ith can be false without 
    %HasROITF_SkinNotPresent_ith being true.
    SkinNotPresent_Skin_ith = SkinNotPresent_ith;          
    
    %If skin-detection algorithm detection found, note detection was successful and record ROI 
    %coordinates
    if SkinTF_ith
        
       %1 x 4 row vector; type int16
       ROISuccessful = ROI_Selected_ith;      
    end
    
%At least one criterion is not met    
else
    
    SkinAttemptedTF_ith       = false;   
    SkinTF_ith                = false;
    SkinNotPresent_Skin_ith   = false;
    ROIDiagnostic_ROISkin_ith = []; %note: this would otherwise be a struct
end


end %end function

