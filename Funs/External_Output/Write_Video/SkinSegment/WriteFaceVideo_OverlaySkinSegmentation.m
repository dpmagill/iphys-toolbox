function VidFrameROI = ...
             WriteFaceVideo_OverlaySkinSegmentation(i, VidFrameROI, SkinSegmentMasks, nRows, ...
                 nCols, UseCompiledFunctionsTF)
%WriteFaceVideo_OverlaySkinSegmentation   Overlay color on frame or ROI of frame for pixels 
%                                         classified as non-skin from skin segmentation.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo. 
%
%
%    Description
%    -----------
%
%    Overlay color on frame or ROI of frame for pixels classified as non-skin from skin 
%    segmentation (see function SkinSegmentMask).                                        
% 
%    Skin segmentation information was previously stored in struct SkinSegmentMasks to avoid
%    redundant computations from rerunning skin segmentation in the current function. The
%    skin-segmentation masks were recorded by function ROIMeans_TakeMeans_StoreMaskForVideoWrite 
%    within function ROIMeans_TakeMeans. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Unpack inverted skin-segmentation mask information for ith frame %%%%%%    

%Inverted skin-segmentation mask
%(True = non-skin).
%Matrix; type logical.
IsSkinMask_Inverted = ... 
    bwunpack( ... unpack 
        SkinSegmentMasks(i).IsNotSkin_PixelColor_Packed, ... packed logical matrix
        nRows                                            ... number of rows in logical matrix
    );


%%%%%% Overlay color corresponding to pixels classified as non-skin %%%%%%

%Compiled functions enabled
if UseCompiledFunctionsTF 

    %Note: 'WriteFaceVideo_MaskOverlay' is a custom compiled function located within folder 
    %'FacePulseRate'. For source code, see file WriteFaceVideo_MaskOverlay.m.       
    VidFrameROI = ... type uint8
        WriteFaceVideo_MaskOverlay_mex( ...
            VidFrameROI,         ... ROI of frame (type uint8)
            single(.30),         ... transparency of overlay
            IsSkinMask_Inverted, ... mask for pixel-color segmentation (logical matrix) 
            [97, 202, 255],      ... color (light blue) for pixel-color segmentation overlay
            nRows, ...
            nCols ...    
        );

%Compiled functions not enabled
else

    %Note: 'WriteFaceVideo_MaskOverlay' is a custom function located within folder 'FacePulseRate'.       
    VidFrameROI = ... type uint8
        WriteFaceVideo_MaskOverlay( ...
            VidFrameROI,         ... ROI of frame (type uint8)
            single(.30),         ... transparency of overlay
            IsSkinMask_Inverted, ... mask for pixel-color segmentation (logical matrix) 
            [97, 202, 255],      ... color (light blue) for pixel-color segmentation overlay
            nRows, ...
            nCols ...
        );
end    


end %end function

