/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinSegmentMask_Threshold_Colors.c
 *
 * Code generation for function 'SkinSegmentMask_Threshold_Colors'
 *
 */

/* Include files */
#include "SkinSegmentMask_Threshold_Colors.h"
#include "SkinSegmentMask_Ops.h"
#include "SkinSegmentMask_Ops_emxutil.h"
#include "mwmathutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void c_SkinSegmentMask_Threshold_Col(const emxArray_uint8_T *RBounded_Uint8,
  const emxArray_uint8_T *GBounded_Uint8, const emxArray_uint8_T *BBounded_Uint8,
  emxArray_real32_T *YBounded_Single, emxArray_real32_T *CbBounded_Single,
  emxArray_real32_T *CrBounded_Single, emxArray_real32_T *HBounded_Single,
  emxArray_real32_T *SBounded_Single, int32_T NRows_Matrix, int32_T NCols_Matrix,
  int32_T NElements_Matrix, boolean_T TailoredThresholdsTF, boolean_T
  DontUseTailoredTF, const real32_T YCbCrThresholds_Generic[7], const real32_T
  YCbCrThresholds_Tailored[8], boolean_T ReturnYTF, boolean_T ReturnCbCrTF,
  boolean_T ReturnHSTF, const real32_T HSThresholds_Generic[2], const real32_T
  HSThresholds_Tailored[3], boolean_T UseLinIdxTF, int32_T XOffset, int32_T
  YOffset, emxArray_boolean_T *IsSkinMask)
{
  real32_T YMin;
  real32_T YMax;
  real32_T CbMin;
  real32_T CbMax;
  real32_T CrMin;
  real32_T CrMax;
  real32_T CbCrRatioMin;
  real32_T CbCrRatioMax;
  real32_T HMax;
  real32_T SMin;
  real32_T SMax;
  int32_T i;
  int32_T b_i;
  uint16_T OutIdxX;
  boolean_T IsSkinMask_ith;
  uint16_T OutIdxY;
  real32_T CbCrRatio_ith;
  int32_T i1;
  int32_T j;
  int32_T c1;
  int32_T YAdjust;
  int32_T XAdjust;
  int32_T c2;
  int32_T c3;
  real32_T cb;
  int32_T v;
  real32_T cr;
  int32_T l;
  real32_T out;
  real32_T s;

  /* SkinSegmentMask_Threshold_Colors   Return a skin-segmentation mask by comparing channels of the     */
  /*                                    YCbCr and HSV colorspaces of the input image to specified  */
  /*                                    thresholds.                                                                                */
  /*  */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by function SkinSegmentMask_Threshold. */
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
  /*     Return a logical matrix (IsSkinMask), or skin-segmentation mask, by comparing the YCbCr and HS   */
  /*     channels of the input image to the YCbCr and HS thresholds, respectively. If a given pixel of   */
  /*     the input image passes each of the YCbCr thresholds and the H and S thresholds, it is    */
  /*     classified as true, or as skin. Additionally, return some of the variables assigned in the  */
  /*     current function for reuse by other functions. For a detailed description of the assumptions  */
  /*     of using these thresholds for skin segmentation, see function SkinSegmentMask_Ops. */
  /*  */
  /*     First, the RGB colorspace variables of the input image (RBounded_Single, GBounded_Single,  */
  /*     BBounded_Single) are converted to the YCbCr colorspace and the H and S channels of the HSV  */
  /*     colorspace. Second, each pixel of the converted colorspaces is compared to the tresholds. For  */
  /*     the YCbCr colorspaces, either the generic or tailored versions of the thresholds are used. The  */
  /*     tailored versions are used when TailoredThresholdsTF == true and DontUseTailoredTF == false. */
  /*     The generic versions are used otherwise. The H threshold is used when, as with the tailored  */
  /*     YCbCr thresholds, TailoredThresholdsTF == true and DontUseTailoredTF == false. */
  /*  */
  /*     The colorspace variables of the input that are assigned in the current function can be  */
  /*     returned for reuse by other functions. When ReturnYTF == true, the Y channel of the YCbCr    */
  /*     colorspace is returned. When ReturnCbCrTF == true, the Cb and Cr channels of the YCbCr   */
  /*     colorspace are also returned. When ReturnHSTF == true, the H and S channels of HSV colorspace   */
  /*     are returned. ReturnYTF, ReturnCbCrTF, and ReturnHSTF are arguments to function  */
  /*     SkinSegmentMask.  */
  /*  */
  /*     For efficiency, calling functions are implemented only to request colorspace variables that  */
  /*     they can reuse. This is because assignment of a colorspace variable requires additional  */
  /*     assignement beyond the operations conducted in the current function. Specifically, in the */
  /*     current function, conversion to colorspaces occurs pixel-by-pixel; however, to return the */
  /*     colorspace variable, a separate variable needs to be assigned to store all of the pixels of  */
  /*     the input image. */
  /*  */
  /*     In the code blocks for the compiled version of the function, some if-else branches may not be */
  /*     used because the particular conditions may not be specified by any calling functions within  */
  /*     FacePulseRate. These if-else branches are still provided for robustness. */
  /*  */
  /*     Operations are divided according to whether colorspace conversions need to be made or whether */
  /*     variables in the necessary colorspaces were provided as input. */
  /*  */
  /*     -- Colorspace Conversions -- */
  /*  */
  /*     The RGB to YCbCr conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab  */
  /*     algorithm is derived from Poynton (1996, p. 175 - 176).  */
  /*  */
  /*     RGB to HS conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
  /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
  /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
  /*     code generation. As of Matlab version 2020a, the file location is  */
  /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
  /*  */
  /*     -- Optimizations -- */
  /*  */
  /*     The current function is highly optimized because of the rather time-consuming tasks. To view */
  /*     more straightforward code, see the bottom of the function for the vectorized (and less */
  /*     efficient) version of the code -- although vectorized code is less efficient for the compiled */
  /*     version of the function, it is more efficient when running Matlab code. To achieve higher */
  /*     efficiency, all operations are placed within one loop to reduce the number of times vectors */
  /*     are indexed. One characteristic of the thresholds used is that a pixel is classified as skin */
  /*     (true) only if each of the thresholds returns true. The code is optimized to take advantage of */
  /*     this by skipping any conversions and comparisons for a given pixel once any threshold returns  */
  /*     false. */
  /*  */
  /*         RGB to YCbCr Algorithm Optimation  */
  /*   */
  /*     (1) Code from function rgb2ycbcr only relevent to uint8 input was extracted (although the */
  /*         input to this function is type single, it was converted to type single from uint8 before */
  /*         entry to the function). */
  /*     (2) Operations are conducted in type single, whereas, in function rgb2ycbcr, function   */
  /*         imlincomb is used, which conducts operations in type double. */
  /*     (3) No conversion is made back to type uint8. This avoids the resourse-intensive conversion  */
  /*         from floating-point to integer. As all the functions in FacePulseRate that use this       */
  /*         function use YCbCr in type single, no conversion to integer is needed.     */
  /*     (4) R, G, and B are handled as separate variables rather than as a concatenated 3D variable. */
  /*         This reduces time otherwise taken by repeatedly indexing into a concatenated 3D variable.    */
  /*     (5) The Y, Cb, and Cr pages are not concatenated into a 3D output variable. By not    */
  /*         concatenating, time is also saved in functions (outside of the current function) that use   */
  /*         the output because nearly all functions that use the output use the three pages   */
  /*         separately, so they do not have to separate the pages or index into the concatenated  */
  /*         output. */
  /*  */
  /*         C-Compiled Code */
  /*  */
  /*     (1) C-compiled code may conduct operations faster than Matlab code when using type single */
  /*         (see https://www.mathworks.com/company/newsletters/articles/accelerating-matlab-algorithms-and-applications.html).        */
  /*     (2) It has been observed through testing that conversion from type uint8 to type single, which  */
  /*         is necessary before the RGB-to-YCbCr conversion) is faster when run in Matlab code than */
  /*         C-compiled code; therefore, this conversion is done in Matlab code and passed as an  */
  /*         argument to the current function. */
  /*  */
  /*         Use in External Functions */
  /*  */
  /*     (1) This function returns the individual color channels rather than the concatenated image.   */
  /*         Because function FacePulseRate assesses color channels individually in its operations, it  */
  /*         is faster if it doesn't have to separate the color channels.  */
  /*     (2) All functions in FacePulseRate that call this function use YCbCr in type single. As this  */
  /*         function returns type single, this avoids many functions converting from type uint8 to  */
  /*         type single. */
  /*      */
  /*  */
  /*     References */
  /*     ---------- */
  /*  */
  /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
  /*  */
  /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
  /*     19. */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
  /*     the Responsible AI License (RAIL). */
  /* %%%%% Code-generation settings %%%%%% */
  /* Inline function */
  /* %%%%% Operations if all color channels used in skin segmentation are provided as input %%%%%% */
  if ((YBounded_Single->size[0] != 0) && (YBounded_Single->size[1] != 0) &&
      ((CbBounded_Single->size[0] != 0) && (CbBounded_Single->size[1] != 0)) &&
      ((CrBounded_Single->size[0] != 0) && (CrBounded_Single->size[1] != 0)) &&
      ((HBounded_Single->size[0] != 0) && (HBounded_Single->size[1] != 0)) &&
      ((SBounded_Single->size[0] != 0) && (SBounded_Single->size[1] != 0))) {
    /* Skin-segmentation mask based upon color thresholds */
    /* M x N matrix; type logical. */
    /* Note: SkinSegmentMask_Threshold_Colors_NoConvert is a custom function located within folder */
    /* 'FacePulseRate'. */
    /* SkinSegmentMask_Threshold_Colors_NoConvert   Return a skin-segmentation mask by comparing channels     */
    /*                                              of the YCbCr and HSV colorspaces of the input image   */
    /*                                              to specified thresholds. The colorspaces used are */
    /*                                              provided as input. */
    /*  */
    /*     Helper function to function FacePulseRate. */
    /*     Within function FacePulseRate, called by function SkinSegmentMask_Threshold. */
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
    /*     Return a skin-segmentation mask by comparing channels of the YCbCr and HSV colorspaces of the  */
    /*     input image to specified thresholds. The colorspaces used are provided as input. */
    /*  */
    /*     This function performs the same segmentation operations as function  */
    /*     SkinSegmentMask_Threshold_Colors_Convert but does not conduct colorspace conversion as the  */
    /*     necessary colorspaces are provided as input. In contrast, function  */
    /*     SkinSegmentMask_Threshold_Colors_Convert converts the necessary colorspaces from the RGB */
    /*     colorspace. */
    /*  */
    /*     For a more detailed description of the operations performed here, see function */
    /*     SkinSegmentMask_Threshold_Colors. */
    /*  */
    /*  */
    /*     Copyright */
    /*     --------- */
    /*  */
    /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
    /*     the Responsible AI License (RAIL). */
    /* %%%%% Code-generation settings %%%%%% */
    /* Inline function */
    /* %%%%% Prepare for operations %%%%%% */
    /* If tailored thresholds not specified or if tailored thresholds specified but flag */
    /* DontUseTailoredTF == true. */
    if ((!TailoredThresholdsTF) || DontUseTailoredTF) {
      /* Values assigned by function SkinSegment_ConfigSetup.   */
      /* Note: these should be in type single for fastest evaluation. */
      /* Remove thresholds from struct for efficiency: */
      YMin = YCbCrThresholds_Generic[0];
      CbMin = YCbCrThresholds_Generic[1];
      CbMax = YCbCrThresholds_Generic[2];
      CrMin = YCbCrThresholds_Generic[3];
      CrMax = YCbCrThresholds_Generic[4];
      CbCrRatioMin = YCbCrThresholds_Generic[5];
      CbCrRatioMax = YCbCrThresholds_Generic[6];
      HMax = HSThresholds_Generic[0];
      SMin = HSThresholds_Generic[1];

      /* Assign for code generation purposes */
      /* These values are not used in this condition. */
      YMax = rtNaNF;
      SMax = rtNaNF;
    } else {
      /* Values assigned by function SkinSegment_SetThresholds. */
      /* Note: these should be in type single for fastest evaluation.  */
      /* Remove thresholds from struct for efficiency */
      YMin = YCbCrThresholds_Tailored[0];
      YMax = YCbCrThresholds_Tailored[1];
      CbMin = YCbCrThresholds_Tailored[2];
      CbMax = YCbCrThresholds_Tailored[3];
      CrMin = YCbCrThresholds_Tailored[4];
      CrMax = YCbCrThresholds_Tailored[5];
      CbCrRatioMin = YCbCrThresholds_Tailored[6];
      CbCrRatioMax = YCbCrThresholds_Tailored[7];
      HMax = HSThresholds_Tailored[0];
      SMin = HSThresholds_Tailored[1];
      SMax = HSThresholds_Tailored[2];
    }

    /* Preallocate skin-segmentation mask */
    i = IsSkinMask->size[0] * IsSkinMask->size[1];
    IsSkinMask->size[0] = NRows_Matrix;
    IsSkinMask->size[1] = NCols_Matrix;
    emxEnsureCapacity_boolean_T(IsSkinMask, i);

    /* %%%%%% Compiled version of function %%%%%%  */
    /* Loop-based operations increase efficiency of the compiled version of the function but decrease the  */
    /* efficiency of Matlab code, so conduct loop-based operations only for the compiled version of the  */
    /* function. */
    /* code generation running */
    /* %%%%% --- Do not use tailored thresholds %%%%%% */
    if ((!TailoredThresholdsTF) || DontUseTailoredTF) {
      /* Index using a linear index */
      if (UseLinIdxTF) {
        for (b_i = 0; b_i < NElements_Matrix; b_i++) {
          /* Extract the ith y, cb, and cr values */
          /* Scalars; type single. */
          /* Classify pixels within all thresholds as skin (true)        */
          if ((YBounded_Single->data[b_i] > YMin) && (CbBounded_Single->data[b_i]
               > CbMin) && (CbBounded_Single->data[b_i] < CbMax) &&
              (CrBounded_Single->data[b_i] > CrMin) && (CrBounded_Single->
               data[b_i] < CrMax)) {
            IsSkinMask_ith = true;
          } else {
            IsSkinMask_ith = false;
          }

          if (IsSkinMask_ith) {
            /* Extract the ith h and s values */
            /* Scalars; type single. */
            /* Classify pixels within all thresholds as skin (true)  */
            if ((HBounded_Single->data[b_i] < HMax) && (SBounded_Single->
                 data[b_i] > SMin)) {
              IsSkinMask_ith = true;
            } else {
              IsSkinMask_ith = false;
            }
          }

          if (IsSkinMask_ith) {
            /* Calculate Cb-to-Cr ratio */
            /* Type single to permit division to return fractions. */
            CbCrRatio_ith = CbBounded_Single->data[b_i] / CrBounded_Single->
              data[b_i];
            if ((!(CbCrRatio_ith > CbCrRatioMin)) || (!(CbCrRatio_ith <
                  CbCrRatioMax))) {
              IsSkinMask_ith = false;
            }
          }

          IsSkinMask->data[b_i] = IsSkinMask_ith;
        }

        /* Index using subscript indices */
      } else {
        /* Number of rows of the input matrices */
        /* Used for conversion to linear index. */
        /* Scalar; type int32. */
        /* Initialize column index for skin-segmentation mask output                                    */
        OutIdxX = 0U;

        /* Loop across columns */
        i = (XOffset + NCols_Matrix) - 1;
        for (b_i = XOffset; b_i <= i; b_i++) {
          /* Advance output index */
          OutIdxX++;

          /* Initialize row index for skin-segmentation mask output */
          OutIdxY = 0U;

          /* Loop across rows */
          i1 = (YOffset + NRows_Matrix) - 1;
          for (j = YOffset; j <= i1; j++) {
            /* Advance output index */
            OutIdxY++;

            /* Linear index corresponding to the full matrix */
            /* Convert from subscript indices to a linear index for more efficient indexing */
            /* Note: In compiled C code, the faster indexing outweighs the cost of this  */
            /* conversion. */
            c1 = (j + (b_i - 1) * YBounded_Single->size[0]) - 1;

            /* Extract the ith y, cb, and cr values */
            /* Scalars; type single. */
            /* Classify pixels within all thresholds as skin (true)        */
            if ((YBounded_Single->data[c1] > YMin) && (CbBounded_Single->data[c1]
                 > CbMin) && (CbBounded_Single->data[c1] < CbMax) &&
                (CrBounded_Single->data[c1] > CrMin) && (CrBounded_Single->
                 data[c1] < CrMax)) {
              IsSkinMask_ith = true;
            } else {
              IsSkinMask_ith = false;
            }

            if (IsSkinMask_ith) {
              /* Extract the ith h and s values */
              /* Scalars; type single. */
              /* Classify pixels within all thresholds as skin (true)  */
              if ((HBounded_Single->data[b_i - 1] < HMax) &&
                  (SBounded_Single->data[b_i - 1] > SMin)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }
            }

            if (IsSkinMask_ith) {
              /* Calculate Cb-to-Cr ratio */
              /* Type single to permit division to return fractions. */
              CbCrRatio_ith = CbBounded_Single->data[c1] /
                CrBounded_Single->data[c1];
              if ((!(CbCrRatio_ith > CbCrRatioMin)) || (!(CbCrRatio_ith <
                    CbCrRatioMax))) {
                IsSkinMask_ith = false;
              }
            }

            IsSkinMask->data[(OutIdxY + IsSkinMask->size[0] * (OutIdxX - 1)) - 1]
              = IsSkinMask_ith;
          }
        }
      }

      /* %%%%% --- Use tailored thresholds %%%%%%      */
    } else {
      /* Index using a linear index */
      if (UseLinIdxTF) {
        for (b_i = 0; b_i < NElements_Matrix; b_i++) {
          /* Extract the ith h and s values */
          /* Scalars; type single. */
          /* Classify pixels within all thresholds as skin (true)  */
          if ((HBounded_Single->data[b_i] < HMax) && (SBounded_Single->data[b_i]
               > SMin) && (SBounded_Single->data[b_i] < SMax)) {
            IsSkinMask_ith = true;
          } else {
            IsSkinMask_ith = false;
          }

          IsSkinMask->data[b_i] = IsSkinMask_ith;
          if (IsSkinMask_ith) {
            /* Extract the ith y, cb, and cr values */
            /* Scalars; type single. */
            /* Note: for efficiency, the output replaces somes variable previously  */
            /* assigned.    */
            if ((YBounded_Single->data[b_i] > YMin) && (YBounded_Single->
                 data[b_i] < YMax) && (CbBounded_Single->data[b_i] > CbMin) &&
                (CbBounded_Single->data[b_i] < CbMax) && (CrBounded_Single->
                 data[b_i] > CrMin) && (CrBounded_Single->data[b_i] < CrMax)) {
              IsSkinMask_ith = true;
            } else {
              IsSkinMask_ith = false;
            }

            IsSkinMask->data[b_i] = IsSkinMask_ith;
            if (IsSkinMask_ith) {
              /* Calculate Cb-to-Cr ratio */
              /* Type single to permit division to return fractions. */
              /* Note: for efficiency, the output replaces a variable previously   */
              /* assigned. */
              CbCrRatio_ith = CbBounded_Single->data[b_i] /
                CrBounded_Single->data[b_i];
              if ((CbCrRatio_ith > CbCrRatioMin) && (CbCrRatio_ith <
                   CbCrRatioMax)) {
                IsSkinMask->data[b_i] = true;
              } else {
                IsSkinMask->data[b_i] = false;
              }
            }
          }
        }

        /* Index using subscript indices */
      } else {
        /* Number of rows of the input matrices */
        /* Used for conversion to linear index. */
        /* Scalar; type int32. */
        /* Initialize column index for skin-segmentation mask output                                    */
        OutIdxX = 0U;

        /* Loop across columns */
        i = (XOffset + NCols_Matrix) - 1;
        for (b_i = XOffset; b_i <= i; b_i++) {
          /* Advance output index */
          OutIdxX++;

          /* Initialize row index for skin-segmentation mask output                                    */
          OutIdxY = 0U;

          /* Loop across rows */
          i1 = (YOffset + NRows_Matrix) - 1;
          for (j = YOffset; j <= i1; j++) {
            /* Advance output index */
            OutIdxY++;

            /* Linear index corresponding to the full matrix */
            /* Convert from subscript indices to a linear index for more efficient indexing */
            /* Note: In compiled C code, the faster indexing outweighs the cost of this  */
            /* conversion. */
            c1 = (j + (b_i - 1) * YBounded_Single->size[0]) - 1;

            /* Extract the ith h and s values */
            /* Scalars; type single. */
            /* Classify pixels within all thresholds as skin (true)  */
            if ((HBounded_Single->data[c1] < HMax) && (SBounded_Single->data[c1]
                 > SMin) && (SBounded_Single->data[c1] < SMax)) {
              IsSkinMask_ith = true;
            } else {
              IsSkinMask_ith = false;
            }

            c2 = OutIdxY - 1;
            c3 = OutIdxX - 1;
            IsSkinMask->data[c2 + IsSkinMask->size[0] * c3] = IsSkinMask_ith;
            if (IsSkinMask_ith) {
              /* Extract the ith y, cb, and cr values */
              /* Scalars; type single. */
              /* Note: for efficiency, the output replaces somes variable previously  */
              /* assigned.    */
              if ((YBounded_Single->data[c1] > YMin) && (YBounded_Single->
                   data[c1] < YMax) && (CbBounded_Single->data[c1] > CbMin) &&
                  (CbBounded_Single->data[c1] < CbMax) &&
                  (CrBounded_Single->data[c1] > CrMin) &&
                  (CrBounded_Single->data[c1] < CrMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              IsSkinMask->data[c2 + IsSkinMask->size[0] * c3] = IsSkinMask_ith;
              if (IsSkinMask_ith) {
                /* Calculate Cb-to-Cr ratio */
                /* Type single to permit division to return fractions. */
                /* Note: for efficiency, the output replaces a variable previously   */
                /* assigned. */
                CbCrRatio_ith = CbBounded_Single->data[c1] /
                  CrBounded_Single->data[c1];
                if ((CbCrRatio_ith > CbCrRatioMin) && (CbCrRatio_ith <
                     CbCrRatioMax)) {
                  IsSkinMask->data[c2 + IsSkinMask->size[0] * c3] = true;
                } else {
                  IsSkinMask->data[c2 + IsSkinMask->size[0] * c3] = false;
                }
              }
            }
          }
        }
      }
    }

    /* %%%%%% Non-compiled version of function %%%%%% */
    /* Use vectorized operations, which are more efficient for Matlab code. */
    /* end function */
    /* As these channels were provided as input, they are not provided back as output.        */
    YBounded_Single->size[0] = 0;
    YBounded_Single->size[1] = 0;
    CbBounded_Single->size[0] = 0;
    CbBounded_Single->size[1] = 0;
    CrBounded_Single->size[0] = 0;
    CrBounded_Single->size[1] = 0;
    HBounded_Single->size[0] = 0;
    HBounded_Single->size[1] = 0;
    SBounded_Single->size[0] = 0;
    SBounded_Single->size[1] = 0;

    /* %%%%% Operations if color channels used in skin segmentation need to be produced %%%%%% */
  } else {
    /* Skin-segmentation mask based upon color thresholds */
    /* M x N matrix; type logical. */
    /* Note: SkinSegmentMask_Threshold_Colors_Convert is a custom function located within folder */
    /* 'FacePulseRate'.      */
    /* SkinSegmentMask_Threshold_Colors_Convert   Return a skin-segmentation mask by comparing channels     */
    /*                                            of the YCbCr and HSV colorspaces of the input image to  */
    /*                                            specified thresholds. The colorspaces used will be */
    /*                                            produced by the current function. */
    /*  */
    /*     Helper function to function FacePulseRate. */
    /*     Within function FacePulseRate, called by function SkinSegmentMask_Threshold. */
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
    /*     Return a skin-segmentation mask by comparing channels of the YCbCr and HSV colorspaces of the  */
    /*     input image to specified thresholds. The colorspaces used will be produced by the current  */
    /*     function. */
    /*  */
    /*     This function performs the same segmentation operations as function  */
    /*     SkinSegmentMask_Threshold_Colors_NoConvert but also converts the RGB colorspace to the  */
    /*     necessary colorspaces. In contrast, function SkinSegmentMask_Threshold_Colors_NoConvert does */
    /*     not conduct colorspace conversions as the necessary colorspace variables are provided to it as */
    /*     input. */
    /*  */
    /*     For a more detailed description of the operations performed here, see function */
    /*     SkinSegmentMask_Threshold_Colors. */
    /*  */
    /*  */
    /*     Copyright */
    /*     --------- */
    /*  */
    /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
    /*     the Responsible AI License (RAIL). */
    /* %%%%% Code-generation settings %%%%%% */
    /* Inline function */
    /* Declare variables: */
    /*                                    Upp. Bounds    Var. Size (T/F) */
    /* %%%%% Operations %%%%%% */
    /* If tailored thresholds not specified or if tailored thresholds specified but flag */
    /* DontUseTailoredTF == true. */
    if ((!TailoredThresholdsTF) || DontUseTailoredTF) {
      /* Values assigned by function SkinSegment_ConfigSetup.   */
      /* Note: these should be in type single for fastest evaluation. */
      /* Remove thresholds from struct for efficiency: */
      YMin = YCbCrThresholds_Generic[0];
      CbMin = YCbCrThresholds_Generic[1];
      CbMax = YCbCrThresholds_Generic[2];
      CrMin = YCbCrThresholds_Generic[3];
      CrMax = YCbCrThresholds_Generic[4];
      CbCrRatioMin = YCbCrThresholds_Generic[5];
      CbCrRatioMax = YCbCrThresholds_Generic[6];
      HMax = HSThresholds_Generic[0];
      SMin = HSThresholds_Generic[1];

      /* Assign for code generation purposes */
      /* These values are not used in this condition. */
      YMax = rtNaNF;
      SMax = rtNaNF;
    } else {
      /* Values assigned by function SkinSegment_SetThresholds. */
      /* Note: these should be in type single for fastest evaluation.  */
      /* Remove thresholds from struct for efficiency: */
      YMin = YCbCrThresholds_Tailored[0];
      YMax = YCbCrThresholds_Tailored[1];
      CbMin = YCbCrThresholds_Tailored[2];
      CbMax = YCbCrThresholds_Tailored[3];
      CrMin = YCbCrThresholds_Tailored[4];
      CrMax = YCbCrThresholds_Tailored[5];
      CbCrRatioMin = YCbCrThresholds_Tailored[6];
      CbCrRatioMax = YCbCrThresholds_Tailored[7];
      HMax = HSThresholds_Tailored[0];
      SMin = HSThresholds_Tailored[1];
      SMax = HSThresholds_Tailored[2];
    }

    /* Preallocate skin-segmentation mask */
    i = IsSkinMask->size[0] * IsSkinMask->size[1];
    IsSkinMask->size[0] = NRows_Matrix;
    IsSkinMask->size[1] = NCols_Matrix;
    emxEnsureCapacity_boolean_T(IsSkinMask, i);

    /* %%%%%% --- Compiled version of function %%%%%%  */
    /* Loop-based operations increase efficiency of the compiled version of the function but decrease the  */
    /* efficiency of Matlab code, so conduct loop-based operations only for the compiled version of the  */
    /* function. */
    /* code generation running */
    /* %%%%% >>>>>> Assign alignment offsets for skin-segmentation mask %%%%%%  */
    /* %%%%% >>>>>> Do not return matrices from the the H and S channels of the HSV colorspace %%%%%%    */
    if (!ReturnHSTF) {
      HBounded_Single->size[0] = 0;
      HBounded_Single->size[1] = 0;
      SBounded_Single->size[0] = 0;
      SBounded_Single->size[1] = 0;

      /* Do not use tailored thresholds */
      if ((!TailoredThresholdsTF) || DontUseTailoredTF) {
        /* (1) Condition 1 */
        /*  - Use generic thresholds: generic YCbCr and HS thresholds. */
        /*  - Do not return H and S channel matrices. */
        /*  - Do not return matrices of the Y, Cb, or Cr channels.        */
        if ((!ReturnCbCrTF) && (!ReturnYTF)) {
          /* M x N matrices; type single. */
          YBounded_Single->size[0] = 0;
          YBounded_Single->size[1] = 0;
          CbBounded_Single->size[0] = 0;
          CbBounded_Single->size[1] = 0;
          CrBounded_Single->size[0] = 0;
          CrBounded_Single->size[1] = 0;

          /* Index using a linear index */
          if (UseLinIdxTF) {
            /* Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm */
            for (b_i = 0; b_i < NElements_Matrix; b_i++) {
              /* Extract and cast to type single the ith r, g, and b values */
              /* Scalars; type single. */
              /* Apply the RGB-to-YCbCr algorithm */
              /* Scalars; type single. */
              /* Note: for efficiency, the outputs replace the inputs. */
              /* Note: rgb2ycbcr_compute is a custom function located within folder */
              /* 'FacePulseRate'. */
              /*  y */
              /*  cb */
              /*  cr */
              /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
              /*  */
              /*     Description: */
              /*  */
              /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*  */
              /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
              /*     derived from Poynton (1996, p. 175 - 176). */
              /*  */
              /*     Note: */
              /*  */
              /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     References: */
              /*  */
              /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
              /* Inline function */
              /* ith Y channel element */
              /* Scalar; type single. */
              /* ith Cb channel element */
              /* Scalar; type single. */
              cb = ((-0.1482F * (real32_T)RBounded_Uint8->data[b_i] + -0.291F *
                     (real32_T)GBounded_Uint8->data[b_i]) + 0.4392F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* ith Cr channel element */
              /* Scalar; type single. */
              cr = ((0.4392F * (real32_T)RBounded_Uint8->data[b_i] + -0.3678F *
                     (real32_T)GBounded_Uint8->data[b_i]) + -0.0714F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* end function */
              /* Classify pixels within all thresholds as skin (true)        */
              if ((((0.2568F * (real32_T)RBounded_Uint8->data[b_i] + 0.5041F *
                     (real32_T)GBounded_Uint8->data[b_i]) + 0.0979F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 16.0F > YMin) && (cb > CbMin) &&
                  (cb < CbMax) && (cr > CrMin) && (cr < CrMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              if (IsSkinMask_ith) {
                /* Apply rgb-to-hs algorithm */
                /* Scalars; type single. */
                /* Note: rgb2h is a custom function located within folder  */
                /* 'FacePulseRate'.   */
                /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                /*           channels of the HSV colorspace.  */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*                     */
                /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                /*     colorspace.  */
                /*  */
                /*     Notes: */
                /*  */
                /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                /*     code generation. As of Matlab version 2020a, the file location is  */
                /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                /*  */
                /*     References: */
                /*  */
                /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                /*     19. */
                /* Inline function */
                /* Maximum channel value */
                if ((RBounded_Uint8->data[b_i] > GBounded_Uint8->data[b_i]) &&
                    (RBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])) {
                  v = RBounded_Uint8->data[b_i];
                } else if (GBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])
                {
                  v = GBounded_Uint8->data[b_i];
                } else {
                  v = BBounded_Uint8->data[b_i];
                }

                /* Minimum channel value */
                if ((RBounded_Uint8->data[b_i] < GBounded_Uint8->data[b_i]) &&
                    (RBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])) {
                  l = RBounded_Uint8->data[b_i];
                } else if (GBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])
                {
                  l = GBounded_Uint8->data[b_i];
                } else {
                  l = BBounded_Uint8->data[b_i];
                }

                /* Difference between maximum and minimum values */
                l = v - l;

                /* Determine value of hue channel (h) */
                if (l == 0) {
                  CbCrRatio_ith = 0.0F;
                } else if (BBounded_Uint8->data[b_i] == v) {
                  CbCrRatio_ith = ((real32_T)(RBounded_Uint8->data[b_i] -
                    GBounded_Uint8->data[b_i]) / (real32_T)l + 4.0F) / 6.0F;
                  if (CbCrRatio_ith < 0.0F) {
                    CbCrRatio_ith++;
                  }
                } else if (RBounded_Uint8->data[b_i] == v) {
                  CbCrRatio_ith = (real32_T)(GBounded_Uint8->data[b_i] -
                    BBounded_Uint8->data[b_i]) / (real32_T)l / 6.0F;
                  if (CbCrRatio_ith < 0.0F) {
                    CbCrRatio_ith++;
                  }
                } else if (GBounded_Uint8->data[b_i] == v) {
                  CbCrRatio_ith = ((real32_T)(BBounded_Uint8->data[b_i] -
                    RBounded_Uint8->data[b_i]) / (real32_T)l + 2.0F) / 6.0F;
                  if (CbCrRatio_ith < 0.0F) {
                    CbCrRatio_ith++;
                  }
                } else {
                  CbCrRatio_ith = 0.0F;
                }

                if (v == 0) {
                  s = 0.0F;
                } else if (l == 0) {
                  s = 0.0F;
                } else {
                  s = (real32_T)l / (real32_T)v;
                }

                /* end function */
                /* Classify pixels within all thresholds as skin (true)  */
                if ((CbCrRatio_ith < HMax) && (s > SMin)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }
              }

              if (IsSkinMask_ith) {
                /* Calculate Cb-to-Cr ratio */
                /* Type single to permit division to return fractions. */
                CbCrRatio_ith = cb / cr;
                if ((!(CbCrRatio_ith > CbCrRatioMin)) || (!(CbCrRatio_ith <
                      CbCrRatioMax))) {
                  IsSkinMask_ith = false;
                }
              }

              IsSkinMask->data[b_i] = IsSkinMask_ith;
            }

            /* Index using subscript indices */
          } else {
            i = (XOffset + NCols_Matrix) - 1;
            for (b_i = XOffset; b_i <= i; b_i++) {
              i1 = (YOffset + NRows_Matrix) - 1;
              for (j = YOffset; j <= i1; j++) {
                /* Indices for output matrices */
                /* Extract and cast to type single the ith r, g, and b values */
                /* Scalars; type single. */
                c1 = RBounded_Uint8->data[(j + RBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c2 = GBounded_Uint8->data[(j + GBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c3 = BBounded_Uint8->data[(j + BBounded_Uint8->size[0] * (b_i -
                  1)) - 1];

                /* Apply the RGB-to-YCbCr algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the outputs replace the inputs. */
                /* Note: rgb2ycbcr_compute is a custom function located within folder */
                /* 'FacePulseRate'. */
                /*  y */
                /*  cb */
                /*  cr */
                /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                /* ith Cb channel element */
                /* Scalar; type single. */
                cb = ((-0.1482F * (real32_T)c1 + -0.291F * (real32_T)c2) +
                      0.4392F * (real32_T)c3) + 128.0F;

                /* ith Cr channel element */
                /* Scalar; type single. */
                cr = ((0.4392F * (real32_T)c1 + -0.3678F * (real32_T)c2) +
                      -0.0714F * (real32_T)c3) + 128.0F;

                /* end function */
                /* Classify pixels within all thresholds as skin (true)        */
                if ((((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)c2) +
                      0.0979F * (real32_T)c3) + 16.0F > YMin) && (cb > CbMin) &&
                    (cb < CbMax) && (cr > CrMin) && (cr < CrMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                if (IsSkinMask_ith) {
                  /* Apply rgb-to-hs algorithm */
                  /* Scalars; type single. */
                  /* Note: rgb2h is a custom function located within folder  */
                  /* 'FacePulseRate'.   */
                  /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                  /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                  /*           channels of the HSV colorspace.  */
                  /*     */
                  /*     Helper function to function FacePulseRate.  */
                  /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                  /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                  /*  */
                  /*     Description: */
                  /*                     */
                  /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                  /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                  /*     colorspace.  */
                  /*  */
                  /*     Notes: */
                  /*  */
                  /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                  /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                  /*  */
                  /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                  /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                  /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                  /*     code generation. As of Matlab version 2020a, the file location is  */
                  /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                  /*  */
                  /*     References: */
                  /*  */
                  /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                  /*     19. */
                  /* Inline function */
                  /* Maximum channel value */
                  if ((c1 > c2) && (c1 > c3)) {
                    v = c1;
                  } else {
                    v = muIntScalarMax_sint32(c2, c3);
                  }

                  /* Minimum channel value */
                  if ((c1 < c2) && (c1 < c3)) {
                    l = c1;
                  } else {
                    l = muIntScalarMin_sint32(c2, c3);
                  }

                  /* Difference between maximum and minimum values */
                  l = v - l;

                  /* Determine value of hue channel (h) */
                  if (l == 0) {
                    CbCrRatio_ith = 0.0F;
                  } else if (c3 == v) {
                    CbCrRatio_ith = ((real32_T)(c1 - c2) / (real32_T)l + 4.0F) /
                      6.0F;
                    if (CbCrRatio_ith < 0.0F) {
                      CbCrRatio_ith++;
                    }
                  } else if (c1 == v) {
                    CbCrRatio_ith = (real32_T)(c2 - c3) / (real32_T)l / 6.0F;
                    if (CbCrRatio_ith < 0.0F) {
                      CbCrRatio_ith++;
                    }
                  } else if (c2 == v) {
                    CbCrRatio_ith = ((real32_T)(c3 - c1) / (real32_T)l + 2.0F) /
                      6.0F;
                    if (CbCrRatio_ith < 0.0F) {
                      CbCrRatio_ith++;
                    }
                  } else {
                    CbCrRatio_ith = 0.0F;
                  }

                  if (v == 0) {
                    s = 0.0F;
                  } else if (l == 0) {
                    s = 0.0F;
                  } else {
                    s = (real32_T)l / (real32_T)v;
                  }

                  /* end function */
                  /* Classify pixels within all thresholds as skin (true)  */
                  if ((CbCrRatio_ith < HMax) && (s > SMin)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }
                }

                if (IsSkinMask_ith) {
                  /* Calculate Cb-to-Cr ratio */
                  /* Type single to permit division to return fractions. */
                  CbCrRatio_ith = cb / cr;
                  if ((!(CbCrRatio_ith > CbCrRatioMin)) || (!(CbCrRatio_ith <
                        CbCrRatioMax))) {
                    IsSkinMask_ith = false;
                  }
                }

                IsSkinMask->data[(j - YOffset) + IsSkinMask->size[0] * (b_i -
                  XOffset)] = IsSkinMask_ith;
              }
            }
          }

          /* (2) Condition 2                 */
          /*  - Use generic thresholds: generic YCbCr and HS thresholds. */
          /*  - Do not return H and S channel matrices. */
          /*  - Return Y-channel matrix but not the Cb and Cr channel matrices.                 */
        } else if ((!ReturnCbCrTF) && ReturnYTF) {
          /* M x N matrices; type single. */
          i = YBounded_Single->size[0] * YBounded_Single->size[1];
          YBounded_Single->size[0] = NRows_Matrix;
          YBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(YBounded_Single, i);
          CbBounded_Single->size[0] = 0;
          CbBounded_Single->size[1] = 0;
          CrBounded_Single->size[0] = 0;
          CrBounded_Single->size[1] = 0;

          /* Index using a linear index */
          if (UseLinIdxTF) {
            /* Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm */
            for (b_i = 0; b_i < NElements_Matrix; b_i++) {
              /* Extract and cast to type single the ith r, g, and b values */
              /* Scalars; type single. */
              /* Apply the RGB-to-YCbCr algorithm */
              /* Scalars; type single. */
              /* Note: for efficiency, the outputs replace the inputs. */
              /* Local function.     */
              /* Note: rgb2ycbcr_compute is a custom function located within folder */
              /* 'FacePulseRate'. */
              /*  y */
              /*  cb */
              /*  cr */
              /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
              /*  */
              /*     Description: */
              /*  */
              /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*  */
              /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
              /*     derived from Poynton (1996, p. 175 - 176). */
              /*  */
              /*     Note: */
              /*  */
              /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     References: */
              /*  */
              /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
              /* Inline function */
              /* ith Y channel element */
              /* Scalar; type single. */
              CbCrRatio_ith = ((0.2568F * (real32_T)RBounded_Uint8->data[b_i] +
                                0.5041F * (real32_T)GBounded_Uint8->data[b_i]) +
                               0.0979F * (real32_T)BBounded_Uint8->data[b_i]) +
                16.0F;

              /* ith Cb channel element */
              /* Scalar; type single. */
              cb = ((-0.1482F * (real32_T)RBounded_Uint8->data[b_i] + -0.291F *
                     (real32_T)GBounded_Uint8->data[b_i]) + 0.4392F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* ith Cr channel element */
              /* Scalar; type single. */
              cr = ((0.4392F * (real32_T)RBounded_Uint8->data[b_i] + -0.3678F *
                     (real32_T)GBounded_Uint8->data[b_i]) + -0.0714F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* end function */
              /* Assign the ith y, value */
              YBounded_Single->data[b_i] = CbCrRatio_ith;

              /* Classify pixels within all thresholds as skin (true)        */
              if ((CbCrRatio_ith > YMin) && (cb > CbMin) && (cb < CbMax) && (cr >
                   CrMin) && (cr < CrMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              if (IsSkinMask_ith) {
                /* Apply rgb-to-hs algorithm */
                /* Scalars; type single. */
                /* Note: rgb2h is a custom function located within folder  */
                /* 'FacePulseRate'.   */
                /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                /*           channels of the HSV colorspace.  */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*                     */
                /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                /*     colorspace.  */
                /*  */
                /*     Notes: */
                /*  */
                /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                /*     code generation. As of Matlab version 2020a, the file location is  */
                /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                /*  */
                /*     References: */
                /*  */
                /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                /*     19. */
                /* Inline function */
                /* Maximum channel value */
                if ((RBounded_Uint8->data[b_i] > GBounded_Uint8->data[b_i]) &&
                    (RBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])) {
                  v = RBounded_Uint8->data[b_i];
                } else if (GBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])
                {
                  v = GBounded_Uint8->data[b_i];
                } else {
                  v = BBounded_Uint8->data[b_i];
                }

                /* Minimum channel value */
                if ((RBounded_Uint8->data[b_i] < GBounded_Uint8->data[b_i]) &&
                    (RBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])) {
                  l = RBounded_Uint8->data[b_i];
                } else if (GBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])
                {
                  l = GBounded_Uint8->data[b_i];
                } else {
                  l = BBounded_Uint8->data[b_i];
                }

                /* Difference between maximum and minimum values */
                l = v - l;

                /* Determine value of hue channel (h) */
                if (l == 0) {
                  CbCrRatio_ith = 0.0F;
                } else if (BBounded_Uint8->data[b_i] == v) {
                  CbCrRatio_ith = ((real32_T)(RBounded_Uint8->data[b_i] -
                    GBounded_Uint8->data[b_i]) / (real32_T)l + 4.0F) / 6.0F;
                  if (CbCrRatio_ith < 0.0F) {
                    CbCrRatio_ith++;
                  }
                } else if (RBounded_Uint8->data[b_i] == v) {
                  CbCrRatio_ith = (real32_T)(GBounded_Uint8->data[b_i] -
                    BBounded_Uint8->data[b_i]) / (real32_T)l / 6.0F;
                  if (CbCrRatio_ith < 0.0F) {
                    CbCrRatio_ith++;
                  }
                } else if (GBounded_Uint8->data[b_i] == v) {
                  CbCrRatio_ith = ((real32_T)(BBounded_Uint8->data[b_i] -
                    RBounded_Uint8->data[b_i]) / (real32_T)l + 2.0F) / 6.0F;
                  if (CbCrRatio_ith < 0.0F) {
                    CbCrRatio_ith++;
                  }
                } else {
                  CbCrRatio_ith = 0.0F;
                }

                if (v == 0) {
                  s = 0.0F;
                } else if (l == 0) {
                  s = 0.0F;
                } else {
                  s = (real32_T)l / (real32_T)v;
                }

                /* end function */
                /* Classify pixels within all thresholds as skin (true)  */
                if ((CbCrRatio_ith < HMax) && (s > SMin)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }
              }

              if (IsSkinMask_ith) {
                /* Calculate Cb-to-Cr ratio */
                /* Type single to permit division to return fractions. */
                CbCrRatio_ith = cb / cr;
                if ((!(CbCrRatio_ith > CbCrRatioMin)) || (!(CbCrRatio_ith <
                      CbCrRatioMax))) {
                  IsSkinMask_ith = false;
                }
              }

              IsSkinMask->data[b_i] = IsSkinMask_ith;
            }

            /* Index using subscript indices */
          } else {
            i = (XOffset + NCols_Matrix) - 1;
            for (b_i = XOffset; b_i <= i; b_i++) {
              i1 = (YOffset + NRows_Matrix) - 1;
              for (j = YOffset; j <= i1; j++) {
                /* Indices for output matrices */
                YAdjust = j - YOffset;
                XAdjust = b_i - XOffset;

                /* Extract and cast to type single the ith r, g, and b values */
                /* Scalars; type single. */
                c1 = RBounded_Uint8->data[(j + RBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c2 = GBounded_Uint8->data[(j + GBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c3 = BBounded_Uint8->data[(j + BBounded_Uint8->size[0] * (b_i -
                  1)) - 1];

                /* Apply the RGB-to-YCbCr algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the outputs replace the inputs. */
                /* Local function.     */
                /* Note: rgb2ycbcr_compute is a custom function located within folder */
                /* 'FacePulseRate'. */
                /*  y */
                /*  cb */
                /*  cr */
                /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                CbCrRatio_ith = ((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)
                                  c2) + 0.0979F * (real32_T)c3) + 16.0F;

                /* ith Cb channel element */
                /* Scalar; type single. */
                cb = ((-0.1482F * (real32_T)c1 + -0.291F * (real32_T)c2) +
                      0.4392F * (real32_T)c3) + 128.0F;

                /* ith Cr channel element */
                /* Scalar; type single. */
                cr = ((0.4392F * (real32_T)c1 + -0.3678F * (real32_T)c2) +
                      -0.0714F * (real32_T)c3) + 128.0F;

                /* end function */
                /* Assign the ith y, value */
                YBounded_Single->data[YAdjust + YBounded_Single->size[0] *
                  XAdjust] = CbCrRatio_ith;

                /* Classify pixels within all thresholds as skin (true)        */
                if ((CbCrRatio_ith > YMin) && (cb > CbMin) && (cb < CbMax) &&
                    (cr > CrMin) && (cr < CrMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                if (IsSkinMask_ith) {
                  /* Apply rgb-to-hs algorithm */
                  /* Scalars; type single. */
                  /* Note: rgb2h is a custom function located within folder  */
                  /* 'FacePulseRate'.   */
                  /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                  /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                  /*           channels of the HSV colorspace.  */
                  /*     */
                  /*     Helper function to function FacePulseRate.  */
                  /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                  /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                  /*  */
                  /*     Description: */
                  /*                     */
                  /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                  /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                  /*     colorspace.  */
                  /*  */
                  /*     Notes: */
                  /*  */
                  /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                  /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                  /*  */
                  /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                  /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                  /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                  /*     code generation. As of Matlab version 2020a, the file location is  */
                  /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                  /*  */
                  /*     References: */
                  /*  */
                  /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                  /*     19. */
                  /* Inline function */
                  /* Maximum channel value */
                  if ((c1 > c2) && (c1 > c3)) {
                    v = c1;
                  } else {
                    v = muIntScalarMax_sint32(c2, c3);
                  }

                  /* Minimum channel value */
                  if ((c1 < c2) && (c1 < c3)) {
                    l = c1;
                  } else {
                    l = muIntScalarMin_sint32(c2, c3);
                  }

                  /* Difference between maximum and minimum values */
                  l = v - l;

                  /* Determine value of hue channel (h) */
                  if (l == 0) {
                    CbCrRatio_ith = 0.0F;
                  } else if (c3 == v) {
                    CbCrRatio_ith = ((real32_T)(c1 - c2) / (real32_T)l + 4.0F) /
                      6.0F;
                    if (CbCrRatio_ith < 0.0F) {
                      CbCrRatio_ith++;
                    }
                  } else if (c1 == v) {
                    CbCrRatio_ith = (real32_T)(c2 - c3) / (real32_T)l / 6.0F;
                    if (CbCrRatio_ith < 0.0F) {
                      CbCrRatio_ith++;
                    }
                  } else if (c2 == v) {
                    CbCrRatio_ith = ((real32_T)(c3 - c1) / (real32_T)l + 2.0F) /
                      6.0F;
                    if (CbCrRatio_ith < 0.0F) {
                      CbCrRatio_ith++;
                    }
                  } else {
                    CbCrRatio_ith = 0.0F;
                  }

                  if (v == 0) {
                    s = 0.0F;
                  } else if (l == 0) {
                    s = 0.0F;
                  } else {
                    s = (real32_T)l / (real32_T)v;
                  }

                  /* end function */
                  /* Classify pixels within all thresholds as skin (true)  */
                  if ((CbCrRatio_ith < HMax) && (s > SMin)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }
                }

                if (IsSkinMask_ith) {
                  /* Calculate Cb-to-Cr ratio */
                  /* Type single to permit division to return fractions. */
                  CbCrRatio_ith = cb / cr;
                  if ((!(CbCrRatio_ith > CbCrRatioMin)) || (!(CbCrRatio_ith <
                        CbCrRatioMax))) {
                    IsSkinMask_ith = false;
                  }
                }

                IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                  IsSkinMask_ith;
              }
            }
          }

          /* (3) Condition 3                 */
          /*  - Use generic thresholds: generic YCbCr and HS thresholds. */
          /*  - Do not return H and S channel matrices. */
          /*  - Return matrices of the Y, Cb, and Cr channels.                 */
        } else {
          /* M x N matrices; type single. */
          i = YBounded_Single->size[0] * YBounded_Single->size[1];
          YBounded_Single->size[0] = NRows_Matrix;
          YBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(YBounded_Single, i);
          i = CbBounded_Single->size[0] * CbBounded_Single->size[1];
          CbBounded_Single->size[0] = NRows_Matrix;
          CbBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(CbBounded_Single, i);
          i = CrBounded_Single->size[0] * CrBounded_Single->size[1];
          CrBounded_Single->size[0] = NRows_Matrix;
          CrBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(CrBounded_Single, i);

          /* Index using a linear index */
          if (UseLinIdxTF) {
            /* Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm */
            for (b_i = 0; b_i < NElements_Matrix; b_i++) {
              /* Extract and cast to type single the ith r, g, and b values */
              /* Scalars; type single. */
              /* Apply the RGB-to-YCbCr algorithm */
              /* Scalars; type single. */
              /* Note: for efficiency, the outputs replace the inputs. */
              /* Local function.   */
              /* Note: rgb2ycbcr_compute is a custom function located within folder */
              /* 'FacePulseRate'.                     */
              /*  y */
              /*  cb */
              /*  cr */
              /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
              /*  */
              /*     Description: */
              /*  */
              /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*  */
              /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
              /*     derived from Poynton (1996, p. 175 - 176). */
              /*  */
              /*     Note: */
              /*  */
              /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     References: */
              /*  */
              /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
              /* Inline function */
              /* ith Y channel element */
              /* Scalar; type single. */
              CbCrRatio_ith = ((0.2568F * (real32_T)RBounded_Uint8->data[b_i] +
                                0.5041F * (real32_T)GBounded_Uint8->data[b_i]) +
                               0.0979F * (real32_T)BBounded_Uint8->data[b_i]) +
                16.0F;

              /* ith Cb channel element */
              /* Scalar; type single. */
              cb = ((-0.1482F * (real32_T)RBounded_Uint8->data[b_i] + -0.291F *
                     (real32_T)GBounded_Uint8->data[b_i]) + 0.4392F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* ith Cr channel element */
              /* Scalar; type single. */
              cr = ((0.4392F * (real32_T)RBounded_Uint8->data[b_i] + -0.3678F *
                     (real32_T)GBounded_Uint8->data[b_i]) + -0.0714F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* end function */
              /* Assign the ith y, cb, and cr values */
              YBounded_Single->data[b_i] = CbCrRatio_ith;
              CbBounded_Single->data[b_i] = cb;
              CrBounded_Single->data[b_i] = cr;

              /* Classify pixels within all thresholds as skin (true)        */
              if ((CbCrRatio_ith > YMin) && (cb > CbMin) && (cb < CbMax) && (cr >
                   CrMin) && (cr < CrMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              if (IsSkinMask_ith) {
                /* Apply rgb-to-hs algorithm */
                /* Scalars; type single. */
                /* Note: rgb2h is a custom function located within folder  */
                /* 'FacePulseRate'.   */
                /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                /*           channels of the HSV colorspace.  */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*                     */
                /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                /*     colorspace.  */
                /*  */
                /*     Notes: */
                /*  */
                /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                /*     code generation. As of Matlab version 2020a, the file location is  */
                /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                /*  */
                /*     References: */
                /*  */
                /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                /*     19. */
                /* Inline function */
                /* Maximum channel value */
                if ((RBounded_Uint8->data[b_i] > GBounded_Uint8->data[b_i]) &&
                    (RBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])) {
                  v = RBounded_Uint8->data[b_i];
                } else if (GBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])
                {
                  v = GBounded_Uint8->data[b_i];
                } else {
                  v = BBounded_Uint8->data[b_i];
                }

                /* Minimum channel value */
                if ((RBounded_Uint8->data[b_i] < GBounded_Uint8->data[b_i]) &&
                    (RBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])) {
                  l = RBounded_Uint8->data[b_i];
                } else if (GBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])
                {
                  l = GBounded_Uint8->data[b_i];
                } else {
                  l = BBounded_Uint8->data[b_i];
                }

                /* Difference between maximum and minimum values */
                l = v - l;

                /* Determine value of hue channel (h) */
                if (l == 0) {
                  CbCrRatio_ith = 0.0F;
                } else if (BBounded_Uint8->data[b_i] == v) {
                  CbCrRatio_ith = ((real32_T)(RBounded_Uint8->data[b_i] -
                    GBounded_Uint8->data[b_i]) / (real32_T)l + 4.0F) / 6.0F;
                  if (CbCrRatio_ith < 0.0F) {
                    CbCrRatio_ith++;
                  }
                } else if (RBounded_Uint8->data[b_i] == v) {
                  CbCrRatio_ith = (real32_T)(GBounded_Uint8->data[b_i] -
                    BBounded_Uint8->data[b_i]) / (real32_T)l / 6.0F;
                  if (CbCrRatio_ith < 0.0F) {
                    CbCrRatio_ith++;
                  }
                } else if (GBounded_Uint8->data[b_i] == v) {
                  CbCrRatio_ith = ((real32_T)(BBounded_Uint8->data[b_i] -
                    RBounded_Uint8->data[b_i]) / (real32_T)l + 2.0F) / 6.0F;
                  if (CbCrRatio_ith < 0.0F) {
                    CbCrRatio_ith++;
                  }
                } else {
                  CbCrRatio_ith = 0.0F;
                }

                if (v == 0) {
                  s = 0.0F;
                } else if (l == 0) {
                  s = 0.0F;
                } else {
                  s = (real32_T)l / (real32_T)v;
                }

                /* end function */
                /* Classify pixels within all thresholds as skin (true)  */
                if ((CbCrRatio_ith < HMax) && (s > SMin)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }
              }

              if (IsSkinMask_ith) {
                /* Calculate Cb-to-Cr ratio */
                /* Type single to permit division to return fractions. */
                CbCrRatio_ith = cb / cr;
                if ((!(CbCrRatio_ith > CbCrRatioMin)) || (!(CbCrRatio_ith <
                      CbCrRatioMax))) {
                  IsSkinMask_ith = false;
                }
              }

              IsSkinMask->data[b_i] = IsSkinMask_ith;
            }

            /* Index using subscript indices */
          } else {
            i = (XOffset + NCols_Matrix) - 1;
            for (b_i = XOffset; b_i <= i; b_i++) {
              i1 = (YOffset + NRows_Matrix) - 1;
              for (j = YOffset; j <= i1; j++) {
                /* Indices for output matrices */
                YAdjust = j - YOffset;
                XAdjust = b_i - XOffset;

                /* Extract and cast to type single the ith r, g, and b values */
                /* Scalars; type single. */
                c1 = RBounded_Uint8->data[(j + RBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c2 = GBounded_Uint8->data[(j + GBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c3 = BBounded_Uint8->data[(j + BBounded_Uint8->size[0] * (b_i -
                  1)) - 1];

                /* Apply the RGB-to-YCbCr algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the outputs replace the inputs. */
                /* Local function.   */
                /* Note: rgb2ycbcr_compute is a custom function located within folder */
                /* 'FacePulseRate'.                     */
                /*  y */
                /*  cb */
                /*  cr */
                /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                CbCrRatio_ith = ((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)
                                  c2) + 0.0979F * (real32_T)c3) + 16.0F;

                /* ith Cb channel element */
                /* Scalar; type single. */
                cb = ((-0.1482F * (real32_T)c1 + -0.291F * (real32_T)c2) +
                      0.4392F * (real32_T)c3) + 128.0F;

                /* ith Cr channel element */
                /* Scalar; type single. */
                cr = ((0.4392F * (real32_T)c1 + -0.3678F * (real32_T)c2) +
                      -0.0714F * (real32_T)c3) + 128.0F;

                /* end function */
                /* Assign the ith y, cb, and cr values */
                YBounded_Single->data[YAdjust + YBounded_Single->size[0] *
                  XAdjust] = CbCrRatio_ith;
                CbBounded_Single->data[YAdjust + CbBounded_Single->size[0] *
                  XAdjust] = cb;
                CrBounded_Single->data[YAdjust + CrBounded_Single->size[0] *
                  XAdjust] = cr;

                /* Classify pixels within all thresholds as skin (true)        */
                if ((CbCrRatio_ith > YMin) && (cb > CbMin) && (cb < CbMax) &&
                    (cr > CrMin) && (cr < CrMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                if (IsSkinMask_ith) {
                  /* Apply rgb-to-hs algorithm */
                  /* Scalars; type single. */
                  /* Note: rgb2h is a custom function located within folder  */
                  /* 'FacePulseRate'.   */
                  /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                  /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                  /*           channels of the HSV colorspace.  */
                  /*     */
                  /*     Helper function to function FacePulseRate.  */
                  /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                  /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                  /*  */
                  /*     Description: */
                  /*                     */
                  /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                  /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                  /*     colorspace.  */
                  /*  */
                  /*     Notes: */
                  /*  */
                  /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                  /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                  /*  */
                  /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                  /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                  /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                  /*     code generation. As of Matlab version 2020a, the file location is  */
                  /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                  /*  */
                  /*     References: */
                  /*  */
                  /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                  /*     19. */
                  /* Inline function */
                  /* Maximum channel value */
                  if ((c1 > c2) && (c1 > c3)) {
                    v = c1;
                  } else {
                    v = muIntScalarMax_sint32(c2, c3);
                  }

                  /* Minimum channel value */
                  if ((c1 < c2) && (c1 < c3)) {
                    l = c1;
                  } else {
                    l = muIntScalarMin_sint32(c2, c3);
                  }

                  /* Difference between maximum and minimum values */
                  l = v - l;

                  /* Determine value of hue channel (h) */
                  if (l == 0) {
                    CbCrRatio_ith = 0.0F;
                  } else if (c3 == v) {
                    CbCrRatio_ith = ((real32_T)(c1 - c2) / (real32_T)l + 4.0F) /
                      6.0F;
                    if (CbCrRatio_ith < 0.0F) {
                      CbCrRatio_ith++;
                    }
                  } else if (c1 == v) {
                    CbCrRatio_ith = (real32_T)(c2 - c3) / (real32_T)l / 6.0F;
                    if (CbCrRatio_ith < 0.0F) {
                      CbCrRatio_ith++;
                    }
                  } else if (c2 == v) {
                    CbCrRatio_ith = ((real32_T)(c3 - c1) / (real32_T)l + 2.0F) /
                      6.0F;
                    if (CbCrRatio_ith < 0.0F) {
                      CbCrRatio_ith++;
                    }
                  } else {
                    CbCrRatio_ith = 0.0F;
                  }

                  if (v == 0) {
                    s = 0.0F;
                  } else if (l == 0) {
                    s = 0.0F;
                  } else {
                    s = (real32_T)l / (real32_T)v;
                  }

                  /* end function */
                  /* Classify pixels within all thresholds as skin (true)  */
                  if ((CbCrRatio_ith < HMax) && (s > SMin)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }
                }

                if (IsSkinMask_ith) {
                  /* Calculate Cb-to-Cr ratio */
                  /* Type single to permit division to return fractions. */
                  CbCrRatio_ith = cb / cr;
                  if ((!(CbCrRatio_ith > CbCrRatioMin)) || (!(CbCrRatio_ith <
                        CbCrRatioMax))) {
                    IsSkinMask_ith = false;
                  }
                }

                IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                  IsSkinMask_ith;
              }
            }
          }
        }

        /* Use tailored thresholds         */
      } else {
        /* (4) Condition 4               */
        /*  - Use tailored thresholds: tailored YCbCr thresholds and tailored HS thresholds. */
        /*  - Do not return H and S channel matrices.           */
        /*  - Do not return YCbCr matrices.             */
        if ((!ReturnCbCrTF) && (!ReturnYTF)) {
          /* M x N matrix; type single. */
          YBounded_Single->size[0] = 0;
          YBounded_Single->size[1] = 0;
          CbBounded_Single->size[0] = 0;
          CbBounded_Single->size[1] = 0;
          CrBounded_Single->size[0] = 0;
          CrBounded_Single->size[1] = 0;

          /* Index using a linear index */
          if (UseLinIdxTF) {
            /* Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm */
            for (b_i = 0; b_i < NElements_Matrix; b_i++) {
              /* Extract and cast to type single the ith r, g, and b values */
              /* Scalars; type single. */
              /* Apply rgb-to-hs algorithm */
              /* Scalars; type single. */
              /* Note: rgb2hs is a custom function located within folder */
              /* 'FacePulseRate'. */
              /*  h; named "out" because later reassigned with different value */
              /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
              /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
              /*           channels of the HSV colorspace.  */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Description: */
              /*                     */
              /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
              /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
              /*     colorspace.  */
              /*  */
              /*     Notes: */
              /*  */
              /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
              /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
              /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
              /*     code generation. As of Matlab version 2020a, the file location is  */
              /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
              /*  */
              /*     References: */
              /*  */
              /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
              /*     19. */
              /* Inline function */
              /* Maximum channel value */
              if ((RBounded_Uint8->data[b_i] > GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])) {
                v = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])
              {
                v = GBounded_Uint8->data[b_i];
              } else {
                v = BBounded_Uint8->data[b_i];
              }

              /* Minimum channel value */
              if ((RBounded_Uint8->data[b_i] < GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])) {
                l = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])
              {
                l = GBounded_Uint8->data[b_i];
              } else {
                l = BBounded_Uint8->data[b_i];
              }

              /* Difference between maximum and minimum values */
              l = v - l;

              /* Determine value of hue channel (h) */
              if (l == 0) {
                out = 0.0F;
              } else if (BBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(RBounded_Uint8->data[b_i] -
                                  GBounded_Uint8->data[b_i]) / (real32_T)l +
                       4.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (RBounded_Uint8->data[b_i] == v) {
                out = (real32_T)(GBounded_Uint8->data[b_i] -
                                 BBounded_Uint8->data[b_i]) / (real32_T)l / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (GBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(BBounded_Uint8->data[b_i] -
                                  RBounded_Uint8->data[b_i]) / (real32_T)l +
                       2.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else {
                out = 0.0F;
              }

              if (v == 0) {
                s = 0.0F;
              } else if (l == 0) {
                s = 0.0F;
              } else {
                s = (real32_T)l / (real32_T)v;
              }

              /* end function */
              /* Classify pixels within all thresholds as skin (true)  */
              if ((out < HMax) && (s > SMin) && (s < SMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              IsSkinMask->data[b_i] = IsSkinMask_ith;
              if (IsSkinMask_ith) {
                /* Apply the RGB-to-Y algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the output replaces the out variable previously  */
                /* assigned. */
                /* Note: rgb2y is a custom function located within folder */
                /* 'FacePulseRate'.      */
                /*  y */
                /* rgb2y   Apply the RGB-to-Y algorithm to a given pixel and return the Y channel. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-Y algorithm to a given pixel and return the Y channel. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Y channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                out = ((0.2568F * (real32_T)RBounded_Uint8->data[b_i] + 0.5041F *
                        (real32_T)GBounded_Uint8->data[b_i]) + 0.0979F *
                       (real32_T)BBounded_Uint8->data[b_i]) + 16.0F;

                /* end function */
                if ((out > YMin) && (out < YMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                IsSkinMask->data[b_i] = IsSkinMask_ith;
                if (IsSkinMask_ith) {
                  /* Apply the RGB-to-Cb algorithm */
                  /* Scalars; type single. */
                  /* Note: rgb2cb is a custom function located within folder */
                  /* 'FacePulseRate'.       */
                  /* rgb2cb   Apply the RGB-to-Cb algorithm to a given pixel and return the Cb channel. */
                  /*     */
                  /*     Helper function to function FacePulseRate.  */
                  /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                  /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                  /*  */
                  /*     Description: */
                  /*   */
                  /*     Apply the RGB-to-Cb algorithm to a given pixel and return the Cb channel. */
                  /*  */
                  /*     This conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is   */
                  /*     derived from Poynton (1996, p. 175 - 176). */
                  /*  */
                  /*     Note: */
                  /*  */
                  /*     For efficiency, the Cb channel of the YCbCr colorspace is assigned to variable b, which */
                  /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                  /*  */
                  /*     References: */
                  /*  */
                  /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                  /* Inline function */
                  /* ith Cb channel element */
                  /* Scalar; type single. */
                  cb = ((-0.1482F * (real32_T)RBounded_Uint8->data[b_i] +
                         -0.291F * (real32_T)GBounded_Uint8->data[b_i]) +
                        0.4392F * (real32_T)BBounded_Uint8->data[b_i]) + 128.0F;

                  /* end function */
                  if ((cb > CbMin) && (cb < CbMax)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }

                  IsSkinMask->data[b_i] = IsSkinMask_ith;
                  if (IsSkinMask_ith) {
                    /* Apply the RGB-to-Cr algorithm */
                    /* Scalars; type single. */
                    /* Note: rgb2cr is a custom function located within folder */
                    /* 'FacePulseRate'.                         */
                    /* rgb2cr   Apply the RGB-to-Cr algorithm to a given pixel and return the Cr channel. */
                    /*     */
                    /*     Helper function to function FacePulseRate.  */
                    /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                    /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                    /*  */
                    /*     Description: */
                    /*    */
                    /*     Apply the RGB-to-Cr algorithm to a given pixel and return the Cr channel. */
                    /*  */
                    /*     This conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is  */
                    /*      derived from Poynton (1996, p. 175 - 176). */
                    /*  */
                    /*     Note: */
                    /*  */
                    /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                    /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                    /*  */
                    /*     References: */
                    /*  */
                    /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                    /* Inline function */
                    /* ith Cr channel element */
                    /* Scalar; type single. */
                    cr = ((0.4392F * (real32_T)RBounded_Uint8->data[b_i] +
                           -0.3678F * (real32_T)GBounded_Uint8->data[b_i]) +
                          -0.0714F * (real32_T)BBounded_Uint8->data[b_i]) +
                      128.0F;

                    /* end function */
                    if ((cr > CrMin) && (cr < CrMax)) {
                      IsSkinMask_ith = true;
                    } else {
                      IsSkinMask_ith = false;
                    }

                    IsSkinMask->data[b_i] = IsSkinMask_ith;
                    if (IsSkinMask_ith) {
                      /* Calculate Cb-to-Cr ratio */
                      /* Type single to permit division to return fractions. */
                      /* Note: for efficiency, the output replaces the out variable   */
                      /* previously assigned. */
                      /* Local function.  */
                      out = cb / cr;
                      if ((out > CbCrRatioMin) && (out < CbCrRatioMax)) {
                        IsSkinMask->data[b_i] = true;
                      } else {
                        IsSkinMask->data[b_i] = false;
                      }
                    }
                  }
                }
              }
            }

            /* Index using subscript indices */
          } else {
            i = (XOffset + NCols_Matrix) - 1;
            for (b_i = XOffset; b_i <= i; b_i++) {
              i1 = (YOffset + NRows_Matrix) - 1;
              for (j = YOffset; j <= i1; j++) {
                /* Indices for output matrices */
                YAdjust = j - YOffset;
                XAdjust = b_i - XOffset;

                /* Extract and cast to type single the ith r, g, and b values */
                /* Scalars; type single. */
                c1 = RBounded_Uint8->data[(j + RBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c2 = GBounded_Uint8->data[(j + GBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c3 = BBounded_Uint8->data[(j + BBounded_Uint8->size[0] * (b_i -
                  1)) - 1];

                /* Apply rgb-to-hs algorithm */
                /* Scalars; type single. */
                /* Note: rgb2hs is a custom function located within folder */
                /* 'FacePulseRate'. */
                /*  h; named "out" because later reassigned with different value */
                /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                /*           channels of the HSV colorspace.  */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*                     */
                /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                /*     colorspace.  */
                /*  */
                /*     Notes: */
                /*  */
                /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                /*     code generation. As of Matlab version 2020a, the file location is  */
                /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                /*  */
                /*     References: */
                /*  */
                /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                /*     19. */
                /* Inline function */
                /* Maximum channel value */
                if ((c1 > c2) && (c1 > c3)) {
                  v = c1;
                } else {
                  v = muIntScalarMax_sint32(c2, c3);
                }

                /* Minimum channel value */
                if ((c1 < c2) && (c1 < c3)) {
                  l = c1;
                } else {
                  l = muIntScalarMin_sint32(c2, c3);
                }

                /* Difference between maximum and minimum values */
                l = v - l;

                /* Determine value of hue channel (h) */
                if (l == 0) {
                  out = 0.0F;
                } else if (c3 == v) {
                  out = ((real32_T)(c1 - c2) / (real32_T)l + 4.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c1 == v) {
                  out = (real32_T)(c2 - c3) / (real32_T)l / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c2 == v) {
                  out = ((real32_T)(c3 - c1) / (real32_T)l + 2.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else {
                  out = 0.0F;
                }

                if (v == 0) {
                  s = 0.0F;
                } else if (l == 0) {
                  s = 0.0F;
                } else {
                  s = (real32_T)l / (real32_T)v;
                }

                /* end function */
                /* Classify pixels within all thresholds as skin (true)  */
                if ((out < HMax) && (s > SMin) && (s < SMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                  IsSkinMask_ith;
                if (IsSkinMask_ith) {
                  /* Apply the RGB-to-Y algorithm */
                  /* Scalars; type single. */
                  /* Note: for efficiency, the output replaces the out variable previously  */
                  /* assigned. */
                  /* Note: rgb2y is a custom function located within folder */
                  /* 'FacePulseRate'.      */
                  /*  y */
                  /* rgb2y   Apply the RGB-to-Y algorithm to a given pixel and return the Y channel. */
                  /*     */
                  /*     Helper function to function FacePulseRate.  */
                  /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                  /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                  /*  */
                  /*     Description: */
                  /*  */
                  /*     Apply the RGB-to-Y algorithm to a given pixel and return the Y channel. */
                  /*  */
                  /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                  /*     derived from Poynton (1996, p. 175 - 176). */
                  /*  */
                  /*     Note: */
                  /*  */
                  /*     For efficiency, the Y channel of the YCbCr colorspace is assigned to variable b, which */
                  /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                  /*  */
                  /*     References: */
                  /*  */
                  /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                  /* Inline function */
                  /* ith Y channel element */
                  /* Scalar; type single. */
                  out = ((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)c2) +
                         0.0979F * (real32_T)c3) + 16.0F;

                  /* end function */
                  if ((out > YMin) && (out < YMax)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }

                  IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                    IsSkinMask_ith;
                  if (IsSkinMask_ith) {
                    /* Apply the RGB-to-Cb algorithm */
                    /* Scalars; type single. */
                    /* Note: rgb2cb is a custom function located within folder */
                    /* 'FacePulseRate'.       */
                    /* rgb2cb   Apply the RGB-to-Cb algorithm to a given pixel and return the Cb channel. */
                    /*     */
                    /*     Helper function to function FacePulseRate.  */
                    /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                    /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                    /*  */
                    /*     Description: */
                    /*   */
                    /*     Apply the RGB-to-Cb algorithm to a given pixel and return the Cb channel. */
                    /*  */
                    /*     This conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is   */
                    /*     derived from Poynton (1996, p. 175 - 176). */
                    /*  */
                    /*     Note: */
                    /*  */
                    /*     For efficiency, the Cb channel of the YCbCr colorspace is assigned to variable b, which */
                    /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                    /*  */
                    /*     References: */
                    /*  */
                    /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                    /* Inline function */
                    /* ith Cb channel element */
                    /* Scalar; type single. */
                    cb = ((-0.1482F * (real32_T)c1 + -0.291F * (real32_T)c2) +
                          0.4392F * (real32_T)c3) + 128.0F;

                    /* end function */
                    if ((cb > CbMin) && (cb < CbMax)) {
                      IsSkinMask_ith = true;
                    } else {
                      IsSkinMask_ith = false;
                    }

                    IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                      IsSkinMask_ith;
                    if (IsSkinMask_ith) {
                      /* Apply the RGB-to-Cr algorithm */
                      /* Scalars; type single. */
                      /* Note: rgb2cr is a custom function located within folder */
                      /* 'FacePulseRate'.                         */
                      /* rgb2cr   Apply the RGB-to-Cr algorithm to a given pixel and return the Cr channel. */
                      /*     */
                      /*     Helper function to function FacePulseRate.  */
                      /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                      /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                      /*  */
                      /*     Description: */
                      /*    */
                      /*     Apply the RGB-to-Cr algorithm to a given pixel and return the Cr channel. */
                      /*  */
                      /*     This conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is  */
                      /*      derived from Poynton (1996, p. 175 - 176). */
                      /*  */
                      /*     Note: */
                      /*  */
                      /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                      /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                      /*  */
                      /*     References: */
                      /*  */
                      /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                      /* Inline function */
                      /* ith Cr channel element */
                      /* Scalar; type single. */
                      cr = ((0.4392F * (real32_T)c1 + -0.3678F * (real32_T)c2) +
                            -0.0714F * (real32_T)c3) + 128.0F;

                      /* end function */
                      if ((cr > CrMin) && (cr < CrMax)) {
                        IsSkinMask_ith = true;
                      } else {
                        IsSkinMask_ith = false;
                      }

                      IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                        IsSkinMask_ith;
                      if (IsSkinMask_ith) {
                        /* Calculate Cb-to-Cr ratio */
                        /* Type single to permit division to return fractions. */
                        /* Note: for efficiency, the output replaces the out variable   */
                        /* previously assigned. */
                        /* Local function.  */
                        out = cb / cr;
                        if ((out > CbCrRatioMin) && (out < CbCrRatioMax)) {
                          IsSkinMask->data[YAdjust + IsSkinMask->size[0] *
                            XAdjust] = true;
                        } else {
                          IsSkinMask->data[YAdjust + IsSkinMask->size[0] *
                            XAdjust] = false;
                        }
                      }
                    }
                  }
                }
              }
            }
          }

          /* (5) Condition 5   */
          /*  - Use tailored thresholds: tailored YCbCr thresholds and tailored HS thresholds. */
          /*  - Do not return H and S channel matrices. */
          /*  - Return Y-channel matrix but not the Cb and Cr channel matrices. */
        } else if ((!ReturnCbCrTF) && ReturnYTF) {
          /* M x N matrix; type single. */
          i = YBounded_Single->size[0] * YBounded_Single->size[1];
          YBounded_Single->size[0] = NRows_Matrix;
          YBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(YBounded_Single, i);
          CbBounded_Single->size[0] = 0;
          CbBounded_Single->size[1] = 0;
          CrBounded_Single->size[0] = 0;
          CrBounded_Single->size[1] = 0;

          /* Index using a linear index */
          if (UseLinIdxTF) {
            /* Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm */
            for (b_i = 0; b_i < NElements_Matrix; b_i++) {
              /* Extract and cast to type single the ith r, g, and b values */
              /* Scalars; type single. */
              /* Apply rgb-to-hs algorithm */
              /* Scalars; type single. */
              /* Note: rgb2hs is a custom function located within folder */
              /* 'FacePulseRate'.  */
              /*  h; named "out" because later reassigned with different value */
              /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
              /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
              /*           channels of the HSV colorspace.  */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Description: */
              /*                     */
              /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
              /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
              /*     colorspace.  */
              /*  */
              /*     Notes: */
              /*  */
              /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
              /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
              /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
              /*     code generation. As of Matlab version 2020a, the file location is  */
              /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
              /*  */
              /*     References: */
              /*  */
              /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
              /*     19. */
              /* Inline function */
              /* Maximum channel value */
              if ((RBounded_Uint8->data[b_i] > GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])) {
                v = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])
              {
                v = GBounded_Uint8->data[b_i];
              } else {
                v = BBounded_Uint8->data[b_i];
              }

              /* Minimum channel value */
              if ((RBounded_Uint8->data[b_i] < GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])) {
                l = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])
              {
                l = GBounded_Uint8->data[b_i];
              } else {
                l = BBounded_Uint8->data[b_i];
              }

              /* Difference between maximum and minimum values */
              l = v - l;

              /* Determine value of hue channel (h) */
              if (l == 0) {
                out = 0.0F;
              } else if (BBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(RBounded_Uint8->data[b_i] -
                                  GBounded_Uint8->data[b_i]) / (real32_T)l +
                       4.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (RBounded_Uint8->data[b_i] == v) {
                out = (real32_T)(GBounded_Uint8->data[b_i] -
                                 BBounded_Uint8->data[b_i]) / (real32_T)l / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (GBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(BBounded_Uint8->data[b_i] -
                                  RBounded_Uint8->data[b_i]) / (real32_T)l +
                       2.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else {
                out = 0.0F;
              }

              if (v == 0) {
                s = 0.0F;
              } else if (l == 0) {
                s = 0.0F;
              } else {
                s = (real32_T)l / (real32_T)v;
              }

              /* end function */
              /* Classify pixels within all thresholds as skin (true)  */
              if ((out < HMax) && (s > SMin) && (s < SMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              IsSkinMask->data[b_i] = IsSkinMask_ith;
              if (IsSkinMask_ith) {
                /* Apply the RGB-to-Y algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the output replaces the out variable previously  */
                /* assigned. */
                /* Note: rgb2y is a custom function located within folder */
                /* 'FacePulseRate'.       */
                /*  y */
                /* rgb2y   Apply the RGB-to-Y algorithm to a given pixel and return the Y channel. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-Y algorithm to a given pixel and return the Y channel. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Y channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                out = ((0.2568F * (real32_T)RBounded_Uint8->data[b_i] + 0.5041F *
                        (real32_T)GBounded_Uint8->data[b_i]) + 0.0979F *
                       (real32_T)BBounded_Uint8->data[b_i]) + 16.0F;

                /* end function */
                if ((out > YMin) && (out < YMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                IsSkinMask->data[b_i] = IsSkinMask_ith;
                if (IsSkinMask_ith) {
                  /* Apply the RGB-to-Cb algorithm */
                  /* Scalars; type single. */
                  /* Note: rgb2cb is a custom function located within folder */
                  /* 'FacePulseRate'.     */
                  /* rgb2cb   Apply the RGB-to-Cb algorithm to a given pixel and return the Cb channel. */
                  /*     */
                  /*     Helper function to function FacePulseRate.  */
                  /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                  /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                  /*  */
                  /*     Description: */
                  /*   */
                  /*     Apply the RGB-to-Cb algorithm to a given pixel and return the Cb channel. */
                  /*  */
                  /*     This conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is   */
                  /*     derived from Poynton (1996, p. 175 - 176). */
                  /*  */
                  /*     Note: */
                  /*  */
                  /*     For efficiency, the Cb channel of the YCbCr colorspace is assigned to variable b, which */
                  /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                  /*  */
                  /*     References: */
                  /*  */
                  /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                  /* Inline function */
                  /* ith Cb channel element */
                  /* Scalar; type single. */
                  cb = ((-0.1482F * (real32_T)RBounded_Uint8->data[b_i] +
                         -0.291F * (real32_T)GBounded_Uint8->data[b_i]) +
                        0.4392F * (real32_T)BBounded_Uint8->data[b_i]) + 128.0F;

                  /* end function */
                  if ((cb > CbMin) && (cb < CbMax)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }

                  IsSkinMask->data[b_i] = IsSkinMask_ith;
                  if (IsSkinMask_ith) {
                    /* Apply the RGB-to-Cr algorithm */
                    /* Scalars; type single. */
                    /* Note: rgb2cr is a custom function located within folder */
                    /* 'FacePulseRate'.                          */
                    /* rgb2cr   Apply the RGB-to-Cr algorithm to a given pixel and return the Cr channel. */
                    /*     */
                    /*     Helper function to function FacePulseRate.  */
                    /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                    /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                    /*  */
                    /*     Description: */
                    /*    */
                    /*     Apply the RGB-to-Cr algorithm to a given pixel and return the Cr channel. */
                    /*  */
                    /*     This conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is  */
                    /*      derived from Poynton (1996, p. 175 - 176). */
                    /*  */
                    /*     Note: */
                    /*  */
                    /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                    /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                    /*  */
                    /*     References: */
                    /*  */
                    /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                    /* Inline function */
                    /* ith Cr channel element */
                    /* Scalar; type single. */
                    cr = ((0.4392F * (real32_T)RBounded_Uint8->data[b_i] +
                           -0.3678F * (real32_T)GBounded_Uint8->data[b_i]) +
                          -0.0714F * (real32_T)BBounded_Uint8->data[b_i]) +
                      128.0F;

                    /* end function */
                    if ((cr > CrMin) && (cr < CrMax)) {
                      IsSkinMask_ith = true;
                    } else {
                      IsSkinMask_ith = false;
                    }

                    IsSkinMask->data[b_i] = IsSkinMask_ith;
                    if (IsSkinMask_ith) {
                      /* Calculate Cb-to-Cr ratio */
                      /* Type single to permit division to return fractions. */
                      /* Note: for efficiency, the output replaces the out variable   */
                      /* previously assigned. */
                      /* Local function.  */
                      out = cb / cr;
                      if ((out > CbCrRatioMin) && (out < CbCrRatioMax)) {
                        IsSkinMask->data[b_i] = true;
                      } else {
                        IsSkinMask->data[b_i] = false;
                      }
                    }
                  }
                }
              } else {
                /* Apply the RGB-to-Y algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the output replaces the out variable previously  */
                /* assigned. */
                /* Note: rgb2y is a custom function located within folder 'FacePulseRate'.     */
                /*  y */
                /* rgb2y   Apply the RGB-to-Y algorithm to a given pixel and return the Y channel. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-Y algorithm to a given pixel and return the Y channel. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Y channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                out = ((0.2568F * (real32_T)RBounded_Uint8->data[b_i] + 0.5041F *
                        (real32_T)GBounded_Uint8->data[b_i]) + 0.0979F *
                       (real32_T)BBounded_Uint8->data[b_i]) + 16.0F;

                /* end function */
              }

              /* Assign the ith y, cb, and cr values */
              YBounded_Single->data[b_i] = out;
            }

            /* Index using subscript indices */
          } else {
            i = (XOffset + NCols_Matrix) - 1;
            for (b_i = XOffset; b_i <= i; b_i++) {
              i1 = (YOffset + NRows_Matrix) - 1;
              for (j = YOffset; j <= i1; j++) {
                /* Indices for output matrices */
                YAdjust = j - YOffset;
                XAdjust = b_i - XOffset;

                /* Extract and cast to type single the ith r, g, and b values */
                /* Scalars; type single. */
                c1 = RBounded_Uint8->data[(j + RBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c2 = GBounded_Uint8->data[(j + GBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c3 = BBounded_Uint8->data[(j + BBounded_Uint8->size[0] * (b_i -
                  1)) - 1];

                /* Apply rgb-to-hs algorithm */
                /* Scalars; type single. */
                /* Note: rgb2hs is a custom function located within folder */
                /* 'FacePulseRate'.  */
                /*  h; named "out" because later reassigned with different value */
                /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                /*           channels of the HSV colorspace.  */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*                     */
                /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                /*     colorspace.  */
                /*  */
                /*     Notes: */
                /*  */
                /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                /*     code generation. As of Matlab version 2020a, the file location is  */
                /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                /*  */
                /*     References: */
                /*  */
                /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                /*     19. */
                /* Inline function */
                /* Maximum channel value */
                if ((c1 > c2) && (c1 > c3)) {
                  v = c1;
                } else {
                  v = muIntScalarMax_sint32(c2, c3);
                }

                /* Minimum channel value */
                if ((c1 < c2) && (c1 < c3)) {
                  l = c1;
                } else {
                  l = muIntScalarMin_sint32(c2, c3);
                }

                /* Difference between maximum and minimum values */
                l = v - l;

                /* Determine value of hue channel (h) */
                if (l == 0) {
                  out = 0.0F;
                } else if (c3 == v) {
                  out = ((real32_T)(c1 - c2) / (real32_T)l + 4.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c1 == v) {
                  out = (real32_T)(c2 - c3) / (real32_T)l / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c2 == v) {
                  out = ((real32_T)(c3 - c1) / (real32_T)l + 2.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else {
                  out = 0.0F;
                }

                if (v == 0) {
                  s = 0.0F;
                } else if (l == 0) {
                  s = 0.0F;
                } else {
                  s = (real32_T)l / (real32_T)v;
                }

                /* end function */
                /* Classify pixels within all thresholds as skin (true)  */
                if ((out < HMax) && (s > SMin) && (s < SMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                  IsSkinMask_ith;
                if (IsSkinMask_ith) {
                  /* Apply the RGB-to-Y algorithm */
                  /* Scalars; type single. */
                  /* Note: for efficiency, the output replaces the out variable previously  */
                  /* assigned. */
                  /* Note: rgb2y is a custom function located within folder */
                  /* 'FacePulseRate'.       */
                  /*  y */
                  /* rgb2y   Apply the RGB-to-Y algorithm to a given pixel and return the Y channel. */
                  /*     */
                  /*     Helper function to function FacePulseRate.  */
                  /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                  /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                  /*  */
                  /*     Description: */
                  /*  */
                  /*     Apply the RGB-to-Y algorithm to a given pixel and return the Y channel. */
                  /*  */
                  /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                  /*     derived from Poynton (1996, p. 175 - 176). */
                  /*  */
                  /*     Note: */
                  /*  */
                  /*     For efficiency, the Y channel of the YCbCr colorspace is assigned to variable b, which */
                  /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                  /*  */
                  /*     References: */
                  /*  */
                  /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                  /* Inline function */
                  /* ith Y channel element */
                  /* Scalar; type single. */
                  out = ((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)c2) +
                         0.0979F * (real32_T)c3) + 16.0F;

                  /* end function */
                  if ((out > YMin) && (out < YMax)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }

                  IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                    IsSkinMask_ith;
                  if (IsSkinMask_ith) {
                    /* Apply the RGB-to-Cb algorithm */
                    /* Scalars; type single. */
                    /* Note: rgb2cb is a custom function located within folder */
                    /* 'FacePulseRate'.     */
                    /* rgb2cb   Apply the RGB-to-Cb algorithm to a given pixel and return the Cb channel. */
                    /*     */
                    /*     Helper function to function FacePulseRate.  */
                    /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                    /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                    /*  */
                    /*     Description: */
                    /*   */
                    /*     Apply the RGB-to-Cb algorithm to a given pixel and return the Cb channel. */
                    /*  */
                    /*     This conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is   */
                    /*     derived from Poynton (1996, p. 175 - 176). */
                    /*  */
                    /*     Note: */
                    /*  */
                    /*     For efficiency, the Cb channel of the YCbCr colorspace is assigned to variable b, which */
                    /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                    /*  */
                    /*     References: */
                    /*  */
                    /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                    /* Inline function */
                    /* ith Cb channel element */
                    /* Scalar; type single. */
                    cb = ((-0.1482F * (real32_T)c1 + -0.291F * (real32_T)c2) +
                          0.4392F * (real32_T)c3) + 128.0F;

                    /* end function */
                    if ((cb > CbMin) && (cb < CbMax)) {
                      IsSkinMask_ith = true;
                    } else {
                      IsSkinMask_ith = false;
                    }

                    IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                      IsSkinMask_ith;
                    if (IsSkinMask_ith) {
                      /* Apply the RGB-to-Cr algorithm */
                      /* Scalars; type single. */
                      /* Note: rgb2cr is a custom function located within folder */
                      /* 'FacePulseRate'.                          */
                      /* rgb2cr   Apply the RGB-to-Cr algorithm to a given pixel and return the Cr channel. */
                      /*     */
                      /*     Helper function to function FacePulseRate.  */
                      /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                      /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                      /*  */
                      /*     Description: */
                      /*    */
                      /*     Apply the RGB-to-Cr algorithm to a given pixel and return the Cr channel. */
                      /*  */
                      /*     This conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is  */
                      /*      derived from Poynton (1996, p. 175 - 176). */
                      /*  */
                      /*     Note: */
                      /*  */
                      /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                      /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                      /*  */
                      /*     References: */
                      /*  */
                      /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                      /* Inline function */
                      /* ith Cr channel element */
                      /* Scalar; type single. */
                      cr = ((0.4392F * (real32_T)c1 + -0.3678F * (real32_T)c2) +
                            -0.0714F * (real32_T)c3) + 128.0F;

                      /* end function */
                      if ((cr > CrMin) && (cr < CrMax)) {
                        IsSkinMask_ith = true;
                      } else {
                        IsSkinMask_ith = false;
                      }

                      IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                        IsSkinMask_ith;
                      if (IsSkinMask_ith) {
                        /* Calculate Cb-to-Cr ratio */
                        /* Type single to permit division to return fractions. */
                        /* Note: for efficiency, the output replaces the out variable   */
                        /* previously assigned. */
                        /* Local function.  */
                        out = cb / cr;
                        if ((out > CbCrRatioMin) && (out < CbCrRatioMax)) {
                          IsSkinMask->data[YAdjust + IsSkinMask->size[0] *
                            XAdjust] = true;
                        } else {
                          IsSkinMask->data[YAdjust + IsSkinMask->size[0] *
                            XAdjust] = false;
                        }
                      }
                    }
                  }
                } else {
                  /* Apply the RGB-to-Y algorithm */
                  /* Scalars; type single. */
                  /* Note: for efficiency, the output replaces the out variable previously  */
                  /* assigned. */
                  /* Note: rgb2y is a custom function located within folder 'FacePulseRate'.     */
                  /*  y */
                  /* rgb2y   Apply the RGB-to-Y algorithm to a given pixel and return the Y channel. */
                  /*     */
                  /*     Helper function to function FacePulseRate.  */
                  /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                  /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                  /*  */
                  /*     Description: */
                  /*  */
                  /*     Apply the RGB-to-Y algorithm to a given pixel and return the Y channel. */
                  /*  */
                  /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                  /*     derived from Poynton (1996, p. 175 - 176). */
                  /*  */
                  /*     Note: */
                  /*  */
                  /*     For efficiency, the Y channel of the YCbCr colorspace is assigned to variable b, which */
                  /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                  /*  */
                  /*     References: */
                  /*  */
                  /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                  /* Inline function */
                  /* ith Y channel element */
                  /* Scalar; type single. */
                  out = ((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)c2) +
                         0.0979F * (real32_T)c3) + 16.0F;

                  /* end function */
                }

                /* Assign the ith y, cb, and cr values */
                YBounded_Single->data[YAdjust + YBounded_Single->size[0] *
                  XAdjust] = out;
              }
            }
          }

          /* (6) Condition 6 */
          /*  - Use tailored thresholds: tailored YCbCr thresholds and tailored HS thresholds. */
          /*  - Do not return H and S channel matrices. */
          /*  - Return matrices of the Y, Cb, and Cr channels.         */
        } else {
          /* M x N matrices; type single. */
          i = YBounded_Single->size[0] * YBounded_Single->size[1];
          YBounded_Single->size[0] = NRows_Matrix;
          YBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(YBounded_Single, i);
          i = CbBounded_Single->size[0] * CbBounded_Single->size[1];
          CbBounded_Single->size[0] = NRows_Matrix;
          CbBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(CbBounded_Single, i);
          i = CrBounded_Single->size[0] * CrBounded_Single->size[1];
          CrBounded_Single->size[0] = NRows_Matrix;
          CrBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(CrBounded_Single, i);

          /* Index using a linear index */
          if (UseLinIdxTF) {
            /* Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm */
            for (b_i = 0; b_i < NElements_Matrix; b_i++) {
              /* Extract and cast to type single the ith r, g, and b values */
              /* Scalars; type single. */
              /* Apply rgb-to-hs algorithm */
              /* Scalars; type single. */
              /* Note: rgb2hs is a custom function located within folder 'FacePulseRate'.  */
              /*  h; named "out" because later reassigned with different value */
              /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
              /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
              /*           channels of the HSV colorspace.  */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Description: */
              /*                     */
              /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
              /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
              /*     colorspace.  */
              /*  */
              /*     Notes: */
              /*  */
              /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
              /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
              /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
              /*     code generation. As of Matlab version 2020a, the file location is  */
              /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
              /*  */
              /*     References: */
              /*  */
              /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
              /*     19. */
              /* Inline function */
              /* Maximum channel value */
              if ((RBounded_Uint8->data[b_i] > GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])) {
                v = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])
              {
                v = GBounded_Uint8->data[b_i];
              } else {
                v = BBounded_Uint8->data[b_i];
              }

              /* Minimum channel value */
              if ((RBounded_Uint8->data[b_i] < GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])) {
                l = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])
              {
                l = GBounded_Uint8->data[b_i];
              } else {
                l = BBounded_Uint8->data[b_i];
              }

              /* Difference between maximum and minimum values */
              l = v - l;

              /* Determine value of hue channel (h) */
              if (l == 0) {
                out = 0.0F;
              } else if (BBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(RBounded_Uint8->data[b_i] -
                                  GBounded_Uint8->data[b_i]) / (real32_T)l +
                       4.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (RBounded_Uint8->data[b_i] == v) {
                out = (real32_T)(GBounded_Uint8->data[b_i] -
                                 BBounded_Uint8->data[b_i]) / (real32_T)l / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (GBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(BBounded_Uint8->data[b_i] -
                                  RBounded_Uint8->data[b_i]) / (real32_T)l +
                       2.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else {
                out = 0.0F;
              }

              if (v == 0) {
                s = 0.0F;
              } else if (l == 0) {
                s = 0.0F;
              } else {
                s = (real32_T)l / (real32_T)v;
              }

              /* end function */
              if ((out < HMax) && (s > SMin) && (s < SMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              /* Apply the RGB-to-YCbCr algorithm */
              /* Scalars; type single. */
              /* Note: for efficiency, the outputs replace the inputs. */
              /* Note: rgb2ycbcr_compute is a custom function located within folder  */
              /* 'FacePulseRate'.       */
              /*  y */
              /*  cb */
              /*  cr */
              /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
              /*  */
              /*     Description: */
              /*  */
              /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*  */
              /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
              /*     derived from Poynton (1996, p. 175 - 176). */
              /*  */
              /*     Note: */
              /*  */
              /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     References: */
              /*  */
              /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
              /* Inline function */
              /* ith Y channel element */
              /* Scalar; type single. */
              CbCrRatio_ith = ((0.2568F * (real32_T)RBounded_Uint8->data[b_i] +
                                0.5041F * (real32_T)GBounded_Uint8->data[b_i]) +
                               0.0979F * (real32_T)BBounded_Uint8->data[b_i]) +
                16.0F;

              /* ith Cb channel element */
              /* Scalar; type single. */
              cb = ((-0.1482F * (real32_T)RBounded_Uint8->data[b_i] + -0.291F *
                     (real32_T)GBounded_Uint8->data[b_i]) + 0.4392F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* ith Cr channel element */
              /* Scalar; type single. */
              cr = ((0.4392F * (real32_T)RBounded_Uint8->data[b_i] + -0.3678F *
                     (real32_T)GBounded_Uint8->data[b_i]) + -0.0714F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* end function */
              /* Assign the ith y, cb, and cr values */
              YBounded_Single->data[b_i] = CbCrRatio_ith;
              CbBounded_Single->data[b_i] = cb;
              CrBounded_Single->data[b_i] = cr;

              /* Classify pixels within all thresholds as skin (true)        */
              if (IsSkinMask_ith) {
                if ((CbCrRatio_ith > YMin) && (CbCrRatio_ith < YMax) && (cb >
                     CbMin) && (cb < CbMax) && (cr > CrMin) && (cr < CrMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }
              }

              if (IsSkinMask_ith) {
                /* Calculate Cb-to-Cr ratio */
                /* Type single to permit division to return fractions. */
                /* Note: for efficiency, the output is assigned to a previously assigned  */
                /* variable. */
                out = cb / cr;
                if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                  IsSkinMask_ith = false;
                }
              }

              IsSkinMask->data[b_i] = IsSkinMask_ith;
            }

            /* Index using subscript indices */
          } else {
            i = (XOffset + NCols_Matrix) - 1;
            for (b_i = XOffset; b_i <= i; b_i++) {
              i1 = (YOffset + NRows_Matrix) - 1;
              for (j = YOffset; j <= i1; j++) {
                /* Indices for output matrices */
                YAdjust = j - YOffset;
                XAdjust = b_i - XOffset;

                /* Extract and cast to type single the ith r, g, and b values */
                /* Scalars; type single. */
                c1 = RBounded_Uint8->data[(j + RBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c2 = GBounded_Uint8->data[(j + GBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c3 = BBounded_Uint8->data[(j + BBounded_Uint8->size[0] * (b_i -
                  1)) - 1];

                /* Apply rgb-to-hs algorithm */
                /* Scalars; type single. */
                /* Note: rgb2hs is a custom function located within folder 'FacePulseRate'.  */
                /*  h; named "out" because later reassigned with different value */
                /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                /*           channels of the HSV colorspace.  */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*                     */
                /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                /*     colorspace.  */
                /*  */
                /*     Notes: */
                /*  */
                /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                /*     code generation. As of Matlab version 2020a, the file location is  */
                /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                /*  */
                /*     References: */
                /*  */
                /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                /*     19. */
                /* Inline function */
                /* Maximum channel value */
                if ((c1 > c2) && (c1 > c3)) {
                  v = c1;
                } else {
                  v = muIntScalarMax_sint32(c2, c3);
                }

                /* Minimum channel value */
                if ((c1 < c2) && (c1 < c3)) {
                  l = c1;
                } else {
                  l = muIntScalarMin_sint32(c2, c3);
                }

                /* Difference between maximum and minimum values */
                l = v - l;

                /* Determine value of hue channel (h) */
                if (l == 0) {
                  out = 0.0F;
                } else if (c3 == v) {
                  out = ((real32_T)(c1 - c2) / (real32_T)l + 4.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c1 == v) {
                  out = (real32_T)(c2 - c3) / (real32_T)l / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c2 == v) {
                  out = ((real32_T)(c3 - c1) / (real32_T)l + 2.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else {
                  out = 0.0F;
                }

                if (v == 0) {
                  s = 0.0F;
                } else if (l == 0) {
                  s = 0.0F;
                } else {
                  s = (real32_T)l / (real32_T)v;
                }

                /* end function */
                if ((out < HMax) && (s > SMin) && (s < SMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                /* Apply the RGB-to-YCbCr algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the outputs replace the inputs. */
                /* Note: rgb2ycbcr_compute is a custom function located within folder  */
                /* 'FacePulseRate'.       */
                /*  y */
                /*  cb */
                /*  cr */
                /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                CbCrRatio_ith = ((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)
                                  c2) + 0.0979F * (real32_T)c3) + 16.0F;

                /* ith Cb channel element */
                /* Scalar; type single. */
                cb = ((-0.1482F * (real32_T)c1 + -0.291F * (real32_T)c2) +
                      0.4392F * (real32_T)c3) + 128.0F;

                /* ith Cr channel element */
                /* Scalar; type single. */
                cr = ((0.4392F * (real32_T)c1 + -0.3678F * (real32_T)c2) +
                      -0.0714F * (real32_T)c3) + 128.0F;

                /* end function */
                /* Assign the ith y, cb, and cr values */
                YBounded_Single->data[YAdjust + YBounded_Single->size[0] *
                  XAdjust] = CbCrRatio_ith;
                CbBounded_Single->data[YAdjust + CbBounded_Single->size[0] *
                  XAdjust] = cb;
                CrBounded_Single->data[YAdjust + CrBounded_Single->size[0] *
                  XAdjust] = cr;

                /* Classify pixels within all thresholds as skin (true)        */
                if (IsSkinMask_ith) {
                  if ((CbCrRatio_ith > YMin) && (CbCrRatio_ith < YMax) && (cb >
                       CbMin) && (cb < CbMax) && (cr > CrMin) && (cr < CrMax)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }
                }

                if (IsSkinMask_ith) {
                  /* Calculate Cb-to-Cr ratio */
                  /* Type single to permit division to return fractions. */
                  /* Note: for efficiency, the output is assigned to a previously assigned  */
                  /* variable. */
                  out = cb / cr;
                  if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                    IsSkinMask_ith = false;
                  }
                }

                IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                  IsSkinMask_ith;
              }
            }
          }
        }
      }

      /* %%%%% >>>>>> Return the H- and S-channel matrices from the HSV colorspace %%%%%%   */
    } else {
      /* Preallocate H- and S-channel outputs */
      /* M x N matrix; type single. */
      i = HBounded_Single->size[0] * HBounded_Single->size[1];
      HBounded_Single->size[0] = NRows_Matrix;
      HBounded_Single->size[1] = NCols_Matrix;
      emxEnsureCapacity_real32_T(HBounded_Single, i);
      i = SBounded_Single->size[0] * SBounded_Single->size[1];
      SBounded_Single->size[0] = NRows_Matrix;
      SBounded_Single->size[1] = NCols_Matrix;
      emxEnsureCapacity_real32_T(SBounded_Single, i);

      /* Do not use tailored thresholds */
      if ((!TailoredThresholdsTF) || DontUseTailoredTF) {
        /* (7) Condition 7        */
        /*  - Use generic thresholds: generic YCbCr and HS thresholds. */
        /*  - Return H and S channel matrices. */
        /*  - Do not return matrices of the Y, Cb, or Cr channels.        */
        if ((!ReturnCbCrTF) && (!ReturnYTF)) {
          /* M x N matrices; type single. */
          YBounded_Single->size[0] = 0;
          YBounded_Single->size[1] = 0;
          CbBounded_Single->size[0] = 0;
          CbBounded_Single->size[1] = 0;
          CrBounded_Single->size[0] = 0;
          CrBounded_Single->size[1] = 0;

          /* Index using a linear index */
          if (UseLinIdxTF) {
            /* Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm */
            for (b_i = 0; b_i < NElements_Matrix; b_i++) {
              /* Extract and cast to type single the ith r, g, and b values */
              /* Scalars; type single. */
              /* Apply rgb-to-hs algorithm */
              /* Scalars; type single. */
              /* Note: rgb2hs is a custom function located within folder 'FacePulseRate'.   */
              /*  h; named "out" because later reassigned with different value */
              /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
              /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
              /*           channels of the HSV colorspace.  */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Description: */
              /*                     */
              /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
              /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
              /*     colorspace.  */
              /*  */
              /*     Notes: */
              /*  */
              /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
              /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
              /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
              /*     code generation. As of Matlab version 2020a, the file location is  */
              /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
              /*  */
              /*     References: */
              /*  */
              /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
              /*     19. */
              /* Inline function */
              /* Maximum channel value */
              if ((RBounded_Uint8->data[b_i] > GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])) {
                v = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])
              {
                v = GBounded_Uint8->data[b_i];
              } else {
                v = BBounded_Uint8->data[b_i];
              }

              /* Minimum channel value */
              if ((RBounded_Uint8->data[b_i] < GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])) {
                l = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])
              {
                l = GBounded_Uint8->data[b_i];
              } else {
                l = BBounded_Uint8->data[b_i];
              }

              /* Difference between maximum and minimum values */
              l = v - l;

              /* Determine value of hue channel (h) */
              if (l == 0) {
                out = 0.0F;
              } else if (BBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(RBounded_Uint8->data[b_i] -
                                  GBounded_Uint8->data[b_i]) / (real32_T)l +
                       4.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (RBounded_Uint8->data[b_i] == v) {
                out = (real32_T)(GBounded_Uint8->data[b_i] -
                                 BBounded_Uint8->data[b_i]) / (real32_T)l / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (GBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(BBounded_Uint8->data[b_i] -
                                  RBounded_Uint8->data[b_i]) / (real32_T)l +
                       2.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else {
                out = 0.0F;
              }

              if (v == 0) {
                s = 0.0F;
              } else if (l == 0) {
                s = 0.0F;
              } else {
                s = (real32_T)l / (real32_T)v;
              }

              /* end function */
              /* Assign the ith h and s values to the H- and S-channel matrices */
              HBounded_Single->data[b_i] = out;
              SBounded_Single->data[b_i] = s;

              /* Apply the RGB-to-YCbCr algorithm */
              /* Scalars; type single. */
              /* Note: for efficiency, the outputs replace the inputs. */
              /* Note: rgb2ycbcr_compute is a custom function located within folder  */
              /* 'FacePulseRate'.        */
              /*  y */
              /*  cb */
              /*  cr */
              /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
              /*  */
              /*     Description: */
              /*  */
              /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*  */
              /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
              /*     derived from Poynton (1996, p. 175 - 176). */
              /*  */
              /*     Note: */
              /*  */
              /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     References: */
              /*  */
              /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
              /* Inline function */
              /* ith Y channel element */
              /* Scalar; type single. */
              /* ith Cb channel element */
              /* Scalar; type single. */
              cb = ((-0.1482F * (real32_T)RBounded_Uint8->data[b_i] + -0.291F *
                     (real32_T)GBounded_Uint8->data[b_i]) + 0.4392F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* ith Cr channel element */
              /* Scalar; type single. */
              cr = ((0.4392F * (real32_T)RBounded_Uint8->data[b_i] + -0.3678F *
                     (real32_T)GBounded_Uint8->data[b_i]) + -0.0714F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* end function */
              /* Classify pixels within all thresholds as skin (true)        */
              if ((((0.2568F * (real32_T)RBounded_Uint8->data[b_i] + 0.5041F *
                     (real32_T)GBounded_Uint8->data[b_i]) + 0.0979F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 16.0F > YMin) && (cb > CbMin) &&
                  (cb < CbMax) && (cr > CrMin) && (cr < CrMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              if (IsSkinMask_ith) {
                /* Classify pixels within all thresholds as skin (true)  */
                if ((out < HMax) && (s > SMin)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }
              }

              if (IsSkinMask_ith) {
                /* Calculate Cb-to-Cr ratio */
                /* Type single to permit division to return fractions. */
                /* Note: for efficiency, the output is assigned to a previously assigned  */
                /* variable. */
                out = cb / cr;
                if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                  IsSkinMask_ith = false;
                }
              }

              IsSkinMask->data[b_i] = IsSkinMask_ith;
            }

            /* Index using subscript indices */
          } else {
            i = (XOffset + NCols_Matrix) - 1;
            for (b_i = XOffset; b_i <= i; b_i++) {
              i1 = (YOffset + NRows_Matrix) - 1;
              for (j = YOffset; j <= i1; j++) {
                /* Indices for output matrices */
                YAdjust = j - YOffset;
                XAdjust = b_i - XOffset;

                /* Extract and cast to type single the ith r, g, and b values */
                /* Scalars; type single. */
                c1 = RBounded_Uint8->data[(j + RBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c2 = GBounded_Uint8->data[(j + GBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c3 = BBounded_Uint8->data[(j + BBounded_Uint8->size[0] * (b_i -
                  1)) - 1];

                /* Apply rgb-to-hs algorithm */
                /* Scalars; type single. */
                /* Note: rgb2hs is a custom function located within folder 'FacePulseRate'.   */
                /*  h; named "out" because later reassigned with different value */
                /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                /*           channels of the HSV colorspace.  */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*                     */
                /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                /*     colorspace.  */
                /*  */
                /*     Notes: */
                /*  */
                /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                /*     code generation. As of Matlab version 2020a, the file location is  */
                /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                /*  */
                /*     References: */
                /*  */
                /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                /*     19. */
                /* Inline function */
                /* Maximum channel value */
                if ((c1 > c2) && (c1 > c3)) {
                  v = c1;
                } else {
                  v = muIntScalarMax_sint32(c2, c3);
                }

                /* Minimum channel value */
                if ((c1 < c2) && (c1 < c3)) {
                  l = c1;
                } else {
                  l = muIntScalarMin_sint32(c2, c3);
                }

                /* Difference between maximum and minimum values */
                l = v - l;

                /* Determine value of hue channel (h) */
                if (l == 0) {
                  out = 0.0F;
                } else if (c3 == v) {
                  out = ((real32_T)(c1 - c2) / (real32_T)l + 4.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c1 == v) {
                  out = (real32_T)(c2 - c3) / (real32_T)l / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c2 == v) {
                  out = ((real32_T)(c3 - c1) / (real32_T)l + 2.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else {
                  out = 0.0F;
                }

                if (v == 0) {
                  s = 0.0F;
                } else if (l == 0) {
                  s = 0.0F;
                } else {
                  s = (real32_T)l / (real32_T)v;
                }

                /* end function */
                /* Assign the ith h and s values to the H- and S-channel matrices */
                HBounded_Single->data[YAdjust + HBounded_Single->size[0] *
                  XAdjust] = out;
                SBounded_Single->data[YAdjust + SBounded_Single->size[0] *
                  XAdjust] = s;

                /* Apply the RGB-to-YCbCr algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the outputs replace the inputs. */
                /* Note: rgb2ycbcr_compute is a custom function located within folder  */
                /* 'FacePulseRate'.        */
                /*  y */
                /*  cb */
                /*  cr */
                /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                /* ith Cb channel element */
                /* Scalar; type single. */
                cb = ((-0.1482F * (real32_T)c1 + -0.291F * (real32_T)c2) +
                      0.4392F * (real32_T)c3) + 128.0F;

                /* ith Cr channel element */
                /* Scalar; type single. */
                cr = ((0.4392F * (real32_T)c1 + -0.3678F * (real32_T)c2) +
                      -0.0714F * (real32_T)c3) + 128.0F;

                /* end function */
                /* Classify pixels within all thresholds as skin (true)        */
                if ((((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)c2) +
                      0.0979F * (real32_T)c3) + 16.0F > YMin) && (cb > CbMin) &&
                    (cb < CbMax) && (cr > CrMin) && (cr < CrMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                if (IsSkinMask_ith) {
                  /* Classify pixels within all thresholds as skin (true)  */
                  if ((out < HMax) && (s > SMin)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }
                }

                if (IsSkinMask_ith) {
                  /* Calculate Cb-to-Cr ratio */
                  /* Type single to permit division to return fractions. */
                  /* Note: for efficiency, the output is assigned to a previously assigned  */
                  /* variable. */
                  out = cb / cr;
                  if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                    IsSkinMask_ith = false;
                  }
                }

                IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                  IsSkinMask_ith;
              }
            }
          }

          /* (8) Condition 8                  */
          /*  - Use generic thresholds: generic YCbCr and HS thresholds. */
          /*  - Return H and S channel matrices. */
          /*  - Return Y-channel matrix but not the Cb and Cr channel matrices.        */
        } else if ((!ReturnCbCrTF) && ReturnYTF) {
          /* M x N matrices; type single. */
          i = YBounded_Single->size[0] * YBounded_Single->size[1];
          YBounded_Single->size[0] = NRows_Matrix;
          YBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(YBounded_Single, i);
          CbBounded_Single->size[0] = 0;
          CbBounded_Single->size[1] = 0;
          CrBounded_Single->size[0] = 0;
          CrBounded_Single->size[1] = 0;

          /* Index using a linear index */
          if (UseLinIdxTF) {
            /* Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm */
            for (b_i = 0; b_i < NElements_Matrix; b_i++) {
              /* Extract and cast to type single the ith r, g, and b values */
              /* Scalars; type single. */
              /* Apply rgb-to-hs algorithm */
              /* Scalars; type single. */
              /* Note: rgb2h is a custom function located within folder 'FacePulseRate'.   */
              /*  h; named "out" because later reassigned with different value */
              /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
              /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
              /*           channels of the HSV colorspace.  */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Description: */
              /*                     */
              /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
              /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
              /*     colorspace.  */
              /*  */
              /*     Notes: */
              /*  */
              /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
              /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
              /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
              /*     code generation. As of Matlab version 2020a, the file location is  */
              /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
              /*  */
              /*     References: */
              /*  */
              /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
              /*     19. */
              /* Inline function */
              /* Maximum channel value */
              if ((RBounded_Uint8->data[b_i] > GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])) {
                v = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])
              {
                v = GBounded_Uint8->data[b_i];
              } else {
                v = BBounded_Uint8->data[b_i];
              }

              /* Minimum channel value */
              if ((RBounded_Uint8->data[b_i] < GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])) {
                l = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])
              {
                l = GBounded_Uint8->data[b_i];
              } else {
                l = BBounded_Uint8->data[b_i];
              }

              /* Difference between maximum and minimum values */
              l = v - l;

              /* Determine value of hue channel (h) */
              if (l == 0) {
                out = 0.0F;
              } else if (BBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(RBounded_Uint8->data[b_i] -
                                  GBounded_Uint8->data[b_i]) / (real32_T)l +
                       4.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (RBounded_Uint8->data[b_i] == v) {
                out = (real32_T)(GBounded_Uint8->data[b_i] -
                                 BBounded_Uint8->data[b_i]) / (real32_T)l / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (GBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(BBounded_Uint8->data[b_i] -
                                  RBounded_Uint8->data[b_i]) / (real32_T)l +
                       2.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else {
                out = 0.0F;
              }

              if (v == 0) {
                s = 0.0F;
              } else if (l == 0) {
                s = 0.0F;
              } else {
                s = (real32_T)l / (real32_T)v;
              }

              /* end function */
              /* Assign the ith h and s values to the H- and S-channel matrices */
              HBounded_Single->data[b_i] = out;
              SBounded_Single->data[b_i] = s;

              /* Apply the RGB-to-YCbCr algorithm */
              /* Scalars; type single. */
              /* Note: for efficiency, the outputs replace the inputs. */
              /* Note: rgb2ycbcr_compute is a custom function located within folder  */
              /* 'FacePulseRate'.        */
              /*  y */
              /*  cb */
              /*  cr */
              /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
              /*  */
              /*     Description: */
              /*  */
              /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*  */
              /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
              /*     derived from Poynton (1996, p. 175 - 176). */
              /*  */
              /*     Note: */
              /*  */
              /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     References: */
              /*  */
              /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
              /* Inline function */
              /* ith Y channel element */
              /* Scalar; type single. */
              CbCrRatio_ith = ((0.2568F * (real32_T)RBounded_Uint8->data[b_i] +
                                0.5041F * (real32_T)GBounded_Uint8->data[b_i]) +
                               0.0979F * (real32_T)BBounded_Uint8->data[b_i]) +
                16.0F;

              /* ith Cb channel element */
              /* Scalar; type single. */
              cb = ((-0.1482F * (real32_T)RBounded_Uint8->data[b_i] + -0.291F *
                     (real32_T)GBounded_Uint8->data[b_i]) + 0.4392F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* ith Cr channel element */
              /* Scalar; type single. */
              cr = ((0.4392F * (real32_T)RBounded_Uint8->data[b_i] + -0.3678F *
                     (real32_T)GBounded_Uint8->data[b_i]) + -0.0714F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* end function */
              /* Assign the ith y value */
              YBounded_Single->data[b_i] = CbCrRatio_ith;

              /* Classify pixels within all thresholds as skin (true)        */
              if ((CbCrRatio_ith > YMin) && (cb > CbMin) && (cb < CbMax) && (cr >
                   CrMin) && (cr < CrMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              if (IsSkinMask_ith) {
                /* Classify pixels within all thresholds as skin (true)  */
                if ((out < HMax) && (s > SMin)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }
              }

              if (IsSkinMask_ith) {
                /* Calculate Cb-to-Cr ratio */
                /* Type single to permit division to return fractions. */
                /* Note: for efficiency, the output is assigned to a previously assigned  */
                /* variable. */
                out = cb / cr;
                if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                  IsSkinMask_ith = false;
                }
              }

              IsSkinMask->data[b_i] = IsSkinMask_ith;
            }

            /* Index using subscript indices */
          } else {
            i = (XOffset + NCols_Matrix) - 1;
            for (b_i = XOffset; b_i <= i; b_i++) {
              i1 = (YOffset + NRows_Matrix) - 1;
              for (j = YOffset; j <= i1; j++) {
                /* Indices for output matrices */
                YAdjust = j - YOffset;
                XAdjust = b_i - XOffset;

                /* Extract and cast to type single the ith r, g, and b values */
                /* Scalars; type single. */
                c1 = RBounded_Uint8->data[(j + RBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c2 = GBounded_Uint8->data[(j + GBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c3 = BBounded_Uint8->data[(j + BBounded_Uint8->size[0] * (b_i -
                  1)) - 1];

                /* Apply rgb-to-hs algorithm */
                /* Scalars; type single. */
                /* Note: rgb2h is a custom function located within folder 'FacePulseRate'.   */
                /*  h; named "out" because later reassigned with different value */
                /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                /*           channels of the HSV colorspace.  */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*                     */
                /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                /*     colorspace.  */
                /*  */
                /*     Notes: */
                /*  */
                /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                /*     code generation. As of Matlab version 2020a, the file location is  */
                /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                /*  */
                /*     References: */
                /*  */
                /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                /*     19. */
                /* Inline function */
                /* Maximum channel value */
                if ((c1 > c2) && (c1 > c3)) {
                  v = c1;
                } else {
                  v = muIntScalarMax_sint32(c2, c3);
                }

                /* Minimum channel value */
                if ((c1 < c2) && (c1 < c3)) {
                  l = c1;
                } else {
                  l = muIntScalarMin_sint32(c2, c3);
                }

                /* Difference between maximum and minimum values */
                l = v - l;

                /* Determine value of hue channel (h) */
                if (l == 0) {
                  out = 0.0F;
                } else if (c3 == v) {
                  out = ((real32_T)(c1 - c2) / (real32_T)l + 4.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c1 == v) {
                  out = (real32_T)(c2 - c3) / (real32_T)l / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c2 == v) {
                  out = ((real32_T)(c3 - c1) / (real32_T)l + 2.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else {
                  out = 0.0F;
                }

                if (v == 0) {
                  s = 0.0F;
                } else if (l == 0) {
                  s = 0.0F;
                } else {
                  s = (real32_T)l / (real32_T)v;
                }

                /* end function */
                /* Assign the ith h and s values to the H- and S-channel matrices */
                HBounded_Single->data[YAdjust + HBounded_Single->size[0] *
                  XAdjust] = out;
                SBounded_Single->data[YAdjust + SBounded_Single->size[0] *
                  XAdjust] = s;

                /* Apply the RGB-to-YCbCr algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the outputs replace the inputs. */
                /* Note: rgb2ycbcr_compute is a custom function located within folder  */
                /* 'FacePulseRate'.        */
                /*  y */
                /*  cb */
                /*  cr */
                /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                CbCrRatio_ith = ((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)
                                  c2) + 0.0979F * (real32_T)c3) + 16.0F;

                /* ith Cb channel element */
                /* Scalar; type single. */
                cb = ((-0.1482F * (real32_T)c1 + -0.291F * (real32_T)c2) +
                      0.4392F * (real32_T)c3) + 128.0F;

                /* ith Cr channel element */
                /* Scalar; type single. */
                cr = ((0.4392F * (real32_T)c1 + -0.3678F * (real32_T)c2) +
                      -0.0714F * (real32_T)c3) + 128.0F;

                /* end function */
                /* Assign the ith y value */
                YBounded_Single->data[YAdjust + YBounded_Single->size[0] *
                  XAdjust] = CbCrRatio_ith;

                /* Classify pixels within all thresholds as skin (true)        */
                if ((CbCrRatio_ith > YMin) && (cb > CbMin) && (cb < CbMax) &&
                    (cr > CrMin) && (cr < CrMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                if (IsSkinMask_ith) {
                  /* Classify pixels within all thresholds as skin (true)  */
                  if ((out < HMax) && (s > SMin)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }
                }

                if (IsSkinMask_ith) {
                  /* Calculate Cb-to-Cr ratio */
                  /* Type single to permit division to return fractions. */
                  /* Note: for efficiency, the output is assigned to a previously assigned  */
                  /* variable. */
                  out = cb / cr;
                  if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                    IsSkinMask_ith = false;
                  }
                }

                IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                  IsSkinMask_ith;
              }
            }
          }

          /* (9) Condition 9                  */
          /*  - Use generic thresholds: generic YCbCr and HS thresholds. */
          /*  - Return H and S channel matrices. */
          /*  - Return the YCbCr matrices.        */
        } else {
          /* M x N matrices; type single. */
          i = YBounded_Single->size[0] * YBounded_Single->size[1];
          YBounded_Single->size[0] = NRows_Matrix;
          YBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(YBounded_Single, i);
          i = CbBounded_Single->size[0] * CbBounded_Single->size[1];
          CbBounded_Single->size[0] = NRows_Matrix;
          CbBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(CbBounded_Single, i);
          i = CrBounded_Single->size[0] * CrBounded_Single->size[1];
          CrBounded_Single->size[0] = NRows_Matrix;
          CrBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(CrBounded_Single, i);

          /* Index using a linear index */
          if (UseLinIdxTF) {
            /* Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm */
            for (b_i = 0; b_i < NElements_Matrix; b_i++) {
              /* Extract and cast to type single the ith r, g, and b values */
              /* Scalars; type single. */
              /* Apply rgb-to-hs algorithm */
              /* Scalars; type single. */
              /* Note: rgb2hse is a custom function located within folder 'FacePulseRate'.  */
              /*  h; named "out" because later reassigned with different value */
              /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
              /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
              /*           channels of the HSV colorspace.  */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Description: */
              /*                     */
              /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
              /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
              /*     colorspace.  */
              /*  */
              /*     Notes: */
              /*  */
              /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
              /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
              /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
              /*     code generation. As of Matlab version 2020a, the file location is  */
              /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
              /*  */
              /*     References: */
              /*  */
              /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
              /*     19. */
              /* Inline function */
              /* Maximum channel value */
              if ((RBounded_Uint8->data[b_i] > GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])) {
                v = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])
              {
                v = GBounded_Uint8->data[b_i];
              } else {
                v = BBounded_Uint8->data[b_i];
              }

              /* Minimum channel value */
              if ((RBounded_Uint8->data[b_i] < GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])) {
                l = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])
              {
                l = GBounded_Uint8->data[b_i];
              } else {
                l = BBounded_Uint8->data[b_i];
              }

              /* Difference between maximum and minimum values */
              l = v - l;

              /* Determine value of hue channel (h) */
              if (l == 0) {
                out = 0.0F;
              } else if (BBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(RBounded_Uint8->data[b_i] -
                                  GBounded_Uint8->data[b_i]) / (real32_T)l +
                       4.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (RBounded_Uint8->data[b_i] == v) {
                out = (real32_T)(GBounded_Uint8->data[b_i] -
                                 BBounded_Uint8->data[b_i]) / (real32_T)l / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (GBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(BBounded_Uint8->data[b_i] -
                                  RBounded_Uint8->data[b_i]) / (real32_T)l +
                       2.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else {
                out = 0.0F;
              }

              if (v == 0) {
                s = 0.0F;
              } else if (l == 0) {
                s = 0.0F;
              } else {
                s = (real32_T)l / (real32_T)v;
              }

              /* end function */
              /* Assign the ith h and s values to the H- and S-channel matrices */
              HBounded_Single->data[b_i] = out;
              SBounded_Single->data[b_i] = s;

              /* Apply the RGB-to-YCbCr algorithm */
              /* Scalars; type single. */
              /* Note: for efficiency, the outputs replace the inputs. */
              /* Note: rgb2ycbcr_compute is a custom function located within folder  */
              /* 'FacePulseRate'.        */
              /*  y */
              /*  cb */
              /*  cr */
              /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
              /*  */
              /*     Description: */
              /*  */
              /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*  */
              /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
              /*     derived from Poynton (1996, p. 175 - 176). */
              /*  */
              /*     Note: */
              /*  */
              /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     References: */
              /*  */
              /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
              /* Inline function */
              /* ith Y channel element */
              /* Scalar; type single. */
              CbCrRatio_ith = ((0.2568F * (real32_T)RBounded_Uint8->data[b_i] +
                                0.5041F * (real32_T)GBounded_Uint8->data[b_i]) +
                               0.0979F * (real32_T)BBounded_Uint8->data[b_i]) +
                16.0F;

              /* ith Cb channel element */
              /* Scalar; type single. */
              cb = ((-0.1482F * (real32_T)RBounded_Uint8->data[b_i] + -0.291F *
                     (real32_T)GBounded_Uint8->data[b_i]) + 0.4392F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* ith Cr channel element */
              /* Scalar; type single. */
              cr = ((0.4392F * (real32_T)RBounded_Uint8->data[b_i] + -0.3678F *
                     (real32_T)GBounded_Uint8->data[b_i]) + -0.0714F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* end function */
              /* Assign the ith y, cb, and cr values */
              YBounded_Single->data[b_i] = CbCrRatio_ith;
              CbBounded_Single->data[b_i] = cb;
              CrBounded_Single->data[b_i] = cr;

              /* Classify pixels within all thresholds as skin (true)        */
              if ((CbCrRatio_ith > YMin) && (cb > CbMin) && (cb < CbMax) && (cr >
                   CrMin) && (cr < CrMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              if (IsSkinMask_ith) {
                /* Classify pixels within all thresholds as skin (true)  */
                if ((out < HMax) && (s > SMin)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }
              }

              if (IsSkinMask_ith) {
                /* Calculate Cb-to-Cr ratio */
                /* Type single to permit division to return fractions. */
                /* Note: for efficiency, the output is assigned to a previously assigned  */
                /* variable. */
                out = cb / cr;
                if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                  IsSkinMask_ith = false;
                }
              }

              IsSkinMask->data[b_i] = IsSkinMask_ith;
            }

            /* Index using subscript indices */
          } else {
            i = (XOffset + NCols_Matrix) - 1;
            for (b_i = XOffset; b_i <= i; b_i++) {
              i1 = (YOffset + NRows_Matrix) - 1;
              for (j = YOffset; j <= i1; j++) {
                /* Indices for output matrices */
                YAdjust = j - YOffset;
                XAdjust = b_i - XOffset;

                /* Extract and cast to type single the ith r, g, and b values */
                /* Scalars; type single. */
                c1 = RBounded_Uint8->data[(j + RBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c2 = GBounded_Uint8->data[(j + GBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c3 = BBounded_Uint8->data[(j + BBounded_Uint8->size[0] * (b_i -
                  1)) - 1];

                /* Apply rgb-to-hs algorithm */
                /* Scalars; type single. */
                /* Note: rgb2hse is a custom function located within folder 'FacePulseRate'.  */
                /*  h; named "out" because later reassigned with different value */
                /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                /*           channels of the HSV colorspace.  */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*                     */
                /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                /*     colorspace.  */
                /*  */
                /*     Notes: */
                /*  */
                /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                /*     code generation. As of Matlab version 2020a, the file location is  */
                /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                /*  */
                /*     References: */
                /*  */
                /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                /*     19. */
                /* Inline function */
                /* Maximum channel value */
                if ((c1 > c2) && (c1 > c3)) {
                  v = c1;
                } else {
                  v = muIntScalarMax_sint32(c2, c3);
                }

                /* Minimum channel value */
                if ((c1 < c2) && (c1 < c3)) {
                  l = c1;
                } else {
                  l = muIntScalarMin_sint32(c2, c3);
                }

                /* Difference between maximum and minimum values */
                l = v - l;

                /* Determine value of hue channel (h) */
                if (l == 0) {
                  out = 0.0F;
                } else if (c3 == v) {
                  out = ((real32_T)(c1 - c2) / (real32_T)l + 4.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c1 == v) {
                  out = (real32_T)(c2 - c3) / (real32_T)l / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c2 == v) {
                  out = ((real32_T)(c3 - c1) / (real32_T)l + 2.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else {
                  out = 0.0F;
                }

                if (v == 0) {
                  s = 0.0F;
                } else if (l == 0) {
                  s = 0.0F;
                } else {
                  s = (real32_T)l / (real32_T)v;
                }

                /* end function */
                /* Assign the ith h and s values to the H- and S-channel matrices */
                HBounded_Single->data[YAdjust + HBounded_Single->size[0] *
                  XAdjust] = out;
                SBounded_Single->data[YAdjust + SBounded_Single->size[0] *
                  XAdjust] = s;

                /* Apply the RGB-to-YCbCr algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the outputs replace the inputs. */
                /* Note: rgb2ycbcr_compute is a custom function located within folder  */
                /* 'FacePulseRate'.        */
                /*  y */
                /*  cb */
                /*  cr */
                /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                CbCrRatio_ith = ((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)
                                  c2) + 0.0979F * (real32_T)c3) + 16.0F;

                /* ith Cb channel element */
                /* Scalar; type single. */
                cb = ((-0.1482F * (real32_T)c1 + -0.291F * (real32_T)c2) +
                      0.4392F * (real32_T)c3) + 128.0F;

                /* ith Cr channel element */
                /* Scalar; type single. */
                cr = ((0.4392F * (real32_T)c1 + -0.3678F * (real32_T)c2) +
                      -0.0714F * (real32_T)c3) + 128.0F;

                /* end function */
                /* Assign the ith y, cb, and cr values */
                YBounded_Single->data[YAdjust + YBounded_Single->size[0] *
                  XAdjust] = CbCrRatio_ith;
                CbBounded_Single->data[YAdjust + CbBounded_Single->size[0] *
                  XAdjust] = cb;
                CrBounded_Single->data[YAdjust + CrBounded_Single->size[0] *
                  XAdjust] = cr;

                /* Classify pixels within all thresholds as skin (true)        */
                if ((CbCrRatio_ith > YMin) && (cb > CbMin) && (cb < CbMax) &&
                    (cr > CrMin) && (cr < CrMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                if (IsSkinMask_ith) {
                  /* Classify pixels within all thresholds as skin (true)  */
                  if ((out < HMax) && (s > SMin)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }
                }

                if (IsSkinMask_ith) {
                  /* Calculate Cb-to-Cr ratio */
                  /* Type single to permit division to return fractions. */
                  /* Note: for efficiency, the output is assigned to a previously assigned  */
                  /* variable. */
                  out = cb / cr;
                  if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                    IsSkinMask_ith = false;
                  }
                }

                IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                  IsSkinMask_ith;
              }
            }
          }
        }

        /* Use tailored thresholds         */
      } else {
        /* (10) Condition 10  */
        /*  - Use tailored thresholds: tailored YCbCr thresholds and tailored HS thresholds. */
        /*  - Return matrices of the H and S channels. */
        /*  - Do not return YCbCr matrices.             */
        if ((!ReturnCbCrTF) && (!ReturnYTF)) {
          /* M x N matrix; type single. */
          YBounded_Single->size[0] = 0;
          YBounded_Single->size[1] = 0;
          CbBounded_Single->size[0] = 0;
          CbBounded_Single->size[1] = 0;
          CrBounded_Single->size[0] = 0;
          CrBounded_Single->size[1] = 0;

          /* Index using a linear index */
          if (UseLinIdxTF) {
            /* Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm */
            for (b_i = 0; b_i < NElements_Matrix; b_i++) {
              /* Extract and cast to type single the ith r, g, and b values */
              /* Scalars; type single. */
              /* Apply rgb-to-h algorithm */
              /* Scalars; type single. */
              /* Note: rgb2hs is a custom function located within folder 'FacePulseRate'.  */
              /*  h; named "out" because later reassigned with different value */
              /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
              /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
              /*           channels of the HSV colorspace.  */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Description: */
              /*                     */
              /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
              /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
              /*     colorspace.  */
              /*  */
              /*     Notes: */
              /*  */
              /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
              /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
              /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
              /*     code generation. As of Matlab version 2020a, the file location is  */
              /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
              /*  */
              /*     References: */
              /*  */
              /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
              /*     19. */
              /* Inline function */
              /* Maximum channel value */
              if ((RBounded_Uint8->data[b_i] > GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])) {
                v = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])
              {
                v = GBounded_Uint8->data[b_i];
              } else {
                v = BBounded_Uint8->data[b_i];
              }

              /* Minimum channel value */
              if ((RBounded_Uint8->data[b_i] < GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])) {
                l = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])
              {
                l = GBounded_Uint8->data[b_i];
              } else {
                l = BBounded_Uint8->data[b_i];
              }

              /* Difference between maximum and minimum values */
              l = v - l;

              /* Determine value of hue channel (h) */
              if (l == 0) {
                out = 0.0F;
              } else if (BBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(RBounded_Uint8->data[b_i] -
                                  GBounded_Uint8->data[b_i]) / (real32_T)l +
                       4.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (RBounded_Uint8->data[b_i] == v) {
                out = (real32_T)(GBounded_Uint8->data[b_i] -
                                 BBounded_Uint8->data[b_i]) / (real32_T)l / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (GBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(BBounded_Uint8->data[b_i] -
                                  RBounded_Uint8->data[b_i]) / (real32_T)l +
                       2.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else {
                out = 0.0F;
              }

              if (v == 0) {
                s = 0.0F;
              } else if (l == 0) {
                s = 0.0F;
              } else {
                s = (real32_T)l / (real32_T)v;
              }

              /* end function */
              /* Assign the ith h and s values to the H- and S-channel matrices */
              HBounded_Single->data[b_i] = out;
              SBounded_Single->data[b_i] = s;
              if ((out < HMax) && (s > SMin) && (s < SMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              /* Apply the RGB-to-YCbCr algorithm */
              /* Scalars; type single. */
              /* Note: for efficiency, the outputs replace the inputs. */
              /* Note: rgb2ycbcr_compute is a custom function located within folder  */
              /* 'FacePulseRate'.    */
              /*  y */
              /*  cb */
              /*  cr */
              /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
              /*  */
              /*     Description: */
              /*  */
              /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*  */
              /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
              /*     derived from Poynton (1996, p. 175 - 176). */
              /*  */
              /*     Note: */
              /*  */
              /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     References: */
              /*  */
              /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
              /* Inline function */
              /* ith Y channel element */
              /* Scalar; type single. */
              CbCrRatio_ith = ((0.2568F * (real32_T)RBounded_Uint8->data[b_i] +
                                0.5041F * (real32_T)GBounded_Uint8->data[b_i]) +
                               0.0979F * (real32_T)BBounded_Uint8->data[b_i]) +
                16.0F;

              /* ith Cb channel element */
              /* Scalar; type single. */
              cb = ((-0.1482F * (real32_T)RBounded_Uint8->data[b_i] + -0.291F *
                     (real32_T)GBounded_Uint8->data[b_i]) + 0.4392F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* ith Cr channel element */
              /* Scalar; type single. */
              cr = ((0.4392F * (real32_T)RBounded_Uint8->data[b_i] + -0.3678F *
                     (real32_T)GBounded_Uint8->data[b_i]) + -0.0714F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* end function */
              /* Classify pixels within all thresholds as skin (true)        */
              if (IsSkinMask_ith) {
                if ((CbCrRatio_ith > YMin) && (CbCrRatio_ith < YMax) && (cb >
                     CbMin) && (cb < CbMax) && (cr > CrMin) && (cr < CrMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }
              }

              if (IsSkinMask_ith) {
                /* Calculate Cb-to-Cr ratio */
                /* Type single to permit division to return fractions. */
                /* Note: for efficiency, the output is assigned to a previously assigned  */
                /* variable. */
                out = cb / cr;
                if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                  IsSkinMask_ith = false;
                }
              }

              IsSkinMask->data[b_i] = IsSkinMask_ith;
            }

            /* Index using subscript indices */
          } else {
            i = (XOffset + NCols_Matrix) - 1;
            for (b_i = XOffset; b_i <= i; b_i++) {
              i1 = (YOffset + NRows_Matrix) - 1;
              for (j = YOffset; j <= i1; j++) {
                /* Indices for output matrices */
                YAdjust = j - YOffset;
                XAdjust = b_i - XOffset;

                /* Extract and cast to type single the ith r, g, and b values */
                /* Scalars; type single. */
                c1 = RBounded_Uint8->data[(j + RBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c2 = GBounded_Uint8->data[(j + GBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c3 = BBounded_Uint8->data[(j + BBounded_Uint8->size[0] * (b_i -
                  1)) - 1];

                /* Apply rgb-to-h algorithm */
                /* Scalars; type single. */
                /* Note: rgb2hs is a custom function located within folder 'FacePulseRate'.  */
                /*  h; named "out" because later reassigned with different value */
                /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                /*           channels of the HSV colorspace.  */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*                     */
                /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                /*     colorspace.  */
                /*  */
                /*     Notes: */
                /*  */
                /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                /*     code generation. As of Matlab version 2020a, the file location is  */
                /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                /*  */
                /*     References: */
                /*  */
                /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                /*     19. */
                /* Inline function */
                /* Maximum channel value */
                if ((c1 > c2) && (c1 > c3)) {
                  v = c1;
                } else {
                  v = muIntScalarMax_sint32(c2, c3);
                }

                /* Minimum channel value */
                if ((c1 < c2) && (c1 < c3)) {
                  l = c1;
                } else {
                  l = muIntScalarMin_sint32(c2, c3);
                }

                /* Difference between maximum and minimum values */
                l = v - l;

                /* Determine value of hue channel (h) */
                if (l == 0) {
                  out = 0.0F;
                } else if (c3 == v) {
                  out = ((real32_T)(c1 - c2) / (real32_T)l + 4.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c1 == v) {
                  out = (real32_T)(c2 - c3) / (real32_T)l / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c2 == v) {
                  out = ((real32_T)(c3 - c1) / (real32_T)l + 2.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else {
                  out = 0.0F;
                }

                if (v == 0) {
                  s = 0.0F;
                } else if (l == 0) {
                  s = 0.0F;
                } else {
                  s = (real32_T)l / (real32_T)v;
                }

                /* end function */
                /* Assign the ith h and s values to the H- and S-channel matrices */
                HBounded_Single->data[YAdjust + HBounded_Single->size[0] *
                  XAdjust] = out;
                SBounded_Single->data[YAdjust + SBounded_Single->size[0] *
                  XAdjust] = s;
                if ((out < HMax) && (s > SMin) && (s < SMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                /* Apply the RGB-to-YCbCr algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the outputs replace the inputs. */
                /* Note: rgb2ycbcr_compute is a custom function located within folder  */
                /* 'FacePulseRate'.    */
                /*  y */
                /*  cb */
                /*  cr */
                /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                CbCrRatio_ith = ((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)
                                  c2) + 0.0979F * (real32_T)c3) + 16.0F;

                /* ith Cb channel element */
                /* Scalar; type single. */
                cb = ((-0.1482F * (real32_T)c1 + -0.291F * (real32_T)c2) +
                      0.4392F * (real32_T)c3) + 128.0F;

                /* ith Cr channel element */
                /* Scalar; type single. */
                cr = ((0.4392F * (real32_T)c1 + -0.3678F * (real32_T)c2) +
                      -0.0714F * (real32_T)c3) + 128.0F;

                /* end function */
                /* Classify pixels within all thresholds as skin (true)        */
                if (IsSkinMask_ith) {
                  if ((CbCrRatio_ith > YMin) && (CbCrRatio_ith < YMax) && (cb >
                       CbMin) && (cb < CbMax) && (cr > CrMin) && (cr < CrMax)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }
                }

                if (IsSkinMask_ith) {
                  /* Calculate Cb-to-Cr ratio */
                  /* Type single to permit division to return fractions. */
                  /* Note: for efficiency, the output is assigned to a previously assigned  */
                  /* variable. */
                  out = cb / cr;
                  if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                    IsSkinMask_ith = false;
                  }
                }

                IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                  IsSkinMask_ith;
              }
            }
          }

          /* (11) Condition 11  */
          /*  - Use tailored thresholds: tailored YCbCr thresholds and tailored HS thresholds. */
          /*  - Return matrices of the H and S channels. */
          /*  - Return Y-channel matrix but not the Cb and Cr channel matrices.         */
        } else if ((!ReturnCbCrTF) && ReturnYTF) {
          /* M x N matrix; type single. */
          i = YBounded_Single->size[0] * YBounded_Single->size[1];
          YBounded_Single->size[0] = NRows_Matrix;
          YBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(YBounded_Single, i);
          CbBounded_Single->size[0] = 0;
          CbBounded_Single->size[1] = 0;
          CrBounded_Single->size[0] = 0;
          CrBounded_Single->size[1] = 0;

          /* Index using a linear index */
          if (UseLinIdxTF) {
            /* Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm */
            for (b_i = 0; b_i < NElements_Matrix; b_i++) {
              /* Extract and cast to type single the ith r, g, and b values */
              /* Scalars; type single. */
              /* Apply rgb-to-h algorithm */
              /* Scalars; type single. */
              /* Note: rgb2hse is a custom function located within folder 'FacePulseRate'.  */
              /*  h; named "out" because later reassigned with different value */
              /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
              /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
              /*           channels of the HSV colorspace.  */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Description: */
              /*                     */
              /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
              /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
              /*     colorspace.  */
              /*  */
              /*     Notes: */
              /*  */
              /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
              /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
              /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
              /*     code generation. As of Matlab version 2020a, the file location is  */
              /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
              /*  */
              /*     References: */
              /*  */
              /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
              /*     19. */
              /* Inline function */
              /* Maximum channel value */
              if ((RBounded_Uint8->data[b_i] > GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])) {
                v = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])
              {
                v = GBounded_Uint8->data[b_i];
              } else {
                v = BBounded_Uint8->data[b_i];
              }

              /* Minimum channel value */
              if ((RBounded_Uint8->data[b_i] < GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])) {
                l = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])
              {
                l = GBounded_Uint8->data[b_i];
              } else {
                l = BBounded_Uint8->data[b_i];
              }

              /* Difference between maximum and minimum values */
              l = v - l;

              /* Determine value of hue channel (h) */
              if (l == 0) {
                out = 0.0F;
              } else if (BBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(RBounded_Uint8->data[b_i] -
                                  GBounded_Uint8->data[b_i]) / (real32_T)l +
                       4.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (RBounded_Uint8->data[b_i] == v) {
                out = (real32_T)(GBounded_Uint8->data[b_i] -
                                 BBounded_Uint8->data[b_i]) / (real32_T)l / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (GBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(BBounded_Uint8->data[b_i] -
                                  RBounded_Uint8->data[b_i]) / (real32_T)l +
                       2.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else {
                out = 0.0F;
              }

              if (v == 0) {
                s = 0.0F;
              } else if (l == 0) {
                s = 0.0F;
              } else {
                s = (real32_T)l / (real32_T)v;
              }

              /* end function */
              /* Assign the ith h and s values to the H- and S-channel matrices */
              HBounded_Single->data[b_i] = out;
              SBounded_Single->data[b_i] = s;
              if ((out < HMax) && (s > SMin) && (s < SMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              /* Apply the RGB-to-YCbCr algorithm */
              /* Scalars; type single. */
              /* Note: for efficiency, the outputs replace the inputs. */
              /* Note: rgb2ycbcr_compute is a custom function located within folder  */
              /* 'FacePulseRate'.        */
              /*  y */
              /*  cb */
              /*  cr */
              /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
              /*  */
              /*     Description: */
              /*  */
              /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*  */
              /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
              /*     derived from Poynton (1996, p. 175 - 176). */
              /*  */
              /*     Note: */
              /*  */
              /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     References: */
              /*  */
              /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
              /* Inline function */
              /* ith Y channel element */
              /* Scalar; type single. */
              CbCrRatio_ith = ((0.2568F * (real32_T)RBounded_Uint8->data[b_i] +
                                0.5041F * (real32_T)GBounded_Uint8->data[b_i]) +
                               0.0979F * (real32_T)BBounded_Uint8->data[b_i]) +
                16.0F;

              /* ith Cb channel element */
              /* Scalar; type single. */
              cb = ((-0.1482F * (real32_T)RBounded_Uint8->data[b_i] + -0.291F *
                     (real32_T)GBounded_Uint8->data[b_i]) + 0.4392F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* ith Cr channel element */
              /* Scalar; type single. */
              cr = ((0.4392F * (real32_T)RBounded_Uint8->data[b_i] + -0.3678F *
                     (real32_T)GBounded_Uint8->data[b_i]) + -0.0714F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* end function */
              /* Assign the ith y, cb, and cr values */
              YBounded_Single->data[b_i] = CbCrRatio_ith;

              /* Classify pixels within all thresholds as skin (true)        */
              if (IsSkinMask_ith) {
                if ((CbCrRatio_ith > YMin) && (CbCrRatio_ith < YMax) && (cb >
                     CbMin) && (cb < CbMax) && (cr > CrMin) && (cr < CrMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }
              }

              if (IsSkinMask_ith) {
                /* Calculate Cb-to-Cr ratio */
                /* Type single to permit division to return fractions. */
                /* Note: for efficiency, the output is assigned to a previously assigned  */
                /* variable. */
                out = cb / cr;
                if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                  IsSkinMask_ith = false;
                }
              }

              IsSkinMask->data[b_i] = IsSkinMask_ith;
            }

            /* Index using subscript indices */
          } else {
            i = (XOffset + NCols_Matrix) - 1;
            for (b_i = XOffset; b_i <= i; b_i++) {
              i1 = (YOffset + NRows_Matrix) - 1;
              for (j = YOffset; j <= i1; j++) {
                /* Indices for output matrices */
                YAdjust = j - YOffset;
                XAdjust = b_i - XOffset;

                /* Extract and cast to type single the ith r, g, and b values */
                /* Scalars; type single. */
                c1 = RBounded_Uint8->data[(j + RBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c2 = GBounded_Uint8->data[(j + GBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c3 = BBounded_Uint8->data[(j + BBounded_Uint8->size[0] * (b_i -
                  1)) - 1];

                /* Apply rgb-to-h algorithm */
                /* Scalars; type single. */
                /* Note: rgb2hse is a custom function located within folder 'FacePulseRate'.  */
                /*  h; named "out" because later reassigned with different value */
                /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                /*           channels of the HSV colorspace.  */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*                     */
                /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                /*     colorspace.  */
                /*  */
                /*     Notes: */
                /*  */
                /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                /*     code generation. As of Matlab version 2020a, the file location is  */
                /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                /*  */
                /*     References: */
                /*  */
                /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                /*     19. */
                /* Inline function */
                /* Maximum channel value */
                if ((c1 > c2) && (c1 > c3)) {
                  v = c1;
                } else {
                  v = muIntScalarMax_sint32(c2, c3);
                }

                /* Minimum channel value */
                if ((c1 < c2) && (c1 < c3)) {
                  l = c1;
                } else {
                  l = muIntScalarMin_sint32(c2, c3);
                }

                /* Difference between maximum and minimum values */
                l = v - l;

                /* Determine value of hue channel (h) */
                if (l == 0) {
                  out = 0.0F;
                } else if (c3 == v) {
                  out = ((real32_T)(c1 - c2) / (real32_T)l + 4.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c1 == v) {
                  out = (real32_T)(c2 - c3) / (real32_T)l / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c2 == v) {
                  out = ((real32_T)(c3 - c1) / (real32_T)l + 2.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else {
                  out = 0.0F;
                }

                if (v == 0) {
                  s = 0.0F;
                } else if (l == 0) {
                  s = 0.0F;
                } else {
                  s = (real32_T)l / (real32_T)v;
                }

                /* end function */
                /* Assign the ith h and s values to the H- and S-channel matrices */
                HBounded_Single->data[YAdjust + HBounded_Single->size[0] *
                  XAdjust] = out;
                SBounded_Single->data[YAdjust + SBounded_Single->size[0] *
                  XAdjust] = s;
                if ((out < HMax) && (s > SMin) && (s < SMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                /* Apply the RGB-to-YCbCr algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the outputs replace the inputs. */
                /* Note: rgb2ycbcr_compute is a custom function located within folder  */
                /* 'FacePulseRate'.        */
                /*  y */
                /*  cb */
                /*  cr */
                /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                CbCrRatio_ith = ((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)
                                  c2) + 0.0979F * (real32_T)c3) + 16.0F;

                /* ith Cb channel element */
                /* Scalar; type single. */
                cb = ((-0.1482F * (real32_T)c1 + -0.291F * (real32_T)c2) +
                      0.4392F * (real32_T)c3) + 128.0F;

                /* ith Cr channel element */
                /* Scalar; type single. */
                cr = ((0.4392F * (real32_T)c1 + -0.3678F * (real32_T)c2) +
                      -0.0714F * (real32_T)c3) + 128.0F;

                /* end function */
                /* Assign the ith y, cb, and cr values */
                YBounded_Single->data[YAdjust + YBounded_Single->size[0] *
                  XAdjust] = CbCrRatio_ith;

                /* Classify pixels within all thresholds as skin (true)        */
                if (IsSkinMask_ith) {
                  if ((CbCrRatio_ith > YMin) && (CbCrRatio_ith < YMax) && (cb >
                       CbMin) && (cb < CbMax) && (cr > CrMin) && (cr < CrMax)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }
                }

                if (IsSkinMask_ith) {
                  /* Calculate Cb-to-Cr ratio */
                  /* Type single to permit division to return fractions. */
                  /* Note: for efficiency, the output is assigned to a previously assigned  */
                  /* variable. */
                  out = cb / cr;
                  if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                    IsSkinMask_ith = false;
                  }
                }

                IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                  IsSkinMask_ith;
              }
            }
          }

          /* (12) Condition 12  */
          /*  - Use tailored thresholds: tailored YCbCr thresholds and tailored HS thresholds. */
          /*  - Return matrices of the H and S channels. */
          /*  - Return matrices of the Y, Cb, and Cr channels.        */
        } else {
          /* M x N matrices; type single. */
          i = YBounded_Single->size[0] * YBounded_Single->size[1];
          YBounded_Single->size[0] = NRows_Matrix;
          YBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(YBounded_Single, i);
          i = CbBounded_Single->size[0] * CbBounded_Single->size[1];
          CbBounded_Single->size[0] = NRows_Matrix;
          CbBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(CbBounded_Single, i);
          i = CrBounded_Single->size[0] * CrBounded_Single->size[1];
          CrBounded_Single->size[0] = NRows_Matrix;
          CrBounded_Single->size[1] = NCols_Matrix;
          emxEnsureCapacity_real32_T(CrBounded_Single, i);

          /* Index using a linear index */
          if (UseLinIdxTF) {
            /* Loop across elements of the matrices to apply the RGB-to-YCbCr algorithm */
            for (b_i = 0; b_i < NElements_Matrix; b_i++) {
              /* Extract and cast to type single the ith r, g, and b values */
              /* Scalars; type single. */
              /* Apply rgb-to-hs algorithm */
              /* Scalars; type single. */
              /* Note: rgb2hs is a custom function located within folder 'FacePulseRate'.  */
              /*  h; named "out" because later reassigned with different value */
              /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
              /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
              /*           channels of the HSV colorspace.  */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Description: */
              /*                     */
              /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
              /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
              /*     colorspace.  */
              /*  */
              /*     Notes: */
              /*  */
              /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
              /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
              /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
              /*     code generation. As of Matlab version 2020a, the file location is  */
              /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
              /*  */
              /*     References: */
              /*  */
              /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
              /*     19. */
              /* Inline function */
              /* Maximum channel value */
              if ((RBounded_Uint8->data[b_i] > GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])) {
                v = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] > BBounded_Uint8->data[b_i])
              {
                v = GBounded_Uint8->data[b_i];
              } else {
                v = BBounded_Uint8->data[b_i];
              }

              /* Minimum channel value */
              if ((RBounded_Uint8->data[b_i] < GBounded_Uint8->data[b_i]) &&
                  (RBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])) {
                l = RBounded_Uint8->data[b_i];
              } else if (GBounded_Uint8->data[b_i] < BBounded_Uint8->data[b_i])
              {
                l = GBounded_Uint8->data[b_i];
              } else {
                l = BBounded_Uint8->data[b_i];
              }

              /* Difference between maximum and minimum values */
              l = v - l;

              /* Determine value of hue channel (h) */
              if (l == 0) {
                out = 0.0F;
              } else if (BBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(RBounded_Uint8->data[b_i] -
                                  GBounded_Uint8->data[b_i]) / (real32_T)l +
                       4.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (RBounded_Uint8->data[b_i] == v) {
                out = (real32_T)(GBounded_Uint8->data[b_i] -
                                 BBounded_Uint8->data[b_i]) / (real32_T)l / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else if (GBounded_Uint8->data[b_i] == v) {
                out = ((real32_T)(BBounded_Uint8->data[b_i] -
                                  RBounded_Uint8->data[b_i]) / (real32_T)l +
                       2.0F) / 6.0F;
                if (out < 0.0F) {
                  out++;
                }
              } else {
                out = 0.0F;
              }

              if (v == 0) {
                s = 0.0F;
              } else if (l == 0) {
                s = 0.0F;
              } else {
                s = (real32_T)l / (real32_T)v;
              }

              /* end function */
              /* Assign the ith h and s values to the H- and S-channel matrices */
              HBounded_Single->data[b_i] = out;
              SBounded_Single->data[b_i] = s;
              if ((out < HMax) && (s > SMin) && (s < SMax)) {
                IsSkinMask_ith = true;
              } else {
                IsSkinMask_ith = false;
              }

              /* Apply the RGB-to-YCbCr algorithm */
              /* Scalars; type single. */
              /* Note: for efficiency, the outputs replace the inputs. */
              /* Note: rgb2ycbcr_compute is a custom function located within folder  */
              /* 'FacePulseRate'.       */
              /*  y */
              /*  cb */
              /*  cr */
              /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*     */
              /*     Helper function to function FacePulseRate.  */
              /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
              /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
              /*  */
              /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
              /*  */
              /*     Description: */
              /*  */
              /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
              /*  */
              /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
              /*     derived from Poynton (1996, p. 175 - 176). */
              /*  */
              /*     Note: */
              /*  */
              /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
              /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
              /*  */
              /*     References: */
              /*  */
              /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
              /* Inline function */
              /* ith Y channel element */
              /* Scalar; type single. */
              CbCrRatio_ith = ((0.2568F * (real32_T)RBounded_Uint8->data[b_i] +
                                0.5041F * (real32_T)GBounded_Uint8->data[b_i]) +
                               0.0979F * (real32_T)BBounded_Uint8->data[b_i]) +
                16.0F;

              /* ith Cb channel element */
              /* Scalar; type single. */
              cb = ((-0.1482F * (real32_T)RBounded_Uint8->data[b_i] + -0.291F *
                     (real32_T)GBounded_Uint8->data[b_i]) + 0.4392F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* ith Cr channel element */
              /* Scalar; type single. */
              cr = ((0.4392F * (real32_T)RBounded_Uint8->data[b_i] + -0.3678F *
                     (real32_T)GBounded_Uint8->data[b_i]) + -0.0714F * (real32_T)
                    BBounded_Uint8->data[b_i]) + 128.0F;

              /* end function */
              /* Assign the ith y, cb, and cr values */
              YBounded_Single->data[b_i] = CbCrRatio_ith;
              CbBounded_Single->data[b_i] = cb;
              CrBounded_Single->data[b_i] = cr;

              /* Classify pixels within all thresholds as skin (true)        */
              if (IsSkinMask_ith) {
                if ((CbCrRatio_ith > YMin) && (CbCrRatio_ith < YMax) && (cb >
                     CbMin) && (cb < CbMax) && (cr > CrMin) && (cr < CrMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }
              }

              if (IsSkinMask_ith) {
                /* Calculate Cb-to-Cr ratio */
                /* Type single to permit division to return fractions. */
                /* Note: for efficiency, the output is assigned to a previously assigned  */
                /* variable. */
                out = cb / cr;
                if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                  IsSkinMask_ith = false;
                }
              }

              IsSkinMask->data[b_i] = IsSkinMask_ith;
            }

            /* Index using subscript indices */
          } else {
            i = (XOffset + NCols_Matrix) - 1;
            for (b_i = XOffset; b_i <= i; b_i++) {
              i1 = (YOffset + NRows_Matrix) - 1;
              for (j = YOffset; j <= i1; j++) {
                /* Indices for output matrices */
                YAdjust = j - YOffset;
                XAdjust = b_i - XOffset;

                /* Extract and cast to type single the ith r, g, and b values */
                /* Scalars; type single. */
                c1 = RBounded_Uint8->data[(j + RBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c2 = GBounded_Uint8->data[(j + GBounded_Uint8->size[0] * (b_i -
                  1)) - 1];
                c3 = BBounded_Uint8->data[(j + BBounded_Uint8->size[0] * (b_i -
                  1)) - 1];

                /* Apply rgb-to-hs algorithm */
                /* Scalars; type single. */
                /* Note: rgb2hs is a custom function located within folder 'FacePulseRate'.  */
                /*  h; named "out" because later reassigned with different value */
                /* rgb2hs    Apply the rgb-to-h algorithm to a given pixel and return the H and S channels. Version       */
                /*           of Matlab function rgb2hsv_compute that is optimized for returning only the h and s  */
                /*           channels of the HSV colorspace.  */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Description: */
                /*                     */
                /*     Apply the rgb-to-h algorithm to a given pixel and return the H channel. Version of Matlab      */
                /*     function rgb2hsv_compute that is optimized for returning only the h channel of the HSV  */
                /*     colorspace.  */
                /*  */
                /*     Notes: */
                /*  */
                /*     For efficiency, the hue channel (h) of the hsv colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     RGB to H conversion algorithm is adapated from Matlab function rgb2hsv_portable, which is a  */
                /*     local function within Matlab function rgb2hsv. Note that there are several versions of  */
                /*     function rgb2hsv; the version from which the function was extracted is the version used for  */
                /*     code generation. As of Matlab version 2020a, the file location is  */
                /*     R2020a\toolbox\eml\lib\matlab\images. The Matlab algorithm is derived from Smith (1978). */
                /*  */
                /*     References: */
                /*  */
                /*     Smith, A. R. (1978). Color gamut transform pairs. ACM Siggraph Computer Graphics, 12(3), 12- */
                /*     19. */
                /* Inline function */
                /* Maximum channel value */
                if ((c1 > c2) && (c1 > c3)) {
                  v = c1;
                } else {
                  v = muIntScalarMax_sint32(c2, c3);
                }

                /* Minimum channel value */
                if ((c1 < c2) && (c1 < c3)) {
                  l = c1;
                } else {
                  l = muIntScalarMin_sint32(c2, c3);
                }

                /* Difference between maximum and minimum values */
                l = v - l;

                /* Determine value of hue channel (h) */
                if (l == 0) {
                  out = 0.0F;
                } else if (c3 == v) {
                  out = ((real32_T)(c1 - c2) / (real32_T)l + 4.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c1 == v) {
                  out = (real32_T)(c2 - c3) / (real32_T)l / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else if (c2 == v) {
                  out = ((real32_T)(c3 - c1) / (real32_T)l + 2.0F) / 6.0F;
                  if (out < 0.0F) {
                    out++;
                  }
                } else {
                  out = 0.0F;
                }

                if (v == 0) {
                  s = 0.0F;
                } else if (l == 0) {
                  s = 0.0F;
                } else {
                  s = (real32_T)l / (real32_T)v;
                }

                /* end function */
                /* Assign the ith h and s values to the H- and S-channel matrices */
                HBounded_Single->data[YAdjust + HBounded_Single->size[0] *
                  XAdjust] = out;
                SBounded_Single->data[YAdjust + SBounded_Single->size[0] *
                  XAdjust] = s;
                if ((out < HMax) && (s > SMin) && (s < SMax)) {
                  IsSkinMask_ith = true;
                } else {
                  IsSkinMask_ith = false;
                }

                /* Apply the RGB-to-YCbCr algorithm */
                /* Scalars; type single. */
                /* Note: for efficiency, the outputs replace the inputs. */
                /* Note: rgb2ycbcr_compute is a custom function located within folder  */
                /* 'FacePulseRate'.       */
                /*  y */
                /*  cb */
                /*  cr */
                /* rgb2ycbcr_compute   Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*     */
                /*     Helper function to function FacePulseRate.  */
                /*     Within function FacePulseRate, called by functions SkinSegmentMask_Threshold_Colors_Convert */
                /*     and SkinSegmentMask_Threshold_Colors_NoConvert. */
                /*  */
                /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
                /*  */
                /*     Description: */
                /*  */
                /*     Apply the RGB-to-YCbCr algorithm to a given pixel and return the channels. */
                /*  */
                /*     The conversion algorithm is adapated from Matlab function rgb2ycbcr. The Matlab algorithm is */
                /*     derived from Poynton (1996, p. 175 - 176). */
                /*  */
                /*     Note: */
                /*  */
                /*     For efficiency, the Cr channel of the YCbCr colorspace is assigned to variable b, which */
                /*     represents the blue channel (b) of the rgb colorspace before the assignment. */
                /*  */
                /*     References: */
                /*  */
                /*     Poynton, C. A. (1996). A technical introduction to digital video. John Wiley & Sons. */
                /* Inline function */
                /* ith Y channel element */
                /* Scalar; type single. */
                CbCrRatio_ith = ((0.2568F * (real32_T)c1 + 0.5041F * (real32_T)
                                  c2) + 0.0979F * (real32_T)c3) + 16.0F;

                /* ith Cb channel element */
                /* Scalar; type single. */
                cb = ((-0.1482F * (real32_T)c1 + -0.291F * (real32_T)c2) +
                      0.4392F * (real32_T)c3) + 128.0F;

                /* ith Cr channel element */
                /* Scalar; type single. */
                cr = ((0.4392F * (real32_T)c1 + -0.3678F * (real32_T)c2) +
                      -0.0714F * (real32_T)c3) + 128.0F;

                /* end function */
                /* Assign the ith y, cb, and cr values */
                YBounded_Single->data[YAdjust + YBounded_Single->size[0] *
                  XAdjust] = CbCrRatio_ith;
                CbBounded_Single->data[YAdjust + CbBounded_Single->size[0] *
                  XAdjust] = cb;
                CrBounded_Single->data[YAdjust + CrBounded_Single->size[0] *
                  XAdjust] = cr;

                /* Classify pixels within all thresholds as skin (true)        */
                if (IsSkinMask_ith) {
                  if ((CbCrRatio_ith > YMin) && (CbCrRatio_ith < YMax) && (cb >
                       CbMin) && (cb < CbMax) && (cr > CrMin) && (cr < CrMax)) {
                    IsSkinMask_ith = true;
                  } else {
                    IsSkinMask_ith = false;
                  }
                }

                if (IsSkinMask_ith) {
                  /* Calculate Cb-to-Cr ratio */
                  /* Type single to permit division to return fractions. */
                  /* Note: for efficiency, the output is assigned to a previously assigned  */
                  /* variable. */
                  out = cb / cr;
                  if ((!(out > CbCrRatioMin)) || (!(out < CbCrRatioMax))) {
                    IsSkinMask_ith = false;
                  }
                }

                IsSkinMask->data[YAdjust + IsSkinMask->size[0] * XAdjust] =
                  IsSkinMask_ith;
              }
            }
          }
        }
      }
    }

    /* %%%%%% --- Non-compiled version of function %%%%%% */
    /* Use vectorized operations, which are more efficient for Matlab code. */
    /* end function */
  }

  /* end function  */
}

/* End of code generation (SkinSegmentMask_Threshold_Colors.c) */
