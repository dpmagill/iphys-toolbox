function PulseRateConfigAndData = ...
             PulseRate_DataSetup(PulseRateTF, PulseRateWindowDurationSec, ...
                 PulseRateExternallyMeasured, PulseRateControlLuminance, ...
                 PulseRateBlockTimestamps, SkinSegmentConfig, VideoReadConfig)
%PulseRate_DataSetup   Setup struct to hold pulse-rate-related configurations and data.
%   
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ValidateAndConfigure.
%
%
%    Description
%    -----------
%
%    This struct contains data and configurations for pulse rate analyses. Its values are used in
%    functions used for the pulse rate analysis, which is conducted in function PulseRate and the
%    functions it calls. The values are also used for displaying on the output video: function
%    WriteFaceVideo_LegendSetup displays some data for the video legend and function 
%    WriteFaceVideo_PulseRate displays the pulse rate values on each frame of the output video. The
%    values are also returned as the output of function FacePulseRate and are written to csvs; this
%    is conducted by function TableOutput.
%
%
%    Description of pulse-rate operations conducted in function PulseRate
%    --------------------------------------------------------------------
%
%    -- ROI RGB means to blood volume pulse (BVP) --
%
%    Blood volume pulse (BVP) is calculated from the RGB means of ROIs using several algorithms 
%    (see function PulseRate_Algorithms, which is called by function PulseRate). These algorithms 
%    were taken from the iPhys Toolbox (McDuff & Blackford, 2019). Citations for the individual 
%    algorithms are provided in function PulseRate_Algorithms.
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
%    function ROIMeans_TakeMeans is more computationally efficient as the RGB frames were already
%    converted to the YCbCr colorspace for a different purpose in function ROIMeans_TakeMeans.  
%
%    If controlling for luminance variation across frames is enabled, the ROI RGB means will be 
%    statistically controlled for luminance variation (see function PulseRate_ControlForLuminance, 
%    which is called by function PulseRate) before the RGB means are conserted to BVP. Note that if 
%    controlling for luminance is enabled, the non-controlled RGB, BVP, and pulse rate values will 
%    be reported alongside those to which the luminance control was applied. 
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
%    When PulseRateWindowDurationSec == inf, the duration of the input video will be used as the
%    window.
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
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Initialization of struct and visualization of pulse rate configurations %%%%%%

PulseRateConfigAndData = ...
    struct( ...
        'TF',                 {PulseRateTF}, ... note: brackets ensure scalar structure
        'WindowDurationSec',  {double(0)}, ...
        'ExternallyMeasured', {PulseRateExternallyMeasured}, ...
        'ControlLuminanceTF', {false}, ...
        'ControlLuminanceColorspace', {PulseRateControlLuminance}, ...
        'BlockTimestamps',    {PulseRateBlockTimestamps}, ...
        'nBlocks', double([]), ...
        'Block', ...
        struct( 'nWindows', int32([]), ...
                'windowsStartIdx', int32([]), ... 
                'windowsEndIdx', int32([]) ...
        ), ...
        'ColorData', ... 
        struct( ...
            'SkinRGBMeans', double([]), ...
            'SkinLuminanceMeans', double([]), ... 
            'SkinRGBMeans_LumControl', double([]) ... 
        ), ...
        'BloodVolPulse', ...
        struct( ...       
            'BloodVolPulse', single([]), ... 
            'BloodVolPulse_LumControl', single([]) ...
        ), ...
        'PulseRate', ...
        struct( ...
            'PulseRate', ... 
            struct( ...
                'Block', double([]) ...
            ), ...
            'PulseRate_LumControl', ... 
            struct( ...
                'Block', double([]) ...
            ), ...
            'PulseRate_External', [], ...
            'PulseRateExpanded', single([]), ...
            'PulseRateExpanded_String', string([]), ...
            'PulseRateExpanded_LumControl', single([]), ...
            'PulseRateExpanded_LumControl_String', string([]), ...
            'PulseRateExpanded_External', [] ...
        ) ...
    );

%%%%%% Specify the window duration %%%%%%

%If PulseRateWindowDurationSec == inf, use the duration of the full video as the window duration.
%Note: if blocks are specified, function PulseRate_DetermineSpans will cap the window duration to
%the duration of each respective block.
if PulseRateWindowDurationSec == inf
    
    PulseRateWindowDurationSec = double(VideoReadConfig.EndTime - VideoReadConfig.StartTime);        
end    

%Must be an integer (although not an integer type).
%Scalar; type double. 
PulseRateConfigAndData.WindowDurationSec = floor(PulseRateWindowDurationSec);


%%%%%% Preallocate matrixs to store ROI RGB means and luminance (Y) means %%%%%%

%Note: the RGB means must be of type double for use in the pulse rate functions.   
PulseRateConfigAndData.ColorData.SkinRGBMeans = nan(VideoReadConfig.NFrames, 3);   

%If controlling ROI RGB means for luminance enabled

%Note: Controlling for luminance is based upon Madan et al. (2018).
%Madan et al. (2018) used L from the LAB colorspace, but Y from the YCbCr color space is nearly 
%equivalent. The option for Y is provided because producing it is more computationally efficient as 
%RGB will have been converted to YCbCr during calculations by function SkinSegmentMask, which is
%called by the function ROIMeans_TakeMeans.

%Demonstration that L and Y are nearly equivalent:
%{
%Load a video frame
VidFrame = read(VidObj, 1);

%Convert video frame to LAB and YCbCr colorspaces
VidFrameLAB = rgb2lab(VidFrame);
VidFrameYCbCr = rgb2ycbcr(VidFrame);

%Modify the luminance channel of both colorspaces to the maximum values
VidFrameLAB(:, :, 1) = 100;
VidFrameYCbCr(:, :, 1) = 235;

%Convert both back to the RGB colorspace for viewing
VidFrameLAB2RGB = lab2rgb(VidFrameLAB, 'OutputType', 'uint8');
VidFrameYCBCR2RGB = ycbcr2rgb(VidFrameYCbCr);

%Display both
%Note that the images are nearly identical.
imtool(VidFrameLAB2RGB)
imtool(VidFrameYCBCR2RGB)
%}

%Note: type double needed as type double required as input to pulse rate functions.

%If controlling ROI RGB means for luminance is disabled 
if PulseRateConfigAndData.ControlLuminanceColorspace == 'F'
 
    %Set flag to disable luminance control
    PulseRateConfigAndData.ControlLuminanceTF = false;    
    
%If controlling ROI RGB means for luminance is enabled 
else
    
    %Set flag to enable luminance control
    PulseRateConfigAndData.ControlLuminanceTF = true;

    %Luminance mean is specified to be from YCbCr colorspace
    %Y is the luminance channel in the YCbCr colorspace.
    if PulseRateConfigAndData.ControlLuminanceColorspace == 'Y'
        
        %Must be type double for operations in function PulseRate
        PulseRateConfigAndData.ColorData.SkinLuminanceMeans.Y_of_YCbCr = ...
            nan(VideoReadConfig.NFrames, 1);

    %Luminance mean is specified to be from LAB colorspace
    %L is the luminance channel in the LAB colorspace.
    elseif PulseRateConfigAndData.ControlLuminanceColorspace == 'L'

        %Must be type double for operations in function PulseRate
        PulseRateConfigAndData.ColorData.SkinLuminanceMeans.L_of_LAB = ...
            nan(VideoReadConfig.NFrames, 1);
    end
end


%%%%%% Validate settings %%%%%%

if PulseRateControlLuminance == 'Y' && ~ SkinSegmentConfig.SkinSegmentTF
    
    ME = ...
        MException( ...
            'Component:Argument', ...
             ['Error: Control of luminance using Y has been implemented to use', ...
              ' skin segmentation (SkinSegmentTF = true) to increase computational efficiecy;', ...
              ' if PulseRateControlLuminance = ''Y'', then SkinSegmentTF must be true.', ...
              ' To control luminance without SkinSegmentTF = true, use', ...
              ' PulseRateControlLuminance = ''L''.'] ...
        );
    
    throw(ME);         
end


end %end function

