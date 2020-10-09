function ROIPredicted = ...
            ROIMeans_FirstRead_ExtrapolateROI(i, ROIForBBox, NearbyDetectionsLinIdx, ...
                SetBoundingBoxes_DiffMax, VideoReadConfig, ROIGeneralConfig)
%ROIMeans_FirstRead_ExtrapolateROI   Predict location of ROI for ith frame from prior ROIs using 
%                                    the median and linear extrapolation.          
%                                    
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead_SetBoundingBoxes.
%
%
%    Description
%    -----------
%
%    Predict the location of ROI for the ith frame from the ROIs of previous frames. First, use
%    linear extrapolation to predict a set of ROI values. Then, cap excessive values by comparing
%    the interpolated values to the median across many ROIs.
%     
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%%%%%% Take median of last few ROI detections %%%%%% 

%Take the median of the ROIs from variable ROIForBBox of the last five detections from the current 
%frame. 
%Type int16.
%For a description on the use of ROIForBBox, see the file for function 
%ROIMeans_FirstRead_SetBoundingBoxes. 
%Note: medianByColumn is a custom function located within folder 'FacePulseRate'.
ROIMedian = medianByColumn( ROIForBBox(NearbyDetectionsLinIdx, :) ); ... median for each column
 

%%%%%% Extrapolate ROI X- and Y-coordinates from last few face-detections ROIs %%%%%%

%Extrapolate values for the X- and Y-coordinate columns of up to the last five ROIs from face
%detections. 
%The ROIs are specified by the linear index NearbyDetectionsLinIdx.
%Extrapolation conducted with linear extrapolation.

%Compiled function
if ROIGeneralConfig.UseCompiledFunctionsTF 
 
    %1 x 2 row vector; type int16.
    %Note: Interp_mex is a compiled custom function located within folder FacePulseRate. For source
    %code, see file Interp.m. 
    ROIExtrapValues = ...   
        Interp_mex( ... linear interpolation rounded to integer
            VideoReadConfig.FrameTimestampUntrimmed_Single(NearbyDetectionsLinIdx), ... time points used for extrapolation
            ROIForBBox(NearbyDetectionsLinIdx, 1 : 2), ... values used for extrapolation
            VideoReadConfig.FrameTimestampUntrimmed_Single(i), ... time point at which extrapolation to be assigned
            true,  ... flag whether extrapolation should be performed with linear method
            false, ... false: do not conduct validity check 
            int16(0), ... unused argument corresponding to validity check
            ROIMedian(1 : 2), ... compare extrapolated values against these provided values         
            SetBoundingBoxes_DiffMax, ... threshold for distance of extrapolated values from provided values                           
            int16(0), ... unused argument corresponding to validity check
            int16(0) ... unused argument corresponding to validity check
        );

%Non-compiled function        
else

    %1 x 2 row vector; type int16.
    %Note: Interp is a custom function located within folder 'FacePulseRate'.  
    ROIExtrapValues = ...
        Interp( ... 
            VideoReadConfig.FrameTimestampUntrimmed_Single(NearbyDetectionsLinIdx), ... time points used for extrapolation
            ROIForBBox(NearbyDetectionsLinIdx, 1 : 2), ... values used for extrapolation
            VideoReadConfig.FrameTimestampUntrimmed_Single(i), ... time point at which extrapolation to be assigned
            true,  ... flag whether extrapolation should be performed with linear method
            false, ... false: do not conduct validity check 
            int16(0), ... unused argument corresponding to validity check
            ROIMedian(1 : 2), ... compare extrapolated values against these provided values              
            SetBoundingBoxes_DiffMax, ... threshold for distance of extrapolated values from provided values                          
            int16(0), ... unused argument corresponding to validity check
            int16(0) ... unused argument corresponding to validity check
        );
end
            

%%%%%% Adjust extrapolated X- and Y-coordinates to contain overshoots %%%%%%

%%%%%% --- Determine distance and position of extrapolated X- and Y-coordinates compared to median coordinates %%%%%%

%X-coordinate difference between median and extrapolated
%Neg value: extrapolated at left of median; pos value: extrapolated at right of median.
%Type int16.
XDiff = ROIExtrapValues(1) - ROIMedian(1);

%Y-coordinate difference between median and extrapolated 
%Neg value: extrapolated higher than median; pos value: extrapolated lower than median.
%Type int16.
YDiff = ROIExtrapValues(2) - ROIMedian(2);


%%%%%% --- Limit overshoots by capping difference between median and extrapolated X- and Y-coordinates values %%%%%%           

%Note: the operations in this block are now handled by function Interp (arguments 7 and 8).

%{

%Maximum difference between median and extrapolated values
%Shorten name for readibility.
%Type int16.
DiffMax = SetBoundingBoxes_DiffMax;

%Cap X-coordinate at DiffMax
if XDiff < -(DiffMax) %extrapolated exceeds limit on left side of median

    ROIExtrapValues(1) = ROIExtrapValues(1) - DiffMax;

elseif XDiff > DiffMax %extrapolated exceeds limit on right side of median        

    ROIExtrapValues(1) = ROIExtrapValues(1) + DiffMax;                
end            

%Cap Y-coordinate at DiffMax           
if YDiff < -(DiffMax) %extrapolated exceeds limit higher than median

    ROIExtrapValues(2) = ROIExtrapValues(2) - DiffMax;

elseif YDiff >  DiffMax %extrapolated exceeds limit lower than median            

    ROIExtrapValues(2) = ROIExtrapValues(2) + DiffMax;                
end           

%}

%%%%%% --- Limit effect of overshoots by expanding ROI side(s) %%%%%%

%Expand side(s) of ROI where extrapolated ROI moves away from median ROI.
%Set the other side(s) at the median. This prevents overshoots from extrapolation from moving
%bounding box too far away from potential detection. The downside of this operation is that the
%larger resulting bounding box results in higher computational time for the face-detection
%detector(s).

%Example:
%  Median ROI:
%  .........___...
%  ........|___|..
%  Overshoot ROI:
%  .___...........
%  |___|..........
%  Expanded ROI:
%  .___________...
%  |___________|..

%Expand and set left and right ROI sides
if XDiff < 0 %extrapolated on left side of median

    XUpperLeft = ROIExtrapValues(1);
    Width = ROIMedian(3) + XDiff * -1; %change to positive sign 
    
else %extrapolated on right side of median

    XUpperLeft = ROIMedian(1);
    Width = ROIMedian(3) + XDiff;
end

%Expand and set top and bottom ROI sides            
if YDiff < 0 %extrapolated higher than median

    YUpperLeft = ROIExtrapValues(2);
    Height = ROIMedian(4) + YDiff * -1; %change to positive sign
    
else %extrapolated below median

    YUpperLeft = ROIMedian(2);
    Height = ROIMedian(4) + YDiff;
end


%%%%%% Concatenate ROI values %%%%%%

%The finished ROI values are termed the "predicted" ROI.

%Predicted ROI from median and extrapolated values
%Type int16.
ROIPredicted = [XUpperLeft, YUpperLeft, Width, Height];


%%%%%% Keep ROI values within frame dimensions %%%%%%

%Adjust coordinates that exceed frame dimensions:

%Use compiled function       
if ROIGeneralConfig.UseCompiledFunctionsTF 
    
    %Type int16.
    %Note: ROIAdjustIfExceedsFrameDims is a custom compiled function located within folder 
    %'FacePulseRate'. For source code, see file ROIResize.m.
    ROIPredicted = ...
        ROIAdjustIfExceedsFrameDims_mex( ...
            ROIPredicted, ...
            VideoReadConfig.VidObjWidth, ... 
            VideoReadConfig.VidObjHeight ...        
        );

%Do not use compiled function 
else

    %Type int16.
    %Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder 'FacePulseRate'.
    ROIPredicted = ...
        ROIAdjustIfExceedsFrameDims( ...
            ROIPredicted, ...
            VideoReadConfig.VidObjWidth, ... 
            VideoReadConfig.VidObjHeight ...        
        );    
end


%%%%%% Output validation %%%%%%

%Check whether any ROI value is zero
%The operations of this function were intended to prevent values of zero, so such a value is likely
%due to an implementation error in this function. 
if any(ROIPredicted == 0) 

    %Throw exception
    ME = ...
        MException( ...
            'Component:InternalError', ...
            ['Internal Error: ROI-modification operations assigned a value of zero for an ROI.', ...
             ' ROI accuracy may be affected. The frame index of corresponding frame is: ', ...
             num2str( VideoReadConfig.FrameIdx(i) ), '.'] ...
        );    
    
    throw(ME);
end

%Check whether the ROI size is unreasonably small
%Such a small size is likely due to an implementation error in this function.
if ROIPredicted(3) < 20 || ROIPredicted(4) < 20

    %Display warning indicating frame index
    warning( ...
        'Component:InternalError', ...
        ['Internal Error: Bounding-box operations assigned a size value for an ROI that is', ...
         ' below 20 pixels, which is likely inaccurate. ROI accuracy may be affected. The', ...
         ' frame index of corresponding frame is: ',  ...
         num2str( VideoReadConfig.FrameIdx(i) ), '.'] ...
    );            
end 

%Check if ROI type not int16 because other functions are implemented to accept values of this type. 
%A non-matching type is likely due to an implementation error.
if ~ isa(ROIPredicted(1, 1), 'int16')

    %Throw exception
    ME = ...
        MException( ...
            'Component:InternalError', ...
            ['Internal Error: Variable ROIPredicted not type int16. Occurred during', ...
             ' bounding-box operations in frame index ', ...
             num2str( VideoReadConfig.FrameIdx(i) ), '.'] ...           
        );

    throw(ME);             
end
    
    
end %end function

