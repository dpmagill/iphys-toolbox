function [Text, TextXY, Candidate_text, Rejected_text] = ...
             WriteFaceVideo_SkinDetectDiagnosis_LabelText(i, RegionScores, RegionRankings, ...
                RegionNPixels, RegionCrSDScores, RegionCentroids)
%WriteFaceVideo_SkinDetectDiagnosis_LabelText   Prepare text for region labels as a part of  
%                                               skin-detection diagnosis.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_SkinDetectDiagnosis_Labels.
%
%
%    Description
%    -----------
%
%    Prepare text for region labels as a part of skin-detection diagnosis (see function 
%    WriteFaceVideo_SkinDetectDiagnosis_Label). 
%
%    Prepare text by assigning ...
%
%      - The characters to be used on the labels, separated into text for the selected region, the
%        the candidate regions, and the rejected regions.
%      - The X- and Y-coordinates that correspond to the position of each label.
%
%    Note: for a cleaner display, not all regions receive labels.
%       
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Prepare label text for regions %%%%%%

%%%%%% --- Prepare label text for selected region %%%%%%

%For selected region, prepare text for RGB probability and YCbCr z-score label(s).  

%If a region was selected
%Note: only one region can be selected.
if ~ isempty(RegionScores(i).SelectedRGBProb)

     %Specify text
     %Example: "P:56; YCbCr[ 0.04 -2.11 0.02]".
     %Convert to string array so that the row is considered of length 1.
     Selected_text = ...
         string([ ...
             'P:',       sprintf('%d',    RegionScores(i).SelectedRGBProb),    ... %d = As integer   
             '; YCbCr[', sprintf(' %.2f', RegionScores(i).SelectedYCbCrZ), ']' ... %.2f = To two 
                                                                               ... decimal places.
         ]);

%If no selected region    
else

    %Empty assignment because object is referenced later.
    Selected_text = [];     
end

%%%%%% --- Prepare label text for candidate regions %%%%%%         

%Note: ' WriteFaceVideo_SkinDetectDiagnosis_LabelTextCand' is a custom function located within    
%folder 'FacePulseRate'.
[Candidate_text, Candidate_idx] = ...
    WriteFaceVideo_SkinDetectDiagnosis_LabelTextCand(i, RegionRankings, RegionScores);

%%%%%% --- Prepare label text for rejected regions %%%%%%

%Note: ' WriteFaceVideo_SkinDetectDiagnosis_LabelTextReject' is a custom function located within    
%folder 'FacePulseRate'.
[Rejected_text, Rejected_FailedN_Idx, Rejected_PassedN_FailedCrSD_Idx, ...
 Rejected_PassedNandCrSD_BestIdx] = ...
    WriteFaceVideo_SkinDetectDiagnosis_LabelTextReject(i, RegionScores, RegionNPixels, ...
        RegionCrSDScores);

%%%%%% --- Combine label text across all regions %%%%%%

%Combine rows vertically.
%Then, covert to row vector for function input.
Text = [Selected_text; Candidate_text; Rejected_text]';


%%%%%% Specify centroids for pinning text labels to regions %%%%%%

%M-by-2 matrix of centroids for each text label
%Only include specified candidate regions.
%Note: empty cells are automatically disregarded in matrix construction.
TextXY = ... 
    [RegionCentroids(i).SelectedXY;  ...              
     RegionCentroids(i).CandidateXY(Candidate_idx, :); ... 
     RegionCentroids(i).RejectedXY( ...
        sort( ...
            [Rejected_FailedN_Idx; ...
             Rejected_PassedN_FailedCrSD_Idx; ...
             Rejected_PassedNandCrSD_BestIdx], ...
            'ascend' ...
        ), ...
     :)];
    
    
end %end function

