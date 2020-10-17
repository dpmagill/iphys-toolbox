function [AdjustedBecauseLowSkinProportionTF_i, ROIAdjusted_i, ROIAdjustCellArray] = ...
             ROIMeans_TakeMeans_ROIValidate(i, IsSkinMask, TrueCount_i, nRows_ROI, nCols_ROI, ...
                 VidFrame, ROI, FirstReadTF, ROIGeneralConfig_ROIMSIR_FirstFrameIdx, ...
                 CountTrueTF, SkinSegmentMask_LocalRange, ReturnYTF, ReturnCbCrTF, ReturnHSTF, ...
                 TailoredThresholdsTF, TailoredThresholdsSevereTF, MorphCloseSevereTF, ...
                 SkinSegmentConfig, VideoReadConfig_VidObjWidth, VideoReadConfig_VidObjHeight, ...
                 VideoReadConfig_FrameIdx) %#codegen 
%ROIMeans_TakeMeans_ROIValidate    Adjust ROI if proportion of pixels classified as skin in ROI is 
%                                  below threshold.
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_TakeMeans.
%
%
%    Code Generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.
%
%
%    Description
%    -----------
%
%    Adjust ROI if proportion of pixels classified as skin in ROI is below threshold. 
%                                  
%    The ROI is considered valid if the proportion of pixels classified as skin exceeds a specified
%    threshold. The proportion is calculated by inspecting the skin-segmentation mask, which  
%    corresponds to the location of the ROI. Specifically, from the skin-segmentation mask, the   
%    number of elements classified as true is divided by the total number of elements. This 
%    calculation is conducted by function ConfirmSkinPresent. This function returns a true / false
%    determination on whether the proportion exceeded the specified threshold 
%    (SkinSegmentConfig.ConfirmSkin).    
%    
%    If the ROI is considered invalid, it will be replaced with an ROI from a previous frame to 
%    attempt to increase accuracy. The ROI will come from a few frames back because it has been 
%    observed that the proportion threshold is typically activated several frames after the ROI 
%    began to drift from the face. 
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.
    

%%%%%% Code generation settings %%%%%%

%Inline function
coder.inline('always');

%Declare variable-size variables:

%                                 Upp. Bounds     Var. Size (T/F)
coder.varsize('nRows_ROIOut',     [1, 1],         [0, 0]);
coder.varsize('nCols_ROIOut',     [1, 1],         [0, 0]);
coder.varsize('RROI_Uint8',       [inf, inf],     [1, 1]);
coder.varsize('GROI_Uint8',       [inf, inf],     [1, 1]);
coder.varsize('BROI_Uint8',       [inf, inf],     [1, 1]);
coder.varsize('IsSkinMaskOut',    [inf, inf],     [1, 1]);
coder.varsize('TrueCount_iOut',   [1, 1],         [1, 0]);
coder.varsize('YROI_Single',      [inf, inf],     [1, 1]);


%%%%%% Initialize output values %%%%%%

nRows_ROIOut   = int32(0);
nCols_ROIOut   = int32(0); 
RROI_Uint8     = uint8([]); 
GROI_Uint8     = uint8([]); 
BROI_Uint8     = uint8([]); 
IsSkinMaskOut  = logical([]); 
TrueCount_iOut = uint32(0);
YROI_Single    = single([]);

%Heterogeneous cell array.
ROIAdjustCellArray = ...
    {nRows_ROIOut, nCols_ROIOut, RROI_Uint8, GROI_Uint8, BROI_Uint8, IsSkinMaskOut, ...
     TrueCount_iOut, YROI_Single};
 

%%%%%% Validate ROI according to the proportion of pixels classified as skin %%%%%%

%Specify condition for skin-color proportion check
FaceAlgorithm = 'm'; %indication to use the threshold for use with taking means  

%Note: 'ConfirmSkinPresent' is a custom function located within folder 'FacePulseRate'.
SkinColorTF = ... true/false indication on whether the proportion is above the threshold
    ConfirmSkinPresent( ...
        SkinSegmentConfig, ... data and configurations
        FaceAlgorithm, ... 
        IsSkinMask, ...
        single(TrueCount_i), ...
        nRows_ROI, ...
        nCols_ROI ...        
    );
 

%%%%%% Replace ROI if ROI not valid %%%%%%

%If the proportion is considered valid
if SkinColorTF 

    %Flag that the ROI was not replaced
    AdjustedBecauseLowSkinProportionTF_i = false; 

    %Assign empty values
    ROIAdjusted_i = zeros(0, 4, 'int16');

%If the proportion is considered invalid
else

    %The number of frames back from which to retrieve a replacement ROI
    FramesBack = int32(4);

    %Conditions when a previous ROI is available for retrieval:

    %During the first-read operations, a previous frame will not be available if the current 
    %frame  is near the first frame where ROI operations began  
    %(ROIGeneralConfig.ROIMSIR_FirstFrameIdx). During second-read operations, a previous frame 
    %will not be available if the current frame is near the beginning of the video. Note that, 
    %perhaps counterintuitively, the second-read operations begin at the beginning of the video 
    %whereas the first-read operations begin farther into the video.

    %Initialize flag that a previous ROI is available for retrieval
    ReplaceROIOK = false;

    %Current frame read during first-read operations        
    if FirstReadTF

        if i >= ROIGeneralConfig_ROIMSIR_FirstFrameIdx + FramesBack 

            ReplaceROIOK = true;
        end        

    %Current frame read during second-read operations           
    else
         if i - FramesBack > 0

            ReplaceROIOK = true;
        end                
    end   

    %%%%%% --- It is possible to replace the ROI %%%%%%
    
    %If a previous ROI can be retrieved, replace the current ROI with a previous ROI 
    if ReplaceROIOK

        %Indicate that ROI was adjusted for display on output video
        %Note: annotation superimposed on output video by function 
        %WriteFaceVideo_ROIAnnotation.
        AdjustedBecauseLowSkinProportionTF_i = true;                                   

        %Frame index of replacement ROI
        FrameIdx_Replacement = i - FramesBack;

        %Replace the ith ROI coordinates with the ROI of a previous frame
        %1 x 4 row vector; type int16.                
        ROIAdjusted_i = ROI(FrameIdx_Replacement, :);       

        %Check if any value of the previous ROI is zero
        %The operations of this function were intended to prevent values of zero, so such a   
        %value is likely due to an implementation error in this function. 
        if ROIAdjusted_i(1) == 0 || ...
           ROIAdjusted_i(2) == 0 || ...
           ROIAdjusted_i(3) == 0 || ...
           ROIAdjusted_i(4) == 0

            %Display error indicating frame index
            error(...
                'Component:InternalError', ...
                ['Internal Error: An ROI adjustment operation assigned a value of zero', ...
                 ' for an ROI. ROI accuracy may be affected. The frame index of the', ...
                 ' corresponding frame is: ', ...
                 sprintf( '%d', int32( VideoReadConfig_FrameIdx(FrameIdx_Replacement) ) ), ...
                 '.'] ...
            );              
        end

        %Determine the number of rows and columns of adjusted ROI
        %Scalars; int32.
        %Note: int32 is the specified input type for some mex functions.
        nRows_ROIOut = int32( ROIAdjusted_i(4) );
        nCols_ROIOut = int32( ROIAdjusted_i(3) );         

        %Assert values to prevent dynamic memory allocation where the colon operator is used
        assert(nRows_ROIOut < 5001);
        assert(nCols_ROIOut < 5001);        

        %Crop frame using new ROI and separate by color channel
        %Note: ROIMeans_TakeMeans_CropSeparateChannels is a custom function located within folder
        %'FacePulseRate'.
        [RROI_Uint8, GROI_Uint8, BROI_Uint8] = ...
            ROIMeans_TakeMeans_CropSeparateChannels(VidFrame, ROIAdjusted_i(1), ...
                 ROIAdjusted_i(2), nRows_ROIOut, nCols_ROIOut, VideoReadConfig_VidObjWidth, ...
                 VideoReadConfig_VidObjHeight);   

        %Segment skin within new ROI:

        %Note: SkinSegmentMask is a custom function located within folder FacePulseRate.
        [IsSkinMaskOut,   ... M x N matrix; type logical 
         TrueCount_iOut,  ... Count of pixels classified as skin; scalar, type uint32   
         YROI_Single] =   ... M x N matrix; type single
            SkinSegmentMask( ...
                RROI_Uint8, ... 
                GROI_Uint8, ...
                BROI_Uint8, ... 
                single([]), ...                               
                single([]), ...
                single([]), ...
                single([]), ...                                
                single([]), ...
                SkinSegmentMask_LocalRange, ...  
                nRows_ROIOut, ...     
                nCols_ROIOut, ... 
                CountTrueTF, ...
                TailoredThresholdsTF, ... 
                ReturnYTF, ... 
                ReturnCbCrTF, ...  
                ReturnHSTF, ... 
                TailoredThresholdsSevereTF, ...
                MorphCloseSevereTF, ... 
                int32(-1), ...
                int32(-1), ...             
                SkinSegmentConfig.Args, ...
                SkinSegmentConfig.UseCompiledFunctionsTF ... 
            ); 

    %Assign as output    
    %Heterogeneous cell array.
    ROIAdjustCellArray = ...
        {nRows_ROIOut, nCols_ROIOut, RROI_Uint8, GROI_Uint8, BROI_Uint8, IsSkinMaskOut, ...
         TrueCount_iOut, YROI_Single};    
        
    %%%%%% --- It is not possible to replace the ROI %%%%%%        
        
    %If a previous ROI cannot be retrieved    
    else

        AdjustedBecauseLowSkinProportionTF_i = false;

        %Assign empty values
        ROIAdjusted_i = zeros(0, 4, 'int16');      
    end
end 

    
end %end function

