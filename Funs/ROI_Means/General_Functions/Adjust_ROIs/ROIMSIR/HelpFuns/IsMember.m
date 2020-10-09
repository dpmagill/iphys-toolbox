function TF = IsMember(a, B, BLength) %#codegen
%IsMember  Determine whether scalar a is a member of vector B.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions ROIMSIR and ROIMSIR_InterpolateFR.
%
%    Code Generation
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


TF = false;

for i = 1 : BLength
    
    if a == B(i)
        
        TF = true;
        
        break
    end
end


end %end function

