function [BVP, PR] = GREEN_VERKRUYSSE_modified(RGB, FS)
% GREEN_VERKRUYSSE The Green-Channel Method from: Verkruysse, W., Svaasand, L. O., & Nelson, J. S. (2008). Remote plethysmographic imaging using ambient light. Optics express, 16(26), 21434-21445. DOI: 10.1364/OE.16.021434
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
% In sum, only the GREEN_VERKRUYSSE algorithm and the BVP-to-pulse rate operations are retained.
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

% Modifications by Douglas Magill, 2020.

%% Parameters
LPF = 0.7; %low cutoff frequency (Hz) - 0.8 Hz in reference
HPF = 2.5; %high cutoff frequency (Hz) - both 6.0 Hz and 2.0 Hz used in reference

%% Select BVP Source:
% Green channel
BVP = RGB(:,2);

%% Filter, Normalize
NyquistF = 1/2*FS;
[B,A] = butter(3,[LPF/NyquistF HPF/NyquistF]);%Butterworth 3rd order filter - originally specified in reference with a 4th order butterworth using filtfilt function
BVP_F = filtfilt(B,A,(double(BVP)-mean(BVP)));

BVP = BVP_F;

PlotPRPSD = false;

% Estimate Pulse Rate from periodogram
PR = prpsd(BVP,FS,40,240,PlotPRPSD);


end%end function
