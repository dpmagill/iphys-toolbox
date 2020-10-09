function ViolaJonesMinDim = ...
             WriteFaceVideo_MinVJDims_Setup(ROIGeneralConfig, VidObjHeight_uint16, ...
                 VidObjWidth_uint16, FaceDetectConfig)
%WriteFaceVideo_MinVJDims_Setup   Setup to display the minimum width and height of ROIs to be
%                                 returned by the Viola-Jones detectors.
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_AnnotationSetup.
%
%
%    Description
%    -----------
%
%    Return a struct (ViolaJonesMinDim) with the specification of lines to show the minimum height  
%    and width required for Viola-Jones detectors. This specification will be used by function 
%    WriteFaceVideo to superimpose lines in the lower-right corner of each frame of the output 
%    video. The lines are superimposed to provide an indication of whether the minimum dimensions 
%    of the ROI that can be returned by the Viola-Jones detectors are large enough to capture the 
%    face in the video. The minimum dimensions are specified by ROIMinWidthRatio and 
%    ROIMinHeightRatio, which are arguments to function FacePulseRate.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Lines showing minimum height and width %%%%%%

%Specify type uint16 for faster evaluation where used.

%Minimum height and width used for Viola-Jones face detectors:

%Primary algorithm:

ViolaJonesMinHeight_Pri = ...
    uint16(round(ROIGeneralConfig.ROIMinHeightProportion * single(VidObjHeight_uint16))); 

ViolaJonesMinWidth_Pri  = ...
    uint16(round(ROIGeneralConfig.ROIMinWidthProportion * single(VidObjWidth_uint16))); 

%Secondary #1 algorithm:
  
ViolaJonesMinHeight_Sec1 = ...
    uint16( ...
        round( ...
            ROIGeneralConfig.ROIMinHeightProportion * single(VidObjHeight_uint16) *...
            FaceDetectConfig.ROIMinHeightProportionIncreaseSec1 ...
        ) ...
    );

ViolaJonesMinWidth_Sec1 = ...
    uint16( ...
        round( ...
            ROIGeneralConfig.ROIMinWidthProportion * single(VidObjWidth_uint16) *...
            FaceDetectConfig.ROIMinWidthProportionIncreaseSec1 ...
        ) ...
    );


%Secondary #2 algorithm:
   
ViolaJonesMinHeight_Sec2 = ...
    uint16( ...
        round( ...
            ROIGeneralConfig.ROIMinHeightProportion * single(VidObjHeight_uint16) *...
            FaceDetectConfig.ROIMinHeightProportionIncreaseSec2 ...
        ) ...
    );

ViolaJonesMinWidth_Sec2 = ...
    uint16( ...
        round( ...
            ROIGeneralConfig.ROIMinWidthProportion * single(VidObjWidth_uint16) *...
            FaceDetectConfig.ROIMinWidthProportionIncreaseSec2 ...
        ) ...
    );

%Rows and columns of example lines showing minimum height and width:
       
%Primary algorithm
Width_StartPoint_Pri  = VidObjWidth_uint16 - ViolaJonesMinWidth_Pri;
Width_EndPoint_Pri    = VidObjWidth_uint16 - 38;
Height_StartPoint_Pri = VidObjHeight_uint16 - ViolaJonesMinHeight_Pri;
Height_EndPoint_Pri   = VidObjHeight_uint16 - 38;

%Local function
[ViolaJonesMinDim.Pri_VertLine_Rows, ...
 ViolaJonesMinDim.Pri_VertLine_Cols, ...
 ViolaJonesMinDim.Pri_HorzLine_Rows, ...
 ViolaJonesMinDim.Pri_HorzLine_Cols] = ...
    LineDims(Width_StartPoint_Pri, Width_EndPoint_Pri, Height_StartPoint_Pri, Height_EndPoint_Pri);
         
%Secondary #1 algorithm:        

Width_StartPoint_Sec1  = VidObjWidth_uint16 - ViolaJonesMinWidth_Sec1;
Width_EndPoint_Sec1    = VidObjWidth_uint16 - 29;
Height_StartPoint_Sec1 = VidObjHeight_uint16 - ViolaJonesMinHeight_Sec1;
Height_EndPoint_Sec1   = VidObjHeight_uint16 - 29;

%Local function
[ViolaJonesMinDim.Sec1_VertLine_Rows, ...
 ViolaJonesMinDim.Sec1_VertLine_Cols, ...
 ViolaJonesMinDim.Sec1_HorzLine_Rows, ...
 ViolaJonesMinDim.Sec1_HorzLine_Cols] = ...
    LineDims(Width_StartPoint_Sec1, Width_EndPoint_Sec1, Height_StartPoint_Sec1, ...
        Height_EndPoint_Sec1);        


%Secondary #2 algorithm:

Width_StartPoint_Sec2  = VidObjWidth_uint16 - ViolaJonesMinWidth_Sec2;
Width_EndPoint_Sec2    = VidObjWidth_uint16 - 20;
Height_StartPoint_Sec2 = VidObjHeight_uint16 - ViolaJonesMinHeight_Sec2;
Height_EndPoint_Sec2   = VidObjHeight_uint16 - 20;

%Local function
[ViolaJonesMinDim.Sec2_VertLine_Rows, ...
 ViolaJonesMinDim.Sec2_VertLine_Cols, ...
 ViolaJonesMinDim.Sec2_HorzLine_Rows, ...
 ViolaJonesMinDim.Sec2_HorzLine_Cols] = ...
    LineDims(Width_StartPoint_Sec2, Width_EndPoint_Sec2, Height_StartPoint_Sec2, ...
        Height_EndPoint_Sec2);    


%Number of algorithms used
if ~ FaceDetectConfig.ROIFaceSecondary1TF 
  
    ViolaJonesMinDim.NAlgs = 1;
    
elseif ~ FaceDetectConfig.ROIFaceSecondary2TF
 
    ViolaJonesMinDim.NAlgs = 2;
    
else
    
    ViolaJonesMinDim.NAlgs = 3;
end


%Color of example lines:

ViolaJonesMinDim.Color = [255, 255, 0]; %yellow


end %end main function


%=============================================================================================
%Local functions 
%=============================================================================================


%=============================================================================================
function [VertLine_Rows, VertLine_Cols, HorzLine_Rows, HorzLine_Cols] = ...
             LineDims(Width_StartPoint, Width_EndPoint, Height_StartPoint, Height_EndPoint)
%LineDims   Return line indices corresponding to the minimum height and width of Viola-Jones face
%           detector(s). 
         

%Vertical line dimensions:

%Rows with length corresponding to height
VertLine_Rows = ...
    single( ...
        Height_StartPoint : Height_EndPoint ...
    );         

%2 pixels thick
VertLine_Cols = ...
    single( ...
        Width_EndPoint : Width_EndPoint + 1 ...
    );

%Horizontal line dimensions:

%2 pixels thick
HorzLine_Rows = ...
    single( ...
        Height_EndPoint : Height_EndPoint + 1 ... 
    );

%Columns with length corresponding to width
HorzLine_Cols = ...
    single( ...
        Width_StartPoint : Width_EndPoint ... 
    );


end %end local function
