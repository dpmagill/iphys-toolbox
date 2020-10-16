function [ROI_Selected_ith, SkinTF_ith, HasROITF_SkinNotPresent_ith] = ...
             SkinDetect_SelectedRegionROI(RegionSelectedLinIdx, BoundingBoxSkin, RegionIndices, ...
                 VidFrame, IsSkinMask, RegionNPixels, ROIGeneralConfig, ...
                 VideoReadConfig_VidObjWidth, VideoReadConfig_VidObjHeight, ...
                 SkinDetectionConfig, SkinSegmentConfig) %#codegen                 
%SkinDetect_SelectedRegionROI   Determine ROI of the selected region.
%  
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function SkinDetect_SelectRegion.
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
%    Determine the ROI values, ROI_Selected_ith, of the selected region. Determining the ROI values
%    includes expanding the size of the region to result in a size that captures more of the face.
%    Additionally, run additional checks to determine whether the ROI contains skin. A true return 
%    value for SkinTF_ith indicates that the ROI passed these checks. If SkinTF_ith is true, 
%    ProportionSkinPixelsTooLowTF_ith will be false and vice versa.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code-generation settings %%%%%%

%Inline function
coder.inline('always');


%%%%%% Determine ROI based on extrema of selected region %%%%%% 

%Find the minimum and maximum extrema of the selected region as row and column subscripts.

%Note: because [X, Y] coordinates are interchangeable with [row, column] coordinates, this implies
%that higher Y values are spatially lower on the Y axis.

%Initialize minimum and maximum row and column extrema 
%For the minimum, these values should be smaller than any possible values.
%For the maximum, these values should be larger than any possible values.
RowMin = uint32(5001);
RowMax = uint32(0);
ColMin = uint32(5001);
ColMax = uint32(0);

nRows = uint32( BoundingBoxSkin(4) );

%Loop across pixel linear indices of the selected region to ...
% - Convert to row and column subscripts
% - Find the minimum extrema (row and column subscript minimums)
% - Find the maximum extrema (row and column subscript maximums)
%Note: linear index to subscript algorithm adapted from Matlab function ind2sub.
for i = 1 : RegionNPixels(RegionSelectedLinIdx)

    %Extract ith pixel linear index 
    %Scalar; type uint32.
    %Note: RegionIndices.PixelIdxList is an M regions x 1 non-scalar struct; each row consists of  
    %an N x 1 column vector (type uint32) of linear indices corresponding to the pixels of a 
    %region.
    linIdx_ith = RegionIndices(RegionSelectedLinIdx).PixelIdxList(i);
    
    %Convert to row subscript
    Row_ith = rem( linIdx_ith - 1, nRows ) + 1;
    
    %Assign as minimum row if smallest row value encountered
    if Row_ith < RowMin
        
       RowMin = Row_ith;       
    end
    
    %Assign as maximum row if largest row value encountered
    if Row_ith > RowMax
        
       RowMax = Row_ith;       
    end
 
    %Convert to column subscript
    Col_ith = ( linIdx_ith - Row_ith ) / nRows + 1;

    %Assign as minimum column if smallest column value encountered
    if Col_ith < ColMin
        
       ColMin = Col_ith;       
    end
    
    %Assign as maximum column if largest column value encountered    
    if Col_ith > ColMax
        
       ColMax = Col_ith;       
    end
end 

%Assign values of ROI based on extrema
%Cast to type int16.
%Scalars; type int16.
ROIRegionSelected_X = int16(ColMin);
ROIRegionSelected_Y = int16(RowMin);
ROIRegionSelected_W = int16(ColMax - ColMin + 1);
ROIRegionSelected_H = int16(RowMax - RowMin + 1);


%%%%%% Adjust coordinates to the coordinate plane of the full frame %%%%%%

%Adjust the [X, Y] coordinates to undo change to [X, Y] as a result of cropping. This adjustment
%will place [X, Y] in the coordinate plane of the full (uncropped) frame so that [X, Y] can be used 
%in the output video. To do so, add back distances of X and Y that were changed by cropping.

%Note: 1 pixel length is subtracted from the [X, Y] that is added back because the previous 
%cropping changed [Xoriginal, Yoriginal] to [1, 1]; that is, the cropping moved the coordinates a
%distance of Xoriginal - 1 and Yoriginal - 1.

%1 x 4 row vector; type int16.
ROIRegionSelected_FullFrame = coder.nullcopy( zeros(1, 4, 'int16') );

ROIRegionSelected_FullFrame(1) = ROIRegionSelected_X + (BoundingBoxSkin(1) - 1);
ROIRegionSelected_FullFrame(2) = ROIRegionSelected_Y + (BoundingBoxSkin(2) - 1);
ROIRegionSelected_FullFrame(3) = ROIRegionSelected_W;
ROIRegionSelected_FullFrame(4) = ROIRegionSelected_H;


%%%%%% Expand width and/or height of ROI according to specified thresholds %%%%%%

%The ROI is expanded to increase coverage of the face or skin because skin regions, especially 
%after partitioning, is likely quite small.

%The ROI is expanded according to minimums specified by ROIWidthMin and ROIHeightMin, which are 
%arguments to function FacePulseRate used to specify the minimum face size. The ROI values are set
%to be 25% larger than ROIMinWidthProportion and ROIMinHeightProportion. Rather than expand the ROI 
%up to the minimum face size, it is expanded to be 25% larger than these minimums based on the  
%assumption that the size of face will be larger than the minimums for most frames. 

%Specify arguments to function SkinDetect_EnlargeROI:

%ROIWidthMin: width minimum, which is 25% larger than the value of ROIMinWidthProportion 
%Type int16 because VidObjWidth type int16.
ROIWidthMin = ROIGeneralConfig.ROIMinWidthProportion * 1.25 * VideoReadConfig_VidObjWidth;

%ROIHeightMin: height minimum, which is 25% larger than the value of ROIMinHeightProportion
%Type int16 because VidObjHeight type int16.
ROIHeightMin = ROIGeneralConfig.ROIMinHeightProportion * 1.25 * VideoReadConfig_VidObjHeight;

%Expand ROI
%Function SkinDetect_EnlargeROI enlarges the ROI as specified and also prevents the enlarged ROI    
%from exceeding frame dimensions.
%1 x 4 row vector; type int16.
%Note: SkinDetect_EnlargeROI is a custom function located within folder 'FacePulseRate'.        
ROIRegionSelected_FullFrame =          ... Enlarged ROI
    SkinDetect_EnlargeROI( ...
        ROIRegionSelected_FullFrame,   ... ROI to enlarge
        ROIWidthMin,                   ... minimum width to apply
        ROIHeightMin,                  ... minimum height to apply
        VideoReadConfig_VidObjWidth,   ... frame width to prevent ROI from exceeding frame width
        VideoReadConfig_VidObjHeight); %   frame height to prevent ROI from exceeding frame height


%%%%%% Verify the validity of ROI %%%%%%    

%Note: SkinDetect_ROIValidate is a custom function located within folder 'FacePulseRate'.
SkinColorTF = ...
    SkinDetect_ROIValidate(ROIRegionSelected_FullFrame, IsSkinMask, VidFrame, BoundingBoxSkin, ...
        VideoReadConfig_VidObjWidth, VideoReadConfig_VidObjHeight, SkinSegmentConfig, ...
        SkinDetectionConfig);
        

%%%%%% Assign selected ROI %%%%%%

%If a sufficient number of pixels within the ROI are classified as skin
if SkinColorTF

    %Note: if this point is reached, the ith frame contains a skin-detection ROI considered to be
    %successful.

    %Indicate that the ROI passed the threshold applied by function ConfirmSkinPresent
    %Note: this value will be the opposite of value SkinColorTF. If true, then SkinTF_ith will be 
    %false. However, SkinTF_ith can be false without HasROITF_SkinNotPresent_ith being true.    
    HasROITF_SkinNotPresent_ith = false;      
    
    %Assign successful detection status
    SkinTF_ith = true;            
        
    %Assign selected ROI
    %1 x 4 row vector; type int16.
    ROI_Selected_ith = ROIRegionSelected_FullFrame;

%If the proportion of pixels classified as skin was below the specified threshold
else

    %Indicate that the ROI did not pass the threshold applied by function ConfirmSkinPresent    
    %Note: this value will be the opposite of value SkinColorTF. If true, then SkinTF_ith will be 
    %false. However, SkinTF_ith can be false without HasROITF_SkinNotPresent_ith being true. 
            
    %and SkinTF_ith.
    HasROITF_SkinNotPresent_ith = true;        
    
    %Assign unsuccessful detection status
    SkinTF_ith = false;      
    
    %Assign empty value for selected ROI
    ROI_Selected_ith = zeros(0, 4, 'int16');              
end


end %end function


