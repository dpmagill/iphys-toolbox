function [UseBoundingBoxFaceTF, BoundingBoxFace, SkinBBoxAvailableTF, BoundingBoxSkin, ...
          ROIForBoundingBoxSkin, IncreaseSkinBBoxFactorStartIdx] = ...
             ROIMeans_FirstRead_SetBoundingBoxes(i, ROIForBBox, HasROI_TF, FaceDetectConfig, ...
                 SkinDetectConfig, ROIGeneralConfig, VideoReadConfig, SetBoundingBoxes_DiffMax, ...
                 IncreaseSkinBBoxFactorStartIdx)                                                                
%ROIMeans_FirstRead_SetBoundingBoxes   Determine the size and position of bounding boxes used for 
%                                      face-detection algorithm(s) and the skin-detection 
%                                      algorithm.
%                                    
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead.
%      
%
%    Description
%    -----------
%
%    Ideally, a bounding box for a given frame should be large enough to capture the face at all 
%    times, which will allow a detection to be made by an algorithm. However, there are at least 
%    two benefits to restricting the size of the bounding box to be only somewhat larger than the  
%    anticipated position and size of the face. The first benefit to restricting the size is a  
%    reduction of processing time. Specifically, the bounding box determines the portion of the   
%    frame that the algorithms scan, and it has been observed that the size of the frame to be 
%    scanned is among the largest contributers to the execution time of the algorithms. The second 
%    benefit to restricting the size is a reduction of false positives if the bounding box can be  
%    positioned in an area of the frame most likely to contain the face. 
%
%    Regarding the processing time benefit of reducing the size of the bounding box, the overall 
%    execution time across algorithms may increase if the size of the bounding box is reduced such
%    that one or more algorithms are not able to make a detection. This is because more than one 
%    algorithm will then need to be used to scan the area until a detection is made or no 
%    algorithms remain as different algorithms are applied until a detection is found. Also, if   
%    repeated detection attemps are unsuccessful because the box is too small for detections to be 
%    made, the method the current function uses to set the bounding box will increase the bounding
%    box size in response, which can increase execution time as well.
%
%    -- Algorithm --
%
%    In the current function, an algorithm is used to attempt to reduce the size of the bounding  
%    box while having its size and position favorable to accurate face or skin detections. For a      
%    given frame, when the bounding box is set, the position of the head is only known for previous 
%    frames but not the current frame. The algorithm takes into account the size of previous face-
%    detection ROIs and apparent movement of the ROIs across previous frames to predict the size 
%    and position of the bounding box. Only ROIs from face detections, rather than skin detections,
%    are used because face detections are generally more accurate.
%      
%    The position and size of the bounding box for the ith frame are determined based on the number 
%    of previous face detections within a specified number of frames back and the position and size 
%    of the corresponding ROIs. The number of previous face detections within the specified number 
%    of frames  back determines whether a bounding box will be used and how large the bounding box 
%    will be. If no face detections are present within the specified number of frames back, no
%    bounding box will be used. If face detection(s) are present, a smaller number of detections 
%    results in a larger bounding box.     
%
%    -- Algorithm procedure --
%
%    First, determine how many frames back the last face detection occurred. If the number 
%    of frames back is under the threshold ROIFace_BoundingBoxGrowthThreshold_adjusted, use the   
%    bounding box size specified by ROIFace_InitialBoundingBoxScale. If no face detections are   
%    found within this number of frames back, enlarge the bounding box according to a growth  
%    factor, ROIFace_BoundingBoxGrowthRate_adj, multipled by the number of frames between the last 
%    face detection and ROIFace_BoundingBoxGrowthThreshold_adj. 
%
%    Finally, use ROIForBBox rather than ROI as a basis for determining size. ROIForBBox is the 
%    result of any size adjustments specified by ROIFace_ChangeFactorROIPrimary,  
%    ROIFace_ChangeFactorROISecondary1, or ROIFace_ChangeFactorROISecondary2. ROIForBBox differs
%    from ROI because the ROI sizes have been adjusted to increase size similarity across different
%    face-detection algorithm detections. 
%
%    -- Background on use of ROIForBBox --
%
%    The sizes of the ROIs returned by a face-detection algorithm can be idoiosyncratic to  
%    the specific algorithm; for example, the typical size of the ROI from the primary 
%    face-detection algorithm can differ from the typical size of the ROI from the secondary #1 
%    face-detection algorithm. This size difference can affect computational speed. Computational   
%    speed is affected because the ROI sizes of the last few frames back from the current frame are 
%    used to determine the bounding box size of the current frame. 
%     
%    Performance is affected in two ways. First, if the last few frames get detections from a 
%    face-detection algorithm that returns smaller detections than other face-detection algorithms, 
%    the bounding box for the current frame may be two small for the other algorithms to make 
%    detections because the bounding box conformed to the sizes of the most recent ROIs. Second, if 
%    the last few frames get detections from an algorithm that returns larger detections than other 
%    algorithms, the bounding box will be of sufficient size for the other algorithms to make 
%    detections, but it may be larger than needed, resulting in greater computational time.
%    
%    To address the effect of ROI size differences on the bounding box size, the ROIs are adjusted
%    to be more similar across face-detection algorithms. These adjustments are only used for 
%    determining the bounding box size: the adjustments are assigned to ROIForBBox rather than the 
%    ROI matrix. An alternative to this procedure would be to vary the bounding box size for each 
%    face-detection algorithm within a given frame rather than adjusting the ROIs that determine 
%    the bounding box size; however, this is not implemented because varying the bounding box size 
%    for each algorithm entails assigning multiple bounding boxes within each frame, which would 
%    require increased computational time from recropping and conversion to grayscale. This 
%    alternative is mentioned to clarify that the procedure currently implemented adjusts the ROIs   
%    that determine the bounding box; it does not alter the bounding box size such that the   
%    bounding box size differs across algorithms.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Input validation %%%%%%

%Must be an integer type because no rounding is conducted.
%Should be type int16 because the function is implemented to assign values of this type.
%A non-matching type would be due to an implementation error.
assert( isa(ROIForBBox(1, 1), 'int16') );


%%%%%% Extract values from struct %%%%%%

%Type int32.
ROIFace_BoundingBoxGrowthThreshold_adjusted = FaceDetectConfig.BoundingBoxGrowthThreshold_adjusted;

%Type double.
ROIFace_BoundingBoxEnlargementFactor = FaceDetectConfig.ROIFace_BoundingBoxEnlargementFactor;


%%%%%% Proceed if minimum number of frames has elapsed %%%%%%

if i > ROIFace_BoundingBoxGrowthThreshold_adjusted          

    
    %%%%%% Determine the linear indices of nearby frames with face-detection algorithm detections %%%%%%
    
    %Linear indices of up to the last five detections within a specified range 
    %The range is is bounded by NFramesBackToSearch.
    %The first five detections are used to determine the initial dimensions of the bounding box. At 
    %least five detections are used to attempt to reduce the effect of outlier ROIs. Not more than
    %five detections are used to allow the bounding box to be responsive to face movement.
    
    %Index of nearest detection(s)
    %Specify type int32 for protection against floating-point gaps.    
    NearbyDetectionsLinIdx = ...
        int32( ... 
            find( ...
                HasROI_TF.FacePrimary    | ...
                HasROI_TF.FaceSecondary1 | ...
                HasROI_TF.FaceSecondary2,  ...
                5,     ... find up to 5 linear indices where detections are present
                'last' ... start at the frame closest to the current frame 
            ) ...
        ); 
      
    
    %%%%%% Proceed if at least five face-detection algorithm detections were found %%%%%%
    
    %At least five face-detection algorithm detections exist between the beginning of the video and
    %the current frame.
    %At least five detections are required for either setting a bounding box.
    %Note: there can be no more than 5 detections because the find function used previously was set
    %only to return up to 5 detections.
    if numel(NearbyDetectionsLinIdx) == 5
     
        MinDetectionsAvailableTF = true;
        

        %%%%%% Use extrapolation to predict the location of the ROI for the ith frame %%%%%%
       
        %Note: for efficiency, function interp1_Linear_mex has been set to a accept a maximum 
        %length of 50 for variable MaxFrameBackForExtrapLinIdx. If the length of the variable is 
        %modified to be longer, then the length accepted by function interp1_Linear should also be 
        %modified and the function recompiled.
        
        %Max number of frames back from current frame that should be used for extrapolation
        %Otherwise, extrapolation may not be meaningful.
        %Note: 51 set as maximum to guard against length greater than 50 for function 
        %interp1_Linear; see note above.
        MaxNFramesBackForExtrap = min( i - 1, min(51, int32(VideoReadConfig.FS * 2)) );

        %Linear index of the maximum frame back
        MaxFrameBackForExtrapLinIdx = i - MaxNFramesBackForExtrap;

        %To conduct extrapolation, require that the 5 detections come after the maximum frame back 
        %Note: there can be no more than 5 detections because the find function used previously was
        %set only to return up to 5 detections.
        if nnz( NearbyDetectionsLinIdx >= MaxFrameBackForExtrapLinIdx ) == 5

            %Flag to apply bounding box for face detection
            UseBoundingBoxFaceTF = true;

            %Flag to use predicted ROI for skin detection
            UsePredictedSkinTF = true;

            %Combine the use of the median and linear regression to extrapolate the ROI for the
            %current frame.
            %Note: ROIMeans_FirstRead_ExtrapolateROI is a custom function located within folder 
            %'FacePulseRate'.
            ROIPredicted = ...
                ROIMeans_FirstRead_ExtrapolateROI(i, ROIForBBox, NearbyDetectionsLinIdx, ...
                    SetBoundingBoxes_DiffMax, VideoReadConfig, ROIGeneralConfig);

        %Fewer than 5 ROIs after max frame back        
        else

            %Do not use a bounding box for the face-detection algorithms
            %That is, submit the full frame to the face-detection algorithms.
            UseBoundingBoxFaceTF = false;

            %Flag that predicted ROI cannot be used to determine bounding box for skin-detection
            %algorithm.
            UsePredictedSkinTF = false;
        end


        %%%%%% Set bounding box for face-detection algorithm(s) %%%%%%

        if UseBoundingBoxFaceTF

            %ROIFace_BoundingBoxEnlargementFactor determines the size of the bounding box by  
            %enlarging the median ROI.

            %Difference between distance threshold and distance to first detection back
            %A zero or negative value indicates the distance threshold has not been exceeded; in 
            %this case, the enlargement factor used to increase the bounding box will not be 
            %increased. If the difference is positive, the enlargement factor will be increased  
            %according to the magnitude of the difference.
            
            %The linear index of the frame that falls on the threshold
            %Start at previous frame because it was the last frame to which the algorithms were 
            %applied.
            ROIFace_BoundingBoxGrowthThreshold_adjusted_LinIdx = ...
                (i - 1) - ROIFace_BoundingBoxGrowthThreshold_adjusted + 1;
            
            DifferenceFromThreshold = ...
                ROIFace_BoundingBoxGrowthThreshold_adjusted_LinIdx - ... distance threshold index
                NearbyDetectionsLinIdx(end); %closest detection back


            %If difference from the distance threshold is positive, increase the enlargement 
            %factor.
            if DifferenceFromThreshold > 0

                %Increase the enlargement factor according to the magnitude of the difference. 
                %Specifically, multiply the difference by a specified growth rate. This product is
                %then multiplied by the enlargement factor, which is then added to the enlargement 
                %factor.
                %Specify type double for compatibility with function ROIResize.
                ROIFace_BoundingBoxEnlargementFactor = ...
                    ROIFace_BoundingBoxEnlargementFactor + ...
                    ROIFace_BoundingBoxEnlargementFactor * ...
                    ( double(DifferenceFromThreshold) *    ... product of difference and growth rate
                     FaceDetectConfig.BoundingBoxGrowthRate_adjusted);
               
            end

            %Enlarge the bounding box by the enlargement factor:    
            
            %Function ROIResize scales bounding box as specified and also prevents scaled bounding   
            %box from exceeding frame dimensions.
            %Bounding box returned as [X-upper-left, Y-upper-left, width, height].
            
            %Use compiled function       
            if ROIGeneralConfig.UseCompiledFunctionsTF

                %1 x 4 row vector; type int16.
                %Note: ROIResize_mex is a custom compiled function located within folder 
                %'FacePulseRate'. For source code, see file ROIResize.m.
                BoundingBoxFace = ...
                    ROIResize_mex( ...
                        ROIPredicted,                         ... ROI to adjust; type int16
                        int32(1),                             ... ROI index (1 entered if only 1 ROI); type int32
                        ROIFace_BoundingBoxEnlargementFactor, ... width resizing scale factor; type double 
                        ROIFace_BoundingBoxEnlargementFactor, ... height resizing scale factor; type double 
                        VideoReadConfig.VidObjWidth,          ... to keep adjustment within frame dimensions; type int16
                        VideoReadConfig.VidObjHeight          ...             
                    );
            
            %Do not use compiled function
            else
 
                %1 x 4 row vector; type int16.
                %Note: ROIResize is a custom function located within folder 'FacePulseRate'.
                BoundingBoxFace = ...
                    ROIResize( ...
                        ROIPredicted, ... 
                        int32(1), ... 
                        ROIFace_BoundingBoxEnlargementFactor, ...  
                        ROIFace_BoundingBoxEnlargementFactor, ... 
                        VideoReadConfig.VidObjWidth, ... 
                        VideoReadConfig.VidObjHeight ...             
                    );                
            end
            
        %No detections found within the specified number of frames back 
        else   

            BoundingBoxFace = [];        
        end  


        %%%%%% Set bounding box for skin-detection algorithm %%%%%%

        %%%%%% --- Set the ROI from which to determine the bounding box %%%%%%

        %Unlike face detection, a bounding is always used for the skin-detection algorithm because 
        %there is a greater chance of a false positives. Bounding the search area helps reduce  
        %false positives. Additionally, using a bounded search area is more efficient.

        %Use predicted ROI
        if UsePredictedSkinTF      

            %Type int16.
            ROIForBoundingBoxSkin = ROIPredicted; 

        %Use the median ROI from the nearest five detections 
        %The predicted ROI is not available because there were not more than 5 face-detection  
        %algorithm detections after the maximum frame back. When there are no detections found   
        %between the maximum frame back and the current frame, no bounding box is used for face  
        %detection; however, because skin detection is less reliable than face detection, a 
        %bounding box will always be required for its use. Base the bounding box on the median of 
        %last 5 face-detection algorithm detections found, regardless of how many frames back they 
        %occur.            
        else
            
            %Take the median of the ROIs from ROIForBBox of the last five face-detection algorithm 
            %detections.
            %Type int16.
            %Note: medianByColumn is a custom function located within folder 'FacePulseRate'.            
            ROIForBoundingBoxSkin = ...
                medianByColumn( ROIForBBox(NearbyDetectionsLinIdx, :) ); %median for each column
        end

        %%%%%% --- Assign the bounding box %%%%%%

        %Determine scale for bounding box:

        %If a certain number of frames occur where no skin-detection algorithm detection is made 
        %(despite being attempted), enlarge bounding box. Unlike the implementation for the 
        %face-detection algorithm, where the bounding box expands at gradations according to the 
        %number of frames since a detection was made, there are only two possible sizes for the 
        %skin-detection bounding box: the specified size (ROISkin_BoundingBoxEnlargementFactor) and 
        %one larger size that is used when a certain number of frames pass without a skin detection.
        %One reason for only using two sizes is that it is uncommon for the skin-detection 
        %bounding box to be enlarged because the skin-detection algorithm almost always makes a
        %detection when the skin-detection algorithm is applied. Another reason is that the
        %bounding box used for skin detection begins quite large, so there is not much room for
        %expansion.
        
        %Note: The most likely case for no skin detection being made is that the area of the image
        %corresponding to the bounding box was completely segmented; this may indicate that the
        %bounding box is not sufficiently large to capture a portion of the face at that time.
 
        %Note: SkinDetect_SetBoundingBoxScale is a custom function located within folder 
        %'FacePulseRate'.
        [ROISkin_BoundingBoxEnlargementFactor, IncreaseSkinBBoxFactorStartIdx] = ...
            SkinDetect_SetBoundingBoxScale(i, HasROI_TF, SkinDetectConfig, ...
                IncreaseSkinBBoxFactorStartIdx);

        %Enlarge the ROI to determine the bounding box:
        
        %Function ROIResize scales bounding box as specified and also prevents scaled bounding box  
        %from exceeding frame dimensions.
        
        %Use compiled function       
        if ROIGeneralConfig.UseCompiledFunctionsTF

            %1 x 4 row vector; type int16.
            %Note: ROIResize_mex is a custom compiled function located within folder 
            %'FacePulseRate'. For source code, see file ROIResize.m.
            BoundingBoxSkin = ...
                ROIResize_mex( ...
                    ROIForBoundingBoxSkin,                ... Resized ROI; type int16  
                    int32(1),                             ... ROI index; type int32  
                    ROISkin_BoundingBoxEnlargementFactor, ... width resizing scale factor; type double
                    ROISkin_BoundingBoxEnlargementFactor, ... height resizing scale factor; type double
                    VideoReadConfig.VidObjWidth,          ... to keep resizing within frame dimensions; type int16
                    VideoReadConfig.VidObjHeight          ...             
                );

        %Do not use compiled function
        else
            
            %1 x 4 row vector; type int16.
            %Note: ROIResize is a custom function located within folder 'FacePulseRate'.
            BoundingBoxSkin = ...
                ROIResize( ...
                    ROIForBoundingBoxSkin, ...  
                    int32(1), ...
                    ROISkin_BoundingBoxEnlargementFactor, ... 
                    ROISkin_BoundingBoxEnlargementFactor, ... 
                    VideoReadConfig.VidObjWidth, ... 
                    VideoReadConfig.VidObjHeight ...             
                );        
        end                      
        
    %Fewer than five face-detection algorithm detections from beginning of video    
    else
        
        MinDetectionsAvailableTF = false;          
    end
        
%Minimum number of frames has not elapsed
else
    
    MinDetectionsAvailableTF = false;
end

%Neither minimum elapsed frames nor at least five face-detection algorithm detections
if ~ MinDetectionsAvailableTF
    
    UseBoundingBoxFaceTF = false;
    BoundingBoxFace = int16([]);  
    BoundingBoxSkin = int16([]);
    ROIForBoundingBoxSkin = int16([]);
end

%Rename because used as output argument that is used to indicate whether a bounding box is
%available for skin detection (if it is not, the skin-detection algorithm will not be used).
SkinBBoxAvailableTF = MinDetectionsAvailableTF;


%%%%%% Output validation %%%%%%

%%%%%% --- ROI values %%%%%%

%Check whether any ROI value is zero
%The operations of this function were intended to prevent values of zero, so such a value is
%likely due to an implementation error in this function. 

if ~ isempty(BoundingBoxFace) && any(BoundingBoxFace == 0) 

    %Throw exception
    ME = ...
        MException( ...
            'Component:InternalError', ...
            ['Internal Error: ROI-modification operations assigned a value of zero for an ROI.', ...
             ' ROI accuracy may be affected. The frame index of corresponding frame is: ', ...
             num2str(VideoReadConfig.FrameIdx(i)), '.'] ...
        );  
    
    throw(ME);
end

if ~ isempty(BoundingBoxSkin) && any(BoundingBoxSkin == 0) 

    %Throw exception
    ME = ...
        MException( ...
            'Component:InternalError', ...
            ['Internal Error: ROI-modification operations assigned a value of zero for an ROI.', ...
             ' ROI accuracy may be affected. The frame index of corresponding frame is: ', ...
             num2str(VideoReadConfig.FrameIdx(i)), '.'] ...
        );     
    
    throw(ME);
end

if ~ isempty(ROIForBoundingBoxSkin) && any(ROIForBoundingBoxSkin == 0) 
    
    %Throw exception
    ME = ...
        MException( ...
            'Component:InternalError', ...
            ['Internal Error: ROI-modification operations assigned a value of zero for an ROI.', ...
             ' ROI accuracy may be affected. The frame index of corresponding frame is: ', ...
             num2str(VideoReadConfig.FrameIdx(i)), '.'] ...
        );      
    
    throw(ME);
end

%Check whether the ROI size is unreasonably small
%Such a small size is likely due to an implementation error in this function.

if ~ isempty(BoundingBoxFace) && ...
   (BoundingBoxFace(3) < 20 || BoundingBoxFace(4) < 20)

    %Display warning indicating frame index
    warning( ...
        'Component:InternalError', ...
        ['Internal Error: Bounding-box operations assigned a size value for an ROI that is', ...
         ' below 20 pixels, which is likely inaccurate. ROI accuracy may be affected. The frame', ...
         ' index of corresponding frame is: ',  ...
         num2str(VideoReadConfig.FrameIdx(i)), '.'] ...
    );            
end 

if ~ isempty(BoundingBoxSkin) && ...
   (BoundingBoxSkin(3) < 20 || BoundingBoxSkin(4) < 20)

    %Display warning indicating frame index
    warning( ...
        'Component:InternalError', ...
        ['Internal Error: Bounding-box operations assigned a size value for an ROI that is', ...
         ' below 20 pixels, which is likely inaccurate. ROI accuracy may be affected. The frame', ...
         ' index of corresponding frame is: ',  ...
         num2str(VideoReadConfig.FrameIdx(i)), '.'] ...
    );            
end 

if ~ isempty(ROIForBoundingBoxSkin) && ...
   (ROIForBoundingBoxSkin(3) < 20 || ROIForBoundingBoxSkin(4) < 20)

    %Display warning indicating frame index
    warning( ...
        'Component:InternalError', ...
        ['Internal Error: Bounding-box operations assigned a size value for an ROI that is', ...
         ' below 20 pixels, which is likely inaccurate. ROI accuracy may be affected. The frame', ...
         ' index of corresponding frame is: ',  ...
         num2str(VideoReadConfig.FrameIdx(i)), '.'] ...
    );            
end

%%%%%% --- ROI type %%%%%%

%Check if ROI type not int16 because other functions are implemented to accept values of this type. 
%A non-matching type would be due to an implementation error.

if ~ isempty(BoundingBoxFace) && ... 
   ~ isa(BoundingBoxFace(1, 1), 'int16')

    %Throw exception
    ME = ...
        MException( ...
            'Component:InternalError', ...
            ['Internal Error: Variable BoundingBoxFace not type int16. Occurred during', ...
             ' bounding-box operations in frame index ', ...
             num2str(VideoReadConfig.FrameIdx(i)), '.'] ...           
        );

    throw(ME);             
end

if ~ isempty(BoundingBoxSkin) && ...
   ~ isa(BoundingBoxSkin(1, 1), 'int16')

    %Throw exception
    ME = ...
        MException( ...
            'Component:InternalError', ...
            ['Internal Error: Variable BoundingBoxSkin not type int16. Occurred during', ...
             ' bounding-box operations in frame index ', ...
             num2str(VideoReadConfig.FrameIdx(i)), '.'] ...           
        );

    throw(ME);             
end

if ~ isempty(ROIForBoundingBoxSkin) && ...
   ~ isa(ROIForBoundingBoxSkin(1, 1), 'int16')

    %Throw exception
    ME = ...
        MException( ...
            'Component:InternalError', ...
            ['Internal Error: Variable ROIForBoundingBoxSkin not type int16. Occurred during ', ...
             ' bounding-box operations in frame index ', ...
             num2str(VideoReadConfig.FrameIdx(i)), '.'] ...           
        );

    throw(ME);             
end


end %end function

