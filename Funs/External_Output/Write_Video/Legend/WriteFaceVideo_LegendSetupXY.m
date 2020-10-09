function textXY = ...
             WriteFaceVideo_LegendSetupXY(text, text_XLeftJustification, text_YLineSpacing, ...
                 text_YParagraphSpacing, text_YTop)
%WriteFaceVideo_LegendSetupXY    Determine X- and Y-coordinates of output video legend text.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_LegendSetup.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Determine number of lines of text %%%%%%

paragraphLength = zeros(length(text), 1);

for i = 1 : length(text)
    
    paragraphLength(i) = length(text{i});    
end

textNLines = sum(paragraphLength);


%%%%%% Determine text X-coordinates %%%%%%

XCoordinates = repmat(text_XLeftJustification, textNLines, 1);


%%%%%% Determine text Y-coordinates %%%%%%

%Implement line spacing and paragraph spacing.

YCoordinates = cumsum( repmat(text_YLineSpacing, textNLines, 1) );

ParagraphSpaceCumulative = ( 0 : (length(text) - 1) ) * text_YParagraphSpacing;


for i = 1 : length(text)
    
    if i == 1
        
        ParagraphSpacingEachLine = [];   
    end
    
    ParagraphSpacingEachLine = ...
        [ParagraphSpacingEachLine; ...
         repmat(ParagraphSpaceCumulative(i), paragraphLength(i), 1)];    %#ok<AGROW>
end

YCoordinates = YCoordinates + ParagraphSpacingEachLine + text_YTop;


%%%%%% Text Y- and X-coordinates %%%%%%

%XY-coordinates for all lines of text
%N-by-2 matrix. 

textXY = [XCoordinates, YCoordinates]; 


end %end function

