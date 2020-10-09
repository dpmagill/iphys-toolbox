function IsNotSkin_PixelColor_Packed = ...
             ROIMeans_TakeMeans_StoreMaskForVideoWrite(IsSkinMask_PixelColor) %#codegen              
%ROIMeans_TakeMeans_StoreMaskForVideoWrite   Compress and store skin-segmentation mask for use in 
%                                            writing output video.
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
%    Compress and store the output from function SkinSegmentMask to structs for later use in 
%    function WriteFaceVideo for displaying skin segmentation results. This prevents the 
%    computational time associated with rerunning function SkinSegmentMask in that function.        
%
%    For storage, the logical matrices will be converted to packed binary images. Compared to a 
%    logical matrix, a packed binary image uses less memory. The number of rows is also recorded as 
%    this is needed, along with the packed binary image, to unpack the matrices.
%    
%    Note: In the present use case, where the matrices contain a relatively large number of   
%    elements with value true, a sparse matrix might be larger than the full matrix, so a packed   
%    binary image is used instead.
%
% 
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%Inline function
coder.inline('always');


%Convert from logical matrix to packed binary image
IsNotSkin_PixelColor_Packed = ...
    bwpack( ~ IsSkinMask_PixelColor); %invert matrix so that nonskin = true


end %end function

