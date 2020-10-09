function [BVP, PR] = ICA_POH_modified(RGB, FS)
% ICA_POH The Independent Component Analysis (ICA) Method from: Poh, M. Z., McDuff, D. J., & Picard, R. W. (2010). Non-contact, automated cardiac pulse measurements using video imaging and blind source separation. Optics express, 18(10), 10762-10774. DOI: 10.1364/OE.18.010762
%
% % ------ Description of modifications to original for use in FacePulseRate ------ %
%
% Modifications by author of FacePulseRate, Douglas Magill, 2020.  
%
% - The video reading operations were removed. In its place, the output from video reading, namely,
%   the RGB matrix (RGB), is entered as input to the function. As video reading operations were 
%   removed, the following related inputs were also removed:
%   - VideoFile
%   - StartTime
%   - Duration
%
% - The plotting operations were removed. The following related inputs and outputs were also 
%   removed:
%   - ECGFile
%   - PPGFile
%   - PlotTF
%   - HR_ECG
%   - PR_PPG
%   - SNR
%
% In sum, only the ICA_POH algorithm and the BVP-to-pulse rate operations are retained.
% 
% % ------ End description of modifications ------ %
%
%   Inputs:
%       VideoFile               = Video file path.
%       FS                      = Video framerate (fps).
%       StartTime               = Timepoint at which to start process (default = 0 seconds).
%       Duration                = Duration of the time window to process (default = 60 seconds).
%       ECGFile                 = File path to corresponding ECG data file (.mat) containing: 1) The waveform - ECGData.data, 2) The ECG sampling rate - ECGData.fs, 3) The ECG peak locations (in samples) - ECGData.peaks.
%       PPGFile                 = File path to corresponding PPG data file (.mat) containing: 1) The waveform - PPGData.data, 2) The PPG sampling rate - PPGData.fs, 3) The PPG peak locations (in samples) - PPGData.peaks.
%       PlotTF                  = Boolean to turn plotting results on or off.
%
%   Outputs:
%       BVP                     = Processed Blood Volume Pulse (BVP).
%       PR                      = Estimated Pulse Rate (PR) from processed BVP timeseries using peak in periodogram.
%       HR_ECG                  = Gold standard Heart Rate (HR) measured from the ECG timeseries R-waves for the window.
%       PR_PPG                  = Pulse Rate (PR) measured from the PPG timeseries systolic onsets for the window.
%       SNR                     = Blood Volume Pulse Signal-to-Noise Ratio (SNR) calculated based on the ECG HR frequency using a method adapted from the method by G. de Haan, TBME, 2013.
%
%   Requires - Signal Processing Toolbox
%
% Daniel McDuff, Ethan Blackford, January 2019
% Copyright (c)
% Licensed under the MIT License and the RAIL AI License.
%
% Modifications by Douglas Magill, 2020.


%% Parameters
LPF = 0.7; %low cutoff frequency (Hz) - 0.7 Hz in reference
HPF = 2.5; %high cutoff frequency (Hz) - 4.0 Hz in reference


%% Detrend & ICA:
NyquistF = 1/2*FS;
RGBNorm=zeros(size(RGB));
Lambda=100;
for c=1:3
    RGBDetrend= spdetrend(RGB(:,c),Lambda); %M. P. Tarvainen, TBME, 2002
    RGBNorm(:,c) = (RGBDetrend - mean(RGBDetrend))/std(RGBDetrend); %normalize to zero mean and unit variance
end
[W,S] = ica(RGBNorm',3); %JADE ICA - J. F. Cardoso 1997, G. D. Clifford, MIT, 2004

%% Select BVP Source:
% Component with maximum normalized (by total power) power
MaxPx=zeros(1,3);
for c=1:3
    FF = fft(S(c,:));
    F=(1:length(FF))/length(FF)*FS*60;
    FF(1)=[];
    N=length(FF);
    Px = abs(FF(1:floor(N/2))).^2;
    Fx = (1:N/2)/(N/2)*NyquistF;
    Px=Px/sum(Px);
    MaxPx(c)=max(Px);
end

[M,MaxComp]=max(MaxPx(:));
BVP_I = S(MaxComp,:);

%% Filter, Normalize
%originally specified in reference with 5-point moving average, bandpass
%filter, and cubic-spine interpolation to 256Hz
[B,A] = butter(3,[LPF/NyquistF HPF/NyquistF]);%Butterworth 3rd order filter
BVP_F = filtfilt(B,A,double(BVP_I));

BVP=BVP_F;

% Estimate Pulse Rate from periodogram

PlotPRPSD = false;

PR = prpsd(BVP,FS,40,240,PlotPRPSD);


end%end function
