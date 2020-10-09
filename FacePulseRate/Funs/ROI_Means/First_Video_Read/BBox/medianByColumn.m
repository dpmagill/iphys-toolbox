function y = medianByColumn(x)
%medianByColumn   Find the median of each column.
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead_SetBoundingBoxes.
%
%    Notes: 
%
%    Adapted from the Matlab function 'median'.
%
%    This function relies on the maximum value of an ROI being 16384. This is because the data type  
%    used for the ROI is int16, which has a maximum value of 32768. In order to allow two variables
%    to be added without exceeding 32768, the maximum value may be half of 32768 (16384). This 
%    constraint is noted in the description of function FacePulseRate; if the current function is 
%    to be removed, the description in function FacePulseRate should be modified.


%Find midway point of each column:

x = sort(x, 1); %sort by column

nRows = size(x, 1);

half = floor(nRows / 2);    

y = x(half + 1, :);

%If even number of rows
if 2 * half == nRows
       
    y = meanof( x(half, :), y );
end


end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function c = meanof(a, b)


c = a + (b - a) / 2;


end %end local function