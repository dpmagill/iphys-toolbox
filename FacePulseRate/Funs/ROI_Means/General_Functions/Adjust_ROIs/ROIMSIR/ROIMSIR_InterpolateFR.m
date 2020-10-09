function [ROIOut_FR, InterpolatedLinIdx_FR] = ...
             ROIMSIR_InterpolateFR(ROINoPrevCallsBlock, NoPrevCallsBlock_ROIDetections, ...
                 ROIBlockDetectionFaceSkinLinIdx, NDetectionsFaceSkin, ...
                 TimestampBlock, TimestampBlockDetections, ...
                 ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ...
                 ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, VidObjWidth, VidObjHeight, ...
                 ROINoResizeBlock_FR, RowToReturnFullLinIdx_FR, RowToReturnBlockLinIdx_FR, ...                              
                 ROIMSIR_FirstFrameLinIdx_FR, LinearExtrapTF, ValidityChecksTF) %#codegen
%ROIMSIR_InterpolateFR   Interpolate or extrapolate an ROI if the target frame does not correspond
%                        to a detection. Used during the first-read operations.
%                        
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function ROIMSIR_Interpolate.
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
%    Interpolate or extrapolate an ROI if the target frame does not correspond to a detection. If 
%    there are not at least two ROIs that correspond to detections within the block of frames used,
%    linear interpolation / extrapolation is not possible. In this case, there may be at least one  
%    ROI that corresponds to a detection within the block. If this is the case, assign this ROI in
%    place of interpolation / extrapolation. Otherwise, assign the dimensions of the full frame as
%    the ROI; for example, if the frame dimensions are 720 x 1280, assign the ROI as [1, 1, 1280, 
%    720].
%        
%    A different function, ROIMSIR_InterpolateSR, conducts interpolation / extrapolation during the
%    second-read operations. 
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
InterpolatedLinIdx_FR = int32(0);


%%%%%% Operation when detection present for target frame %%%%%%    

%If detection found for target frame
%Note: function IsMember is local function.
if IsMember( ...
        RowToReturnBlockLinIdx_FR,       ... set A
        ROIBlockDetectionFaceSkinLinIdx, ... set B
        NDetectionsFaceSkin              ... length set B
    )                       

    %A detection is present for the current frame; do not interpolate
    %1 x 4 row vector; type int16.
    ROIOut_FR = ROINoPrevCallsBlock(RowToReturnBlockLinIdx_FR, 1 : 4);

    %Exit function
    return

    
%%%%%% Operations when detection not present for target frame %%%%%%

else        

    %%%%%% --- Assign ROIs for frames without detections %%%%%%               

    %Linear index of frames where ROIs assigned
    %Note: these indices may not necessarily be the result of interpolation / extrapolation if
    %too few detections were available on which to base interpolation / extrapolation. In that
    %case, ROIs will have been assigned using an alternative method.
    InterpolatedLinIdx_FR = RowToReturnFullLinIdx_FR;        

    %%%%%% >>>>>> Interpolate / extrapolate target ROI %%%%%%

    %Interpolate / extrapolate X-, Y-coordinate, width, and height of target ROI.

    %If at least two detections are present within the block
    %The detections counted come from both the face- and skin-detection algorithms.
    %At least two ROIs corresponding to detections are needed so that they can be used as the
    %basis of interpolation or extrapolation.
    if NDetectionsFaceSkin > 1                                                                                                         

        %Arguments to function Interp for first-read operations:

        %Timestamps in block corresponding to the target frame
        %Scalar; type single.
        TimestampTarget = TimestampBlock(RowToReturnBlockLinIdx_FR);       

        %NoPrevCallsBlock_ROIDetections = ROIs corresponding to detections that do not have 
        %                                 modifications from previous calls to ROIMSIR but do
        %                                 have modifications from the current call to ROIMSIR
        %                                 (by functions ROIMSIR_MatchSize and 
        %                                 ROIMSIR_DetectionSmooth).
        %                                 M x 4 matrix; type int16.

        %If this is not the first time the function is called from the first read (function
        %ROIMeans_FirstRead_TakeMeans). On the first call, the values of the previous ROI will
        %be zeros, but this block relies on the previous ROI containing non-zero values. This
        %is required by argument ROINoResizeBlock_Previous.
        if RowToReturnFullLinIdx_FR ~= ROIMSIR_FirstFrameLinIdx_FR

            %Previous ROI X- and Y-coordinates without resizing
            %A Non-resized ROI is used because the target ROI has not yet been resized (it will 
            %be in the final step of function ROIMSIR). 
            ROINoResizeBlock_Previous = ...
                ROINoResizeBlock_FR( ...
                    RowToReturnBlockLinIdx_FR - 1, ...
                    1 : 2 ...
                );                

            %1 x 4 row vector; type int16.
            %Note: for a description of the arguments to function Interp, see the description 
            %at top.                
            %Note: Interp is a custom function located within folder 'FacePulseRate'.                    
            ROIOut_FR =                                        ... Interpolated ROI
                Interp( ... 
                    TimestampBlockDetections,                  ... Time points used for   
                                                               ... interpolation.
                    NoPrevCallsBlock_ROIDetections,            ... Values used for 
                                                               ... interpolation.
                    TimestampTarget,                           ... Time point at which   
                                                               ... interpolation to be 
                                                               ... assigned.
                    LinearExtrapTF,                            ... False: use nearest-neighbor   
                                                               ... method for extrapolation.
                    ValidityChecksTF, ... 
                    ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ... 
                    ROINoResizeBlock_Previous, ... 
                    ROIGeneralConfig_ROIMSIR_DiffMaxAdjacent, ...               
                    VidObjWidth, ...
                    VidObjHeight ...
                 );                                   

        else

            %1 x 4 row vector; type int16.
            %Note: for a description of the arguments to function Interp, see the description 
            %at top.
            %Note: Interp is a custom function located within folder 'FacePulseRate'.                    
            ROIOut_FR =                                        ... Interpolated ROI
                Interp( ... 
                    TimestampBlockDetections,                  ... Time points used for   
                                                               ... interpolation.
                    NoPrevCallsBlock_ROIDetections,            ... Values used for 
                                                               ... interpolation. 
                    TimestampTarget,                           ... Time point at which   
                                                               ... interpolation to be 
                                                               ... assigned.
                    LinearExtrapTF,                            ... 
                    ValidityChecksTF,                          ... 
                    ROIGeneralConfig_ROIMSIR_DiffMaxDetection, ... 
                    zeros(0, 2, 'int16'),                      ... Empty = do not conduct 
                                                               ... adjacent ROI check. 
                    int16(0),                                  ... Unused argument for adjacent 
                                                               ... ROI check/                                                                                          
                    VidObjWidth, ...
                    VidObjHeight ...
                 );                                                                        
        end

    %%%%%% >>>>>> Assign ROI without using interpolation / extrapoltion %%%%%% 

    %Fewer than two face-detection algorithm or skin-detection algorithm ROIs are present in 
    %ROIBlock. Note that this case should be relatively infrequent. Consequently, 
    %interpolation / extrapolation cannot be conducted. First, if there is at least one ROI  
    %that corresponds to a detection, use this ROI in place of interpolation / extrapolation. 
    %If an ROI corresponding to a detection cannot be found within the block, assign the full 
    %frame dimensions as the ROI.             

    %Fewer than two face-detection algorithm or skin-detection algorithm ROIs are present in 
    %ROIBlock.             
    else

        %Find the temporally-nearest non-zero ROI
        %If a non-zero ROI does not exist, assign an ROI whose dimensions take the dimensions 
        %of the full frame.     
        %Local function.
        ROIOut_FR = ...
            AssignROI(NDetectionsFaceSkin, NoPrevCallsBlock_ROIDetections, VidObjWidth, ...
                VidObjHeight);                                                
    end         
end


end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function ROIOut_FR = ...
             AssignROI(NDetectionsFaceSkin, NoPrevCallsBlock_ROIDetections, VidObjWidth, ...
                 VidObjHeight)                                           
%AssignROI   Assign an ROI in place of interpolation / extrapolation.    
%
%    Description:
%
%    Assign the single ROI that corresponds to a detection. If no frames within the block 
%    correspond to a detection, assign the dimesions of the frame.
%
%    Notes:
%
%    - No interpolation conducted.
%    - Calling this function is expected to occur infrequently.


%Inline function
coder.inline('always');


%If a single ROI corresponding to an ROI exists
if NDetectionsFaceSkin == 1

    %Note: NoPrevCallsBlock_ROIDetections will have exactly one row if this condition is entered;
    %clarify this fact to code generation by explicitly indexing the first row.
    ROIOut_FR = NoPrevCallsBlock_ROIDetections(1, 1 : 4);          
    
%No ROIs within the block correspond to detections    
else %NDetectionsFaceSkin == 0

    %Assign an ROI with dimensions of the full frame
    %1 x 4 row vector; type int16.
    ROIOut_FR = ...
        int16( ...
            [1, 1, VidObjWidth, VidObjHeight] ...
        );
end

            
end %end local function
