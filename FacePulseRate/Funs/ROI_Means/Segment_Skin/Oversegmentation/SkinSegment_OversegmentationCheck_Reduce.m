function [ROIGeneralConfig, VideoReadConfig, ROI, ROIDiagnostic, SkinSegmentConfig, ...
          SkinSegmentMasks, PulseRateConfigAndData, SkinDetectConfig, HasROI_TF, ...
          ROIMatchSizeData] = ...
              SkinSegment_OversegmentationCheck_Reduce(MakeMorphLessSevereTF, ...
                  MakeColorThresLessSevereTF,MorphCloseSEMediumWidth_Tuned, ... 
                  MorphCloseSELargeWidth_Tuned, SkinSegmentSeverityFactor, videoFReader, ...
                  ROIGeneralConfig, FaceDetectConfig, VideoReadConfig, SkinSegmentConfig, ...
                   SkinSegmentMasks, PulseRateConfigAndData, SkinDetectConfig, OutputConfig)                                                          
%SkinSegment_OversegmentationCheck_Reduce   Apply the reductions of the severity of 
%                                           skin-segmentation assigned by function
%                                           SkinSegment_OversegmentationCheck_Reduce.
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead.
%    
%
%    Description
%    -----------
%
%    Apply the reductions of the severity of skin-segmentation settings assigned by function
%    SkinSegment_OversegmentationCheck. The settings adjusted include those for the morphlogical
%    close operations and those for the pixel-color thresholds (for a discussion of the settings  
%    assigned, see function SkinSegment_OversegmentationCheck). Then, in order to have the 
%    modifications to settings apply to all frames, start function ROIMeans_FirstRead from the  
%    beginning by calling it. Some settings previously assigned within ROIMeans_FirstRead, such as 
%    those regarding the modified skin-segmentation settings, will not reassigned during the call, 
%    but most other settings and variables will be reassigned.     
%
%    Note: As ROIMeans_FirstRead calls the current function, the call to ROIMeans_FirstRead here is 
%    recursive. 
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.  


%%%%%% Notification message %%%%%%

%Flag to reduce the severity of the morphological close
if MakeMorphLessSevereTF
    
    MorphText = '\n        - SkinSegmentSeverityFactor';
    
else
    
    MorphText = [];   
end

%Flag to reduce the severity of the pixel-color thresholds
if MakeColorThresLessSevereTF 
 
    ColorThres = ... 
        ['\n        - SkinSegmentThresholdsGenericYCbCr', ...
         '\n        - SkinSegmentThresholdsGenericHSV', ...
         '\n        - DetectVerifyPercentilesYCbCrH', ...
         '\n        - DetectVerifyPercentilesS'];
 
else
    
    ColorThres = [];   
end 

   %Notification message    
    message = ...
        ['\n', ...
         '\n       Skin-segmentation settings recalibrated due to detected', ...
         '\n       over-segmentation. The values of the following arguments', ...
         '\n       were modified:', ...
          ['       ', MorphText, ColorThres], ...
         '\n       The first-read processing will start over to apply the', ...
         '\n       modifications to all frames.\n'];     
    
    %Display message
    fprintf(message);

    %Display message immediately
    drawnow(); 


%%%%%% Reduce the severity of the morphological close %%%%%%
    
%For details, see the description in function SkinSegment_OversegmentationCheck.

%Assign some variables to struct. This allows the variables to maintain persistence across 
%recursive calls.

%Flag to reduce the severity of the morphological close
if MakeMorphLessSevereTF
     
    %Scalar; type double.
    SkinSegmentConfig.SkinSegmentSeverityFactor = SkinSegmentSeverityFactor;

    %Scalars; type int16.
    SkinSegmentConfig.Args.MorphCloseSEMediumWidth_Tuned = MorphCloseSEMediumWidth_Tuned;
    SkinSegmentConfig.Args.MorphCloseSELargeWidth_Tuned  = MorphCloseSELargeWidth_Tuned;        
    
    %Increment number of times the severity has been reduced
    %This value will be checked against the maximum number permitted on subsequent calls to  
    %function SkinSegment_OversegmentationCheck.
    %Scalar; type int32.
    %Note: this value is also displayed on the output video.
    SkinSegmentConfig.OverSegmentedCheck.NMorphReductions = ...
        SkinSegmentConfig.OverSegmentedCheck.NMorphReductions + 1;       
end


%%%%%% Reduce the severity of the pixel-color thresholds %%%%%%

%For details, see the description in function SkinSegment_OversegmentationCheck.

%Assign some variables to struct SkinSegmentConfig. This allows the variables to maintain  
%persistence across recursive calls to function ROIMeans_FirstRead.

%Flag to reduce the severity of the pixel-color thresholds
if MakeColorThresLessSevereTF 
    
    %Flag that too much darkness is present according to the darkness threshold 
    %This is an indication that pixel-color thresholds should be made less severe. 
    SkinSegmentConfig.OverSegmentedCheck.BelowDarknessThresholdTF = true;               
    
    %Note: the tailored thresholds are updated periodically by function SkinSegment_SetThresholds.
    %However, SkinSegment_SetThresholds will not modify the pixel-color thresholds that are 
    %modified here. Specifically, it will not modify the thresholds if flag 
    %SkinSegmentConfig.OverSegmentedCheck.BelowDarknessThresholdTF is true.

    %Set generic YCbCr and HSV thresholds:
    
    TailoredTF = false;
    
    %Local function.
    [SkinSegmentConfig.Args.YCbCrThresholdsGeneric, ...
     SkinSegmentConfig.Args.HSThresholdsGeneric] = ...
        SetFixedThresholds(TailoredTF, SkinSegmentConfig.Args.YCbCrThresholdsGeneric, ...
            SkinSegmentConfig.Args.HSThresholdsGeneric, SkinSegmentConfig);   
    
    %Set tailored low-severity YCbCr and HSV thresholds:
    
    TailoredTF = true;    
    
    %Local function.
    [SkinSegmentConfig.Args.YCbCrThresholdsTailored, ...
     SkinSegmentConfig.Args.HSThresholdsTailored] = ...
        SetFixedThresholds(TailoredTF, SkinSegmentConfig.Args.YCbCrThresholdsTailored, ...
            SkinSegmentConfig.Args.HSThresholdsTailored, SkinSegmentConfig); 
    
    %Set tailored high-severity YCbCr and HSV thresholds:
    
    TailoredTF = true;     
    
    %Local function.    
    [SkinSegmentConfig.Args.YCbCrThresholdsTailored_Sev, ...
     SkinSegmentConfig.Args.HSThresholdsTailored_Sev] = ...
        SetFixedThresholds(TailoredTF, SkinSegmentConfig.Args.YCbCrThresholdsTailored_Sev, ...
            SkinSegmentConfig.Args.HSThresholdsTailored_Sev, SkinSegmentConfig);
    
    %Flag that the pixel-color thresholds have been made less severe
    %The pixel-color thresholds can only be made less severe once, so this flag will indicate that 
    %they do not need to be adjusted again.
    SkinSegmentConfig.OverSegmentedCheck.PixelColorsAdjustedTF = true;         
end


%%%%%% Reinitialize some variables previously set during function ROIMeans_FirstRead %%%%%%

%For proper functioning of function ROIMeans_FirstRead, the following variables need to be reset.

%If video reader VideoReadConfig.UseVisionTF is use
if VideoReadConfig.UseVisionTF

    %Reset vision.VideoFileReader
    release(videoFReader);
end

ROIGeneralConfig.ROIMeansOperationsReadyFirstReadTF = false;
SkinSegmentConfig.TailoredData.OpsReadyTF           = false;
SkinDetectConfig.Thresholds.SetTF                   = false;
SkinDetectConfig.SkinDetectionReadyTF               = false;

%Note: ROIMeans_ROIVarsSetup is a custom function located within folder 'FacePulseRate'.
[ROI, ROIForBBox, ROIDiagnostic, HasROI_TF, ROIMatchSizeData] = ...
    ROIMeans_ROIVarsSetup(VideoReadConfig, ROIGeneralConfig);        

%Insert the skin-detection diagnostic structure
%Note: SkinDetect_PreallocateDiagnosticData is a custom function located within folder 
%'FacePulseRate'.
ROIDiagnostic.ROISkin = SkinDetect_PreallocateDiagnosticData(ROI, SkinDetectConfig);


%%%%%% Recursively call function ROIMeans_FirstRead to start over first read %%%%%%          
     
%Note: if the implementation is changed so that a recursive call is not made, the variables 
%assigned in section "Variables for the oversegmentation check" of function ROIMeans_FirstRead 
%(near top) should be copied and pasted (not moved) right after the function call to 
%SkinSegment_OversegmentationCheck_Reduce. This will reinitialize and restart counters as used by
%function SkinSegment_OversegmentationCheck as intended (see function 
%SkinSegment_OversegmentationCheck).

%Flag that function ROIMeans_FirstRead will be called recursively
ROIGeneralConfig.RecursiveTF = true;

%Note: ROIMeans_FirstRead is a custom function located within folder 'FacePulseRate'.
[ROIGeneralConfig, VideoReadConfig, ROI, ROIDiagnostic, SkinSegmentConfig, SkinSegmentMasks, ...
 PulseRateConfigAndData, SkinDetectConfig, HasROI_TF, ROIMatchSizeData] = ...           
    ROIMeans_FirstRead(ROIGeneralConfig, FaceDetectConfig, VideoReadConfig, ROI, ROIForBBox,...
        ROIDiagnostic, SkinSegmentConfig, SkinSegmentMasks, PulseRateConfigAndData, HasROI_TF, ...  
        ROIMatchSizeData, SkinDetectConfig, OutputConfig);
         
                        
end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function [AdjustedThresholdsYCbCr, AdjustedThresholdsHSV] = ...
              SetFixedThresholds(TailoredTF, ThresholdsYCbCr, ThresholdsHSV, SkinSegmentConfig)                            
%SetFixedThresholds   Set fixed thresholds values.
%
%    Description:
%
%    Set fixed thresholds values. These values will be set if 
%    SkinSegmentConfig.OverSegmentedCheck.BelowDarknessThresholdTF is true. Set the values 
%    according to SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo. If an element of
%    SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo is NaN, there is no specified fixed 
%    value for the corresponding threshold, so the threshold will be returned unmodified.
%    
%    For a description of why these thresholds are set as fixed, see function 
%    SkinSegment_OversegmentationCheck.  


%%%%%% Set fixed values for HSV tailored pixel-color thresholds %%%%%%

if TailoredTF

    %Preallocate
    AdjustedThresholdsHSV = zeros(1, 3, 'single');

    %H maximum    
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(8) )

        AdjustedThresholdsHSV(1) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(8);

    else

        AdjustedThresholdsHSV(1) = ThresholdsHSV(1);    
    end

    %S minimum   
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(9) )

        AdjustedThresholdsHSV(2) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(9);

    else

        AdjustedThresholdsHSV(2) = ThresholdsHSV(2);     
    end

    %S maximum
    AdjustedThresholdsHSV(3) = ThresholdsHSV(3);


%%%%%% Set fixed values for HSV generic pixel-color thresholds %%%%%%

else

    %Preallocate
    AdjustedThresholdsHSV = zeros(1, 2, 'single');
    
    %H maximum    
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(8) )

        AdjustedThresholdsHSV(1) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(8);

    else

        AdjustedThresholdsHSV(1) = ThresholdsHSV(1);    
    end

    %S minimum   
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(9) )

        AdjustedThresholdsHSV(2) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(9);

    else

        AdjustedThresholdsHSV(2) = ThresholdsHSV(2);     
    end    
end


%%%%%% Set fixed values for YCbCr tailored pixel-color thresholds %%%%%%

if TailoredTF
    
    %Preallocate
    AdjustedThresholdsYCbCr = zeros(1, 8, 'single');    
    
    %Y-minimum
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(1) )

        AdjustedThresholdsYCbCr(1) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(1);
        
    else
    
        AdjustedThresholdsYCbCr(1) = ThresholdsYCbCr(1);         
    end

    %Y-maximum
    AdjustedThresholdsYCbCr(2) = ThresholdsYCbCr(2);
    
    %Cb-minimum
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(2) )

        AdjustedThresholdsYCbCr(3) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(2);
        
    else
    
        AdjustedThresholdsYCbCr(3) = ThresholdsYCbCr(3);                   
    end    

    %Cb-maximum    
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(3) )

        AdjustedThresholdsYCbCr(4) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(3);
        
    else
    
        AdjustedThresholdsYCbCr(4) = ThresholdsYCbCr(4);          
    end    

    %Cr-minimum     
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(4) )

        AdjustedThresholdsYCbCr(5) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(4);
        
    else
    
        AdjustedThresholdsYCbCr(5) = ThresholdsYCbCr(5);          
    end        

    %Cr-maximum     
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(5) )

        AdjustedThresholdsYCbCr(6) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(5);
        
    else
    
        AdjustedThresholdsYCbCr(6) = ThresholdsYCbCr(6);          
    end    

    %Cb-to-Cr minimum    
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(6) )

        AdjustedThresholdsYCbCr(7) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(6);
        
    else
    
        AdjustedThresholdsYCbCr(7) = ThresholdsYCbCr(7);          
    end    

    %Cb-to-Cr maximum    
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(7) )

        AdjustedThresholdsYCbCr(8) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(7);
        
    else
    
        AdjustedThresholdsYCbCr(8) = ThresholdsYCbCr(8);          
    end    
 
    
%%%%%% Set fixed values for YCbCr generic pixel-color thresholds %%%%%%

else
 
    %Preallocate
    AdjustedThresholdsYCbCr = zeros(1, 7, 'single');     
    
    %Y-minimum
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(1) )

        AdjustedThresholdsYCbCr(1) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(1);
        
    else
    
        AdjustedThresholdsYCbCr(1) = ThresholdsYCbCr(1);          
    end    

    %Cb-minimum
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(2) )

        AdjustedThresholdsYCbCr(2) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(2);
        
    else
    
        AdjustedThresholdsYCbCr(2) = ThresholdsYCbCr(2);          
    end      

    %Cb-maximum    
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(3) )

        AdjustedThresholdsYCbCr(3) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(3);
        
    else
    
        AdjustedThresholdsYCbCr(3) = ThresholdsYCbCr(3);          
    end      

    %Cr-minimum     
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(4) )

        AdjustedThresholdsYCbCr(4) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(4);
        
    else
    
        AdjustedThresholdsYCbCr(4) = ThresholdsYCbCr(4);          
    end      

    %Cr-maximum     
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(5) )

        AdjustedThresholdsYCbCr(5) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(5);
        
    else
    
        AdjustedThresholdsYCbCr(5) = ThresholdsYCbCr(5);          
    end  

    %Cb-to-Cr minimum    
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(6) )

        AdjustedThresholdsYCbCr(6) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(6);
        
    else
    
        AdjustedThresholdsYCbCr(6) = ThresholdsYCbCr(6);          
    end  

    %Cb-to-Cr maximum    
    if ~ isnan( SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(7) )

        AdjustedThresholdsYCbCr(7) = ...
            SkinSegmentConfig.OverSegmentedCheck.ColorThresAdjustTo(7);
        
    else
    
        AdjustedThresholdsYCbCr(7) = ThresholdsYCbCr(7);          
    end     
end


end %end local function

