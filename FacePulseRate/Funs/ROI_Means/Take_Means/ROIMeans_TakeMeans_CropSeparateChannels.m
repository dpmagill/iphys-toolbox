function [RROI_Uint8, GROI_Uint8, BROI_Uint8] = ...
             ROIMeans_TakeMeans_CropSeparateChannels(VidFrame, x_ROI_int16, y_ROI_int16, ...
                 nRows_ROI, nCols_ROI, nCols_Full_int16, nRows_Full_int16) %#codegen                
%ROIMeans_TakeMeans_CropSeparateChannels  Crop the input frame and separate it into its colorspace 
%                                         channels.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by functions ROIMeans_TakeMeans and 
%    ROIMeans_TakeMeans_ROIValidate.
%
%
%    Code Generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.  
%
%
%    Note
%    ----
%
%    The parfor-loop is slower than a for-loop when run in Matlab code, so use the parfor-loop only  
%    for code generation.
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code-generation settings %%%%%%

%Inline function
coder.inline('always');


%%%%%% Code generation running %%%%%%

%If code generation running
if ~ coder.target('MATLAB') 

    %Cast to int32 to prevent overflow when converting to linear index
    %Scalars; type int32.
    nCols_Full = int32(nCols_Full_int16); 
    nRows_Full = int32(nRows_Full_int16);
    
    %X and Y-coordinates to crop to
    %Cast to int32 to prevent overflow when converting to linear index.
    %Scalars; type int32.
    x_crop = int32( x_ROI_int16 ); 
    y_crop = int32( y_ROI_int16 ); 

    %Preallocate channel matrices:
    
    %Red channel
    %M x N matrix; type uint8.
    RROI_Uint8 = coder.nullcopy( zeros(nRows_ROI, nCols_ROI, 'uint8') );
    
    %Green channel
    %M x N matrix; type uint8.
    GROI_Uint8 = coder.nullcopy( zeros(nRows_ROI, nCols_ROI, 'uint8') );
    
    %Blue channel
    %M x N matrix; type uint8.
    BROI_Uint8 = coder.nullcopy( zeros(nRows_ROI, nCols_ROI, 'uint8') );

    %Crop offsets
    %Scalars; type int32.
    %Note: the step prevents repeated subtraction by one in the parfor loop.
    ColOffset = x_crop - 1;
    RowOffset = y_crop - 1;    
    
    %Number of elements in one color channel of the full frame
    %Scalar; type int32.
    NPageElements = nCols_Full * nRows_Full;
    
    %Number multiplied by 2
    %Scalar; type int32.
    NPageElementsBy2 = NPageElements * 2;
    
    %Crop to ROI and separate by color channel:
    
    %Loop across columns
    parfor i = 1 : nCols_ROI 

        %Adjust column index to align with coordinate plane of full frame
        iFull = i + ColOffset;
        
        %Loop across rows
        for j = 1 : nRows_ROI             
            
            %Adjust row index to align with coordinate plane of full frame
            jFull = j + RowOffset;
            
            %Convert from subscript indices to a linear index for more efficient indexing
            %Scalar; type int32.
            %Note: In compiled C code, the faster indexing outweighs the cost of this conversion.
            LinIdxFull = jFull + (iFull - 1) * nRows_Full;
            
            %Red channel element:
            
            %Extract value from full frame                      
            jth = VidFrame(LinIdxFull); %#ok<PFBNS>

            %Insert value into bounded frame
            RROI_Uint8(j, i) = jth;

            %Green channel element:
            
            %Extract value from full frame
            jth = VidFrame(LinIdxFull + NPageElements); 

            %Insert value into bounded frame
            GROI_Uint8(j, i) = jth;

            %Blue channel element:
            
            %Extract value from full frame
            jth = VidFrame(LinIdxFull + NPageElementsBy2);

            %Insert value into bounded frame
            BROI_Uint8(j, i) = jth;
        end       
    end

    
%%%%%% Code generation not running %%%%%%   

else 

    %Crop ROI from frame
    %M x N x 3 array; type uint8.
    VidFrame = ...
        VidFrame( ...
            y_ROI_int16 : y_ROI_int16 + int16(nRows_ROI - 1), ... rows
            x_ROI_int16 : x_ROI_int16 + int16(nCols_ROI - 1), ... columns
            :                                                 ... pages
        ); 
    
    %Separate by color channel
    %M x N matrices; type uint8.
    RROI_Uint8 = VidFrame(:, :, 1); %Red channel
    GROI_Uint8 = VidFrame(:, :, 2); %Green channel
    BROI_Uint8 = VidFrame(:, :, 3); %Blue channel
end


end %end function


