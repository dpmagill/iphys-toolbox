function [ROISuccessful, ROISuccessfulTF, HasROITF_SkinNotPresent_ith, ...
          HasROITF_ProfileEyesPresent_ith, ProfileEyesIdx, YSingle, CbSingle, CrSingle, RUint8, ...
          GUint8, BUint8, HSingle, SSingle, IsSkinMask_LocalRange, NRows_Matrix, ...
          NCols_Matrix, ProportionSkin] = ...          
              FaceDetect_ROIValidate(i, ROITentative, FaceAlgorithm, ProfileDetectorTF, ...
                  ProfileEyesIdx, VidFrame, UseBoundingBoxFaceTF, BoundingBoxFace, ...
                  FaceDetectConfig, SkinSegmentConfig, SkinDetectConfig)
%FaceDetect_ROIValidate    Validate the ROI returned by a Viola-Jones face detector.
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function FaceDetect.
%
%
%    Description
%    -----------
%
%    Validate the ROI returned by a Viola-Jones face detector according to ...
%    
%    (1) The number of detections returned by the Viola-Jones face detector
%    (2) The proportion of pixels classified as skin within the detection ROI
%    (3) The presence of a pair of eyes for Viola-Jones face detectors that return profiles    
%
%    Note: additional checks are included in the detector (vision.CascadeObjectDetector) used in
%    function FaceDetect that returns the ROI. These options include a minimum merge threshold 
%    (option MergeThreshold) and a minimum ROI size (option MinSize). The minimum ROI size both
%    increases efficiency and helps avoid small detections that are likely inaccurate. These 
%    options are assigned to the detector by function FaceDetect_ConfigSetup.
%
%    Also adjust the X- and Y-coordinates of the ROI to align with the dimensions of the full frame
%    rather than with the dimensions of the bounding box.
%
%    In addition to returning the ROI and detection information, also return color channels 
%    assigned during the operations for reuse in setting the thresholds for tailored 
%    skin-segmentation and for the skin-detection algorithm (see function 
%    ROIMeans_FirstRead_SetThresholds).
% 
%    Note: face-detection settings in struct FaceDetectConfig are assigned by function 
%    FaceDetect_ConfigSetup. 
%
%    -- Validity Conditions --
%
%    1. Number of detections
%
%    Regarding the the number of detections returned by the Viola-Jones detector, if the number is 
%    other than one, the result is not considered to be valid. If the number of detections is zero,
%    this indicates that the Viola-Jones detector did not make a detection. If the number of 
%    detections is greater than one, this is considered an invalid result as it is expected that 
%    there will be only one face present in the video frame. 
%
%    2. Proportion of pixels classified as skin
%
%    Regarding the criterion of the proportion of pixels classified as skin, the proportion of 
%    pixels classified as skin by the skin-segmentation algorithm within the ROI is checked to 
%    determine whether it is above a specified threshold (see functions ConfirmSkinPresent and
%    SkinSegment_ConfigSetupConfirmSkinPresent). If the proportion is above the specified 
%    threshold, the ROI is considered valid. 
%
%    The number of pixels classified as skin within an ROI is controlled by many settings. First,
%    there are skin-segmentation settings that affect the skin-segmentation algorithm (see 
%    functions SkinSegmentMask and SkinSegment_ConfigSetup). Second, there are the settings 
%    specific to the proportion-of-pixels test (see function 
%    SkinSegment_ConfigSetupConfirmSkinPresent). Note that the skin-detection algorithm may be used
%    by the proportion-of-pixels test (see function ConfirmSkinPresent_SkinDetectReject), so 
%    settings for the skin-detection algorithm (see function SkinDetect_ConfigSetup) may also 
%    influence the number of pixels. Depending on the severity of the settings, there may be fewer 
%    pixels classified as skin within the ROI; this will, in turn, affect the proportion of pixels
%    classified as skin. 
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
%    3. Presence of a pair of eyes for profile orientation
%   
%    An profile-eyes test is conducted for detectors that return profiles (ProfileDetectorTF == 
%    true). This test determines whether a pair of eyes is present alongside the profile. Because a 
%    pair of eyes would be likely in a frontal orientation of the face but less likely in profile 
%    orientation of the face, the presence of both a pair of eyes and a profile may suggest a 
%    detection error. Therefore, if a pair of eyes exists alongside a profile, the ROI is 
%    considered a detection error. This test is enabled by flag FaceDetectConfig.ProfileEyesTestTF.
%    Settings for the profile-eyes test are set by function FaceDetect_ConfigSetup.     
%                  
%    -- Third-party copyright notices --
%
%    The following Viola-Jones detection algorithm is used when the default algorithms are used. 
%    Third-party copyrights are property of their respective owners. 
%
%    - Large pair-of-eyes Viola-Jones detector used by the profile-eyes test: 
%
%      haarcascade_mcs_eyepair_big.xml. Copyright (c) 2006-2020, Modesto Castrillon-Santana   
%      (SIANI), Universidad de Las Palmas de Gran Canaria, Spain. The file, which includes a copy 
%      of the licence, is located in     
%      ...\FacePulseRate\Helper_Funs\ROI_Means\Detect_Algs\Face\Open_CV_Viola-Jones.      
%
%      See discussion in Castrillón, M., Déniz, O., Hernández, D., & Lorenzo, J. (2011). A 
%      comparison of face and facial feature detectors based on the Viola–Jones general object 
%      detection framework. Machine Vision and Applications, 22(3), 481-494.
%
%      The file was accessed from OpenCV (Open Source Computer Vision Library) copyright (c) 2020, 
%      OpenCV team. 
%    
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Number-of-ROIs check %%%%%%

%Determine the number of ROI detections
%The number of detections corresponds to the number of rows.
%Scalar; type double.
NDetections = size(ROITentative, 1);  

%Check whether one and only one detection was made
if NDetections == 1        

    %Indicate that the ROI passed the number-of-ROIs check
    Passed_NROI_TF = true;
    
    %Convert from type double to type int16 as this it the type used for ROIs in function 
    %FacePulseRate.
    %1 x 4 row vector; type int16.
    ROITentative_int16 = int16(ROITentative);
        
    %%%%%% --- Adjust ROI values to coordinate plane of full frame %%%%%%

    %If a bounding box was used, this operation converts the ROI values from the coordinate plane 
    %of the bounding box to the coordinate plane of the full frame. This is conducted so that the
    %frame can be cropped to the ROI. Also, if the ROI passes all validity checks, its coordinates
    %should be aligned with the frame before insertion to matrix ROI.
    
    %If bounding box used
    if UseBoundingBoxFaceTF     
        
        %1 x 4 row vector; type int16.
        ROITentative_int16(1) = ROITentative_int16(1) + (BoundingBoxFace(1) - 1); %X-coordinate
        ROITentative_int16(2) = ROITentative_int16(2) + (BoundingBoxFace(2) - 1); %Y-coordinate   
    end
    
else
    
    %Indicate that the ROI did not pass the number-of-ROIs check
    Passed_NROI_TF = false;   
end


%%%%%% Proportion-of-skin check %%%%%%

%If passed the number-of-ROIs check
if Passed_NROI_TF
    
    %The ROI is considered valid if the proportion of pixels classified as skin exceeds a specified
    %threshold. The proportion is calculated by producing a skin-segmentation mask that corresponds 
    %to the location of the ROI and then inspecting the elements of the mask. Specifically, the  
    %number of elements classified as true is divided by the total number of elements of the mask.
    %This calculation is conducted by function ConfirmSkinPresent. This function returns a true / 
    %false determination on whether the proportion exceeded the specified threshold. 

    %Arguments to function ConfirmSkinPresent:
    
    %Note: If this function is to be converted to code-generation code, for efficiency, the 
    %cropping and separation operations below should follow the template in function 
    %SkinDetect_PartitionRegions. 
    
    %Crop portion of frame to inspect according to the detection ROI
    %M x N x 3 array; type uint8.
    ImageToInspect = ...
        VidFrame( ...
            ROITentative_int16(2) : ROITentative_int16(2) + ROITentative_int16(4) - 1, ... rows
            ROITentative_int16(1) : ROITentative_int16(1) + ROITentative_int16(3) - 1, ... columns
            :                                                                          ... pages
        );
    
    %Separate the cropped frame into its color channels
    %M x N matrices; type uint8.
    RUint8 = ImageToInspect(:, :, 1); 
    GUint8 = ImageToInspect(:, :, 2);
    BUint8 = ImageToInspect(:, :, 3);

    %Dimensions of the cropped frame
    %Scalars; type int32.
    NRows_Matrix = int32( ROITentative_int16(4) ); %height (number of rows)
    NCols_Matrix = int32( ROITentative_int16(3) ); %widtht (number of columns)   
 
    %FaceAlgorithm = This setting specifies which threshold is used from  
    %SkinSegmentConfig.ConfirmSkin. SkinSegmentConfig.ConfirmSkin is assigned by function 
    %SkinSegment_ConfigSetup.
    
    %Flag whether to use tailored thresholds during segmentation
    %Tailored thresholds, rather than generic thresholds, are specified as they are more
    %conservative than generic thresholds.
    %Tailored thresholds include the tailored-YCbCr thresholds and the tailored-HS tresholds.
    %If the number of skin-color samples required for tailored thresholds 
    %(SkinSegmentConfig.TailoredData.PriAlgROIs_NThreshold) has not yet been collected, function 
    %SkinSegmentMask, which is called by function ConfirmSkinPresent, will use generic rather than
    %tailored thresholds.
    TailoredThresholdsTF = true;

    % - Return the Y channel of the YCbCr colorspace, assigned during the skin-segmentation  
    %operations, for reuse in setting the skin-segmentation Y threshold (see function 
    %SkinSegment_SetThresholds) and the skin-detection Y threshold (see function
    %SkinDetect_SetThresholds).
    ReturnYTF = true;

    % - Return the Cb and Cr channels of the YCbCr colorspace, assigned during the 
    %skin-segmentation operations, for reuse in setting the skin-segmentation Cr and Cb thresholds   
    %(see function SkinSegment_SetThresholds) and the skin-detection Cr and Cb thresholds (see 
    %function SkinDetect_SetThresholds).
    ReturnCbCrTF = true;

    % - Return the H and S channels of the HSV colorspace, assigned during the skin-segmentation 
    %operations, for reuse in setting the skin-segmentation H and S thresholds (see function  
    %SkinSegment_SetThresholds). 
    ReturnHSTF = true; 
    
    % - Apply thresholds from the skin-detection algorithm to refine the inspection
    SkinDetectionThresholdsTF = true;    
        
    %Note: 'ConfirmSkinPresent' is a custom function located within folder 'FacePulseRate'. 
    [Passed_SkinColor_TF,     ... True/false determination on whether the proportion in the ROI is  
                              ... above the threshold.
     ProportionSkin,          ... The proportion of skin on which the determination was made; type
                              ... single.
     ~, ... 
     YSingle,                 ... ROI in Y colorspace. M x N matrix; type single  
     CbSingle,                ... ROI in Cb colorspace. M x N matrix; type single 
     CrSingle,                ... ROI in Cr colorspace. M x N matrix; type single 
     HSingle,                 ... ROI in H colorspace. M x N matrix; type single 
     SSingle,                 ... ROI in S colorspace. M x N matrix; type single 
     IsSkinMask_LocalRange] = ... ROI skin-segmentation mask based upon local range threshold. M x      
                              ... N matrix; type logical.                          
        ConfirmSkinPresent( ...
            SkinSegmentConfig, ... Skin-segmentation configurations
            FaceAlgorithm,     ... The proportion threshold to apply, which varies by context 
            RUint8,            ... ROI in R colorspace. M x N matrix; type uint8
            GUint8,            ... ROI in G colorspace. M x N matrix; type uint8
            BUint8,            ... ROI in B colorspace. M x N matrix; type uint8
            NRows_Matrix,      ... Scalar; type int32    
            NCols_Matrix,      ... Scalar; type int32 
            TailoredThresholdsTF, ...
            ReturnYTF, ...
            ReturnCbCrTF, ...
            ReturnHSTF, ...
            SkinDetectionThresholdsTF, ...
            SkinDetectConfig   ... Skin-detection configurations
        );

    %If the ROI passed the proportion-of-skin check  
    if Passed_SkinColor_TF                                      

        %Indicate that the ROI passed the proportion-of-skin check
        HasROITF_SkinNotPresent_ith = false;        
        
    else        
        
        %Indicate that the ROI did not pass the proportion-of-skin check
        %Note: this value is displayed on the output video.
        HasROITF_SkinNotPresent_ith = true;  
    end
    
else
    
    %Indicate that the ROI did not pass the proportion-of-skin check
    %Note: the proportion-of-skin check was not conducted in this condition.    
    Passed_SkinColor_TF = false;
    
    %As the proportion-of-skin check was not conducted, do not indicate that the ROI failed the
    %proportion-of-skin check. 
    HasROITF_SkinNotPresent_ith = false;    

    %Indicate that no proportion is available
    %-1 indicates that no proportion is available.
    ProportionSkin = single(-1);
end


%%%%%% Profile-eyes check %%%%%%

if FaceDetectConfig.ProfileEyesTestTF && ... If the profile-eyes test is enabled
   ProfileDetectorTF                     %   If the current face detector returns profiles

    %For efficiency, proceed only if the previous checks were successful
    if Passed_NROI_TF      && ... If the ROI passed the number-of-ROIs check 
       Passed_SkinColor_TF    %   If the ROI passed the proportion-of-skin check 

        %Use the full frame rather than the bounded frame (VidFrameGray)
        %Matrix; type uint8.
        VidFrameGrayEyes = rgb2gray(VidFrame);

        %Search frame for a pair of eyes
        %If at least one detection returned: M detections x 4 matrix; type double.
        %If no detections returned: 0 x 0 element; type double.
        ROIEyePair = FaceDetectConfig.faceDetectorEyePair(VidFrameGrayEyes);

        %If there is not a pair of eyes, then the ROI passes the test 
        Passed_ProfileEyes_TF = isempty(ROIEyePair);                

        %If the ROI passed the test
        if Passed_ProfileEyes_TF 
            
            %Indicate that the ROI passed the profile-eyes check
            %Note: this value is displayed on the output video.
            HasROITF_ProfileEyesPresent_ith = false;
            
        else
            
            %Indicate that the ROI did not pass the profile-eyes check
            %Note: this value is displayed on the output video.
            HasROITF_ProfileEyesPresent_ith = true;
            
            %Record frame index
            %Detection attempts will not be permitted from algorithms that return profiles for a 
            %specified number of frames from the current index. This is enforced by function
            %FaceDetect.
            %Scalar; type int32.
            ProfileEyesIdx = i;
        end 
            
    else

        %Indicate that the ROI passed the profile-eyes check
        %Note: the profile-eyes check was not conducted in this condition.
        Passed_ProfileEyes_TF = true;   
        
        %As the profile-eyes check was not conducted, do not indicate that the ROI failed the
        %profile-eyes check.         
        HasROITF_ProfileEyesPresent_ith = false;       
    end
    
else    
    
    %Indicate that the ROI passed the profile-eyes check
    %Note: true is assigned if the profile-eyes check is not enabled or if the detection algorithm 
    %returns a facial orientation that is not a profile.
    Passed_ProfileEyes_TF = true; 
    
    %As the profile-eyes check was not conducted, do not indicate that the ROI failed the
    %profile-eyes check.         
    HasROITF_ProfileEyesPresent_ith = false;           
end


%%%%%% Assign ROI coordinates if ROI passed all criteria %%%%%%

if Passed_NROI_TF        && ... passed the number-of-ROIs check
   Passed_SkinColor_TF   && ... passed the skin-proportion check
   Passed_ProfileEyes_TF    ... passed the profile-eyes check    

    %Indicate that detection attempt was successful       
    ROISuccessfulTF = true; 
    
    %Assign ROI coordinates 
    %1 x 4 row vector; type int16.
    ROISuccessful = ROITentative_int16;  

else  
    
    %Indicate that detection attempt was not successful       
    ROISuccessfulTF = false;  
    
    %Assign empty ROI coordinates     
    ROISuccessful = int16([]); 

    %If function ConfirmSkinPresent not was called 
    %Otherwise, ConfirmSkinPresent would have returned YSingle. If YSingle was returned, it will be  
    %used for function SkinSegment_OversegmentationCheck.    
    if ~ Passed_NROI_TF       
        
        YSingle = [];
    end    
    
    %Assign empty ROI values
    CbSingle              = [];
    CrSingle              = [];  
    RUint8                = []; 
    GUint8                = []; 
    BUint8                = [];
    HSingle               = [];
    SSingle               = [];
    IsSkinMask_LocalRange = [];
    NRows_Matrix          = int32([]); 
    NCols_Matrix          = int32([]);    
end      


end %end function

