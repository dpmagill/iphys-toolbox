function [theta] = SkinDetect_RGBProbSkinTrain(ForRegionColors_PrimaryFramesRGBMeans)
%SkinDetect_RGBProbSkinTrain   Training for function SkinDetect_RGBProbSkin. 
% 
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinDetect_SetThresholds.
%
%
%    Description
%    -----------
%
%    Train theta values used for skin classification on a mixture of external and internal RGB 
%    skin-color samples. These theta values will be used for skin classification by function 
%    SkinDetect_RGBProbSkin, which is called by function SkinDetect.
%
%    The skin-color samples are from three sources:
%
%    - External data:
%
%    In part from Bhatt & Dhall (2009), 'Skin Segmentation Dataset', UCI Machine 
%    Learning Repository. See discussion in Bhatt, Sharma, Dhall, Chaudhury (2009). Efficient skin 
%    region segmentation using low complexity fuzzy decision tree model. IEEE-INDICON, Dec 16-18, 
%    Ahmedabad, India, pp. 1-4. See also Dhall, Sharma, Bhatt, and Khan (2009). Adaptive Digital 
%    Makeup, Proc. of International Symposium on Visual Computing (ISVC), Nov. 30 -Dec. 02, 
%    Las Vegas, Nevada, USA, Lecture Notes in Computer Science, Vol. 5876, pp. 728-736. 
%
%    In part from Douglas Magill (2020). These data are included under the license for function 
%    FacePulseRate.  
%
%    - Data from input video:
%
%    The RGB means from the current video, as supplied by function 
%    ROIMeans_FirstRead_CollectSkinColorSamples, are from ROIs detected from the primary 
%    face-detection algorithm of function FacePulseRate. These detection are assumed to contain
%    skin regions. As these skin regions are from the person in the video,  this may increase the 
%    ability to detect skin idiosyncratic to this person. Means from an external dataset are used 
%    to help allow for variations in lighting conditions, pose, etc., to be found in the current 
%    video.   
%
%    Inputs:
%
%        Internal data = A matrix of R, G, and B positive skin sample means from the primary
%                        face-detection algorithm ROIs of the current video.
%                        Columns are R, B, G, and an identifier (1 = positive).                       
%                                                                           
%        External data = A matrix of R, G, and B positive and negative skin sample means from
%                        an external source (not from the current video).
%                        Columns are R, B, G, and an identifier (1 = positive; 2 = negative).
%                        A more detailed description is provided below.
%                                                                                                         
%    Output:
%
%        theta         = Four estimated parameters used by function SkinDetect_RGBProbSkin to
%                        estimate the probability that a given ROI is skin.
%
%    This function is adapted from the Skin Segmentation toolbox, which was obtained from Madhav
%    Rajan (2014). See discussion on Github (https://github.com/madhrajan91/Skin-Segmentation).
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.
                                      

%%%%%% Prepare skin samples %%%%%%

%Prepare samples from current video, which are all positive samples
%Remove rows with no detections or no identified skin regions from matrix 
%ForRegionColors_PrimaryFramesRGBMeans by omitting rows that equal 0.
%Note: Because the matrix was preallocated with zeros, rows without detections will contain zeros.
%Rows with detections but without an identified skin region will also contain zeros, as function
%ROIOrientOnSkin_CollectPriAlgROIColorData, which populated the matrix, is programmed to return 
%zeros in this case.
Video_Positive = ForRegionColors_PrimaryFramesRGBMeans;
Video_Positive = Video_Positive(sum(Video_Positive, 2) ~= 0, :); %remove rows that equal 0
Video_Positive = round(Video_Positive, 0); %convert to integers
Video_Positive = [Video_Positive, ones(length(Video_Positive), 1)]; %add column of ones for compatibility with later function

%Load skin sample means not from current video ("RGB_External_Rand.txt") 
%Columns 1 to 3 are means from skin samples representing
%red, green, and blue, respectively.  Column 4 identifies whether
%the sample is a positive sample (skin; 1) or a negative sample
%(non-skin; 2).

%RGB_External_Rand.txt was prepared as follows:
% - Skin samples were written to a txt file, "RGB_External.txt".
% - Rows 1 to 245057 are from Bhatt and Dhall (2012) (see
%   https://archive.ics.uci.edu/ml/datasets/Skin+Segmentation). The rows
%   contain both positive and negative samples.
% - Rows 245058 until end from Douglas Magill (dpm59@zips.uakron.edu). The
%   rows contain only positive samples. 
% - Note: This file can be modified to include more or other samples if desired.
% - The order of the rows was then randomized (see the file for function 
%   RGBProbSkinTrainRandomizer) and the output was written
%   to file "RGB_External_Rand.txt". 
External = load('RGB_External_Rand.txt');

%Separate external samples by positive and negative samples
%External negative samples (where column 4 == 2)
External_Negative = External(External(:, 4) == 2, :);
%External positive samples (where column 4 == 1)
External_Positive = External(External(:, 4) == 1, :); 


%%%%%% Combine video positive samples with external negative samples %%%%%%

%However, if few positive samples from video, add some positive samples from external
%source to aid convergence of logistic regression and to offer
%heterogeneity to sample.
[nrows, ~] = size(Video_Positive);
if nrows < 30
    
    %Extract the first 30 rows of data from the external source
    External_Positive_Sample = External_Positive(1:30, :);
    
    %Concatenate rows
    Video_Positive = [Video_Positive; External_Positive_Sample];
    
end

%Extract external negative samples the length of positive video samples
External_Negative_Sample = External_Negative(1:length(Video_Positive), :);

%Concatenate rows of positive video samples and external negative samples
Training_Data_Video = [Video_Positive; External_Negative_Sample]; 


%%%%%% Estimate theta parameters from video data %%%%%%

%Code from Skin Segmentation toolbox (https://github.com/madhrajan91/Skin-Segmentation)
%(see file skin_segmentation.m within that toolbox) {

%Take RGB means columns from training set and call them X
X = Training_Data_Video(:, 1:3);

%Take pos/neg column from training set and call it y
y = Training_Data_Video(:, 4);

%Change skin/non-skin value
y(y == 1) = 0; %skin
y(y == 2) = 1; %non-skin

%Add column of ones as first column to RGB means matrix
[m, n] = size(X);
X = [ones(m, 1), X];

%Parameters
initial_theta = zeros(n + 1, 1);
lambda = 0.5;

%Compute initial cost and gradient
%[cost, grad] = costFunction(initial_theta, X, y, lambda);

%Gradient using fminunc
options = ...
    optimset('GradObj', 'on', ...
    'MaxIter', 10000, ... %DPM: increaed from 1000 to 10000
    'Display', 'off'); %DPM: do not display outcome on console

%Calculate theta
[theta, cost] = fminunc(@(t)(costFunction(t, X, y, lambda)), initial_theta, options);

%Rename
theta_video = theta;

%Compute accuracy on our training set
%p = predict(theta_video, X);

%} End code from Skin Segmentation toolbox


%%%%%% Estimate theta parameters from external source %%%%%%

%Code from skin_segmentation package (https://github.com/madhrajan91/Skin-Segmentation)
%(see file skin_segmentation.m within that package) {

%Take RGB means columns from training set and call them X
X = External(:, 1:3);

%Take pos/neg column from training set and call it y
y = External(:, 4);

%Change skin/non-skin value
y(y == 1) = 0; %skin
y(y == 2) = 1; %non-skin

%Add column of ones as first column to RGB means matrix
[m, n] = size(X);
X = [ones(m, 1), X];

%Parameters
initial_theta = zeros(n + 1, 1);
lambda = 0.5;

%Compute initial cost and gradient
%[cost, grad] = costFunction(initial_theta, X, y, lambda); %DPM: commented out as not needed programmatically

%Gradient using fminunc
options = ...
    optimset('GradObj', 'on', ...
        'MaxIter', 1000, ... %DPM: increased from 1000 to 10000
        'Display', 'off'); %DPM: do not display outcome on console

%Calculate theta
[theta, cost] = fminunc(@(t)(costFunction(t, X, y, lambda)), initial_theta, options);

%Rename
theta_external = theta;

%Compute accuracy on our training set
%p = predict(theta_external, X); %DPM: commented out as not needed programmatically

%} End code from skin_segmentation package


%%%%%% Average video theta with external theta %%%%%%

%Purpose is to provide robust theta values

%Average video theta and external theta, weighting the video data more (by 3)
theta = (theta_video * 3 + theta_external) / 4;


end %end function

