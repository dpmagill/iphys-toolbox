function [Video_InputFile, EndTimeSpecified, EndTime, PulseRateControlLuminance, ...
          UseCompiledFunctionsTF] = ...          
              ValidateAndConfigure_Validate(Video_InputFile, StartTime, EndTime, ...
                  ROISpecifyByArgument, ROIIgnoreByArgument, PulseRateTF, ...                 
                  PulseRateExternallyMeasured, PulseRateBlockTimestamps, ...                        
                  PulseRateControlLuminance, SkinSegmentThresholdsGenericYCbCr, ...
                  SkinSegmentThresholdsGenericHSV, DetectVerifyPercentilesYCbCrH, ...
                  DetectVerifyPercentilesS, UseCompiledFunctionsTF)                                                                  
%ValidateAndConfigure_Validate   Architecture, toolbox, argument, and flag validation for function 
%                                FacePulseRate. 
%                             
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ValidateAndConfigure.
%
%
%    Description
%    -----------
%
%    First, the architecture required for third-party executables is verified. Then, required 
%    Matlab toolboxes are checked against toolboxes installed, and input arguments to function 
%    FacePulseRate receive further validation (initial validation was conducted in the arguments 
%    block of function FacePulseRate). Internal flags (see function 
%    ValidateAndConfigure_InternalFlags) are also validated. 
%
%    Most of the input argument validation is conducted by the current function, but some 
%    validation is also conducted by the individual configuration functions (e.g., 
%    ROIGeneralConfig_Setup) within function ValidateAndConfigure.
%
%    Matlab exception handling documentation:
%
%    https://www.mathworks.com/help/matlab/ref/mexception.throw.html?s_tid=doc_ta
%    https://www.mathworks.com/help/matlab/ref/mexception.html?s_tid=doc_ta#d117e912083
% 
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author. 


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Display notification message %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  
message = '\n\nValidating inputs ...\n';

%Display message
fprintf(message);

%Display message immediately
drawnow(); 
    

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Architecture Check %%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%See note in description of FacePulseRate.

if ~ ( ...
       ispc() && strcmp( computer('arch'), 'win64' ) ...
       ... || ismac() && strcmp( computer('arch'), 'maci64' ) ... currently disabled
   )
    
    ME = ...
        MException( ...
            'Component:Architecture', ...
            'Error: FacePulseRate requires 64-bit Windows.' ...
        );
    
    throw(ME);   
end


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Toolbox Check %%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Note: These are the toolbox names as of Matlab release 2020b. Toolbox names occassionally change
%or are merged with other products.       

%Statistics and Machine Learning Toolbox: Various functions are used from this toolbox. Known to
%                                         Matlab as statistics_toolbox.

%Computer Vision System Toolbox:          Face-detection operations and video reading. Known to 
%                                         Matlab as video_and_image_blockset.

%Image Processing Toolbox:                Skin-segmentation and skin-detection operations. Known to  
%                                         Matlab as image_toolbox.

%Signal Processing Toolbox:               Butterworth filtering and periodogram for pulse rate  
%                                         operations. Known to Matlab as signal_toolbox.       

%DSP System Toolbox:                      Filtering operations for pulse rate operations. Known to
%                                         Matlab as signal_blocks.

%Optimization Toolbox:                    Used to find the minimum of a mathematical function. This  
%                                         is used to train RGB data in the skin-detection  
%                                         operations. Known to Matlab as optimization_toolbox.

ErrorText = [];

%If Statistics and Machine Learning Toolbox not installed
if ~ license('test', 'statistics_toolbox') 
    
    ErrorText = ...
        [ErrorText, ...
        '\n - Statistics and Machine Learning Toolbox'];
end

%If Computer Vision Toolbox not installed
if ~ license('test', 'video_and_image_blockset') 

    ErrorText = ...
        [ErrorText, ...
        '\n - Computer Vision Toolbox'];    
end

%If Image Processing Toolbox not installed
if ~ license('test', 'image_toolbox') 

    ErrorText = ...
        [ErrorText, ...
        '\n - Image Processing Toolbox'];       
end

%If Signal Processing Toolbox not installed
if ~ license('test', 'signal_toolbox') 

    ErrorText = ...
        [ErrorText, ...
        '\n - Signal Processing Toolbox'];        
end

%If DSP System Toolbox not installed
if ~ license('test', 'signal_blocks') 

    ErrorText = ...
        [ErrorText, ...
        '\n - DSP System Toolbox'];             
end

%If Optimization Toolbox not installed
if ~ license('test', 'optimization_toolbox') 
    
    ErrorText = ...
        [ErrorText, ...
        '\n - Optimization Toolbox'];  
end

%Display error message if a required toolbox is not installed
if ~ isempty(ErrorText)
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: The following Matlab toolboxes are required but not installed:', ... 
             ErrorText] ...
        ); 
    
    throw(ME);
end


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% String to Char Conversion %%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%Convert type string to type char:

Video_InputFile           = char(Video_InputFile);
PulseRateControlLuminance = char(PulseRateControlLuminance);    


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Video Reading %%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%Check whether input video file exists:

%Extract file information from input video
listing = dir(Video_InputFile);

%Check wheter file exists
if isempty(listing) 
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: File specified for Video_InputFile does not appear to exist.' ...
        );
    
    throw(ME);
end


%Check for characters that could cause issues using operating system shell commands:

%Shell commands used to execute ffmpeg.exe and ffprobe.exe.

%If the characters ',' OR ';' occur at least once in any of the file paths specified by argument
%This is to support compatibility with the command prompt, which cannot handle these characters.
if ~ isempty( regexp(Video_InputFile, '[,;]', 'Once') )

    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: file names cannot contain '','' or '';''.' ...
        );
    
    throw(ME);  
end 


%Check whether file extension for Video_InputFile is supported by system object VideoReader:

%Note: two video readers are used by function FacePulseRate: VideoReader and 
%vision.VideoFileReader. Only VideoReader is checked for support against the input video because
%VideoReader supports a larger number of video formats than vision.VideoFileReader. Function
%VideoReadConfig_Setup, which is called later, checks for support specifically for 
%vision.VideoFileReader. If it is not supported, only VideoReader is specified for use.

%Return structure containing supported VideoReader file extensions for the platform on which Matlab 
%is installed.
SupportedFileFormats = VideoReader.getFileFormats();

%Extract the last three characters of the input argument Video_InputFile, which should
%indicate the file extension.
Video_InputFile_Extension = char( Video_InputFile(end - 2 : end) );   

%Check whether there is not a match between the extension of Video_InputFile and a cell array of
%extensions corresponding to the supported file extensions.
if ~ ismember(Video_InputFile_Extension, {SupportedFileFormats.Extension})
     
    %Convert list of supported extensions and list of corresponding descriptions to cell arrays
    SupportedFileFormats_Extension = {SupportedFileFormats.Extension};
    SupportedFileFormats_Description = {SupportedFileFormats.Description};
    
    %Preallocate cell array for loop
    ExtensionAndDescriptionList = cell( length(SupportedFileExtentions), 1 ); 
    
    %Combine list of supported extensions and list of corresponding descriptions
    %Insert a new line escape character between each extension type so that displayed list appears
    %as a column vector.
    for i = 1 : length(SupportedFileExtentions)
    
        ExtensionAndDescriptionList{i} = ...
            ['\n.', SupportedFileFormats_Extension{i}, ' - ', SupportedFileFormats_Description{i}];
    end   
    
    %Concatenate across cell arrays
    ExtensionAndDescription = ...
        strjoin(ExtensionAndDescriptionList, ...
            ''); %delimiter
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: File extension specified in argument Video_InputFile is not', ...
             ' supported. Supported file extensions include...', ...
             ExtensionAndDescription] ...
        );
    
    throw(ME);          
end


%Setup VideoReader system object used in checks:

%Check whether the file can be successfully read by system object VideoReader:

%The existence of the file and the compatibility of the file extension were tested previously, so a
%lack of success here may indicate an unsupported format type. Although the file extension was 
%previously checked, the same file extension can be used with different encoding formats, some of 
%which may not be supported. Lack of support may be due either to limitations in VideoReader or to
%the required codecs not being installed.

%VidObj will also be used in additional checks.  

try

    VidObj = VideoReader(Video_InputFile);

    %Read the first frame
    read(VidObj, 1);
    
catch

    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: The format of the input video does not appear to be supported either by', ...
             ' Matlab video readers or by codecs installed on this computer. Try installing', ...
             ' the latest release of Matlab or using a different computer'] ...
        );
    
    throw(ME);    
end


%Verify that the input video is in color (not grayscale):

VidFrame = read(VidObj, 1);

[~, ~, NPages] = size(VidFrame);

if NPages ~= 3
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: Only color videos are supported.' ...
        );
    
    throw(ME);    
    
end


%Set EndTime if EndTime is not specified as argument:

%If EndTime is not specified as argument
if EndTime == -1
    
    %Set EndTime to the end of the video
    %Note: this value may be modified by function ROIMeans_FirstRead_Trim.
    EndTime = VidObj.Duration;
end


%Check that start time comes after end time:

if EndTime < StartTime  
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: EndTime cannot be less than StartTime.' ...
        );
    
    throw(ME);
end


%Check that EndTime does not exceed length of video:

%Record specified EndTime
EndTimeSpecified = EndTime;

%Adjust EndTime if greater than duration reported by VideoReader.

%Note: EndTime may be modified again in function ROIMeans_FirstRead when the first video read has
%completed and the accurate end time is known.

if EndTime > VidObj.Duration
    
    EndTime = VidObj.Duration;
    
    warning( ...
        'Component:Argument', ...
        ['EndTime is greater than video duration; EndTime adjusted to ', ...
         num2str(EndTime), '.'] ...
    );
end


%Set end time:

if EndTime == -1
    
    %End Time
    if EndTime == -1

        %Extract framerate and assign
        %Note: the final timestamp used throughout the function will be based upon the timestamp
        %read directly from the frame nearest to the EndTime, so it is OK if EndTime, as defined 
        %here, differs from that. 
        EndTime = floor(VidObj.Duration);  
    end
end


%Check whether video length exceeds maximum supported by FacePulseRate:

%Note: this would be highly unlikely but is included for completeness.
%This maximum is based upon the maximum integer available for type int32, which is used for
%indexing.
if EndTime - StartTime > intmax('int32') / VidObj.FR

    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: FacePulseRate does not support video lengths exceeding ', ...
             num2str( intmax('int32') / VidObj.FR ), ' seconds.'] ...
        );
    
    throw(ME);      
end


%Check whether frame dimensions exceed maximum supported by FacePulseRate:

%Note: The rationale for these bounds is noted in the description in file FacePulseRate.m.

if VidObj.Height > 5000 || VidObj.Width > 5000

    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: FacePulseRate does not support frame dimensions exceeding 5000 pixels.' ...
        );
    
    throw(ME);      
end


%Check if video length is relatively long:

%RAM demands may cause some systems to become unstable if video length exceeds 1.5 hours
if (EndTime - StartTime) / 60 / 60 > 1.5

    warning( ...
        'Component:Argument', ...
        ['RAM demands may cause some systems to become unstable when video length exceeds', ...
        ' 1.5 hours.'] ...
    );    
end



%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Skin Segmentation %%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%Skin-segmentation color thresholds:

if ~ (ismember(SkinSegmentThresholdsGenericYCbCr(1),        16 : 1 : 235)   && ...
      all( ismember(SkinSegmentThresholdsGenericYCbCr(2:5), 16 : 1 : 240) )    ...
     )

    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: SkinSegmentThresholdsGenericYCbCr(1) must be an integer', ...
             ' between 16 and 235 and SkinSegmentYCbCrThresholdsGeneric(2:5)', ...
             ' should be integers between 16 and 240.'] ...
        );
          
    throw(ME);
end

if ~ ( all( SkinSegmentThresholdsGenericHSV >= 0 ) && ...
       all( SkinSegmentThresholdsGenericHSV <= 1 ) ...
     )         

    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: values of SkinSegmentThresholdsGenericHSV must be between', ...
             ' 0 and 1 (inclusive).'] ...
        );
          
    throw(ME);
end

if ~ ( all( DetectVerifyPercentilesYCbCrH >= 0   ) && ...
       all( DetectVerifyPercentilesS      >= 0   ) && ...
       all( DetectVerifyPercentilesYCbCrH <= 100 ) && ...
       all( DetectVerifyPercentilesS      <= 100 ) )
              
    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: values of DetectVerifyPercentilesYCbCrH and', ... 
             ' DetectVerifyPercentilesS must be between 0 and 1 (inclusive).'] ...             
        );
          
    throw(ME);
end

if (DetectVerifyPercentilesYCbCrH(1) >= DetectVerifyPercentilesYCbCrH(2) )         

    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: DetectVerifyPercentilesYCbCrH(1) must be less than ', ... 
             ' DetectVerifyPercentilesYCbCrH(2).'] ...             
        );
          
    throw(ME);
end
 
if (DetectVerifyPercentilesS(1) >= DetectVerifyPercentilesS(2) )         

    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: DetectVerifyPercentilesS(1) must be less than ', ... 
             ' DetectVerifyPercentilesS(2).'] ...             
        );
          
    throw(ME);
end


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% ROI modifications %%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%ROISpecifyByArgument:

%Note: -1 are the default values, which indicate that this argument will not be used.
if ROISpecifyByArgument(1, 1) ~= -1 

    %If ROISpecifyByArgument does not contain positive values
    if any(ROISpecifyByArgument < 1, 'all')  

        ME = ...
            MException( ...
                'Component:Argument', ...
                'Error: ROISpecifyByArgument must contain positive integers.' ...
            );

        throw(ME);        
    end     
    
    %Check whether the ROI values exceed the frame dimensions           
    
    if any(ROISpecifyByArgument(:, 2) > VidObj.Width)  || ... X-coordinates
       any(ROISpecifyByArgument(:, 4) > VidObj.Width)  || ... width
       any(ROISpecifyByArgument(:, 3) > VidObj.Height) || ... Y-coordinates
       any(ROISpecifyByArgument(:, 5) > VidObj.Height)    %   height
            
        ME = ...
            MException( ...
                'Component:Argument', ...
                ['Error: ROISpecifyByArgument (columns 2 to 5) contains value(s) that exceed the', ...
                 ' video frame dimensions. Columns 2 and 4 (X-coordinate and width) cannot', ...
                 ' exceed frame width (', num2str(VidObj.Width),'). Columns 3 and 5 (Y-coordinate', ...
                 ' and height) cannot exceed frame height (', num2str(VidObj.Height),').'] ...
            );

        throw(ME);        
    end      
end
  

%ROIIgnoreByArgument:

%Note: -1 is the default value, which indicates that this argument will not be used.
if ROIIgnoreByArgument(1) ~= -1

    %If ROIIgnoreByArgument does not contain positive values
    if any(ROIIgnoreByArgument < 1)  

        ME = ...
            MException( ...
                'Component:Argument', ...
                'Error: ROIIgnoreByArgument must contain positive integer(s).' ...
            );

        throw(ME);        
    end      
end
    
    
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Pulse Rate %%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%Calculation of pulse rate enabled but specified video duration less than 2 seconds:

if PulseRateTF && (EndTime - StartTime) < 2   
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            ['Error: To calculate pulse rate with the CHROM_DEHAAN algorithm', ...
             ' video duration must be greater than or equal to 2 seconds.'] ...
        );
    
    throw(ME);
end


%PulseRateBlockTimestamps:

if PulseRateTF && ~ isempty(PulseRateBlockTimestamps)
    
    %If the start or end times of the blocks exceed the specified StartTime or EndTime
    if any(PulseRateBlockTimestamps < StartTime) || any(PulseRateBlockTimestamps > EndTime)
    
        ME = ...
            MException(...
                'Component:Argument', ...
                ['Error: Pulse rate block start or end time(s) do not fall within StartTime', ...
                 ' and EndTime.'] ...
            );

        throw(ME);
    end
    
    %There should be more than two elements. If not, user should StartTime and EndTime to
    %adjust times.
    if PulseRateBlockTimestamps < 3
        
        ME = ...
            MException( ...
                'Component:Argument', ...
                ['Error: The length of PulseRateBlockTimestamps must be greater than two.', ...
                 ' Adjust StartTime and EndTime to restrict assessment between two timestamps.'] ...
            );
 
        throw(ME);  
        
    end
    
    %If there are not an even number of block start times and end times
    if rem( numel(PulseRateBlockTimestamps), 2 ) ~= 0
    
        ME = ...
            MException( ...
                'Component:Argument', ...
                'Error: The number of pulse rate block times must be an even number.' ...
            );

        throw(ME);
    end
    
    %Determine whether vector is in chronological order
    %Check whether the difference between any time is negative.
    if any( diff(PulseRateBlockTimestamps) < 0 )
      
        ME = ...
            MException( ...
                'Component:Argument', ...
                ['Error: Pulse rate block start and end times must be in chronological order,' ...
                 ' e.g., [100, 200, 400, 500].'] ...
            );
    
        throw(ME);       
    end    
end


%PulseRateControlLuminance:

if ~ PulseRateControlLuminance == 'F' && ...
   ~ PulseRateTF
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: To control RGB for luminance, PulseRateTF must be enabled' ...
        );
    
    throw(ME);          
end

if ~ PulseRateControlLuminance == 'Y' && ...
   ~ PulseRateControlLuminance == 'L' && ...
   ~ PulseRateControlLuminance == 'F' 
    
    ME = ...
        MException( ...
            'Component:Argument', ...
            'Error: PulseRateControlLuminance accepts characters ''Y'', ''L'', and ''F''.' ...
        );
    
    throw(ME);         
end


%PulseRateExternallyMeasured:
   
%Externally-measured pulse rate values supplied
if ~ isempty(PulseRateExternallyMeasured)
    
    if ~ PulseRateTF
     
     ME = ...
         MException( ...
            'Component:Argument', ...
            ['Error: PulseRateTF must be enabled to include values for', ...
             ' PulseRateExternallyMeasured.'] ...
         );

        throw(ME);      
    end
    
    %For both non-cell arrays and cell arrays:
    
    %Dimensions
    if numel( size(PulseRateExternallyMeasured) ) ~= 2   || ... Should be 2-dimensional
       nnz( size(PulseRateExternallyMeasured) == 1) ~= 1    %   The length of one-dimension, and only 
                                                            %   one dimension, is 1.
        ME = ...
            MException( ...
                'Component:Argument', ...
                ['Error: PulseRateExternallyMeasured should be a 2-dimensional vector or cell', ...
                 ' array where one dimesion has length 1 and the other dimesion has length', ...
                 ' greater than one.'] ...
            );

        throw(ME);                
    end
    
    %--- If non-cell array 
    if ~ iscell(PulseRateExternallyMeasured)
   
        %Must be numeric
        if ~ isnumeric(PulseRateExternallyMeasured)
         
            ME = ...
                MException( ...
                    'Component:Argument', ...
                    ['Error: PulseRateExternallyMeasured must either be numeric or a cell', ...
                     ' array with numeric elements.'] ...
                );
    
            throw(ME);
        end
        
        %Check whether exceeds span between StartTime and EndTime
        if length(PulseRateExternallyMeasured) > EndTime - StartTime
            
            ME = ...
                MException( ...
                    'Component:Argument', ...
                    ['Error: The length of the contents of PulseRateExternallyMeasured should', ...
                     ' not exceed the span between StartTime and EndTime.', ...
                     ' This is because it is expected that PulseRateExternallyMeasured is', ... 
                     ' aggregated to seconds.'] ...
                );
    
            throw(ME);              
        end
        
        %Check whether exceeds duration of video
               
        if length(PulseRateExternallyMeasured) > VidObj.Duration
        
            ME = ...
                MException( ...
                    'Component:Argument', ...
                    ['Error: The length of the contents of PulseRateExternallyMeasured cannot', ...
                     ' be greater than the duration (in seconds) of the input video.', ...
                     ' This is because it is expected that PulseRateExternallyMeasured is', ... 
                     ' aggregated to seconds. The duration of the video is checked against', ...
                     ' the duration returned by VidObj = VideoReader(<Input File>);', ...
                     ' VidObj.Duration.'] ...
                );
    
            throw(ME);            
        end
    
        %PulseRateBlockTimestamps should be empty if PulseRateExternallyMeasured is not a cell
        %array.
        if ~ isempty(PulseRateBlockTimestamps)
            
            ME = ...
                MException( ...
                    'Component:Argument', ...
                    ['Error: PulseRateBlockTimestamps cannot be used if', ...
                     ' PulseRateExternallyMeasured is not a cell array.', ... 
                     ' Adjust StartTime and EndTime to restrict assessment between only', ...
                     ' two timestamps.'] ...
               );
 
            throw(ME);                 
        end
               
        %Display duration of PulseRateExternallyMeasured for user verificiation:
        fprintf( ...
            ['External PR durations (sec.): ', ...
             sprintf('\t%d', length(PulseRateExternallyMeasured)),    '\n'] ...
        ); 
        
    %--- If cell array   
    else

        %Must be numeric
        if ~ isnumeric([PulseRateExternallyMeasured{:}])
         
            ME = ...
                MException( ...
                    'Component:Argument', ...
                    ['Error: PulseRateExternallyMeasured must either be numeric or a cell', ...
                     ' array with numeric elements.'] ...
                );
    
            throw(ME);
        end
        
        %Obtain length of contents of each cell       
        CellLengths = zeros(length(PulseRateExternallyMeasured), 1);
        
        for i = 1 : length(PulseRateExternallyMeasured)
        
            CellLengths(i) = length(PulseRateExternallyMeasured{i});
        end
        
        %Subtract 1 to convert to duration.
        CellDurations = CellLengths - 1;
        
        %Check whether sum of contents exceeds span between StartTime and EndTime
         
        if sum(CellDurations) > EndTime - StartTime
            
            ME = ...
                MException( ...
                    'Component:Argument', ...
                    ['Error: The length of the contents of PulseRateExternallyMeasured cannot', ...
                     ' exceed the span between StartTime and EndTime.', ...
                     ' This is because it is expected that PulseRateExternallyMeasured is', ... 
                     ' aggregated to seconds.'] ...
                );
    
            throw(ME);              
        end
        
        %Check whether contents exceeds duration of video
               
        if sum(CellDurations) > VidObj.Duration
        
            ME = ...
                MException( ...
                    'Component:Argument', ...
                    ['Error: The length of the contents of PulseRateExternallyMeasured cannot', ...
                     ' be greater than the duration (in seconds) of the input video.', ...
                     ' This is because it is expected that PulseRateExternallyMeasured is', ... 
                     ' aggregated to seconds. The duration of the video is checked against the', ...
                     ' duration returned by VidObj = VideoReader(<Input File>); VidObj.Duration.'] ...
                );
    
            throw(ME);            
        end
        
        %PulseRateBlockTimestamps should be non-empty
        if isempty(PulseRateBlockTimestamps)
    
            ME = ...
                MException( ...
                    'Component:Argument', ...
                    ['Error: A cell array can used for PulseRateExternallyMeasured', ...
                     ' only when PulseRateBlockTimestamps is non-empty.'] ...
                );
    
            throw(ME);
        end
        
        %Length correspondence between PulseRateBlockTimestamps and PulseRateExternallyMeasured       
        if length(PulseRateBlockTimestamps) / 2 ~= length(PulseRateExternallyMeasured) %should be equal
            
            ME = ...
                MException( ...
                    'Component:Argument', ...
                    ['Error: The length of PulseRateBlockTimestamps divided by 2 must', ...
                     ' be equal to the length of the cell array provided for', ...
                     ' PulseRateExternallyMeasured.'] ...
                );
    
            throw(ME);             
        end   
        
        %Display durations of PulseRateBlockTimestamps and PulseRateExternallyMeasured for
        %user verificiation:

        %Convert the block timestamps to an M-by-2 matrix:   

        %Logical index
        Col1Idx = repmat([true, false], 1, length(PulseRateBlockTimestamps) / 2);
        Col2Idx = ~ Col1Idx;

        %Rearrange to m-by-2
        PulseRateBlockTimestamps_Mx2(:, 1) = PulseRateBlockTimestamps(Col1Idx);
        PulseRateBlockTimestamps_Mx2(:, 2) = PulseRateBlockTimestamps(Col2Idx);

        %Durations of each block
        BlockDurations = ...
            PulseRateBlockTimestamps_Mx2(:, 2) - PulseRateBlockTimestamps_Mx2(:, 1);

        fprintf(['\nSpecified block durations (sec.): ', sprintf('\t%d', BlockDurations), '\n']);
        fprintf([  'External PR durations (sec.):     ', sprintf('\t%d', CellDurations),   '\n']); 
        
    end %end if cell array 
end 


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Compiled Functions %%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%Binaries are currently available only for 64-bit Windows. 

if UseCompiledFunctionsTF && ...
   ~ ( ispc() && strcmp(computer('arch'), 'win64') )
    
    message = ...
        ['\n\nNote: Compiled versions of functions are currently only implemented for use', ...
        '\non 64-bit Windows platforms. On other platforms, these compiled functions will', ...
        '\nnot be used. This may result in slower operations compared to when compiled', ...
        '\nfunctions are used.\n'];

    %Display message
    fprintf(message);

    %Display message immediately
    drawnow();     
   
    UseCompiledFunctionsTF = false;
end


end %end function

