function [VideoReadConfig, ROI, HasROI_TF, ROIDiagnostic, SkinSegmentConfig, ...
          PulseRateConfigAndData, ROIGeneralConfig, DataForSkinDetection, ...
          DataForTailoredSkinSegmentation] = ...
             ROIMeans_FirstRead_Trim(VideoReadConfig, ROI, HasROI_TF, ROIDiagnostic, ...
                 SkinSegmentConfig, ROIGeneralConfig, PulseRateConfigAndData, ...
                 DataForSkinDetection, DataForTailoredSkinSegmentation)
%ROIMeans_FirstRead_Trim   Trim variables up to EndTime after the last frame has been read by the
%                          first-read operations.
%   
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead_PostProcess.
%
%
%    Description
%    -----------
%
%    This function is called after all frames that lie between StartTime and EndTime have been read 
%    by the first-read operations. Prior to all frames having been read, the number of frames that
%    lie between StartTime and EndTime has been estimated but not known exactly (for a description 
%    of why the number of frames is not known in advance, see function VideoReadConfig_Setup). As 
%    all frames have now been read, the number of frames between StartTime and EndTime is now 
%    known, so preallocated variables whose length was based upon the estimated number of frames 
%    can be trimmed to the length of the exact number of frames. This function trims such 
%    variables.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Determine number of frames %%%%%%

%Use the original timestamps (VideoReadConfig.FrameTimestampUntrimmed_Double), which are of type 
%double, to determine which frames to retain. 
%Note that the timestamps that were converted to type single 
%(VideoReadConfig.FrameTimestampUntrimmed_Single) sometimes yield different frames than the
%original timestamps when compared to EndTime. To ensure all variables use the same set of frames,
%only use the original timestamps for determining the frames to retain.

%Logical index of frames before EndTime
RowsToRetainLogIdx = ...
    VideoReadConfig.FrameTimestampUntrimmed_Double < VideoReadConfig.EndTime;

%Trim original timestamps and assign to new variable 
VideoReadConfig.FrameTimestamp_Double = ...
    VideoReadConfig.FrameTimestampUntrimmed_Double(RowsToRetainLogIdx);

%%%%%% --- Ensure timestamps are in chronological order %%%%%%

%If not in chronological order, problems could arise in function PulseRate.
%If not in chronological order, the non-chronological order typically occurs with the last couple 
%of timestamps. Remove the frames that correspond to such timestamps.

%Logical index of timestamps not in chronological order
NonChronLogIdx = [false; diff(VideoReadConfig.FrameTimestamp_Double) <= 0];

%Remove timestamps once timestamps are not in chronological order
if any(NonChronLogIdx)
    
    %Linear index of the first frame where the timestamp is not in chronological order
    NonChronLinIdx_First = find(NonChronLogIdx, 1, 'first');

    %Linear index from first timestamp not in chronological order to end of video
    NonChronLinIdx = NonChronLinIdx_First : length(VideoReadConfig.FrameTimestamp_Double);

    %Linear index of remaining timestamps
    ChronLinIdx = setdiff(1 : length(VideoReadConfig.FrameTimestamp_Double), NonChronLinIdx);
    
    %Display warning
    warning(['Timestamp(s) ', ...
             num2str( VideoReadConfig.FrameTimestamp_Double(NonChronLinIdx_First) ), ... 
             ' not in chronological order; frames from this point until the end of the video', ...
             ' will not be processed.']);
     
    %Remove timestamps from first timestamp not in chronological order to end of video     
    VideoReadConfig.FrameTimestamp_Double = ...
        VideoReadConfig.FrameTimestamp_Double(ChronLinIdx);
    
    %Revise logical index indicating which frames to retain
    RowsToRetainLogIdx(NonChronLinIdx) = false; 
end    


%%%%%% Update and trim other variables %%%%%%

VideoReadConfig.FrameTimestamp_Single = ...
    VideoReadConfig.FrameTimestampUntrimmed_Single(RowsToRetainLogIdx);
    
%Remove fields of untrimmed timestamps
VideoReadConfig = ...
    rmfield(VideoReadConfig, {'FrameTimestampUntrimmed_Double', 'FrameTimestampUntrimmed_Single'});

%Update EndTime
VideoReadConfig.EndTime = VideoReadConfig.FrameTimestamp_Double(end);

VideoReadConfig.NFrames = int32( nnz(RowsToRetainLogIdx) );  

VideoReadConfig.FrameIdxFromStart = VideoReadConfig.FrameIdxFromStart(RowsToRetainLogIdx);

VideoReadConfig.FrameIdx = VideoReadConfig.FrameIdx(RowsToRetainLogIdx);

ROI = ROI(RowsToRetainLogIdx, :);

HasROI_TF = ... 
    structfun(@(x) x(RowsToRetainLogIdx), ...
        HasROI_TF, ...
        'UniformOutput', false);

ROIDiagnostic.ROI_NonSmoothed = ROIDiagnostic.ROI_NonSmoothed(RowsToRetainLogIdx, :);
ROIDiagnostic.ROI_NonFinalSmoothed = ROIDiagnostic.ROI_NonFinalSmoothed(RowsToRetainLogIdx, :);

ROIDiagnostic.BBox_Scan = ...
    structfun(@(x) x(RowsToRetainLogIdx, :), ...
        ROIDiagnostic.BBox_Scan, ...
        'UniformOutput', false);

PulseRateConfigAndData.ColorData.SkinRGBMeans = ...
    PulseRateConfigAndData.ColorData.SkinRGBMeans(RowsToRetainLogIdx, :); 

if PulseRateConfigAndData.ControlLuminanceTF
    
    if PulseRateConfigAndData.ControlLuminanceColorspace == 'Y'
        
        PulseRateConfigAndData.ColorData.SkinLuminanceMeans.Y_of_YCbCr = ...
            PulseRateConfigAndData.ColorData.SkinLuminanceMeans.Y_of_YCbCr(RowsToRetainLogIdx);
        
    elseif PulseRateConfigAndData.ControlLuminanceColorspace == 'L'
        
        PulseRateConfigAndData.ColorData.SkinLuminanceMeans.L_of_LAB = ...
            PulseRateConfigAndData.ColorData.SkinLuminanceMeans.L_of_LAB(RowsToRetainLogIdx);
    end
end

if ~ ROIGeneralConfig.ROIMeansOperationsReadyFirstReadTF
    
    ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx = VideoReadConfig.NFrames;
end

%The follow variables currently are not used outside of function ROIMeans_First; however, for 
%robustness, they are trimmed.

DataForSkinDetection.RGBMeans = ...
    DataForSkinDetection.RGBMeans(RowsToRetainLogIdx, :);
    
DataForSkinDetection.YCbCrMeans = ...
    DataForSkinDetection.YCbCrMeans(RowsToRetainLogIdx, :);

DataForTailoredSkinSegmentation = ...
    DataForTailoredSkinSegmentation(RowsToRetainLogIdx, :);


end %end function


