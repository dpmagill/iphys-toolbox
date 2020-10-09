function [textColor, BoxColor] = ...
             WriteFaceVideo_SkinDetectDiagnosis_LabelColors(i, RegionBoundaries, ...
                 Candidate_text, Rejected_text)
%WriteFaceVideo_SkinDetectDiagnosis_LabelColors   Specify colors for region labels as a part of  
%                                                 skin-detection diagnosis.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_SkinDetectDiagnosis_Labels.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Specify colors for text labels %%%%%%

%Assign matrix, textColor, to specify colors of text
%The colors should correspond to the colors of boundaries, as specified in function 
%WriteFaceVideo_SkinDetectDiagnosis.
%The number of rows is equal to the number regions for which text will be displayed.
%Three columns, for R, G, and B, respectively. 

%%%%%% --- Selected region %%%%%%

%Note: Number of rows is number of selected regions (which will either be 0 (none) or 1).

if isempty(RegionBoundaries(i).SelectedLinIdx)

    Selected_text_length = 0;

else

    Selected_text_length = 1;        
end

textColor = ...
    repmat([0, 255, 0], ... green
        Selected_text_length, 1); 

%%%%%% --- Candidate regions %%%%%%    
    
%Vertically concatenate RGB row(s) for text of the candidate region(s)
%Number of rows is number of candidate regions for which text is displayed, which can be 0 (none).
textColor = ...
    [textColor; ...
     repmat([255, 255, 0], ... yellow
         length(Candidate_text), 1) ...
    ];

%%%%%% --- Rejected regions %%%%%% 

%Vertically concatenate RGB row(s) for text of the rejected region(s)
%Number of rows is number of rejected regions for which text is displayed, which can be 0 (none).
textColor = ...
    [textColor; ...
     repmat([255, 75, 255], ... magenta
         length(Rejected_text), 1) ...
    ];


%%%%%% Specify box background color %%%%%%   

BoxColor = [0, 0, 0]; %black


end %end function

