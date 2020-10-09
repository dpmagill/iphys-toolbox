function VidFrame = ...
             WriteFaceVideo_SkinDetectDiagnosis(i, VidFrame, ROIDiagnostic, HasROI_TF, ...
                 VidObjWidth_uint16, VidObjHeight_uint16, bulletpointRadius, ...
                 UseCompiledFunctionsTF)
%WriteFaceVideo_SkinDetectDiagnosis   Write skin-detection algorithm metrics to output video for 
%                                     diagnostic purposes.
% 
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo.
%
%
%    Description
%    -----------
%
%    Annotate output video with diagnostics for the skin-detection algorithm, which was conducted 
%    by function SkinDetect. See also the description in function WriteFaceVideo. For a detailed 
%    description of the skin-detection algorithm, see function SkinDetect. 
%     
%    -- Skin-detection algorithm states --
%
%    Four states are possible from function SkinDetect. The first state is a successful ROI 
%    detection. In this state, region borders are shown for all regions, with the regions color 
%    coded depending on whether the region corresponds to a rejected, candidate, or selected 
%    region. Other information is also shown. The second state is a region selected that fails the
%    skin proportion test (see function ConfirmSkinPresent). In this state, borders and other
%    information are not shown but a message is displayed on the output video indicating this 
%    result. The third is when all regions fail the rejection thresholds (see function 
%    SkinDetect_RejectRegions). In this state, region borders of the rejected region(s) are shown 
%    on the output video along with other information. The forth state is when no regions are
%    available for classification, likely because of complete, or near complete, skin segmentation  
%    of the bounding box area. In this state, borders and other information are not shown but a 
%    message is displayed on the output video indicating this result.
%
%    -- Diagnostics on output video --
%
%    - The borders of all regions considered in colors denoting whether a region was rejected 
%      (magneta), a candidate (yellow), or selected (green).
%    - The absence of borders for a region can also be used for diagnostic purposes. Specifically,
%      provided the region fell within the skin-detection bounding box, if a region is not enclosed  
%      by a border, this indicates that the region was classified as non-skin by the 
%      skin-segmentation function (SkinSegmentMask). If regions that are skin too often appear 
%      without borders, this could indicate that the skin segmentation settings used during the
%      skin-detection algorithm are too severe. Note that only regions within the skin-detection 
%      bounding box are assessed by the skin-detection algorithm. 
%    - Values corresponding to some of the criteria used to determine whether a region was
%      rejected, a candidate, or selected. Values are shown only for a subset of regions because of
%      limitied display area. The values include the standard deviations of Y, Cb, and Cr, the 
%      probability that the R, G, and B means correspond to skin, and the standard deviation of Cr
%      standard deviation.
%    - The distance between the centroid of the selected region and the center of the predicted
%      ROI, which is a selection criterion.
%      For details on the classification algorithm used for skin detection, see the file for 
%      function SkinDetect.
%
%    Note: If the skin-detection algorithm was attempted for ith frame, but all skin regions for a 
%    given frame were rejected, metrics for the selected and candidate skin regions will be empty,
%    but metrics for rejected regions will still be available. These rejected regions are
%    superimposed on the video to diagnose whether the rejection rate is too high.      
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Annotate if skin detection attempted for ith frame, even if all regions were rejected %%%%%%

%If skin-detection algorithm (function SkinDetect) did not attempt detection for ith frame  
%Function SkinDetect would not have processed a frame if it were within a certain proximity to a 
%face-detection algorithm detection. 
%Note: this proximity is specified by ROISkinSkipFrameThreshold, which is an argument to function
%FacePulseRate.
if ~ ROIDiagnostic.ROISkin.RegionSkinROIAttempted(i)
    
    %Exit function 
    return
end


%%%%%% Specify annotation sizes for functions below %%%%%%

%Note that the compiled versions of function insertText, located near the bottom of the function
%file, depend upon these font sizes being constant. If the sizes are changed, the compiled 
%functions should be recompiled with the new size.

%Specify depending on frame size
if VidObjWidth_uint16 <= 1280 || VidObjHeight_uint16 <= 720
    
    FontSize = 13; %note: some text appears fuzzy below this font size in this frame size    
    LineLineWidth = 2;
    MarkerSize = 4;
    
else %for other frame sizes
   
    FontSize = 16;
    LineLineWidth = 2;
    MarkerSize = 7;
end
 

%%%%%% At least one region available for assessment and sufficient number of skin pixels in ROI for ith frame %%%%%%

%In ith frame ... 

%(1) At least one region could be submitted to the skin-detection algorithm. If not, it is likely
%    that the skin-segmentation operation conducted within the bounding box during the 
%    skin-detection algorithm (see function SkinDetect_PartitionRegions) completely segmented all 
%    potential regions. This complete segmentation could be valid, such as if something in the
%    environment temporarily occluded the face. However, it could also be an indication that the
%    skin-segmentation parameters are too severe.
%       
%    Note that the skin-segmentation operation conducted during the skin-detection algorithm is 
%    more severe compared to the skin segmentation conducted during the final skin segmentation, 
%    which is the skin segmentation superimposed on the output video; hence, the final skin 
%    segmentation may appear to show regions available that were not available during the 
%    skin-detection algorithm. 
%
%    If this condition is not met, the ROI annotation output will append "[NR]" to "Skin" in the 
%    list of algorithms attempted (see function WriteFaceVideo_ROIAnnotation).
%     
%(2) The proportion of pixels classified as skin within the ROI determined by the skin-detection
%    algorithm was above the specified threshold. During the skin-detection algorithm (function   
%    SkinDetect), function ConfirmSkinPresent checked whether the proportion of pixels was above
%    the specified threshold. The purpose of checking the proportion is to remove ROIs from the 
%    skin-detection algorithm that may have been based on false-positive skin classifications; the
%    assumption is that if a small proportion is classified as skin, the ROI is likely not of 
%    actual skin given that skin would be expected to be present in large, contiguous regions.
%    If below the threshold, diagnostic information is not displayed to avoid confusion because the 
%    depiction of candidate regions and a selected region may make it appear that the  
%    skin-detection algorithm was successful for the ith frame. 
%
%    If below the proportion, the ROI annotation output will append "[R]" to "Skin" in the list of 
%    algorithms attempted (see function WriteFaceVideo_ROIAnnotation).

if ROIDiagnostic.ROISkin.RegionAnyAvailable(i) &&        ... At least one region submitted to 
                                                         ... skin-detection algorithm
   ~ ROIDiagnostic.ROISkin.ProportionSkinPixelsTooLow(i) %   Proportion of pixels classified as 
                                                         %   skin above threshold.    
                                                                                                                  
    %%%%%% --- Extract diagnosis variables from struct for readibility %%%%%% 
        
    RegionBoundaries_uint32    = ROIDiagnostic.ROISkin.RegionBoundaries;    %type uint32
    RegionCentroids_int16      = ROIDiagnostic.ROISkin.RegionCentroids;     %type int16
    PredictedROI_center_uint16 = ROIDiagnostic.ROISkin.PredictedROI_center; %type uint16
    RegionScores_single        = ROIDiagnostic.ROISkin.RegionScores;        %type single
    RegionCrSDScores_single    = ROIDiagnostic.ROISkin.RegionCrSDScores;    %type single
    RegionRankings_single      = ROIDiagnostic.ROISkin.RegionRankings;      %type single
    RegionNPixels_uint32       = ROIDiagnostic.ROISkin.RegionNPixels;       %type uint32  
    
    
    %%%%%% --- Insert boundaries of regions %%%%%%

    %Assign colors to pixels that are the boundaries of regions.
    %The boundaries were determined in function SkinDetect_RegionBoundaries.
    %The borders have been thickened to increase their visibility. Thickening was implemented by
    %performing a dilation operation in function SkinDetect_RegionBoundaries.
    %A linear index is use for assignment.
    %Specify color values to assign as uint8 for efficiency.
    %For efficiency, when adjusting linear indexes for use across pages, make calculations with
    %type integer (the linear indices are already of this type).

    %Extract region boundary linear indices of ith frame from struct
    RegionBoundaries_ith_SelectedLinIdx  = RegionBoundaries_uint32(i).SelectedLinIdx;
    RegionBoundaries_ith_CandidateLinIdx = RegionBoundaries_uint32(i).CandidateLinIdx;
    RegionBoundaries_ith_RejectedLinIdx  = RegionBoundaries_uint32(i).RejectedLinIdx;
    
    %Size of page to use for adjusting linear indexing to second page (green channel)
    NElementsPage = uint32(VidObjWidth_uint16) * uint32(VidObjHeight_uint16);
    
    %Size of two pages to use for adjusting linear indexing to third page (blue channel)  
    %Optimize multiplication by two by bit-wise operation.
    NElementsTwoPages = bitshift(NElementsPage, 1);
    
    %Boundaries of selected regions (green; [0, 255, 0])
    if ~ isempty(RegionBoundaries_ith_SelectedLinIdx)
       
        VidFrame(RegionBoundaries_ith_SelectedLinIdx)                      = uint8(0);   %red page
        VidFrame(RegionBoundaries_ith_SelectedLinIdx + NElementsPage)      = uint8(255); %blue page
        VidFrame(RegionBoundaries_ith_SelectedLinIdx + NElementsTwoPages)  = uint8(0);   %green page
    end

    %Boundaries of candidate regions (yellow; [255, 255, 0])
    if ~ isempty(RegionBoundaries_ith_CandidateLinIdx)
        
        VidFrame(RegionBoundaries_ith_CandidateLinIdx)                     = uint8(255);
        VidFrame(RegionBoundaries_ith_CandidateLinIdx + NElementsPage)     = uint8(255);
        VidFrame(RegionBoundaries_ith_CandidateLinIdx + NElementsTwoPages) = uint8(0);
    end

    %Boundaries of rejected regions (magenta; [255, 75, 255])
    if ~ isempty(RegionBoundaries_ith_RejectedLinIdx)
        
        VidFrame(RegionBoundaries_ith_RejectedLinIdx)                      = uint8(255);
        VidFrame(RegionBoundaries_ith_RejectedLinIdx + NElementsPage)      = uint8(75);
        VidFrame(RegionBoundaries_ith_RejectedLinIdx + NElementsTwoPages)  = uint8(255);
    end     
 
    
    %%%%%% --- Insert text labels on regions %%%%%%      
    
    %Note: ' WriteFaceVideo_SkinDetectDiagnosis_Labels' is a custom function located within folder   
    %'FacePulseRate'. 
    VidFrame = ...
        WriteFaceVideo_SkinDetectDiagnosis_Labels(VidFrame, i, RegionScores_single, ...
            RegionRankings_single, RegionNPixels_uint32, RegionCrSDScores_single, ...
            RegionCentroids_int16, RegionBoundaries_uint32, bulletpointRadius, ...
            VidObjHeight_uint16, VidObjWidth_uint16, FontSize, UseCompiledFunctionsTF);                        
    
    %%%%%% --- Insert star markers and line connecting markers %%%%%%  

    %Insert star markers indicating proximity of selected ROI to predicted ROI, as well as line
    %connecting them.
    
    %Note: for description of predicted ROI, see the file for function SkinDetect.
    
    %Only insert marker and lines if a skin region was selected
    %If all regions rejected, proximity of region centroid to predicted ROI would not have been
    %assessed.
    if HasROI_TF.Skin(i) 
        
        %%%%%% >>>>>> Crop frame %%%%%%
        
        %Specify origin [X, Y]-coordinates of shapes
        %Type int16.
        MarkerOriginsXY = ...     
            [RegionCentroids_int16(i).SelectedXY; ... [X, Y] markers; Nmarkers-by-2 matrix
             int16( PredictedROI_center_uint16(i, :) )];

        %Insertion of shapes is made more efficient (while requiring more code) by reassigning only 
        %portion of frame where shapes are to be inserted rather than reassigning entire frame. 

        %Crop frame and adjust shape coordinates to correspond to cropped frame
        %Local function.
        [FrameCropped_Markers, MarkerPointsXY_Cropped, MarkersRowMin, MarkersRowMax, ...
         MarkersColMin, MarkersColMax] = ...
            CropFrame_Markers(VidFrame, MarkerOriginsXY, MarkerSize, VidObjHeight_uint16, ...
                VidObjWidth_uint16);

        %%%%%% >>>>>> Star markers %%%%%%
            
        %Insert marker shapes to cropped frame:
        
        %Use compiled function
        if UseCompiledFunctionsTF
            
            %Note: insertMarkerFast_mex is a custom compiled version of function insertMarker 
            %located within folder 'FacePulseRate'. See the code generation file (insertMarkerFast) 
            %for details. 
            FrameCropped_Markers = ...
                insertMarkerFast_mex(FrameCropped_Markers, MarkerPointsXY_Cropped, MarkerSize);
            
        %Use non-compiled function    
        else
        
            FrameCropped_Markers = ...
                insertMarker(FrameCropped_Markers, ... Specify image where marker annotation 
                                                   ... inserted.
                    MarkerPointsXY_Cropped,        ... [X, Y] marker origins; Nmarkers-by-2 matrix 
                    '*',                           ... Marker type (star)
                    'color', {'green', 'white'},   ... Colors of markers
                    'size', MarkerSize);           %   Size of markers
        end
        
        %%%%%% >>>>>> Line segment %%%%%%
        
        %Insert line segment shape connecting selected-region centroid and center of predicted ROI
        %to cropped frame:
        
        %Use compiled function
        if UseCompiledFunctionsTF
            
            %Note: insertShapeFast_Line_mex is a custom compiled version of function insertShape 
            %located within folder 'FacePulseRate'. See the code generation file 
            %(insertShapeFast_Line) for details.
            FrameCropped_Markers = ...
                insertShapeFast_Line_mex(FrameCropped_Markers, MarkerPointsXY_Cropped, ...
                    LineLineWidth);
             
        %Use non-compiled function         
        else 
            
            FrameCropped_Markers = ...
                insertShape(FrameCropped_Markers,            ... Specify image where shape 
                                                             ... annotation inserted.
                    'line',                                  ... Shape (line)
                    reshape(MarkerPointsXY_Cropped', 1, []), ... Reshaped to [X, Y] row vector of 
                                                             ... endpoints of line.
                    'color', 'white',                        ...
                    'LineWidth', LineLineWidth);             %   Line width    
        end

        %%%%%% >>>>>> Insert cropped frame into frame %%%%%%
        
        %Insert cropped frame with shapes into original-size frame:    
        VidFrame( ...
            MarkersRowMin : MarkersRowMax, ... rows
            MarkersColMin : MarkersColMax, ... columns
            :                              ... pages
        ) = FrameCropped_Markers;
            
    end %end if skin region selected      
end 


end %end main function


%=============================================================================================
%Local functions 
%=============================================================================================


%=================================================================================================
function [FrameCropped_Markers, MarkerPointsXY_Cropped, MarkersRowMin, MarkersRowMax, ...
          MarkersColMin, MarkersColMax] = ...
             CropFrame_Markers(VidFrame, MarkerOriginsXY, MarkerSize, VidObjHeight, ...
                VidObjWidth)
%CropFrame_Markers   Crop frame for the purpose of inserting markers to show selected-ROI
%                    centroid and predicted-ROI center and to show a line connecting them.

            
%Define area to be cropped according to the extrema of shapes:

%Extrema of shapes: shape origins +/- size
%Scalars; type int16.
MarkersRowMin = min( MarkerOriginsXY(:, 2) ) - MarkerSize; %min Y (row) - size
MarkersRowMax = max( MarkerOriginsXY(:, 2) ) + MarkerSize; %max Y (row) + size
MarkersColMin = min( MarkerOriginsXY(:, 1) ) - MarkerSize; %min X (column) - size
MarkersColMax = max( MarkerOriginsXY(:, 1) ) + MarkerSize; %max X (column) + size

%Adjust extrema where they exceed edges of frame
%Scalars; type int16.
MarkersRowMin = max( MarkersRowMin, 1 );                   %top edge
MarkersRowMax = min( MarkersRowMax, int16(VidObjHeight) ); %bottom edge
MarkersColMin = max( MarkersColMin, 1 );                   %left edge
MarkersColMax = min( MarkersColMax, int16(VidObjWidth) );  %right edge

%Crop frame to rectangular area occupied by shapes to be inserted
%(As defined by shape extrema).
FrameCropped_Markers = ...
    VidFrame( ...
        MarkersRowMin : MarkersRowMax, ... rows
        MarkersColMin : MarkersColMax, ... columns
        :                              ... pages
    );    

%Adjust origin [X, Y]-coordinates of shapes to correspond to cropped frame
MarkerPointsXY_Cropped = ...
    [MarkerOriginsXY(:, 1) - (MarkersColMin - 1),  ... subtract the min X-coordinate
     MarkerOriginsXY(:, 2) - (MarkersRowMin - 1)]; %   subtract the min Y-coordinate

 
end %end local function
