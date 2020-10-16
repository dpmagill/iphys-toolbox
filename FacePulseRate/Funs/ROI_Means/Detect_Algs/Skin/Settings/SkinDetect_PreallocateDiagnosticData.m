function ROISkinDiagnosis = SkinDetect_PreallocateDiagnosticData(ROI, SkinDetectConfig)
%SkinDetect_PreallocateDiagnosticData   Preallocate variables used for skin-detection algorithm
%                                       diagnostics.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by functions SkinDetect_ConfigSetup and
%    SkinSegment_OversegmentationCheck_Reduce.
%
%
%    Description
%    -----------
%
%    Preallocate variables used for skin-detection algorithm diagnostics. The information in these 
%    variables is used to display diagnostic information about the skin-detection algorithm on the 
%    output video, which is written by function WriteFaceVideo. Data for these variables come from
%    function SkinDetect, which conducts the skin-detection algorithm.
%    
%    Most of the variables preallocated here will only be used if flag 
%    OutputConfig.WriteVideoShowROISkinDiagnosisTF is true (see function 
%    OutputConfig_Setup_VideoWriting). Also, if flag OutputConfig.WriteVideoDetailedDiagnosticsTF
%    is false, then OutputConfig.WriteVideoShowROISkinDiagnosisTF will be false.
%
%    Note: the variables preallocated here may be preallocated here again after processing begins 
%    if function ROIMeans_FirstRead is called recursively (see function
%    SkinSegment_OversegmentationCheck_Reduce).
%
%    -- Use of Data for Diagnostics --
%
%    In function SkinDetect, regions may become rejected, and only one region will be selected 
%    as the skin detection region.
%    The variables preallocated in this section will store data on each region for display
%    on the output video (assigned by function WriteFaceVideo when  
%    WriteVideoShowROISkinDiagnosisTF, an argument to function FacePulseRate, is true). This 
%    display shows the location of each region, each region's selection status (selected, neither 
%    selected nor rejected, or rejected), and some scores associated with the regions (for more 
%    details on the display, see function WriteFaceVideo_SkinDetectDiagnosis, which is called by 
%    function WriteFaceVideo). When viewing the output video, it can be determined whether there 
%    were too many regions rejected or too many regions not rejected based upon visual inspection 
%    of the skin regions they occupy. Adjustments can then be made to threshold arguments to 
%    function FacePulseRate.
%
%    Additionally, the centerpoint of the predicted ROI (see description in file for function  
%    SkinDetect) is stored because the distance from each region's centroid to the predicted ROI  
%    center is used as an additional selection score once regions have passed the rejection 
%    thresholds cutoff. On the output video, the distance between the selected region's centroid 
%    and the predicted ROI center is highlighted so that one may determine whether the weighting of  
%    the distance score should be increased.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.
  

%%%%%% Number of rows to preallocate in matrices and struct fields %%%%%%

%Number of rows in the ROI matrix
nRows = size(ROI, 1);


%%%%%% Vector indicating whether skin detection was conducted for each frame %%%%%%

RegionSkinROIAttempted = false( nRows, 1 );


%%%%%% Vector indicating whether regions were available for skin detection for ith frame %%%%%%

%This will be false if the ROI was completely segmented by skin segmentation.
%This will also be false if skin detection was not conducted for the ith frame, that is, if 
%RegionSkinROIAttempted(i) == false.

RegionAnyAvailable = false( nRows, 1 );


%%%%%% Vector indicating whether ROI contained too few pixels classified as skin %%%%%%

ProportionSkinPixelsTooLow = false( nRows, 1 );


%%%%%%  Struct for referencing region boundaries %%%%%%

%Preallocate non-scalar structure RegionBoundaries to store the linear indices of skin-region  
%boundaries returned by function SkinDetect_RegionBoundaries. The boundaries of a region include 
%the external (perimeter) and internal (holes) edges of the region.   

%Struct RegionBoundaries contains three fields, "SelectedLinIdx", "CandidateLinIdx", and 
%"RejectedLinIdx", corresponding to the three categories used in the skin-detection algorithm, 
%namely, selected, candidate, and rejected. For the ith frame, the indices of the one selected
%region are assigned to RegionBoundaries.SelectedLinIdx(i); it is possible that no region was 
%selected, in which case the element will remain empty. The indices of the candidate regions are
%concatenated across regions and assigned to RegionBoundaries.CandidateLinIdx(i), and the indices
%of the rejected regions are concatenated across regions and assigned to 
%RegionBoundaries.RejectedLinIdx(i); if there are no candidate regions or if there are no rejected 
%regions, the corresponding element will remain empty.

%The linear indices of region boundaries will be used to delineate the location of these regions on  
%the output video. The RegionBoundaries structure contains the linear indices of the region that  
%will be selected as well as the indices of other (candidate and rejected) regions. The locations  
%of skin regions that were not selected can be useful to diagnose whether the incorrect skin region 
%was selected or whether the rejection rate is too high. These issues can be addressed by modifying 
%the selection criteria specified by function SkinDetect_ConfigSetup.

%Preallocate structure
%Assign non-scalar struct with rows the length of ROI for indexing purposes.
%Brackets are used to specify that the struct should take the form of a non-scalar struct.
%Use type uint32 for memory conservation. 
%Note: section "Insert boundaries of regions" of function WriteFaceVideo_SkinDetectDiagnosis
%expects type uint32.
RegionBoundaries = ...
    struct('SelectedLinIdx',  repmat( {uint32.empty}, nRows, 1 ), ...
           'CandidateLinIdx', repmat( {uint32.empty}, nRows, 1 ), ... 
           'RejectedLinIdx',  repmat( {uint32.empty}, nRows, 1 )  ...  
    ); 
             
             
%%%%%% Struct for referencing region centroids %%%%%%                    

%This structure serves much the same purpose as the structure used to store region boundary 
%indices. The structure stores the centroid of each region, categorized as selected, candidate, or 
%rejected. The centroids are used to pin score labels on each region in the output video.

%Preallocate structure
%Assign non-scalar struct with rows the length of ROI for indexing purposes.
%Brackets are used to specify that the struct should take the form of a non-scalar struct.
%Use rows of type int16 because data will be of this type for memory conservation. 
RegionCentroids = ...
    struct('SelectedXY',  repmat( {int16.empty}, nRows, 1 ), ...
           'CandidateXY', repmat( {int16.empty}, nRows, 1 ), ... 
           'RejectedXY',  repmat( {int16.empty}, nRows, 1 )  ...  
    ); 

             
%%%%%% Matrix for referencing center of predicted ROI %%%%%%                    

%See note in file for function SkinDetect.

%Preallocate matrix PredictedROI_center to store the (X, Y) coordinates of the center of the
%predicted ROI per frame.
%Assign scalar struct with rows the length of ROI for indexing purposes.
%Use rows of type uint16 for memory conservation.
PredictedROI_center = zeros( nRows, 2, 'uint16' );             


%%%%%% Struct for referencing region RGB and YCbCr scores %%%%%%                    

%This structure serves much the same purpose as the structure used to store region boundary 
%indices. The structure stores the RGB probability and YCbCR z-scores. The RGB probability and 
%YCbCr z-scores are used to determine whether a region is rejected by comparison again specified 
%thresholds for these values. Among regions not rejected, higher probability and lower YCbCr 
%z-scores are used, alongside other criteria, to determine which region is selected as the region 
%to consider as detected skin. For each region, these values are categorized according to whether 
%the region was ultimately selected, was a candidate (not selected nor rejected), or was rejected.
%The values are pinned to the centroid of each region on the output video.

%Preallocate structure
%Assign scalar struct with rows the length of ROI for indexing purposes.
%Brackets are used to specify that the struct should take the form of a non-scalar struct.
%Use rows of type uint8 or single because data will be of this type for memory conservation.

RegionScores = ...
    struct('SelectedRGBProb',  repmat( {uint8.empty},  nRows, 1 ), ...
           'CandidateRGBProb', repmat( {uint8.empty},  nRows, 1 ), ...
           'RejectedRGBProb',  repmat( {uint8.empty},  nRows, 1 ), ...
           'SelectedYCbCrZ',   repmat( {single.empty}, nRows, 1 ), ... 
           'CandidateYCbCrZ',  repmat( {single.empty}, nRows, 1 ), ...
           'RejectedYCbCrZ',   repmat( {single.empty}, nRows, 1 )  ...
     );                                  


%%%%%% Struct for referencing rankings of candidate regions %%%%%%

%Preallocate structure
%Assign non-scalar struct with rows the length of ROI for indexing purposes.
%Brackets are used to specify that the struct should take the form of a non-scalar struct.
%Use rows of type single because data will be of this type for memory conservation. 
RegionRankings = ...
    struct('CandidateHi2Lo', repmat( {single.empty}, nRows, 1 ) ...
    );


%%%%%% Struct for referencing region pixel count %%%%%%                    

%This structure serves much the same purpose as the structure used to region boundary indices.
%The structure stores the Cr standard deviation for each region within the rejected category. The 
%Cr standard deviations are pinned to the centroid of regions that were rejected due to exceeding 
%the Cr standard deviation threshold. Additionally, the second field indicates by linear index 
%whether a region was rejected due to exceeding the Cr standard deviation threshold.

%Preallocate structure
%Assign non-scalar struct with rows the length of ROI for indexing purposes.
%Brackets are used to specify that the struct should take the form of a non-scalar struct array.
%Use rows of type single and uint16 because data will be of these types. A linear index of uint16
%will be used instead of a logical index because few regions are expected to be rejected by this 
%threshold. Storing a few linear indices of type uint16 will use less memory than holding a logical 
%value for each region.  
RegionCrSDScores = ...
    struct('RejectedCrSD',       repmat( {single.empty}, nRows, 1 ), ...
           'RejectedCrSDLinIdx', repmat( {uint16.empty}, nRows, 1 )  ...
    );


%%%%%% Struct for referencing region pixel count %%%%%%                    

%This structure serves much the same purpose as the structure used to store region boundary 
%indices. The structure stores the number of pixels for each region within the rejected category. 
%The pixel counts are pinned to the centroid of each region on the output video. Additionally, the 
%second field indicates (TF) whether a region was rejected based upon a pixel below the minimum 
%threshold.

%Preallocate structure
%Assign non-scalar struct with rows the length of ROI for indexing purposes.
%Brackets are used to specify that the struct should take the form of a non-scalar struct.
%Use rows of type uint32 and logical because data will be of this type for memory conservation. 
RegionNPixels = ...
    struct('RejectedN',      repmat( {uint32.empty},  nRows, 1 ), ...
           'RejectedLowNTF', repmat( {logical.empty}, nRows, 1 )  ...
    );

 
%%%%%% Flag indicating whether function SkinDetect was conducted %%%%%%

%This will not be true if the skin-detection algorithm is not enabled or if the skin-detection 
%algorithm is enabled but the number of primary face-detection algorithm detections is below a 
%threshold (see function SkinDetect_ConfigSetup). These requirements are conditions to call  
%function SkinDetect. This value also will not be true if writing skin-detection diagnostics to the 
%output video is not enabled, which is a condition to enter the current function.

ConductedTF = true;


%%%%%% Combine all structures, matrices, and vectors into one struct for readibility %%%%%%   

ROISkinDiagnosis = ...
    struct( ...
        'ConductedTF',                 ConductedTF, ...
        'RegionSkinROIAttempted',      RegionSkinROIAttempted, ...
        'RegionAnyAvailable',          RegionAnyAvailable, ...
        'ProportionSkinPixelsTooLow',  ProportionSkinPixelsTooLow, ... 
        'RegionBoundaries',            RegionBoundaries, ...
        'RegionCentroids',             RegionCentroids, ...
        'PredictedROI_center',         PredictedROI_center, ...
        'RegionScores',                RegionScores, ...
        'RegionCrSDScores',            RegionCrSDScores, ...
        'RegionRankings',              RegionRankings, ...
        'RegionNPixels',               RegionNPixels, ...
        'RegionNThreshold',            SkinDetectConfig.Thresholds.RegionNThreshold ...
    );


end %end function

