function FaceDetectConfig = ...
             FaceDetect_ConfigSetup_ViolaJones(ROIFacePrimaryXML, ProfileFaceDetectorTF, ...
                 FaceDetectConfig, ROIGeneralConfig, VideoReadConfig)
%FaceDetect_ConfigSetup_ViolaJones   Specify settings for the Viola-Jones face detectors.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function FaceDetect_ConfigSetup.
%
%
%    Description
%    -----------
%
%    Specify settings for the Viola-Jones face detectors, which are used by the face-detection
%    algorithms.
%
%    -- Assumptions on orientation of faces returned by Viola-Jones face detectors --
%
%    As of the current implementation, the primary face-detection algorithm is expected to detect  
%    faces in a frontal orientation. One operation that depends upon this is the collection of skin 
%    samples from which to set the thresholds for skin segmentation and skin detection (see 
%    function ROIMeans_FirstRead_CollectSkinColorSamples). Additionally, some annotations on the 
%    output video label the primary face-detection algorithm as the "frontal" algorithm (see  
%    functions WriteFaceVideo_LegendSetupText and WriteFaceVideo_ROIAnnotation).
%
%    As of the current implementation, the secondary #1 face-detection algorithm is expected to   
%    detect faces in a profile orientation. Some annotations on the output video label the primary 
%    face-detection algorithm as the "profile" algorithm (see functions  
%    WriteFaceVideo_LegendSetupText and WriteFaceVideo_ROIAnnotation). As of the current  
%    implementation, the secondary #2 face-detection algorithm is not expected to correspond to a 
%    particular orientation.
%
%    The Viola-Jones face detectors are vision.CascadeObjectDetector system objects. Their code is
%    from the Matlab Computer Vision Toolbox.
%
%
%    Note on Code Generation
%    -----------------------
%
%    Code generation and compilation was tested for Viola-Jones face detectors, but they did not
%    appear to improve execution speed.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Viola-Jones algorithms %%%%%%

%Specify the xml files for the Viola-Jones detectors.

%Primary face-detection algorithm
%Note: ROIFacePrimaryXML is specified in function ValidateAndConfigure_InternalFlags. This is
%because another function requires this variable before the current function.
%If changed, algorithm labels in function WriteFaceVideo_LegendSetupText should be modified. Values
%may also need to be changed in section "Adjustments to the minimum ROI size depending on 
%algorithm".
FaceDetectConfig.ROIFacePrimaryXML = ROIFacePrimaryXML;

%Whether the detection algorithm returns a profile of a face
%This field is used by the profile-eyes test.
FaceDetectConfig.PrimaryProfileTF = false;

%Whether to enabled the secondary #1 face-detection algorithm
FaceDetectConfig.ROIFaceSecondary1TF = ProfileFaceDetectorTF;

%Secondary #1 face-detection algorithm
%Note: if changed, algorithm labels in function WriteFaceVideo_LegendSetupText should be modified.
%Values may also need to be changed in section "Adjustments to the minimum ROI size depending on 
%algorithm".
FaceDetectConfig.ROIFaceSecondary1XML = 'haarcascade_profileface.xml';

%Whether the detection algorithm returns a profile of a face
%This field is used by the profile-eyes test.
FaceDetectConfig.Secondary1ProfileTF = true;

%Whether to enabled the secondary #2 face-detection algorithm
%Note: currently, the secondary #2 face-detection algorithm is only used for testing purposes.
FaceDetectConfig.ROIFaceSecondary2TF = false;

%Secondary #2 face-detection algorithm
%Note: if changed, algorithm labels in function WriteFaceVideo_LegendSetupText should be modified.
%Values may also need to be changed in section "Adjustments to the minimum ROI size depending on 
%algorithm".
FaceDetectConfig.ROIFaceSecondary2XML = 'cuda_haarcascade_frontalface_alt_tree.xml';

%Whether the detection algorithm returns a profile of a face
%This field is used by the profile-eyes test.
FaceDetectConfig.Secondary2ProfileTF = false;


%%%%%% Minimum ROI size %%%%%%

%The Viola-Jones detectors scan a frame by seaching for objects, which match parameters of the xml 
%file, of a given size. The detectors start with the minimum ROI size, which is specified in the  
%xml file; they incrementally increase the ROI size until the size can grow no larger within the 
%frame dimensions. 

%A minimum ROI size can be specified that is different from the minimum ROI size specified within 
%the xml file. Specifying a minimum ROI size has a couple possible advantages. First, it may result
%in the detector conducting fewer scans because scans are not conducted for ROI sizes below the  
%specified minimum. Reducing such scans has been observed to reduce considerably the execution time 
%of the Viola-Jones detectors. Second, specifying a minimum ROI size has been observed to reduce 
%false positives; specifically, objects too small to be a face are less likely to be returned as a 
%detection because the detectors skip objects whose size is smaller than the specified minimum.

%Specify minimum size threshold for a detection
%1 x 2 row vector; type double.
MinSizeThreshold = ...
    [round( ... minimum height of ROI in pixels, rounded to integer
        ROIGeneralConfig.ROIMinHeightProportion * ... 
        double(VideoReadConfig.VidObj.Height)     ...
     ),   ...  
     round( ... minimum width of ROI in pixels, rounded to integer
        ROIGeneralConfig.ROIMinWidthProportion *  ... 
        double(VideoReadConfig.VidObj.Width)      ...
     )];     

%Prevent MinSizeThreshold from being too small because the size cannot be smaller than the minimum
%size specified in the xml file.
MinSizeThreshold(1) = max( 45, MinSizeThreshold(1) );
MinSizeThreshold(2) = max( 45, MinSizeThreshold(2) );


%%%%%% Adjustments to the minimum ROI size depending on algorithm %%%%%%

%ROIMinWidthRatioIncreaseSec1, ROIMinHeightRatioIncreaseSec1, ROIMinWidthRatioIncreaseSec2, and
%ROIMinHeightRatioIncreaseSec2 indicate the size to adjust ROIMinWidthRatio and ROIMinHeightRatio 
%for the secondary algorithms for the purpose of setting the minimum accepted size in the 
%Viola-Jones detectors. ROIMinWidthRatio and ROIMinHeightRatio is applied to the primary algorithm  
%for the purpose of setting the minimum accepted size in the Viola-Jones detectors. 

%These adjustments should be set if the typical size of detections of one or both of the secondary 
%algorithms differs from that of the primary algorithm, whose minimum size is set by 
%ROIMinWidthRatio and ROIMinHeightRatio. For example, if one or both of the secondary algorithms 
%return larger detections, increasing the minimum size for these algorithms may help decrease false 
%positives. 

%ROIMinWidthRatio and ROIMinHeightRatio are also used for purposes other than setting the minimum  
%accepted size in the Viola-Jones detectors; for these purposes, these adjustments are not used. 
%That is, these adjustments only affect the minimum accepted size in the Viola-Jones detectors for 
%the secondary algorithms. 

%%%%%% --- Secondary #1 face-detection algorithm %%%%%% 

%Specify adjustment factors
%Scalars; type double.
FaceDetectConfig.ROIMinWidthProportionIncreaseSec1 = 1.1;
FaceDetectConfig.ROIMinHeightProportionIncreaseSec1 = 1.1;

%Adjust size of minimum-size threshold:

%The adjustment might be made when the typical size of the detection from the secondary #1
%algorithm is different from the typical size of the detection from the primary algorithm.
MinSizeThresholdSecondary1 = MinSizeThreshold;

%Min height    
MinSizeThresholdSecondary1(1) = ...
    round( ...
        MinSizeThresholdSecondary1(1) * FaceDetectConfig.ROIMinHeightProportionIncreaseSec1 ...
    );

%Min width    
MinSizeThresholdSecondary1(2) = ...
    round( ...
        MinSizeThresholdSecondary1(2) * FaceDetectConfig.ROIMinWidthProportionIncreaseSec1 ...
    );

%%%%%% --- Secondary #2 face-detection algorithm %%%%%% 

%Specify adjustment factors
%Scalars; type double.
FaceDetectConfig.ROIMinWidthProportionIncreaseSec2 = 1.05;
FaceDetectConfig.ROIMinHeightProportionIncreaseSec2 = 1.05;

%Adjust size of minimum-size threshold:

%The adjustment might be made when the typical size of the detection from the secondary #2
%algorithm is different from the typical size of the detection from the primary algorithm.
MinSizeThresholdSecondary2 = MinSizeThreshold;

%Min height
MinSizeThresholdSecondary2(1) = ...
    round( ...
        MinSizeThresholdSecondary2(1) * ...
        FaceDetectConfig.ROIMinHeightProportionIncreaseSec2 ...
    );

%Min width  
MinSizeThresholdSecondary2(2) = ...
    round( ...
        MinSizeThresholdSecondary2(2) * ...
        FaceDetectConfig.ROIMinWidthProportionIncreaseSec2 ...
    );
    

%%%%%% Merge threshold %%%%%%

%A higher merge threshold may increase accuracy.

MergeThreshold = 5;


%%%%%% Initialize Viola-Jones face detectors %%%%%%

%%%%%% --- Viola-Jones face detector with primary algorithm %%%%%% 
   
%Detector object
FaceDetectConfig.faceDetectorPrimary = ...
    vision.CascadeObjectDetector( ...
        FaceDetectConfig.ROIFacePrimaryXML, ...
        'MergeThreshold', MergeThreshold, ...
        'MinSize', MinSizeThreshold ...
    );

%%%%%% --- Viola-Jones face detector with secondary #1 algorithm %%%%%%

%If secondary #1 algorithm enabled
if FaceDetectConfig.ROIFaceSecondary1TF
     
    %Detector object
    FaceDetectConfig.faceDetectorSecondary1 = ...
        vision.CascadeObjectDetector( ...
            FaceDetectConfig.ROIFaceSecondary1XML, ...
            'MergeThreshold', MergeThreshold, ...
            'MinSize', MinSizeThresholdSecondary1 ...
        );    
end
     
%%%%%% --- Viola-Jones face detector with secondary #2 algorithm %%%%%%
    
%If secondary #2 algorithm enabled
if FaceDetectConfig.ROIFaceSecondary2TF
    
    %Detector object
    FaceDetectConfig.faceDetectorSecondary2 = ...
        vision.CascadeObjectDetector( ...
            FaceDetectConfig.ROIFaceSecondary2XML, ...
            'MergeThreshold', MergeThreshold, ...
            'MinSize', MinSizeThresholdSecondary2 ...
        );   
end


end %end function

