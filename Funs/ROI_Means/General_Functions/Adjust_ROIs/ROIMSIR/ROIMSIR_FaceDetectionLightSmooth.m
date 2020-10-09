function [ROIDetections, FaceIdxFit] = ...
             ROIMSIR_FaceDetectionLightSmooth(ROI_In, FaceSkinIdx, NFaceSkinIdx, FaceIdx, NFaceIdx)            
             %#codegen
%ROIMSIR_FaceDetectionLightSmooth   Lightly smooth ROIs corresponding to face detections.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function ROIMSIR_DetectionSmooth.
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
%    Lightly smooth ROIs corresponding to face detections: 
%
%    (1) Smooth the height and width of each ROI.
%    (2) Adjust the X- and Y-coordinates of each ROI to correspond to the previous changes to the 
%        height and width.
%    (3) Smooth the X- and Y-coordinates of each ROI.
%
%    Return a matrix of ROIs that correspond to either face- or skin-detection algorithm 
%    detections. Although this function only smooths ROIs corresponding to face detections, ROIs 
%    corresponding to skin detections are also included in the output for efficient use in other 
%    functions. Vector FaceIdxFit is an index that indicates which rows in the output matrix 
%    correspond to the smoothed ROIs from face detections.
%
%    Under certain conditions, even if a face-detection ROI is present, the ROI may not be 
%    smoothed. In this case, there will not be a corresponding index in FaceIdxFit.
%    
%    Assumptions:
%   
%    - Neither NFaceSkinIdx nor NFaceIdx equal 0.
%    - Elements of set FaceIdx are entirely nested within set FaceSkinIdx.      
%    - Within each of these sets, values do not repeat and are ordered such that they increase
%      monotonically.
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


%Preallocate ROI matrix where ROIs correspond to either face- or skin-detection algorithm 
%detections.
ROIDetections = coder.nullcopy( zeros(NFaceSkinIdx, 4, 'int16') );

%Preallocate index indicating position of smoothed ROIs that correspond to face-detection algorithm 
%within variable ROIDetections.
%If this variable is returned as 0, this indicates that no ROIs were smoothed within this function.
FaceIdxFit = int32(0);

%If a smoothing window of 3 is possible
if NFaceSkinIdx > 2    
    
    %%%%%% --- Widths and heights and tentative X- and Y-coordinates %%%%%%      
    
    %Initialize face-detection algorithm detection counter
    FaceIdxCounter = int32(1);
    
    %Loop across rows corresponding to a detection (either from face-detection or skin-detection
    %algorithm).
    %Note: the value of NFaceSkinIdx equals the length of FaceSkinIdx. 
    for i = 1 : NFaceSkinIdx       

        %Index of ith face- or skin-detection
        FaceSkinIdx_ith = FaceSkinIdx(i);        
        
        %If the ith row corresponds to a face-detection algorithm detection
        %Note: this comparison method is possible because ...
        %(1) Set FaceIdx is completed nested within set FaceSkinIdx. 
        %(2) Both FaceIdx and FaceSkinIdx are sets of non-repeating monotonically increasing 
        %values.
        if FaceIdxCounter <= NFaceIdx && ... prevent FaceIdxCounter from indexing beyond length of FaceIdx 
           FaceSkinIdx(i) == FaceIdx(FaceIdxCounter) %the ith row corresponds to a face detection       

            %For first and last detections, do not smooth because a smoothing window of 3 cannot be
            %used.
            if ~ (i == 1 || i == NFaceSkinIdx)
 
                FaceSkinIdx_ithM1 = FaceSkinIdx(i - 1);      

                FaceSkinIdx_ithP1 = FaceSkinIdx(i + 1);                 
                
                %Loop across width and height columns
                for j = 3 : 4                                                                     
                    
                    %ijth ROI
                    ROI_ij = ROI_In(FaceSkinIdx_ith, j);                                    
                    
                    %Smooth ijth ROI 
                    %Scalar; int16.
                    %Note: as only three elements are summed, the data type will not overflow.                    
                    Smoothed_ij = ...
                        (ROI_In(FaceSkinIdx_ithM1, j) + ...
                         ROI_ij + ...
                         ROI_In(FaceSkinIdx_ithP1, j)) / ...
                         int16(3);                       
 
                    %Assign width or height:
                    
                    ROIDetections(i, j) = Smoothed_ij;
                                          
                    %Adjust X- or Y-coordinate to correspond to changes in width or height:
                    
                    %(1) Take half of difference between old and new widths/heights
                    %(2) Add to X- or Y-coordinate
                    %Optimize division by 2 with bitwise operation.
                    
                    switch j
                        
                        %Width was smoothed -> Adjust X-coordinate
                        case 3

                            ROIDetections(i, 1) = ...
                                ROI_In(FaceSkinIdx_ith, 1) + ...
                                bitshift(ROI_ij - Smoothed_ij, -1);                            

                        %Height was smoothed -> Adjust Y-coordinate
                        case 4
                            
                            ROIDetections(i, 2) = ...
                                ROI_In(FaceSkinIdx_ith, 2) + ...
                                bitshift(ROI_ij - Smoothed_ij, -1);                                                        
                    end
                end
            
            %Position of ROI does not permit smoothing window of length 3
            else 
                
                %If first row of ROIDetections               
                if i == 1 
                  
                    ROIDetections(1, 1 : 4) = ROI_In(FaceSkinIdx_ith, 1 : 4);                        
                    
                %If last row of ROIDetections                     
                else % i == NFaceSkinIdx                    
                    
                    ROIDetections(NFaceSkinIdx, 1 : 4) = ROI_In(FaceSkinIdx_ith, 1 : 4);                                              
                end                
            end
            
            %Advance counter of face-detection algorithm detections
            FaceIdxCounter = FaceIdxCounter + int32(1);
            
        %If the ith detection is not a face-detection algorithm detection
        %I.e., it is a skin-detection algorithm detection.
        else

            ROIDetections(i, 1 : 4) = ROI_In(FaceSkinIdx_ith, 1 : 4);               
        end    
    end 

    %%%%%% --- Final X- and Y-coordinates %%%%%%             
    
    %Preallocate column of smoothed ROI elements that correspond to the X- and Y-coordinates of
    %face-detection algorithm detections. 
    %Smoothed ROI elements are assigned to this variable rather than variable ROIDetections to 
    %prevent elements that have been smoothed from being included in the smoothing windows of 
    %subsequent elements. After the loop, the smoothed elements are assigned to ROIDetections.    
    SmoothedXYColumn = coder.nullcopy( zeros(NFaceIdx, 2, 'int16') );                   
 
    %Assign the first and/or last rows of SmoothedXYColumn if there is a match to the first and/or 
    %last rows of ROIDetections:
    
    %This assignment is made here because these rows will not be assigned later.
 
    if FaceIdx(1) == FaceSkinIdx(1) 
        
        SmoothedXYColumn(1, 1 : 2) = ROIDetections(1, 1 : 2);
    end
    
    if FaceIdx(NFaceIdx) == FaceSkinIdx(NFaceSkinIdx) 
        
        SmoothedXYColumn(NFaceIdx, 1 : 2) = ROIDetections(NFaceSkinIdx, 1 : 2);
    end

    %Smooth X- and Y-coordinates:

    %Find the positions of FaceIdx in FaceSkinIdx 
    %Column vector; int32.
    %Note: PositionsIn is a custom function located within folder 'FacePulseRate'.
    FaceIdxFit = ...
        PositionsIn( ...
            FaceIdx,     ... set A
            FaceSkinIdx, ... set B
            NFaceIdx     ... length of set A
        );    
       
    %Loop across rows corresponding to a face detection 
    %Note: the value of NFaceIdx equals the length of FaceIdx. 
    for i = 1 : NFaceIdx          
        
        ii = FaceIdxFit(i);
        
        %For first and last detections, do not smooth because a smoothing window of 3 cannot be
        %used.
        if ~ (ii == 1 || ii == NFaceSkinIdx)    

            %Loop across X- and Y-coordinate columns
            for j = 1 : 2

                %Smooth ijth ROI and assign to SmoothedXYColumn
                %(See note where SmoothedColumn preallocated).
                %Scalar; int16.
                %Note: as only three elements are summed, the data type will not overflow.                    
                SmoothedXYColumn(i, j) = ...
                    (ROIDetections(ii - 1, j) + ...
                     ROIDetections(ii, j) + ...
                     ROIDetections(ii + 1, j)) / ...
                     int16(3);                                                             
            end    
        end      
    end   
    
    %Assign final X- and Y-coordinates:
    
    %Loop across X- and Y-coordinate columns corresponding to detections
    for i = 1 : 2
        
        %Loop across rows corresponding to a face detection 
        %Note: the value of NFaceIdx equals the length of FaceIdx. 
        for j = 1 : NFaceIdx            

            jj = FaceIdxFit(j);

            ROIDetections(jj, i) = SmoothedXYColumn(j, i);
        end
    end
        
%A smoothing window of 3 is not possible
%ROINoPrevCallsBlock_ROIDetections will not be empty.
elseif NFaceSkinIdx > 0
 
    for i = 1 : NFaceSkinIdx
        
        FaceSkinIdx_ith = FaceSkinIdx(i);
    
        for j = 1 : 4
        
            ROIDetections(i, j) = ROI_In(FaceSkinIdx_ith, j);                            
        end
    end
    
%A smoothing window of 3 is not possible
%ROINoPrevCallsBlock_ROIDetections will be empty.    
else %NDetectionsFaceSkin == 0
    
    ROIDetections = zeros(0, 4, 'int16');
end
   

end %end function

