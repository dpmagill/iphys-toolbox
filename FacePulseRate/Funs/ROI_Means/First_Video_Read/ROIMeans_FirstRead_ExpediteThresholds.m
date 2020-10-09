function ExpediteColorProcessingTF = ...
             ROIMeans_FirstRead_ExpediteThresholds(i, SkinSegmentConfig, SkinDetectConfig)
%ROIMeans_FirstRead_ExpediteThresholds   Determine whether to expedite setting the thresholds for
%                                        tailored skin segmentation and the skin-detection
%                                        algorithm.
%                                       
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function ROIMeans_FirstRead.
%
%
%    Description
%    -----------
%
%    Determine whether color processing, for both the skin-detection algorithm and tailored skin
%    segmentation, should be expedited. The purpose of expediting color processing is to begin 
%    the operations in nested function TakeMeans_Ops() sooner. By beginning these operations  
%    sooner, fewer frames will have to be re-read in function ROIMeans_SecondRead, resulting in a 
%    shorter execution time for this function. 
%
%    Expediting is implemented by instructing function FaceDetect_AlgOrder, called within function 
%    ROIMeans_FirstRead_AlgSelector, to prioritize the primary face-detection algorithm. The 
%    primary face-detection algorithm is prioritized because color processing is set to be 
%    activated only when a specified number of skin-color samples are obtained from the primary 
%    face-detection algorithm.
%
%    Expediting is not activated until the frame iteration passes a specified threshold to increase
%    the diverity of color samples. With limited diversity, the standard deviations and 
%    distributions of color samples will be lower than expected. The skin-detection algorithm 
%    classifies skin regions, in part, on standard deviations, and lower standard deviations would 
%    result in classification decisions that may be too conservative (see the file for function 
%    SkinDetect, which conducts the skin-detection algorithm, for details). The tailored 
%    skin-segmentation operations use the percentiles of the distribution of colors, in part, for 
%    classification decisions; similar to the skin-detection algorithm, more restricted values may 
%    result in classification decisions that are too conservative (see the file for function 
%    SkinSegmentMask, which conducts skin segmentation, for details).
%
%    Note: In addition to not expediting until a certain number of frames elapses to increase the
%    diversity of color samples, other considerations have been taken to increase the diversity. 
%    For example, other implementations that could speed color processing but limit the diversity,  
%    such as avoiding frame skipping until the specified number of samples are obtained, are not 
%    used. Also, if a frame skipping value lower than .75 is specified for argument 
%    ROISkinSkipFrameThreshold, the number of required color samples will be higher (see functions
%    SkinDetectConfig_Setup and SkinSegmentConfig_Setup).
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


ExpediteColorProcessingTF = ...
    ~ SkinDetectConfig.Thresholds.SetTF       && ...
    ~ SkinSegmentConfig.TailoredData.OpsReadyTF && ...
    i > 750;  


end %end function

