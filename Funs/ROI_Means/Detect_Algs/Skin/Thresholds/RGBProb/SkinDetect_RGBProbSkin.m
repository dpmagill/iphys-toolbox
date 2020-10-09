function prob_skin = SkinDetect_RGBProbSkin(RGB_mean, theta) %#codegen
%SkinDetect_RGBProbSkin   Estimate probability that mean RGB of an ROI is skin.
%   
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function SkinDetect_RejectRegions.
%
%
%    Code Generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.
%
%
%    Description
%    -----------
%
%    Estimate probability that mean RGB of an ROI is skin.
%
%    This function is adapted from the Skin Segmentation toolbox, which was obtained from Madhav
%    Rajan (2014). See discussion on Github (https://github.com/madhrajan91/Skin-Segmentation). For 
%    usage notes in toolbox FacePulseRate, see function SkinDetect_RGBProbSkinTrain.
%
%    Note: The theta parameters used by the function are supplied by function
%    SkinDetect_RGBProbSkinTrain.
%
%    Input:
%
%        RGB_mean   = N-by-3 matrix of skin sample RGB means. Each row corresponds to a skin sample 
%                     and the columns correspond to means of R, G, and B, respectively.                   
%        theta      = Probability criteria.
%
%    Output:
%
%        prob_skin  = The probability(ies) that the means of R, G and B represent skin, based upon
%                     theta, which was produced by training with a sample of skin and non-skin 
%                     means. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%Inline function
coder.inline('always');


%Add column to right equal to 1
[nrow, ~] = size(RGB_mean);
RGB_mean_1 = [ones(nrow, 1), RGB_mean];

%Calculate probability that means of R, G, and B do not represent skin
prob_notskin = sigmoid(RGB_mean_1 * theta);

%Convert to probabilty of skin
prob_skin = 1 - prob_notskin;


end %end function

