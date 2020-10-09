function FaceDetectConfig = FaceDetect_ConfigSetup_ProfileEyes(FaceDetectConfig, VideoReadConfig)
%FaceDetect_ConfigSetup_ProfileEyes   Settings for the profile-eyes test.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function FaceDetect_ConfigSetup.
%
%
%    Description
%    -----------
%
%    Settings for the profile-eyes test.
%             
%    The purpose of the profile-eyes test is to check the validity of a face-detection algorithm  
%    that returns a profile detection of the face. (By default, the secondary #1 algorithm is the 
%    only algorithm that returns a profile detection). The test determines whether a pair of eyes 
%    is also detected anywhere in the frame. Because a pair of eyes would be likely in a frontal 
%    orientation of the face but less likely in profile orientation of the face, the presence of  
%    both a pair of eyes and a profile may suggest a detection error. Therefore, if a pair of eyes 
%    exists alongside a profile, the profile is considered a detection error.
%
%    When a pair of eyes is detected in a profile, any detectors that return profiles are
%    deactivated for a specified number of frames. This is conducted because the detector that 
%    detects a pair of eyes may not always successfully detect a pair of eyes when one is present.
%    To guard against these false negatives, detectors that return profiles are deactivated for a
%    short period of time when a pair of eyes is detected alongside a profile. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Whether the profile-eyes test should be enabled %%%%%%

FaceDetectConfig.ProfileEyesTestTF = true;


%%%%%% Initialize Viola-Jones pair-of-eyes detector %%%%%%

%Minimum accepted size of ROI 
%This is specified to increase the efficiency of the Viola-Jones detector.
%1 x 2 row vector; type double.
MinSize = zeros(1, 2, 'double');

%Minimum ROI height
MinSize(1) = round(VideoReadConfig.VidObj.Height * .0417);

%Minimum ROI width
MinSize(2) = round(VideoReadConfig.VidObj.Width * .0820);

%Maximum accepted size of ROI 
%This is specified to increase the efficiency of the Viola-Jones detector.
%1 x 2 row vector; type double.
MaxSize = MinSize * 2;

%Detector that detects a pair of eyes
FaceDetectConfig.faceDetectorEyePair = ...
    vision.CascadeObjectDetector( ...
        'haarcascade_mcs_eyepair_big.xml', ...
        'MergeThreshold', 3, ...
        'MinSize', MinSize, ...
        'MaxSize', MaxSize ...
    );


%%%%%% Set deactivation buffer %%%%%%

%The number of frames that must pass after a pair of eyes is detected for profiles to be considered
%valid.
FaceDetectConfig.ProfileEyesBuffer = int32(50);

%Initialize the index of the most recent frame in which a pair of eyes was found.
FaceDetectConfig.ProfileEyesIdx = -FaceDetectConfig.ProfileEyesBuffer;


end %end function

