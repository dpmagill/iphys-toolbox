function OutputConfig = ...
             OutputConfig_Setup(Video_InputFile, WriteVideoDetailedDiagnosticsTF, ...
                 SkinSegmentConfig, SkinDetectConfig)              
%OutputConfig_Setup    Setup configuration struct for writing output.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ValidateAndConfigure.
%
%
%    Description
%    -----------
%
%    Settings and validation for writing the output video and the output csv files.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Video Writing %%%%%% 

%Settings and validation for video writing.

%Note: OutputConfig_Setup_VideoWriting is a custom function located within folder 'FacePulseRate'.
OutputConfig = ...
    OutputConfig_Setup_VideoWriting(Video_InputFile, WriteVideoDetailedDiagnosticsTF, ...
        SkinSegmentConfig, SkinDetectConfig);


%%%%%% CSV Writing %%%%%% 

%Settings and validation csv writing.

%Note: OutputConfig_Setup_CSVWriting is a custom function located within folder 'FacePulseRate'.
OutputConfig = OutputConfig_Setup_CSVWriting(Video_InputFile, OutputConfig);


end %end function

