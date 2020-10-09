function [IsSkinMask, TrueCount, YSingle, CbSingle, CrSingle, HSingle, SSingle, ...
          IsSkinMask_Range] = ...
             SkinSegmentMask(RUint8, GUint8, BUint8, YSingle, CbSingle, CrSingle, HSingle, ...
                 SSingle, IsSkinMask_Range, NRows_Matrix, NCols_Matrix, CountTrueTF, ...
                 TailoredThresholdsTF, ReturnYTF, ReturnCbCrTF, ReturnHSTF, ...
                 TailoredThresholdsSevereTF, MorphCloseSevereTF, XOffset, YOffset, ...
                 SkinSegmentConfig_Args, UseCompiledFunctionsTF) %#codegen                                                                                                                                      
%SkinSegmentMask   Return logical matrix, or skin-segmentation mask, where pixels classified as 
%                  skin are true. Wrapper function for function SkinSegmentMask_Ops.
%  
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, this function is called by functions ...
%        - ConfirmSkinPresent (which is called by functions FaceDetect_ROIValidate,  
%          SkinDetect_SelectedRegionROI, and ROIMeans_TakeMeans)
%        - SkinDetect_PartitionRegions (which is called by function SkinDetect)          
%        - ROIMeans_TakeMeans (which is called by functions ROIMeans_FirstRead_TakeMeans and
%          ROIMeans_SecondRead_TakeMeans)
%        - ROIMeans_FirstRead_CollectSkinColorSamples (which is called by function
%          ROIMeans_FirstRead)
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
%    Return logical matrix, or skin-segmentation mask, where pixels classified as skin are true.
%    This is a wrapper function for function SkinSegmentMask_Ops. For a description of the 
%    skin-segmentation operations, see function SkinSegmentMask_Ops.
%
%    Execute either the compiled or non-compiled function depending on argument 
%    UseCompiledFunctionsTF.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% Code-generation settings %%%%%%

%Inline function
coder.inline('always');


%Compiled functions enabled and code generation not running
%Value of SkinSegmentConfig.UseCompiledFunctionsTF assigned in function 
%SkinSegment_ConfigSetup. 
if UseCompiledFunctionsTF && ...
   coder.target('MATLAB') %called outside of code generation   

    %Note: SkinSegmentMask_Ops_mex is a compiled custom function located within folder 
    %FacePulseRate. For source code, see file SkinSegmentMask_Ops.m. 
    [IsSkinMask,         ... Skin-segmentation mask; M x N matrix, type logical
     TrueCount,          ... Count of pixels classified as skin; scalar, type uint32
     YSingle,            ... Y channel of the YCbCr colorspace; M x N matrix, type single
     CbSingle,           ... Cb channel of the YCbCr colorspace; M x N matrix, type single
     CrSingle,           ... Cr channel of the YCbCr colorspace; M x N matrix, type single
     HSingle,            ... H channel of the HSV colorspace; M x N matrix, type single
     SSingle,            ... S channel of the HSV colorspace; M x N matrix, type single 
     IsSkinMask_Range] = ... Skin-segmentation mask based upon local range threshold; M x N matrix, 
                         ... type logical.
        SkinSegmentMask_Ops_mex( ...
            ... The following subset of variables can be entered as empty if variables YSingle,   
            ... CbSingle, CrSingle, HSingle, SSingle, and localRange are non-empty.        
            RUint8,                     ... R channel of the RGB colorspace; M x N matrix, type 
                                        ... uint8.
            GUint8,                     ... G channel of the RGB colorspace; M x N matrix, type 
                                        ... uint8.
            BUint8,                     ... B channel of the RGB colorspace; M x N matrix, type 
                                        ... uint8. 
            ... -- end subset --
            ... The following subset of variables can be entered as empty if variables RUint8,
            ... GUint8, BUint8 are non-empty.
            YSingle,                    ... Y channel of the YCbCr colorspace; M x N matrix, type 
                                        ... single.
            CbSingle,                   ... Cb channel of the YCbCr colorspace; M x N matrix, type 
                                        ... single.
            CrSingle,                   ... Cr channel of the YCbCr colorspace; M x N matrix, type 
                                        ... single.
            HSingle,                    ... H channel of the HSV colorspace; M x N matrix, type 
                                        ... single. 
            SSingle,                    ... S channel of the HSV colorspace; M x N matrix, type 
                                        ... single.
            IsSkinMask_Range,           ... Skin-segmentation mask based upon local range 
                                        ... threshold; M x N matrix, type logical. 
            ... -- end subset --
            NRows_Matrix,               ... Number of rows of an input matrix. If Y_Matrix_Reduced 
                                        ... is non-empty, then this value indicates the number of
                                        ... rows to index into, which can be different from the
                                        ... height of the input matrices. Note that this indexing  
                                        ... is not applied to input IsSkinMask_LocalRange;
                                        ... IsSkinMask_LocalRange should be cropped to the height 
                                        ... of NRows_Matrix_Reduced before entered as an argument.
                                        ... Scalar; type int32.
            NCols_Matrix,               ... Number of columns of an input matrix. If  
                                        ... X_Matrix_Reduced is non-empty, then this value
                                        ... indicates the number of columns to index into, which 
                                        ... can be different from the width of the input matrices.
                                        ... Note that this indexing is not applied to input  
                                        ... IsSkinMask_LocalRange; IsSkinMask_LocalRange should be 
                                        ... cropped to the width of NCols_Matrix_Reduced before 
                                        ... entered as an argument. Scalar; type int32. 
            CountTrueTF,                ... Whether to return a count of pixels classified as skin;
                                        ... scalar, type logical.
            TailoredThresholdsTF,       ... Whether to use thresholds that are tailored; scalar, 
                                        ... type logical.
            ReturnYTF,                  ... Whether to return Y channel of the YCbCr colorspace; 
                                        ... scalar, type logical.
            ReturnCbCrTF,               ... Whether to return the Cb and Cr channels of the YCbCr 
                                        ... colorspace; scalar, type logical.
            ReturnHSTF,                 ... Whether to return the H and S channels of the HSV 
                                        ... colorspace; scalar, type logical.
            TailoredThresholdsSevereTF, ... Whether to use severe tailored thresholds; scalar, type 
                                        ... logical.         
            MorphCloseSevereTF,         ... Whether the morphological close operation will be 
                                        ... conducted with a high level of severity; scalar, type
                                        ... logical.
            XOffset,                    ... Optional X-coordinate offset applied to input matrices.
                                        ... However, does not apply to input IsSkinMask_LocalRange. 
                                        ... Specify -1 to ignore. If argument used, adjust  
                                        ... NCols_Matrix accordingly. NCols_Matrix can be set to an  
                                        ... arbitrary value when XOffset is non-empty. Scalar; type 
                                        ... int32. 
            YOffset,                    ... Optional Y-coordinate offset applied to input matrices.
                                        ... However, does not apply to input IsSkinMask_LocalRange. 
                                        ... Specify -1 to ignore. If argument used, adjust  
                                        ... NRows_Matrix accordingly. NRows_Matrix can be set to an 
                                        ... arbitrary value when YOffset is non-empty. Scalar; type 
                                        ... int32.
            SkinSegmentConfig_Args      ... Skin-segmentation configurations; scalar struct. Struct
                                        ... assigned by function SkinSegment_ConfigSetup.
        );

%Compiled functions disabled or code generation running
else

    %Note: SkinSegmentMask_Ops is a custom function located within folder FacePulseRate.
    [IsSkinMask, TrueCount, YSingle, CbSingle, CrSingle, HSingle, SSingle, IsSkinMask_Range] = ...
        SkinSegmentMask_Ops( ...
            RUint8, ... 
            GUint8, ...
            BUint8, ... 
            YSingle, ... 
            CbSingle, ...
            CrSingle, ...
            HSingle, ... 
            SSingle, ...
            IsSkinMask_Range, ... 
            NRows_Matrix, ...     
            NCols_Matrix, ...
            CountTrueTF, ...
            TailoredThresholdsTF, ...
            ReturnYTF, ...
            ReturnCbCrTF, ...
            ReturnHSTF, ...
            TailoredThresholdsSevereTF, ...            
            MorphCloseSevereTF, ... 
            XOffset, ...
            YOffset, ...
            SkinSegmentConfig_Args ... 
        ); 
end
    
    
end %end function

