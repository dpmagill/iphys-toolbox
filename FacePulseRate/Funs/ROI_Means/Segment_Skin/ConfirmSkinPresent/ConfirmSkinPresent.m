function varargout = ConfirmSkinPresent(SkinSegmentConfig, FaceAlgorithm, varargin) %#codegen                             
%ConfirmSkinPresent   Determine whether an ROI should be considered valid based upon the proportion
%                     of pixels classified as skin within the ROI.
%    
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by functions FaceDetect_ROIValidate,   
%    SkinDetect_ROIValidate, and ROIMeans_TakeMeans_ROIValidate.
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
%    Return a true/false determination on whether an ROI is valid by determining whether the
%    proportion of pixels classified as skin within the ROI is above the specified threshold.
%
%    The number of inputs to the function is variable. The number of inputs depends on the 
%    information currently available regarding the classification of pixels in the ROI as skin or 
%    non-skin. If the classification has already been conducted, this is entered as input to the 
%    function, and the function moves to calculate the proportion of pixels classified as skin out 
%    of all pixels. This is termed "condition 1". If the classification is not available, 
%    information needed to conduct the classification is entered as input to the function, and the 
%    classification is conducted before calculating the proportion. This is termed "condition 2". 
%
%    If condition 2 is used, an additional skin-classification method can be specified,  
%    specifically, the use of the skin-detection algorithm to refine the skin-segmentation mask. If 
%    argument SkinDetectionThresholdsTF is true, the skin-detection algorithm will be used. 
%
%    If condition 2 is used, the color channels produced during the classification operation will 
%    be returned as they can be reused in other functions.
%   
%
%    Accuracy
%    --------
%
%    If there are fewer skin-color samples than required for tailored skin segmentation, the 
%    proportion of pixels may be less accurate (less conservative). Whether the required number of 
%    skin-color samples has been satisfied is indicated by 
%    SkinSegmentConfig.TailoredData.OpsReadyTF.
%
%    If there are fewer skin-color samples than required for skin detection (see function 
%    ConfirmSkinPresent_SkinDetectReject), the proportion of pixels may be less accurate (less 
%    conservative. Whether the required number of skin-color samples has been satisfied is 
%    indicated by SkinDetectConfig.Thresholds.SkinColorSamples_NThresholdPassedTF.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code-generation settings %%%%%%

%Inline function
coder.inline('always');

%Declare variables:

%                                    Upp. Bounds    Var. Size (T/F)
coder.varsize('IsSkinMask_Range',    [5000, 5000],    [1, 1]);


%%%%%% Parse inputs %%%%%%

%%%%%% --- Determine whether to use condition 1 or condition 2 %%%%%%

%In condition 1, skin-classification infomation is provided as input. This information can either 
%be the number of pixels classified as skin or the skin-segmentation mask, from which the number of 
%pixels classified as skin can be obtained. In condition 2, information to conduct the skin 
%classification, namely, the color channels of the ROI, is provided as input. The condition can be 
%determined according to the number of inputs to the function.

%Number of inputs
%Note: variable NArgin is used in two places in the function.
NArgin = nargin;

%Condition according to the number of inputs
%If the number of inputs is 6, condition 1 is used.
%Note: variable Condition1TF is used in two places in the function.
Condition1TF = NArgin == 6;


%%%%%% Condition 1: Classification information available %%%%%%

%Determine the proportion of pixels classified as skin within the ROI. If the number of pixels 
%classified as skin was not provided as input, then the skin-segmentation mask would have been
%provided as input. In the latter case, obtain the number of pixels classified as skin from the
%skin-segmentation mask.

%If condition 1
if Condition1TF 

    %Argument 3
    %Skin-segmentation mask.
    %Type logical.
    IsSkinMask = varargin{1}; 
 
    %Argument 4
    %Count of pixels classified as true by skin-segmentation mask
    %This can be provided in place of providing the skin-segmentation mask.
    %-1 is used to ignore.
    %Type single.
    NSkinPixels = varargin{2};    
    
    %Argument 5
    %Number of rows of the skin-segmentation mask.
    NRows_Matrix = varargin{3};
    
    %Argument 6
    %Number of columns of the skin-segmentation mask.
    NCols_Matrix = varargin{4};     
   
    %Count of pixels classified as skin    
    %If count of pixels classified as skin not provided
    %(-1 is flag that count is not provided).
    if NSkinPixels == -1
        
        NSkinPixels = single( nnz(IsSkinMask) );       
    end
  
    
%%%%%% Condition 2: Classification information not available; assign here %%%%%%    
 
%In this condition, neither then number of pixels classified as skin nor the skin-segmentation mask
%was provided as input. In this case, assign the skin-segmentation mask necessary to calculate the
%number of pixels classified as skin. The skin-segmentation mask is assigned by the 
%skin-segmentation algorithm.

%If this condition is used, an additional skin-classification method can be specified,  
%specifically, the use of the skin-detection algorithm to refine the skin-segmentation mask. If 
%argument SkinDetectionThresholdsTF is true, the skin-detection algorithm will be used. The 
%skin-detection algorithm is applied by function ConfirmSkinPresent_SkinDetectReject.

%If condition 2    
else 
    
    %Arguments 3 to 5
    %Input image, in RGB colorspace channels, to be segmented; M x N matrices; type uint8.
    RUint8 = varargin{1}; 
    GUint8 = varargin{2};
    BUint8 = varargin{3};

    %Argument 6
    %Number of rows of an input matrix.
    NRows_Matrix = varargin{4};
    
    %Argument 7
    %Number of columns of an input matrix.
    NCols_Matrix = varargin{5};    
    
    %Argument 8
    %Flag whether to use tailored thresholds during segmentation.
    %Tailored thresholds include the tailored-YCbCr thresholds and the tailored-HS tresholds.
    TailoredThresholdsTF = varargin{6}; 
 
    %Argument 9
    %Flag whether to return the Y channel of the YCbCr colorspace after segmentation. This
    %variable is assigned during a step of the skin-segmentation operation. For efficiency, it can
    %returned to be reused in other functions that use this color information.
    %Scalar; type logical.
    ReturnYTF = varargin{7};
    
    %Argument 10    
    %Flag whether to return the Cb and Cr channels of the YCbCr colorspace after segmentation. This
    %variable is assigned during a step of the skin-segmentation operation. For efficiency, it can
    %returned to be reused in other functions that use this color information. 
    %Scalar; type logical.
    ReturnCbCrTF = varargin{8};
    
    %Argument 11
    %Flag whether to return the H and S channels of the HSV colorspace after segmentation. This
    %variable is produced during a step of the skin-segmentation operation. For efficiency, it can
    %returned to be reused in other functions that use this color information. 
    %Scalar; type logical.
    ReturnHSTF = varargin{9};    
    
    %Argument 12  
    %Flag whether to apply thresholds from the skin-detection algorithm to refine the inspection
    %Scalar; type logical.    
    SkinDetectionThresholdsTF = varargin{10}; 
    
    %Argument 13
    %Configurations for the skin-detection algorithm, which are used if SkinDetectionThresholdsTF 
    %is true.
    SkinDetectConfig = varargin{11}; 
        
    %%%%%% --- Assign skin-segmentation mask %%%%%%

    %Return a logical matrix, i.e., a skin-segmentation mask, where pixels classified as skin are 
    %true. Also return ImageToInspect broken down by channel in the YCbCr colorspace for reuse by 
    %other functions.
    
    %Arguments to function SkinSegmentMask, which returns the skin-segmentation mask:
    
    %Argument TailoredThresholdsTF is specified as an argument to the current function.
    %This argument specifies whether tailored thresholds should be used for skin segmentation.

    %Argument ReturnYTF is specified as an argument to the current function.
    %This argument specifies whether the Y channel of the YCbCr colorspace should be returned. 
    %This channels, assigned during skin-segmentation operations, would be returned so that it
    %could be reused by other functions.    
    
    %Argument ReturnCbCrTF is specified as an argument to the current function.
    %This argument specifies whether the Cb and Cr channels of the YCbCr colorspace should be 
    %returned. These channels, assigned during skin-segmentation operations, would be returned so
    %that they could be reused by other functions. 
    
    %Argument ReturnHSTF is specified as an argument to the current function.
    %This argument specifies whether the H and S channel sof the HSV colorspace should be returned.  
    %These channels, assigned during skin-segmentation operations, would be returned so that they 
    %could be reused by other functions. 
         
    %Assign as variable for code-generation purpose
    IsSkinMask_Range = logical([]);
    
    %Note: SkinSegmentMask is a custom function located within folder FacePulseRate.
    [IsSkinMask,         ... Skin-segmentation mask; M x N matrix, type logical
     TrueCount,          ... Count of pixels classified as skin; scalar, type uint32
     YSingle,            ... Y channel of the YCbCr colorspace; M x N matrix, type single
     CbSingle,           ... Cb channel of the YCbCr colorspace; M x N matrix, type single
     CrSingle,           ... Cr channel of the YCbCr colorspace; M x N matrix, type single
     HSingle,            ... H channel of the HSV colorspace; M x N matrix, type single
     SSingle,            ... S channel of the HSV colorspace; M x N matrix, type single 
     IsSkinMask_Range] = ... Skin-segmentation mask based upon local range threshold; M x N matrix, 
                         ... type logical.
        SkinSegmentMask( ...
            RUint8,                                  ... Bounded frame in RGB colorspace separated 
                                                     ... by channel; type uint8.
            GUint8, ...
            BUint8, ... 
            single([]),                              ... Unused arguments                              
            single([]), ...
            single([]), ...
            single([]), ...                                
            single([]), ...
            IsSkinMask_Range, ...                    
            NRows_Matrix,                            ... Number of rows of an input matrix      
            NCols_Matrix,                            ... Number of columns of an input matrix
            true,                                    ... Whether to return a count of pixels
                                                     ... classified as skin.
            TailoredThresholdsTF,                    ... Whether to use YCbCr thresholds that are 
                                                     ... tailored.
            ReturnYTF,                               ... Whether to return Y channel of the YCbCr 
                                                     ... colorspace.
            ReturnCbCrTF,                            ... Whether to return Cb and Cr channels of 
                                                     ... the YCbCr colorspace. 
            ReturnHSTF,                              ... Whether to return the H and S channels of 
                                                     ... the HSV colorspace. 
            true,                                    ... Whether to use severe tailored thresholds           
            true,                                    ... Whether the morphological close operation  
                                                     ... will be conducted with a high level of 
                                                     ... severity. 
            int32(-1),                               ... Optional X-coordinate offset; specify -1 
                                                     ... to ignore; type int32.
            int32(-1),                               ... Optional Y-coordinate offset; specify -1 
                                                     ... to ignore; type int32.
            SkinSegmentConfig.Args,                  ... Skin-segmentation configurations
            SkinSegmentConfig.UseCompiledFunctionsTF ... Whether to use compiled functions            
        );        

    %%%%%% --- Determine the number of pixels classified as skin %%%%%%

    %%%%%% >>>>>> Refine classification with the skin-detection algorithm %%%%%%

    %Apply thresholds from the skin-detection algorithm to refine the skin-segmentation mask.
    %Return the number of pixels present after this refinement.
    
    %If refinement of the skin-segmentation mask by the skin-detection algorithm is enabled
    if SkinDetectionThresholdsTF && ...
       SkinDetectConfig.Thresholds.SetTF %if the thresholds required by the algorithm have been set
        
        %If compiled functions are enabled
        if SkinDetectConfig.UseCompiledFunctionsTF
        
            %Scalar; type int32.
            %Note: ConfirmSkinPresent_SkinDetectReject_mex is a custom compiled function located 
            %within folder 'FacePulseRate'. For source code, see file 
            %ConfirmSkinPresent_SkinDetectReject.m.           
            NSkinPixels_int32 = ...
                ConfirmSkinPresent_SkinDetectReject_mex(IsSkinMask, RUint8, GUint8, BUint8, ...
                    YSingle, CbSingle, CrSingle, NRows_Matrix, NCols_Matrix, SkinDetectConfig);

        %If compiled functions are not enabled         
        else
            
            %Scalar; type int32.            
            %Note: ConfirmSkinPresent_SkinDetectReject is a custom function located within folder
            %'FacePulseRate'.
            NSkinPixels_int32 = ...
                ConfirmSkinPresent_SkinDetectReject(IsSkinMask, RUint8, GUint8, BUint8, ...
                    YSingle, CbSingle, CrSingle, NRows_Matrix, NCols_Matrix, SkinDetectConfig);           
        end
            
        %Number of pixels classified as skin 
        %Cast to type single.
        %Scalar; type single.
        NSkinPixels = single(NSkinPixels_int32);    

    %%%%%% >>>>>> Do not refine with the skin-detection algorithm %%%%%%        
        
    %If refinement of the skin-segmentation mask by the skin-detection algorithm is not enabled 
    %(Or if the thresholds required by the algorithm have not yet been set).
    else   
    
        %Number of pixels classified as skin 
        %Scalar; type single.
        NSkinPixels = single(TrueCount);
    end
end
  

%%%%%% Determine whether ROI contains skin %%%%%%

%%%%%% --- Determine proportion of ROI classified as skin %%%%%%

%Determine the proportion of pixels classified as skin out of all pixels of the ROI.

%Cast to a floating-point type to permit decimal.
%Scalar; type single.
%Note: NRows_Matrix and NCols_Matrix are type int32.
proportionSkin = NSkinPixels / single(NRows_Matrix * NCols_Matrix);

%%%%%% --- Specify minimum-proportion threshold to apply %%%%%%

%Specify the minimum proportion of pixels classified as skin to use as the threshold. If the 
%proportion of pixels is above this threshold, the ROI will be considered valid.

%Specify the thresholds according to the detection algorithm by which the ROI was returned or the  
%stage of ROI processing the ROI has undergone. The thresholds are set by function 
%SkinSegment_ConfigSetup. For details on the thresholds used for each case, see function
%SkinSegment_ConfigSetup.

switch FaceAlgorithm
    
    %ROI returned by primary face-detection algorithm (see function FaceDetect_ROIValidate)
    case 'p' 
    
        thresholdContainsSkin = SkinSegmentConfig.ConfirmSkin.ProportionThresholdPrimary;            

    %ROI returned by secondary #1 face-detection algorithm (see function FaceDetect_ROIValidate)
    case '1' 
 
        thresholdContainsSkin = SkinSegmentConfig.ConfirmSkin.ProportionThresholdSecondary1;

    %ROI returned by secondary #2 face-detection algorithm (see function FaceDetect_ROIValidate)
    case '2' 
 
        thresholdContainsSkin = SkinSegmentConfig.ConfirmSkin.ProportionThresholdSecondary2;
    
    %ROI returned by skin-detection algorithm setting (see function SkinDetect_ROIValidate)    
    case 's'   
    
        thresholdContainsSkin = SkinSegmentConfig.ConfirmSkin.ProportionThresholdSkin;            

    %ROI after all modifications when means are taken for pulse-rate purposes (see function 
    %ROIMeans_TakeMeans_ROIValidate)    
    case 'm' 
        
        thresholdContainsSkin = SkinSegmentConfig.ConfirmSkin.ProportionThresholdMeans;            
end

%%%%%% --- Make determination on whether the ROI is valid %%%%%%

%Consider the ROI valid if the proportion of pixels classified as skin exceeds the specified 
%threshold.

%If the proportion exceeds the threshold
if proportionSkin > thresholdContainsSkin

    %Scalar; type logical.
    SkinColorTF = true;

else

    SkinColorTF = false;
end


%%%%%% Assign output arguments %%%%%%

%If condition 1
if Condition1TF  
    
    varargout = ...
        {SkinColorTF,     ... Determination on whether the ROI is valid; scalar, type logical
         proportionSkin}; %   The proportion of skin on which the determination was made; scalar, 
                          %   type single.
             
%If condition 2    
else
   
    varargout = ...
        {SkinColorTF,       ... Determination on whether the ROI is valid; scalar, type logical
         proportionSkin,    ... The proportion of skin on which the determination was made; scalar,
                            ... type single.
         ... The following variables were assigned for the skin-segmentation operations; they are
         ... returned so that other functions can reuse this information:
         IsSkinMask,        ... Skin-segmentation mask; M x N matrix, type logical
         YSingle,           ... ImageToInspect in YCbCr colorspace; M x N matrices, type single
         CbSingle,          ... 
         CrSingle,          ...
         HSingle,           ... H channel of ImageToInspect in HSV colorspace; M x N matrix, type 
                            ... single.
         SSingle,           ... S channel of ImageToInspect in HSV colorspace; M x N matrix, type 
                            ... single. 
         IsSkinMask_Range}; %   Skin-segmentation mask based only on local range; M x N matrix, 
                            %   type logical.
end


end %end function

