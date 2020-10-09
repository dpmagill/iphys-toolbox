function localRange = ...
             SkinSegmentMask_Threshold_Range(AreaToSegment2D, nhoodWidth, SE3, SE5, SE7, SE9)
             %#codegen                                           
%SkinSegmentMask_Threshold_Range    Function rangefilt optimized for use in function
%                                   SkinSegmentMask_Threshold.
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
%    For a description of the assumptions behind the use of the following operations to classify
%    pixels as skin, see function SkinSegmentMask_Ops.
%
%    Note: The algorithm used is adapted from Matlab function rangefilt.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code-generation settings %%%%%%

coder.inline('always');


%%%%%% Parse inputs %%%%%%

%Because the structuring element object (SE3, SE5, SE7, or SE9) must be a compile-time constant,  
%only four structuring element objects are made available, each of which has a corresponding 
%function. The function with the structuring element closest in size to the specified structuring 
%element size (RangeNeighborhoodWidth) is used.

%Select function from available functions
%Select the function with the SE width most similar to the specified SE width.
%Local function.
%Scalar; type int16.
functionWidthToUse = SelectFunction(nhoodWidth);


%%%%%% Erosion followed by dilation %%%%%%

%Use available function with SE width closest to specified SE width 
switch functionWidthToUse

    %Local range of square neighborhood with width of 3 pixels    
    case 3

        %M x N matrices; type uint8.
        [dilateI, erodeI] = ...
            rangefilt_optim_SEWidth3(AreaToSegment2D, SE3); %one channel

    %Local range of square neighborhood with width of 5 pixels
    case 5

        %M x N matrices; type uint8.
        [dilateI, erodeI] = ...
            rangefilt_optim_SEWidth5(AreaToSegment2D, SE5); %one channel

    %Local range of square neighborhood with width of 7 pixels
    case 7  
        
        %M x N matrices; type uint8.
        [dilateI, erodeI] = ...
            rangefilt_optim_SEWidth7(AreaToSegment2D, SE7); %one channel

    %Local range of square neighborhood with width of 9 pixels
    case 9
        
        %M x N matrices; type uint8.
        [dilateI, erodeI] = ...
            rangefilt_optim_SEWidth9(AreaToSegment2D, SE9); %one channel
     
    %(Required for code generation validation)   
    otherwise
        
        localRange = uint8(0);
        
        return
end    


%%%%%% Element-wise subtraction %%%%%%

%Note: Code used in function rangefilt: localRange = imlincomb(1, dilateI, -1, erodeI, 'uint8').
%Use element-wise subtraction, which is equivalent, to avoid the argument parsing and conversion to
%to type double that occurs in function imlincomb.

%M x N matrix; type uint8.
localRange = dilateI - erodeI; 


end %end main function


%=============================================================================================
%Local functions 
%=============================================================================================


%=============================================================================================
function functionWidthToUse = SelectFunction(nhoodWidth)
%SelectFunction   Select the function with the SE width most similar to nhoodWidth.   


%Inline function
coder.inline('always');


%Scalars; type int16.
Diff3 = abs(3 - nhoodWidth);
Diff5 = abs(5 - nhoodWidth);
Diff7 = abs(7 - nhoodWidth);
Diff9 = abs(9 - nhoodWidth);

if Diff3 < Diff5
    
    Diff = Diff3;
    
    functionWidthToUse = int16(3);
    
else
    
    Diff = Diff5;
    
    functionWidthToUse = int16(5);    
end

if Diff7 < Diff
    
    Diff = Diff7;
    
    functionWidthToUse = int16(7);
end

if Diff9 < Diff
 
    functionWidthToUse = int16(9);
end    


end %end local function


%=============================================================================================
function [dilateI, erodeI] = rangefilt_optim_SEWidth3(AreaToSegment2D, SE)
%rangefilt_optim_SEWidth3    Optimized range filter using square structuring element of width 3.


%Inline function
coder.inline('always');


%Dilate
%M x N matrix; type uint8.
dilateI = imdilate(AreaToSegment2D, SE);

%Erode
%M x N matrix; type uint8.
%Note: Difference from function rangefilt: use of structuring element object (strel).
%Note from rangefilt function file: IMERODE returns the local minima of I in NHOOD.
erodeI = imerode(AreaToSegment2D, SE); 


end  %end local function


%=============================================================================================
function [dilateI, erodeI] = rangefilt_optim_SEWidth5(AreaToSegment2D, SE)
%rangefilt_optim_SEWidth5    Optimized range filter using square structuring element of width 5.


%Inline function
coder.inline('always');


%Dilate
%M x N matrix; type uint8.
dilateI = imdilate(AreaToSegment2D, SE);

%Erode
%M x N matrix; type uint8.
%Note: Difference from function rangefilt: use structuring element object (strel).
%Note from rangefilt function file: IMERODE returns the local minima of I in NHOOD.
erodeI = imerode(AreaToSegment2D, SE); 


end %end local function


%=============================================================================================
function [dilateI, erodeI] = rangefilt_optim_SEWidth7(AreaToSegment2D, SE)
%rangefilt_optim_SEWidth9    Optimized range filter using square structuring element of width 7.


%Inline function
coder.inline('always');


%Dilate
%M x N matrix; type uint8.
dilateI = imdilate(AreaToSegment2D, SE);

%Erode
%M x N matrix; type uint8.
%Note: Difference from function rangefilt: use structuring element object (strel).
%Note from rangefilt function file: IMERODE returns the local minima of I in NHOOD.
erodeI = imerode(AreaToSegment2D, SE); 


end %end local function


%=============================================================================================
function [dilateI, erodeI] = rangefilt_optim_SEWidth9(AreaToSegment2D, SE)
%rangefilt_optim_SEWidth9    Optimized range filter using square structuring element of width 9.


%Inline function
coder.inline('always');


%Dilate
%M x N matrix; type uint8.
dilateI = imdilate(AreaToSegment2D, SE);

%Erode
%M x N matrix; type uint8.
%Note: Difference from function rangefilt: use structuring element object (strel).
%Note from rangefilt function file: IMERODE returns the local minima of I in NHOOD.
erodeI = imerode(AreaToSegment2D, SE); 


end %end local function


