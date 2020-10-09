function [legendText_PixelLinIdx, legendText_PixelRGB] = ...
             WriteFaceVideo_LegendSetupTextStore(text, textXY, legendBoxWidth, legendBoxHeight, ...
                VidObjHeight, VidObjWidth, OutputConfig)               
%WriteFaceVideo_LegendSetupTextStore   Store legend text as pixels and a corresponding index to be
%                                      inserted by function WriteFaceVideo.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_LegendSetup.
%
%
%    Description
%    -----------
%
%    Store legend text as pixels and a corresponding index to be inserted by function 
%    WriteFaceVideo.
%                                      
%    Repeating text creation operations (e.g., calculating glyphs, checking for the availability of  
%    fonts on the system, etc.), such as those conducted by Matlab function insertText, for legend   
%    text is not needed for each frame because this text and its position are contant across   
%    frames. To avoid the repetition of these operations, which are quite time-consuming, determine 
%    the pixel values and their corresponding index so that they can be reused on each frame to 
%    assign the text. Compared to assigning text by calling function insertText for each frame,   
%    this procedure has been observed to reduce 20 minutes of processing time for each 1 minute of   
%    video output written.
%    
%    The legend text, in the specified color, is set against a representative background because 
%    the edges of the text take on the color of the background. In this case, the background is  
%    white with a partially transparent filled gray box set on top of it. The white background is  
%    used to replicate a bright background and the gray box replicates the gray legend box.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Insert white background %%%%%%

%Assign blank (white) image as a canvas for inserting the legend box and legend text.
%The size of a video frame is used so that a logical index, assigned later, will match the 
%dimensions of the frames on the output video.

blankWhite = repmat( uint8(255), VidObjHeight, VidObjWidth );


%%%%%% Insert partially transparent gray background %%%%%%

%Insert legend box on canvas
%X- and Y-coordinates are set at (1, 1), which places box at top-left of image.
blankShape = ...
    insertShape(blankWhite,                      ... Specify image where shape annotation inserted
        'FilledRectangle',                       ... Shape
        [1, 1, legendBoxWidth, legendBoxHeight], ... [X, Y, width, height] (X and Y denote 
                                                 ... upper-left-hand corner).
        'Color', 'black',                        ... Shape color
        'Opacity', .5);                          %   Opacity  

    
%%%%%% Insert text on background %%%%%%
    
%Specify font for legend
if ismember( 'Consolas Bold', listTrueTypeFonts() ) %if 'Consolas Bold' available on system

    legendFont = 'Consolas Bold'; 

%Otherwise, use 'Courier', under the assumption it is available across system platforms
else 

    legendFont = 'Courier';
end    
 
%Specify font size for legend
%Specify depending on frame size.
if VidObjWidth == 1280 && VidObjHeight == 720
    
    %Use a larger font if the detailed diagnostics are not shown 
    if OutputConfig.WriteVideoDetailedDiagnosticsTF
           
        FontSize = 9; %at this resolution, text will be fuzzy below this font size
        
    else
        
        FontSize = 10;        
    end
    
elseif VidObjWidth == 1920 && VidObjHeight == 1080

    FontSize = 12;   
end

%Concatenate text across paragraphs (remove cells indicating paragraphs)
for i = 1 : length(text)
    
    if i == 1  
        
       textConcatenated = []; 
    end
    
    textConcatenated = [textConcatenated, text{i}]; %#ok<AGROW>
end

%Insert legend text on canvas
blankText = ...
    insertText(blankShape,           ... specify image (canvas) where annotation is to be inserted
        textXY,                      ... [X, Y] coordinates of lines of text
        textConcatenated,            ... legend text (cell array)
        'Font', legendFont,          ... specify text font 
        'TextColor',  'white',       ... text color
        'BoxOpacity', 0,             ... 0 denotes fully transparent background color of text
        'AnchorPoint', 'LeftCenter', ... position of [X, Y] coordinates relative to text 
        'FontSize', FontSize         ... font size
    );


%%%%%% Segment text pixels from background %%%%%%

%Segment canvas to leave only text against black background
% - Change to 0 pixels below RGB = [127, 127, 127] (gray), which is the background color of the  
%   legend box as inserted by the insertShape function.
% - Change to 0 pixels outside of textbox.

%Note: built-in scaler expansion permits 127 to be used in place of repmat(127, size(blankText)),
%but the current usage is used for clarity.

blankText(blankText <= repmat(127, size(blankText))) = 0; 
blankText( (legendBoxHeight + 1) : VidObjHeight, :, :) = 0;
blankText(:, (legendBoxWidth + 1) : VidObjWidth, :) = 0;


%%%%% Produce index to correspond to extracted text pixels %%%%%%

%Determine linear index that corresponds to pixels of text (not of the background)
% - A linear index is used in place of a logical index to reduce size (as most of the logical 
%   values are 0) because a small size may make the variable more efficient in the loop in which it 
%   will be used (in function WriteFaceVideo).
% - To reduce size, the linear index is converted to uint32 (from the default double).
%Note: built-in scaler expansion permits 0 to be used in place of repmat(0, size(blankText)), so 
%the current usage is only for clarity.

legendText_PixelLinIdx = ...
    uint32( find( blankText > repmat(0, size(blankText)) ) ); %#ok<REPMAT>


%%%%%% Extract text pixels %%%%%%

%Extract pixels corresponding to text and assign to vector.
%The corresponding logical index is used during the writing of the output video to assign the 
%pixels to the corresponding coordinates.

legendText_PixelRGB = blankText(legendText_PixelLinIdx);
 

end %end function

