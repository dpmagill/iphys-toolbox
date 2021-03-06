
# FacePulseRate: A Suite of Features to Facilitate the Use of iPhys Toolbox

FacePulseRate returns frame-by-frame blood volume pulse (BVP) and windows of pulse rate from a face present within a pre-recorded (not streaming) input video. 

FacePulseRate is designed to return output from the four (as of November, 2019) blood volume pulse (BVP) algorithms provided by iPhys Toolbox (McDuff & Blackford, 2019). As in iPhys Toolbox, the pulse rate of an interval of time (termed a window here) is calculated from BVP by conducting a fast Fourier transform (FFT) to select the greatest peak. 

## Use Case

FacePulseRate has been designed for researchers interested in acquiring pulse rate from videos, which have the benefit of being recorded remotely and without contact, in contrast with traditional instruments. FacePulseRate is ready to use; that is, code does not need to be added or modified. In fact, all features of FacePulseRate are available from the relatively short Matlab scripts (i.e., .mlx files) included. Only introductory experience with programming languages is assumed. 

## Purpose

FacePulseRate adopts the approach of iPhys Toolbox, as well as other sources from the literature, by calculating pulse rate (1) from a relatively long 
duration and (2) as determined by the greatest peak in a periodogram. This contrasts to the calculation typically used for traditional measures, such as PPG or 
ECG, where a millisecond time scale may be used and local peak detection is used rather than a periodogram. Although it is possible to apply the 
calculations used for traditional measures on a video measure, it is unclear whether the noise often present in video data is conducive to that level of precision.

In the literature, the long duration typically used is the entire length of the video. For example, Poh, McDuff, and Picard (2011) recorded participants
for 1 minute and then used the greatest peak from a periodogram to calculate pulse rate. 

A limitation to taking pulse rate from the entire video is that this may not address research questions concerning changes in pulse rate across time.
Addressing this limitation is the first purpose of FacePulseRate. To do so, FacePulseRate allows pulse rate to vary across time while still adhering to the use of a relatively long
duration and the use of a periodogram. Specifically, FacePulseRate is implemented to take pulse rate separately from windows of time within the video.
The default window duration is 1 minute, although an argument permits this to be changed to an arbitrary value (although constrained to be at least 2 seconds).
The window duration can also be changed to be the length of video when a time-varying measure is not desired. 

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

This toolbox accepts pre-recorded video rather than video streams. The benefit of pre-recorded video is that some operations can be aware of the future (they can look ahead in the video), which improves the accuracy of ROI placement.      

## Output

The BVP and pulse rate results are provided, along with additional information, as output tables. Included among the additional information are the input video timestamps and means from the red, green, and blue color channels of an ROI from each frame; these two components of the data are the basis for the BVP.  These tables are also written to CSV files. As previously mentioned, an output video is provided to facilitate corrections to ROI placement and skin segmentation. Code examples of corrections are provided in file Examples_Correct_ROIs_and_Skin_Segmentation.mlx.

In sum, ...
* Frame-by-frame BVP as Matlab table variable
* Frame-by-frame BVP as csv file 
* Window-by-window pulse rate as Matlab table variable
* Window-by-window pulse rate as csv file
* Annotated output video 

![Alt text](Guides/img/Example_Frame.png?raw=true "Example Frame.")
*A Frame.*

| Frame       | Timestamp_sec | BVP_Chrom | BVP_Green | PulseRate_Chrom | PulseRate_Green |
| :---------- | :------------ | :-------- | :-------- | :-------------- | :---------------|
| 1           | .125          | 0         | -.004     | 68              | 65              |        
| 2           | .167          | -3.40E-06 |  .134     | 68              | 65              | 
| 3           | .208          | -2.61E-06 |  .274     | 68              | 65              |

*Frame-by-Frame Table.*
A few lines from the first window. Only a small selection of columns is shown. These columns show the output from the Chrom and Green algorithms.


| Block       | Window        | Chrom     | Green     | ICA       | POS       |
| :---------- | :------------ | :-------- | :-------- | :-------- | :-------- |
| 1           | 1             | 68        | 65        | 68        | 69        |
| 1           | 2             | 70        | 70        | 71        | 72        |

*Window-by-Window Table.*
Pulse rate from the 2 windows used. Pulse rate is from the Chrom, Green, ICA, and POS algorithms. Segmenting data by block is optional.     

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

3. Obtain the files for FacePulseRate. As of October 2020, the files can be found on Github.com under iphys-toolbox. Specifically, FacePulseRate Toolbox is a fork of iphys-toolbox.

### General Use

See code examples for general use in "Examples_General_Instructions.mlx". 

Note: .mlx files can only be displayed in the Matlab Environment.

### Corrections to ROI Placement or Skin Segmentation

See code examples for correcting ROI Placement or Skin Segmentation in "Examples_Correct_ROIs_and_Skin_Segmentation.mlx".

Note: .mlx files can only be displayed in the Matlab Environment.

## Implementation

FacePulseRate consists of about 10,000 lines of Matlab code and includes compiled-C code for performance benefits. Compiled code is also used from the FFmpeg (r) project for efficiency. However, no code needs to be modified and no files need to be compiled to use FacePulseRate.   

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

Madan, C. R., Harrison, T., & Mathewson, K. E. (2018). Noncontact measurement of emotional and physiological changes in heart rate from a webcam. *Psychophysiology, 55*(4), e13005.        

McDuff, D., & Blackford, E. (2019). *iphys: An open non-contact imaging-based physiological measurement toolbox*. In 2019 Annual International Conference of the IEEE Engineering in Medicine and Biology Society (EMBC), pp. 6521-6524. 

Poh, M. Z., McDuff, D. J., & Picard, R. W. (2011). Advancements in noncontact, multiparameter physiological measurements using a webcam. *IEEE Transactions on Biomedical Engineering, 58*(1), 7-11.