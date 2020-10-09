function b = rgb2y(r, g, b) %#codegen
%rgb2y   Apply the RGB-to-Y algorithm to a given pixel and return the Y channel.
%   
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert
%    and SkinSegmentMask_Threshold_Colors_NoConvert.
%
%    Description:
%
%    Apply the RGB-to-Y algorithm to a given pixel and return the Y channel.
%
%    The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is
%    derived from Poynton (1996, p. 175 - 176).
%
%    Note:
%
%    For efficiency, the Y channel of the YCbCr colorspace is assigned to variable b, which
%    represents the blue channel (b) of the rgb colorspace before the assignment.
%
%    References:
%
%    Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons.


%Inline function
coder.inline('always');


%ith Y channel element
%Scalar; type single.
b = ...
    0.2568 * r + ... 
    0.5041 * g + ... 
    0.0979 * b + ... 
    16;          


end %end function

