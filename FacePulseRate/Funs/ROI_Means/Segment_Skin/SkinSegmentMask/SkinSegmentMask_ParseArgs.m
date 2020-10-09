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
%    Code generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.    
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

% - Structuring element width for calculating local range for a given pixel

%Value assigned in function SkinSegment_ConfigSetup.

RangeNeighborhoodWidth = SkinSegmentArgs.RangeSEWidth;

% - Individual pixel local color range threshold 

%Value assigned in function SkinSegment_ConfigSetup.
%Should be type uint8 for fastest evaluation. 

RangeThreshold = SkinSegmentArgs.RangeThreshold; 


%%%%%% Color thresholds %%%%%%

% - Individual pixel YCbCr colorspace skin-segmentation generic thresholds

%Values assigned in function SkinSegment_ConfigSetup.  
%Note: these should be in type single for fastest evaluation.

YCbCrThresholds_Generic = SkinSegmentArgs.YCbCrThresholdsGeneric;

%Function SkinSegmentMask_Threshold_Colors will only use < and > rather than <= and >=, so these 
%values are adjusted so that < and > are equivalent to <= and >=, respectively.

YCbCrThresholds_Generic(1) = YCbCrThresholds_Generic(1) - 1;  %Y min
YCbCrThresholds_Generic(2) = YCbCrThresholds_Generic(2) - 1;  %Cb min
YCbCrThresholds_Generic(4) = YCbCrThresholds_Generic(4) - 1;  %Cr min
YCbCrThresholds_Generic(6) = YCbCrThresholds_Generic(6) - .1; %Cb-to-Cr ratio min

YCbCrThresholds_Generic(3) = YCbCrThresholds_Generic(3) + 1;  %Cb max
YCbCrThresholds_Generic(5) = YCbCrThresholds_Generic(5) + 1;  %Cr max
YCbCrThresholds_Generic(4) = YCbCrThresholds_Generic(4) + .1; %Cb-to-Cr ratio max

% - Individual pixel HSV colorspace skin-segmentation generic thresholds

%Values assigned in function SkinSegment_ConfigSetup.  
%Note: these should be in type single for fastest evaluation.

HSThresholds_Generic = SkinSegmentArgs.HSThresholdsGeneric;

%Function SkinSegmentMask_Threshold_Colors will only use < and > rather than <= and >=, so these 
%values are adjusted so that < and > are equivalent to <= and >=, respectively.

HSThresholds_Generic(2) = HSThresholds_Generic(2) - .1;  %S min

HSThresholds_Generic(1) = HSThresholds_Generic(1) + .1;  %H max

% - Individual pixel YCbCr and HSV colorspaces skin-segmentation tailored thresholds

%Values assigned in function SkinSegment_SetThresholds.
%Note: a threshold is not used for the value (V) channel of the HSV colorspace. 
%Note: these should be in type single for fastest evaluation. 

%   - Low-severity tailored thresholds
if ~ TailoredThresholdsSevereTF

    %YCbCr channels
    YCbCrThresholds_Tailored = SkinSegmentArgs.YCbCrThresholdsTailored;
    
    %H and S channels
    HSThresholds_Tailored = SkinSegmentArgs.HSThresholdsTailored;
    
%   - High-severity tailored thresholds    
else
    
    %YCbCr channels
    YCbCrThresholds_Tailored = SkinSegmentArgs.YCbCrThresholdsTailored_Sev;

    %H and S channels
    HSThresholds_Tailored = SkinSegmentArgs.HSThresholdsTailored_Sev;    
end

% - Flag not to use tailored thresholds

%Whether a sufficient number of skin-color samples was collected to activate tailored skin
%segmentation. For details on the collection skin-color samples, see function
%ROIMeans_FirstRead_CollectSkinColorSamples.
%Value assigned by function SkinSegment_SetThresholds.
DontUseTailoredTF = ~ SkinSegmentArgs.SkinColorSamples_NThresholdPassedTF;


%%%%%% Morphological close %%%%%%

% - Severity of morphological close

%   - High severity of morphological close operation
if MorphCloseSevereTF

    MorphCloseNeighborhoodWidth = SkinSegmentArgs.MorphCloseSELargeWidth_Tuned;
    
%   - Low severity of morphological close operation
else

    MorphCloseNeighborhoodWidth = SkinSegmentArgs.MorphCloseSEMediumWidth_Tuned;
end


%%%%%% Number of elements in input matrices %%%%%%

%Number of elements of a given matrix
%Scalar; type int32.
NElements_Matrix = NRows_Matrix * NCols_Matrix;


end %end function