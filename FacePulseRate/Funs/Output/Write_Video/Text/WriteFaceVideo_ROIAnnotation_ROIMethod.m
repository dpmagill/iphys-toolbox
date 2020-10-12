function Text = WriteFaceVideo_ROIAnnotation_ROIMethod(i, HasROI_TF, ROIDiagnostic, OutputConfig)
%WriteFaceVideo_ROIAnnotation_ROIMethod    Prepare text for method that determined ROI.
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_ROIAnnotation.
%
%
%    Description
%    -----------
%
%    Prepare text for method that determined ROI. See function WriteFaceVideo_ROIAnnotation for 
%    details.
%
%    -- Default vs. detailed display --
%
%    More detailed ROI-detection information is displayed under the detailed display option
%    compared to the default display option. The detailed display option is intended only for 
%    internal development and, by default, is not enabled. The detailed display is enabled by flag   
%    OutputConfig.WriteVideoDetailedDiagnosticsTF, which is assigned by function 
%    ValidateAndConfigure_InternalFlags. Examples of the differences between the options are  
%    provided in function WriteFaceVideo_ROIAnnotation.
%
%    Under the default display option, the characters '[RS]' and '[NR]' are prepared in the current
%    function. Under the detailed display option, these characters are prepared by function 
%    WriteFaceVideo_ROIAnnotation_DetectAttempts.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Default display option %%%%%%

if ~ OutputConfig.WriteVideoDetailedDiagnosticsTF

    %%%%%% --- Detection method %%%%%%
    
    %Note: the following ROI categories are mutually exclusive.

    %If ROI detection ignored, as specified by argument ROIIgnoreByArgument 
    %In this case, the ROI will have been interpolated from nearby frames.
    %Note: when OutputConfig.WriteVideoDetailedDiagnosticsTF == true, an annotation for 
    %ROIIgnoreByArgument is added by function WriteFaceVideo_ROIAnnotation_DetectAttempts. 
    %Note: ROIIgnoreByArgument is an argument to function FacePulseRate.
    %Note: HasROI_TF.Skipped(i) will also be true because the ROI is ignored by skipping detection 
    %algorithms for the frame.
    if HasROI_TF.ROIIgnoreByArgument(i)

        Text = 'ROI: Ignored';

    %If ROI specified by argument ROISpecifiedByArgument 
    %Note: when OutputConfig.WriteVideoDetailedDiagnosticsTF == true, an annotation for 
    %ROISpecifiedByArgument is added by function WriteFaceVideo_ROIAnnotation_DetectAttempts.
    %Note: ROISpecifiedByArgument is an argument to function FacePulseRate.
    elseif HasROI_TF.ROISpecifiedByArgument(i)
   
        Text = 'ROI: Specified by argument';    
    
    %If interpolation performed for a frame 
    %Interpolation will occur if no detection algorithms were successful, if the frame was skipped
    %for efficiency ( HasROI_TF.Skipped(i) == true ), or if the ROI for the frame was specified to  
    %be ignored by argument ROIIgnoreByArgument ( HasROI_TF.ROIIgnoreByArgument(i) == true), which 
    %is an argument to function FacePulseRate. Under the default display option, if the frame was
    %specified to be ignored, the text 'ROI: Ignored |' will be displayed instead of 
    %'ROI: Interpolated |'. Under the detailed display option (see function  
    %WriteFaceVideo_ROIAnnotation_DetectAttempts), the display will be 
    %'ROI: Interpolated | Ignored'. 
    elseif  HasROI_TF.Interpolated(i)

        Text = 'ROI: Interpolated';                                                   

    %If ROI from primary face-detection algorithm
    %Under the default display option, this algorithm will be termed "Frontal" for simplicity.
    elseif HasROI_TF.FacePrimary(i)

        Text = 'ROI: Frontal';

    %If ROI from secondary #1 face-detection algorithm
    %Under the default display option, this algorithm will be termed "Profile" for simplicity.    
    elseif HasROI_TF.FaceSecondary1(i)

        Text = 'ROI: Profile';

    %If ROI from secondary #2 face-detection algorithm 
    %Under the default display option, this algorithm will be termed "Frontal 2" for simplicity.
    %As of the current implementation, this condition will not be used.
    elseif HasROI_TF.FaceSecondary2(i)

        Text = 'ROI: Frontal 2';

    %If ROI from skin-detection algorithm
    elseif HasROI_TF.Skin(i)

        Text = 'ROI: Skin';
        
    %This condition should not occur
    %Provided for robustness.
    else 

        Text = '';
    end     

    %%%%%% --- Detection notifications %%%%%%
    
    %Note: under the detailed display option, these characters are prepared by function 
    %WriteFaceVideo_ROIAnnotation_DetectAttempts.    

    %Initialize flag
    SkinNotPresent = false;
    
    %If ROI classified as not containing skin
    if HasROI_TF.SkinNotPresent_Skin(i) || ... skin-detection algorithm
       HasROI_TF.SkinNotPresent_Pri(i)  || ... primary face-detection algorithm
       HasROI_TF.SkinNotPresent_Sec1(i) || ... secondary #1 face-detection algorithm
       HasROI_TF.SkinNotPresent_Sec2(i)    %   secondary #2 face-detection algorithm
   
        Text = [Text, ' | [RS]'];
        
        SkinNotPresent = true;
    end
    
    %If no regions were avilable to the skin-detection algorithm
    if HasROI_TF.SkinAttempted(i) && ... the skin-detection algorithm was attempted
       ~ ROIDiagnostic.ROISkin.RegionAnyAvailable(i)                
   
        if SkinNotPresent
            
            Text = [Text, ' [NR]']; 
            
        else
            
            Text = [Text, ' | [NR]'];
        end
    end  
        
        
%%%%%% Detailed display option %%%%%%
    
else
    
    %Note: the following ROI categories are mutually exclusive.

    %If interpolation performed for a frame 
    %Interpolation will occur if no detection algorithms were successful, if the frame was skipped
    %for efficiency ( HasROI_TF.Skipped(i) == true ), or if the ROI for the frame was specified to  
    %be ignored by argument ROIIgnoreByArgument, which is an argument to function FacePulseRate.
    if  HasROI_TF.Interpolated(i)

        Text = 'ROI: Interpolated |';                                                   

    %If ROI from primary face-detection algorithm
    elseif HasROI_TF.FacePrimary(i)

        Text = 'ROI: Pri. |';

    %If ROI from secondary #1 face-detection algorithm
    elseif HasROI_TF.FaceSecondary1(i)

        Text = 'ROI: Sec.#1 |';

    %If ROI from secondary #2 face-detection algorithm    
    elseif HasROI_TF.FaceSecondary2(i)

        Text = 'ROI: Sec.#2 |';

    %If ROI from skin-detection algorithm
    elseif HasROI_TF.Skin(i)

        Text = 'ROI: Skin |';

    %This condition should not occur
    %Provided for robustness.
    else 

        Text = '';
    end     
end


end %end function

