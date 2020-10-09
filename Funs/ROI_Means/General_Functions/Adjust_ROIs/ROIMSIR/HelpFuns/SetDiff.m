function Set = SetDiff(A, A_length, B, B_length) %#codegen
%SetDiff   Return the elements of set A that are different from set B, assuming elements within   
%          each set do not repeat and monotonically increase.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions ROIMSIR_FrameByFrameSmooth_InterpFR and
%    ROIMSIR_FrameByFrameSmooth_SmoothFR.
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
%    Optimized algorithm for returning the elements of set A that are different from set B. 
%    Optimized by assuming that, within each set, elements do not repeat and monotonically 
%    increase.
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


%Preallocate output
Set = coder.nullcopy( zeros(A_length, 1, 'int32') );

%Index of A of elements that are different from B
%The elements of A corresponding to this index will be returned as output Set.
KeepCounter = int32(0);

%Index of B where last match made with A
LastMatch = int32(0);

%Loop across elements of A
for i = 1 : A_length

    %Reset match flag
    MatchTF = false;   

    %On first iteration of each while-loop, start after the element of B where the last match was
    %made. This increases efficiency by skipping elements of B where a match was already made. This 
    %is only possible when the values within each input are sorted and unique.
    j = LastMatch;
    
    %Loop across elements of B
    %Note: once all elements of B have been iterated across, all remaining elements of A are 
    %considered different than B. This is only possible when all values of A are unique.
    while j < B_length
                    
        j = j + 1;                       

        %If B(j) matches A(i)
        if A(i) == B(j)                        

            MatchTF = true;
            
            LastMatch = j;
            
            %With assumption that only unique values within each set, the remaining elements in B
            %can be skipped for this element of A.
            break                              
        end 
    end

    %Assign A(i) if no match with B
    if ~ MatchTF

        KeepCounter = KeepCounter + 1;

        %Assign value of A(i)
        Set(KeepCounter) = A(i);            
    end
end

%Trim preallocated rows that were not assigned
Set = Set(1 : KeepCounter);


end %end function

