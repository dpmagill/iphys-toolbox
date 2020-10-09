function [FramesLowSkinProportionTF, LowSkinProportionTF, FramesLowSkinProportionCounter] = ...
             SkinSegment_OversegmentationCheck_LowSkin(ProportionSkin, ProportionSkin_AlgName, ...
                 FramesLowSkinProportionStatus, FramesLowSkinProportionCounter, ...
                 SkinSegmentConfig)             
%SkinSegment_OversegmentationCheck_LowSkin    Check whether ROIs appear to be oversegmented, which
%                                             is checked according to the chronic presence of low
%                                             skin.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinSegment_OversegmentationCheck.
%    
%
%    Description
%    -----------
%
%    Check whether ROIs appear to be oversegmented, which is defined as the chronic condition of
%    ROIs with a low proportion of skin. If ROIs are considered to be oversegmented, return flag 
%    FramesLowSkinProportionTF and return modified settings that result in the morphological close
%    operations being made less severe. This flag signals to function  
%    SkinSegment_OversegmentationCheck_Reduce to assign the modified settings to struct 
%    SkinSegentConfig, which is used by the function that carries out skin segmentation, 
%    SkinSegmentMask. 
%
%    A different function, SkinSegment_OversegmentationCheck_Dark, checks whether ROIs appear to be
%    oversegmented due to dark ROIs.  
%
%    For a more detailed description, see function SkinSegment_OversegmentationCheck. 
%   
%
%    Note
%    ----
%
%    This function should be called only if ProportionSkin was calculated for at least one 
%    face-detection algorithm attempt. In this case, ProportionSkin will not equal -1; -1 indicates
%    the proportion was not calculated for any face-detection algorithm attempt. ProportionSkin
%    will not be calculated when the result returned from a face-detection algorithm does not meet  
%    the first criterion of function FaceDetect_ROIValidate, namely, that one and only one ROI was
%    returned.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% The severity of the morphological close has not been reduced the maximum number of times %%%%%%

if SkinSegmentConfig.OverSegmentedCheck.NMorphReductions < ... 
   SkinSegmentConfig.OverSegmentedCheck.NMorphReductionLimit 

    %%%%%% --- Select the skin-proportion threshold based on the algorithm that returned the ROI %%%%%%

    %If the proportion is from a primary face-detection algorithm attempt
    if ProportionSkin_AlgName == 'p'

        %Scalar; type single.
        ProportionSkinThreshold = SkinSegmentConfig.OverSegmentedCheck.ProportionThresholdPrimary;

    %If the proportion is from a secondary #1 face-detection algorithm attempt
    elseif ProportionSkin_AlgName == '1'

        %Scalar; type single.
        ProportionSkinThreshold = ...
            SkinSegmentConfig.OverSegmentedCheck.ProportionThresholdSecondary1;

    %If the proportion is from a secondary #2 face-detection algorithm attempt
    elseif ProportionSkin_AlgName == '2'

        %Scalar; type single.
        ProportionSkinThreshold = ...
            SkinSegmentConfig.OverSegmentedCheck.ProportionThresholdSecondary2;

    %If true, an implementation error has occurred    
    else

        ME = ...
            MException( ...
                'Component:OversegmentationCheck', ...
                'Implementation Error: AlgName should match an algorithm.' ...
            );

        throw(ME);     
    end      

    %%%%%% --- Determine whether the ith ROI is below the skin-proportion threshold %%%%%%
    
    LowSkinProportionTF = ProportionSkin < ProportionSkinThreshold;

    %%%%%% --- Determine whether the frames-low-skin proportion is above the threshold %%%%%% 
    
    %Determine whether there is a chronic condition of ROIs with a low proportion of skin, which is
    %operationalized by a frames-low-skin proportion that is above a specified threshold.     
    
    %Increment the counter:    

    %Note: this value is also used by function ROIMeans_FirstRead.
    
    %If the counter had previously reached the end of PreviousFramesStatus, reset the counter
    if FramesLowSkinProportionCounter == ...
           SkinSegmentConfig.OverSegmentedCheck.NFramesLowSkinProportionStatus

        %Scalar; type int16.
        FramesLowSkinProportionCounter = int16(1);

    else

        %Scalar; type int16.
        FramesLowSkinProportionCounter = FramesLowSkinProportionCounter + 1;                          
    end    
    
    %The frames-low-skin proportion only needs to be calculated if the current value of 
    %LowSkinProportionTF is true.
    if LowSkinProportionTF

        %Assign value to vector    
        %Note: For efficiency, vector FramesLowSkinProportionStatus is not returned by the current 
        %function. If returned, this would result in the vector being reassigned in function
        %ROIMeans_FirstRead on each call to the current function. Rather, only LowSkinProportionTF 
        %is returned; this value is then assigned to FramesLowSkinProportionStatus in function 
        %ROIMeans_FirstRead, resulting in only one element being reassigned. Also, when it is  
        %assigned by ROIMeans_FirstRead, LowSkinProportionTF is assigned regardless of whether it  
        %is false. It is not assigned to FramesLowSkinProportionStatus if false in the current  
        %function only for efficiency. 
        FramesLowSkinProportionStatus(FramesLowSkinProportionCounter) = LowSkinProportionTF;           
        
        %The frames-low-skin proportion
        %That is, the proportion of frames in which an ROI was under the skin-proportion  
        %threshold. The frames-low-skin proportion is out of the number of frames for which a   
        %status can be stored. This number of frames is equal to 
        %SkinSegmentConfig.OverSegmentedCheck.NFramesLowSkinProportionStatus.
        %Scalar; type double.
        FramesLowSkinProportion = ...
            nnz(FramesLowSkinProportionStatus) / ...
            SkinSegmentConfig.OverSegmentedCheck.NFramesLowSkinProportionStatus;    
 
        %Determine whether oversegmentation is present:
        
        %Oversegmentation is present when the frames-low-skin proportion is above the threshold. If 
        %present, set flag FramesLowSkinProportionTF to true. This will cause the severity of the 
        % morphological close to be reduced (see function SkinSegment_OversegmentationCheck).

        %Note: After the severity of the morphological close is reduced, the status of all previous  
        %frames in PreviousFramesStatus will be reset (all elements changed to false) to let  
        %evidence of oversegmentation accumulate before the severity can be reduced again. This 
        %resetting is conducted at the top of function ROIMeans_FirstRead after the recursive call
        %to function ROIMeans_FirstRead.

        %If true, the frames are determined to be oversegmented
        FramesLowSkinProportionTF = ...
            FramesLowSkinProportion > ...
            SkinSegmentConfig.OverSegmentedCheck.FramesLowSkinProportionThreshold; 
        
    else
        
        FramesLowSkinProportionTF = false;        
    end 

    
%%%%%% The severity of the morphological close has been reduced the maximum number of times %%%%%%

else
    
    LowSkinProportionTF       = false;
    FramesLowSkinProportionTF = false;     
end


end %end function

