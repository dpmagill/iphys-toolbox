function ROIMat = ...
             SkinDetect_EnlargeROI(ROIMat, ROIWidthMin, ROIHeightMin, VidObjWidth, VidObjHeight)
             %#codegen
%SkinDetect_EnlargeROI   Expand width and height of skin-detection algorithm ROI if below minimum.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinDetect_SelectedRegionROI.
%
%
%    Code Generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.
%
%
%    Description
%    -----------
%
%    Expanding ROIs is intended to increase coverage of the face or skin, especially if the ROI is 
%    quite small but larger regions or the face or skin are known to exist about it. ROIs are 
%    expanded according to the arguments ROIWidthMin and ROIHeightMin.   
%
%    Inputs:
%
%        ROIMat         = M-by-4 matrix. Should be of an integer type to ensure no decimals are
%                         included in the assignment; this is because no rounding is conducted. The
%                         columns in the ROI matrix indicate x-upper-left corner, y-upper-left 
%                         corner (larger y-values are lower on the y-axis), width, and height, in  
%                         pixels.
%                         Frames can be non-consecutive. 
%        ROIWidthMin    = The minimum ROI width, specified as an integer type. 
%                         Widths less than this value will be expanded up to this value.                                           
%        ROIHeightMin   = The minimum ROI height, specified as an integer type. 
%                         Heights less than this value will be expanded up to this value.                                                                     
%
%    Note: this function is compatible with code generation. This compatability was used for 
%    testing purposes, but a compiled funtion is not used in FacePulseRate toolbox. See function
%    SkinDetect for notes.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code generation specifications %%%%%%

%Inline function
coder.inline('always');


%%%%%% Input validation %%%%%%

%Should be of an integer type 
%This is to ensure no decimals are included in the assignment; this is because no rounding is 
%conducted. This error would likely be due to an implementation error.
assert( isinteger(ROIMat(1, 1)) );


%%%%%% Expand specified ROI widths if less than specified minimum %%%%%%

%Description: Make adjustments to widths (and, consequently, X-coordinate) if lower than specified
%minimum.

%%%%%% --- Identify ROIs with widths below minimum %%%%%%

%Extract width columns from ROIs
ROISpecifedWidth = ROIMat(:, 3);

%Assign logical index of ROI widths that are below minimum
WidthToBeAdjustedLogIdx = ROISpecifedWidth < ROIWidthMin;

%%%%%% --- Assign new widths for ROIs below minimum %%%%%%

%Assign the specified minimum width for all ROIs below the minimum width.
%Assign to vector with length the number of ROIs below minimum.
ROI_widths_adjust = repmat(ROIWidthMin,  length(WidthToBeAdjustedLogIdx), 1);

%%%%%% --- Assign new left-side X-coordinates as a result of width expansion %%%%%%

%Find X-coordinates of center points of ROIs with widths that were below minimum
%(The centerpoints for the adjusted ROIs are the same as those for the original ROIs).
%Note: ROIFindCenterPoint is a custom function located within folder 'FacePulseRate'.
[ROISpecifiedFrames_center_X, ~] = ROIFindCenterPoint(ROIMat, WidthToBeAdjustedLogIdx);
    
%Assign new left-side X-coordinates as a result of expanding width from centerpoint
%Optimize division by 2 by bit-wise operation.
ROI_left_X_adjust = ROISpecifiedFrames_center_X - bitshift(ROIWidthMin, -1);


%%%%%% Expand ROI heights if less than specified minimum %%%%%%

%Description: Make adjustments to height (and, consequently, Y-coordinate) if lower than specified
%minimum. 

%%%%%% --- Identify ROIs with heights below minimum %%%%%%

%Extract height columns specified ROIs
ROISpecifiedHeight = ROIMat(:, 4);

%Assign logical index of specified ROI heights that are below minimum
HeightToBeAdjustedLogIdx = ROISpecifiedHeight < ROIHeightMin;

%%%%%% --- Assign new heights for ROIs below minimum %%%%%%

%Assign the specified minimum height for all ROIs below the minimum height.
%Assign to vector with length the number of ROIs below minimum.
ROI_heights_adjust = repmat(ROIHeightMin, length(HeightToBeAdjustedLogIdx), 1);  

%%%%%% --- Assign new upper-side Y-coordinates as a result of height expansion %%%%%%

%Find Y-coordinates of center points of specified ROIs with heights that were below minimum
%(The centerpoints for the adjusted ROIs are the same as those for the original ROIs).
%Note: ROIFindCenterPoint is a custom function located within folder 'FacePulseRate'.
[~, ROISpecifiedFrames_center_Y] = ROIFindCenterPoint(ROIMat, HeightToBeAdjustedLogIdx);
    
%Assign upper-side Y-coordinates as a result of expanding height from centerpoint
%Optimize division by 2 by bit-wise operation.
ROI_upper_Y_adjust = ROISpecifiedFrames_center_Y - bitshift(ROIHeightMin, -1);


%%%%%% Verify adjustments are within frame dimensions; Adjust if necessary to conform %%%%%%

%Function ROIAdjustIfExceedsFrameDims verifies if adjusted ROIs are within frame dimensions and, if
%not, adjusts the ROI values to conform to frame dimensions.

%Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder 'FacePulseRate'. 
ROIsVerifiedOrAdjusted = ...
    ROIAdjustIfExceedsFrameDims( ...
        [ROI_left_X_adjust, ROI_upper_Y_adjust, ROI_widths_adjust, ROI_heights_adjust], ...
        VidObjWidth, VidObjHeight ...
    );


%%%%%% Assign adjusted ROIs to ROI matrix %%%%%%

%Assign new left-side X-coordinates, which were modified as a result of width expansion, to ROI
%matrix. 
ROIMat(WidthToBeAdjustedLogIdx, 1) = ROIsVerifiedOrAdjusted(:, 1);

%Assign new upper-size Y-coordinates, which were modified as a result of height expansion, to ROI 
%matrix. 
ROIMat(HeightToBeAdjustedLogIdx, 2) = ROIsVerifiedOrAdjusted(:, 2);

%Assign expanded widths, where skin-detection ROI widths were below minimum, to ROI matrix 
ROIMat(WidthToBeAdjustedLogIdx, 3) = ROIsVerifiedOrAdjusted(:, 3);

%Assign expanded heights, where skin-detection ROI heights were below minimum, to ROI matrix 
ROIMat(HeightToBeAdjustedLogIdx, 4) = ROIsVerifiedOrAdjusted(:, 4);


end %end function

