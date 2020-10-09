function [ROIOut_SR, ROIOutBeforeFrameByFrameSmoothing_SR, InterpolatedLinIdx_SR] = ...
             ROIMSIR_OutputIfNoDetections_SecondRead(BlockFullLinIdx_In, VidObjWidth, VidObjHeight)
             %#codegen
%ROIMSIR_OutputIfNoDetections_SecondRead   Assign output for second-read operations when no 
%                                          detection is present in ROIs to be processed.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function ROIMSIR.
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
%    Assign output for second-read operations when no detection is present in ROIs to be processed 
%    BlockFullLinIdx_In. For ROI output, assign the ROIs with the size of the frame dimensions. For 
%    example, if the frame dimensions are 1920 x 1080, assign ROIs of [1, 1, 1920, 1080]. Return
%    InterpolatedLinIdx_SR filled with the indices of all frames within the block, indicating that
%    all frames were interpolated. Although assigning the frame dimensions may not be considered
%    an interpolation operation, it is considered interpolation for convenience.
%               
%    Note: in first-read operations, cases where no detections are available in the ROI block are
%    handled in function ROIMSIR_InterpolateFR. In the second-read operations, an operation
%    similar to the one here is conducted when there are fewer than two detections (see function
%    ROIMSIR_InterpolateSR). 
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


%Assign frame dimensions in place of an ROI
ROIOut_SR = ...
    repmat( ...
        int16([1, 1, VidObjWidth, VidObjHeight]), ...
        length(BlockFullLinIdx_In), ...
        1 ...
    );            

%These output values will be identical to the ROI output values
ROIOutBeforeFrameByFrameSmoothing_SR = ROIOut_SR;

%Count these ROIs as being interpolated
InterpolatedLinIdx_SR = BlockFullLinIdx_In;   


end %end function

