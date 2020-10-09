function IsSkinMask = ...
             SkinSegmentMask_Threshold_Colors_NoConvert(YBounded_Single, CbBounded_Single, ...
                 CrBounded_Single, HBounded_Single, SBounded_Single, NRows_Matrix, ...
                 NCols_Matrix, NElements_Matrix, TailoredThresholdsTF, DontUseTailoredTF, ...
                 YCbCrThresholds_Generic, YCbCrThresholds_Tailored, HSThresholds_Generic, ...
                 HSThresholds_Tailored, UseLinIdxTF, XOffset, YOffset) %#codegen                                                                                  
%SkinSegmentMask_Threshold_Colors_NoConvert   Return a skin-segmentation mask by comparing channels    
%                                             of the YCbCr and HSV colorspaces of the input image  
%                                             to specified thresholds. The colorspaces used are
%                                             provided as input.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinSegmentMask_Threshold.
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
%    Return a skin-segmentation mask by comparing channels of the YCbCr and HSV colorspaces of the 
%    input image to specified thresholds. The colorspaces used are provided as input.
%
%    This function performs the same segmentation operations as function 
%    SkinSegmentMask_Threshold_Colors_Convert but does not conduct colorspace conversion as the 
%    necessary colorspaces are provided as input. In contrast, function 
%    SkinSegmentMask_Threshold_Colors_Convert converts the necessary colorspaces from the RGB
%    colorspace.
%
%    For a more detailed description of the operations performed here, see function
%    SkinSegmentMask_Threshold_Colors.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% Code-generation settings %%%%%%

%Inline function
coder.inline('always');


%%%%%% Prepare for operations %%%%%%

%If tailored thresholds not specified or if tailored thresholds specified but flag
%DontUseTailoredTF == true.
if ~ TailoredThresholdsTF || ...
   DontUseTailoredTF 

    %Values assigned by function SkinSegment_ConfigSetup.  
    %Note: these should be in type single for fastest evaluation.

    %Remove thresholds from struct for efficiency:
   
    YMin         = YCbCrThresholds_Generic(1);
    CbMin        = YCbCrThresholds_Generic(2);
    CbMax        = YCbCrThresholds_Generic(3);
    CrMin        = YCbCrThresholds_Generic(4);
    CrMax        = YCbCrThresholds_Generic(5);
    CbCrRatioMin = YCbCrThresholds_Generic(6);
    CbCrRatioMax = YCbCrThresholds_Generic(7);

    HMax         = HSThresholds_Generic(1);
    SMin         = HSThresholds_Generic(2);

    %Assign for code generation purposes
    %These values are not used in this condition.
    YMax = nan(1, 1, 'single');
    SMax = nan(1, 1, 'single');

else    
    
    %Values assigned by function SkinSegment_SetThresholds.
    %Note: these should be in type single for fastest evaluation. 

    %Remove thresholds from struct for efficiency
    YMin         = YCbCrThresholds_Tailored(1);
    YMax         = YCbCrThresholds_Tailored(2);
    CbMin        = YCbCrThresholds_Tailored(3);
    CbMax        = YCbCrThresholds_Tailored(4);
    CrMin        = YCbCrThresholds_Tailored(5);
    CrMax        = YCbCrThresholds_Tailored(6);
    CbCrRatioMin = YCbCrThresholds_Tailored(7);
    CbCrRatioMax = YCbCrThresholds_Tailored(8); 
    
    HMax = HSThresholds_Tailored(1);
    SMin = HSThresholds_Tailored(2);
    SMax = HSThresholds_Tailored(3);
    
end

%Preallocate skin-segmentation mask
IsSkinMask = coder.nullcopy( false(NRows_Matrix, NCols_Matrix) );


%%%%%%% Compiled version of function %%%%%% 

%Loop-based operations increase efficiency of the compiled version of the function but decrease the 
%efficiency of Matlab code, so conduct loop-based operations only for the compiled version of the 
%function.

if ~ coder.target('MATLAB') %code generation running
    
    %%%%%% --- Do not use tailored thresholds %%%%%%

    if ~ TailoredThresholdsTF || ...
       DontUseTailoredTF    

        %Index using a linear index
        if UseLinIdxTF                  
            
            for i = 1 : NElements_Matrix

                %Extract the ith y, cb, and cr values
                %Scalars; type single.
                y  = YBounded_Single(i);
                cb = CbBounded_Single(i); 
                cr = CrBounded_Single(i);       

                %Classify pixels within all thresholds as skin (true)       
                IsSkinMask_ith = ...
                    y  > YMin  && ...
                    cb > CbMin && ...
                    cb < CbMax && ...  
                    cr > CrMin && ... 
                    cr < CrMax; 

                if IsSkinMask_ith

                    %Extract the ith h and s values
                    %Scalars; type single.
                    h = HBounded_Single(i);
                    s = SBounded_Single(i); 
 
                    %Classify pixels within all thresholds as skin (true) 
                    IsSkinMask_ith = ...
                        h < HMax && ...
                        s > SMin; 
                end

                if IsSkinMask_ith

                    %Calculate Cb-to-Cr ratio
                    %Type single to permit division to return fractions.
                    CbCrRatio_ith = cb / cr;

                    IsSkinMask_ith = ...
                        CbCrRatio_ith > CbCrRatioMin && ... 
                        CbCrRatio_ith < CbCrRatioMax;
                end

                IsSkinMask(i) = IsSkinMask_ith;
            end    
        
        %Index using subscript indices
        else
            
            %Number of rows of the input matrices
            %Used for conversion to linear index.
            %Scalar; type int32.
            NRows_Full = int32( size(YBounded_Single, 1) );              
            
            %Initialize column index for skin-segmentation mask output                                   
            OutIdxX = uint16(0);
            
            %Loop across columns
            for i = XOffset : XOffset + NCols_Matrix - 1

                %Advance output index
                OutIdxX = OutIdxX + 1;
                
                %Initialize row index for skin-segmentation mask output
                OutIdxY = uint16(0);
                
                %Loop across rows
                for j = YOffset : YOffset + NRows_Matrix - 1
 
                    %Advance output index
                    OutIdxY = OutIdxY + 1;                    
                    
                    %Linear index corresponding to the full matrix
                    %Convert from subscript indices to a linear index for more efficient indexing
                    %Note: In compiled C code, the faster indexing outweighs the cost of this 
                    %conversion.
                    LinIdx_Full = j + (i - 1) * NRows_Full;
                    
                    %Extract the ith y, cb, and cr values
                    %Scalars; type single.
                    y  = YBounded_Single(LinIdx_Full);
                    cb = CbBounded_Single(LinIdx_Full); 
                    cr = CrBounded_Single(LinIdx_Full);       

                    %Classify pixels within all thresholds as skin (true)       
                    IsSkinMask_ith = ...
                        y  > YMin  && ...
                        cb > CbMin && ...
                        cb < CbMax && ...  
                        cr > CrMin && ... 
                        cr < CrMax; 

                    if IsSkinMask_ith

                        %Extract the ith h and s values
                        %Scalars; type single.
                        h = HBounded_Single(i);
                        s = SBounded_Single(i); 

                        %Classify pixels within all thresholds as skin (true) 
                        IsSkinMask_ith = ...
                            h < HMax && ...
                            s > SMin; 
                    end

                    if IsSkinMask_ith

                        %Calculate Cb-to-Cr ratio
                        %Type single to permit division to return fractions.
                        CbCrRatio_ith = cb / cr;

                        IsSkinMask_ith = ...
                            CbCrRatio_ith > CbCrRatioMin && ... 
                            CbCrRatio_ith < CbCrRatioMax;
                    end
                    
                    IsSkinMask(OutIdxY, OutIdxX) = IsSkinMask_ith;
                end
            end
        end   
        
    %%%%%% --- Use tailored thresholds %%%%%%     
        
        else         

        %Index using a linear index
        if UseLinIdxTF        
                     
            for i = 1 : NElements_Matrix         

                %Extract the ith h and s values
                %Scalars; type single.
                c1 = HBounded_Single(i);
                c2 = SBounded_Single(i);   

                %Classify pixels within all thresholds as skin (true) 

                IsSkinMask_ith = ...
                    c1 < HMax && ...
                    c2 > SMin && ...
                    c2 < SMax;

                if IsSkinMask_ith

                    %Extract the ith y, cb, and cr values
                    %Scalars; type single.
                    %Note: for efficiency, the output replaces somes variable previously 
                    %assigned.   
                    c1 = YBounded_Single(i);
                    c2 = CbBounded_Single(i); 
                    c3 = CrBounded_Single(i);   

                    IsSkinMask_ith = ... 
                        c1 > YMin  && ...
                        c1 < YMax  && ... 
                        c2 > CbMin && ...
                        c2 < CbMax && ... 
                        c3 > CrMin && ...
                        c3 < CrMax; 

                    if IsSkinMask_ith

                        %Calculate Cb-to-Cr ratio
                        %Type single to permit division to return fractions.
                        %Note: for efficiency, the output replaces a variable previously  
                        %assigned.
                        c1 = c2 / c3;

                        IsSkinMask_ith = ...
                            c1 > CbCrRatioMin && ... 
                            c1 < CbCrRatioMax;                            
                    end
                end

                IsSkinMask(i) = IsSkinMask_ith;
            end 
        
        %Index using subscript indices
        else 

            %Number of rows of the input matrices
            %Used for conversion to linear index.
            %Scalar; type int32.
            NRows_Full = int32( size(YBounded_Single, 1) );            
            
            %Initialize column index for skin-segmentation mask output                                   
            OutIdxX = uint16(0);  
            
            %Loop across columns
            for i = XOffset : XOffset + NCols_Matrix - 1
                    
                %Advance output index
                OutIdxX = OutIdxX + 1;
                
                %Initialize row index for skin-segmentation mask output                                   
                OutIdxY = uint16(0);                
                
                %Loop across rows
                for j = YOffset : YOffset + NRows_Matrix - 1                                       
                    
                    %Advance output index
                    OutIdxY = OutIdxY + 1; 
                    
                    %Linear index corresponding to the full matrix
                    %Convert from subscript indices to a linear index for more efficient indexing
                    %Note: In compiled C code, the faster indexing outweighs the cost of this 
                    %conversion.
                    LinIdx_Full = j + (i - 1) * NRows_Full;                    
                    
                    %Extract the ith h and s values
                    %Scalars; type single.
                    c1 = HBounded_Single(LinIdx_Full);
                    c2 = SBounded_Single(LinIdx_Full);   

                    %Classify pixels within all thresholds as skin (true) 

                    IsSkinMask_ith = ...
                        c1 < HMax && ...
                        c2 > SMin && ...
                        c2 < SMax;

                    if IsSkinMask_ith

                        %Extract the ith y, cb, and cr values
                        %Scalars; type single.
                        %Note: for efficiency, the output replaces somes variable previously 
                        %assigned.   
                        c1 = YBounded_Single(LinIdx_Full);
                        c2 = CbBounded_Single(LinIdx_Full); 
                        c3 = CrBounded_Single(LinIdx_Full);   

                        IsSkinMask_ith = ... 
                            c1 > YMin  && ...
                            c1 < YMax  && ... 
                            c2 > CbMin && ...
                            c2 < CbMax && ... 
                            c3 > CrMin && ...
                            c3 < CrMax; 

                        if IsSkinMask_ith

                            %Calculate Cb-to-Cr ratio
                            %Type single to permit division to return fractions.
                            %Note: for efficiency, the output replaces a variable previously  
                            %assigned.
                            c1 = c2 / c3;

                            IsSkinMask_ith = ...
                                c1 > CbCrRatioMin && ... 
                                c1 < CbCrRatioMax;                            
                        end
                    end
            
                    IsSkinMask(OutIdxY, OutIdxX) = IsSkinMask_ith;                    
                end
            end            
        end
    end             
            

%%%%%%% Non-compiled version of function %%%%%%

%Use vectorized operations, which are more efficient for Matlab code.

else %running in Matlab code

    %Index using subscript indices
    if ~ UseLinIdxTF 
        
        %Crop according to specified offsets, width, and height:  
        
        YBounded_Single = ...
            YBounded_Single( ... 
                YOffset : YOffset + NRows_Matrix - 1, ...
                XOffset : XOffset + NCols_Matrix - 1 ...
            );

        CbBounded_Single = ...
            CbBounded_Single( ... 
                YOffset : YOffset + NRows_Matrix - 1, ...
                XOffset : XOffset + NCols_Matrix - 1 ...
            );   

        CrBounded_Single = ...
            CrBounded_Single( ... 
                YOffset : YOffset + NRows_Matrix - 1, ...
                XOffset : XOffset + NCols_Matrix - 1 ...
            );

        HBounded_Single = ...
            HBounded_Single( ... 
                YOffset : YOffset + NRows_Matrix - 1, ...
                XOffset : XOffset + NCols_Matrix - 1 ...
            ); 

        SBounded_Single = ...
            SBounded_Single( ... 
                YOffset : YOffset + NRows_Matrix - 1, ...
                XOffset : XOffset + NCols_Matrix - 1 ...
            );                             
    end    
    
    %%%%%% --- YCbCr thresholds %%%%%%
    
    %Assign CbCrRatio:
    
    %Calculate Cb-to-Cr ratio
    %Type single to permit division to return fractions.
    CbCrRatio = CbBounded_Single ./ CrBounded_Single;    

    %Apply YCbCr thresholds:
    
    %Use generic thresholds
    if ~ TailoredThresholdsTF || ...
       DontUseTailoredTF    

        %Pixels that are within all thresholds are classified as skin (i.e., as true)
        IsSkinMask =  ... 
            YBounded_Single    >  YMin        & ... 
            CbBounded_Single   > CbMin        & ...
            CbBounded_Single   < CbMax        & ...
            CrBounded_Single   > CrMin        & ...
            CrBounded_Single   < CrMax        & ...
            CbCrRatio          > CbCrRatioMin & ...
            CbCrRatio          < CbCrRatioMax;  
         
    %Use tailored thresolds     
    else
 
        %Pixels that are within all thresholds are classified as skin (i.e., as true)
        %Note: YMin not included in generic thresholds because YMin has been observed to be 
        %variable depending on individual differences in skin color of the face.
        IsSkinMask =  ... 
            YBounded_Single    >  YMin        & ... 
            YBounded_Single    <  YMax        & ...
            CbBounded_Single   > CbMin        & ...
            CbBounded_Single   < CbMax        & ...
            CrBounded_Single   > CrMin        & ...
            CrBounded_Single   < CrMax        & ...
            CbCrRatio          > CbCrRatioMin & ...
            CbCrRatio          < CbCrRatioMax;            
    end    
 
    %%%%%% --- H and S thresholds %%%%%%    

    %Use generic thresholds
    if ~ TailoredThresholdsTF || ...
       DontUseTailoredTF

        %Assign false where H-channel or S-channel pixels exceed threshold
        %M x N matrix; type logical.
        IsSkinMaskHS = ...
            HBounded_Single < HMax & ...
            SBounded_Single > SMin;

    %Use tailored thresholds
    else

        %Assign false where H-channel or S-channel pixels exceed threshold
        %M x N matrix; type logical.
        IsSkinMaskHS = ...
            HBounded_Single < HMax & ...
            SBounded_Single > SMin & ...
            SBounded_Single < SMax;
    end

    %Update skin-segmentation mask:
    
    %Assign false where the H-channel or the S-channel exceeds threshold
    %M x N matrix; type logical.
    IsSkinMask = IsSkinMask & IsSkinMaskHS;              
end


end %end function

