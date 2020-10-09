function SkinDetectConfig = ...
             SkinDetect_SetThresholds(i, SkinDetectConfig, DataForSkinDetection, NSamples, ...
                 FirstCallTF_SetSkinDetectThresholds)                                 
%SkinDetect_SetThresholds   Process data from primary face-detection algorithm ROIs to assign color
%                           thresholds for the skin-detection algorithm.
%  
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead_SetThresholds.
%
%
%    Description
%    -----------
%
%    This function processes skin-color samples in order to set skin-detection thresholds tailored  
%    to the face in the video. For details on the collection of skin-color samples, see function 
%    ROIMeans_FirstRead_CollectSkinColorSamples. 
%
%    This function is called in function ROIMeans_FirstRead once a minimum number of skin-color 
%    samples has been reached.                                                
%
%    The RGB skin-classification training function (SkinDetect_RGBProbSkinTrain) is adapted from  
%    the Skin Segmentation toolbox, which was obtained from Madhav Rajan (2014). See discussion on          
%    Github (https://github.com/madhrajan91/Skin-Segmentation). 
%
%    The data used in the RGB skin-classification function (SkinDetect_RGBProbSkinTrain) is, in 
%    part, from Bhatt and Dhall 2009, 'Skin Segmentation Dataset', UCI Machine Learning Repository. 
%    See discussion in Bhatt, Sharma, Dhall, Chaudhury (2009). Efficient skin region segmentation 
%    using low complexity fuzzy decision tree model. IEEE-INDICON, Dec 16-18, Ahmedabad, India,
%    pp. 1-4. See also Dhall, Sharma, Bhatt, and Khan (2009). Adaptive Digital Makeup, Proc. of 
%    International Symposium on Visual Computing (ISVC), Nov. 30 -Dec. 02, Las Vegas, Nevada, USA, 
%    Lecture Notes in Computer Science, Vol. 5876, pp. 728-736. 
%
%    The data used in the RGB skin-classification function (SkinDetect_RGBProbSkinTrain) is, in
%    part, from Douglas Magill (2020). This data is included in the license for function 
%    FacePulseRate. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Argument Validation %%%%%%

%If fewer skin-color samples collected than specified, exit function. This is imposed to ensure 
%robust use of ROI colors. For details on the collection of skin-color samples, see function
%ROIMeans_FirstRead_CollectSkinColorSamples. If fewer skin-color samples than threshold, the  
%skin-detection algorithm will not be used as it depends upon region colors.

SkinDetectConfig.Thresholds.SkinColorSamples_NThresholdPassedTF = ...
    NSamples >= SkinDetectConfig.Thresholds.SkinColorSamples_NThreshold;
    
if ~ SkinDetectConfig.Thresholds.SkinColorSamples_NThresholdPassedTF

    %Exit function
    return
end


%%%%%% Display notification message %%%%%%  

%If first call to current function within function FacePulseRate
if FirstCallTF_SetSkinDetectThresholds

    message = '\n       Setting thresholds for the skin-detection algorithm.';

else
    
    message = '\n       Recalculating thresholds for the skin-detection algorithm.';   
end
    
%Display message on command window
fprintf(message);

%Display message immediately
drawnow();
  

%%%%%% Calculate ROI RGB probability theta parameters %%%%%%

%For details, see the file for function SkinDetect_ConfigSetup.

%Remove rows with NaN
%Rows will have NaN if function ROIMeans_FirstRead_CollectSkinColorSamples did not collect any
%skin-color samples. There are also rows with NaN that were preallocated but not filled. 
%Note: If one column of a row is NaN, other columns of the row will also be NaN.
DataForSkinDetection.RGBMeans = ...
    DataForSkinDetection.RGBMeans( ...
        ~ isnan( DataForSkinDetection.RGBMeans(:, 1) ), ...
        : ...
    );

%This function trains the function SkinDetect_RGBProbSkin.
%For details, see the file for function SkinDetect_ConfigSetup.  
%Note: SkinDetect_RGBProbSkinTrain is a custom function located within folder 'FacePulseRate'.
SkinDetectConfig.Thresholds.RGBProbTheta = ...
    SkinDetect_RGBProbSkinTrain(DataForSkinDetection.RGBMeans);

%%%%%% --- Calculate YCbCr overall means and frame-mean standard deviations %%%%%%

%For details, see the file for function SkinDetect_ConfigSetup.

%Remove rows with NaN
%Rows will have NaN if function ROIMeans_FirstRead_CollectSkinColorSamples did not collect any
%skin-color samples. There are also rows with NaN that were preallocated but not filled. 
%Note: If one column of a row is NaN, other columns of the row will also be NaN.
DataForSkinDetection.YCbCrMeans = ...
    DataForSkinDetection.YCbCrMeans( ...
        ~ isnan( DataForSkinDetection.YCbCrMeans(:, 1) ), ...
        : ...
    ); 

%Separate the columns  
SkinDetect_YMeans  = DataForSkinDetection.YCbCrMeans(:, 1);
SkinDetect_CbMeans = DataForSkinDetection.YCbCrMeans(:, 2);
SkinDetect_CrMeans = DataForSkinDetection.YCbCrMeans(:, 3);

%Determine the Y, Cb, and Cr means and standard deviations across all ROIs samples collected during 
%the primary face-detection algorithm procedure.
%Note: sum() / numel() faster than function mean().
YMeanOfMeans  = sum(SkinDetect_YMeans)  / numel(SkinDetect_YMeans);
CbMeanOfMeans = sum(SkinDetect_CbMeans) / numel(SkinDetect_CbMeans);
CrMeanOfMeans = sum(SkinDetect_CrMeans) / numel(SkinDetect_CrMeans); 

%Combine and assign
SkinDetectConfig.Thresholds.YCbCrMeanOfMeans = [YMeanOfMeans, CbMeanOfMeans, CrMeanOfMeans];   

YStdDevOfMeans  = std(SkinDetect_YMeans);
CbStdDevOfMeans = std(SkinDetect_CbMeans);
CrStdDevOfMeans = std(SkinDetect_CrMeans);

%Combine and assign
SkinDetectConfig.Thresholds.YCbCrStdDevOfMeans = ...
    [YStdDevOfMeans, CbStdDevOfMeans, CrStdDevOfMeans];
   

%%%%%% Determine whether to narrow the thresholds based upon the number of skin-color samples %%%%%%

%If the number of skin-color samples is above the specified threshold, set a flag to use more 
%narrow the color thresholds (assigned by function SkinDetect_ConfigSetup). This is conducted 
%because when there is a greater number of skin samples, the standard deviations of color samples   
%may become more expansive, requiring more narrow thresholds to reduce false positives (classifying 
%non-skin as skin). Function SkinDetect_RejectRegions will use this flag to select the appropriate 
%thresholds. 

%If the number of skin-color samples is above the specified threshold
%This threshold is set by function SkinDetect_ConfigSetup.
if NSamples >= SkinDetectConfig.Thresholds.SkinColorSamples_HighNThreshold

    %Flag indicating whether the threshold is met
    SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdPassedTF = true;
    
    %Record the frame index at which the number of skin-color samples satisfied the threshold
    %This frame index will be used by function WriteFaceVideo to display the corresponding 
    %thresholds on the output video.
    SkinDetectConfig.Thresholds.SkinColorSamples_HighNThresholdIdx = i;
end


end %end function

