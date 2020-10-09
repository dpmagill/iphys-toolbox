function [ROINoPrevCallsBlock, NoPrevCallsBlock_ROIDetections] = ...
             ROIMSIR_DetectionSmooth(ROINoPrevCallsBlock, ROIBlockDetectionFaceLinIdx, ...
                 NDetectionsFace, ROIBlockDetectionSkinLinIdx, NDetectionsSkin, ...
                 ROIBlockDetectionFaceSkinLinIdx, NDetectionsFaceSkin, VidObjWidth, ...
                 VidObjHeight, FaceDetectConfig_ROIFaceSmoothingWindow, ...                
                 SkinDetectConfig_ROISkinSmoothingWindow, FirstReadTF, ...
                 SecondReadPostProcessingTF, VideoReadConfig_FrameIdx_FR, ...
                 RowToReturnFullLinIdx_FR, ExpectedBehaviorTestTF) %#codegen                                                  
%ROIMSIR_DetectionSmooth   Smooth ROIs that correspond to face-detection and skin-detection    
%                          algorithm detections to help remove the effect of false positives and to 
%                          add stability. 
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
%    Smooth ROIs that correspond to face-detection and skin-detection algorithm detections to help  
%    remove the effect of false positives and to add stability. False positives may be reduced   
%    because they sometimes occur as outliers, and smoothing should reduce the effect of outliers.   
%    Increasing stability across ROIs may help keep the ROI more oriented on the same area of the  
%    face, which may help increase accuracy of pulse rate calculations. Smooth with a moving mean.
%
%    The face-detection algorithm ROIs have been observed to be, on average, more accurate than the
%    skin-detection algorithm ROIs, so the smoothing operations have been ordered to increase the 
%    influence of face-detection ROIs. Specifically, the face-detection ROIs will be smoothed first
%    without including skin-detection ROIs; this removes the influence of skin-detection ROIs on 
%    the face-detection ROIs. Second, the skin-detection ROIs are smoothed with the face-detection 
%    ROIs included so that the face-detection ROIs can influence the skin-detection ROIs. Any 
%    face-detection ROIs smoothed in the second operation are not retained to remove the influence 
%    of skin-detection ROIs on face-detection ROIs.
%
%    All smoothing follows the following pattern:
%
%    (1) A moving mean is used to smooth the height and width of each ROI.
%    (2) The X- and Y-coordinates of each ROI are adjusted to correspond to the previous changes to  
%        the height and width.
%    (3) A moving mean is used to smooth the X- and Y-coordinates of each ROI.
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


%%%%%% Preallocate variables %%%%%%

NoPrevCallsBlock_ROIDetections = coder.nullcopy( zeros(NDetectionsFaceSkin, 4, 'int16') );


%%%%%% Face-detection algorithm detection smoothing %%%%%%

%Note: used during the first read or during the second read in the pre-processing (but not  
%post-processing) step.
%During the second read pre-processing step, size match ROIs near the beginning of the video that
%were not size matched during the first read. The second read does not use the face-detection
%algorithm, so size matching is not needed during the second read post-processing step.

%Note: during the first read, calls by function ROIMeans_FirstRead; during the second read, calls 
%by function ROIMeans_SecondRead.   

if FirstReadTF ||               ... first read
   ~ SecondReadPostProcessingTF %   second read pre-processing step 
    
    %If more than one face-detection algorithm detection within block
    %No need to smooth if one or zero detections.
    if NDetectionsFace > 1

        %%%%%% --- Moving-mean smoothing on X- and Y-coordinates %%%%%%        
        
        %Smooth face-detection algorithm ROI X- and Y-coordinates with those of other 
        %face-detection algorithm ROIs.
        %The moving-mean smoothing window is specified by argument ROIFaceSmoothingWindow to
        %function FacePulseRate. 
        %M x 4 matrix; type int16.
        %Note: MovMean is a custom function located within folder 'FacePulseRate'.
        ROINoPrevCallsBlock(ROIBlockDetectionFaceLinIdx, 1 : 2) = ...
            MovMean( ...
                ROINoPrevCallsBlock(ROIBlockDetectionFaceLinIdx, 1 : 2), ...
                FaceDetectConfig_ROIFaceSmoothingWindow, ... Smoothing window
                NDetectionsFace,                         ... The number or rows of the input matrix
                int32(2)                                 ... The number or columns of the input 
                                                         ... matrix.                 
            );
        
        %%%%%% --- Moving-mean smoothing on widths and heights %%%%%%

        %Assign unsmoothed widths and heights for later step
        %Only extract ROIs corresponding to a face-detection algorithm detection.
        %N detections x 2 matrix; type int16.              
        ROIWidthHeightPreSmooth = ROINoPrevCallsBlock(ROIBlockDetectionFaceLinIdx, 3 : 4);
        
        %Smooth face-detection algorithm ROI widths and heights with those of other face-detection 
        %algorithm ROIs.
        %The moving-mean smoothing window is relatively large to increase stability of ROI size
        %across frames.
        %M x 4 matrix; type int16.
        %Note: MovMean is a custom function located within folder 'FacePulseRate'.
        ROINoPrevCallsBlock(ROIBlockDetectionFaceLinIdx, 3 : 4) = ...
            MovMean( ... 
                ROINoPrevCallsBlock(ROIBlockDetectionFaceLinIdx, 3 : 4), ... 
                30,              ... smoothing window
                NDetectionsFace, ... the number or rows of the input matrix
                int32(2)         ... the number or columns of the input matrix                       
            );
        
        %%%%%% --- Adjust X- and Y-coordinates to correspond to adjustments in widths and heights %%%%%%

        %Loop across ROIs corresponding to face-detection algorithm detections
        for i = 1 : NDetectionsFace

            %Extract index corresponding to detection 
            ii = ROIBlockDetectionFaceLinIdx(i);

            %Half of difference between unmatched widths and height and adjusted widths and 
            %heights.
            %Optimize division by two by bit-wise operation.
            WidthHalfDiff_ith  = ...
                bitshift(ROIWidthHeightPreSmooth(i, 1) - ROINoPrevCallsBlock(ii, 3),  -1);

            HeightHalfDiff_ith = ...
                bitshift(ROIWidthHeightPreSmooth(i, 2) - ROINoPrevCallsBlock(ii, 4),  -1);

            %Add the half-differences to the X- and Y-coordinates
            %M x 4 matrix (229 x 4 during first-read operations); type int16.
            %Note: if there were negative differences, the half-differences will be subtracted from  
            %the X- and Y-coordinates.
            ROINoPrevCallsBlock(ii, 1) = ROINoPrevCallsBlock(ii, 1) + WidthHalfDiff_ith;
            ROINoPrevCallsBlock(ii, 2) = ROINoPrevCallsBlock(ii, 2) + HeightHalfDiff_ith;           
        end                
    end    
end


%%%%%% Skin-detection algorithm detection smoothing %%%%%%

%Note: used during all calls: during the first-read operations and during both the pre-processing
%and post-processing steps of the second-read operations.
%During the second-read pre-processing step, smooth skin-detection ROIs near the beginning of the 
%video that were smoothed during the first read. During the second-read post-processing step,
%smooth skin-detection ROIs near the beginning of the video based on recent skin-detection
%algorithm ROI detections.

%Don't need to smooth if no ROIs correspond to skin-detections.
SkinSmoothTF = NDetectionsSkin > 0;

if SkinSmoothTF
    
    %Only apply smoothing in this section to the skin-detection algorithm ROIs as the  
    %face-detection algorithm ROIs have already been smoothed. In order to use the ROIs from the 
    %face-detection algorithms as information in the smoothing, include ROIs from the 
    %face-detection algorithm; however, after smoothing, only retain the smoothed skin-detection 
    %ROIs so that the face-detection ROIs don't retain this additional smoothing. To do so, store 
    %the smoothed ROIs to a temporary variable and then extract only the skin-detection ROIs.
    
    %%%%%% --- Find positions of skin detections in detection-only ROI matrix %%%%%%
    
    %Find the positions in ROIBlockDetectionFaceSkinLinIdx where ROIBlockDetectionSkinLinIdx 
    %matches ROIBlockDetectionFaceSkinLinIdx. In other words, where in vector
    %ROIBlockDetectionFaceSkinLinIdx are the skin detections located. This index is used in a 
    %couple sections that follow. 

    %Column vector; int32.
    %Note: PositionsIn is a custom function located within folder 'FacePulseRate'.
    SkinIdxFit = ...
        PositionsIn( ...
            ROIBlockDetectionSkinLinIdx,     ... set A
            ROIBlockDetectionFaceSkinLinIdx, ... set B
            NDetectionsSkin                  ... length of set A
        );    
    
    %%%%%% --- Assign temporary ROI matrix %%%%%%
    
    %Assign temporary ROI matrix that consists of ROIs that correspond to face or skin detections.
    %Rows of the matrix that correspond to face detections will be discarded at the end of  
    %skin-detection smoothing procedure. 
    
    %Preallocate: 
    
    %N face-or-skin detections x 4 matrix; type int16.
    ROIBlockFaceSkin_Temp = ...
        coder.nullcopy( ...
            zeros( NDetectionsFaceSkin, 4, 'int16' ) ...
        ); 

    %Assign ROIs that correspond to face or skin detections:   
    
    %Loop across columns
    for i = int32(1) : 4
    
        %Loop across rows
        for j = 1 : NDetectionsFaceSkin
            
            jj = ROIBlockDetectionFaceSkinLinIdx(j);            
            
            ROIBlockFaceSkin_Temp(j, i) = ROINoPrevCallsBlock(jj, i);                                            
        end
    end

    %%%%%% --- Moving-mean smoothing on widths and heights %%%%%%    
    
    %Smooth with face-detection and/or skin-detection algorithm ROI widths and heights with those  
    %of other face-detection and/or skin-detection algorithm ROIs. As mentioned previously, any 
    %smoothing on ROIs that correspond to face detections will be discarded later.
    
    %The moving-mean smoothing window is relatively large to increase stability of ROI size across
    %frames.
    
    %Note: MovMean is a custom function located within folder 'FacePulseRate'.
    ROIBlockFaceSkin_Temp(:, 3 : 4) = ...
        MovMean( ... 
            ROIBlockFaceSkin_Temp(:, 3 : 4),  ...
            30,                  ... smoothing window
            NDetectionsFaceSkin, ... the number of rows of the input matrix
            int32(2)             ... the number of columns of the input matrix             
        ); 
    
    %%%%%% --- Adjust X- and Y-coordinates as a result of adjustments in widths and heights %%%%%%
    
    %Adjust X- and Y-coordinates corresponding to skin detections as a result of adjustments in 
    %widths and heights.
    
    %Loop across columns
    for i = 1 : 2
        
        %Loop across rows
        for j = 1 : NDetectionsSkin
            
            %Index of position of jth ROI corresponding to a skin detection in face-or-skin 
            %detection matrix.
            jj = SkinIdxFit(j);     
            
            %Index of position of jth ROI corresponding to a skin detection in the ROI block
            jjj = ROIBlockDetectionSkinLinIdx(j);
                            
            ROIBlockFaceSkin_Temp(jj, i) = ...
                ... Add the half-difference to the X- or Y-coordinate
                ... (If there were a negative difference, this would imply the abs value of the
                ... half-difference is subtracted from the coordinate).
                ROIBlockFaceSkin_Temp(jj, i) + ...
                ... Take half of the difference (optimize division by 2 with bit-wise division)
                bitshift( ...
                    ... Difference between unsmoothed width and height and smoothed width and 
                    ... height.
                    ROINoPrevCallsBlock(jjj, i + 2) - ROIBlockFaceSkin_Temp(jj, i + 2), ...
                    -1 ... 
                );
        end
    end    

    %%%%%% --- Moving-mean smoothing on X- and Y-coordinates %%%%%%
    
    %Smooth with face-detection and/or skin-detection algorithm ROI X- and Y-coordinates with those  
    %of other face-detection and/or skin-detection algorithm ROIs. As mentioned previously, any  
    %smoothing on ROIs that correspond to face detections will be discarded later.
           
    %The moving-mean smoothing window is specified by argument ROISkinSmoothingWindow to function 
    %FacePulseRate.  
    
    %Note: MovMean is a custom function located within folder 'FacePulseRate'.
    ROIBlockFaceSkin_Temp(:, 1 : 2) = ...
        MovMean( ... 
            ROIBlockFaceSkin_Temp(:, 1 : 2), ...
            SkinDetectConfig_ROISkinSmoothingWindow, ... smoothing window
            NDetectionsFaceSkin, ... the number of rows of the input matrix
            int32(2) ... the number of columns of the input matrix     
        );     
    
    %%%%%% --- Discard recent smoothing for ROIs corresponding to face-detection algorithm detections %%%%%%
    
    %Discard smoothing for ROIs corresponding to face-detection algorithm detections where  
    %smoothing was applied that included skin-detection algorithm ROIs. This removes the influence
    %of skin-detection algorithm ROIs on face-detection algorithm ROIs. This is conducted because
    %face-detection algorithm ROIs are assumed to be more accurate than skin-detection algorithm 
    %ROIs.
            
    %Keep only ROIs corresponding to skin-detection algorithm detections 
    %M x 4 matrix (229 x 4 during first-read operations); type int16.
    
    %Loop across columns
    for i = 1 : 4
        
        %Loop across rows
        for j = 1 : NDetectionsSkin
                                  
            %Index of position of jth ROI corresponding to a skin detection in the ROI block 
            jj = ROIBlockDetectionSkinLinIdx(j);
            
            %Index of position of jth ROI corresponding to a skin detection in face-or-skin 
            %detection matrix.
            jjj = SkinIdxFit(j);                      
                                  
            ROINoPrevCallsBlock(jj, i) = ROIBlockFaceSkin_Temp(jjj, i);                
        end
    end
        
    %%%%%% --- Lightly smooth ROIs corresponding to face-detection algorithm detections %%%%%%
    
    %The previous step (discarding smoothing for face-detection algorithm ROIs) may result in some 
    %undesired jumps of the ROI between face-detection algorithm detections and skin-detection 
    %algorithm detections. To smooth these jumps, the face-detection algorithm detections are
    %smoothed with a set of ROIs that include skin-detection algorithm detections. To reduce the
    %influence of skin-detection algorithm detections on face-detection algorithm detections -- 
    %which was the purpose of the discarding step -- a small smoothing window of 3 is used.
    
    %Also assign a variable, NoPrevCallsBlock_ROIDetections, that only contains ROIs that 
    %correspond to a detection. This variable would have been assigned in the next section ("Assign  
    %an ROI matrix that contains only ROIs that correspond to a detection"), but it is assigned 
    %here for efficiency.
    
    %Return smoothed ROIs that correspond to either a face- or skin-detection algorithm detection

    if NDetectionsFace ~= 0     
    
        %Note: ROIMSIR_FaceDetectionLightSmooth is a custom function located within folder 
        %'FacePulseRate'.
        [NoPrevCallsBlock_ROIDetections, ... 229 x 4 matrix; type int16
         FaceIdxFit] =                   ... Index of positions of face detections in 
                                         ... NoPrevCallsBlock_ROIDetections.
            ROIMSIR_FaceDetectionLightSmooth(ROINoPrevCallsBlock, ...
                ROIBlockDetectionFaceSkinLinIdx, NDetectionsFaceSkin, ...
                ROIBlockDetectionFaceLinIdx, NDetectionsFace);
     
        %Assign smoothed ROIs corresponding to face detections to ROI matrix:
    
        %Loop across columns
        for i = 1 : 4

            %Loop across rows        
            for j = 1 : NDetectionsFace

                %Position of jth face-detection in ROINoPrevCallsBlock 
                jj = ROIBlockDetectionFaceLinIdx(j);                 
                
                %Position of jth face-detection in NoPrevCallsBlock_ROIDetections 
                jjj = FaceIdxFit(j);                              
                
                ROINoPrevCallsBlock(jj, i) = NoPrevCallsBlock_ROIDetections(jjj, i);                                               
            end
        end
    end
end
    

%%%%%% Assign an ROI matrix that contains only ROIs that correspond to a detection %%%%%%

%This variable contains all ROIs that correspond to either a face- or skin-detection algorthm 
%detection. This variable will be used as input to functions ROIMSIR_Interpolate and 
%ROIMSIR_FrameByFrameSmooth.
    
%If no skin-detection ROIs were smoothed or if the number of face detections equals 0.
%In either case, variable NoPrevCallsBlock_ROIDetections would not have been previously assigned. 
if ~ SkinSmoothTF || NDetectionsFace == 0
    
    %If no ROIs in the block correspond to detections by either the skin-detection algorithm or the
    %face-detection algorithm.
    if NDetectionsFaceSkin == 0
    
        NoPrevCallsBlock_ROIDetections = zeros(0, 4, 'int16');
        
    %If at least one ROI in block corresponds to a detection        
    else        
        
        %Loop across columns
        for i = 1 : 4

            %Loop across rows    
            for j = 1 : NDetectionsFaceSkin       

                %jjth index corresponding to a detection
                jj = ROIBlockDetectionFaceSkinLinIdx(j);

                NoPrevCallsBlock_ROIDetections(j, i) = ROINoPrevCallsBlock(jj, i);
            end
        end
    end
end
      

%%%%%% Adjust ROI(s) that exceed frame dimensions %%%%%%   

%Although ROI(s) are also checked later in function ROIMSIR, check here as well so that any
%overshoots from smoothing don't affect the interpolation operations in function 
%ROIMSIR_Interpolate, which occurs before the check by ROIMSIR. Also, before the check by ROIMSIR,
%ROIs returned here will influence variable ROIOutBeforeFrameByFrameSmoothing_FR or 
%ROIOutBeforeFrameByFrameSmoothing_SR (assigned in function ROIMSIR), and this variable needs to be
%within frame dimensions for later use in function WriteFaceVideo. 

%Note: used during all calls: during the first read and during both the pre-processing and
%post-processing steps of the second read. 

%Note: although it may seem unlikely for the smoothing of ROIs to result in values outside of frame
%dimensions, this might occur when, for example, both the width and the X-coordinate increased or  
%both the height and the Y-coordinate increased.
   
%Adjust any coordinates that exceed frame dimensions
%M x 4 matrix (229 x 4 during first-read operations); type int16.
%Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder 'FacePulseRate'.
ROINoPrevCallsBlock(ROIBlockDetectionFaceSkinLinIdx, 1 : 4) = ...
    ROIAdjustIfExceedsFrameDims( ...
        ROINoPrevCallsBlock(ROIBlockDetectionFaceSkinLinIdx, 1 : 4), ...
        VidObjWidth, ...
        VidObjHeight ...
    );  

%Adjust any coordinates that exceed frame dimensions
%N detections x 4 matrix (:229 x 4 during first-read operations); type int16.
%Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder 'FacePulseRate'.
NoPrevCallsBlock_ROIDetections = ...
    ROIAdjustIfExceedsFrameDims( ...
        NoPrevCallsBlock_ROIDetections, ...
        VidObjWidth, ...
        VidObjHeight ...
    ); 


%%%%%% Output validation %%%%%%

%First-read operations
if FirstReadTF

    %Check whether any ROIs assigned in the current function equal zero.
    %The operations of this function were intended to prevent values of zero, so such a value is
    %likely due to an implementation error in this function. 
    
    %Loop across columns
    for i = int32(1) : 4
 
        %Loop across ROIs rows that correspond to ROIs assigned in the current function
        for j = 1 : NDetectionsFaceSkin

            jj = ROIBlockDetectionFaceSkinLinIdx(j);
            
            if ROINoPrevCallsBlock(jj, i) == 0 
                
                %Throw error 
                %Called as extrinsic so that stack trace can be displayed.
                error( ...
                    'Component:InternalError', ...
                    ['Internal Error (ROIMSIR, code 10): ROI-modification operations', ...
                     ' assigned a value of zero for an ROI. ROI accuracy may be affected. The', ...
                     ' frame index of the corresponding frame is: ', ... 
                     sprintf( '%d', ...
                         int32( VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR) ) ...
                     ), ... 
                     '. Detected within function ROIMSIR in function ROIMSIR_DetectionSmooth.'] ...
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
        %Note: '%.0f' = floating point with no decimals.         
        warning( ...
            'Component:InternalError', ...
            ['Potential Internal Error (ROIMSIR, code 11): ROI-modification operations', ...
             ' assigned a size value for an ROI that is below 20 pixels, which is likely', ...
             ' inaccurate. ROI accuracy may be affected. The frame index of the corresponding', ...
             ' frame is: ',  ...
             sprintf( '%d', int32( VideoReadConfig_FrameIdx_FR(RowToReturnFullLinIdx_FR) ) ), ... 
             '. Detected within function ROIMSIR in function ROIMSIR_DetectionSmooth.'] ...             
        );           
    end 

%Second-read operations
else

    %Check whether any ROIs assigned in the current function equal zero.
    %The operations of this function were intended to prevent values of zero, so such a value is
    %likely due to an implementation error in this function.     
    
    %Loop across columns
    for i = 1 : 4
 
        %Loop across ROIs rows that correspond to ROIs assigned in the current function
        for j = 1 : NDetectionsFaceSkin

            jj = ROIBlockDetectionFaceSkinLinIdx(j);
            
            if ROINoPrevCallsBlock(jj, i) == 0
                
                %Throw exception
                %Called as extrinsic so that stack trace can be displayed.
                %Note: '%.0f' = floating point with no decimals.
                error( ...
                    'Component:InternalError', ...
                    ['Internal Error (ROIMSIR, code 12): ROI-modification operations assigned', ...
                     ' a value of zero for an ROI. ROI accuracy may be affected. The error', ...
                     ' occurred during the second-read operations. Detected within function', ...  
                     ' ROIMSIR in function ROIMSIR_DetectionSmooth.'] ...              
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
            ['Potential Internal Error (ROIMSIR, code 13): ROI-modification operations', ...
             ' assigned a size value for an ROI that is below 20 pixels, which is likely', ...
             ' inaccurate. ROI accuracy may be affected. Occurred during the second-read', ... 
             ' operations. Detected within function ROIMSIR in function', ...
             ' ROIMSIR_DetectionSmooth.'] ...
        );            
    end         
end


end %end function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Note: this function is not currently used as a compiled function as it is nested within a
%compiled function, ROIMSIR_mex.

%Code-generation and build script used to generate C-language code and create the compiled version 
%(ROIMSIR_DetectionSmooth_mex) of the function.

%{
           
     
%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%                                                     Example Code                 Upp. Bounds  Var. Size (T/F)  Type
ROINoPrevCallsBlockCode               = coder.typeof( zeros(500, 4, 'int16'),      [inf, 4],    [1, 0] );        %int16
ROIBlockDetectionFaceLogIdxCode       = coder.typeof( false(500, 1),               [inf, 1],    [1, 0] );        %logical
ROIBlockDetectionSkinLogIdxCode       = coder.typeof( false(500, 1),               [inf, 1],    [1, 0] );        %logical
ROIBlockDetectionFaceSkinLogIdxCode   = coder.typeof( false(500, 1),               [inf, 1],    [1, 0] );        %logical 
VideoReadConfig_FrameIdxCode          = coder.typeof( zeros(1, 500, 'int32'),      [1, inf],    [0, 1] );        %uint32 
              
   
%%%%%% Specify fixed-size input arguments %%%%%%

VidObjWidthCode                              = int16(0);         
VidObjHeightCode                             = int16(0);
FirstReadTFCode                              = false;
SecondReadPostProcessingTFCode               = false;
RowToReturnFullLinIdxCode                    = int32(0);
FaceDetectConfig_ROIFaceSmoothingWindowCode  = double(0);
SkinDetectConfig_ROISkinSmoothingWindowCode  = double(0);


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

codegen ROIMSIR_DetectionSmooth.m -config cfg -args {ROINoPrevCallsBlockCode, ROIBlockDetectionFaceLogIdxCode, ROIBlockDetectionSkinLogIdxCode, ROIBlockDetectionFaceSkinLogIdxCode, VidObjWidthCode, VidObjHeightCode, FaceDetectConfig_ROIFaceSmoothingWindowCode, SkinDetectConfig_ROISkinSmoothingWindowCode, FirstReadTFCode, SecondReadPostProcessingTFCode, VideoReadConfig_FrameIdxCode, RowToReturnFullLinIdxCode}
             
%}

