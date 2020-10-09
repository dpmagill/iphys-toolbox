function [] = RGBProbSkinTrainRandomizer()
%RGBProbSkinTrainRandomizer   Randomize external skin samples. 
%   
%    Used during development of function FacePulseRate.
%    Not called by any functions.
%
%
%    Description
%    -----------
%
%    Used to prepare data for function SkinDetect_RGBProbSkinTrain, which is called by function 
%    FacePulseRate. However, the present function is not called by either of these functions. 
%    Rather, the purpose of this function is to serve as a reference for how a data file, 
%    RGB_External_Rand.txt, used by function SkinDetect_RGBProbSkinTrain, was prepared.
%
%    See for file for function SkinDetect_RGBProbSkinTrain for further discussion.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%Load external skin color samples
SkinColorSamplesExternal = load('RGB_External.txt');

%Assign a vector with the data's row index randomly ordered  
rand_filter = ...
    randperm(size(SkinColorSamplesExternal, 1), ...
        size(SkinColorSamplesExternal, 1) )';

%Randomly order the data according to the randomized index    
SkinColorSamplesExternalRand = SkinColorSamplesExternal(rand_filter, :);

%Specify current directory as the directory containing the files for function FacePulseRate
cd() %fill in according to the location of the function files

%Full path
filepath = ...
    [cd, filesep(), filesep(), ...
    'Helper Functs\ROIs\Orient\Skin\Thresholds\RGBProb\RGB_External_Rand.txt'];

%Write text file
writematrix(SkinColorSamplesExternalRand, filepath);


end %end function

