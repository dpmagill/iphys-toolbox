function [IsSkinMask, YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single, ...
          SBounded_Single] = ...
             SkinSegmentMask_Threshold_Colors_Convert(RBounded_Uint8, GBounded_Uint8, ...                
                 BBounded_Uint8, NRows_Matrix, NCols_Matrix, NElements_Matrix, ...
                 TailoredThresholdsTF, DontUseTailoredTF, YCbCrThresholds_Generic, ...
                 YCbCrThresholds_Tailored, ReturnYTF, ReturnCbCrTF, ReturnHSTF, ...
                 HSThresholds_Generic, HSThresholds_Tailored, UseLinIdxTF, XOffset, YOffset) 
                 %#codegen               
%SkinSegmentMask_Threshold_Colors_Convert   Return a skin-segmentation mask by comparing channels    
%                                           of the YCbCr and HSV colorspaces of the input image to 
%                                           specified thresholds. The colorspaces used will be
%                                           produced by the current function.
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
%    input image to specified thresholds. The colorspaces used will be produced by the current 
%    function.
%
%    This function performs the same segmentation operations as function 
%    SkinSegmentMask_Threshold_Colors_NoConvert but also converts the RGB colorspace to the 
%    necessary colorspaces. In contrast, function SkinSegmentMask_Threshold_Colors_NoConvert does
%    not conduct colorspace conversions as the necessary colorspace variables are provided to it as
%    input.
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

%Declare variables:
%                                   Upp. Bounds    Var. Size (T/F)
coder.varsize('IsSkinMask',         [inf, inf],    [1, 1]);
coder.varsize('YBounded_Single',    [inf, inf],    [1, 1]);
coder.varsize('CbBounded_Single',   [inf, inf],    [1, 1]);
coder.varsize('CrBounded_Single',   [inf, inf],    [1, 1]);
coder.varsize('HBounded_Single',    [inf, inf],    [1, 1]);
coder.varsize('SBounded_Single',    [inf, inf],    [1, 1]);


%%%%%% Operations %%%%%%

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

    %Remove thresholds from struct for efficiency:

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


%%%%%%% --- Compiled version of function %%%%%% 

%Loop-based operations increase efficiency of the compiled version of the function but decrease the 
%efficiency of Matlab code, so conduct loop-based operations only for the compiled version of the 
%function.

if ~ coder.target('MATLAB') %code generation running

    %%%%%% >>>>>> Assign alignment offsets for skin-segmentation mask %%%%%% 
    
    XOffsetMin1 = XOffset - 1;   
    YOffsetMin1 = YOffset - 1;    
    
    %%%%%% >>>>>> Do not return matrices from the the H and S channels of the HSV colorspace %%%%%%   
    if ~ ReturnHSTF    

        HBounded_Single = coder.const( single([]) );
        SBounded_Single = coder.const( single([]) );

        %Do not use tailored thresholds
        if ~ TailoredThresholdsTF || ...
           DontUseTailoredTF    

            %(1) Condition 1
            % - Use generic thresholds: generic YCbCr and HS thresholds.
            % - Do not return H and S channel matrices.
            % - Do not return matrices of the Y, Cb, or Cr channels.       
            if ~ ReturnCbCrTF && ~ ReturnYTF
                
                %M x N matrices; type single.
                YBounded_Single  = coder.const( single([]) );
                CbBounded_Single = coder.const( single([]) );
                CrBounded_Single = coder.const( single([]) );   

                %Index using a linear index
                if UseLinIdxTF
                
                    %Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm
                    for i = 1 : NElements_Matrix

                        %Extract and cast to type single the ith r, g, and b values
                        %Scalars; type single.
                        r = single( RBounded_Uint8(i) );
                        g = single( GBounded_Uint8(i) ); 
                        b = single( BBounded_Uint8(i) );       

                        %Apply the RGB-to-YCbCr algorithm
                        %Scalars; type single.
                        %Note: for efficiency, the outputs replace the inputs.
                        %Note: rgb2ycbcr_compute is a custom function located within folder
                        %'FacePulseRate'.
                        [y,    ... y
                         cb,   ... cb 
                         cr] = ... cr
                            rgb2ycbcr_compute(r, g, b);

                        %Classify pixels within all thresholds as skin (true)       
                        IsSkinMask_ith = ...
                            y  > YMin  && ...
                            cb > CbMin && ...
                            cb < CbMax && ...  
                            cr > CrMin && ... 
                            cr < CrMax; 

                        if IsSkinMask_ith

                            %Apply rgb-to-hs algorithm
                            %Scalars; type single.
                            %Note: rgb2h is a custom function located within folder 
                            %'FacePulseRate'.  
                            [h, s] = rgb2hs(r, g, b); 
                            
                            %Classify pixels within all thresholds as skin (true) 
                            IsSkinMask_ith = ...
                                h  < HMax  && ...
                                s  > SMin; 
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
                    
                    for i = XOffset : XOffset + NCols_Matrix - 1

                        for j = YOffset : YOffset + NRows_Matrix - 1 
                            
                            %Indices for output matrices
                            YAdjust = j - YOffsetMin1; 
                            XAdjust = i - XOffsetMin1;  
                            
                            %Extract and cast to type single the ith r, g, and b values
                            %Scalars; type single.
                            r = single( RBounded_Uint8(j, i) );
                            g = single( GBounded_Uint8(j, i) ); 
                            b = single( BBounded_Uint8(j, i) );       

                            %Apply the RGB-to-YCbCr algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the outputs replace the inputs.
                            %Note: rgb2ycbcr_compute is a custom function located within folder
                            %'FacePulseRate'.
                            [y,    ... y
                             cb,   ... cb 
                             cr] = ... cr
                                rgb2ycbcr_compute(r, g, b);

                            %Classify pixels within all thresholds as skin (true)       
                            IsSkinMask_ith = ...
                                y  > YMin  && ...
                                cb > CbMin && ...
                                cb < CbMax && ...  
                                cr > CrMin && ... 
                                cr < CrMax;
 
                            if IsSkinMask_ith

                                %Apply rgb-to-hs algorithm
                                %Scalars; type single.
                                %Note: rgb2h is a custom function located within folder 
                                %'FacePulseRate'.  
                                [h, s] = rgb2hs(r, g, b); 

                                %Classify pixels within all thresholds as skin (true) 
                                IsSkinMask_ith = ...
                                    h  < HMax  && ...
                                    s  > SMin; 
                            end

                            if IsSkinMask_ith

                                %Calculate Cb-to-Cr ratio
                                %Type single to permit division to return fractions.
                                CbCrRatio_ith = cb / cr;

                                IsSkinMask_ith = ...
                                    CbCrRatio_ith > CbCrRatioMin && ... 
                                    CbCrRatio_ith < CbCrRatioMax;
                            end

                            IsSkinMask(YAdjust, XAdjust) = IsSkinMask_ith;
                        end
                    end
                end
                
            %(2) Condition 2                
            % - Use generic thresholds: generic YCbCr and HS thresholds.
            % - Do not return H and S channel matrices.
            % - Return Y-channel matrix but not the Cb and Cr channel matrices.                
            elseif ~ ReturnCbCrTF && ReturnYTF
                
                %M x N matrices; type single.
                YBounded_Single  = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
                CbBounded_Single = coder.const( single([]) );
                CrBounded_Single = coder.const( single([]) );   

                %Index using a linear index
                if UseLinIdxTF               
                
                    %Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm
                    for i = 1 : NElements_Matrix

                        %Extract and cast to type single the ith r, g, and b values
                        %Scalars; type single.
                        r = single( RBounded_Uint8(i) );
                        g = single( GBounded_Uint8(i) ); 
                        b = single( BBounded_Uint8(i) );       

                        %Apply the RGB-to-YCbCr algorithm
                        %Scalars; type single.
                        %Note: for efficiency, the outputs replace the inputs.
                        %Local function.    
                        %Note: rgb2ycbcr_compute is a custom function located within folder
                        %'FacePulseRate'.
                        [y,   ... y
                         cb,   ... cb
                         cr] = ... cr
                            rgb2ycbcr_compute(r, g, b);

                        %Assign the ith y, value
                        YBounded_Single(i) = y; 

                        %Classify pixels within all thresholds as skin (true)       
                        IsSkinMask_ith = ...
                            y  > YMin  && ...
                            cb > CbMin && ...
                            cb < CbMax && ...  
                            cr > CrMin && ... 
                            cr < CrMax;
 
                        if IsSkinMask_ith

                            %Apply rgb-to-hs algorithm
                            %Scalars; type single.
                            %Note: rgb2h is a custom function located within folder 
                            %'FacePulseRate'.  
                            [h, s] = rgb2hs(r, g, b); 

                            %Classify pixels within all thresholds as skin (true) 
                            IsSkinMask_ith = ...
                                h  < HMax  && ...
                                s  > SMin; 
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
                    
                   for i = XOffset : XOffset + NCols_Matrix - 1

                        for j = YOffset : YOffset + NRows_Matrix - 1                          
             
                            %Indices for output matrices
                            YAdjust = j - YOffsetMin1; 
                            XAdjust = i - XOffsetMin1;
                            
                            %Extract and cast to type single the ith r, g, and b values
                            %Scalars; type single.
                            r = single( RBounded_Uint8(j, i) );
                            g = single( GBounded_Uint8(j, i) ); 
                            b = single( BBounded_Uint8(j, i) );       

                            %Apply the RGB-to-YCbCr algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the outputs replace the inputs.
                            %Local function.    
                            %Note: rgb2ycbcr_compute is a custom function located within folder
                            %'FacePulseRate'.
                            [y,    ... y
                             cb,   ... cb
                             cr] = ... cr
                                rgb2ycbcr_compute(r, g, b);

                            %Assign the ith y, value
                            YBounded_Single(YAdjust, XAdjust) = y; 

                            %Classify pixels within all thresholds as skin (true)       
                            IsSkinMask_ith = ...
                                y  > YMin  && ...
                                cb > CbMin && ...
                                cb < CbMax && ...  
                                cr > CrMin && ... 
                                cr < CrMax; 

                            if IsSkinMask_ith

                                %Apply rgb-to-hs algorithm
                                %Scalars; type single.
                                %Note: rgb2h is a custom function located within folder 
                                %'FacePulseRate'.  
                                [h, s] = rgb2hs(r, g, b); 

                                %Classify pixels within all thresholds as skin (true) 
                                IsSkinMask_ith = ...
                                    h  < HMax && ...
                                    s  > SMin; 
                            end

                            if IsSkinMask_ith

                                %Calculate Cb-to-Cr ratio
                                %Type single to permit division to return fractions.
                                CbCrRatio_ith = cb / cr;

                                IsSkinMask_ith = ...
                                    CbCrRatio_ith > CbCrRatioMin && ... 
                                    CbCrRatio_ith < CbCrRatioMax;
                            end

                            IsSkinMask(YAdjust, XAdjust) = IsSkinMask_ith;                        
                        end
                    end
                end
                
            %(3) Condition 3                
            % - Use generic thresholds: generic YCbCr and HS thresholds.
            % - Do not return H and S channel matrices.
            % - Return matrices of the Y, Cb, and Cr channels.                
            else                                          
       
                %M x N matrices; type single.
                YBounded_Single  = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
                CbBounded_Single = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
                CrBounded_Single = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );   

                %Index using a linear index
                if UseLinIdxTF                
                
                    %Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm
                    for i = 1 : NElements_Matrix

                        %Extract and cast to type single the ith r, g, and b values
                        %Scalars; type single.
                        r = single( RBounded_Uint8(i) );
                        g = single( GBounded_Uint8(i) ); 
                        b = single( BBounded_Uint8(i) );       

                        %Apply the RGB-to-YCbCr algorithm
                        %Scalars; type single.
                        %Note: for efficiency, the outputs replace the inputs.
                        %Local function.  
                        %Note: rgb2ycbcr_compute is a custom function located within folder
                        %'FacePulseRate'.                    
                        [y,    ... y
                         cb,   ... cb
                         cr] = ... cr
                            rgb2ycbcr_compute(r, g, b);

                        %Assign the ith y, cb, and cr values
                        YBounded_Single(i)  = y;
                        CbBounded_Single(i) = cb; 
                        CrBounded_Single(i) = cr;    

                        %Classify pixels within all thresholds as skin (true)       
                        IsSkinMask_ith = ...
                            y > YMin  && ...
                            cb > CbMin && ...
                            cb < CbMax && ...  
                            cr > CrMin && ... 
                            cr < CrMax; 

                        if IsSkinMask_ith

                            %Apply rgb-to-hs algorithm
                            %Scalars; type single.
                            %Note: rgb2h is a custom function located within folder 
                            %'FacePulseRate'.  
                            [h, s] = rgb2hs(r, g, b); 

                            %Classify pixels within all thresholds as skin (true) 
                            IsSkinMask_ith = ...
                                h  < HMax && ...
                                s  > SMin; 
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
                    
                   for i = XOffset : XOffset + NCols_Matrix - 1

                        for j = YOffset : YOffset + NRows_Matrix - 1                                     

                            %Indices for output matrices
                            YAdjust = j - YOffsetMin1; 
                            XAdjust = i - XOffsetMin1;
                            
                            %Extract and cast to type single the ith r, g, and b values
                            %Scalars; type single.
                            r = single( RBounded_Uint8(j, i) );
                            g = single( GBounded_Uint8(j, i) ); 
                            b = single( BBounded_Uint8(j, i) );       

                            %Apply the RGB-to-YCbCr algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the outputs replace the inputs.
                            %Local function.  
                            %Note: rgb2ycbcr_compute is a custom function located within folder
                            %'FacePulseRate'.                    
                            [y,    ... y
                             cb,   ... cb
                             cr] = ... cr
                                rgb2ycbcr_compute(r, g, b);

                            %Assign the ith y, cb, and cr values
                            YBounded_Single(YAdjust, XAdjust)  = y;
                            CbBounded_Single(YAdjust, XAdjust) = cb; 
                            CrBounded_Single(YAdjust, XAdjust) = cr;    

                            %Classify pixels within all thresholds as skin (true)       
                            IsSkinMask_ith = ...
                                y  > YMin  && ...
                                cb > CbMin && ...
                                cb < CbMax && ...  
                                cr > CrMin && ... 
                                cr < CrMax; 

                            if IsSkinMask_ith

                                %Apply rgb-to-hs algorithm
                                %Scalars; type single.
                                %Note: rgb2h is a custom function located within folder 
                                %'FacePulseRate'.  
                                [h, s] = rgb2hs(r, g, b); 

                                %Classify pixels within all thresholds as skin (true) 
                                IsSkinMask_ith = ...
                                    h  < HMax && ...
                                    s  > SMin; 
                            end

                            if IsSkinMask_ith

                                %Calculate Cb-to-Cr ratio
                                %Type single to permit division to return fractions.
                                CbCrRatio_ith = cb / cr;

                                IsSkinMask_ith = ...
                                    CbCrRatio_ith > CbCrRatioMin && ... 
                                    CbCrRatio_ith < CbCrRatioMax;
                            end

                            IsSkinMask(YAdjust, XAdjust) = IsSkinMask_ith;                       
                        end
                    end                                        
                end     
            end
            
        %Use tailored thresholds        
        else
            
            %(4) Condition 4              
            % - Use tailored thresholds: tailored YCbCr thresholds and tailored HS thresholds.
            % - Do not return H and S channel matrices.          
            % - Do not return YCbCr matrices.            
            if ~ ReturnCbCrTF && ~ ReturnYTF            

                %M x N matrix; type single.
                YBounded_Single  = coder.const( single([]) );
                CbBounded_Single = coder.const( single([]) );
                CrBounded_Single = coder.const( single([]) );
                
                %Index using a linear index
                if UseLinIdxTF
                    
                    %Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm
                    for i = 1 : NElements_Matrix

                        %Extract and cast to type single the ith r, g, and b values
                        %Scalars; type single.
                        r = single( RBounded_Uint8(i) );
                        g = single( GBounded_Uint8(i) ); 
                        b = single( BBounded_Uint8(i) );                

                        %Apply rgb-to-hs algorithm
                        %Scalars; type single.
                        %Note: rgb2hs is a custom function located within folder
                        %'FacePulseRate'.
                        [out, ... h; named "out" because later reassigned with different value
                         s] = rgb2hs(r, g, b);   

                        %Classify pixels within all thresholds as skin (true) 

                        IsSkinMask_ith = ...
                            out < HMax && ...
                            s   > SMin && ...
                            s   < SMax;

                        if IsSkinMask_ith

                            %Apply the RGB-to-Y algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the output replaces the out variable previously 
                            %assigned.
                            %Note: rgb2y is a custom function located within folder
                            %'FacePulseRate'.     
                            out = ... y
                                rgb2y(r, g, b); 

                            IsSkinMask_ith = ... 
                                out > YMin && ...
                                out < YMax; 

                            if IsSkinMask_ith

                                %Apply the RGB-to-Cb algorithm
                                %Scalars; type single.
                                %Note: rgb2cb is a custom function located within folder
                                %'FacePulseRate'.      
                                cb = rgb2cb(r, g, b);

                                IsSkinMask_ith = ...                    
                                    cb > CbMin && ...
                                    cb < CbMax;

                                if IsSkinMask_ith

                                    %Apply the RGB-to-Cr algorithm
                                    %Scalars; type single.
                                    %Note: rgb2cr is a custom function located within folder
                                    %'FacePulseRate'.                        
                                    cr = rgb2cr(r, g, b);                        

                                    IsSkinMask_ith = ...                        
                                        cr > CrMin && ... 
                                        cr < CrMax;  

                                    if IsSkinMask_ith

                                        %Calculate Cb-to-Cr ratio
                                        %Type single to permit division to return fractions.
                                        %Note: for efficiency, the output replaces the out variable  
                                        %previously assigned.
                                        %Local function. 
                                        out = cb / cr;

                                        IsSkinMask_ith = ...
                                            out > CbCrRatioMin && ... 
                                            out < CbCrRatioMax;                            
                                    end
                                end
                            end 
                        end            

                        IsSkinMask(i) = IsSkinMask_ith;
                    end             
            
                %Index using subscript indices
                else
                    
                    for i = XOffset : XOffset + NCols_Matrix - 1

                        for j = YOffset : YOffset + NRows_Matrix - 1  
                            
                            %Indices for output matrices
                            YAdjust = j - YOffsetMin1; 
                            XAdjust = i - XOffsetMin1;  
                            
                            %Extract and cast to type single the ith r, g, and b values
                            %Scalars; type single.
                            r = single( RBounded_Uint8(j, i) );
                            g = single( GBounded_Uint8(j, i) ); 
                            b = single( BBounded_Uint8(j, i) );                

                            %Apply rgb-to-hs algorithm
                            %Scalars; type single.
                            %Note: rgb2hs is a custom function located within folder
                            %'FacePulseRate'.
                            [out, ... h; named "out" because later reassigned with different value
                             s] = rgb2hs(r, g, b);   

                            %Classify pixels within all thresholds as skin (true) 

                            IsSkinMask_ith = ...
                                out < HMax && ...
                                s   > SMin && ...
                                s   < SMax;

                            if IsSkinMask_ith

                                %Apply the RGB-to-Y algorithm
                                %Scalars; type single.
                                %Note: for efficiency, the output replaces the out variable previously 
                                %assigned.
                                %Note: rgb2y is a custom function located within folder
                                %'FacePulseRate'.     
                                out = ... y
                                    rgb2y(r, g, b); 

                                IsSkinMask_ith = ... 
                                    out > YMin && ...
                                    out < YMax; 

                                if IsSkinMask_ith

                                    %Apply the RGB-to-Cb algorithm
                                    %Scalars; type single.
                                    %Note: rgb2cb is a custom function located within folder
                                    %'FacePulseRate'.      
                                    cb = rgb2cb(r, g, b);

                                    IsSkinMask_ith = ...                    
                                        cb > CbMin && ...
                                        cb < CbMax;

                                    if IsSkinMask_ith

                                        %Apply the RGB-to-Cr algorithm
                                        %Scalars; type single.
                                        %Note: rgb2cr is a custom function located within folder
                                        %'FacePulseRate'.                        
                                        cr = rgb2cr(r, g, b);                        

                                        IsSkinMask_ith = ...                        
                                            cr > CrMin && ... 
                                            cr < CrMax;  

                                        if IsSkinMask_ith

                                            %Calculate Cb-to-Cr ratio
                                            %Type single to permit division to return fractions.
                                            %Note: for efficiency, the output replaces the out variable  
                                            %previously assigned.
                                            %Local function. 
                                            out = cb / cr;

                                            IsSkinMask_ith = ...
                                                out > CbCrRatioMin && ... 
                                                out < CbCrRatioMax;                            
                                        end
                                    end
                                end 
                            end            

                            IsSkinMask(YAdjust, XAdjust) = IsSkinMask_ith;                            
                        end
                    end
                end
                
            %(5) Condition 5  
            % - Use tailored thresholds: tailored YCbCr thresholds and tailored HS thresholds.
            % - Do not return H and S channel matrices.
            % - Return Y-channel matrix but not the Cb and Cr channel matrices.
            elseif ~ ReturnCbCrTF && ReturnYTF                 
                
                %M x N matrix; type single.
                YBounded_Single  = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );

                CbBounded_Single = coder.const( single([]) );
                CrBounded_Single = coder.const( single([]) );

                %Index using a linear index
                if UseLinIdxTF                
                
                    %Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm
                    for i = 1 : NElements_Matrix

                        %Extract and cast to type single the ith r, g, and b values
                        %Scalars; type single.
                        r = single( RBounded_Uint8(i) );
                        g = single( GBounded_Uint8(i) ); 
                        b = single( BBounded_Uint8(i) );                

                        %Apply rgb-to-hs algorithm
                        %Scalars; type single.
                        %Note: rgb2hs is a custom function located within folder
                        %'FacePulseRate'. 
                        [out, ... h; named "out" because later reassigned with different value
                         s] = rgb2hs(r, g, b);   

                        %Classify pixels within all thresholds as skin (true) 

                        IsSkinMask_ith = ...
                            out < HMax && ...
                            s   > SMin && ...
                            s   < SMax;

                        if IsSkinMask_ith

                            %Apply the RGB-to-Y algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the output replaces the out variable previously 
                            %assigned.
                            %Note: rgb2y is a custom function located within folder
                            %'FacePulseRate'.      
                            out = ... y
                                rgb2y(r, g, b); 

                            IsSkinMask_ith = ... 
                                out > YMin && ...
                                out < YMax; 

                            if IsSkinMask_ith

                                %Apply the RGB-to-Cb algorithm
                                %Scalars; type single.
                                %Note: rgb2cb is a custom function located within folder
                                %'FacePulseRate'.    
                                cb = rgb2cb(r, g, b);

                                IsSkinMask_ith = ...                    
                                    cb > CbMin && ...
                                    cb < CbMax;

                                if IsSkinMask_ith

                                    %Apply the RGB-to-Cr algorithm
                                    %Scalars; type single.
                                    %Note: rgb2cr is a custom function located within folder
                                    %'FacePulseRate'.                         
                                    cr = rgb2cr(r, g, b);                        

                                    IsSkinMask_ith = ...                        
                                        cr > CrMin && ... 
                                        cr < CrMax;  

                                    if IsSkinMask_ith

                                        %Calculate Cb-to-Cr ratio
                                        %Type single to permit division to return fractions.
                                        %Note: for efficiency, the output replaces the out variable  
                                        %previously assigned.
                                        %Local function. 
                                        out = cb / cr;

                                        IsSkinMask_ith = ...
                                            out > CbCrRatioMin && ... 
                                            out < CbCrRatioMax;                            
                                    end
                                end
                            end 

                        else

                            %Apply the RGB-to-Y algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the output replaces the out variable previously 
                            %assigned.
                            %Note: rgb2y is a custom function located within folder 'FacePulseRate'.    
                            out = ... y
                                rgb2y(r, g, b);
                        end            

                        %Assign the ith y, cb, and cr values
                        YBounded_Single(i) = out;

                        IsSkinMask(i) = IsSkinMask_ith;
                    end 

                %Index using subscript indices
                else
                                    
                    for i = XOffset : XOffset + NCols_Matrix - 1

                        for j = YOffset : YOffset + NRows_Matrix - 1
                            
                            %Indices for output matrices
                            YAdjust = j - YOffsetMin1; 
                            XAdjust = i - XOffsetMin1;
                            
                            %Extract and cast to type single the ith r, g, and b values
                            %Scalars; type single.
                            r = single( RBounded_Uint8(j, i) );
                            g = single( GBounded_Uint8(j, i) ); 
                            b = single( BBounded_Uint8(j, i) );                

                            %Apply rgb-to-hs algorithm
                            %Scalars; type single.
                            %Note: rgb2hs is a custom function located within folder
                            %'FacePulseRate'. 
                            [out, ... h; named "out" because later reassigned with different value
                             s] = rgb2hs(r, g, b);   

                            %Classify pixels within all thresholds as skin (true) 

                            IsSkinMask_ith = ...
                                out < HMax && ...
                                s   > SMin && ...
                                s   < SMax;

                            if IsSkinMask_ith

                                %Apply the RGB-to-Y algorithm
                                %Scalars; type single.
                                %Note: for efficiency, the output replaces the out variable previously 
                                %assigned.
                                %Note: rgb2y is a custom function located within folder
                                %'FacePulseRate'.      
                                out = ... y
                                    rgb2y(r, g, b); 

                                IsSkinMask_ith = ... 
                                    out > YMin && ...
                                    out < YMax; 

                                if IsSkinMask_ith

                                    %Apply the RGB-to-Cb algorithm
                                    %Scalars; type single.
                                    %Note: rgb2cb is a custom function located within folder
                                    %'FacePulseRate'.    
                                    cb = rgb2cb(r, g, b);

                                    IsSkinMask_ith = ...                    
                                        cb > CbMin && ...
                                        cb < CbMax;

                                    if IsSkinMask_ith

                                        %Apply the RGB-to-Cr algorithm
                                        %Scalars; type single.
                                        %Note: rgb2cr is a custom function located within folder
                                        %'FacePulseRate'.                         
                                        cr = rgb2cr(r, g, b);                        

                                        IsSkinMask_ith = ...                        
                                            cr > CrMin && ... 
                                            cr < CrMax;  

                                        if IsSkinMask_ith

                                            %Calculate Cb-to-Cr ratio
                                            %Type single to permit division to return fractions.
                                            %Note: for efficiency, the output replaces the out variable  
                                            %previously assigned.
                                            %Local function. 
                                            out = cb / cr;

                                            IsSkinMask_ith = ...
                                                out > CbCrRatioMin && ... 
                                                out < CbCrRatioMax;                            
                                        end
                                    end
                                end 

                            else

                                %Apply the RGB-to-Y algorithm
                                %Scalars; type single.
                                %Note: for efficiency, the output replaces the out variable previously 
                                %assigned.
                                %Note: rgb2y is a custom function located within folder 'FacePulseRate'.    
                                out = ... y
                                    rgb2y(r, g, b);
                            end            

                            %Assign the ith y, cb, and cr values
                            YBounded_Single(YAdjust, XAdjust) = out;

                            IsSkinMask(YAdjust, XAdjust) = IsSkinMask_ith;                            
                        end
                    end
                end
                
            %(6) Condition 6
            % - Use tailored thresholds: tailored YCbCr thresholds and tailored HS thresholds.
            % - Do not return H and S channel matrices.
            % - Return matrices of the Y, Cb, and Cr channels.        
            else

                %M x N matrices; type single.
                YBounded_Single  = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
                CbBounded_Single = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
                CrBounded_Single = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );

                %Index using a linear index
                if UseLinIdxTF                
                
                    %Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm
                    for i = 1 : NElements_Matrix

                        %Extract and cast to type single the ith r, g, and b values
                        %Scalars; type single.
                        c1 = single( RBounded_Uint8(i) );
                        c2 = single( GBounded_Uint8(i) ); 
                        c3 = single( BBounded_Uint8(i) );         

                        %Apply rgb-to-hs algorithm
                        %Scalars; type single.
                        %Note: rgb2hs is a custom function located within folder 'FacePulseRate'. 
                        [out, ... h; named "out" because later reassigned with different value
                         s] = rgb2hs(c1, c2, c3);            

                        IsSkinMask_ith = ...
                            out < HMax && ...
                            s   > SMin && ...
                            s   < SMax;

                        %Apply the RGB-to-YCbCr algorithm
                        %Scalars; type single.
                        %Note: for efficiency, the outputs replace the inputs.
                        %Note: rgb2ycbcr_compute is a custom function located within folder 
                        %'FacePulseRate'.      
                        [c1,   ... y
                         c2,   ... cb
                         c3] = ... cr
                            rgb2ycbcr_compute(c1, c2, c3);

                        %Assign the ith y, cb, and cr values
                        YBounded_Single(i)  = c1; 
                        CbBounded_Single(i) = c2;
                        CrBounded_Single(i) = c3;

                        %Classify pixels within all thresholds as skin (true)       
                        if IsSkinMask_ith

                            IsSkinMask_ith = ...
                                c1 > YMin  && ...
                                c1 < YMax  && ...
                                c2 > CbMin && ...
                                c2 < CbMax && ...  
                                c3 > CrMin && ... 
                                c3 < CrMax; 
                        end

                        if IsSkinMask_ith

                            %Calculate Cb-to-Cr ratio
                            %Type single to permit division to return fractions.
                            %Note: for efficiency, the output is assigned to a previously assigned 
                            %variable.
                            out = c2 / c3;

                            IsSkinMask_ith = ...
                                out > CbCrRatioMin && ... 
                                out < CbCrRatioMax;
                        end

                        IsSkinMask(i) = IsSkinMask_ith;
                    end                    
            
                %Index using subscript indices
                else
                    
                    for i = XOffset : XOffset + NCols_Matrix - 1

                        for j = YOffset : YOffset + NRows_Matrix - 1
                            
                            %Indices for output matrices
                            YAdjust = j - YOffsetMin1; 
                            XAdjust = i - XOffsetMin1;   
                            
                            %Extract and cast to type single the ith r, g, and b values
                            %Scalars; type single.
                            c1 = single( RBounded_Uint8(j, i) );
                            c2 = single( GBounded_Uint8(j, i) ); 
                            c3 = single( BBounded_Uint8(j, i) );         

                            %Apply rgb-to-hs algorithm
                            %Scalars; type single.
                            %Note: rgb2hs is a custom function located within folder 'FacePulseRate'. 
                            [out, ... h; named "out" because later reassigned with different value
                             s] = rgb2hs(c1, c2, c3);            

                            IsSkinMask_ith = ...
                                out < HMax && ...
                                s   > SMin && ...
                                s   < SMax;

                            %Apply the RGB-to-YCbCr algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the outputs replace the inputs.
                            %Note: rgb2ycbcr_compute is a custom function located within folder 
                            %'FacePulseRate'.      
                            [c1,   ... y
                             c2,   ... cb
                             c3] = ... cr
                                rgb2ycbcr_compute(c1, c2, c3);

                            %Assign the ith y, cb, and cr values
                            YBounded_Single(YAdjust, XAdjust)  = c1; 
                            CbBounded_Single(YAdjust, XAdjust) = c2;
                            CrBounded_Single(YAdjust, XAdjust) = c3;

                            %Classify pixels within all thresholds as skin (true)       
                            if IsSkinMask_ith

                                IsSkinMask_ith = ...
                                    c1 > YMin  && ...
                                    c1 < YMax  && ...
                                    c2 > CbMin && ...
                                    c2 < CbMax && ...  
                                    c3 > CrMin && ... 
                                    c3 < CrMax; 
                            end

                            if IsSkinMask_ith

                                %Calculate Cb-to-Cr ratio
                                %Type single to permit division to return fractions.
                                %Note: for efficiency, the output is assigned to a previously assigned 
                                %variable.
                                out = c2 / c3;

                                IsSkinMask_ith = ...
                                    out > CbCrRatioMin && ... 
                                    out < CbCrRatioMax;
                            end

                            IsSkinMask(YAdjust, XAdjust) = IsSkinMask_ith;                            
                        end
                    end
                end
            end                        
        end

        
    %%%%%% >>>>>> Return the H- and S-channel matrices from the HSV colorspace %%%%%%  
    else

        %Preallocate H- and S-channel outputs
        %M x N matrix; type single.
        HBounded_Single = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
        SBounded_Single = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
        
        %Do not use tailored thresholds
        if ~ TailoredThresholdsTF || ...
           DontUseTailoredTF
       
            %(7) Condition 7       
            % - Use generic thresholds: generic YCbCr and HS thresholds.
            % - Return H and S channel matrices.
            % - Do not return matrices of the Y, Cb, or Cr channels.       
            if ~ ReturnCbCrTF && ~ ReturnYTF           
 
                %M x N matrices; type single.
                YBounded_Single  = coder.const( single([]) );
                CbBounded_Single = coder.const( single([]) );
                CrBounded_Single = coder.const( single([]) );   

                %Index using a linear index
                if UseLinIdxTF                
                
                    %Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm
                    for i = 1 : NElements_Matrix

                        %Extract and cast to type single the ith r, g, and b values
                        %Scalars; type single.
                        c1 = single( RBounded_Uint8(i) );
                        c2 = single( GBounded_Uint8(i) ); 
                        c3 = single( BBounded_Uint8(i) );

                        %Apply rgb-to-hs algorithm
                        %Scalars; type single.
                        %Note: rgb2hs is a custom function located within folder 'FacePulseRate'.  
                        [out, ... h; named "out" because later reassigned with different value
                         s] = rgb2hs(c1, c2, c3);  

                        %Assign the ith h and s values to the H- and S-channel matrices
                        HBounded_Single(i) = out;    
                        SBounded_Single(i) = s;

                        %Apply the RGB-to-YCbCr algorithm
                        %Scalars; type single.
                        %Note: for efficiency, the outputs replace the inputs.
                        %Note: rgb2ycbcr_compute is a custom function located within folder 
                        %'FacePulseRate'.       
                        [c1,   ... y
                         c2,   ... cb
                         c3] = ... cr
                            rgb2ycbcr_compute(c1, c2, c3);        

                        %Classify pixels within all thresholds as skin (true)       
                        IsSkinMask_ith = ...
                            c1 > YMin  && ...
                            c2 > CbMin && ...
                            c2 < CbMax && ...  
                            c3 > CrMin && ... 
                            c3 < CrMax; 

                        if IsSkinMask_ith

                            %Classify pixels within all thresholds as skin (true) 
                            IsSkinMask_ith = ...
                                out < HMax && ...
                                s   > SMin; 
                        end

                        if IsSkinMask_ith

                            %Calculate Cb-to-Cr ratio
                            %Type single to permit division to return fractions.
                            %Note: for efficiency, the output is assigned to a previously assigned 
                            %variable.
                            out = c2 / c3;

                            IsSkinMask_ith = ...
                                out > CbCrRatioMin && ... 
                                out < CbCrRatioMax;
                        end

                        IsSkinMask(i) = IsSkinMask_ith;
                    end 

                %Index using subscript indices
                else
                                    
                    for i = XOffset : XOffset + NCols_Matrix - 1

                        for j = YOffset : YOffset + NRows_Matrix - 1 
                            
                            %Indices for output matrices
                            YAdjust = j - YOffsetMin1; 
                            XAdjust = i - XOffsetMin1; 
                            
                            %Extract and cast to type single the ith r, g, and b values
                            %Scalars; type single.
                            c1 = single( RBounded_Uint8(j, i) );
                            c2 = single( GBounded_Uint8(j, i) ); 
                            c3 = single( BBounded_Uint8(j, i) );

                            %Apply rgb-to-hs algorithm
                            %Scalars; type single.
                            %Note: rgb2hs is a custom function located within folder 'FacePulseRate'.  
                            [out, ... h; named "out" because later reassigned with different value
                             s] = rgb2hs(c1, c2, c3);  

                            %Assign the ith h and s values to the H- and S-channel matrices
                            HBounded_Single(YAdjust, XAdjust) = out;    
                            SBounded_Single(YAdjust, XAdjust) = s;

                            %Apply the RGB-to-YCbCr algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the outputs replace the inputs.
                            %Note: rgb2ycbcr_compute is a custom function located within folder 
                            %'FacePulseRate'.       
                            [c1,   ... y
                             c2,   ... cb
                             c3] = ... cr
                                rgb2ycbcr_compute(c1, c2, c3);        

                            %Classify pixels within all thresholds as skin (true)       
                            IsSkinMask_ith = ...
                                c1 > YMin  && ...
                                c2 > CbMin && ...
                                c2 < CbMax && ...  
                                c3 > CrMin && ... 
                                c3 < CrMax; 

                            if IsSkinMask_ith

                                %Classify pixels within all thresholds as skin (true) 
                                IsSkinMask_ith = ...
                                    out < HMax && ...
                                    s   > SMin; 
                            end

                            if IsSkinMask_ith

                                %Calculate Cb-to-Cr ratio
                                %Type single to permit division to return fractions.
                                %Note: for efficiency, the output is assigned to a previously assigned 
                                %variable.
                                out = c2 / c3;

                                IsSkinMask_ith = ...
                                    out > CbCrRatioMin && ... 
                                    out < CbCrRatioMax;
                            end

                            IsSkinMask(YAdjust, XAdjust) = IsSkinMask_ith;                           
                        end
                    end
                end
                
            %(8) Condition 8                 
            % - Use generic thresholds: generic YCbCr and HS thresholds.
            % - Return H and S channel matrices.
            % - Return Y-channel matrix but not the Cb and Cr channel matrices.       
            elseif ~ ReturnCbCrTF && ReturnYTF    

                %M x N matrices; type single.
                YBounded_Single  = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
                CbBounded_Single = coder.const( single([]) );
                CrBounded_Single = coder.const( single([]) );   

                %Index using a linear index
                if UseLinIdxTF                
                
                    %Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm
                    for i = 1 : NElements_Matrix

                        %Extract and cast to type single the ith r, g, and b values
                        %Scalars; type single.
                        c1 = single( RBounded_Uint8(i) );
                        c2 = single( GBounded_Uint8(i) ); 
                        c3 = single( BBounded_Uint8(i) );

                        %Apply rgb-to-hs algorithm
                        %Scalars; type single.
                        %Note: rgb2h is a custom function located within folder 'FacePulseRate'.  
                        [out, ... h; named "out" because later reassigned with different value
                         s] = rgb2hs(c1, c2, c3);  

                        %Assign the ith h and s values to the H- and S-channel matrices
                        HBounded_Single(i) = out;    
                        SBounded_Single(i) = s;

                        %Apply the RGB-to-YCbCr algorithm
                        %Scalars; type single.
                        %Note: for efficiency, the outputs replace the inputs.
                        %Note: rgb2ycbcr_compute is a custom function located within folder 
                        %'FacePulseRate'.       
                        [c1,   ... y
                         c2,   ... cb
                         c3] = ... cr
                            rgb2ycbcr_compute(c1, c2, c3);        

                        %Assign the ith y value
                        YBounded_Single(i)  = c1;

                        %Classify pixels within all thresholds as skin (true)       
                        IsSkinMask_ith = ...
                            c1 > YMin  && ...
                            c2 > CbMin && ...
                            c2 < CbMax && ...  
                            c3 > CrMin && ... 
                            c3 < CrMax; 

                        if IsSkinMask_ith

                            %Classify pixels within all thresholds as skin (true) 
                            IsSkinMask_ith = ...
                                out < HMax && ...
                                s   > SMin; 
                        end

                        if IsSkinMask_ith

                            %Calculate Cb-to-Cr ratio
                            %Type single to permit division to return fractions.
                            %Note: for efficiency, the output is assigned to a previously assigned 
                            %variable.
                            out = c2 / c3;

                            IsSkinMask_ith = ...
                                out > CbCrRatioMin && ... 
                                out < CbCrRatioMax;
                        end

                        IsSkinMask(i) = IsSkinMask_ith;
                    end  

                %Index using subscript indices
                else
                                    
                    for i = XOffset : XOffset + NCols_Matrix - 1

                        for j = YOffset : YOffset + NRows_Matrix - 1 
                            
                            %Indices for output matrices
                            YAdjust = j - YOffsetMin1; 
                            XAdjust = i - XOffsetMin1;   
                            
                            %Extract and cast to type single the ith r, g, and b values
                            %Scalars; type single.
                            c1 = single( RBounded_Uint8(j, i) );
                            c2 = single( GBounded_Uint8(j, i) ); 
                            c3 = single( BBounded_Uint8(j, i) );

                            %Apply rgb-to-hs algorithm
                            %Scalars; type single.
                            %Note: rgb2h is a custom function located within folder 'FacePulseRate'.  
                            [out, ... h; named "out" because later reassigned with different value
                             s] = rgb2hs(c1, c2, c3);  

                            %Assign the ith h and s values to the H- and S-channel matrices
                            HBounded_Single(YAdjust, XAdjust) = out;    
                            SBounded_Single(YAdjust, XAdjust) = s;

                            %Apply the RGB-to-YCbCr algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the outputs replace the inputs.
                            %Note: rgb2ycbcr_compute is a custom function located within folder 
                            %'FacePulseRate'.       
                            [c1,   ... y
                             c2,   ... cb
                             c3] = ... cr
                                rgb2ycbcr_compute(c1, c2, c3);        

                            %Assign the ith y value
                            YBounded_Single(YAdjust, XAdjust)  = c1;

                            %Classify pixels within all thresholds as skin (true)       
                            IsSkinMask_ith = ...
                                c1 > YMin  && ...
                                c2 > CbMin && ...
                                c2 < CbMax && ...  
                                c3 > CrMin && ... 
                                c3 < CrMax; 

                            if IsSkinMask_ith

                                %Classify pixels within all thresholds as skin (true) 
                                IsSkinMask_ith = ...
                                    out < HMax && ...
                                    s   > SMin; 
                            end

                            if IsSkinMask_ith

                                %Calculate Cb-to-Cr ratio
                                %Type single to permit division to return fractions.
                                %Note: for efficiency, the output is assigned to a previously assigned 
                                %variable.
                                out = c2 / c3;

                                IsSkinMask_ith = ...
                                    out > CbCrRatioMin && ... 
                                    out < CbCrRatioMax;
                            end

                            IsSkinMask(YAdjust, XAdjust) = IsSkinMask_ith;                            
                        end
                    end
                end
                
            %(9) Condition 9                 
            % - Use generic thresholds: generic YCbCr and HS thresholds.
            % - Return H and S channel matrices.
            % - Return the YCbCr matrices.       
            else     
                
                %M x N matrices; type single.
                YBounded_Single  = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
                CbBounded_Single = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
                CrBounded_Single = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );   

                %Index using a linear index
                if UseLinIdxTF                
                
                    %Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm
                    for i = 1 : NElements_Matrix

                        %Extract and cast to type single the ith r, g, and b values
                        %Scalars; type single.
                        c1 = single( RBounded_Uint8(i) );
                        c2 = single( GBounded_Uint8(i) ); 
                        c3 = single( BBounded_Uint8(i) );

                        %Apply rgb-to-hs algorithm
                        %Scalars; type single.
                        %Note: rgb2hse is a custom function located within folder 'FacePulseRate'. 
                        [out, ... h; named "out" because later reassigned with different value
                         s] = rgb2hs(c1, c2, c3);  

                        %Assign the ith h and s values to the H- and S-channel matrices
                        HBounded_Single(i) = out;    
                        SBounded_Single(i) = s;

                        %Apply the RGB-to-YCbCr algorithm
                        %Scalars; type single.
                        %Note: for efficiency, the outputs replace the inputs.
                        %Note: rgb2ycbcr_compute is a custom function located within folder 
                        %'FacePulseRate'.       
                        [c1,   ... y
                         c2,   ... cb
                         c3] = ... cr
                            rgb2ycbcr_compute(c1, c2, c3);        

                        %Assign the ith y, cb, and cr values
                        YBounded_Single(i)  = c1;
                        CbBounded_Single(i) = c2; 
                        CrBounded_Single(i) = c3;    

                        %Classify pixels within all thresholds as skin (true)       
                        IsSkinMask_ith = ...
                            c1 > YMin  && ...
                            c2 > CbMin && ...
                            c2 < CbMax && ...  
                            c3 > CrMin && ... 
                            c3 < CrMax; 

                        if IsSkinMask_ith

                            %Classify pixels within all thresholds as skin (true) 
                            IsSkinMask_ith = ...
                                out < HMax && ...
                                s   > SMin; 
                        end

                        if IsSkinMask_ith

                            %Calculate Cb-to-Cr ratio
                            %Type single to permit division to return fractions.
                            %Note: for efficiency, the output is assigned to a previously assigned 
                            %variable.
                            out = c2 / c3;

                            IsSkinMask_ith = ...
                                out > CbCrRatioMin && ... 
                                out < CbCrRatioMax;
                        end

                        IsSkinMask(i) = IsSkinMask_ith;
                    end                    
        
                %Index using subscript indices
                else
                    
                    for i = XOffset : XOffset + NCols_Matrix - 1

                        for j = YOffset : YOffset + NRows_Matrix - 1 
                            
                            %Indices for output matrices
                            YAdjust = j - YOffsetMin1; 
                            XAdjust = i - XOffsetMin1;     
                            
                            %Extract and cast to type single the ith r, g, and b values
                            %Scalars; type single.
                            c1 = single( RBounded_Uint8(j, i) );
                            c2 = single( GBounded_Uint8(j, i) ); 
                            c3 = single( BBounded_Uint8(j, i) );

                            %Apply rgb-to-hs algorithm
                            %Scalars; type single.
                            %Note: rgb2hse is a custom function located within folder 'FacePulseRate'. 
                            [out, ... h; named "out" because later reassigned with different value
                             s] = rgb2hs(c1, c2, c3);  

                            %Assign the ith h and s values to the H- and S-channel matrices
                            HBounded_Single(YAdjust, XAdjust) = out;    
                            SBounded_Single(YAdjust, XAdjust) = s;

                            %Apply the RGB-to-YCbCr algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the outputs replace the inputs.
                            %Note: rgb2ycbcr_compute is a custom function located within folder 
                            %'FacePulseRate'.       
                            [c1,   ... y
                             c2,   ... cb
                             c3] = ... cr
                                rgb2ycbcr_compute(c1, c2, c3);        

                            %Assign the ith y, cb, and cr values
                            YBounded_Single(YAdjust, XAdjust)  = c1;
                            CbBounded_Single(YAdjust, XAdjust) = c2; 
                            CrBounded_Single(YAdjust, XAdjust) = c3;    

                            %Classify pixels within all thresholds as skin (true)       
                            IsSkinMask_ith = ...
                                c1 > YMin  && ...
                                c2 > CbMin && ...
                                c2 < CbMax && ...  
                                c3 > CrMin && ... 
                                c3 < CrMax; 

                            if IsSkinMask_ith

                                %Classify pixels within all thresholds as skin (true) 
                                IsSkinMask_ith = ...
                                    out < HMax && ...
                                    s   > SMin; 
                            end

                            if IsSkinMask_ith

                                %Calculate Cb-to-Cr ratio
                                %Type single to permit division to return fractions.
                                %Note: for efficiency, the output is assigned to a previously assigned 
                                %variable.
                                out = c2 / c3;

                                IsSkinMask_ith = ...
                                    out > CbCrRatioMin && ... 
                                    out < CbCrRatioMax;
                            end

                            IsSkinMask(YAdjust, XAdjust) = IsSkinMask_ith;                            
                        end
                    end
                end                    
            end                    
                
        %Use tailored thresholds        
        else
            
            %(10) Condition 10 
            % - Use tailored thresholds: tailored YCbCr thresholds and tailored HS thresholds.
            % - Return matrices of the H and S channels.
            % - Do not return YCbCr matrices.            
            if ~ ReturnCbCrTF && ~ ReturnYTF                

                %M x N matrix; type single.
                YBounded_Single  = coder.const( single([]) );
                CbBounded_Single = coder.const( single([]) );
                CrBounded_Single = coder.const( single([]) );

                %Index using a linear index
                if UseLinIdxTF                
                
                    %Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm
                    for i = 1 : NElements_Matrix

                        %Extract and cast to type single the ith r, g, and b values
                        %Scalars; type single.
                        c1 = single( RBounded_Uint8(i) );
                        c2 = single( GBounded_Uint8(i) ); 
                        c3 = single( BBounded_Uint8(i) );           

                        %Apply rgb-to-h algorithm
                        %Scalars; type single.
                        %Note: rgb2hs is a custom function located within folder 'FacePulseRate'. 
                        [out, ... h; named "out" because later reassigned with different value
                         s] = rgb2hs(c1, c2, c3);            

                        %Assign the ith h and s values to the H- and S-channel matrices
                        HBounded_Single(i) = out;
                        SBounded_Single(i) = s;

                        IsSkinMask_ith = ...
                            out < HMax && ...
                            s   > SMin && ...
                            s   < SMax;                     

                        %Apply the RGB-to-YCbCr algorithm
                        %Scalars; type single.
                        %Note: for efficiency, the outputs replace the inputs.
                        %Note: rgb2ycbcr_compute is a custom function located within folder 
                        %'FacePulseRate'.   
                        [c1,   ... y
                         c2,   ... cb
                         c3] = ... cr
                            rgb2ycbcr_compute(c1, c2, c3);                     

                        %Classify pixels within all thresholds as skin (true)       

                        if IsSkinMask_ith

                            IsSkinMask_ith = ...
                                c1 > YMin  && ...
                                c1 < YMax  && ...
                                c2 > CbMin && ...
                                c2 < CbMax && ...  
                                c3 > CrMin && ... 
                                c3 < CrMax; 
                        end

                        if IsSkinMask_ith

                            %Calculate Cb-to-Cr ratio
                            %Type single to permit division to return fractions.
                            %Note: for efficiency, the output is assigned to a previously assigned 
                            %variable.
                            out = c2 / c3;

                            IsSkinMask_ith = ...
                                out > CbCrRatioMin && ... 
                                out < CbCrRatioMax;
                        end

                        IsSkinMask(i) = IsSkinMask_ith;  
                    end  
                
                %Index using subscript indices
                else

                    for i = XOffset : XOffset + NCols_Matrix - 1

                        for j = YOffset : YOffset + NRows_Matrix - 1 
                            
                            %Indices for output matrices
                            YAdjust = j - YOffsetMin1; 
                            XAdjust = i - XOffsetMin1;    
                            
                            %Extract and cast to type single the ith r, g, and b values
                            %Scalars; type single.
                            c1 = single( RBounded_Uint8(j, i) );
                            c2 = single( GBounded_Uint8(j, i) ); 
                            c3 = single( BBounded_Uint8(j, i) );           

                            %Apply rgb-to-h algorithm
                            %Scalars; type single.
                            %Note: rgb2hs is a custom function located within folder 'FacePulseRate'. 
                            [out, ... h; named "out" because later reassigned with different value
                             s] = rgb2hs(c1, c2, c3);            

                            %Assign the ith h and s values to the H- and S-channel matrices
                            HBounded_Single(YAdjust, XAdjust) = out;
                            SBounded_Single(YAdjust, XAdjust) = s;

                            IsSkinMask_ith = ...
                                out < HMax && ...
                                s   > SMin && ...
                                s   < SMax;                     

                            %Apply the RGB-to-YCbCr algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the outputs replace the inputs.
                            %Note: rgb2ycbcr_compute is a custom function located within folder 
                            %'FacePulseRate'.   
                            [c1,   ... y
                             c2,   ... cb
                             c3] = ... cr
                                rgb2ycbcr_compute(c1, c2, c3);                     

                            %Classify pixels within all thresholds as skin (true)       

                            if IsSkinMask_ith

                                IsSkinMask_ith = ...
                                    c1 > YMin  && ...
                                    c1 < YMax  && ...
                                    c2 > CbMin && ...
                                    c2 < CbMax && ...  
                                    c3 > CrMin && ... 
                                    c3 < CrMax; 
                            end

                            if IsSkinMask_ith

                                %Calculate Cb-to-Cr ratio
                                %Type single to permit division to return fractions.
                                %Note: for efficiency, the output is assigned to a previously assigned 
                                %variable.
                                out = c2 / c3;

                                IsSkinMask_ith = ...
                                    out > CbCrRatioMin && ... 
                                    out < CbCrRatioMax;
                            end

                            IsSkinMask(YAdjust, XAdjust) = IsSkinMask_ith;                              
                        end
                    end
                end
                
            %(11) Condition 11 
            % - Use tailored thresholds: tailored YCbCr thresholds and tailored HS thresholds.
            % - Return matrices of the H and S channels.
            % - Return Y-channel matrix but not the Cb and Cr channel matrices.        
            elseif ~ ReturnCbCrTF && ReturnYTF

                %M x N matrix; type single.
                YBounded_Single  = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
                CbBounded_Single = coder.const( single([]) );
                CrBounded_Single = coder.const( single([]) );

                %Index using a linear index
                if UseLinIdxTF                
                
                    %Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm
                    for i = 1 : NElements_Matrix

                        %Extract and cast to type single the ith r, g, and b values
                        %Scalars; type single.
                        c1 = single( RBounded_Uint8(i) );
                        c2 = single( GBounded_Uint8(i) ); 
                        c3 = single( BBounded_Uint8(i) );           

                        %Apply rgb-to-h algorithm
                        %Scalars; type single.
                        %Note: rgb2hse is a custom function located within folder 'FacePulseRate'. 
                        [out, ... h; named "out" because later reassigned with different value
                         s] = rgb2hs(c1, c2, c3);            

                        %Assign the ith h and s values to the H- and S-channel matrices
                        HBounded_Single(i) = out;
                        SBounded_Single(i) = s;

                        IsSkinMask_ith = ...
                            out < HMax && ...
                            s   > SMin && ...
                            s   < SMax;                     

                        %Apply the RGB-to-YCbCr algorithm
                        %Scalars; type single.
                        %Note: for efficiency, the outputs replace the inputs.
                        %Note: rgb2ycbcr_compute is a custom function located within folder 
                        %'FacePulseRate'.       
                        [c1,   ... y
                         c2,   ... cb
                         c3] = ... cr
                            rgb2ycbcr_compute(c1, c2, c3);

                        %Assign the ith y, cb, and cr values
                        YBounded_Single(i) = c1;                               

                        %Classify pixels within all thresholds as skin (true)       

                        if IsSkinMask_ith

                            IsSkinMask_ith = ...
                                c1 > YMin  && ...
                                c1 < YMax  && ...
                                c2 > CbMin && ...
                                c2 < CbMax && ...  
                                c3 > CrMin && ... 
                                c3 < CrMax; 
                        end

                        if IsSkinMask_ith

                            %Calculate Cb-to-Cr ratio
                            %Type single to permit division to return fractions.
                            %Note: for efficiency, the output is assigned to a previously assigned 
                            %variable.
                            out = c2 / c3;

                            IsSkinMask_ith = ...
                                out > CbCrRatioMin && ... 
                                out < CbCrRatioMax;
                        end

                        IsSkinMask(i) = IsSkinMask_ith;  
                    end 

                %Index using subscript indices
                else

                    for i = XOffset : XOffset + NCols_Matrix - 1

                        for j = YOffset : YOffset + NRows_Matrix - 1 
                            
                            %Indices for output matrices
                            YAdjust = j - YOffsetMin1; 
                            XAdjust = i - XOffsetMin1; 
                            
                            %Extract and cast to type single the ith r, g, and b values
                            %Scalars; type single.
                            c1 = single( RBounded_Uint8(j, i) );
                            c2 = single( GBounded_Uint8(j, i) ); 
                            c3 = single( BBounded_Uint8(j, i) );           

                            %Apply rgb-to-h algorithm
                            %Scalars; type single.
                            %Note: rgb2hse is a custom function located within folder 'FacePulseRate'. 
                            [out, ... h; named "out" because later reassigned with different value
                             s] = rgb2hs(c1, c2, c3);            

                            %Assign the ith h and s values to the H- and S-channel matrices
                            HBounded_Single(YAdjust, XAdjust) = out;
                            SBounded_Single(YAdjust, XAdjust) = s;

                            IsSkinMask_ith = ...
                                out < HMax && ...
                                s   > SMin && ...
                                s   < SMax;                     

                            %Apply the RGB-to-YCbCr algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the outputs replace the inputs.
                            %Note: rgb2ycbcr_compute is a custom function located within folder 
                            %'FacePulseRate'.       
                            [c1,   ... y
                             c2,   ... cb
                             c3] = ... cr
                                rgb2ycbcr_compute(c1, c2, c3);

                            %Assign the ith y, cb, and cr values
                            YBounded_Single(YAdjust, XAdjust) = c1;                               

                            %Classify pixels within all thresholds as skin (true)       

                            if IsSkinMask_ith

                                IsSkinMask_ith = ...
                                    c1 > YMin  && ...
                                    c1 < YMax  && ...
                                    c2 > CbMin && ...
                                    c2 < CbMax && ...  
                                    c3 > CrMin && ... 
                                    c3 < CrMax; 
                            end

                            if IsSkinMask_ith

                                %Calculate Cb-to-Cr ratio
                                %Type single to permit division to return fractions.
                                %Note: for efficiency, the output is assigned to a previously assigned 
                                %variable.
                                out = c2 / c3;

                                IsSkinMask_ith = ...
                                    out > CbCrRatioMin && ... 
                                    out < CbCrRatioMax;
                            end

                            IsSkinMask(YAdjust, XAdjust) = IsSkinMask_ith;                             
                        end
                    end
                end
                
            %(12) Condition 12 
            % - Use tailored thresholds: tailored YCbCr thresholds and tailored HS thresholds.
            % - Return matrices of the H and S channels.
            % - Return matrices of the Y, Cb, and Cr channels.       
            else

                %M x N matrices; type single.
                YBounded_Single  = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
                CbBounded_Single = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );
                CrBounded_Single = coder.nullcopy( zeros(NRows_Matrix, NCols_Matrix, 'single') );

                %Index using a linear index
                if UseLinIdxTF                
                
                    %Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm
                    for i = 1 : NElements_Matrix

                        %Extract and cast to type single the ith r, g, and b values
                        %Scalars; type single.
                        c1 = single( RBounded_Uint8(i) );
                        c2 = single( GBounded_Uint8(i) ); 
                        c3 = single( BBounded_Uint8(i) );            

                        %Apply rgb-to-hs algorithm
                        %Scalars; type single.
                        %Note: rgb2hs is a custom function located within folder 'FacePulseRate'. 
                        [out, ... h; named "out" because later reassigned with different value
                         s] = rgb2hs(c1, c2, c3);            

                        %Assign the ith h and s values to the H- and S-channel matrices
                        HBounded_Single(i) = out;
                        SBounded_Single(i) = s;

                        IsSkinMask_ith = ...
                            out < HMax && ...
                            s   > SMin && ...
                            s   < SMax;

                        %Apply the RGB-to-YCbCr algorithm
                        %Scalars; type single.
                        %Note: for efficiency, the outputs replace the inputs.
                        %Note: rgb2ycbcr_compute is a custom function located within folder 
                        %'FacePulseRate'.      
                        [c1,   ... y
                         c2,   ... cb
                         c3] = ... cr
                            rgb2ycbcr_compute(c1, c2, c3);

                        %Assign the ith y, cb, and cr values
                        YBounded_Single(i)  = c1; 
                        CbBounded_Single(i) = c2;
                        CrBounded_Single(i) = c3;

                        %Classify pixels within all thresholds as skin (true)       

                        if IsSkinMask_ith

                            IsSkinMask_ith = ...
                                c1 > YMin && ...
                                c1 < YMax && ...
                                c2 > CbMin && ...
                                c2 < CbMax && ...  
                                c3 > CrMin && ... 
                                c3 < CrMax; 
                        end

                        if IsSkinMask_ith

                            %Calculate Cb-to-Cr ratio
                            %Type single to permit division to return fractions.
                            %Note: for efficiency, the output is assigned to a previously assigned 
                            %variable.
                            out = c2 / c3;

                            IsSkinMask_ith = ...
                                out > CbCrRatioMin && ... 
                                out < CbCrRatioMax;
                        end

                        IsSkinMask(i) = IsSkinMask_ith;
                    end 
                
                %Index using subscript indices
                else 
                    
                    for i = XOffset : XOffset + NCols_Matrix - 1

                        for j = YOffset : YOffset + NRows_Matrix - 1
                            
                            %Indices for output matrices
                            YAdjust = j - YOffsetMin1; 
                            XAdjust = i - XOffsetMin1; 
                            
                            %Extract and cast to type single the ith r, g, and b values
                            %Scalars; type single.
                            c1 = single( RBounded_Uint8(j, i) );
                            c2 = single( GBounded_Uint8(j, i) ); 
                            c3 = single( BBounded_Uint8(j, i) );            

                            %Apply rgb-to-hs algorithm
                            %Scalars; type single.
                            %Note: rgb2hs is a custom function located within folder 'FacePulseRate'. 
                            [out, ... h; named "out" because later reassigned with different value
                             s] = rgb2hs(c1, c2, c3);            

                            %Assign the ith h and s values to the H- and S-channel matrices
                            HBounded_Single(YAdjust, XAdjust) = out;
                            SBounded_Single(YAdjust, XAdjust) = s;

                            IsSkinMask_ith = ...
                                out < HMax && ...
                                s   > SMin && ...
                                s   < SMax;

                            %Apply the RGB-to-YCbCr algorithm
                            %Scalars; type single.
                            %Note: for efficiency, the outputs replace the inputs.
                            %Note: rgb2ycbcr_compute is a custom function located within folder 
                            %'FacePulseRate'.      
                            [c1,   ... y
                             c2,   ... cb
                             c3] = ... cr
                                rgb2ycbcr_compute(c1, c2, c3);

                            %Assign the ith y, cb, and cr values
                            YBounded_Single(YAdjust, XAdjust)  = c1; 
                            CbBounded_Single(YAdjust, XAdjust) = c2;
                            CrBounded_Single(YAdjust, XAdjust) = c3;

                            %Classify pixels within all thresholds as skin (true)       

                            if IsSkinMask_ith

                                IsSkinMask_ith = ...
                                    c1 > YMin && ...
                                    c1 < YMax && ...
                                    c2 > CbMin && ...
                                    c2 < CbMax && ...  
                                    c3 > CrMin && ... 
                                    c3 < CrMax; 
                            end

                            if IsSkinMask_ith

                                %Calculate Cb-to-Cr ratio
                                %Type single to permit division to return fractions.
                                %Note: for efficiency, the output is assigned to a previously assigned 
                                %variable.
                                out = c2 / c3;

                                IsSkinMask_ith = ...
                                    out > CbCrRatioMin && ... 
                                    out < CbCrRatioMax;
                            end

                            IsSkinMask(YAdjust, XAdjust) = IsSkinMask_ith;                            
                        end
                    end
                end                
            end
        end
    end


%%%%%%% --- Non-compiled version of function %%%%%%

%Use vectorized operations, which are more efficient for Matlab code.

else %running in Matlab code

    %Index using subscript indices
    if ~ UseLinIdxTF 
      
        %Crop according to specified offsets, width, and height:
        
        RBounded_Uint8 = ...
            RBounded_Uint8( ...
                YOffset : YOffset + NRows_Matrix - 1, ...
                XOffset : XOffset + NCols_Matrix - 1 ...
            );

        GBounded_Uint8 = ...
            GBounded_Uint8( ...
                YOffset : YOffset + NRows_Matrix - 1, ...
                XOffset : XOffset + NCols_Matrix - 1 ...
            );   

        BBounded_Uint8 = ...
            BBounded_Uint8( ...
                YOffset : YOffset + NRows_Matrix - 1, ...
                XOffset : XOffset + NCols_Matrix - 1 ...
            );                           
    end  
    
    %Convert to floating-point type
    RBounded_Single = single(RBounded_Uint8);
    GBounded_Single = single(GBounded_Uint8);
    BBounded_Single = single(BBounded_Uint8);    
    
    %%%%%% >>>>>> YCbCr thresholds %%%%%%
    
    %RGB to YCbCr conversion:
    
    %Y-channel page
    %M x N matrix; type single.
    YBounded_Single = ...
        single(0.2568) .* RBounded_Single + ... scaler, image
        single(0.5041) .* GBounded_Single + ... scaler, image
        single(0.0979) .* BBounded_Single + ... scaler, image
        single(16);                         %   scaler

    %Cb-channel page
    %M x N matrix; type single.
    CbBounded_Single = ...
        single(-0.1482) .* RBounded_Single + ...
        single(-0.2910) .* GBounded_Single + ...
        single(0.4392)  .* BBounded_Single + ...
        single(128); 

    %Cr-channel page
    %M x N matrix; type single.
    CrBounded_Single = ...
        single(0.4392)  .* RBounded_Single + ...
        single(-0.3678) .* GBounded_Single + ...
        single(-0.0714) .* BBounded_Single + ...
        single(128);
    
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
 
    %%%%%% >>>>>> H and S thresholds %%%%%%    
    
    %RGB to HSV conversion:
    
    %M x N matrices; type single.
    %Note: using three inputs and three outputs is an undocumented usage of Matlab function 
    %rgb2hsv. The documented usage is one input and one output of a 3-D array. By using three 
    %inputs instead of one, efficiency is increased by avoiding concatenation to the 3-D array; by 
    %using three outputs, efficiency is increased by avoiding indexing to extract the H channel. 
    %Note that if this function were to be used for code generation, only the one input / one 
    %output usage is supported.    
    [HBounded_Single, SBounded_Single, ~] = ...
        rgb2hsv(RBounded_Single, GBounded_Single, BBounded_Single);

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

