function RGB_frame_annt = ...
             WriteFaceVideo_LowProportionSkin(RGB_frame_annt, i, ROI_uint16, ...
                 VidObjWidth_uint16, VidObjHeight_uint16)
%WriteFaceVideo_LowProportionSkin   Insert annotation indicating that the ROI was adjusted due to a
%                                   low proproption of pixels classified as skin.
%
%   Helper function to function FacePulseRate.
%   Within function FacePulseRate, called by function WriteFaceVideo.
%
%
%   Description
%   -----------
%
%   Insert annotation indicating that the ROI was adjusted due to a low proproption of pixels 
%   classified as skin. This adjustment occurred in function ROIMeans_TakeMeans.
%                                      
%   This function is only used for infrequent annotations (a few frames in the entire video) as it
%   is somewhat inefficient for two reaons. (1) Function insertText is not compiled; compiling this
%   function would result in much faster execution but would require more specific checks. (2) The
%   entire frame, rather than a portion of it, is returned, causing more memory to be written to.
%   However, by not implementing these modifications, the function can be more conveniently 
%   modified in the future.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%Specify font size depending on frame size:

%The font size used here will be slightly smaller than the font used in other functions within
%function WriteFaceVideo.

%Note: font size should be consistent with font size used in function 
%WriteFaceVideo_SkinDetectDiagnosis.

if VidObjWidth_uint16 == 1280 && VidObjHeight_uint16 == 720

    FontSizeSmall = 14; %note: some text appears fuzzy below this font size in this frame size    

elseif VidObjWidth_uint16 == 1920 && VidObjHeight_uint16 == 1080

    FontSizeSmall = 15;

else %for other frame sizes

    FontSizeSmall = 15;
end

%Specify text:

Text = ...
    ['ROI adjusted because low proportion of pixels classified as skin; ROI from previous', ...
     ' frame used.'];

%Position text immediately below top of ROI
%This position avoids a conflict with an annotation inserted for skin-detection diagnosis (see 
%function WriteFaceVideo_SkinDetectDiagnosis).
TextXY = ...
    [ROI_uint16(i, 1) + round( (ROI_uint16(i, 3) / 2) ), ... X = center of ROI
     ROI_uint16(i, 2) + 1];                              %   Y = bottom of ROI

%Text box background color:

%Note: should match color of final ROI box border, which was inserted in function WriteFace Video.
BoxColor = [189, 233, 255]; %light blue

%Position of [X, Y] coordinates relative to text:

AnchorPoint = 'CenterTop';

%Insert text:

RGB_frame_annt = ...
    insertText(RGB_frame_annt,      ... Specify image where annotation inserted
        TextXY,                     ... [X, Y] coordinates of lines of text
        Text,                       ... Text
        'BoxColor', BoxColor,       ... Box background color; note: white has been observed to  
                                    ... cause unexpected colors to appear.
        'AnchorPoint', AnchorPoint, ... Position of [X, Y] coordinates relative to text 
        'FontSize', FontSizeSmall   ... Font size
);


end %end function

