function [IsSkinMask, RegionIndices, NRegions, RegionNPixels, RegionCentroids, RBounded_Uint8, ...
          GBounded_Uint8, BBounded_Uint8, YBounded_Single, CbBounded_Single, ...
          CrBounded_Single, NRows_Matrix, NCols_Matrix] = ...
             SkinDetect_PartitionRegions(VidFrame, BoundingBoxSkin, SkinDetectConfig, ...
                 SkinSegmentConfig, VideoReadConfig_VidObjWidth, VideoReadConfig_VidObjHeight) 
                 %#codegen
%SkinDetect_PartitionRegions    Partition bounded area of a frame into regions that will be  
%                               submitted to steps of the skin-detection algorithm. 
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
%    Partition bounded area of a frame into two-dimensional regions for use in steps of the skin-
%    detection algorithm, which is conducted by function SkinDetect. 
%
%    Before partitioning, crop the frame to a bounded area specified by a bounding box 
%    (BoundingBoxSkin). In the first-read operations, the bounding box is set by function 
%    ROIMeans_FirstRead_SetBoundingBoxes; in the second-read operations, the bounding box is set by 
%    function ROIMeans_SecondRead_SkinDetect. 
%    
%    To partition, first apply skin segmentation and return a logical matrix (also termed a     
%    skin-segmentation mask) where pixels classified as skin = true. Then, break regions of true 
%    values into smaller regions by applying grid lines at specified intervals of rows and columns. 
%    As the grid lines consist of false values, this has the effect of breaking regions into 
%    regions that fit within the grid lines.
%   
%    The skin segmentation mask with gridlines superimposed (IsSkinMask) is assigned as output. 
%    Additionally, an index of pixels corresponding to each region and the centroids of each region
%    are assigned as output. Regarding the centroids, note that a centroid may actually fall on a 
%    pixel marked as non-skin by the skin-segmentation mask if this pixel is the centroid of a 
%    region.
%
%    Additionally, the output of intermediate operations, such as color channels of the bounded 
%    frame, is returned for reuse by other steps of the skin-detection algorithm.   
%
%    For further description of purpose of partitioning, see section "Partitioning frame into 
%    regions to classify" in the notes of function SkinDetect.
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

%Call function as extrinsic so that stack trace can be displayed
coder.extrinsic('error');

%Declare variables:

%                                             Upp. Bounds  Var. Size (T/F)
coder.varsize('RegionIndices',                [400, 1],    [1, 0]);
coder.varsize('RegionIndices.PixelIdxList',   [inf, 1],    [1, 1]);
coder.varsize('IsSkinMask_Range',             [inf, inf],  [1, 1]);


%%%%%% Bound ith frame and return skin-segmentation mask %%%%%%

%For the bounded area of the frame, conduct skin-segmentation to return a 2-dimensional logical   
%matrix where pixels classified as skin are true.
%The skin-segmentation function converts the frame to YCbCr color channels for its operations; for
%efficiency, return these color channels for reuse by other functions that require these channels
%because the YCbCr conversion is computationally expensive.

%Height and width of bounding box
NRows_Matrix = BoundingBoxSkin(4);
NCols_Matrix = BoundingBoxSkin(3);

%Prevent dynamic memory allocation from colon operator by asserting lengths
%Note: these values also constrain the maximum frame dimensions that can be used in function
%FacePulseRate. If modified, modify the maximum frame dimensions stated in the description in
%function FacePulseRate.
assert(NRows_Matrix <= 5000);
assert(NCols_Matrix <= 5000);

%Arguments to function SkinSegmentMask, which returns the skin-segmentation mask:

% - Bound frame, separate by colorspace channels, and convert to type single
%   These channels are also used for function SkinDetect_RegionMetrics, which is called by function
%   SkinDetect_RejectRegions. 
%   Local function.
[RBounded_Uint8, GBounded_Uint8, BBounded_Uint8] = ...
    BoundSeparateChannels(VidFrame, BoundingBoxSkin, NRows_Matrix, NCols_Matrix, ...
        VideoReadConfig_VidObjWidth, VideoReadConfig_VidObjHeight);

% - Assign as a variable rather than a constant for code-generation purposes
IsSkinMask_Range = logical([]);

%Note: SkinSegmentMask is a custom function located within folder 'FacePulseRate'. 
[IsSkinMask,      ... logical matrix where pixels classified as skin = true
 ~, ...   
 YBounded_Single, ... bounded frame in YCbCr colorspace, separated by channel; type single
 CbBounded_Single, ...
 CrBounded_Single] = ... 
    SkinSegmentMask( ...
        RBounded_Uint8,                          ... Bounded frame in RGB colorspace separated by 
                                                 ... channel; type uint8.
        GBounded_Uint8, ...
        BBounded_Uint8, ... 
        single([]),                              ... Unused arguments                                   
        single([]), ...
        single([]), ...
        single([]), ...                                
        single([]), ...
        IsSkinMask_Range, ...     
        int32(NRows_Matrix),                     ... Number of rows of an input matrix      
        int32(NCols_Matrix),                     ... Number of columns of an input matrix
        false,                                   ... Whether to return a count of pixels classified 
                                                 ... as skin.
        true,                                    ... Whether to use thresholds that are tailored
        true,                                    ... Whether to return Y channel of the YCbCr 
                                                 ... colorspace.
        true,                                    ... Whether to return Cb and Cr channels of the 
                                                 ... YCbCr colorspace. 
        false,                                   ... Whether to return the H and S channels of the 
                                                 ... HSV colorspace (HSingle).                                   
        true,                                    ... Whether to use severe tailored thresholds            
        true,                                    ... Whether the morphological close operation will  
                                                 ... be conducted with a high level of severity.
        int32(-1),                               ... Optional X-coordinate offset; use -1 to 
                                                 ... ignore; type int32.
        int32(-1),                               ... Optional Y-coordinate offset; use -1 to 
                                                 ... ignore; type int32.                                               
        SkinSegmentConfig.Args,                  ... Configurations
        SkinSegmentConfig.UseCompiledFunctionsTF ... Whether to use compiled functions
    );
   

%%%%%% Partition skin-segmentation mask into smaller regions using grid lines %%%%%%

%Specify the intervals to use to partition the skin-segmentation mask
%Scalar; type single.
%Note: Values specified in function SkinDetectConfig_Setup.
PartitionColInterval = SkinDetectConfig.PartitionColInterval;
PartitionRowInterval = SkinDetectConfig.PartitionRowInterval; 

%Insert vertical lines:

Col_ith = int16(1);

while Col_ith <= NCols_Matrix
              
    for j = 1 : NRows_Matrix 
        
        IsSkinMask(j, Col_ith) = false;        
    end    
    
    Col_ith = Col_ith + PartitionColInterval;  
end

%Insert horizontal lines: 

%Preallocate for code-generation purposes
Row_ith = coder.nullcopy( int16(0) );

for i = 1 : NCols_Matrix

    Row_ith = int16(1);

    while Row_ith <= NRows_Matrix 
        
       IsSkinMask(Row_ith, i) = false;
       
       Row_ith = Row_ith + PartitionRowInterval;         
    end            
end   

%%%%%% --- Verify number of potential regions is at or below expected number %%%%%%

%If the number of regions is potentially greater than the upper bounds used in the compiled 
%functions. Such an error would be the result of an implementation error.

%Find the number of column partitions and the number of row partitions
%Local function.
[NColPartitions, NRowPartitions] = ...
    FindNPartitions(Col_ith, PartitionColInterval, NCols_Matrix, Row_ith, ...
        PartitionRowInterval, NRows_Matrix);

%Note: NColPartitions * NRowPartitions approximates the number of regions; 250 is added because 
%many possible regions will likely have been removed by skin segmentation.
%Note: if frame dimensions exceed 5000 x 5000, integer overflow is possible in this calculation.
if NColPartitions * NRowPartitions > 400 + 250

    %Throw error 
    %Called as extrinsic so that stack trace can be displayed.
    error( ...
        'Component:InternalError', ...
        ['Internal Error (SkinDetect_PartitionRegions): Number of regions exceeds upper ', ...
         ' bounds set for compiled function'] ...        
    );          
end


%%%%%% Return region information  %%%%%%

%Find connected areas (i.e, regions)
%Find connected areas, using connection criteria of 8. Return information about each of the 
%regions, including the linear indices corresponding to the pixels in each region, the number of
%regions, the number of pixels in each region, and the centroids of each region.

%Note: a centroid may fall on a pixel marked as non-skin by the skin-segmentation mask if the pixel  
%is the centroid of a region.     

%Note: function SkinDetect_RegionInfo is a custom function located within folder 'FacePulseRate'.
[RegionIndices,     ... Linear indices of pixels corresponding to each region 
                    ... (RegionIndices.PixelIdxList).
                    ... M regions x 1 non-scalar struct; elements: N pixels x 1, type uint32.
 NRegions,          ... Number of regions; scalar, type int32.
 RegionNPixels,     ... The number of pixels (i.e., area) of each region. M regions x 1 column 
                    ... vector; type single.
 RegionCentroids] = ... Centroids (X, Y) of each region. M regions x 2 matrix; type int32. 
    SkinDetect_RegionInfo(IsSkinMask);

% <<<<< For tesing purposes: View centroids superimposed on image >>>>>

%{

%convert centroid (X, Y) coordinates to a linear index
centroids_per_region_mat_r = round(centroids_per_region_mat, 0);
centroids_cols = centroids_per_region_mat_r(:, 1);
centroids_rows = centroids_per_region_mat_r(:, 2);
centroids_per_region_linearIdx = sub2ind(size(IsSkinMask), centroids_rows, centroids_cols);

%mark centroids by black (0)
IsSkinMaskTest = IsSkinMask;
IsSkinMaskTest(centroids_per_region_linearIdx) = 0;

%view centroids superimposed on image
imtool(IsSkinMaskTest)

%}

% <<<<<     .     .     .     .     .     .     .     .     .     >>>>> 


end %end main function


%=============================================================================================
%Local functions 
%=============================================================================================


%=============================================================================================
function [RBounded_Uint8, GBounded_Uint8, BBounded_Uint8] = ...
             BoundSeparateChannels(VidFrame, BoundingBoxSkin, nRows_IsSkinMask_int16, ...
                 nCols_IsSkinMask_int16, nCols_Full_int16, nRows_Full_int16)                
%BoundSeparateChannels  Bound the input frame and separate it into its colorspace channels.
%
%    Note: 
%
%    The parfor-loop is slower than a for-loop when run in Matlab code, so use the parfor-loop only  
%    for code generation.


%%%%%% Code-generation settings %%%%%%

%Inline function
coder.inline('always');


%%%%%% Code generation running %%%%%%

if ~ coder.target('MATLAB') %code generation running

    %Cast to int32 to prevent overflow when converting to linear index
    %Scalars; type int32.
    nRows_IsSkinMask = int32(nRows_IsSkinMask_int16);
    nCols_IsSkinMask = int32(nCols_IsSkinMask_int16); 
    nCols_Full       = int32(nCols_Full_int16); 
    nRows_Full       = int32(nRows_Full_int16);
    
    %X and Y-coordinates
    %Cast to int32 to prevent overflow when converting to linear index.
    %Scalars; type int32.
    x = int32( BoundingBoxSkin(1) ); 
    y = int32( BoundingBoxSkin(2) ); 

    %Preallocate channel matrices:
    
    %Red channel 
    %M x N matrix; type uint8.
    RBounded_Uint8 = coder.nullcopy( zeros(nRows_IsSkinMask, nCols_IsSkinMask, 'uint8') );
    
    %Green channel 
    %M x N matrix; type uint8.    
    GBounded_Uint8 = coder.nullcopy( zeros(nRows_IsSkinMask, nCols_IsSkinMask, 'uint8') );
    
    %Blue channel 
    %M x N matrix; type uint8.    
    BBounded_Uint8 = coder.nullcopy( zeros(nRows_IsSkinMask, nCols_IsSkinMask, 'uint8') );

    %Bounding offsets
    %Scalars; type int32.
    %Note: the step prevents repeated subtraction by one in the parfor loop.
    ColOffset = x - 1;
    RowOffset = y - 1;    
    
    %Number of elements in one color channel of the full frame
    %Scalar; type int32.
    NPageElements = nCols_Full * nRows_Full;
    
    %Number multiplied by 2
    %Scalar; type int32.
    NPageElementsBy2 = NPageElements * 2;
    
    %Bound frame and separate to channels:
    
    %Loop across columns
    parfor i = 1 : nCols_IsSkinMask 

        %Adjust column index to align with coordinate plane of full frame
        iFull = i + ColOffset;
        
        %Loop across rows
        for j = 1 : nRows_IsSkinMask             
            
            %Adjust row index to align with coordinate plane of full frame
            jFull = j + RowOffset;
            
            %Convert from subscript indices to a linear index for more efficient indexing
            %Scalar; type int32.
            %Note: In compiled C code, the faster indexing outweighs the cost of this conversion.
            LinIdxFull = jFull + (iFull - 1) * nRows_Full;
            
            %Red channel element:
            
            %Extract value from full frame                      
            jth = VidFrame(LinIdxFull); %#ok<PFBNS>

            %Insert value into bounded frame
            RBounded_Uint8(j, i) = jth;

            %Green channel element:
            
            %Extract value from full frame
            jth = VidFrame(LinIdxFull + NPageElements); 

            %Insert value into bounded frame
            GBounded_Uint8(j, i) = jth;

            %Blue channel element:
            
            %Extract value from full frame
            jth = VidFrame(LinIdxFull + NPageElementsBy2);

            %Insert value into bounded frame
            BBounded_Uint8(j, i) = jth;
        end       
    end

    
%%%%%% Code generation not running %%%%%%   

else 

    %Bound frame
    %M x N x 3 array; type uint8.
    VidFrame = ...
        VidFrame( ...
            BoundingBoxSkin(2) : BoundingBoxSkin(2) + (BoundingBoxSkin(4) - 1), ... rows
            BoundingBoxSkin(1) : BoundingBoxSkin(1) + (BoundingBoxSkin(3) - 1), ... columns
            :                                                                   ... pages
        ); 
    
    %Separate by channel
    %M x N matrices; type uint8.
    RBounded_Uint8 = VidFrame(:, :, 1); %Red channel;   M x N matrix; type uint8
    GBounded_Uint8 = VidFrame(:, :, 2); %Green channel; M x N matrix; type uint8
    BBounded_Uint8 = VidFrame(:, :, 3); %Blue channel;  M x N matrix; type uint8
end


end %end local function


%=============================================================================================
function [NColPartitions, NRowPartitions] = ...
             FindNPartitions(Col_ith, PartitionColInterval, nCols_IsSkinMask, Row_ith, ...
                 nRows_IsSkinMask, PartitionRowInterval)
%FindNPartitions   Find the number of column partitions and the number of row partitions.


%Inline function
coder.inline('always');


%Number of column partitions:

if Col_ith > nCols_IsSkinMask
    
    ColMax = Col_ith - PartitionColInterval; 
   
else
    
    ColMax = Row_ith;
end

NColPartitions = ColMax / PartitionColInterval + 1;

%Number of row partitions:

if Row_ith > nRows_IsSkinMask
    
    RowMax = Row_ith - PartitionRowInterval; 
   
else
    
    RowMax = Row_ith;
end

NRowPartitions = RowMax / PartitionRowInterval + 1;


end %end local function
