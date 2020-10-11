
# FacePulseRate: A Suite of Features to Facilitate the Use of iPhys Toolbox

FacePulseRate returns frame-by-frame blood volume pulse (BVP) and windows of pulse rate from a face present within an input video. This toolbox accepts pre-recorded video rather than video streams. The benefit of pre-recorded video is that some operations can be aware of the future (they can look ahead in the video), which improves the accuracy of ROI placement.      

FacePulseRate is designed to return output from the four (as of November, 2019) pulse-rate algorithms provided by iPhys Toolbox (McDuff & Blackford, 2019). As in iPhys Toolbox, the pulse rate of an interval (termed a window here) is calculated by conducting a fast Fourier transform (FFT) to select the greatest peak. 

## Purpose

The first purpose of FacePulseRate is to break down time into numerous windows (each 1.5 minutes) to allow pulse rate to vary across time. An argument can be used to change the window duration according to preference. It is unclear whether this approach has been used previously, so developing the duration according to comparison with objective data (e.g., PPG, ECG) may provide guidance.

The second purpose is to provide features to make the collection of data from the videos convenient, accurate, diagnosable, and correctable. These features do not alter the pulse rate algorithms from iPhys Toolbox, but rather concentrate on obtaining data for input into the algorithms. Good data should facilitate the accuracy of the pulse-rate algorithms. The features include ...

* Automatically positioning a face ROI for each frame using OpenCV (Viola-Jones) face detection and a novel skin-detection method.

* Providing a novel method of skin segmentation where thresholds are tailored from skin-color samples from the video.

* An argument that enables controlling for variation in luminance across frames (see Madan et al., 2018). 

* Providing verification of ROI placement and skin-segmentation by providing an annotated output video. Arguments are available to make adjustments to ROI placement and skin-segmentation based upon inspection of the output video.

## Input

Color Videos. 

Supported file extensions include ...
* .mp4
* .avi

Other file extensions may be supported. 

For additional discussion and recommendations, see "Video_and_Recording_Environment_Recommendations.pdf".

## Output

The BVP and pulse rate results are provided, along with additional information, as output tables. Included among the additional information are the input video timestamps and means from the red, green, and blue color channels of an ROI from each frame; these two components of the data are the basis for the BVP.  These tables are also written to CSV files. As previously mentioned, an output video is provided to facilitate corrections to ROI placement and skin segmentation. Code examples of corrections are provided in file Examples_Correct_ROIs_and_Skin_Segmentation.mlx.

In sum, ...
* Frame-by-frame BVP as Matlab table variable
* Frame-by-frame BVP as csv file 
* Window-by-window pulse rate as Matlab table variable
* Window-by-window pulse rate as csv file
* Annotated output video 

## Interface

* Matlab (see software requirements below)

## System Requirements

* 64-bit Windows

Currently, 64-bit macOS has not been implemented or tested.

## Software Requirements

* Matlab. FacePulseRate has been tested on Matlab versions 2020a and 2020b. Matlab can often be acquired without cost through a university affiliation. 

The following Matlab toolboxes are also required. Note that these toolboxes require corresponding licenses from Matlab. However, these can often be acquired without cost through a university affiliation. These are the toolbox names as of Matlab release 2020b; toolboxes are occassionally renamed.

* Statistics and Machine Learning Toolbox
* Computer Vision System Toolbox
* Image Processing Toolbox
* Signal Processing Toolbox 
* DSP System Toolbox
* Optimization Toolbox

## Instructions

Most of the features of FacePulseRate occur automatically, so few lines of code need to be used to return results 
under default options. For example, once the required toolboxes have been installed and FacePulseRate Toolbox is placed on
Matlab's path, entering the following line in Matlab is all that is needed to return results:

    FacePulseRate(<\...\MyInputVideo.mp4>);

### Study Preparation

Experience has indicated at least two steps of preparation should be undertaken before data collection:

1. Optimize the video recording environment. See Video_and_Recording_Environment_Recommendations.pdf.

2. Conduct pretests. See Pretesting.pdf.

### Setup

1. Install Matlab on a Windows 64-bit computer. Matlab version 2020a or later is recommended. Matlab is often provided at no cost through a university affiliation. 

2. Install the following Matlab toolboxes. As of Matlab version 2020b, Matlab toolboxes can be installed in the Matlab environment through Apps > Install App. The following toolboxes are often provided at no cost when using an academic license.
- Statistics and Machine Learning Toolbox
- Computer Vision System Toolbox
- Image Processing Toolbox
- Signal Processing Toolbox 
- DSP System Toolbox
- Optimization Toolbox 

3. Download the folder that contains the functions for FacePulseRate. This folder is named 'FacePulseRate'. As of October 2020, FacePulseRate can be found on Github.com under the username 'dpmagill' as a fork to McDuff and Blackford's (2019) iPhys Toolbox. 

### General Use

See file "Examples_General_Instructions.mlx". 

This script is aimed at users with no previous experience with Matlab and introductory experience with programming languages.

Note: .mlx files can only be displayed in the Matlab Environment.

### Corrections to ROI Placement or Skin Segmentation

See "Examples_Correct_ROIs_and_Skin_Segmentation.mlx".

Note: .mlx files can only be displayed in the Matlab Environment.

## Implementation

For a detailed discussion on the implmentation of FacePulseRate, see file FacePulseRate.m. Additional discussion is included in the helper files to FacePulseRate.m.

## License and Third-Party Software Acknowledgements

FacePulseRate Toolbox copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>.

For interest in a commercial license, please contact the author.

Note: the author is not affiliated with iPhys Toolbox, which is the property of its respective owners.

### GNU General Public License, Version 2

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License, version 2, as published by the Free Software Foundation. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program; if not, see <https://www.gnu.org/licenses>.

In addition, as a special exception, the copyright holder of FacePulseRate gives you permission to combine FacePulseRate with free software programs or libraries that are released under the GNU LGPL and with code included in the standard release of MATLAB under the appropriate MATLAB license (or modified versions of such code, with unchanged license). You may copy and distribute such a system following the terms of the GNU GPL for FacePulseRate and the licenses of the other code concerned.

### RAIL License      

In addition to the aforementioned GNU General Public License, this program is licensed under the terms of the Responsible AI License (RAIL). 

### Third-Party Software Acknowledgements

FacePulseRate is only possible through the use of third-party open-source software. The author is grateful for its use.

See an acknowledgement of third-party software in file 'FacePulseRate/License/Third-Party Software Acknowledgements.txt'.

## References

Madan, C. R., Harrison, T., & Mathewson, K. E. (2018). Noncontact measurement of emotional and physiological changes in heart rate from a webcam. Psychophysiology, 55(4), e13005.        

McDuff, D., & Blackford, E. (2019). iphys: An open non-contact imaging-based physiological measurement toolbox. In 2019 Annual International Conference of the IEEE Engineering in Medicine and Biology Society (EMBC), pp. 6521-6524. 

