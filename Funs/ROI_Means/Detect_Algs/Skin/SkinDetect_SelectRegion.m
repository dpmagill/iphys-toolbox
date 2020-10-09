function [ROI_Selected_ith, SkinTF_ith, HasROITF_SkinNotPresent_ith, RegionSelectedLinIdx, ...
          RegionPoints_Realigned, ROIPredicted_CenterX, ROIPredicted_CenterY] = ...         
             SkinDetect_SelectRegion(ROI_SR_ith, ROIForBoundingBoxSkin_FR, BoundingBoxSkin, ...
                 IsSkinMask, RegionPassAllThresholdsTF_LogIdx, NRegions, NRegionsPass, ...
                 RegionRGBProbSkin, RegionZ_Y, RegionZ_Cb, RegionZ_Cr, RegionCentroids, ...
                 RegionIndices, RegionNPixels, VidFrame, FirstReadSkinTF, SkinDetectConfig, ...
                 SkinSegmentConfig, ROIGeneralConfig, VideoReadConfig_VidObjWidth, ...
                 VideoReadConfig_VidObjHeight) %#codegen                                   
%SkinDetect_SelectRegion   Select the partitioned region that appears the most likely to be skin.
%  
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function SkinDetect.
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
%    Following rejection of some regions (see function SkinDetect_RejectRegions), select one of the
%    remaining regions as the skin detection.
%
%    For further discussion of the selection process, see the description of the skin-detection 
%    algorithm in the file of function SkinDetect.
%   
%    Then, determine the ROI values, ROI_Selected_ith, of the selected region. Determining the ROI 
%    values includes expanding the size of the region to result in a size that captures more of the 
%    face. Additionally, run additional checks to determine whether the ROI contains skin. A true 
%    return value for SkinTF_ith indicates that the ROI passed these checks. If SkinTF_ith is true, 
%    ProportionSkinPixelsTooLowTF_ith will be false and vice versa.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.   


%%%%%% Code-generation settings %%%%%%

%Inline function
coder.inline('always');

%Declare variables:

%Note: set bounds so that these variables do not use dynamic memory allocation, increasing 
%efficiency.

%                                                      Upp. Bounds  Var. Size (T/F)
coder.varsize('RegionCentroids_X',                     [400, 1],    [1, 0]);
coder.varsize('RegionCentroids_Y',                     [400, 1],    [1, 0]);
coder.varsize('RegionPoints_Proximity',                [400, 1],    [1, 0]); 
coder.varsize('Points',                                [400, 1],    [1, 0]);
coder.varsize('RegionRGBProbSkin_LinIdx',              [400, 1],    [1, 0]); 
coder.varsize('RegionPoints_RGBProbSkin',              [400, 1],    [1, 0]); 
coder.varsize('RegionZ_Difference',                    [400, 1],    [1, 0]);
coder.varsize('RegionZ_Difference_LinIdx',             [400, 1],    [1, 0]);
coder.varsize('RegionZ_Y_Standardized',                [400, 1],    [1, 0]);
coder.varsize('RegionZ_Cb_Standardized',               [400, 1],    [1, 0]);
coder.varsize('RegionZ_Cr_Standardized',               [400, 1],    [1, 0]);
coder.varsize('RegionPoints_YCbCrSimilaritySkin',      [400, 1],    [1, 0]); 
coder.varsize('RegionZ_Y_Std',                         [400, 1],    [1, 0]);    
coder.varsize('RegionPoints_ColorSimilarity',          [400, 1],    [1, 0]); 
coder.varsize('RegionDistance_LinIdx',                 [400, 1],    [1, 0]);
coder.varsize('RegionPassAllThresholdsTF_LinIdx',      [400, 1],    [1, 0]);
coder.varsize('RegionNotPassAllThresholdsTF_LinIdx',   [400, 1],    [1, 0]);


%%%%%% Setup %%%%%%

%Assert value to limit dynamic memory when using the colon operation with this variable.
assert(NRegionsPass <= 400);

%Convert variable RegionPassAllThresholdsTF_LogIdx to linear indices for indexing efficiency
%Local function.
%Type uint16.
[RegionPassAllThresholdsTF_LinIdx, RegionNotPassAllThresholdsTF_LinIdx] = ...
    LogToLin(RegionPassAllThresholdsTF_LogIdx, NRegions, NRegionsPass);


%%%%%% Assign selection points: Proximity to predicted ROI %%%%%%

%Assign selection points to regions based upon proximity to ROI predicted from face-detection 
%algorithms.

%%%%%% --- Find the center point of the ROI used as the basis for the current bounding box %%%%%%

%Find the center point of the ROI used as the basis for the current bounding box.

%In the case of the first read, the ROI is the median of the last few ROIs detected by the 
%face-detection algorithms (for details, see function ROIMeans_FirstRead_SetBoundingBoxes). In the 
%case of the second read, the ROI is interpolated from ROIs detected by the face-detection
%algorithms from nearby frames. This interpolated ROI may also be interpolated from skin-detection 
%ROIs from the first read if the current frame is near where the first-read skin detection became    
%enabled.

%ROI used as the basis for the current bounding box:

%If first read
if FirstReadSkinTF           
    
    %Rename for current use.
    %Median ROI from last few frames
    %This ROI was assigned in function ROIMeans_FirstRead_SetBoundingBoxes, which was
    %called by function ROIMeans_FirstRead.
    ROIPredicted = ROIForBoundingBoxSkin_FR;

%If second read    
else     
    
    %Interpolated ROI for current frame
    %This ROI was assigned by function ROIMSIR, which was called in function 
    %ROIMeans_FirstRead_TakeMeans. 
    %1 x 4 row vector; type int16.
    ROIPredicted = ROI_SR_ith;            
end

%Adjust upper-left-hand X- and Y-coordinates of predicted ROI to coordinates of bounding box. 
%1 x 4 row vector; type int16.
ROIPredicted(1) = ROIPredicted(1) - (BoundingBoxSkin(1) - 1); %adjust X-left
ROIPredicted(2) = ROIPredicted(2) - (BoundingBoxSkin(2) - 1); %adjust Y-upper

%Find center of predicted ROI
%Optimize division by 2 by bit-wise operation.
%Scalars; type int16.
ROIPredicted_CenterX = ROIPredicted(1) + bitshift( ROIPredicted(3), -1 ); %X-left + width / 2    
ROIPredicted_CenterY = ROIPredicted(2) + bitshift( ROIPredicted(4), -1 ); %Y-upper + height / 2

%%%%%% --- Compare center coordinates of predicted ROI to centroids to assign points %%%%%%

%Find distance between the center point of the predicted ROI and the centroid of each region 
%(distance formula).
%P non-rejected regions x 1 colum vector; type int16.

distances = coder.nullcopy( zeros(NRegionsPass, 1, 'int16') );

for i = 1 : NRegionsPass

    ii = RegionPassAllThresholdsTF_LinIdx(i);
    
    %Scalars; type int16.
    DeltaX = RegionCentroids(ii, 1) - ROIPredicted_CenterX;
    DeltaY = RegionCentroids(ii, 2) - ROIPredicted_CenterY; 
    
    %Cast to type int32 to prevent integer overflow during multiplication
    %Scalars; type int32.
    DeltaX_int32 = int32(DeltaX);
    DeltaY_int32 = int32(DeltaY);    
    
    %Note: multiply is used in place of ^2 for efficiency.
    %Also, type must be at least 32 bits to prevent integer overflow.
    SumSquares = DeltaX_int32 * DeltaX_int32 + DeltaY_int32 * DeltaY_int32;    
    
    %Cast to single as floating-point type required for function sqrt
    distances(i) = sqrt( single(SumSquares) );    
end

%Assign points according to rank order of distances
%The region with the best (smallest) distance gets points equal to the number of non-rejected 
%regions. That is, if there are 33 regions that were not rejected, the best region gets 33 points 
%and the worst region gets 1 point.

%Order distances (only non-rejected) from larger to smallest 
%P non-rejected regions x 1 colum vector; type double.
[~, RegionDistance_LinIdx] = sort( distances, 'descend' );

%Preallocate points vector for proximity
%P non-rejected regions x 1 colum vector; type uint16.
RegionPoints_Proximity = coder.nullcopy( zeros(NRegionsPass, 1, 'uint16') );

%Order points by ordered distances index 
%P non-rejected regions x 1 colum vector; type uint16.
for i = uint16(1) : NRegionsPass
    
    ii = RegionDistance_LinIdx(i);
    
    RegionPoints_Proximity(ii) = i;
end


%%%%%% Assign selection points: RGB probability %%%%%%     

%Assign selection points to regions based upon RGB probability

%Note: see notes in function SkinDetect.

%Assign points according to rank order of RegionRGBProbSkin
%The region with the best (greatest) RegionRGBProbSkin gets points equal to the number of
%non-rejected regions. That is, if there are 33 regions that were not rejected, the best region
%gets 33 points and the worst region gets 1 point.

%Order RegionRGBProbSkin (only non-rejected regions) from smallest to largest
%P non-rejected regions x 1 colum vector; type double.
[~, RegionRGBProbSkin_LinIdx] = ...
    sort( RegionRGBProbSkin(RegionPassAllThresholdsTF_LinIdx), 'ascend' );

%Preallocate points vector for RGB probability skin
%Specify type uint16 for faster evaluation where used.
%P non-rejected regions x 1 colum vector; type uint16.
RegionPoints_RGBProbSkin = coder.nullcopy( zeros(NRegionsPass, 1, 'uint16') );

%Order points by ordered RegionRGBProbSkin_LinIdx index 
%P non-rejected regions x 1 colum vector; type uint16.
for i = uint16(1) : NRegionsPass
    
    ii = RegionRGBProbSkin_LinIdx(i);
    
    RegionPoints_RGBProbSkin(ii) = i;
end


%%%%%% Assign selection points: YCbCr means similarity %%%%%% 

%Assign selection points to regions for similarity of YCbCr means to the grand YCbCr means from 
%primary face-detection algorithm ROIs. 

%%%%%% --- Standardize z-scores to balance the contribution of dimensions %%%%%%

%Standardize Y, Cb, and Cr z-score vectors 
%Exclude rejected regions. 
%P non-rejected regions x 1 colum vectors; type single.

%Cast to type single for use in function Standardize
NRegionsPass_Single = single(NRegionsPass);

%Local function.
RegionZ_Y_Standardized  = ...
    Standardize( RegionZ_Y, RegionPassAllThresholdsTF_LinIdx,  NRegionsPass_Single );

RegionZ_Cb_Standardized = ...
    Standardize( RegionZ_Cb, RegionPassAllThresholdsTF_LinIdx, NRegionsPass_Single );

RegionZ_Cr_Standardized = ...
    Standardize( RegionZ_Cr, RegionPassAllThresholdsTF_LinIdx, NRegionsPass_Single );             

%%%%%% --- Composite scores %%%%%%

%Sum absolute values of standardized z-scores across Y, Cb, and Cr dimensions for composite 
%difference score.
%P non-rejected regions x 1 colum vector; type single.

RegionZ_Difference = coder.nullcopy( zeros(NRegionsPass, 1, 'single') );

for i = 1 : NRegionsPass

    RegionZ_Difference(i) = ...
        abs( RegionZ_Y_Standardized(i) )  + ...
        abs( RegionZ_Cb_Standardized(i) ) + ...
        abs( RegionZ_Cr_Standardized(i) );        
end


%%%%%% --- Assign selected points %%%%%%

%Assign points according to the rank order of the difference. The region with the best (least) 
%difference gets points equal to the number of non-rejected regions. For example, if there are 33 
%regions that were not rejected, the best region gets 33 points and the worst region gets 1 point.

%Order difference (only non-rejected) from smallest to largest absolute difference
%P non-rejected regions x 1 colum vector; type double.
[~, RegionZ_Difference_LinIdx] = sort(RegionZ_Difference, 'descend');

%Preallocate vector
%Specify type uint16 for faster evaluation where used.
%P non-rejected regions x 1 colum vector; type uint16.
RegionPoints_YCbCrSimilaritySkin = coder.nullcopy( zeros(NRegionsPass, 1, 'uint16') );
    
%Order points by absolute difference index 
%P non-rejected regions x 1 colum vector; type uint16.
for i = uint16(1) : NRegionsPass
    
    ii = RegionZ_Difference_LinIdx(i);
    
    RegionPoints_YCbCrSimilaritySkin(ii) = i;
end


%%%%%% Determine selected region based upon region with highest points %%%%%%

%Select region with highest points (out of passing regions).

%Note: see notes in function SkinDetect.

%%%%%% --- Apply weights and sum %%%%%%

%Specify weight to apply to proximity relative to skin similarity
%This weight is specified as an argument to function FacePulseRate.
%Scalar; type single.
ROISkinRegionProximityWeight = single( SkinDetectConfig.ROISkinRegionProximityWeight );

%Preallocate vector for sum of selection points for each region 
%Specify type uint16 for faster evaluation where used.
%P non-rejected regions x 1 colum vector; type uint16.
RegionPoints = coder.nullcopy( zeros(NRegionsPass, 1, 'uint16') );

for i = 1 : NRegionsPass

    %Combine points (to the mean) from RGB probability and YCbCr likeness
    %Optimize division by 2 by bit-wise operation.
    RegionPoints_ColorSimilarity_ith = ...
        bitshift(RegionPoints_RGBProbSkin(i) + RegionPoints_YCbCrSimilaritySkin(i), -1);       

    %Apply weight to proximity scores
    %Cast to type single for calculation.
    RegionPoints_Proximity_ith = ...
        uint16( single( RegionPoints_Proximity(i) ) * ROISkinRegionProximityWeight );
    
    RegionPoints(i) = RegionPoints_Proximity_ith + RegionPoints_ColorSimilarity_ith;
end

%%%%%% --- Select region with highest points %%%%%%    

%Assign linear index indicating the region with the maximum points

%Initialize value of region with the most points 
%Assign a starting value that is lower than the lowest possible points of any region.
MaxPoints = uint16(0);

%Initialize index corresponding to the region with the most points
MaxPointsIdx = uint16(0);

for i = 1 : NRegionsPass
                
    RegionPoints_ith = RegionPoints(i);
    
    if RegionPoints_ith > MaxPoints
        
        MaxPoints = RegionPoints_ith;
        
        MaxPointsIdx = uint16(i);
    end    
end


%Align index out of index of all regions (not just passing regions)
%Cast to type uint16.
%Scalar; type uint16.
RegionSelectedLinIdx = ...
    uint16( RegionPassAllThresholdsTF_LinIdx(MaxPointsIdx) );

%Demonstrate to code generation that variable is scalar
%This variable needs to be a scalar to index into a non-scalar struct.
RegionSelectedLinIdx = RegionSelectedLinIdx(1);

%%%%%% --- Adjust region points vector to align with all regions (not just passing regions) %%%%%%

%This adjusted vector will be returned for use in a later function.

RegionPoints_Realigned = coder.nullcopy( zeros(NRegions, 1, 'uint16') );

RegionPoints_Realigned(RegionPassAllThresholdsTF_LinIdx) = RegionPoints;

%Assign zeros to elements corresponding to non-passing regions
RegionPoints_Realigned(RegionNotPassAllThresholdsTF_LinIdx) = uint16(0);


%%%%%% Determine ROI of selected region %%%%%% 
        
%Determine the ROI values, ROI_Selected_ith, of the selected region. Determining the ROI values
%includes expanding the size of the region to result in a size that captures more of the face.
%Additionally, run additional checks to determine whether the ROI contains skin. A true return 
%value for SkinTF_ith and HasROITF_SkinPresent_ith indicates that the ROI passed these checks. 

%Note: SkinDetect_SelectedRegionROI is a custom function located within folder 'FacePulseRate'. 
[ROI_Selected_ith, SkinTF_ith, HasROITF_SkinNotPresent_ith] = ...
    SkinDetect_SelectedRegionROI(RegionSelectedLinIdx, BoundingBoxSkin, RegionIndices, ...
        VidFrame, IsSkinMask, RegionNPixels, ROIGeneralConfig, VideoReadConfig_VidObjWidth, ...
        VideoReadConfig_VidObjHeight, SkinDetectConfig, SkinSegmentConfig); 


end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function [LinIdx_True, LinIdx_False] = LogToLin(LogIdx, NRegions, NRegionsPass)            
%LogToLin   Convert a logical index to linear indices.
%
%    Description:
%
%    Assign a linear index, LinIdx_True, to correspond to elements of the logical index that equal
%    true. Assign a linear index, LinIdx_False, to correspond to elements of the logical index that 
%    equal false.


%Inline function
coder.inline('always');


NRegions_uint16 = uint16(NRegions);

Counter_True  = uint16(0);
Counter_False = uint16(0);

LinIdx_True  = coder.nullcopy( zeros(NRegionsPass, 1, 'uint16') );
LinIdx_False = coder.nullcopy( zeros(NRegions_uint16 - NRegionsPass, 1, 'uint16') );

for i = 1 : NRegions_uint16

    if LogIdx(i)
    
        Counter_True = Counter_True + 1;
        
        LinIdx_True(Counter_True) = i;
        
    else
        
        Counter_False = Counter_False + 1;
        
        LinIdx_False(Counter_False) = i;        
    end
end


end %end local function


%=============================================================================================
function StandardizedOut = Standardize(VectorIn, LinIdx, NLinIdx)            
%Standardize    Conduct standardization.  
        

%Inline function
coder.inline('always');


%%%%%% Mean of indexed vector %%%%%%

%Preallocate accumulator
Sum = single(0);

for i = 1 : NLinIdx
    
    ii = LinIdx(i);
    
    Sum = Sum + VectorIn(ii);    
end

%Take mean
VectorMean = Sum / NLinIdx;


%%%%%% Standard deviation of indexed vector %%%%%%

%Preallocate accumulator
SumSquares = single(0);

for i = 1 : NLinIdx
   
    ii = LinIdx(i);
   
    Deviation = VectorIn(ii) - VectorMean;
    
    %Note: multiply used in place of ^2 for efficiency
    Deviation = Deviation * Deviation;
    
    SumSquares = SumSquares + Deviation;
end

VectorStd = sqrt( SumSquares / (NLinIdx - 1) );


%%%%%% Standardized scores of indexed vector %%%%%%

StandardizedOut = coder.nullcopy( zeros(NLinIdx, 1, 'single') );

for i = 1 : NLinIdx

    ii = LinIdx(i);
    
    StandardizedOut(i) = (VectorIn(ii) - VectorMean) / VectorStd; 
end   
 
        
end %end local function

