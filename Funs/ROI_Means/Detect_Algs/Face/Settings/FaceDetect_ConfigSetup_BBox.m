function FaceDetectConfig = FaceDetect_ConfigSetup_BBox(FaceDetectConfig, VideoReadConfig)
%FaceDetect_ConfigSetup_BBox   Specify size settings for bounding box used for the face-detection
%                              algorithms.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function FaceDetect_ConfigSetup.
%
%
%    Description
%    -----------
%
%    Specify size settings for bounding box used for the face-detection algorithms.                                 
%
%    For a description of all the influences on the bounding box, see function
%    ROIMeans_FirstRead_SetBoundingBoxes.
%
%    -- Bounding box size according to face-detection algorithm --
%
%    ROIFace_ChangeFactorROIPrimary, ROIFace_ChangeFactorROISecondary1, 
%    ROIFace_ChangeFactorROISecondary2 influence the size of the bounding box used for the 
%    face-detection algorithm(s). This is useful if the typical sizes of ROIs returned from the
%    algorithms vary across algorithms. The sizes of the ROIs returned from the algorithm(s) affect 
%    the sizes of the bounding boxes used for the subsequent applications of the algorithm(s). If 
%    one algorithm tends to return an ROI smaller than another algorithm, the bounding box used for 
%    subsequent applications may be too small for the other algorithm to make a detection. In this 
%    case, the value for the former algorithm may be increased to make the bounding box for the
%    latter algorithm more suitable. Additionally, the value for the latter algorithm might be 
%    decreased slightly, if it doesn't make the bounding box too small for a detection to be found, 
%    to decrease processing time for the first algorithm.  
%
%    The values for these arguments are set based upon the idiosyncratic ROI sizes of the default 
%    algorithms (i.e., those specified by xml files), so changing them might be appropriate if 
%    algorithms other than the defaults are used. 
%
%    On the ith frame, the bounding box used is the same across the primary, the secondary #1, and 
%    the secondary #2 algorithms. Using the same bounding box across algorithms helps reduce 
%    processing time used for cropping the frame and converting to grayscale. Because the same 
%    bounding box is used across algorithms, setting different values for
%    ROIFace_ChangeFactorROIPrimary, ROIFace_ChangeFactorROISecondary1, and 
%    ROIFace_ChangeFactorROISecondary2 will not result in a different bounding box for each 
%    algorithm for a given frame. Rather, the values weight the size of the ROI detected by a given 
%    algorithm when using the ROI from that algorithm for setting the sizes of subsequent bounding 
%    boxes.
%
%    These values only affect the sizes of the bounding boxes but not the ROIs. A different 
%    operation, conducted at the end of the algorithm processing, adjusts the sizes of the ROIs to 
%    be similar across algorithms to reduce instability in ROI size across frames; this is targeted 
%    to reduce noise in the RGB means introducing by a rapidly flucuating ROI.
%
%    -- Bounding box growth rate --
%
%    A bounding box is used both to reduce false positives and reduce computational time, as a  
%    bounding box limits the area of the image that is scanned. The size of the bounding box has  
%    been observed to be one of the largest factors determining the execution time of the 
%    algorithms. After a specified number frames, as specified by  
%    ROIFace_BoundingBoxGrowthThreshold, the bounding box is expanded under the assumption that the  
%    face was able to have moved outside the bounding box in the time elapsed across the specified  
%    number of frames. ROIFace_BoundingBoxGrowthThreshold is an argument to function FacePulseRate.  
%    This this value is adjusted by frame rate to make the value consistent across videos with 
%    different frame rates.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Bounding box size according to face-detection algorithm %%%%%%

%Amount by which to change effect on bounding box.

FaceDetectConfig.ROIFace_ChangeFactorROIPrimary = 1.05;  

%Note: smaller than primary only because the detections from the secondary xml file specified tend 
%to be larger than the primary detections.
FaceDetectConfig.ROIFace_ChangeFactorROISecondary1 = .95;

FaceDetectConfig.ROIFace_ChangeFactorROISecondary2 = 1;


%%%%%% Bounding box growth rate %%%%%%

%Specify bounding box growth rate
%Specify as type double to facilitate calculations with variables of type int16.

BoundingBoxEnlargementFactor = 1.55;

FaceDetectConfig.ROIFace_BoundingBoxEnlargementFactor = ...
    double(BoundingBoxEnlargementFactor);

%Specify the number of frames to have passed since detection was found after which the bounding
%box will be expanded:

BoundingBoxGrowthThreshold = .35;

%This this value is adjusted by frame rate to make the value consistent across videos with 
%different frame rates.
%Specify type int32 for protection against floating-point gaps.
FaceDetectConfig.BoundingBoxGrowthThreshold_adjusted = ...
    int32( round(VideoReadConfig.FS * BoundingBoxGrowthThreshold) );
        
%Specify how much to enlarge the bounding box for each frame beyond the threshold (specified by 
%ROIFace_BoundingBoxGrowthThreshold) where a detection is not present:

BoundingBoxGrowthRate = .16;

%This this value is adjusted by frame rate to make the value consistent across videos with 
%different frame rates.
%Specify as type double to facilitate calculations with variables of type int16.
FaceDetectConfig.BoundingBoxGrowthRate_adjusted = ...
    double(VideoReadConfig.FS / 24 * BoundingBoxGrowthRate);


end %end function

