function [VideoReadConfig, SkinSegmentConfig, SkinSegmentMasks, ROIGeneralConfig,  ...
          FaceDetectConfig, SkinDetectConfig, ROI, ROIForBBox, ROIDiagnostic, HasROI_TF, ...
          ROIMatchSizeData, PulseRateConfigAndData, OutputConfig, FunctionStartTime, ...
          UseCompiledFunctionsTF] = ...                      
              ValidateAndConfigure(Video_InputFile, NVArgs)
%ValidateAndConfigure   Validate inputs and setup configuration structs.
%
%    Helper function to function FacePulseRate.
%
%
%    Description
%    -----------
%
%    Validate the input arguments to function FacePulseRate, assign variables to be used across
%    functions, and assign configuration structs corresponding to groups of related operations.    
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%Function start message:

%Extract file name and extension from input video path
[~, fileName, fileExt] = fileparts(Video_InputFile);

name = [char(fileName), char(fileExt)];

%Notification message
message = ['\n\nConducting operations on file "', name, '".']; 

%Display notification message          
fprintf(message);

%Display message immediately
drawnow(); 
        

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Move name-value arguments out of struct for ease of use %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

StartTime                                = NVArgs.StartTime; 
EndTime                                  = NVArgs.EndTime;

%ROI:

ROISpecifyByArgument                     = NVArgs.ROISpecifyByArgument;
ROIIgnoreByArgument                      = NVArgs.ROIIgnoreByArgument;

ROIMinWidthProportion                    = NVArgs.ROIMinWidthProportion; 
ROIMinHeightProportion                   = NVArgs.ROIMinHeightProportion;

ROIWidthResizeFactor                     = NVArgs.ROIWidthResizeFactor; 
ROIHeightResizeFactor                    = NVArgs.ROIHeightResizeFactor;

ProfileFaceDetectorTF                    = NVArgs.ProfileFaceDetectorTF;

DetectVerifyPercentilesYCbCrH            = NVArgs.DetectVerifyPercentilesYCbCrH;
DetectVerifyPercentilesS                 = NVArgs.DetectVerifyPercentilesS;

%Skin segmentation:

SkinSegmentThresholdsGenericYCbCr        = NVArgs.SkinSegmentThresholdsGenericYCbCr;
SkinSegmentThresholdsGenericHSV          = NVArgs.SkinSegmentThresholdsGenericHSV;
SkinSegmentSeverityFactor                = NVArgs.SkinSegmentSeverityFactor;
OversegmentationCheckTF                  = NVArgs.OversegmentationCheckTF;

%Pulse rate:

PulseRateBlockTimestamps                 = NVArgs.PulseRateBlockTimestamps;
PulseRateControlLuminance                = NVArgs.PulseRateControlLuminance;
PulseRateWindowDurationSec               = NVArgs.PulseRateWindowDurationSec;
PulseRateExternallyMeasured              = NVArgs.PulseRateExternallyMeasured;

 
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Internal Development Flags %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Assign internal flags that control various settings. These flags are intended to be used for
%internal development. The annotations on the output video can help guide the fine-tuning of many 
%of these flags. See file WriteFaceVideo.m for a description on how they can be used.

%Note: function ValidateAndConfigure_InternalFlags is a custom function located within folder
%'FacePulseRate'.
[ROIFacePrimaryXML, ...
 PulseRateTF, ...
 WriteVideoDetailedDiagnosticsTF, ...
 UseCompiledFunctionsTF] = ...
    ValidateAndConfigure_InternalFlags();


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Defaults and Validation %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Check whether required toolboxes are installed and whether function arguments have been entered 
%correctly. If not, end function and display error message on command window.

%Note: 'ValidateAndConfigure_Validate' is a custom function located within folder 'FacePulseRate'.
[Video_InputFile, EndTimeSpecified, EndTime, PulseRateControlLuminance, ...
 UseCompiledFunctionsTF] = ...
    ValidateAndConfigure_Validate(Video_InputFile, StartTime, EndTime, ROISpecifyByArgument, ...
        ROIIgnoreByArgument, PulseRateTF, PulseRateWindowDurationSec, ...                 
        PulseRateExternallyMeasured, PulseRateBlockTimestamps, PulseRateControlLuminance, ...                                   
        SkinSegmentThresholdsGenericYCbCr, SkinSegmentThresholdsGenericHSV, ...
        DetectVerifyPercentilesYCbCrH, DetectVerifyPercentilesS, UseCompiledFunctionsTF);                
                                               
     
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Assign Settings and Variables %%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%% Start Function Timer %%%%%%

%For timing elapsed processing time of function

%Restart timer
tic; 

%Start timer and save variable for display at end of function
FunctionStartTime = tic; 


%%%%%% Setup video reading configuration struct %%%%%%

%Note: 'VideoReadConfig_Setup' is a custom function located within folder 'FacePulseRate'.
VideoReadConfig = VideoReadConfig_Setup(Video_InputFile, StartTime, EndTimeSpecified, EndTime);       


%%%%%% Setup general ROI configurations %%%%%%

%Note: 'ROIGeneralConfig_Setup' is a custom function located within folder 'FacePulseRate'.
ROIGeneralConfig = ...
    ROIGeneralConfig_Setup(ROIMinWidthProportion, ROIMinHeightProportion, ROIWidthResizeFactor, ...
        ROIHeightResizeFactor, VideoReadConfig, ROIFacePrimaryXML, ROISpecifyByArgument, ...
        ROIIgnoreByArgument, UseCompiledFunctionsTF);
 

%%%%%% Setup ROI variables %%%%%%

%Note: 'ROIMeans_ROIVarsSetup' is a custom function located within folder 'FacePulseRate'.
[ROI, ROIForBBox, ROIDiagnostic, HasROI_TF, ROIMatchSizeData] = ...
    ROIMeans_ROIVarsSetup(VideoReadConfig, ROIGeneralConfig); 
 
   
%%%%%% Setup skin-segmentation configuration struct %%%%%%

%Setup struct to hold configurations for skin segmentation.

%Note: 'SkinSegment_ConfigSetup' is a custom function located within folder 'FacePulseRate'.
[SkinSegmentConfig, SkinSegmentMasks] = ...
    SkinSegment_ConfigSetup(VideoReadConfig, SkinSegmentThresholdsGenericYCbCr, ...
        SkinSegmentThresholdsGenericHSV, DetectVerifyPercentilesYCbCrH, ...
        DetectVerifyPercentilesS, SkinSegmentSeverityFactor, OversegmentationCheckTF, ...
        ROIGeneralConfig, UseCompiledFunctionsTF);
           
    
%%%%%% Setup skin-detection algorithm configuration struct and variables %%%%%%
    
%Note: 'SkinDetect_ConfigSetup' is a custom function located within folder 'FacePulseRate'.
[SkinDetectConfig, ROIDiagnostic] = ...
    SkinDetect_ConfigSetup(ROI, UseCompiledFunctionsTF, SkinSegmentConfig, ROIGeneralConfig, ...       
         VideoReadConfig, ROIDiagnostic);
    
    
%%%%%% Setup face-detection algorithm configuration struct %%%%%%

%Note: 'FaceDetect_ConfigSetup' is a custom function located within folder 'FacePulseRate'.
FaceDetectConfig = ...
    FaceDetect_ConfigSetup(ROIFacePrimaryXML, ProfileFaceDetectorTF, SkinDetectConfig, ...
        ROIGeneralConfig, VideoReadConfig);            
                   
      
%%%%%% Setup pulse rate configuration and data struct %%%%%%

%Setup struct to hold configurations and data for pulse rate operations.

%Note: 'PulseRate_DataSetup' is a custom function located within folder 'FacePulseRate'.
PulseRateConfigAndData = ...
    PulseRate_DataSetup(PulseRateTF, PulseRateWindowDurationSec, PulseRateExternallyMeasured, ...
        PulseRateControlLuminance, PulseRateBlockTimestamps, SkinSegmentConfig, VideoReadConfig);        

    
%%%%%% Setup output files configuration struct %%%%%%

%Settings and validation for output video and output CSV files.

%Note: 'OutputConfig_Setup' is a custom function located within folder 'FacePulseRate'.
OutputConfig = ...
    OutputConfig_Setup(Video_InputFile, WriteVideoDetailedDiagnosticsTF, SkinSegmentConfig, ...
        SkinDetectConfig);    
   
    
end %end function

