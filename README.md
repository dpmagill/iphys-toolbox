# FacePulseRate: A Suite of Features to Use with iPhys Toolbox

Calculate frame-by-frame blood volume pulse (BVP) and windows of pulse rate from a face present within an input video. FacePulseRate is designed to supply output from the four (as of November, 2019) pulse-rate algorithms provided by iPhys Toolbox (McDuff & Blackford, 2019). Additionally, FacePulseRate ...

- Breaks down pulse rate into windows, permitting pulse rate to vary across time.
- Automically positions a face ROI for each frame.
- Provides enhanced skin segmentation.
- Provides separate versions of each of the four algorithms while controlled for variation in luminance across frames (see Madan et al., 2018). This is in addition to providing the four versions without controlling for luminance.
- Provides verification of ROI placement and skin-segmentation by providing an annotated output video. Arguments are available to make adjustments to ROI placement and skin-segmentation based upon inspection of the output video.

## Treatment of Pulse Rate Variations Across Time

The method in iPhys Toolbox for deriving pulse rate derives BVP from a span of time, the limitation of which is that changes in pulse rate across this span are not calculated.  Although methods exist to derive a continuous measure of pulse rate from BVP as calculated from a sensor attached directly to the body, these methods do not appear to be appropriate for BVP captured from a video because of the additional noise present in the video. To provide a somewhat continuous measure of pulse rate while retaining the method used in iPhys Toolbox, the current function breaks the video into windows (the duration of which can be specified by PulseRateWindowDurationSec) and applies the method used in iPhys Toolbox to each.

## Input

Color Videos. 

Supported file extensions include ...
- .mp4
- .avi

Other file extensions may be supported. Use Matlab function VideoReader.getFileFormats() to return a list of supported file extensions. 

Note that videos with these file extensions may not be supported depending on the specific format (encoding) of the video.    

Whether a format is supported depends upon two factors. The first factor is the Matlab release as FacePulseRate uses Matlab video readers. Format support from the Matlab video readers may change between releases. The second factor is the availability of codecs installed on a particular computer. FacePulseRate will verify whether a video is supported when the function is run. FacePulseRate uses the Matlab video readers to check the support of the video readers and to check whether the appropriate codecs are available on a particular computer.   

## Output

The BVP and pulse rate results are provided, along with addition information, as output tables. Included among the additional information are the input video timestamps and means from the red, green, and blue color channels of an ROI from each frame; these two components of the data are the basis for the BVP.  These tables are also written to CSV files. As previously mentioned, an output video is provided to facilitate corrections to ROI placement and skin segmentation. Examples of corrections are provided in file Example_Script.mlx.

## Use of Pretests

When planning a study, pretests should be conducted where video as well as traditional measures of pulse rate (e.g., PPG, ECG) are recorded. The traditional measures of pulse rate should be used to validate the use of video-derived pulse rate for expected behavioral tendencies. This is because the accuracy of video-derived pulse rate is highly dependent on the degree of facial movement, where greater movement tends to result in video-derived pulse rate that is less accurate. The four pulse-rate algorithms may vary in accuracy depending on the degree of movement. The pulse-rate algorithm with greatest accuracy in a given context should be used.
For a detailed discussion of the key features and technical implementation, see the description in function FacePulseRate.

## System Requirements

- 64-bit Windows

Currently, 64-bit macOS has not been implemented and tested.

## Software Requirements

- Matlab. FacePulseRate has been tested on Matlab versions 2020a and 2020b.

The following Matlab toolboxes are also required. Note that these toolboxes are licensed by Matlab and are not free software. The following toolboxes are often provided at no cost when using an academic license. These are the toolbox names as of Matlab release 2020b; toolboxes are occassionally renamed.

- Statistics and Machine Learning Toolbox
- Computer Vision System Toolbox
- Image Processing Toolbox
- Signal Processing Toolbox 
- DSP System Toolbox
- Optimization Toolbox

## Getting Started

1. Install Matlab on a Windows 64-bit computer. Matlab version 2020a or later is recommended. Matlab is often provided at no cost through a university affiliation. 

2. Install the following Matlab toolboxes. As of Matlab version 2020b, Matlab toolboxes can be installed in the Matlab environment through Apps > Install App. The following toolboxes are often provided at no cost when using an academic license.
- Statistics and Machine Learning Toolbox
- Computer Vision System Toolbox
- Image Processing Toolbox
- Signal Processing Toolbox 
- DSP System Toolbox
- Optimization Toolbox 

3. Download the folder that contains the functions for FacePulseRate. This folder is named 'FacePulseRate'. As of October 2020, FacePulseRate can be found on Github.com under the username 'dpmagill' as a fork to McDuff and Blackford's (2019) iPhys Toolbox. The examples that follow assume FacePulseRate was downloaded to the arbitrary location of "C:\Users\User1\Downloads\FacePulseRate". 

4. Open file Example_Script.mlx. This covers the remaining setup. It also covers all use cases of FacePulseRate. The script is aimed at users with no previous experience with Matlab and introductory experience with programming languages.

5. See "Video and Recording Environment Recommendations.pdf" for recommendations on the input video and the physical enviroment in which it is recorded.

## Implementation

For a detailed discussion on the implmentation of FacePulseRate, see file FacePulseRate.m. Addition discussion is included in the helper files to FacePulseRate.m.

## License and Third-Party Copyright Notices

FacePulseRate Toolbox copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>.

For interest in a commercial license, please contact the author.

Note: the author claims no affilation with iPhys Toolbox, which is the property of its respective owners.

### GNU General Public License, Version 2

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License, version 2, as published by the Free Software Foundation. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program; if not, see <https://www.gnu.org/licenses>.

In addition, as a special exception, the copyright holder of FacePulseRate gives you permission to combine FacePulseRate with free software programs or libraries that are released under the GNU LGPL and with code included in the standard release of MATLAB under the appropriate MATLAB license (or modified versions of such code, with unchanged license). You may copy and distribute such a system following the terms of the GNU GPL for FacePulseRate and the licenses of the other code concerned.

### RAIL License      

In addition to the aforementioned GNU General Public License, this program is licensed under the terms of the Responsible AI License (RAIL).
For third-party copyright notices, see FacePulseRate/License/License.txt.

### Third-Party Copyright Acknowledgements

For full license terms and acknowledgement of third-party copyrights, see folder "License".

## References

Madan, C. R., Harrison, T., & Mathewson, K. E. (2018). Noncontact measurement of emotional and physiological changes in heart rate from a webcam. Psychophysiology, 55(4), e13005.        

McDuff, D., & Blackford, E. (2019). iphys: An open non-contact imaging-based physiological measurement toolbox. In 2019 Annual International Conference of the IEEE Engineering in Medicine and Biology Society (EMBC), pp. 6521-6524. 
