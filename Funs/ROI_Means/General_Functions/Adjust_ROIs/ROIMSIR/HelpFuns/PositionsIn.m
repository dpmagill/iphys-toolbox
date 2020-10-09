function PositionsAinB = PositionsIn(A, B, A_Length) %#codegen           
%PositionsIn   Return the index indicating where elements in set A are positioned in set B. 
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions ROIMSIR_DetectionSmooth and 
%    ROIMSIR_FaceDetectionLightSmooth.
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
%    Return the index indicating where elements in set A are positioned in set B. Various 
%    assumptions are made to increase efficiency. 
%
%        Assumptions
%   
%    - Elements of set A are entirely nested within set B.
%    - Within each set, values do not repeat and are ordered such that they increase monotonically.
%
%    Example:
%
%    A = [4, 5, 6];
%    B = [2, 3, 4, 5, 6];
%    A_Length = numel(A);
%
%    PositionsIn(A, B, A_Length)
%    >> [3; 4; 5]
%
%    -- Note --
%
%    The return values are equivalent to those returned by int32( find( ismember(B, A) )' );
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

%Index of B on a given iteration
BCounter = int32(0);

%Preallocate output
PositionsAinB = coder.nullcopy( zeros(A_Length, 1, 'int32') );         

%Loop across elements of A
for i = 1 : uint32(A_Length)

    while true

        BCounter = BCounter + 1; 

        if A(i) == B(BCounter)

            %Position (index) of ith index of A in B.
            PositionsAinB(i) = BCounter;

            break
        end                      
    end        
end  
    
    
end %end function

