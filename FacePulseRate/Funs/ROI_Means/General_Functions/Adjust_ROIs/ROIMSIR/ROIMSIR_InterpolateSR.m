function [ROIOut_SR, InterpolatedLinIdx_SR] = ...
             ROIMSIR_InterpolateSR(ROINoPrevCallsBlock, NoPrevCallsBlock_ROIDetections, ...
                 BlockFullLinIdx, NDetectionsFaceSkin, ROIBlockNoDetectionFaceSkinLinIdx, ...
                 NNoDetectionsFaceSkin, TimestampBlock, TimestampBlockDetections, ...
                 ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...
                 ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, VidObjWidth, VidObjHeight, ...
                 LinearExtrapTF, ValidityChecksTF) %#codegen                
%ROIMSIR_InterpolateSR   Interpolate or extrapolate ROIs for frames without a detection during the
%                        second-read operations.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function ROIMSIR_Interpolate.
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
%    Interpolate or extrapolate ROIs for frames without a detection during the second-read 
%    operations. If there are not at least two ROIs that correspond to detections within the block 
%    of frames used, linear interpolation / extrapolation is not possible. In this case, there may 
%    be at least one ROI that corresponds to a detection within the block. If this is the case, 
%    assign this ROI in place of interpolation / extrapolation. Otherwise, assign the dimensions of 
%    the full frame as the ROI; for example, if the frame dimensions are 720 x 1280, assign the ROI 
%    as [1, 1, 1280, 720]. 
%
%    A different function, ROIMSIR_InterpolateFR, conducts interpolation / extrapolation during the
%    first-read operations.  
%
%    Note: if there are exactly zero detections within the block, then function 
%    ROIMSIR_OutputIfNoDetections_SecondRead, called by function ROIMSIR, would have returned ROIs
%    of the full frame dimensions and returned InterpolatedLinIdx_SR filled with the indices of all
%    frames within the block. ROIMSIR would then have terminated immediately after that assignment,
%    preventing the current function from being called.
%
%    For a more detailed description, see function ROIMSIR_Interpolate.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code generation settings %%%%%%

%Inline function
coder.inline('always');


%%%%%% Initialize variables %%%%%%

%Note: If not reassigned, 0 will act as a flag to other functions to indicate no ROIs were 
%interpolated.
InterpolatedLinIdx_SR = int32(0);


%%%%%% Assign ROIs for frames without detections %%%%%%

%At least one frame without a detection (for interp / extrap)
if NNoDetectionsFaceSkin > 0 

    %Linear index of frames where ROIs assigned
    %Convert linear index aligning with block to align with length of video.  
    %Note: these indices may not necessarily be the result of interpolation / extrapolation if
    %too few detections were available on which to base interpolation / extrapolation. In that
    %case, ROIs will have been assigned using an alternative method.
    InterpolatedLinIdx_SR = ROIBlockNoDetectionFaceSkinLinIdx + BlockFullLinIdx(1) - 1;         

    %%%%%% --- Interpolate / extrapolate %%%%%%        

    %If at least two detections are present within the block
    %The detections counted come from both the face- and skin-detection algorithms.
    %At least two ROIs corresponding to detections are needed so that they can be used as the
    %basis of interpolation or extrapolation.    
    if NDetectionsFaceSkin > 1   

        %%%%%% >>>>>> Interpolate / extrapolate %%%%%%
        
        %Arguments to function Interp for second-read operations:

        %Timestamps in block corresponding to frames without a detection
        %Column vector; type single.
        TimestampBlockNoDetections = TimestampBlock(ROIBlockNoDetectionFaceSkinLinIdx);

        %NoPrevCallsBlock_ROIDetections = ROIs corresponding to detections that do not have 
        %                                 modifications from previous calls to ROIMSIR but do
        %                                 have modifications from the current call to ROIMSIR
        %                                 (by functions ROIMSIR_MatchSize and 
        %                                 ROIMSIR_DetectionSmooth).
        %                                 M x 4 matrix; type int16.
        
        %M x 4 matrix; type int16. 
        %Note: for a description of the arguments to function Interp, see the description at 
        %top.  
        %Note: Interp is a custom function located within folder 'FacePulseRate'.                    
        ROINoPrevCallsBlock(ROIBlockNoDetectionFaceSkinLinIdx, 1 : 4) =  ... interpolated ROIs
            Interp( ... 
                TimestampBlockDetections,                  ... Time points used for 
                                                           ... interpolation.
                NoPrevCallsBlock_ROIDetections,            ... ROIs used for interpolation.
                TimestampBlockNoDetections,                ... Time points at which  
                                                           ... interpolation to be assigned.
                LinearExtrapTF,                            ... False: use nearest-neighbor  
                                                           ... method for extrapolation.
                ValidityChecksTF,                          ...    
                ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ... 
                zeros(0, 2, 'int16'),                      ... Empty = do not conduct adjacent  
                                                           ... ROI check.       
                int16(0),  ... 
                VidObjWidth, ...
                VidObjHeight ...
             );         

        %%%%%% >>>>>> Limit overshoots by capping movement of X- and Y-coordinates of adjacent ROIs %%%%%%         

        %Note: for first-read operations, this operation is conducted within function Interp. 
        %This operation is conducted outside of function Interp for second-read operations due  
        %to limitations of function Interp (see note at top).

        %Linear index of ROI values interpolated above
        %Convert to row vector for loop.
        %Row vector; type int32.
        NoDetectionsLinIdx = ROIBlockNoDetectionFaceSkinLinIdx';

        %If an index equals 1, remove it as it cannot be compared to a previous ROI
        %Note: if an index equals 1, there will only be one such index and it will be located 
        %at position 1 of the vector.
        if NoDetectionsLinIdx(1) == 1

            NoDetectionsLinIdx = NoDetectionsLinIdx(2 : NNoDetectionsFaceSkin);

            NNoDetectionsFaceSkin = NNoDetectionsFaceSkin - 1;
        end

        %Maximum difference between an interpolated ROI and previous ROI X- and Y-coordinates
        %Specified in function ValidateAndConfigure.
        %Type int16.
        DiffMax = ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent;        

        %Loop across X-coordinate and Y-coordinate columns
        for i = 1 : 2

            %Loop across ROI rows corresponding to frames without detections
            for j = 1 : NNoDetectionsFaceSkin

                jj = NoDetectionsLinIdx(j); 

                %Find difference between jth and j-1th rows
                %Type int16.
                Diff = ROINoPrevCallsBlock(jj, i) - ROINoPrevCallsBlock(jj - 1, i);

                %If difference greater than threshold
                if Diff > DiffMax   

                    %Replace with j-1th plus threshold
                    ROINoPrevCallsBlock(jj, i) = ROINoPrevCallsBlock(jj - 1, i) + DiffMax;        

                %If difference less than negative of threshold
                elseif Diff < -DiffMax

                    %Replace with j-1th minus threshold
                    ROINoPrevCallsBlock(jj, i) = ROINoPrevCallsBlock(jj - 1, i) - DiffMax;            
                end                                 
            end
        end

        %Assign output:

        %M x 4 matrix; type int16.
        ROIOut_SR = ROINoPrevCallsBlock;     

    %%%%%% --- Assign ROIs without using interpolation / extrapoltion %%%%%% 

    %Fewer than two face-detection algorithm or skin-detection algorithm ROIs are present in 
    %ROIBlock. Note that this case should be relatively infrequent. Consequently, 
    %interpolation / extrapolation cannot be conducted. In place of interpolation / 
    %extrapolation, assign the full frame dimensions as the ROI. Unlike in the first-read
    %operations, the frame dimensions are assigned rather than using a single ROI that 
    %corresponds to a detection. This is done because the block size for the second read is 
    %quite large, and a single ROI may not be representative of all frames within the block.

    else

        ROIOut_SR = ROINoPrevCallsBlock;
        
        %M x 4 row vector; type int16.
        ROIOut_SR(ROIBlockNoDetectionFaceSkinLinIdx) = ...
            repmat( ...
                int16([1, 1, VidObjWidth, VidObjHeight]), ... Full frame values
                NNoDetectionsFaceSkin,                    ... Number of frames without a 
                                                          ... detection.
                 1 ...
            ); ...
    end


%%%%%% No frames correspond to ROIs without detections %%%%%%    

%If no ROIs need to be interpolated / extrapolated. No interpolation / extrapolation is conducted.
%This condition should be accessed relatively infrequently.

else

    %M x 4 matrix; type int16.
    ROIOut_SR = ROINoPrevCallsBlock;
end    
    
        
%%%%%% Adjust ROI(s) that exceed frame dimensions %%%%%%   

%Function ROIAdjustIfExceedsFrameDims, called below, is also called within function Interp. 
%As the X- and Y-coordinate check of ROIs was conduced outside of function Interp for second-read
%operations, the ROIs need to be checked again here in second-read operations.

%Note: Although ROI(s) are also checked later in function ROIMSIR, check here as well so that any
%overshoots from interpolation / extrapolation don't affect the frame-by-frame smoothing operations 
%in function ROIMSIR_FrameByFrameSmooth, which occurs before the check by ROIMSIR. Also, before the 
%check by ROIMSIR, ROIs returned here will influence variable ROIOutBeforeFrameByFrameSmoothing_FR 
%or ROIOutBeforeFrameByFrameSmoothing_SR (assigned in function ROIMSIR), and this variable needs to
%be within frame dimensions for later use in function WriteFaceVideo.  

%Note: used both the pre-processing and post-processing steps of second-read operations. 
    
%Adjust any coordinates that exceed frame dimensions
%M x 4 matrix; type int16.
%Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder 'FacePulseRate'.
ROIOut_SR = ...
    ROIAdjustIfExceedsFrameDims( ...
        ROIOut_SR, ...
        VidObjWidth, ...
        VidObjHeight ...
    ); 

            
end %end function
