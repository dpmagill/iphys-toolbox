function Text = ...
             WriteFaceVideo_ROIAnnotation_DetectAttempts(i, Text, HasROI_TF, ROIDiagnostic, ...
                 FaceDetectConfig)
%WriteFaceVideo_ROIAnnotation_DetectAttempts    Prepare text for detection attempts.
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_ROIAnnotation.
%
%
%    Description
%    -----------
%
%    Prepare text for detection attempts. See function WriteFaceVideo_ROIAnnotation for details.
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
%    Under the default display option (OutputConfig.WriteVideoDetailedDiagnosticsTF == false), the 
%    characters '[R]' and '[NR]' are prepared by function WriteFaceVideo_ROIAnnotation_ROIMethod.
%    Under the detailed display option, these characters are prepared in the current function. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%If at least one method attempted a detection on the ith frame.
%Note: if no method attempted a detection, this indicates the frame was intentionally skipped (see 
%function ROIMeans_FirstRead_DetermineSkipFrame, called within function 
%ROIMeans_FirstRead, and function ROIMeans_SecondRead_SkinDetect).
if HasROI_TF.FacePrimaryAttempted(i)    || ... primary face-detection algorithm
   HasROI_TF.FaceSecondary1Attempted(i) || ... secondary #1 face-detection algorithm
   HasROI_TF.FaceSecondary2Attempted(i) || ... secondary #2 face-detection algorithm
   HasROI_TF.SkinAttempted(i)              %   skin-detection algorithm

    %Assign character array of attempted methods.
    %Separate detection methods with with ',' delimiter.
    %Separate the one method that made the detection (if any) from the detection attempts with a  
    %'|' delimiter.

    %Whether more than one method was attempted
    PriorAttemptsTF = false;

    %Primary face-detection algorithm:

    if HasROI_TF.FacePrimaryAttempted(i)   

        %If ROI classified as not containing skin
        if HasROI_TF.SkinNotPresent_Pri(i)  

            Text = [Text, ' Pri.[RS]'];

        else

            Text = [Text, ' Pri.'];
        end        

        %Whether the primary face-detection algorithm returns a profile of a face
        if FaceDetectConfig.PrimaryProfileTF
        
            %If the ROI failed the profile-eyes test.
            if HasROI_TF.ProfileEyesPresent_Pri
                
                Text = [Text, '[RE]'];    
            end
        end
               
        PriorAttemptsTF = true; %flag to add comma
    end

    %Secondary #1 face-detection algorithm:    

    if HasROI_TF.FaceSecondary1Attempted(i) 

        if PriorAttemptsTF

            %If ROI classified as not containing skin
            if HasROI_TF.SkinNotPresent_Sec1(i)  

                Text = [Text, ', Sec.#1[RS]'];

            else

                Text = [Text, ', Sec.#1'];
            end            
            
            %Whether the secondary #1 face-detection algorithm returns a profile of a face
            if FaceDetectConfig.Secondary1ProfileTF

                %If the ROI failed the profile-eyes test.
                if HasROI_TF.ProfileEyesPresent_Sec1

                    Text = [Text, '[RE]'];    
                end
            end
            
        else

            %If ROI classified as not containing skin
            if HasROI_TF.SkinNotPresent_Sec1(i)  

                Text = [Text, ' Sec.#1[RS]'];

            else

                Text = [Text, ' Sec.#1'];
            end            

            %Whether the secondary #1 face-detection algorithm returns a profile of a face
            if FaceDetectConfig.Secondary1ProfileTF

                %If the ROI failed the profile-eyes test.
                if HasROI_TF.ProfileEyesPresent_Sec1

                    Text = [Text, '[RE]'];    
                end
            end            
            
            PriorAttemptsTF = true; %flag to add comma
        end                
    end

    %Secondary #2 face-detection algorithm:    

    if HasROI_TF.FaceSecondary2Attempted(i)

        if PriorAttemptsTF

            %If ROI classified as not containing skin
            if HasROI_TF.SkinNotPresent_Sec2(i)  

                Text = [Text, ', Sec.#2[RS]'];

            else

                Text = [Text, ', Sec.#2'];
            end                 

            %Whether the secondary #2 face-detection algorithm returns a profile of a face
            if FaceDetectConfig.Secondary2ProfileTF

                %If the ROI failed the profile-eyes test.
                if HasROI_TF.ProfileEyesPresent_Sec2

                    Text = [Text, '[RE]'];    
                end
            end
            
        else

            %If ROI classified as not containing skin
            if HasROI_TF.SkinNotPresent_Sec2(i)  

                Text = [Text, ' Sec.#2[RS]'];

            else

                Text = [Text, ' Sec.#2'];
            end               

            %Whether the secondary #2 face-detection algorithm returns a profile of a face
            if FaceDetectConfig.Secondary2ProfileTF

                %If the ROI failed the profile-eyes test.
                if HasROI_TF.ProfileEyesPresent_Sec2

                    Text = [Text, '[RE]'];    
                end
            end            
            
            PriorAttemptsTF = true; %flag to add comma
        end                
    end

    %Skin-detection algorithm:    

    if HasROI_TF.SkinAttempted(i) 

        if PriorAttemptsTF

            %If ROI classified as not containing skin
            if HasROI_TF.SkinNotPresent_Skin(i)  

                Text = [Text, ', Skin[RS]'];

            else

                Text = [Text, ', Skin'];
            end                  

        else

            %If ROI classified as not containing skin
            if HasROI_TF.SkinNotPresent_Skin(i)  

                Text = [Text, ' Skin[RS]'];

            else

                Text = [Text, ' Skin'];
            end            
        end

        %If no regions were avilable to the skin-detection algorithm
        if ~ ROIDiagnostic.ROISkin.RegionAnyAvailable(i)

            Text = [Text, '[NR]'];
        end        
    end     

%No methods attempted: ROI specified by argument ROISpecifiedByArgument
%Note: ROISpecifiedByArgument is an argument to function FacePulseRate.
elseif HasROI_TF.ROISpecifiedByArgument(i)

    Text = 'ROI: Specified by argument';

%No methods attempted: ROI detection ignored, as specified by argument ROIIgnoreByArgument
%Note: ROIIgnoreByArgument is an argument to function FacePulseRate.
%Note: HasROI_TF.Skipped(i) will also be true because the ROI is ignored by skipping detection 
%algorithms for the frame.
elseif HasROI_TF.ROIIgnoreByArgument(i)    

    Text = 'ROI: Interpolated | Ignored';

%No methods attempted: frame skipped
%Note: HasROI_TF.Skipped(i) will also be true when HasROI_TF.ROIIgnoreByArgument(i) is true. It is 
%intended that the HasROI_TF.ROIIgnoreByArgument message, rather than the HasROI_TF.Skipped(i)
%message, will be displayed when HasROI_TF.ROIIgnoreByArgument(i) is true, so  
%HasROI_TF.ROIIgnoreByArgument(i) should be checked before HasROI_TF.Skipped is checked. 
else %HasROI_TF.Skipped(i)

    Text = 'ROI: Interpolated | Skipped';    
end
    
    
end %end function

