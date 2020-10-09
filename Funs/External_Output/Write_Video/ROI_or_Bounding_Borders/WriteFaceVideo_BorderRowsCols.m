function [RowsTB, ColsTB, RowsLR, ColsLR] = WriteFaceVideo_BorderRowsCols(Borders_uint16)        
%WriteFaceVideo_BorderRowsCols    Return row and column subscripts of border.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_ROIAndBoundingBoxBorders.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.
 

%%%%%%% Specify border thickness %%%%%%%

%Note: the thickness of borders is increased by adding rows and columns inside the borders (rather
%than expanding outward from the borders). This prevents the added rows and columns from being
%outside of the frame dimensions.

BorderThickness = 2;


%%%%%%% Rename for readibility %%%%%%%

XUpperLeft = Borders_uint16(1);
YUpperLeft = Borders_uint16(2);
Width      = Borders_uint16(3);
Height     = Borders_uint16(4);


%%%%%%% Left and right borders %%%%%%%

RowsLR = YUpperLeft : YUpperLeft + (Height - 1); 

%The number of columns is specified by BorderThickness
ColsLR = ...
    [ ...
        XUpperLeft : XUpperLeft + (BorderThickness - 1),                             ... left border columns
        XUpperLeft + (Width - 1) - (BorderThickness - 1) : XUpperLeft + (Width - 1), ... right border columns
    ]; 


%%%%%%% Top and bottom borders %%%%%%%

%The number of rows is specified by BorderThickness
%Note that Y-axis decreases going up.
RowsTB = ...
    [ ...
        YUpperLeft : YUpperLeft + (BorderThickness - 1),                              ... top border columns               
        YUpperLeft + (Height - 1) - (BorderThickness - 1) : YUpperLeft + (Height - 1) ... bottom border columns
    ];

ColsTB = XUpperLeft : XUpperLeft + (Width - 1);


end %end function

