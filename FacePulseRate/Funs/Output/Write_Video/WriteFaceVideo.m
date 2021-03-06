function WriteFaceVideo(VideoReadConfig, ROI, HasROI_TF, ROIDiagnostic, SkinSegmentConfig, ...
             PulseRateConfigAndData, ROIGeneralConfig, FaceDetectConfig, SkinDetectConfig, ...
             SkinSegmentMasks, OutputConfig, UseCompiledFunctionsTF)                                                                   
%WriteFaceVideo   Write video with pulse rate and diagnostic annotations.
%
%   Helper function to function FacePulseRate.
%
%
%   Description
%   -----------
%
%   Write output video with annotations on each frame regarding frame information, ROI detection, 
%   skin segmentation, and pulse rate. 
%
%   -- Differences Between Output Video Seek Time and Timestamp Annotations --
%
%       On the output video, the timestamp annotations, but not necessarily the seek time, will
%       correspond to the seek time of input video.
%
%   -- Annotations --
%
%       - Timestamp
%       - Frame index
%       - Indication if ROI skipped, which is influenced by argument ROISkinSkipFrameThreshold.
%       - Indication if ROI ignored, as specified by argument ROIIgnoreByArgument, or if ROI 
%         specified, as specified by argument ROISpecifyByArgument. 
%       - Skin-segmentation mask. A semi-transparent skin-segmentation mask is superimposed on 
%         pixels. The mask indicates pixels classified as non-skin. The classification was 
%         conducted by function SkinSegmentMask in function ROIMeans_TakeMeans. The 
%         skin-segmentation mask is inserted by function WriteFaceVideo_OverlaySkinSegmentation.    
%       - In the legend, whether tailored skin segmentation was not possible due to an
%         insufficient number of skin-color samples.  
%       - Pulse rate annotations
%       - The border of the ROI, as modified by frame-by-frame smoothing and resizing (see 
%         function ROIMSIR). 
%       - An indication of which algorithm was ultimately successful. 
%       - Half-rectangle(s) in the lower right-hand corner indicating the minimum ROI size accepted 
%         from the face-detection algorithm(s).
%       - Two notifications regarding the detection algorithm(s) that determined the ROI may
%       - A legend on the left-hand side of the frame
%   
%   -- Use of Annotations to Correct ROI Placement --
%
%       Note: the text in this section is copied from file Example_Script.mlx. However, unlike
%       Examples_Correct_ROIs_and_Skin_Segmentation.mlx, code examples of arguments used to make 
%       corrections to ROI placement are not included. See 
%       Examples_Correct_ROIs_and_Skin_Segmentation.mlx for these examples. Portions of this text
%       are also present in function FacePulseRate.
% 
%       Eight courses of action can be taken to correct ROI placement. It is expected that only one 
%       course of action will be needed for a given video. The courses of action involve changing 
%       an input argument to function FacePulseRate and rerunning FacePulseRate to actuate the 
%       change. The courses of action are listed in order of ease of use and the likelihood that 
%       they will lead to the desired correction.            
%
%       (1): To have one or more misplaced ROIs removed, enter the frame indices (shown on the 
%            output video) to argument ROIIgnoreByArgument. When the function is rerun, the ROIs 
%            corresponding to these frames will be ignored and replaced by nearby ROIs that are 
%            assumed to be correct.
%
%       (2): To manually specify the values of one or more misplaced ROIs, enter a frame index 
%            (shown on the output video) followed by the desired X, Y, width, and height values to 
%            argument ROISpecifyByArgument. The example in the code block below shows how these 
%            values can be determined. When the function is rerun, the ROIs corresponding to these 
%            frames will be replaced with the specified ROIs. For a short time span with many 
%            misplaced ROIs, it may only be necessary to specify a few ROIs because the normal 
%            smoothing conducted by the function may pull other misplaced ROIs to fit the 
%            trajectory of the manually specified ROIs.
%
%       (3): To adjust the sizes of all ROIs across the video, adjust argument ROIWidthResizeFactor 
%            to modify the width and argument ROIHeightResizeFactor to modify the height. A larger 
%            value increases the size.
%
%       (4): The profile face-detection algorithm tends to be less accurate than the frontal 
%            face-detection algorithm. If the profile algorithm appears to be responsible for many 
%            misplacements, it can be disabled. The algorithm that determined the ROI is listed on 
%            the top of the ROI box. Disable the profile detector by specifying argument 
%            ProfileFaceDetectorTF as false.
%
%       (5): If the half-rectangles in the lower right-hand side are noticably larger than the size 
%            of the face, this could indicate that the minimize size of the ROI is set too low, 
%            resulting in too many ROIs being rejected by the Viola-Jones face detectors. This can 
%            be remedied by decreasing the value of arguments ROIWidthResizeFactor and/or 
%            ROIHeightResizeFactor. 
%
%       (6): An ROI verification algorithm accepts or rejects ROIs returned by detection 
%            algorithms. The first step of verification involves rejected pixels in the ROI that 
%            are outside an accepted range. If the severity of the range is too great (i.e., the 
%            range is too narrow), this could lead ROIs being rejected too frequently.  When an ROI 
%            is rejected, the annotation "R" will appear. If this annotation appears too 
%            frequently, this may indicate the severity is too great. For ROIs returned by the 
%            skin-detection algorithm, the annotation "NR" may also be observed frequently if the 
%            skin segmentation range used for verification is too severe ("NR" means no skin 
%            regions were available). To reduce the severity of the skin segmentation range used 
%            for verification, increase the range specified by arguments 
%            DetectVerifyPercentilesYCbCrH and DetectVerifyPercentilesS. That is, decrease the 
%            minimum of the range and increase the maximum of the range. Note that these values 
%            refer to percentiles (corresponding to skin-color samples collected from the video) 
%            rather than the actual pixel-color values. A description of the values of these 
%            arguments is provided in the code section example below.
%
%       (7): The range for ROI verification (see course of action No. 6) is constrained by the 
%            arguments SkinSegmentThresholdsGenericYCbCr and SkinSegmentThresholdsGenericHSV. The 
%            default values for these arguments consist of rather wide ranges, reducing the 
%            likelihood of causing ROI verification to reject too many ROIs. However, if these 
%            arguments were manually adjusted, this may be the cause of ROI verification rejecting 
%            too many ROIs. As mentioned in course of action No. 6, a high rate of rejection will 
%            result in the display of "R" or "NS" on many frames. If this is the cause of too many 
%            ROIs being rejected, the range can be widened by decreasing the minimums of the ranges 
%            and increasing the maximums of the ranges (for an example argument, see the code block 
%            included in the section on skin segmentation).
%
%       (8): Conversely, the ROI verification algorithm (see also courses of action No. 6 and 7) 
%            may be too lenient, resulting in ROIs not being rejected when they should be. This is 
%            likely due to there being an insufficient number of skin-color samples from the video 
%            for verification mechanisms that require a minimum number of samples (these mechamisms 
%            include tailored skin segmentation and skin-detection used in the service of ROI 
%            verification). These mechanisms will not be activated if the required number of 
%            skin-color samples is not present. The legend will indicate whether tailored skin 
%            segmentation and/or the skin-detection algorithm could not be activated due to a low 
%            number of samples. Skin-color samples are collected only from ROIs returned by the 
%            frontal face-detection algorithm, so a lack of detections by this algorithm is likely 
%            the cause of too few samples. The most straightforward way to increase the number of 
%            samples is to increase the length of the input video. Too few samples could also be 
%            caused by ROIs from the frontal face-detection algorithm being rejected too often (see 
%            courses of action No. 5, 6, and 7).
%
%   -- Use of Annotations to Correct Skin Segmentation --
%
%       Note: the text in this section is copied from file Example_Script.mlx. However, unlike
%       Examples_Correct_ROIs_and_Skin_Segmentation.mlx, code examples of arguments used to make   
%       corrections to skin segmentation are not included. See 
%       Examples_Correct_ROIs_and_Skin_Segmentation.mlx for these examples. Portions of this text
%       are also present in function FacePulseRate.
%
%       The courses of action described in this section can be used to modify the extent of skin 
%       segmentation.
%
%       Skin Segmentation Overview:
%
%       As determining the appropriate level of skin segmentation is not necessarily straitfoward, 
%       the following subsection summaries the author's view on the goals of skin segmentation.
%       
%       Skin segmentation refers to excluding pixels that are classified as non-skin by the 
%       skin-segmentation algorithm. The purpose of skin segmentation is to make the face and skin 
%       measurments more robust to change across frames of areas that do not correspond to skin, 
%       e.g., moving objects, blinking, and mouth movement. Changes in coloration across frames, 
%       rather than the coloration in any given frame, is the concern because the pulse rate is 
%       calculated as a function of change in coloration across frames. Specifically, anything that 
%       changes other than skin will be erroneously considered as change in skin coloration, and, 
%       hence, pulse rate, if not excluded. Areas that have constant coloration across frames, even 
%       if they are non-skin areas, are of least concern because they will not affect the pulse 
%       rate calculation.
%       
%       As mentioned previously, increasing the exclusion of non-skin areas is not necessarily the 
%       goal of skin segmentation. In fact, increasing the severity of skin segmentation across 
%       frames may actually have the side effect of making skin classification less stable across 
%       frames. For example, a high severity of skin segmentation may result in the nose being 
%       classified back and forth as skin and non-skin across frames.  This instability may distort 
%       the pulse rate calculations as changes other than skin coloration are changing across 
%       frames.
%            
%       Skin Segmentation Courses of Action:
%
%       Three courses of action can be taken to correct the extent of skin segmentation. The first 
%       course of action (No. 1) is the most straightforward. The other courses of action are less 
%       likely to be needed but are included in case the first course does not result in 
%       satisfactory skin segmentation. These courses of action involve changing an input argument 
%       to function FacePulseRate and rerunning FacePulseRate to actuate the change. Code examples 
%       are provided in a code section that follows.
%
%       (1): General severity factor.  Increasing this value generally results in more severe skin 
%            segmentation and vice versa. Note that this factor cannot remove segmentation enforced 
%            by the permanent thresholds (see course of action No. 2). However, segmentation is 
%            determined by several factors in addition to the permanent thresholds, so differences 
%            in segmentation should generally be expected when adjusting this factor. Adjust the 
%            factor by argument SkinSegmentSeverityFactor.
%
%       (2): Permanent thresholds. The permanent thresholds are hard limitiations on which pixel 
%            colors are considered skin. Consider changing these if over- or under-segmentation may 
%            be due to environmental conditions. For example, if the face is in a shadow, it may be 
%            necessary to allow pixels that are darker than the default permanent thresholds permit 
%            (i.e., reduce the Y channel minimum treshold to its minimum, which is 16). Note that 
%            FacePulseRate checks whether the ROIs appear to be in a shadow and makes a 
%            corresponding correction; however, this check is somewhat conservative, so manually 
%            changing the permanent thresholds may still be necessary in the case of ROIs with low 
%            illumination. Another case where permanent thresholds may need to be changed is the 
%            case of an unusual tint across frames. That is, sometimes the coloration, white 
%            balance, etc., of a video may not be compatible with the default permanent thresholds; 
%            however, this is expected to be uncommon. Change the range of permanent thesholds by 
%            adjusting arguments SkinSegmentThresholdsGenericYCbCr and 
%            SkinSegmentThresholdsGenericHSV. The left value of these arguments indiates the 
%            minimum of the range, and the right value indicates the maximum of the range. 
%            Widening the range reduces the severity of skin segmentation.
%
%       (3): Oversegmentation adjustments. By default, the presence of oversegmentation is checked. 
%            If oversegmentation is determined to be present, some skin-segmentation settings will 
%            be made less severe. The purpose of the oversegmentation check is to automatically 
%            adjust the severity of skin segmentation without the need to modify the arguments 
%            noted in this section. However, sometimes oversegmentation will be detected when it 
%            doesn't exist. For example, the presense of hair occluding part of the face (e.g., the 
%            presence of long bangs) can sometimes lead the oversegmentation check to determine 
%            that too much of the face was segmented; in this case, the large extent of face 
%            segmentation is appropriate rather than being an indication of oversegmentation, but 
%            the segmentation check is not aware of this subtle difference.  If the 
%            oversegmentation check erroneously detects oversegmentation and subsequently reduces 
%            the severity of skin segmentation, the resulting skin segmentation may not be 
%            satisfactory (note that low segmentation is not necessarily undesirable; see section 
%            "Skin Segmentation Overview" above). If the oversegmentation check reduced the 
%            severity, the legend text will indicate "Oversegmentation Adjustments: true". The 
%            oversegmentation adjustments can be disabled by specifying argument 
%            OversegmentationCheckTF as false.
%
%   -- Detailed Display Option --
% 
%   The detailed display option is only intended for internal development. the detailed display
%   option can be toggled to true within function ValidateAndConfigure_InternalFlags.
%   
%   The detailed option, in addition to displaying what is displayed by the default option, 
%   displays ...
%       - The bounding boxes used in each detection algorithm. Bounding boxes are influenced by  
%         flags ROIFace_BoundingBoxGrowthThreshold, ROIFace_BoundingBoxGrowthFactor,   
%         ROIFace_BoundingBoxEnlargementFactor, ROISkin_BoundingBoxGrowthThreshold,   
%         ROISkin_BoundingBoxGrowthFactor, ROISkin_BoundingBoxEnlargementFactor,
%         ROIFace_ChangeFactorROIPrimary, ROIFace_ChangeFactorROISecondary1, and
%         ROIFace_ChangeFactorROISecondary2.
%       - List of detection algorithms that attempted to make a detection, some or all of which may
%         have been unsuccessful.
%       - ROI from face-detection or skin-detection algorithm without modifications from function
%         ROIMSIR.
%       - ROI with size matching across algorithms and detection smoothing if corresponds to a
%         detection and with interpolation if skipped or no detection. Detection smoothing is set 
%         by arguments ROIFaceSmoothingWindow and ROISkinSmoothingWindow. Note: these modifications  
%         were conducted by function ROIMSIR.
%       - Skin-detection algorithm diagnositics (see function WriteFaceVideo_SkinDetectDiagnosis).
%         Skin-detection settings are influenced by many arguments (see function SkinDetect).
%       - Within the legend, the detections-to-attempts proportion for each detection algorithm. 
%         These proportions indicate the proportion of frames in which a detection was successfully 
%         made out of all frames in which a detection algorithm was attemped. These proportions are        
%         displayed separately for each detection algorithm. If the proportions appear relatively  
%         low compared to expected proportions (expected proportions may be from other videos in a 
%         similar environment), this may be an indication that something interferred with 
%         successfully obtaining detections. Although this could be due to issues that cannot be 
%         remedied, it could also be indication that settings (arguments to function FacePulseRate) 
%         should be adjusted.
%       - The number of times the severity of the morphological close operation was reduced (see
%         function SkinSegment_ConfigSetupOversegmentation). The morphological close operation is a
%         component of skin segmentation (see function SkinSegmentMask).         
%   
%   -- Example of pulse rate annotations --
%
%       Pulse rate annotations are displayed below the ROI. Pulse rate information was calculated
%       by function PulseRate. The annotations are inserted by function WriteFaceVideo_PulseRate.
%       The pulse rate annotations are common to the default and detailed display options.
%
%               'EM: 67; C: 68/63L G: 48/63L I: 63/53L P: 136/46L Window boundary: - 4312'
%     Externally--^      ^--Pulse-rate ^--Pulse rate ^--Pulse rate          Number of --^
%     measured pulse        algorithm.    without       with luminance      frames remaining in     
%     rate, which is                      luminance     control.            the pulse-rate window      
%     specified by                        control.                          of which the ith frame       
%     argument                                                              is a member.
%     "PulseRateExternallyMeasured"                                                                                 
%     to function                                                                                 
%     FacePulseRate.
%
%   -- Example of annotations placed on top of the ROI --      
%
%       Frame and detection information are displayed above the ROI. They are inserted by function
%       WriteFaceVideo_ROIAnnotation. 
%
%       Display under default display option:
%
%          "Frame: 1. Time: 0.1250. ROI: Frontal | [RS] [NR]" 
%    Frame index --^ Timestamp --^    Method --^      ^----^--------------------- Detection attempt  
%                                     that returned ROI. These can include        notifications            
%                                     "Frontal", "Profile", "Skin",                                                             
%                                     "Interpolated", "Specified by                  
%                                     argument", and "Ignored". In 
%                                     contrast to the detailed display
%                                     option, for simplicity, the primary,
%                                     secondary #1, and secondary #2  
%                                     face-detection algorithms are  
%                                     displayed as "Frontal", "Profile",
%                                     and "Frontal 2", respectively.                                     
%                                     When the method is "Ignored", 
%                                     "Ignored" is used rather than 
%                                     "Interpolated" although the ROI
%                                     would have been interpolated.
%                                     "Interpolated" is displayed if the
%                                     frame was skipped for efficiency or 
%                                     if no detection algorithms were
%                                     successful. "Ignored" and "Specified
%                                     by argument" are controlled by                     
%                                     arguments ROIIgnoreByArgument and
%                                     ROISpecifiedByArgument,  
%                                     respectively, which are arguments to 
%                                     function FacePulseRate.                                    
%
%       Display under detailed display option:
%
%          "Frame: 1. Time: 0.1250. ROI: Interpolated | Pri., Sec.#1[RS][RE], Skin[NR]" 
%    Frame index --^ Timestamp --^    Method that --^      ^-------^-- Detection methods that  
%                                     returned ROI.                    attempted detection. These 
%                                     These can include                can include "Pri.",   
%                                     "Pri.", "Sec.#1",                "Sec.#1", "Sec.#2", and  
%                                     "Sec.#2", Skin,                  "Skin". "Skipped" and 
%                                     "Interpolated",                  "Ignored" are also possible 
%                                     and "Specified by                entries, although they are 
%                                     argument".                       not detection methods but 
%                                                                      rather indications that a 
%                                                                      detection method was skipped 
%                                                                      for efficiency or specified
%                                                                      to be ignored (argument
%                                                                      "ROIIgnoreByArgument" to 
%                                                                      function FacePulseRate). If 
%                                                                      a detection method made a   
%                                                                      detection, then the name of  
%                                                                      the method will also appear    
%                                                                      to the right of '|'. If  
%                                                                      there is more than one 
%                                                                      entry, as in this example, 
%                                                                      only one method could have  
%                                                                      been successful. If the  
%                                                                      "Method of ROI" is 
%                                                                      "Interpolated", as in this 
%                                                                      example, then all detection 
%                                                                      methods that attempted 
%                                                                      detection would have been 
%                                                                      unsuccessful.
%
%       Detection-attempt notifications ('[RS]', ['RE'], and '[NR]'):          
%
%           - [RS]: The '[RS]' characters are shown when the ROI returned by an attempted detection    
%             algorithm was rejected due to a low proportion of pixels classified as the skin. This  
%             classification was conducted by function ConfirmSkinPresent. For face-detection
%             algorithms, this classification would have been conducted within function 
%             FaceDetect_ROIValidate. For the skin-detection algorithm, this classification would  
%             have been conducted within function SkinDetect_SelectedRegionROI. Note that function 
%             ConfirmSkinPresent is also called by function ROIMeans_TakeMeans, but classifications
%             within that function do not result in '[RS]' being applied because the purpose of 
%             that function is not to assign ROI detections; a classification within that function  
%             results in an annotation by function WriteFaceVideo_LowProportionSkin. Under the          
%             default display option, these characters will be displayed if any detection algorithm 
%             was rejected, even if another detection algorithm was not rejected. Under the 
%             detailed display option, the characters will be appended to the name of the specific 
%             detection algorithm that was rejected. Occassional misclassifications are expected;  
%             however, if the ROI, by visual inspection, does not appear to have the correct 
%             placement and if there are many apparent misclassifications, the cause could be 
%             skin-segmentation parameters that are too severe.                     
%
%           - [RE]: The '[RE]' characters are shown when the ROI returned by an attempted detection    
%             algorithm is of a profile orientation and a pair of eyes is detected in the frame. 
%             These characters are only shown for face-detection algorithms that target a profile 
%             orientation. This classification was conducted by function FaceDetect_ROIValidate.  
%             These characters are only displayed under the detailed display option. 
%                                                                                                                                                                
%           - [NR]: The '[NR]' characters are shown when no regions were available for the 
%             skin-detection algorithm attempted after the skin-segmentation step (see function 
%             SkinDetect_PartitionRegions). These characters only apply to the skin-detection
%             algorithm (and not the face-detection algorithms). This complete segmentation could  
%             be valid, such as if something in the environment temporarily occluded the face.  
%             However, it could also be an indication that the skin-segmentation parameters are too 
%             severe. Note that the skin-segmentation operation conducted during the skin-detection    
%             algorithm is more severe compared to the skin segmentation conducted during the final    
%             skin segmentation, which is the skin segmentation superimposed on the output video;   
%             hence, the final skin segmentation may appear to show regions available that were not  
%             available during the skin-detection algorithm.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% Extract some configuration settings for performance %%%%%%

FrameIdx                         = VideoReadConfig.FrameIdx;              %type int32
FrameTimestamp_Double            = VideoReadConfig.FrameTimestamp_Double; %type double
VidObj                           = VideoReadConfig.VidObj;                %VideoReader system object
VidObjHeight                     = VideoReadConfig.VidObjHeight;          %type int16
VidObjWidth                      = VideoReadConfig.VidObjWidth;           %type int16

WriteVideoNoSoundTF              = OutputConfig.WriteVideoNoSoundTF;
WriteVideoShowSkinSegmentTF      = OutputConfig.WriteVideoShowSkinSegmentTF;
WriteVideoShowROISkinDiagnosisTF = OutputConfig.WriteVideoShowROISkinDiagnosisTF;
WriteVideoShowLegendTF           = OutputConfig.WriteVideoShowLegendTF;


%%%%%% Convert ROI variables to type uint16  %%%%%%

%Convert from type int16 to type uint16 because signed operations not conducted with these
%variables.

ROI_uint16          = uint16(ROI);
VidObjWidth_uint16  = uint16(VidObjWidth);
VidObjHeight_uint16 = uint16(VidObjHeight);


%%%%%% Display notification message %%%%%%

message = '\nWriting to output video ...\n';

%Display message
fprintf(message);

%Display message immediately
drawnow(); 


%%%%%% Initialize video and/or audio writing %%%%%%

%Note: 'WriteFaceVideo_InitializeWriter' is a custom function located within folder  
%'FacePulseRate'.
%Note: code analyzer indication that cleanupObj1 and cleanupObj2 are not used is suppressed 
%(%#ok<ASGLU>) because the objects are used when the function terminates.
[VideoFileWriter, OutputFile_OnlyVideo, cleanupObj1, cleanupObj2] = ...  
    WriteFaceVideo_InitializeWriter(WriteVideoNoSoundTF, OutputConfig.WriteVideoName, ...
        VideoReadConfig.FS); %#ok<ASGLU>          
    

%%%%%% Specify formatting for annotations %%%%%%

%Set format of annotations in output video for the following:
% - Text box size.
% - Text box font type and font size.
% - Size of bullet points for skin-detection diagnostics text.
% - Size of lines showing minimum size of Viola-Jones detectors (the minimum size is set by 
%   ROIMinWidthRatio and ROIMinHeightRatio, which are arguments to function FacePulseRate).
% - Text accompanying lines showing minimum size of Viola-Jones detectors.

%Note: 'WriteFaceVideo_AnnotationFormatting' is a custom function located within folder  
%'FacePulseRate'.
[TextboxFontType, TextboxFontSize, TextBoxMaxRowSize, TextBoxMaxColSize_Annotation, ...
 TextBoxMaxColSize_PulseRate, ROI_Text, PulseRate_Text, bulletpointRadius, ...
 ViolaJonesMinDim] = ...
    WriteFaceVideo_AnnotationSetup(VideoReadConfig, VidObjWidth_uint16, VidObjHeight_uint16, ...
        PulseRateConfigAndData, ROIGeneralConfig, FaceDetectConfig);

%Initialize flags indicating which version of the legend should be assigned     
LegendVersion1NotAssignedTF = true;
LegendVersion2NotAssignedTF = true;
    
%Initialize values for legend 
%These variables are only used in a nested function; for them to be persistent in the main 
%function, they must be initialized in the main function, so they are initialized here.
legendText_PixelRGB    = [];
legendText_PixelLinIdx = [];
legendBoxRowsIdx       = [];
legendBoxColsIdx       = [];
LegendSupportedTF      = [];


%%%%%% Setup progress notifications %%%%%%
  
%Note: progress notifications are displayed to command window by function LoopProgressNotification.

%Interval to elapse between each notification message
%Type int32 for protection against floating-point gaps.
Notifications_Interval = int32(1000);

%Frames in loop
%Note: already type int32.
Notifications_FrameIdx = VideoReadConfig.FrameIdxFromStart; 

%Initialize loop counter for progress notifications 
%Type int32 for protection against floating-point gaps.
Notifications_LoopCounter = int32(0);

%Record start time for progress notifications 
Notifications_LoopStartTime = tic;


%%%%%% Read video through last timestamp %%%%%%

%The video reader to use is specified by VideoReadConfig.UseVisionTF, which is specified by 
%function VideoReadConfig_Setup.

%%%%%% --- Use system object vision.VideoFileReader for video reading %%%%%%

if VideoReadConfig.UseVisionTF

    %Extract vision.VideoFileReader system object
    videoFReader = VideoReadConfig.videoFReader; 
    
    %Setup cleanup object to release and destruct videoFReader if function WriteFaceVideo is 
    %interrupted (e.g., by an error being thrown or, more likely, by use of ctrl+c). If 
    %videoFReader is not released, when function WriteFaceVideo resumes, the video will be read 
    %starting from where it left off, but all of the operations in the function will begin at the
    %beginning.
    cleanupObj3 = onCleanup( @()release(videoFReader) );
    
    %Initialize flag indicating whether seeking to StartTime has completed
    SeekCompletedTF = false;
   
    %Initialize frame index that counts frames from the beginning of the video
    %Only used for seeking to StartTime.
    %Type int32 for protection against floating-point gaps.
    FromBeginningIdx = int32(0);
   
    %Initialize frame index that counts frames from StartTime, which may be later than the
    %beginning of the video.
    %Used for all operations except seeking to StartTime.
    %Type int32 for protection against floating-point gaps.
    i = int32(0);
    
    %Maximum frame index
    FrameIdxMax = int32( length(FrameTimestamp_Double) );    
    
    %Initialize end-of-file flag
    EndOfFileTF = false;
        
    %Loop through frames up to index of last timestamp recorded in function ROIMeans_FirstRead
    while i < FrameIdxMax && ...
          ~ EndOfFileTF %verify that frame exists for next frame 
                     
        %Read ith frame
        [VidFrame,      ... M x N x 3 array; type uint8
         EndOfFileTF] = ... logical flag indicating whether the last frame in file has been read
            videoFReader();
        
        %%%%%% >>>>>> Seek to frame corresponding to StartTime %%%%%%
        
        %System object vision.VideoFileReader can only start reading at the beginning of the video,
        %which may be different from StartTime, so seek up to the frame corresponding to StartTime.
        
        %Seek if StartTime has not been reached
        if ~ SeekCompletedTF
        
            %Advance frame counter that counts frames from beginning of video
            %Only used for seeking to StartTime.
            %Type int32.
            FromBeginningIdx = FromBeginningIdx + 1;

            %Go to next frame until the frame index counted from beginning of video 
            %(FromBeginningIdx) equals the frame index corresponding to StartTime (FrameIdx(1)).
            if FromBeginningIdx ~= FrameIdx(1) 

                %Go to next frame
                continue 
                
            else
                
                %Indicate seeking completed
                SeekCompletedTF = true;
            end
        end
        
        %%%%%% >>>>>> Frame corresponding to StartTime reached: Begin operations %%%%%%        
        
        %Advance index       
        i = i + 1;
        
        %Perform operations for ith frame
        %Nested function.
        WriteFaceVideo_Ops();        
        
    end %end frame loop 
    
    %Reset vision.VideoFileReader
    release(videoFReader);

%%%%%% --- Use system object VideoReader for video reading %%%%%%
else    
    
    %Note: Function readFrame can be considerably faster than function read().

    %Set the CurrentTime property of system object VideoRead a value just before (earlier) than the
    %timestamp corresponding to the frame to be read. This is because readFrame reads the frame  
    %corresponding to the next, not the current, timestamp. Note that the timestamp used to set 
    %CurrentTime does not need to correspond to an actual timestamp; it can be any non-negative 
    %value. Set back by a magnitude of at least 10e-5; otherwise, the precision will be below that   
    %which VideoReader can recognize. 
    %Note: VidObj.CurrentTime requires type double.
    VidObj.CurrentTime = max(VideoReadConfig.StartTime - 10e-5, 0);

    %Maximum frame index
    FrameIdxMax = int32( length(FrameTimestamp_Double) );
    
    %Initialize index
    %Type int32 for protection against floating-point gaps.
    i = int32(0);

    %Loop through frames up to EndTime
    while i < FrameIdxMax && ...
          hasFrame(VidObj) %verify that frame exists for next frame

        %Read the frame corresponding to the frame after the current time
        %M x N x 3 array; type uint8.
        VidFrame = readFrame(VidObj);

        %Advance index       
        i = i + 1;       
        
        %Perform operations for ith frame 
        %Nested function.
        WriteFaceVideo_Ops(); 

    end %end frame loop    
end
  

%%%%%% Finish video writing %%%%%%
   
release(VideoFileWriter);   

  
%%%%%% Add audio to output file %%%%%%

%Audio in output file is enabled
if ~ WriteVideoNoSoundTF
    
    %Note: 'WriteFaceVideo_CombineOutputVideoAndAudio' is a custom function located within folder 
    %'FacePulseRate'.    
    WriteFaceVideo_CombineOutputVideoAndAudio(OutputConfig, OutputFile_OnlyVideo, VideoReadConfig);                  
end


%%%%%% Display completion message %%%%%%

%Display path and .avi file to which video file was written
message = ['\nOutput video written to file:', ...
             '\n    ']; %new line, indent           

fprintf(message);

%Specify type string to write a directory without escape characters
fprintf( '%s\n', string(OutputConfig.WriteVideoName) );     

%Display message immediately
drawnow();     


%=============================================================================================
%Nested functions 
%=============================================================================================


%=============================================================================================
function WriteFaceVideo_Ops()
%WriteFaceVideo_Ops    Conduct file writing operations. Nested function.    
               
 
%%%%%% Specify text for legend in output video %%%%%% 

%If legend enabled
if OutputConfig.WriteVideoShowLegendTF
    
    %Use two versions of legends, one for skin-detection color thresholds corresponding to a large 
    %number of skin-color samples and one for skin-detection color thresholds corresponding to a  
    %small number of skin-color samples. These two versions differ only on the display of the
    %skin-detection color thresholds. Version 2 is used once the frame index equals
    %SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdIdx. However, Version 2 will not be 
    %used if SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdPassedTF == false.
        
    %The text for the legend only needs to be assigned twice, one for each version of the legend.
    %Hence, after the text is assigned for a version, do not assign the text of that version again.
    
    if LegendVersion1NotAssignedTF ||  ... version 1 not assigned
       (LegendVersion2NotAssignedTF && ... version 2 not assigned
        SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdPassedTF && ... version 2 ready
        i >= SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdIdx)  
                  
        %Specify text for legend in output video
        %Text is stored as individual pixels and a corresponding index based upon one frame.
        %These pixels and index are then referenced to assign the legend for all frames within the 
        %output video. This method is more computationally efficient compared to redrawing text for
        %each frame. This method is only possible because the legend is static across the frames. This
        %method was implemented because redrawing text for each frame was observed to add about 20 min 
        %of processing time per 1 min of video input.
        %Note: 'WriteFaceVideo_LegendSetup' is a custom function located within folder 'FacePulseRate'. 
        [legendText_PixelRGB, legendText_PixelLinIdx, legendBoxRowsIdx, legendBoxColsIdx, ...
         LegendSupportedTF] = ...
             WriteFaceVideo_LegendSetup(LegendVersion1NotAssignedTF, VidObjWidth_uint16, ...
                 VidObjHeight_uint16, ROIDiagnostic.ROISkin.RegionNThreshold, HasROI_TF,  ...
                 SkinSegmentConfig, PulseRateConfigAndData, FaceDetectConfig, SkinDetectConfig, ...
                 OutputConfig);
         
        if LegendVersion1NotAssignedTF
            
            %Flag that version 1 was assigned
            LegendVersion1NotAssignedTF = false; 
            
        else     
       
            %Flag that version 2 was assigned
            LegendVersion2NotAssignedTF = false;       
        end                 
    end
end


%%%%%% Show minimum height and width required for Viola-Jones detectors %%%%%%
 
%Note: Viola-Jones detectors are a component of the face-detection algorithms. See function
%FaceDetect_ConfigSetup for details.

%Draw lines indicating the minimum height and width of the detection ROI for each enabled face-
%detection algorithm.
for j = 1 : ViolaJonesMinDim.NAlgs

    %Obtain line dimensions
    switch j
    
        %Primary face-detection algorithm
        case 1
        
            VertLine_Rows = ViolaJonesMinDim.Pri_VertLine_Rows;
            VertLine_Cols = ViolaJonesMinDim.Pri_VertLine_Cols;
            HorzLine_Rows = ViolaJonesMinDim.Pri_HorzLine_Rows;
            HorzLine_Cols = ViolaJonesMinDim.Pri_HorzLine_Cols;
 
        %Secondary #1 face-detection algorithm            
        case 2
 
            VertLine_Rows = ViolaJonesMinDim.Sec1_VertLine_Rows;
            VertLine_Cols = ViolaJonesMinDim.Sec1_VertLine_Cols;
            HorzLine_Rows = ViolaJonesMinDim.Sec1_HorzLine_Rows;
            HorzLine_Cols = ViolaJonesMinDim.Sec1_HorzLine_Cols;
 
        %Secondary #2 face-detection algorithm             
        case 3
            VertLine_Rows = ViolaJonesMinDim.Sec2_VertLine_Rows;
            VertLine_Cols = ViolaJonesMinDim.Sec2_VertLine_Cols;
            HorzLine_Rows = ViolaJonesMinDim.Sec2_HorzLine_Rows;
            HorzLine_Cols = ViolaJonesMinDim.Sec2_HorzLine_Cols;        
    end
   
    %Draw lines
    %Loop across color channels.
    for k = 1 : 3

        %Vertical line indicating height
        VidFrame( ...
            VertLine_Rows, ... 
            VertLine_Cols, ... 
            k ...
        ) =  ViolaJonesMinDim.Color(k);

        %Horizontal line indicating width     
        VidFrame( ...
            HorzLine_Rows, ... 
            HorzLine_Cols, ...
            k ...
        ) = ViolaJonesMinDim.Color(k);
    end
end


%%%%%% Crop ROI %%%%%%

%1 x 4 row vector; type uint16.
ROI_ith = ROI_uint16(i, :);

%Type uint8.
VidFrameROI = ... cropped frame
    VidFrame( ...
        ROI_ith(2) : ROI_ith(2) + (ROI_ith(4) - 1), ... rows
        ROI_ith(1) : ROI_ith(1) + (ROI_ith(3) - 1), ... columns
        :                                           ... pages
    ); 


%%%%%% Overlay color for pixels classified as non-skin from skin segmentation %%%%%%

%Overlay color indicating pixels classified as non-skin.
%The inverted skin-segmentation mask was assigned by function SkinSegmentMask. SkinSegmentMask is 
%used many times throughout function FacePulseRate, resulting in different skin-segmentation masks 
%for a given frame. The skin-segmentation mask displayed here is the final skin-segmentation mask 
%assigned, where SkinSegmentMask was called by function ROIMeans_TakeMeans. The mask has been 
%inverted so that true values equal non-skin.

%Display only if displaying skin segmentation on output video is enabled.
if WriteVideoShowSkinSegmentTF                                             

    %Note: 'WriteFaceVideo_OverlaySkinSegmentation' is a custom function located within folder 
    %'FacePulseRate'.
    %Type uint8.
    VidFrameROI = ...
        WriteFaceVideo_OverlaySkinSegmentation(i, VidFrameROI, SkinSegmentMasks, ...
            ROI_uint16(i, 4), ROI_uint16(i, 3), UseCompiledFunctionsTF);

end %end if WriteVideoShowSkinSegmentTF == true


%%%%%% Insert ROI with skin segmentation into full frame %%%%%%

%If ShowSkinSegTF enabled
if WriteVideoShowSkinSegmentTF 

    %Height and width of ROI
    %Specify type uint16 for faster evaluation where used.
    [VidFrameROIHeight, VidFrameROIWidth] = size(VidFrameROI, [1, 2]);
    VidFrameROIHeight = uint16(VidFrameROIHeight);
    VidFrameROIWidth = uint16(VidFrameROIWidth);

    %Superimpose skin-segmented ROI image onto VidFrame (original) image
    %Adjust the [X, Y] coordinates to undo change to [X, Y] as a result of cropping; this
    %adjustment will place [X, Y] in coordinate plane of original (uncropped) image so that [X, Y] 
    %can be used in the original image used in the output video. To do so, add back distances of X
    %and Y that were changed by previous cropping.

    %1 x 4 row vector; type uint16.
    ROI_ith = ROI_uint16(i, :); 

    %Type uint8.
    VidFrame( ...
        (1 : VidFrameROIHeight) + (ROI_ith(2) - 1), ... rows
        (1 : VidFrameROIWidth)  + (ROI_ith(1) - 1), ... columns
        :                                           ... pages
    ) = VidFrameROI; %ROI of frame                                                
end      


%%%%%% Insert legend %%%%%%      

%A legend is currently only supported for particular frame sizes 
%Flag LegendSupportedTF is set by function WriteFaceVideo_LegendSetup, which is called by function
%WriteFaceVideo_AnnotationSetup.
if WriteVideoShowLegendTF && LegendSupportedTF

    %Insert partially-opaque legend box at top-left of frame
    %The X- and Y-coordinates, which denote the upper-left-hand corner, are set at (1, 1), which 
    %places box at top-left of frame.
    %Legend indices (legendBoxRowsIdx and legendBoxColsIdx) are set in function 
    %WriteFaceVideo_LegendSetup.
    %Make opaque by dividing pixel values by 2.
    %Optimize the division by bit-wise operations. 
    %Type uint8.
    VidFrame( ...
        legendBoxRowsIdx, ... rows
        legendBoxColsIdx, ... columns
        :                 ... pages
    ) = ...                                           
        bitshift( ...
            VidFrame( ...
                legendBoxRowsIdx, ...
                legendBoxColsIdx, ...
                :                 ...
            ), ... 
            -1 ...
        );       

    %Insert text onto legend
    %As the text used for the legend is constant across frames, for efficiency, the evaluation   
    %to create the text is only performed once. The evaluation is performed by function  
    %WriteFaceVideo_LegendSetup, which stores the color values and index of each pixel
    %corresponding to text (only the pixels corresponding to text, not the background, is stored). 
    %This is more computationally efficient compared to redrawing text for each frame. This is 
    %possible because text to display is consistent across frames. Without indexed text, redrawing
    %text for each frame was observed to add about 20 min of processing time per 1 min of video
    %input. Indexed text is assigned in function WriteFaceVideo_LegendSetup within function 
    %WriteFaceVideo_AnnotationSetup.
    VidFrame(legendText_PixelLinIdx) = legendText_PixelRGB;            

end %end insert legend


%%%%%% Insert skin detection diagnosis annotations %%%%%%

%If the skin-detection algorithm (function SkinDetect) was conducted and if displaying 
%skin-detection algorithm diagnostic annotations is enabled.
if ROIDiagnostic.ROISkin.ConductedTF 
    
    %If displaying skin-detection algorithm diagnostic annotations on the output video is enabled
    %Note: WriteVideoShowROISkinDiagnosisTF will be false if 
    %OutputConfig.WriteVideo_DetailedDiagnosticsTF false.    
    if WriteVideoShowROISkinDiagnosisTF

        %Insert skin-detection algorithm diagnostic annotations
        %M x N x 3 array; type uint8.
        %Note: 'WriteFaceVideo_SkinDetectDiagnosis' is a custom function located within folder 
        %'FacePulseRate'.  
        VidFrame = ...
            WriteFaceVideo_SkinDetectDiagnosis(i, VidFrame, ROIDiagnostic, HasROI_TF, ...
                VidObjWidth_uint16, VidObjHeight_uint16, bulletpointRadius, ...
                UseCompiledFunctionsTF);
    end
end 


%%%%%% Insert ROI and bounding box borders %%%%%%

%If detailed diagnostics enabled
if OutputConfig.WriteVideoDetailedDiagnosticsTF

    %Insert all possible borders
    %This index will result in the insertion of borders of bounding boxes used when scanning for    
    %the ROI and the borders of the different stages of ROIs. 
    NBorders = 5;
    
%If detailed diagnostics not enabled      
else
   
    %Insert only the borders of the final ROI   
    NBorders = 1;   
end

%Loop across possible ROI borders and bounding box borders 
for BorderIdx = 1 : NBorders
    
    %Determine borders
    %Note: 'WriteFaceVideo_ROIAndBoundingBoxBorders' is a custom function located within folder 
    %'FacePulseRate'.
    [BorderRGB_uint8, RowsTB, ColsTB, RowsLR, ColsLR, SkipToNextCaseTF] = ...
        WriteFaceVideo_ROIAndBoundingBoxBorders(i, BorderIdx, ROI_uint16, ROIDiagnostic); 

    %ROI or bounding box not present for jth frame
    if SkipToNextCaseTF
        
        continue
    end
    
    %Insert border into frame 
    %Type uint8.
    VidFrame(RowsTB, ColsTB, 1) = BorderRGB_uint8(1); %assign to top and bottom border subscripts
    VidFrame(RowsTB, ColsTB, 2) = BorderRGB_uint8(2); 
    VidFrame(RowsTB, ColsTB, 3) = BorderRGB_uint8(3); 
    VidFrame(RowsLR, ColsLR, 1) = BorderRGB_uint8(1); %assign to left and right border subscripts
    VidFrame(RowsLR, ColsLR, 2) = BorderRGB_uint8(2); 
    VidFrame(RowsLR, ColsLR, 3) = BorderRGB_uint8(3);       
end    


%%%%%% Insert annotations with description of ROI %%%%%%

%The annotation includes ...

% - How the ROI was assigned, e.g., the primary face-detection algorithm, interpolation.
% - Which detection algorithm(s) were used on the frame (if any), e.g., the primary face-detection 
%   algorithm.
% - The timestamp.
% - The frame index. Note: the frame index reported here starts where timestamp = 0; for 
%   differences between this index and the frame index that starts where timestamp = StartTime, see
%   function VideoReadConfig_Setup).

%To increase efficiency, this function returns only the portion of the video frame occupied by the 
%text box. Otherwise, the full frame would be reassigned.

%Note: 'WriteFaceVideo_ROIAnnotation' is a custom function located within folder 'FacePulseRate'. 
[VidFrame_AnnotationTextBox,  ... portion of frame occupied by text box
 TextBoxLowerLeftXY] =        ... upper-left [X, Y] coordinates of text box for indexing
    WriteFaceVideo_ROIAnnotation(VidFrame, i, ROI_Text, ROI_uint16, HasROI_TF, ... 
        VidObjWidth_uint16, TextboxFontSize, TextBoxMaxRowSize, TextBoxMaxColSize_Annotation, ...
        TextboxFontType, ROIDiagnostic, FaceDetectConfig, OutputConfig, UseCompiledFunctionsTF);           

%Assign text box to portion of frame occupied by text box
%Type uint8.
%Note: when indexing, subtract 1 to be inclusive.
VidFrame( ... index into area corresponding to text box
    TextBoxLowerLeftXY(2) - (TextBoxMaxRowSize - 1) : TextBoxLowerLeftXY(2),          ... rows 
    TextBoxLowerLeftXY(1) : TextBoxLowerLeftXY(1) + TextBoxMaxColSize_Annotation - 1, ... cols 
    :                                                                                 ... pages
) = VidFrame_AnnotationTextBox;


%%%%%% Add annotation if ROI adjusted because proportion of skin too low %%%%%%    

%If ROI adjusted
%Note: HasROI_TF.AdjustedBecauseLowSkinProportion assigned in function ROIMeans_TakeMeans.
if HasROI_TF.AdjustedBecauseLowSkinProportion(i)   

    %M x N x 3 array; type uint8.
    %Note: 'WriteFaceVideo_LowProportionSkin' is a custom function located within folder  
    %'FacePulseRate'.
    VidFrame = ...
        WriteFaceVideo_LowProportionSkin(VidFrame, i, ROI_uint16, VidObjWidth_uint16, ...
            VidObjHeight_uint16);
end               


%%%%%% Display pulse rate and window information %%%%%%

%If calculating pulse rate enabled
if PulseRateConfigAndData.TF

    %The annotations include ...
    
    % - The externally-measured pulse rate value corresponding to the ith frame. This value would  
    %   have been specified as argument PulseRateExternallyMeasured to function FacePulseRate. 
    % - Four pulse rate values from the four pulse rate algorithms, respectively.
    % - Four pulse rate values from the four pulse rate algorithms, respectively, that have been 
    %   controlled for luminance variation across frames.
    % - The number of frames remaining in the pulse-rate window to which the ith frame is a member. 
    
    %To increase efficiency, this function returns only the portion of the video frame occupied by 
    %the text box. Otherwise, the full frame would be reassigned.

    %Note: 'WriteFaceVideo_PulseRate' is a custom function located within folder 'FacePulseRate'.  
    [VidFrame_PulseRateTextBox,    ... portion of frame occupied by text box
     TextBoxUpperLeftXY] =         ... upper-left [X, Y] coordinates of text box for indexing
         WriteFaceVideo_PulseRate(i, PulseRate_Text, VidFrame, TextboxFontSize, ...
             TextBoxMaxRowSize, TextBoxMaxColSize_PulseRate, TextboxFontType, ROI_uint16, ...
             VidObjWidth_uint16, VidObjHeight_uint16, PulseRateConfigAndData, ...             
             UseCompiledFunctionsTF);   

    %Assign text box to portion of frame occupied by text box
    %Type uint8.
    %Note: when indexing, subtract 1 to be inclusive.
    VidFrame( ... index into area corresponding to text box
        TextBoxUpperLeftXY(2) : TextBoxUpperLeftXY(2) + TextBoxMaxRowSize - 1,           ... rows   
        TextBoxUpperLeftXY(1) : TextBoxUpperLeftXY(1) + TextBoxMaxColSize_PulseRate - 1, ... cols 
        :                                                                                ... pages
    ) = VidFrame_PulseRateTextBox;
    
end %end display pulse rate                   


%%%%%% Write ith frame to output video file %%%%%%

%Note: VideoFileWriter is a system object, which was assigned in function 
%WriteFaceVideo_InitializeWriter.

VideoFileWriter(VidFrame);


%%%%%% Loop progress notifications %%%%%%

%Note: include the following statement before loop: LoopStartTime = tic.   

%Note: 'LoopProgressNotification' is a custom function located within folder 'FacePulseRate'.
Notifications_LoopCounter = ...
    LoopProgressNotification(Notifications_Interval, Notifications_FrameIdx, i, ...
        Notifications_LoopStartTime, Notifications_LoopCounter); 
 
end %end nested function


end %end main function

