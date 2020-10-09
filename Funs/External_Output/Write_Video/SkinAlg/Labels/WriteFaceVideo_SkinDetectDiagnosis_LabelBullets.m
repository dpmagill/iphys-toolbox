function [FrameCropped_BulletPoints, BulletPointsRowMin, BulletPointsRowMax, ...
          BulletPointsColMin, BulletPointsColMax] = ...
              WriteFaceVideo_SkinDetectDiagnosis_LabelBullets(VidFrame, TextXY, ...
                  bulletpointRadius, VidObjHeight_uint16, VidObjWidth_uint16, ...
                  UseCompiledFunctionsTF)
%WriteFaceVideo_SkinDetectDiagnosis_LabelBullets    Prepare bullet points for region labels as a   
%                                                   part of skin-detection diagnosis.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_SkinDetectDiagnosis_Labels.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.

 
%Assign M-by-3 matrix, where each row = [X, Y, radius]
%Use the [X, Y] coordinates used for inserting text labels as shape origins; add the specified  
%radius as a column vector to this matrix. 
BulletPointsXYR = ...
    [TextXY,                                         ... text coordinates to use as shape origins
     repmat(bulletpointRadius, size(TextXY, 1), 1)]; %   column vector of shape radii    

%Insertion of shapes is made more efficient (while requiring more code) by reassigning only 
%portion of frame where shapes are to be inserted rather than reassigning entire frame.

%Crop frame and adjust shape coordinates to correspond to cropped frame
%Local function.
[FrameCropped_BulletPoints, BulletPointsXYR_Cropped, BulletPointsRowMin, ...
 BulletPointsRowMax, BulletPointsColMin, BulletPointsColMax] = ...
    CropFrame_BulletPoints(VidFrame, BulletPointsXYR, VidObjHeight_uint16, ...
        VidObjWidth_uint16);

%Insert filled circles (bullet points) corresponding to positions of text labels to cropped 
%frame:

%Use compiled function
if UseCompiledFunctionsTF

    %Note: insertShapeFast_FilledCircles_mex is a custom compiled version of function 
    %insertShape located within folder 'FacePulseRate'. See the code generation file 
    %(insertShapeFast_FilledCircles) for details.
    FrameCropped_BulletPoints = ...
        insertShapeFast_FilledCircles_mex(FrameCropped_BulletPoints, BulletPointsXYR_Cropped);

%Use non-compiled function    
else

    FrameCropped_BulletPoints = ...
        insertShape( ...
            FrameCropped_BulletPoints, ... specify image where shape annotation inserted
            'FilledCircle',            ... shape
            BulletPointsXYR_Cropped,   ... M-by-3 matrix; row = [X, Y, radius]
            'Color', 'black',          ... shape color
            'Opacity', 1,              ... opacity of 1 is a solid color
            'SmoothEdges', false);     %   disable anti-aliasing filter to save processing time
end


end %end main function


%=============================================================================================
%Local functions 
%=============================================================================================


%=================================================================================================
function [FrameCropped_BulletPoints, BulletPointsXYR_Cropped, BulletPointsRowMin, ...
          BulletPointsRowMax, BulletPointsColMin, BulletPointsColMax] = ...
             CropFrame_BulletPoints(VidFrame, BulletPointsXYR, VidObjHeight, VidObjWidth)
%CropFrame_BulletPoints   Crop frame for the purpose of inserting bullet points.


%Define area to be cropped according to the extrema of shapes:

%Extrema of shapes: shape origins +/- radii (column 3 indicates radii)
BulletPointsRowMin = min(BulletPointsXYR(:, 2)) - BulletPointsXYR(1, 3); %min Y (row) - radius
BulletPointsRowMax = max(BulletPointsXYR(:, 2)) + BulletPointsXYR(1, 3); %max Y (row) + radius
BulletPointsColMin = min(BulletPointsXYR(:, 1)) - BulletPointsXYR(1, 3); %min X (column) - radius
BulletPointsColMax = max(BulletPointsXYR(:, 1)) + BulletPointsXYR(1, 3); %max X (column) + radius

%Adjust extrema where they exceed edges of frame
BulletPointsRowMin = max(1, BulletPointsRowMin);                    %top edge
BulletPointsRowMax = min(double(VidObjHeight), BulletPointsRowMax); %bottom edge
BulletPointsColMin = max(1, BulletPointsColMin);                    %left edge
BulletPointsColMax = min(double(VidObjWidth), BulletPointsColMax);  %right edge

%Crop frame to rectangular area occupied by shapes to be inserted 
%(As defined by shape extrema).
FrameCropped_BulletPoints = ...
    VidFrame( ...
        BulletPointsRowMin : BulletPointsRowMax, ... rows
        BulletPointsColMin : BulletPointsColMax, ... columns
        :                                        ... pages
    ); 

%Adjust origin [X, Y]-coordinates of shapes to correspond to cropped frame
BulletPointsXYR_Cropped = ...
    [BulletPointsXYR(:, 1) - (BulletPointsColMin - 1), ... X column: subtract min X (column)
     BulletPointsXYR(:, 2) - (BulletPointsRowMin - 1), ... Y column: subtract min Y (row)
     BulletPointsXYR(:, 3)];                           %   radii column
     
 
end %end local function

