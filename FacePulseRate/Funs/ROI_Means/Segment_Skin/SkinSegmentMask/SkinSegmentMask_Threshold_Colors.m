function [IsSkinMask, YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single, ...
          SBounded_Single] = ...
             SkinSegmentMask_Threshold_Colors(RBounded_Uint8, GBounded_Uint8, BBounded_Uint8, ...                
                 YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single, ...
                 SBounded_Single, NRows_Matrix, NCols_Matrix, NElements_Matrix, ... 
                 TailoredThresholdsTF, DontUseTailoredTF, YCbCrThresholds_Generic, ...
                 YCbCrThresholds_Tailored, ReturnYTF, ReturnCbCrTF, ReturnHSTF, ...
                 HSThresholds_Generic, HSThresholds_Tailored, UseLinIdxTF, XOffset, YOffset) 
                 %#codegen                                 
%SkinSegmentMask_Threshold_Colors   Return a skin-segmentation mask by comparing channels of the    
%                                   YCbCr and HSV colorspaces of the input image to specified 
%                                   thresholds.                                                                               
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinSegmentMask_Threshold.
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
%    Return a logical matrix (IsSkinMask), or skin-segmentation mask, by comparing the YCbCr and HS  
%    channels of the input image to the YCbCr and HS thresholds, respectively. If a given pixel of  
%    the input image passes each of the YCbCr thresholds and the H and S thresholds, it is   
%    classified as true, or as skin. Additionally, return some of the variables assigned in the 
%    current function for reuse by other functions. For a detailed description of the assumptions 
%    of using these thresholds for skin segmentation, see function SkinSegmentMask_Ops.
%
%    First, the RGB colorspace variables of the input image (RBounded_Single, GBounded_Single, 
%    BBounded_Single) are converted to the YCbCr colorspace and the H and S channels of the HSV 
%    colorspace. Second, each pixel of the converted colorspaces is compared to the tresholds. For 
%    the YCbCr colorspaces, either the generic or tailored versions of the thresholds are used. The 
%    tailored versions are used when TailoredThresholdsTF == true and DontUseTailoredTF == false.
%    The generic versions are used otherwise. The H threshold is used when, as with the tailored 
%    YCbCr thresholds, TailoredThresholdsTF == true and DontUseTailoredTF == false.
%
%    The colorspace variables of the input that are assigned in the current function can be 
%    returned for reuse by other functions. When ReturnYTF == true, the Y channel of the YCbCr   
%    colorspace is returned. When ReturnCbCrTF == true, the Cb and Cr channels of the YCbCr  
%    colorspace are also returned. When ReturnHSTF == true, the H and S channels of HSV colorspace  
%    are returned. ReturnYTF, ReturnCbCrTF, and ReturnHSTF are arguments to function 
%    SkinSegmentMask. 
%
%    For efficiency, calling functions are implemented only to request colorspace variables that 
%    they can reuse. This is because assignment of a colorspace variable requires additional 
%    assignement beyond the operations conducted in the current function. Specifically, in the
%    current function, conversion to colorspaces occurs pixel-by-pixel; however, to return the
%    colorspace variable, a separate variable needs to be assigned to store all of the pixels of 
%    the input image.
%
%    In the code blocks for the compiled version of the function, some if-else branches may not be
%    used because the particular conditions may not be specified by any calling functions within 
%    FacePulseRate. These if-else branches are still provided for robustness.
%
%    Operations are divided according to whether colorspace conversions need to be made or whether
%    variables in the necessary colorspaces were provided as input.
%
%    -- Colorspace Conversions --
%
%    The RGB to YCbCr conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab 
%    algorithm is derived from Poynton (1996, p. 175 - 176). 
%
%    RGB to HS conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a 
%    local function within Matlab function rgb2hsv. Note that there are several versions of 
%    function rgb2hsv; the version from which the function was extracted is the version used for 
%    code generation. As of Matlab version 2020a, the file location is 
%    R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978).
%
%    -- Optimizations --
%
%    The current function is highly optimized because of the rather time-consuming tasks. To view
%    more straightforward code, see the bottom of the function for the vectorized (and less
%    efficient) version of the code -- although vectorized code is less efficient for the compiled
%    version of the function, it is more efficient when running Matlab code. To achieve higher
%    efficiency, all operations are placed within one loop to reduce the number of times vectors
%    are indexed. One characteristic of the thresholds used is that a pixel is classified as skin
%    (true) only if each of the thresholds returns true. The code is optimized to take advantage of
%    this by skipping any conversions and comparisons for a given pixel once any threshold returns 
%    false.
%
%        RGB to YCbCr Algorithm Optimation 
% 
%    (1) Code from function rgb2ycbcr only relevent to uint8 input was extracted (although the
%        input to this function is type single, it was converted to type single from uint8 before
%        entry to the function).
%    (2) Operations are conducted in type single, whereas, in function rgb2ycbcr, function  
%        imlincomb is used, which conducts operations in type double.
%    (3) No conversion is made back to type uint8. This avoids the resourse-intensive conversion 
%        from floating-point to integer. As all the functions in FacePulseRate that use this      
%        function use YCbCr in type single, no conversion to integer is needed.    
%    (4) R, G, and B are handled as separate variables rather than as a concatenated 3D variable.
%        This reduces time otherwise taken by repeatedly indexing into a concatenated 3D variable.   
%    (5) The Y, Cb, and Cr pages are not concatenated into a 3D output variable. By not   
%        concatenating, time is also saved in functions (outside of the current function) that use  
%        the output because nearly all functions that use the output use the three pages  
%        separately, so they do not have to separate the pages or index into the concatenated 
%        output.
%
%        C-Compiled Code
%
%    (1) C-compiled code may conduct operations faster than Matlab code when using type single
%        (see https://www.mathworks.com/company/newsletters/articles/accelerating-matlab-algorithms-and-applications.html).       
%    (2) It has been observed through testing that conversion from type uint8 to type single, which 
%        is necessary before the RGB-to-YCbCr conversion) is faster when run in Matlab code than
%        C-compiled code; therefore, this conversion is done in Matlab code and passed as an 
%        argument to the current function.
%
%        Use in External Functions
%
%    (1) This function returns the individual color channels rather than the concatenated image.  
%        Because function FacePulseRate assesses color channels individually in its operations, it 
%        is faster if it doesn't have to separate the color channels. 
%    (2) All functions in FacePulseRate that call this function use YCbCr in type single. As this 
%        function returns type single, this avoids many functions converting from type uint8 to 
%        type single.
%    
%
%    References
%    ----------
%
%    Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons.
%
%    Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12-
%    19.
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
    

%%%%%% Operations if all color channels used in skin segmentation are provided as input %%%%%%

if ~ isempty(YBounded_Single)  && ...
   ~ isempty(CbBounded_Single) && ...
   ~ isempty(CrBounded_Single) && ...
   ~ isempty(HBounded_Single)  && ...
   ~ isempty(SBounded_Single)

    %Skin-segmentation mask based upon color thresholds
    %M x N matrix; type logical.
    %Note: SkinSegmentMask_Threshold_Colors_NoConvert is a custom function located within folder
    %'FacePulseRate'.
    IsSkinMask = ...
        SkinSegmentMask_Threshold_Colors_NoConvert(YBounded_Single, CbBounded_Single, ...
            CrBounded_Single, HBounded_Single, SBounded_Single, NRows_Matrix, NCols_Matrix, ...
            NElements_Matrix, TailoredThresholdsTF, DontUseTailoredTF, YCbCrThresholds_Generic, ...
            YCbCrThresholds_Tailored, HSThresholds_Generic, HSThresholds_Tailored, UseLinIdxTF, ...
            XOffset, YOffset);            

    %As these channels were provided as input, they are not provided back as output.       
    YBounded_Single  = coder.const( single([]) );
    CbBounded_Single = coder.const( single([]) );
    CrBounded_Single = coder.const( single([]) );
    HBounded_Single  = coder.const( single([]) );
    SBounded_Single  = coder.const( single([]) );
    
    
%%%%%% Operations if color channels used in skin segmentation need to be produced %%%%%%

else
    
    %Skin-segmentation mask based upon color thresholds
    %M x N matrix; type logical.
    %Note: SkinSegmentMask_Threshold_Colors_Convert is a custom function located within folder
    %'FacePulseRate'.     
    [IsSkinMask, YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single, ...
     SBounded_Single] = ...
        SkinSegmentMask_Threshold_Colors_Convert(RBounded_Uint8, GBounded_Uint8, ...                
            BBounded_Uint8, NRows_Matrix, NCols_Matrix, NElements_Matrix, TailoredThresholdsTF, ...
            DontUseTailoredTF, YCbCrThresholds_Generic, YCbCrThresholds_Tailored, ReturnYTF, ...
            ReturnCbCrTF, ReturnHSTF, HSThresholds_Generic, HSThresholds_Tailored, UseLinIdxTF, ...
            XOffset, YOffset);        
end
          

end %end function 


