function text = ...
             WriteFaceVideo_LegendSetupText(LegendVersion1NotAssignedTF, RegionNThreshold, ...
                 HasROI_TF, SkinSegmentConfig, FaceDetectConfig, SkinDetectConfig, ...
                 PulseRateConfigAndData, OutputConfig)
%WriteFaceVideo_LegendSetupText    Prepare text for legend on output video.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_AnnotationSetup.
%    
%
%    Description
%    -----------
%
%    Prepare text for legend on output video.
%
%    To indicate a line(s) of text, wrap line(s) in curly brackets.
%    To indicate a paragraph, which will result in additional space, wrap lines of text within the
%    paragraph in an additional set curly brackets.
%
%    The legend text differs depending on flag OutputConfig.WriteVideoDetailedDiagnosticsTF. For 
%    details and the rationale on these differences, see the description in function 
%    WriteFaceVideo.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Text section 1: ROI information %%%%%%

%See functions WriteFaceVideo_ROIBoxRowsCols and WriteFaceVideo_ROIAnnotation, which insert the 
%annotations that correspond to this part of the legend.

%Section title:

%Spaces on left for center-jusification.
textROITitle = ...
    { ...
        {'                    Region of Interest (ROI)'} ... 
    };

%%%%%% --- Text subsection: ROI Methods %%%%%%

%Make list of enabled algorithms
%Note: WriteFaceVideo_LegendSetupAlgList is a custom function located in folder 'FacePulseRate'.
[AlgorithmsEnabledList, AlgorithmsEnabledList_OnlyFaceAlgs] = ...
    WriteFaceVideo_LegendSetupAlgList(FaceDetectConfig, SkinDetectConfig, OutputConfig);

%Subsection title:

%Line should appear left-justified (no leading spaces).
textAlgsTitle = ...
    { ...
        {'ROI Method'} ... 
    };

%Subsection body:

%Lines within paragraph should appear left-justified (no leading spaces). 

textAlgsEnabled = ...
    { ...
        { ... 
         'Detection algorithms', ...
        ['enabled:             ', AlgorithmsEnabledList], ...  
        '  ', ... new line before next subsection
        } ...
    };

%If detailed diagnostics enabled
%Note: for text differences between the detailed and non-detailed (default) display options, see  
%the description in function WriteFaceVideo.
if OutputConfig.WriteVideoDetailedDiagnosticsTF
    
    %Subsection body:

    %Lines within paragraph should appear left-justified (no leading spaces). 
    
    textAlgs = ... 
        { ...
            {
             'Pri.:                Primary face-detection algorithm.', ...
             'Sec.#1:              Secondary face-detection algorithm #1.', ...
             'Sec.#2:              Secondary face-detection algorithm #2.', ...
             'Skin:                Skin-detection algorithm.' ...
             'Skipped:             Detection algs. skipped for efficiency.', ...
             'Interpolated:        Interpolated because skipped or detection', ... 
             '                     not made.' ...
            } ...
        };
    
%If detailed diagnostics not enabled
else
      
    %Subsection body:

    %Lines within paragraph should appear left-justified (no leading spaces). 
    
    textAlgs = ... 
         { ...
            { ...        
             'Frontal.:            Frontal face-detection algorithm.', ...
             'Profile:             Profile face-detection algorithm.', ...
             'Skin:                Skin-detection algorithm.' ...
             'Interpolated:        Interpolated for efficiency or', ... i.e., skipped for efficiency
             '                     because detection not made.' ...
             'Ignored:             ROI ignored by argument.', ...
             'Assigned:            ROI assigned by argument.' ...
            } ...
        };    
end

%%%%%% --- Text subsection: Bounding Boxes %%%%%%

%If detailed diagnostics enabled
%Note: for text differences between the detailed and non-detailed (default) display options, see  
%the description in function WriteFaceVideo.
if OutputConfig.WriteVideoDetailedDiagnosticsTF

    %Subsection title:
    
    %Line should appear left-justified (no leading spaces).
    
    textBBoxTitle = ...
        { ...
            {'Bounding Boxes for Algorithm Scanning'} ... 
        };

    %Subsection body:
    
    %Lines within paragraph should appear left-justified (no leading spaces).
    
    textBBox = ...
        { ...
            {'Purple:              Face algorithm', ... 
             'Gray:                Skin algorithm', ... 
            } ...
        };

%If detailed diagnostics not enabled    
else
    
    textBBoxTitle = {};
    textBBox      = {};
end

%%%%%% --- Text subsection: Detections, detection attempts, and modifications %%%%%%

%If detailed diagnostics enabled
if OutputConfig.WriteVideoDetailedDiagnosticsTF
    
    %Subsection title:

    %Line should appear left-justified (no leading spaces).
    textDATitle = ...
        { ...
            {'ROI Detections and Modifications'} ... 
        }; 
    
    %Subsection body:

    %Lines within paragraph should appear left-justified (no leading spaces).    
    
    textDA = ...
        { ...
            { ...
             'Black box:           ROI: Detection.', ... 
             'Blue box:            ROI: Interpolated or modified.', ... 
             'Light blue box:      ROI: Final. Frame-by-frame smoothing and', ...
             '                     size adjustments.', ...
             'ROI info:            "ROI: <determined ROI> | <detection attemps>"', ...
             '                     Detection notes:', ...
             '                     [R]  = An ROI-detection attempt rejected as', ... 
             '                            ROI may not contain skin.', ...
             '                     [NR] = Regions not available for', ...
             '                            skin-detection algorithm.', ...
             'Half rectangles:     Minimum accepted size of ROIs from', ...
            ['                     face-detection algorithm(s): ', AlgorithmsEnabledList_OnlyFaceAlgs] ...
            } ...
        };
    
%If detailed diagnostics not enabled    
else
    
    %Subsection title:

    %Line should appear left-justified (no leading spaces).
    textDATitle = ...
        { ...
            {'ROI Box and Status'} ... 
        }; 
    
    %Subsection body:

    %Lines within paragraph should appear left-justified (no leading spaces).    
    
    textDA = ...
        { ...
            { ...
             'Light blue box:      ROI', ... 
             'ROI info:            "ROI: <determined ROI> | <detection notes>"', ... 
             '                     Detection notes:', ...
             '                     [R]  = An ROI-detection attempt rejected as', ... 
             '                            ROI may not contain skin.', ...
             '                     [NR] = Regions not available for', ...
             '                            skin-detection algorithm.' ...
             'Half rectangles:     Minimum accepted size of ROIs from', ...
            ['                     face-detection algorithm(s): ', AlgorithmsEnabledList_OnlyFaceAlgs] ...
            } ...
        };    
end

%Face-detection algorithm detections-to-attempts proportion(s):

%If detailed diagnostics enabled
if OutputConfig.WriteVideoDetailedDiagnosticsTF

    %Subsection body (cont.):
    
    %Lines within paragraph should appear left-justified (no leading spaces).
    
    %Calculate detections-to-attempts proportion(s) for face-detection algorithm(s). See the
    %description in function WriteFaceVideo for its interpretation.    
    %Note: WriteFaceVideo_LegendSetupTextProportions is a custom function located within folder
    %'FacePulseRate'.
    [DAProportion_Pri, DAProportion_Sec1, DAProportion_Sec2] = ...
        WriteFaceVideo_LegendSetupTextProportions(HasROI_TF, FaceDetectConfig);       
    
    textDAProportion = ...
        { ...
            { ... 
             'Face algorithm detections-to-attempts proportion:', ...
             ['Pri.: ', DAProportion_Pri, ',  Sec.#1: ', DAProportion_Sec1, ',  Sec.#2: ', ...
              DAProportion_Sec2] ...     
            } ...
        };

%If detailed diagnostics not enabled    
else
  
    textDAProportion = {};  
end

%Concatenate text cell arrays:

text = ...
    [textROITitle, textAlgsTitle, textAlgsEnabled, textAlgs, textBBoxTitle, textBBox, ... 
     textDATitle, textDA, textDAProportion];
        
%%%%%% --- Text subsection: Skin-detection algorithm %%%%%%

%See function WriteFaceVideo_SkinDetectDiagnosis, which inserts the annotations that 
%correspond to this part of the legend.

%If displaying skin-detection algorithm diagnosis annotations is enabled and 
%Note: if OutputConfig.WriteVideoDetailedDiagnosticsTF is false, then 
%OutputConfig.WriteVideoShowROISkinDiagnosisTF will be false.
if OutputConfig.WriteVideoShowROISkinDiagnosisTF 

    %Subsection title:

    %Line should appear left-justified (no leading spaces).

    textROISkinTitle = ...
        { ...
            {'ROI from Skin-Detection Algorithm'} 
        };   
    
    %If at least one skin-detection algorithm detection was made across all frames 
    if any(HasROI_TF.Skin)

        %Subsection text:

        %Lines within paragraph should appear left-justified (no leading spaces).

        %Calculate skin-detection algorithm metrics for legend. For interpretation, see function
        %SkinDetect.
        %Note: WriteFaceVideo_LegendSetupTextSkinDetect is a custom function located within folder
        %'FacePulseRate'.
        [N_Min, CrSD_Max, P_Min, CbZ_MinMax, CrZ_MinMax] = ...
            WriteFaceVideo_LegendSetupTextSkinDetect(LegendVersion1NotAssignedTF, ...
                RegionNThreshold, SkinDetectConfig);

        textROISkin = ...
            { ...
                { ... 
                  'Green outline:       Selected skin region.', ... 
                  'Yellow outline:      Candidate skin regions.', ...
                  'Magenta outline:     Rejected skin regions.', ...
                  'Green star:          Selected skin region centroid.', ... 
                  'White star:          V.J.-Interpolated-ROI center.', ... 
                  'White line:          Distance between two above.', ...
                  'Text boxes:          Skin classification values:', ...
                  '                     N         = Pixel count', ...
                 ['                                 Current min limit: ', N_Min], ...
                  '                     Cr SD     = Cr standard deviation', ...
                 ['                                 Current max limit: ', CrSD_Max], ...
                  '                     P         = RGB probability', ...
                 ['                                 Current min limit: ', P_Min], ...
                  '                     Y, Cb, Cr = YCbCr color space z-scores', ...
                  '                                 Current max limits (+/-):' ...
                 ['                                 Cb: ', CbZ_MinMax, ' Cr: ', CrZ_MinMax], ...                                                              
                  'Note: text boxes displayed for two (top- and bottom-ranked)', ... 
                  'candidate regions and up to three (top-ranked) rejected regions.', ...
                  'Text boxes also displayed for rejected regions below N limit, in', ...
                  'which case only N is shown. Rejection occurs if outside limits for' , ...
                  'N, P, Cb, or Cr (Y is not used, so it is not shown for rejected', ...
                  'regions). Out of candidates, P, Y, Cb, Cr, and distance from', ...
                  'predicted ROI to region centroid are used to determine selected', ...
                  'region.' ...
                } ...
            };    
    
    %If insufficient skin-color samples collected to activate skin detection    
    elseif ~ SkinDetectConfig.Thresholds.SkinColorSamples_NThresholdPassedTF

        %Subsection text:

        %Lines within paragraph should appear left-justified (no leading spaces).        
        
        textROISkin = ...
            { ...
                { ... 
                 'Warning: Too few skin-color samples to activate skin-detect', ...
                 'algorithm. Detection verfication will be less robust.'
                } ...
            };        
    end

     %Concatenate text cell arrays:

     text = [text, textROISkinTitle, textROISkin];         
    
else
   
    %If insufficient skin-color samples collected to activate skin detection    
    if ~ SkinDetectConfig.Thresholds.SkinColorSamples_NThresholdPassedTF

        %Subsection title:

        %Line should appear left-justified (no leading spaces).

        textROISkinTitle = ...
            { ...
                { 'ROI from Skin-Detection Algorithm'} 
            };          
 
        %Subsection text:

        %Lines within paragraph should appear left-justified (no leading spaces).         
        
        textROISkin = ...
            { ...
                { ... 
                 'Warning: Too few skin-color samples to activate skin-detect', ...
                 'algorithm. Detection verfication will be less robust.'
                } ...
            };  
        
         %Concatenate text cell arrays:

         text = [text, textROISkinTitle, textROISkin];        
    end         
end      


%%%%%% Text section 2: Skin-segmentation information %%%%%%

if SkinSegmentConfig.SkinSegmentTF &&       ... Skin segmentation enabled
   OutputConfig.WriteVideoShowSkinSegmentTF %   Display of skin segmentation on output video 
                                            %   enabled.

    %See function WriteFaceVideo_OverlaySkinSegmentation, which inserts the annotations that 
    %correspond to this part of the legend.

    %Section title:
    
    %Spaces on left for center-jusification.
    
    textSkinSegmentTitle = ...
        { ...
            {'                       Skin Segmentation'} ... 
        };

    %Section body:

    %Lines within paragraph should appear left-justified (no leading spaces).
    
    %If detailed diagnostics enabled
    if OutputConfig.WriteVideoDetailedDiagnosticsTF
    
        %Number of times the severity of the morphological closure operation was reduced
        %See function SkinSegment_ConfigSetupOversegmentation_Reduce.
        NMorphReductions = num2str(SkinSegmentConfig.OverSegmentedCheck.NMorphReductions);
        
        %Whether the severity of the pixel-color thresholds was made less severe
        %See function SkinSegment_ConfigSetupOversegmentation.
        if SkinSegmentConfig.OverSegmentedCheck.BelowDarknessThresholdTF
            
            ThresholdsMadeLessSevere = 'true';
            
        else
            
            ThresholdsMadeLessSevere = 'false';            
        end

        textSkinSegment = ...
            { ...
                {'Light blue overlay:  Classified non-skin by skin segmentation', ...
                 '                     (only shown within final ROI).', ...
                 'N times morpho-', ...
                ['logical reduction:   ', NMorphReductions], ...
                ['Thresholds altered:  ', ThresholdsMadeLessSevere]} ...
            };
        
    %If detailed diagnostics not enabled                     
    else

        %Whether oversegmentation adjustments occurred
        %See functions SkinSegment_ConfigSetupOversegmentation and
        %SkinSegment_ConfigSetupOversegmentation_Reduce.
 
        if SkinSegmentConfig.OverSegmentedCheck.NMorphReductions > 0 ||  ... If the severity of the 
                                                                         ... morphological close  
                                                                         ... was reduced.
           SkinSegmentConfig.OverSegmentedCheck.BelowDarknessThresholdTF %   If the severity of the
                                                                         %   morphological close
                                                                         %   was reduced and the
                                                                         %   severity of the pixel-
                                                                         %   color thresholds were
                                                                         %   reduced.   
            SettingsAdjustedStatus = 'true';
           
        else
            
            SettingsAdjustedStatus = 'false';            
        end                                 
        
        textSkinSegment = ...
            { ...
                {'Light blue overlay:  Classified non-skin by skin segmentation', ...
                 'Oversegmentation', ...
                ['Adjustments:         ', SettingsAdjustedStatus]} ...
            };
    end 
    
    %If an insufficient number of skin-color samples were collected to activate tailored skin
    %segmentation
    if ~ SkinSegmentConfig.TailoredData.OpsReadyTF
        
        textSkinSegmentInsufficient = ...
            { ...
                {'Warning: Too few skin-color samples to activate tailored', ...
                 'segmentation. Skin segmentation and ROI detection verfication', ... 
                 'will be less robust.'} ...
            };            
      
    else
        
        textSkinSegmentInsufficient = {};            
    end

    %Concatenate text cell arrays:
    
    text = [text, textSkinSegmentTitle, textSkinSegment, textSkinSegmentInsufficient];
end


%%%%%% Text section 3: Pulse rate %%%%%%

%See function WriteFaceVideo_PulseRate, which inserts the annotations that correspond to this part
%of the legend.

%If pulse rate calculation enabled
if PulseRateConfigAndData.TF

    %Section title:
    
    %Spaces on left for center-jusification.
    
    textPulseRateTitle = ...
        { ...
            {'                          Pulse Rate'} ...                     
        };                              

    %Subsection body:
    
    %Lines within paragraph should appear left-justified (no leading spaces).
    
    %The specified duration of a window
    %The value can include inf.
    %Note: the duration can be specified to a value other than the default by argument 
    %PulseRateWindowDurationSec.
    WindowDurationSpecifiedStr = num2str(PulseRateConfigAndData.WindowDurationSec_Specified);
    
    %The number of pulse-rate windows used
    NWindowsStr = num2str( sum([PulseRateConfigAndData.Block.nWindows]) );
    
    textPulseRateWindow = ...
        { ...
            { ...
             ['Specified seconds per window:  ', WindowDurationSpecifiedStr], ...
             ['Number of windows:   ', NWindowsStr], ...
            } ...
        };     

    %Subsection title:
    
    %Line should appear left-justified (no leading spaces).
    
    textPulseRateAlgorithmTitle = ...
        { ...
            {'Pulse Rate Algorithm'} ... 
        };

    %Subsection body:
    
    %Lines within paragraph should appear left-justified (no leading spaces).
    
    textPulseRateAlgorithm = ...
        { ...
            { ...
             '''C'':                 CHROM_DEHAAN', ...
             '''G'':                 GREEN_VERKRUYSSE', ...
             '''I'':                 ICA_POH', ...
             '''P'':                 POS_WANG' ...
            } ...
        };       
    
    %If controlling RGB means for luminance enabled
    if PulseRateConfigAndData.ControlLuminanceTF
        
        %Add to cell array above
        %Note: 'L' represents 'luminance' rather than L of the LAB colorspace.
        textPulseRateAlgorithm{1}(end + 1) = ...
            {'''L'':                 Value when controlled for luminance'};  
        
    end  
    
    %If externally-measured pulse rate included
    %Note: externally-measured pulse rate is optionally entered as argument 
    %PulseRateExternallyMeasured to function FacePulseRate. See function PulseRate.
    if ~ isempty(PulseRateConfigAndData.ExternallyMeasured)
        
        %Add to cell array above
        textPulseRateAlgorithm{1}(end + 1) = ...
            {'''(EM)'':              Supplied external pulse rate values'};  
        
    end  
   
    %Concatenate text cell arrays:
    
    text = ...
        [text, textPulseRateTitle, textPulseRateWindow, textPulseRateAlgorithmTitle, ...
         textPulseRateAlgorithm];

end %end pulse rate text section   


%%%%%% Text section 4: Output video %%%%%%

%Note the limitation of seek time in the output video.
%Only include this note when detailed diagnositics are not enabled because there is not enough room
%when the detailed diagnostics are used.

%If detailed diagnostics not enabled
if ~ OutputConfig.WriteVideoDetailedDiagnosticsTF
    
    %Section title:
    
    %Spaces on left for center-jusification.
    
    textOutputVideoTitle = ...
        { ...
            {'                          Output Video'} ...                     
        };                              
                                        
    %Subsection body:
    
    %Lines within paragraph should appear left-justified (no leading spaces).
    
    textOutputVideo = ...
        { ...
            { ...
             'On the output video, the timestamp annotations, but not', ...
             'necessarily the seek time, will correspond to the seek time of', ...
             'input video.'
            } ...
        }; 
 
     %Concatenate text cell arrays:

     text = [text, textOutputVideoTitle, textOutputVideo];    
end


end %end function


