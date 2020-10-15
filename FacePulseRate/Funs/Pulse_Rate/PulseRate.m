function PulseRateConfigAndData = PulseRate(PulseRateConfigAndData, VideoReadConfig)                               
%PulseRate   Calculate the pulse rates of specified windows of time from the RGB means of ROIs.
%
%    Helper function to function FacePulseRate.
%
%
%    Description
%    -----------
%
%    -- ROI RGB means to blood volume pulse (BVP) --
%
%    Blood volume pulse (BVP) is calculated from the RGB means of ROIs using several algorithms 
%    (function PulseRate_Algorithms). These algorithms were taken from the iPhys Toolbox (McDuff & 
%    Blackford, 2019). Citations for the individual algorithms are provided in function
%    PulseRate_Algorithms.
%
%    The BVP and RGB values will be recorded on the "by-frame" table, which is an output variable 
%    of function FacePulseRate and which is written to a csv (see function TableOuput, which is
%    called by function FacePulseRate).
%
%       - Controlling RGB means for luminance variation across frames  
%
%    An argument (PulseRateControlLuminance) to function FacePulseRate allows the RGB means to be
%    controlled for luminance variation across frames. Controlling for luminance is based upon 
%    Madan et al. (2018). Specifying value 'L' for the argument uses the L channel from the LAB 
%    colorspace to represent luminance, which is the channel used by Madan et al. (2018). 
%    Specifying value 'Y' for the argument uses the Y channel from the YCbCr color space, which 
%    should approximate the L channel. The option for Y is provided because producing it (in 
%    function ROIMeans_TakeMeans) is more computationally efficient as the RGB frames were already
%    converted to the YCbCr colorspace for a different purpose in function ROIMeans_TakeMeans.  
%
%    If controlling for luminance variation across frames is enabled, the ROI RGB means will be 
%    statistically controlled for luminance variation (function PulseRate_ControlForLuminance) 
%    before the RGB means are conserted to BVP. Note that if controlling for luminance is enabled,
%    the non-controlled RGB, BVP, and pulse rate values will be reported alongside those to which
%    the luminance control was applied. 
%
%    -- BVP to pulse rate windows -- 
%
%    Although ROI RGB means are collected frame-by-frame and BVP is calculated frame-by-frame,
%    pulse rate is calculated by windows of frames (function PulseRate_Algorithms). That is, for a 
%    given window of frames, the frames within the window will have the same pulse rate value 
%    assigned. Although pulse rate is calculated by window here, it is possible to calculate pulse 
%    rate (as well as BVP) frame-by-frame. Calculating pulse rate frame-by-frame is commonly 
%    conducted with instruments that use a camera and light source (i.e., PPG) attached to the 
%    finger, ear, or other extremities. In FacePulseRate, however, frame-by-frame calculations are 
%    not made for two reasons. First, casual testing indicated that frame-by-frame calculations 
%    lacked precision at the frame level. Second, most implementations of calculating pulse rate 
%    from webcams in the literature calculated pulse rate across a window rather than 
%    frame-by-frame. The algorithm used to convert BVP to pulse rate is taken from iPhys Toolbox 
%    (McDuff & Blackford, 2019). 
%
%       - Pulse rate window specification 
%
%    From the literature, only instances of a single window used was observed, although an 
%    extensive literature review was not conducted. In contrast, the implementation in the current 
%    function divides frames into separate windows in order for changes in pulse rate across time 
%    to be observed. The span of the window is specified by PulseRateWindowDurationSec, which is an
%    argument to function FacePulseRate. The default currently in use is rather arbitrary; the  
%    span, or spans, that provides optimal accuracy still needs to be determined. Data are arranged
%    by span by function PulseRate_DetermineSpans, which is called by function PulseRate.
%
%    The pulse rate values will be recorded on the "by-window" table, which is an output variable 
%    of function FacePulseRate and which is written to a csv (see function TableOuput, which is
%    called by function FacePulseRate).
%    
%       - Pulse rate windows represented frame-by-frame
%
%    Although pulse rate is calculated by window and not by frame, for visual assessement, it may 
%    be useful to see the pulse rate reported for each frame (in which case, all frames within a 
%    window will have the same pulse rate value). This frame-by-frame reporting is used in the
%    frame-by-frame output variable of function FacePulseRate, written to the frame-by-frame csv,
%    and displayed on the output video. The variables storing these frame-by-frame values are
%    denoted by the suffix "expanded". Additionally, pulse rate values are converted to string 
%    format (function PulseRate_Algorithms) for use in annotations on the output video. The
%    annotations are written to the output video by function WriteFaceVideo_PulseRate, which is 
%    called by function WriteFaceVideo.
%
%    -- Externally-measured pulse rate data --
%
%    If externally-measured pulse rate values were entered as an argument 
%    (PulseRateExternallyMeasured) to function FacePulseRate, these values, which would have been
%    entered at the second level, will be arranged here to align with the by-window and the  
%    by-frame format. These aligned values will be repoted on the by-window table and csv, the
%    by-frame table and csv, and the output video. 
%
%    -- Note --
%
%    The settings for the current function were specified in function PulseRate_DataSetup, which is
%    called by function ValidateAndConfigure.
%
%
%    References
%    ----------
%
%    Madan, C. R., Harrison, T., & Mathewson, K. E. (2018). Noncontact measurement of emotional and 
%    physiological changes in heart rate from a webcam. Psychophysiology, 55(4), e13005. 
%
%    McDuff, D., & Blackford, E. (2019). iphys: An open non-contact imaging-based physiological 
%    measurement toolbox. In 2019 Annual International Conference of the IEEE Engineering in 
%    Medicine and Biology Society (EMBC), pp. 6521-6524.         
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Extract configuration settings %%%%%%

%Exract variable from struct for efficiency
FrameTimestamp_Double = VideoReadConfig.FrameTimestamp_Double;


%%%%%% Fill in ROI RGB means values that are missing (NaN) %%%%%%

%Fill in ROI RGB means values that are missing (NaN) as the pulse-rate algorithms cannot accept 
%missing values. Also, if luminance-control is enabled, missing values may also be problematic 
%for linear regression.

%Note: missing values may occur intentionally. For example, if the entire ROI happens to be
%segmented out -- which might occur, for example, if a paper is flipped in front of the camera --  
%there will be no values with which to compute the mean because segmented pixels are excluded from  
%the mean calculation.  

%Check for missing (NaN) values 
if any( isnan(PulseRateConfigAndData.ColorData.SkinRGBMeans), 'all' ) 
    
    %Frame index of frames with missing RGB values
    FramesMissingIdx = ...
        num2str( ...
            VideoReadConfig.FrameIdx( ...
                isnan( PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 1) ) ...
            ) ...
        );
    
    %Display warning message:
    
    fprintf('\n'); %new line
    
    warning( ...
        ['Some frame(s) do not have ROI means.' ...
         ' These frame(s) were likely completely masked by skin segmentation, preventing', ...
         ' mean(s) from being taken. It is typical for a few frames in a video to be masked', ...
         ' due to environmental conditions. For example, the individual could have', ...
         ' momentarily blocked the camera with a paper while reading. However, if there are', ...
         ' dozens of frames masked, this could indicate either incorrect ROI placement or', ...
         ' skin segmentation that is too severe. The pulse rate algorithms cannot accept', ...
         ' missing values, so the missing means will be filled by linear interpolation.', ... 
         ' Frame(s) without means include ', ...
         FramesMissingIdx, '.'] ...
    );   
    
    %Display message immediately
    drawnow(); 
       
    %Fill in missing RGB means by linear interpolation
    PulseRateConfigAndData.ColorData.SkinRGBMeans = ...
        fillmissing(PulseRateConfigAndData.ColorData.SkinRGBMeans, ... Y axis
            'linear', 'SamplePoints', ...
            FrameTimestamp_Double ... X axis
        );    
end


%%%%%% Change ROI RGB means values that are zeros to non-zeros %%%%%%

%Fill in ROI RGB means values that are zero as the pulse-rate algorithms cannot accept values of 
%zero. 

%Values of zero are unlikely but may occur under two conditions:

%(1) The only pixels left unsegmented are black (zero). These values are unlikely because the 
%    skin-segmentation algorithm will likely segment out values of zero.

%(2) The linear interpolation step conducted previously to fill in missing values assigned values 
%    of zero.

%Check for values of zero and change to non-zeros if present
if any( PulseRateConfigAndData.ColorData.SkinRGBMeans == 0, 'all' )
       
    PulseRateConfigAndData.ColorData.SkinRGBMeans( ...
        PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 1) == 0, ...
        1 ...
    ) = .001;

    PulseRateConfigAndData.ColorData.SkinRGBMeans( ...
        PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 2) == 0, ...
        2 ...
    ) = .001;

    PulseRateConfigAndData.ColorData.SkinRGBMeans( ...
        PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 3) == 0, ...
        3 ...
    ) = .001;
end


%%%%%% Control ROI RGB means for time-varying luminance %%%%%%

%Controlling for luminance is based upon Madan et al. (2018).
%Madan et al. (2018) used L from the LAB colorspace, but Y from the YCbCr color may closely
%approximate it. The option for Y is provided because producing it (in function ROIMeans_TakeMeans)
%is more computationally efficient as another function (SkinSegmentMask) has already converted the
%frame to the YCbCr colorspace, from which the Y channel can be used. See the function file for 
%function ROIMeans_TakeMeans for further discussion.

%If controlling ROI RGB means for luminance is enabled
if PulseRateConfigAndData.ControlLuminanceTF 
    
    %Note: PulseRate_ControlForLuminance is a custom function located within folder FacePulseRate.
    PulseRateConfigAndData = ...
        PulseRate_ControlForLuminance(PulseRateConfigAndData, FrameTimestamp_Double);
end


%%%%%% Determine pulse rate windows %%%%%%

%The duration of each window is specified by PulseRateWindowDurationSec, which is an argument  
%to function FacePulseRate.
%If the duration between BlockTimestampStart and BlockTimestampEnd is not exactly divisible by 
%PulseRateWindowDurationSec, modifications will be made to the duration(s) of the window(s).

%In the case where more than one windows fit entirely between BlockTimestampStart and 
%BlockTimestampEnd, the duration of the first and last windows will be enlarged to fill the span 
%between BlockTimestampStart and BlockTimestampEnd.

%In the case of one window, the window will be enlarged or reduced to be equal to the span between
%BlockTimestampStart and BlockTimestampEnd. If the span exceeds the duration of 
%PulseRateWindowDurationSec, a window may contain frames one less than twice the frames expected to
%fill the duration specified by PulseRateWindowDurationSec, that is,  
%2 * (FS * PulseRateWindowDurationSec) - 1; a window will not contain fewer frames than
%FS * PulseRateWindowDurationSec. If the span between BlockTimestampStart and BlockTimestampEnd is 
%less than the duration of PulseRateWindowDurationSec, the window will be reduced.

%Note: PulseRate_DetermineSpans is a custom function located within folder FacePulseRate.
PulseRateConfigAndData = ...
    PulseRate_DetermineSpans(PulseRateConfigAndData, FrameTimestamp_Double, VideoReadConfig.FS);
        

%%%%%% Calculate BVP and pulse rate from ROI RGB means with various algorithms within specified windows %%%%%%

%%%%%% --- Display notification message %%%%%%

message = ...
    ['\nEstimating blood volume pulse (BVP) from ROI means and calculating', ...
     '\npulse rate from BVP.\n'];
       
%Display message       
fprintf(message);

%Display message immediately
drawnow(); 

%%%%%% --- Calculate BVP and pulse rate %%%%%%

%Do not use ROI RGB means controlled for luminance
LumControlTF = false;

%Note: PulseRate_Algorithms is a custom function located within folder FacePulseRate.
[BVP, PR, PRExpanded, PRExpanded_String] = ...
    PulseRate_Algorithms(PulseRateConfigAndData, VideoReadConfig, FrameTimestamp_Double, ...
        LumControlTF);
  
PulseRateConfigAndData.BloodVolPulse.BloodVolPulse = BVP; %type single
PulseRateConfigAndData.PulseRate.PulseRate = PR; %struct
PulseRateConfigAndData.PulseRate.PulseRateExpanded = PRExpanded; %type single
PulseRateConfigAndData.PulseRate.PulseRateExpanded_String = PRExpanded_String; %type string

%%%%%% --- Calculate luminance-controlled BVP and pulse rate %%%%%%    
    
%If controlling ROI RGB means for luminance is enabled
%Note: If controlling for luminance is enabled, BVP and pulse rate will be calculating for both
%controlled and uncontrolled ROI RGB means. Both the controlled and uncontrolled versions will be 
%displayed in the output video and assigned to the output table or written to the output csv.
if PulseRateConfigAndData.ControlLuminanceTF
 
    %Use ROI RGB means controlled for luminance
    LumControlTF = true;
    
    %Note: 'PulseRate_Algorithms' is a custom function located within folder 'FacePulseRate'.
    [BVP, PR, PRExpanded, PRExpanded_String] = ...
        PulseRate_Algorithms(PulseRateConfigAndData, VideoReadConfig, FrameTimestamp_Double, ...
            LumControlTF);
               
    PulseRateConfigAndData.BloodVolPulse.BloodVolPulse_LumControl = BVP; %type single
    PulseRateConfigAndData.PulseRate.PulseRate_LumControl = PR; %struct
    PulseRateConfigAndData.PulseRate.PulseRateExpanded_LumControl = PRExpanded; %type single 
    PulseRateConfigAndData.PulseRate.PulseRateExpanded_LumControl_String = PRExpanded_String; %type string
end


%%%%%% Adapt external pulse rate measurements for comparison to pulse rate detected from face %%%%%%

%If externally-measured pulse rate values provided by user (argument PulseRateExternallyMeasured to 
%function FacePulseRate).
if ~ isempty(PulseRateConfigAndData.ExternallyMeasured)
    
    %Note: 'PulseRate_External' is a custom function located within folder 'FacePulseRate'. 
    PulseRateConfigAndData = PulseRate_External(PulseRateConfigAndData, FrameTimestamp_Double);
end
    
   
end %end function

