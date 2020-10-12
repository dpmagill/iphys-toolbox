function [ROIMinWidthProportion, ROIMinHeightProportion] = ...
             ROIGeneralConfig_Setup_MinROIProportions(ROIMinWidthProportion, ...
                 ROIMinHeightProportion, ROIFacePrimaryXML, VideoReadConfig)
%ROIGeneralConfig_Setup_MinROIProportions   Set the minimum size proportions at which ROIs will be 
%                                           accepted from the face-detection algorithm.
%                      
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIGeneralConfig_Setup. 
%
%
%    Description
%    -----------
%
%    Specify a minimum size if a minimum size was not entered as arguments to function 
%    FacePulseRate. The minimum size is defined by two proportions, ROIMinWidthProportion and 
%    ROIMinHeightProportion. To do so, sample the ROI sizes of detections returned by the primary 
%    face-detection algorithm. Then, take the median of the ROI sizes as the basis for the minimum  
%    size. Reduce the median slightly to avoid setting the minimum as too large. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.  


%If no argument was entered for one or both of the proportions
if ROIMinWidthProportion == -1 || ROIMinHeightProportion == -1
    
    %Numer of sample detections to take
    NSamples = 48;
    
    %Because the last frames may be estimated and may not actually exist, only sample up to a 
    %buffer from the last frame index.
    FrameIdxBuffer = 50;    
    
    %Number of frame estimated indices
    
    %Note: neither NFrames nor the length of VideoReadConfig.FrameIdx is used to determine the 
    %number of frames because these values will sometimes be much longer than the number of frames  
    %to be processed.
    %Scalar integer; type double.
    NFrames = floor( (VideoReadConfig.EndTime - VideoReadConfig.StartTime) * VideoReadConfig.FS );
    
    
    %%%%%% Insufficient number of frames for sampling %%%%%%
    
    %If there is an insufficient number of frames from which to take samples. There may be an 
    %insufficient number of frames if the duration of the video to be processed is quite short.    
    
    if NFrames < NSamples + FrameIdxBuffer
 
        %Use generic proportions rather than calculating them through sampling     
        UseGenericProportionsTF = true;         

        
    %%%%%% Sufficient number of frames for sampling %%%%%%        
        
    %If there is a sufficient number of frames from which to take samples  
    else
        
        %Notification message
        message = '\nDetermining minimum ROI size ...\n';

        %Display message
        fprintf(message);

        %Display message immediately
        drawnow();     

        %%%%%% --- Setup %%%%%%   

        %Initialize Viola-Jones detector object using primary face-detection algorithm
        faceDetectorPrimary = ...
            vision.CascadeObjectDetector( ...
                ROIFacePrimaryXML, ...
                'MergeThreshold', 5 ...
            );

        %%%%%% --- Determine frame indices from which to take sample detections %%%%%%

        %Sample using a stratified random sample. Stratify by quartiles of the frame index to ensure
        %sampling across the length of the video. Within a quartile, use pseudorandom sampling. The 
        %maximum possible index will be slightly less than the last frame index in 
        %VideoReadConfig.FrameIdx because, at this point, the number of frame indices may be an 
        %estimation (see function VideoReadConfig_Setup).

        %Determine the number of frame indices within a quartile                                                    
        FrameIdxQuartile = ...
            int32( ...
                floor( (NFrames - FrameIdxBuffer) / 4 ) ...
            );

        %Preallocate an index of frame indices from which sample detections will be taken
        IndicesSample = zeros(48, 1, 'uint32');

        %Initialize loop indices
        EndIdx = int32( floor(VideoReadConfig.StartTime * VideoReadConfig.FS) );    
        EndIdxSample = 0;

        %Assign frame indices at which to take samples
        for i = 1 : 4

            %Note: this value must be at least 1
            BeginIdx = int32(EndIdx + 1);
            
            assert(BeginIdx >= 1);

            EndIdx = ...
                int32( ...
                    min( EndIdx + FrameIdxQuartile, VideoReadConfig.FrameIdx(end) ) ...
                );

            BeginIdxSample = EndIdxSample + 1;

            EndIdxSample = EndIdxSample + 12;

            %Assign frame indices at which to take samples for ith quartile
            IndicesSample(BeginIdxSample : EndIdxSample) = ...
                sort(                                        ... Sort indices in case this makes 
                                                             ... seeking through the video more 
                                                             ... efficient.
                    randi(                                   ... Pseudorandom integers
                        [VideoReadConfig.FrameIdx(BeginIdx), ... Minimum index of ith quartile
                         VideoReadConfig.FrameIdx(EndIdx)],  ... Maximum index of ith quartile
                         1,                                  ... 
                         12                                  ... Number of samples (indices)
                     ) ...
                );               
        end

        %%%%%% --- Read video at specified frame indices to sample detections %%%%%%

        %Extract video reader object
        VideoReadConfig_VidObj = VideoReadConfig.VidObj;

        %Preallocate matrix to hold ROI widths and heights from detections
        ROISample = zeros(48, 2, 'uint32');

        %Loop across sample of frame indices
        for i = 1 : 48

            FrameIdx = IndicesSample(i);

            %Read ith frame
            VidFrame = read(VideoReadConfig_VidObj, FrameIdx);  

            %Convert frame to grayscale
            VidFrameGray = rgb2gray(VidFrame); 

            %Find ROI(s) using the Viola-Jones detector specified for the primary face-detection 
            %algorithm.
            %M x 4 row vector; type double.
            ROI = faceDetectorPrimary(VidFrameGray);

            %Number of rows from ROI
            %The number of rows corresponds to the number of detections made in a given frame.
            ROINRows = size(ROI, 1);

            %Add ith ROI width and height values to matrix
            %An empty ROI indicates no detection was made.       
            if ROINRows ~= 0            

                %If one ROI returned for ith frame
                if ROINRows == 1

                    ROISample(i, :) = ROI(3 : 4);

                %If more than one ROI returned for ith frame
                %For some frames, multiple ROIs may be returned, although this would be considered
                %erroneous because there should only be one face in the frame. In this case, select the
                %first ROI with a width of at least 50 pixels.
                else %ROINRows > 1               

                    for j = 1 : ROINRows

                        if ROI(j, 3) > 50

                            ROISample(i, :) = ROI(j, 3 : 4);
                        end
                    end    
                end
            end
        end   

        %%%%%% --- Determine minimum proportions based upon ROIs from sampled detections %%%%%%    

        %Number of samples in which a detection was made 
        NROISamples = nnz( ROISample(:, 1) );
        
        %If at least five samples correspond a detection
        if NROISamples >= 5

            %Do not use generic proportions
            UseGenericProportionsTF = false;            
            
            %If any values in the matrix are zero
            if NSamples - NROISamples > 0

                %Remove any rows in the matrix where a value is zero
                %A row will contain zeros if no detection was made for the corresponding frame. 
                ROISample = ROISample( all(ROISample ~= 0, 2) , :);
            end

            %Take column-wise median width and height
            %1 x 2 row vector.
            ROISample_Median = median(ROISample, 1);

            %Reduce the median width and height by about 1/6 to ensure some valid detections are  
            %not ruled out.    
            %1 x 2 row vector.
            ROISample_Median = ROISample_Median - ROISample_Median ./ uint32(6);

            %Convert the width and height to a proportion out of the total:  

            %Width proportion
            %Note: -1 is a flag that no argument was entered for the width proportion.
            if ROIMinWidthProportion == -1

                %Width proportion 
                %Reduced width / total width.
                ROIMinWidthProportion = ...
                    double( ROISample_Median(1) ) / double(VideoReadConfig.VidObj.Width); 
            end

            %Height proportion   
            %Note: -1 is a flag that no argument was entered for the height proportion.        
            if ROIMinHeightProportion == -1

                %Height proportion
                %Reduced height / total height.  
                ROIMinHeightProportion = ...
                    double( ROISample_Median(2) ) / double(VideoReadConfig.VidObj.Height);    
            end

        %If fewer than 5 samples correspond to a detection        
        else

            %Use generic proportions as the proportions cannot be calculated    
            UseGenericProportionsTF = true;       
        end    
    end
    
    
    %%%%%% Use generic proportions rather than calculated proportions %%%%%%
    
    %If generic proportions should be used
    if UseGenericProportionsTF    
                
        %Width proportion
        %Note: -1 is a flag that no argument was entered for the width proportion.
        if ROIMinWidthProportion == -1
        
            %Width proportion 
            %Reduced width / total width.
            ROIMinWidthProportion = .09;
        end

        %Height proportion   
        %Note: -1 is a flag that no argument was entered for the height proportion.        
        if ROIMinHeightProportion == -1
        
            %Height proportion
            %Reduced height / total height.  
            ROIMinHeightProportion = .19;    
        end        
    end
end


end %end function

