function [OutputConfig] = OutputConfig_Setup_CSVWriting(Video_InputFile, OutputConfig)
%OutputConfig_Setup_CSVWriting    Settings for csv file writing. 
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function OutputConfig_Setup.
%
%
%    Description
%    -----------
%
%    Settings and validation for csv file writing. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% CSV Writing Settings %%%%%%

%Whether to enable csv writing
WriteCSV_TF = true;

%Output CSV file names:
    
%Remove file extension from path and file name
fileNoExt = Video_InputFile(1 : length(Video_InputFile) - 4);
    
%Append string and file extension to path and file name
WriteCSVByFrameName = [fileNoExt, 'ByFrame.csv'];   
    
%Remove file extension from path and file name
fileNoExt = Video_InputFile(1 : length(Video_InputFile) - 4);
    
%Append string and file extension to path and file name
WriteCSVByWindowName = [fileNoExt, 'ByWindow.csv'];   


%%%%%% Validation %%%%%%

%Extract path name
[path, ~, ~] = fileparts(WriteCSVByFrameName);

%Extract directory information from input video
listing = dir(path);

%Check wheter file exists
if isempty(listing) 
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: Folder specified for WriteCSVByFrameName does not appear to exist.' ...
        );
    
    throw(ME);
end


%Extract path name
[path, ~, ~] = fileparts(WriteCSVByWindowName);

%Extract directory information from input video
listing = dir(path);

%Check wheter file exists
if isempty(listing) 
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: Folder specified for WriteCSVByWindowName does not appear to exist.' ...
        );
    
    throw(ME);
end


%Extension csv required:

if ~ strcmp( '.csv', WriteCSVByFrameName(end - 3 : end) )
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: Extension .csv required for WriteCSVByFrameName.' ...
        );
    
    throw(ME);           
end

if ~ strcmp( '.csv', WriteCSVByWindowName(end - 3 : end) )
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: Extension .csv required for WriteCSVByWindowName.' ...
        );
    
    throw(ME);           
end


%Check whether files to be written to are locked by operating system:

%If locked, the likely cause is that files of the same name are open in another program.

TableTest = ...
    table( ...
        {''}, ...     
        'VariableNames', ... 
        { ...
            'Test', ...
        } ...
    ); 

%If files are locked, then the try will fail
try
    
    %Frame-by-frame table
    writetable(TableTest, WriteCSVByFrameName);

    %Pulse rate by window table
    writetable(TableTest, WriteCSVByWindowName);
    
    %Delete tables
    delete(WriteCSVByFrameName);
    delete(WriteCSVByWindowName);
    
catch

    %Change back-slash to forward-slash to avoid escaped characters:
    
    WriteCSVByFrameName_ForwdSlash = WriteCSVByFrameName;
    
    for i = 1 : length(WriteCSVByFrameName_ForwdSlash)

        if WriteCSVByFrameName_ForwdSlash(i) == '\'

            WriteCSVByFrameName_ForwdSlash(i) = '/';
        end   
    end

    WriteCSVByWindowName_ForwdSlash = WriteCSVByWindowName;
    
    for i = 1 : length(WriteCSVByWindowName_ForwdSlash)

        if WriteCSVByWindowName_ForwdSlash(i) == '\'

            WriteCSVByWindowName_ForwdSlash(i) = '/';
        end   
    end    
    
    %Throw error:
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: File ', WriteCSVByFrameName_ForwdSlash, ' or ', ...
             WriteCSVByWindowName_ForwdSlash, ' appears to be in use by another program.', ...
             ' Please close the file(s) before running FacePulseRate.'] ... 
        );
    
    throw(ME);    
end


%%%%%% Insert CSV settings into configuration struct

OutputConfig.WriteCSVByFrameName = WriteCSVByFrameName;
OutputConfig.WriteCSVByWindowName = WriteCSVByWindowName; 
OutputConfig.WriteCSV_TF = WriteCSV_TF;


end %end function

