function FaceDetectConfig = ...
             FaceDetect_ConfigSetup(ROIFacePrimaryXML, ProfileFaceDetectorTF, SkinDetectConfig, ...
                 ROIGeneralConfig, VideoReadConfig)                                 
%FaceDetect_ConfigSetup     Setup configuration struct for face-detection algorithms.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ValidateAndConfigure.
%
%
%    Description
%    -----------
%
%    Setup configuration struct for face-detection algorithms. This struct contains various 
%    settings for the face-detection algorithms. The settings include bounding box size controls,  
%    various Viola-Jones detectors, and settings controlling whether detectors should skip certain
%    frames for efficiency, among others.    
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
%    - Large pair-of-eyes Viola-Jones detector used by the profile-eyes test: 
%
%      haarcascade_mcs_eyepair_big.xml. Copyright (c) 2006-2020, Modesto Castrillon-Santana (SIANI,  
%      Universidad de Las Palmas de Gran Canaria, Spain.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Initialization and visualization of configuration struct %%%%%%

FaceDetectConfig = ...
    struct( ...
        ... Settings for the Viola-Jones face detectors:
        'ROIFacePrimaryXML', ' ', ...
        'faceDetectorPrimary', [], ...
        'PrimaryProfileTF', false, ...
        'ROIFaceSecondary1TF', false, ...
        'ROIFaceSecondary1XML', ' ', ...
        'ROIMinWidthProportionIncreaseSec1', double(0), ...
        'ROIMinHeightProportionIncreaseSec1', double(0), ...        
        'faceDetectorSecondary1', [], ...
        'Secondary1ProfileTF', false, ...
        'ROIFaceSecondary2TF', false, ...
        'ROIFaceSecondary2XML', ' ', ...
        'ROIMinWidthProportionIncreaseSec2', double(0), ...
        'ROIMinHeightProportionIncreaseSec2', double(0), ...
        'faceDetectorSecondary2', [], ...
        'Secondary2ProfileTF', false, ...
        ... Settings for detection skipping:       
        'DetectsToAttemptsRatioThreshold', double(0), ...
         ... Settings for bounding boxes:           
        'ROIFace_ChangeFactorROIPrimary', double(0), ...
        'ROIFace_ChangeFactorROISecondary1', double(0), ...
        'ROIFace_ChangeFactorROISecondary2', double(0), ...
        'ROIFace_BoundingBoxEnlargementFactor', double(0), ...
        'BoundingBoxGrowthThreshold_adjusted', double(0), ...
        'BoundingBoxGrowthRate_adjusted', double(0), ...
        ... Settings for the order in which detectors are applied:        
        'Algorithms', " ", ...
        'NAlgs', double(0),  ...
        'SecAlg', double(0), ...   
        ... Settings for the profile-eyes test:    
        'ProfileEyesTestTF', false, ...
        'faceDetectorEyePair', [], ...
        'ProfileEyesBuffer', int32(0), ...
        'ProfileEyesIdx', int32(0) ...
    );


%%%%%% Setup Viola-Jones face detectors %%%%%%

%Specify settings for the Viola-Jones face detectors.

%Note: FaceDetect_ConfigSetup_ViolaJones is a custom function located within folder 
%'FacePulseRate'.
FaceDetectConfig = ...
    FaceDetect_ConfigSetup_ViolaJones(ROIFacePrimaryXML, ProfileFaceDetectorTF, ...
        FaceDetectConfig, ROIGeneralConfig, VideoReadConfig);


%%%%%% Detection skipping %%%%%%

%Detection skipping is implemented to increase efficiency. 

%For details, see function ROIMeans_FirstRead_DetermineSkipFrame.

%Specify detections-to-attempts ratio threshold to determine whether the face-detection algorithm 
%can be skipped for a given frame. Skipping, which is otherwise determined by argument 
%ROISkipFrameThreshold (see function ROIGeneralConfig_Setup), is overwridden by this parameter. 
%Implementation of this parameter is designed to increase the number of detections obtained for 
%segments of the video where detections are spotty.
%Scalar; type double.
FaceDetectConfig.DetectsToAttemptsRatioThreshold = .75;


%%%%%% Bounding box size settings %%%%%%

%Specify size settings for bounding box used for the face-detection algorithms.                             

FaceDetectConfig = FaceDetect_ConfigSetup_BBox(FaceDetectConfig, VideoReadConfig); 


%%%%%% Settings for determining the order in which Viola-Jones detectors are applied %%%%%%

%Initialize the list for use in ordering the Viola-Jones face detectors for a given frame. 

%Note: FaceDetect_ConfigSetup_ViolaJonesOrder is a custom function located within folder 
%'FacePulseRate'.
FaceDetectConfig = FaceDetect_ConfigSetup_ViolaJonesOrder(FaceDetectConfig);   


%%%%%% Settings for the profile-eyes test %%%%%%%

%Note: FaceDetect_ConfigSetup_ProfileEyes is a custom function located within folder 
%'FacePulseRate'.
FaceDetectConfig = FaceDetect_ConfigSetup_ProfileEyes(FaceDetectConfig, VideoReadConfig);


%%%%%% Smoothing settings %%%%%%

%This setting is used by function ROIMSIR.

FaceDetectConfig.ROIFaceSmoothingWindow = 8;


%%%%%% Validate settings %%%%%%

%Check whether Viola-Jones file arguments have extension xml:

%Viola-Jones file for primary face-detection algorithm
if ~ strcmp( '.xml', FaceDetectConfig.ROIFacePrimaryXML(end - 3 : end) )
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: File specified for ROIFacePrimaryXML must have extension .xml.' ...
        );
    
    throw(ME);           
end

%Viola-Jones file for secondary #1 face-detection algorithm
if FaceDetectConfig.ROIFaceSecondary1TF && ...
    ~ strcmp( '.xml', FaceDetectConfig.ROIFaceSecondary1XML(end - 3 : end) )
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: File specified for ROIFaceSecondary1XML must have extension .xml.' ...
        );
    
    throw(ME);           
end

%Viola-Jones file for secondary #2 face-detection algorithm
if FaceDetectConfig.ROIFaceSecondary2TF && ...
    ~ strcmp( '.xml', FaceDetectConfig.ROIFaceSecondary2XML(end - 3 : end) )
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: File specified for ROIFaceSecondary2XML must have extension .xml.' ...
        );
    
    throw(ME);           
end


%Check Viola-Jones argument precedence:

%The argument for the Viola-Jones file for primary face-detection algorithm cannot be empty
if isempty(FaceDetectConfig.ROIFacePrimaryXML)  
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: ROIFacePrimaryXML cannot be empty.' ...
        );
    
    throw(ME);
end

%ROIFaceSecondary2XML not empty but ROIFaceSecondary1XML is empty:
if ~ isempty(FaceDetectConfig.ROIFaceSecondary2XML) && ...
   isempty(FaceDetectConfig.ROIFaceSecondary1XML) 
    
    ME = ...
        MException( ...
            'Component:Argument', ...
             ['Error: when ROIFaceSecondary2XML is assigned, \nFace_Alg_Secondary should be', ...
              ' assigned. To use only one secondary algorithm, assign ROIFaceSecondary1XML.'] ...
        );
    
    throw(ME);
end 

%ROIFaceSecondary1TF = true but ROIFaceSecondary1XML empty 
if FaceDetectConfig.ROIFaceSecondary1TF && ...
   isempty(FaceDetectConfig.ROIFaceSecondary1XML)  
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: If ROIFaceSecondary1TF = true,', ...
             ' ROIFaceSecondary1XML must be assigned.'] ...
        );
    
    throw(ME);
end

%ROIFaceSecondary1TF = true but ROIFacePrimaryXML empty 
if FaceDetectConfig.ROIFaceSecondary1TF && isempty(FaceDetectConfig.ROIFacePrimaryXML)  
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: If ROIFaceSecondary1TF = true,', ...
             ' ROIFacePrimaryXML must be assigned.'] ...
        );
    
    throw(ME);
end

%ROISkinTF == true but ROIFacePrimaryXML empty 
if SkinDetectConfig.ROISkinTF && isempty(FaceDetectConfig.ROIFacePrimaryXML)  
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: If ROISkinTF = true ROIFacePrimaryXML must be assigned.' ...
        );
    
    throw(ME);
end

%Validate window size for smoothing arguments, which can be up to FrameCacheMaxFrames * 2 - 1. 
WindowSizeMax = ROIGeneralConfig.FrameCacheMaxFrames * 2 - 1;

if FaceDetectConfig.ROIFaceSmoothingWindow > WindowSizeMax 


    %Throw exception
    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: The maximum window value is ', num2str(WindowSizeMax), ' for input', ...
             ' arguments ROIFaceSmoothingWindow, ROISkinSmoothingWindow, and' ...
             ' ROIFinalSmoothingWindows.'] ...
        );       
    
    throw(ME)
end


end %end function

