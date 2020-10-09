function [ROI, HasROI_TF, ROIDiagnostic, PulseRateConfigAndData, ...
          SkinSegmentConfig, SkinSegmentMasks] = ...
             ROIMeans_SecondRead(ROI, HasROI_TF, ROIMatchSizeData, ROIDiagnostic, ... 
                 ROIGeneralConfig, FaceDetectConfig, SkinDetectConfig, SkinSegmentConfig, ...
                 SkinSegmentMasks, PulseRateConfigAndData, VideoReadConfig, OutputConfig)               
%ROIMeans_SecondRead   Apply skin-ROI detection algorithm and take ROI means for frames near 
%                      beginning of video where these operations were omitted in functions
%                      ROIMeans_FirstRead and ROIMeans_FirstRead_TakeMeans.
%
%    Helper function to function FacePulseRate.
%
%
%    Description
%    -----------
%
%    Conduct the skin-detection algorithm, ROI modifications, and the ROI means calculations that 
%    were omitted in functions ROIMeans_FirstRead and ROIMeans_FirstRead_TakeMeans. See function 
%    ROIMeans_FirstRead_TakeMeans for details.
%
%    Note: the function that conducts skin detection in the second read 
%    (ROIMeans_SecondRead_SkinDetect) and the function that conducts ROI means calculations in the
%    second read (ROIMeans_SecondRead_TakeMeans) read through frames separately. This contrasts
%    with the implementation in the first read (function ROIMeans_FirstRead), where a frame is read 
%    only once for both operations. Reading a frame only once for both operations improves  
%    efficiency as frame reading is computationally expensive. The strategy of combining these
%    operations was developed after the second-read operations were implemented and has not yet 
%    been implemented for them. In the future, the second-read operations might be improved by
%    implementing this strategy. To implement this strategy, skin-detection, ROI modification, and
%    ROI means calculations would be merged into one function. A frame cache (see function
%    ROIMeans_FirstRead_TakeMeans) would be used to allow ROI modication and ROI means calculations 
%    to lag behind the skin-detection algorithm. A lag is necessary for the ROI modications, and  
%    the ROI means calculations require these modifications.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% Specify testing flag %%%%%%

%Whether testing is enabled to determine whether ROI widths and heights are below a certain value  
%after various steps of the operations.                              
%If below the value, this may indicate that the implementation is not behaving as expected. 
%Occasionally, however, widths or heights may be below the value in the absence of an
%implementation issue. If a width or height is below the value, a warning is displayed. This option                               
%is intended to be enabled only during testing. Otherwise, to increase efficiency and avoid the                               
%display of unnecessary warnings, it should be disabled.                             
ExpectedBehaviorTestTFCode = false;


%%%%%% Preprocessing: modify ROIs near beginning of video %%%%%%

%Modify ROIs -- size match, smooth detections, interpolate, smooth frame-by-frame, and resize --   
%before their corresponding frames are submitted to the skin-detection algorithm. These 
%modifications, which are intended to make the ROIs more stable and accurate, can benefit the 
%function that sets the bounding boxes for the skin-detection algorithm, which is based upon nearby 
%ROIs. As the skin-detection algorithm can assign new ROIs based upon its detections, ROI 
%modifications will also applied a second time after the skin-detection algorithm has been applied
%(see the post-processing section).

%%%%%% --- Specify frame indices for ROI modifications %%%%%%

%Specify frame indices of ROIs that did not receive modifications in the first read (within 
%function ROIMeans_FirstRead).

%Note: the index of frames to modify here must not overlap with the index of frames for which 
%ROIMSIR was called in the first read. This is because function ROIMeans_TakeMeans assigned
%skin-segementation masks (among other values) that correspond to the dimensions of ROIs in the ROI
%matrix assigned by ROIMSIR. If any ROIs in the ROI matrix for which skin-segementation masks were 
%assigned are modified, then the size of the skin-segmentation masks may not match the size of  
%ROIs. This would lead to an error in function WriteFaceVideo because the skin segmentation masks 
%do not match the size of the ROIs to which they are applied.

%Frame indices for ROI modifications
%Row vector; type int32.
%Note: function ROIMSIR relies on this index consisting of elements that increase linearly by one 
%integer.
BlockFullLinIdx = int32(1 : ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx);

%Transpose to column vector
BlockFullLinIdx = BlockFullLinIdx(:);

%%%%%% --- ROI modifications %%%%%%

%Flag that ROIMSIR is called during the pre-processing step of the second read. This will result in
%some modifications (frame-by-frame smoothing and resizing) being postponed until the next call  
%(the post-processing section) to avoid modifications unneeded at this time.
SecondReadPostProcessingTF = false;

%Flag that function ROIMSIR is not being called during the first-read operations
FirstReadTF = false;

%Flag that this is not the first call to function ROIMSIR
FirstCallTF = false;

%Arguments not relevant in second-read operations
%Note: These arguments are only used in function ROIMeans_FirstRead_TakeMeans.
RowToReturnLinIdx = int32(0);
ROINoMods         = zeros(0, 4, 'int16'); %4 columns required
ROINoResize       = zeros(0, 4, 'int16'); %4 columns required

%Note: tildes indicate output arguments only used in first-read operations (see function
%ROIMeans_FirstRead_TakeMeans). 
%The compiled version of ROIMSIR is used in the first-read operations (see function 
%ROIMeans_FirstRead_TakeMeans) but not the second-read operations.  
[~, ROIOut_SecondRead, ~, InterpolatedLinIdx_SecondRead, ~, ~, ~, ROIMatchSizeData] = ...        
    ROIMSIR(BlockFullLinIdx, ROI, VideoReadConfig.FrameTimestamp_Single, ...
        HasROI_TF, ROIGeneralConfig.ROIMSIR_DiffMaxDetection, ...
        ROIGeneralConfig.ROIMSIR_DiffMaxAdjacent, ROIGeneralConfig.ROIWidthResizeFactor, ...
        ROIGeneralConfig.ROIHeightResizeFactor, FaceDetectConfig.ROIFaceSmoothingWindow, ...        
        FaceDetectConfig.ROIFaceSecondary1TF, FaceDetectConfig.ROIFaceSecondary2TF, ... 
        SkinDetectConfig.ROISkinSmoothingWindow, ROIGeneralConfig.ROIFinalSmoothingWindows, ...
        VideoReadConfig.VidObjWidth, VideoReadConfig.VidObjHeight, ExpectedBehaviorTestTFCode, ...
        FirstReadTF, FirstCallTF, VideoReadConfig.FrameIdx, RowToReturnLinIdx, ... 
        ROIGeneralConfig.ROIMSIR_FirstFrameIdx, ROINoMods, ROINoResize, ROIMatchSizeData, ...
        SecondReadPostProcessingTF);           
            
%Assign modified ROIs  
%Type int16.
ROI(BlockFullLinIdx, :) = ROIOut_SecondRead;    

%Record use of interpolation
  
%0 indicates that none of the ROIs was interpolated
if InterpolatedLinIdx_SecondRead ~= 0
    
    HasROI_TF.Interpolated(InterpolatedLinIdx_SecondRead) = true;
end


%%%%%% Second-read skin-detection algorithm operations %%%%%%

%Conduct the skin-detection algorithm if enabled and if a sufficient number of skin-color samples
%have been collected. For details on the collection of skin-color samples, see function
%ROIMeans_FirstRead_CollectSkinColorSamples.
if SkinDetectConfig.ROISkinTF && ...
   SkinDetectConfig.Thresholds.SkinColorSamples_NThresholdPassedTF

    %Note: 'ROIMeans_SecondRead_SkinDetect' is a custom function located within folder 
    %'FacePulseRate'.
    [ROI, ROIDiagnostic, HasROI_TF] = ...
         ROIMeans_SecondRead_SkinDetect(VideoReadConfig, ROI, ROIDiagnostic, ROIGeneralConfig, ... 
             SkinDetectConfig, HasROI_TF, SkinSegmentConfig, OutputConfig);
end


%%%%%% Postprocessing: modify ROIs near beginning of video %%%%%%

%Modify ROIs -- size match, smooth detections, interpolate, smooth frame-by-frame, and resize --
%from skin-detection algorithm detections.

%Specify frame indices for ROI modifications.
%Note: Function ROIMeans_SecondRead_TakeMeans processes the frames processed here. The index  
%specified here  (1 : ROIGeneralConfig...) will also be used in function 
%ROIMeans_SecondRead_TakeMeans. The same index must be used in both the current function and 
%ROIMeans_SecondRead_TakeMeans to ensure that function ROIMeans_SecondRead_TakeMeans processes the 
%results from the current function. If ROIMeans_SecondRead_TakeMeans does not use the same index 
%and does not process some of the results from the current function, errors may occur. One example 
%is that the ROIs recorded here may not align with the dimensions of the skin-segmentation results, 
%which are returned by ROIMeans_SecondRead_TakeMeans; this would lead to an error being thrown in
%function WriteFaceVideo when the skin-segmentation mask is overlayed on the output video.
%Type int32.

%Note: function ROIMSIR relies on this index consisting of elements that increase linearly by one 
%integer.

BlockFullLinIdx = int32(1 : ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx);

%Transpose to column vector
BlockFullLinIdx = BlockFullLinIdx(:);

%Flag that function ROIMSIR is called in the post-processing step of the second read
%This will result in some modifications (frame-by-frame smoothing and resizing) that were not  
%conducted during the previous call to ROIMSIR (in the pre-processing section) to be conducted 
%here.
SecondReadPostProcessingTF = true;
    
%Flag that function is not called during the first read.
FirstReadTF = false;     

%Arguments not relevant in second-read operations
%Note: These arguments are only used in function ROIMeans_FirstRead_TakeMeans.
RowToReturnLinIdx = int32(0);
ROINoMods         = zeros(0, 4, 'int16'); %4 columns required
ROINoResize       = zeros(0, 4, 'int16'); %4 columns required

%Note: tildes indicate output arguments only used in first-read operations (see function
%ROIMeans_FirstRead_TakeMeans). 
%The compiled version of ROIMSIR is used in the first-read operations (see function 
%ROIMeans_FirstRead_TakeMeans) but not the second-read operations.
%'ROIMSIR' is a custom function located within folder 'FacePulseRate'.
[~, ROIOut_SecondRead, ~, InterpolatedLinIdx_SecondRead, ~, ...
 ROIOutBeforeFrameByFrameSmoothing_SecondRead, ~, ~] = ...        
    ROIMSIR(BlockFullLinIdx, ROI, VideoReadConfig.FrameTimestamp_Single, ...
        HasROI_TF, ROIGeneralConfig.ROIMSIR_DiffMaxDetection, ...
        ROIGeneralConfig.ROIMSIR_DiffMaxAdjacent, ROIGeneralConfig.ROIWidthResizeFactor, ...
        ROIGeneralConfig.ROIHeightResizeFactor, FaceDetectConfig.ROIFaceSmoothingWindow, ...        
        FaceDetectConfig.ROIFaceSecondary1TF, FaceDetectConfig.ROIFaceSecondary2TF, ... 
        SkinDetectConfig.ROISkinSmoothingWindow, ROIGeneralConfig.ROIFinalSmoothingWindows, ...
        VideoReadConfig.VidObjWidth, VideoReadConfig.VidObjHeight, ExpectedBehaviorTestTFCode, ...
        FirstReadTF, FirstCallTF, VideoReadConfig.FrameIdx, RowToReturnLinIdx, ... 
        ROIGeneralConfig.ROIMSIR_FirstFrameIdx, ROINoMods, ROINoResize, ROIMatchSizeData, ...
        SecondReadPostProcessingTF);   
                       
%%%%%% --- Validate and assign %%%%%%   
    
%Verify that the sizes of ROIs are not unreasonably small
%ROIs that are too small may indicate an unexpected error occurred during function ROIMSIR.
%Such a small size would likely be due to an implementation error.
if any( ROIOut_SecondRead(:, 3) < 20 ) || any( ROIOut_SecondRead(:, 4) < 20 )

    ROITooSmallFrameIdx = ...
        VideoReadConfig.FrameIdx( ... frame index
            BlockFullLinIdx( ... index
                ROIOut_SecondRead(:, 3) < 20 | ROIOut_SecondRead(:, 4) < 20 ...
            ) ...
        );
          
    %Display warning
    warning( ...
        'Component:InternalError', ...
        ['Internal Error: ROI-modification operations assigned a size value for an ROI that is', ...
         ' below 20 pixels, which is likely inaccurate. ROI accuracy may be affected. Frames', ...
         ' affected include: ', num2str(ROITooSmallFrameIdx), '.'] ...
    );       
end

%Check if ROI type not int16 because other functions are implemented to accept values of this type. 
%A non-matching type would be due to an implementation error.
assert( isa(ROIOut_SecondRead(1, 1), 'int16') );    
    
%Assign modified ROIs
%Type int16.
ROI(BlockFullLinIdx, :) = ROIOut_SecondRead;    
 
%Record ROIs not modified by frame-by-frame smoothing or resizing, two of the operations 
%conducted in function ROIMSIR. The two operations that occured prior to these, size matching and
%detection smoothing, are present. This permits diagnosis of false positives or false negatives 
%resulting from size matching and detection smoothing. The ROI coordinates will be superimposed on 
%the output video for assessment.  
%Note: the final ROIs differ from these only as a result of receiving frame-by-frame smoothing and 
%resizing. Hence, the final ROIs can be inspected to diagnose false positives or false negatives  
%resulting from frame-by-frame smoothing and resizing. 
%Convert from type int16 to type uint16 because signed operations not conducted with this variable.
ROIDiagnostic.ROI_NonFinalSmoothed(BlockFullLinIdx, :) = ...
    uint16(ROIOutBeforeFrameByFrameSmoothing_SecondRead);

%Record use of interpolation
%0 indicates that none of the ROIs was interpolated
if InterpolatedLinIdx_SecondRead ~= 0
    
    HasROI_TF.Interpolated(InterpolatedLinIdx_SecondRead) = true;
end

%%%%%% --- Transition smoothing %%%%%%

%Smooth a few ROIs where the second-read modifications began to smooth the transition. Do not
%change the ROIs from the first read as the skin-segmentation masks have already been recorded, so
%the corresponding ROIs should not be modified. (ROIs processed in the first read begin 1 frame
%after ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx).

if ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx - 10 > 1 && ...
   ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx + 10 < size(ROI, 1)

    %Smooth across transition ROIs
    ROITransition = ...
        round( ...
            movmean( ...
                ROI( ...
                    ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx - 10 : ...
                    ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx + 10, ...
                    : ...
                ), ...
                21 ... smoothing window
            ) ...
        ); 

    %Verify that the sizes of ROIs are not unreasonably small as a result of transition smoothing
    %Such a small size would likely be due to an implementation error.
    if any( ROITransition(1 : 11, 3) < 20 ) || any( ROITransition(1 : 11, 4) < 20 )
  
        %Display warning
        warning( ...
            'Component:InternalError', ...
            ['Internal Error: ROI-modification transition smoothing operations assigned a', ...
             ' size value for an ROI that is below 20 pixels, which is likely inaccurate. ROI', ...
             ' accuracy may be affected.'] ...
        );       
    end    
    
    %Assign smoothed transition ROIs up to, but not overlapping, where first read started
    ROI( ...
        ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx - 10 : ...
        ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx, ...
        : ...
    ) = ROITransition(1 : 11, :);   
end


%%%%%% Second-read ROI-means operations %%%%%%

%Note: 'ROIMeans_SecondRead_TakeMeans' is a custom function located within folder 'FacePulseRate'.
[PulseRateConfigAndData, ROI, HasROI_TF, SkinSegmentConfig, SkinSegmentMasks] = ...
    ROIMeans_SecondRead_TakeMeans(VideoReadConfig, ROI, PulseRateConfigAndData, ...
    SkinSegmentConfig, SkinSegmentMasks, HasROI_TF, OutputConfig, ROIGeneralConfig);


end %end function

