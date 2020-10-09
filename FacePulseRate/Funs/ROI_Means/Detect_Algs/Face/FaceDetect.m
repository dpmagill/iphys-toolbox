function [ROISuccessfulTF, ROISuccessful, HasROITF_SkinNotPresent_ith, ...
          HasROITF_ProfileEyesPresent_ith, YSingle, CbSingle, CrSingle, RUint8, GUint8, BUint8, ...
          HSingle, SSingle, IsSkinMask_LocalRange, NRows_Matrix, NCols_Matrix, ProfileEyesIdx, ...
          ProportionSkin] = ...                            
             FaceDetect(i, faceDetector, VidFrameGray, UseBoundingBoxFaceTF, BoundingBoxFace, ...
                 FaceAlgorithm, VidFrame, ProfileEyesIdx, ProfileDetectorTF, ...
                 FaceDetectConfig, SkinSegmentConfig, SkinDetectConfig)                  
%FaceDetect   Face-detection algorithm. Identify an ROI for a frame using a specified Viola-Jones 
%             face detector and ROI verifications. 
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead_AlgSelector_Face.
%
%
%    Description
%    -----------
%
%    Identify an ROI from the bounding box of a frame using a specified Viola-Jones face detector. 
%    Then, determine whether the ROI should be considered valid according to certain criteria.
%    During the validation operations, also adjust the X- and Y-coordinates of the ROI to align 
%    with the dimensions of the full frame rather than with the dimensions of the bounding box.
%    
%    In addition to returning the ROI and detection information, also return color channels 
%    assigned during the operations for reuse in setting the thresholds for tailored 
%    skin-segmentation and for the skin-detection algorithm (see function 
%    ROIMeans_FirstRead_SetThresholds).
% 
%    -- Summary of reasons why a face-detection attempt will be considered unsuccesful --
%
%    - The detector (vision.CascadeObjectDetector) did not return an ROI
%
%        Possible reasons:
%
%        - A face, if present, was excluded in whole or in part by the bounding box. For bounding
%          box settings, see function FaceDetect_ConfigSetup. For a discussion, see function
%          ROIMeans_FirstRead_SetBoundingBoxes. 
%        - The specified minimum ROI size, which is an argument to vision.CascadeObjectDetector,
%          is too large, resulting in an accurate ROI not being detected. By default, the minimum 
%          ROI size is calculated automatically (see function ROIGeneralConfig_Setup); the minimum 
%          ROI size can also be set manually by arguments ROIMinWidthRatio and ROIMinHeightRatio. 
%          The following flags also influence the minimum ROI size:                          
%            - ROIMinWidthRatio
%            - ROIMinHeightRatio
%            - ROIMinWidthRatioIncreaseSec1 
%            - ROIMinHeightRatioIncreaseSec1
%            - ROIMinWidthRatioIncreaseSec2
%            - ROIMinHeightRatioIncreaseSec2
%         - The merge threshold, which is an argument to vision.CascadeObjectDetector, may be too
%           large. The merge threshold is assigned by function FaceDetect_ConfigSetup. 
%
%    - Validation criteria not met (see function FaceDetect_ROIValidate):
%
%        - Too many detections made (more than one face detections per frame)
%        - Rejected because of a low proportion of pixels classified as skin
%        - An ROI of a profile also contains a pair of eyes (i.e., the profile-eyes test)
%                  
%    -- Third-party copyright notices --
%
%    The following Viola-Jones detection algorithms are used when the default algorithms are used. 
%    Third-party copyrights are property of their respective owners.
%
%    The following Viola-Jones face-detection files were accessed from OpenCV (Open Source Computer 
%    Vision Library) copyright (c) 2020, OpenCV team. The files, which include copies of their
%    respective licences, are located in 
%    ...\FacePulseRate\Helper_Funs\ROI_Means\Detect_Algs\Face\Open_CV_Viola-Jones.
%     
%    - Primary face-detection algorithm Viola-Jones detector:
%
%      lbpcascade_frontalface_improved.xml. Copyright (c) 2017, Puttemans Steven, Can Ergun and   
%      Toon Goedeme, all rights reserved. 
%
%      See discussion in Puttemans, S., Can, E., & Goedemé, T. (2017). Improving open source face 
%      detection by combining an adapted cascade classification pipeline and active learning.     
%      Proceedings of VISAPP 2017, 5, 396-404.      
%
%    - Secondary #1 face-detection algorithm Viola-Jones detector:
%
%      haarcascade_profileface.xml. Copyright (c) 2000, Intel Corporation, all rights reserved.   
%      Contributed by David Bradley from Princeton University.      
%
%    - Secondary #2 face-detection algorithm Viola-Jones detector:
%
%      cuda_haarcascade_frontalface_alt_tree.xml. Copyright (c) 2000, Intel Corporation, all rights  
%      reserved. Contributed by Rainer Lienhart. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Determine whether attempting detection is permitted by profile-eyes test %%%%%%

%Attempting a detection will not be permitted from algorithms that return profiles for a specified 
%number of frames from the most recent index where a pair of eyes was found. For details, see
%function FaceDetect_ROIValidate.

if FaceDetectConfig.ProfileEyesTestTF && ... If the absent-eyes test is enabled
   ProfileDetectorTF                     %   If the current face detector returns profiles 

    %If a pair of eyes was detected within a specified number of frames
    if i < ProfileEyesIdx +                   ... Most recent index where a pair of eyes was found
           FaceDetectConfig.ProfileEyesBuffer ... Number of frames after which a detection attempt 
                                              ... is permitted.

        %Indicate that the ROI did not pass the profile-eyes check
        %Note: this value is displayed on the output video.
        HasROITF_ProfileEyesPresent_ith = true;                                        
                                          
        %Indicate that detection attempt was not successful       
        ROISuccessfulTF = false;  

        %Assign ROI coordinates     
        ROISuccessful = int16([]); 

        %Assign empty ROI values
        YSingle                     = [];
        CbSingle                    = [];
        CrSingle                    = [];  
        RUint8                      = []; 
        GUint8                      = []; 
        BUint8                      = [];
        HSingle                     = [];
        SSingle                     = [];
        IsSkinMask_LocalRange       = [];
        NRows_Matrix                = int32([]); 
        NCols_Matrix                = int32([]);
        HasROITF_SkinNotPresent_ith = false;
        ProportionSkin              = int32(-1); %-1 indicates that no proportion is available.       

        %Exit function
        return
    end    
end
        

%%%%%% Scan bounded area of frame with Viola-Jones face detector %%%%%%              

%Object faceDetector is either the primary, secondary #1, or secondary #2 Viola-Jones face 
%detector, as assigned in function ROIMeans_FirstRead_AlgSelector.

%An empty return variable indicates no detection was made.
%A variable with more than one rows indicates more than one detection was made. As only one face is
%expected to be present in the frame, more than one detection probably indicates one or more
%erroneous detections.

%The Viola-Jones algorithm uses a grayscale colorspace of the frame. A grayscale colorspace 
%variable, VidFrameGray, was assigned previously (by function ROIMeans_FirstRead_AlgSelector). The
%grayscale variable covers either the entire frame or a bounded portion of the frame.
    
%Conduct Viola-Jones face detection and return ROI(s) corresponding to detections
%If at least one detection returned: M detections x 4 matrix; type double.
%If no detections returned: 0 x 0 element; type double.
ROITentative = faceDetector(VidFrameGray);                                                                              


%%%%%% Check validity of face-detection ROI %%%%%%

%Validate the ROI returned by a Viola-Jones face detector. 

%Also adjust the X- and Y-coordinates of the ROI to align with the dimensions of the full frame
%rather than with the dimensions of the bounding box.

%In addition to returning the ROI and detection information, also return color channels assigned 
%during the operations for reuse in setting the thresholds for tailored skin-segmentation and for 
%the skin-detection algorithm (see function ROIMeans_FirstRead_SetThresholds). 

%Note: FaceDetect_ROIValidate is a custom function located within folder 'FacePulseRate'.
[ROISuccessful, ROISuccessfulTF, HasROITF_SkinNotPresent_ith, HasROITF_ProfileEyesPresent_ith, ...
 ProfileEyesIdx, YSingle, CbSingle, CrSingle, RUint8, GUint8, BUint8, HSingle, SSingle, ...
 IsSkinMask_LocalRange, NRows_Matrix, NCols_Matrix, ProportionSkin] = ...
    FaceDetect_ROIValidate(i, ROITentative, FaceAlgorithm, ProfileDetectorTF, ProfileEyesIdx, ...
        VidFrame, UseBoundingBoxFaceTF, BoundingBoxFace, FaceDetectConfig, SkinSegmentConfig, ...
        SkinDetectConfig);


end %end function
 
