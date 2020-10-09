function [ROI, ROIForBBox, ROIDiagnostic, HasROI_TF, ROIMatchSizeData] = ...
             ROIMeans_ROIVarsSetup(VideoReadConfig, ROIGeneralConfig)                
%ROIMeans_ROIVarsSetup    Setup ROI variables for use across functions.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions ValidateAndConfigure and
%    SkinSegment_OversegmentationCheck_Reduce.
%
%
%    Description
%    -----------
%
%    Setup ROI variables for use across functions. 
%
%    -- Notes --
%    
%    Function SkinDetect_ConfigSetup adds an additional field to struct ROIDiagnostic.
%
%    The variables preallocated here may be preallocated again after processing begins if function
%    ROIMeans_FirstRead is called recursively (see function
%    SkinSegment_OversegmentationCheck_Reduce).
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%Assign number of frames
NFrames = VideoReadConfig.NFrames;


%%%%%% Preallocate ROI matrix %%%%%%

%ROIs of the face or skin region for each frame.

%ROI box coordinates: x, y, width, height (in pixels).
%The face ROI is a rectangle; x and y indicate the upper-left-hand corner of the box.
%Although the X-coordinate typically increases from bottom to top, the X-coordinate used here, as
%with typical Matlab usage, increases from top to bottom. This is because the X-coordinate is used
%interchangeably with row indexing.

%Specify type int16 for faster evaluation where used.
%A signed type is used to facilitate some operations that expect negative numbers.
ROI = zeros(NFrames, 4, 'int16'); 

%ROIs with any adjustment from arguments ROIFace_ChangeFactorROIPrimary,  
%ROIFace_ChangeFactorROISecondary1, or ROIFace_ChangeFactorROISecondary2. 
%Used when determining bounding boxes (see function ROIMeans_FirstRead_SetBoundingBoxes).
%Specify type int16 for faster evaluation where used.
%A signed type is used to facilitate some operations that expect negative numbers.
ROIForBBox = zeros(NFrames, 4, 'int16');


%%%%%% Setup ROI(s) specified by argument %%%%%%

%ROISpecifiedByArgument, an argument to function FacePulseRate, specifies the frame index of the
%ROI(s) and the values of the ROI(s) to be inserted into the ROI matrix. 
%The frame index of the ROI(s) is specified by column 1 of ROISpecifiedByArgument.
%The values of the ROI(s) are specified by columns 2 to 5.

%Description:

%For these ROI(s), the detection algorithms will not reassign the ROI(s) that have been specified.  
%The specified ROI(s) will still be size matched, smoothed, and resized as if they were assigned by  
%a detection algorithm. Specifying the ROI(s) is implemented by having function  
%ROIMeans_FirstRead_DetermineSkipFrame cause the detection algorithms to be skipped for the 
%specified frames so that the specified ROI(s) are not reassigned. Function ROIMSIR, which handles 
%size matching, smoothing, and resizing, will treat the specified ROI(s) as if they were
%face-detection algorithm detections. Any specified ROI(s) will be noted in the ROI description of
%the output video for the corresponding frames.

%If argument used
%A row vector of -1 is the default values, which indicate that no ROIs are assigned by argument.
if ROIGeneralConfig.ROISpecifyByArgument(1, 1) ~= -1

    %Convert frame index specified, which is the frame index aligned with the length of the video
    %starting at time = 0 sec., to align with the length of the video starting at StartTime, which
    %may not necessarily = 0.
    FrameIdxAdjusted = ...
        ROIGeneralConfig.ROISpecifyByArgument(:, 1) -   ... Frame index specified
        double(VideoReadConfig.FrameIdx(1) + 1);        %   Number of frames before StartTime 
                                                        %   plus 1.
    
    %The frame index of ROISpecifyByArgument must be less than the maximum frame index, NFrames, of 
    %the video or the video to be processed. 
    %Note: if the video reader is vision.VideoFileReader, NFrames will be equal to, or very close 
    %to, the frame index corresponding to EndTime.
    %If the video reader is VideoReader, NFrames will be equal to the final frame of the entire 
    %video, regardless of EndTime. 
    if max(FrameIdxAdjusted) > NFrames

        ME = ...
            MException( ...
                'Component:Argument', ...
                 ['Error: The frame index specified by ROISpecifyByArgument (column 1) exceeds', ...
                  ' the maximum frame index, ', num2str( VideoReadConfig.FrameIdx(NFrames) ), ... 
                  ', of the portion of the video to be processed.'] ...
            );
              
        %Throw exception 
        throw(ME)        
    end      
    
    %Assign ROI(s) specified by argument
    ROI(FrameIdxAdjusted, :) = ... adjusted frame index 
        ROIGeneralConfig.ROISpecifyByArgument(:, 2 : 5);
    
    %Assign logical index indicating which ROIs will be specified
    ROISpecifiedByArgumentTF = false(NFrames, 1);
    ROISpecifiedByArgumentTF(FrameIdxAdjusted) = true;

%Argument not used
else
 
    ROISpecifiedByArgumentTF = false(NFrames, 1);
end


%%%%%% Setup ROI(s) to be ignored, as specified by argument %%%%%%

%ROIIgnoreByArgument, an argument to function FacePulseRate, specifies the frame index of ROI(s) to
%ignore if corresponding detection(s) are made by a detection algorithm. 

%Description:

%If ignored, ROI(s) found by detections for the corresponding frames will be ignored, and the 
%ROI(s) will be interpolated by nearby ROIs. 
%Ignoring the ROI(s) is implemented by having function ROIMeans_FirstRead_DetermineSkipFrame cause
%the detection algorithms to be skipped for the specified frames. Any ignored frame will be noted 
%in the ROI description on the output video for the corresponding frames. In function 
%ROIMeans_FirstRead, the corresponding indices for HasROI_TF.ByAnyMethod are marked as true so that
%function ROIMeans_TakeMeans conducts skin segmentation and RGB means processing and so that
%function WriteFaceVideo displays the ROI on the output video.

%If argument used
%-1 is the default value, which indicates that no ROIs are to be ignored.
if ROIGeneralConfig.ROIIgnoreByArgument(1) ~= -1

    %Convert frame index specified, which is the frame index aligned with the length of the video
    %starting at time = 0 sec., to align with the length of the video starting at StartTime.
    FrameIdxAdjusted = ...
        ROIGeneralConfig.ROIIgnoreByArgument -            ... Frame index specified
        double(VideoReadConfig.FrameIdx(1) + 1);          %   Number of frames before StartTime 
                                                          %   plus 1.
    
    %The frame index of ROIIgnoreByArgument must be less than the maximum frame index, NFrames, of 
    %the video or the video to be processed. 
    %Note: if the video reader is vision.VideoFileReader, NFrames will be equal to, or very close 
    %to, the frame index corresponding to EndTime.
    %If the video reader is VideoReader, NFrames will be equal to the final frame of the entire 
    %video, regardless of EndTime. 
    if max(FrameIdxAdjusted) > NFrames

        ME = ...
            MException( ...
                'Component:Argument', ...
                ['Error: The frame index specified by ROIIgnoreByArgument exceeds', ...
                 ' the maximum frame index, ', num2str( VideoReadConfig.FrameIdx(NFrames) ), ... 
                 ', of the portion of the video to be processed.'] ...
            );
        
        %Throw exception      
        throw(ME)        
    end      
    
    %Assign logical index indicating which ROIs to ignore
    ROIIgnoreByArgumentTF = false(NFrames, 1);
    ROIIgnoreByArgumentTF(FrameIdxAdjusted) = true; %adjusted frame index
    
%Argument not used
else
    
    ROIIgnoreByArgumentTF = false(NFrames, 1);
end


%%%%%% Preallocate struct for ROI-detection diagnostics %%%%%%

%Store information for diagnosing ROI detections. This information will be displayed on the output
%video.

%%%%%% --- Preallocate struct for storing coordinates of bounding box used for scanning for ROI %%%%%% 

%Preallocate matrix for storing the borders of bounding boxes used to bound the scanning by the
%face-detection and skin-detection algorithms. The coordinates are displayed on the output video
%for diagnositic purposes. For example, they can be used to diagnosis cases where the bounding box  
%appears to be too small to permit detections or so large as to result in higher computation time  
%for the detection algorithms. For details about the use of bounding boxes, see function 
%ROIMeans_FirstRead_SetBoundingBoxes and notes in function ROIMeans_FirstRead.

%A bounding box is not used for frames where a detection algorithm was not run. For these frames, 
%no bounding box values will be reassigned and no bounding box will appear on the output video.

%Specify type uint16 for memory conservation and faster evaluation where used.
%Although the function used to assign bounding boxes, ROIMeans_FirstRead_SetBoundingBoxes, uses  
%type int16, this variable uses type uint16 because signed operations are not needed with it.

BBox_Scan = ...
    struct( ...
        'FaceAlg', zeros(NFrames, 4, 'uint16'), ...
        'SkinAlg', zeros(NFrames, 4, 'uint16') ...
    );

%Assign to ROIDiagnostic struct
ROIDiagnostic.BBox_Scan = BBox_Scan;

%%%%%% --- Preallocate ROI matrices to provide diagnostics on ROI modifications %%%%%%

%ROIs in different states of modifications will be recorded to diagnose apparent false positives
%or false negatives that may have been caused by these modifications. The modifications that will
%be applied are conducted by function ROIMSIR, which is called in function ROIMeans_FirstRead and
%in the pre-processing and post-processing steps of function ROIMeans_SecondRead. These ROIs will
%be displayed on the output video.

%Preallocate ROI matrix for ROIs corresponding to a detection algorithm without modifications by 
%function ROIMSIR.
%Note: interpolated ROIs are not included.
%The ROI coordinates will be superimposed on the output video for assessment. 
%Specify type uint16 for memory conservation and faster evaluation where used.
%Although matrix ROI uses type int16, this variable uses type uint16 because signed operations are
%not needed.
ROIDiagnostic.ROI_NonSmoothed = zeros(NFrames, 4, 'uint16');

%Preallocate ROI matrix for ROIs corresponding to a detection algorithm or interpolated ROIs before  
%frame-by-frame smoothing and resizing modifications. If interpolated, this shows the ROI directly  
%after interpolation by function ROIMSIR. If a detection, this shows the ROI after size matching
%and detection-smoothing by function ROIMSIR. For either case, frame-by-frame smoothing and 
%resizing, conducted in function ROIMSIR, have not yet been applied.
%Specify type uint16 for memory conservation and faster evaluation where used.
%Although matrix ROI uses type int16, this variable uses type uint16 because signed operations are
%not needed.
ROIDiagnostic.ROI_NonFinalSmoothed = zeros(NFrames, 4, 'uint16');
  
%Note: the final ROI will include modifications by frame-by-frame smoothing and resizing. 

%%%%%% --- Initialize struct to store skin-detection algorithm diagnostics %%%%%%

%Values will be assigned by function SkinDetect_RecordDiagnosticData, which is called by function
%SkinDetect.

ROISkin = ...
    struct( ...
        'ConductedTF',         false, ...
        'RegionBoundaries',    [], ...
        'RegionCentroids',     [], ...
        'PredictedROI_center', [], ...
        'RegionScores',        [], ...
        'RegionCrSDScores',    [], ...
        'RegionRankings',      [], ...
        'RegionNPixels',       [], ...
        'RegionNThreshold',    []  ...
    );   

ROIDiagnostic.ROISkin = ROISkin;


%%%%%% Preallocate or assign detection status struct %%%%%%

%Assign a logical vector to each field according to the length of the number frames.

%Description:

% - FacePrimary, FaceSecondary1, FaceSecondary2, Skin: indicates a detection by the respective
%   algorithm. These categories are mutually exclusive because, once a detection is found, no
%   other algorithm is applied to the frame.
%
% - FacePrimaryAttempted, FaceSecondary1Attempted, FaceSecondary2Attempted, SkinAttempted: the
%   respective algorithm was applied to the frame and either a detection was found or not found.
%   These categories are not mutually exclusive because, unless the frame is skipped, each 
%   algorithm will be applied to the frame until a detection is found. If none of these is present,
%   this indicates the frame was skipped for efficiency.
%
% - Interpolated: the ROI for the frame was interpolated from nearby frames because either the
%   frame was skipped or no detection was found by any algorithm. This indication is mutually
%   exclusive with FacePrimary, FaceSecondary1, FaceSecondary2, and Skin. The status may change   
%   after being assigned. For example, any frame that does not have an ROI after function 
%   ROIMeans_FirstRead will have been interpolated. Then, in function SkinDetect, frames without  
%   face detections that meet the scanning criteria will have the skin-detection algorithm applied;
%   if a detection is found, the interpolation status will be removed and the skin-detection 
%   status will be added.
%
% - SkinNotPresent_Pri, SkinNotPresent_Sec1, SkinNotPresent_Sec2, SkinNotPresent_Skin: Whether 
%   function ConfirmSkinPresent determined that the ROI did not contain skin. This value is 
%   assigned after a tentative detection is made by a face-detection algorithm (see function  
%   FaceDetect_ROIValidate) or the skin-detection algorithm (see function 
%   SkinDetect_SelectedRegionROI). 
%
% - ProfileEyesPresent_Pri, ProfileEyesPresent_Sec1, ProfileEyesPresent_Sec2: Whether a pair of 
%   eyes was detected in a frame where a tentative detection was made by a face-detection algorithm  
%   that targets faces in a profile orientation. (See function FaceDetect_ROIValidate). If this  
%   value is true, then the tentative ROI would have been rejected.
%   function ConfirmSkinPresent determined that the ROI did not contain skin. This value is 
%   assigned after a tentative detection is made by a face-detection algorithm (see function  
%   FaceDetect_ROIValidate) or the skin-detection algorithm (see function 
%   SkinDetect_SelectedRegionROI). If this value is true, then the tentative ROI would have been
%   rejected.
%
% - AdjustedBecauseLowSkinProportion: Function ConfirmSkinPresent determined the ROI does not 
%   contain skin. As a result, the ROI was adjusted to that of the ROI a few frames back. This
%   is conducted by function ROIMeans_TakeMeans.
%   ConfirmSkinPresent returned a value of false, which indicates the ROI may not contain skin.
%
% - ROISpecifiedByArgument: The ROI(s) to use for specified frame(s) were specified as an argument  
%   to function FacePulseRate.
%
% - ROIIgnoreByArgument: The ROI(s) corresponding to detections for specified frames will be
%   ignored; these ROI(s) will be interpolated from ROIs of nearby frames. The frames for which
%   ROI(s) will be ignored were specified by an argument to function FacePulseRate.

%Note: the form of the struct below, including the order of the fields, must be maintained for
%compatibility with the compiled function ROIMSIR_mex. If modified, then function ROIMSIR_mex 
%should be recompiled with the modifications applied to the arguments declared in the code 
%generation / build file (see file ROIMSIR.m).

HasROI_TF = ...
    struct( ...  
        'FacePrimary',                      false(NFrames, 1), ...
        'FacePrimaryAttempted',             false(NFrames, 1), ...
        'SkinNotPresent_Pri',               false(NFrames, 1), ...
        'ProfileEyesPresent_Pri',           false(NFrames, 1), ...
        'FaceSecondary1',                   false(NFrames, 1), ...
        'FaceSecondary1Attempted',          false(NFrames, 1), ...
        'SkinNotPresent_Sec1',              false(NFrames, 1), ...
        'ProfileEyesPresent_Sec1',          false(NFrames, 1), ...
        'FaceSecondary2',                   false(NFrames, 1), ...
        'FaceSecondary2Attempted',          false(NFrames, 1), ...
        'SkinNotPresent_Sec2',              false(NFrames, 1), ...
        'ProfileEyesPresent_Sec2',          false(NFrames, 1), ...
        'Skipped',                          false(NFrames, 1), ...
        'Skin',                             false(NFrames, 1), ...
        'SkinAttempted',                    false(NFrames, 1), ...
        'SkinNotPresent_Skin',              false(NFrames, 1), ... 
        'Interpolated',                     false(NFrames, 1), ...      
        'AdjustedBecauseLowSkinProportion', false(NFrames, 1), ...
        'ROISpecifiedByArgument',           ROISpecifiedByArgumentTF, ...
        'ROIIgnoreByArgument',              ROIIgnoreByArgumentTF ...
    );


%%%%%% Preallocate struct for use in function ROIMSIR %%%%%%

ROIMatchSizeData = ...
    struct( ...
        'SumW_Pri', single(0), ...
        'SumH_Pri', single(0), ...
        'AlgN_Pri', single(0), ...
        'ROIMeanWidthPri', single(0), ...
        'ROIMeanHeightPri', single(0), ...
        'SumW_Sec1', single(0), ... 
        'SumH_Sec1', single(0), ...
        'AlgN_Sec1', single(0), ...
        'ROIMeanWidthSec1', single(0), ...
        'ROIMeanHeightSec1', single(0), ...
        'SumW_Sec2', single(0), ...
        'SumH_Sec2', single(0), ...
        'AlgN_Sec2', single(0), ...
        'ROIMeanWidthSec2', single(0), ...
        'ROIMeanHeightSec2', single(0), ...
        'SumW_Skin', single(0), ...
        'SumH_Skin', single(0), ...
        'AlgN_Skin', single(0), ...
        'ROIMeanWidthSkin', single(0), ...
        'ROIMeanHeightSkin', single(0) ... 
    );        


end %end function

