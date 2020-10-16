function [ROI_Selected_ith, SkinTF_ith, HasROITF_SkinNotPresent_ith, ROIDiagnostic_ROISkin_ith, ...
          LoopCounter] = ...
             SkinDetect(i, VidFrame, VideoReadConfig_VidObjWidth, VideoReadConfig_VidObjHeight, ...
                 SkinSegmentConfig, ROIGeneralConfig, SkinDetectConfig, ...
                 OutputConfig_WriteVideoShowROISkinDiagnosisTF, BoundingBoxSkin, ...
                 FirstReadSkinTF, ROIForBoundingBoxSkin_FR, ROI_SR_ith, ...
                 FramesToProcessLinIdx_SR, Notifications_Interval_SR, ...
                 Notifications_LoopStartTime_SR, Notifications_LoopCounter_SR) %#codegen                                        
%SkinDetect   Identify an ROI for a frame using a skin-detection algorithm.                  
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions ROIMeans_FirstRead_AlgSelector_Skin and 
%    ROIMeans_SecondRead_SkinDetect.
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
%    This function conducts the skin-detection algorithm. As function FacePulseRate already 
%    utilizes the face-detection method, which has a strong accuracy rate for frontal-face 
%    orientations, the primary purpose of the present function is to identify skin regions where 
%    the face-detection method is not successful, which may occur, in particular, in  
%    non-frontal-face orientations, for example, in profile-face orientations. 
%
%    The input of functions directly related to the skin-detection algorithm is used. These   
%    functions include SkinDetect_ConfigSetup, ROIMeans_FirstRead_CollectSkinColorSamples, and 
%    SkinDetect_SetThresholds. 
%
%    - Function SkinDetect_ConfigSetup: assigned many of the skin-detection settings used here, 
%      which are contained in struct SkinDetectConfig. This function was called by function
%      ValidateAndConfigure. 
%    - Function ROIMeans_FirstRead_CollectSkinColorSamples: collected skin-color samples from the 
%      face in the video. These samples were used to set skin-color thresholds to be used in the 
%      skin-detection algorithm. This function was called by function ROIMeans_FirstRead.  
%    - Function SkinDetect_SetThresholds: set the skin-color thresholds from skin-color samples
%      supplied by function ROIMeans_FirstRead_CollectSkinColorSamples. This function was called by 
%      function ROIMeans_FirstRead.  
%
%    The skin-detection algorithm can be unsuccessful (i.e., return a value of false for variable
%    SkinTF_ith) for the following reasons:
%
%    - The bounding box did not contain a skin region.
%    - The portion of the frame submitted to the skin-detection algorithm was completely segmented  
%      by the skin-segmentation algorithm.
%    - All regions within the portion of the frame submitted to the skin-detection algorithm were
%      rejected.
%    - Rejected by function ConfirmSkinPresent.
%
%
%    Extended Description
%    --------------------
%
%
%    -- Partitioning Bounding Box into Regions to Classify --
%
%    See function SkinDetect_PartitionRegions, which is called by the current function.
% 
%    The area within the bounding box is partitioned into regions so that each region can be 
%    assessed as being skin. By the completion of the algorithm, one region (or no regions) will be
%    selected as the skin detection.
%
%    - Bounding Box:
%
%    Using a bounding box may reduce false positive skin detections by focusing on an area of the 
%    frame potentially more likely to contain skin. Using a bounding box may also reduce 
%    computational time because less area needs to be assessed by the skin-detection algorithm. The 
%    size and position of the bounding box are determined by the size and position of ROIs from 
%    previous and subsequent frames. The ROIs from these other frames will be the result of 
%    detections from the face-detection algorithm and interpolation where the face-detection 
%    algorithm did not make a detection or where the face-detection algorithm was skipped for 
%    efficiency. In the first-read operations, the bounding box is set by function 
%    ROIMeans_FirstRead_SetBoundingBoxes. In the second-read operations, the bounding box is set by
%    function ROIMeans_SecondRead_SkinDetect. 
%      
%    - Skin Segmentation:
%
%    Within the bounding box, skin segmentation (see function SkinSegmentMask) is applied to remove 
%    areas less likely to be skin. The term "skin segmentation" is used to define the operations
%    conducted by function SkinSegmentMask, although many operations in the current function have
%    the effect of segmenting skin as well. The thresholds used by function SkinSegmentMask differ 
%    from the thresholds used directly in the skin-detection algorithm because the thresholds used 
%    by SkinSegmentMask apply to the properties of individual pixels. In constrast, the thresholds 
%    used in the skin-detection algorithm apply to the properties of regions of pixels. For 
%    example, in skin segmentation, the threholds include minimum and maximum pixel color values,
%    e.g., for color channel Cr, the default mimimum is 131 and the default maximum is 173. In the
%    skin-detection algorithm, the thresholds include the minimum and maximum difference from the 
%    means of regions of the face in the video (which are taken from skin-color samples of the 
%    face). Assessing regions of pixels may provide information to supplement information found by 
%    assessing individual pixels.
%
%    - Partitioning:
%
%    Skin segmentation returns a two-dimension logical matrix, where true values indicate pixels
%    classified as skin. This matrix, or mask, typically consists of several contingous regions of
%    true values. These regions are further broken down before being submitted to further 
%    skin-detection algorithm operations. The matrix is broken down, or partitioned, simply by 
%    applying a grid of dividing lines to the matrix. Specifically, vertical lines are inserted at 
%    specified intervals of columns (SkinDetectConfig.PartitionColInterval) and horizontal lines 
%    are inserted at specified intervals of rows (SkinDetectConfig.PartitionRowInterval). These 
%    lines, along with the pixels classified as non-skin by skin segmentation, are logical false 
%    values. The true values that remain are distinguished as groups according to regions of 
%    connected pixels (the criteria of 8-connectivity is used; see Matlab function bwconncomp).
%
%    One purpose of breaking down contiguous regions into smaller regions is to improve 
%    discrimination between skin and non-skin regions; these non-skin regions are portions
%    misclassified as skin by the skin-segmentation procedure. After breaking up the regions, the  
%    misclassified portions may end up in regions separate from correctely-classified portions. If
%    this is the case, the high proportion of non-skin pixels in these regions may make it easier
%    for the skin-detection algorithm to correctly discriminate between skin and non-skin regions.
%   
%    The other purpose of breaking down continguous regions into smaller regions is to make the 
%    centroid-distance criteria (see section "Selecting one region out of candidates") more 
%    effective. The distance between the centroid of a region and the center of the ROI assuming no
%    skin-detection is conducted is used to help spacially stablize the region selected across  
%    frames. Stability is enhanced across frames because the centroid-distance criteria favors  
%    regions that occur in similar spacial areas across frames. Smaller regions increase the 
%    stability resulting from this criteria because smaller regions permit greater distance 
%    discrimination among regions. 
%
%    For example, suppose that the tip of the nose is the center of the ROI assuming no 
%    skin-detection is conducted. Suppose that selection is down to two regions, one of which 
%    comprises the forehead and one a cheek. Finally, suppose that the distance between the 
%    forehead-region centroid and the tip of the nose is nearly equal to the distance between the 
%    cheek-region centroid and the tip of the nose. If these two regions continue to be the top 
%    candidates across frames, on some occassions the forehead-region may be selected and on some 
%    occassions the cheek-region may be selected depending on small deviations in 
%    centroid-distance. If the selected region alternates more or less between these two regions 
%    across frames, this will result in high fluctuation of the ROI as it moves between the 
%    forehead and the cheek across frames. By using smaller regions, the centroid-distance will 
%    have higher discrimination among regions. For example, with smaller regions, the forehead now 
%    consists of many regions, as does the cheek. The centroid-distance may now favor the lower
%    forehead and the region of the cheek close to the nose. Fluctuation between these two regions
%    across frames will be less than the flucuation between the entire forehead and the entire 
%    cheek.
%    
%    The regions resulting from partitioning are termed "candidate regions" as some will be  
%    rejected and only one will be seleted.
%
%    Note: this partitioning procedure may appear similar to that of dividing an image into 
%    superpixels (regions  of pixels) for use in classification. One rational for using superpixels  
%    is that fewer areas within an image need to be assessed for classification compared to an  
%    operation using a moving window (see Matlab documentation under the title "Plot Land   
%    Classification with Color Features and Superpixels"). However, the use of regions in the  
%    current operation is simply to take advantage of assessing regions of pixels compared to 
%    assessing individual pixels.
%
%
%    -- Rejecting Regions --
%
%    See function SkinDetect_RejectRegions, which is called by the current function.
%
%    Candidate skin regions must pass certain rejection criteria to be considered. These rejection 
%    criteria include the size of the region; the probability of skin color according to RGB  
%    references samples; the similarity to the mean Cb and Cr skin colors collected from the video 
%    frames; and the standard deviation of the Cr colors.
% 
%    - RGB Probability:
%     
%    The RGB probability is calculated RGB reference samples from both samples collected current 
%    video and samples from a population of individuals; the population samples are included to 
%    increase heterogeneity, which is intended to make the probability parameters more robust. The 
%    population samples are also included because they include negative samples, whereas the 
%    samples collected from the current video are all positive samples. For details on the 
%    collection of skin-color samples from the video, see function 
%    ROIMeans_FirstRead_CollectSkinColorSamples.   
%
%    The frame means are collected by function ROIMeans_FirstRead_CollectSkinColorSamples, which is  
%    called in function ROIMeans_FirstRead. Function SkinDetect_RGBProbSkin is called within the
%    function SkinDetect_RejectRegions to calculate the probability of skin for each region. This  
%    function is supplied with theta parameters, which were calculated from RGB color means from    
%    the video and from external sources. The theta parameters were returned by function   
%    SkinDetect_RGBProbSkinTrain, which was called by function SkinDetect_SetThresholds, which was   
%    called by function ROIMeans_FirstRead.
%
%    The RGB skin-classification functions (SkinDetect_RGBProbSkinTrain and SkinDetect_RGBProbSkin)
%    are adapted from the Skin Segmentation toolbox, which was obtained from Madhav Rajan (2014).  
%    See discussion on Github (https://github.com/madhrajan91/Skin-Segmentation).      
%
%    The external (population) data for producing the RGB skin-classification theta values are from 
%    two sources:
%
%        In part from Bhatt and Dhall 2009, 'Skin Segmentation Dataset', UCI Machine Learning  
%        Repository. See discussion in Bhatt, Sharma, Dhall, Chaudhury (2009). Efficient skin  
%        region segmentation using low complexity fuzzy decision tree model. IEEE-INDICON, Dec 
%        16-18, Ahmedabad, India, pp. 1-4. See also Dhall, Sharma, Bhatt, and Khan (2009). Adaptive 
%        Digital Makeup, Proc. of International Symposium on Visual Computing (ISVC), Nov. 30 -Dec. 
%        02, Las Vegas, Nevada, USA, Lecture Notes in Computer Science, Vol. 5876, pp. 728-736.
%
%        In part from  Douglas Magill (2020). These data are included under the license for  
%        function FacePulseRate.
%
%    The threshold outside of which regions are rejected is specified as an argument 
%    (SkinClassifyRegionColorThresholds(1)) to function FacePulseRate. A Larger threshold value may   
%    decrease false positives but increase false negatives.
%
%    - Cb, Cr means:
%
%    Regarding the YCbCr color space, only Cb and Cr are used for rejection thresholds because of
%    greater luminance invariance compared to Y. The Cb and Cr similarities are quanitifed as 
%    z-scores, one for each dimension (Cb and Cr). The z-scores are calulated according to the 
%    overall Cb and Cr means across ROIs from the primary face-detection algorithm and the standard 
%    deviations of  these means. The means across the primary face-detection algorithm ROIs are  
%    collected by function ROIMeans_FirstRead_CollectSkinColorSamples, which is called by function  
%    ROIMeans_FirstRead. The overall means and standard deviations of these means are returned by 
%    function SkinDetect_SetThresholds, which is called by function ROIMeans_FirstRead. The  
%    thresholds outside of which regions are rejected are specified as an argument to function
%    FacePulseRate: SkinClassifyRegionColorThresholds(2) = Cb z-score threshold; 
%    SkinClassifyRegionColorThresholds(3) = Cr z-score threshold. Smaller threshold values may  
%    decrease false positives but increase false negatives.
%
%   - Pixel count:
%
%    In addition to assessing regions by their means, they are also assessed by their pixel counts,
%    with the assumption that small pixel counts indicate non-skin as skin is assumed to be present 
%    in contiguous regions. Using regions with larger pixel counts may also enhance the advantage 
%    of mean comparison. The threshold below which regions are rejected is specified by 
%    RegionNThreshold, which is specified by function SkinDetect_ConfigSetup. A Larger threshold 
%    value may decrease false positives but increase false negatives.  
%
%    - Standard deviation of Cr:
%
%    The standard deviation of colors within a region can be an indication that the region is not
%    skin as it has been observed that skin regions have fairly homogeneous color ranges, which 
%    results in a low standard deviation. Hence, a threshold is applied above which regions are  
%    rejected as skin.
%
%
%    -- Selecting one Region Out of Candidates (Regions That were Not Rejected) --
%
%    See function SkinDetect_SelectRegion, which is called by the current function.
%
%    If no candidate region passes the rejection thresholds, skin detection moves to the next 
%    frame. If more than one candidate region passes all the rejection thresholds, one candidate  
%    region is selected based upon the ranking of regions on 3 additional criteria: (1) the  
%    proximity to the predicted-ROI center, (2) higher probability of skin compared to RGB 
%    references samples, and (3) the similarity to YCbCr overall means (including Y) across 
%    reference samples. 
%
%    - Proximity to the predicted ROI:
%
%    Proximity to the predicted-ROI center is used to increase the stability of the ROI positions  
%    across frames; as the predicted ROIs are based upon face detections, whose positions across  
%    frames are assumed to be relatively stable, proximity to these stable detections would, in 
%    turn, increase the stability of the positions of selected skin regions across frames. Also,  
%    the face-detection algorithms mainly detect the frontal face, whereas the skin-detection 
%    algorithm detects skin wherever it is (e.g., the neck, hands, etc.). Part of the purpose of    
%    using the skin-detection algorithm is to capture skin when the face is not frontal, for 
%    example, turned to the side, etc; however, if the face is frontal (but the face-detection 
%    algorithm(s) failed to detect it), it is preferable to have the skin-detection algorithm focus 
%    on the face rather than other skin areas for consistency. Toward this end, weighting toward 
%    the face-detection algorithm ROIs helps guide the skin detections toward the frontal face 
%    rather than other areas.
%    
%    - RGB probability:
%
%    RGB probability is calculated in the method described above under "rejection thresholds".   
%
%    - YCbCr similarity:
%
%    The YCbCr similarity is quanitifed as a composite of three z-scores, one for each channel (Y,
%    Cb, and Cr). The z-scores are calulated according to the overall Y, Cb, and Cr means across
%    all frames and the standard deviations of Y, Cb, and Cr means across all frames. The z-score 
%    for each channel is then standardized in comparison to the other regions in the frame to   
%    balance out the contribution of each channel (otherwise, the Y-channel tends to have a much  
%    higher z-score). Finally, a single composite similarity score is assigned by summing the 
%    absolute values of the standarized z-scores.           
%
%    - Combined skin-similarity score:
%
%    The scores based upon skin color (RGB probability and YCbCr similarity) are then combined, 
%    with equal weight, to one score. 
%
%    - Apply weights to proximity and skin-similarity scores:
%
%    The proximity score and the skin color score are then assigned weights, specified as an 
%    argument, ROISkinRegionProximityWeight, to function FacePulseRate. Specifically, this argument
%    specifies the relative weight to apply to proximity compared to skin color similarity.
%
%    - Determining ROI box from the selected region:
%
%    The ROI from the selected candidate region is determined based upon the X and Y extrema of the 
%    region. The size of this ROI is then increased to 25% above the minimum ROI size dimensions 
%    specified as arguments to function FacePulseRate, if it is not as large. This ROI increase is
%    based upon the assumption that regions detected by the skin-detection algorithm are smaller 
%    than the size of ROIs returned by the face-detection algorithm(s); the increase is intended to 
%    capture the entire face if the face is frontal. This expansion is returned by function
%    SkinDetect_EnlargeROI, which is called by function SkinDetect_SelectRegion.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.     


%%%%%% Code-generation settings %%%%%%

%Called during code generation
if ~ coder.target('MATLAB') %code generation running

    %Inline function
    coder.inline('always');
    
    %Declare variables:
    
    %Note: for many, set bounds so that these variables do not use dynamic memory allocation,
    %increasing efficiency.
    
    %                                                                              Upp. Bounds  Var. Size (T/F)
    coder.varsize('RegionCentroids',                                               [400, 2],    [1, 0]);
    coder.varsize('RegionNPixels',                                                 [400, 1],    [1, 0]);
    coder.varsize('RegionNPixels_PassNThresholdTF_LogIdx',                         [400, 1],    [1, 0]);     
    coder.varsize('RegionRGBProbSkin',                                             [400, 1],    [1, 0]);  
    coder.varsize('RegionZ_Y',                                                     [400, 1],    [1, 0]);     
    coder.varsize('RegionZ_Cb',                                                    [400, 1],    [1, 0]);   
    coder.varsize('RegionZ_Cr',                                                    [400, 1],    [1, 0]);      
    coder.varsize('RegionSD_Cr',                                                   [400, 1],    [1, 0]);   
    coder.varsize('RegionSD_Cr_PassThresholdTF_LogIdx',                            [400, 1],    [1, 0]);    
    coder.varsize('RegionPassAllThresholdsTF_LogIdx',                              [400, 1],    [1, 0]);  
    coder.varsize('RegionPoints',                                                  [400, 1],    [1, 0]);
    coder.varsize('RegionSelectedLinIdx',                                          [1, 1],      [1, 1]);
    coder.varsize('ROI_Selected',                                                  [1, 4],      [1, 0]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedLowNTF',        [400, 1],    [1, 1]); 
    coder.varsize('ROIDiagnostic_ROISkin_ith.BBox_Scan_SkinAlg',                   [1, 4],      [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx',     [inf, 1],    [1, 1]); 
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionBoundaries_CandidateLinIdx',    [inf, 1],    [1, 1]); 
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx',     [inf, 1],    [1, 1]);    
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionCentroids_SelectedXY',          [1, 2],      [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionCentroids_CandidateXY',         [400, 2],    [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionCentroids_RejectedXY',          [400, 2],    [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.PredictedROI_center',                 [1, 2],      [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionScores_SelectedRGBProb',        [1, 1],      [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionScores_CandidateRGBProb',       [400, 1],    [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionScores_RejectedRGBProb',        [400, 1],    [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ',         [1, 3],      [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionScores_CandidateYCbCrZ',        [400, 3],    [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionScores_RejectedYCbCrZ',         [400, 3],    [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo',       [400, 1],    [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSDLinIdx', [400, 1],    [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSD',       [400, 1],    [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedN',             [400, 1],    [1, 1]);
    coder.varsize('ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedLowNTF',        [400, 1],    [1, 1]);
end

%Preallocate variables:

RegionPassAllThresholdsTF_LogIdx      = coder.nullcopy( false(0, 1) );
RegionSelectedLinIdx                  = zeros(0, 0, 'uint16');
ROIPredicted_CenterX                  = coder.nullcopy( zeros(1, 'int16') ); 
ROIPredicted_CenterY                  = coder.nullcopy( zeros(1, 'int16') );
RegionRGBProbSkin                     = coder.nullcopy( zeros(0, 1, 'double') );  
RegionZ_Y                             = coder.nullcopy( zeros(0, 1, 'single') ); 
RegionZ_Cb                            = coder.nullcopy( zeros(0, 1, 'single') ); 
RegionZ_Cr                            = coder.nullcopy( zeros(0, 1, 'single') );
RegionPoints                          = coder.nullcopy( zeros(0, 1, 'uint16') );
RegionNPixels_PassNThresholdTF_LogIdx = coder.nullcopy( false(0, 1) );   
RegionSD_Cr                           = coder.nullcopy( zeros(0, 1, 'single') );
RegionSD_Cr_PassThresholdTF_LogIdx    = coder.nullcopy( false(0, 1) );   
HasROITF_SkinNotPresent_ith           = false;
SkinTF_ith                            = false;
ROI_Selected_ith                      = coder.nullcopy( zeros(0, 4, 'int16') );

%Preallocate struct for diagnostic data
%Local function.
ROIDiagnostic_ROISkin_ith = ROIDiagnosticPreallocate();


%%%%%% Input validation %%%%%%

%Validate whether inputs BoundingBoxSkin and ROI_SR_ith are type int16.
%Should be type int16 because the function is implemented to assign values of this type.
%Must be an integer type because no rounding is conducted.
%A non-matching type would be due to an implementation error.

assert( isa(BoundingBoxSkin(1, 1), 'int16') );

%Note: ROI_SR_ith will be empty during first-read operations
if ~ FirstReadSkinTF

    assert( isa(ROI_SR_ith(1, 1), 'int16') );
end


%%%%%% Assign logical value that skin-detection algorithm was attempted for ith frame %%%%%%

ROIDiagnostic_ROISkin_ith.RegionSkinROIAttempted = true;       


%%%%%% Partition bounded area of frame into regions %%%%%%

%Partition bounded area of frame into regions for preparation to submit the regions to the 
%skin-detection algorithm. The frame is partitioned through skin segmentation and the superposition 
%of grid lines. 

%Record bounding box used for scan for display on output video    
%Convert from type int16 to type uint16 because signed operations not conducted with this variable.
ROIDiagnostic_ROISkin_ith.BBox_Scan_SkinAlg = uint16(BoundingBoxSkin);

%Note: 'SkinDetect_PartitionRegions' is a custom function located within folder 'FacePulseRate'.
[IsSkinMask,         ... Logical matrix (i.e, skin-segmentation mask) from skin segmentation where 
                     ... pixels classified as skin == true.
 RegionIndices,      ... N x 1 non-scalar struct with field 'PixelIdxList', where N equals the  
                     ... number of regions. Each row consists of linear indices, of type uint32, 
                     ... corresponding to the pixels of a given region. 
 NRegions,           ... Number of regions. Scalar; int32.
 RegionNPixels,      ... N x 1 column vector indicating the number of pixels of each region, where 
                     ... N equals the number of regions; type single.
 RegionCentroids,    ... N x 2 matrix of the centroids (X, Y) of each region, where N equals the 
                     ... number of regions; type int16.               
 RBounded_Uint8,     ... Bounded area in RGB colorspace, separated by channel; type uint8.
 GBounded_Uint8,     ...  
 BBounded_Uint8,     ...  
 YBounded_Single,    ... Bounded area in YCbCr colorspace, separated by channel; type single.
 CbBounded_Single,   ...
 CrBounded_Single,   ...
 nRows_IsSkinMask,   ... Skin-segmentation mask dimensions.
 nCols_IsSkinMask] = ...          
    SkinDetect_PartitionRegions(VidFrame, BoundingBoxSkin, SkinDetectConfig, SkinSegmentConfig, ...
        VideoReadConfig_VidObjWidth, VideoReadConfig_VidObjHeight);
     
    
%%%%%% Assess the partitioned regions %%%%%%
    
%If no regions found, skip region assessment
%No regions found would likely be due to complete skin segmentation of ROI.
if NRegions ~= 0  
    
    %%%%%% --- Reject regions according to specified thresholds %%%%%%   
    
    %Note: 'SkinDetect_RejectRegions' is a custom function located within folder 'FacePulseRate'. 
    [RegionPassAllThresholdsTF_LogIdx, RegionNPixels_PassNThresholdTF_LogIdx, ...
     RegionSD_Cr_PassThresholdTF_LogIdx, RegionNPixels, NRegionsPass, RegionRGBProbSkin, ... 
     RegionZ_Y, RegionZ_Cb, RegionZ_Cr, RegionSD_Cr] = ...                             
        SkinDetect_RejectRegions(SkinDetectConfig, RegionIndices, NRegions, RegionNPixels, ...
            RBounded_Uint8, GBounded_Uint8, BBounded_Uint8, YBounded_Single, CbBounded_Single, ...
            CrBounded_Single);    
            
    %%%%%% --- Select the partitioned region that appears the most likely to be skin %%%%%%

    %Proceed with region selection if at least one region passed the rejection thresholds.
    %Otherwise, skip further evaluation and proceed to recording values that can be displayed on
    %the output video for potential diagnosis. 
    if NRegionsPass > 0
 
        %Note: 'SkinDetect_SelectRegion' is a custom function located within folder 
        %'FacePulseRate'.
        [ROI_Selected_ith, SkinTF_ith, HasROITF_SkinNotPresent_ith, RegionSelectedLinIdx, ...
         RegionPoints, ROIPredicted_CenterX, ROIPredicted_CenterY] = ...        
            SkinDetect_SelectRegion(ROI_SR_ith, ROIForBoundingBoxSkin_FR, BoundingBoxSkin, ...
                IsSkinMask, RegionPassAllThresholdsTF_LogIdx, NRegions, NRegionsPass, ...
                RegionRGBProbSkin, RegionZ_Y, RegionZ_Cb, RegionZ_Cr, RegionCentroids, ...
                RegionIndices, RegionNPixels, VidFrame, FirstReadSkinTF, SkinDetectConfig, ...
                SkinSegmentConfig, ROIGeneralConfig, VideoReadConfig_VidObjWidth, ...
                VideoReadConfig_VidObjHeight);                        
        
        %If the proportion of pixels classified as skin was below the specified threshold       
        if HasROITF_SkinNotPresent_ith                  
            
            %Record status
            ROIDiagnostic_ROISkin_ith.ProportionSkinPixelsTooLow = true;

            %Initialize fields in struct ROIDiagnostic_ROISkin_ith:

            EntryFlag = 'ProportionSkinPixelsTooLow';
                         
            %Local function.
            ROIDiagnostic_ROISkin_ith = ...
                ROIDiagnosticInitialize(ROIDiagnostic_ROISkin_ith, EntryFlag);
           
        else           
       
           %Record status        
           %Note: If the compiled version of function SkinDetect is being used, the variable below  
           %must be initialized because the variable was preallocated by a call to function  
           %nullcopy. The variable must be initialized because nullcopy preallocates but does not
           %initialize. The variable is initialized by the assignment below. Note that if the  
           %Matlab version of function SkinDetect is being used, function nullcopy has no effect  
           %and variables are always initialized; hence, the assignment below is not necessary.  
           ROIDiagnostic_ROISkin_ith.ProportionSkinPixelsTooLow = false;
        end
        
    %No regions passed the rejection thresholds or a centroid was not able to be calculated for any
    %region. 
    %Note: this should be relatively uncommon.
    else   
       
        %Assign false, zero, or empty values for use in function SkinDetect_RecordDiagnosticData
        %For code generation purposes, specify the corresponding types.               
        RegionSelectedLinIdx = zeros(0, 0, 'uint16');
        ROIPredicted_CenterX = zeros(1, 'int16');
        ROIPredicted_CenterY = zeros(1, 'int16');
        RegionPoints         = zeros(0, 1, 'uint16');
        
        %Initialize fields in struct ROIDiagnostic_ROISkin_ith:
        
        EntryFlag = 'AllRejected';
        
        %Local function.
        ROIDiagnostic_ROISkin_ith = ROIDiagnosticInitialize(ROIDiagnostic_ROISkin_ith, EntryFlag);       
    end
    
%No regions were available
%Note: this should be relatively uncommon.
else
      
    %Initialize fields in struct ROIDiagnostic_ROISkin_ith:

    EntryFlag = 'NoRegions';

    %Local function.
    ROIDiagnostic_ROISkin_ith = ROIDiagnosticInitialize(ROIDiagnostic_ROISkin_ith, EntryFlag);        
end


%%%%%% Record data for use in skin-detection diagnostics %%%%%%

%Record data to be displayed on the output video for the purpose of assessing the effectiveness of 
%the skin-detection algorithm.

%At least one region was available
%(See function SkinDetect_PartitionRegions).
if NRegions > 0 

    %Record that at least one region was available for skin detection for the ith frame
    %If the skin-detection algorithm was attempted for the ith frame (HasROI_TF.SkinAttempted(i) ==
    %true) but at least one region was not available, the characters '[NS]' will be displayed on
    %the output video (see function WriteFaceVideo_ROIAnnotation_ROIMethod). These characters are 
    %an acronym for "no skin", indicating that no skin regions were available.
    
    %Note: This will be false (assigned by local function ROIDiagnosticInitialize) if the area 
    %corresponding to the skin-detection bounding box was completely segmented and, hence, has no 
    %regions available (NRegions == 0). Note that a false value will also be present if the frame 
    %did not have the skin-detection algorithm applied on it, that is, if function SkinDetect was 
    %not used for the frame; in this case, the value would have been preallocated as false by
    %function SkinDetect_PreallocateDiagnosticData.
    
    ROIDiagnostic_ROISkin_ith.RegionAnyAvailable = true;  

    %%%%%% --- Detailed skin-diagnostic information %%%%%%
        
    %Record detailed skin-detection algorithm diagnostic information. 
    
    %Note: the following condition will be true only if the detailed display option is enabled. 
    %This diagnostic information is shown in the output video only if the detailed display option
    %is enabled, in which case flag OutputConfig.WriteVideoDetailedDiagnosticsTF will be true. By 
    %default, it is false. Flag OutputConfig.WriteVideoDetailedDiagnosticsTF is set by function
    %ValidateAndConfigure_InternalFlags.
    if OutputConfig_WriteVideoShowROISkinDiagnosisTF

        %Scalar struct.
        %Note: 'SkinDetect_RecordDiagnosticData' is a custom function located within folder 
        %'FacePulseRate'.
        ROIDiagnostic_ROISkin_ith = ...
            SkinDetect_RecordDiagnosticData(ROIDiagnostic_ROISkin_ith, ... 
                RegionPassAllThresholdsTF_LogIdx, RegionSelectedLinIdx, RegionIndices, ... 
                BoundingBoxSkin, RegionCentroids, ROIPredicted_CenterX, ROIPredicted_CenterY, ... 
                RegionRGBProbSkin, RegionZ_Y, RegionZ_Cb, RegionZ_Cr, RegionPoints, ...
                RegionNPixels, NRegions, RegionNPixels_PassNThresholdTF_LogIdx, RegionSD_Cr, ...
                RegionSD_Cr_PassThresholdTF_LogIdx, nRows_IsSkinMask, nCols_IsSkinMask, ...
                VideoReadConfig_VidObjHeight);                        
    end
end


%%%%%% Display progress notifications %%%%%%    

%Note: include the following statement immediately before loop: LoopStartTime = tic.

%Only use when called in second read (called by function ROIMeans_SecondRead_SkinDetect).
%Also, do not implement for generated code. Specifically, passing tic 
%(Notifications_LoopStartTime_SR) from Matlab code to toc in compiled code not recommended by 
%Matlab documentation.    
if ~ FirstReadSkinTF &&   ... second-read operations ongoing
   coder.target('MATLAB') %   code generation not running  
    
    %Note: 'LoopProgressNotification' is a custom function located within folder 'FacePulseRate'.
    LoopCounter = ...
        LoopProgressNotification(Notifications_Interval_SR, FramesToProcessLinIdx_SR, i, ...
            Notifications_LoopStartTime_SR, Notifications_LoopCounter_SR);      

else  
    
    LoopCounter = uint32(0);
end


end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function ROIDiagnostic_ROISkin_ith = ROIDiagnosticPreallocate()
%ROIDiagnosticPreallocate   Preallocate values for ROIDiagnostic_ROISkin_ith.
%
%    Note: only the types, but not the values, are assigned when coder.nullcopy is used. Local
%    function ROIDiagnosticInitialize is used to assign values (i.e., initialize the values) when
%    the values are not assigned elsewhere in function SkinDetect.


%Inline function
coder.inline('always');


ROIDiagnostic_ROISkin_ith = ...
    coder.nullcopy( ...
        coder.const( ...
            struct( ...
                'RegionSkinROIAttempted',              false, ...
                'BBox_Scan_SkinAlg',                   zeros(1, 4, 'uint16'), ...
                'RegionAnyAvailable',                  false, ...
                'RegionNPixels_RejectedN',             uint32([]), ...
                'RegionNPixels_RejectedLowNTF',        logical([]), ...
                'RegionCentroids_SelectedXY',          int16([]), ...
                'RegionCentroids_CandidateXY',         int16([]), ...
                'RegionCentroids_RejectedXY',          int16([]), ...
                'PredictedROI_center',                 zeros(1, 2, 'uint16'), ...
                'RegionScores_SelectedRGBProb',        uint8([]), ...
                'RegionScores_CandidateRGBProb',       uint8([]), ...
                'RegionScores_RejectedRGBProb',        uint8([]), ...
                'RegionScores_SelectedYCbCrZ',         single([]), ...
                'RegionScores_CandidateYCbCrZ',        single([]), ...
                'RegionScores_RejectedYCbCrZ',         single([]), ...
                'RegionRankings_CandidateHi2Lo',       single([]), ...
                'RegionCrSDScores_RejectedCrSDLinIdx', uint16([]), ...
                'RegionCrSDScores_RejectedCrSD',       single([]), ...
                'ProportionSkinPixelsTooLow',          false, ...
                'RegionBoundaries_SelectedLinIdx',     uint32([]), ...
                'RegionBoundaries_CandidateLinIdx',    uint32([]), ...
                'RegionBoundaries_RejectedLinIdx',     uint32([]) ...
            ) ...
        ) ...
    );


end %end local function


%=============================================================================================
function ROIDiagnostic_ROISkin_ith = ROIDiagnosticInitialize(ROIDiagnostic_ROISkin_ith, EntryFlag)
%ROIDiagnosticInitialize   Assign uninitialized values for ROIDiagnostic_ROISkin_ith.    
%
%    Description:
%
%    If the compiled version of function SkinDetect is being used, all fields in struct   
%    ROIDiagnostic_ROISkin_ith must be initialized because the struct was preallocated by a call to  
%    function nullcopy. The variables must be initialized because nullcopy preallocates but does
%    not initialize. The fields are initialized by the current function. They are initialied here 
%    because certain fields, depending on EntryFlag, will not be initialized by function 
%    SkinDetect_RecordDiagnosticData.    
%
%    Note: if the Matlab version of function SkinDetect is being used, function nullcopy has no   
%    effect and variables are always initialized; hence, assignment here is not necessary.   


%Inline function
coder.inline('always');


ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo = single([]);
ROIDiagnostic_ROISkin_ith.PredictedROI_center           = zeros(1, 2, 'uint16');

if EntryFlag(1) == 'N' || ... 'NoRegions'
   EntryFlag(1) == 'P'    %   'ProportionSkinPixelsTooLow'
    
    ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx     = uint32([]);
    ROIDiagnostic_ROISkin_ith.RegionBoundaries_CandidateLinIdx    = uint32([]);
    ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx     = uint32([]);
    ROIDiagnostic_ROISkin_ith.RegionScores_SelectedRGBProb        = uint8([]);
    ROIDiagnostic_ROISkin_ith.RegionScores_CandidateRGBProb       = uint8([]);
    ROIDiagnostic_ROISkin_ith.RegionScores_RejectedRGBProb        = uint8([]);
    ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ         = single([]);
    ROIDiagnostic_ROISkin_ith.RegionScores_CandidateYCbCrZ        = single([]);
    ROIDiagnostic_ROISkin_ith.RegionScores_RejectedYCbCrZ         = single([]);
    ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSDLinIdx = uint16([]);
    ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSD       = single([]);    
end

if EntryFlag(1) == 'N' %'NoRegions'

    ROIDiagnostic_ROISkin_ith.RegionAnyAvailable = false;
end

if ~ EntryFlag(1) == 'P' %'ProportionSkinPixelsTooLow'
    
    ROIDiagnostic_ROISkin_ith.ProportionSkinPixelsTooLow = false;
end 


end %end local function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(SkinDetect_mex) of the function.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.
                                                                 
%                                            Example Code                    Upp. Bounds       Var. Size (T/F)    Type
VidFrameCode                 = coder.typeof( zeros(500, 500, 3, 'uint8'),    [inf, inf, 3],    [1, 1, 0] );       %uint8 
ROI_SRCode                   = coder.typeof( zeros(1, 4, 'int16'),           [1, 4],           [1, 0] );          %int16
FramesToProcessLinIdx_SRCode = coder.typeof( zeros(1, 500, 'int32'),         [1, inf],         [0, 1] );          %uint32 
         
      
%%%%%% Specify fixed-size input arguments %%%%%%

iCode                                             = int32(0);
BoundingBoxSkinCode                               = zeros(1, 4, 'int16');
ROIForBoundingBoxSkin_FRCode                      = zeros(1, 4, 'int16');
VideoReadConfig_VidObjWidthCode                   = int16(0);
VideoReadConfig_VidObjHeightCode                  = int16(0);
OutputConfig_WriteVideoShowROISkinDiagnosisTFCode = false;
FirstReadSkinTFCode                               = false;
Notifications_Interval_SRCode                     = int32(0);
Notifications_LoopStartTime_SRCode                = uint64(0); 
Notifications_LoopCounter_SRCode                  = int32(0);                

%Note: the number, names, and order of struct fields are compile-time constants.

%%%%%% --- ROIGeneralConfigCode struct %%%%%%

%                        Example Code              Upp. Bounds    Var. Size (T/F)   Type
Element1 = coder.typeof( zeros(10, 5, 'double'),   [inf, 5],      [1, 0] );         %double

Element2 = coder.typeof( zeros(10, 1, 'double'),   [inf, 1],      [1, 0] );         %double

ROIGeneralConfigCode = ...
    struct( ...
        'ROIMinWidthProportion',                      double(0), ...                          
        'ROIMinHeightProportion',                     double(0), ... 
        'ROIWidthResizeFactor',                       double(0), ...
        'ROIHeightResizeFactor',                      double(0), ...            
        'ROIFinalSmoothingWindows',                   zeros(1, 2, 'int32'), ...
        'ROISkipFrameThreshold_adjusted',             int32(0), ...
        'ROIMSIR_DiffMaxDetection',                   int16(0), ...
        'ROIMSIR_DiffMaxAdjacent',                    int16(0), ...
        'ROIMSIR_FirstFrameIdx',                      int32(0), ...
        'FrameCacheMaxFrames',                        int32(0), ...
        'ROIMeansOperationsReadyFirstReadTF',         false, ...
        'ROIMeansMaxFrameToProcessSecondReadLinIdx',  int32(0), ...
        'ROISpecifyByArgument',                       Element1, ...
        'ROIIgnoreByArgument',                        Element2, ...
        'RecursiveTF',                                false, ...
        'ReturnAllTF',                                false, ...
        'UseCompiledFunctionsTF',                     false ...
    );

%%%%%% --- SkinSegmentConfig struct %%%%%% 

SkinSegmentConfigCode = ...
    struct( ...
        'SkinSegmentTF', false, ... Whether skin segmentation enabled
        'SkinSegmentSeverityFactor', double(0), ... For tuning severity of skin segmentation
        'MorphCloseSEMediumWidth', double(0), ... Width of structuring element for medium 
                                              ... morphological close before tuning.
        'MorphCloseSELargeWidth', double(0), ... Width of structuring element for large 
                                             ... morphological close before tuning.        
        'UseCompiledFunctionsTF', false, ... Whether to use compiled functions        
        'Args', ... Arguments to fuction SkinSegmentMask 
        struct( ...
            'SkinColorSamples_NThresholdPassedTF', false, ...
            'YCbCrThresholdsGeneric', zeros(1, 7, 'single'), ...
            'HSThresholdsGeneric', zeros(1, 2, 'single'), ...
            'YCbCrThresholdsTailored', zeros(1, 8, 'single'), ...
            'YCbCrThresholdsTailored_Sev', zeros(1, 8, 'single'), ...
            'HSThresholdsTailored', zeros(1, 3, 'single'), ...
            'HSThresholdsTailored_Sev', zeros(1, 3, 'single'), ...
            'RangeSEWidth', int16(0), ...
            'RangeThreshold', uint8(0), ...
            'MorphCloseSEMediumWidth_Tuned', int16(0), ...
            'MorphCloseSELargeWidth_Tuned', int16(0) ...
        ), ... 
        'TailoredData', ... Tailored skin-segmentation settings
        struct( ...
            ... Properties determining whether SkinSegment_SetThresholds will be called in function
            ... ROIMeans_FirstRead:
            'OpsReadyTF', false, ...
            'RecentThresholdOpsFrameIdx', int32(0), ...
            'ThresholdOpsInterval', int32(0), ...
            'ThresholdOpsRunCurrentFrameTF', false, ...
            ... Arguments to function SkinSegment_SetThresholds, which sets thresholds for the
            ... "tailored" option used by function SkinSegmentMask:
            'SkinColorSamples_NThreshold', double(0), ...
            'RangePercentile_YCbCrH', zeros(1, 2, 'double'), ...
            'RangePercentile_S', zeros(1, 2, 'double'), ...
            'SkinColorSamples_HighNThreshold', double(0), ...
            'SkinColorSamples_HighNThresholdPassedTF', false, ...
            'RangePercentileHighN_YCbCrH', zeros(1, 2, 'double'), ...
            'RangePercentileHighN_S', zeros(1, 2, 'double'), ...
            'RangePercentileSev_YCbCrH', zeros(1, 2, 'double'), ...
            'RangePercentileSev_S', zeros(1, 2, 'double') ...
        ), ...
        ... Values used by function ConfirmSkinPresent depending on the argument 
        ... PixelColorThresholdsType:
        'ConfirmSkin', ... 
        struct( ...
            'ProportionThresholdPrimary',    single(0), ...
            'ProportionThresholdSecondary1', single(0), ...
            'ProportionThresholdSecondary2', single(0), ...
            'ProportionThresholdSkin',       single(0), ...
            'ProportionThresholdMeans',      single(0)  ...
        ), ...
        'OverSegmentedCheck', ...
        struct( ...
            'CheckTF',                          false, ...
            'ProportionThresholdPrimary',       single(0), ...
            'ProportionThresholdSecondary1',    single(0), ...
            'ProportionThresholdSecondary2',    single(0), ...
            'FramesLowSkinProportionThreshold', double(0), ...
            'NFramesLowSkinProportionStatus',   double(0), ...
            'MorphReductionAmount',             double(0), ...
            'NMorphReductionLimit',             int32(0), ...
            'NMorphReductions',                 int32(0), ...
            'DarknessThreshold',                single(0), ...
            'BelowDarknessThresholdTF',         false, ...
            'NFramesYSingleMean',               single(0), ...
            'PixelColorsAdjustedTF',            false, ...
            'ColorThresAdjustTo',               zeros(1, 9, 'single') ...               
        ) ...
    );       

%%%%%% --- SkinDetectConfig struct %%%%%%

SkinDetectConfigCode = ... 
    struct( ...
        'ROISkinTF', false, ...
        'Thresholds', ...
        struct( ...   
            'SetTF', false, ...
            'SkinColorSamples_NThreshold', double(0), ...
            'SkinColorSamples_NThresholdPassedTF', false, ...
            'SkinColorSamples_HighNThreshold', double(0), ... 
            'SkinColorSamples_HighNThresholdPassedTF', false, ...
            'SkinColorSamples_HighNThresholdIdx', int32(0), ... 
            'ColorThreshold', zeros(1, 3, 'single'), ...
            'ColorThresholdHighN', zeros(1, 3, 'single'), ...
            'RecentThresholdOpsFrameIdx', int32(0), ...
            'ThresholdOpsInterval', int32(0), ...
            'ThresholdOpsRunCurrentFrameTF', false, ...
            'ColorSDThreshold', single(0), ...
            'RGBProbTheta', zeros(4, 1, 'double'), ...
            'YCbCrMeanOfMeans', zeros(1, 3, 'single'), ...
            'YCbCrStdDevOfMeans', zeros(1, 3, 'single'), ...
            'RegionNThreshold', single(0) ...
        ), ...
        'ROISkinSkipFrameThreshold', int32(0), ...
        'ROISkin_BoundingBoxGrowthThreshold', int32(0), ...
        'ROISkin_BoundingBoxGrowthFactor', double(0), ...
        'ROISkin_InitialBoundingBoxScale', double(0), ...
        'ROISkinRegionMinSizeFactor', single(0), ...
        'ROISkinRegionProximityWeight', double(0), ...
        'ROISkinSmoothingWindow', double(0), ...
        'PartitionColInterval', int16(0), ...
        'PartitionRowInterval', int16(0), ...
        'SkinDetectionReadyTF', false, ...
        'ROISkin_BoundingBoxEnlargementFactor', double(0), ...
        'ROISkinSkipFrameThreshold_adjusted', int32(0), ...
        'UseCompiledFunctionsTF', false ...
    );


%%%%%% Set configurations to increase performance %%%%%%

%Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic 
%"Optimization Strategies"

cfg = coder.config('mex');
cfg.GlobalDataSyncMethod = 'NoSync';
cfg.ConstantInputs = 'IgnoreValues';
cfg.ExtrinsicCalls = true; %true to permit display of errors
cfg.SaturateOnIntegerOverflow = false;
cfg.IntegrityChecks = false;
cfg.ResponsivenessChecks = false;


%%%%%% Specify flags to minGW compiler to optimize execution speed %%%%%%

%For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

%The flags are specified as part of the code-generation configuration object. A custom function,
%setbuildargs, is used to specify these flags. For details on the function implementation, see the 
%function file, which is located within folder FacePulseRate. This custom function is based upon 
%Matlab guidance found in
%https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function

%setbuildargs will be evaluated from text within the code-generation object, so it is converted to 
%a character vector prior to execution of the codegen command.

%%%%%% --- Specify the flags as arguments to function setbuildargs %%%%%%

%Argument buildInfo: this variable is assign by the caller (the codegen command executed 
%below) and is not present in the base workspace.

%Second argument: specify a cell array of compiler-specific flags, where each flag is a 
%character vector. As function setbuildargs will be evaluated from text, use double ' quotes for 
%each character vector to maintain the charater vector,
%e.g., {''-Ofast'' ''-fsingle-precision-constant''}.

setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})';

%Assign to code-generation configuration object
cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen SkinDetect.m -report -config cfg -args {iCode, VidFrameCode, VideoReadConfig_VidObjWidthCode, VideoReadConfig_VidObjHeightCode, SkinSegmentConfigCode, ROIGeneralConfigCode, SkinDetectConfigCode, OutputConfig_WriteVideoShowROISkinDiagnosisTFCode, BoundingBoxSkinCode, FirstReadSkinTFCode, ROIForBoundingBoxSkin_FRCode, ROI_SRCode, FramesToProcessLinIdx_SRCode, Notifications_Interval_SRCode, Notifications_LoopStartTime_SRCode, Notifications_LoopCounter_SRCode}
                
%}
