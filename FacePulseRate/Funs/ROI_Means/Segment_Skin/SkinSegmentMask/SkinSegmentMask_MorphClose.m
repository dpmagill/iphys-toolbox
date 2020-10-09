function IsSkinMask = ...
             SkinSegmentMask_MorphClose(IsSkinMask, NRows_Matrix_int32, MorphCloseSevereTF, ...
                 MorphCloseNeighborhoodWidth) %#codegen
%SkinSegmentMask_MorphClose    Morphologically close regions with patchy skin classification to 
%                              refine the skin-segmentation mask previously assigned by comparison 
%                              to thresholds.
%                                                                          
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinSegmentMask_Ops.
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
%    For a description of the assumptions behind the use of a morphological close to classify
%    pixels as skin, see function SkinSegmentMask_Ops.  
%
%    Apply a morphological close operation to the skin-segmentation mask resulting from thresholds
%    previously applied (by function SkinSegmentMask_Threshold). The morphological close tends to 
%    fill in classification holes, where a hole is loosely defined as a region of pixels classified 
%    as true that are enclosed by pixels classified as false. The morphological close fills in 
%    holes only below a specified size (specified by a morphological structuring element), such 
%    that many holes are not filled.    
%     
%    A morphological dilation followed by a morphological erosion is conducted to perform the  
%    morphological close. These operations are conducted by Matlab functions imerode and imdilate.
%    Although a Matlab function is available to conduct a close (imclose), it has been observed  
%    that using imerode followed by imdilate is more efficient.
%
%    For a description of the choice of structuring element used in the morphological close, see 
%    the description below in section "Assign structuring element".  
%
%    -- Structuring Element Specifications --
%
%    - Severity == high:
%
%    Use liberal dilation and erosion to mask non-skin pixels 
%    Do so by using a large morphological structuring element (SE), which specifies the size of    
%    dilation and erosion to carry out on each pixel (where pixel == 0). High severity may favor
%    the rejection of non-skin pixels over the retention of of true-skin pixels. Function 
%    FaceDetect and SkinDetect specify skin segmentation with high severity. This severity may be  
%    useful for these functions because the priority in these functions is avoiding non-skin 
%    pixels rather than retaining as many pixels as possible that are actually skin.    
%
%    - Severity == low:
%
%    Use moderate dilation and erosion to mask non-skin pixels.
%    Do so by using a medium morphological structuring element (SE), which specifies the size of  
%    dilation to carry out on each pixel (where pixel == 0). Compared to high severity, low 
%    severity is intended to strike a balance between rejecting pixels and accepting pixels that   
%    are actually skin. Function ROIMeans_TakeMeans specifies skin segmentation with low severity. 
%    This low severity may be useful for the purpose of function ROIMeans_TakeMeans, which is to   
%    calculate the accurate mean of an ROI. The ROIs that ROIMeans_TakeMeans processes have been 
%    previously processed by functions FaceDetect and SkinDetect, which specify high severity, so 
%    these ROIs may already be expected to have benefited from adjustment based upon avoidance of  
%    non-skin pixels.
%
%    -- Notes -- 
%
%    By default, Matlab's morphological operations act on true values, not false values, although
%    false values (non-skin) are the target.
%   
%    For Matlab documentation discussing removal of patchy regions, see the Matlab documentation
%    topic "Detect Cell Using Edge Detection and Morphology" 
%    (https://www.mathworks.com/help/images/detecting-a-cell-using-image-segmentation.html).
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


%%%%%% Binary Packing %%%%%%

%Note: For use as a Matlab function rather than code generation for a mex function, it is faster 
%not to pack the logical matrix.

%Pack logical image for increased performance of morphological functions 
IsSkinMask_PixelColorPacked = bwpack(IsSkinMask);


%%%%%% Assign structuring element %%%%%%

%Because structuring element objects are compile-time constants, a fixed number of structuring  
%element objects are made available, each of which has a corresponding function. The function  
%with the structuring element closest in size to the specified structuring element size is used.  
 
%Select function from available functions
%Select the function with the SE width most similar to the specified SE width.
%Local function.
%Scalar; type int16.
functionWidthToUse = SelectFunction(MorphCloseNeighborhoodWidth, MorphCloseSevereTF);


%%%%%% Erosion followed by dilation %%%%%%

%Cast to type double for use by function imerode
%Scalar; type double.
NRows_Matrix = double(NRows_Matrix_int32); 

%%%%%% --- High severity erosion and dilation %%%%%% 
if MorphCloseSevereTF
 
    %Use function corresponding to closest SE width
    switch functionWidthToUse

        %Square structuring element with width of 12 pixels    
        case 12

            %Packed binary image
            %Local function.
            %Type uint32.
            IsSkinMask_PixelColor_DilatePacked = ...
                ErodeAndDilate_SESquare12(IsSkinMask_PixelColorPacked, NRows_Matrix);        
        
        %Square structuring element with width of 22 pixels    
        case 22

            %Packed binary image
            %Local function.
            %Type uint32.
            IsSkinMask_PixelColor_DilatePacked = ...
                ErodeAndDilate_SESquare22(IsSkinMask_PixelColorPacked, NRows_Matrix);

        %Square structuring element with width of 32 pixels    
        case 32

            %Packed binary image
            %Local function.
            %Type uint32.
            IsSkinMask_PixelColor_DilatePacked = ...
                ErodeAndDilate_SESquare32(IsSkinMask_PixelColorPacked, NRows_Matrix);            
            
        %Square structuring element with width of 50 pixels    
        case 50

            %Packed binary image
            %Local function.
            %Type uint32.
            IsSkinMask_PixelColor_DilatePacked = ...
                ErodeAndDilate_SESquare50(IsSkinMask_PixelColorPacked, NRows_Matrix);

        %(Required for code generation)    
        otherwise

            return
    end 

    
%%%%%% --- Low severity erosion and dilation %%%%%%   
else
        
    %Use function corresponding to closest SE radius
    switch functionWidthToUse

        %Disk-shaped structuring element with radius of 4 pixels    
        case 4
            
            %Packed binary image
            %Local function.
            %Type uint32.
            IsSkinMask_PixelColor_DilatePacked = ...
                ErodeAndDilate_SEDisk4(IsSkinMask_PixelColorPacked, NRows_Matrix);        
        
        %Disk-shaped structuring element with radius of 6 pixels    
        case 6
            
            %Packed binary image
            %Local function.
            %Type uint32.
            IsSkinMask_PixelColor_DilatePacked = ...
                ErodeAndDilate_SEDisk6(IsSkinMask_PixelColorPacked, NRows_Matrix);

        %Disk-shaped structuring element with radius of 10 pixels    
        case 10
            
            %Packed binary image
            %Local function.
            %Type uint32.
            IsSkinMask_PixelColor_DilatePacked = ...
                ErodeAndDilate_SEDisk10(IsSkinMask_PixelColorPacked, NRows_Matrix);           
            
        %Disk-shaped structuring element with radius of 14 pixels    
        case 14
            
            %Packed binary image
            %Local function.
            %Type uint32.
            IsSkinMask_PixelColor_DilatePacked = ...
                ErodeAndDilate_SEDisk14(IsSkinMask_PixelColorPacked, NRows_Matrix);

        %(Required for code generation)    
        otherwise

            return
    end        
end

%%%%%% --- Unpack %%%%%%   

%Unpack packed binary image
%M x N matrix; type logical.
IsSkinMask = bwunpack(IsSkinMask_PixelColor_DilatePacked, NRows_Matrix);
    

end %end main function


%=============================================================================================
%Local functions 
%=============================================================================================


%=============================================================================================
function functionWidthToUse = SelectFunction(MorphCloseNeighborhoodWidth, MorphCloseSevereTF)
%SelectFunction    Select the function with the SE width most similar to 
%                  MorphCloseNeighborhoodWidth.   
%
%    Description:
%
%    Select the size of the structuring element to use. The size is partly determined according to
%    MorphCloseSevereTF. 


%Inline function
coder.inline('always');


%%%%%% High severity %%%%%%

if MorphCloseSevereTF

    %Scalars; type int16.
    Diff12 = abs(12 - MorphCloseNeighborhoodWidth);
    Diff22 = abs(22 - MorphCloseNeighborhoodWidth);
    Diff32 = abs(32 - MorphCloseNeighborhoodWidth);    
    Diff50 = abs(50 - MorphCloseNeighborhoodWidth);

    if Diff12 < Diff22

        functionWidthToUse = int16(12);
        
        Diff = Diff12;
    else

        functionWidthToUse = int16(22); 
        
        Diff = Diff22;        
    end

    if Diff32 < Diff

        functionWidthToUse = int16(32);
        
        Diff = Diff32;         
    end    
    
    if Diff50 < Diff

        functionWidthToUse = int16(50);
    end

    %Note: Use this pattern for adding additional SEs
    %{
    if DiffX < Diff

        functionWidthToUse = int16(X);
    
        Diff = DiffX; %include this line if this is not the last condition
    end
    %}

    
%%%%%% Low severity %%%%%%

else

    %As low severity uses a structuring element specified by radius, divide width by 2
    %Optimize division by two by bitwise operation.
    %Scalar; type int16.
    MorphCloseNeighborhoodRadius = bitshift(MorphCloseNeighborhoodWidth, -1);     
    
    %Scalars; type int16.
    Diff4  = abs(4  - MorphCloseNeighborhoodRadius);
    Diff6  = abs(6  - MorphCloseNeighborhoodRadius);
    Diff10 = abs(10 - MorphCloseNeighborhoodRadius);    
    Diff14 = abs(14 - MorphCloseNeighborhoodRadius);

    if Diff4 < Diff6

        functionWidthToUse = int16(4);

         Diff = Diff4;       
    else

        functionWidthToUse = int16(6);  
        
        Diff = Diff6;
    end

    if Diff10 < Diff

        functionWidthToUse = int16(10);
        
        Diff = Diff10;        
    end     
    
    if Diff14 < Diff

        functionWidthToUse = int16(14);    
    end    
    
    %Note: Use this pattern for adding additional SEs
    %{
    if DiffX < Diff

        functionWidthToUse = int16(X);
    
        Diff = DiffX; %include this line if this is not the last condition
    end
    %}
end



end %end local function


%=============================================================================================
function [IsSkinMask_PixelColor_DilatePacked] = ...
             ErodeAndDilate_SESquare12(IsSkinMask_PixelColorPacked, NRows_Matrix)
%ErodeAndDilate_SESquare12    Erode and dilate with square structuring element of width 12.


%Inline function
coder.inline('always');


persistent SE

if isempty(SE)
    
    %Assign structuring element 
    %For code generation, the structuring element must be a compile-time constant.
    SE = ...
        strel('square', ... shape of structuring element
            12          ... width of structuring element
        );               
end

%Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_ErodePacked = ... eroded logical image
    imerode( ...
       IsSkinMask_PixelColorPacked, ... logical image
       SE,                          ... structuring element
       'ispacked',                  ... flag for packed image
       NRows_Matrix                 ... number of rows in unpacked image
    );  

%Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_DilatePacked =       ... dilated logical image
    imdilate( ...
        IsSkinMask_PixelColor_ErodePacked, ... 
        SE,                                ... structuring element
        'ispacked'                         ... flag for packed image
    );      

    
end %end local function


%=============================================================================================
function [IsSkinMask_PixelColor_DilatePacked] = ...
             ErodeAndDilate_SESquare22(IsSkinMask_PixelColorPacked, NRows_Matrix)
%ErodeAndDilate_SESquare22    Erode and dilate with square structuring element of width 22.


%Inline function
coder.inline('always');


persistent SE

if isempty(SE)
    
    %Assign structuring element 
    %For code generation, the structuring element must be a compile-time constant.
    SE = ...
        strel('square', ... shape of structuring element
            22          ... width of structuring element
        );               
end

%Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_ErodePacked = ... eroded logical image
    imerode( ...
       IsSkinMask_PixelColorPacked, ... logical image
       SE,                          ... structuring element
       'ispacked',                  ... flag for packed image
       NRows_Matrix                 ... number of rows in unpacked image
    );  

%Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_DilatePacked =       ... dilated logical image
    imdilate( ...
        IsSkinMask_PixelColor_ErodePacked, ... 
        SE,                                ... structuring element
        'ispacked'                         ... flag for packed image
    );      

    
end %end local function
 

%=============================================================================================
function [IsSkinMask_PixelColor_DilatePacked] = ...
             ErodeAndDilate_SESquare32(IsSkinMask_PixelColorPacked, NRows_Matrix)
%ErodeAndDilate_SESquare32    Erode and dilate with square structuring element of width 32.


%Inline function
coder.inline('always');


persistent SE

if isempty(SE)
    
    %Assign structuring element 
    %For code generation, the structuring element must be a compile-time constant.
    SE = ...
        strel('square', ... shape of structuring element
            32          ... width of structuring element
        );               
end

%Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_ErodePacked = ... eroded logical image
    imerode( ...
       IsSkinMask_PixelColorPacked, ... logical image
       SE,                          ... structuring element
       'ispacked',                  ... flag for packed image
       NRows_Matrix                 ... number of rows in unpacked image
    );  

%Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_DilatePacked =       ... dilated logical image
    imdilate( ...
        IsSkinMask_PixelColor_ErodePacked, ... 
        SE,                                ... structuring element
        'ispacked'                         ... flag for packed image
    );      

    
end %end local function


%=============================================================================================
function [IsSkinMask_PixelColor_DilatePacked] = ...
             ErodeAndDilate_SESquare50(IsSkinMask_PixelColorPacked, NRows_Matrix)
%ErodeAndDilate_SESquare50    Erode and dilate with square structuring element of width 50.


%Inline function
coder.inline('always');


persistent SE

if isempty(SE)

    %Assign structuring element 
    %For code generation, the structuring element must be a compile-time constant.
    SE = ...
        strel('square', ... shape of structuring element
            50          ... width of structuring element
        );             
end

%Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_ErodePacked = ... eroded packed logical image
    imerode( ...
       IsSkinMask_PixelColorPacked, ... packed logical image
       SE,                          ... structuring element
       'ispacked',                  ... flag for packed image
       NRows_Matrix                 ... number of rows in unpacked image
    );  

%Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_DilatePacked =       ... dilated packed logical image
    imdilate( ...
        IsSkinMask_PixelColor_ErodePacked, ... packed logical image
        SE,                                ... structuring element
        'ispacked'                         ... flag for packed image
    );      

    
end %end local function


%=============================================================================================
function [IsSkinMask_PixelColor_DilatePacked] = ...
             ErodeAndDilate_SEDisk4(IsSkinMask_PixelColorPacked, NRows_Matrix)
%ErodeAndDilate_SEDisk4    Erode and dilate with disk-shaped structuring element of radius 4.
 

%Inline function
coder.inline('always');


persistent SE

if isempty(SE)

    %Assign structuring element 
    %For code generation, the structuring element must be a compile-time constant.
    SE = ...
        strel('disk', ... shape of structuring element
            4,        ... radius of structuring element
            8         ... approximations to use during operations; non-zero for better
        );            %   performance.
end

%Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_ErodePacked = ... eroded packed logical image
    imerode( ...
       IsSkinMask_PixelColorPacked, ... packed logical image
       SE,                          ... structuring element
       'ispacked',                  ... flag for packed image
       NRows_Matrix                 ... number of rows in unpacked image
    );  

%Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_DilatePacked =       ... dilated packed logical image
    imdilate( ...
        IsSkinMask_PixelColor_ErodePacked, ... packed logical image
        SE,                                ... structuring element
        'ispacked'                         ... flag for packed image
    );       
      
    
end %end local function


%=============================================================================================
function [IsSkinMask_PixelColor_DilatePacked] = ...
             ErodeAndDilate_SEDisk6(IsSkinMask_PixelColorPacked, NRows_Matrix)
%ErodeAndDilate_SEDisk6    Erode and dilate with disk-shaped structuring element of radius 6.
 

%Inline function
coder.inline('always');


persistent SE

if isempty(SE)

    %Assign structuring element 
    %For code generation, the structuring element must be a compile-time constant.
    SE = ...
        strel('disk', ... shape of structuring element
            6,        ... radius of structuring element
            8         ... approximations to use during operations; non-zero for better
        );            %   performance.
end

%Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_ErodePacked = ... eroded packed logical image
    imerode( ...
       IsSkinMask_PixelColorPacked, ... packed logical image
       SE,                          ... structuring element
       'ispacked',                  ... flag for packed image
       NRows_Matrix                 ... number of rows in unpacked image
    );  

%Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_DilatePacked =       ... dilated packed logical image
    imdilate( ...
        IsSkinMask_PixelColor_ErodePacked, ... packed logical image
        SE,                                ... structuring element
        'ispacked'                         ... flag for packed image
    );       
      
    
end %end local function


%=============================================================================================
function [IsSkinMask_PixelColor_DilatePacked] = ...
             ErodeAndDilate_SEDisk10(IsSkinMask_PixelColorPacked, NRows_Matrix)
%ErodeAndDilate_SEDisk10    Erode and dilate with disk-shaped structuring element of radius 10.
 

%Inline function
coder.inline('always');


persistent SE

if isempty(SE)
    
    %Assign structuring element
    %For code generation, the structuring element must be a compile-time constant.
    SE = ...
        strel('disk', ... shape of structuring element
            10,       ... radius of structuring element
            8         ... approximations to use during operations; non-zero for better
        );            %   performance.
end

%Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_ErodePacked = ... eroded packed logical image
    imerode( ...
       IsSkinMask_PixelColorPacked, ... packed logical image
       SE,                          ... structuring element
       'ispacked',                  ... flag for packed image
       NRows_Matrix                 ... number of rows in unpacked image
    );  

%Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_DilatePacked =       ... dilated packed logical image
    imdilate( ...
        IsSkinMask_PixelColor_ErodePacked, ... packed logical image
        SE,                                ... structuring element
        'ispacked'                         ... flag for packed image
    );       
       
    
end %end local function


%=============================================================================================
function [IsSkinMask_PixelColor_DilatePacked] = ...
             ErodeAndDilate_SEDisk14(IsSkinMask_PixelColorPacked, NRows_Matrix)
%ErodeAndDilate_SEDisk14    Erode and dilate with disk-shaped structuring element of radius 14.
 

%Inline function
coder.inline('always');


persistent SE

if isempty(SE)
    
    %Assign structuring element
    %For code generation, the structuring element must be a compile-time constant.
    SE = ...
        strel('disk', ... shape of structuring element
            14,       ... radius of structuring element
            8         ... approximations to use during operations; non-zero for better
        );            %   performance.
end

%Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_ErodePacked = ... eroded packed logical image
    imerode( ...
       IsSkinMask_PixelColorPacked, ... packed logical image
       SE,                          ... structuring element
       'ispacked',                  ... flag for packed image
       NRows_Matrix                 ... number of rows in unpacked image
    );  

%Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin)
%Type uint32.
IsSkinMask_PixelColor_DilatePacked =       ... dilated packed logical image
    imdilate( ...
        IsSkinMask_PixelColor_ErodePacked, ... packed logical image
        SE,                                ... structuring element
        'ispacked'                         ... flag for packed image
    );       
       
    
end %end local function


