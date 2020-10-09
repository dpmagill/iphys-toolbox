# FacePulseRate Toolbox: A Suite of Features to Use with iPhys Toolbox
Calculate frame-by-frame blood volume pulse (BVP) and windows of pulse rate from a face present within an input video. FacePulseRate is designed to supply output from the four (as of November, 2019) pulse-rate algorithms provided by iPhys Toolbox (McDuff & Blackford, 2019). Additionally, FacePulseRate ...

- Breaks down pulse rate into windows, permitting pulse rate to vary across time
- Automically positions a face ROI for each frame
- Provides enhanced skin segmentation
- Separate versions of each of the four algorithms while controlled for variation in luminance across frames are provided (see Madan et al., 2018). 
- Provides verification of ROI placement and skin-segmentation by providing an annotated output video. Arguments are available to make adjustments to ROI placement and skin- segmentation based upon inspection of the output video


## Examples ##

Examples are provided in Example_Script.mlx.


### License ###

See folder "License".
