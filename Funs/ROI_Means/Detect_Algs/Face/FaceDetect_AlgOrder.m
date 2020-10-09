function FaceDetectAlgorithmsOrdered = ...
             FaceDetect_AlgOrder(i, HasROI_TF, Algorithms, NAlgs, SecAlg, ...
                 ExpediteColorThresholdsTF)
%FaceDetect_AlgOrder  Determine order that the face-detection algorithms will be applied.                            
%                                
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead_AlgSelector_Face.
%
%
%    Description
%    -----------
%
%    Assign the order in which the face-detection algorithms will be applied to increase 
%    efficiency. Specifically, assign the order such that face-detection algorithms that have been
%    more likely to make a detection within a local set of frames come first. Efficiency is
%    increased because each face-detection algorithm is applied until an algorithm makes a 
%    detection. By placing algorithms more likely to make a detection first, fewer face-detection
%    algorithms may need to be used until a detection is made.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% If color-processing expediting is activated %%%%%%

if ExpediteColorThresholdsTF

    %Use the default ordering as this favors the primary algorithm.
    FaceDetectAlgorithmsOrdered = Algorithms;
    
%%%%%% If color-processing expediting is not activated %%%%%%    
    
else
       
    %%%%%% --- Sum detections for each algorithm for the specified number of frames back %%%%%%

    %Specify the number of frames back to sum detections
    FramesBack = 60;

    %Number of detections by the primary face-detection algorithm
    NPrimaryDetections = ...
        nnz( ...
            HasROI_TF.FacePrimary( max(1, i - FramesBack) : max(1, i - 1) ) ...
        );

    %If at least one of the two secondary face-detection algorithms is used
    if NAlgs > 1

        %Three algorithms: Use both secondary algorithms #1 and #2
        if NAlgs == 3 

            %Number of detections by secondary #1 algorithm
            NSecondary1Detections = ...
                nnz( ...
                    HasROI_TF.FaceSecondary1( max(1, i - FramesBack) : max(1, i - 1) ) ...
                );

            %Number of detections by secondary #2 algorithm
            NSecondary2Detections = ...
                nnz( ...
                    HasROI_TF.FaceSecondary2( max(1, i - FramesBack) : max(1, i - 1) ) ...
                );

        %Vector with the number of detections by each algorithm
        NDetectionsByAlg = [NPrimaryDetections, NSecondary1Detections, NSecondary2Detections];    

        %Two algorithms: Use only one secondary face-detection algorithm
        else 

            %The only secondary algorithm is #1
            if SecAlg == 1

                %Number of detections by secondary #1 algorithm
                NSecondary1Detections = ...
                    nnz( ...
                        HasROI_TF.FaceSecondary1( max(1, i - FramesBack) : max(1, i - 1) ) ...
                    );

            %Vector with the number of detections by each algorithm
            NDetectionsByAlg = [NPrimaryDetections, NSecondary1Detections];

            %The only secondary face-detection algorithm is #2
            else

                %Number of detections by secondary #2 algorithm
                NSecondary2Detections = ...
                    nnz( ...
                        HasROI_TF.FaceSecondary2( max(1, i - FramesBack) : max(1, i - 1) ) ...
                    );  

                %Vector with the number of detections by each algorithm
                NDetectionsByAlg = [NPrimaryDetections, NSecondary2Detections];
            end
        end %end secondary algorithms

    %The only face-detection algorithm is the primary face-detection algorithm
    else

        NDetectionsByAlg = NPrimaryDetections;           
    end

    %%%%%% --- Rank the face-detection algorithms by the number of detections made %%%%%%

    %Return the index ordering the algorithms by most-to-least detections
    [~, MaxDetectionsIdx] = ...
        sort( ...
            NDetectionsByAlg, ...
            'descend' ...
         );

    %Order the string vector Algorithms, which contains the name of each algorithm, by rank.
    %Algorithms only contains names of the algorithms that are enabled.
    %Algorithms are assigned by function FaceDetect_ConfigSetup.
    FaceDetectAlgorithmsOrdered = Algorithms(MaxDetectionsIdx);
end


end %end function

