function [ROI_Text, PulseRate_Text] = ...
             WriteFaceVideo_TextSetup(VideoReadConfig, PulseRateConfigAndData)
%WriteFaceVideo_TextSetup   Assign string arrays of pre-formatted text for use in ROI and pulse 
%                           rate annotations.
%   
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function WriteFaceVideo_AnnotationSetup.
%
%
%    Description
%    -----------
%
%    Increase efficiency by using vectorized operations in place of loop operations to prepare text
%    used for ROI and pulse rate annotations. To do so, return string arrays of text assigned with
%    vectorization to be used by the functions that insert the annotations into the frames 
%    (WriteFaceVideo_ROIAnnotation and WriteFaceVideo_PulseRate). These functions will index text 
%    from the string arrays rather than assigning text on each frame loop, increasing efficiency.
%
%    Regarding these functions, WriteFaceVideo_ROIAnnotation will index from the ROI text string 
%    array to insert ROI annotations and WriteFaceVideo_PulseRate will index from the pulse rate 
%    text string array to insert pulse rate annotations.
%    
%    Some text within the functions is still assigned on each loop because vectorizing the text 
%    here would be cumbersome.
%
%    Note: the functions that insert the text use compiled functions that expect a text length
%    under specified maximum. Therefore, if text is modified here, ensure that the compiled 
%    functions can accept the new lengths. For details, see functions WriteFaceVideo_ROIAnnotation  
%    and WriteFaceVideo_PulseRate.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Assign ROI annotation text %%%%%%

%%%%%% --- Prepare timestamp text %%%%%%

%Prepare M x 1 string array of timestamps:

%Example: 
%    "9.9583."
%    "10.0000."
%    "10.0417."
%    "10.0833."
%    ...

%Use function num2str because it can specify the number of decimal places. A consistent number of
%decimal places is desired for smoothness of appearance across frames. However, num2str returns
%characters rather than strings, so the assignment will be converted to type string. Once in type
%string, trim leading spaces that resulted as a side effect of using type char.
timestamps_String = ...
    strtrim( ... trim spaces
        string( ... convert to type string
            num2str( ... convert to characters (use num2str because decimal places can be specified)
                VideoReadConfig.FrameTimestamp_Single, ... frame timestamps 
                "%.4f."                                ... use 4 decimal places; add period
            ) ...
        ) ...
    );

%Prepend description to timestamp text:

%Example:
%    ". Time: 9.9583."
%    ". Time: 10.0000."
%    ". Time: 10.0417."
%    ". Time: 10.0833."
%    ...

Timestamp_Text = ...
    join( ...
         [repmat(". Time: ", VideoReadConfig.NFrames, 1), ...
          timestamps_String], ...
         "" ... no space between elements
    );

%%%%%% --- Prepare frame index text and concatenate with timestamp text %%%%%%

%Example:
%    "Frame: 237. Time: 9.9583."
%    "Frame: 238. Time: 10.0000."
%    "Frame: 239. Time: 10.0417."
%    "Frame: 240. Time: 10.0833."
%    ...

ROI_Text = ...
    join( ...
        [repmat("Frame: ", VideoReadConfig.NFrames, 1), ... 
         string(VideoReadConfig.FrameIdx'), ... frame index
         Timestamp_Text], ...
         "" ... no space between elements
    );


%%%%%% Assign pulse rate annotation text %%%%%%

%Text preparation conducted previously:

% - Most pulse rate values were previously rounded to an integer and converted to type string by 
%   function PulseRate_Algorithms, which was called by function PulseRate. The rounding and 
%   conversion were conducted in that function for efficiency. Other pulse rate values (namely, the 
%   externally-measured pulse rate) are rounded to an integer and converted to type string here.

%Text preparation conducted here:

% - Externally-measured pulse rate values are rounded to an integer and converted to type string. 
%   Other pulse rate measurements had these operations applied previously by function 
%   PulseRate_Algorithms.
% - '--' is displayed in place of 'NaN' to save some space.
% - '/' is used to separate non-luminance-controlled text from luminance-controlled text.
% - 'L' is appended to the luminance text to denote luminance-control.
% - 'EM' is prepended to the externally-measured text to denote that it is from an externally-
%   measured source.
% - Abbreviations are prepended to each pulse rate value to indicate the pulse-rate algorithm that
%   returned it. The abbrevations have the following meaning (for details on the algorithms, see
%   function PulseRate_Algorithms):
%    - 'C': CHROM_DEHAAN
%    - 'G': GREEN_VERKRUYSSE
%    - 'I': ICA_POH
%    - 'P': POS_WANG
            
%%%%%% --- Prepare non-externally-measured pulse rate values %%%%%%

%Example when luminance control is enabled:
%    " C: 68/63L"    " G: 48/63L"    " I: 63/53L"    " P: 136/46L"
%    " C: 68/63L"    " G: 48/63L"    " I: 63/53L"    " P: 136/46L"
%    " C: 68/63L"    " G: 48/63L"    " I: 63/53L"    " P: 136/46L"
%    " C: --"        " G: --"        " I: --"        " P: --"
%    ...

%Example when luminance control is not enabled:
%    " C: 68"    " G: 48"    " I: 63"    " P: 136"
%    " C: 68"    " G: 48"    " I: 63"    " P: 136"
%    " C: 68"    " G: 48"    " I: 63"    " P: 136"
%    " C: --"    " G: --"    " I: --"    " P: --"
%    ...

%Preallocate string array
PulseRate_Text = strings(VideoReadConfig.NFrames, 4);

%Loop across pulse rate algorithms
for i = 1 : 4

    %Assign pulse rate algorithm abbrevation for ith algorithm
    switch i
        case 1

            AlgSymbol = repmat("C: ", VideoReadConfig.NFrames, 1);

        case 2

            AlgSymbol = repmat(" G: ", VideoReadConfig.NFrames, 1);

        case 3

            AlgSymbol = repmat(" I: ", VideoReadConfig.NFrames, 1);

        case 4

            AlgSymbol = repmat(" P: ", VideoReadConfig.NFrames, 1);
    end    

    %Concatenate pulse rate value text for ith algorithm
    % - PulseRateConfigAndData.PulseRate.PulseRateExpanded_String: pulse rate values not controlled
    %   for luminance.
    % - PulseRateConfigAndData.PulseRate.PulseRateExpanded_LumControl_String: pulse rate values 
    %   controlled for luminance.
    
    %If luminance-control is enabled
    if PulseRateConfigAndData.ControlLuminanceTF   

        PulseRate_Text(:, i) = ...
            join( ...
                [AlgSymbol, ...
                 PulseRateConfigAndData.PulseRate.PulseRateExpanded_String(:, i), ... 
                 PulseRateConfigAndData.PulseRate.PulseRateExpanded_LumControl_String(:, i)], ...
                "" ... no space between elements
            );     
    
    %If luminance-control is disabled
    else
        
        PulseRate_Text(:, i) = ...
            join( ...
                [AlgSymbol, ...
                 PulseRateConfigAndData.PulseRate.PulseRateExpanded_String(:, i)], ...  
                "" ... no space between elements
            );           
    end
end

%%%%%% --- Concatenate text across columns (algorithms) %%%%%%

%Example when luminance control is enabled:
%    " C: 68/63L G: 48/63L I: 63/53L P: 136/46L"
%    " C: 68/63L G: 48/63L I: 63/53L P: 136/46L"
%    " C: 68/63L G: 48/63L I: 63/53L P: 136/46L"
%    " C: 68/63L G: 48/63L I: 63/53L P: 136/46L"
%    ...

%Example when luminance control is not enabled:
%    " C: 68 G: 48 I: 63 P: 136"
%    " C: 68 G: 48 I: 63 P: 136"
%    " C: 68 G: 48 I: 63 P: 136"
%    " C: 68 G: 48 I: 63 P: 136"
%    ...

PulseRate_Text = ...
    join( ...       
        PulseRate_Text, ...
        "", ... no space between elements
        2   ... combine across columns 
    );

%%%%%% --- Prepare externally-measured pulse rate text %%%%%%

%%%%%% >>>>>> Round and convert to string externally-measured pulse rate values %%%%%%

%If externally-measured pulse rate values included as argument PulseRateExternallyMeasured to 
%function FacePulseRate.
if ~ isempty(PulseRateConfigAndData.PulseRate.PulseRateExpanded_External)    

    %Example:
    %    " EM: 67;"
    %    " EM: 67;"
    %    " EM: 67;"
    %    " EM: --;"
    %    ...
    
    %EM = externally measured
    ExternalSymbol = repmat("EM: ", VideoReadConfig.NFrames, 1);

    %Round and convert externally-measured pulse rate values to string
    ExternalPulse = ...
        string( ...
            round( ...
                PulseRateConfigAndData.PulseRate.PulseRateExpanded_External ...
            ) ...
        );

    %Replace NaN with "--":
    
    NaNTF = isnan(PulseRateConfigAndData.PulseRate.PulseRateExpanded_External);

    if any(NaNTF)

        ExternalPulse(NaNTF) = "--";
    end

    %Add delimiter to separate externally-measured pulse rate text from other pulse rate text
    ExternalDelimiter = repmat("; ", VideoReadConfig.NFrames, 1);

    %Concatenate externally-measured pulse rate text
    ExternalString = ...
        join( ...
            [ExternalSymbol, ...
             ExternalPulse, ... 
             ExternalDelimiter
            ], ... 
            "" ... no space between elements
        );

    %%%%%% >>>>>> Concatenate externally-measured and non-externally-measured text %%%%%%    

    %Example:
    %    " EM: 67; C: 68/63L G: 48/63L I: 63/53L P: 136/46L"
    %    " EM: 67; C: 68/63L G: 48/63L I: 63/53L P: 136/46L"
    %    " EM: 67; C: 68/63L G: 48/63L I: 63/53L P: 136/46L"
    %    " EM: 67; C: 68/63L G: 48/63L I: 63/53L P: 136/46L"
    %    ...

    PulseRate_Text = ...
        join( ...
            [ExternalString, ...
             PulseRate_Text], ...
            "" ... no space between elements
        );    
end


end %end function

