function [N_Min, CrSD_Max, P_Min, CbZ_MinMax, CrZ_MinMax] = ...
             WriteFaceVideo_LegendSetupTextSkinDetect(LegendVersion1NotAssignedTF, ...
                 RegionNThreshold, SkinDetectConfig)
%WriteFaceVideo_LegendSetupTextSkinDetect    Calculate skin-detection metrics for legend.
%                                             
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_LegendSetupText.
%    
%
%    Description
%    -----------
%
%    Calculate skin-detection algorithm metrics for legend. For interpretation, see function
%    SkinDetect.
%
%    Different text is assigned in this function depending on the value of 
%    LegendVersion1NotAssignedTF. See note in function WriteFaceVideo. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%Pixel count minimum
N_Min = num2str(RegionNThreshold);

%Cr standard deviation minimum
CrSD_Max = num2str(SkinDetectConfig.Thresholds.ColorSDThreshold);

%If version 1 of the legend has not yet been assigned
%Assign text for version 1 of the legend.
if LegendVersion1NotAssignedTF

    %Color thresholds corresponding to a non-large number of skin-color samples:
    
    %Probability minimum
    P_Min = num2str( uint8(SkinDetectConfig.Thresholds.ColorThreshold(1) * 100) );
    
    %Cb z-score minimum and maximum (-/+)
    CbZ_MinMax = num2str( SkinDetectConfig.Thresholds.ColorThreshold(2) ); 

    %Cr z-score minimum and maximum (-/+)
    CrZ_MinMax = num2str( SkinDetectConfig.Thresholds.ColorThreshold(3) );

%If version 2 of the legend has not yet been assigned
%Assign text for version 2 of the legend.     
else

    %Color thresholds corresponding to a large number of skin-color samples:    
    
    %Probability minimum
    P_Min = num2str( uint8(SkinDetectConfig.Thresholds.ColorThresholdHighN(1) * 100) );    
    
    %Cb z-score minimum and maximum (-/+)
    CbZ_MinMax = num2str( SkinDetectConfig.Thresholds.ColorThresholdHighN(2) ); 

    %Cr z-score minimum and maximum (-/+)
    CrZ_MinMax = num2str( SkinDetectConfig.Thresholds.ColorThresholdHighN(3) );   
end
        

end %end function

