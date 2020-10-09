function [TextboxFontType, TextboxFontSize, TextBoxMaxRowSize, TextBoxMaxColSize_Annotation, ...
          TextBoxMaxColSize_PulseRate, ROI_Text, PulseRate_Text, bulletpointRadius, ...
          ViolaJonesMinDim] = ...
             WriteFaceVideo_AnnotationSetup(VideoReadConfig, VidObjWidth_uint16, ...
                 VidObjHeight_uint16, PulseRateConfigAndData, ROIGeneralConfig, FaceDetectConfig)                                                                               
%WriteFaceVideo_AnnotationSetup   Specify formatting to use for annotations in output video.
%   
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo.
%
%
%    Description
%    -----------
%
%    Set format of annotations in output video for the following:
%    - Text box size.
%    - Text box font type and font size.
%    - Size of bullet points for skin-detection diagnostics text.
%    - Specify text for ROI and pulse rate annotations.
%    - Specifications of text and lines showing the minimum size of ROIs returned by the 
%      Viola-Jones detectors, which are used in the face-detection algorithms.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Specify arguments used for text boxes %%%%%% 

%Specify arguments used for textboxes inserted by functions WriteFaceVideo_ROIAnnotation and 
%WriteFaceVideo_PulseRate.

%%%%%% --- Text box font type %%%%%%

%Specify annotation font type for annotations appearing on ROI box
if ismember('Consolas Bold', listTrueTypeFonts) %if 'Consolas Bold' available on system

    TextboxFontType = 'Consolas'; 

%Otherwise, use 'Courier', under the assumption it is available across system platforms
else 

    TextboxFontType = 'Courier';
end 

%%%%%% --- Text box font size and dimensions %%%%%%

%The values are specified for two purposes:

%(1) To adjust the position of the text boxes in case the initial position of the text box exceeds
%    the frame dimensions. For both functions WriteFaceVideo_ROIAnnotation and 
%    WriteFaceVideo_PulseRate, this would occur if the ROI is near the right edge of the frame as 
%    the text box is left-justified at the ROI box. For function WriteFaceVideo_ROIAnnotation, 
%    this would also occur if the ROI is near the top of the frame as the text box is inserted 
%    above the ROI. For function WriteFaceVideo_PulseRate, this would also occur if the ROI is 
%    near the bottom of the frame as the text box is inserted below the ROI. 

%(2) To optimize the speed of functions WriteFaceVideo_ROIAnnotation and WriteFaceVideo_PulseRate.
%    To optimize speed by reducing assignment, only the approximate area of frame to be occupied by  
%    the text box is modified. The approximate area is determined by these values.

%If the font size specified here is modified or if the characters of text within function
%WriteFaceVideo_ROIAnnotation or function WriteFaceVideo_PulseRate is modified, changes to the 
%values specified here may need to be changed. Details are provided below.

%Specify depending on frame size.
if VidObjWidth_uint16 <= 1280 || VidObjHeight_uint16 <= 720

    %Text box font size
    %Note: if value of TextboxFontSize is changed, values of TextBoxMaxRowSize, 
    %TextBoxMaxColSize_Annotation, and TextBoxMaxColSize_PulseRate should also be changed. These
    %values need to be determined manually (e.g., measuring the pixel height and width of the text
    %after the change).
    TextboxFontSize = 13; %for default font, use 16
    
    %Maximum text box row size
    %Only needs to be modified if TextboxFontSize modified.
    %Specify type uint16 for faster evaluation where used.
    TextBoxMaxRowSize = uint16(29);
    
    %Maximum text box column size: function WriteFaceVideo_ROIAnnotation
    %Note: if the text characters changed in function WriteFaceVideo_ROIAnnotation, 
    %TextBoxMaxColSize_Annotation should also be changed. This value needs to be determined 
    %manually (e.g., measuring the pixel width of the text after the change).
    %Specify type uint16 for faster evaluation where used.
    TextBoxMaxColSize_Annotation = uint16(550);
    
    %Maximum text box column size: function WriteFaceVideo_PulseRate
    %Note: if the text characters changed in function WriteFaceVideo_PulseRate, 
    %TextBoxMaxColSize_PulseRate should also be changed. This value needs to be determined 
    %manually (e.g., measuring the pixel width of the text after the change).
    %Specify type uint16 for faster evaluation where used.
    TextBoxMaxColSize_PulseRate = uint16(575);

else
 
    %Text box font size
    %Note: if value of TextboxFontSize is changed, values of TextBoxMaxRowSize, 
    %TextBoxMaxColSize_Annotation, and TextBoxMaxColSize_PulseRate should also be changed. These
    %values need to be determined manually (e.g., measuring the pixel height and width of the text
    %after the change).
    TextboxFontSize = 20; %for default font, use 24  
    
    %Maximum text box row size
    %Only needs to be modified if TextboxFontSize modified.
    %Specify type uint16 for faster evaluation where used.
    TextBoxMaxRowSize = uint16(45);
    
    %Maximum text box column size: function WriteFaceVideo_ROIAnnotation
    %Note: if the text characters changed in function WriteFaceVideo_ROIAnnotation, 
    %TextBoxMaxColSize_Annotation should also be changed. This value needs to be determined 
    %manually (e.g., measuring the pixel width of the text after the change).
    %Specify type uint16 for faster evaluation where used.
    TextBoxMaxColSize_Annotation = uint16(800);    
    
    %Maximum text box column size: function WriteFaceVideo_PulseRate
    %Note: if the text characters changed in function WriteFaceVideo_PulseRate, manually (e.g., 
    %TextBoxMaxColSize_PulseRate should also be changed. These value needs to be determined 
    %measuring the pixel width of the text after the change).
    %Specify type uint16 for faster evaluation where used.
    TextBoxMaxColSize_PulseRate = uint16(850);
end


%%%%%% Specify text for ROI and pulse rate annotations %%%%%% 

%These string arrays will be used as input to functions WriteFaceVideo_ROIAnnotation and
%WriteFaceVideo_PulseRate.
%Note: 'WriteFaceVideo_TextSetup' is a custom function located within folder 'FacePulseRate'.
[ROI_Text, PulseRate_Text] = WriteFaceVideo_TextSetup(VideoReadConfig, PulseRateConfigAndData);


%%%%%% Specify size of bullets points %%%%%% 

%Specify size of bullets points used in function WriteFaceVideo_BulletPoints, which is called by
%function WriteFaceVideo_SkinDetectDiagnosis.

%Specify depending on frame size.
if VidObjWidth_uint16 <= 1280 || VidObjHeight_uint16 <= 720

    bulletpointRadius = 2;

else

    bulletpointRadius = 3;
end


%%%%%% Setup to display the minimum dimensions of ROIs to be returned by the Viola-Jones detectors %%%%%%
 
%Note: 'WriteFaceVideo_MinVJDims_Setup' is a custom function located within folder 'FacePulseRate'.
ViolaJonesMinDim = ...
    WriteFaceVideo_MinVJDims_Setup(ROIGeneralConfig, VidObjHeight_uint16, VidObjWidth_uint16, ...
        FaceDetectConfig);


end %end main function

