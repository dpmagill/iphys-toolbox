function [YCbCrHSMinsMaxs_Single, YCbCrMeans_Single, RGBMeans_Double] = ...
             MeansMinsMaxes(Y_Single, Cb_Single, Cr_Single, H_Single, S_Single, R_Uint8, ...
                 G_Uint8, B_Uint8, LinearIdx, LinearIdx_N, X_Matrix_Reduced, Y_Matrix_Reduced, ...
                 NRows_Matrix_Reduced, NRows_Matrix) %#codegen                 
%MeansMinsMaxes   Returns the means, minimums, and maximums from the YCbCr, HSV, and RGB color
%                 channels according to a linear index.                           
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead_CollectSkinColorSamples.
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
%    -- Arguments --
%
%    Inputs:
%
%        Y_Single, 
%        Cb_Single, 
%        Cr_Single,     
%        H_Single,
%        S_Single,
%        R_Uint8,
%        G_Uint8,
%        B_Uint8,
%                               = R, G, B, Y, Cb, Cr, H, and S color channels (matrices) to be    
%                                 indexed. M x N matrices; type single or type uint8 as indicated.
%        LinearIdx              = Linear index for indexing values in each of the matrices. P x 1 
%                                 column vector; type int32.
%        LinearIdx_N            = Length of the linear index; used as the divisor for the mean.  
%                                 Although this value could be found here (i.e.,   
%                                 length(LinearIdx_Double)), this value is assumed to be available  
%                                 for input. Scalar; type int32.
%        TakeMeansTF            = Whether to return the Y, Cb, and Cr means.
%
%        The following inputs used to align the coordinate plane from that of the reduced-size ROI 
%        to that of the full-size ROI:                       
%                                 
%        X_Matrix_Reduced       = The X-coordinate offset for the reduced matrix. Scalar; type 
%                                 int32.
%        Y_Matrix_Reduced       = The Y-coordinate offset for the reduced matrix. Scalar; type 
%                                 int32.
%        NRows_Matrix_Reduced   = Number of rows for the reduced matrix. Scalar; type int32.
%        NRows_Matrix           = Number of rows for the full matrix. Scalar; type int32.
%
%    Outputs:
%
%        YCbCrHSMinsMaxs_Single = Minimums and maximums of the Y, Cb, Cr, H, and S channels and the
%                                 Cb-to-Cr proportion. I.e.,    
%                                 [RegionMaxN_YMin,          RegionMaxN_YMax,  ...
%                                  RegionMaxN_CbMin,         RegionMaxN_CbMax, ...
%                                  RegionMaxN_CrMin,         RegionMaxN_CrMax, ...
%                                  RegionMaxN_CbCrRatioMin,  RegionMaxN_CbCrRatioMax ...
%                                  RegionMaxN_HMax,          RegionMaxN_SMin, ...
%                                  RegionMaxN_SMax]; 
%                                 %1 x 11 row vector; type single.
%        YCbCrMeans_Single      = Means of Y, Cb, and Cr channels. 1 x 3 row vector; type single.
%        RGBMeans_Double        = Means of R, G, and B channels. 1 x 3 row vector; type double.
%
%    -- Performance Notes -- 
%
%    - It has been observed that linear indexing is faster with C-compiled code than with Matlab 
%      code, which plays a role in the speed improvement. This same improvement is not evident by
%      logical indexing. The speed improvement may still be retained even after converting from a 
%      logical index to a linear index prior to entry to the function.
%    - sum() / N shows better performance than mean().  
%    - The divisor should be of the same type as the dividend for fastest evaluation.
%    - Testing has found that performance is fastest with uint8 as input rather than single; this 
%      is true even when the divisor (NDouble) is of type single. However, note that conversion 
%      from from floating point to uint8 for the purpose of using as input is inefficient.
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


%%%%%% Setup %%%%%%

%Preallocate output vector for the Y, Cb, and Cr means
YCbCrMeans_Single = coder.nullcopy( zeros(1, 3, 'single') );

%Preallocate output vector for the R, G, and B means
RGBMeans_Double = coder.nullcopy( zeros(1, 3, 'double') );

%Initialize running minimums and maximums
%Note: the initial minimums and maximums should be outside the range of possible values.
RegionMaxN_YMin         = single(300); 
RegionMaxN_YMax         = single(-1);
RegionMaxN_CbMin        = single(300);
RegionMaxN_CbMax        = single(-1); 
RegionMaxN_CrMin        = single(300); 
RegionMaxN_CrMax        = single(-1); 
RegionMaxN_HMax         = single(-1); 
RegionMaxN_SMin         = single(300); 
RegionMaxN_SMax         = single(-1);
RegionMaxN_CbCrRatioMin = single(300);
RegionMaxN_CbCrRatioMax = single(-1);

%Initialize sum accumulators for means
SumY  = single(0);
SumCb = single(0);
SumCr = single(0);
SumR  = uint32(0);
SumG  = uint32(0);
SumB  = uint32(0);


%%%%%% Take mins, maxes, and means %%%%%%

%%%%%% --- Loop across elements of color channels %%%%%%    

%Loop across elements
for i = 1 : LinearIdx_N

    %%%%%% >>>>>> Extract ith elements of color channels %%%%%%        

    %Extract ith linear index
    %Scalar; type int32.
    LinIdx_ith = LinearIdx(i);

    %Convert the linear index to align with the coordinate plane of the full ROI
    %Local function.
    %Scalars; type int32.
    LinIdx_ith = ...
        AdjustLinIdxCoordinatePlane(LinIdx_ith, X_Matrix_Reduced, Y_Matrix_Reduced, ...
            NRows_Matrix_Reduced, NRows_Matrix);

    %Extract from input matrices
    %Scalars; type single.
    %Note: H_Single and S_Single elements extracted directly.
    Y_Single_ith  = Y_Single(LinIdx_ith);
    Cb_Single_ith = Cb_Single(LinIdx_ith);
    Cr_Single_ith = Cr_Single(LinIdx_ith);
    H_Single_ith  = H_Single(LinIdx_ith);
    S_Single_ith  = S_Single(LinIdx_ith);

    %%%%%% >>>>>> Take minimums and maximums of ith elements or element ratios %%%%%% 

    %Ratio of Cb to Cr
    RegionMaxN_CbCrRatio_ith = Cb_Single_ith / Cr_Single_ith;        

    %Minimums and maximums:

    if Y_Single_ith < RegionMaxN_YMin

        RegionMaxN_YMin = Y_Single_ith;          
    end                 

    if Y_Single_ith > RegionMaxN_YMax

        RegionMaxN_YMax = Y_Single_ith;          
    end       

    if Cb_Single_ith < RegionMaxN_CbMin

        RegionMaxN_CbMin = Cb_Single_ith;          
    end                 

    if Cb_Single_ith > RegionMaxN_CbMax

        RegionMaxN_CbMax = Cb_Single_ith;          
    end       

    if Cr_Single_ith < RegionMaxN_CrMin

        RegionMaxN_CrMin = Cr_Single_ith;          
    end                 

    if Cr_Single_ith > RegionMaxN_CrMax

        RegionMaxN_CrMax = Cr_Single_ith;          
    end        

    if H_Single_ith > RegionMaxN_HMax

        RegionMaxN_HMax = H_Single_ith;          
    end 

    if S_Single_ith < RegionMaxN_SMin

        RegionMaxN_SMin = S_Single_ith;          
    end                 

    if S_Single_ith > RegionMaxN_SMax

        RegionMaxN_SMax = S_Single_ith;          
    end              

    if RegionMaxN_CbCrRatio_ith < RegionMaxN_CbCrRatioMin

        RegionMaxN_CbCrRatioMin = RegionMaxN_CbCrRatio_ith;          
    end                 

    if RegionMaxN_CbCrRatio_ith > RegionMaxN_CbCrRatioMax

        RegionMaxN_CbCrRatioMax = RegionMaxN_CbCrRatio_ith;          
    end         

    %%%%%% >>>>>> Accumulate sums of ith elements %%%%%%             

    %Sums of Y, Cb and Cr elements
    %Scalars; type single.
    SumY  = Y_Single_ith  + SumY;
    SumCb = Cb_Single_ith + SumCb;
    SumCr = Cr_Single_ith + SumCr;

    %Sums of R, G and B elements
    %Cast to larger-size type to prevent overflow; use type uint32 for integer arithmetic.
    %Scalars; type uint32.
    SumR = uint32( R_Uint8(LinIdx_ith) ) + SumR;
    SumG = uint32( G_Uint8(LinIdx_ith) ) + SumG;
    SumB = uint32( B_Uint8(LinIdx_ith) ) + SumB;        
end
    

%%%%%% Take and assign means %%%%%%

LinearIdx_N_Single = single(LinearIdx_N); %denominator

YCbCrMeans_Single(1) = SumY  / LinearIdx_N_Single;
YCbCrMeans_Single(2) = SumCb / LinearIdx_N_Single;
YCbCrMeans_Single(3) = SumCr / LinearIdx_N_Single;

LinearIdx_N_Double = double(LinearIdx_N_Single); %denominator

RGBMeans_Double(1) = double(SumR) / LinearIdx_N_Double;
RGBMeans_Double(2) = double(SumG) / LinearIdx_N_Double;
RGBMeans_Double(3) = double(SumB) / LinearIdx_N_Double;
       

%%%%%% Assign mins and maxes %%%%%%

YCbCrHSMinsMaxs_Single = ...
    [RegionMaxN_YMin,          RegionMaxN_YMax,  ...
     RegionMaxN_CbMin,         RegionMaxN_CbMax, ...
     RegionMaxN_CrMin,         RegionMaxN_CrMax, ...
     RegionMaxN_CbCrRatioMin,  RegionMaxN_CbCrRatioMax ...
     RegionMaxN_HMax,          RegionMaxN_SMin, ...
     RegionMaxN_SMax];


end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function LinIdx = AdjustLinIdxCoordinatePlane(LinIdx, Offset_X, Offset_Y, NRows_A, NRows_B)                            
%AdjustLinIdxCoordinatePlane   Adjust a scalar linear index to align with a different coordinate 
%                              plane.
%
%    Description: 
%
%    Adjust a scalar linear index in coordinate plane A to align with coordinate plane B. To adjust
%    between planes, known offsets between the planes are used. The offsets are given in X- and 
%    Y-coordinates.
%
%    During the alignment, the linear index is converted into subscripts. An additional step then
%    converts the subscripts back to a linear index. Although there is a cost to converting back 
%    to a linear index, this cost should be made up for by the greater efficiency of indexing with
%    a linear index where the linear index is used.
%
%    Inputs:
%
%        LinIdx   = Linear index of coordinate plane A. Scalar.
%        Offset_X = X-coordinate offset giving difference between coordinate plane B and coordinate
%                   plane A.
%        Offset_Y = Y-coordinate offset giving difference between coordinate plane B and coordinate
%                   plane A.
%        NRows_A  = Number of rows of coordinate plane A.
%        NRows_B  = Number of rows of coordinate plane B.


%Inline function
coder.inline('always');


%Convert to row subscript 
%Scalar; type int32.       
Row_ith = rem(LinIdx - 1, NRows_A) + 1; 

%Convert to column subscript 
%Scalar; type int32.
Col_ith = ( LinIdx - Row_ith ) / NRows_A + 1;

%Use offset to align with coordinate plane B
Row_ith = Row_ith + Offset_Y - 1;
Col_ith = Col_ith + Offset_X - 1;

%Adjust from subscripts to linear index for indexing efficiency
%Note: as we are in the coordinate plane B now, the rows of coordinate plane B (NRows_B) are used.
LinIdx = Row_ith + (Col_ith - 1) * NRows_B;


end %end local function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(MeansMinsMaxes) of the function.

%Note: as of the current implementation of FacePulseRate, a compiled version of this function is
%not produced because it is compiled within function ROIMeans_FirstRead_CollectSkinColorSamples. 

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.
%                             Example Code                 Upp. Bounds    Var. Size (T/F)   Type
Y_SingleCode  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],    [1, 1] );         %single
Cb_SingleCode = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],    [1, 1] );         %single
Cr_SingleCode = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],    [1, 1] );         %single
H_SingleCode  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],    [1, 1] );         %single
S_SingleCode  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],    [1, 1] );         %single
LinearIdxCode = coder.typeof( zeros(500, 1,   'double'),   [inf, 1],      [1, 0] );         %double


%%%%%% Specify fixed-size input arguments %%%%%%

LinearIdx_NCode          = int32(0);
X_Matrix_ReducedCode     = int32(0); 
Y_Matrix_ReducedCode     = int32(0);
NRows_Matrix_ReducedCode = int32(0);
NRows_MatrixCode         = int32(0);
TakeMeansTFCode          = false;


%%%%%% Set configurations to increase performance %%%%%%

%Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic 
%"Optimization Strategies"

cfg = coder.config('mex');
cfg.GlobalDataSyncMethod = 'NoSync';
cfg.ConstantInputs = 'IgnoreValues';
cfg.ExtrinsicCalls = false;
cfg.SaturateOnIntegerOverflow = false;
cfg.IntegrityChecks = false;
cfg.ResponsivenessChecks = false;


%%%%%% Specify flags to minGW compiler to optimize execution speed %%%%%%

%For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

%The flags are specified as part of the code-generation configuration object. A custom function,
%setbuildargs, is used to specify these flags. For details on the function implementation, see the 
%function file, which is located within folder FacePulseRate. This custom function is based upon 
%Matlab guidance found in
%https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function

%setbuildargs will be evaluated from text within the code-generation object, so it is converted to 
%a character vector prior to execution of the codegen command.

%%%%%% --- Specify the flags as arguments to function setbuildargs %%%%%%

%Argument buildInfo: this variable is assign by the caller (the codegen command executed below) and 
%is not present in the base workspace.

%Second argument: specify a cell array of compiler-specific flags, where each flag is a character 
%vector. As function setbuildargs will be evaluated from text, use double ' quotes for each 
%character vector to maintain the charater vector,
%e.g., {''-Ofast'' ''-fsingle-precision-constant''}.

setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})';

cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen MeansMinsMaxesYCbCrHSV.m -report -config cfg -args {Y_SingleCode, Cb_SingleCode, Cr_SingleCode, H_SingleCode, S_SingleCode, LinearIdxCode, LinearIdx_NCode, X_Matrix_ReducedCode, Y_Matrix_ReducedCode, NRows_Matrix_ReducedCode, NRows_MatrixCode, TakeMeansTFCode}
             
%}




