function [b, s] = rgb2hs(r, g, b) %#codegen
%rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version      
%          of Matlab function rgb2hsv_compute that is optimized for returning only the h and s 
%          channels of the HSV colorspace. 
%   
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert
%    and SkinSegmentMask_Threshold_Colors_NoConvert.
%
%    Description:
%                   
%    Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab     
%    function rgb2hsv_compute that is optimized for returning only the h channel of the HSV 
%    colorspace. 
%
%    Notes:
%
%    For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which
%    represents the blue channel (b) of the rgb colorspace before the assignment.
%
%    RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a 
%    local function within Matlab function rgb2hsv. Note that there are several versions of 
%    function rgb2hsv; the version from which the function was extracted is the version used for 
%    code generation. As of Matlab version 2020a, the file location is 
%    R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978).
%
%    References:
%
%    Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12-
%    19.


%Inline function
coder.inline('always');
 

%Maximum channel value
if r > g && r > b
 
    v = r;
    
elseif g > b
   
    v = g;
    
else
    
    v = b; 
end

%Minimum channel value
if r < g && r < b
 
    l = r;
    
elseif g < b
   
    l = g;
    
else
    
    l = b; 
end

%Difference between maximum and minimum values
delta = v - l;

%Determine value of hue channel (h)
if delta == 0.0   

    b = coder.const( single(0) ); 
    
elseif b == v     
    
    b = 4 + (r - g) / delta;
 
    b = b / 6;

    if b < 0
    
        b = b + 1;
    end    
    
elseif  r == v
    
    b = (g - b) / delta;

    b = b / 6;

    if b < 0
    
        b = b + 1;
    end        
    
elseif g == v 
    
    b = 2 + (b - r) / delta;

    b = b / 6;
 
    if b < 0
    
        b = b + 1;
    end       
    
else
    
    b = coder.const( single(0) );
end


if v == 0

    s = coder.const( single(0) );
    
else 

    if delta == 0
     
        s = coder.const( single(0) );
    else
    
        s = delta / v;
    end
end


end %end function

