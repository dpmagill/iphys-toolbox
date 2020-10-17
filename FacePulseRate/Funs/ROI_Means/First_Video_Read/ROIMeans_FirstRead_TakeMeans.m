function [ii, ROIOut_FirstRead_ii, ROIMatchSizeData, ...
          ROIOutBeforeFrameByFrameSmoothing_FirstRead_ii, InterpolatedLinIdx_FirstRead_ii, ...
          ROIGeneralConfig, SkinRGBMeans_ii, IsNotSkin_PixelColor_Packed_ii, ...
          AdjustedBecauseLowSkinProportionTF_ii, ROIAdjusted_ii, Y_of_YCbCr_ii, L_of_LAB_ii] = ...         
              ROIMeans_FirstRead_TakeMeans(i, ii, ContinueFrameReadTF, VidFrame, ROI, ...
                  HasROI_TF, ROIMatchSizeData, SkinSegmentConfig, FaceDetectConfig, ... 
                  SkinDetectConfig, ROIGeneralConfig, PulseRateConfigAndData, VideoReadConfig, ...
                  OutputConfig)                                     
%ROIMeans_FirstRead_TakeMeans   Conduct lagged frame-by-frame ROI-means operations within the first 
%                               read.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead.
%
%
%    Description
%    -----------
%
%    For the iith frame, conduct ROI-modification operations to improve accuracy. Specifically, if 
%    a frame contains a detection, conduct size matching, detection smoothing, frame-by-frame
%    smoothing, and resizing according to arguments ROIWidthResizeFactor and ROIHeightResizeFactor.
%    If a frame does not have a detection, conduct many of the same operations but interpolate the
%    ROI from nearby ROIs. These operations are conducted in function ROIMSIR. Afterward, apply 
%    skin segmentation to the ROI and then take the RGB and luminance means of the ROI, which are
%    conducted in function ROIMeans_TakeMeans. ROIMeans_TakeMeans also adjusts the ROI to that of
%    the previous frame if it detects the proportion of pixels classified as skin is below the 
%    specified threshold.
%
%    To conduct the ROI-modification operations, a certain number of frames must have elapsed to
%    provide a sufficient number of ROIs on either side of the ROI to be processed. Further, before   
%    the ROI-means operations can be activated, the skin-detection operations must have completed  
%    scanning the frame for a detection, if needed, and the skin-detection operations require a 
%    certain number of detections to have previously occurred from which to draw skin-color samples.
%    Finally, both the ROI-means operations and the skin-detection operations rely upon tailored
%    skin segmentation, which, like the skin-detection operations, require certain number of 
%    detections to have previously occurred. Because of these needs for a sufficient number of 
%    frames to have elapsed, the operations in this nested function cannot occur simultaneouly with
%    frame reading. To improve efficiency by avoiding re-reading as few frames as possible, this
%    function conducts its operations a lagged number of frames behind the frame reading, where it
%    retrieves the frames stored in a cache. By retriving the frame from a cache, having been 
%    deposited on an earlier iteration by the frame reading, re-reading is mostly avoided.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% Declare persistent variables %%%%%% 

%These variables are not used outside of this function.

%Declare persistant variables
persistent FrameCache FrameCacheCounter FrameCacheKey ROINoMods ROINoResize ROINRows;

%Lock function to prevent it from being cleared, which prevents persistent variables from being
%reinitialized. The additional step of locking the function is necessary because the current
%function is called within a nested function, which does not have persistence. When the function
%reaches the last frame, the function will unlock itself (see code at end of function). Unlocking 
%the function allows the persistence of variables to be removed and permits any recent code 
%modifications to take effect.
mlock(); 


%%%%%% Cache frame for lagged ROI-means operations %%%%%%

%Cache frame during the same iteration the frame was read (the ith iteration) for later use for the
%ROI-means operations, which lag behind (the iith iteration) the frame reading.

%If first call to function
%Initialize variables. 
if i == 1  

    %Cell array to cache frames 
    FrameCache = cell(ROIGeneralConfig.FrameCacheMaxFrames, 1);

    %Counter to assign rows in cache
    FrameCacheCounter = int32(0);    

    %Key that matches the frame index to the rows of the cache
    FrameCacheKey = zeros(ROIGeneralConfig.FrameCacheMaxFrames, 1, 'int32');    
end

%If there are still frames being read by the video reader 
%If not, there is no need to continue to assign a frame to the cache.
if ContinueFrameReadTF

    %Advance counter
    FrameCacheCounter = FrameCacheCounter + 1;

    %Assign frame to cache
    FrameCache{FrameCacheCounter} = VidFrame;

    %Update frame cache key
    FrameCacheKey(FrameCacheCounter) = int32(i);

    %The last row in the cache has been assigned
    if FrameCacheCounter == ROIGeneralConfig.FrameCacheMaxFrames

        %Reset counter
        FrameCacheCounter = int32(0);       
    end
end


%%%%%% Determine whether conditions are ready for lagged ROI-means operations %%%%%%

%If ROI-means operations not ready
if ~ ROIGeneralConfig.ROIMeansOperationsReadyFirstReadTF

    if i > (ROIGeneralConfig.FrameCacheMaxFrames - 1) && ... Wait until the frame cache is nearly
                                                         ... filled so that the maximum number of
                                                         ... frames are available for ROI 
                                                         ... modifications, which may improve the
                                                         ... accuracy of the modifications 
                                                         ... (conducted by function ROIMSIR).
       SkinSegmentConfig.TailoredData.OpsReadyTF && ... Thresholds have been set at least once for  
                                                    ... tailored skin segmentation, which is   
                                                    ... required for ROI-means operations.
       SkinDetectConfig.SkinDetectionReadyTF %The thresholds have been set for the skin-detection 
                                             %algorithm and the required number of frames has  
                                             %elapsed to form a skin-detection bounding box, both  
                                             %of which are required to activate the skin-detection
                                             %algorithm. Activation of the skin-detection algorithm    
                                             %is required to ROI-means operations.   

        %Flag that ROI-means operations are ready to begin
        ROIGeneralConfig.ROIMeansOperationsReadyFirstReadTF = true;               
    end
end


%%%%%% Lagged ROI-means operations %%%%%%

%If ready for ROI-means operations
if ROIGeneralConfig.ROIMeansOperationsReadyFirstReadTF 

    %%%%%% --- Advance index and assign variables %%%%%%

    %If first call once ROIGeneralConfig.ROIMeansOperationsReadyFirstReadTF == true
    %Initialize variables.
    if ii == 0

        %Set first frame index to be processed
        %The first frame processed will be the earliest frame available from the cache.
        %The earliest frame available (index ii) is a certain number of frames behind the current 
        %frame-reading iteration (i); the number of frames back is 
        %ROIGeneralConfig.FrameCacheMaxFrames - 1.
        %Specify type int32 for protection against floating-point gaps.
        ii = int32(i) - (ROIGeneralConfig.FrameCacheMaxFrames - 1);

        %Frame index indicating the first frame that underwent ROI size-matching, smoothing,
        %interpolation, and resizing. This will be used by function ROIMSIR.
        %Specify type int32 for protection against floating-point gaps.
        ROIGeneralConfig.ROIMSIR_FirstFrameIdx = int32(ii);

        %Record frame index up to which operations (tailored skin segmentation, skin detection,  
        %taking ROI means) will be conducted in the second read. This index will correspond to the
        %frame before the first frame processed here. See function ROIGeneralConfig_Setup for 
        %details.
        %Specify type int32 for protection against floating-point gaps.
        ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx = int32(ii - 1);       

        %Assign ROIs to a matrix that will not receive size matching, smoothing, interpolation,  
        %and resizing. The values in this matrix will be used for most operations in function 
        %ROIMSIR. Values without these modifications are needed as input because, otherwise, a
        %positive feedback loop will develop, resulting in inaccurate ROI oscillations across  
        %frames (see note in the file for function ROIMSIR). 
        %M x 4 matrix; type int16.
        ROINoMods = ROI;         
        
        %Preallocate the matrix for non-resized ROIs returned by function ROIMSIR 
        %This matrix will be used as input on each call to function ROIMSIR.
        %M x 4 matrix; type int16.
        ROINoResize = zeros( size(ROI), 'int16' );           
        
        %Number of rows in ROI matrices
        %Used for indexing.
        ROINRows = size(ROI, 1);
        
        %Flag to function ROIMSIR that function ROIMSIR has been called previously        
        FirstCallTF = true;
        
    %Subsequent calls    
    else         

        %Advance index used for ROI-means operations
        ii = ii + 1;   

        %Assign, frame-by-frame, ROIs to ROINoMods
        %Note: although the ROI-means operations frame index (ii) lags behind the frame-reading
        %index (i), where the most recent ROI detections are made, ROI-means operations needs  
        %access to the most recent detections because it uses a span of ROIs on either side of the
        %ROI-means operations frame index. For this reason, this variable is updated with the most  
        %recent ROIs (from the i index). 
        %Type int16.
        ROINoMods(i, :) = ROI(i, :);   
        
        %Flag to function ROIMSIR that function ROIMSIR has not been called previously
        FirstCallTF = false;
    end    

    %%%%%% --- Extract iith frame from cache %%%%%%    

    %Extract iith frame for ROI means operations 
    VidFramePrevious = FrameCache{FrameCacheKey == ii};

    %%%%%% --- Lagged ROI modifications for iith ROI %%%%%%

    %Conduct ROI modifications: size matching, detection smoothing, interpolation, frame-by-frame  
    %smoothing, and resizing. For a detailed description, see function ROIMSIR.
    
    %Arguments to function ROIMSIR:    
    
    %Set frame index for block of ROIs used to facilitate ROI modifications for iith ROI.
    %Type int32 for protection against floating-point gaps.
    %Row vector; type int32.
    %Note: function ROIMSIR relies on this index consisting of elements that increase linearly by 
    %one integer.
    BlockFullLinIdx = ...
        ii - (ROIGeneralConfig.FrameCacheMaxFrames - 1) : ...
        min( ...
            ii + (ROIGeneralConfig.FrameCacheMaxFrames - 1), ... index of last element of cache
            min( ...
                int32(VideoReadConfig.MaxFrameIdx),          ... maximum frame index
                ROINRows                                     ... index of last row of ROI matrices
            ) ...
        );
    
    %Transpose to column vector
    BlockFullLinIdx = BlockFullLinIdx(:);
    
    %The function is called within the first read.
    %ROIs are processesed sequentially (one-by-one) rather than as a vectorized operation. An ROI 
    %of one row (1 x 4) is returned.
    FirstReadTF = true;

    %Specify row to return from ROI input matrix (ROI)
    %Type int32.
    RowToReturnLinIdx = ii;

    %Argument not relevant in first-read operations
    SecondReadPostProcessingTF = false;
    
    %Whether testing is enabled to determine whether ROI widths and heights are below a certain  
    %value after various steps of the operations.                              
    %If below the value, this may indicate that the implementation is not behaving as expected. 
    %Occasionally, however, widths or heights may be below the value in the absence of an
    %implementation issue. If a width or height is below the value, a warning is displayed. This                               
    %option is intended to be enabled only during testing. Otherwise, to increase efficiency and                               
    %avoid the display of unnecessary warnings, it should be disabled.                             
    ExpectedBehaviorTestTFCode = false;
    
    %Compiled function
    if ROIGeneralConfig.UseCompiledFunctionsTF

        %Note: tildes indicate output arguments only used in second-read operations (see function
        %ROIMeans_SecondRead). 
        %ROIMSIR_mex is a custom compiled-C function located within folder FacePulseRate. For   
        %source code, see file ROIMSIR.m.
        [ROIOut_FirstRead_ii, ~, InterpolatedLinIdx_FirstRead_ii, ~, ...
         ROIOutBeforeFrameByFrameSmoothing_FirstRead_ii, ~, ROIOutNoResize_FirstRead_ii, ...
         ROIMatchSizeData] = ...
            ROIMSIR_mex(BlockFullLinIdx, ROI, VideoReadConfig.FrameTimestampUntrimmed_Single, ...
                HasROI_TF, ROIGeneralConfig.ROIMSIR_DiffMaxDetection, ...
                ROIGeneralConfig.ROIMSIR_DiffMaxAdjacent, ...               
                ROIGeneralConfig.ROIWidthResizeFactor, ROIGeneralConfig.ROIHeightResizeFactor, ... 
                FaceDetectConfig.ROIFaceSmoothingWindow, FaceDetectConfig.ROIFaceSecondary1TF, ...
                FaceDetectConfig.ROIFaceSecondary2TF, SkinDetectConfig.ROISkinSmoothingWindow, ...
                ROIGeneralConfig.ROIFinalSmoothingWindows, VideoReadConfig.VidObjWidth, ... 
                VideoReadConfig.VidObjHeight, ExpectedBehaviorTestTFCode, FirstReadTF, ... 
                FirstCallTF, VideoReadConfig.FrameIdx, RowToReturnLinIdx, ... 
                ROIGeneralConfig.ROIMSIR_FirstFrameIdx, ROINoMods, ROINoResize, ...
                ROIMatchSizeData, SecondReadPostProcessingTF);

    %Non-compiled function    
    else

        %Note: tildes indicate output arguments only used in second-read operations (see function
        %ROIMeans_SecondRead). 
        %'ROIMSIR' is a custom function located within folder 'FacePulseRate'. 
        [ROIOut_FirstRead_ii, ~, InterpolatedLinIdx_FirstRead_ii, ~, ...
         ROIOutBeforeFrameByFrameSmoothing_FirstRead_ii, ~, ROIOutNoResize_FirstRead_ii, ...
         ROIMatchSizeData] = ...        
            ROIMSIR(BlockFullLinIdx, ROI, VideoReadConfig.FrameTimestampUntrimmed_Single, ...
                HasROI_TF, ROIGeneralConfig.ROIMSIR_DiffMaxDetection, ... 
                ROIGeneralConfig.ROIMSIR_DiffMaxAdjacent, ...
                ROIGeneralConfig.ROIWidthResizeFactor, ROIGeneralConfig.ROIHeightResizeFactor, ... 
                FaceDetectConfig.ROIFaceSmoothingWindow, FaceDetectConfig.ROIFaceSecondary1TF, ...
                FaceDetectConfig.ROIFaceSecondary2TF, SkinDetectConfig.ROISkinSmoothingWindow, ...
                ROIGeneralConfig.ROIFinalSmoothingWindows, VideoReadConfig.VidObjWidth, ... 
                VideoReadConfig.VidObjHeight, ExpectedBehaviorTestTFCode, FirstReadTF, ... 
                FirstCallTF, VideoReadConfig.FrameIdx, RowToReturnLinIdx, ... 
                ROIGeneralConfig.ROIMSIR_FirstFrameIdx, ROINoMods, ROINoResize, ...
                ROIMatchSizeData, SecondReadPostProcessingTF);                 
    end
    
    %Assign modified ROI for use below in function ROIMeans_TakeMeans 
    %1 x 4 row vector; type int16.
    ROI(ii, :) = ROIOut_FirstRead_ii; 

    %Assign the modified but non-resized ROI 
    %This will be used as input on each call to function ROIMSIR.
    %1 x 4 row vector; type int16.
    ROINoResize(ii, :) = ROIOutNoResize_FirstRead_ii;
    
    %Record use of interpolation for use below in function ROIMeans_TakeMeans 
    %0 indicates the iith ROI was not interpolated.
    if InterpolatedLinIdx_FirstRead_ii ~= 0

        HasROI_TF.Interpolated(InterpolatedLinIdx_FirstRead_ii) = true;  
    end

    %Note: ROIOut_ii and InterpolatedLinIdx_ii will also be output of function 
    %ROIMeans_FirstRead_TakeMeans, and they will be assigned on a persistent basis to variables ROI 
    %and HasROI_TF in function ROIMeans_FirstRead; ROI and HasROI_TF are not assigned as output in 
    %function ROIMeans_FirstRead_TakeMeans to avoid inefficiency that would otherwise result from  
    %reassiging the entirety of the variables on each iteration.     
    
    %%%%%% --- Lagged tailored skin segmentation and taking of ROI means for iith ROI %%%%%%    
    
    %Flag that function called from first-read operations
    FirstReadTF = true;
    
    %Conduct operations for the iith frame
    %Note: the final input argument only used during the current function.
    %Note: ROIMeans_TakeMeans is a custom function located within folder 'FacePulseRate'.
    [SkinRGBMeans_ii, IsNotSkin_PixelColor_Packed_ii, AdjustedBecauseLowSkinProportionTF_ii, ...
     ROIAdjusted_ii, Y_of_YCbCr_ii, L_of_LAB_ii] = ...
        ROIMeans_TakeMeans(ii, VidFramePrevious, ROI, SkinSegmentConfig, ...
            PulseRateConfigAndData.ControlLuminanceTF, ...                 
            PulseRateConfigAndData.ControlLuminanceColorspace, OutputConfig.WriteVideoTF, ...
            OutputConfig.WriteVideoShowSkinSegmentTF, VideoReadConfig.FrameIdx, ...
            VideoReadConfig.VidObjWidth, VideoReadConfig.VidObjHeight, ...
            ROIGeneralConfig.ROIMSIR_FirstFrameIdx, FirstReadTF);

        
%%%%%% Not ready for ROI means operations %%%%%%  

else

    %Assign empty values.

    ROIOut_FirstRead_ii                            = int16([]); 
    ROIOutBeforeFrameByFrameSmoothing_FirstRead_ii = int16([]);
    InterpolatedLinIdx_FirstRead_ii                = int32([]);
    SkinRGBMeans_ii                                = [];
    IsNotSkin_PixelColor_Packed_ii                 = uint32([]);
    AdjustedBecauseLowSkinProportionTF_ii          = false;
    ROIAdjusted_ii                                 = int16([]);
    Y_of_YCbCr_ii                                  = [];
    L_of_LAB_ii                                    = [];
end


%%%%%% Unlock function on final call to function %%%%%%

%Maximum frame index reached
if ii == VideoReadConfig.MaxFrameIdx  

    %Unlock function, which allows persistent variables to be cleared when the function ends; 
    %additionally, unlocking is necessary for any recent code modifications to take effect. One
    %persistent variable, the frame cache, requires a large memory allocation, so clearing the
    %persistence frees much memory.
    
    %Note: Because the function is called by a nested function, the variables do not need to be 
    %explicitly cleared; rather, unlocking the function is sufficient to remove their persistence.
    
    %Note: Some conditions may prevent this procedure from occurring. These include an error being
    %being thrown, the use of ctrl+c, or the case where no frames are ultimately processed by the 
    %current function. To unlock the function is these cases, a clean up object has been inserted 
    %into function ROIMeans_FirstRead, which calls the nested function that calls the current 
    %function.
    
    munlock('ROIMeans_FirstRead_TakeMeans');
end


end %end function

