function [Rejected_text, Rejected_FailedN_Idx, Rejected_PassedN_FailedCrSD_Idx, ...
          Rejected_PassedNandCrSD_BestIdx] = ...
             WriteFaceVideo_SkinDetectDiagnosis_LabelTextReject(i, RegionScores, RegionNPixels, ...
                 RegionCrSDScores)
%WriteFaceVideo_SkinDetectDiagnosis_LabelTextReject    Prepare text for labels of rejected region   
%                                                      as a part of skin-detection diagnosis.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function 
%    WriteFaceVideo_SkinDetectDiagnosis_LabelText.
%
%
%    Description
%    -----------
%
%    Prepare text for region labels for a limited number of rejected region(s) as a part of 
%    skin-detection diagnosis. Prepare text for RGB probability and YCbCr z-score label(s).    
%      
%    Display only pixel count if the region was rejected because of not meeting the pixel count 
%    (which is specified by SkinDetectDiagnosis.RegionNPixels, assigned in function 
%    SkinDetect_ConfigSetup). By displaying only pixel count (and no other metrics) for these 
%    regions, a cleaner display is shown; for these regions, a low pixel count is considered the
%    most relevant information. For rejected regions with passing pixel counts, display RGB 
%    probability, Y, Cb and Cr z-score label(s), as one or more these metrics would have resulted 
%    in their rejection. Finally, for ease of presentation, only show labels for regions with 
%    either the best (highest) RGB probability, best (smallest) Cb z-score, or best (smallest) Cr 
%    z-score. The metrics for the rejected regions not displayed will have less desirable scores 
%    than those displayed.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% If at least one rejected region present for ith frame %%%%%%

if ~ isempty(RegionScores(i).RejectedRGBProb)

    %%%%%% --- Filter text for cleaner display %%%%%% 
    
    %Filter text by pixel count, Cr standard deviation, YCbCr z-scores, and RGB probability.
    
    %%%%%% >>>>>> Rejected regions with low pixel counts %%%%%% 

    %Assign linear index indicating rejected regions that were not rejected due to low pixel count
    %(this is mainly for use later when combining text).
    Rejected_FailedN_Idx = find(RegionNPixels(i).RejectedLowNTF);

    %N-rejected text
    %Note: num2str(RegionNPixels(i).RejectedN(Rejected_FailedN_Idx)) is more concise but 
    %inefficient.
    if ~ isempty( RegionNPixels(i).RejectedN(Rejected_FailedN_Idx) )

        Ntext = ...
            char( ... convert to characters
                split( ... split into separate elements by specified delimiter
                    sprintf( ... convert vector of region values to concatenated string
                        "%d,", ... convert to integers, add comma delimiter, convert to type string
                        RegionNPixels(i).RejectedN(Rejected_FailedN_Idx) ...
                    ), ...
                    ',' ... split by this delimiter 
                ) ... 
            );      
        
        Ntext = Ntext(1 : end - 1, :); %remove last element, which is just a space

    else

        Ntext = [];
    end
    
    %Specify text:
    %Assign a column for each chunk of text, with rows the length of regions included; then,
    %concatenate the columns together to assign a matrix of text, with each row vector containing
    %the complete text.
    %Convert to string array so that each row is considered of length 1.

    %Example of row: "N: 6".

    Rejected_FailedN_text = ...
        string([ ...
            ... 'N:' abbreviation for probability:
            repmat('N: ', length(Rejected_FailedN_Idx), 1), ...
            ... column vector of pixel counts:
            Ntext ...
        ]);

    %%%%%% >>>>>> Rejected regions with passing pixel counts %%%%%%

    %Assign linear index indicating rejected regions that were not rejected due to low pixel count.
    Rejected_PassedN_Idx = find(~ RegionNPixels(i).RejectedLowNTF);

    %Rejected regions with passing pixel counts but non-passing Cr standard deviations:

    if ~ isempty(RegionCrSDScores(i).RejectedCrSDLinIdx)

        %Assign linear index indicating rejected regions that were not rejected due to low pixel
        %count but rejected due to Cr SD. 
        Rejected_PassedN_FailedCrSD_Idx = ...
            intersect(Rejected_PassedN_Idx, RegionCrSDScores(i).RejectedCrSDLinIdx);

        if ~ isempty(Rejected_PassedN_FailedCrSD_Idx)

            %Extract the standard deviations from RegionCrSDScores(i).RejectedCrSD that correspond 
            %to the standard deviations to display (as specified by the linear index
            %Rejected_PassedN_FailedCrSD_Idx).
            CrSDToDisplay = ...
                RegionCrSDScores(i).RejectedCrSD( ...
                    ismember(RegionCrSDScores(i).RejectedCrSDLinIdx, ...
                             Rejected_PassedN_FailedCrSD_Idx) ...
                );

            %Specify text:
            %Assign a column for each chunk of text, with rows the length of regions included; 
            %then, concatenate the columns together to assign a matrix of text, with each row 
            %vector containing the complete text. 
            %Convert to string array so that each row is considered of length 1.

            %Example of row: "Cr SD: 6".

            Rejected_FailedCrSD_text = ...
                string([ ...
                    ... 'N:' abbreviation for probability:
                    repmat('Cr SD: ', length(Rejected_PassedN_FailedCrSD_Idx), 1), ...
                    ... column vector of pixel counts:
                    num2str(CrSDToDisplay) ...
                ]);
        else

            Rejected_FailedCrSD_text = [];
        end

    else

        Rejected_FailedCrSD_text = [];
        Rejected_PassedN_FailedCrSD_Idx = [];           
    end

    %Rejected regions with passing pixel counts and passing Cr standard deviations:

    %Assign linear index indicating rejected regions that were not rejected due to low pixel count
    %or Cr SD.
    %Note: equivalent to Rejected_PassedNandCrSD_Idx = ...
    %      setdiff(Rejected_PassedN_Idx, RegionCrSDScores(i).RejectedCrSDLinIdx);                  
    Rejected_PassedNandCrSD_Idx = ...
    Rejected_PassedN_Idx(~ ismember(Rejected_PassedN_Idx, RegionCrSDScores(i).RejectedCrSDLinIdx));   

    %For ease of presentation, of these regions, only use regions with either the highest RGB 
    %probability, smallest Cb z-score, or smallest Cr z-score, which, for convenience, will be  
    %referred to as the "best" rejected regions. Determine the indexes of these regions.
    [~, RejectedRGBProb_PassedNandCrSD_MaxPIdx] = ...
        max(RegionScores(i).RejectedRGBProb(Rejected_PassedNandCrSD_Idx));
    [~, RejectedCbCrZ_PassedNandCrSD_MinCbIdx]  = ...
        min(abs( RegionScores(i).RejectedYCbCrZ(Rejected_PassedNandCrSD_Idx, 2) ));
    [~, RejectedCbCrZ_PassedNandCrSD_MinCrIdx]  = ...
        min(abs( RegionScores(i).RejectedYCbCrZ(Rejected_PassedNandCrSD_Idx, 3) ));

    %Combine indices of best N-passed regions
    %For ease of use with corresponding data, convert the indices of these regions according to
    %all rejected regions (RegionScores(i).RejectedRGBProb and RegionScores(i).RejectedYCbCrZ) 
    %rather than out of the rejected regions that passed the N threshold.
    %Also, find unique regions in case a region was best for multiple metrics.
    Rejected_PassedNandCrSD_BestIdx = ...
        Rejected_PassedNandCrSD_Idx( ...
            unique( ...
                [RejectedRGBProb_PassedNandCrSD_MaxPIdx, ...
                 RejectedCbCrZ_PassedNandCrSD_MinCbIdx, ...
                 RejectedCbCrZ_PassedNandCrSD_MinCrIdx] ...
            ) ...                   
        );     
    
    %Number of regions to display
    NRejected_PassedNandCrSD_BestIdx = length(Rejected_PassedNandCrSD_BestIdx);   
            
    %%%%%% --- Concatenate filtered text %%%%%% 
    
    %If at least one rejected region to display after filtering
    if NRejected_PassedNandCrSD_BestIdx ~= 0
    
        %%%%%% >>>>>> RGB probability %%%%%% 
        
        %RGB-rejected text
        %Note: num2str(RegionScores(i).RejectedRGBProb(Rejected_PassedNandCrSD_BestIdx)) is more
        %concise but inefficient. 
        RGBtext = ...
            char(              ... convert to characters
                split(         ... split into separate elements by specified delimiter
                    sprintf(   ... convert vector of region values to concatenated string
                        "%d,", ... convert to integers, add comma delimiter, convert to type string
                        RegionScores(i).RejectedRGBProb(Rejected_PassedNandCrSD_BestIdx) ...
                    ), ...
                    ','        ... split by this delimiter 
                ) ... 
            );

        RGBtext = RGBtext(1 : end - 1, :); %remove last element, which is just a space
        
        %%%%%% >>>>>> YCbCr z-score %%%%%%         
        
        %YCbCrZ-rejected text
        %Note: num2str(RegionScores(i).RejectedYCbCrZ(Rejected_PassedNandCrSD_BestIdx, :), ' %.2f') 
        %is more concise but inefficient.
        YCbCrZtext = ...          
                split(           ... Split into separate strings by specified delimiter
                    sprintf(     ... Convert vector of region values to concatenated string
                        "%.2f,", ... Convert to 2 decimal places, add comma delimiter, convert to 
                                 ... type string.
                        RegionScores(i).RejectedYCbCrZ(Rejected_PassedNandCrSD_BestIdx, :) ...
                    ), ...
                    ','          ... Split by this delimiter 
                ); 

        YCbCrZtext = YCbCrZtext(1 : end - 1, :); %remove last element, which is just a space

        YCbCrZtext = ... change such that number of rows equal to number of regions        
                reshape(YCbCrZtext, ...
                    NRejected_PassedNandCrSD_BestIdx, ... n rows
                    [] ... n columns (determined based on constraint from rows)
                 ); 

        YCbCrZtext = ... 
            char( ... convert to type character
                join(YCbCrZtext, ' ', 2) ... concatenate across columns, specified by argument '2',
                                         ... and add a space when doing so e.g., 
                                         ... ["3", "2"] -> ["3 2"]
            ); 

    else

        RGBtext    = [];
        YCbCrZtext = [];
    end

    %%%%%% >>>>>> All criteria %%%%%%
    
    %Specify text:
    %Assign a column for each chunk of text, with rows the length of regions included; then,
    %concatenate the columns together to assign a matrix of text, with each row vector containing 
    %the complete text for a given region. 
    %Convert to string array so that each row is considered of length 1.

    %Example of matrix 
    %(Not necessarily always in order shown in example. Also, there may be fewer than three  
    %regions if a region was best on multiple metrics or if there are fewer than three rejected 
    %regions).
    %    ["P:100; YCbCr[1.13 2.13 -4.50]";    (best RGB probability)
    %     "P: 62; YCbCr[0.13 1.19 -6.51]";    (best Cb z-score)   
    %     "P: 54; YCbCr[-0.13 2.43 -4.02]"]   (best Cr z-score)

    Rejected_PassedNandCrSD_Best_text = ...
        string([ ...
            ... 'P:' repeated to length of probability values:
            repmat('P:', NRejected_PassedNandCrSD_BestIdx, 1), ...
            ... vector of probability values:
            RGBtext, ...
            ... '; YCbCr[' repeated to length of YCbCr z-scores values:
            repmat('; YCbCr[', NRejected_PassedNandCrSD_BestIdx, 1), ... 
            ... M-by-2 matrix of Cb and Cr z-scores, to two decimal points:
            YCbCrZtext, ... 
            ... end bracket repeated to length of YCbCr z-scores values:
            repmat(']', NRejected_PassedNandCrSD_BestIdx, 1) ...
        ]);

    %Concatenate text of all rejected regions:

    %Preallocate string array to hold text of failed-N and best passed-N rejected regions
    %Number of rows equals the highest linear index.
    Rejected_text = ... 
        strings(...
            max( ...
                [Rejected_FailedN_Idx; ...
                Rejected_PassedN_FailedCrSD_Idx; ... 
                Rejected_PassedNandCrSD_BestIdx] ...
            ), ...
            1 ...
        );

    %Assign text in order of indices in RegionNPixels(i) and RegionScores(i)
    Rejected_text(Rejected_FailedN_Idx)            = Rejected_FailedN_text; %assign text
    Rejected_text(Rejected_PassedN_FailedCrSD_Idx) = Rejected_FailedCrSD_text; %assign text
    Rejected_text(Rejected_PassedNandCrSD_BestIdx) = Rejected_PassedNandCrSD_Best_text; %assign text

    %Remove empty rows
    %(Because length of string array based up maximum index rather than the length of indices).
    Rejected_text = Rejected_text(Rejected_text ~= "");

    
%%%%%% If no rejected regions present for ith frame %%%%%% 

else    

    %Assign empty variables because variables are referenced later.
    
    Rejected_text = [];
    Rejected_FailedN_Idx = [];
    Rejected_PassedN_FailedCrSD_Idx = [];
    Rejected_PassedNandCrSD_BestIdx = [];       
end


end %end function

