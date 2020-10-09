function [ROIBlock, ROIBlockDetectionFaceLinIdx, NDetectionsFace, ROIBlockDetectionSkinLinIdx, ...           
          NDetectionsSkin, ROIBlockDetectionFaceSkinLinIdx, NDetectionsFaceSkin, ...
          ROIBlockNoDetectionFaceSkinLinIdx, NNoDetectionsFaceSkin, TimestampBlock, ...
          TimestampBlockDetections] = ...          
             ROIMSIR_AssignVars(BlockFullLinIdx, ROI, HasROI_TF, Timestamp, FirstReadTF) %#codegen
%ROIMSIR_AssignVars   Assign variables, which may differ in length depending on whether they are 
%                     assigned during first-read or second-read operations.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function ROIMSIR.
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
%    Assign variables, which may differ in length depending on whether they are assigned during 
%    first-read or second-read operations.
%                     
%    Note:
%
%    Linear indices returned (e.g., ROIBlockDetectionFaceLinIdx) should contain unique values
%    sorted from least to greatest. This is required by functions SetDiff (called by functions 
%    ROIMSIR_FrameByFrameSmooth_InterpFR and ROIMSIR_FrameByFrameSmooth_SmoothFR) and PositionsIn
%    (called by function ROIMSIR_DetectionSmooth).
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


%If code generation running
if ~ coder.target('MATLAB')
    
    %If first-read operations
    if FirstReadTF

        %Local function
        [ROIBlockDetectionFaceLinIdx, NDetectionsFace, ROIBlockDetectionSkinLinIdx, ...
         NDetectionsSkin, ROIBlockDetectionFaceSkinLinIdx, NDetectionsFaceSkin, ...          
         ROIBlockNoDetectionFaceSkinLinIdx, NNoDetectionsFaceSkin] = ...
            DetectionIndices_FR(BlockFullLinIdx, HasROI_TF);
        
    %If second-read operations          
    else

        %Local function
        [ROIBlockDetectionFaceLinIdx, NDetectionsFace, ROIBlockDetectionSkinLinIdx, ...
         NDetectionsSkin, ROIBlockDetectionFaceSkinLinIdx, NDetectionsFaceSkin, ...          
         ROIBlockNoDetectionFaceSkinLinIdx, NNoDetectionsFaceSkin] = ...
            DetectionIndices_SR(BlockFullLinIdx, HasROI_TF);          
    end

%If code generation not running   
else
    
    %Local function
    [ROIBlockDetectionFaceLinIdx, NDetectionsFace, ROIBlockDetectionSkinLinIdx, ...
     NDetectionsSkin, ROIBlockDetectionFaceSkinLinIdx, NDetectionsFaceSkin, ...          
     ROIBlockNoDetectionFaceSkinLinIdx, NNoDetectionsFaceSkin] = ...
        DetectionIndices_MAT(BlockFullLinIdx, HasROI_TF);    
end

%ROI matrix with modifications corresponding to block index
%For the case of more than one output row assigned as output, ROI may not have had modifications,
%but whether it had modifications or not does not affect this case.
ROIBlock = ROI(BlockFullLinIdx, :);

%Timestamps in block
TimestampBlock = Timestamp(BlockFullLinIdx);

%Timestamps in block corresponding to frames with a detection 
TimestampBlockDetections = TimestampBlock(ROIBlockDetectionFaceSkinLinIdx);


end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function [ROIBlockDetectionFaceLinIdx, counterF, ROIBlockDetectionSkinLinIdx, counterS, ...          
          ROIBlockDetectionFaceSkinLinIdx, counterFOrS, ROIBlockNoDetectionFaceSkinLinIdx, ...
          counterNFOrS] = ...
              DetectionIndices_FR(BlockFullLinIdx, HasROI_TF)
%DetectionIndices_FR   Assign linear indices and counts corresponding to detections for first-read 
%                      operations.
%
%    Description:
%
%    Assign linear indices corresponding to the detections for first-read operations. Specifically,
%    return a linear index corresponding to detections by the face-detection algorithm, a linear
%    index corresponding to detections by the skin-detection algorithm, and a linear index 
%    corresponding to detections by either the face- or skin-detection algorithms. Also return 
%    counts of detections corresponding to each of the linear indices.
%
%    Notes:
%
%    This function differs from function DetectionIndices_SR because the lengths of the variables  
%    are fixed at 229 to prevent dynamic memory allocation. Note that constant 229 assumes that the  
%    length of BlockFullLinIdx == 229. If the length of this variable were to change, the constant  
%    would need to be modified.
%
%    Linear indices returned (e.g., ROIBlockDetectionFaceLinIdx) should contain unique values
%    sorted from least to greatest. See note at top.
          

%Inline function
coder.inline('always');          
 

%Preallocate linear index indicating ROIs that correspond to face detections or ROIs specified by 
%argument ROISpecifiedByArgument to FacePulseRate.
ROIBlockDetectionFaceLinIdx = coder.nullcopy( zeros(229, 1, 'int32') );    

%Preallocate linear index indicating ROIs that correspond to skin detections
ROIBlockDetectionSkinLinIdx = coder.nullcopy( zeros(229, 1, 'int32') );

%Preallocate linear index indicating ROIs that correspond to face detections, ROIs specified by  
%argument ROISpecifiedByArgument, or skin detections.
ROIBlockDetectionFaceSkinLinIdx = coder.nullcopy( zeros(229, 1, 'int32') );

%The converse of ROIBlockDetectionFaceSkinLinIdx
ROIBlockNoDetectionFaceSkinLinIdx = coder.nullcopy( zeros(229, 1, 'int32') );
    
%Face-detection counter
counterF = int32(0);

%Skin-detection counter
counterS = int32(0);

%Face or skin-detection counter
counterFOrS = int32(0);

%Converse
counterNFOrS = int32(0);

%Loop across the variables
for i = 1 : int32(229)

    %Assign index that aligns with full index
    %The full index used to index into HasROI_TF.
    ii = BlockFullLinIdx(i);
    
    %If any face detection
    if HasROI_TF.FacePrimary(ii)    || ...
       HasROI_TF.FaceSecondary1(ii) || ...   
       HasROI_TF.FaceSecondary2(ii) || ...
       HasROI_TF.ROISpecifiedByArgument(ii)
       
        counterF = counterF + 1;
        
        %Assign index
        ROIBlockDetectionFaceLinIdx(counterF) = i; 
        
        FaceOrSkinTF = true;
        
    else
        
        FaceOrSkinTF = false; 
    end 

    %If any skin detection
    if HasROI_TF.Skin(ii)
 
        counterS = counterS + 1;
        
        %Assign index
        ROIBlockDetectionSkinLinIdx(counterS) = i; 
        
        if ~ FaceOrSkinTF
 
           FaceOrSkinTF = true; 
        end              
    end

    %If any face detection or a skin detection
    if FaceOrSkinTF

        counterFOrS = counterFOrS + 1;

        %Assign index
        ROIBlockDetectionFaceSkinLinIdx(counterFOrS) = i;
        
    else

        counterNFOrS = counterNFOrS + 1;
        
        %Assign index
        ROIBlockNoDetectionFaceSkinLinIdx(counterNFOrS) = i;        
    end    
end

%Assert to prevent dynamic memory allocation by colon operation
assert(counterF     <= 229);
assert(counterS     <= 229);
assert(counterFOrS  <= 229);
assert(counterNFOrS <= 229);

%Linear index indicating ROIs that correspond to face detections or ROIs specified by argument 
%ROISpecifiedByArgument to FacePulseRate.
%:229 x 1 column vector; type int32.
if counterF ~= 0
    
    ROIBlockDetectionFaceLinIdx = ROIBlockDetectionFaceLinIdx(1 : counterF);
    
else
    
    ROIBlockDetectionFaceLinIdx = zeros(0, 1, 'int32');
end
    
%Linear index indicating ROIs that correspond to skin detections
%:229 x 1 column vector; type int32.
if counterS ~= 0
    
    ROIBlockDetectionSkinLinIdx = ROIBlockDetectionSkinLinIdx(1 : counterS);

else
    
    ROIBlockDetectionSkinLinIdx = zeros(0, 1, 'int32');    
end

%Linear index indicating ROIs that correspond to face detections, ROIs specified by argument 
%ROISpecifiedByArgument, or skin detections.
%:229 x 1 column vector; type int32.
if counterFOrS ~= 0
    
    ROIBlockDetectionFaceSkinLinIdx = ROIBlockDetectionFaceSkinLinIdx(1 : counterFOrS);
    
else
    
    ROIBlockDetectionFaceSkinLinIdx = zeros(0, 1, 'int32'); 
end

%Converse
%:229 x 1 column vector; type int32.
if counterNFOrS ~= 0
    
    ROIBlockNoDetectionFaceSkinLinIdx = ROIBlockNoDetectionFaceSkinLinIdx(1 : counterNFOrS);
    
else
    
    ROIBlockNoDetectionFaceSkinLinIdx = zeros(0, 1, 'int32');
end


end %end local function


%=============================================================================================
function [ROIBlockDetectionFaceLinIdx, counterF, ROIBlockDetectionSkinLinIdx, counterS, ...          
          ROIBlockDetectionFaceSkinLinIdx, counterFOrS, ROIBlockNoDetectionFaceSkinLinIdx, ...
          counterNFOrS] = ...
              DetectionIndices_SR(BlockFullLinIdx, HasROI_TF)
%DetectionIndices_SR   Assign linear indices and counts corresponding to detections for second-read 
%                      operations.
%
%    Description:
%
%    Assign linear indices corresponding to the detections for second-read operations. 
%    Specifically, return a linear index corresponding to detections by the face-detection 
%    algorithm, a linear index corresponding to detections by the skin-detection algorithm, and a  
%    linear index corresponding to detections by either the face- or skin-detection algorithms.  
%    Also return counts of detections corresponding to each of the linear indices.
%
%    Notes:
%
%    This function differs from function DetectionIndices_FR because the lengths of the variables  
%    are not fixed in the current function.
%
%    Linear indices returned (e.g., ROIBlockDetectionFaceLinIdx) should contain unique values
%    sorted from least to greatest. See note at top.


%Inline function
coder.inline('always');          
 

%Length of ROI block          
NElements = int32( numel(BlockFullLinIdx) );

%Preallocate linear index indicating ROIs that correspond to face detections or ROIs specified by 
%argument ROISpecifiedByArgument to FacePulseRate.
ROIBlockDetectionFaceLinIdx = coder.nullcopy( zeros(NElements, 1, 'int32') );    

%Preallocate linear index indicating ROIs that correspond to skin detections
ROIBlockDetectionSkinLinIdx = coder.nullcopy( zeros(NElements, 1, 'int32') );
    
%Preallocate linear index indicating ROIs that correspond to face detections, ROIs specified by  
%argument ROISpecifiedByArgument, or skin detections.
ROIBlockDetectionFaceSkinLinIdx = coder.nullcopy( zeros(NElements, 1, 'int32') );   

%The converse of ROIBlockDetectionFaceSkinLinIdx
ROIBlockNoDetectionFaceSkinLinIdx = coder.nullcopy( zeros(229, 1, 'int32') );

%Face-detection counter
counterF = int32(0);

%Skin-detection counter
counterS = int32(0);

%Face or skin-detection counter
counterFOrS = int32(0);

%Converse
counterNFOrS = int32(0);

%Loop across the variables
for i = 1 : NElements

    %Assign index that aligns with full index
    %The full index used to index into HasROI_TF.
    ii = BlockFullLinIdx(i);
    
    %If any face detection
    if HasROI_TF.FacePrimary(ii)    || ...
       HasROI_TF.FaceSecondary1(ii) || ...   
       HasROI_TF.FaceSecondary2(ii) || ...
       HasROI_TF.ROISpecifiedByArgument(ii)
       
        counterF = counterF + 1;
        
        %Assign index
        ROIBlockDetectionFaceLinIdx(counterF) = i; 
        
        FaceOrSkinTF = true;
        
    else
        
        FaceOrSkinTF = false; 
    end 

    %If any skin detection
    if HasROI_TF.Skin(ii)
 
        counterS = counterS + 1;
        
        %Assign index
        ROIBlockDetectionSkinLinIdx(counterS) = i; 
        
        if ~ FaceOrSkinTF
 
           FaceOrSkinTF = true; 
        end         
    end

    %If any face detection or a skin detection
    if FaceOrSkinTF

        counterFOrS = counterFOrS + 1;

        %Assign index
        ROIBlockDetectionFaceSkinLinIdx(counterFOrS) = i;
        
    else
        
        counterNFOrS = counterNFOrS + 1;

        %Assign index
        ROIBlockNoDetectionFaceSkinLinIdx(counterNFOrS) = i; 
    end
end

%Linear index indicating ROIs that correspond to face detections or ROIs specified by argument 
%ROISpecifiedByArgument to FacePulseRate.
%M x 1 column vector; type int32.
if counterF ~= 0
    
    ROIBlockDetectionFaceLinIdx = ROIBlockDetectionFaceLinIdx(1 : counterF);
    
else
    
    ROIBlockDetectionFaceLinIdx = zeros(0, 1, 'int32');
end
    
%Linear index indicating ROIs that correspond to skin detections
%M x 1 column vector; type int32.
if counterS ~= 0
    
    ROIBlockDetectionSkinLinIdx = ROIBlockDetectionSkinLinIdx(1 : counterS);

else
    
    ROIBlockDetectionSkinLinIdx = zeros(0, 1, 'int32');    
end

%Linear index indicating ROIs that correspond to face detections, ROIs specified by argument 
%ROISpecifiedByArgument, or skin detections.
%M x 1 column vector; type int32.
if counterFOrS ~= 0
    
    ROIBlockDetectionFaceSkinLinIdx = ROIBlockDetectionFaceSkinLinIdx(1 : counterFOrS);
    
else
    
    ROIBlockDetectionFaceSkinLinIdx = zeros(0, 1, 'int32'); 
end

%Converse
%M x 1 column vector; type int32.
if counterNFOrS ~= 0
    
    ROIBlockNoDetectionFaceSkinLinIdx = ROIBlockNoDetectionFaceSkinLinIdx(1 : counterNFOrS);
    
else
    
    ROIBlockNoDetectionFaceSkinLinIdx = zeros(0, 1, 'int32');
end


end %end local function


%=============================================================================================
function [ROIBlockDetectionFaceLinIdx, counterF, ROIBlockDetectionSkinLinIdx, counterS, ...          
          ROIBlockDetectionFaceSkinLinIdx, counterFOrS, ROIBlockNoDetectionFaceSkinLinIdx, ...
          counterNFOrS] = ...
              DetectionIndices_MAT(BlockFullLinIdx, HasROI_TF)
%DetectionIndices_MAT   Assign linear indices and coutns corresponding to detections when not using  
%                       code generation.
%
%    Description:
%
%    Assign linear indices corresponding to the detections for second-read operations. 
%    Specifically, return a linear index corresponding to detections by the face-detection 
%    algorithm, a linear index corresponding to detections by the skin-detection algorithm, and a  
%    linear index corresponding to detections by either the face- or skin-detection algorithms.  
%    Also return counts of detections corresponding to each of the linear indices.
%
%    Note:
%
%    This function differs from functions DetectionIndices_FR and DetectionIndices_SR because
%    vectorization rather than loop-based code is used in the current function.
%
%    Linear indices returned (e.g., ROIBlockDetectionFaceLinIdx) should contain unique values
%    sorted from least to greatest. See note at top.


%Linear index corresponding to ROI block indicating frames with a detection from a face-detection 
%algorithm or an ROI specified by argument ROISpecifiedByArgument to FacePulseRate.
ROIBlockDetectionFaceLogIdx = ...
    HasROI_TF.FacePrimary(BlockFullLinIdx)    | ...
    HasROI_TF.FaceSecondary1(BlockFullLinIdx) | ...
    HasROI_TF.FaceSecondary2(BlockFullLinIdx) | ...
    HasROI_TF.ROISpecifiedByArgument(BlockFullLinIdx);

ROIBlockDetectionFaceLinIdx = int32( find(ROIBlockDetectionFaceLogIdx) );

%Number of face-detection algorithm detections
counterF = int32( numel(ROIBlockDetectionFaceLinIdx) );

%Linear index corresponding to ROI block indicating frames with a detection from the skin-detection 
%algorithm.
ROIBlockDetectionSkinLogIdx = HasROI_TF.Skin(BlockFullLinIdx); 

ROIBlockDetectionSkinLinIdx = int32( find(ROIBlockDetectionSkinLogIdx) );

%Number of face-detection algorithm detections
counterS = int32( numel(ROIBlockDetectionSkinLinIdx) );

%Linear index corresponding to ROI block indicating frames with a detection from either the  
%face-detection algorithm or skin-detection algorithm.
ROIBlockDetectionFaceSkinLogIdx = ROIBlockDetectionFaceLogIdx | ROIBlockDetectionSkinLogIdx; 

ROIBlockDetectionFaceSkinLinIdx = int32( find(ROIBlockDetectionFaceSkinLogIdx) );

%Number of face-detection algorithm detections
counterFOrS = int32( numel(ROIBlockDetectionFaceSkinLinIdx) );

%Converse
ROIBlockNoDetectionFaceSkinLinIdx = int32( find(~ ROIBlockDetectionFaceSkinLogIdx) );
   
%Number of non-detections
counterNFOrS = int32( numel(ROIBlockNoDetectionFaceSkinLinIdx) );
    

end %end local function
