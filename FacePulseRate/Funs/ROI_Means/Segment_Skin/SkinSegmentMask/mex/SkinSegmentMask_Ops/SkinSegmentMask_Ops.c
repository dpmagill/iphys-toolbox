/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinSegmentMask_Ops.c
 *
 * Code generation for function 'SkinSegmentMask_Ops'
 *
 */

/* Include files */
#include "SkinSegmentMask_Ops.h"
#include "SkinSegmentMask_Ops_data.h"
#include "SkinSegmentMask_Ops_emxutil.h"
#include "SkinSegmentMask_Ops_types.h"
#include "SkinSegmentMask_Threshold.h"
#include "bwunpack.h"
#include "imdilate.h"
#include "imerode.h"
#include "rt_nonfinite.h"
#include "setPackedFillBits.h"
#include "libmwbwpackctbb.h"
#include "libmwmorphop_packed.h"
#include "mwmathutil.h"

/* Function Definitions */
void SkinSegmentMask_Ops(const emxArray_uint8_T *RBounded_Uint8, const
  emxArray_uint8_T *GBounded_Uint8, const emxArray_uint8_T *BBounded_Uint8,
  const emxArray_real32_T *YSingle, const emxArray_real32_T *CbSingle, const
  emxArray_real32_T *CrSingle, const emxArray_real32_T *HSingle, const
  emxArray_real32_T *SSingle, emxArray_boolean_T *IsSkinMask_Range, int32_T
  NRows_Matrix, int32_T NCols_Matrix, boolean_T CountTrueTF, boolean_T
  TailoredThresholdsTF, boolean_T ReturnYTF, boolean_T ReturnCbCrTF, boolean_T
  ReturnHSTF, boolean_T TailoredThresholdsSevereTF, boolean_T MorphCloseSevereTF,
  int32_T XOffset, int32_T YOffset, const struct0_T *SkinSegmentArgs,
  emxArray_boolean_T *IsSkinMask, uint32_T TrueCount_data[], int32_T
  TrueCount_size[1], emxArray_real32_T *YBounded_Single, emxArray_real32_T
  *CbBounded_Single, emxArray_real32_T *CrBounded_Single, emxArray_real32_T
  *HBounded_Single, emxArray_real32_T *SBounded_Single)
{
  emxArray_uint32_T *B;
  emxArray_uint32_T *IsSkinMask_PixelColorPacked;
  emxArray_uint32_T *c_IsSkinMask_PixelColor_DilateP;
  emxArray_uint32_T *c_IsSkinMask_PixelColor_ErodePa;
  emxArray_uint32_T *d_IsSkinMask_PixelColor_DilateP;
  emxArray_uint32_T *d_IsSkinMask_PixelColor_ErodePa;
  emxArray_uint32_T *r;
  real_T bwSize[2];
  real_T bwpSize[2];
  int32_T NElements_Matrix;
  int32_T b_i;
  int32_T i;
  int32_T loop_ub;
  real32_T YCbCrThresholds_Tailored[8];
  real32_T YCbCrThresholds_Generic[7];
  real32_T HSThresholds_Tailored[3];
  real32_T HSThresholds_Generic[2];
  int16_T Diff10;
  int16_T Diff22;
  int16_T Diff4;
  int16_T MorphCloseNeighborhoodRadius;
  int16_T functionWidthToUse;
  boolean_T c_nhood[50];
  boolean_T b_nhood[32];
  boolean_T nhood[22];
  boolean_T d_nhood[12];
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

  /* SkinSegmentMask_Ops   Return logical matrix, or skin-segmentation mask, where pixels classified as   */
  /*                       skin are true. */
  /*                                                */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, called by function SkinSegmentMask. */
  /*  */
  /*  */
  /*     Code Generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*     Compiled file: The compiled file included in folder FacePulseRate  */
  /*     (SkinSegmentMask_Ops_mex.mexw64) only compatible on Windows platforms.        */
  /*  */
  /*  */
  /*     Description */
  /*     ----------- */
  /*  */
  /*     -- Combined Use of YCbCr and HSV Colorspaces for Pixel-Color Thresholds -- */
  /*  */
  /*     The combined used of the YCbCr and HSV colorspaces is based on ... */
  /*     (1) Dahmani et al. (2020), who found that using both improved skin classification compared to */
  /*         the use of either alone. */
  /*     (2) The observation that using only the YCbCr colorspace did not permit enough diversity of */
  /*         individual differences in skin color. Specifically, Y-minimum and Cr-minimum must be at  */
  /*         least as low as the defaults to avoid oversegmentation in individuals with darker average */
  /*         skin colors when ambient illumination is rather low. However, these defaults also permit  */
  /*         pixel values from objects that should be segmented out; for example, the Cr-minimum at  */
  /*         this level permits pixel values from overhead lamps. Applying the HSV thresholds in  */
  /*         addition to the YCbCr thresholds segmented out these extraneous objects. */
  /*  */
  /*     -- YCbCr Pixel-Color Thresholds --  */
  /*  */
  /*     YCbCr color thresholds in use: */
  /*  */
  /*     - Y-channel minimum */
  /*     - Y-channel maximum (tailored-thresholds only) */
  /*     - Cb-channel minimum */
  /*     - Cb-channel maximum  */
  /*     - Cr-channel minimum */
  /*     - Cr-channel maximum  */
  /*  */
  /*     Apply color thresholds to individual pixels from the luminance (Y), Cb chroma (Cb), and Cr  */
  /*     chroma (Cr) channels of the YCbCr colorspace. */
  /*  */
  /*     Use either the generic YCbCr color thresholds or tailored YCbCr color thresholds. The use of */
  /*     tailored thresholds is specified by argument TailoredThresholdsTF. However, generic thresholds */
  /*     are used when TailoredThresholdsTF is true if the criterion for using tailored thresholds has */
  /*     not been satisfied, which is indicated by DontUseTailoredTF == true.  */
  /*  */
  /*         Generic Thresholds */
  /*  */
  /*     The YCbCr generic color thresholds (SkinSegmentArgs.YCbCrThresholdsGeneric) are used when */
  /*     TailoredThresholdsTF is set to false. Thresholds include a Y-channel minimum, Cb-channel  */
  /*     minimum and maximum, Cr-channel minimum and maximum, and Cb-to-Cr ratio minimum and maximum. */
  /*      */
  /*     The threshold values are set by an argument, SkinSegmentYCbCrThresholdsGeneric, to function  */
  /*     FacePulseRate. If the argument is not specified, default values are used. The default Y, Cb,   */
  /*     and Cr minimums and maximums are based on a consultation of the values provided in iphys  */
  /*     toolbox (McDuff & Blackford, 2019). These values were modified somewhat as a result of   */
  /*     testing. The Cb-to-Cr ratio minimum and maximum and not used in iphys toolbox; these values  */
  /*     were developed through testing. */
  /*       */
  /*     Function SkinSegment_ConfigSetup sets the values for SkinSegmentArgs.YCbCrThresholdsGeneric */
  /*     based on argument SkinSegmentThresholdsGenericYCbCr.     */
  /*  */
  /*     Within the current function, the YCbCr generic threshold operations are conducted by function   */
  /*     SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold. */
  /*  */
  /*         Tailored Thresholds */
  /*  */
  /*     The YCbCr tailored thresholds (SkinSegmentArgs.YCbCrThresholdsGeneric) are used when */
  /*     TailoredThresholdsTF is set to true. The threshold values are set based upon skin-color   */
  /*     samples collected from the input video. The threshold types include those used in the generic */
  /*     thresholds as well as a Y-channel maximum. The Y-channel maximum may be more sensitive than */
  /*     other thresholds to individual differences in facial colors. Due to this sensitivity, this */
  /*     value is not used for generic thresholds but is used for tailored thresholds as tailored */
  /*     thresholds are based upon the face in the video. */
  /*  */
  /*     The skin-color samples are collected from the input video. For details on the collection of  */
  /*     skin-color samples, see function ROIMeans_FirstRead_CollectSkinColorSamples. Before a */
  /*     sample is collected by function ROIMeans_FirstRead_CollectSkinColorSamples, function  */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples calls function SkinSegmentMask to attempt to  */
  /*     isolate pixel colors corresponding to skin. When SkinSegmentMask is called by function  */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples samples, TailoredThresholdsTF is set to false; that  */
  /*     is, generic thresholds are used. As tailored thresholds are based upon skin-color samples that */
  /*     were filtered by the generic thresholds, the tailored thresholds can be expected to be more */
  /*     stringent compared to the generic thresholds. The term "sample" refers to two values taken  */
  /*     from each YCbCr color channel of skin-segmented ROI. Specifically, the the minimum and maximum */
  /*     color values are taken from each channel.  */
  /*      */
  /*     Skin-color samples used for tailored YCbCr thresholds are collected by function  */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples, which is called by function ROIMeans_FirstRead.  */
  /*     For details on the collection of skin-color samples, see function  */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples.  */
  /*  */
  /*     After a certain number of samples has been collected, the samples are used to set the tailored  */
  /*     threshold values. The setting of thresholds from skin-color samples is conduted by function */
  /*     SkinSegment_SetThresholds. The number of samples required to set the tailored threshold  */
  /*     values, SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold, is specified by function  */
  /*     SkinSegment_ConfigSetup. This value can only be modified by adjusting the code within this */
  /*     function.  */
  /*  */
  /*     It has been observed that if the skin-color samples are too heavily concentrated within a  */
  /*     particular portion of the video, the thresholds that come from them can be too restrictive.  */
  /*     This is likey because samples limited to a brief portion of the video do not contain a */
  /*     sufficient level enough heterogeneity to reflect the color variations across the video. To  */
  /*     address this restrictiveness, the thresholds are reset periodically. Specifically, the  */
  /*     thresholds are reset after a specified number of frames has elapsed since the thresholds were  */
  /*     last set or reset. This number of frames is specified by  */
  /*     SkinSegmentConfig.TailoredData.ThresholdOpsInterval, which is set by function */
  /*     SkinSegment_ConfigSetup. This value can only be modified by adjusting the code within function */
  /*     SkinSegment_ConfigSetup. */
  /*  */
  /*     Although resetting the thresholds addresses the lack of heterogeneity across most of the  */
  /*     video, heterogeneity may still be unacceptably low between the first setting of the thresholds */
  /*     and the first resetting of the thresholds. This may occur if the skin-color samples are */
  /*     collected within close proximity. One condition that causes samples to be collected within  */
  /*     close proximity is a low frame-skipping rate (ROIGeneralConfig.ROISkipFrameThreshold; see */
  /*     function ROIGeneralConfig_Setup). To increase the heterogeneity in this case, the number of  */
  /*     skin-color samples required before the first thresholds are set  */
  /*     (SkinSegmentConfig.TailoredData.SkinColorSamples_NThreshold) is increased when the   */
  /*     frame-skipping rate is relatively low (see funtion SkinSegment_ConfigSetup).  */
  /*  */
  /*     Before the required number of skin-color samples has been collected, generic thresholds are */
  /*     used in place of tailored thresholds. If argument TailoredThresholdsTF is set to true,  */
  /*     specifying that tailored thresholds should be used, generic thresholds will be used if the  */
  /*     required number of samples has not been collected. Within the current function, the flag */
  /*     DontUseTailoredTF is set to true in this case to indicate that generic thresholds should be   */
  /*     used in place of tailored thresholds. */
  /*      */
  /*     For each skin-color sample, minimums and maximums are taken from each colorspace channel.  */
  /*     These values are set aside until the thresholds are to be set or reset. When setting or  */
  /*     resetting occurs, percentiles are applied to these values to extract the values at lower and */
  /*     upper percentiles. The value at the lower percentile becomes the lower threshold and the */
  /*     value at the upper percentile becomes the upper percentile. For example, suppose the lower and  */
  /*     upper percentiles are specified as 1.5 and 98.5, respecively. From all skin-color samples */
  /*     previously collected, the sample values from each channel that occur at the 1.5th percentile   */
  /*     and 98.5th percentile become the lower the upper thresholds, respectively. One point of  */
  /*     confusion may be that the terms "minimum" and "maximum" are used for two purposes here. */
  /*     The first use is in taking the minimum and maximum of each skin-color sample. These minimums */
  /*     and maximums are set aside until the percentiles are applied. When the percentiles are  */
  /*     applied, the lower percentile becomes the lower threshold and the upper percentile becomes the */
  /*     upper threshold. Although the terms "upper" and "lower" and used to refer to these thresholds */
  /*     for clarity, the terms "minimum" and "maximum" would also be appropriate. That is, the lower, */
  /*     or minimum, threshold is selected from a collection of minimum values; the upper, or maximum, */
  /*     threshold is selected from a collection of maximum values. */
  /*  */
  /*     One set of percentiles is used for the Y, Cb, Cr, Cb-to-Cr ratio, and H thresholds, and a  */
  /*     separate set of percentiles is used for the S thresholds. A separate set of percentiles is  */
  /*     used for the S thresholds because it has been observed that a wider range is appropriate for */
  /*     the S color channel. These percentiles are specified by function SkinSegmentConfig_Setup. The */
  /*     percentiles can be modified only by adjusting the code within SkinSegmentConfig_Setup. */
  /*  */
  /*     Within the current function, the YCbCr tailored threshold operations are conducted by function   */
  /*     SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold. */
  /*  */
  /*     -- HSV Pixel-Color Thresholds -- */
  /*    */
  /*     HSV color thresholds in use: */
  /*  */
  /*     - H-channel maximum */
  /*     - S-channel minimum */
  /*     - S-channel maximum (tailored-thresholds only) */
  /*  */
  /*     Apply color thresholds to individual pixels from the hue (H) and saturation (S) channels of   */
  /*     the HSV colorspace. */
  /*      */
  /*     Use either the generic HSV color thresholds or tailored HSV color thresholds. The use of */
  /*     tailored thresholds is specified by argument TailoredThresholdsTF. However, generic  */
  /*     thresholds are used when TailoredThresholdsTF is true if the criterion for using tailored  */
  /*     thresholds has not been satisfied, which is indicated by DontUseTailoredTF == true. */
  /*  */
  /*         Generic Thresholds */
  /*  */
  /*     The HSV generic color thresholds (SkinSegmentArgs.HSVThresholdsGeneric) are used when */
  /*     TailoredThresholdsTF is set to false. Thresholds include an H-channel maximum and an S-channel */
  /*     minimum. */
  /*      */
  /*     The threshold values are set by an argument, SkinSegmentThresholdsGenericHSV, to function  */
  /*     FacePulseRate. If the argument is not specified, default values are used. The default H and S   */
  /*     minimums and maximums are based on testing by DPM.  */
  /*       */
  /*     Function SkinSegment_ConfigSetup sets the values for SkinSegmentArgs.HSVThresholdsGeneric */
  /*     based on argument SkinSegmentThresholdsGenericHSV.     */
  /*  */
  /*     Within the current function, the HSV generic threshold operations are conducted by function   */
  /*     SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold. */
  /*  */
  /*         Tailored Thresholds */
  /*  */
  /*     The H and S tailored color thresholds (SkinSegmentArgs.HSThresholdsTailored) are used when */
  /*     TailoredThresholdsTF is set to true. The combination of a maximum for the H channel and a   */
  /*     minimum and a maximum for the S channel is based on Dahmani et al. (2020).  */
  /*      */
  /*     As with the tailored YCbCr thresholds, these thresholds are set based upon skin-color samples  */
  /*     collected from the input video. The process of setting the H and S tailored thresholds is   */
  /*     identical to the process of setting the tailored YCbCr thresholds.  */
  /*  */
  /*     If argument TailoredThresholdsTF is specified as true but the required number of samples has */
  /*     not been acquired, the H and S tailored thresholds will not be used. As with the tailored  */
  /*     YCbCr thresholds, the flag DontUseTailoredTF will be set to true to cause the H and S tailored  */
  /*     thresholds not to be used. */
  /*  */
  /*     Within the current function, the H and S tailored threshold operations are conducted by    */
  /*     function SkinSegmentMask_Threshold_Colors, which is called by function  */
  /*     SkinSegmentMask_Threshold. */
  /*  */
  /*     -- Low- and High-Severity Tailored Thresholds --  */
  /*  */
  /*     When TailoredThresholdsSevereTF == true, high-severity thresholds are used when conducting */
  /*     segmentation with the tailored YCbCr and HSV thresholds. High-severity thresholds are used for  */
  /*     applications where the priority is to reduce false positives (pixels incorrectly classified as */
  /*     skin) at the expense of a greater number false negatives (pixels incorrectly classified as  */
  /*     non-skin). When false, low-severity thresholds are used. Low-severity thresholds are used for  */
  /*     applications where a balance is desired between false positives and false negatives.      */
  /*  */
  /*     -- Local-Range Pixel Threshold --  */
  /*  */
  /*     The local-range pixel threshold classifies pixels based upon the homogeneity of color values */
  /*     of nearby, or local, pixels. When the local range is relatively homogeneous rather than */
  /*     heterogeneous, the value of the local range will be lower. A relatively homogeneous color  */
  /*     range of a given pixel is used as a heuristic of a pixel corresponding to skin. This is based   */
  /*     on the assumption that true skin tends to occur in regions of homogeneous color. When the  */
  /*     local range of a pixel falls below a specified threshold (SkinSegmentArgs.HThresholdTailored),  */
  /*     the pixel is classified as skin. */
  /*  */
  /*     The threshold for local range is a static value; that is, it is not set by assessment of color  */
  /*     samples. The threshold value is set by function SkinSegmentConfig_Setup. The value can only be  */
  /*     modified by adjusting the code within SkinSegmentConfig_Setup. The effectiveness of the value  */
  /*     used was established through testing.  */
  /*  */
  /*     Within the current function, the local-range pixel threshold operations are conducted by    */
  /*     function SkinSegmentMask_Threshold_Range, which is called by function  */
  /*     SkinSegmentMask_Threshold. */
  /*  */
  /*     -- Morphological Close of Patchy Regions --  */
  /*  */
  /*     Following the application of these thresholds, a two-dimensional logical matrix is assigned  */
  /*     where pixels that satisfied all thresholds are classified as true and pixels that did not are */
  /*     classified as false. A morphological close operation is then applied to the logical matrix.  */
  /*     The morphological close tends to fill in classification holes, where a hole is loosely defined  */
  /*     as a region of pixels classified as true that are enclosed by pixels classified as false.   */
  /*     Holes are filled in based on the assumption that true skin tends to be distributed in the face   */
  /*     in contiguous, rather than patchy, regions. */
  /*      */
  /*     The morphological close fills in holes only below a certain shape and size, which are    */
  /*     determined by the shape and size of the morphological structuring element, such that many  */
  /*     holes are not filled. Otherwise, large regions classified as true -- which are assumed to be  */
  /*     regions of skin -- may be erroneously filled. For a description on the choice of structuring  */
  /*     element used, see function SkinSegmentMask_MorphClose.  */
  /*  */
  /*     Within the current function, the morphological close operations are conducted by function   */
  /*     SkinSegmentMask_Threshold_MorphClose, which is called by function SkinSegmentMask_Threshold. */
  /*  */
  /*     -- Return Skin-Segmentation Mask Without Performing Colorspace Conversion -- */
  /*  */
  /*     To return a skin-segmentation mask without performing colorspace conversion, the colorspaces */
  /*     needed for skin-segmentation can be entered as input. These include YSingle, CbSingle,  */
  /*     CrSingle, HSingle, and SSingle. If all of these color channels are non-empty, colorspace */
  /*     conversion will not be performed. */
  /*  */
  /*     Additionally, IsSkinMask_Range, a skin-segmentation based upon the local range, can also be */
  /*     be entered as input.  */
  /*  */
  /*     A case where these may be entered is where skin segmentation is first run with either tailored */
  /*     thresholds on or off and it is desired to rerun the skin segmentation using tailored or non- */
  /*     tailored thresholds. In this case, the color channels and IsSkinMask_Range would have been */
  /*     assigned previously and can be reused. */
  /*  */
  /*     -- Color Channel Return Values -- */
  /*  */
  /*     The H and S channels of the HSV colorspace and the Y, Cb, and Cr channels of the YCbCr  */
  /*     colorspace are assigned during the operations of function SkinSegmentMask_Threshold. For  */
  /*     efficiency, these channels can be returned for reuse by other functions within function  */
  /*     FacePulseRate. One use of these values by another function is to periodically reset the color   */
  /*     thresholds (YCbCrThresholds_Tailored, HSThresholds_Tailored) used by the current function;   */
  /*     this is conducted by function SkinSegment_SetThresholds. To return these channels for reuse by */
  /*     other functions, the values are assigned to matrices, which are quite large due to the number  */
  /*     of pixels processed. Assignment to these large matrices may incur additional processing time.  */
  /*     To avoid this processing time when values are not to be reused, whether the channels are  */
  /*     returned can be controlled by arguments.  */
  /*  */
  /*     Argument ReturnYTF determines whether the Y channel is returned. Argument ReturnCbCrTF  */
  /*     determines whether the Cb and Cr channels are returned. Argument ReturnHSTF determines whether  */
  /*     the H and S channels are returned.     */
  /*            */
  /*  */
  /*     Notes */
  /*     ----- */
  /*  */
  /*     For detailed descriptions of the implementation of settings used in this function, see  */
  /*     function SkinSegmentConfig_Setup, which sets the settings. */
  /*  */
  /*     To view an image segmented with the skin-segmentation mask returned by this function, run the */
  /*     following code. The resulting image will be segmented in the same manner it is segmented in */
  /*     function FacePulseRate. */
  /*     SkinSegmented =        ... Segmented image */
  /*         AreaToSegment .*   ... Original image prior to segmentation */
  /*         uint8(IsSkinMask); %   Segmentation mask */
  /*  */
  /*  */
  /*     Requires */
  /*     -------- */
  /*  */
  /*         - Image Processing Toolbox (when non-compiled functions are used) */
  /*  */
  /*  */
  /*     References */
  /*     ---------- */
  /*  */
  /*     For helpful Matlab documentation on image segmentation operations, see the Matlab   */
  /*     documentation topic "image segmentation". */
  /*  */
  /*     Dahmani, D., Cheref, M., & Larabi, S. (2020). Zero-sum game theory model for segmenting skin  */
  /*     regions. Image and Vision Computing, 103925. */
  /*  */
  /*     McDuff, D., & Blackford, E. (2019, July). iphys: An open non-contact imaging-based  */
  /*     physiological measurement toolbox. In 2019 41st Annual International Conference of the IEEE  */
  /*     Engineering in Medicine and Biology Society (EMBC) (pp. 6521-6524). IEEE. */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
  /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
  /*     licensing, please contact the author. */
  /* %%%%% Code generation specifications %%%%%% */
  /* Inline function */
  /* Declare variables: */
  /*                               Upp. Bounds    Var. Size (T/F) */
  /* %%%%% Parse input arguments %%%%%% */
  /* Note: SkinSegmentMask_ParseArgs is a custom function located within folder FacePulseRate. */
  /* SkinSegmentMask_ParseArgs   Parse imput arguments to function SkinSegmentMask_Ops.  */
  /*                                                */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, called by function SkinSegmentMask_Ops. */
  /*  */
  /*  */
  /*     Code Generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation.     */
  /*  */
  /*  */
  /*     Description */
  /*     ----------- */
  /*  */
  /*     Parse imput arguments to function SkinSegmentMask_Ops. */
  /*  */
  /*     -- Adjustment to thresholds -- */
  /*  */
  /*     Function SkinSegmentMask_Threshold_Colors will only use < and > for efficiency rather than <=     */
  /*     and >=, although <= and >= are more appropriate as the thresholds are intended to accept    */
  /*     values equal to them. To use < and > while also allowing equality, the thresholds are  */
  /*     modified.  */
  /*  */
  /*     Note that for the thresholds of floating-point type, even if <= and >= were used, the     */
  /*     thresholds would still need to be modified to allow a tolerance for floating-point equality. */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
  /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
  /*     licensing, please contact the author.  */
  /* Inline function */
  /* %%%%% Local range %%%%%% */
  /* Structuring element width for calculating local range for a given pixel: */
  /* Value assigned in function SkinSegment_ConfigSetup. */
  /* Individual pixel local color range threshold:  */
  /* Value assigned in function SkinSegment_ConfigSetup. */
  /* Should be type uint8 for fastest evaluation.  */
  /* Type uint8. */
  /* Adjust maximum */
  /* %%%%% Color thresholds %%%%%% */
  /* The Cb-to-Cr ratio, H, and S thresholds use a smaller adjustment because the intervals between */
  /* colors are smaller. */
  /* %%%%% --- Generic thresholds %%%%%% */
  /* Values assigned in function SkinSegment_ConfigSetup.   */
  /* Note: these should be in type single for fastest evaluation. */
  /* YCbCr thresholds */
  /* Type single. */
  /* HSV thresholds */
  /* Type single. */
  /* Adjust minimums */
  YCbCrThresholds_Generic[0] = SkinSegmentArgs->YCbCrThresholdsGeneric[0] - 0.1F;

  /* Y min */
  YCbCrThresholds_Generic[1] = SkinSegmentArgs->YCbCrThresholdsGeneric[1] - 0.1F;

  /* Cb min */
  YCbCrThresholds_Generic[3] = SkinSegmentArgs->YCbCrThresholdsGeneric[3] - 0.1F;

  /* Cr min */
  YCbCrThresholds_Generic[5] = SkinSegmentArgs->YCbCrThresholdsGeneric[5] -
    0.01F;

  /* Cb-to-Cr ratio min */
  HSThresholds_Generic[1] = SkinSegmentArgs->HSThresholdsGeneric[1] - 0.01F;

  /* S min */
  /* Adjust maximums */
  YCbCrThresholds_Generic[2] = SkinSegmentArgs->YCbCrThresholdsGeneric[2] + 0.1F;

  /* Cb max */
  YCbCrThresholds_Generic[4] = SkinSegmentArgs->YCbCrThresholdsGeneric[4] + 0.1F;

  /* Cr max */
  YCbCrThresholds_Generic[6] = SkinSegmentArgs->YCbCrThresholdsGeneric[6] +
    0.01F;

  /* Cb-to-Cr ratio max */
  HSThresholds_Generic[0] = SkinSegmentArgs->HSThresholdsGeneric[0] + 0.01F;

  /* H max */
  /* %%%%% --- Tailored thresholds %%%%%% */
  /* Values assigned in function SkinSegment_SetThresholds. */
  /* Note: a threshold is not used for the value (V) channel of the HSV colorspace.  */
  /* Note: these should be in type single for fastest evaluation.  */
  /* Low-severity tailored thresholds */
  if (!TailoredThresholdsSevereTF) {
    /* YCbCr thresholds */
    /* Type single. */
    for (i = 0; i < 8; i++) {
      YCbCrThresholds_Tailored[i] = SkinSegmentArgs->YCbCrThresholdsTailored[i];
    }

    /* HSV thresholds */
    /* Type single. */
    HSThresholds_Tailored[0] = SkinSegmentArgs->HSThresholdsTailored[0];
    HSThresholds_Tailored[1] = SkinSegmentArgs->HSThresholdsTailored[1];
    HSThresholds_Tailored[2] = SkinSegmentArgs->HSThresholdsTailored[2];

    /* High-severity tailored thresholds    */
  } else {
    /* YCbCr thresholds */
    /* Type single. */
    for (i = 0; i < 8; i++) {
      YCbCrThresholds_Tailored[i] = SkinSegmentArgs->
        YCbCrThresholdsTailored_Sev[i];
    }

    /* HSV thresholds */
    /* Type single. */
    HSThresholds_Tailored[0] = SkinSegmentArgs->HSThresholdsTailored_Sev[0];
    HSThresholds_Tailored[1] = SkinSegmentArgs->HSThresholdsTailored_Sev[1];
    HSThresholds_Tailored[2] = SkinSegmentArgs->HSThresholdsTailored_Sev[2];
  }

  /* Adjust minimums */
  YCbCrThresholds_Tailored[0] -= 0.1F;

  /* Y min */
  YCbCrThresholds_Tailored[2] -= 0.1F;

  /* Cb min */
  YCbCrThresholds_Tailored[4] -= 0.1F;

  /* Cr min */
  YCbCrThresholds_Tailored[6] -= 0.01F;

  /* Cb-to-Cr ratio min */
  HSThresholds_Tailored[1] -= 0.01F;

  /* S min */
  /* Adjust maximums */
  YCbCrThresholds_Tailored[1] -= 0.1F;

  /* Y min */
  YCbCrThresholds_Tailored[3] += 0.1F;

  /* Cb max */
  YCbCrThresholds_Tailored[5] += 0.1F;

  /* Cr max */
  YCbCrThresholds_Tailored[7] += 0.01F;

  /* Cb-to-Cr ratio max */
  HSThresholds_Tailored[0] += 0.01F;

  /* H max */
  /* Flag not to use tailored thresholds: */
  /* Whether a sufficient number of skin-color samples was collected to activate tailored skin */
  /* segmentation. For details on the collection skin-color samples, see function */
  /* ROIMeans_FirstRead_CollectSkinColorSamples. */
  /* Value assigned by function SkinSegment_SetThresholds. */
  /* %%%%% Morphological close %%%%%% */
  /* High severity of morphological close operation */
  if (MorphCloseSevereTF) {
    MorphCloseNeighborhoodRadius = SkinSegmentArgs->MorphCloseSELargeWidth_Tuned;

    /* Low severity of morphological close operation */
  } else {
    MorphCloseNeighborhoodRadius =
      SkinSegmentArgs->MorphCloseSEMediumWidth_Tuned;
  }

  /* %%%%% Number of elements in input matrices %%%%%% */
  /* Number of elements of a given matrix */
  /* Scalar; type int32. */
  NElements_Matrix = NRows_Matrix * NCols_Matrix;

  /* end function */
  /* %%%%% Apply pixel-color and pixel-color local range thresholds %%%%%% */
  /* Apply individual pixel-color and pixel-color local range thresholds to assign a skin-segmentation  */
  /* mask. */
  /* Note: SkinSegmentMask_Threshold is a custom function located within folder FacePulseRate. */
  i = YBounded_Single->size[0] * YBounded_Single->size[1];
  YBounded_Single->size[0] = YSingle->size[0];
  YBounded_Single->size[1] = YSingle->size[1];
  emxEnsureCapacity_real32_T(YBounded_Single, i);
  loop_ub = YSingle->size[0] * YSingle->size[1];
  for (i = 0; i < loop_ub; i++) {
    YBounded_Single->data[i] = YSingle->data[i];
  }

  i = CbBounded_Single->size[0] * CbBounded_Single->size[1];
  CbBounded_Single->size[0] = CbSingle->size[0];
  CbBounded_Single->size[1] = CbSingle->size[1];
  emxEnsureCapacity_real32_T(CbBounded_Single, i);
  loop_ub = CbSingle->size[0] * CbSingle->size[1];
  for (i = 0; i < loop_ub; i++) {
    CbBounded_Single->data[i] = CbSingle->data[i];
  }

  i = CrBounded_Single->size[0] * CrBounded_Single->size[1];
  CrBounded_Single->size[0] = CrSingle->size[0];
  CrBounded_Single->size[1] = CrSingle->size[1];
  emxEnsureCapacity_real32_T(CrBounded_Single, i);
  loop_ub = CrSingle->size[0] * CrSingle->size[1];
  for (i = 0; i < loop_ub; i++) {
    CrBounded_Single->data[i] = CrSingle->data[i];
  }

  i = HBounded_Single->size[0] * HBounded_Single->size[1];
  HBounded_Single->size[0] = HSingle->size[0];
  HBounded_Single->size[1] = HSingle->size[1];
  emxEnsureCapacity_real32_T(HBounded_Single, i);
  loop_ub = HSingle->size[0] * HSingle->size[1];
  for (i = 0; i < loop_ub; i++) {
    HBounded_Single->data[i] = HSingle->data[i];
  }

  i = SBounded_Single->size[0] * SBounded_Single->size[1];
  SBounded_Single->size[0] = SSingle->size[0];
  SBounded_Single->size[1] = SSingle->size[1];
  emxEnsureCapacity_real32_T(SBounded_Single, i);
  loop_ub = SSingle->size[0] * SSingle->size[1];
  for (i = 0; i < loop_ub; i++) {
    SBounded_Single->data[i] = SSingle->data[i];
  }

  SkinSegmentMask_Threshold(emlrtRootTLSGlobal, RBounded_Uint8, GBounded_Uint8,
    BBounded_Uint8, YBounded_Single, CbBounded_Single, CrBounded_Single,
    HBounded_Single, SBounded_Single, IsSkinMask_Range, NRows_Matrix,
    NCols_Matrix, NElements_Matrix, YCbCrThresholds_Generic,
    TailoredThresholdsTF, !SkinSegmentArgs->c_SkinColorSamples_NThresholdPa,
    YCbCrThresholds_Tailored, ReturnYTF, ReturnCbCrTF, HSThresholds_Generic,
    HSThresholds_Tailored, ReturnHSTF, SkinSegmentArgs->RangeSEWidth, (uint8_T)
    (SkinSegmentArgs->RangeThreshold + 1U), XOffset, YOffset, IsSkinMask);

  /* %%%%% Morphologically close skin-segmentation mask regions with patchy classifications %%%%%% */
  /* Note: SkinSegmentMask_MorphClose is a custom function located within folder FacePulseRate. */
  /* SkinSegmentMask_MorphClose    Morphologically close regions with patchy skin classification to  */
  /*                               refine the skin-segmentation mask previously assigned by comparison  */
  /*                               to thresholds. */
  /*                                                                            */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by function SkinSegmentMask_Ops. */
  /*  */
  /*  */
  /*     Code Generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*  */
  /*     Description */
  /*     ----------- */
  /*  */
  /*     For a description of the assumptions behind the use of a morphological close to classify */
  /*     pixels as skin, see function SkinSegmentMask_Ops.   */
  /*  */
  /*     Apply a morphological close operation to the skin-segmentation mask resulting from thresholds */
  /*     previously applied (by function SkinSegmentMask_Threshold). The morphological close tends to  */
  /*     fill in classification holes, where a hole is loosely defined as a region of pixels classified  */
  /*     as true that are enclosed by pixels classified as false. The morphological close fills in  */
  /*     holes only below a specified size (specified by a morphological structuring element), such  */
  /*     that many holes are not filled.     */
  /*       */
  /*     A morphological dilation followed by a morphological erosion is conducted to perform the   */
  /*     morphological close. These operations are conducted by Matlab functions imerode and imdilate. */
  /*     Although a Matlab function is available to conduct a close (imclose), it has been observed   */
  /*     that using imerode followed by imdilate is more efficient. */
  /*  */
  /*     For a description of the choice of structuring element used in the morphological close, see  */
  /*     the description below in section "Assign structuring element".   */
  /*  */
  /*     -- Structuring Element Specifications -- */
  /*  */
  /*     - Severity == high: */
  /*  */
  /*     Use liberal dilation and erosion to mask non-skin pixels  */
  /*     Do so by using a large morphological structuring element (SE), which specifies the size of     */
  /*     dilation and erosion to carry out on each pixel (where pixel == 0). High severity may favor */
  /*     the rejection of non-skin pixels over the retention of of true-skin pixels. Function  */
  /*     FaceDetect and SkinDetect specify skin segmentation with high severity. This severity may be   */
  /*     useful for these functions because the priority in these functions is avoiding non-skin  */
  /*     pixels rather than retaining as many pixels as possible that are actually skin.     */
  /*  */
  /*     - Severity == low: */
  /*  */
  /*     Use moderate dilation and erosion to mask non-skin pixels. */
  /*     Do so by using a medium morphological structuring element (SE), which specifies the size of   */
  /*     dilation to carry out on each pixel (where pixel == 0). Compared to high severity, low  */
  /*     severity is intended to strike a balance between rejecting pixels and accepting pixels that    */
  /*     are actually skin. Function ROIMeans_TakeMeans specifies skin segmentation with low severity.  */
  /*     This low severity may be useful for the purpose of function ROIMeans_TakeMeans, which is to    */
  /*     calculate the accurate mean of an ROI. The ROIs that ROIMeans_TakeMeans processes have been  */
  /*     previously processed by functions FaceDetect and SkinDetect, which specify high severity, so  */
  /*     these ROIs may already be expected to have benefited from adjustment based upon avoidance of   */
  /*     non-skin pixels. */
  /*  */
  /*     -- Notes --  */
  /*  */
  /*     By default, Matlab's morphological operations act on true values, not false values, although */
  /*     false values (non-skin) are the target. */
  /*     */
  /*     For Matlab documentation discussing removal of patchy regions, see the Matlab documentation */
  /*     topic "Detect Cell Using Edge Detection and Morphology"  */
  /*     (https://www.mathworks.com/help/images/detecting-a-cell-using-image-segmentation.html). */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
  /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
  /*     licensing, please contact the author. */
  /* %%%%% Code-generation settings %%%%%% */
  /* Inline function */
  /* %%%%% Binary Packing %%%%%% */
  /* Note: For use as a Matlab function rather than code generation for a mex function, it is faster  */
  /* not to pack the logical matrix. */
  /* Pack logical image for increased performance of morphological functions  */
  loop_ub = (int32_T)muDoubleScalarCeil((real_T)IsSkinMask->size[0] / 32.0);
  emxInit_uint32_T(&IsSkinMask_PixelColorPacked, 2, true);
  if ((IsSkinMask->size[0] == 0) || (IsSkinMask->size[1] == 0)) {
    i = IsSkinMask_PixelColorPacked->size[0] * IsSkinMask_PixelColorPacked->
      size[1];
    IsSkinMask_PixelColorPacked->size[0] = loop_ub;
    IsSkinMask_PixelColorPacked->size[1] = IsSkinMask->size[1];
    emxEnsureCapacity_uint32_T(IsSkinMask_PixelColorPacked, i);
    loop_ub *= IsSkinMask->size[1];
    for (i = 0; i < loop_ub; i++) {
      IsSkinMask_PixelColorPacked->data[i] = 0U;
    }
  } else {
    i = IsSkinMask_PixelColorPacked->size[0] * IsSkinMask_PixelColorPacked->
      size[1];
    IsSkinMask_PixelColorPacked->size[0] = loop_ub;
    IsSkinMask_PixelColorPacked->size[1] = IsSkinMask->size[1];
    emxEnsureCapacity_uint32_T(IsSkinMask_PixelColorPacked, i);
    bwSize[0] = IsSkinMask->size[0];
    bwSize[1] = IsSkinMask->size[1];
    bwpSize[0] = loop_ub;
    bwpSize[1] = IsSkinMask->size[1];
    bwPackingtbb(&IsSkinMask->data[0], &bwSize[0],
                 &IsSkinMask_PixelColorPacked->data[0], &bwpSize[0], true);
  }

  /* %%%%% Assign structuring element %%%%%% */
  /* Because structuring element objects are compile-time constants, a fixed number of structuring   */
  /* element objects are made available, each of which has a corresponding function. The function   */
  /* with the structuring element closest in size to the specified structuring element size is used.   */
  /* Select function from available functions */
  /* Select the function with the SE width most similar to the specified SE width. */
  /* Local function. */
  /* Scalar; type int16. */
  /* end main function */
  /* ============================================================================================= */
  /* Local functions  */
  /* ============================================================================================= */
  /* ============================================================================================= */
  /* SelectFunction    Select the function with the SE width most similar to  */
  /*                   MorphCloseNeighborhoodWidth.    */
  /*  */
  /*     Description: */
  /*  */
  /*     Select the size of the structuring element to use. The size is partly determined according to */
  /*     MorphCloseSevereTF.  */
  /* Inline function */
  /* %%%%% High severity %%%%%% */
  if (MorphCloseSevereTF) {
    /* Scalars; type int16. */
    if ((int16_T)(12 - MorphCloseNeighborhoodRadius) < 0) {
      Diff4 = (int16_T)(MorphCloseNeighborhoodRadius - 12);
    } else {
      Diff4 = (int16_T)(12 - MorphCloseNeighborhoodRadius);
    }

    if ((int16_T)(22 - MorphCloseNeighborhoodRadius) < 0) {
      Diff22 = (int16_T)(MorphCloseNeighborhoodRadius - 22);
    } else {
      Diff22 = (int16_T)(22 - MorphCloseNeighborhoodRadius);
    }

    if ((int16_T)(32 - MorphCloseNeighborhoodRadius) < 0) {
      Diff10 = (int16_T)(MorphCloseNeighborhoodRadius - 32);
    } else {
      Diff10 = (int16_T)(32 - MorphCloseNeighborhoodRadius);
    }

    if (Diff4 < Diff22) {
      functionWidthToUse = 12;
      Diff22 = Diff4;
    } else {
      functionWidthToUse = 22;
    }

    if (Diff10 < Diff22) {
      functionWidthToUse = 32;
      Diff22 = Diff10;
    }

    if ((int16_T)(50 - MorphCloseNeighborhoodRadius) < 0) {
      i = (int16_T)(MorphCloseNeighborhoodRadius - 50);
    } else {
      i = (int16_T)(50 - MorphCloseNeighborhoodRadius);
    }

    if (i < Diff22) {
      functionWidthToUse = 50;
    }

    /* Note: Use this pattern for adding additional SEs */
    /*     %{ */
    /*     if DiffX < Diff */
    /*  */
    /*         functionWidthToUse = int16(X); */
    /*      */
    /*         Diff = DiffX; %include this line if this is not the last condition */
    /*     end */
    /*     %} */
    /* %%%%% Low severity %%%%%% */
  } else {
    /* As low severity uses a structuring element specified by radius, divide width by 2 */
    /* Optimize division by two by bitwise operation. */
    /* Scalar; type int16. */
    MorphCloseNeighborhoodRadius >>= 1;

    /* Scalars; type int16. */
    if (4 - MorphCloseNeighborhoodRadius < 0) {
      Diff4 = (int16_T)(MorphCloseNeighborhoodRadius - 4);
    } else {
      Diff4 = (int16_T)(4 - MorphCloseNeighborhoodRadius);
    }

    if (6 - MorphCloseNeighborhoodRadius < 0) {
      Diff22 = (int16_T)(MorphCloseNeighborhoodRadius - 6);
    } else {
      Diff22 = (int16_T)(6 - MorphCloseNeighborhoodRadius);
    }

    if (10 - MorphCloseNeighborhoodRadius < 0) {
      Diff10 = (int16_T)(MorphCloseNeighborhoodRadius - 10);
    } else {
      Diff10 = (int16_T)(10 - MorphCloseNeighborhoodRadius);
    }

    if (Diff4 < Diff22) {
      functionWidthToUse = 4;
      Diff22 = Diff4;
    } else {
      functionWidthToUse = 6;
    }

    if (Diff10 < Diff22) {
      functionWidthToUse = 10;
      Diff22 = Diff10;
    }

    if (14 - MorphCloseNeighborhoodRadius < 0) {
      i = MorphCloseNeighborhoodRadius - 14;
    } else {
      i = 14 - MorphCloseNeighborhoodRadius;
    }

    if (i < Diff22) {
      functionWidthToUse = 14;
    }

    /* Note: Use this pattern for adding additional SEs */
    /*     %{ */
    /*     if DiffX < Diff */
    /*  */
    /*         functionWidthToUse = int16(X); */
    /*      */
    /*         Diff = DiffX; %include this line if this is not the last condition */
    /*     end */
    /*     %} */
  }

  /* %%%%% Erosion followed by dilation %%%%%% */
  /* Cast to type double for use by function imerode */
  /* Scalar; type double. */
  /* %%%%% --- High severity erosion and dilation %%%%%%  */
  emxInit_uint32_T(&c_IsSkinMask_PixelColor_DilateP, 2, true);
  emxInit_uint32_T(&d_IsSkinMask_PixelColor_DilateP, 2, true);
  emxInit_uint32_T(&c_IsSkinMask_PixelColor_ErodePa, 2, true);
  emxInit_uint32_T(&d_IsSkinMask_PixelColor_ErodePa, 2, true);
  emxInit_uint32_T(&B, 2, true);
  emxInit_uint32_T(&r, 2, true);
  if (MorphCloseSevereTF) {
    /* Use function corresponding to closest SE width */
    switch (functionWidthToUse) {
     case 12:
      /* Square structuring element with width of 12 pixels     */
      /* Packed binary image */
      /* Local function. */
      /* Type uint32. */
      /* end local function */
      /* ============================================================================================= */
      /* ErodeAndDilate_SESquare12    Erode and dilate with square structuring element of width 12. */
      /* Inline function */
      /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  eroded logical image */
      /*  logical image */
      /*  structuring element */
      /*  flag for packed image */
      /*  number of rows in unpacked image */
      setPackedFillBits(IsSkinMask_PixelColorPacked, NRows_Matrix);
      i = B->size[0] * B->size[1];
      B->size[0] = IsSkinMask_PixelColorPacked->size[0];
      B->size[1] = IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(B, i);
      for (b_i = 0; b_i < 12; b_i++) {
        d_nhood[b_i] = true;
      }

      bwSize[0] = IsSkinMask_PixelColorPacked->size[0];
      bwpSize[0] = 12.0;
      bwSize[1] = IsSkinMask_PixelColorPacked->size[1];
      bwpSize[1] = 1.0;
      erode_packed_uint32(&IsSkinMask_PixelColorPacked->data[0], &bwSize[0], 2.0,
                          &d_nhood[0], &bwpSize[0], 2.0, (real_T)NRows_Matrix,
                          &B->data[0], true);
      i = IsSkinMask_PixelColorPacked->size[0] *
        IsSkinMask_PixelColorPacked->size[1];
      IsSkinMask_PixelColorPacked->size[0] = B->size[0];
      IsSkinMask_PixelColorPacked->size[1] = B->size[1];
      emxEnsureCapacity_uint32_T(IsSkinMask_PixelColorPacked, i);
      loop_ub = B->size[0] * B->size[1];
      for (i = 0; i < loop_ub; i++) {
        IsSkinMask_PixelColorPacked->data[i] = B->data[i];
      }

      i = B->size[0] * B->size[1];
      B->size[0] = IsSkinMask_PixelColorPacked->size[0];
      B->size[1] = IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(B, i);
      for (b_i = 0; b_i < 12; b_i++) {
        d_nhood[b_i] = true;
      }

      bwSize[0] = IsSkinMask_PixelColorPacked->size[0];
      bwpSize[0] = 1.0;
      bwSize[1] = IsSkinMask_PixelColorPacked->size[1];
      bwpSize[1] = 12.0;
      erode_packed_uint32(&IsSkinMask_PixelColorPacked->data[0], &bwSize[0], 2.0,
                          &d_nhood[0], &bwpSize[0], 2.0, (real_T)NRows_Matrix,
                          &B->data[0], true);

      /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  dilated logical image */
      /*  structuring element */
      /*  flag for packed image */
      i = r->size[0] * r->size[1];
      r->size[0] = B->size[0];
      r->size[1] = B->size[1];
      emxEnsureCapacity_uint32_T(r, i);
      loop_ub = B->size[0] * B->size[1];
      for (i = 0; i < loop_ub; i++) {
        r->data[i] = B->data[i];
      }

      b_setPackedFillBits(r);
      i = B->size[0] * B->size[1];
      B->size[0] = r->size[0];
      B->size[1] = r->size[1];
      emxEnsureCapacity_uint32_T(B, i);
      loop_ub = r->size[0] * r->size[1];
      for (i = 0; i < loop_ub; i++) {
        B->data[i] = r->data[i];
      }

      i = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      d_IsSkinMask_PixelColor_ErodePa->size[0] = B->size[0];
      d_IsSkinMask_PixelColor_ErodePa->size[1] = B->size[1];
      emxEnsureCapacity_uint32_T(d_IsSkinMask_PixelColor_ErodePa, i);
      for (b_i = 0; b_i < 12; b_i++) {
        d_nhood[b_i] = true;
      }

      bwSize[0] = B->size[0];
      bwpSize[0] = 12.0;
      bwSize[1] = B->size[1];
      bwpSize[1] = 1.0;
      dilate_packed_uint32(&B->data[0], &bwSize[0], 2.0, &d_nhood[0], &bwpSize[0],
                           2.0, &d_IsSkinMask_PixelColor_ErodePa->data[0], true);
      i = IsSkinMask_PixelColorPacked->size[0] *
        IsSkinMask_PixelColorPacked->size[1];
      IsSkinMask_PixelColorPacked->size[0] =
        d_IsSkinMask_PixelColor_ErodePa->size[0];
      IsSkinMask_PixelColorPacked->size[1] =
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      emxEnsureCapacity_uint32_T(IsSkinMask_PixelColorPacked, i);
      loop_ub = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      for (i = 0; i < loop_ub; i++) {
        IsSkinMask_PixelColorPacked->data[i] =
          d_IsSkinMask_PixelColor_ErodePa->data[i];
      }

      i = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      d_IsSkinMask_PixelColor_ErodePa->size[0] =
        IsSkinMask_PixelColorPacked->size[0];
      d_IsSkinMask_PixelColor_ErodePa->size[1] =
        IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(d_IsSkinMask_PixelColor_ErodePa, i);
      for (b_i = 0; b_i < 12; b_i++) {
        d_nhood[b_i] = true;
      }

      bwSize[0] = IsSkinMask_PixelColorPacked->size[0];
      bwpSize[0] = 1.0;
      bwSize[1] = IsSkinMask_PixelColorPacked->size[1];
      bwpSize[1] = 12.0;
      dilate_packed_uint32(&IsSkinMask_PixelColorPacked->data[0], &bwSize[0],
                           2.0, &d_nhood[0], &bwpSize[0], 2.0,
                           &d_IsSkinMask_PixelColor_ErodePa->data[0], true);
      i = c_IsSkinMask_PixelColor_DilateP->size[0] *
        c_IsSkinMask_PixelColor_DilateP->size[1];
      c_IsSkinMask_PixelColor_DilateP->size[0] =
        d_IsSkinMask_PixelColor_ErodePa->size[0];
      c_IsSkinMask_PixelColor_DilateP->size[1] =
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      emxEnsureCapacity_uint32_T(c_IsSkinMask_PixelColor_DilateP, i);
      loop_ub = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      for (i = 0; i < loop_ub; i++) {
        c_IsSkinMask_PixelColor_DilateP->data[i] =
          d_IsSkinMask_PixelColor_ErodePa->data[i];
      }

      /* Square structuring element with width of 22 pixels     */
      /* %%%%% --- Low severity erosion and dilation %%%%%%    */
      /* %%%%% --- Unpack %%%%%%    */
      /* Unpack packed binary image */
      /* M x N matrix; type logical. */
      bwunpack(c_IsSkinMask_PixelColor_DilateP, NRows_Matrix, IsSkinMask);
      break;

     case 22:
      /* Packed binary image */
      /* Local function. */
      /* Type uint32. */
      /* end local function */
      /* ============================================================================================= */
      /* ErodeAndDilate_SESquare22    Erode and dilate with square structuring element of width 22. */
      /* Inline function */
      /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  eroded logical image */
      /*  logical image */
      /*  structuring element */
      /*  flag for packed image */
      /*  number of rows in unpacked image */
      setPackedFillBits(IsSkinMask_PixelColorPacked, NRows_Matrix);
      i = B->size[0] * B->size[1];
      B->size[0] = IsSkinMask_PixelColorPacked->size[0];
      B->size[1] = IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(B, i);
      for (b_i = 0; b_i < 22; b_i++) {
        nhood[b_i] = true;
      }

      bwSize[0] = IsSkinMask_PixelColorPacked->size[0];
      bwpSize[0] = 22.0;
      bwSize[1] = IsSkinMask_PixelColorPacked->size[1];
      bwpSize[1] = 1.0;
      erode_packed_uint32(&IsSkinMask_PixelColorPacked->data[0], &bwSize[0], 2.0,
                          &nhood[0], &bwpSize[0], 2.0, (real_T)NRows_Matrix,
                          &B->data[0], true);
      i = IsSkinMask_PixelColorPacked->size[0] *
        IsSkinMask_PixelColorPacked->size[1];
      IsSkinMask_PixelColorPacked->size[0] = B->size[0];
      IsSkinMask_PixelColorPacked->size[1] = B->size[1];
      emxEnsureCapacity_uint32_T(IsSkinMask_PixelColorPacked, i);
      loop_ub = B->size[0] * B->size[1];
      for (i = 0; i < loop_ub; i++) {
        IsSkinMask_PixelColorPacked->data[i] = B->data[i];
      }

      i = B->size[0] * B->size[1];
      B->size[0] = IsSkinMask_PixelColorPacked->size[0];
      B->size[1] = IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(B, i);
      for (b_i = 0; b_i < 22; b_i++) {
        nhood[b_i] = true;
      }

      bwSize[0] = IsSkinMask_PixelColorPacked->size[0];
      bwpSize[0] = 1.0;
      bwSize[1] = IsSkinMask_PixelColorPacked->size[1];
      bwpSize[1] = 22.0;
      erode_packed_uint32(&IsSkinMask_PixelColorPacked->data[0], &bwSize[0], 2.0,
                          &nhood[0], &bwpSize[0], 2.0, (real_T)NRows_Matrix,
                          &B->data[0], true);

      /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  dilated logical image */
      /*  structuring element */
      /*  flag for packed image */
      i = r->size[0] * r->size[1];
      r->size[0] = B->size[0];
      r->size[1] = B->size[1];
      emxEnsureCapacity_uint32_T(r, i);
      loop_ub = B->size[0] * B->size[1];
      for (i = 0; i < loop_ub; i++) {
        r->data[i] = B->data[i];
      }

      b_setPackedFillBits(r);
      i = B->size[0] * B->size[1];
      B->size[0] = r->size[0];
      B->size[1] = r->size[1];
      emxEnsureCapacity_uint32_T(B, i);
      loop_ub = r->size[0] * r->size[1];
      for (i = 0; i < loop_ub; i++) {
        B->data[i] = r->data[i];
      }

      i = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      d_IsSkinMask_PixelColor_ErodePa->size[0] = B->size[0];
      d_IsSkinMask_PixelColor_ErodePa->size[1] = B->size[1];
      emxEnsureCapacity_uint32_T(d_IsSkinMask_PixelColor_ErodePa, i);
      for (b_i = 0; b_i < 22; b_i++) {
        nhood[b_i] = true;
      }

      bwSize[0] = B->size[0];
      bwpSize[0] = 22.0;
      bwSize[1] = B->size[1];
      bwpSize[1] = 1.0;
      dilate_packed_uint32(&B->data[0], &bwSize[0], 2.0, &nhood[0], &bwpSize[0],
                           2.0, &d_IsSkinMask_PixelColor_ErodePa->data[0], true);
      i = IsSkinMask_PixelColorPacked->size[0] *
        IsSkinMask_PixelColorPacked->size[1];
      IsSkinMask_PixelColorPacked->size[0] =
        d_IsSkinMask_PixelColor_ErodePa->size[0];
      IsSkinMask_PixelColorPacked->size[1] =
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      emxEnsureCapacity_uint32_T(IsSkinMask_PixelColorPacked, i);
      loop_ub = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      for (i = 0; i < loop_ub; i++) {
        IsSkinMask_PixelColorPacked->data[i] =
          d_IsSkinMask_PixelColor_ErodePa->data[i];
      }

      i = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      d_IsSkinMask_PixelColor_ErodePa->size[0] =
        IsSkinMask_PixelColorPacked->size[0];
      d_IsSkinMask_PixelColor_ErodePa->size[1] =
        IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(d_IsSkinMask_PixelColor_ErodePa, i);
      for (b_i = 0; b_i < 22; b_i++) {
        nhood[b_i] = true;
      }

      bwSize[0] = IsSkinMask_PixelColorPacked->size[0];
      bwpSize[0] = 1.0;
      bwSize[1] = IsSkinMask_PixelColorPacked->size[1];
      bwpSize[1] = 22.0;
      dilate_packed_uint32(&IsSkinMask_PixelColorPacked->data[0], &bwSize[0],
                           2.0, &nhood[0], &bwpSize[0], 2.0,
                           &d_IsSkinMask_PixelColor_ErodePa->data[0], true);
      i = c_IsSkinMask_PixelColor_DilateP->size[0] *
        c_IsSkinMask_PixelColor_DilateP->size[1];
      c_IsSkinMask_PixelColor_DilateP->size[0] =
        d_IsSkinMask_PixelColor_ErodePa->size[0];
      c_IsSkinMask_PixelColor_DilateP->size[1] =
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      emxEnsureCapacity_uint32_T(c_IsSkinMask_PixelColor_DilateP, i);
      loop_ub = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      for (i = 0; i < loop_ub; i++) {
        c_IsSkinMask_PixelColor_DilateP->data[i] =
          d_IsSkinMask_PixelColor_ErodePa->data[i];
      }

      /* Square structuring element with width of 32 pixels     */
      /* %%%%% --- Low severity erosion and dilation %%%%%%    */
      /* %%%%% --- Unpack %%%%%%    */
      /* Unpack packed binary image */
      /* M x N matrix; type logical. */
      bwunpack(c_IsSkinMask_PixelColor_DilateP, NRows_Matrix, IsSkinMask);
      break;

     case 32:
      /* Packed binary image */
      /* Local function. */
      /* Type uint32. */
      /* end local function */
      /* ============================================================================================= */
      /* ErodeAndDilate_SESquare32    Erode and dilate with square structuring element of width 32. */
      /* Inline function */
      /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  eroded logical image */
      /*  logical image */
      /*  structuring element */
      /*  flag for packed image */
      /*  number of rows in unpacked image */
      setPackedFillBits(IsSkinMask_PixelColorPacked, NRows_Matrix);
      i = B->size[0] * B->size[1];
      B->size[0] = IsSkinMask_PixelColorPacked->size[0];
      B->size[1] = IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(B, i);
      for (b_i = 0; b_i < 32; b_i++) {
        b_nhood[b_i] = true;
      }

      bwSize[0] = IsSkinMask_PixelColorPacked->size[0];
      bwpSize[0] = 32.0;
      bwSize[1] = IsSkinMask_PixelColorPacked->size[1];
      bwpSize[1] = 1.0;
      erode_packed_uint32(&IsSkinMask_PixelColorPacked->data[0], &bwSize[0], 2.0,
                          &b_nhood[0], &bwpSize[0], 2.0, (real_T)NRows_Matrix,
                          &B->data[0], true);
      i = IsSkinMask_PixelColorPacked->size[0] *
        IsSkinMask_PixelColorPacked->size[1];
      IsSkinMask_PixelColorPacked->size[0] = B->size[0];
      IsSkinMask_PixelColorPacked->size[1] = B->size[1];
      emxEnsureCapacity_uint32_T(IsSkinMask_PixelColorPacked, i);
      loop_ub = B->size[0] * B->size[1];
      for (i = 0; i < loop_ub; i++) {
        IsSkinMask_PixelColorPacked->data[i] = B->data[i];
      }

      i = B->size[0] * B->size[1];
      B->size[0] = IsSkinMask_PixelColorPacked->size[0];
      B->size[1] = IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(B, i);
      for (b_i = 0; b_i < 32; b_i++) {
        b_nhood[b_i] = true;
      }

      bwSize[0] = IsSkinMask_PixelColorPacked->size[0];
      bwpSize[0] = 1.0;
      bwSize[1] = IsSkinMask_PixelColorPacked->size[1];
      bwpSize[1] = 32.0;
      erode_packed_uint32(&IsSkinMask_PixelColorPacked->data[0], &bwSize[0], 2.0,
                          &b_nhood[0], &bwpSize[0], 2.0, (real_T)NRows_Matrix,
                          &B->data[0], true);

      /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  dilated logical image */
      /*  structuring element */
      /*  flag for packed image */
      i = r->size[0] * r->size[1];
      r->size[0] = B->size[0];
      r->size[1] = B->size[1];
      emxEnsureCapacity_uint32_T(r, i);
      loop_ub = B->size[0] * B->size[1];
      for (i = 0; i < loop_ub; i++) {
        r->data[i] = B->data[i];
      }

      b_setPackedFillBits(r);
      i = B->size[0] * B->size[1];
      B->size[0] = r->size[0];
      B->size[1] = r->size[1];
      emxEnsureCapacity_uint32_T(B, i);
      loop_ub = r->size[0] * r->size[1];
      for (i = 0; i < loop_ub; i++) {
        B->data[i] = r->data[i];
      }

      i = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      d_IsSkinMask_PixelColor_ErodePa->size[0] = B->size[0];
      d_IsSkinMask_PixelColor_ErodePa->size[1] = B->size[1];
      emxEnsureCapacity_uint32_T(d_IsSkinMask_PixelColor_ErodePa, i);
      for (b_i = 0; b_i < 32; b_i++) {
        b_nhood[b_i] = true;
      }

      bwSize[0] = B->size[0];
      bwpSize[0] = 32.0;
      bwSize[1] = B->size[1];
      bwpSize[1] = 1.0;
      dilate_packed_uint32(&B->data[0], &bwSize[0], 2.0, &b_nhood[0], &bwpSize[0],
                           2.0, &d_IsSkinMask_PixelColor_ErodePa->data[0], true);
      i = IsSkinMask_PixelColorPacked->size[0] *
        IsSkinMask_PixelColorPacked->size[1];
      IsSkinMask_PixelColorPacked->size[0] =
        d_IsSkinMask_PixelColor_ErodePa->size[0];
      IsSkinMask_PixelColorPacked->size[1] =
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      emxEnsureCapacity_uint32_T(IsSkinMask_PixelColorPacked, i);
      loop_ub = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      for (i = 0; i < loop_ub; i++) {
        IsSkinMask_PixelColorPacked->data[i] =
          d_IsSkinMask_PixelColor_ErodePa->data[i];
      }

      i = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      d_IsSkinMask_PixelColor_ErodePa->size[0] =
        IsSkinMask_PixelColorPacked->size[0];
      d_IsSkinMask_PixelColor_ErodePa->size[1] =
        IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(d_IsSkinMask_PixelColor_ErodePa, i);
      for (b_i = 0; b_i < 32; b_i++) {
        b_nhood[b_i] = true;
      }

      bwSize[0] = IsSkinMask_PixelColorPacked->size[0];
      bwpSize[0] = 1.0;
      bwSize[1] = IsSkinMask_PixelColorPacked->size[1];
      bwpSize[1] = 32.0;
      dilate_packed_uint32(&IsSkinMask_PixelColorPacked->data[0], &bwSize[0],
                           2.0, &b_nhood[0], &bwpSize[0], 2.0,
                           &d_IsSkinMask_PixelColor_ErodePa->data[0], true);
      i = c_IsSkinMask_PixelColor_DilateP->size[0] *
        c_IsSkinMask_PixelColor_DilateP->size[1];
      c_IsSkinMask_PixelColor_DilateP->size[0] =
        d_IsSkinMask_PixelColor_ErodePa->size[0];
      c_IsSkinMask_PixelColor_DilateP->size[1] =
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      emxEnsureCapacity_uint32_T(c_IsSkinMask_PixelColor_DilateP, i);
      loop_ub = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      for (i = 0; i < loop_ub; i++) {
        c_IsSkinMask_PixelColor_DilateP->data[i] =
          d_IsSkinMask_PixelColor_ErodePa->data[i];
      }

      /* Square structuring element with width of 50 pixels     */
      /* %%%%% --- Low severity erosion and dilation %%%%%%    */
      /* %%%%% --- Unpack %%%%%%    */
      /* Unpack packed binary image */
      /* M x N matrix; type logical. */
      bwunpack(c_IsSkinMask_PixelColor_DilateP, NRows_Matrix, IsSkinMask);
      break;

     case 50:
      /* Packed binary image */
      /* Local function. */
      /* Type uint32. */
      /* end local function */
      /* ============================================================================================= */
      /* ErodeAndDilate_SESquare50    Erode and dilate with square structuring element of width 50. */
      /* Inline function */
      /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  eroded packed logical image */
      /*  packed logical image */
      /*  structuring element */
      /*  flag for packed image */
      /*  number of rows in unpacked image */
      setPackedFillBits(IsSkinMask_PixelColorPacked, NRows_Matrix);
      i = B->size[0] * B->size[1];
      B->size[0] = IsSkinMask_PixelColorPacked->size[0];
      B->size[1] = IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(B, i);
      for (b_i = 0; b_i < 50; b_i++) {
        c_nhood[b_i] = true;
      }

      bwSize[0] = IsSkinMask_PixelColorPacked->size[0];
      bwpSize[0] = 50.0;
      bwSize[1] = IsSkinMask_PixelColorPacked->size[1];
      bwpSize[1] = 1.0;
      erode_packed_uint32(&IsSkinMask_PixelColorPacked->data[0], &bwSize[0], 2.0,
                          &c_nhood[0], &bwpSize[0], 2.0, (real_T)NRows_Matrix,
                          &B->data[0], true);
      i = IsSkinMask_PixelColorPacked->size[0] *
        IsSkinMask_PixelColorPacked->size[1];
      IsSkinMask_PixelColorPacked->size[0] = B->size[0];
      IsSkinMask_PixelColorPacked->size[1] = B->size[1];
      emxEnsureCapacity_uint32_T(IsSkinMask_PixelColorPacked, i);
      loop_ub = B->size[0] * B->size[1];
      for (i = 0; i < loop_ub; i++) {
        IsSkinMask_PixelColorPacked->data[i] = B->data[i];
      }

      i = B->size[0] * B->size[1];
      B->size[0] = IsSkinMask_PixelColorPacked->size[0];
      B->size[1] = IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(B, i);
      for (b_i = 0; b_i < 50; b_i++) {
        c_nhood[b_i] = true;
      }

      bwSize[0] = IsSkinMask_PixelColorPacked->size[0];
      bwpSize[0] = 1.0;
      bwSize[1] = IsSkinMask_PixelColorPacked->size[1];
      bwpSize[1] = 50.0;
      erode_packed_uint32(&IsSkinMask_PixelColorPacked->data[0], &bwSize[0], 2.0,
                          &c_nhood[0], &bwpSize[0], 2.0, (real_T)NRows_Matrix,
                          &B->data[0], true);

      /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  dilated packed logical image */
      /*  packed logical image */
      /*  structuring element */
      /*  flag for packed image */
      i = r->size[0] * r->size[1];
      r->size[0] = B->size[0];
      r->size[1] = B->size[1];
      emxEnsureCapacity_uint32_T(r, i);
      loop_ub = B->size[0] * B->size[1];
      for (i = 0; i < loop_ub; i++) {
        r->data[i] = B->data[i];
      }

      b_setPackedFillBits(r);
      i = B->size[0] * B->size[1];
      B->size[0] = r->size[0];
      B->size[1] = r->size[1];
      emxEnsureCapacity_uint32_T(B, i);
      loop_ub = r->size[0] * r->size[1];
      for (i = 0; i < loop_ub; i++) {
        B->data[i] = r->data[i];
      }

      i = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      d_IsSkinMask_PixelColor_ErodePa->size[0] = B->size[0];
      d_IsSkinMask_PixelColor_ErodePa->size[1] = B->size[1];
      emxEnsureCapacity_uint32_T(d_IsSkinMask_PixelColor_ErodePa, i);
      for (b_i = 0; b_i < 50; b_i++) {
        c_nhood[b_i] = true;
      }

      bwSize[0] = B->size[0];
      bwpSize[0] = 50.0;
      bwSize[1] = B->size[1];
      bwpSize[1] = 1.0;
      dilate_packed_uint32(&B->data[0], &bwSize[0], 2.0, &c_nhood[0], &bwpSize[0],
                           2.0, &d_IsSkinMask_PixelColor_ErodePa->data[0], true);
      i = IsSkinMask_PixelColorPacked->size[0] *
        IsSkinMask_PixelColorPacked->size[1];
      IsSkinMask_PixelColorPacked->size[0] =
        d_IsSkinMask_PixelColor_ErodePa->size[0];
      IsSkinMask_PixelColorPacked->size[1] =
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      emxEnsureCapacity_uint32_T(IsSkinMask_PixelColorPacked, i);
      loop_ub = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      for (i = 0; i < loop_ub; i++) {
        IsSkinMask_PixelColorPacked->data[i] =
          d_IsSkinMask_PixelColor_ErodePa->data[i];
      }

      i = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      d_IsSkinMask_PixelColor_ErodePa->size[0] =
        IsSkinMask_PixelColorPacked->size[0];
      d_IsSkinMask_PixelColor_ErodePa->size[1] =
        IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(d_IsSkinMask_PixelColor_ErodePa, i);
      for (b_i = 0; b_i < 50; b_i++) {
        c_nhood[b_i] = true;
      }

      bwSize[0] = IsSkinMask_PixelColorPacked->size[0];
      bwpSize[0] = 1.0;
      bwSize[1] = IsSkinMask_PixelColorPacked->size[1];
      bwpSize[1] = 50.0;
      dilate_packed_uint32(&IsSkinMask_PixelColorPacked->data[0], &bwSize[0],
                           2.0, &c_nhood[0], &bwpSize[0], 2.0,
                           &d_IsSkinMask_PixelColor_ErodePa->data[0], true);
      i = c_IsSkinMask_PixelColor_DilateP->size[0] *
        c_IsSkinMask_PixelColor_DilateP->size[1];
      c_IsSkinMask_PixelColor_DilateP->size[0] =
        d_IsSkinMask_PixelColor_ErodePa->size[0];
      c_IsSkinMask_PixelColor_DilateP->size[1] =
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      emxEnsureCapacity_uint32_T(c_IsSkinMask_PixelColor_DilateP, i);
      loop_ub = d_IsSkinMask_PixelColor_ErodePa->size[0] *
        d_IsSkinMask_PixelColor_ErodePa->size[1];
      for (i = 0; i < loop_ub; i++) {
        c_IsSkinMask_PixelColor_DilateP->data[i] =
          d_IsSkinMask_PixelColor_ErodePa->data[i];
      }

      /* (Required for code generation)     */
      /* %%%%% --- Low severity erosion and dilation %%%%%%    */
      /* %%%%% --- Unpack %%%%%%    */
      /* Unpack packed binary image */
      /* M x N matrix; type logical. */
      bwunpack(c_IsSkinMask_PixelColor_DilateP, NRows_Matrix, IsSkinMask);
      break;
    }
  } else {
    /* Use function corresponding to closest SE radius */
    switch (functionWidthToUse) {
     case 4:
      /* Disk-shaped structuring element with radius of 4 pixels     */
      /* Packed binary image */
      /* Local function. */
      /* Type uint32. */
      /* end local function */
      /* ============================================================================================= */
      /* ErodeAndDilate_SEDisk4    Erode and dilate with disk-shaped structuring element of radius 4. */
      /* Inline function */
      /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  eroded packed logical image */
      /*  packed logical image */
      /*  structuring element */
      /*  flag for packed image */
      /*  number of rows in unpacked image */
      imerode(IsSkinMask_PixelColorPacked, NRows_Matrix,
              d_IsSkinMask_PixelColor_ErodePa);

      /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  dilated packed logical image */
      /*  packed logical image */
      /*  structuring element */
      /*  flag for packed image */
      imdilate(d_IsSkinMask_PixelColor_ErodePa, IsSkinMask_PixelColorPacked);
      i = c_IsSkinMask_PixelColor_DilateP->size[0] *
        c_IsSkinMask_PixelColor_DilateP->size[1];
      c_IsSkinMask_PixelColor_DilateP->size[0] =
        IsSkinMask_PixelColorPacked->size[0];
      c_IsSkinMask_PixelColor_DilateP->size[1] =
        IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_uint32_T(c_IsSkinMask_PixelColor_DilateP, i);
      loop_ub = IsSkinMask_PixelColorPacked->size[0] *
        IsSkinMask_PixelColorPacked->size[1];
      for (i = 0; i < loop_ub; i++) {
        c_IsSkinMask_PixelColor_DilateP->data[i] =
          IsSkinMask_PixelColorPacked->data[i];
      }

      /* Disk-shaped structuring element with radius of 6 pixels     */
      /* %%%%% --- Unpack %%%%%%    */
      /* Unpack packed binary image */
      /* M x N matrix; type logical. */
      bwunpack(c_IsSkinMask_PixelColor_DilateP, NRows_Matrix, IsSkinMask);
      break;

     case 6:
      /* Packed binary image */
      /* Local function. */
      /* Type uint32. */
      /* end local function */
      /* ============================================================================================= */
      /* ErodeAndDilate_SEDisk6    Erode and dilate with disk-shaped structuring element of radius 6. */
      /* Inline function */
      /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  eroded packed logical image */
      /*  packed logical image */
      /*  structuring element */
      /*  flag for packed image */
      /*  number of rows in unpacked image */
      b_imerode(IsSkinMask_PixelColorPacked, NRows_Matrix,
                c_IsSkinMask_PixelColor_ErodePa);

      /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  dilated packed logical image */
      /*  packed logical image */
      /*  structuring element */
      /*  flag for packed image */
      b_imdilate(c_IsSkinMask_PixelColor_ErodePa,
                 d_IsSkinMask_PixelColor_DilateP);
      i = c_IsSkinMask_PixelColor_DilateP->size[0] *
        c_IsSkinMask_PixelColor_DilateP->size[1];
      c_IsSkinMask_PixelColor_DilateP->size[0] =
        d_IsSkinMask_PixelColor_DilateP->size[0];
      c_IsSkinMask_PixelColor_DilateP->size[1] =
        d_IsSkinMask_PixelColor_DilateP->size[1];
      emxEnsureCapacity_uint32_T(c_IsSkinMask_PixelColor_DilateP, i);
      loop_ub = d_IsSkinMask_PixelColor_DilateP->size[0] *
        d_IsSkinMask_PixelColor_DilateP->size[1];
      for (i = 0; i < loop_ub; i++) {
        c_IsSkinMask_PixelColor_DilateP->data[i] =
          d_IsSkinMask_PixelColor_DilateP->data[i];
      }

      /* Disk-shaped structuring element with radius of 10 pixels     */
      /* %%%%% --- Unpack %%%%%%    */
      /* Unpack packed binary image */
      /* M x N matrix; type logical. */
      bwunpack(c_IsSkinMask_PixelColor_DilateP, NRows_Matrix, IsSkinMask);
      break;

     case 10:
      /* Packed binary image */
      /* Local function. */
      /* Type uint32. */
      /* end local function */
      /* ============================================================================================= */
      /* ErodeAndDilate_SEDisk10    Erode and dilate with disk-shaped structuring element of radius 10. */
      /* Inline function */
      /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  eroded packed logical image */
      /*  packed logical image */
      /*  structuring element */
      /*  flag for packed image */
      /*  number of rows in unpacked image */
      c_imerode(IsSkinMask_PixelColorPacked, NRows_Matrix,
                c_IsSkinMask_PixelColor_ErodePa);

      /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  dilated packed logical image */
      /*  packed logical image */
      /*  structuring element */
      /*  flag for packed image */
      c_imdilate(c_IsSkinMask_PixelColor_ErodePa,
                 d_IsSkinMask_PixelColor_DilateP);
      i = c_IsSkinMask_PixelColor_DilateP->size[0] *
        c_IsSkinMask_PixelColor_DilateP->size[1];
      c_IsSkinMask_PixelColor_DilateP->size[0] =
        d_IsSkinMask_PixelColor_DilateP->size[0];
      c_IsSkinMask_PixelColor_DilateP->size[1] =
        d_IsSkinMask_PixelColor_DilateP->size[1];
      emxEnsureCapacity_uint32_T(c_IsSkinMask_PixelColor_DilateP, i);
      loop_ub = d_IsSkinMask_PixelColor_DilateP->size[0] *
        d_IsSkinMask_PixelColor_DilateP->size[1];
      for (i = 0; i < loop_ub; i++) {
        c_IsSkinMask_PixelColor_DilateP->data[i] =
          d_IsSkinMask_PixelColor_DilateP->data[i];
      }

      /* Disk-shaped structuring element with radius of 14 pixels     */
      /* %%%%% --- Unpack %%%%%%    */
      /* Unpack packed binary image */
      /* M x N matrix; type logical. */
      bwunpack(c_IsSkinMask_PixelColor_DilateP, NRows_Matrix, IsSkinMask);
      break;

     case 14:
      /* Packed binary image */
      /* Local function. */
      /* Type uint32. */
      /* end local function */
      /* ============================================================================================= */
      /* ErodeAndDilate_SEDisk14    Erode and dilate with disk-shaped structuring element of radius 14. */
      /* Inline function */
      /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  eroded packed logical image */
      /*  packed logical image */
      /*  structuring element */
      /*  flag for packed image */
      /*  number of rows in unpacked image */
      d_imerode(IsSkinMask_PixelColorPacked, NRows_Matrix,
                c_IsSkinMask_PixelColor_ErodePa);

      /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
      /* Type uint32. */
      /*  dilated packed logical image */
      /*  packed logical image */
      /*  structuring element */
      /*  flag for packed image */
      d_imdilate(c_IsSkinMask_PixelColor_ErodePa,
                 d_IsSkinMask_PixelColor_DilateP);

      /* end local function */
      i = c_IsSkinMask_PixelColor_DilateP->size[0] *
        c_IsSkinMask_PixelColor_DilateP->size[1];
      c_IsSkinMask_PixelColor_DilateP->size[0] =
        d_IsSkinMask_PixelColor_DilateP->size[0];
      c_IsSkinMask_PixelColor_DilateP->size[1] =
        d_IsSkinMask_PixelColor_DilateP->size[1];
      emxEnsureCapacity_uint32_T(c_IsSkinMask_PixelColor_DilateP, i);
      loop_ub = d_IsSkinMask_PixelColor_DilateP->size[0] *
        d_IsSkinMask_PixelColor_DilateP->size[1];
      for (i = 0; i < loop_ub; i++) {
        c_IsSkinMask_PixelColor_DilateP->data[i] =
          d_IsSkinMask_PixelColor_DilateP->data[i];
      }

      /* (Required for code generation)     */
      /* %%%%% --- Unpack %%%%%%    */
      /* Unpack packed binary image */
      /* M x N matrix; type logical. */
      bwunpack(c_IsSkinMask_PixelColor_DilateP, NRows_Matrix, IsSkinMask);
      break;
    }
  }

  emxFree_uint32_T(&r);
  emxFree_uint32_T(&B);
  emxFree_uint32_T(&d_IsSkinMask_PixelColor_ErodePa);
  emxFree_uint32_T(&c_IsSkinMask_PixelColor_ErodePa);
  emxFree_uint32_T(&d_IsSkinMask_PixelColor_DilateP);
  emxFree_uint32_T(&c_IsSkinMask_PixelColor_DilateP);
  emxFree_uint32_T(&IsSkinMask_PixelColorPacked);

  /* %%%%% Count the number of pixels classified as skin (true) %%%%%% */
  /* If returning a count of the pixels classified as true is enabled */
  if (CountTrueTF) {
    TrueCount_size[0] = 1;
    TrueCount_data[0] = 0U;
    for (b_i = 0; b_i < NElements_Matrix; b_i++) {
      if (IsSkinMask->data[b_i]) {
        loop_ub = TrueCount_size[0];
        for (i = 0; i < loop_ub; i++) {
          TrueCount_data[i]++;
        }
      }
    }
  } else {
    TrueCount_size[0] = 0;
  }

  /* end function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (SkinSegmentMask_Ops_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Modify function files for performance %%%%%% */
  /*  */
  /* Before running code generation, input validation was removed from the files for the  */
  /* following functions: */
  /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\bwpack.m */
  /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\bwunpack.m */
  /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\+images\+internal\+coder\morphop.m  */
  /*  */
  /* Specifically, in these files, the following validation functions were commented out: */
  /*  - narginchk */
  /*  - validateattributes */
  /*  */
  /* Note: Seperate files for these functions with these changes could not be made because code   */
  /* generation for these functions expects specific file names. Hence, after code generation, the   */
  /* input validation was added back to the files. */
  /* Note: as these files are located in 'Program Files', admin access is required to edit them. */
  /*  */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /*                                              Example Code                 Upp. Bounds  Var. Size (T/F)  Type */
  /* RUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8 */
  /* GUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8 */
  /* BUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8 */
  /* YSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single                       */
  /* CbSingleCode                  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single */
  /* CrSingleCode                  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single */
  /* HSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single                                  */
  /* SSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single  */
  /* IsSkinMask_RangeCode          = coder.typeof( false(500, 500),             [inf, inf],  [1, 1] );        %logical            */
  /*                   */
  /*                      */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /* NRows_MatrixCode               = int32(0); */
  /* NCols_MatrixCode               = int32(0); */
  /* CountTrueTFCode                = false; */
  /* TailoredThresholdsTFCode       = false; */
  /* ReturnYTFCode                  = false; */
  /* ReturnCbCrTFCode               = false; */
  /* ReturnHSTFCode                 = false; */
  /* TailoredThresholdsSevereTFCode = false; */
  /* MorphCloseSevereTFCode         = false; */
  /* XOffsetCode                    = int32(0); */
  /* YOffsetCode                    = int32(0); */
  /*  */
  /* Struct with fixed-size fields */
  /* Note: the order and names of fields are compile-time constants. */
  /*  */
  /* SkinSegmentArgsCode = ...                                                                                               */
  /*     struct( ... */
  /*         'SkinColorSamples_NThresholdPassedTF', false, ... */
  /*         'YCbCrThresholdsGeneric', zeros(1, 7, 'single'), ... */
  /*         'HSThresholdsGeneric', zeros(1, 2, 'single'), ... */
  /*         'YCbCrThresholdsTailored', zeros(1, 8, 'single'), ... */
  /*         'YCbCrThresholdsTailored_Sev', zeros(1, 8, 'single'), ... */
  /*         'HSThresholdsTailored', zeros(1, 3, 'single'), ... */
  /*         'HSThresholdsTailored_Sev', zeros(1, 3, 'single'), ... */
  /*         'RangeSEWidth', int16(0), ... */
  /*         'RangeThreshold', uint8(0), ... */
  /*         'MorphCloseSEMediumWidth_Tuned', int16(0), ... */
  /*         'MorphCloseSELargeWidth_Tuned', int16(0) ...    */
  /*     );                                                                    */
  /*  */
  /*  */
  /* %%%%% Set configurations to increase performance %%%%%% */
  /*  */
  /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
  /* "Optimization Strategies" */
  /*  */
  /* cfg = coder.config('mex'); */
  /* cfg.GlobalDataSyncMethod = 'NoSync'; */
  /* cfg.ConstantInputs = 'IgnoreValues'; */
  /* cfg.ExtrinsicCalls = false;  */
  /* cfg.SaturateOnIntegerOverflow = false; */
  /* cfg.IntegrityChecks = false; */
  /* cfg.ResponsivenessChecks = false; */
  /*  */
  /*  */
  /* %%%%% Specify flags to minGW compiler to optimize execution speed %%%%%% */
  /*  */
  /* For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html */
  /*  */
  /* The flags are specified as part of the code-generation configuration object. A custom function, */
  /* setbuildargs, is used to specify these flags. For details on the function implementation, see the  */
  /* function file, which is located within folder FacePulseRate. This custom function is based upon  */
  /* Matlab guidance found in */
  /* https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function */
  /*  */
  /* setbuildargs will be evaluated from text within the code-generation object, so it is converted to  */
  /* a character vector prior to execution of the codegen command. */
  /*  */
  /* %%%%% --- Specify the flags as arguments to function setbuildargs %%%%%% */
  /*  */
  /* Argument buildInfo: this variable is assign by the caller (the codegen command executed  */
  /* below) and is not present in the base workspace. */
  /*  */
  /* Second argument: specify a cell array of compiler-specific flags, where each flag is a  */
  /* character vector. As function setbuildargs will be evaluated from text, use double ' quotes for  */
  /* each character vector to maintain the charater vector, */
  /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
  /*  */
  /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})'; */
  /*  */
  /* Assign to code-generation configuration object */
  /* cfg.PostCodeGenCommand = setbuildargsAsText; */
  /*  */
  /*  */
  /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
  /*  */
  /* codegen SkinSegmentMask_Ops.m -report -config cfg -args {RUint8Code, GUint8Code, BUint8Code, YSingleCode, CbSingleCode, CrSingleCode, HSingleCode, SSingleCode, IsSkinMask_RangeCode, NRows_MatrixCode, NCols_MatrixCode, CountTrueTFCode, TailoredThresholdsTFCode, ReturnYTFCode, ReturnCbCrTFCode, ReturnHSTFCode, TailoredThresholdsSevereTFCode, MorphCloseSevereTFCode, XOffsetCode, YOffsetCode, SkinSegmentArgsCode} */
  /*               */
  /* } */
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

emlrtCTX emlrtGetRootTLSGlobal(void)
{
  return emlrtRootTLSGlobal;
}

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, const emlrtConstCTX aTLS,
  void *aData)
{
  omp_set_lock(&emlrtLockGlobal);
  emlrtCallLockeeFunction(aLockee, aTLS, aData);
  omp_unset_lock(&emlrtLockGlobal);
}

/* End of code generation (SkinSegmentMask_Ops.c) */
