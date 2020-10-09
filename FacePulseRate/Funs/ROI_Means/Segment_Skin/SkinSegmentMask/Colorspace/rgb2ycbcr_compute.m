function [y, cb, b] = rgb2ycbcr_compute(r, g, b) %#codegen
%rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels.
%   
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert
%    and SkinSegmentMask_Threshold_Colors_NoConvert.
%
%    Code generation: Can be called as a Matlab function or used for C-language code generation.
%
%    Description:
%
%    Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels.
%
%    The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is
%    derived from Poynton (1996, p. 175 - 176).
%
%    Note:
%
%    For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which
%    represents the blue channel (b) of the rgb colorspace before the assignment.
%
%    References:
%
%    Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons.


%Inline function
coder.inline('always');


%ith Y channel element
%Scalar; type single.
y = ...
    0.2568 * r + ... 
    0.5041 * g + ... 
    0.0979 * b + ... 
    16;          

%ith Cb channel element
%Scalar; type single.
cb = ...
    -0.1482 * r + ...
    -0.2910 * g + ...
     0.4392 * b + ...
    128;   

%ith Cr channel element
%Scalar; type single.
b = ...
     0.4392 * r + ...
    -0.3678 * g + ...
    -0.0714 * b + ...
    128;  


end %end function

