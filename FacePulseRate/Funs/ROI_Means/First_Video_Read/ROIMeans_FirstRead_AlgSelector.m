function [ROISuccessful, FacePrimaryAttemptedTF_ith, FacePrimaryTF_ith, SkinNotPresent_Pri_ith, ...
          ProfileEyesPresent_Pri_ith, FaceSecondary1AttemptedTF_ith, FaceSecondary1TF_ith, ...          
          SkinNotPresent_Sec1_ith, ProfileEyesPresent_Sec1_ith, FaceSecondary2AttemptedTF_ith, ...
          FaceSecondary2TF_ith, SkinNotPresent_Sec2_ith, ProfileEyesPresent_Sec2_ith, ...
          BBox_Scan_FaceAlg_ith, YSingle, CbSingle, CrSingle, RUint8, GUint8, BUint8, HSingle, ...
          SSingle, IsSkinMask_LocalRange, NRows_Matrix, NCols_Matrix, ...
          ROIDiagnostic_ROISkin_ith, SkinTF_ith, SkinAttemptedTF_ith, SkinNotPresent_Skin_ith, ...
          ProfileEyesIdx, ProportionSkin_AlgName, ProportionSkin, ...
          YSingle_OversegmentationCheck, OversegmentationCheckReady] = ...                                                 
             ROIMeans_FirstRead_AlgSelector(i, ROIGeneralConfig, FaceDetectConfig, ...
                 UseBoundingBoxFaceTF, BoundingBoxFace, VidFrame, VideoReadConfig, ...
                 SkinSegmentConfig, HasROI_TF, SkinDetectConfig, OutputConfig, BoundingBoxSkin, ...
                 ROIForBoundingBoxSkin_FR, ExpediteColorThresholdsTF, ProfileEyesIdx)                                                   
%ROIMeans_FirstRead_AlgSelector   Apply detection algorithms to a given frame in a specified order
%                                 to detect an ROI corresponding to a face.
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead. 
%
%
%    Description
%    -----------
%    
%    For a given frame, call detection algorithms to scan the area within the bounding box for an 
%    ROI corresponding to the face. Once a detection is made by any detection algorithm, no further 
%    algorithms are called. The skin-detection algorithm is only called if no face-detection
%    algorithm(s) make a detection.        
%
%    In addition to returning the ROI and detection information, also return color channels  
%    assigned during the operations for reuse in setting the thresholds for tailored   
%    skin-segmentation and for the skin-detection algorithm (see function 
%    ROIMeans_FirstRead_SetThresholds).                              
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Conduct face-detection algorithm(s) for ith frame %%%%%%

%Apply the face-detection algorithm(s) to the ith frame.

%Note: ROIMeans_FirstRead_AlgSelector_Face is a custom function located within folder
%'FacePulseRate'.
[ROISuccessful, FacePrimaryAttemptedTF_ith, FacePrimaryTF_ith, SkinNotPresent_Pri_ith, ...
 ProfileEyesPresent_Pri_ith, FaceSecondary1AttemptedTF_ith, FaceSecondary1TF_ith, ...
 SkinNotPresent_Sec1_ith, ProfileEyesPresent_Sec1_ith, FaceSecondary2AttemptedTF_ith, ...
 FaceSecondary2TF_ith, SkinNotPresent_Sec2_ith, ProfileEyesPresent_Sec2_ith, YSingle, CbSingle, ...
 CrSingle, RUint8, GUint8, BUint8, HSingle, SSingle, IsSkinMask_LocalRange, NRows_Matrix, ...
 NCols_Matrix, BBox_Scan_FaceAlg_ith, ProfileEyesIdx, ProportionSkin_AlgName, ProportionSkin, ...
 YSingle_OversegmentationCheck, OversegmentationCheckReady] = ...                        
    ROIMeans_FirstRead_AlgSelector_Face(i, VidFrame, UseBoundingBoxFaceTF, BoundingBoxFace, ...
        ExpediteColorThresholdsTF, ProfileEyesIdx, HasROI_TF, FaceDetectConfig, ...
        SkinSegmentConfig, SkinDetectConfig, VideoReadConfig);  


%%%%%% Conduct skin-detection algorithm %%%%%%

%Apply the skin-detection algorithm to the ith frame if certain criteria care satisified.                                    

%If skin-detection algorithm is enabled in function FacePulseRate
if SkinDetectConfig.ROISkinTF
    
    %Note: ROIMeans_FirstRead_AlgSelector_Skin is a custom function located within folder
    %'FacePulseRate'.
    [SkinAttemptedTF_ith, SkinTF_ith, ROISuccessful, SkinNotPresent_Skin_ith, ...
     ROIDiagnostic_ROISkin_ith] = ...
        ROIMeans_FirstRead_AlgSelector_Skin(i, VidFrame, ROISuccessful, BoundingBoxSkin, ...
            ROIForBoundingBoxSkin_FR, FacePrimaryTF_ith, FaceSecondary1TF_ith, ...
            FaceSecondary2TF_ith, HasROI_TF, SkinDetectConfig, VideoReadConfig, ...
            SkinSegmentConfig, ROIGeneralConfig, OutputConfig);    
        
else
    
    SkinAttemptedTF_ith       = false;   
    SkinTF_ith                = false;
    SkinNotPresent_Skin_ith   = false;
    ROIDiagnostic_ROISkin_ith = []; %note: this would otherwise be a struct  
end
 

end %end function
        

