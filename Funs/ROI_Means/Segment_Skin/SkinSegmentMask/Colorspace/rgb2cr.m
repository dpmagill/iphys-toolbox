function b = rgb2cr(r, g, b) %#codegen
%rgb2cr   Apply the RGB-to-Cr algorithm to a given pixel and return the Cr channel.
%   
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert
%    and SkinSegmentMask_Threshold_Colors_NoConvert.
%
%    Description:
%  
%    Apply the RGB-to-Cr algorithm to a given pixel and return the Cr channel.
%
%    This conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is 
%     derived from Poynton (1996, p. 175 - 176).
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


%ith Cr channel element
%Scalar; type single.
b = ...
     0.4392 * r + ...
    -0.3678 * g + ...
    -0.0714 * b + ...
    128;        


end %end function
