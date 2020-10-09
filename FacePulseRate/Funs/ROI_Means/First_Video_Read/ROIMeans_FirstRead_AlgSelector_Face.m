function [ROISuccessful, FacePrimaryAttemptedTF_ith, FacePrimaryTF_ith, SkinNotPresent_Pri_ith, ...
          ProfileEyesPresent_Pri_ith, FaceSecondary1AttemptedTF_ith, FaceSecondary1TF_ith, ...
          SkinNotPresent_Sec1_ith, ProfileEyesPresent_Sec1_ith, FaceSecondary2AttemptedTF_ith, ...
          FaceSecondary2TF_ith, SkinNotPresent_Sec2_ith, ProfileEyesPresent_Sec2_ith, YSingle, ...
          CbSingle, CrSingle, RUint8, GUint8, BUint8, HSingle, SSingle, IsSkinMask_LocalRange, ...
          NRows_Matrix, NCols_Matrix, BBox_Scan_FaceAlg_ith, ProfileEyesIdx, ...
          ProportionSkin_AlgName, ProportionSkin, YSingle_OversegmentationCheck, ...
          OversegmentationCheckReady] = ...                        
              ROIMeans_FirstRead_AlgSelector_Face(i, VidFrame, UseBoundingBoxFaceTF, ...
                  BoundingBoxFace, ExpediteColorThresholdsTF, ProfileEyesIdx, HasROI_TF, ...
                  FaceDetectConfig, SkinSegmentConfig, SkinDetectConfig, VideoReadConfig)
%ROIMeans_FirstRead_AlgSelector_Face   Apply the face-detection algorithm(s) to the ith frame.
%                                  
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead_AlgSelector. 
%
%
%    Description
%    -----------
%
%    Apply the face-detection algorithm(s) to the bounded area of the ith frame. Apply each 
%    face-detection algorithm in turn until a successful detection is made. Once a successful 
%    detection is made, the ROI is returned, and no further face-detection algorithm(s) are run.  
%    The order in which the face-detection algorithm(s) are called is dynamically updated so that  
%    the algorithm(s) that have been most likely to make detections within a local number of frames  
%    are called before others. 
%
%    In addition to returning the ROI and detection information, also return color channels  
%    assigned during the operations for reuse in setting the thresholds for tailored   
%    skin-segmentation and for the skin-detection algorithm (see function 
%    ROIMeans_FirstRead_SetThresholds). 
%
%    Note: face-detection settings in struct FaceDetectConfig are assigned by function 
%    FaceDetect_ConfigSetup.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.
 

%%%%%% Initialize output arguments %%%%%%

%Depending on the detection results, some may not be filled.
ROISuccessful                  = int16([]);
FacePrimaryAttemptedTF_ith     = false;
FacePrimaryTF_ith              = false;
SkinNotPresent_Pri_ith         = false;
ProfileEyesPresent_Pri_ith     = false;
ProportionSkin_Pri_ith         = -1;
FaceSecondary1AttemptedTF_ith  = false;
FaceSecondary1TF_ith           = false;
SkinNotPresent_Sec1_ith        = false;
ProfileEyesPresent_Sec1_ith    = false;
ProportionSkin_Sec1_ith        = -1; 
FaceSecondary2AttemptedTF_ith  = false;
FaceSecondary2TF_ith           = false;
SkinNotPresent_Sec2_ith        = false;
ProfileEyesPresent_Sec2_ith    = false;
ProportionSkin_Sec2_ith        = -1;
YSingle                        = single([]);
CbSingle                       = single([]);
CrSingle                       = single([]);
RUint8                         = uint8([]); 
GUint8                         = uint8([]); 
BUint8                         = uint8([]);
HSingle                        = single([]);
SSingle                        = single([]);
IsSkinMask_LocalRange          = logical([]);
NRows_Matrix                   = int32([]); 
NCols_Matrix                   = int32([]); 

             
%%%%%% Crop frame to bound scanned region and convert to grayscale %%%%%%

%Note: although the face-detection object (vision.CascadeObjectDetector) can crop and convert to
%grayscale as specified, to avoid the object from repeating this cropping and conversion for each
%algorithm, it is done once here. Also, the same bounding box is used for each algorithm to reduce
%processing time from recropping and conversion for each algorithm.

%If bounding box to be used
if UseBoundingBoxFaceTF

    %Index of rows to crop
    rowCrop = ...
        BoundingBoxFace(2) :                         ... Y-upper
        BoundingBoxFace(2) + BoundingBoxFace(4) - 1; %   Y-upper + height

    %Index of columns to crop
    colCrop = ...
        BoundingBoxFace(1) :                         ... X-left
        BoundingBoxFace(1) + BoundingBoxFace(3) - 1; %   X-left + width

    %Crop frame to bound scanned region
    VidFrameCrop = VidFrame(rowCrop, colCrop, :);

    %Record bounding box for display on output video for diagnostic use
    %Convert from type int16 to type uint16 because signed operations not conducted with this
    %variable.
    BBox_Scan_FaceAlg_ith = uint16(BoundingBoxFace);
    
    %Convert cropped frame to grayscale
    VidFrameGray = rgb2gray(VidFrameCrop);
 
%No bounding will be used    
else

    %Record bounding box (full frame) for display on output video for diagnostic use
    %Convert from type int16 to type uint16 because signed operations not conducted with this
    %variable.
    BBox_Scan_FaceAlg_ith = ...
        uint16([1, 1, VideoReadConfig.VidObjWidth, VideoReadConfig.VidObjHeight]);
    
    %Convert entire frame to grayscale
    VidFrameGray = rgb2gray(VidFrame); 
end


%%%%%% Determine order in which face-detection algorithm(s) will be used %%%%%%
    
%Order according to the number of detections each algorithm has a specified number of frames back.
%The purpose of this function is to choose make scanning more efficient by using the algorithm(s) 
%more likely to find a detection first. Once a detection is found, the other algorithms are not  
%run, so time could be saved if the algorithm(s) more likely to find a detection are run first.
%Note: 'FaceDetect_AlgOrder' is a custom function located within folder 'FacePulseRate'.
FaceDetectAlgorithmsOrdered = ...
    FaceDetect_AlgOrder(i, HasROI_TF, FaceDetectConfig.Algorithms, FaceDetectConfig.NAlgs, ...
        FaceDetectConfig.SecAlg, ExpediteColorThresholdsTF);

    
%%%%%% Assess frames with face-detection algorithm(s) until detection is made %%%%%%

%Loops across face-detection algorithms, in the order specified by FaceDetectAlgorithmsOrdered, 
%until a detection is made or no algorithms remain.

%Initialize flag
ROISuccessfulTF = false;

%Loop across algorithms in the order specified by FaceDetectAlgorithmsOrdered 
for j = FaceDetectAlgorithmsOrdered

    %Exit loop if a detection is found
    if ROISuccessfulTF

        %Exit loop
        break               
    end

    switch j                      

        %%%%%% --- Primary face-detection algorithm %%%%%%
        case "Primary"

            %Specify primary face-detection algorithm
            faceDetector = FaceDetectConfig.faceDetectorPrimary;
            
            %Specify condition for skin-color proportion check
            FaceAlgorithm = 'p'; %Indication to use the threshold for the primary face-detection 
                                 %algorithm.
                
            %Whether the detection algorithm returns a profile of a face
            %This field is used by the profile-eyes test.
            ProfileDetectorTF = FaceDetectConfig.PrimaryProfileTF;
            
            %Conduct face-detection algorithm operations
            %ROISuccessful is type int16.
            %Note: 'FaceDetect' is a custom function located within folder 'FacePulseRate'. 
            [ROISuccessfulTF, ROISuccessful, SkinNotPresent_ith, ProfileEyesPresent_ith, ...
             YSingle, CbSingle, CrSingle, RUint8, GUint8, BUint8, HSingle, SSingle, ...
             IsSkinMask_LocalRange, NRows_Matrix, NCols_Matrix, ProfileEyesIdx, ...
             ProportionSkin] = ...                       
                FaceDetect(i, faceDetector, VidFrameGray, UseBoundingBoxFaceTF, ...
                    BoundingBoxFace, FaceAlgorithm, VidFrame, ProfileEyesIdx, ...
                    ProfileDetectorTF, FaceDetectConfig, SkinSegmentConfig, SkinDetectConfig);
                    
            %Mark that detection was attempted by algorithm
            FacePrimaryAttemptedTF_ith = true;       
            
            %Assign the proportion of pixels classified as skin in the ROI (ProportionSkin). 
            %Used by function SkinSegment_OversegmentationCheck.
            %Note: ProportionSkin will not contain a proportion and YSingle will be empty if  
            %function ConfirmSkinPresent was not called by function FaceDetect_ROIValidate. -1  
            %indicates that these variables cannot be used because ConfirmSkinPresent was not
            %called.
            
            ProportionSkin_Pri_ith = ProportionSkin;
            
            if ProportionSkin ~= -1                 
                
                YSingle_Pri = YSingle;
            end

            %Value indicating whether the ROI passed the proportion-of-skin check
            %Note: if true, then ROISuccessfulTF will be false. However, ROISuccessfulTF can be
            %false without SkinNotPresent_ith being true. 
            SkinNotPresent_Pri_ith = SkinNotPresent_ith;
            
            %Value indicating whether the ROI passed the proportion-of-skin check
            %Note: if true, then ROISuccessfulTF will be false. However, ROISuccessfulTF can be
            %false without SkinNotPresent_ith being true. 
            ProfileEyesPresent_Pri_ith = ProfileEyesPresent_ith;            
            
            %If detection successful
            if ROISuccessfulTF

                %Note detection was successful
                FacePrimaryTF_ith = true;

            %If detection not successful
            else

                %Note detection was not successful
                FacePrimaryTF_ith = false;
                
                %Note: ROISuccessful will remain as preallocated (zeros(1, 4, 'int16')) 
            end

        %%%%%% --- Secondary #1 face-detection algorithm %%%%%% 
        case "Secondary1"             
            
            %Specify secondary #1 face-detection algorithm
            faceDetector = FaceDetectConfig.faceDetectorSecondary1;

            %Specify condition for skin-color proportion check
            FaceAlgorithm = '1'; %Indication to use the threshold for the secondary #1  
                                 %face-detection algorithm.

            %Whether the detection algorithm returns a profile of a face
            %This field is used by the profile-eyes test.
            ProfileDetectorTF = FaceDetectConfig.Secondary1ProfileTF;            
            
            %Conduct face-detection algorithm operations
            %ROISuccessful is type int16.
            %Note: 'FaceDetect' is a custom function located within folder 'FacePulseRate'.
            [ROISuccessfulTF, ROISuccessful, SkinNotPresent_ith, ProfileEyesPresent_ith, ...
             YSingle, CbSingle, CrSingle, RUint8, GUint8, BUint8, HSingle, SSingle, ...
             IsSkinMask_LocalRange, NRows_Matrix, NCols_Matrix, ProfileEyesIdx, ...
             ProportionSkin] = ...                             
                FaceDetect(i, faceDetector, VidFrameGray, UseBoundingBoxFaceTF, ...
                    BoundingBoxFace, FaceAlgorithm, VidFrame, ProfileEyesIdx, ...
                    ProfileDetectorTF, FaceDetectConfig, SkinSegmentConfig, SkinDetectConfig);                  

            %Mark that detection was attempted by algorithm
            FaceSecondary1AttemptedTF_ith = true;       

            %Assign the proportion of pixels classified as skin in the ROI (ProportionSkin). 
            %Used by function SkinSegment_OversegmentationCheck.
            %Note: ProportionSkin will not contain a proportion and YSingle will be empty if  
            %function ConfirmSkinPresent was not called by function FaceDetect_ROIValidate. -1  
            %indicates that these variables cannot be used because ConfirmSkinPresent was not
            %called.
            
            ProportionSkin_Sec1_ith = ProportionSkin;
            
            if ProportionSkin ~= -1
                 
                 YSingle_Sec1 = YSingle;                 
            end

            %Value indicating whether the ROI passed the proportion-of-skin check
            %Note: if true, then ROISuccessfulTF will be false. However, ROISuccessfulTF can be
            %false without SkinNotPresent_ith being true. 
            SkinNotPresent_Sec1_ith = SkinNotPresent_ith;                        

            %Value indicating whether the ROI passed the proportion-of-skin check
            %Note: if true, then ROISuccessfulTF will be false. However, ROISuccessfulTF can be
            %false without SkinNotPresent_ith being true. 
            ProfileEyesPresent_Sec1_ith = ProfileEyesPresent_ith;             
            
            %If detection successful
            if ROISuccessfulTF

                %Note detection was successful
                FaceSecondary1TF_ith = true; 

            %If detection not successful
            else

                %Note detection was not successful
                FaceSecondary1TF_ith = false;

                %Note: ROISuccessful will remain as preallocated (zeros(1, 4, 'int16')) 
            end                              
            
        %%%%%% --- Secondary #2 face-detection algorithm %%%%%%         
        case "Secondary2"  
            
            %Specify secondary #2 face-detection algorithm
            faceDetector = FaceDetectConfig.faceDetectorSecondary2;
            
            %Specify condition for skin-color proportion check
            FaceAlgorithm = '2'; %Indication to use the threshold for the secondary #2  
                                 %face-detection algorithm.  

            %Whether the detection algorithm returns a profile of a face
            %This field is used by the profile-eyes test.
            ProfileDetectorTF = FaceDetectConfig.Secondary2ProfileTF;             
            
            %Conduct face-detection algorithm operations
            %ROISuccessful is type int16.
            %Note: 'FaceDetect' is a custom function located within folder 'FacePulseRate'. 
            [ROISuccessfulTF, ROISuccessful, SkinNotPresent_ith, ProfileEyesPresent_ith, ...
             YSingle, CbSingle, CrSingle, RUint8, GUint8, BUint8, HSingle, SSingle, ...
             IsSkinMask_LocalRange, NRows_Matrix, NCols_Matrix, ProfileEyesIdx, ...
             ProportionSkin] = ...
                FaceDetect(i, faceDetector, VidFrameGray, UseBoundingBoxFaceTF, ...
                    BoundingBoxFace, FaceAlgorithm, VidFrame, ProfileEyesIdx, ...
                    ProfileDetectorTF, FaceDetectConfig, SkinSegmentConfig, SkinDetectConfig);

            %Mark that detection was attempted by algorithm
            FaceSecondary2AttemptedTF_ith = true;       
            
            %Assign the proportion of pixels classified as skin in the ROI (ProportionSkin). 
            %Used by function SkinSegment_OversegmentationCheck.
            %Note: ProportionSkin will not contain a proportion and YSingle will be empty if  
            %function ConfirmSkinPresent was not called by function FaceDetect_ROIValidate. -1  
            %indicates that these variables cannot be used because ConfirmSkinPresent was not
            %called.
                        
            ProportionSkin_Sec2_ith = ProportionSkin;
            
            if ProportionSkin ~= -1
                                 
                 YSingle_Sec2 = YSingle;                 
            end

            %Value indicating whether the ROI passed the proportion-of-skin check
            %Note: if true, then ROISuccessfulTF will be false. However, ROISuccessfulTF can be
            %false without SkinNotPresent_ith being true. 
            SkinNotPresent_Sec2_ith = SkinNotPresent_ith;             

            %Value indicating whether the ROI passed the proportion-of-skin check
            %Note: if true, then ROISuccessfulTF will be false. However, ROISuccessfulTF can be
            %false without SkinNotPresent_ith being true. 
            ProfileEyesPresent_Sec2_ith = ProfileEyesPresent_ith;
            
            %If detection successful
            if ROISuccessfulTF

                %Note detection was successful
                FaceSecondary2TF_ith = true;
                
            %If detection not successful
            else

                %Note detection was not successful
                FaceSecondary2TF_ith = false;
                
                %Note: ROISuccessful will remain as preallocated (zeros(1, 4, 'int16')) 
            end  
    end %end switch 
end %end for


%%%%%% Setup for oversegmentation check %%%%%%

%The oversegmentation check is conducted within function ROIMeans_FirstRead.

%Select an algorithm from which to test for oversegmentation
if ProportionSkin_Pri_ith ~= -1

    ProportionSkin_AlgName        = 'p';
    ProportionSkin                = ProportionSkin_Pri_ith;
    YSingle_OversegmentationCheck = YSingle_Pri;
    OversegmentationCheckReady    = true;
    
elseif ProportionSkin_Sec1_ith ~= -1

    ProportionSkin_AlgName        = '1';
    ProportionSkin                = ProportionSkin_Sec1_ith;
    YSingle_OversegmentationCheck = YSingle_Sec1;
    OversegmentationCheckReady    = true;
    
elseif ProportionSkin_Sec2_ith ~= -1
    
    ProportionSkin_AlgName        = '2';
    ProportionSkin                = ProportionSkin_Sec2_ith; 
    YSingle_OversegmentationCheck = YSingle_Sec2;
    OversegmentationCheckReady    = true;
    
else
  
    ProportionSkin_AlgName        = 'NA';
    ProportionSkin                = -1;
    YSingle_OversegmentationCheck = [];
    OversegmentationCheckReady    = false;   
end


end %end function

