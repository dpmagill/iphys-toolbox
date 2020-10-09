function [VidFrameCrop, TextBoxUpperLeftXY] = ...
             WriteFaceVideo_PulseRate(i, PulseRate_Text, VidFrame, TextboxFontSize, ...
                 TextBoxMaxRowSize, TextBoxMaxColSize_PulseRate, TextboxFontType, ROI_uint16, ...  
                 VidObjWidth_uint16, VidObjHeight_uint16, PulseRateConfigAndData, ...
                 UseCompiledFunctionsTF)
%WriteFaceVideo_PulseRate   Insert pulse rates and related annotations for the ith frame.
%   
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo.
%
%
%    Description
%    -----------
%
%    Insert pulse rates and related annotations for the ith frame.
%
%    The annotation includes ...
%    - The externally-measured pulse rate value corresponding to the ith frame. This value would  
%      have been specified as argument PulseRateExternallyMeasured to function FacePulseRate. 
%    - Four pulse rate values from the four pulse rate algorithms, respectively.
%    - Four pulse rate values from the four pulse rate algorithms, respectively, that have been 
%      controlled for luminance variation across frames.
%    - The number of frames remaining in the pulse-rate window of which the ith frame is a member.
%
%    -- Example --  
%
%               'EM: 67; C: 68/63L G: 48/63L I: 63/53L P: 136/46L Window boundary: - 4312'
%     Externally--^      ^--Pulse-rate ^--Pulse rate ^--Pulse rate          Number of --^
%     measured pulse        algorithm.    without       with luminance      frames remaining in     
%     rate, which is                      luminance     control.            the pulse-rate window      
%     specified by                        control.                          of which the ith frame       
%     argument                                                              is a member.
%     "PulseRateExternallyMeasured"                                                                                 
%     to function                                                                                 
%     FacePulseRate.                                                                                
%
%    -- Note -- 
%
%    If text length is changed, the value of TextBoxMaxColSize_PulseRate, which limits the
%    width of the textbox, may need to be expanded. If TextBoxMaxColSize_PulseRate is modified, the 
%    mex function below that inserts the annotation will need to be modified and recompiled.
%    TextBoxMaxColSize_PulseRate is assigned by function WriteFaceVideo_AnnotationSetup.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Text box position %%%%%%

%Specify upper-left [X, Y] coordinates of text box: 

%Position X-coordinate of text box at X-coordinate of ROI.
%Position Y-coordinate of text box at 1 pixel below bottom edge of ROI: add ROI height to ROI
%upper-Y-coordinate (which pushes it 1 pixel below bottom edge of ROI). The Y-coordinate
%position places the textbox below the border of the ROI. 

TextBoxUpperLeftXY = ...
    [ROI_uint16(i, 1),                     ... X = ROI X
     ROI_uint16(i, 2) + ROI_uint16(i, 4)]; %   Y = ROI Y + ROI height


%%%%%% Make adjustments to position of text box %%%%%%

%%%%%% --- Right of frame %%%%%%

%If right-most column of text box exceeds frame width
if TextBoxUpperLeftXY(1) + TextBoxMaxColSize_PulseRate - 1 > VidObjWidth_uint16 
     
    %Move left-X-coordinate of text box left by amount right-most text box column exceeds frame 
    %width.
    TextBoxUpperLeftXY(1) = ...
        TextBoxUpperLeftXY(1) - ... move left
        (TextBoxUpperLeftXY(1) + TextBoxMaxColSize_PulseRate - 1 - VidObjWidth_uint16);         
end

%%%%%% --- Bottom of frame %%%%%%

%If lowest row of text box exceeds frame height
if TextBoxUpperLeftXY(2) + TextBoxMaxRowSize - 1 > ... lowest text box row (subtract 1 to be inclusive)
   VidObjHeight_uint16                             %   bottom of frame row
     
    %Move upper-Y-coordinate of text box higher by amount lowest text box row exceeds frame height
    TextBoxUpperLeftXY(2) = ...
        TextBoxUpperLeftXY(2) - ... move up
        (TextBoxUpperLeftXY(2) + TextBoxMaxRowSize - 1 - VidObjHeight_uint16); %by amount exceeding frame height        
end


%%%%%% Specify text %%%%%%

%%%%%% --- Pulse rate values text %%%%%%

%Note: the pulse rate value text was assigned by function WriteFaceVideo_TextSetup, which was 
%called by function WriteFaceVideo_AnnotationSetup. This text was assigned in  
%WriteFaceVideo_TextSetup so that vectorized operations could be use to assign the text. Otherwise,
%the current function would need to assign the text on each frame, which would be less efficient.

%Examples:

%Text when luminance control is enabled:
%    " C: 68/63L G: 48/63L I: 63/53L P: 136/46L"

%Text when luminance control is not enabled:
%    " C: 68 G: 48 I: 63 P: 136"

%Text when externally-measured pulse rate is included (and luminance control is enabled):
%    " EM: 67; C: 68/63L G: 48/63L I: 63/53L P: 136/46L"

%Extract pulse rate text for ith frame and convert to character array
PulseRateText_ith = char( PulseRate_Text(i) );

%%%%%% --- Window text %%%%%%

%Display number of frames remaining until next window begins.

%Frame index(es) of window-start amd window-end frames that are greater than current frame index
%If none greater (i.e., the case for the last frame), [] assigned.
%Type int32.
WindowsStartEndIdx = ...
    sort( ...
        [PulseRateConfigAndData.Block.windowsStartIdx, ...
         PulseRateConfigAndData.Block.windowsEndIdx], ...
        'ascend' ...
    );

greaterThanCurrent = WindowsStartEndIdx(WindowsStartEndIdx > i);

%The number of frames between the current frame index and the nearest window-end frame
%As greaterThanCurrent is ordered from smallest to greatest (as windowsEndIdx is ordered in this
%manner), the element in position 1 (greaterThanCurrent(1)) will correspond to the nearest
%window-end frame.
%If no frame indices available, assign empty.
if ~ isempty(greaterThanCurrent)

    windowCountDown = greaterThanCurrent(1) - i; 

else

    windowCountDown = [];
end

PulseRateWindowText = ...
    [' Window boundary: - ', sprintf('%d', windowCountDown)];
     

%%%%%% Insert text %%%%%%

%Concatenate text
Text = [PulseRateText_ith, PulseRateWindowText];

%Specify box background color
%Set to a light blue slightly lighter than color denoting skin segmentation.
BoxColor = [189, 233, 255];
    
%%%%%% --- Insert text %%%%%%

%Rather than send image WriteToVideo to function insertText or mex files, only send the portion of
%it to be occupied by the textbox. This way, once the textbox is returned, only that small area
%needs to be assigned to WriteToVideo, preventing reassignment of the entire image, which is less
%efficient.
VidFrameCrop = ...
    VidFrame( ... index into area corresponding to text box
        TextBoxUpperLeftXY(2) : TextBoxUpperLeftXY(2) + TextBoxMaxRowSize - 1,           ... rows (subtract 1 to be inclusive) 
        TextBoxUpperLeftXY(1) : TextBoxUpperLeftXY(1) + TextBoxMaxColSize_PulseRate - 1, ... cols (subtract 1 to be inclusive)
        :                                                                                ... pages
    );

%%%%%% >>>>>> Use compiled function %%%%%%

if UseCompiledFunctionsTF && strcmp(TextboxFontType, 'Consolas')
 
    %Note: the mex files are custom compiled versions of function insertText located within folder
    %'FacePulseRate'. See the code generation files (insertTextFast_PulseRate13 and 
    %insertTextFast_PulseRate20) for details. 
    
    %Use the mex file that corresponds to the specified font size
    switch TextboxFontSize

        case 13

            VidFrameCrop = ...
                insertTextFast_PulseRate13_mex( ...
                    VidFrameCrop, ... cropped frame; 29 x 575 x 3 matrix array, type uint8 
                    Text          ... annotation text; 1 x :125 vector, type char
                );
            
        case 20
            
            VidFrameCrop = ...
                insertTextFast_PulseRate20_mex( ...
                    VidFrameCrop, ... cropped frame; 45 x 850 x 3 matrix array, type uint8
                    Text          ... annotation text; 1 x :125 vector, type char
                );
    end
       
%%%%%% >>>>>> Use non-compiled function %%%%%%  

else   
    VidFrameCrop = ...
        insertText( ...
            VidFrameCrop,                ...
            [1, 1],                      ... [X, Y] coordinates: top-left of indexed area
            Text,                        ... text
            'Font', TextboxFontType,     ... font type
            'FontSize', TextboxFontSize, ... font size
            'BoxColor', BoxColor,        ... box background color; note: white has been observed to cause 
                                         ... unexpected colors to appear.
            'AnchorPoint', 'LeftTop'     ... [X, Y] coordinates position relative to text 
         ); 
end


end %end function



