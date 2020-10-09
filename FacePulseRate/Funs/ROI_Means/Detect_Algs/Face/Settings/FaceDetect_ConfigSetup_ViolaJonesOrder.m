function FaceDetectConfig = FaceDetect_ConfigSetup_ViolaJonesOrder(FaceDetectConfig)
%FaceDetect_ConfigSetup_ViolaJonesOrder   Initialize list for use in ordering the Viola-Jones face 
%                                         detectors for a given frame.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function FaceDetect_ConfigSetup.
%
%
%    Description
%    -----------
%
%    Initialize list for use in ordering the Viola-Jones face detectors for a given frame. For 
%    details, see function FaceDetect_AlgOrder.
%                                     
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.




%Assign the string vector used by function FaceDetect_AlgOrder to assign the order in which the 
%algorithms will be used.

if FaceDetectConfig.ROIFaceSecondary1TF && FaceDetectConfig.ROIFaceSecondary2TF

    FaceDetectConfig.Algorithms = ["Primary", "Secondary1", "Secondary2"];

    %Number of algorithms
    FaceDetectConfig.NAlgs = 3;

    %Not used for this condition
    FaceDetectConfig.SecAlg = [];

elseif FaceDetectConfig.ROIFaceSecondary1TF && ~ FaceDetectConfig.ROIFaceSecondary2TF

    FaceDetectConfig.Algorithms = ["Primary", "Secondary1"];

    %Number of algorithms
    FaceDetectConfig.NAlgs = 2;

    %Specify that the secondary algorithm is secondary #1
    FaceDetectConfig.SecAlg = 1;

%Currently, this condition isn't possible as secondary #2 cannot be run unless
%secondary #1 is also enabled. This condition is included for robustness.
elseif ~ FaceDetectConfig.ROIFaceSecondary1TF && FaceDetectConfig.ROIFaceSecondary2TF

    FaceDetectConfig.Algorithms = ["Primary", "Secondary2"];

    %Number of algorithms
    FaceDetectConfig.NAlgs = 2;

    %Specify that the secondary algorithm is secondary #1
    FaceDetectConfig.SecAlg = 2;

else

    FaceDetectConfig.Algorithms = "Primary";

    %Number of algorithms
    FaceDetectConfig.NAlgs = 1;

    %Not used for this condition
    FaceDetectConfig.SecAlg = [];
end


end %end function

