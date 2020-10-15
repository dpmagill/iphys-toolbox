function [BoundingBoxSkin, IncreaseSkinBBoxFactorStartIdx] = ...
             ROIMeans_SecondRead_SetBoundingBox(i, IncreaseSkinBBoxFactorStartIdx, ROI, ...
                 HasROI_TF, ROIGeneralConfig, SkinDetectConfig, VideoReadConfig)
%ROIMeans_SecondRead_SetBoundingBox   Set the bounding box for the ith frame for the skin-detection
%                                     algorithm.
%                                 
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_SecondRead_SkinDetect.
%
%
%    Description
%    -----------
%
%    Set the bounding box for the ith frame for the skin-detection algorithm.
%                                     
%    If a certain number of frames occur where no skin-detection algorithm detection is made  
%    (despite being attempted), enlarge the bounding box. The most likely case for no skin    
%    detection being made is that the area of the frame corresponding to the bounding box was    
%    completely segmented; this may indicate that the bounding box is not sufficiently large to   
%    capture a portion of the face at that time.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Enlarge bounding box as needed %%%%%%

%If a certain number of assessed frames have no detections, within a specified number of frames 
%back, enlarge bounding box.

%Note: SkinDetect_SetBoundingBoxScale is a custom function located within folder 'FacePulseRate'. 
[ROISkin_BoundingBoxEnlargementFactor, IncreaseSkinBBoxFactorStartIdx] = ...
    SkinDetect_SetBoundingBoxScale(i, HasROI_TF, SkinDetectConfig, ...
        IncreaseSkinBBoxFactorStartIdx);    

    
%%%%%% Assign bounding box %%%%%%

%Use compiled function       
if ROIGeneralConfig.UseCompiledFunctionsTF
    
    %Note: ROIResize is a custom compiled function located within folder 'FacePulseRate'. For 
    %source code, see file ROIResize.m.
    BoundingBoxSkin = ...
        ROIResize_mex( ...
            ROI(i, :),                            ... ROI to be adjusted; type int16
            int32(1),                             ... ROI index (1 entered if only 1 ROI); type 
                                                  ... int32.  
            ROISkin_BoundingBoxEnlargementFactor, ... Width resizing scale factor; type double 
            ROISkin_BoundingBoxEnlargementFactor, ... Height resizing scale factor; type double 
            VideoReadConfig.VidObjWidth,          ... To keep adjustment within frame dimensions; 
                                                  ... type int16. 
            VideoReadConfig.VidObjHeight          ...           
        );

%Do not use compiled function
else
    
    %Note: ROIResize is a custom function located within folder 'FacePulseRate'. 
    BoundingBoxSkin = ...
        ROIResize( ...
            ROI(i, :), ... 
            int32(1), ... 
            ROISkin_BoundingBoxEnlargementFactor, ... 
            ROISkin_BoundingBoxEnlargementFactor, ... 
            VideoReadConfig.VidObjWidth, ... 
            VideoReadConfig.VidObjHeight ...           
        );    
end   


end %end function

