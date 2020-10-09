function [ROIFacePrimaryXML, PulseRateTF, WriteVideoDetailedDiagnosticsTF, ...
          UseCompiledFunctionsTF] = ...
              ValidateAndConfigure_InternalFlags()
%ValidateAndConfigure_InternalFlags   Assign internal flags.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ValidateAndConfigure.
%
%
%    Description
%    -----------
%
%    Assign internal flags that control various settings. These flags are intended to be used for
%    internal development. The annotations on the output video can help guide the fine-tuning of 
%    many of these flags. See file WriteFaceVideo.m for a description on how they can be used.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Enable detailed diagnostic annotations on output video %%%%%%

%Use WriteVideo_DetailedDiagnosticsTF for detailed diagnostics on the output video. This flag
%displays the following on the output video. For additional details, see function WriteFaceVideo. 
%
%    - Bounding box diagnostics:
%
%      For background, see function ROIMeans_FirstRead_SetBoundingBoxes.
%      For details on annotations, see function WriteFaceVideo.
%
%      - Bounding box for the face-detection algorithm
%      - Bounding box for the skin-detection algorithm
%
%    - ROI modification diagnostics:
%
%      For background, see function ROIMSIR.
%      For details on annotations, see function WriteFaceVideo.
%
%      - ROI without modifications by function ROIMSIR
%      - ROI with modifications by function ROIMSIR without frame-by-frame smoothing and resizing 
%
%    - Skin-detection algorithm diagnostics
%
%      For background, see function SkinDetect.
%      For details on annotations, see function WriteFaceVideo_SkinDetectDiagnosis.
%        
%      - Annotations of regions considered by function SkinDetect 
%      - Annotation of the distance between the predicted ROI and the selected regions.
%
%    - Additional detection diagnostics:
%
%      - A list of all detection methods attempted, including unsuccessful methods.
%
%    If WriteVideo_DetailedDiagnosticsTF is false, then WriteVideoShowROISkinDiagnosisTF will be
%    false.

%Default = false;
WriteVideoDetailedDiagnosticsTF = false;


%%%%%% Enable pulse-rate calculations %%%%%%

PulseRateTF = true;


%%%%%% Enable the use of compiled functions %%%%%%

%Note: If UseCompiledFunctionsTF == true, function ValidateAndConfigure_Validate will determine 
%whether the architecture of the user's computer meets the specified architecture. If not,  
%UseCompiledFunctionsTF will be changed to false. The specified architecture can be modified in
%function ValidateAndConfigure_Validate.

UseCompiledFunctionsTF = true;


%%%%%% Specify the xml file for the primary Viola-Jones detector %%%%%%

%As of the current implementation, the primary face-detection algorithm is expected to detect faces 
%in a frontal orientation. One operation that depends upon this is the collection of skin samples
%from which to set the thresholds for skin segmentation and skin detection (see function
%ROIMeans_FirstRead_CollectSkinColorSamples). Additionally, some annotations on the output video
%label the primary face-detection algorithm as the "frontal" algorithm (see functions 
%WriteFaceVideo_LegendSetupText and WriteFaceVideo_ROIAnnotation).

%Note: this variable is not assigned by function FaceDetect_ConfigSetup, where the detectors of 
%other face-detection algorithms are assigned, because it is needed by a function before 
%FaceDetect_ConfigSetup is called.

%Note: if changed, algorithm labels in function WriteFaceVideo_LegendSetupText should be modified.
%Values may also need to be changed for settings ROIMinWidthProportionIncreaseSec1, 
%ROIMinHeightProportionIncreaseSec1, ROIMinWidthProportionIncreaseSec2, and
%ROIMinHeightProportionIncreaseSec2 in function FaceDetect_ConfigSetup_ViolaJones.
ROIFacePrimaryXML = 'lbpcascade_frontalface_improved.xml';


%%%%%% Old input argument validation %%%%%%

%Copy of the argument block to function FacePulseRate that includes these flags in case any flags 
%to be converted to back to arguments:

%{

arguments
    
    %Input Arguments                                %Size  %Class  %Validation                        %Default Value
                                                                   %Function(s)
    % - Positional Argument:   
    Video_InputFile                                 (1, :) char    {mustBeNonempty}                   %note: also accepts type string
    
    % - Name-Value Arguments:
    NVArgs.FS                                       (1, 1) double  {mustBeNonempty, ...
                                                                    mustBeInteger}                    = -1 % -1 = flag to define default later
    NVArgs.StartTime                                (1, 1) double  {mustBeNonempty, ...
                                                                    mustBeNonnegative}                = 0 
    NVArgs.EndTime                                  (1, 1) double  {mustBeNonempty, ... 
                                                                    mustBeNumeric}                    = -1 % -1 = flag to define default later
    NVArgs.ROISkipFrameThreshold                    (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = .1667                                                                   
    NVArgs.ROIFace_BoundingBoxGrowthThreshold       (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = .35 
    NVArgs.ROIFace_BoundingBoxEnlargementFactor     (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = 1.55                                                                
    NVArgs.ROIFace_BoundingBoxGrowthRate            (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = .16
    NVArgs.ROIFacePrimaryXML                        (1, :) char    {mustBeNonempty}                   = 'lbpcascade_frontalface_improved.xml' %note: also accepts type string                                                         
    NVArgs.ROIFace_ChangeFactorROIPrimary           (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = 1.05 
    NVArgs.ROIFaceSecondary1TF                      (1, 1) logical {mustBeNonempty}                   = true 
    NVArgs.ROIFaceSecondary1XML                     (1, :) char    {mustBeNonempty}                   = 'haarcascade_profileface.xml' %note: also accepts type string
    NVArgs.ROIFace_ChangeFactorROISecondary1        (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = .95 
    NVArgs.ROIMinWidthProportionIncreaseSec1        (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = 1.1;
    NVArgs.ROIMinHeightProportionIncreaseSec1       (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = 1.1;    
    NVArgs.ROIFaceSecondary2TF                      (1, 1) logical {mustBeNonempty}                   = false
    NVArgs.ROIFaceSecondary2XML                     (1, :) char    {mustBeNonempty}                   = 'cuda_haarcascade_frontalface_alt_tree.xml' %note: also accepts type string
    NVArgs.ROIFace_ChangeFactorROISecondary2        (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = 1                                                               
    NVArgs.ROIMinWidthProportionIncreaseSec2        (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = 1.05;
    NVArgs.ROIMinHeightProportionIncreaseSec2       (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = 1.05;    
    NVArgs.ROIFaceSmoothingWindow                   (1, 1) double  {mustBeNonempty, ...
                                                                    mustBeInteger, ...
                                                                    mustBePositive}                   = 8                                                                    
    NVArgs.ROISkinTF                                (1, 1) logical {mustBeNonempty}                   = true
    NVArgs.ROISkinSkipFrameThreshold                (1, 1) double  {mustBeNonempty, ...
                                                                    mustBeNonnegative}                = .75                                                          
    NVArgs.ROISkin_BoundingBoxGrowthThreshold       (1, 1) double  {mustBeNonempty, ...
                                                                    mustBeInteger, ...
                                                                    mustBePositive, ...
                                                                    mustBeNonempty}                   = 1
    NVArgs.ROISkin_BoundingBoxGrowthFactor          (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = 1.2
    NVArgs.ROISkin_BoundingBoxEnlargementFactor     (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = 2.5
    NVArgs.ROISkinRegionMinSizeFactor               (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = 1
    NVArgs.ROISkinRegionProximityWeight             (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = 2
    NVArgs.ROISkinSmoothingWindow                   (1, 1) double  {mustBeNonempty, ...
                                                                    mustBeInteger, ...
                                                                    mustBePositive}                   = 50
    NVArgs.ROIMinWidthProportion                    (1, 1) double  {mustBeNonempty}                   = -1 %flag that none specified
    NVArgs.ROIMinHeightProportion                   (1, 1) double  {mustBeNonempty}                   = -1 %flag that none specified
    NVArgs.ROIWidthResizeFactor                     (1, 1) double  {mustBeNonempty, ...
                                                                    mustBePositive}                   = .90
    NVArgs.ROIHeightResizeFactor                    (1, 1) double  {mustBeNonempty, ...                                                                 
                                                                    mustBePositive}                   = 1.20
    NVArgs.ROIFinalSmoothingWindows                 (1, 2)         {mustBeNonempty, ...
                                                                    mustBeInteger, ...
                                                                    mustBePositive}                   = [11, 200] %note: argument block also accepts column vector, which will be automatically converted to row vector
    NVArgs.ROISpecifyByArgument                     (:, 5)         {mustBeNonempty, ...
                                                                    mustBeInteger}                    = repmat(-1, 1, 5) %flag that none specified      
    NVArgs.ROIIgnoreByArgument                      (:, 1)         {mustBeNonempty, ...
                                                                    mustBeInteger}                    = -1 %flag that none specified
    NVArgs.SkinClassifyRegionColorThresholds        (1, 3)         {mustBeNonempty, ...
                                                                    mustBePositive}                   = [.36, 9, 9.5] %note: argument block also accepts column vector, which will be automatically converted to row vector
    NVArgs.SkinClassifyRegionColorSDThreshold       (1, 1)         {mustBeNonempty, ...
                                                                    mustBeInteger, ...
                                                                    mustBePositive}                   = 9
    NVArgs.SkinSegmentTF                            (1, 1) logical {mustBeNonempty}                   = true
    NVArgs.SkinSegmentYCbCrThresholdsGeneric        (1, 7)         {mustBeNonempty, ...
                                                                    mustBePositive}                   = [40, 77, 131, 133, 173, .54, .98] %note: argument block also accepts column vector, which will be automatically converted to row vector
    NVArgs.SkinSegmentPixelMorphSize                (1, 1) double  {mustBeNonempty, ...
                                                                    mustBeInteger, ...
                                                                    mustBePositive}                   = 1                                          
    NVArgs.PulseRateTF                              (1, 1) logical {mustBeNonempty}                   = true
    NVArgs.PulseRateBlockTimestamps                 (1, :) double  {mustBePositive}                   = [] %note: argument block also accepts column vector, which will be automatically converted to row vector
    NVArgs.PulseRateControlLuminance                (1, 1) char    {mustBeNonempty}                   = 'F' %note: also accepts strings
    NVArgs.PulseRateWindowDurationSec               (1, 1) double  {mustBeNonempty, ...
                                                                    mustBeInteger, ...
                                                                    mustBePositive, ...
                                                                    mustBeGreaterThanOrEqual( ...
                                                                    NVArgs.PulseRateWindowDurationSec, ...
                                                                    2)}                               = 90 %>= 2 sec for compatibility with function CHROM_DEHAAN   
    NVArgs.PulseRateExternallyMeasured              (1, :)                                            = [] %note: argument block also accepts column vector, which will be automatically converted to row vector
    NVArgs.WriteCSV_TF                              (1, 1) logical {mustBeNonempty}                   = true
    NVArgs.WriteCSVByFrameName                      (1, :) char    {mustBeNonempty}                   = "DefineDefaultLater" %flag to define default later; %note: also accepts type string               
    NVArgs.WriteCSVByWindowName                     (1, :) char    {mustBeNonempty}                   = "DefineDefaultLater" %flag to define default later; %note: also accepts type string               
    NVArgs.WriteVideoTF                             (1, 1) logical {mustBeNonempty}                   = true
    NVArgs.WriteVideoNoSoundTF                      (1, 1) logical {mustBeNonempty}                   = false
    NVArgs.WriteVideoName                           (1, :) char    {mustBeNonempty}                   = "DefineDefaultLater" %flag to define default later; %note: also accepts type string
    NVArgs.WriteVideoShowSkinSegmentTF              (1, 1) logical {mustBeNonempty}                   = true
    NVArgs.WriteVideoShowROISkinDiagnosisTF         (1, 1) logical {mustBeNonempty}                   = true 
    NVArgs.WriteVideoShowLegendTF                   (1, 1) logical {mustBeNonempty}                   = true
    NVArgs.UseCompiledFunctionsTF                   (1, 1) logical {mustBeNonempty}                   = true
end

%}


end %end function

