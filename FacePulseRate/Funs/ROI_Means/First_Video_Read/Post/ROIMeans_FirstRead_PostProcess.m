function [VideoReadConfig, ROI, HasROI_TF, ROIDiagnostic, SkinSegmentConfig, ...
          PulseRateConfigAndData, ROIGeneralConfig, DataForSkinDetection, ...
          DataForTailoredSkinSegmentation] = ...
              ROIMeans_FirstRead_PostProcess(HasROI_TF, VideoReadConfig, ROI, ROIDiagnostic, ...
                  SkinSegmentConfig, SkinDetectConfig, ROIGeneralConfig, ...
                  PulseRateConfigAndData, DataForSkinDetection, ...
                  DataForTailoredSkinSegmentation) 
%ROIMeans_FirstRead_PostProcess   Conduct post-processing operations after the first-read 
%                                 operations have read all frames to be processed.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function ROIMeans_FirstRead.
%
%
%    Description
%    -----------
%
%    Conduct post-processing operations after the first-read operations have read all frames to be 
%    processed. These operations include displaying various warnings and trimming the length of
%    some variables.                                
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% Display warning if no face-detection algorithm detections were made %%%%%%

if ~ ( any(HasROI_TF.FacePrimary)    || ...
       any(HasROI_TF.FaceSecondary1) || ...
       any(HasROI_TF.FaceSecondary2) ...
     )
     
    
    %Display warning
    warning( ...
        ['A face was not detected by the face-detection algorithms in any frames. ' ... 
         'Function FacePulseRate will continue but with reduced functionality.'] ...
     );  
         
    %Display message immediately      
    drawnow();      
end     


%%%%%% Trim variables %%%%%%

%Now that the number of timestamps are known because all frames have been read, the data can be 
%trimmed up to EndTime.

%Note: 'ROIMeans_FirstRead_Trim' is a custom function located within folder 'FacePulseRate'.
[VideoReadConfig, ROI, HasROI_TF, ROIDiagnostic, SkinSegmentConfig, PulseRateConfigAndData, ...
 ROIGeneralConfig, DataForSkinDetection, DataForTailoredSkinSegmentation] = ...
    ROIMeans_FirstRead_Trim(VideoReadConfig, ROI, HasROI_TF, ROIDiagnostic, ...
        SkinSegmentConfig, ROIGeneralConfig, PulseRateConfigAndData, DataForSkinDetection, ...
        DataForTailoredSkinSegmentation);

    
%%%%%% Display warning if thresholds not set for tailored skin-segmentation %%%%%%    
 
%If number of skin-color samples collected is lower than threshold
if ~ SkinSegmentConfig.Args.SkinColorSamples_NThresholdPassedTF
    
    %Display warning message on command window     
    warning( ...
        ['Fewer than ', ...
         num2str(SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold), ...
         ' skin-color samples collected. "Generic" skin segmentation will be used in place of', ... 
         ' "tailored". This will result in more lenient skin-segmentation and ROI-detection', ...
         ' verification. Consider using a longer video length.'] ...
    );
         
    %Display message immediately
    drawnow();            
end 
 

%%%%%% Display warning if thresholds not set for the skin-detection algorithm %%%%%%

%If number of skin-color samples collected is lower than threshold
if ~ SkinDetectConfig.Thresholds.SkinColorSamples_NThresholdPassedTF

    %Display warning message on command window
    warning( ...
        ['Fewer than ', ...
         num2str(SkinDetectConfig.Thresholds.SkinColorSamples_NThreshold), ...
         ' skin-color samples collected. ROI detection will not be conducted with the', ... 
         ' skin-detection algorithm. This will result in more lenient skin-segmentation and', ...
         ' ROI-detection verification. Consider using a longer video length.'] ...
    ); 
         
    %Display message immediately
    drawnow();        
end


end %end function

