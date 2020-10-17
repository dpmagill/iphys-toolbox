function [IsSkinMask, YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single, ...
          SBounded_Single, IsSkinMask_Range] = ...
             SkinSegmentMask_Threshold(RBounded_Uint8, GBounded_Uint8, BBounded_Uint8, ...
                 YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single, ...
                 SBounded_Single, IsSkinMask_Range, NRows_Matrix, NCols_Matrix, ...
                 NElements_Matrix, YCbCrThresholds_Generic, TailoredThresholdsTF, ...
                 DontUseTailoredTF, YCbCrThresholds_Tailored, ReturnYTF, ReturnCbCrTF, ...
                 HSThresholds_Generic, HSThresholds_Tailored, ReturnHSTF, ...
                 RangeNeighborhoodWidth, RangeThreshold, XOffset, YOffset) %#codegen                                                                                                                                       
%SkinSegmentMask_Threshold   Classify pixels as skin or non-skin based upon the color values, the   
%                            color ratios, and the local range of individual pixels.
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
%    For a description of the assumptions behind the use of the following operations to classify
%    pixels as skin, see function SkinSegmentMask_Ops. 
%
%    Classify individual pixels as skin or non-skin using the following operations:
%
%    (1) Pixel-color thresholds:
%
%        YCbCr thresholds
%
%        Compare the color values and color ratios of individual pixels from the YCbCr colorspace 
%        to specified thresholds. Use either the generic color thresholds 
%        (YCbCrThresholds_Generic), which are set by function SkinSegment_ConfigSetup, or tailored 
%        color thresholds (YCbCrThresholds_Tailored), which are set by function 
%        SkinSegment_SetThresholds based upon skin-color samples observed in the video. 
%
%        The use of tailored thresholds is specified by argument TailoredThresholdsTF. However, use 
%        generic thresholds when TailoredThresholdsTF is true if the criterion for using tailored    
%        thresholds has not been satisfied, which is indicated by DontUseTailoredTF == true.      
%    
%        HS thresholds
%
%        Compare the color values of individual pixels from the H and S channels of the HSV   
%        colorspace to specified thresholds, HSThresholds.
%
%        The use of the H and S thresholds is specified by argument TailoredThresholdsTF. However,  
%        do not use these thresholds when TailoredThresholdsTF is true if the criterion for using     
%        tailored thresholds has not been satisfied, which is indicated by DontUseTailoredTF == 
%        true.        
%
%    (2) Compare the local color range of individual pixels to a specified threshold, 
%        RangeThreshold.        
%    
%    Also return the YCbCr and HS color channels used in operations for operations in other 
%    functions. Always return the Y channel. Only return the Cb and Cr channels if ReturnCbCrTF == 
%    true. Only return the H and S channels if ReturnHSTF == true.   
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% Code-generation settings %%%%%%

coder.inline('always');

%Declare variables:
%                                   Upp. Bounds    Var. Size (T/F)
coder.varsize('IsSkinMask',         [inf, inf],    [1, 1]);
coder.varsize('ParCell1{:}{:}',     [inf, inf],    [1, 1]);
coder.varsize('ParCell2{:}',        [inf, inf],    [1, 1]);


%%%%%% Parse optional X- and Y-coordinate offsets %%%%%%

%Initialize flag to use a linear index
%A linear index will be used when neither an X offset nor a Y offset is specified.
UseLinIdxTF = true;

%Set flags indicating whether an X or Y offset is specified.
%Scalars; type int32.
%Note: -1 indicates the offset is not specified.
XOffsetSpecifiedTF = XOffset ~= -1; 
YOffsetSpecifiedTF = YOffset ~= -1;

if XOffsetSpecifiedTF || YOffsetSpecifiedTF

    %Flag to use subscript indices rather than a linear index
    UseLinIdxTF = false;
    
    %If XOffset not specified, use 1
    if ~ XOffsetSpecifiedTF
        
        XOffset = int32(1);
    end
    
    %If YOffset not specified, use 1    
    if ~ YOffsetSpecifiedTF
        
        YOffset = int32(1);
    end    
end


%%%%%% Assign structuring objects for the local range operations %%%%%%

%Note that mex files, as of the time of implementation, cannot accept strel objects as input     
%arguments, so the strel objects are assigned within the current function. Strel objects cannot be
%assigned as constants (i.e., by coder.const), so, for efficiency, they are declared persistent so 
%that assignment occurs only once.

%Note that persistent variables cannot be declared within a parfor call. For this reason, these
%variables are declared here rather than in the function, SkinSegmentMask_Threshold_Range, for 
%which they are used.

persistent SE3 SE5 SE7 SE9

if isempty(SE3) %only need to check one as all assigned at same time

    %Assign structuring element
    %Note: for code generation, the structuring element must be a compile-time constant.
    SE3 = ...
        strel('square', ... shape of structuring element
            3           ... width of structuring element
        );

    %Assign structuring element
    %Note: for code generation, the structuring element must be a compile-time constant.
    SE5 = ...
        strel('square', ... shape of structuring element
            5           ... width of structuring element
        );
    
    %Assign structuring element
    %Note: for code generation, the structuring element must be a compile-time constant.
    SE7 = ...
        strel('square', ... shape of structuring element
            7           ... width of structuring element
        );
    
    %Assign structuring element
    %Note: for code generation, the structuring element must be a compile-time constant.
    SE9 = ...
        strel('square', ... shape of structuring element
            9           ... width of structuring element
        );
end


%%%%%% Apply thresholds %%%%%%

%%%%%%% --- Compiled version of function %%%%%% 

%Parallel processing operations increase efficiency of the compiled version of the function but 
%decrease the efficiency of Matlab code, so conduct parallel processing operations only for the 
%compiled version of the function.

if ~ coder.target('MATLAB') %code generation running

    %%%%%% >>>>>> If IsSkinMask_Range is not provided as input %%%%%%

    if isempty(IsSkinMask_Range)  

        %Apply the color thresholds and the local-range threshold in parallel. Note that the  
        %parallel-for loop is coded such that it actually acts like a pareval operation.

        %Preallocate cells to hold results from parallel operations:

        %Cell array to hold YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single, and
        %SBounded_Single.
        ParCell1 = ...
            coder.nullcopy( ...
                 coder.const( ...
                 { ...
                  {single(0), single(0), single(0), single(0), single(0)}, ...
                  {single(0), single(0), single(0), single(0), single(0)} ... cells on this line will not be assigned
                 } ...
                 ) ...
             );  

         %Cell array to hold IsSkinMask and IsSkinMask_Range
         ParCell2 = ...
             coder.nullcopy( ...
                 coder.const( ...
                      {false, ...
                       false} ...
                 ) ...
             );      

        %Run operations in parallel
        %Only use 2 threads.
        parfor (i = 1 : 2, 2) 

            %Apply YCbCr and HS thresholds:   

            if i == 1

                %Note: SkinSegmentMask_Threshold_Colors is a custom function located within folder 
                %'FacePulseRate'.
                [ParCell2{i},      ... skin-segmentation mask based on color thresholds
                 ParCell1{i}{1},   ... Y channel matrix
                 ParCell1{i}{2},   ... Cb channel matrix
                 ParCell1{i}{3},   ... Cr channel matrix
                 ParCell1{i}{4},   ... H channel matrix
                 ParCell1{i}{5}] = ... S channel matrix
                    SkinSegmentMask_Threshold_Colors(RBounded_Uint8, GBounded_Uint8, ... 
                        BBounded_Uint8, YBounded_Single, CbBounded_Single, CrBounded_Single, ...
                        HBounded_Single, SBounded_Single, NRows_Matrix, NCols_Matrix, ...
                        NElements_Matrix, TailoredThresholdsTF, DontUseTailoredTF, ...
                        YCbCrThresholds_Generic, YCbCrThresholds_Tailored, ReturnYTF, ...
                        ReturnCbCrTF, ReturnHSTF, HSThresholds_Generic, HSThresholds_Tailored, ...
                        UseLinIdxTF, XOffset, YOffset);                                                                                                               

            %Apply local-range threshold:

            else %i == 2

                %Local range threshold  
                %Local function.
                %M x N matrix; type logical.
                ParCell2{i} = ... skin-segmentation mask based on local color range threshold
                    ApplyRangeThreshold(RBounded_Uint8, RangeNeighborhoodWidth, RangeThreshold, ...
                        SE3, SE5, SE7, SE9, UseLinIdxTF, XOffset, YOffset, NRows_Matrix, ...
                        NCols_Matrix);

                %Unused values to satisfy parfor requirements
                ParCell1{i}{1} = coder.nullcopy( single(0) );
                ParCell1{i}{2} = coder.nullcopy( single(0) );
                ParCell1{i}{3} = coder.nullcopy( single(0) );
                ParCell1{i}{4} = coder.nullcopy( single(0) );  
                ParCell1{i}{5} = coder.nullcopy( single(0) );
            end
        end    

        %Extract results from parallel operations:
        
        YBounded_Single  = ParCell1{1}{1};
        CbBounded_Single = ParCell1{1}{2};
        CrBounded_Single = ParCell1{1}{3};
        HBounded_Single  = ParCell1{1}{4};
        SBounded_Single  = ParCell1{1}{5};

        IsSkinMask       = ParCell2{1};     
        IsSkinMask_Range = ParCell2{2};

    %%%%%% >>>>>> If IsSkinMask_Range is provided %%%%%%
    else

        %Note: SkinSegmentMask_Threshold_Colors is a custom function located within folder
        %'FacePulseRate'.
        [IsSkinMask, YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single, ...
         SBounded_Single] = ...
            SkinSegmentMask_Threshold_Colors(RBounded_Uint8, GBounded_Uint8, ... 
                BBounded_Uint8, YBounded_Single, CbBounded_Single, CrBounded_Single, ...
                HBounded_Single, SBounded_Single, NRows_Matrix, NCols_Matrix, NElements_Matrix, ...
                TailoredThresholdsTF, DontUseTailoredTF, YCbCrThresholds_Generic, ...
                YCbCrThresholds_Tailored, ReturnYTF, ReturnCbCrTF, ReturnHSTF, ...
                HSThresholds_Generic, HSThresholds_Tailored, UseLinIdxTF, XOffset, YOffset);                  
    end

%%%%%%% --- Non-compiled version of function %%%%%% 

else %code generation not running
    
    %Apply YCbCr and HS thresholds:

    %Note: SkinSegmentMask_Threshold_Colors is a custom function located within folder 
    %'FacePulseRate'.
    [IsSkinMask, YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single, ...
     SBounded_Single] = ...
        SkinSegmentMask_Threshold_Colors(RBounded_Uint8, GBounded_Uint8, BBounded_Uint8, ...                
            YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single, ...
            SBounded_Single, NRows_Matrix, NCols_Matrix, NElements_Matrix, ...
            TailoredThresholdsTF, DontUseTailoredTF, YCbCrThresholds_Generic, ...
            YCbCrThresholds_Tailored, ReturnYTF, ReturnCbCrTF, ReturnHSTF, ...
            HSThresholds_Generic, HSThresholds_Tailored, UseLinIdxTF, XOffset, YOffset);            
                                           
    %%%%%% >>>>>> If IsSkinMask_Range is not provided as input %%%%%%
    
    if isempty(IsSkinMask_Range)
    
        %Apply local-range threshold:

        %M x N matrix; type logical.
        %Local function.
        IsSkinMask_Range = ...
            ApplyRangeThreshold(RBounded_Uint8, RangeNeighborhoodWidth, RangeThreshold, SE3, ...
                SE5, SE7, SE9, UseLinIdxTF, XOffset, YOffset, NRows_Matrix, NCols_Matrix);      
    end                  
end
 
    
%%%%%% Combine skin-segmentation masks %%%%%%

%Loop across skin-segmentation mask elements
for i = 1 : NElements_Matrix

    IsSkinMask(i) = IsSkinMask(i) && IsSkinMask_Range(i); 
end


end %end main function


%=============================================================================================
%Local functions 
%=============================================================================================


%=============================================================================================
function IsSkinMask_Range = ...
             ApplyRangeThreshold(RBounded_Uint8, RangeNeighborhoodWidth, RangeThreshold, SE3, ...
                 SE5, SE7, SE9, UseLinIdxTF, XOffset, YOffset, NRows_Matrix, NCols_Matrix)
%ApplyRangeThreshold   Apply local color range threshold to individual pixels.                                     
%
%    Description:
%
%    For a detailed description of the assumptions of using this threshold for skin segmentation,
%    see function SkinSegmentMask_Ops.
%
%    Take the local color range of each pixel and classify it as skin if it is below the specified
%    threshold (RangeThreshold). The threshold is assigned by function SkinSegment_ConfigSetup.
%
%    The local range is defined as the square neighborhood specified by RangeNeighborhoodWidth.
%    Because the structuring element object (SE3, SE5, SE7, or SE9) must be a compile-time 
%    constant, only four structuring element objects are made available. The structuring element 
%    object closest to the specified structuring element size (RangeNeighborhoodWidth) is used.
%
%    Only the local range of the red channel, rather than all RGB channels, is used for 
%    computational efficiency. An RGB channel may be preferable to the Cb and Cr channels because 
%    the RGB channels contain luminance information, the range of which seems to be useful in 
%    indicating non-skin. The Y channel from the YCbCr colorspace, which is a measure a luminance,
%    might also be suitable.
 

%Inline function
coder.inline('always');


%If subscript indexing specified
if ~ UseLinIdxTF
    
    %Crop matrix according to subscripts
    RBounded_Uint8 = ...
        RBounded_Uint8( ...
            YOffset : YOffset + NRows_Matrix - 1, ...
            XOffset : XOffset + NCols_Matrix - 1 ...
        );    
end

%Return the local range of each pixel
%M x N matrix; type uint8.
localRange = ...
    SkinSegmentMask_Threshold_Range(RBounded_Uint8, RangeNeighborhoodWidth, SE3, SE5, SE7, SE9);
        
%Return logical matrix where pixels below specified local range threshold are classified as skin.
%Note: SkinSegmentMask_Threshold_Range is a custom version of Matlab function rangefilt optimized 
%for use in the current function. It is located within folder 'FacePulseRate'.
IsSkinMask_Range = ... skin == true; non-skin == false
    localRange ...
    < RangeThreshold; %threshold (should be type uint8 for fastest evaluation). 


%Previous implementation (local standard deviation threshold):

%Note: limited testing indicates that calculating the local range might be about 8 times faster
%than calculating the local standard deviation, which is why local range is used.

%{

%Neighborhood in which to calculate standard deviation for a given pixel
SDNeighborhood = ***;

%Assign standard deviation filter
%Take standard deviation of the neighborhood of each pixel and compare it against the threshold.
%Classify pixel as skin if its local standard deviation does not exceed the specified threshold.
%Only calculate standard deviations for the red channel for computational efficiency.
%Note: stdfilt_optim is a custom function located within folder FacePulseRate; it is an optimized
%version of function stdfilt; see the function file for details. 
%The optimized version does not use padding; as a result, the pixels near the inner edge of the ROI
%will be marked as non-skin. As the effect is consistent across ROIs, it is not considered to have
%a substantive effect on the analysis.
SDfilter =                                ... skin == true; non-skin == false
    stdfilt_optim(AreaToSegment(:, :, 1), ... red channel
        SDNeighborhood)                   ... pixel neighborhood
    < SkinClassificationByColor.Pixel.SkinSeg.SDThreshold; %threshold

%Combine classifications from pixel color and pixel color standard deviation
IsSkinMask_PixelColor = IsSkinMask_PixelColor & SDfilter;  

%}         


end %end local function

               
