function [ROISpecifiedFrames_center_X, ROISpecifiedFrames_center_Y] = ...
             ROIFindCenterPoint(ROI, FramesIdx) %#codegen
%ROIFindCenterPoint   Find center point of one or more ROIs and return as X- and Y-coordinates.                              
%            
%    Helper function to function FacePulseRate.
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
%    Find center point of one or more ROIs and return as X- and Y-coordinates.
%
%    Inputs:
%
%        ROI       = ROI matrix of an integer type. The columns in the ROI matrix indicate 
%                    x-upper-left corner, y-upper-left corner (higher y-values are lower on the                  
%                    Matlab y-axis), width, and height, in pixels.                                                                                              
%        FramesIdx = A linear index of frame(s) cooresponding to ROI(s). Frames can be 
%                    non-consecutive.
%                    
%    Outputs:
%
%        ROISpecifiedFrames_center_X = X-coordinate(s) of center point(s) of ROI(s). 
%        ROISpecifiedFrames_center_Y = Y-coordinate(s) of center point(s) of ROI(s).
%
%    -- Note -- 
%
%    Intended only for use with integer types as rounding is not conducted. For modification for 
%    use with floating-point types, rounding would be necessary as ROI values should be integers.
%    
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%Inline function
coder.inline('always');


%ROI center X- and Y-coordinate(s) of specified ROI row(s) 
%Sum X and Y-upper-left-hand corners of ROI(s) (columns 1 and 2) with half of the width(s) and 
%height(s) (columns 3 and 4). 
%Optimize division by 2 by bit-wise operations.
ROISpecifiedFrames_center_XY = ...
     ROI(FramesIdx, 1 : 2) + bitshift( ROI(FramesIdx, 3 : 4), - 1 );

%Separate to X- and Y-coordinates
ROISpecifiedFrames_center_X = ROISpecifiedFrames_center_XY(:, 1);
ROISpecifiedFrames_center_Y = ROISpecifiedFrames_center_XY(:, 2);


end %end function

