function SkinSegmentConfig = ...
             SkinSegment_ConfigSetupMaskArgs(SkinSegmentConfig, SkinSegmentSeverityFactor, ...
                 SkinSegmentThresholdsGenericYCbCr, SkinSegmentThresholdsGenericHSV, ...
                 ROIGeneralConfig, VidObj)                                 
%SkinSegment_ConfigSetupMaskArgs   Set settings used as arguments to function SkinSegmentMask.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinSegment_ConfigSetup.
%
%    
%    Description
%    -----------
%
%    Set settings used as arguments to function SkinSegmentMask. SkinSegmentMask conducts the
%    skin-segmentation operations in function FacePulseRate.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% Generic pixel-color thresholds %%%%%%

%Thresholds used for generic skin segmentation. These thresholds specify the ranges (minimums and 
%maximums) of accepted pixel colors from the YCbCr and HSV colorspaces. Generic skin segmentation
%is used when argument TailoredThresholdsTF to function SkinSegmentMask is false.

%These settings may be modified by function SkinSegment_OversegmentationCheck_Reduce if 
%oversegmentation is determined to be present. If so, they will be assigned values specifed by
%function SkinSegment_ConfigSetupOversegmentation.

%%%%%% --- Generic YCbCr thresholds %%%%%%

%Thresholds for the YCbCr colorspace. These thresholds are specified by 
%SkinSegmentThresholdsGenericYCbCr, which is an argument to function FacePulseRate.

%Cast to type single for faster evaluation in function SkinSegmentMask_Threshold.
%Also, type single is expected by compiled function SkinSegmentMask, which calls function
%SkinSegmentMask_Threshold.
SkinSegmentConfig.Args.YCbCrThresholdsGeneric = single(SkinSegmentThresholdsGenericYCbCr);
    
%%%%%% --- Generic HSV thresholds %%%%%%

%Thresholds for the YCbCr colorspace. These thresholds are specified by 
%SkinSegmentThresholdsGenericHSV, which is an argument to function FacePulseRate.

%Cast to type single for faster evaluation in function SkinSegmentMask_Threshold.
%Type single is expected by compiled function SkinSegmentMask.
SkinSegmentConfig.Args.HSThresholdsGeneric = single(SkinSegmentThresholdsGenericHSV);


%%%%%% Tailored pixel-color thresholds %%%%%%

%Thresholds used for tailored skin segmentation. These thresholds specify the ranges (minimums and 
%maximums) of accepted pixel colors from the YCbCr and HSV colorspaces. Tailored skin segmentation
%is used when argument TailoredThresholdsTF to function SkinSegmentMask is true.

%Different thresholds are used depending on the specified severity of the tailored thresholds, 
%which is controlled by argument TailoredThresholdsSevereTF to function SkinSegmentMask. When
%TailoredThresholdsSevereTF is true, SkinSegmentConfig.Args.YCbCrThresholdsTailored_Sev are used;
%when false, SkinSegmentConfig.Args.YCbCrThresholdsTailored are used.

%These thresholds are reassigned periodically by function SkinSegmentMask_Threshold. 
%SkinSegmentMask_Threshold assigns the thresholds based upon skin-color samples collected from the
%input video. Settings for SkinSegmentMask_Threshold are assigned by function 
%SkinSegment_ConfigSetupTailoredThresholds

%These settings may be modified by function SkinSegment_OversegmentationCheck_Reduce if 
%oversegmentation is determined to be present. If so, they will be assigned values specifed by
%function SkinSegment_ConfigSetupOversegmentation.

%Type single is expected by function SkinSegmentMask.

%%%%%% --- Tailored YCbCr thresholds %%%%%%

%Thresholds for the YCbCr colorspace.

%Low-severity thresholds
SkinSegmentConfig.Args.YCbCrThresholdsTailored = nan(1, 8, 'single');

%High-severity thresholds
SkinSegmentConfig.Args.YCbCrThresholdsTailored_Sev = nan(1, 8, 'single');    

%%%%%% --- Tailored HSV thresholds %%%%%%

%Thresholds for the HSV colorspace. 

%Low-severity thresholds
SkinSegmentConfig.Args.HSThresholdsTailored = nan(1, 3, 'single');

%High-severity thresholds
SkinSegmentConfig.Args.HSThresholdsTailored_Sev = nan(1, 3, 'single');

%%%%%% Local color-range threshold %%%%%%

%Specify struct width for pixel-based local color-range calculations
%This width will be used to construct a square-shaped structuring element in the function using it.
%Specify type int16 because double expected by compiled version of function SkinSegmentMask.
SkinSegmentConfig.Args.RangeSEWidth =  ...
    int16( ...
        round( ...
            ROIGeneralConfig.ROIMinWidthProportion * ...
            ROIGeneralConfig.ROIMinHeightProportion / .0057 * ... for distance adjustment 
            (VidObj.Width * VidObj.Height / 921600) ... for frame size adjustment       
        ) ...
    );

%Specify the threshold above which to classify pixels as non-skin
%Specify as type uint8 for faster evaluation in function SkinSegmentMask_Threshold as this value is
%evaluated against a large number of values. Also, type uint8 is expected by compiled function
%SkinSegmentMask, in which function SkinSegmentMask_Threshold is included.
SkinSegmentConfig.Args.RangeThreshold = uint8(50);


%%%%%% Severity of morphological close to modify patchy classification regions %%%%%%

%Within function SkinSegmentMask, following the application of color thresholds, a two-dimensional 
%logical matrix is assigned where pixels that satisfied all thresholds are classified as true and
%pixels that did not are classified as false. A morphological close operation is then applied to  
%the logical matrix. The morphological close tends to fill in classification holes, where a hole is  
%loosely defined as a region of pixels classified as true that are enclosed by pixels classified as  
%false. Holes are filled in based on the assumption that true skin tends to be distributed in the 
%face in contiguous, rather than patchy, regions.
  
%The morphological close fills in holes only below a certain shape and size, which are determined    
%by the shape and size of the morphological structuring element, such that many holes are not 
%filled.  Otherwise, large regions classified as true -- which are assumed to be regions of skin --
%may be erroneously filled. For a description on the choice of structuring element used, see 
%function SkinSegmentMask_MorphClose. 

%First, assign the width of the structuring element according to the distance of the face from the 
%camera and the video frame size, both of which affect the number of pixels in the ROI. Then, tune
%the size according to SkinSegmentConfig.SkinSegmentSeverityFactor, which is an argument to 
%function FacePulseRate. This argument is used to tune (increase or decrease) the severity of 
%segmentation by adjusting the size of the structuring element.

%While frames are being processed, function SkinSegment_OversegmentationCheck checks whether ROIs
%appear to be oversegmented. If so, this function will decrease the severity of skin segmentation.
%It will do so by reducing the value of SkinSegmentConfig.SkinSegmentSeverityFactor and then tuning 
%the structuring elements (SkinSegmentConfig.MorphCloseSEMediumWidth and 
%SkinSegmentConfig.MorphCloseSELargeWidth) by the reducing value. 

%%%%%% --- Tuning factor for adjusting size of morphological close %%%%%%

%SkinSegmentSeverityFactor is an argument to function FacePulseRate. It is used to adjust the size
%of the morpological close operations.

%This value may be modified by function SkinSegment_OversegmentationCheck_Reduce if  
%oversegmentation is determined to be present. If so, it will be assigned a value specifed by
%function SkinSegment_ConfigSetupOversegmentation.

%Scalar; type double.
SkinSegmentConfig.SkinSegmentSeverityFactor = SkinSegmentSeverityFactor;

%%%%%% --- Large structuring element width %%%%%%

%Used in function SkinSegmentMask_MorphClose of function SkinSegmentMask. The large option is used
%in skin-detection operations, where liberal skin segmentation can help avoid false positions. The
%large option is also used when collecting skin-color samples during the first read (by function
%ROIMeans_FirstRead_CollectSkinColorSamples) and when confirming that the proportion of skin
%exceeds the specified threshold (see function ConfirmSkinPresent). Consider reducing the size if
%too much segmentation occurs. The effect of the size can be assessed by inspecting the skin-
%detection diagnosis annotations on the output video. Specifically, the colored borders that denote 
%assessed regions will only be present for regions not segmented. 

%A square structuring element is used because, for some images, it can result in less processing
%compared to a disk-shaped structuring element in the morphological operation in which it is used.
%The use of a square structuring element will likely result in region borders less smooth compared
%to the use of a disk structuring element. It is not clear whether a square structuring element
%will be less accurate than a disk structuring element. However, as prioritizing the rejection of
%non-skin pixels is the objective in the operations in which this structuring element is used, a
%small loss of true-skin pixels is considered less important than time-savings associated with it.

%Assign width of large structuring element
%The size of the structuring element is designed to adjust depending on the  
%This width will be used to construct a square-shaped structuring element in the function using it.
SkinSegmentConfig.MorphCloseSELargeWidth = ...
    ROIGeneralConfig.ROIMinWidthProportion * ...
    ROIGeneralConfig.ROIMinHeightProportion / .0004 * ... for distance adjustment 
    (VidObj.Width * VidObj.Height / 2073600);         %   for frame size adjustment       

%Tune the width according to SkinSegmentSeverityFactor
%SkinSegmentSeverityFactor is an argument to function FacePulseRate.
%Specify type int16 because type int16 expected by compiled version of function SkinSegmentMask.
%Scalar; type int16.
SkinSegmentConfig.Args.MorphCloseSELargeWidth_Tuned = ...
    int16( ...
        round( ...
            SkinSegmentConfig.MorphCloseSELargeWidth * ...       
            SkinSegmentConfig.SkinSegmentSeverityFactor ...                         
        ) ...
    );
    
%%%%%% --- Medium structuring element width %%%%%%

%Used in function SkinSegmentMask_MorphClose of function SkinSegmentMask. The large option is used
%for the operations conducted by function ROIMeans_TakeMeans. There, reducing false negatives is as 
%important as as reducing false positives. Accordingly, the size of the structuring element, which 
%corresponds to its masking effect, is kept moderate. Consider reducing the size if too much
%segmentation occurs. The effect of the size can be assessed by inspecting the skin-segmentation
%mask displayed on the output video, which is assigned during function ROIMeans_TakeMeans. The size
%of the structural element can be modified by specifying SkinSegmentPixelMorphSize, which is an 
%argument to function FacePulseRate. 

%Assign width (diameter) of medium structuring element
%The size of the structuring element is designed to adjust depending on the individual's distance 
%from the camera and to the video frame size, both of which affect the number of pixels in the ROI.
%This diameter will be used to construct a disk-shaped structuring element in the function using 
%it.
SkinSegmentConfig.MorphCloseSEMediumWidth = ...
    ROIGeneralConfig.ROIMinWidthProportion * ...
    ROIGeneralConfig.ROIMinHeightProportion / .0007 * ... for distance adjustment 
    (VidObj.Width * VidObj.Height / 2073600);         %   for frame size adjustment                 

%Tune the width according to SkinSegmentSeverityFactor
%SkinSegmentSeverityFactor is an argument to function FacePulseRate.
%Specify type int16 because type int16 expected by compiled version of function SkinSegmentMask.
%Scalar; type int16.
SkinSegmentConfig.Args.MorphCloseSEMediumWidth_Tuned = ...
    int16( ...
        round( ...
            SkinSegmentConfig.MorphCloseSEMediumWidth * ...     
            SkinSegmentConfig.SkinSegmentSeverityFactor ... 
        ) ...           
    );


end %end function

