function [RangeNeighborhoodWidth, RangeThreshold, DontUseTailoredTF, YCbCrThresholds_Generic, ...
          YCbCrThresholds_Tailored, HSThresholds_Generic, HSThresholds_Tailored, ...
          MorphCloseNeighborhoodWidth, NElements_Matrix] = ...
             SkinSegmentMask_ParseArgs(SkinSegmentArgs, TailoredThresholdsSevereTF, ...
                 MorphCloseSevereTF, NRows_Matrix, NCols_Matrix) %#codegen
%SkinSegmentMask_ParseArgs   Parse imput arguments to function SkinSegmentMask_Ops. 
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
%    Parse imput arguments to function SkinSegmentMask_Ops.
%
%    -- Adjustment to thresholds --
%
%    Function SkinSegmentMask_Threshold_Colors will only use < and > for efficiency rather than <=    
%    and >=, although <= and >= are more appropriate as the thresholds are intended to accept   
%    values equal to them. To use < and > while also allowing equality, the thresholds are 
%    modified. 
%
%    Note that for the thresholds of floating-point type, even if <= and >= were used, the    
%    thresholds would still need to be modified to allow a tolerance for floating-point equality.
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


%%%%%% Local range %%%%%%

%Structuring element width for calculating local range for a given pixel:

%Value assigned in function SkinSegment_ConfigSetup.

RangeNeighborhoodWidth = SkinSegmentArgs.RangeSEWidth;

%Individual pixel local color range threshold: 

%Value assigned in function SkinSegment_ConfigSetup.
%Should be type uint8 for fastest evaluation. 

%Type uint8.
RangeThreshold = SkinSegmentArgs.RangeThreshold; 

%Adjust maximum
RangeThreshold = RangeThreshold + 1;


%%%%%% Color thresholds %%%%%%

%The Cb-to-Cr ratio, H, and S thresholds use a smaller adjustment because the intervals between
%colors are smaller.

%%%%%% --- Generic thresholds %%%%%%

%Values assigned in function SkinSegment_ConfigSetup.  
%Note: these should be in type single for fastest evaluation.

%YCbCr thresholds
%Type single.
YCbCrThresholds_Generic = SkinSegmentArgs.YCbCrThresholdsGeneric;

%HSV thresholds
%Type single.
HSThresholds_Generic = SkinSegmentArgs.HSThresholdsGeneric;

%Adjust minimums
YCbCrThresholds_Generic(1) = YCbCrThresholds_Generic(1) - .1;  %Y min
YCbCrThresholds_Generic(2) = YCbCrThresholds_Generic(2) - .1;  %Cb min
YCbCrThresholds_Generic(4) = YCbCrThresholds_Generic(4) - .1;  %Cr min
YCbCrThresholds_Generic(6) = YCbCrThresholds_Generic(6) - .01; %Cb-to-Cr ratio min
HSThresholds_Generic(2)    = HSThresholds_Generic(2)    - .01; %S min

%Adjust maximums
YCbCrThresholds_Generic(3) = YCbCrThresholds_Generic(3) + .1;  %Cb max
YCbCrThresholds_Generic(5) = YCbCrThresholds_Generic(5) + .1;  %Cr max
YCbCrThresholds_Generic(7) = YCbCrThresholds_Generic(7) + .01; %Cb-to-Cr ratio max
HSThresholds_Generic(1)    = HSThresholds_Generic(1)    + .01; %H max

%%%%%% --- Tailored thresholds %%%%%%

%Values assigned in function SkinSegment_SetThresholds.
%Note: a threshold is not used for the value (V) channel of the HSV colorspace. 
%Note: these should be in type single for fastest evaluation. 

%Low-severity tailored thresholds
if ~ TailoredThresholdsSevereTF

    %YCbCr thresholds
    %Type single.
    YCbCrThresholds_Tailored = SkinSegmentArgs.YCbCrThresholdsTailored;
    
    %HSV thresholds
    %Type single.
    HSThresholds_Tailored = SkinSegmentArgs.HSThresholdsTailored;
    
%High-severity tailored thresholds   
else
    
    %YCbCr thresholds
    %Type single.
    YCbCrThresholds_Tailored = SkinSegmentArgs.YCbCrThresholdsTailored_Sev;

    %HSV thresholds
    %Type single.
    HSThresholds_Tailored = SkinSegmentArgs.HSThresholdsTailored_Sev;    
end

%Adjust minimums
YCbCrThresholds_Tailored(1) = YCbCrThresholds_Tailored(1) - .1;  %Y min
YCbCrThresholds_Tailored(3) = YCbCrThresholds_Tailored(3) - .1;  %Cb min
YCbCrThresholds_Tailored(5) = YCbCrThresholds_Tailored(5) - .1;  %Cr min
YCbCrThresholds_Tailored(7) = YCbCrThresholds_Tailored(7) - .01; %Cb-to-Cr ratio min
HSThresholds_Tailored(2)    = HSThresholds_Tailored(2)    - .01; %S min

%Adjust maximums
YCbCrThresholds_Tailored(2) = YCbCrThresholds_Tailored(2) - .1;  %Y min
YCbCrThresholds_Tailored(4) = YCbCrThresholds_Tailored(4) + .1;  %Cb max
YCbCrThresholds_Tailored(6) = YCbCrThresholds_Tailored(6) + .1;  %Cr max
YCbCrThresholds_Tailored(8) = YCbCrThresholds_Tailored(8) + .01; %Cb-to-Cr ratio max
HSThresholds_Tailored(1)    = HSThresholds_Tailored(1)    + .01; %H max

%Flag not to use tailored thresholds:

%Whether a sufficient number of skin-color samples was collected to activate tailored skin
%segmentation. For details on the collection skin-color samples, see function
%ROIMeans_FirstRead_CollectSkinColorSamples.
%Value assigned by function SkinSegment_SetThresholds.
DontUseTailoredTF = ~ SkinSegmentArgs.SkinColorSamples_NThresholdPassedTF;


%%%%%% Morphological close %%%%%%

%High severity of morphological close operation
if MorphCloseSevereTF

    MorphCloseNeighborhoodWidth = SkinSegmentArgs.MorphCloseSELargeWidth_Tuned;
    
%Low severity of morphological close operation
else

    MorphCloseNeighborhoodWidth = SkinSegmentArgs.MorphCloseSEMediumWidth_Tuned;
end


%%%%%% Number of elements in input matrices %%%%%%

%Number of elements of a given matrix
%Scalar; type int32.
NElements_Matrix = NRows_Matrix * NCols_Matrix;


end %end function