function [ROIsDarkTF, MakeColorThresLessSevereTF, YSingleMean, FramesYSingleMeanCounter] = ...
             SkinSegment_OversegmentationCheck_Dark(YSingle_OversegmentationCheck, ...
                 FramesYSingleMean, FramesYSingleMeanCounter, SkinSegmentConfig)             
%SkinSegment_OversegmentationCheck_Dark    Check whether ROIs are likey oversegmented because of
%                                          chronic darkness of ROIs.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinSegment_OversegmentationCheck.
%    
%
%    Description
%    -----------
%
%    Check whether ROIs are likey oversegmented because of chronic darkness of ROIs. Whether the
%    ROIs are actually oversegmented (a chronic low proportion of skin across frames) is not 
%    checked because it is assumed that if chronic darkness is present then oversegmentation will
%    also be present. 
%
%    If ROIs are considered to be dark (ROIsDarkTF), both the pixel-color thresholds and the 
%    morphological close operations will be made less severe. Flag MakeColorThresLessSevereTF 
%    signals to function SkinSegment_OversegmentationCheck_Reduce that the severity of the  
%    pixel-color thresholds should be reduced. Flag ROIsDarkTF signals to function 
%    SkinSegment_OversegmentationCheck that the morphological close operations should be made less 
%    severe. 
%
%    A different function, SkinSegment_OversegmentationCheck_Dark, checks whether ROIs are actually
%    oversegmented.
%
%    For a more detailed description, see function SkinSegment_OversegmentationCheck. 
%   
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% The severity of the pixel-color thresholds has not been reduced previously %%%%%%

%The severity of the pixel-color thresholds can be reduced only one time. Hence, once reduced, 
%checking whether ROIs are dark is not necessary.

%Note: this flag is set by function SkinSegment_OversegmentationCheck_Reduce. 
if ~ SkinSegmentConfig.OverSegmentedCheck.PixelColorsAdjustedTF

    %%%%%% --- Take mean of the Y colorspace corresponding to the ROI %%%%%%
    
    %The Y-colorspace mean across frames will be used to determine whether chronic darkness is
    %present across frames.
            
    %Take the mean
    YSingleMean = sum(YSingle_OversegmentationCheck, 'all') / numel(YSingle_OversegmentationCheck);       

    %%%%%% --- Determine whether the Y-mean across frames is below the threshold %%%%%%    

    %Determine whether there is a chronic darkness in ROIs.    
    
    %Increment the counter:    

    %Note: this value is also used by function ROIMeans_FirstRead.
    
    %If the counter had previously reached the end of FramesYSingleMean, reset the counter
    if FramesYSingleMeanCounter == SkinSegmentConfig.OverSegmentedCheck.NFramesYSingleMean
            
        %Scalar; type int16.
        FramesYSingleMeanCounter = int16(1);

    else

        %Scalar; type int16.
        FramesYSingleMeanCounter = FramesYSingleMeanCounter + 1;                          
    end      
        
    %Assign to vector
    %Note: YSingleMean is also assigned to the vector outside of the function. This prevents the
    %entire vector from being returned (and, hence, reassigned) on each call.
    FramesYSingleMean(FramesYSingleMeanCounter) = YSingleMean;
               
    %Mean of the Y-colorspace across frames
    %Scalar; type single.
    YMeanAcrossFrame = ...
        sum(FramesYSingleMean) / SkinSegmentConfig.OverSegmentedCheck.NFramesYSingleMean;

    %If the mean across frames is less than the darkness threshold
    %In addition to ROIsDarkTF signaling whether the pixel-color thresholds should be made less  
    %severe (below), it also signals whether the morphological close operations should be made less
    %severe (function SkinSegment_OversegmentationCheck).
    ROIsDarkTF = YMeanAcrossFrame < SkinSegmentConfig.OverSegmentedCheck.DarknessThreshold;
    
    %Flag to reduce the severity of the pixel-color thresholds
    MakeColorThresLessSevereTF = ROIsDarkTF;
 
    
%%%%%% The severity of the pixel-color thresholds has been reduced previously %%%%%%    
    
else
    
    YSingleMean = [];
    ROIsDarkTF = false;
    MakeColorThresLessSevereTF = false;    
end


end %end function

