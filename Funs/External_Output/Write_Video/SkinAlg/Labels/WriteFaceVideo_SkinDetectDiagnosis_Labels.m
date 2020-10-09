function VidFrame = ...
             WriteFaceVideo_SkinDetectDiagnosis_Labels(VidFrame, i, RegionScores_single, ...
                 RegionRankings_single, RegionNPixels_uint32, RegionCrSDScores_single, ...
                 RegionCentroids_int16, RegionBoundaries, bulletpointRadius, ... 
                 VidObjHeight_uint16, VidObjWidth_uint16, FontSize, UseCompiledFunctionsTF)                        
%WriteFaceVideo_SkinDetectDiagnosis_Labels   Insert labels for regions as a part of skin-detection 
%                                            diagnosis.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_SkinDetectDiagnosis.
%
%
%    Description
%    -----------
%
%    Prepare labels for certain regions that were used in the skin-detection algorithm (see 
%    function SkinDetect). These labels will be used as a part of the skin-detection diagnosis 
%    annotations for the output video (see function WriteFaceVideo_SkinDetectDiagnosis). The text 
%    includes values from criteria used in the skin-detection algorithm. These criteria include 
%    pixel count; standard deviation of the Cr color channels; z-scores from the Y, Cb, and Cr
%    color channels; and probability values from the R, G, and B color channels.
%
%    Prepare labels by assigning ...
%
%      - The characters to be used
%      - The colors for the text and the text labels 
%      - Bullet points for each label
%
%    For a cleaner display, not all regions receive labels.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.  


%%%%%% Insert text for each region label %%%%%%

%%%%%% --- Prepare text for each region label %%%%%%

%Note: 'WriteFaceVideo_SkinDetectDiagnosis_TextArgs' is a custom function located within   
%folder 'FacePulseRate'.    
[Text, TextXY, Candidate_text, Rejected_text] = ...
    WriteFaceVideo_SkinDetectDiagnosis_LabelText(i, RegionScores_single, ...
        RegionRankings_single, RegionNPixels_uint32, RegionCrSDScores_single, ...
        RegionCentroids_int16);
    
%%%%%% --- Prepare text colors for each region label %%%%%%       

%Note: WriteFaceVideo_SkinDetectDiagnosis_TextColors is a custom function located within folder
%'FacePulseRate'.
[textColor, BoxColor] = ...
    WriteFaceVideo_SkinDetectDiagnosis_LabelColors(i, RegionBoundaries, Candidate_text, ...
        Rejected_text);        

%%%%%% --- Insert text for each region label %%%%%%    
    
%Use compiled version of function insertText if platform is Windows
if UseCompiledFunctionsTF

    %Convert string array to cell array for compatibility with compiled function 
    TextCell = cell( length(Text), 1 );

    for j = 1 : length(Text)

        TextCell(j) = { char( Text(j) ) };
    end

    %Note: the mex files are custom compiled versions of function insertText located within
    %folder 'FacePulseRate'. See the code generation files (insertTextFast_Font13LT and 
    %insertTextFast_Font16LT) for details. 

    %For text of font size 13
    if FontSize == 13

        %Compiled version of function insertText
        VidFrame = ...
            insertTextFast_Font13LT_mex(VidFrame, TextXY, TextCell, textColor, BoxColor);
    end

    %For text of font size 16
    if FontSize == 16

        %Compiled version of function insertText           
        VidFrame = ...
            insertTextFast_Font16LT_mex(VidFrame, TextXY, TextCell, textColor, BoxColor);
    end

%Use uncompiled function
else

    %Insert text labels
    VidFrame = ...
        insertText(VidFrame,        ... Specify image where text annotation inserted
            TextXY,                 ... [X, Y] coordinates for M regions: M-by-2 matrix
            Text,                   ... Text for M regions: M-by-1 string array
            'TextColor', textColor, ... Colors for M regions:  M-by-3 matrix
            'FontSize', FontSize,   ... Font size
            'BoxOpacity', 0.5,      ... Background opacity: 1 indicates a solid color
            'BoxColor', BoxColor);  %   Note: white has been observed to cause unexpected
                                    %   colors to appear.
end


%%%%%% Insert bullet points for each region label %%%%%%

%%%%%% --- Prepare bullet points %%%%%%

%Note: WriteFaceVideo_SkinDetectDiagnosis_LabelBullets is a custom function located within folder
%'FacePulseRate'.
[FrameCropped_BulletPoints, BulletPointsRowMin, BulletPointsRowMax, BulletPointsColMin, ...
 BulletPointsColMax] = ...
    WriteFaceVideo_SkinDetectDiagnosis_LabelBullets(VidFrame, TextXY, bulletpointRadius, ...
        VidObjHeight_uint16, VidObjWidth_uint16, UseCompiledFunctionsTF);
        
%%%%%% --- Insert bullet points %%%%%%    
    
%The insertion of bullet points is conducted outside of function 
%WriteFaceVideo_SkinDetectDiagnosis_LabelBullets so that only a portion of VidFrame needs to be
%reassigned.

%Insert cropped frame with shapes into original-size frame:
%Type uint8.
VidFrame( ...
     BulletPointsRowMin : BulletPointsRowMax, ... rows
     BulletPointsColMin : BulletPointsColMax, ... columns
     :                                        ... pages                                                                                     ...
) = FrameCropped_BulletPoints;


end %end function

