function ROIDiagnostic_ROISkin_ith = ...
             SkinDetect_RecordDiagnosticData(ROIDiagnostic_ROISkin_ith, ...
                 RegionPassAllThresholdsTF_LogIdx, RegionSelectedLinIdx, RegionIndices, ...
                 BoundingBoxSkin, RegionCentroids, ROIPredicted_CenterX, ROIPredicted_CenterY, ... 
                 RegionRGBProbSkin, RegionZ_Y, RegionZ_Cb, RegionZ_Cr, RegionPoints, ...
                 RegionNPixels, NRegions, RegionNPixels_PassNThresholdTF_LogIdx, RegionSD_Cr, ... 
                 RegionSD_Cr_PassThresholdTF_LogIdx, nRows_IsSkinMask, nCols_IsSkinMask, ...
                 VidObjHeight) %#codegen                                 
%SkinDetect_RecordDiagnosticData   Record various metrics to determine effectiveness of the skin- 
%                                  detection algorithm on each frame assessed.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function SkinDetect.  
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
%    Collect frame-by-frame diagnostic information regarding the performance of the skin-detection 
%    algorithm. This information will be displayed on the output video (by function WriteFaceVideo 
%    and, more specifically, WriteFaceVideo_SkinDetectDiagnosis). 
%
%    Four states are possible from function SkinDetect, from which the current function is called.
%
%    The first state is a successful ROI detection. In this state, region borders are shown for all 
%    regions, with the regions color coded depending on whether the region corresponds to a 
%    rejected, candidate, or selected region. Other information is also shown. 
%
%    The second state is a region selected that fails the skin proportion test (see function 
%    ConfirmSkinPresent). In this state, borders and other information are not shown but a message 
%    is displayed on the output video indicating this result. 
%
%    The third state is when all regions fail the rejection thresholds (see function 
%    SkinDetect_RejectRegions). In this state, region borders of the rejected region(s) are shown 
%    on the output video along with other information.     
%
%    The forth state is when no regions are available for classification, likely because of 
%    complete, or near complete, skin segmentation of the bounding box area. In this state, borders 
%    and other information are not shown but a message is displayed on the output video indicating 
%    this result. For more information on the diagnostic information displayed on the output video, 
%    see functions WriteFaceVideo and WriteFaceVideo_SkinDetectDiagnosis.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Code-generation settings %%%%%

%Inline function
coder.inline('always');

%Declare variable-size variables:

%                                         Upp. Bounds   Var. Size (T/F)
coder.varsize('RegionsCandidateLinIdx',   [400, 1],     [1, 0]); 
coder.varsize('RegionsRejectedLinIdx',    [400, 1],     [1, 0]);
coder.varsize('RegionBoundaries',         [1, 3],       [0, 0]); %cell array
coder.varsize('RegionBoundaries{:}',      [inf, 1],     [1, 0]); %cell array element


%%%%%% Setup %%%%%%

%Record that at least one region was available for skin detection for ith frame
%Note: a false value will be present if the area corresponding to the skin-detection bounding box 
%was completely segmented and, hence, has no regions available. Note that a false value will also 
%be present if the frame did not have the skin-detection algorithm applied on it, that is, if 
%function SkinDetect was not used for the frame. 
ROIDiagnostic_ROISkin_ith.RegionAnyAvailable = true;  

%Proceed if the proportion of pixels classified as skin within the ROI from the selected region was 
%above the specified threshold. If not, it is likely that skin-segmentation completely segmented 
%the ROI. If not, diagnostic information is not displayed to avoid confusion because the depiction
%of candidate regions and a selected region may make it appear that the skin-detection algorithm 
%was successful for the ith frame.
if ~ ROIDiagnostic_ROISkin_ith.ProportionSkinPixelsTooLow
 
    
    %%%%%% Assign linear indices and flags to specify region status (candidate, rejected) %%%%%%
    
    %Note: RegionSelectedLinIdx already assigned.
       
    %Flag indicating a region was selected 
    RegionSelectedAnyTF = ~ isempty(RegionSelectedLinIdx);
    
    %Linear index of rejected regions
    %Local function.
    [RegionsRejectedLinIdx, ... column vector; type uint16
     NRegionsRejected] =    ... scalar; type uint16
        FindRejectedRegions(NRegions, RegionPassAllThresholdsTF_LogIdx);  
    
    %Flag indicating at least one region was rejected 
    RegionsRejectedAnyTF = NRegionsRejected ~= 0;        

    %Assert value to prevent dynamic memory allocation
    assert(NRegionsRejected <= 400);        
    
    %Linear index of candidate regions
    %Local function.
    [RegionsCandidateLinIdx, ... column vector; type uint16
     NRegionsCandidate] =    ... scalar; type uint16
        FindCandidateRegions(NRegions, RegionSelectedLinIdx, RegionsRejectedLinIdx, ...
            NRegionsRejected);    

    %Flag indicating at least one region is a candidate region 
    RegionsCandidateAnyTF = NRegionsCandidate ~= 0;    

    %Assert value to prevent dynamic memory allocation
    assert(NRegionsCandidate <= 400);              
    
    %%%%%% Record Boundaries of Regions %%%%%%

    %Return an index of the pixels that lie on the external (perimeter) and internal (holes)
    %boundaries for each region. As the pixels have been dilated (for visibility on the output  
    %video), the pixels include pixels near the boundary as well.
       
    %1 x 3 cell array; elements: N pixels x 1 column vector, type uint32.
    %Note: SkinDetect_RegionBoundariesByCategory is a custom function located within folder   
    %'FacePulseRate'.    
    RegionBoundaries = ...
        SkinDetect_RegionBoundariesByCategory(RegionSelectedAnyTF, NRegionsCandidate, ...
                 NRegionsRejected, RegionSelectedLinIdx, RegionIndices, RegionsCandidateLinIdx, ...
                 RegionsRejectedLinIdx, VidObjHeight, BoundingBoxSkin, RegionNPixels, ...        
                 nRows_IsSkinMask, nCols_IsSkinMask);
                                            
    %Store linear index of boundary pixels for later use for displaying skin regions on output 
    %video: 
    
    %Selected region
    if RegionSelectedAnyTF

        %Assign boundary index to struct  
        %N pixels x 1 column vector; type uint32.
        ROIDiagnostic_ROISkin_ith.RegionBoundaries_SelectedLinIdx = RegionBoundaries{1};            
    end

    %Candidate regions
    if RegionsCandidateAnyTF

        %Assign boundary index to struct  
        %N pixels x 1 column vector; type uint32.
        ROIDiagnostic_ROISkin_ith.RegionBoundaries_CandidateLinIdx = RegionBoundaries{2};            
    end

    %Rejected regions
    if RegionsRejectedAnyTF

        %Assign boundary index to struct  
        %N pixels x 1 column vector; type uint32.
        ROIDiagnostic_ROISkin_ith.RegionBoundaries_RejectedLinIdx = RegionBoundaries{3};            
    end 

    
    %%%%%% Record Centroids of Regions %%%%%%

    %Adjust the [X, Y] coordinates to undo change to [X, Y] as a result of cropping. This 
    %adjustment will place [X, Y] in the coordinate plane of the full (uncropped) frame so that 
    %[X, Y] can be used in the output video. To do so, add back distances of X and Y that were 
    %changed by cropping.

    %Note: 1 pixel length is subtracted from the [X, Y] that is added back because the previous 
    %cropping changed [Xoriginal, Yoriginal] to [1, 1]; that is, the cropping moved the coordinates 
    %a distance of Xoriginal - 1 and Yoriginal - 1.
   
    %Called during code generation
    if ~ coder.target('MATLAB') 
       
        %M regions x 2 matrix; type int16
        RegionCentroids_Uncrop = coder.nullcopy( zeros(NRegions, 2, 'int16') );        

        %Scalars; type int16.
        AdjustmentOffsetX = BoundingBoxSkin(1) - 1;
        AdjustmentOffsetY = BoundingBoxSkin(2) - 1;
        
        %The X-coordinate column
        for i = 1 : NRegions     

            RegionCentroids_Uncrop(i, 1) = RegionCentroids(i, 1) + AdjustmentOffsetX; 
            
            RegionCentroids_Uncrop(i, 2) = RegionCentroids(i, 2) + AdjustmentOffsetY;
        end
        
    %Called outsize of code generation           
    else

        RegionCentroids_Uncrop = ...
            int16( ...
                RegionCentroids + ...
                [(BoundingBoxSkin(1) - 1), (BoundingBoxSkin(2) - 1)] ...
            );                               
    end

    %Assign [X, Y] coordinates of region centroids to ith row of nested-struct RegionCentroids;
    %assign to the field corresponding to regions status (selected, candidate, rejected).
    %Type uint16.

    if RegionSelectedAnyTF %if at least one region

       %1 selected region x 2 row vector; type uint16.
       ROIDiagnostic_ROISkin_ith.RegionCentroids_SelectedXY = ...
           RegionCentroids_Uncrop(RegionSelectedLinIdx, 1 : 2);
    end

    if RegionsCandidateAnyTF %if at least one region

        %M candidate regions x 2 matrix; type uint16.
        ROIDiagnostic_ROISkin_ith.RegionCentroids_CandidateXY = ...
            RegionCentroids_Uncrop(RegionsCandidateLinIdx, 1 : 2);
    end

    if RegionsRejectedAnyTF %if at least one region

        %M rejected regions x 2 matrix; type uint16.
        ROIDiagnostic_ROISkin_ith.RegionCentroids_RejectedXY = ...
            RegionCentroids_Uncrop(RegionsRejectedLinIdx, 1 : 2); 
    end


    %%%%%% Record the center point [X, Y] coordinates of the predicted ROI %%%%%%

    %Record the center point [X, Y] coordinates of the predicted ROI for the use of diagnosing 
    %skin-detection errors later. The predicted ROI will be superimposed on the output video if 
    %WriteVideoShowROISkinDiagnosisTF, which is an argument to function FacePulseRate, is true. In 
    %diagnosis, the proximity of the centroid of the selected region to the predicted-ROI center is 
    %inspected. This proximity is used, in part, to determine which of the candidate regions is
    %selected. Inspection can determine whether the proximity weight should be fine tuned depending 
    %on the desirability of the selected skin region.
 
    %Adjust the [X, Y] coordinates to undo change to [X, Y] as a result of cropping. This 
    %adjustment will place [X, Y] in the coordinate plane of the full (uncropped) frame so that 
    %[X, Y] can be used in the output video. To do so, add back distances of X and Y that were 
    %changed by cropping.

    %Convert from type int16 to type uint16 because signed operations not conducted with this
    %variable.

    %If at least one region passed the rejection thresholds (resulting in at least one selected or
    %candidate region). Otherwise, this information wasn't used in the assessment of regions for 
    %this frame.
    if RegionSelectedAnyTF || RegionsCandidateAnyTF

        %1 x 2 row vector; type uint16.
        ROIDiagnostic_ROISkin_ith.PredictedROI_center = ...
            uint16( ...
                [ROIPredicted_CenterX + (BoundingBoxSkin(1) - 1), ... 
                 ROIPredicted_CenterY + (BoundingBoxSkin(2) - 1)] ...
            );    
    end


    %%%%%% Record RGB probabilities of regions %%%%%%

    %Assign probabilities of regions to ith row of nested-struct RegionScores; assign to the RGB
    %probability field corresponding to region status (selected, candidate, rejected). 
    %To conserve memory, convert RGB probability to type uint8 (multiply by 100 to remove 
    %fraction); uint8 conversion automatically rounds value to integer, which is necessary later  
    %when using the values as indices.

    if RegionSelectedAnyTF %if at least one region

        %Scalar; type uint8.
        ROIDiagnostic_ROISkin_ith.RegionScores_SelectedRGBProb = ...
            uint8( RegionRGBProbSkin(RegionSelectedLinIdx) * 100 );
    end

    if RegionsCandidateAnyTF %if at least one region

        %M candidate regions x 1 column vector; type uint8.
        ROIDiagnostic_ROISkin_ith.RegionScores_CandidateRGBProb= ...
            uint8( RegionRGBProbSkin(RegionsCandidateLinIdx) * 100 );
    end

    if RegionsRejectedAnyTF %if at least one region
        
        %M rejected regions x 1 column vector; type uint8.
        ROIDiagnostic_ROISkin_ith.RegionScores_RejectedRGBProb = ...
            uint8( RegionRGBProbSkin(RegionsRejectedLinIdx) * 100 );
    end


    %%%%%% Record YCbCr Z-Scores of Regions %%%%%%

    %Assign z-scores of regions to ith row of nested-struct RegionScores; assign to the YCbCr 
    %z-scores field corresponding to region status (selected, candidate, rejected).
    %Round to 2 decimal places for presentation purposes. The round(X * 100) * .01 is used because 
    %code generation does not support round(X, 2).

    if RegionSelectedAnyTF %if at least one region

        %1 selected region x 3 row vector; type single.        
        ROIDiagnostic_ROISkin_ith.RegionScores_SelectedYCbCrZ = ... 
            [round( RegionZ_Y(RegionSelectedLinIdx)  * 100 ) * .01, ...
             round( RegionZ_Cb(RegionSelectedLinIdx) * 100 ) * .01, ...
             round( RegionZ_Cr(RegionSelectedLinIdx) * 100 ) * .01];

    end

    if RegionsCandidateAnyTF %if at least one region  
                      
        %M candidate regions x 3 matrix; type single.
        RegionScores_CandidateYCbCrZ = coder.nullcopy( zeros(NRegionsCandidate, 3, 'single') );
 
        for i = 1 : NRegionsCandidate
        
            ii = RegionsCandidateLinIdx(i);
            
            RegionScores_CandidateYCbCrZ(i, 1) = round( RegionZ_Y(ii)  * 100 ) * .01;
            RegionScores_CandidateYCbCrZ(i, 2) = round( RegionZ_Cb(ii) * 100 ) * .01;
            RegionScores_CandidateYCbCrZ(i, 3) = round( RegionZ_Cr(ii) * 100 ) * .01;
        end
        
        %Assign to struct
        ROIDiagnostic_ROISkin_ith.RegionScores_CandidateYCbCrZ = RegionScores_CandidateYCbCrZ;  
    end

    if RegionsRejectedAnyTF %if at least one region                     
        
        %M rejected regions x 3 matrix; type single.
        RegionScores_RejectedYCbCrZ = coder.nullcopy( zeros(NRegionsRejected, 3, 'single') );        

        for i = 1 : NRegionsRejected
        
            ii = RegionsRejectedLinIdx(i);
            
            RegionScores_RejectedYCbCrZ(i, 1) = round( RegionZ_Y(ii)  * 100 ) * .01;
            RegionScores_RejectedYCbCrZ(i, 2) = round( RegionZ_Cb(ii) * 100 ) * .01;
            RegionScores_RejectedYCbCrZ(i, 3) = round( RegionZ_Cr(ii) * 100 ) * .01;
        end   
        
        %Assign to struct
        ROIDiagnostic_ROISkin_ith.RegionScores_RejectedYCbCrZ = RegionScores_RejectedYCbCrZ;          
    end


    %%%%%% Record Rankings Index of Candidate Regions %%%%%% 

    %Rankings are recorded to enable a cleaner display on the output video.
    %For example, it may be most useful to show only the top couple and bottom couple of candidate 
    %regions.

    %Index candidate regions by selection points from largest to smallest
    %Convert to type single to conserve memory.

    if RegionsCandidateAnyTF %if at least one region

        %Type double.
        [~, idx_regionPointsHi2Lo] = sort( RegionPoints(RegionsCandidateLinIdx), 'descend' );

        %M candidate regions x 1 column vector; type single.
        ROIDiagnostic_ROISkin_ith.RegionRankings_CandidateHi2Lo = ...
            single(idx_regionPointsHi2Lo);
    end     


    %%%%%% Record the Cr standard deviation of rejected regions %%%%%%

    %For regions rejected due to exceeding the Cr standard deviation, only Cr standard deviation 
    %information on the output video (RGB, YCbCr, and pixel-count values not displayed for these
    %regions).   

    %If at least one region rejected due to Cr SD
    if any(~ RegionSD_Cr_PassThresholdTF_LogIdx) 

        %Record index of regions rejected due to Cr SD
        %A linear index of uint16 will be used instead of a logical index because few regions are
        %expected to be rejected by this threshold. Storing a few linear indices of type uint16
        %will use less memory than holding a logical value for each region.
        %M x 1 column vector; type uint16.
        ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSDLinIdx = ...
            uint16( find(~ RegionSD_Cr_PassThresholdTF_LogIdx) );

        %Record standard deviation of regions rejected due to Cr SD
        %M x 1 column vector; type single.
        ROIDiagnostic_ROISkin_ith.RegionCrSDScores_RejectedCrSD = ...
            RegionSD_Cr(~ RegionSD_Cr_PassThresholdTF_LogIdx);
    end


    %%%%%% Record the Number of Pixels of Rejected Regions %%%%%%

    %For regions rejected due to low pixel counts, only display the pixel count information on the
    %output video (RGB and YCbCr values not displayed for these regions).
    %This is conducted to enable a cleaner display. For example, if a region is rejected due to a 
    %low pixel count, this may be the only relevant information as a low pixel count tends to  
    %predict non-skin regions well.

    if RegionsRejectedAnyTF %if at least one region
    
        %Assign number of pixels of regions to field RejectedN in ith row of nested-struct 
        %RegionNPixels.
        %Convert to type uint32 to conserve memory.
        
        RegionNPixels_RejectedN = coder.nullcopy( zeros(NRegionsRejected, 1, 'uint32') );
        
        for i = 1 : NRegionsRejected
 
            ii = RegionsRejectedLinIdx(i);

            RegionNPixels_RejectedN(i) = RegionNPixels(ii);
        end
        
        %Assign to struct
        ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedN = RegionNPixels_RejectedN;
     
        %Record TF whether rejected region was rejected because n lower than minimum:

        %This information can be used in conjuction with the pixel count data.

        if any( RegionNPixels_PassNThresholdTF_LogIdx(RegionsRejectedLinIdx) )
        
            %Assign to ith row of field RejectedLowNTF of nested-struct RegionNPixels
            %Type logical.
            ROIDiagnostic_ROISkin_ith.RegionNPixels_RejectedLowNTF = ...
                ~ RegionNPixels_PassNThresholdTF_LogIdx(RegionsRejectedLinIdx);
        end
    end
end

    
end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function [RegionsRejectedLinIdx, NRegionsRejected] = ...
             FindRejectedRegions(NRegions, RegionPassAllThresholdsTF_LogIdx)
%FindRejectedRegions   Return a linear index of rejected regions.
%
%    Note: The linear index will be in the order of least to greatest.


%Inline function
coder.inline('always');


RegionsRejectedLinIdx = coder.nullcopy( zeros(NRegions, 1, 'uint16') );

Counter = uint16(0);

for i = 1 : NRegions

    %If false value
    if ~ RegionPassAllThresholdsTF_LogIdx(i) 

        Counter = Counter + 1;

        RegionsRejectedLinIdx(Counter) = uint16(i);
    end
end   

%Trim unassigned preallocated elements
if Counter == 0
    
    RegionsRejectedLinIdx = zeros(0, 1, 'uint16');
    
else
 
    RegionsRejectedLinIdx = RegionsRejectedLinIdx(1 : Counter);
end

%Assign number of rejected regions
NRegionsRejected = Counter;


end %end local function


%=============================================================================================
function [RegionsCandidateLinIdx, NRegionsCandidate] = ...
             FindCandidateRegions(NRegions, RegionSelectedLinIdx, RegionsRejectedLinIdx, ...
                 NRegionsRejected)
%FindCandidateRegions   Return a linear index of candidate regions.
%
%    Description:
%
%    Return a linear index of candidate regions. Determine whether a region is a candidate region 
%    by determining whether the linear index of the region does not correspond to that of a 
%    selected region or a rejected region.
%
%    The linear index will be in the order of least to greatest.
%
%    Restrictions:
%
%    - RegionSelectedLinIdx must be of length 0 or 1.
%    - RegionsRejectedLinIdx must contain non-repeating values and monotonically increase.
%    - The values of RegionSelectedLinIdx and RegionsRejectedLinIdx must be mutually exclusive.
 

%Inline function
coder.inline('always');


NRejected = uint16(NRegionsRejected);    

RegionsCandidateLinIdx = coder.nullcopy( zeros(NRegions, 1, 'uint16') );

%If at least one rejected region
if NRejected ~= 0

    %If at least one region is not rejected
    if NRejected ~= NRegions
        
        LastMatch = uint16(0);

        Counter = uint16(0);

        for i = 1 : NRegions

            j = LastMatch;

            AnyMatchTF = false;

            while j < NRejected  

                j = j + 1;            

                jj = RegionsRejectedLinIdx(j);

                if i == jj

                    AnyMatchTF = true;

                    LastMatch = j;

                    break
                end
            end

            if ~ AnyMatchTF

                %If at least one selected region
                if ~ isempty(RegionSelectedLinIdx)
                
                    %If linear index is not the index of the selected region
                    if i ~= RegionSelectedLinIdx

                        Counter = Counter + 1;

                        %Add linear index as candidate linear index
                        RegionsCandidateLinIdx(Counter) = i;   
                    end
                
                %If no region was selected    
                else   
                     
                    Counter = Counter + 1;

                    %Add linear index as candidate linear index
                    RegionsCandidateLinIdx(Counter) = i;                         
                end
            end
        end

        %Trim unused preallocated elements
        if Counter == 0

            RegionsCandidateLinIdx = zeros(0, 1, 'uint16');             
            
        else
            
            RegionsCandidateLinIdx = RegionsCandidateLinIdx(1 : Counter);
        end
        
        %Assign number of candidate regions
        NRegionsCandidate = Counter;
        
    %If all regions rejected         
    else   

        RegionsCandidateLinIdx = zeros(0, 1, 'uint16');  
        
        %Assign number of candidate regions
        NRegionsCandidate = uint16(0);
    end   
    
%If no rejected regions    
else

    %If at least one selected region
    if ~ isempty(RegionSelectedLinIdx)

        %Note: length is NRegions - 1 because there can only be one selected region.
        RegionsCandidateLinIdx = coder.nullcopy( zeros(NRegions - 1, 1, 'uint16') );

        Counter = uint16(0);
        
        for i = 1 : NRegions

            if i ~= RegionSelectedLinIdx
            
                Counter = Counter + uint16(1);
                
                RegionsCandidateLinIdx(Counter) = i;    
            end            
        end 
        
        %Assign number of candidate regions
        NRegionsCandidate = Counter;        
        
    %If no region was selected
    else
        
        for i = 1 : NRegions

            RegionsCandidateLinIdx(i) = i;    
        end        
        
        %Assign number of candidate regions
        NRegionsCandidate = uint16(NRegions);
    end
end


end %end local function

