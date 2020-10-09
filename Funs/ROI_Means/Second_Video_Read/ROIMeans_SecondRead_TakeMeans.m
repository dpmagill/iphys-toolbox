function [PulseRateConfigAndData, ROI, HasROI_TF, SkinSegmentConfig, SkinSegmentMasks] = ...
          ROIMeans_SecondRead_TakeMeans(VideoReadConfig, ROI, PulseRateConfigAndData, ...
              SkinSegmentConfig, SkinSegmentMasks, HasROI_TF, OutputConfig, ROIGeneralConfig)
%ROIMeans_SecondRead_TakeMeans   Calculate means of the ROI of each frame for any frames where the 
%                                first-read operations were not ready to take the ROI means. 
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_SecondRead.
%
%
%    Description
%    -----------
%
%    Conduct the ROI-means operations (function ROIMeans_TakeMeans) for frames that did not receive 
%    these operations during the the first read. These frames come temporally before the frames on  
%    which operations were conducted by the first read. 
%
%    - A skin-proportion check will be applied to each ROI. If an ROI does not pass this check, the  
%      ROI will be replaced by a previous ROI if one is available.
%    - Record the R, G, and B means from the ROI, with skin segmentation if enabled, of each frame.    
%    - Record the luminance channel (either L of the LAB colorspace or Y of the YCbCr colorspace)
%      mean from the ROI, with skin segmentation if enabled, to control for luminance variations in 
%      function PulseRate.
%    - Record the skin-segmentation masks for later display on the output video. These 
%      skin-segmentation masks will be used by function WriteFaceVideo.  
%
%    Note: for frames that were ready to receive these operations within the first-read operations, 
%    function ROIMeans_TakeMeans was called by function ROIMeans_FirstRead_TakeMeans.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Display notification message %%%%%%

message = ...
    ['\n\nCalculating ROI means for frames near beginning of video where' ...
     '\nROI-means operations not previously conducted ...\n'];
 
%Display message
fprintf(message);

%Display message immediately
drawnow(); 


%%%%%% Extract some configuration settings for performance %%%%%%

FrameIdx                    = VideoReadConfig.FrameIdx; %type int32
VidObj                      = VideoReadConfig.VidObj; %VideoReader system object

WriteVideoTF                = OutputConfig.WriteVideoTF;
WriteVideoShowSkinSegmentTF = OutputConfig.WriteVideoShowSkinSegmentTF;


%%%%%% Setup video reading %%%%%% 

%ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx indicates the maximum frame index for
%which operations should be conducted by this function. Lower frame indices would have already had
%the operations conducted here performed previously (by function ROIMeans_FirstRead_TakeMeans). See 
%function ROIGeneralConfig_Setup for details.
%Type int32.
MaxFrameToProcessLinIdx = ROIGeneralConfig.ROIMeansMaxFrameToProcessSecondReadLinIdx;


%%%%%% Setup progress notifications %%%%%%

%Progress notifications are displayed to command window by function LoopProgressNotification.

%Interval to elapse between each notification message
%Specify type int32 for protection against floating-point gaps.
Notifications_Interval = int32(1000);    

%Index of frames in loop for progress notifications 
%Specify type int32 for protection against floating-point gaps.
Notifications_FrameIdx = int32(1 : MaxFrameToProcessLinIdx); 

%Initialize loop counter for progress notifications    
%Specify type int32 for protection against floating-point gaps.
Notifications_LoopCounter = int32(0); 

%Record start time for progress notifications 
Notifications_LoopStartTime = tic;


%%%%%% Read video %%%%%%

%The video reader to use is specified by VideoReadConfig.UseVisionTF, which is specified by  
%function VideoReadConfig_Setup.

%%%%%% --- Use system object vision.VideoFileReader for video reading %%%%%%

if VideoReadConfig.UseVisionTF

    %Extract vision.VideoFileReader system object
    videoFReader = VideoReadConfig.videoFReader;   
    
    %Initialize flag indicating whether seeking to StartTime has completed
    SeekCompletedTF = false;
   
    %Initialize frame index that counts frames from the beginning of the video (rather than from
    %StartTime, which is where i begins). This is needed as vision.VideoFileReader always starts
    %reading from the beginning of the video.
    %Only used for seeking to StartTime.
    FromBeginningIdx = int32(0);
    
    %Initialize frame index that counts frames from StartTime, which may be later than the
    %beginning of the video.
    %Used for all operations except seeking to StartTime.
    %Specify type int32 for protection against floating-point gaps.
    i = int32(0);
    
    %Initialize end-of-file flag
    EndOfFileTF = false;

    %Loop through frames 
    while i < MaxFrameToProcessLinIdx && ... 
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
            
        %Conduct operations for ith frame
        %For ith ROI, apply tailored skin segmentation and take the RGB means and the luminance 
        %mean.
        %Nested function.
        TakeMeans_Ops();                                
 
    end %end vision.VideoFileReader frame-reading loop 
    
    %Reset system object vision.VideoFileReader
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
    
    %Initialize index
    %Specify type int32 for protection against floating-point gaps.
    i = int32(0);
    
    %Loop through frames 
    while i < MaxFrameToProcessLinIdx && ...
          hasFrame(VidObj) %verify that frame exists for next frame
      
        %Read the frame corresponding to the frame after the current time
        %Type uint8.
        VidFrame = readFrame(VidObj);

        %Advance index       
        i = i + 1;
        
        %Conduct operations for ith frame
        %For ith ROI, apply tailored skin segmentation and take RGB means and the luminance mean. 
        %Nested function.
        TakeMeans_Ops();            

    end %end VideoReader frame-reading loop      
end


%=============================================================================================
%Nested functions 
%=============================================================================================


%=============================================================================================
function TakeMeans_Ops()  
%TakeMeans_Ops    For ith ROI, apply tailored skin segmentation and take the RGB means and the  
%                 luminance mean.


%%%%%% For ith ROI, apply skin segmentation and take the RGB means and the luminance mean %%%%%%

%Additionally, function ROIMeans_TakeMeans will apply a skin-proportion check to the ith ROI. If 
%the ROI does not pass this check, the ROI will be replaced by a previous ROI (if available). This
%replacement ROI will be returned as ROIAdjusted_i and flag AdjustedBecauseLowSkinProportionTF_i
%will be returned as true.

%Flag that function not called from first-read operations
FirstReadTF = false;

%Note: ROIMeans_TakeMeans is a custom function located within folder 'FacePulseRate'.
[SkinRGBMeans_i, IsNotSkin_PixelColor_Packed_i, AdjustedBecauseLowSkinProportionTF_i, ...
 ROIAdjusted_i, Y_of_YCbCr_i, L_of_LAB_i] = ...
    ROIMeans_TakeMeans(i, VidFrame, ROI, SkinSegmentConfig, ...
        PulseRateConfigAndData.ControlLuminanceTF, ...                 
        PulseRateConfigAndData.ControlLuminanceColorspace, WriteVideoTF, ...
        WriteVideoShowSkinSegmentTF, VideoReadConfig.FrameIdx, VideoReadConfig.VidObjWidth, ...
        VideoReadConfig.VidObjHeight, ROIGeneralConfig.ROIMSIR_FirstFrameIdx, FirstReadTF);       

     
%%%%%% Assign output from ith frame %%%%%%

%These assignments are not made within function ROIMeans_TakeMeans because this would result in the
%variables being entirely reassigned on each iteration; by making the assignments outside the  
%function, only the ith portion of each variable is reassigned on each iteration. 

%Assign ROI RGB mean
%Type double.
PulseRateConfigAndData.ColorData.SkinRGBMeans(i, :) = SkinRGBMeans_i;            

%If the ROI from the previous frame was used due to a low proportion of pixels classified as skin
%within the ROI.
if AdjustedBecauseLowSkinProportionTF_i

    %Logical value indicating that the ROI from the previous frame was used
    HasROI_TF.AdjustedBecauseLowSkinProportion(i) = AdjustedBecauseLowSkinProportionTF_i;    
    
    %Assign adjusted value to ROI matrix
    %Type int16.
    ROI(i, :) = ROIAdjusted_i;
end

%Assign the binary-packed inverted skin-segmentation mask that corresponds to the ROI. 
%These values will be used in function WriteFaceVideo to display the skin-segmentation mask on the
%output video.
if SkinSegmentConfig.SkinSegmentTF
    
    %Inverted skin-segmentation mask as binary-packed image 
    %Matrix; type uint32.
    SkinSegmentMasks(i).IsNotSkin_PixelColor_Packed = IsNotSkin_PixelColor_Packed_i;     
end

%If controlling ROI RGB means for luminance is enabled
if PulseRateConfigAndData.ControlLuminanceTF

    %Luminance mean is specified to be from YCbCr colorspace
    %Y is the luminance channel in the YCbCr colorspace.
    if PulseRateConfigAndData.ControlLuminanceColorspace == 'Y'

        %Assign luminance mean
        %Type double.
        PulseRateConfigAndData.ColorData.SkinLuminanceMeans.Y_of_YCbCr(i) = Y_of_YCbCr_i;

    %Luminance mean is specified to be from LAB colorspace
    %L is the luminance channel in the LAB colorspace.
    elseif PulseRateConfigAndData.ControlLuminanceColorspace == 'L'

        %Assign luminance mean
        %Type double.
        PulseRateConfigAndData.ColorData.SkinLuminanceMeans.L_of_LAB(i) = L_of_LAB_i;
    end        
end


%%%%%% Loop Progress Notifications %%%%%%

%Note: include the following statement immediately before loop: LoopStartTime = tic

%Note: 'LoopProgressNotification' is a custom function located within folder 'FacePulseRate'.
Notifications_LoopCounter = ...
    LoopProgressNotification(Notifications_Interval, Notifications_FrameIdx, i, ...
        Notifications_LoopStartTime, Notifications_LoopCounter); 
  
    
end %end nested function


end %end main function

