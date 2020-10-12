function [TableByFrame, TableByWindow] = ...
             TableOutput(VideoReadConfig, ROI, HasROI_TF, FaceDetectConfig, SkinDetectConfig, ...       
                 PulseRateConfigAndData, SkinSegmentConfig, OutputConfig)
%TableOutput   Return results tables and/or write tables to csv files.
%
%    Helper function to function FacePulseRate.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Frame-by-frame table %%%%%%

TableByFrame = ...
    table( ...
        VideoReadConfig.FrameIdx', ...
        VideoReadConfig.FrameTimestamp_Double, ...
        ROI(:, 1), ...
        ROI(:, 2), ...
        ROI(:, 3), ...
        ROI(:, 4), ...
        string(HasROI_TF.FacePrimary), ...       
        'VariableNames', ... 
        { ...
            'Frame', ...
            'Timestamp_sec', ...
            'ROI_X_px', ...
            'ROI_Y_px', ...
            'ROI_Width_px', ...
            'ROI_Height_px', ...
            'Face_Detection_PrimaryTF' ...
        } ...
    ); 

if FaceDetectConfig.ROIFaceSecondary1TF 

   TableByFrame.Face_Detection_Secondary_TF = string(HasROI_TF.FaceSecondary1); 
end

if FaceDetectConfig.ROIFaceSecondary2TF 
    
    TableByFrame.Face_Detection_SecondaryAux_TF = string(HasROI_TF.FaceSecondary2);
end   
 
if SkinDetectConfig.ROISkinTF
    
    TableByFrame.Skin_Detection_TF = string(HasROI_TF.Skin);    
end
    
TableByFrame.Skin_Mean_R = PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 1);
TableByFrame.Skin_Mean_G = PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 2);
TableByFrame.Skin_Mean_B = PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 3);

%If calculating pulse rate is enabled
if PulseRateConfigAndData.TF

    %RGB means controlled for luminance
    if PulseRateConfigAndData.ControlLuminanceTF

        %Luminance mean is specified to be from YCbCr colorspace
        %Y is the luminance channel in the YCbCr colorspace.
        if PulseRateConfigAndData.ControlLuminanceColorspace == 'Y'

            %Luminance means
            TableByFrame.Skin_Luminance_Mean_YofYCbCr = ...
                PulseRateConfigAndData.ColorData.SkinLuminanceMeans.Y_of_YCbCr;

        %Luminance mean is specified to be from LAB colorspace
        %L is the luminance channel in the LAB colorspace.    
        elseif PulseRateConfigAndData.ControlLuminanceColorspace == 'L'

            %Luminance means
            TableByFrame.Skin_Luminance_Mean_LofLAB = ...
                PulseRateConfigAndData.ColorData.SkinLuminanceMeans.L_of_LAB;
        end

        %Red channel luminance-controlled means
        TableByFrame.Skin_Mean_LumControlled_R = ...
            PulseRateConfigAndData.ColorData.SkinRGBMeans_LumControl(:, 1);
        
        %Green channel luminance-controlled means
        TableByFrame.Skin_Mean_LumControlled_G = ...
            PulseRateConfigAndData.ColorData.SkinRGBMeans_LumControl(:, 2);
        
        %Blue channel luminance-controlled means
        TableByFrame.Skin_Mean_LumControlled_B = ...
            PulseRateConfigAndData.ColorData.SkinRGBMeans_LumControl(:, 3);               
    end    

    %Blood volume pulse and pulse rate:

    TableByFrame.BVP_Chrom_DeHaan     = PulseRateConfigAndData.BloodVolPulse.BloodVolPulse(:, 1);
    TableByFrame.BVP_Green_Verkruysse = PulseRateConfigAndData.BloodVolPulse.BloodVolPulse(:, 2);
    TableByFrame.BVP_ICA_Poh          = PulseRateConfigAndData.BloodVolPulse.BloodVolPulse(:, 3);
    TableByFrame.BVP_POS_Wang         = PulseRateConfigAndData.BloodVolPulse.BloodVolPulse(:, 4);
    
    TableByFrame.PulseRate_Chrom_DeHaan_bpm     = PulseRateConfigAndData.PulseRate.PulseRateExpanded(:, 1);
    TableByFrame.PulseRate_Green_Verkruysse_bpm = PulseRateConfigAndData.PulseRate.PulseRateExpanded(:, 2);
    TableByFrame.PulseRate_ICA_Poh_bpm          = PulseRateConfigAndData.PulseRate.PulseRateExpanded(:, 3);
    TableByFrame.PulseRate_POS_Wang_bpm         = PulseRateConfigAndData.PulseRate.PulseRateExpanded(:, 4);  
    
    %Blood volume pulse and pulse rate controlled for luminance:
    if PulseRateConfigAndData.ControlLuminanceTF
    
        TableByFrame.LumControl_BVP_Chrom_DeHaan     = ...
            PulseRateConfigAndData.BloodVolPulse.BloodVolPulse_LumControl(:, 1);
        TableByFrame.LumControl_BVP_Green_Verkruysse = ...
            PulseRateConfigAndData.BloodVolPulse.BloodVolPulse_LumControl(:, 2);
        TableByFrame.LumControl_BVP_ICA_Poh          = ...
            PulseRateConfigAndData.BloodVolPulse.BloodVolPulse_LumControl(:, 3);
        TableByFrame.LumControl_BVP_POS_Wang         = ...
            PulseRateConfigAndData.BloodVolPulse.BloodVolPulse_LumControl(:, 4); 

        TableByFrame.LumControl_PulseRate_Chrom_DeHaan_bpm     = ...
            PulseRateConfigAndData.PulseRate.PulseRateExpanded_LumControl(:, 1);
        TableByFrame.LumControl_PulseRate_Green_Verkruysse_bpm = ...
            PulseRateConfigAndData.PulseRate.PulseRateExpanded_LumControl(:, 2);
        TableByFrame.LumControl_PulseRate_ICA_Poh_bpm          = ...
            PulseRateConfigAndData.PulseRate.PulseRateExpanded_LumControl(:, 3);
        TableByFrame.LumControl_PulseRate_POS_Wang_bpm         = ...
            PulseRateConfigAndData.PulseRate.PulseRateExpanded_LumControl(:, 4); 
    end
     
    %Externally-measured pulse rate values supplied
    if ~ isempty(PulseRateConfigAndData.ExternallyMeasured)
     
        TableByFrame.PulseRate_ExternallyMeasured_bpm = ...
            PulseRateConfigAndData.PulseRate.PulseRateExpanded_External;
    end
end

%%%%%% --- Column of configurations %%%%%%

ScalarData = ...
    { ...
    'Frame_Width:'; ...
     VideoReadConfig.VidObj.Width; ...
     'Frame_Height:'; ...
     VideoReadConfig.VidObj.Height; ...
     'Frame_Rate:'; ...
     VideoReadConfig.FS; ...
     'Start_Time:'; ...
     VideoReadConfig.StartTime; ...
     'End_Time:'; ...
     VideoReadConfig.EndTime; ...
     'End_Time_Specified:'; ...
     VideoReadConfig.EndTimeSpecified; ...
     'Skin_Segmentation:'; ...
     string(SkinSegmentConfig.SkinSegmentTF); ... %convert from numeric to string so that string appears in output
     'Pulse_Rate_Window_sec';
     PulseRateConfigAndData.WindowDurationSec
     };

%Make ScalarData contain the number of rows equal to the number of rows in the table. 
ScalarData = [ScalarData; repmat({char.empty}, size(ROI, 1) - length(ScalarData), 1)];

TableByFrame.Parameters = ScalarData;


%%%%%% Pulse rate by window table %%%%%%

%Example:

% Block    Window    Chrom_DeHaan    Chrom_DeHaan_LumCon    Green_Verkruysse    Green_Verkruysse_LumCon    ICA_Poh    ICA_Poh_LumCon    POS_Wang    POS_Wang_LumCon 
% -----    ------    ------------    -------------------    ----------------    -----------------------    -------    --------------    --------    ---------------
% 1        1         68.5            71                     83                  87.6                       75.6       65.7              67.8        75.4
% 1        2         71              72.5                   84.5                88.6                       76.8       66.8              68.9        76.5
% 2        1         71.5            73.6                   85.6                89.7                       77.8       68.9              69.3        77.8
% 2        2         70.5            72.1                   86.7                90.1                       78.9       69.4              70.5        80

%%%%%% --- Preallocate table %%%%%%

%Vector of number of windows per block
nWindowsByBlock = zeros(PulseRateConfigAndData.nBlocks, 1, 'uint32');

for i = 1 : PulseRateConfigAndData.nBlocks
    
    nWindowsByBlock(i) = PulseRateConfigAndData.Block(i).nWindows;   
end
 
%Number of windows across blocks
nWindowsAllBlocks = sum(nWindowsByBlock);

%Preallocate table:

FieldPreallocate_Int = zeros(nWindowsAllBlocks, 1, 'uint32');

FieldPreallocate_Double = zeros(nWindowsAllBlocks, 1, 'double');

TableByWindow = ...
    table( ...
        FieldPreallocate_Int, ...
        FieldPreallocate_Int, ...
        FieldPreallocate_Double, ...
        FieldPreallocate_Double, ...
        FieldPreallocate_Double, ...
        FieldPreallocate_Double, ...
        FieldPreallocate_Double, ...     
        FieldPreallocate_Double, ...
        FieldPreallocate_Double, ...
        FieldPreallocate_Double, ...
        'VariableNames', ... 
        { ...
            'Block', ...
            'Window', ...
            'Chrom', ...
            'Chrom_LumCon', ...
            'Green', ...
            'Green_LumCon', ...
            'ICA', ...
            'ICA_LumCon', ...
            'POS', ...
            'POS_LumCon' ...
        } ...
    ); 

%Remove fields if controlling for luminance disabled
if ~ PulseRateConfigAndData.ControlLuminanceTF
    
    %Remove variables corresponding to luminance control
    TableByWindow = ...
        removevars( ...
            TableByWindow, ...
                {'Chrom_LumCon', ... 
                 'Green_LumCon', ... 
                 'ICA_LumCon', ... 
                 'POS_LumCon'} ...
            );
end

%%%%%% --- Add some table properties %%%%%%

%Description
TableByWindow.Properties.Description = 'Pulse Rate by Window';

%Input video file
TableByWindow = addprop(TableByWindow, {'SourceFile'}, {'table'});
TableByWindow.Properties.CustomProperties.SourceFile = VideoReadConfig.Video_InputFile;

%%%%%% --- Assign pulse rate data to table %%%%%%

%Note: see function PulseRate_Algorithms for a description of the structure of field
%PulseRateConfigAndData.PulseRate.PulseRate.Block. The structure of 
%PulseRateConfigAndData.PulseRate.PulseRate.Block is the same as that of 
%PulseRateConfigAndData.PulseRate.PulseRate_LumControl.Block.

BlockIdx = 1;
WinIdx = 1;

for i = 1 : nWindowsAllBlocks
    
    %If maximum window reached for a block
    if WinIdx > nWindowsByBlock(BlockIdx)
        
        %Advance to next block
        BlockIdx = BlockIdx + 1;
        
        %Exit if all blocks finished
        if BlockIdx > length(nWindowsByBlock)
        
            return
        end
        
        %Reset window index
        WinIdx = 1;
    end
    
    %Assign window index to ith row Block field
    TableByWindow.Block(i) = BlockIdx;
    
    %Assign window index to ith row Window field
    TableByWindow.Window(i) = WinIdx;

    %Assign pulse rate to ith block x window entry of field:
    
    TableByWindow.Chrom_DeHaan(i) = ...
        PulseRateConfigAndData.PulseRate.PulseRate(BlockIdx).Block(WinIdx, 1);  
    
    TableByWindow.Green_Verkruysse(i) = ...
        PulseRateConfigAndData.PulseRate.PulseRate(BlockIdx).Block(WinIdx, 2); 
    
    TableByWindow.ICA_Poh(i) = ...
        PulseRateConfigAndData.PulseRate.PulseRate(BlockIdx).Block(WinIdx, 3);     
      
    TableByWindow.POS_Wang(i) = ...
        PulseRateConfigAndData.PulseRate.PulseRate(BlockIdx).Block(WinIdx, 4);    

    %If controlling for luminance enabled
    if PulseRateConfigAndData.ControlLuminanceTF    
    
        TableByWindow.Chrom_DeHaan_LumCon(i) = ...
            PulseRateConfigAndData.PulseRate.PulseRate_LumControl(BlockIdx).Block(WinIdx, 1);  

        TableByWindow.Green_Verkruysse_LumCon(i) = ...
            PulseRateConfigAndData.PulseRate.PulseRate_LumControl(BlockIdx).Block(WinIdx, 2); 

        TableByWindow.ICA_Poh_LumCon(i) = ...
            PulseRateConfigAndData.PulseRate.PulseRate_LumControl(BlockIdx).Block(WinIdx, 3);     

        TableByWindow.POS_Wang_LumCon(i) = ...
            PulseRateConfigAndData.PulseRate.PulseRate_LumControl(BlockIdx).Block(WinIdx, 4);               
    end
    
    %Advance to next window
    WinIdx = WinIdx + 1;
end


%%%%%% Write tables as .csv files %%%%%%

%If writing table to file is enabled
if OutputConfig.WriteCSV_TF
    
    %Frame-by-frame table
    writetable(TableByFrame, OutputConfig.WriteCSVByFrameName);
    
    %Pulse rate by window table
    writetable(TableByWindow, OutputConfig.WriteCSVByWindowName);
    
    %Notification message
    message = '\ncsv output data written to files:';
             
    %Display notification message          
    fprintf(message);
    
    %Display directory name 
    %Display without escape characters by specifying %s.
    fprintf('\n    %s',   string(OutputConfig.WriteCSVByFrameName)); 
    fprintf('\n    %s\n', string(OutputConfig.WriteCSVByWindowName));
    
    %Display message immediately
    drawnow(); 
end


end %end function

