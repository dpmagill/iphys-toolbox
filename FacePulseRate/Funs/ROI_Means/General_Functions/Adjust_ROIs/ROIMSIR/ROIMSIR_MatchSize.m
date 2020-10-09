function [ROINoPrevCallsBlock, ROIMatchSizeData] = ...
             ROIMSIR_MatchSize(ROINoMods, ROINoPrevCallsBlock, HasROI_TF, ...
                 ROIBlockDetectionSkinLinIdx, NDetectionsSkin, ROIBlockDetectionFaceSkinLinIdx, ...
                 NDetectionsFaceSkin, BlockFullLinIdx, VidObjWidth, VidObjHeight, FirstReadTF, ...
                 SecondReadPostProcessingTF, FaceDetectConfig_ROIFaceSecondary1TF, ...
                 FaceDetectConfig_ROIFaceSecondary2TF, VideoReadConfig_FrameIdx_FR, ...
                 RowToReturnFullLinIdx_FR, ROIMatchSizeData, ExpectedBehaviorTestTF, FirstCallTF) 
                 %#codegen                                               
%ROIMSIR_MatchSize    Match sizes of ROIs that correspond to detections to be more consistent  
%                     across detection algorithms.
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
%    The ROIs returned across different detection algorithms systematically differ in size. For
%    example, the default primary face-detection algorithm returns an ROI about half the size of 
%    the default secondary #1 face-detection algorithm. The sizes of ROIs that correspond to  
%    detections are adjusted to be more similar to increase stability of sizes across frames. The
%    objective of increased stability is to reduce fluctuations in the ROI means from ROIs across 
%    frames, which could introduce artifacts into the pulse rate processing.
%
%    In this implementation, ROIs from detections are matched to the size of ROIs from the primary 
%    face-detection algorithm, the size of which is used because it tends to capture much of the 
%    face without permitting non-skin pixels. The size matching is implemented by multiplying the
%    size of the ROI by the ratio indicating the systematic size difference between the ROIs 
%    returned from the primary face-detection algorithm and the ROIs returned from the algorithm
%    that corresponds to the ROI. For example, the size ratio of the primary face-detection
%    algorithm to the secondary #1 face-detection algorithm might be .8 for width and .6 for  
%    height. In such a case, the width and height of an ROI returned by the secondary #1   
%    face-detection algorithm would be multiplied by .8 and .6, respectively. A ratio, rather than 
%    a fixed size, is used to permit the size of the ROI to vary based upon other factors, such as 
%    the distance between the face and the camera. As the ROI size of the primary face-detection 
%    algorithm is used as the target size, ROIs from the primary face-detection algorithm are not
%    adjusted here.
%     
%    Hypothetically, the systematic size differences between the primary face-detection algorithm 
%    and other detection algorithms might be known in advance. However, this implementation assumes
%    they are initially unknown and calculates the systematic size differences (the ratios) based 
%    on the ROI sizes it observes. The accuracy of calculating the systematic size differences 
%    may improve as more ROIs are observed; to take advantage of this, the systematic size 
%    differences are recalculated on each call to the function. The accuracy may improve as more  
%    ROIs are observed because a larger quantity of ROIs may reduce the impact of momentary   
%    influences by factors other than the systematic size difference. For example, the calculated 
%    size difference may also be due to the distance between the face and the camera if the 
%    primary face-detection algorithm happened to make more detections when the face was near the 
%    camera whereas other algorithms happened to make detections when the face was distant from the 
%    camera. As a result, the calculation will not accurately reflect only the systematic size
%    difference. As more ROIs are observed, it is anticipated that size differences due to other   
%    factors, such as distance, will cancel out to a certain extent.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.
 

%%%%%% Code generation settings %%%%%%

%Inline function
coder.inline('always');

%Call function as extrinsic
%See note where warning() is used.
coder.extrinsic('warning');

%Call function as extrinsic so that stack trace can be displayed
coder.extrinsic('error')


%%%%%% Setup %%%%%%

%Length of ROI block
BlockLength = numel(BlockFullLinIdx);


%%%%%% Take means of ROIs corresponding to detection-algorithm detections %%%%%%

%Return means from detection-algorithm detections
%Also return accumulators for use on subsequent function calls.
%Local function.
[AlgN_Pri, ROIMeanWidthPri, ROIMeanHeightPri, AlgN_Sec1, ROIMeanWidthSec1, ROIMeanHeightSec1, ...
 AlgN_Sec2, ROIMeanWidthSec2, ROIMeanHeightSec2, ROIMeanWidthSkin, ROIMeanHeightSkin, ...
 ROIMatchSizeData] = ...
    DetectionMeans(ROINoMods, HasROI_TF, BlockFullLinIdx, FirstCallTF, ROIMatchSizeData, ...
        FirstReadTF, SecondReadPostProcessingTF);
    

%%%%%% Size match face-detection ROIs in block to be more similar across face-detection algorithms %%%%%%

%Note: used during the first read or during the second read in the pre-processing (but not  
%post-processing) step. During the second read pre-processing step, size match ROIs near the 
%beginning of the video that were not size matched during the first read. The second read does not 
%use the face-detection algorithm(s), so size matching is not needed during the second read 
%post-processing step. 

if FirstReadTF ||               ... first read
   ~ SecondReadPostProcessingTF %   second read pre-processing step 
 
    %%%%%% --- Match the size of secondary. #1 alg. ROIs in block to size of primary alg. ROIs %%%%%%   
                 
    if FaceDetectConfig_ROIFaceSecondary1TF && ... if sec. #1 alg. enabled
       any( HasROI_TF.FaceSecondary1(BlockFullLinIdx) ) && ... if any sec. #1 alg. detections in block
       AlgN_Pri  > 5 && ... min sample for better ratio determination
       AlgN_Sec1 > 5    %   min sample for better ratio determination       
       
        %Determine size ratio of primary alg. to secondary #1 alg
        WidthRatio_Single  = ROIMeanWidthPri / ROIMeanWidthSec1;
        HeightRatio_Single = ROIMeanHeightPri / ROIMeanHeightSec1;

        %Logical index of secondary #1 algorithm detections within ROI block
        Secondary1BlockDetectionTFLogIdx = HasROI_TF.FaceSecondary1(BlockFullLinIdx);
   
        %Loop across elements of ROIs where a detection was made by the secondary #1 algorithm
        for i = 1 : BlockLength
        
            %Where an ROI corresponds to the detection algorithm
            if Secondary1BlockDetectionTFLogIdx(i)
 
                %Match ROI widths and heights of ROIs from secondary #1 algorithm:
                
                %Extract width and height of ith ROI
                Width_ith  = ROINoPrevCallsBlock(i, 3);
                Height_ith = ROINoPrevCallsBlock(i, 4);
                
                %Adjust size by primary-to-secondary #1 ROI width ratio
                %Cast to floating point type during calculation
                WidthNew_ith = int16( single( Width_ith ) * WidthRatio_Single );
                                       
                %Adjust size by primary-to-secondary #1 ROI height ratio
                %Cast to floating point type during calculation
                HeightNew_ith = int16( single( Height_ith ) * HeightRatio_Single );
                                      
                %Reassign
                ROINoPrevCallsBlock(i, 3) = WidthNew_ith;
                ROINoPrevCallsBlock(i, 4) = HeightNew_ith;
                
                %Adjust X- and Y-coordinates to correspond to adjustments in widths and heights:

                %Half of difference between unmatched widths and height and adjusted widths and 
                %heights.
                %Optimize division by two by bit-wise operation.
                WidthHalfDiff_ith  = bitshift(Width_ith  - WidthNew_ith,  -1);
                HeightHalfDiff_ith = bitshift(Height_ith - HeightNew_ith, -1);
                
                %Add the half-differences to the X- and Y-coordinates
                %Note: if there were negative differences, the half-differences will be subtracted 
                %from the X- and Y-coordinates.
                ROINoPrevCallsBlock(i, 1) = ROINoPrevCallsBlock(i, 1) + WidthHalfDiff_ith;
                ROINoPrevCallsBlock(i, 2) = ROINoPrevCallsBlock(i, 2) + HeightHalfDiff_ith;                                            
            end
        end
    end

    %%%%%% --- Match the size of secondary. #2 alg. ROIs in block to size of primary alg. ROIs %%%%%%    
                 
    if FaceDetectConfig_ROIFaceSecondary2TF && ... if sec. #2 alg. enabled
       any( HasROI_TF.FaceSecondary2(BlockFullLinIdx) ) && ... if any sec. #2 alg. detections in block
       AlgN_Pri  > 5 && ... min sample for better ratio determination
       AlgN_Sec2 > 5    %   min sample for better ratio determination       
       
        %Determine size ratio of primary alg. to secondary #2 alg
        WidthRatio_Single  = ROIMeanWidthPri / ROIMeanWidthSec2;
        HeightRatio_Single = ROIMeanHeightPri / ROIMeanHeightSec2;

        %Logical index of secondary #2 algorithm detections within ROI block
        Secondary2BlockDetectionTFLogIdx = HasROI_TF.FaceSecondary2(BlockFullLinIdx);
        
        %Loop across elements of ROIs where a detection was made by the secondary #1 algorithm
        for i = 1 : BlockLength
        
            %Where an ROI corresponds to the detection algorithm
            if Secondary2BlockDetectionTFLogIdx(i)
 
                %Match ROI widths and heights of ROIs from secondary #2 algorithm:
                
                %Extract width and height of ith ROI
                Width_ith  = ROINoPrevCallsBlock(i, 3);
                Height_ith = ROINoPrevCallsBlock(i, 4);
                
                %Adjust size by primary-to-secondary #2 ROI width ratio
                %Cast to floating point type during calculation
                WidthNew_ith = int16( single( Width_ith ) * WidthRatio_Single );                      
                
                %Adjust size by primary-to-secondary #2 ROI height ratio
                %Cast to floating point type during calculation
                HeightNew_ith = int16( single( Height_ith ) * HeightRatio_Single );
                                     
                %Reassign
                ROINoPrevCallsBlock(i, 3) = WidthNew_ith;
                ROINoPrevCallsBlock(i, 4) = HeightNew_ith;
                
                %Adjust X- and Y-coordinates to correspond to adjustments in widths and heights:

                %Half of difference between unmatched widths and height and adjusted widths and 
                %heights.
                %Optimize division by two by bit-wise operation.
                WidthHalfDiff_ith  = bitshift(Width_ith  - WidthNew_ith,  -1);
                HeightHalfDiff_ith = bitshift(Height_ith - HeightNew_ith, -1);
                
                %Add the half-differences to the X- and Y-coordinates
                %Note: if there were negative differences, the half-differences will be subtracted 
                %from the X- and Y-coordinates.
                ROINoPrevCallsBlock(i, 1) = ROINoPrevCallsBlock(i, 1) + WidthHalfDiff_ith;
                ROINoPrevCallsBlock(i, 2) = ROINoPrevCallsBlock(i, 2) + HeightHalfDiff_ith;                                            
            end
        end        
    end 
end %end if output is one row


%%%%%% Match the size of skin-detection ROIs to the size of face-detection ROIs %%%%%%

%Note: used during all calls.
%During the second read pre-processing step, size match ROIs near the beginning of the video
%that were not size matched during the first read. During the second read post-processing step,
%size match ROIs near the beginning of the video based on recent skin-detection algorithm
%ROI detections. 

%If at least one skin-detection algorithm detection within block; no matching needed if no 
%detections within block.
%Also, at least two face-detection algorithm detections from which to make size match.
if NDetectionsSkin ~= 0 && ... 
   (AlgN_Pri > 1 || AlgN_Sec1 > 1 || AlgN_Sec2 > 1)
                
    %Use the ROIs from a face-detection algorithm as the basis of ROIs sizes for the ROIs from the
    %skin-detection algorithms. Use ROIs only from the primary face-detection algorithm if 
    %available. Otherwise, use ROIs only from the secondary #1 face-detection algorithm if 
    %available; otherwise, use ROIs from the secondary #2 face-detection algorithm. If ROI not
    %available from any face-detection algorithm, skip skin-detection ROI size adjustment.
 
    %Match widths and heights:
    
    %Use primary algorithm mean ROI size as basis for skin-detection ROI size
    if AlgN_Pri > 1 

        %Use primary algorithm as mean face-detection ROI size
        ROIMeanWidthFace  = ROIMeanWidthPri; 
        ROIMeanHeightFace = ROIMeanHeightPri;
        
    %Use secondary #1 algorithm mean ROI size as basis for skin-detection ROI size
    elseif AlgN_Sec1 > 1 

        %Use secondary #1 algorithm as mean face-detection ROI size
        ROIMeanWidthFace  = ROIMeanWidthSec1; 
        ROIMeanHeightFace = ROIMeanHeightSec1; 
        
    %Use secondary #2 algorithm mean ROI size as basis for skin-detection ROI size
    else 

        %Use secondary #2 algorithm as mean face-detection ROI size
        ROIMeanWidthFace  = ROIMeanWidthSec2; 
        ROIMeanHeightFace = ROIMeanHeightSec2;  
    end     
   
    %Determine face-to-skin size ratio 
    WidthRatio_Single  = ROIMeanWidthFace / ROIMeanWidthSkin;
    HeightRatio_Single = ROIMeanHeightFace / ROIMeanHeightSkin;
    
    %Match ROI size of ROIs from skin-detection algorithm:    
    
    %Loop across elements of ROIs where a detection was made by the skin-detection algorithm
    for i = 1 : NDetectionsSkin

        %Where an ROI corresponds to the detection algorithm
        ii = ROIBlockDetectionSkinLinIdx(i);

        %Match ROI widths and heights of ROIs from skin-detection algorithm:

        %Extract width and height of ith ROI
        Width_ith  = ROINoPrevCallsBlock(ii, 3);
        Height_ith = ROINoPrevCallsBlock(ii, 4);

        %Adjust size by face-to-skin ROI width ratio
        %Cast to floating point type during calculation
        WidthNew_ith = int16( single( Width_ith ) * WidthRatio_Single );                      

        %Adjust size by face-to-skin ROI height ratio
        %Cast to floating point type during calculation
        HeightNew_ith = int16( single( Height_ith ) * HeightRatio_Single );

        %Reassign
        ROINoPrevCallsBlock(ii, 3) = WidthNew_ith;
        ROINoPrevCallsBlock(ii, 4) = HeightNew_ith;

        %Adjust X- and Y-coordinates to correspond to adjustments in widths and heights:

        %Half of difference between unmatched widths and height and adjusted widths and 
        %heights.
        %Optimize division by two by bit-wise operation.
        WidthHalfDiff_ith  = bitshift(Width_ith  - WidthNew_ith,  -1);
        HeightHalfDiff_ith = bitshift(Height_ith - HeightNew_ith, -1);

        %Add the half-differences to the X- and Y-coordinates
        %Note: if there were negative differences, the half-differences will be subtracted 
        %from the X- and Y-coordinates.
        ROINoPrevCallsBlock(ii, 1) = ROINoPrevCallsBlock(ii, 1) + WidthHalfDiff_ith;
        ROINoPrevCallsBlock(ii, 2) = ROINoPrevCallsBlock(ii, 2) + HeightHalfDiff_ith;                                            
    end  
end
 

%%%%%% Adjust ROI(s) that exceed frame dimensions %%%%%%   

%Although ROI(s) are also checked later in function ROIMSIR, check here as well so that any
%overshoots from size matching don't affect the detection-smoothing operations in function 
%ROIMSIR_DetectionSmooth, which occurs before the check by ROIMSIR. Also, before the check by   
%ROIMSIR, ROIs returned here will influence variable ROIOutBeforeFrameByFrameSmoothing_FR or
%ROIOutBeforeFrameByFrameSmoothing_SR (assigned in function ROIMSIR), and this variable needs to be  
%within frame dimensions for later use in function WriteFaceVideo. 
   
%Adjust any coordinates that exceed frame dimensions
%M x 4 matrix (229 x 4 during first-read operations); type int16.
%Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder 'FacePulseRate'.
ROINoPrevCallsBlock(ROIBlockDetectionFaceSkinLinIdx, :) = ...
    ROIAdjustIfExceedsFrameDims( ...
        ROINoPrevCallsBlock(ROIBlockDetectionFaceSkinLinIdx, :), ...
        VidObjWidth, ...
        VidObjHeight ...
    );       
  

%%%%%% Output validation %%%%%%

%First-read operations
if FirstReadTF

    %Check whether any ROI value is zero
    %The operations of this function were intended to prevent values of zero, so such a value is
    %likely due to an implementation error in this function.
    
    %Loop across columns
    for i = int32(1) : 4
 
        %Loop across ROIs rows that correspond to ROIs modified in the current function
        for j = 1 : NDetectionsFaceSkin

            jj = ROIBlockDetectionFaceSkinLinIdx(j);
                      
            if ROINoPrevCallsBlock(jj, i) == 0 

                %Throw error
                %Called as extrinsic so that stack trace can be displayed.
                error( ...
                    'Component:InternalError', ...
                    ['Internal Error (ROIMSIR, code 6): ROI-modification operations assigned', ...
                     ' a value of zero for an ROI. ROI accuracy may be affected. The frame', ...
                     ' index of corresponding frame is: ', ...
                     sprintf( '%d', ...
                         int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ...
                     ), ... 
                     '. Detected within function ROIMSIR in function ROIMSIR_MatchSize.'] ...                                 
                );                       
            end
        end       
    end               

    %Check whether the ROI size is unreasonably small
    %Such a small size is likely due to an implementation error in this function.
    %This check is intended to be run when testing new implementations, as small ROI sizes are an
    %indication of a implementation error. As occassional values below 20 may be considered
    %acceptable, this check is not intended for use outside of testing. "Occassional" in this case   
    %might be defined as a few occurances out of 10,000. Flag ExpectedBehaviorTestTF enables the
    %check.    
    if ExpectedBehaviorTestTF && ...
       any( ROINoPrevCallsBlock(ROIBlockDetectionFaceSkinLinIdx, 3 : 4) < 20, 'all' )
        
        %Note: function warning() not available for code generation; so it must have previously
        %been declared as extrinsic.
        %Function fprintf can not be used as a substitute for warning() in this case because 
        %fprintf can not accept variable-length arguments.   
        warning( ...
            'Component:InternalError', ...
            ['Potential Internal Error (ROIMSIR, code 7): ROI-modification operations assigned', ...
             ' a size value for an ROI that is below 20 pixels, which is likely inaccurate.', ...
             ' ROI accuracy may be affected. The frame index of corresponding frame is: ',  ...
             sprintf( '%d', int32(VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR)) ), ... 
             '. Detected within function ROIMSIR in function', ...
             ' ROIMSIR_MatchSize.'] ...
        );          
    end 

%Second-read operations    
else
   
    %Check whether any ROI value is zero
    %The operations of this function were intended to prevent values of zero, so such a value is
    %likely due to an implementation error in this function. 
    
    %Loop across columns
    for i = 1 : 4
 
        %Loop across ROIs rows that correspond to ROIs modified in the current function
        for j = 1 : NDetectionsFaceSkin

            jj = ROIBlockDetectionFaceSkinLinIdx(j);
            
            if ROINoPrevCallsBlock(jj, i) == 0
                
                     %Throw exception
                %Called as extrinsic so that stack trace can be displayed.
                %Note: '%.0f' = floating point with no decimals.
                error( ...
                    'Component:InternalError', ...
                    ['Internal Error (ROIMSIR, code 8): Size-matching operations assigned a', ...
                     ' value of zero for an ROI. ROI accuracy may be affected. The error', ...
                     ' occurred during the second-read operations. Detected within function', ...
                     ' ROIMSIR in function ROIMSIR_MatchSize.'] ...              
                );                       
            end
        end       
    end    

    %Check whether the ROI size is unreasonably small
    %Such a small size is likely due to an implementation error in this function.
    %This check is intended to be run when testing new implementations, as small ROI sizes are an
    %indication of a implementation error. As occassional values below 20 may be considered
    %acceptable, this check is not intended for use outside of testing. "Occassional" in this case   
    %might be defined as a few occurances out of 10,000. Flag ExpectedBehaviorTestTF enables the
    %check.    
    if ExpectedBehaviorTestTF && ...
       any( ROINoPrevCallsBlock(ROIBlockDetectionFaceSkinLinIdx, 3 : 4) < 20, 'all' )

        %Display warning
        %Note: function warning() not available for code generation, so it must have previously
        %been declared as extrinsic.
        warning( ...
            'Component:InternalError', ...
            ['Potential Internal Error (ROIMSIR, code 9): ROI-modification operations', ...
             ' assigned a size value for an ROI that is below 20 pixels, which is likely ', ...
             ' inaccurate. ROI accuracy may be affected. Occurred during the second-read', ... 
             ' operations. Detected within function ROIMSIR in function ROIMSIR_MatchSize.'] ...
        );             
    end     
end
    

end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function [AlgN_Pri, ROIMeanWidthPri,  ROIMeanHeightPri, AlgN_Sec1, ROIMeanWidthSec1, ...
          ROIMeanHeightSec1, AlgN_Sec2, ROIMeanWidthSec2, ROIMeanHeightSec2, ROIMeanWidthSkin, ...
          ROIMeanHeightSkin, MatchSizeData] = ...
              DetectionMeans(ROINoMods, HasROI_TF, BlockFullLinIdx, FirstCallTF, MatchSizeData, ...
                  FirstReadTF, SecondReadPostProcessingTF)                 
%DetectionMeans   Take means of ROIs corresponding to detection-algorithm detections.

              
%Inline function
coder.inline('always');


%%%%%% Take means over a range of frames %%%%%%

%If first call to function or if called within post-processing second-read operations
%Note: the first call to function always occurs during the first-read operations.
%Note: in the pre-processing second-read operations, no new detections will be encountered, so this
%loop does not need to be run. In the post-processing second-read operations, the new detections
%are skin detections from frame 1 until the length of BlockFullLinIdx.
if FirstCallTF || SecondReadPostProcessingTF        
    
    IdxEnd = BlockFullLinIdx(end);
        
    %Loop across ROI rows
    for i = 1 : IdxEnd  

        %%%%%% --- First-call operations %%%%%%

        %If called during the first call to the function
        if FirstCallTF         
        
            %If detection from primary algorithm
            if HasROI_TF.FacePrimary(i) 

               %Cast to floating-point type and accumulate width sum 
               MatchSizeData.SumW_Pri = MatchSizeData.SumW_Pri + single( ROINoMods(i, 3) );

               %Cast to floating-point type and accumulate height sum 
               MatchSizeData.SumH_Pri = MatchSizeData.SumH_Pri + single( ROINoMods(i, 4) ); 

               %Detection count
               MatchSizeData.AlgN_Pri = MatchSizeData.AlgN_Pri + 1;

               %Mean width from primary algorithm
               MatchSizeData.ROIMeanWidthPri = MatchSizeData.SumW_Pri / MatchSizeData.AlgN_Pri;

               %Mean height from primary algorithm
               MatchSizeData.ROIMeanHeightPri = MatchSizeData.SumH_Pri / MatchSizeData.AlgN_Pri;
            end  

            %If detection from secondary #1 algorithm
            if HasROI_TF.FaceSecondary1(i) 

                %Cast to floating-point type and accumulate width sum
                MatchSizeData.SumW_Sec1 = MatchSizeData.SumW_Sec1 + single( ROINoMods(i, 3) );

                %Cast to floating-point type and accumulate height sum
                MatchSizeData.SumH_Sec1 = MatchSizeData.SumH_Sec1 + single( ROINoMods(i, 4) );  

                %Detection count
                MatchSizeData.AlgN_Sec1 = MatchSizeData.AlgN_Sec1 + 1;

                %Mean ROI width from secondary #1 algorithm
                MatchSizeData.ROIMeanWidthSec1 = MatchSizeData.SumW_Sec1 / MatchSizeData.AlgN_Sec1;

                %Mean ROI height from secondary #1 algorithm
                MatchSizeData.ROIMeanHeightSec1 = MatchSizeData.SumH_Sec1 / MatchSizeData.AlgN_Sec1;           
            end               

            %If detection from secondary #1 algorithm
            if HasROI_TF.FaceSecondary2(i) 

                %Cast to floating-point type and accumulate width sum 
                MatchSizeData.SumW_Sec2 = MatchSizeData.SumW_Sec2 + single( ROINoMods(i, 3) );

                %Cast to floating-point type and accumulate height sum
                MatchSizeData.SumH_Sec2 = MatchSizeData.SumH_Sec2 + single( ROINoMods(i, 4) );  

                %Detection count
                MatchSizeData.AlgN_Sec2 = MatchSizeData.AlgN_Sec2 + 1;

                %Mean ROI width from secondary #2 algorithm
                MatchSizeData.ROIMeanWidthSec2 = MatchSizeData.SumW_Sec2 / MatchSizeData.AlgN_Sec2;

                %Mean ROI height from secondary #2 algorithm
                MatchSizeData.ROIMeanHeightSec2 = MatchSizeData.SumH_Sec2 / MatchSizeData.AlgN_Sec2;           
            end              
        end
        
        %%%%%% --- First-call or second-read post-processing operations %%%%%%         
        
        if FirstCallTF || SecondReadPostProcessingTF
                        
            %If detection from skin algorithm
            if HasROI_TF.Skin(i) 

                %Cast to floating-point type and accumulate width sum 
                MatchSizeData.SumW_Skin = MatchSizeData.SumW_Skin + single( ROINoMods(i, 3) );

                %Cast to floating-point type and accumulate height sum
                MatchSizeData.SumH_Skin = MatchSizeData.SumH_Skin + single( ROINoMods(i, 4) );  

                %Detection count
                MatchSizeData.AlgN_Skin = MatchSizeData.AlgN_Skin + 1;

                %Mean ROI width from skin algorithm
                MatchSizeData.ROIMeanWidthSkin = MatchSizeData.SumW_Skin / MatchSizeData.AlgN_Skin;

                %Mean ROI height from skin algorithm
                MatchSizeData.ROIMeanHeightSkin = MatchSizeData.SumH_Skin / MatchSizeData.AlgN_Skin;           
            end 
        end
    end
 
    
%%%%%% Take means by addition of one frame %%%%%%    
    
%If during the first-read operations (other than the first call to the function)
elseif FirstReadTF

    %Index of last frame that has been read
    LastIdx = BlockFullLinIdx(end);

    if HasROI_TF.FacePrimary(LastIdx)

        %Cast to floating-point type and accumulate width sum 
        MatchSizeData.SumW_Pri = MatchSizeData.SumW_Pri + single( ROINoMods(LastIdx, 3) );

        %Cast to floating-point type and accumulate height sum 
        MatchSizeData.SumH_Pri = MatchSizeData.SumH_Pri + single( ROINoMods(LastIdx, 4) );

        %Increase count
        MatchSizeData.AlgN_Pri = MatchSizeData.AlgN_Pri + 1;

        %Mean width from primary algorithm
        MatchSizeData.ROIMeanWidthPri = MatchSizeData.SumW_Pri / MatchSizeData.AlgN_Pri;

        %Mean height from primary algorithm
        MatchSizeData.ROIMeanHeightPri = MatchSizeData.SumH_Pri / MatchSizeData.AlgN_Pri;        
    end

    if HasROI_TF.FaceSecondary1(LastIdx)

        %Cast to floating-point type and accumulate width sum 
        MatchSizeData.SumW_Sec1 = MatchSizeData.SumW_Sec1 + single( ROINoMods(LastIdx, 3) );

        %Cast to floating-point type and accumulate height sum 
        MatchSizeData.SumH_Sec1 = MatchSizeData.SumH_Sec1 + single( ROINoMods(LastIdx, 4) );

        %Increase count
        MatchSizeData.AlgN_Sec1 = MatchSizeData.AlgN_Sec1 + 1;

        %Mean ROI width from secondary #1 algorithm
        MatchSizeData.ROIMeanWidthSec1 = MatchSizeData.SumW_Sec1 / MatchSizeData.AlgN_Sec1;

        %Mean ROI height from secondary #1 algorithm
        MatchSizeData.ROIMeanHeightSec1 = MatchSizeData.SumH_Sec1 / MatchSizeData.AlgN_Sec1;         
    end    

    if HasROI_TF.FaceSecondary2(LastIdx)

        %Cast to floating-point type and accumulate width sum 
        MatchSizeData.SumW_Sec2 = MatchSizeData.SumW_Sec2 + single( ROINoMods(LastIdx, 3) );

        %Cast to floating-point type and accumulate height sum 
        MatchSizeData.SumH_Sec2 = MatchSizeData.SumH_Sec2 + single( ROINoMods(LastIdx, 4) );

        %Increase count
        MatchSizeData.AlgN_Sec2 = MatchSizeData.AlgN_Sec2 + 1;

        %Mean ROI width from secondary #2 algorithm
        MatchSizeData.ROIMeanWidthSec2 = MatchSizeData.SumW_Sec2 / MatchSizeData.AlgN_Sec2;

        %Mean ROI height from secondary #2 algorithm
        MatchSizeData.ROIMeanHeightSec2 = MatchSizeData.SumH_Sec2 / MatchSizeData.AlgN_Sec2;        
    end        
    
    if HasROI_TF.Skin(LastIdx)

        %Cast to floating-point type and accumulate width sum 
        MatchSizeData.SumW_Skin = MatchSizeData.SumW_Skin + single( ROINoMods(LastIdx, 3) );

        %Cast to floating-point type and accumulate height sum 
        MatchSizeData.SumH_Skin = MatchSizeData.SumH_Skin + single( ROINoMods(LastIdx, 4) );
       
        %Increase count
        MatchSizeData.AlgN_Skin = MatchSizeData.AlgN_Skin + 1;
        
        %Mean ROI width from skin algorithm
        MatchSizeData.ROIMeanWidthSkin = MatchSizeData.SumW_Skin / MatchSizeData.AlgN_Skin;

        %Mean ROI height from skin algorithm
        MatchSizeData.ROIMeanHeightSkin = MatchSizeData.SumH_Skin / MatchSizeData.AlgN_Skin;        
    end            
end  


%%%%%% Assign for use in function ROIMSIR_MatchSize %%%%%%
 
AlgN_Pri          = MatchSizeData.AlgN_Pri;
ROIMeanWidthPri   = MatchSizeData.ROIMeanWidthPri; 
ROIMeanHeightPri  = MatchSizeData.ROIMeanHeightPri;
AlgN_Sec1         = MatchSizeData.AlgN_Sec1;
ROIMeanWidthSec1  = MatchSizeData.ROIMeanWidthSec1;
ROIMeanHeightSec1 = MatchSizeData.ROIMeanHeightSec1; 
AlgN_Sec2         = MatchSizeData.AlgN_Sec2;
ROIMeanWidthSec2  = MatchSizeData.ROIMeanWidthSec2;
ROIMeanHeightSec2 = MatchSizeData.ROIMeanHeightSec2;
ROIMeanWidthSkin  = MatchSizeData.ROIMeanWidthSkin;
ROIMeanHeightSkin = MatchSizeData.ROIMeanHeightSkin;


end %end local function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Note: this function is not currently used as a compiled function as it is nested within a
%compiled function, ROIMSIR_mex.

%Code-generation and build script used to generate C-language code and create the compiled version 
%(ROIMSIR_MatchSize_mex) of the function.

%{
                

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%Specify struct variable-size element properties
Element1 = ...
    coder.typeof(false(500, 1), ... example code
                 [inf, 1],      ... upper bounds
                 [1, 0]         ... variable size (T/F)
    );

HasROI_TFCode = ...
    struct( ...
        'ByAnyMethod',                      Element1, ...   
        'FacePrimary',                      Element1, ...
        'FacePrimaryAttempted',             Element1, ...
        'FaceSecondary1',                   Element1, ...
        'FaceSecondary1Attempted',          Element1, ...
        'FaceSecondary2',                   Element1, ...
        'FaceSecondary2Attempted',          Element1, ...
        'Skipped',                          Element1, ...
        'Skin',                             Element1, ...
        'SkinAttempted',                    Element1, ...
        'Interpolated',                     Element1, ...
        'AdjustedBecauseLowSkinProportion', Element1, ...
        'ROISpecifiedByArgument',           Element1, ...
        'ROIIgnoreByArgument',              Element1 ...
    );

%                                                     Example Code                 Upp. Bounds  Var. Size (T/F)  Type
ROINoModsCode                         = coder.typeof( zeros(500, 4, 'int16'),      [inf, 4],    [1, 0] );        %int16
ROINoPrevCallsBlockCode               = coder.typeof( zeros(500, 4, 'int16'),      [inf, 4],    [1, 0] );        %int16
BlockFullLinIdxCode                   = coder.typeof( zeros(1, 500, 'uint32'),     [1, inf],    [0, 1] );        %int32
ROIBlockDetectionSkinLogIdxCode       = coder.typeof( false(500, 1),               [inf, 1],    [1, 0] );        %logical
ROIBlockDetectionFaceSkinLogIdxCode   = coder.typeof( false(500, 1),               [inf, 1],    [1, 0] );        %logical 
VideoReadConfig_FrameIdxCode          = coder.typeof( zeros(1, 500, 'uint32'),     [1, inf],    [0, 1] );        %int32 
                 

%%%%%% Specify fixed-size input arguments %%%%%%

VidObjWidthCode                          = int16(0);         
VidObjHeightCode                         = int16(0);
FirstReadTFCode                          = false;
SecondReadPostProcessingTFCode           = false;
RowToReturnFullLinIdxCode                = int32(0);
FaceDetectConfig_ROIFaceSecondary1TFCode = false;
FaceDetectConfig_ROIFaceSecondary2TFCode = false;


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

%Argument buildInfo: this variable is assign by the caller (the codegen command executed 
%below) and is not present in the base workspace.

%Second argument: specify a cell array of compiler-specific flags, where each flag is a 
%character vector. As function setbuildargs will be evaluated from text, use double ' quotes for 
%each character vector to maintain the charater vector,
%e.g., {''-Ofast'' ''-fsingle-precision-constant''}.

setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})';

%Assign to code-generation configuration object
cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen ROIMSIR_MatchSize.m -config cfg -args {ROINoModsCode, ROINoPrevCallsBlockCode, HasROI_TFCode, ROIBlockDetectionSkinLogIdxCode, ROIBlockDetectionFaceSkinLogIdxCode, BlockFullLinIdxCode, VidObjWidthCode, VidObjHeightCode, FirstReadTFCode, SecondReadPostProcessingTFCode, FaceDetectConfig_ROIFaceSecondary1TFCode, FaceDetectConfig_ROIFaceSecondary2TFCode, VideoReadConfig_FrameIdxCode, RowToReturnFullLinIdxCode}
             
%}



 
                 
                 
                 