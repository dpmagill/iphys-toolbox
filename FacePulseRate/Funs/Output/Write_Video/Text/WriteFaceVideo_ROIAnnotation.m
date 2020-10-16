function [VidFrameCrop, TextBoxLowerLeftXY] = ...
             WriteFaceVideo_ROIAnnotation(VidFrame, i, ROI_Text, ROI_uint16, HasROI_TF, ...
                 VidObjWidth_uint16, TextboxFontSize, TextBoxMaxRowSize, ...
                 TextBoxMaxColSize_Annotation, TextboxFontType, ROIDiagnostic, ...
                 FaceDetectConfig, OutputConfig, UseCompiledFunctionsTF)                 
%WriteFaceVideo_ROIAnnotation   Insert ROI text annotation onto frame of output video.
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo.
%
%
%    Description
%    -----------
%
%    Insert a text annotation onto the ith frame of the output video that contains the frame index,
%    timestamp, and ROI-detection information. The text is inserted above the ROI box.
%
%    -- Default vs. detailed display --
%
%    More detailed ROI-detection information is displayed under the detailed display option
%    (OutputConfig.WriteVideoDetailedDiagnosticsTF == true) compared to the default display option.
%    The detailed display option is intended only for internal development. 
%    OutputConfig.WriteVideoDetailedDiagnosticsTF is assigned by function 
%    ValidateAndConfigure_InternalFlags. The default is false. Examples of the difference between 
%    the options are provided below.
%
%    -- Frame index and timestamp --
%
%    The text for the frame index and timestamp was assigned previously for efficiency. The text
%    was assigned by function WriteFaceVideo_TextSetup.
%
%    Note: the frame index reported here starts where timestamp = 0; for differences between this
%    index and the frame index that starts where timestamp = StartTime, see function 
%    VideoReadConfig_Setup).         
%
%    -- Detection attempt notifications --          
%
%        - [RS]: The '[RS]' characters are shown when the ROI returned by an attempted detection    
%          algorithm was rejected due to a low proportion of pixels classified as the skin. This  
%          classification was conducted by function ConfirmSkinPresent. For face-detection
%          algorithms, this classification would have been conducted within function 
%          FaceDetect_ROIValidate. For the skin-detection algorithm, this classification would have 
%          been conducted within function SkinDetect_SelectedRegionROI. Note that function 
%          ConfirmSkinPresent is also called by function ROIMeans_TakeMeans, but classifications
%          within that function do not result in '[RS]' being applied because the purpose of that
%          function is not to assign ROI detections; a classification within that function results 
%          in an annotation by function WriteFaceVideo_LowProportionSkin. Under the default display          
%          option, these characters will be displayed if any detection algorithm was rejected, even
%          if another detection algorithm was not rejected. Under the detailed display option, the
%          characters will be appended to the name of the specific detection algorithm that was 
%          rejected. Occassional misclassifications are expected; however, if the ROI, by visual 
%          inspection, does not appear to have the correct placement and if there are many apparent 
%          misclassifications, the cause could be skin-segmentation parameters that are too severe.                     
%
%        - [RE]: The '[RE]' characters are shown when the ROI returned by an attempted detection    
%          algorithm is of a profile orientation and a pair of eyes is detected in the frame. These
%          characters are only shown for face-detection algorithms that target a profile 
%          orientation. This classification was conducted by function FaceDetect_ROIValidate. These 
%          characters are only displayed under the detailed display option.
%
%        - [NR]: The '[NR]' characters are shown when no regions were available for the 
%          skin-detection algorithm attempted after the skin-segmentation step (see function 
%          SkinDetect_PartitionRegions). This complete segmentation could be valid, such as if 
%          something in the environment temporarily occluded the face. However, it could also be 
%          an indication that the skin-segmentation parameters are too severe. Note that the 
%          skin-segmentation operation conducted during the skin-detection algorithm is more severe   
%          compared to the skin segmentation conducted during the final skin segmentation, which is   
%          the skin segmentation superimposed on the output video; hence, the final skin  
%          segmentation may appear to show regions available that were not available during the  
%          skin-detection algorithm.
%
%    -- Note on modifications to text length --
%
%    If text length is changed, the value of TextBoxMaxColSize_Annotation, which limits the width
%    of the textbox, may need to be expanded. If TextBoxMaxColSize_Annotation is modified, the mex 
%    function below that inserts the annotation will need to be modified and recompiled.
%    TextBoxMaxColSize_Annotation is assigned by function WriteFaceVideo_AnnotationSetup.
%
%
%    Example Annotations
%    -------------------
%
%    -- Display under default display option --
%
%          "Frame: 1. Time: 0.1250. ROI: Frontal | [RS] [NR]" 
%    Frame index --^ Timestamp --^    Method --^      ^----^--------------------- Detection attempt  
%                                     that returned ROI. These can include        notifications            
%                                     "Frontal", "Profile", "Skin",                                                             
%                                     "Interpolated", "Specified by                  
%                                     argument", and "Ignored". In 
%                                     contrast to the detailed display
%                                     option, for simplicity, the primary,
%                                     secondary #1, and secondary #2  
%                                     face-detection algorithms are  
%                                     displayed as "Frontal", "Profile",
%                                     and "Frontal 2", respectively.                                     
%                                     When the method is "Ignored", 
%                                     "Ignored" is used rather than 
%                                     "Interpolated" although the ROI
%                                     would have been interpolated.
%                                     "Interpolated" is displayed if the
%                                     frame was skipped for efficiency or 
%                                     if no detection algorithms were
%                                     successful. "Ignored" and "Specified
%                                     by argument" are controlled by                     
%                                     arguments ROIIgnoreByArgument and
%                                     ROISpecifiedByArgument,  
%                                     respectively, which are arguments to 
%                                     function FacePulseRate.                                    
%
%    -- Display under detailed display option --
%
%          "Frame: 1. Time: 0.1250. ROI: Interpolated | Pri., Sec.#1[RS][RE], Skin[NR]" 
%    Frame index --^ Timestamp --^    Method that --^      ^-------^-- Detection methods that  
%                                     returned ROI.                    attempted detection. These 
%                                     These can include                can include "Pri.",   
%                                     "Pri.", "Sec.#1",                "Sec.#1", "Sec.#2", and  
%                                     "Sec.#2", Skin,                  "Skin". "Skipped" and 
%                                     "Interpolated",                  "Ignored" are also possible 
%                                     and "Specified by                entries, although they are 
%                                     argument".                       not detection methods but 
%                                                                      rather indications that a 
%                                                                      detection method was skipped 
%                                                                      for efficiency or specified
%                                                                      to be ignored (argument
%                                                                      "ROIIgnoreByArgument" to 
%                                                                      function FacePulseRate). If 
%                                                                      a detection method made a   
%                                                                      detection, then the name of  
%                                                                      the method will also appear    
%                                                                      to the right of '|'. If  
%                                                                      there is more than one 
%                                                                      entry, as in this example, 
%                                                                      only one method could have  
%                                                                      been successful. If the  
%                                                                      "Method of ROI" is 
%                                                                      "Interpolated", as in this 
%                                                                      example, then all detection 
%                                                                      methods that attempted 
%                                                                      detection would have been 
%                                                                      unsuccessful.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Specify text for ith frame %%%%%%

%%%%%% --- Method that determined ROI %%%%%%

%Return annotation text for method that determined ROI.

%Note: WriteFaceVideo_ROIAnnotation_ROIMethod is a custom function located within folder
%'FacePulseRate'.
Text = WriteFaceVideo_ROIAnnotation_ROIMethod(i, HasROI_TF, ROIDiagnostic, OutputConfig);    
 
%%%%%% --- Method that attempted to determine ROI %%%%%%

%Return annotation text for method that attempted to determine ROI. This text will include the
%method that actually determined the ROI (see above section) as well as methods that attempted but
%failed to determine the ROI.

%If detailed annotations enabled
if OutputConfig.WriteVideoDetailedDiagnosticsTF

    %Note: WriteFaceVideo_ROIAnnotation_DetectAttempts is a custom function located within folder
    %'FacePulseRate'.
    Text = ...
        WriteFaceVideo_ROIAnnotation_DetectAttempts(i, Text, HasROI_TF, ROIDiagnostic, ...
            FaceDetectConfig);
end

%%%%%% --- Extract text with frame index and timestamp %%%%%%

%The frame index and timestamp text were assigned by function WriteFaceVideo_TextSetup, which was  
%called by function WriteFaceVideo_AnnotationSetup. This text was assigned in  
%WriteFaceVideo_TextSetup so that vectorized operations could be use to assign the text. Otherwise,
%the current function would need to assign the text on each frame, which would be less efficient.

%Note: to revert to assigning the text on each frame, the following code could be used:
%{
%Frame number text
TextFrame = ["Frame:", sprintf("%d.", VideoReadConfig.FrameIdx(i))]; %convert to integer

%Frame timestamp text
TextTime = ["Time:", sprintf("%.4f.", VideoReadConfig.FrameTimestamp_Single(i))]; %4 decimal places

%Concatenate text
Text = ...
    join(TextFrame, ...
         TextTime, ...
         " " ... delimiter
    );
%}

%Example:
% "Frame: 237. Time: 9.9583."

%Extract frame index and timestamp text for ith frame
ROI_Text_ith = char( ROI_Text(i) );

%Text
Text = ...
    [ROI_Text_ith, ... frame index and timestamp 
     ' ',          ...
     Text];        %   text regarding detections


%%%%%% Insert text %%%%%%

%Text box background color
%Note: should match color of final ROI box border, which was inserted in function WriteFaceVideo.
BoxColor = [189, 233, 255]; %light blue

%%%%%% --- Text box position %%%%%%

%Specify lower-left [X, Y] coordinates of text box
%Position X-coordinate of text box at X-coordinate of ROI.
%Position Y-coordinate of text box at 1 pixels above top edge of ROI (note that Y-axis decreases 
%going up). The Y-coordinate position places the textbox above the border of the ROI.
TextBoxLowerLeftXY    = ROI_uint16(i, 1 : 2);  
TextBoxLowerLeftXY(2) = TextBoxLowerLeftXY(2) - 1;

%%%%%% --- Make adjustments to position of text box %%%%%%

%%%%%% >>>>>> Right of frame %%%%%%

%If right-most column of text box exceeds frame width
if TextBoxLowerLeftXY(1) + TextBoxMaxColSize_Annotation - 1 > VidObjWidth_uint16 
    
    %Move left-X-coordinate of text box left by amount right-most text box column exceeds frame 
    %width.
    TextBoxLowerLeftXY(1) = ...
        TextBoxLowerLeftXY(1) - ...
        (TextBoxLowerLeftXY(1) + TextBoxMaxColSize_Annotation - 1 - VidObjWidth_uint16);         
end  

%%%%%% >>>>>> Top of frame %%%%%%

%If highest row of text box exceeds top of frame 
if TextBoxMaxRowSize >   ... text box height
   TextBoxLowerLeftXY(2) %   lower row of text box                                             
     
    %Move lower-Y-coordinate of text box lower to accommodate height:         
    TextBoxLowerLeftXY(2) = TextBoxMaxRowSize;       
end

%%%%%% --- Crop frame %%%%%%

%Rather than send image VidFrame to function insertText or mex files, only send the portion of it
%to be occupied by the textbox. This way, once the textbox is returned, only that small area needs 
%to be assigned to VidFrame, preventing reassignment of the entire image, which is less efficient.
%Note: subtract 1 from rows and columns to be inclusive.  
VidFrameCrop = ...
    VidFrame( ... index into area corresponding to text box
        TextBoxLowerLeftXY(2) - (TextBoxMaxRowSize - 1) : TextBoxLowerLeftXY(2),          ... rows 
        TextBoxLowerLeftXY(1) : TextBoxLowerLeftXY(1) + TextBoxMaxColSize_Annotation - 1, ... cols 
        :                                                                                 ... pages
    );

%%%%%% --- Insert text to cropped frame %%%%%%

%Use compiled function
if UseCompiledFunctionsTF && strcmp(TextboxFontType, 'Consolas')
 
    %Note: the mex files are custom compiled versions of function insertText located within folder
    %'FacePulseRate'. See the code generation files (insertTextFast_ROIAnnotation13 and 
    %insertTextFast_ROIAnnotation20) for details. 
    %The mex files limit the length of characters to 125. To change, edit source code and
    %recompile.
    
    %Use the mex file that corresponds to the specified font size
    %Different mex files are used because the font size differs depending on the frame size, and 
    %font size is a compile-time constant.
    switch TextboxFontSize

        case 13

            %Cropped frame with annotation
            %29 x 550 x 3 matrix array; type uint8.
            VidFrameCrop = ...
                insertTextFast_ROIAnnotation13_mex( ...
                    VidFrameCrop, ... cropped frame; 29 x 550 x 3 matrix array, type uint8
                    Text          ... annotation text; 1 x :125 vector, type char
                );
            
        case 20

            %Cropped frame with annotation 
            %45 x 800 x 3 matrix array; type uint8.
            VidFrameCrop = ...
                insertTextFast_ROIAnnotation20_mex( ...
                    VidFrameCrop, ... cropped frame; 45 x 800 x 3 matrix array, type uint8
                    Text          ... annotation text; 1 x :125 vector, type char
                );
    end
       
%Use non-compiled function    
else   
    
    VidFrameCrop = ...
        insertText( ...
            VidFrameCrop,                ...
            [1, TextBoxMaxRowSize],      ... [X, Y] coordinates: bottom-left (as specified by 
                                         ... argument AnchorPoint) of indexed area.
            Text,                        ... Text
            'TextColor', textColor,      ... Text color
            'Font', TextboxFontType,     ... Font type
            'FontSize', TextboxFontSize, ... Font size
            'BoxOpacity', 0.5,           ... Background opacity: 1 indicates a solid color
            'BoxColor', BoxColor,        ... Box background color; note: white has been observed to  
                                         ... cause unexpected colors to appear.
            'AnchorPoint', 'LeftBottom'  ... [X, Y] coordinates position relative to text 
        ); 
end
                                                                                              

end %end function

