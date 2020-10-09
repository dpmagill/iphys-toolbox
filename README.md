# FacePulseRate: A Suite of Features To Use With iPhys Toolbox

Calculate frame-by-frame blood volume pulse (BVP) and windows of pulse rate from a face present within an input video. FacePulseRate is designed to supply output from the four (as of November, 2019) pulse-rate algorithms provided by iPhys Toolbox (McDuff & Blackford, 2019). Additionally, FacePulseRate ...

- Breaks down pulse rate into windows, permitting pulse rate to vary across time.
- Automically positions a face ROI for each frame.
- Provides enhanced skin segmentation.
- Provides separate versions of each of the four algorithms while controlled for variation in luminance across frames (see Madan et al., 2018). This is in addition to providing the four versions without controlling for luminance.
- Provides verification of ROI placement and skin-segmentation by providing an annotated output video. Arguments are available to make adjustments to ROI placement and skin-segmentation based upon inspection of the output video.

## Examples and Detailed Description ##

See Example_Script.mlx.

## License and Third-Party Copyright Notices ##

See folder "License".

## References ##

Madan, C. R., Harrison, T., & Mathewson, K. E. (2018). Noncontact measurement of emotional and physiological changes in heart rate from a webcam. Psychophysiology, 55(4), e13005.        

McDuff, D., & Blackford, E. (2019). iphys: An open non-contact imaging-based physiological measurement toolbox. In 2019 Annual International Conference of the IEEE Engineering in Medicine and Biology Society (EMBC), pp. 6521-6524. 
