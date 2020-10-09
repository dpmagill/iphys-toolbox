function yi = ... 
             Interp(x, y, xi, LinearExtrapTF, ValidityChecksTF, DiffMaxActual, YArbitrary, ...
                 DiffMaxArbitrary, VidObjWidth, VidObjHeight) %#codegen               
%Interp   Conduct linear interpolation/extrapolation or nearest-neighbor extrapolation.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions ROIMeans_FirstRead_ExtrapolateROI, 
%    ROIMSIR_Interpolate and ROIMSIR_FrameByFrameSmooth_InterpFR.
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
%    When LinearExtrapTF == true, conduct linear interpolation or extrapolation. 
%    When LinearExtrapTF == false, conduct linear interpolation only when xi falls within domain of 
%    x. Otherwise, conduct nearest-neighbor extrapolation.
%
%    When ValidityChecksTF == true, conduct checks and adjustments on values returned by linear
%    interpolation / extrapolation. These checks and adjustments include ...  
%
%    - Checking whether the difference between an interpolated value and a nearby actual value is
%      within a specified threshold (DiffMaxActual). If not, this may be an indication of an  
%      overshoot; in this case, the interpolated value is changed to the maximum value specified by 
%      the threshold. This check and adjustment are only applied to an interpolated value 
%      corresponding to the X- or Y-coordinate (rather than height or width) of the ROI. The check 
%      is not applied to height or width as testing has indicated that an overshoot  is not as  
%      common for height or width.
%
%    - Checking whether an interpolated value corresponding to ROI height or width is above 20. If
%      not, the interpolated value is recalculated by conducting nearest-neighbor extrapolation. A
%      height or width below 20 is considered to be too small for the size of faces expected in a
%      video.
%
%    - Checking whether an interpolated value is within the frame dimensions (minimum of 1 and
%      maximums of VidObjWidth and VidObjHeight). If not, the interpolated value is changed to be
%      bounded by the frame dimensions.
%
%    When YArbitrary is non-empty, conduct checks and adjustments on interpolated / extrapolated
%    values. These checks and adjustments include ...  
%
%    - Checking whether the difference between an interpolated value and a nearby arbitrary value 
%      is within a specified threshold (DiffMaxArbitrary). If not, this may be an indication of an  
%      overshoot; in this case, the interpolated value is changed to the maximum value specified by 
%      the threshold. This check and adjustment are only applied to an interpolated value 
%      corresponding to the X- or Y-coordinate (rather than height or width) of the ROI. The check 
%      is not applied to height or width as testing has indicated that an overshoot is not as  
%      common for height or width.
%
%    -- Restrictions --
%
%    - x is are assumed to increase monotonically and contain unique values. x must contain at
%      least two elements. The number of elements must equal the number of elements of y.                        
%    - xi is assumed to increase monotonically. 
%    - y is assumed to have 4 columns. y must contain at least two elements. The number of elements 
%      must equal the number of elements of x. 
%
%    This function uses bounded variable sizes to improve efficiency. Ensure that inputs do not
%    exceed the bounds.
%
%    -- Arguments --
%
%    Inputs:
%
%    x                = Time values that correspond to values of y. M x 1 column vector; type 
%                       single.
%    y                = Values from which to interpolate. M x :4 matrix; type int16.                   
%    xi               = Time values at which interpolation will occur. The elements do not need to  
%                       be unique. The number of values is not restricted. Column vector; type 
%                       single.                                        
%    LinearExtrapTF   = If true, use the linear method for extrapolation. If false, use the 
%                       nearest-neighbor method. Scalar; type logical.
%    ValidityChecksTF = If true, check whether the interpolated values appears valid. Scalar; 
%                       type logical.
%    DiffMaxActual    = The threshold specifying the maximum absolute-value difference between an 
%                       interpolated / extrapolated value and a previous actual value. Scalar; type 
%                       int16. Threshold only applied when InterpChecksTF == true;     
%    DiffMaxArbitrary = The threshold specifying the maximum absolute-value difference between an 
%                       interpolated / extrapolated value and an arbitrary X- or Y-coordinate  
%                       value, which is specified by YArbitrary. Scalar; type int16.                     
%    YArbitrary       = Arbitary X- and Y-coordinate values used with the threshold specified by 
%                       DiffMaxArbitrary. To disable DiffMaxArbitrary checks, use 0 x 2 input.                        
%                       0 x 2 or 1 x 2 row vector; type int16.                                                                                    
%    VidObjWidth      = The frame width. Scalar; type int16.
%    VidObjHeight     = The frame height. Scalar; type int16.
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


%Whether to conduct arbitrary value check
ArbitraryCheckTF = ~ isempty(YArbitrary);

%Length of input time points
x_length = int32( numel(x) );

%Length of input interpolation timepoints
%This length will equal the length of yi.
xi_length = int32( numel(xi) );

nColsY = size(y, 2);

%Assert length to prevent dynamic memory allocation by colon operator
assert(nColsY <= 4);

%Preallocate output
yi = coder.nullcopy( zeros(xi_length, nColsY, 'int16') );

%Initialize x_idx at 1 
%x_idx is used to search for the value of x that is greater than xi.
%In while loop, the first operation is to increment j by 1; hence, the effective use of x_idx
%starts at 2.
%By initializing x_idx here, rather than after each iteration of i, it is assumed that both x and  
%xi are sorted in order from least to greatest. This assumption improves performance because values 
%of x already matched are not researched (a qualification is that the implementation does research  
%the immediately previous value of x -- see note within loop). If x or xi is not sorted, the   
%initialization of x_idx (setting x_idx to 1) should occur after each iteration of i.
x_idx = int32(1); 

%Loop across interpolation times points
for xi_idx = 1 : xi_length    

    %The ith xi value (the ith interpolation point)
    xi_ith = xi(xi_idx);
    
    %Find the indices of x: x_before_idx and x_after_idx:      

    %If ith xi value is to left of domain of x
    %Case of extrapolation.
    if xi_ith < x(1)     
        
        %If linear extrapolation permitted
        if LinearExtrapTF

            %Assign first and second indices of x
            x_before_idx = int32(1);
            x_after_idx  = int32(2);            
            
            %Linear extrapolation
            %Local function.
            %1 x nColsY row vector; type int16.
            yi_ith = ...
                ExtrapLinear(x, x_before_idx, x_after_idx, y, xi_ith, nColsY, ValidityChecksTF, ...
                    DiffMaxActual, ArbitraryCheckTF, YArbitrary, DiffMaxArbitrary); 
                                       
        else
            
            %Flag indicating ith xi value is to left of domain of x
            LeftOfDomainTF = true;           
            
            %Nearest-neighbor extrapolation
            %Local function.
            %1 x nColsY row vector; type int16.   
            yi_ith = ...
                ExtrapNearest(y, LeftOfDomainTF, nColsY, x_length, ArbitraryCheckTF, ...
                    YArbitrary, DiffMaxArbitrary);                                
        end           
        
    %If ith xi value is either within domain of x or to right of domain of x      
    else                 
        
        %If xi is within the domain of x, ...
        % - x_before_idx is the index of x where x is less than xi.
        % - x_after_idx is the index of x where x is greater than or equal to xi.
        
        %If xi is to right of the domain of x, ...
        % - both x_before_idx and x_after_idx index x where x is less than xi. 
        % - x at x_before_idx is less than x at x_after_idx.
                      
        while true 

            x_idx = x_idx + 1;

            %If ith xi value is to right of domain of x
            %Case of extrapolation.
            if x_idx >= x_length 
                                               
                %If linear extrapolation permitted
                if LinearExtrapTF
                    
                    %Assign x indices
                    x_before_idx = x_length - 1;            
                    x_after_idx  = x_length;
                
                    %Linear extrapolation
                    %Local function.
                    %1 x nColsY row vector; type int16.
                    yi_ith = ...
                        ExtrapLinear(x, x_before_idx, x_after_idx, y, xi_ith, nColsY, ...
                            ValidityChecksTF, DiffMaxActual, ArbitraryCheckTF, YArbitrary, ...
                            DiffMaxArbitrary);    

                else

                    %Flag indicating ith xi value is to right of domain of x
                    LeftOfDomainTF = false;                    
                    
                    %Nearest-neighbor extrapolation
                    %Local function.
                    %1 x nColsY row vector; type int16.   
                    yi_ith = ...
                        ExtrapNearest(y, LeftOfDomainTF, nColsY, x_length, ArbitraryCheckTF, ...
                            YArbitrary, DiffMaxArbitrary);                                        
                end   
            
                %Set back x_idx by one for use for i+1th xi element.
                %xi is assumed to be sorted, but the values are not assumed to be unique, so x_idx
                %should start back by one in case the next value of xi is the same as the current.
                %Even is all values are unique, floating-point imprecision could effectively cause
                %some to be non-unique.
                x_idx = x_idx - 1;     
                
                break

            %If ith xi value is within of domain of x   
            %Case of interpolation.
            elseif x(x_idx) >= xi_ith 

                %Assign x indices
                x_before_idx = x_idx - 1;
                x_after_idx  = x_idx;
                
                %Linear interpolation
                %Local function.
                %1 x nColsY row vector; type int16.                
                yi_ith = ...
                    InterpLinear(x, x_before_idx, x_after_idx, y, xi_ith, nColsY, ...
                        ValidityChecksTF, DiffMaxActual, ArbitraryCheckTF, YArbitrary, ...
                        DiffMaxArbitrary);
                                            
                %Set back x_idx by one for use for i+1th xi element.
                %xi is assumed to be sorted, but the values are not assumed to be unique, so x_idx
                %should start back by one in case the next value of xi is the same as the current.
                %Even is all values are unique, floating-point imprecision could effectively cause
                %some to be non-unique.
                x_idx = x_idx - 1;   
                
                break           
            end        
        end 
    end
        
    %Check whether interpolated values are within frame dimensions
    %If not, adjust to be within frame dimensions.        
    if ValidityChecksTF

        %Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder
        %'FacePulseRate'.
        %1 x nColsY row vector; type int16.
        yi_ith = ...
            ROIAdjustIfExceedsFrameDims( ...
                yi_ith, ...
                VidObjWidth, ...
                VidObjHeight ...
            );            
    end
    
    %Assign interpolated / extrapolated values of yi at xi
    yi(xi_idx, 1 : nColsY) = yi_ith;         
end


end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function yi_ith = ...
             InterpLinear(x, x_before_idx, x_after_idx, y, xi_ith, nColsY, ValidityChecksTF, ...
                 DiffMaxActual, ArbitraryCheckTF, YArbitrary, DiffMaxArbitrary)                        
%InterpLinear   Linear interpolation of y at a single time point (xi).


%Inline function
coder.inline('always');
 

%Preallocate output for ith yi values
yi_ith = coder.nullcopy( zeros(1, nColsY, 'int16') );   

%Assign x values  
%Scalars; type single.
x_before = x(x_before_idx);
x_after  = x(x_after_idx); 

%Proportion of interpolated time interval to actual time interval
%Scalar; type single.
r = (xi_ith - x_before) / (x_after - x_before);

%Loop across columns of y
for j = int32(1) : nColsY

    %y value that comes before time point to be interpolated
    %Scalar; type int16.
    y_before = y(x_before_idx, j);
    
    %y value that comes after time point to be interpolated
    %Scalar; type int16.
    y_after  = y(x_after_idx, j);

    
    %%%%%% Skip interpolation %%%%%%
    
    %If y values same, assign one of them as interpolated value
    if y_before == y_after

        yi_ijth = y_before;
        
        
    %%%%%% Interpolate %%%%%%         
        
    else           
        
        %Step 1
        %Interpolated distance of y.
        %Multipy interpolated time-interval proportion by actual change in y.
        %Cast to floating-point type to multiply.  
        yDistance = int16( single( (y_after - y_before) ) * r );

        %Step 2
        %Add distance to most immediate previous actual y value.
        yi_ijth = y_before + yDistance;                             
               
        %%%%%% --- Check whether interpolated value appears valid %%%%%%
        
        if ValidityChecksTF             
 
            %Local function.
            %Scalar; type int16.
            yi_ijth = ...
                ValidityCheck(yi_ijth, y_before, y_after, xi_ith, x_before, x_after, j, ...
                    DiffMaxActual);                   
        end
    end
    
    
    %%%%%% Check whether interpolated value within specified distance from arbitrary value %%%%%% 
    
    %If arbitary check enabled   
    if ArbitraryCheckTF && j < 3
        
        %Check whether the interpolated X- or Y-coordinate is within a specified distance 
        %(DiffMaxArbitrary) from a specified X- or Y-coordinate.
        
        %Local function.
        %Scalar; type int16.
        yi_ijth = ArbitraryCheck_XY(yi_ijth, j, YArbitrary, DiffMaxArbitrary);
    end    
    
    
    %%%%%% Assign %%%%%%

    yi_ith(j) = yi_ijth;    
end
    

end %end local function


%=============================================================================================
function yi_ith = ...
             ExtrapLinear(x, x_before_idx, x_after_idx, y, xi_ith, nColsY, ValidityChecksTF, ...
                 DiffMaxActual, ArbitraryCheckTF, YArbitrary, DiffMaxArbitrary)                        
%ExtrapLinear   Linear extrapolation of y at a single time point (xi).
%
%    Note:
%
%    Same as function InterpLinear except that an integer overflow check is also conducted.


%Inline function
coder.inline('always');
 

%Preallocate output for ith yi values
yi_ith = coder.nullcopy( zeros(1, nColsY, 'int16') );   

%Assign x values   
%Scalars; type single.
x_before = x(x_before_idx);
x_after  = x(x_after_idx); 

%Proportion of interpolated time interval to actual time interval
%Scalar; type single.
r = (xi_ith - x_before) / (x_after - x_before);

%Loop across columns of y
for j = int32(1) : nColsY

    %y value that comes before time point to be interpolated
    %Scalar; type int16.
    y_before = y(x_before_idx, j);
    
    %y value that comes after time point to be interpolated
    %Scalar; type int16.
    y_after  = y(x_after_idx, j);
    
    
    %%%%%% Skip extrapolation %%%%%%
    
    %If y values same, assign one of them as extrapolated value
    if y_before == y_after

        yi_ijth = y_before;

        
    %%%%%% Extrapolate %%%%%%         
        
    else           
        
        %Step 1
        %Extrapolated distance of y.
        %Multipy interpolated time-interval proportion by actual change in y.
        %Cast to floating-point type to multiply. 
        %Scalar; type single.
        yDistance = single( (y_after - y_before) ) * r;

        %Step 2
        %Add distance to most immediate previous actual y value.
        %As extrapolation could result in extreme value for y, conduct operation so that it can be
        %determined whether type int16 could overflow; specifically, cast to type int32 to prepare
        %for later check.
        %Scalar; type int32.
        yi_ijth_int32 = int32(y_before) + int32(yDistance);
                             
        %Check if extrapolated value will cause int16 type to overflow
        %If so, assign maximum or minimum value.

        %If positive value 
        if yi_ijth_int32 > 0

            %If exceeds maximum value of type            
            if yi_ijth_int32 >= int32(32767)

                yi_ijth_int32 = int32(32767);                
            end
            
        %If negative value
        else
            
            %If exceeds minimum value of type
            if yi_ijth_int32 <= int32(-32767)

                yi_ijth_int32 = int32(-32767); 
            end
        end
        
        %Cast back to type int16
        yi_ijth = int16(yi_ijth_int32);
               
        %%%%%% --- Check whether interpolated value appears valid %%%%%%
        
        if ValidityChecksTF

            %Local function.
            %Scalar; type int16.
            yi_ijth = ...
                ValidityCheck(yi_ijth, y_before, y_after, xi_ith, x_before, x_after, j, ...
                    DiffMaxActual);            
        end
    end

    
    %%%%%% Check whether interpolated value within specified distance from arbitrary value %%%%%% 
      
    %If arbitary check enabled
    if ArbitraryCheckTF && j < 3
        
        %Check whether the interpolated X- or Y-coordinate is within a specified distance 
        %(DiffMaxArbitrary) from a specified X- or Y-coordinate.
        %Local function.
        %Scalar; type int16.
        yi_ijth = ArbitraryCheck_XY(yi_ijth, j, YArbitrary, DiffMaxArbitrary);            
    end    
    
    
    %%%%%% Assign %%%%%%

    %Scalar; type int16.
    yi_ith(j) = yi_ijth;    
end
    

end %end local function


%=============================================================================================
function yi_ith = ...
             ExtrapNearest(y, LeftOfDomainTF, nColsY, x_length, ArbitraryCheckTF, YArbitrary, ...
                  DiffMaxArbitrary)
%ExtrapNearest   Nearest-neighbor extrapolation of y at single time point (xi).


%Inline function
coder.inline('always');


%Preallocate output for ith yi values
yi_ith = coder.nullcopy( zeros(1, nColsY, 'int16') );

%If ith xi value is to left of domain of x
if LeftOfDomainTF

    %Loop across columns of y
    for j = int32(1) : nColsY

        %Assign from first row of y
        yi_ijth = y(1, j); 
        
        %If arbitary check enabled
        if ArbitraryCheckTF && j < 3

            %Check whether the interpolated X- or Y-coordinate is within a specified distance 
            %(DiffMaxArbitrary) from a specified X- or Y-coordinate.
            
            %Local function.
            %Scalar; type int16.            
            yi_ijth = ArbitraryCheck_XY(yi_ijth, j, YArbitrary, DiffMaxArbitrary);                                     
        end 
        
        yi_ith(j) = yi_ijth;
    end  
    
%If ith xi value is to right of domain of x    
else
    
    %Loop across columns of y
    for j = int32(1) : nColsY

        %Assign from last row of y
        yi_ijth = y(x_length, j);
        
        %If arbitary check enabled
        if ArbitraryCheckTF && j < 3

            %Check whether the interpolated X- or Y-coordinate is within a specified distance 
            %(DiffMaxArbitrary) from a specified X- or Y-coordinate.
            
            %Local function.
            %Scalar; type int16.
            yi_ijth = ArbitraryCheck_XY(yi_ijth, j, YArbitrary, DiffMaxArbitrary);                                     
        end 
        
        yi_ith(j) = yi_ijth;
    end
end


end %end local function


%=============================================================================================
function yi_ijth = ...
             ValidityCheck(yi_ijth, y_before, y_after, xi_ith, x_before, x_after, j, ...
                 DiffMaxActual)
%ValidityCheck   Check whether interpolated / extrapolated value appears valid.


%Inline function
coder.inline('always');


%Switch according to column
switch j

    case 1 %x-coordinate column

        %Local function.
        yi_ijth = ...
            ValidityCheck_XY(yi_ijth, y_before, DiffMaxActual);
        
    case 2 %y-coordinate column
        
        %Local function.
        yi_ijth = ...
            ValidityCheck_XY(yi_ijth, y_before, DiffMaxActual); 
        
    case 3 %width column
        
        %Local function.
        yi_ijth = ValidityCheck_WH(yi_ijth, xi_ith, x_before, x_after, y_before, y_after);
        
    case 4 %height column
        
        %Local function.
        yi_ijth = ValidityCheck_WH(yi_ijth, xi_ith, x_before, x_after, y_before, y_after);        
end
            
            
end %end local function


%=============================================================================================
function yi_ijth = ValidityCheck_XY(yi_ijth, y_before, DiffMaxActual)         
%ValidityCheck_XY   Validity check for X- or Y-coordinate.
%
%    Description:
%
%    Check whether difference between before-value and interpolated / extrapolated value is greater  
%    than specified threshold. If so, set value at maximum of threshold. 
      

%Inline function
coder.inline('always');
              

Diff = yi_ijth - y_before;

if Diff > DiffMaxActual

    yi_ijth = y_before + DiffMaxActual;

elseif Diff < -(DiffMaxActual)

    yi_ijth = y_before - DiffMaxActual;
end  


end %end local function


%=============================================================================================
function yi_ijth = ValidityCheck_WH(yi_ijth, xi_ith, x_before, x_after, y_before, y_after)
%ValidityCheck_WH   Validity check for width or height.
%
%    Description:
%
%    Check whether width or height value is less than 20. If so, then substitute the 
%    nearest-neighbor method in place of the linear method.
     

%Inline function
coder.inline('always');

             
if yi_ijth < int16(20)

    %Determine whether x_after or x_before nearest and assign.

    a = abs(x_after  - xi_ith); 
    b = abs(x_before - xi_ith);

    %x_after nearest
    if a <= b

        yi_ijth = y_after;

    %x_before nearest
    else

        yi_ijth = y_before;
    end            
end
    
    
end %end local function


%=============================================================================================
function yi_ijth = ArbitraryCheck_XY(yi_ijth, j, YArbitrary, DiffMaxArbitrary)                         
%ArbitraryCheck_XY   Check whether the interpolated / extrapolated X- or Y-coordinate is within a 
%                    specified distance (DiffMaxArbitrary) from a specified X- or Y-coordinate
%                    ( YArbitrary(j) ).
%
%    Description:
%
%    Check whether the interpolated / extrapolated X- or Y-coordinate is within a specified 
%    distance (DiffMaxArbitrary) from a specified for X- or Y-coordinate ( YArbitrary(j) ). If so, 
%    set value at maximum of threshold. 
%
%    Inputs (subset):
%
%    YArbitrary(1) = Specified arbitrary X-coordinate.
%    YArbitrary(2) = Specified arbitrary Y-coordinate.


%Inline function
coder.inline('always');


%Index either X- or Y-coordinate from arbitrary ROI
YArbitrary_jth = YArbitrary(j);

Diff = yi_ijth - YArbitrary_jth;

if Diff > DiffMaxArbitrary

    yi_ijth = YArbitrary_jth + DiffMaxArbitrary;

elseif Diff < -(DiffMaxArbitrary)

    yi_ijth = YArbitrary_jth - DiffMaxArbitrary;
end


end %end local function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(Interp_mex) of the function.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.
%                                    Example Code                 Upp. Bounds    Var. Size (T/F)  Type
xCode                = coder.typeof( zeros(50, 1, 'single'),      [50, 1],       [1, 0] );        %single
yCode                = coder.typeof( zeros(50, 4, 'int16'),       [50, 4],       [1, 1] );        %int16
xiCode               = coder.typeof( zeros(50, 1, 'single'),      [50, 1],       [1, 0] );        %single                                                        
YArbitraryCode       = coder.typeof( zeros(1, 2, 'int16'),        [1, 2],        [1, 0] );        %int16


%%%%%% Specify fixed-size input arguments %%%%%%

LinearExtrapTFCode   = false;
InterpChecksTFCode   = false;
DiffMaxActualCode    = int16(0); 
VidObjWidthCode      = int16(0);
VidObjHeightCode     = int16(0);           
DiffMaxArbitraryCode = int16(0);    

                
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
cfg.DynamicMemoryAllocation = 'off'; %disabled to improve efficiency as all variables have bounded size


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

codegen Interp.m -report -config cfg -args {xCode, yCode, xiCode, LinearExtrapTFCode, InterpChecksTFCode, DiffMaxActualCode, YArbitraryCode, DiffMaxArbitraryCode, VidObjWidthCode, VidObjHeightCode}
 
%}
