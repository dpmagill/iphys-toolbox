function [DAProportion_Pri, DAProportion_Sec1, DAProportion_Sec2] = ...
             WriteFaceVideo_LegendSetupTextProportions(HasROI_TF, FaceDetectConfig)
%WriteFaceVideo_LegendSetupTextProportions    Calculate detections-to-attempts proportion(s) for
%                                             face-detection algorithm(s). 
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_LegendSetupText.
%    
%
%    Description
%    -----------
%
%    Calculate detections-to-attempts proportion(s) for face-detection algorithm(s). See the
%    description in function WriteFaceVideo for its interpretation.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Primary face-detection algorithm detections-to-attempts proportion %%%%%%

DAProportion_Pri = ...
    sprintf( ...
        '%.2f', ... number to 2 decimals in type character 
        nnz(HasROI_TF.FacePrimary) / nnz(HasROI_TF.FacePrimaryAttempted) ...
    );


%%%%%% Secondary #1 face-detection algorithm detections-to-attempts proportion %%%%%%

if FaceDetectConfig.ROIFaceSecondary1TF %secondary #1 algorithm enabled

    DAProportion_Sec1 = ...
        sprintf( ...
            '%.2f', ... number to 2 decimals in type character 
            nnz(HasROI_TF.FaceSecondary1) / nnz(HasROI_TF.FaceSecondary1Attempted) ...
        );

else %secondary #1 algorithm not enabled

    DAProportion_Sec1 = 'NA';
end


%%%%%% Secondary #2 face-detection algorithm detections-to-attempts proportion %%%%%%

if FaceDetectConfig.ROIFaceSecondary2TF %secondary #2 algorithm enabled

    DAProportion_Sec2 = ...
        sprintf( ...
            '%.2f', ... number to 2 decimals in type character 
            nnz(HasROI_TF.FaceSecondary2) / nnz(HasROI_TF.FaceSecondary2Attempted) ...
        );

else %secondary #2 algorithm not enabled

    DAProportion_Sec2 = 'NA';
end
    
    
end %end function

