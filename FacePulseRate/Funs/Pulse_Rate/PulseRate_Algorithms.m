function [BVP, PR, PRExpanded, PRExpanded_String] = ...
             PulseRate_Algorithms(PulseRateConfigAndData, VideoReadConfig, ...
                 FrameTimestamp_Double, LumControlTF)
%PulseRate_Algorithms   Calculate blood volume pulse (BVP) and pulse rate within specified windows  
%                       from ROI RGB means using several algorithms. 
%                      
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function PulseRate.
%
%
%    Description
%    -----------
%
%    Calculate blood volume pulse (BVP) and pulse rate within specified windows from ROI RGB means  
%    using several algorithms.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Preallocate for loop %%%%%%

%For each window, four separate algorithms estimate frame-by-frame blood volume pulse (BVP) from 
%ROI RGB means. This results in four estimated-BVP vectors for each window.

%%%%%% --- Vector for BVP %%%%%%

%Preallocate matrix to which the BVP data from three algorithms will be assigned.
%Use NaN in case some frames are not specified by the blocks.
%For algorithm CHROM-DEHAAN, the length of its output vector is sometimes less than the length of 
%specified frames, so NaN could may be returned by this algorithm for frames within a block.
%Type double is required for pulse rate algorithms.
BVP = NaN(length(FrameTimestamp_Double), 4);

%%%%%% --- Struct to hold mean externally-measured pulse rate by block and by window %%%%%%  

%For details on structure, see section "Assign pulse rates" below.
PR = ...
    struct( ...
        'Block', cell(PulseRateConfigAndData.nBlocks, 1) ...
    );

%%%%%% --- Matrix for pulse rate expanded to frame-by-frame length %%%%%%

%Preallocate matrix to which the pulse rates for each frame will be assigned
%The frames will be assigned the pulse rates that correspond to the window to which they belong.
%Specify type single for memory conservation.
PRExpanded = NaN(length(FrameTimestamp_Double), 4, 'single');

%Preallocate string matrix for pulse rate values in format used for text annotations on output
%video.
PRExpanded_String = strings(length(FrameTimestamp_Double), 4);


%%%%%%  Calculate BVP and pulse rate for each window %%%%%%

%Loop across blocks
for i = 1 : PulseRateConfigAndData.nBlocks %number of blocks
    
    %Extract from struct for readibility
    nWindows        = PulseRateConfigAndData.Block(i).nWindows;
    windowsStartIdx = PulseRateConfigAndData.Block(i).windowsStartIdx;
    windowsEndIdx   = PulseRateConfigAndData.Block(i).windowsEndIdx;
    
    %%%%%% --- Calculate BVP and pulse rate for each window within a block %%%%%%

    %Preallocate matrix to which the pulse rates for each window will be assigned.
    %For each window, each of the four algorithms estimates one pulse rate based upon its BVP 
    %vector. This results in four estimated pulse rates for each window.
    PRWindows = zeros(nWindows, 4);

    %Loop across windows within a block to calculate BVP and pulse rate
    for j = 1 : nWindows

        %%%%%% >>>>>> Specify BVP / pulse rate function input arguments to be modified each iteration %%%%%%

        %ROI RGB values within ith window            
        if ~ LumControlTF %do not use ROI RGB means controlled for luminance
            
            SkinRGBMeansWindow = ...
                PulseRateConfigAndData.ColorData.SkinRGBMeans( ...
                    windowsStartIdx(j) : windowsEndIdx(j), ...
                    : ...
                );
        
        else %use ROI RGB means controlled for luminance
            
            SkinRGBMeansWindow = ...
                PulseRateConfigAndData.ColorData.SkinRGBMeans_LumControl( ...
                    windowsStartIdx(j) : windowsEndIdx(j), ...
                    : ...
                );               
        end
            
        %Timestamps corresponding to jth window
        TWindow          = FrameTimestamp_Double(windowsStartIdx(j) : windowsEndIdx(j)); %all timestamps of jth window
        
        %Use the following for plotting, which is not currently implemented
        %{
        
        TWindowStartTime = TWindow(1);   %staring timestamp of ith window
        TWindowEndTime   = TWindow(end); %ending timestamp of ith window

        %}
        
        %Assign frame index to assign BVP output 
        FrameIdxWindow = windowsStartIdx(j) : windowsEndIdx(j);

        %%%%%% >>>>>> Call four separate ROI RGB-to-pulse rate algorithms %%%%%%

        %Initialize flag indicating whether the general input arguments have been validated
        GeneralValidationCompleted_TF = false;
        
        %Note: PulseRate_iPhysToolboxWrapper is a custom function located within folder
        %'FacePulseRate'.
        
        %CHROM_DEHAAN:
        
        Alg = 'C';
        
        [BVP_jthWindow, PR_jthWindow] = ...
             PulseRate_iPhysToolboxWrapper(Alg, SkinRGBMeansWindow, VideoReadConfig, TWindow, ...
                 GeneralValidationCompleted_TF);
             
        %The general input arguments were validated     
        GeneralValidationCompleted_TF = true;     
             
        %Assign CHROM_DEHAAN BVP output to vector according to length of output because this length 
        %can sometimes be less than the length of input RGB means.
        BVP(FrameIdxWindow(1) : FrameIdxWindow(1) - 1 + length(BVP_jthWindow), 1) = BVP_jthWindow;
                   
        PRWindows(j, 1) = PR_jthWindow;

        %GREEN_VERKRUYSSE:         
        
        Alg = 'G';
        
        [BVP_jthWindow, PR_jthWindow] = ...
             PulseRate_iPhysToolboxWrapper(Alg, SkinRGBMeansWindow, VideoReadConfig, TWindow, ...
                 GeneralValidationCompleted_TF);
                     
        BVP(FrameIdxWindow, 2) = BVP_jthWindow;
        PRWindows(j, 2) = PR_jthWindow; 
        
        %ICA_POH:     
        
        Alg = 'I';
        
        [BVP_jthWindow, PR_jthWindow] = ...
             PulseRate_iPhysToolboxWrapper(Alg, SkinRGBMeansWindow, VideoReadConfig, TWindow, ...
                 GeneralValidationCompleted_TF);          
        
        BVP(FrameIdxWindow, 3) = BVP_jthWindow;
        PRWindows(j, 3) = PR_jthWindow; 
        
        %POS_WANG: 
        
        Alg = 'P';
        
        [BVP_jthWindow, PR_jthWindow] = ...
             PulseRate_iPhysToolboxWrapper(Alg, SkinRGBMeansWindow, VideoReadConfig, TWindow, ...
                 GeneralValidationCompleted_TF);          
        
        BVP(FrameIdxWindow, 4) = BVP_jthWindow;
        PRWindows(j, 4) = PR_jthWindow; 
    end 
    
    %%%%%% --- Assign pulse rates %%%%%%

    %Loop across windows 
    for j = 1 : nWindows

        %Assign pulse rate by block and by window to field PR.Block.
                
        %Description: 
        
        % - One block
        
        %One block will be used if only two values specified for argument PulseRateBlockTimestamps 
        %or if argument PulseRateBlockTimestamps not used. 
        
        %In this case, field PR.Block will consist of one row. Within this row, a matrix will be
        %assigned. The rows of the matrix indicate separate windows and the columns indicate the
        %algorithm used. The order of the algorithms across the columns is CHROM_DEHAAN,
        %GREEN_VERKRUYSSE, ICA_POH, and POS_WANG. An example of field PR.Block with one block and
        %two windows is shown below. 
        
        % Window    CHROM_DEHAAN    GREEN_VERKRUYSSE    ICA_POH    POS_WANG
        % _____    ____________    ________________    _______    _________
        % 1         68              70                  72         71
        % 2         70              73                  71         72
        
        % - More than one block
        
        %More than one block will be used if more than two values are specified for argument  
        %PulseRateBlockTimestamps. 
        
        %In this case, the rows in field PR.Block will be equal to the number of blocks. Within 
        %each row, a matrix will be assigned. The rows of each matrix indicate separate windows and 
        %the columns indicate the algorithm used. The order of the algorithms across the columns is 
        %CHROM_DEHAAN, GREEN_VERKRUYSSE, ICA_POH, and POS_WANG. An example of field PR.Block with 
        %more than one block, and each block with a variable number of windows, is shown below. 
        
        % Block    Window    CHROM_DEHAAN    GREEN_VERKRUYSSE    ICA_POH    POS_WANG
        % _____    ______    ____________    ________________    _______    _________
        % 1        1         68              70                  72         71
        %          2         70              73                  71         72 
        % --------------------------------------------------------------------------- 
        % 2        1         71              70                  72         73
        %          2         73              74                  72         72
        %          3         70              72                  70         71        
        
        
        PR(i).Block(j, :) = PRWindows(j, :);
        
        %Assign pulse rate expanded to frame-by-frame length by block and by window 
        %Also convert to type single for memory conservation.
        PRExpanded(windowsStartIdx(j) : windowsEndIdx(j), :) = ...
            single( ...
                repmat(PRWindows(j, :), length(windowsStartIdx(j) : windowsEndIdx(j)), 1) ...
            ); 
 
        %Assign pulse rate expanded to frame-by-frame length by block and by window in format used
        %for text annotations on output video.
        %For details on the use of the string array that is assigned, see functions 
        %WriteFaceVideo_PulseRateSetup and WriteFaceVideo_PulseRate.
        %Assigns M x 4 string array.
        %Nested function.
        PrepareForVideo();       
    end 

end %end block (i) loop


%%%%%% Convert to type single for memory conservation %%%%%%

BVP = single(BVP);


%================================================================================================
%Nested functions 
%================================================================================================


%================================================================================================
function PrepareForVideo()
%PrepareForVideo    Modify pulse rate values to format used for text annotations on output video.
%
%    Description:
%
%    Round pulse rate values to integer and convert to type string for use on output video. See 
%    function WriteFaceVideo_PulseRate, which is called by function WriteFaceVideo.
%
%    In some cases, C may be NaN while the others are not, so isnan needs to be evaluated 
%    separately for C. For increased robustness, isnan is evaluated separately for each.  


%Loop across pulse-rate algorithms
for k = 1 : size(PRExpanded_String, 2)

    %If NaN, use "--"
    if isnan( PRWindows(j, k) )

        %Luminance control is not activated on this call to the function
        if ~ LumControlTF
            
            str = "--";
            
        %Luminance control is activated on this call to the function    
        else

            %Use '' rather than '--' because '--' will already be present from  
            %non-luminance-controlled text in annotation            
            
            str = "";
        end

    %If not NaN, round to integer and convert to type string    
    else
        
        %Luminance control is not activated on this call to the function
        if ~ LumControlTF
            
            str = ...
                sprintf("%d", ... type string
                    round( ... round to integer
                        PRWindows(j, k) ...
                    ) ...
                ); 
            
        %Luminance control is activated on this call to the function             
        else

            %Place '/' as separator between non-luminance-controlled text and luminance-controlled 
            %text in annotation.
            %Append 'L' to denote luminance-controlled.            
            
            str = ...
                sprintf("/%dL", ... type string
                    round( ... round to integer
                        PRWindows(j, k) ...
                    ) ...
                );
        end
    end

    %Expand to number of frame within window
    PRExpanded_String(windowsStartIdx(j) : windowsEndIdx(j), k) = ...    
        repmat(...
            str, ...
            length(windowsStartIdx(j) : windowsEndIdx(j)), ...
            1 ...
        );
end


end %end nested function


end %end main function



