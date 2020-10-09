function [BorderRGB_uint8, RowsTB, ColsTB, RowsLR, ColsLR, SkipToNextCaseTF] = ...
             WriteFaceVideo_ROIAndBoundingBoxBorders(i, BorderIdx, ROI_uint16, ROIDiagnostic)
%WriteFaceVideo_ROIAndBoundingBoxBorders   Prepare for insertion of ROI and bounding box borders on
%                                          the output video. 
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo.
%
%
%    Description
%    -----------
%
%    Prepare for the insertion of ROI and bounding box borders on the output video. To avoid 
%    reassigning the entire video frame, the assignment of the borders into the video frame is 
%    conducted outside of the function.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.                                         
        
  
%%%%%% Switch by border %%%%%%

switch BorderIdx 
        
    %%%%%% --- ROI borders %%%%%% 
    
    %The final ROI from a detection algorithm or interpolation
    %ROI after frame-by-frame smoothing and resizing modifications by function ROIMSIR         
    case 1

       Borders_uint16 = ROI_uint16(i, :); %type uint16.
       BorderRGB = [189, 233, 255]; %light blue  

    %ROI from a detection algorithm without modifications by function ROIMSIR
    %Note: In first-operations, ROIDiagnostic.ROI_NonSmoothed assigned by function 
    %ROIMeans_FirstRead. In second-read operations, ROIDiagnostic.ROI_NonSmoothed assigned by
    %function ROIMeans_SecondRead_SkinDetect.        
    %Note: interpolated ROIs are not included.
    case 2

       Borders_uint16 = ROIDiagnostic.ROI_NonSmoothed(i, :); %type uint16.
       BorderRGB = [0, 0, 0]; %black

    %ROI from a detection algorithm or interpolation before frame-by-frame smoothing and 
    %resizing modifications. If interpolated, this shows the ROI directly after interpolation 
    %by function ROIMSIR. If a detection, this shows the ROI after size matching and
    %detection-smoothing by function ROIMSIR. For either case, frame-by-frame smoothing and
    %resizing, conducted in function ROIMSIR, have not yet been applied.
    %Note: In first-operations, ROIDiagnostic.ROI_NonFinalSmoothed assigned by function 
    %ROIMeans_FirstRead. In second-read operations, ROIDiagnostic.ROI_NonFinalSmoothed assigned 
    %by function ROIMeans_SecondRead.        
    %Note: interpolated ROIs are not included.        
    case 3

       Borders_uint16 = ROIDiagnostic.ROI_NonFinalSmoothed(i, :); %type uint16.
       BorderRGB = [0, 0, 255]; %blue           
       
    %%%%%% --- Bounding box borders %%%%%%  

    %Bounding box for face-detection algorithm(s)  
    case 4 

        %Note: ROIDiagnostic.BBox_Scan.FaceAlg assigned by function ROIMeans_FirstRead.
        Borders_uint16 = ROIDiagnostic.BBox_Scan.FaceAlg(i, :); %type uint16.
        BorderRGB = [153, 51, 255]; %medium purple

    %Bounding box for skin-detection algorithm
    case 5

        %Note: In first-read operations, ROIDiagnostic.BBox_Scan.SkinAlg assigned by function 
        %ROIMeans_FirstRead. In second-read operations, ROIDiagnostic.BBox_Scan.SkinAlg 
        %assigned by function ROIMeans_SecondRead_SkinDetect.          
        Borders_uint16 = ROIDiagnostic.BBox_Scan.SkinAlg(i, :); %type uint16.
        BorderRGB = [178, 178, 178]; %light gray
end


%%%%%% Flag to skip to next case if elements are zero %%%%%%

%For a bounding box, this indicates a detection algorithm was not not run for ith frame.
%For an ROI, this only applies to ROI_NonSmoothed.
if all(Borders_uint16 == 0) 

    SkipToNextCaseTF = true;
    
else
    
    SkipToNextCaseTF = false;    
end


%%%%%% Determine subscripts of border %%%%%%

%Note: 'WriteFaceVideo_BorderRowsCols' is a custom function located within folder  
%'FacePulseRate'.
[RowsTB, ColsTB, RowsLR, ColsLR] = WriteFaceVideo_BorderRowsCols(Borders_uint16);                    

%Change to type uint8 for efficiency in assignment
BorderRGB_uint8 = uint8(BorderRGB);


end %end function

