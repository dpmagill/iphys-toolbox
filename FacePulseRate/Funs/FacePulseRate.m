function [TableByFrame, TableByWindow] = FacePulseRate(Video_InputFile, NVArgs) 
%FacePulseRate    Top-level function to the FacePulseRate toolbox.
%                 Calculate windows of pulse rate from a face identified within the input video.
%                 Return data tables, write the tables to csv files, and write a video with pulse 
%                 rate and diagnostic annotations. 
%
%   Summary
%   -------
%
%       Calculate frame-by-frame blood volume pulse (BVP) and windows of pulse rate from a face 
%       present within an input video. 
%
%       FacePulseRate is designed to supply output from the four (as of November, 2019) pulse-rate 
%       algorithms provided by iPhys Toolbox (McDuff & Blackford, 2019). Additionally, 
%       FacePulseRate ...
%
%       - Breaks down pulse rate into windows, permitting pulse rate to vary across time.
%       - Automatically positions a face ROI for each frame.
%       - Provides enhanced skin segmentation.
%       - Provides separate versions of each of the four algorithms while controlled for variation   
%         in luminance across frames (see Madan et al., 2018). This is in addition to providing the
%         four versions without controlling for luminance.
%       - Provides verification of ROI placement and skin-segmentation by providing an annotated
%         output video. Arguments are available to make adjustments to ROI placement and 
%         skin-segmentation based upon inspection of the output video. For a description of how the
%         annotations on the output video can inform modifications to the arguments, see the
%         description in function WriteFaceVideo.
%       
%       The BVP and pulse rate results are provided, along with addition information, as output 
%       tables. Included among the additional information are the input video timestamps and means   
%       from the red, green, and blue color channels of an ROI from each frame; these two 
%       components of the data are the basis for the BVP. These tables are also written to CSV 
%       files.
%
%       Note: When planning a study, pretests should be conducted where video as well as 
%       traditional measures of pulse rate (e.g., PPG, ECG) are recorded. The traditional measures
%       of pulse rate should be used to validate the use of video-derived pulse rate for expected
%       behavioral tendencies. This is because the accuracy of video-derived pulse rate is highly 
%       dependent on the degree of facial movement, where greater movement tends to result in 
%       video-derived pulse rate that is less accurate. The four pulse-rate algorithms may vary in 
%       accuracy depending on the degree of movement. The pulse-rate algorithm with greatest 
%       accuracy in a given context should be used.
%
%
%   Key Features
%   ------------
%
%       - Provides a relatively robust automated ROI-detection system with which to conduct the
%         four RGB-to-BVP algorithms (as of January, 2020) provided in iPhys Toolbox (McDuff &  
%         Blackford, 2019). iPhys Toolbox indicates where in the implementation ROI detection tools
%         should be used but does not provide explicit tools. The current function integrates the
%         RGB-to-BVP algorithms with an ROI-detection system.
%
%       - Provides a relatively robust automated ROI-detection system to focus on the face rather  
%         than the environment. The current function attemps to avoid any gaps in ROIs directed at 
%         the face. To do so, it combines ROIs returned by a Viola-Jones frontal-face detector, a 
%         Viola-Jones profile-face detector, and a novel skin-detection algorithm. An algorithm is
%         then used to stitch together ROIs returned by these methods. The algorithm smooths the
%         ROIs to maintain a smooth trajectory and consistent size. Frames for which a detection
%         was not made are interpolated from nearby ROIs. For some frames, the detection algorithms
%         are skipped for more efficient processing. Finally, an output video is written to assist
%         with verifying ROI placement across frames. Arguments are provided to make refinements to
%         ROI placement, including manual replacement of ROIs. 
%
%       - Provides a skin segmentation method that removes non-facial areas of the ROI. The method
%         uses information from the YCbCr and HSV colorspaces and the local color range. 
%         Morphological adjustments are then made to fill in gaps that may correspond to non-skin.
%         Additionally, a novel method is included that self-tailors the color thresholds by 
%         drawing from skin-color samples from the input video itself. During segmentation, checks
%         are made to determine whether over-segmentation has occurred, and, if so, adjustments are
%         made to recalibrate segmentation settings. Finally, the output video displays the
%         segmentation for each frame for verification. Arguments are provided to make 
%         refinements to skin segmentation.
%
%       - The method used by iPhys Toolbox -- as well as some sources in the literatue -- for 
%         deriving pulse rate from BVP collected via video results in only one pulse rate value for 
%         the duration of the video. The limitation of a single pulse rate value is that changes in 
%         pulse rate across this span are not calculated. Although methods exist to derive a 
%         continuous measure of pulse rate from BVP as calculated from a sensor attached directly 
%         to the body, these methods do not appear to be appropriate for BVP captured from a video 
%         because of the additional noise present in the video. To provide a somewhat continuous 
%         measure of pulse rate while retaining the method used in iPhys Toolbox, the current 
%         function breaks the video into windows (the duration of which can be specified by 
%         PulseRateWindowDurationSec) and applies the method used in iPhys Toolbox to each. The 
%         appropriate value of the duration, as well as conditions that might necessitate changing 
%         the value, still require further research, although a default value is provided.
%
%
%   Description
%   -----------
%
%   -- How-To Guides --
%
%   The text in this function is rather detailed. It may be more useful to review the How-To 
%   guides.
%
%   For an overview of FacePulseRate, see README.pdf.
%
%   For recommendations on the input video and the physical enviroment in which it is recorded, see
%   Video and Recording Environment Recommendations.pdf.
%
%   For setting up FacePulseRate (downloading the tools), see README.pdf.
%
%   For general instructions, see Examples_General_Instructions.mlx.
%
%   For making corrections to ROI placement or skin segmentation, see 
%   Examples_Correct_ROIs_and_Skin_Segmentation.mlx.
%
%   -- Overview -- 
%
%       The face in the video is tracked across frames and an ROI is used to separate the face from
%       the environment. Skin segmentation is applied to further separate facial skin from the
%       environment. Means from the RGB colorspace are taken from the ROI of each frame as the 
%       basis for pulse-rate calculations. 
% 
%       From these means, four versions of BVP are calculated using the four RGB-to-BVP algorithms 
%       provided in iPhys Toolbox (McDuff & Blackford, 2019). Additionally, separate versions of 
%       each of the four while controlled for variation in luminance across frames are provided (if 
%       enabled) (see Madan et al., 2018). Windows of pulse rate are then derived from each using 
%       the method from iPhys Toolbox. 
%        
%       The method in iPhys Toolbox for deriving pulse rate derives BVP from a span of time, the 
%       limitation of which is that changes in pulse rate across this span are not calculated. 
%       Although methods exist to derive a continuous measure of pulse rate from BVP as calculated 
%       from a sensor attached directly to the body, these methods do not appear to be appropriate 
%       for BVP captured from a video because of the additional noise present in the video. To 
%       provide a somewhat continuous measure of pulse rate while retaining the method used in 
%       iPhys Toolbox, the current function breaks the video into windows (the duration of which  
%       can be specified by PulseRateWindowDurationSec) and applies the method used in iPhys 
%       Toolbox to each.
%       
%       The BVP and pulse rate results are written to a csv output file along with other data. 
%       Included among these data are the input video timestamps and means from the red, green, and    
%       blue color channels of an ROI from each frame; these two components of the data are the
%       basis for the BVP. Additionally, an output video is provided for inspecting and refining 
%       the ROI placement.              
%       
%       Optionally, externally-measured pulse rate (e.g, via photoplethysmography [PPG] or 
%       electocardiography [ECG]) can be entered as an input argument to be displayed alongside the 
%       pulse rate calculated by this function. Comparison of externally-measured pulse rate to 
%       that calculated by the function can be used to determine environmental and behavioral 
%       conditions under which the best accuracy is obtained.
%
%       An output video is written to enable inspection of the ROIs from which face measurements 
%       are taken. The output video also superimposes the calculated pulse rate from several 
%       pulse-rate algorithms to enabled visualization of changes in pulse rate across time. The 
%       primary purpose of the output video is to determine whether the ROI placement needs to be
%       change for some frames and whether the severity of skin segmentations needs to be changed.
%       Arguments, discussed below, are provided for adjusting ROI placement and the severity of 
%       skin segmentation. For a full description on how the annotations on the output video can 
%       inform modifications to the arguments, see the description in function WriteFaceVideo.
%
%
%   System Requirements
%   -------------------
%
%       - 64-bit Windows 
%
%       Currently, 64-bit macOS has not been implemented and tested.
%
%       Note on macOS: 
%
%       macOS can be supported if macOS versions of ffmpeg and ffprobe (see folder 
%       FacePulseRate/Funs/General/ffmpeg/mac) are included. Currently, they are not. These 
%       versions should be compiled under flags that permit compatibility with the LGPL license
%       rather than the GPL license. Otherwise, FacePulseRate must be released under the GPL
%       license. Once these files are included, the validation check in function  
%       ValidateAndConfigure_Validate should be modified to include macOS architecture.
%
%       Currently, compiled versions of functions are only provided for 64-bit Windows. 
%       FacePulseRate is designed to work without compiled versions of functions, but it will be
%       slower.
%
%
%   Required Software
%   -----------------
%
%       - Matlab. FacePulseRate has been tested on Matlab versions 2020a and 2020b.
%
%       The following Matlab toolboxes are also required. Note that these toolboxes are licensed by 
%       Matlab and are not free software. These are the toolbox names as of Matlab release 2020b; 
%       toolboxes are occassionally renamed. 
%
%       - Statistics and Machine Learning Toolbox: Various functions.
%       - Computer Vision System Toolbox:          Face-detection operations and video reading.
%       - Image Processing Toolbox:                Skin-segmentation and skin-detection operations.
%       - Signal Processing Toolbox:               Butterworth filtering and periodogram for pulse 
%                                                  rate operations.
%       - DSP System Toolbox:                      Filtering operaions for pulse rate operations. 
%       - Optimization Toolbox:                    Training RGB probability for skin-detection 
%                                                  operations.
%
%
%   Example Script
%   --------------
%
%       See example script Example_Script.mlx, which is located within folder FacePulseRate.   
%
%
%   Example Use
%   -----------
%
%       Full path, file name, and extension for input video file
%       Path cannot contain characters ',' or ';'. 
%       Character vector or string array.
%       Video_InputFile = "C:\Users\User1\Downloads\Data\001.mp4";
%
%       [TableByFrame, TableByWindow] = FacePulseRate(Video_InputFile);
%           
%
%   Inputs
%   ------
%
%       Required:
%
%           Video_InputFile                 = Video file path. This is the only required argument.                                           
%                                             Path cannot contain characters ',' or ';'.
%                                             Character vector or string scalar.
%                                             For a description of supported video types, see 
%                                             section 
%                                             "Input Video Requirements and Recommendations" below.
%
%                                             E.g.,
%                                             Video_InputFile = ...
%                                                 'C:\Users\User1\Downloads\MyVideo.mp4';
%
%       Optional Name-Value Pairs:
%
%           -- Seek Settings --
%
%               StartTime                   = Optional timepoint, in seconds, at which to start 
%                                             processing. The default is the beginning of the 
%                                             video.
%                                             Note: Faster read performance will occur when   
%                                             StartTime is less than 5% the length of the full  
%                                             video based on video-reading implementations (see  
%                                             function VideoReadConfig_Setup).
%                                             Numeric scalar.
%
%               EndTime                     = Optional timepoint, in seconds, at which to end 
%                                             processing. The default is the end of the video.
%                                             Numeric scalar.
%
%           -- ROI Settings -- 
%    
%               A feature of the ROIs that can be assessed by inspection of the output video is the  
%               placement of the ROI on the face or an area of skin. If the ROI does not include   
%               the face or skin, arguments to the function can be entered to adjust the position 
%               of the ROI. 
%  
%               One option is to ignore an erroneous ROI by using argument ROIIgnoreByArgument to    
%               specify the frame index of the erroneous ROI. In this case, the position of the   
%               erroneous ROI will be removed and replaced by a position interpolated from nearby  
%               ROIs. An example of doing so with argument ROIIgnoreByArgument is provided in the 
%               Inputs section.       
%
%               If more than ignoring an erroneous ROI is required, values for a replacement ROI   
%               can be entered directly for a given frame index. 
%
%               ROISpecifyByArgument          = Optionally specify ROIs to use in place of those  
%                                               determined by detection algorithms for frames   
%                                               specified by frame indices. Each row corresponds to   
%                                               an ROI. The columns correspond to the frame index,  
%                                               X-left, Y-top, width, and height.
%                                               Default = repmat(-1, 1, 5) (flag to ignore).
%                                               Numeric M-by-5 matrix.
%                                     
%                                               E.g.,
%                                               ROISpecifyByArgument = ...
%                                                   [40,   500, 500, 500, 500; ...   
%                                                    1200, 600, 400, 300, 200; ...  
%                                                    ...                      ];  
%                                     
%               ROIIgnoreByArgument           = Optionally specify frame indices of ROIs where ROIs  
%                                               from detection algorithms will be ignored. ROIs of   
%                                               these indices will be interpolated from ROIs of 
%                                               nearby frames.
%                                               Default = -1 (flag to ignore).                                             
%                                               Numeric vector.
%
%                                               E.g.,
%                                               ROIIgnoreByArgument = [70, 1300, ...];
%
%               ROIMinWidthProportion       = Optional minimum width of ROI, given as proportion of   
%                                             ROI width to frame width.
%                                             Default = calculated from video.
%                                             Numeric scalar.
%
%               ROIMinHeightProportion      = Optional minimum height of ROI, given as proportion      
%                                             of ROI height to frame height.
%                                             Default = calculated from video.
%                                             Numeric scalar. 
%                __________________________________________________________________________________
%               | Tutorial to set optional arguments ROIMinWidthProportion and 
%               | ROIMinHeightProportion
%               |
%               | Before a set of videos is to be processed, setting a minimum ROI (face) size can  
%               | help the function filter out false-positive face ROI detections. Specifying a  
%               | minimum size can also reduce processing time because the face-detection  
%               | algorithm limits it scanning to areas larger than the minimum size. The minimum  
%               | ROI size can be specified by arguments ROIMinWidthProportion and   
%               | ROIMinHeightProportion. 
%               |
%               | If argument ROIMinWidthProportion or ROIMinHeightProportion is not supplied as an
%               | input, function FacePulseRate samples frames across the video and takes face
%               | detections from these frames. Proportions corresponding to approximately the
%               | median size of the detections taken are then specified for these arguments.
%               |
%               | The automatic setting of the arguments (as noted above) should work reasonably
%               | well, but manually setting the arguments can be advantageous. Manually setting 
%               | the arguments can avoid instances where the minimum ROI is set too small, which 
%               | lessens the advantages of a minimum ROI, or too large, in which case valid ROIs 
%               | may be filtered out. An example of how to set these arguments follows.
%               | 
%               | First, review the video(s) planned for processing. Out of these, choose a part of   
%               | a video where the face is the smallest. Note that it may not be advisable to use    
%               | a frame where, assuming no zoom, the distance between the camera and face is not 
%               | greater than a few feet. Measure the width and height of this face in pixels, and 
%               | then convert these into proportions. Proportions are used because their effect
%               | remains the same across videos of different frame sizes (e.g., 1920 x 1080 and
%               | 1280 x 720).
%               | 
%               | (1) Extract image at frame
%               | 
%               |     v = VideoReader(Video_InputFile); 
%               |     v.CurrentTime = 7.00; %set time
%               |     frame = readFrame(v); %extract frame to image
%               | 
%               | (2) Measure width and height of face in pixels
%               | 
%               |     Use function imtool to display the frame. Use the ruler tool on the   
%               |     interactive display to take measurements.
%               | 
%               |     imtool(frame); %display image
%               |     width = 161;  
%               |     height = 215;
%               | 
%               | (3) Reduce the measurements by about 1/3 to ensure some valid detections are not  
%               |     ruled out.
%               | 
%               |     width = width - width / 3;
%               |     height = height - height / 3;
%               |  
%               | (4) Convert the width and height to a proportion out of the total width and total  
%               |     height, respectively. 
%               | 
%               |     These proportions will be the arguments specifying the minimum proportions  
%               |     that the face should occupy while scanning a face in the input video during  
%               |     the function.
%               | 
%               |     Width proportion 
%               |     ROIMinWidthProportion = width / v.Width; %reduced width / total width
%               | 
%               |     Height proportion
%               |     ROIMinHeightProportion = height / v.Height; %reduced height / total height          
%                __________________________________________________________________________________
%
%               It may be useful to resize the final ROIs to maximum the portion of the ROI that
%               captures skin and minimize the portion that could capture non-skin. For example,
%               Poh, McDuff, and Picard (2011) used ROIs of full height but 60% width. In 
%               FacePulseRate, the defaults are 120% height and 90% width.
%
%               ROIWidthResizeFactor        = Adjust the final widths of the ROIs by this factor.
%                                             Default = .9.
%                                             Numeric scalar.
%
%               ROIHeightResizeFactor       = Adjust the final heights of the ROIs by this factor.
%                                             Default = 1.2.
%                                             Numeric scalar.
%
%               ProfileFaceDetectorTF         = Whether the profile face detector is enabled. By 
%                                               default, the face detector is enabled. The profile 
%                                               face-detection algorithm tends to be less accurate 
%                                               than the frontal face-detection algorithm. If the 
%                                               profile algorithm appears to be responsible for 
%                                               many misplacements, it can be disabled. The 
%                                               algorithm that determined the ROI is listed on the 
%                                               top of the ROI box. Disable the profile detector by 
%                                               specifying argument ProfileFaceDetectorTF as false.
%
%               DetectVerifyPercentilesYCbCrH = An ROI verification algorithm (for face detection,  
%                                               see function FaceDetect_ROIValidate; for skin 
%                                               detection, see function SkinDetect_ROIValidate)  
%                                               accepts or rejects ROIs returned by detection 
%                                               algorithms. The first step of verification involves 
%                                               applying a severe range of skin segmentation to the 
%                                               ROI. Note that this range is different from the 
%                                               range used for skin segmentation applied when 
%                                               taking the RGB means; that is, it is different from 
%                                               the range specified by 
%                                               SkinSegmentThresholdsGenericYCbCr and 
%                                               SkinSegmentThresholdsGenericHSV. However, as the 
%                                               range used for verification is constrained by 
%                                               SkinSegmentThresholdsGenericYCbCr and 
%                                               SkinSegmentThresholdsGenericHSV, severe settings 
%                                               for SkinSegmentThresholdsGenericYCbCr and 
%                                               SkinSegmentThresholdsGenericHSV could cause the 
%                                               range used for verification to be too severe. If 
%                                               the severity of the range is too high, this could 
%                                               lead ROIs being rejected too frequently. When an 
%                                               ROI is rejected, the annotation "R" will appear. If 
%                                               this annotation appears too frequently, this may 
%                                               indicate the severity is too great. For ROIs 
%                                               returned by the skin-detection algorithm, the 
%                                               annotation "NR" may also be observed frequently if 
%                                               the skin segmentation range used for verification 
%                                               is too severe ("NR" means no skin regions were 
%                                               available; see function 
%                                               SkinDetect_PartitionRegions"). To reduce the 
%                                               severity of the skin segmentation range used for 
%                                               verification, increase the range specified by 
%                                               arguments DetectVerifyPercentilesYCbCrH and
%                                               DetectVerifyPercentilesS.
%
%                                               Default:
%                                               Range for the pixel colors in the YCbCr colorspace 
%                                               and the H channel of the HSV colorspace. The left 
%                                               value is the minimum range and the right value is 
%                                               the maximum range. Note that the values do not 
%                                               refer to pixel colors but to percentages. These 
%                                               percentages indicate color values to use based on 
%                                               percentages from collected skin-color samples. Make 
%                                               the left value smaller and the right value larger 
%                                               to increase the range and, hence, decrease the 
%                                               severity.
%                                               DetectVerifyPercentilesYCbCrH = [6, 94];
%
%               DetectVerifyPercentilesS    =   See description for argument
%                                               DetectVerifyPercentilesYCbCrH.
%                                                 
%                                               Default:
%                                               Range for the pixel colors in the S channel of the 
%                                               HSV colorspace.
%                                               The left value is the minimum range and the right 
%                                               value is the maximum range. Note that the values do 
%                                               not refer to pixel colors but to percentages. 
%                                               These percentages indicate color values to use 
%                                               based on percentages from collected skin-color 
%                                               samples. Make the left value smaller and the right  
%                                               value larger to increase the range and, hence, 
%                                               decrease the severity.
%                                               DetectVerifyPercentilesS = [1, 99];
%
%           -- Skin-Segmentation Settings --
%
%               Another feature of ROIs to inspect is the appropriate degree of skin segmentation. 
%               Skin segmentation refers to excluding pixels that are classified as non-skin by the 
%               skin-segmentation algorithm. The purpose of skin segmentation is to make the face  
%               and skin measurments more robust to environmental changes across the video.  
%               Specifically, anything that changes in the environment could be interpreted as a 
%               change in skin coloration if not excluded. Environmental features that remain 
%               constant and are consistently included in each ROI are not of concern as these 
%               features will not produces changes in skin coloration across frames. Increasing the 
%               exclusion of environmental features within the ROI may have the side effect of   
%               increasing the exclusion of skin areas. Excluding skin areas may become detrimental  
%               if it results in the location of the face from which measurements are taken  
%               changing across frames. It can also be detrimental if the number of pixels from  
%               which measurements are taken changes across frames. These two events will be  
%               detrimental if they lead to changes to measurements that are not due solely to  
%               changes in skin coloration due to blood oxygenation levels. Therefore, the extent 
%               of excluding environmental features should be balanced with the exclusion of skin 
%               areas.
%
%               Some alterations can be made to the skin-segmentation properties to change the  
%               extent of skin segmentation, although the defaults are considered robust under most 
%               circumstances.
%
%               One adjustment that can be made is the range of pixels values accepted as skin from  
%               the YCbCr and HSV colorspaces. Widening the range will decrease the extent of skin  
%               segmentation. 
%
%               The combined used of the YCbCr and HSV colorspaces is based on ...
%               (1) Dahmani et al. (2020), who found that using both improved skin classification
%                   compared to the use of either alone.
%               (2) The observation that using only the YCbCr colorspace did not permit enough
%                   diversity of individual differences in skin color. Specifically, Y-minimum and
%                   Cr-minimum must be at least as low as the defaults to avoid oversegmentation in 
%                   individuals with darker average skin colors when ambient illumination is rather 
%                   low. However, these defaults also permit pixel values from objects that should 
%                   be segmented out; for example, the Cr-minimum at this level permits pixel 
%                   values from overhead lamps. Applying the HSV thresholds in addition to the 
%                   YCbCr thresholds segmented out these extraneous objects.
%
%               SkinSegmentThresholdsGenericYCbCr = Optionally specify the minimum and maximum    
%                                                   values of pixels to be classified as skin in 
%                                                   the YCbCr colorspace.
%                                                   1 x 7 numeric vector.
%                                                   
%                                                   Default:
%                                                   SkinSegmentThresholdsGenericYCbCr = ...
%                                                       [ 29,  ... Y minimum threshold 
%                                                         78,  ... Cb minimum threshold         
%                                                         132, ... Cb maximum threshold 
%                                                         132, ... Cr minimum threshold       
%                                                         172, ... Cr maximum threshold
%                                                        .55,  ... Cb-to-Cr ratio minimum threshold 
%                                                        .97]; % Cb-to-Cr ratio maximum threshold 
%
%               SkinSegmentThresholdsGenericHSV  = Optionally specify the minimum and maximum    
%                                                  values of pixels to be classified as skin in the 
%                                                  HSV colorspace.
%                                                  1 x 2 numeric vector.
%                                                   
%                                                   Default:
%                                                   SkinSegmentThresholdsGenericHSV = ...
%                                                       [ .96,  ... H maximum
%                                                         .09]; %   S minimum 
%
%               Another adjusment is the extent to which pixels near pixels classified as non-skin 
%               are excluded. Increasing argument SkinSegmentSeverityFactor will potentially   
%               increase the number of pixels near non-skin pixels that are classified as non-skin,
%               and vice versa.
%
%               SkinSegmentSeverityFactor   = Optional adjusment of the severity of skin      
%                                             segmentation. Increasing the value will potentially  
%                                             increase the number of pixels excluded through skin
%                                             segmentation.
%                                             Default = 1.
%                                             Numeric scalar.  
%
%               OversegmentationCheckTF     = Whether the oversegmentation check is enabled. By 
%                                             default, the presence of oversegmentation is checked. 
%                                             If oversegmentation is determined to be present, some  
%                                             skin-segmentation settings will be made less severe.  
%                                             Sometimes, oversegmentation will be detected when it 
%                                             doesn't exist. For example, the presense of hair 
%                                             occluding part of the face can sometimes lead the 
%                                             oversegmentation check to determine that too much of 
%                                             the face was segmented; in this case, the cause of 
%                                             much segmentation of the face is due to proper 
%                                             segmentation of hair rather than general 
%                                             oversegmentation. Whether settings were made less 
%                                             severe will be indicated by text on the legend: 
%                                             "Oversegmentation Adjustments: true". If 
%                                             skin-segmentation settings have been made less 
%                                             severe, and the resulting skin segmentation appears 
%                                             too lenient, the oversegmentation adjustments can be 
%                                             disabled by specifying argument 
%                                             OversegmentationCheckTF as false. 
%
%           -- Pulse Rate Settings --
%
%               PulseRateBlockTimestamps    = Optionally specify segments of the input video to  
%                                             analyze. Other portions will not be processed. Must   
%                                             contain an even number of elements.
%                                             Default = [];
%                                             Numeric vector.
%
%                                             E.g., 
%                                             PulseRateBlockTimestamps = [20, 110, 115, 205, ...]; 
%                                             (StartSegment1, EndSegment1, StartSegment2,  
%                                             EndSegment2, ...)
%
%               PulseRateExternallyMeasured = Optionally include externally-measured pulse rate,   
%                                             such as from photoplethysmography (PPG) or   
%                                             electocardiography (ECG), to validate use of   
%                                             FacePulseRate for the specific conditions in which 
%                                             the videos were taken. For example, differences in 
%                                             lighting, distance, and movement, among others, can 
%                                             have large effects on the validity of pulse rate from 
%                                             video.
%                                             Default = [];
%                                             Numeric vector | Cell array.
%
%                                             Note: if blocks specified by argument 
%                                             PulseRateBlockTimestamps, a cell array should be used   
%                                             with a vector corresponding to each block. Each   
%                                             element in a vector represents the pulse rate spaced  
%                                             at 1-second intervals.
%
%                                             E.g.,
%
%                                             - Vector:
%
%                                               Fictitious externally-measured pulse rate 
%                                               measuments:
%                                               PulseRateVector = repmat([74, 75], 90, 1);
%
%                                               PulseRateExternallyMeasured = PulseRateVector;
%
%                                             - Cell array:
%
%                                               Fictitious externally-measured pulse rate
%                                               measuments:
%                                               PulseRateVectorBlock1 = repmat([74, 75], 90, 1);
%                                               PulseRateVectorBlock2 = repmat([61, 60], 90, 1);
%
%                                               PulseRateExternallyMeasured = ...
%                                                   {PulseRateVectorBlock1, ...
%                                                    PulseRateVectorBlock2, ...};
%
%               Although ROI RGB means are collected frame-by-frame and BVP is calculated 
%               frame-by-frame, pulse rate is calculated by windows of frames (function  
%               PulseRate_Algorithms). That is, for a given window of frames, the frames within the 
%               window will have the same pulse rate value assigned. Although pulse rate is 
%               calculated by window here, it is possible to calculate pulse rate (as well as BVP)  
%               frame-by-frame. Calculating pulse rate frame-by-frame is commonly conducted with  
%               instruments that use a camera and light source (i.e., PPG) attached to the finger, 
%               ear, or other extremities. In FacePulseRate, however, frame-by-frame calculations  
%               are not made for two reasons. First, casual testing indicated that frame-by-frame  
%               calculations lacked precision at the frame level. Second, most implementations of  
%               calculating pulse rate from webcams in the literature calculated pulse rate across  
%               a window rather than frame-by-frame. The algorithm used to convert BVP to pulse 
%               rate is taken from iPhys Toolbox (McDuff & Blackford, 2019). 
%
%               From the literature, only instances of a single window used was observed, although  
%               an extensive literature review was not conducted. In contrast, the implementation  
%               in the current function divides frames into separate windows in order for changes 
%               in pulse rate across time to be observed. The span of the window is specified by 
%               PulseRateWindowDurationSec, which is an argument to function FacePulseRate. The   
%               default currently in use is rather arbitrary; the span, or spans, that provides 
%               optimal accuracy still needs to be determined. Data are arranged by span by 
%               function PulseRate_DetermineSpans, which is called by function PulseRate.
%
%               The pulse rate values will be recorded on the "by-window" table, which is an output  
%               variable of function FacePulseRate and which is written to a csv (see function 
%               TableOuput, which is called by function FacePulseRate).              
%
%               PulseRateWindowDurationSec  = Duration, in seconds, of the each window from which
%                                             pulse rate is calculated.
%                                             Default = 90.
%                                             Numeric scalar.
%
%               Pulse rate can be controlled for variations in luminance across the video. 
%               Controlling for luminance is based upon Madan et al. (2018). Madan et al. (2018)  
%               used the L channel from the LAB colorspace, but the Y channel from the YCbCr  
%               colorspace should be nearly equivalent. The option of using the Y channel is 
%               provided because producing it is  more computationally efficient.
%
%               To control for luminance using the Y channel, specify 'Y'. To control for luminance  
%               using the L channel, specify 'L'. To disable controlling for luminance, specify 
%               'F'. Note that even when controlling for luminance is enabled (i.e., either 'Y' or 
%               'L' is used), separate values of pulse rate that are not controlled for luminance 
%               will still be recorded. Therefore, the only difference that may be observed when 
%               disabling luminance control (i.e., specifying 'F') is a minor increase in 
%               performance.
%              
%               PulseRateControlLuminance = Optional control for luminance variation across frames.
%                                           Default = 'F' (disabled).
%                                           Scalar character.                                             
%
%   Outputs
%   -------
%
%       TableByFrame      = Table with RGB means, blood volume pulse (BVP) and pulse rate results,  
%                           input-video timestamps, and various configuration specifications. Also
%                           contains external pulse rate measurements, specified by argument 
%                           PulseRateExternallyMeasured, which might be used for validation
%                           purposes.
%                           Table.
%
%       TableByWindow     = The resolution of the pulse rate results is determined by the window 
%                           size. As a consequence, frames within a window will have identical
%                           pulse rate values. This output contains the results at the window-level
%                           to accommodate analyses at this level.
%                           Table.
%   
%
%   Files Written
%   -------------
%
%       - csv               = TableByFrame written to csv file.
%       - csv               = TableByWindow written to csv file.
%       - Output video      = mp4 media file with pulse rate and diagnostic annotations.      
%        
%
%   Input Video Requirements and Recommendations
%   --------------------------------------------
%
%       Note: only color, not grayscale, videos supported.
%
%       -- Supported File Extensions --
%
%       - .mp4
%       - .avi
%
%       Other file extensions may be supported. Use VideoReader.getFileFormats() to return a list 
%       of supported file extensions. 
%
%       Note that videos with these file extensions may not be supported depending on the specific 
%       format (encoding) of the video.        
%
%       Whether a format is supported depends upon two factors. The first factor is the Matlab 
%       release as FacePulseRate uses Matlab video readers. Format support from the Matlab video
%       readers may change between releases. The second factor is the availability of codecs 
%       installed on a particular computer. FacePulseRate will verify whether a video is supported
%       when the function is run. FacePulseRate uses the Matlab video readers to check the support
%       of the video readers and to check whether the appropriate codecs are available on a
%       particular computer.
%       
%       -- Maximum Video Frame Size -- 
%
%       The input videos can be up to 5000 pixels in either height or width. The limiting factor is
%       assert statements that specify this upper limit in functions SkinDetect_PartitionRegions, 
%       SkinDetect_RegionBoundaries, SkinDetect_ROIValidate, and ROIMeans_TakeMeans. These assert  
%       statements are used to limit dynamic memory allocation. Otherwise, the height and width are   
%       limited by the data type, int16, used to store ROI values across many functions. The  
%       maximum value in type int16 is 32768. However, two functions that calculate a median rely   
%       upon the maximum value being 16384 -- half of 32768 -- this is because the median   
%       calculation needs to add two variables, both of which may be up to 16384. The two functions 
%       that calculate medians are medianByColumn and ROIMSIR_FrameByFrameSmooth_SmoothFR. 
%
%       If the upper bounds are modified, the bounds checking conducted in function 
%       ValidateAndConfigure_Validate should be modified.
%
%       -- Minimum Recommended Video Length --
%
%       Consider using input videos of at least 3 minutes. The skin-detection algorithm and 
%       tailored skin-segmentation algorithm use skin-color samples from the face in the video to  
%       enhance their classifications. These algorithms require a minimum number of samples to be  
%       collected in order to be activated. For videos where face detections are not readily made, 
%       a longer length will be needed. These algorithms do not need to be enabled for proper 
%       operation, but their use may improve accuracy. A warning message will indicate when these 
%       algorithms were not activated due to an insufficient number of skin-color samples.       
%
%       -- Maximum Video Length --
%
%       There is no established maximum length, but the RAM demands for videos over 1.5 hours may 
%       cause some systems to become unstable.
%
%       Beyond the RAM used by Matlab, this function may use around 1 gibabyte of RAM for a 20-
%       minute input video. The RAM use will gradually increase for longer videos. RAM use 
%       faciliates efficiency by reducing frame re-reading and duplicate processing. For longer
%       videos, RAM used should be monitored to determine whether it is within desired levels. 
%       If operation becomes noticably slower, this could indicate RAM use has exceeded RAM 
%       capacity and is being allocated to the hard drive. If RAM use is undesirable, consider 
%       breaking the video down to smaller segments. The function has been tested on a system with 
%       8 gigabytes of RAM.
%
%       -- Recording Environment --
%
%       Although the environment cannot always be changed, skin detection and skin segmentation 
%       will be more successful in some recording environments than others. 
%
%       Best recording environments:
%
%       - The face is not more than a few feet from the video camera. 
%
%       - The colors of the background are distinct from the colors of the face. Skin tends to have 
%         a red hue -- this is the case across individuals with different skin colors -- so care 
%         might be taken to avoid backgrounds with colors similar to skin that also have a red hue.
%
%       - The brightness of the face is not too dark. Skin segmentation will sometimes segment out 
%         pixels that are close to black, so ensuring proper brightness in the area of the face can  
%         avoid this. Note that, assuming brightness of the face is adequate, the skin-segmentation 
%         algorithm is robust across individuals with different skin colors as no skin color would 
%         be expected to approach pure black. Cases of inadequate brightness are often the result  
%         of video cameras automatically reducing their brightness or exposure when a bright light 
%         source is present in an area of the frame other than the face. For example, lamps,  
%         windows, and solid white objects, including clothing, can sometimes lead to a video
%         automatically reducing the brightness of the face.
%
%       -- For Best Appearance of Output Video -- 
%
%       The legend that is displayed on the output video has only been implemented for input videos
%       with dimesions 1280 x 720 or 1920 x 1080 where the video is in a landscape orientation. For 
%       other cases, the legend will not be displayed.
%
%   For Faster Operation
%   --------------------
%
%       Faster read performance will occur when argument StartTime is less than 10% the length of 
%       the full video based on video-reading implementations.
%
%
%   Internal Development
%   --------------------
%
%       Set flags intended for internal development in function ValidateAndConfigure_InternalFlags.
%       Setting flag WriteVideoDetailedDiagnosticsTF to true (false by default) enables additional
%       diagnostic annotations on the output video. Documentation for these flags and the 
%       additional video annotations is not provided in the example script (Example_Script.mlx) and
%       may not be as well developed as for arguments to FacePulseRate and default annotations.
%       Documentation for the additional video annotations is provided in function WriteFaceVideo,
%       but a fuller background on these annotations requires inspection of the individual   
%       functions that correspond to the annotations.
%
%
%   Execution Path
%   --------------
%
%       Input Validation 
%       (ValidateAndConfigure > ValidateAndConfigure_Validate)
%       | 
%       \/
%       Assign structs to hold properties used for groups of related functions 
%       (ValidateAndConfigure)
%       | 
%       \/
%       Read video to determine ROIs and take means from ROIs 
%       (ROIMeans_FirstRead)
%        - Skip the use of detection algorithms for short intervals of frames to improve efficiency
%          (ROIMeans_FirstRead_DetermineSkipFrame).
%        - Set bounding box for detection algorithms (ROIMeans_FirstRead_SetBoundingBoxes). Using a 
%          bounding box reduces the computational time of the algorithms and may reduce false 
%          positives by restricting the area scanned to that where a face is most likely to be 
%          detected. The position of the bounding box is determined based upon the trajectory of 
%          previous face movements, and the size is based upon the number of frames that have 
%          elapsed since a detection was last made.
%        - Select the face-detection algorithm, which returns face ROIs, based upon the success
%          rates of the various face-detection algorithms (FaceDetect_AlgOrder).
%        - Scan bounding box for face ROI with face-detection algorithm (FaceDetect).
%        - Verify detection from face-detection algorithm by checking the number of ROIs returned
%          and whether a pair of eyes is present in ROIs corresponding to a profile orientation of
%          the face (FaceDetect_ROIValidate).
%        - If no face found, scan bounding box for skin ROI with skin-detection algorithm
%          (SkinDetect).
%        - Verify detection from face-detection or skin-detection algorithm by determining the 
%          proportion of pixels that are skin within ROI (ConfirmSkinPresent).
%        - At intervals, recalculate pixel-color thresholds based upon skin-color samples from the 
%          video (ROIMeans_FirstRead_SetThresholds). These thresholds are used for tailored skin
%          segmentation and the skin-detection algorithm. The skin-color samples are collected by
%          function ROIMeans_FirstRead_CollectSkinColorSamples.
%        - Check whether over-segmentation appears to be present from skin segmentation. If so,
%          reduce the severity of the skin-segmentation settings and restart function
%          ROIMeans_FirstRead (SkinSegment_OversegmentationCheck). This check also attempts to
%          modify segmentation settings in response to dark conditions.
%        - Modify the ROI to improve accuracy by stabilizing size and smoothing across frames
%          (ROIMSIR).
%        - Interpolate ROI from nearby ROIs for frames without a detection or for skipped frames
%          (ROIMSIR).
%        - Apply skin segmentation to the ROI (segment out pixels classified as non-skin) 
%          (SkinSegmentMask).
%        - If the ROI appears to be nearly completely segmented by skin segmentation, replace the
%          current ROI with the ROI from a few frames back (ROIMeans_TakeMeans).
%        - Take the mean of the segmented ROI in the RGB colorspace for later use in determining 
%          blood volume pulse (BVP) and pulse rate (ROIMeans_TakeMeans).
%        - Take the mean of the segmented ROI from a luminance channel for later use in controlling 
%          for luminance variation across frames when determining blood volume pulse (BVP) and 
%          pulse rate (ROIMeans_TakeMeans).
%       | 
%       \/
%       Read the beginning portion of the video where determining ROIs and taking means were 
%       skipped in previous step because not enough data were available for assessment
%       (ROIMeans_SecondRead).
%       - Conduct most of the same operations as in the previous step.
%       | 
%       \/
%       Calculate the blood volume pulse (BVP) and pulse rate from each ROI (PulseRate).
%       - Calculate four separate versions of BVP and pulse rate from the four algorithms provided  
%         in iPhys Toolbox (McDuff & Blackford, 2019).        
%       - Calculate a separate version of BVP and pulse rate from each of the four algorithms while
%         controlling for luminance variation across frames (if enabled) (see Madan et al., 2018).                  
%       | 
%       \/
%       Assign the two output arguments (TableByFrame, TableByWindow), which contain tables of
%       data, and write the two output arguments to csv files (TableOutput). Among other variables,
%       these tables contain BVP and pulse rate. Versions of BVP and pulse rate controlled for
%       luminance variation are included if enabled. TableByFrame contains data by frame, whereas
%       TableOutput contains data by window, which is the unit of pulse rate. 
%       | 
%       \/
%       Write a video where pulse rate and diagnostic information are annotated on each frame
%       (WriteFaceVideo). The diagnostic information displayed varies based upon internal flag
%       WriteVideoDetailedDiagnosticsTF, which is set by function 
%       ValidateAndConfigure_InternalFlags. By default, detailed information is not displayed,
%       corresponding to WriteVideoDetailedDiagnosticsTF == false. See function WriteFaceVideo for
%       a description of the video annotations. 
%
%
%   Version History
%   ---------------
%
%       1.0: 8 October 2020. 
%           Initial release.
%           Developed on Matlab 2020b for Windows.
%           Lines of Matlab code, excluding blank lines and comments: 9809.
% 
%
%   Copyright
%   ---------
%
%       Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. 
%
%       For commercial licensing, please contact the author.
%
%       Note: the author claims no affilation with iPhys Toolbox, which is the property of its 
%       respective owners.
% 
%       -- GNU General Public License, Version 2 --
%
%       This program is free software: you can redistribute it and/or modify it under the terms of 
%       the GNU General Public License, version 2, as published by the Free Software Foundation.
%       
%       This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;  
%       without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
%       See the GNU General Public License for more details. 
%       
%       You should have received a copy of the GNU General Public License along with this program;      
%       if not, see <https://www.gnu.org/licenses>.
%       
%       In addition, as a special exception, the copyright holder of FacePulseRate gives you  
%       permission to combine FacePulseRate with free software programs or libraries that are 
%       released under the GNU LGPL and with code included in the standard release of MATLAB under  
%       the appropriate MATLAB license (or modified versions of such code, with unchanged license). 
%       You may copy and distribute such a system following the terms of the GNU GPL for 
%       FacePulseRate and the licenses of the other code concerned.
%       
%       -- RAIL License --
%              
%       In addition to the aforementioned GNU General Public License, this program is licensed 
%       under the terms of the Responsible AI License (RAIL).
%
%
%   Third-Party Copyright Notices
%   -----------------------------
%
%       FacePulseRate Toolbox uses programs from other authors. These programs are listed here.  
%       Third-party copyrights are property of their respective owners.
%
%
%       -- Pulse-Rate Algorithms --
%
%       The following files are based in whole or in part on the implementation in iPhys Toolbox,  
%       copyright (c) Daniel McDuff, Ethan Blackford, January 2019, licensed under the MIT License  
%       and the Responsible AI License (RAIL). See discussion in McDuff, D., & Blackford, E.   
%       (2019). iphys: An open non-contact imaging-based physiological measurement toolbox. In 2019      
%       Annual International Conference of the IEEE Engineering in Medicine and Biology Society  
%       (EMBC), pp. 6521-6524. These files, as well as the licenses for iPhys Toolbox, can be found
%       in folder '.../FacePulseRate/Funs/PulseRate/iPhysToolbox_modified'.
%
%           CHROM_DEHAAN_modified.m ("Chrominance" method). See discussion in De Haan, G., &     
%           Jeanne, V. (2013). Robust pulse rate from chrominance-based rPPG. IEEE Transactions on   
%           Biomedical Engineering, 60(10), 2878-2886. DOI: 10.1109/TBME.2013.2266196
%
%           GREEN_VERKRUYSSE_modified.m ("Green-Channel" method). See discussion in Verkruysse, W.,    
%           Svaasand, L. O., & Nelson, J. S. (2008). Remote plethysmographic imaging using ambient    
%           light. Optics express, 16(26), 21434-21445. DOI: 10.1364/OE.16.021434
%
%           ICA_POH_modified.m ("Independent Component Analysis [ICA]" method). See discussion in   
%           Poh, M. Z., McDuff, D. J., & Picard, R. W. (2010). Non-contact, automated cardiac pulse   
%           measurements using video imaging and blind source separation. Optics express, 18(10),  
%           10762-10774. DOI: 10.1364/OE.18.010762   
%
%           POS_WANG_modified.m ("Plane Orthogonal to Skin-Tone [POS]" method). See discussion in     
%           Wang, W., den Brinker, A. C., Stuijk, S., & de Haan, G. (2017). Algorithmic principles    
%           of remote PPG. IEEE Transactions on Biomedical Engineering, 64(7), 1479-1491. DOI: 
%           10.1109/TBME.2016.2609282    
%
%           ICA.m. Daniel McDuff, Ethan Blackford, & Justin Estepp, December, 2018. Based on an 
%           implementation by: G. D. Clifford (2004) <gari@mit.edu>. Licensed under the MIT License  
%           and the Responsible AI License (RAIL).
% 
%           jade.m. J. F. Cardoso, Version 1.5. See discussion in Cardoso, J. C. C. O., &  
%           Souloumiac, A. Blind beamforming for non-Gaussian signals. 1993. IET. p, 362-370.
%
%           spdetrend.m. Implementation based on M. P. Tarvainen, TBME, 2002.  
%
%           bvpsnr.m. Adapted from the method by G. de Haan, TBME, 2013.       
%
%       PulseRate_ControlForLuminance.m. The use of luminance values to control RGB values for
%       luminance variation across frames was based upon Madan, C. R., Harrison, T., & Mathewson,  
%       K. E. (2018). Noncontact measurement of emotional and physiological changes in heart rate  
%       from a webcam. Psychophysiology, 55(4), e13005.    
%
%
%       -- Viola-Jones Face Detection --
%
%       The following Viola-Jones face-detection files were accessed from OpenCV (Open Source  
%       Computer Vision Library) copyright (c) 2020, OpenCV team. See files, which also contain the
%       respective licences, in
%       '.../FacePulseRate/Funs/ROI_Means/Detect_Algs/Face/Open_CV_Viola-Jones'.
%          
%           lbpcascade_frontalface_improved.xml. Copyright (c) 2017, Puttemans Steven, Can Ergun    
%           and Toon Goedeme, all rights reserved. See discussion in Puttemans, S., Can, E., &  
%           Goedeme, T. (2017). Improving open source face detection by combining an adapted  
%           cascade classification pipeline and active learning. Proceedings of VISAPP 2017, 5, 
%           396-404.
% 
%           haarcascade_profileface.xml. Copyright (c) 2000, Intel Corporation, all rights    
%           reserved. Contributed by David Bradley from Princeton University. 
%       
%           cuda_haarcascade_frontalface_alt_tree.xml. Copyright (c) 2000, Intel Corporation, all   
%           rights reserved. Contributed by Rainer Lienhart. 
%
%           haarcascade_mcs_eyepair_big.xml. Copyright (c) 2006-2020, Modesto Castrillon-Santana   
%           (SIANI), Universidad de Las Palmas de Gran Canaria, Spain. See discussion in 
%           Castrillón, M., Déniz, O., Hernández, D., & Lorenzo, J. (2011). A comparison of face 
%           and facial feature detectors based on the Viola–Jones general object detection 
%           framework. Machine Vision and Applications, 22(3), 481-494. 
%
%
%       -- Skin Region Classification -- 
%
%       SkinDetect_RGBProbSkinTrain.m and SkinDetect_RGBProbSkin.m are files modified for use in 
%       FacePulseRate toolbox from the Skin Segmentation toolbox by Madhav Rajan, 2014. Accessed  
%       from  the Matlab Central File Exchange. See discussion on Github 
%       (https://github.com/madhrajan91/Skin-Segmentation).     
%   
%       data.txt is from the Skin Segmentation Dataset, UCI Machine Learning Repository, copyright   
%       (c) Rajen Bhatt & Abhinav Dhall, 2009. Accessed June, 2020, from 
%       http://archive.ics.uci.edu/ml/datasets/Skin+Segmentation. See discussion in Bhatt, Sharma,  
%       Dhall, Chaudhury (2009). Efficient skin region segmentation using low complexity fuzzy         
%       decision tree model. IEEE-INDICON, Dec 16-18, Ahmedabad, India, pp. 1-4. See also Dhall,    
%       Sharma, Bhatt, and Khan (2009). Adaptive  Digital Makeup, Proc. of International Symposium   
%       on Visual Computing (ISVC), Nov. 30 -Dec. 02, Las Vegas, Nevada, USA, Lecture Notes in  
%       Computer Science, Vol. 5876, pp. 728-736.
%   
%       RGB_External.txt and RGB_External_Rand.txt contain data from data.txt, listed above, with  
%       additional data copyright (c) Douglas Magill, June, 2020.
%
%
%       -- Skin Segmentation -- 
%
%       SkinSegmentMask_Threshold.m. The use of fixed minimum and maximum YCbCr values is adapted  
%       from iphys toolbox. The other features were developed solely by toolbox FacePulseRate.  
%       iphys toolbox copyright (c) Daniel McDuff, Ethan Blackford, January 2019, licensed under   
%       the MIT License and the Responsible AI License (RAIL). See discussion in McDuff, D., &  
%       Blackford, E. (2019). iphys: An open non-contact imaging-based physiological measurement       
%       toolbox. In 2019 Annual International Conference of the IEEE Engineering in Medicine and 
%       Biology Society (EMBC), pp. 6521-6524. 
%
%
%       -- Video Reading and Writing -- 
%
%       ffmpeg.exe and ffprobe.exe are used by FacePulseRate as unmodified binary files. These 
%       files are from the FFmpeg project, which licenses these files under LGPLv2.1. These binary 
%       files can be found in '.../FacePulseRate/Funs/General/ffmpeg'. In accordance with the  
%       license, the source code for the files is included with the distribution of FacePulseRate.  
%       The source code can also be found in '.../FacePulseRate/Funs/General/ffmpeg'.
%
%       getFrameTimestamps.m was adapted from file videoframets.m (v0.1), copyright (c) David  
%       Bulkin, January, 2017. Accessed from the Matlab Central File Exchange.
%
%
%   References
%   ----------
%
%       Dahmani, D., Cheref, M., & Larabi, S. (2020). Zero-sum game theory model for segmenting  
%           skin regions. Image and Vision Computing, 103925.
%
%       Madan, C. R., Harrison, T., & Mathewson, K. E. (2018). Noncontact measurement of emotional 
%           and physiological changes in heart rate from a webcam. Psychophysiology, 55(4), e13005.        
%
%       McDuff, D., & Blackford, E. (2019). iphys: An open non-contact imaging-based physiological 
%           measurement toolbox. In 2019 Annual International Conference of the IEEE Engineering in 
%           Medicine and Biology Society (EMBC), pp. 6521-6524. 
      
 
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Input validation and parsing %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% (1) Validate inputs or assign defaults with the arguments block
%
%     - The arguments block will convert the size or type of inputs to conform to specifications if
%       the input can be readily converted (see Matlab documentation topic "Function Argument 
%       Validation"). For example, a row vector will be converted to a column vector where a 
%       column vector is specified; type single will be converted to type double where type double  
%       is specified; type string will be converted to type char where type char is specified.         
%
%     - Operations within the arguments block are limited. Therefore, many validation and default    
%       assignment operations are conducted after the arguments block. These additional operations 
%       are conducted by function ValidateAndConfigure. If operations to assign a default value  
%       cannot be conducted by the arguments block, they are flagged by -1; defaults assigned this
%       flag will be reassigned by functions called by function ValidateAndConfigure.
%
%     Notes regarding general behavior of the arguments block:
%
%     - The arguments block must come after the function signature and before any executable code.
%       Positional arguments, which are required arguments, come before name-value arguments, which 
%       are always optional arguments.
%
%     - Name-value arguments, but not positional arguments, must be specified as fields to a common 
%       struct. The struct used here is named NVArgs.
%
%     - Validation function mustBeNonempty is not needed when mustBeInteger is used because an 
%       integer is not considered empty.
%
%     - For an empty value to be accepted or assigned, if size is specified, at least one dimension 
%       must be permitted to be 0. For example, specifying size [1, 1] would not permit an empty 
%       value, whereas [:, 1] would permit an empty value.
%
%     - For a list of available validation functions (e.g., mustBeInteger) see Matlab documentation
%       topic "Argument Validation Functions".
%
%     - As mentioned previously, the arguments block will make size and type conversions if the
%       input can be readily converted. If this conversion behavior is not desired, see section 
%       "Avoiding Class and Size Conversions" in Matlab documentation topic "Function Argument 
%       Validation).
%
%     To bypass arguments block for testing:    
%
%     For testing, it may be desired to run functions within function FacePulseRate individually.
%     However, the inputs required for these functions are assigned by the arguments block, but the
%     arguments block can only be used when function FacePulseRate is called. To assign variables
%     assigned by the arguments block without running the arguments block, it is necessary to 
%     assign the struct, NVArgs, that would have been assigned by the arguments block. Each  
%     function directly within function FacePulseRate can then be called manually, assuming that
%     the functions are called in sequential order.
%
% (2) Validate inputs, assign defaults, and set configuration settings with function 
%     ValidateAndConfigure
%
%     - As previously mentioned, operations within the arguments block are limited. Therefore, many     
%       validation and default assignment operations are conducted after the arguments block; this
%       occurs in function ValidateAndConfigure. Extensive additional validation of inputs is
%       conducted within this function. Also, some defaults are reassigned where the arguments
%       block assigned flags of -1.
%         
%     - Structs containing related configuration settings are assigned (e.g., SkinSegmentConfig, 
%       FaceDetectConfig). These structs are accessed by functions within function FacePulseRate.
%       The functions that assign these structs (e.g., SkinSegment_ConfigSetup, 
%       FaceDetect_ConfigSetup) can be consulted for a description of the related settings and the
%       related functions that use them. The functions that assign the structs are called by 
%       function ValidateAndConfigure.


%%%%%% Validate and assign defaults with arguments block %%%%%%

arguments
    
    %Input Arguments                                %Size  %Class  %Validation                        %Default Value
                                                                   %Function(s)
    % - Positional Argument (Required):  
    
    Video_InputFile                                 (1, :) char    {mustBeNonempty, ...               %note: also accepts type string
                                                                    mustBeFile}                   
    % - Name-Value Arguments (Optional):
    
    NVArgs.StartTime                                (1, 1) double  {mustBeNonempty, ...
                                                                    mustBeNonnegative}                = 0 
    NVArgs.EndTime                                  (1, 1) double  {mustBeNonempty, ... 
                                                                    mustBeNumeric}                    = -1 % -1 = flag to define default later
    NVArgs.ROISpecifyByArgument                     (:, 5) double  {mustBeNonempty, ...
                                                                    mustBeInteger}                    = repmat(-1, 1, 5) %flag that none specified      
    NVArgs.ROIIgnoreByArgument                      (:, 1) double  {mustBeNonempty, ...
                                                                    mustBeInteger}                    = -1 %flag that none specified    
    NVArgs.ROIMinWidthProportion                    (1, 1) double  {mustBeNonempty}                   = -1 %flag that none specified
    NVArgs.ROIMinHeightProportion                   (1, 1) double  {mustBeNonempty}                   = -1 %flag that none specified
    NVArgs.ROIWidthResizeFactor                     (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = .90
    NVArgs.ROIHeightResizeFactor                    (1, 1) double  {mustBeNonempty, ...                                                                 
                                                                    mustBePositive}                   = 1.20
    NVArgs.ProfileFaceDetectorTF                    (1, 1) logical {mustBeNonempty}                   = true 
    NVArgs.DetectVerifyPercentilesYCbCrH            (1, 2) double  {mustBeNonempty, ...
                                                                    mustBeNonnegative}                = [6, 94]                                              
    NVArgs.DetectVerifyPercentilesS                 (1, 2) double  {mustBeNonempty, ...                
                                                                    mustBeNonnegative}                = [1, 99]     
    NVArgs.SkinSegmentThresholdsGenericYCbCr        (1, 7) single  {mustBeNonempty, ...
                                                                    mustBePositive}                   = [29, 78, 132, 132, 172, .55, .97] %note: argument block also accepts column vector, which will be automatically converted to row vector
    NVArgs.SkinSegmentThresholdsGenericHSV          (1, 2) single  {mustBeNonempty, ...
                                                                    mustBePositive}                   = [.96, .09] %note: argument block also accepts column vector, which will be automatically converted to row vector    
    NVArgs.SkinSegmentSeverityFactor                (1, 1) double  {mustBeNonempty, ...
                                                                    mustBeInteger, ...
                                                                    mustBePositive}                   = 1 
    NVArgs.OversegmentationCheckTF                  (1, 1) logical {mustBeNonempty}                   = true                                       
    NVArgs.PulseRateBlockTimestamps                 (1, :) double  {mustBePositive}                   = [] %note: argument block also accepts column vector, which will be automatically converted to row vector
    NVArgs.PulseRateControlLuminance                (1, 1) char    {mustBeNonempty}                   = 'F' %note: also accepts strings
    NVArgs.PulseRateWindowDurationSec               (1, 1) double  {mustBeNonempty, ...
                                                                    mustBeInteger, ...
                                                                    mustBePositive, ...
                                                                    mustBeGreaterThanOrEqual( ...
                                                                    NVArgs.PulseRateWindowDurationSec, ...
                                                                    2)}                               = 90 %>= 2 sec for compatibility with function CHROM_DEHAAN   
    NVArgs.PulseRateExternallyMeasured              (1, :) double                                     = [] %note: argument block also accepts column vector, which will be automatically converted to row vector
end
    
            
%%%%%% Additional validation and assignment of defaults; configuration of settings %%%%%%

%Note: 'ValidateAndConfigure' is a custom function located within folder 'FacePulseRate'.
[VideoReadConfig, SkinSegmentConfig, SkinSegmentMasks, ROIGeneralConfig, FaceDetectConfig, ...
 SkinDetectConfig, ROI, ROIForBBox, ROIDiagnostic, HasROI_TF, ROIMatchSizeData, ...
 PulseRateConfigAndData, OutputConfig, FunctionStartTime, UseCompiledFunctionsTF] = ...                      
    ValidateAndConfigure(Video_InputFile, NVArgs);


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Facial ROI determination and ROI-means calculations %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Description:
  
%Determine ROIs targeting frontal or profile orientations of the face. Apply skin segmentation to
%these ROIs, take the means of these ROIs, and assign the means to a struct for use in pulse rate 
%calculations, which occur in a later step. 

%A number of operations depend on settings being set that require a certain number of frames to 
%have been processed. To facilitate this, frames are stored in a limited-size frame cache to permit
%delayed evaluation. For some operations near the first frames processed, the frame cache will not 
%be large enough to permit delayed evaluation. For these frames, the operations will be delayed 
%until the frames will be read a second time. Because some frames are processed the first time they 
%are read and others are processed the second time they are read, a distinction is made in 
%FacePulseRate between frames read during "first-read operations" and "second-read operations".
%Frames processed during first-read operations are processed by function ROIMeans_FirstRead. Frames  
%processed during second-read operations are processed by function ROIMeans_SecondRead.

%Conduct the following operations:

% - A bounding box is determined for each frame to bound the scanning performed by the 
%   face-detection algorithm(s) and the skin-detection algorithm. Using a bounding box reduces the
%   computational time of the algorithms and may reduce false positives by restricting the area
%   scanned to that where a face is most likely to be detected. The position of the bounding box is
%   determined based upon the trajectory of previous face movements, and the size is based upon the
%   number of frames that have elapsed since a detection was last made.
%
% - An ROI for each frame is assigned to be used for calculating pulse rate. The ROI is targeted to
%   be within the frontal or profile orientation of the face. It may also pick up skin in other
%   areas. For each frame, the ROI is determined either by a detection algorithm or by 
%   interpolation based upon ROIs from nearby frames. The detection algorithms include  
%   face-detection algorithms (see functions FaceDetect_ConfigSetup and FaceDetect) and a 
%   skin-detection algorithm (see functions SkinDetect_ConfigSetup and SkinDetect). Interpolation
%   occurs either when the detection algorithms are unable to make a detection for a frame or when  
%   the detection algorithms are skipped for a frame for efficiency. Interpolation is conducted by
%   function ROIMSIR. (The acronym ROIMSIR stands for ROI size-matching, smoothing, interpolation, 
%   and resizing.)   
%
% - Skin-color samples are collected for use in skin segmentation and the skin-detection algorithm. 
%   For details on the collection of skin-color samples, see function 
%   ROIMeans_FirstRead_CollectSkinColorSamples. 
%
% - Timestamps are recorded for each frame if function readFrame is used rather than 
%   vision.VideoFileWriter. Otherwise, timestamps would been assigned by function
%   VideoFaceReadConfig, which was called by function ValidateAndConfigure. Timestamps, in turn,  
%   are used by several functions. Specifically, functions ROIMeans_FirstRead_ExtrapolateROI and  
%   ROIMSIR use timestamps for interpolation, function ROIMeans_SecondRead_SkinDetect uses 
%   timestamps for seeking, function PulseRate uses timestamps for pulse rate calculations,  
%   function TableOutput uses timestamps when writing the output tables, and function   
%   WriteFaceVideo uses timestamps when writing the output video file.
%
% - The position (i.e., [X, Y] coordinates) and size (i.e., width and height) of each ROI are 
%   modified after being returned by a detection algorithm to increase accuracy. Modifications 
%   include normalizing the sizes of ROIs returned from different algorithms to have a consistent 
%   size and smoothing the position and size of a given ROI with ROIs from nearby frames. 
%   Additionally, the size of ROIs may be modified based upon arguments ROIWidthResizeFactor and
%   ROIHeightResizeFactor. The aim of these arguments is to produce an ROI size that tends to 
%   maximize coverage of the face while minimizing coverage of non-skin regions. Although skin
%   segmentation will be conducted (in a later step) to help exclude non-skin regions, skin 
%   segmentation is not perfect, so adjusting the ROI size can be useful. These modifications are
%   conducted by function ROIMSIR.
%
% - Skin segmentation is conducted to exclude pixels within the ROI that may not correspond to 
%   skin. Skin segmentation uses color thresholds, texture thresholds, and morphological operations
%   to classify pixels as skin or non-skin. 
%
%   - Regarding color thresholds, the pixels within the ROI are converted to the YCbCr and HSV
%     colorspaces for comparison against thresholds. These colorspaces are used because they were
%     found to be more effective than the RGB colorspace during testing. These colorspaces are 
%     frequently used when skin segmentation is discussed in the literature. Preset color 
%     thresholds are used as well as color thresholds tailored to the face that appears in the ROI.
%
%   - Regarding texture thresholds, the local color range of each pixel is used. A relatively low  
%     local color range for a given pixel is used as a heuristic of a pixel corresponding to skin 
%     based on the assumption that true skin tends to occur in regions of homogeneous color. The
%     effectiveness of local color range was established through testing. 
%
%   - From the application of these thresholds, a two-dimensional logical matrix is assigned where 
%     pixels that satisfied all thresholds are classified as true and pixels that did not are   
%     classified as false. A morphological close operation is then applied to the logical matrix. 
%     The morphological close tends to fill in classification holes, where a hole is loosely  
%     defined as a region of pixels classified as true that are enclosed by pixels classified as 
%     false. Holes are filled in based on the assumption that true skin tends to be distributed in  
%     the face in contiguous, rather than patchy, regions. The morphological close fills in holes  
%     only below a specified size, which is specified by a morphological structuring element, such 
%     that many holes are not filled. Otherwise, large regions classified as true -- which are
%     assumed to be regions of skin -- may be erroneously filled. 
%
% - Periodically, the thresholds for skin segmentation and the skin-detection algorithm are reset
%   based on recently-collected skin-color samples from the video. A notification is made to the 
%   command window when this occurs.
%
% - If an ROI contains a low proportion of pixels classified as skin by skin segmentation, the ROI 
%   will be discarded. 
%
% - If an ROI that represents a facial profile (as returned by a face-detection algorithm that
%   targets the profile orientation of the face) occurs in a frame in which a pair of eyes is
%   detected, the ROI is discarded. It is assumed that a pair of eyes should not be detectable if 
%   the face is in a profile orientation.
%
% - A check will be conducted to determine whether the skin-segmentation algorithm appears to be
%   oversegmenting ROIs. If so, skin-segmentation settings will be modified to reduce the severity
%   of segmentation in subsequent operations. The first-read operations will start over again to
%   enable the modifications to be applied to all frames. A notification is made to the command
%   window when this occurs.
%
% - The means from the RGB colorspace are taken from each ROI. These means are used later to
%   calculate pulse rate (in function PulseRate).
%
% - The luminance mean is taken from each ROI. The luminance mean is taken either from the Y 
%   channel of the YCbCr colorspace or the L channel of the LAB colorspace. These means can be used 
%   to control the R, G, and B means for luminance variation across frames when the pulse rate is 
%   calculated. 
%
% - Diagnostic information from many of the above steps is recorded for later display on the output
%   video file (see function WriteFaceVideo). This information can be used to fine-tune some input  
%   arguments to function FacePulseRate.

%First-read operations:

%Note: 'ROIMeans_FirstRead' is a custom function located within the folder 'FacePulseRate'.
[ROIGeneralConfig, VideoReadConfig, ROI, ROIDiagnostic, SkinSegmentConfig, SkinSegmentMasks, ...
 PulseRateConfigAndData, SkinDetectConfig, HasROI_TF, ROIMatchSizeData] = ...          
    ROIMeans_FirstRead(ROIGeneralConfig, FaceDetectConfig, VideoReadConfig, ROI, ROIForBBox, ...
        ROIDiagnostic, SkinSegmentConfig, SkinSegmentMasks, PulseRateConfigAndData, HasROI_TF, ...  
        ROIMatchSizeData, SkinDetectConfig, OutputConfig);

%Second-read operations:    
    
%Note: 'ROIMeans_SecondRead' is a custom function located within folder 'FacePulseRate'.
[ROI, HasROI_TF, ROIDiagnostic, PulseRateConfigAndData, SkinSegmentConfig, SkinSegmentMasks] = ...
    ROIMeans_SecondRead(ROI, HasROI_TF, ROIMatchSizeData, ROIDiagnostic, ROIGeneralConfig, ... 
        FaceDetectConfig, SkinDetectConfig, SkinSegmentConfig, SkinSegmentMasks, ...
        PulseRateConfigAndData, VideoReadConfig, OutputConfig);         
     
     
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
%%% Estimate blood volume pulse and calculate pulse rate %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Description:

% - Calculate the blood volume pulse (BVP) at the frame-by-frame level from the ROI means 
%   previously calculated from the ROI of each frame.
%
% - Calculate pulse rate for windows of frames using BVP. Pulse rate is calculated for windows
%   rather than at the frame-by-frame level because, from the author's observations, too much noise
%   exists at the frame-by-frame level for accurate frame-by-frame pulse rate. Further, the  
%   algorithms utilized were designed to estimate pulse rate across a set of frames rather than at
%   the frame-by-frame level.

%If calculating pulse rate enabled
if PulseRateConfigAndData.TF
    
    %Note: 'PulseRate' is a custom function located within folder 'FacePulseRate'.
    PulseRateConfigAndData = PulseRate(PulseRateConfigAndData, VideoReadConfig);                    
end


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Return data table and write table to csv file %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Description:

%Conduct the following operations:

% - Two tables of data are returned. Table TableByFrame contains frame-by-frame ROI means, blood  
%   volume pulse, and pulse rate estimated by windows. Various configuration settings are also  
%   included. Table TableByWindow contains data at the window-level, which is at the level of
%   resolution provided by the pulse-rate algorithms.
%
% - These tables are written to csv files. 

%Note: 'TableOutput' is a custom function located within folder 'FacePulseRate'.
[TableByFrame, TableByWindow] = ...
    TableOutput(VideoReadConfig, ROI, HasROI_TF, FaceDetectConfig, SkinDetectConfig, ...
        PulseRateConfigAndData, SkinSegmentConfig, OutputConfig);              
               
    
%% %%%%%%%%%%%%%%%%%%%%%
%%% Write video file %%%
%%%%%%%%%%%%%%%%%%%%%%%%

%Description:

%Write video with the following annotations:

% - Timestamp
% - Frame number
% - Pulse rate
% - ROIs at various stages of modifications (see function ROIMSIR)
% - Detection algorithms attempted
% - Detection algorithm that made detection
% - Proportion of detection algorithm detections out of attempts
% - Bounding boxes used for detection algorithms
% - Skin-detection algorithm diagnositics
% - Skin-segmentation mask

%Function WriteFaceVideo provides a description of how the annotations can be used to fix ROI
%placement and skin segmentation. Specifically, it provides recommendations on how input arguments
%can be modified to correct ROI placement and skin segmentation.

%If writing to video is enabled
if OutputConfig.WriteVideoTF 
    
    %Note: 'WriteFaceVideo' is a custom function located within folder 'FacePulseRate'.
    WriteFaceVideo(VideoReadConfig, ROI, HasROI_TF, ROIDiagnostic, SkinSegmentConfig, ...
        PulseRateConfigAndData, ROIGeneralConfig, FaceDetectConfig, SkinDetectConfig, ...
        SkinSegmentMasks, OutputConfig, UseCompiledFunctionsTF);                                                 
end


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Display Completion Message and Elapsed Time %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Note: 'FacePulseRate_CompletionMessage' is a custom function located within folder 
%'FacePulseRate'.
FacePulseRate_CompletionMessage(VideoReadConfig, FunctionStartTime);


end %end function
