function [Candidate_text, Candidate_idx] = ...
             WriteFaceVideo_SkinDetectDiagnosis_LabelTextCand(i, RegionRankings, RegionScores)
%WriteFaceVideo_SkinDetectDiagnosis_LabelTextCand    Prepare text for labels of candidate region as    
%                                                    a part of skin-detection diagnosis.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function 
%    WriteFaceVideo_SkinDetectDiagnosis_LabelText.
%
%
%    Description
%    -----------
%
%    Prepare text for region labels for a limited number of candidate region(s) as a part of 
%    skin-detection diagnosis. Prepare text for RGB probability and YCbCr z-score label(s).    
%      
%    Only affix labels to candidate regions if they have a relatively high rating or if the have a
%    relatively low rating. This permits a cleaner display. These regions are perhaps considered 
%    more important than other candidate regions because they provide closer comparison between the  
%    selected region, which would have a higher rating than all candidate regions, and the rejected  
%    region(s), which would have lower ratings than the candidate regions.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%Number of candidate regions present
NCandidates = numel(RegionRankings(i).CandidateHi2Lo);


%%%%%%% If at least one candidate region present %%%%%%

if NCandidates ~= 0

    %Assign index of candidate regions to use
    %If there are two or fewer candidate regions, specify index to display all; otherwise, specify
    %index to display the top- and bottom-ranked candidate regions. 
    
    %If one candidate region
    if NCandidates == 1 

        Candidate_idx = 1;
        
        NCandidate_idx = 1;
        
    %If two candidate regions
    elseif NCandidates == 2 
        
        Candidate_idx = 1 : 2;    

        NCandidate_idx = 2;
        
    %If three or more candidate regions
    else %NCandidates >= 3 

        Candidate_idx = ...
            [1, ...        %Index 1 == top-ranked
             NCandidates]; %Last index == bottom-ranked 
         
        NCandidate_idx = 2;         
    end                         

    %%%%%% --- RGB probability %%%%%%
    
    %Note: num2str(RegionScores(i).CandidateRGBProb(Candidate_idx)) is more concise but less 
    %efficient.
    RGBtext = ...
        char(              ... convert to characters
            split(         ... split into separate elements by specified delimiter
                sprintf(   ... convert vector of region values to concatenated string
                    "%d,", ... convert to integers, add comma delimiter, convert to type string
                    RegionScores(i).CandidateRGBProb(Candidate_idx) ...
                ), ...
                ','        ... split by this delimiter 
            ) ... 
        );

    RGBtext = RGBtext(1 : end - 1, :); %remove last element, which is just a space

    %%%%%% --- YCbCr z-scores %%%%%%    
    
    %Note: num2str(RegionScores(i).CandidateYCbCrZ(Candidate_idx, :), ' %.2f') is more concise but
    %less efficient.
    YCbCrZtext = ...          
        split(           ... Split into separate elements by specified delimiter
            sprintf(     ... Convert vector of region values to concatenated string
                "%.2f,", ... Convert to 2 decimal places, add comma delimiter, convert to 
                         ... type string.
                RegionScores(i).CandidateYCbCrZ(Candidate_idx, :) ...
            ),           ...
            ','          ... Split by this delimiter
        );     
         
    YCbCrZtext = YCbCrZtext(1 : end - 1, :); %Remove last element, which is just a space    
    
    YCbCrZtext = ... Change such that rows equal to number of regions to be displayed        
        reshape(YCbCrZtext, ...
            NCandidate_idx, ... n rows
            []              ... n columns (determined based on constraint from rows)
         ); 
         
    YCbCrZtext = ...
        char(                        ... Convert to type character
            join(YCbCrZtext, ' ', 2) ... Concatenate across columns, specified by argument '2',
                                     ... and add a space when doing so e.g., 
                                     ... ["3", "2"] -> ["3 2"]
        );
    
    %%%%%% --- Concatenate text %%%%%%
    
    %Assign a column for each chunk of text, with rows the length of regions included; then, 
    %concatenate the columns together to assign a matrix of text, with each row vector containing
    %the complete text for given region. 
    %Convert to string array so that each row is considered of length 1.

    %Example of row: "P:56; YCbCr[ 0.04 -2.11  0.02]".

    Candidate_text = ...
        string([ ...
            ... 'P:' abbreviation for probability:
            repmat('P:', NCandidate_idx, 1), ...
            ... column vector of probability values:
            RGBtext, ...
            ... '; YCbCr[' abbreviation:
            ... (query only length of rows because more than one dimension)
            repmat('; YCbCr[', NCandidate_idx, 1), ...
            ... M-by-3 matrix of Y, Cb, and Cr z-scores, to two decimal points::
            YCbCrZtext, ...
            ... YCrCb bracket suffix:
            repmat(']', NCandidate_idx, 1) ...
        ]);

    
%%%%%%% If no candidate regions %%%%%% 

else

    %Assign empty values because variables are referenced later
    Candidate_text = [];
    Candidate_idx = [];
end


end %end function

