function [legendText_PixelRGB, legendText_PixelLinIdx, legendBoxRowsIdx, legendBoxColsIdx, ...
          LegendSupportedTF] = ...
             WriteFaceVideo_LegendSetup(LegendVersion1NotAssignedTF, VidObjWidth, VidObjHeight, ...
                 RegionNThreshold, HasROI_TF, SkinSegmentConfig, PulseRateConfigAndData, ...
                 FaceDetectConfig, SkinDetectConfig, OutputConfig)                                                  
%WriteFaceVideo_LegendSetup   Prepare the text for the legend in the output video.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo.
%
%
%    Description
%    -----------
%
%    Prepare the text for the legend in the output video.
%
%    Two versions of the legend are assigned depending on the value of LegendVersion1NotAssignedTF.    
%    There is only a small difference in text assigned between versions. This difference is due to
%    different text assigned by function WriteFaceVideo_LegendSetup. See the note in function 
%    WriteFaceVideo. 
%
%    Also create the pixels values of the legend text and a corresponding index that matches the
%    frames in the output video. Repeating text creation operations (e.g., calculating glyphs,  
%    checking for the availability of fonts on the system, etc.), such as those conducted by Matlab  
%    function insertText, for legend text is not needed for each frame because this text and its  
%    position are contant across frames. To avoid the repetition of these operations, which are 
%    quite time-consuming, determine the pixel values and their corresponding index so that they  
%    can be reused on each frame to assign the text. Compared to assigning text by calling function   
%    insertText for each frame, this procedure has been observed to reduce 20 minutes of processing   
%    time for each 1 minute of video output written. As two versions of the text are needed, the
%    current function will be called two times. The pixel values and corresponding index produced
%    will be reused on each frame for which the legend version remains the same.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Function Validation %%%%%%

%A legend is only used for frames with dimensions of 1920 x 1080 or 1280 x 720 and in landscape,
%not portrait, orientation. This is because characteristics of the legend need to be customized
%according to these properties. 

%Regarding size, a font size that is neither too small (for legibility) nor too large (to conserve
%screen space) needs to be specified. Additionally, the width of the legend box needs to align with 
%the width of a line of text, which is dependent on font size; however, it is difficult to 
%anticipate the width of a line of text based upon the font size. However, the height of the legend 
%box can be anticipated because the XY position of text, which is known, is the main driver of 
%legend box height.

%Regarding aspect ratio, the dimenions of a legend box for a frame with a larger width than height
%will need to be different for a frame with a larger height than width. Additionally, the width of 
%each line of text will need to be adjusted by changing the number of words per line.

%Legend text is currently supported only for other frame sizes of 1920 x 1080 and 1280 x 720.
LegendSupportedTF = ...
    (VidObjWidth == 1920 && VidObjHeight == 1080) || ...
    (VidObjWidth == 1280 && VidObjHeight == 720);
    
%Frame dimensions not supported for legend
%Assign empty output values and exit function.
if ~ LegendSupportedTF

    %Assign empty output as input to other functions.
    legendText_PixelRGB = [];
    legendText_PixelLinIdx = [];
    legendBoxRowsIdx = [];
    legendBoxColsIdx = [];

    %Display warning message on command window
    %Indented to appear nested under notification message indicating start of video writing.
    warning( ...
        ['Output video legend not supported for these frame dimensions or orientation. Legend' ... 
         ' will not be inserted into output video. Supported frame dimensions include 1920 x' ...
         ' 1080 and 1280 x 720. Landscape, but not portrait, orientation is supported.' ] ... 
    );
    
    %Exit function
    return
end


%%%%%% Specify legend text %%%%%%

%Note: 'WriteFaceVideo_LegendSetupText' is a custom function located within folder 'FacePulseRate'.
text = ...
    WriteFaceVideo_LegendSetupText(LegendVersion1NotAssignedTF, RegionNThreshold, HasROI_TF, ...
        SkinSegmentConfig, FaceDetectConfig, SkinDetectConfig, PulseRateConfigAndData, ...
        OutputConfig);
             

%%%%%% Specify left-justification and line and paragraph spacing %%%%%%

% - text_XLeftJustification specifies the left-justification to be applied to all lines of text.
% - text_YLineSpacing specifies the line spacing to be applied to all lines of text. 
% - text_YParagraphSpacing specifies the paragraph spacing to be applied to all sections of text.   
% - text_YTop specifies the vertical location to start the text.
% - Other variables are determined based upon the values of the above variables.

%Specify  according to frame size
if VidObjWidth == 1280 && VidObjHeight == 720
    
    %Text X-coordinates:
    
    text_XLeftJustification = 3; 
    
    %Text Y-coordinates:
    
    text_YTop = 4;
    
    %If detailed diagnostics enabled
    if OutputConfig.WriteVideoDetailedDiagnosticsTF

        text_YLineSpacing = 8;
        text_YParagraphSpacing = 8;
        
    else
        
        text_YLineSpacing = 12;
        text_YParagraphSpacing = 11;        
    end 

elseif VidObjWidth == 1920 && VidObjHeight == 1080

    %Text X-coordinates:
    
    text_XLeftJustification = 5; 
    
    %Text Y-coordinates:
    
    text_YTop = 5;
    
    %If detailed diagnostics enabled
    if OutputConfig.WriteVideoDetailedDiagnosticsTF 
        
        text_YLineSpacing = 13;
        text_YParagraphSpacing = 11; 
        
    else
        
        text_YLineSpacing = 18;
        text_YParagraphSpacing = 15;               
    end
     
end


%%%%%% Determine X- and Y-coordinates of text based upon specifications %%%%%%

%Note: 'WriteFaceVideo_LegendSetupXY' is a custom function located within folder 'FacePulseRate'.
textXY = ...
    WriteFaceVideo_LegendSetupXY(text, text_XLeftJustification, text_YLineSpacing, ...
        text_YParagraphSpacing, text_YTop);
         

%%%%%% Specify legend box dimensions %%%%%%

%Specify legend box dimensions.
% - The height and width are set according to the space occupied by text. 
% - The width probably requires visual inspection to determine.
% - The height is set to be a given length of pixels below the maximum Y-coordinate specified for 
%   the text. 
%These dimension variables are also supplied to function WriteFaceVideo so that it can insert the
%legend box on each frame.

%Specify legend box dimensions according to frame size
if VidObjWidth == 1280 && VidObjHeight == 720
 
    %If the detailed diagnostics are shown 
    if OutputConfig.WriteVideoDetailedDiagnosticsTF    
    
        legendBoxWidth = 342;
        
    else
        
        %Use a larger width here, althought less text is displayed, because a larger font is used
        %(see function WriteFaceVideo_LegendSetupTextStore).
        legendBoxWidth = 415;
    end
    
    legendBoxHeight = ...
        min( ...
            720,               ... maximum height
            textXY(end, 2) + 9 ... length after text length  
        );

elseif VidObjWidth == 1920 && VidObjHeight == 1080

    legendBoxWidth = 478;
    
    legendBoxHeight = ...
        min( ...
            1080,               ... maximum height
            textXY(end, 2) + 15 ... length after text length
        );
end

%Legend index for use in function WriteFaceVideo
%Specify as type uint16 for faster evaluation where used.
legendBoxRowsIdx = uint16(1 : legendBoxHeight);
legendBoxColsIdx = uint16(1 : legendBoxWidth); 


%%%%%% Store legend pixels and corresponding index %%%%%%

%Store the pixels of legend text and a corresponding index for insertion by function 
%WriteFaceVideo.

%Note: WriteFaceVideo_LegendSetupTextStore is a custom function located within folder 
%'FacePulseRate'.
[legendText_PixelLinIdx, legendText_PixelRGB] = ...
    WriteFaceVideo_LegendSetupTextStore(text, textXY, legendBoxWidth, legendBoxHeight, ...
        VidObjHeight, VidObjWidth, OutputConfig);


end %end function

