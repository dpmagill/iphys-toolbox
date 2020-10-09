function SkinColorTF = ...
             SkinDetect_ROIValidate(ROIRegionSelected_FullFrame, IsSkinMask, VidFrame, ...
                 BoundingBoxSkin, VideoReadConfig_VidObjWidth, VideoReadConfig_VidObjHeight, ...
                 SkinSegmentConfig, SkinDetectionConfig) %#codegen            
%SkinDetect_ROIValidate   Verify the validity of the ROI from the skin-detection algorithm.
%  
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function SkinDetect_SelectRegionROI.
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
%    Verify the validity of the ROI from the skin-detection algorithm. The ROI is considered valid 
%    if the proportion of pixels classified as skin exceeds a specified threshold. The proportion 
%    is calculated by inspecting the skin-segmentation mask that corresponds to the location of the 
%    ROI. Specifically, in the portion of the skin-segmentation mask that corresponds to the ROI, 
%    the number of elements classified as true is divided by the total number of elements. This 
%    calculation is conducted by function ConfirmSkinPresent. This function returns a true / false 
%    determination on whether the proportion exceeded the specified threshold. 
%
%    If the ROI is completely contained within the skin-segmentation mask:
%
%    The skin-segmentation mask will be cropped to the ROI dimensions and then passed to function
%    ConfirmSkinSegment. The function will check the proportion of skin pixels and return a 
%    validity determination.
%
%    If the ROI is not completely contained within the skin-segmentation mask:
%
%    In other words, all or some portion of the ROI is located outside of the existing 
%    skin-segmentation mask. The full video frame will be passed to function ConfirmSkinPresent.
%    The function will produce a skin-segmentation mask corresponding to the ROI and then check the 
%    proportion of skin pixels and return a validity determination. This condition is less 
%    efficient than the above condition because the skin-segmentation mask is recalculated rather 
%    than just cropped.
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


%%%%%% Specify algorithm for ROI verification %%%%%%

%Indicate that the algorithm is the skin-detection algorithm. 
%Note: This setting specifies which threshold is used from SkinSegmentConfig.ConfirmSkin. 
%SkinSegmentConfig.ConfirmSkin is assigned by function SkinSegment_ConfigSetupConfirmSkinPresent.

FaceAlgorithm = 's'; 


%%%%%% Determine whether ROI is completely contained within skin-segmentation mask %%%%%% 

%Determine whether the ROI is completely contained within the skin-segmentation mask. 
%This is true if no extrema of the ROI exceeds the bounds of the skin-segmentation mask.
%Local function.
%Scalar; type logical.
CompletelyContainedTF = IsCompletelyContained(ROIRegionSelected_FullFrame, BoundingBoxSkin);   
         

%%%%%% If completely contained: Crop ROI from skin-segmentation mask and check skin pixels %%%%%%        

if CompletelyContainedTF

    %Adjust X- and Y-coordinates of the selected-region ROI from the coordinate plane of the full 
    %frame to the coordinate plane of the bounding box.
    %Scalars; type int16.

    %X-coordinate 
    ROIRegionSelected_FullFrame_Crop_XLeft = ...
        ROIRegionSelected_FullFrame(1) - (BoundingBoxSkin(1) - 1);

    %Y-coordinate
    ROIRegionSelected_FullFrame_Crop_YTop = ...
        ROIRegionSelected_FullFrame(2) - (BoundingBoxSkin(2) - 1);

    %Crop the skin-segmentation mask to correspond to the selected-region ROI 
    %M x N matrix; type logical.
    IsSkinMask_ROISelected = ...
        IsSkinMask( ...        
            ROIRegionSelected_FullFrame_Crop_YTop :  ... rows
            ROIRegionSelected_FullFrame_Crop_YTop +  ...
            (ROIRegionSelected_FullFrame(4) - 1),    ... 
            ROIRegionSelected_FullFrame_Crop_XLeft : ... columns
            ROIRegionSelected_FullFrame_Crop_XLeft + ...
            (ROIRegionSelected_FullFrame(3) - 1)     ...
        );     
    
    %Determine whether the proportion of pixels classified as skin is considered valid:

    %Dimensions of the cropped skin-segmentation mask
    NRows_Matrix = int32( ROIRegionSelected_FullFrame(4) );
    NCols_Matrix = int32( ROIRegionSelected_FullFrame(3) );

    %Return true / false determination on whether the proportion of skin pixels is considered 
    %valid.
    %Scalar; type logical.
    %Note: 'ConfirmSkinPresent' is a custom function located within folder 'FacePulseRate'.
    SkinColorTF = ...
        ConfirmSkinPresent( ...
            SkinSegmentConfig, ... configurations
            FaceAlgorithm, ...
            IsSkinMask_ROISelected, ...
            single(-1), ... unused argument
            NRows_Matrix, ...
            NCols_Matrix ...
        );           

    
%%%%%% If not completely contained: Crop ROI from full frame and check skin-pixel proportion %%%%%% 

%The skin-segmentation mask will be reassigned by function ConfirmSkinPresent.

else    
    
    %Crop VidFrame and separate into colorspace channels
    %Local function.
    %M x N matrices; type uint8.
    [RUint8, GUint8, BUint8] = ...
        CropVidAndSeparateChannels( ...
            VidFrame,                       ... full frame
            ROIRegionSelected_FullFrame(1), ... ROI X-coordinate in coordinate plane of full frame
            ROIRegionSelected_FullFrame(2), ... ROI Y-coordinate in coordinate plane of full frame
            ROIRegionSelected_FullFrame(3), ... ROI width
            ROIRegionSelected_FullFrame(4), ... ROI height
            VideoReadConfig_VidObjWidth,    ... full-frame width; scalar, type int16
            VideoReadConfig_VidObjHeight    ... full-frame height
        );
         
    %Determine whether the proportion of pixels classified as skin is above the specified threshold:

    %Dimensions of ROI
    %Scalars; type int32
    NRows_Matrix = int32( ROIRegionSelected_FullFrame(4) );
    NCols_Matrix = int32( ROIRegionSelected_FullFrame(3) );    
    
    %Specify whether to use thresholds that are tailored
    %The use of tailored thresholds provides a more conservative assessment (more likely to decide 
    %that the ROI is not mostly skin).
    TailoredThresholdsTF = true;

    %Do not return the Y channel of the YCbCr colorspace
    ReturnYTF = false;    
    
    %Do not return the Cb or Cr channels of the YCbCr colorspace
    ReturnCbCrTF = false;
    
    %Do not return the H or S channels of the HSV colorspace
    ReturnHSTF = false;
    
    %Do not apply thresholds from the skin-detection algorithm to refine the inspection.
    %This option is intended to be used in functions where the skin-detection algorithm is not
    %otherwise used in order to refine the confirmation decision. As the skin-detection algorithm
    %has already influenced the selected region, it is not applied used here.
    SkinDetectionThresholdsTF = false;     
    
    %Return true / false determination on whether the proportion of skin pixels is considered 
    %valid. 
    %Scalar; type logical.
    %Note: 'ConfirmSkinPresent' is a custom function located within folder 'FacePulseRate'. 
    SkinColorTF = ... 
        ConfirmSkinPresent( ...
            SkinSegmentConfig, ... configurations
            FaceAlgorithm, ...
            RUint8, ... 
            GUint8, ...
            BUint8, ... 
            NRows_Matrix, ...
            NCols_Matrix, ...
            TailoredThresholdsTF, ...
            ReturnYTF, ...
            ReturnCbCrTF, ...
            ReturnHSTF, ...
            SkinDetectionThresholdsTF, ...
            SkinDetectionConfig ...
        );     
end


end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function TF = IsCompletelyContained(ROIRegionSelected_FullFrame, BoundingBoxSkin)
%IsCompletelyContained   Determine whether the selected ROI is completely contained within the
%                        skin-segmentation mask.


%Inline function
coder.inline('always');


%XY-coordinates of extrema of the selected-region ROI:
%Type int16.

%X left
ROIRegionSelected_FullFrame_XLeft = ROIRegionSelected_FullFrame(1); 

%X right
ROIRegionSelected_FullFrame_XRight = ...
    ROIRegionSelected_FullFrame_XLeft + (ROIRegionSelected_FullFrame(3) - 1); 

%Y top
ROIRegionSelected_FullFrame_YTop = ROIRegionSelected_FullFrame(2); 

%Y bottom
ROIRegionSelected_FullFrame_YBottom = ...
    ROIRegionSelected_FullFrame_YTop + (ROIRegionSelected_FullFrame(4) - 1);      

%Determine whether the ROI is completely contained within the skin-segmentation mask. 
%This is true if no extrema of the ROI exceeds the bounds of the skin-segmentation mask.
TF = ...
    ...Selected-region extrema            ...Skin-segmentation mask extrema
    ROIRegionSelected_FullFrame_XLeft   > BoundingBoxSkin(1) && ... X left within 
    ROIRegionSelected_FullFrame_YTop    > BoundingBoxSkin(2) && ... Y top within
    ROIRegionSelected_FullFrame_XRight  < BoundingBoxSkin(1) + (BoundingBoxSkin(3) - 1) && ... X right within
    ROIRegionSelected_FullFrame_YBottom < BoundingBoxSkin(2) + (BoundingBoxSkin(4) - 1);   %   Y bottom within


end %end local function


%=============================================================================================
function [RUint8, GUint8, BUint8] = ...
             CropVidAndSeparateChannels(VidFrame, x_int16, y_int16, width_int16, height_int16, ...
                 NCols_VidFrame_int16, NRows_VidFrame_int16)
%CropVidAndSeparateChannels  Crop the video and separate it by color channels.


%Inline function
coder.inline('always');


%Cast to int32 to prevent overflow when converting to linear index
%Scalars; type int32.

%ROI values of selected ROI
x      = int32(x_int16);
y      = int32(y_int16); 
width  = int32(width_int16); 
height = int32(height_int16);

%Dimensions of the full frame
NCols_VidFrame = int32(NCols_VidFrame_int16);
NRows_VidFrame = int32(NRows_VidFrame_int16);

%Number of elements in one color channel of the full frame
%Scalar; type int32.
NPageElements = NCols_VidFrame * NRows_VidFrame;

%Number multiplied by 2
%Scalar; type int32.
NPageElementsBy2 = NPageElements * 2;

%Preallocate
RUint8 = coder.nullcopy( zeros(height, width, 'uint8') );
GUint8 = coder.nullcopy( zeros(height, width, 'uint8') );
BUint8 = coder.nullcopy( zeros(height, width, 'uint8') );

%Cropping offsets
%Scalars; type int32.
%Note: the step prevents repeated subtraction by one in the parfor loop.
ColOffset = x - 1;
RowOffset = y - 1;    

%Prevent dynamic memory allocation from colon operator by asserting lengths
%Note: these values also constrain the maximum frame dimensions that can be used in function
%FacePulseRate. If modified, modify the maximum frame dimensions stated in the description in
%function FacePulseRate. 
assert(width <= 5000);
assert(height <= 5000);            

%Bound frame and separate to channels:

%Loop across columns
parfor i = 1 : width 

    %Column index for full frame
    iFull = i + ColOffset;

    %Loop across rows
    for j = 1 : height             

        %Row index for full frame
        jFull = j + RowOffset;

        %Convert from subscript indices to a linear index for more efficient indexing
        %Scalar; type int32.
        %Note: In compiled C code, the faster indexing outweighs the cost of this conversion.
        LinIdxFull = jFull + (iFull - 1) * NRows_VidFrame;        
        
        %Red channel element:

        %Extract value from full frame                      
        jth = VidFrame(LinIdxFull); %#ok<PFBNS>

        %Insert value into bounded frame
        RUint8(j, i) = jth;

        %Green channel element:

        %Extract value from full frame
        jth = VidFrame(LinIdxFull + NPageElements); 

        %Insert value into bounded frame
        GUint8(j, i) = jth;

        %Blue channel element:

        %Extract value from full frame
        jth = VidFrame(LinIdxFull + NPageElementsBy2);

        %Insert value into bounded frame
        BUint8(j, i) = jth;
    end       
end
    
    
end %end local function
