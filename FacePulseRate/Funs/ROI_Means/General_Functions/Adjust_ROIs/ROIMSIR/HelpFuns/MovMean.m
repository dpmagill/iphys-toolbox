function ROIOut = MovMean(ROI, Win, NRowsROI, NColsROI) %#codegen
%MovMean   Moving mean column-wise smoother.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions ROIMSIR_DetectionSmooth and
%    ROIMSIR_FrameByFrameSmooth.
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
%    Use a moving mean to conduct column-wise smoothing to a matrix. Weight rows corresponding to
%    linear index WeightLinIdx by weight Weight.
%
%    Inputs:
%
%        ROI          = Matrix of values to be smoothed. M x :4 matrix; type int16. 
%        Win          = Moving-mean window. Scalar; type double.
%        NRowsROI     = The number of rows of the input matrix. Scalar; int32.
%        NColsROI     = The number of columns of the input matrix. Scalar; int32.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code generation settings %%%%%%

%Inline function
coder.inline('always');  


%%%%%% Setup %%%%%%

%Take half of window for use during operations
winHalf = int32( floor(Win / 2) );

%Make the full window equal twice the value of the half-window: 
winNew = int32(winHalf) * 2 + 1;    

%Assert maximum number of columns to prevent dynamic memory allocation by the colon operator
assert(NColsROI <= 4);

%Preallocate output
ROIOut = coder.nullcopy( zeros(NRowsROI, NColsROI, 'int16') );

Start = coder.nullcopy( int32(0) );


%%%%%% Reduce size of window if window cannot move %%%%%%

if NRowsROI <= winNew
   
    %Take one-fourth of window rather than one-half for use during operations
    winHalf = int32( floor(Win / 4) );

    %Make the full window equal twice the value of the half-window: 
    winNew = int32(winHalf) * 2 + 1;
end    


%%%%%% If window still cannot move %%%%%%

if NRowsROI <= winNew   
    
    %Loop across columns
    for i = int32(1) : NColsROI

        %Initialize accumulator
        Sum = int32(0);
        
        %Sum rows across window          
        for j = 1 : NRowsROI

            %Element cast to type int32.
            Sum = Sum + int32( ROI(j, i) );                       
        end  
 
        %Take the mean
        colMean = Sum / NRowsROI;
        
        %Assign the mean to all rows of column i
        for j = 1 : NRowsROI
            
            ROIOut(j, i) = colMean;    
        end        
    end

    
%%%%%% If window can move %%%%%%    
    
else

    %Loop across columns
    for i = int32(1) : NColsROI       
        
        %Initialize
        Sum = int32(0);      
 
        %%%%%% --- Apply moving mean to row 1 %%%%%%        
        
        %Set intial window end index
        End = winHalf + 1; 
            
        %Sum across truncated window          
        for j = int32(1) : End 

            %Cast to type int32 and add
            Sum = Sum + int32( ROI(j, i) );
        end       
        
        %Take mean
        ROIOut(1, i) = Sum / End;

        %%%%%% --- Apply moving mean up to first row where full window can be used %%%%%%
        
        %Set initial truncated window length
        n = End;
        
        %Loop across rows
        for j = int32(2) : winHalf + 1          
        
            %Set window end index for jth row
            End = j + winHalf; 
            
            %Add value at end of current window
            %Element cast to type int32.
            Sum = Sum + int32( ROI(End, i) );  

            %Take mean:                

            n = n + 1;

            %Mean
            ROIOut(j, i) = Sum / n;     
        end
       
        %%%%%% --- Apply moving mean for rows where full window can be used %%%%%% 
        
        %Loop across rows
        for j = winHalf + 2 : NRowsROI - winHalf         

            %Set window start index for jth row
            Start = j - winHalf;

            %Set window end index for jth row
            End   = j + winHalf;

            %Subtract value at start of previous window. 
            %Then, add value at end of current window.
            %Element cast to type int32.
            Sum = Sum - int32( ROI(Start - 1, i) ) + int32( ROI(End, i) );                 

            %Take mean
            ROIOut(j, i) = Sum / winNew;
        end 
        
        %%%%%% --- Apply moving mean for rows near end where full window cannot be used %%%%%%
        
        %Set intial window length
        n = winNew;        
        
        Start = Start - 2;
        
        for j = NRowsROI - winHalf + 1 : NRowsROI  
 
            Start = Start + 1;
            
            %Subtract value at start of previous window
            %Element cast to type int32.
            Sum = Sum - int32( ROI(Start, i) );                   

            %Take mean:       

            n = n - 1;

            %Mean
            ROIOut(j, i) = Sum / n;      
        end
    end
end


end %end function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(MovMean_mex) of the function.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.
%                        Example Code               Upp. Bounds   Var. Size (T/F)  Type
ROICode  = coder.typeof( zeros(50, 2, 'int16'),     [500, 2],      [1, 0] );        %int16


%%%%%% Specify fixed-size input arguments %%%%%%

winCode = double(0);
NRowsROI = int32(0);
NColsROI = int32(0);         
   
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

codegen MovMean.m -report -config cfg -args {ROICode, winCode, NRowsROI, NColsROI}
 
%}
