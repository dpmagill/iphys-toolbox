function p = predict(theta, X)
%PREDICT   Predict whether the label is 0 or 1 using learned logistic regression parameters theta.
%
%   Helper function to function FacePulseRate.
%
%   Description:
%
%   p = PREDICT(theta, X) computes the predictions for X using a 
%   threshold at 0.5 (i.e., if sigmoid(theta'*x) >= 0.5, predict 1)
%
%   Adapted from the Skin Segmentation toolbox, which was obtained from Madhav
%   Rajan (2014). See discussion on Github (https://github.com/madhrajan91/Skin-Segmentation).


m = size(X, 1); % Number of training examples

p = zeros(m, 1);

prediction = sigmoid(X*theta);
for i=1:m
  if (prediction(i) >= 0.5)
    p(i)=1;
  
  end
end


end %end function
