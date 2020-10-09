function [RGBMeans_Double, LuminanceMean_Double] = ...
             IndexAndMean_LogIdx(R_Uint8, G_Uint8, B_Uint8, Luminance_Single, LogIdx, NRows, ...
                 NCols, TrueCount, TakeLuminanceMeanTF) %#codegen                                 
%IndexAndMean_LogIdx   Take the mean of each of four matrices according to a logical index.                        
% 
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_TakeMeans.    
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
%    Take the mean of each of three matrices of type uint8 according to a logical index.
%                        
%    Inputs:
%
%        R_Uint8, 
%        G_Uint8, 
%        B_Uint8                = R, G, and B color channels from which to take means. M x N  
%                                 matrices, type uint8.
%        Luminance_Single       = Luminance channel from which to take mean. M x N matrix, type 
%                                 single.
%        LogIdx                 = Logical matrix indicating elements from which to take means. M x   
%                                 N matrix; type logical. 
%        NRows                  = Number of rows of one of the above inputs. Scalar; type int32.
%        NCols                  = Number of columns of one of the above inputs. Scalar; type int32.
%        TrueCount              = Number of elements in LogIdx that are true. Scalar; type uint32.
%        TakeLuminanceMeanTF    = Whether to take the mean of the luminance matrix. Scalar; type
%                                 logical.                        
%                              
%    Outputs:
%
%        RGBMeans_Double      = Means of the R, G, and B color channels. 1 x 3 row vector; type 
%                               double. 
%        LuminanceMean_Double = Mean of the luminance channel. Scalar; type double.
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


%Preallocate outputs 
RGBMeans_Double  = coder.nullcopy( zeros(1, 3) );
LuminanceMean_Double = double(0);

%The number of elements in an input matrix
%Scalar; type int32.
NElements = NRows * NCols;


%%%%%%% If taking the luminance mean is enabled %%%%%%%

if TakeLuminanceMeanTF
    
    %%%%%% --- Optimized with integer arithmetic %%%%%%

    %If matrix IsSkinMask is under specified size, use algorithm optimized with integer arithmetic.
    if NElements < 15686000

        %Initialize accumulating variables
        %Use a type that is large enought to prevent overflow.
        %Note: for LuminanceMatrix_Single, which is of type single, it less efficient to cast to
        %type uint32 than to stay in type single.
        SumR_uint32 = uint32(0);
        SumG_uint32 = uint32(0);
        SumB_uint32 = uint32(0);
        SumL        = single(0);

        %Loop across elements, accumulating sum
        parfor i = 1 : NElements

            %If element classified as skin
            if LogIdx(i)

                %Accumulate
                %Cast elements of type uint8 to type uint32.
                SumR_uint32 = uint32( R_Uint8(i) ) + SumR_uint32;
                SumG_uint32 = uint32( G_Uint8(i) ) + SumG_uint32;
                SumB_uint32 = uint32( B_Uint8(i) ) + SumB_uint32;
                SumL        = Luminance_Single(i)  + SumL;
            end        
        end

        %Take means and cast to double:

        %Cast to type double for use as denominator
        TrueCount_Double = double(TrueCount);

        RGBMeans_Double(1)   = double(SumR_uint32) / TrueCount_Double;
        RGBMeans_Double(2)   = double(SumG_uint32) / TrueCount_Double;
        RGBMeans_Double(3)   = double(SumB_uint32) / TrueCount_Double;
        LuminanceMean_Double = double(SumL)        / TrueCount_Double;

    %%%%%% --- Not optimized with integer arithmetic %%%%%%    

    else

        %Initialize accumulating variables
        %Use a type that is large enought to prevent overflow.
        SumR        = single(0);
        SumG        = single(0);
        SumB        = single(0);
        SumL        = single(0);

        %Loop across elements, accumulating sum
        parfor i = 1 : NElements

            %If element classified as skin
            if LogIdx(i)

                %Cast to type single and accumulate
                SumR = single( R_Uint8(i) ) + SumR;
                SumG = single( G_Uint8(i) ) + SumG;
                SumB = single( B_Uint8(i) ) + SumB;
                SumL = Luminance_Single(i)  + SumL;
            end        
        end

        %Take means and cast to double:

        %Cast to type double for use as denominator
        TrueCount_Double = double(TrueCount);

        RGBMeans_Double(1)   = double(SumR)        / TrueCount_Double;
        RGBMeans_Double(2)   = double(SumG)        / TrueCount_Double;
        RGBMeans_Double(3)   = double(SumB)        / TrueCount_Double;  
        LuminanceMean_Double = double(SumL)        / TrueCount_Double;
    end


%%%%%%% If taking the luminance mean is not enabled %%%%%%%

else
    
    %%%%%% --- Optimized with integer arithmetic %%%%%%

    %If matrix IsSkinMask is under specified size, use algorithm optimized with integer arithmetic.
    if NElements < 15686000

        %Initialize accumulating variables
        %Use a type that is large enought to prevent overflow.
        SumR_uint32 = uint32(0);
        SumG_uint32 = uint32(0);
        SumB_uint32 = uint32(0);        
        
        %Loop across elements, accumulating sum
        parfor i = 1 : NElements

            %If element classified as skin
            if LogIdx(i)

                %Cast to type uint32 and accumulate
                SumR_uint32 = uint32( R_Uint8(i) ) + SumR_uint32;
                SumG_uint32 = uint32( G_Uint8(i) ) + SumG_uint32;
                SumB_uint32 = uint32( B_Uint8(i) ) + SumB_uint32;
            end        
        end

        %Take means and cast to double:

        %Cast to type double for use as denominator
        TrueCount_Double = double(TrueCount);

        RGBMeans_Double(1) = double(SumR_uint32) / TrueCount_Double;
        RGBMeans_Double(2) = double(SumG_uint32) / TrueCount_Double;
        RGBMeans_Double(3) = double(SumB_uint32) / TrueCount_Double;

    %%%%%% --- Not optimized with integer arithmetic %%%%%%    

    else

        %Initialize accumulating variables
        SumR = single(0);
        SumG = single(0);
        SumB = single(0);

        %Loop across elements, accumulating sum
        parfor i = 1 : NElements

            %If element classified as skin
            if LogIdx(i)

                %Cast to type single and accumulate
                SumR = single( R_Uint8(i) ) + SumR;
                SumG = single( G_Uint8(i) ) + SumG;
                SumB = single( B_Uint8(i) ) + SumB;
            end        
        end

        %Take means and cast to double:

        %Cast to type double for use as denominator
        TrueCount_Double = double(TrueCount);

        RGBMeans_Double(1) = double(SumR) / TrueCount_Double;
        RGBMeans_Double(2) = double(SumG) / TrueCount_Double;
        RGBMeans_Double(3) = double(SumB) / TrueCount_Double;    
    end    
end


end %end function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(IndexAndMean_Uint8_LogIdx_mex) of the function.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%                                    Example Code                 Upp. Bounds    Var. Size (T/F)   Type
Matrix1_Uint8Code    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],    [1, 1] );         %uint8
Matrix2_Uint8Code    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],    [1, 1] );         %uint8
Matrix3_Uint8Code    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],    [1, 1] );         %uint8
Luminance_SingleCode = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],    [1, 1] );         %single
LogIdxCode           = coder.typeof( false(500, 500),             [inf, inf],    [1, 1] );         %logical 


%%%%%% Specify fixed-size input arguments %%%%%%

NRowsCode               = int32(0);
NColsCode               = int32(0);
TrueCountCode           = uint32(0);
TakeLuminanceMeanTFCode = false;


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

%Assign to code-generation configuration object
cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen IndexAndMean_LogIdx.m -report -config cfg -args {Matrix1_Uint8Code, Matrix2_Uint8Code, Matrix3_Uint8Code, Luminance_SingleCode, LogIdxCode, NRowsCode, NColsCode, TrueCountCode, TakeLuminanceMeanTFCode}
             
%}


