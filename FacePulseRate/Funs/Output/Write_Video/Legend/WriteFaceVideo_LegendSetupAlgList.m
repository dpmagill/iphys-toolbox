function [AlgorithmsEnabledList, AlgorithmsEnabledList_OnlyFaceAlgs] = ...
             WriteFaceVideo_LegendSetupAlgList(FaceDetectConfig, SkinDetectConfig, OutputConfig)
%WriteFaceVideo_LegendSetupAlgList   Return character strings of enabled detection algorithms.
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_LegendSetupText.
%
%
%    Description
%    -----------
%
%    Return character strings of enabled detection algorithms:
%        AlgorithmsEnabledList              = All enabled algorithms.
%        AlgorithmsEnabledList_OnlyFaceAlgs = All enabled face-detection algorithms.
%
%    The legend text differs depending on flag OutputConfig.WriteVideoDetailedDiagnosticsTF. For 
%    details and the rationale on these differences, see the description in function 
%    WriteFaceVideo.
%
%    Also, if the skin-detection algorithm was enabled but there were too few skin-color samples
%    collected to activate it, add text indicating that the algorithm could not be activated.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Assign list of face-detection algorithms %%%%%%

%%%%%% --- If detailed diagnostics enabled %%%%%% 

%Note: for text differences between the detailed and non-detailed (default) display options, see  
%the description in function WriteFaceVideo.
if OutputConfig.WriteVideoDetailedDiagnosticsTF
    
    %Initialize string array
    %Note: primary face-detection algorithm always enabled.
    AlgorithmsEnabledList_OnlyFaceAlgs = "Pri";           
    
    if FaceDetectConfig.ROIFaceSecondary1TF     

        AlgorithmsEnabledList_OnlyFaceAlgs = [AlgorithmsEnabledList_OnlyFaceAlgs, " Sec.#1"];   
    end
    
    if FaceDetectConfig.ROIFaceSecondary2TF     

        AlgorithmsEnabledList_OnlyFaceAlgs = [AlgorithmsEnabledList_OnlyFaceAlgs, " Sec.#2"];   
    end
   
%%%%%% --- If detailed diagnostics not enabled (default) %%%%%%

else

    %Initialize string array
    %Note: Frontal (primary) face-detection algorithm always enabled.
    AlgorithmsEnabledList_OnlyFaceAlgs = "Frontal";        
    
    if FaceDetectConfig.ROIFaceSecondary1TF     

        AlgorithmsEnabledList_OnlyFaceAlgs = [AlgorithmsEnabledList_OnlyFaceAlgs, " Profile"];   
    end
    
    if FaceDetectConfig.ROIFaceSecondary2TF     

        AlgorithmsEnabledList_OnlyFaceAlgs = [AlgorithmsEnabledList_OnlyFaceAlgs, " Frontal 2"];   
    end
end


%%%%%% Assign list of all detection algorithms %%%%%%     
    
%In this list, include both face- and skin-detection algorithms.

AlgorithmsEnabledList = AlgorithmsEnabledList_OnlyFaceAlgs;

%If skin-detection algorithm enabled
if  SkinDetectConfig.ROISkinTF 

    %If sufficient number of skin-color samples to activate skin-detection algorithm
    if SkinDetectConfig.Thresholds.SkinColorSamples_NThresholdPassedTF 

        AlgorithmsEnabledList = [AlgorithmsEnabledList, " Skin"];
    end
end
    
    
%%%%%% Join string array and convert to type char %%%%%%

%Add comma(s) if more than one algorithm
if length(AlgorithmsEnabledList_OnlyFaceAlgs) ~= 1

    AlgorithmsEnabledList_OnlyFaceAlgs = ...
        join( AlgorithmsEnabledList_OnlyFaceAlgs(1 : end), "," );
end

%Add comma(s) if more than one algorithm
if length(AlgorithmsEnabledList) ~= 1

    AlgorithmsEnabledList = ...
        join( AlgorithmsEnabledList(1 : end), "," );
end

%Convert type string to type char
AlgorithmsEnabledList_OnlyFaceAlgs = char(AlgorithmsEnabledList_OnlyFaceAlgs);

%Convert type string to type char
AlgorithmsEnabledList = char(AlgorithmsEnabledList);        

    

end %end function

