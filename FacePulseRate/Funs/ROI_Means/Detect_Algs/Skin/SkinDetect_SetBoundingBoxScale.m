function [ROISkin_BoundingBoxEnlargementFactor, IncreaseSkinBBoxFactorStartIdx] = ...
             SkinDetect_SetBoundingBoxScale(i, HasROI_TF, SkinDetectConfig, ...
                 IncreaseSkinBBoxFactorStartIdx)
%SkinDetect_SetBoundingBoxScale    Set bounding box enlargement factor for the skin-detection 
%                                  algorithm.
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by functions ROIMeans_FirstRead_SetBoundingBoxes and 
%    ROIMeans_SecondRead_SkinDetect.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Determine whether to increase skin-detection bounding box enlargement factor for ith frame %%%%%%

%Initialize flag
IncreaseSkinBBoxFactorTF = false;

%Specify threshold: how many consecutive unsuccessful skin detections required to increase bounding
%box enlargement factor used for the current skin detection operation.
FramesBack = SkinDetectConfig.ROISkin_BoundingBoxGrowthThreshold;

%Only check skin detections against threshold if enough frames have elapsed to check
if i > FramesBack 
    
    %Number of unsuccessful skin detections meets threshold for increase
    if nnz( ...
            HasROI_TF.SkinAttempted(i - FramesBack : i - 1) & ... frames assessed with skin-detection algorithm 
            ~ HasROI_TF.Skin(       i - FramesBack : i - 1)   ... frames with no skin-detection algorithm detection
       ) ... 
       == FramesBack                                          %   threshold
    
        %Flag to increase skin bounding box enlargement factor for current frame
        IncreaseSkinBBoxFactorTF = true;
        
        %Flag to continue to increase bounding box (at same level) until a detection is made; this 
        %flag is a numeric value that specifies the frame where the threshold was met.
        IncreaseSkinBBoxFactorStartIdx = i;
    
    %Number of unsuccessful skin detections does not meet threshold for enlargement, but continue 
    %enlargement (to same extent) unless a detection was made (by any algorithm).
    elseif IncreaseSkinBBoxFactorStartIdx > 0
        
        %A detection was not made since enlargement; continue to enlarge
        if nnz(...
                HasROI_TF.FacePrimary(   IncreaseSkinBBoxFactorStartIdx : i - 1) | ...
                HasROI_TF.FaceSecondary1(IncreaseSkinBBoxFactorStartIdx : i - 1) | ...
                HasROI_TF.FaceSecondary2(IncreaseSkinBBoxFactorStartIdx : i - 1) ...
           ) == 0
       
            IncreaseSkinBBoxFactorTF = true;
   
        %A detection was made since enlargement; do not expand
        else
            
            %Reset flag
            IncreaseSkinBBoxFactorStartIdx = uint32(0);
        end
    end
end


%%%%%% Set skin-detection algorithm bounding box enlargement factor for ith frame %%%%%%

%Increase skin-detection algorithm bounding box enlargement factor for ith frame 
if IncreaseSkinBBoxFactorTF
    
    ROISkin_BoundingBoxEnlargementFactor = ...
        SkinDetectConfig.ROISkin_BoundingBoxEnlargementFactor * ...
        SkinDetectConfig.ROISkin_BoundingBoxGrowthFactor;

%Do not increase    
else

    ROISkin_BoundingBoxEnlargementFactor = SkinDetectConfig.ROISkin_BoundingBoxEnlargementFactor;
end


end %end function

