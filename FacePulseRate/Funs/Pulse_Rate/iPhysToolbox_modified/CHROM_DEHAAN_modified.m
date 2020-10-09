function [BVP, PR] = CHROM_DEHAAN_modified(RGB, FS, T, WinSec, FN)
% CHROM_DEHAAN The Chrominance Method from: De Haan, G., & Jeanne, V. (2013). Robust pulse rate from chrominance-based rPPG. IEEE Transactions on Biomedical Engineering, 60(10), 2878-2886. DOI: 10.1109/TBME.2013.2266196
%
% % ------ Description of modifications to original for use in FacePulseRate ------ %
%
% Modifications by author of FacePulseRate, Douglas Magill, 2020.  
%
% - The video reading operations were removed. In its place, the output from video reading, which
%   includes the RGB matrix (RGB) and timestamps (T), are entered as inputs to the function. As
%   video reading operations were removed, the following related inputs were also removed:
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
% - WinSec is entered as an argument instead of being assigned within the function.
%
% In sum, only the CHROM_DEHAAN algorithm and the BVP-to-pulse rate operations are retained.
% 
% % ------ End description of modifications ------ %
% 
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

LPF = 0.7; %low cutoff frequency (Hz) - specified as 40 bpm (~0.667 Hz) in reference
HPF = 2.5; %high cutoff frequency (Hz) - specified as 240 bpm (~4.0 Hz) in reference


%{

WinSec=1.6; %(was a 32 frame window with 20 fps camera)

%}

%% CHROM:
NyquistF = 1/2*FS;
[B,A] = butter(3,[LPF/NyquistF HPF/NyquistF]);%Butterworth 3rd order filter - originally specified as an a FIR band-pass filter with cutoff frequencies 40-240 BPM

%Window parameters - overlap, add with 50% overlap
WinL = ceil(WinSec*FS);
if(mod(WinL,2))%force even window size for overlap, add of hanning windowed signals
    WinL=WinL+1;
end
NWin = floor((FN-WinL/2)/(WinL/2));
S = zeros(NWin,1);
WinS = 1;%Window Start Index
WinM = WinS+WinL/2;%Window Middle Index
WinE = WinS+WinL-1;%Window End Index

for i = 1:NWin
    TWin = T(WinS:WinE,:);
    
    RGBBase = mean(RGB(WinS:WinE,:));
    RGBNorm = bsxfun(@times,RGB(WinS:WinE,:),1./RGBBase)-1;
    
    % CHROM
    Xs = squeeze(3*RGBNorm(:,1)-2*RGBNorm(:,2));%3Rn-2Gn
    Ys = squeeze(1.5*RGBNorm(:,1)+RGBNorm(:,2)-1.5*RGBNorm(:,3));%1.5Rn+Gn-1.5Bn
    
    Xf = filtfilt(B,A,double(Xs));
    Yf = filtfilt(B,A,double(Ys));
    
    Alpha = std(Xf)./std(Yf);
    
    SWin = Xf - Alpha.*Yf;
    
    SWin = hann(WinL).*SWin;
    %overlap, add Hanning windowed signals
    if(i==1)
        S = SWin;
        TX = TWin;
    else
        S(WinS:WinM-1) = S(WinS:WinM-1)+SWin(1:WinL/2);%1st half overlap
        S(WinM:WinE) = SWin(WinL/2+1:end);%2nd half
        TX(WinM:WinE) = TWin(WinL/2+1:end);
    end
    
    WinS = WinM;
    WinM = WinS+WinL/2;
    WinE = WinS+WinL-1;
end

BVP=S;                                      

PlotPRPSD = false;

% Estimate Pulse Rate from periodogram
PR = prpsd(BVP,FS,40,240,PlotPRPSD);



end%end function
