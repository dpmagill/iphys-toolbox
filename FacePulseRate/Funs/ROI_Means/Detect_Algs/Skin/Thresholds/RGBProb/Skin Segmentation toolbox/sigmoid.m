function g = sigmoid(z) %#codegen
%SIGMOID   Compute sigmoid function.
%
%   Helper function to function FacePulseRate.
%   Within function FacePulseRate, called by functions SkinDetect_RGBProbSkinTrain and
%   SkinDetect_RGBProbSkin.
%
%   Code generation: Can be called as a Matlab function or used for C-language code generation.
%
%   Description:
%
%   J = SIGMOID(z) computes the sigmoid/ Logistic function of z.
%
%   Adapted from the Skin Segmentation toolbox, which was obtained from Madhav
%   Rajan (2014). See discussion on Github (https://github.com/madhrajan91/Skin-Segmentation).


%Inline function
coder.inline('always');


g = 1 ./ ( 1 + exp( -1 .* z ) );


end %end function