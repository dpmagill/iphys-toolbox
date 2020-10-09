/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinSegmentMask_Threshold.c
 *
 * Code generation for function 'SkinSegmentMask_Threshold'
 *
 */

/* Include files */
#include "SkinSegmentMask_Threshold.h"
#include "SkinSegmentMask_Ops.h"
#include "SkinSegmentMask_Ops_emxutil.h"
#include "SkinSegmentMask_Threshold_Colors.h"
#include "libmwmorphop_ipp.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static boolean_T SE3_not_empty;
static boolean_T SE5_not_empty;
static boolean_T SE7_not_empty;
static boolean_T SE9_not_empty;

/* Function Declarations */
static void ApplyRangeThreshold(emlrtCTX aTLS, emxArray_uint8_T *RBounded_Uint8,
  int16_T RangeNeighborhoodWidth, uint8_T RangeThreshold, boolean_T UseLinIdxTF,
  int32_T XOffset, int32_T YOffset, int32_T NRows_Matrix, int32_T NCols_Matrix,
  emxArray_boolean_T *IsSkinMask_Range);

/* Function Definitions */
static void ApplyRangeThreshold(emlrtCTX aTLS, emxArray_uint8_T *RBounded_Uint8,
  int16_T RangeNeighborhoodWidth, uint8_T RangeThreshold, boolean_T UseLinIdxTF,
  int32_T XOffset, int32_T YOffset, int32_T NRows_Matrix, int32_T NCols_Matrix,
  emxArray_boolean_T *IsSkinMask_Range)
{
  emxArray_uint8_T *B;
  int32_T i;
  int32_T b_i;
  int32_T i1;
  int32_T i2;
  int32_T loop_ub;
  int32_T b_loop_ub;
  int16_T Diff3;
  int16_T Diff5;
  int16_T Diff7;
  emxArray_uint8_T *Apadpack;
  emxArray_uint8_T *b_B;
  boolean_T guard1 = false;
  real_T asize[2];
  boolean_T nhood[5];
  boolean_T b_nhood[7];
  boolean_T c_nhood[9];
  real_T nsize[2];
  emlrtHeapReferenceStackEnterFcnR2012b(aTLS);

  /* end main function */
  /* ============================================================================================= */
  /* Local functions  */
  /* ============================================================================================= */
  /* ============================================================================================= */
  /* ApplyRangeThreshold   Apply local color range threshold to individual pixels.                                      */
  /*  */
  /*     Description: */
  /*  */
  /*     For a detailed description of the assumptions of using this threshold for skin segmentation, */
  /*     see function SkinSegmentMask_Ops. */
  /*  */
  /*     Take the local color range of each pixel and classify it as skin if it is below the specified */
  /*     threshold (RangeThreshold). The threshold is assigned by function SkinSegment_ConfigSetup. */
  /*  */
  /*     The local range is defined as the square neighborhood specified by RangeNeighborhoodWidth. */
  /*     Because the structuring element object (SE3, SE5, SE7, or SE9) must be a compile-time  */
  /*     constant, only four structuring element objects are made available. The structuring element  */
  /*     object closest to the specified structuring element size (RangeNeighborhoodWidth) is used. */
  /*  */
  /*     Only the local range of the red channel, rather than all RGB channels, is used for  */
  /*     computational efficiency. An RGB channel may be preferable to the Cb and Cr channels because  */
  /*     the RGB channels contain luminance information, the range of which seems to be useful in  */
  /*     indicating non-skin. The Y channel from the YCbCr colorspace, which is a measure a luminance, */
  /*     might also be suitable. */
  /* Inline function */
  /* If subscript indexing specified */
  emxInit_uint8_T(aTLS, &B, 2, true);
  if (!UseLinIdxTF) {
    /* Crop matrix according to subscripts */
    i = (YOffset + NRows_Matrix) - 2;
    if (YOffset > i + 1) {
      b_i = 0;
      i = -1;
    } else {
      b_i = YOffset - 1;
    }

    i1 = (XOffset + NCols_Matrix) - 2;
    if (XOffset > i1 + 1) {
      i2 = 0;
      i1 = -1;
    } else {
      i2 = XOffset - 1;
    }

    loop_ub = i - b_i;
    i = B->size[0] * B->size[1];
    B->size[0] = loop_ub + 1;
    b_loop_ub = i1 - i2;
    B->size[1] = b_loop_ub + 1;
    emxEnsureCapacity_uint8_T(B, i);
    for (i = 0; i <= b_loop_ub; i++) {
      for (i1 = 0; i1 <= loop_ub; i1++) {
        B->data[i1 + B->size[0] * i] = RBounded_Uint8->data[(b_i + i1) +
          RBounded_Uint8->size[0] * (i2 + i)];
      }
    }

    i = RBounded_Uint8->size[0] * RBounded_Uint8->size[1];
    RBounded_Uint8->size[0] = B->size[0];
    RBounded_Uint8->size[1] = B->size[1];
    emxEnsureCapacity_uint8_T(RBounded_Uint8, i);
    loop_ub = B->size[0] * B->size[1];
    for (i = 0; i < loop_ub; i++) {
      RBounded_Uint8->data[i] = B->data[i];
    }
  }

  /* Return the local range of each pixel */
  /* M x N matrix; type uint8. */
  /* SkinSegmentMask_Threshold_Range    Function rangefilt optimized for use in function */
  /*                                    SkinSegmentMask_Threshold. */
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
  /*     For a description of the assumptions behind the use of the following operations to classify */
  /*     pixels as skin, see function SkinSegmentMask_Ops. */
  /*  */
  /*     Note: The algorithm used is adapted from Matlab function rangefilt. */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
  /*     the Responsible AI License (RAIL). */
  /* %%%%% Code-generation settings %%%%%% */
  /* %%%%% Parse inputs %%%%%% */
  /* Because the structuring element object (SE3, SE5, SE7, or SE9) must be a compile-time constant,   */
  /* only four structuring element objects are made available, each of which has a corresponding  */
  /* function. The function with the structuring element closest in size to the specified structuring  */
  /* element size (RangeNeighborhoodWidth) is used. */
  /* Select function from available functions */
  /* Select the function with the SE width most similar to the specified SE width. */
  /* Local function. */
  /* Scalar; type int16. */
  /* end main function */
  /* ============================================================================================= */
  /* Local functions  */
  /* ============================================================================================= */
  /* ============================================================================================= */
  /* SelectFunction   Select the function with the SE width most similar to nhoodWidth.    */
  /* Inline function */
  /* Scalars; type int16. */
  if ((int16_T)(3 - RangeNeighborhoodWidth) < 0) {
    Diff3 = (int16_T)(RangeNeighborhoodWidth - 3);
  } else {
    Diff3 = (int16_T)(3 - RangeNeighborhoodWidth);
  }

  if ((int16_T)(5 - RangeNeighborhoodWidth) < 0) {
    Diff5 = (int16_T)(RangeNeighborhoodWidth - 5);
  } else {
    Diff5 = (int16_T)(5 - RangeNeighborhoodWidth);
  }

  if ((int16_T)(7 - RangeNeighborhoodWidth) < 0) {
    Diff7 = (int16_T)(RangeNeighborhoodWidth - 7);
  } else {
    Diff7 = (int16_T)(7 - RangeNeighborhoodWidth);
  }

  if (Diff3 < Diff5) {
    Diff5 = Diff3;
    Diff3 = 3;
  } else {
    Diff3 = 5;
  }

  if (Diff7 < Diff5) {
    Diff5 = Diff7;
    Diff3 = 7;
  }

  if ((int16_T)(9 - RangeNeighborhoodWidth) < 0) {
    i = (int16_T)(RangeNeighborhoodWidth - 9);
  } else {
    i = (int16_T)(9 - RangeNeighborhoodWidth);
  }

  if (i < Diff5) {
    Diff3 = 9;
  }

  /* %%%%% Erosion followed by dilation %%%%%% */
  /* Use available function with SE width closest to specified SE width  */
  emxInit_uint8_T(aTLS, &Apadpack, 2, true);
  emxInit_uint8_T(aTLS, &b_B, 2, true);
  guard1 = false;
  switch (Diff3) {
   case 3:
    /* Local range of square neighborhood with width of 3 pixels     */
    /* M x N matrices; type uint8. */
    /* end local function */
    /* ============================================================================================= */
    /* rangefilt_optim_SEWidth3    Optimized range filter using square structuring element of width 3. */
    /* Inline function */
    /* Dilate */
    /* M x N matrix; type uint8. */
    i = B->size[0] * B->size[1];
    B->size[0] = RBounded_Uint8->size[0];
    B->size[1] = RBounded_Uint8->size[1];
    emxEnsureCapacity_uint8_T(B, i);
    for (i = 0; i < 9; i++) {
      c_nhood[i] = true;
    }

    asize[0] = RBounded_Uint8->size[0];
    nsize[0] = 3.0;
    asize[1] = RBounded_Uint8->size[1];
    nsize[1] = 3.0;
    dilate_uint8_ipp(&RBounded_Uint8->data[0], asize, c_nhood, nsize, &B->data[0]);

    /* Erode */
    /* M x N matrix; type uint8. */
    /* Note: Difference from function rangefilt: use of structuring element object (strel). */
    /* Note from rangefilt function file: IMERODE returns the local minima of I in NHOOD. */
    i = b_B->size[0] * b_B->size[1];
    b_B->size[0] = RBounded_Uint8->size[0];
    b_B->size[1] = RBounded_Uint8->size[1];
    emxEnsureCapacity_uint8_T(b_B, i);
    for (i = 0; i < 9; i++) {
      c_nhood[i] = true;
    }

    asize[0] = RBounded_Uint8->size[0];
    nsize[0] = 3.0;
    asize[1] = RBounded_Uint8->size[1];
    nsize[1] = 3.0;
    erode_uint8_ipp(&RBounded_Uint8->data[0], asize, c_nhood, nsize, &b_B->data
                    [0]);

    /* one channel */
    /* Local range of square neighborhood with width of 5 pixels */
    guard1 = true;
    break;

   case 5:
    /* M x N matrices; type uint8. */
    /* end local function */
    /* ============================================================================================= */
    /* rangefilt_optim_SEWidth5    Optimized range filter using square structuring element of width 5. */
    /* Inline function */
    /* Dilate */
    /* M x N matrix; type uint8. */
    i = B->size[0] * B->size[1];
    B->size[0] = RBounded_Uint8->size[0];
    B->size[1] = RBounded_Uint8->size[1];
    emxEnsureCapacity_uint8_T(B, i);
    for (b_i = 0; b_i < 5; b_i++) {
      nhood[b_i] = true;
    }

    asize[0] = RBounded_Uint8->size[0];
    nsize[0] = 5.0;
    asize[1] = RBounded_Uint8->size[1];
    nsize[1] = 1.0;
    dilate_uint8_ipp(&RBounded_Uint8->data[0], asize, nhood, nsize, &B->data[0]);
    i = Apadpack->size[0] * Apadpack->size[1];
    Apadpack->size[0] = B->size[0];
    Apadpack->size[1] = B->size[1];
    emxEnsureCapacity_uint8_T(Apadpack, i);
    loop_ub = B->size[0] * B->size[1];
    for (i = 0; i < loop_ub; i++) {
      Apadpack->data[i] = B->data[i];
    }

    i = B->size[0] * B->size[1];
    B->size[0] = Apadpack->size[0];
    B->size[1] = Apadpack->size[1];
    emxEnsureCapacity_uint8_T(B, i);
    for (b_i = 0; b_i < 5; b_i++) {
      nhood[b_i] = true;
    }

    asize[0] = Apadpack->size[0];
    nsize[0] = 1.0;
    asize[1] = Apadpack->size[1];
    nsize[1] = 5.0;
    dilate_uint8_ipp(&Apadpack->data[0], asize, nhood, nsize, &B->data[0]);

    /* Erode */
    /* M x N matrix; type uint8. */
    /* Note: Difference from function rangefilt: use structuring element object (strel). */
    /* Note from rangefilt function file: IMERODE returns the local minima of I in NHOOD. */
    i = b_B->size[0] * b_B->size[1];
    b_B->size[0] = RBounded_Uint8->size[0];
    b_B->size[1] = RBounded_Uint8->size[1];
    emxEnsureCapacity_uint8_T(b_B, i);
    for (b_i = 0; b_i < 5; b_i++) {
      nhood[b_i] = true;
    }

    asize[0] = RBounded_Uint8->size[0];
    nsize[0] = 5.0;
    asize[1] = RBounded_Uint8->size[1];
    nsize[1] = 1.0;
    erode_uint8_ipp(&RBounded_Uint8->data[0], asize, nhood, nsize, &b_B->data[0]);
    i = Apadpack->size[0] * Apadpack->size[1];
    Apadpack->size[0] = b_B->size[0];
    Apadpack->size[1] = b_B->size[1];
    emxEnsureCapacity_uint8_T(Apadpack, i);
    loop_ub = b_B->size[0] * b_B->size[1];
    for (i = 0; i < loop_ub; i++) {
      Apadpack->data[i] = b_B->data[i];
    }

    i = b_B->size[0] * b_B->size[1];
    b_B->size[0] = Apadpack->size[0];
    b_B->size[1] = Apadpack->size[1];
    emxEnsureCapacity_uint8_T(b_B, i);
    for (b_i = 0; b_i < 5; b_i++) {
      nhood[b_i] = true;
    }

    asize[0] = Apadpack->size[0];
    nsize[0] = 1.0;
    asize[1] = Apadpack->size[1];
    nsize[1] = 5.0;
    erode_uint8_ipp(&Apadpack->data[0], asize, nhood, nsize, &b_B->data[0]);

    /* one channel */
    /* Local range of square neighborhood with width of 7 pixels */
    guard1 = true;
    break;

   case 7:
    /* M x N matrices; type uint8. */
    /* end local function */
    /* ============================================================================================= */
    /* rangefilt_optim_SEWidth9    Optimized range filter using square structuring element of width 7. */
    /* Inline function */
    /* Dilate */
    /* M x N matrix; type uint8. */
    i = B->size[0] * B->size[1];
    B->size[0] = RBounded_Uint8->size[0];
    B->size[1] = RBounded_Uint8->size[1];
    emxEnsureCapacity_uint8_T(B, i);
    for (b_i = 0; b_i < 7; b_i++) {
      b_nhood[b_i] = true;
    }

    asize[0] = RBounded_Uint8->size[0];
    nsize[0] = 7.0;
    asize[1] = RBounded_Uint8->size[1];
    nsize[1] = 1.0;
    dilate_uint8_ipp(&RBounded_Uint8->data[0], asize, b_nhood, nsize, &B->data[0]);
    i = Apadpack->size[0] * Apadpack->size[1];
    Apadpack->size[0] = B->size[0];
    Apadpack->size[1] = B->size[1];
    emxEnsureCapacity_uint8_T(Apadpack, i);
    loop_ub = B->size[0] * B->size[1];
    for (i = 0; i < loop_ub; i++) {
      Apadpack->data[i] = B->data[i];
    }

    i = B->size[0] * B->size[1];
    B->size[0] = Apadpack->size[0];
    B->size[1] = Apadpack->size[1];
    emxEnsureCapacity_uint8_T(B, i);
    for (b_i = 0; b_i < 7; b_i++) {
      b_nhood[b_i] = true;
    }

    asize[0] = Apadpack->size[0];
    nsize[0] = 1.0;
    asize[1] = Apadpack->size[1];
    nsize[1] = 7.0;
    dilate_uint8_ipp(&Apadpack->data[0], asize, b_nhood, nsize, &B->data[0]);

    /* Erode */
    /* M x N matrix; type uint8. */
    /* Note: Difference from function rangefilt: use structuring element object (strel). */
    /* Note from rangefilt function file: IMERODE returns the local minima of I in NHOOD. */
    i = b_B->size[0] * b_B->size[1];
    b_B->size[0] = RBounded_Uint8->size[0];
    b_B->size[1] = RBounded_Uint8->size[1];
    emxEnsureCapacity_uint8_T(b_B, i);
    for (b_i = 0; b_i < 7; b_i++) {
      b_nhood[b_i] = true;
    }

    asize[0] = RBounded_Uint8->size[0];
    nsize[0] = 7.0;
    asize[1] = RBounded_Uint8->size[1];
    nsize[1] = 1.0;
    erode_uint8_ipp(&RBounded_Uint8->data[0], asize, b_nhood, nsize, &b_B->data
                    [0]);
    i = Apadpack->size[0] * Apadpack->size[1];
    Apadpack->size[0] = b_B->size[0];
    Apadpack->size[1] = b_B->size[1];
    emxEnsureCapacity_uint8_T(Apadpack, i);
    loop_ub = b_B->size[0] * b_B->size[1];
    for (i = 0; i < loop_ub; i++) {
      Apadpack->data[i] = b_B->data[i];
    }

    i = b_B->size[0] * b_B->size[1];
    b_B->size[0] = Apadpack->size[0];
    b_B->size[1] = Apadpack->size[1];
    emxEnsureCapacity_uint8_T(b_B, i);
    for (b_i = 0; b_i < 7; b_i++) {
      b_nhood[b_i] = true;
    }

    asize[0] = Apadpack->size[0];
    nsize[0] = 1.0;
    asize[1] = Apadpack->size[1];
    nsize[1] = 7.0;
    erode_uint8_ipp(&Apadpack->data[0], asize, b_nhood, nsize, &b_B->data[0]);

    /* one channel */
    /* Local range of square neighborhood with width of 9 pixels */
    guard1 = true;
    break;

   case 9:
    /* M x N matrices; type uint8. */
    /* end local function */
    /* ============================================================================================= */
    /* rangefilt_optim_SEWidth9    Optimized range filter using square structuring element of width 9. */
    /* Inline function */
    /* Dilate */
    /* M x N matrix; type uint8. */
    i = B->size[0] * B->size[1];
    B->size[0] = RBounded_Uint8->size[0];
    B->size[1] = RBounded_Uint8->size[1];
    emxEnsureCapacity_uint8_T(B, i);
    for (i = 0; i < 9; i++) {
      c_nhood[i] = true;
    }

    asize[0] = RBounded_Uint8->size[0];
    nsize[0] = 9.0;
    asize[1] = RBounded_Uint8->size[1];
    nsize[1] = 1.0;
    dilate_uint8_ipp(&RBounded_Uint8->data[0], asize, c_nhood, nsize, &B->data[0]);
    i = Apadpack->size[0] * Apadpack->size[1];
    Apadpack->size[0] = B->size[0];
    Apadpack->size[1] = B->size[1];
    emxEnsureCapacity_uint8_T(Apadpack, i);
    loop_ub = B->size[0] * B->size[1];
    for (i = 0; i < loop_ub; i++) {
      Apadpack->data[i] = B->data[i];
    }

    i = B->size[0] * B->size[1];
    B->size[0] = Apadpack->size[0];
    B->size[1] = Apadpack->size[1];
    emxEnsureCapacity_uint8_T(B, i);
    for (i = 0; i < 9; i++) {
      c_nhood[i] = true;
    }

    asize[0] = Apadpack->size[0];
    nsize[0] = 1.0;
    asize[1] = Apadpack->size[1];
    nsize[1] = 9.0;
    dilate_uint8_ipp(&Apadpack->data[0], asize, c_nhood, nsize, &B->data[0]);

    /* Erode */
    /* M x N matrix; type uint8. */
    /* Note: Difference from function rangefilt: use structuring element object (strel). */
    /* Note from rangefilt function file: IMERODE returns the local minima of I in NHOOD. */
    i = b_B->size[0] * b_B->size[1];
    b_B->size[0] = RBounded_Uint8->size[0];
    b_B->size[1] = RBounded_Uint8->size[1];
    emxEnsureCapacity_uint8_T(b_B, i);
    for (i = 0; i < 9; i++) {
      c_nhood[i] = true;
    }

    asize[0] = RBounded_Uint8->size[0];
    nsize[0] = 9.0;
    asize[1] = RBounded_Uint8->size[1];
    nsize[1] = 1.0;
    erode_uint8_ipp(&RBounded_Uint8->data[0], asize, c_nhood, nsize, &b_B->data
                    [0]);
    i = Apadpack->size[0] * Apadpack->size[1];
    Apadpack->size[0] = b_B->size[0];
    Apadpack->size[1] = b_B->size[1];
    emxEnsureCapacity_uint8_T(Apadpack, i);
    loop_ub = b_B->size[0] * b_B->size[1];
    for (i = 0; i < loop_ub; i++) {
      Apadpack->data[i] = b_B->data[i];
    }

    i = b_B->size[0] * b_B->size[1];
    b_B->size[0] = Apadpack->size[0];
    b_B->size[1] = Apadpack->size[1];
    emxEnsureCapacity_uint8_T(b_B, i);
    for (i = 0; i < 9; i++) {
      c_nhood[i] = true;
    }

    asize[0] = Apadpack->size[0];
    nsize[0] = 1.0;
    asize[1] = Apadpack->size[1];
    nsize[1] = 9.0;
    erode_uint8_ipp(&Apadpack->data[0], asize, c_nhood, nsize, &b_B->data[0]);

    /* end local function */
    /* one channel */
    /* (Required for code generation validation)    */
    guard1 = true;
    break;

   default:
    i = B->size[0] * B->size[1];
    B->size[0] = 1;
    B->size[1] = 1;
    emxEnsureCapacity_uint8_T(B, i);
    B->data[0] = 0U;
    break;
  }

  if (guard1) {
    /* %%%%% Element-wise subtraction %%%%%% */
    /* Note: Code used in function rangefilt: localRange = imlincomb(1, dilateI, -1, erodeI, 'uint8'). */
    /* Use element-wise subtraction, which is equivalent, to avoid the argument parsing and conversion to */
    /* to type double that occurs in function imlincomb. */
    /* M x N matrix; type uint8. */
    loop_ub = B->size[0] * B->size[1];
    for (i = 0; i < loop_ub; i++) {
      B->data[i] = (uint8_T)((uint32_T)B->data[i] - b_B->data[i]);
    }
  }

  emxFree_uint8_T(&b_B);
  emxFree_uint8_T(&Apadpack);

  /* Return logical matrix where pixels below specified local range threshold are classified as skin. */
  /* Note: SkinSegmentMask_Threshold_Range is a custom version of Matlab function rangefilt optimized  */
  /* for use in the current function. It is located within folder 'FacePulseRate'. */
  /*  skin == true; non-skin == false */
  i = IsSkinMask_Range->size[0] * IsSkinMask_Range->size[1];
  IsSkinMask_Range->size[0] = B->size[0];
  IsSkinMask_Range->size[1] = B->size[1];
  emxEnsureCapacity_boolean_T(IsSkinMask_Range, i);
  loop_ub = B->size[0] * B->size[1];
  for (i = 0; i < loop_ub; i++) {
    IsSkinMask_Range->data[i] = (B->data[i] < RangeThreshold);
  }

  emxFree_uint8_T(&B);

  /* threshold (should be type uint8 for fastest evaluation).  */
  /* Previous implementation (local standard deviation threshold): */
  /* Note: limited testing indicates that calculating the local range might be about 8 times faster */
  /* than calculating the local standard deviation, which is why local range is used. */
  /* { */
  /*  */
  /* Neighborhood in which to calculate standard deviation for a given pixel */
  /* SDNeighborhood = ***; */
  /*  */
  /* Assign standard deviation filter */
  /* Take standard deviation of the neighborhood of each pixel and compare it against the threshold. */
  /* Classify pixel as skin if its local standard deviation does not exceed the specified threshold. */
  /* Only calculate standard deviations for the red channel for computational efficiency. */
  /* Note: stdfilt_optim is a custom function located within folder FacePulseRate; it is an optimized */
  /* version of function stdfilt; see the function file for details.  */
  /* The optimized version does not use padding; as a result, the pixels near the inner edge of the ROI */
  /* will be marked as non-skin. As the effect is consistent across ROIs, it is not considered to have */
  /* a substantive effect on the analysis. */
  /* SDfilter =                                ... skin == true; non-skin == false */
  /*     stdfilt_optim(AreaToSegment(:, :, 1), ... red channel */
  /*         SDNeighborhood)                   ... pixel neighborhood */
  /*     < SkinClassificationByColor.Pixel.SkinSeg.SDThreshold; %threshold */
  /*  */
  /* Combine classifications from pixel color and pixel color standard deviation */
  /* IsSkinMask_PixelColor = IsSkinMask_PixelColor & SDfilter;   */
  /*  */
  /* }          */
  /* end local function */
  emlrtHeapReferenceStackLeaveFcnR2012b(aTLS);
}

void SkinSegmentMask_Threshold(emlrtCTX aTLS, const emxArray_uint8_T
  *RBounded_Uint8, const emxArray_uint8_T *GBounded_Uint8, const
  emxArray_uint8_T *BBounded_Uint8, emxArray_real32_T *YBounded_Single,
  emxArray_real32_T *CbBounded_Single, emxArray_real32_T *CrBounded_Single,
  emxArray_real32_T *HBounded_Single, emxArray_real32_T *SBounded_Single,
  emxArray_boolean_T *IsSkinMask_Range, int32_T NRows_Matrix, int32_T
  NCols_Matrix, int32_T NElements_Matrix, const real32_T
  YCbCrThresholds_Generic[7], boolean_T TailoredThresholdsTF, boolean_T
  DontUseTailoredTF, const real32_T YCbCrThresholds_Tailored[8], boolean_T
  ReturnYTF, boolean_T ReturnCbCrTF, const real32_T HSThresholds_Generic[2],
  const real32_T HSThresholds_Tailored[3], boolean_T ReturnHSTF, int16_T
  RangeNeighborhoodWidth, uint8_T RangeThreshold, int32_T XOffset, int32_T
  YOffset, emxArray_boolean_T *IsSkinMask)
{
  boolean_T UseLinIdxTF;
  boolean_T XOffsetSpecifiedTF;
  boolean_T YOffsetSpecifiedTF;
  cell_wrap_2 ParCell1[2];
  cell_wrap_3 ParCell2[2];
  int32_T loop_ub;
  int32_T i;
  emxArray_uint8_T *b_RBounded_Uint8;
  int32_T b_i;
  int32_T b_loop_ub;
  int32_T i1;
  int32_T i2;
  int32_T c_loop_ub;
  jmp_buf * volatile emlrtJBStack;
  boolean_T emlrtHadParallelError = false;
  jmp_buf emlrtJBEnviron;
  emlrtHeapReferenceStackEnterFcnR2012b(aTLS);

  /* SkinSegmentMask_Threshold   Classify pixels as skin or non-skin based upon the color values, the    */
  /*                             color ratios, and the local range of individual pixels. */
  /*                              */
  /*     Helper function to function FacePulseRate.  */
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
  /*     For a description of the assumptions behind the use of the following operations to classify */
  /*     pixels as skin, see function SkinSegmentMask_Ops.  */
  /*  */
  /*     Classify individual pixels as skin or non-skin using the following operations: */
  /*  */
  /*     (1) Pixel-color thresholds: */
  /*  */
  /*         YCbCr thresholds */
  /*  */
  /*         Compare the color values and color ratios of individual pixels from the YCbCr colorspace  */
  /*         to specified thresholds. Use either the generic color thresholds  */
  /*         (YCbCrThresholds_Generic), which are set by function SkinSegment_ConfigSetup, or tailored  */
  /*         color thresholds (YCbCrThresholds_Tailored), which are set by function  */
  /*         SkinSegment_SetThresholds based upon skin-color samples observed in the video.  */
  /*  */
  /*         The use of tailored thresholds is specified by argument TailoredThresholdsTF. However, use  */
  /*         generic thresholds when TailoredThresholdsTF is true if the criterion for using tailored     */
  /*         thresholds has not been satisfied, which is indicated by DontUseTailoredTF == true.       */
  /*      */
  /*         HS thresholds */
  /*  */
  /*         Compare the color values of individual pixels from the H and S channels of the HSV    */
  /*         colorspace to specified thresholds, HSThresholds. */
  /*  */
  /*         The use of the H and S thresholds is specified by argument TailoredThresholdsTF. However,   */
  /*         do not use these thresholds when TailoredThresholdsTF is true if the criterion for using      */
  /*         tailored thresholds has not been satisfied, which is indicated by DontUseTailoredTF ==  */
  /*         true.         */
  /*  */
  /*     (2) Compare the local color range of individual pixels to a specified threshold,  */
  /*         RangeThreshold.         */
  /*      */
  /*     Also return the YCbCr and HS color channels used in operations for operations in other  */
  /*     functions. Always return the Y channel. Only return the Cb and Cr channels if ReturnCbCrTF ==  */
  /*     true. Only return the H and S channels if ReturnHSTF == true.    */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
  /*     the Responsible AI License (RAIL). */
  /* %%%%% Code-generation settings %%%%%% */
  /* Declare variables: */
  /*                                    Upp. Bounds    Var. Size (T/F) */
  /* %%%%% Parse optional X- and Y-coordinate offsets %%%%%% */
  /* Initialize flag to use a linear index */
  /* A linear index will be used when neither an X offset nor a Y offset is specified. */
  UseLinIdxTF = true;

  /* Set flags indicating whether an X or Y offset is specified. */
  /* Scalars; type int32. */
  /* Note: -1 indicates the offset is not specified. */
  XOffsetSpecifiedTF = (XOffset != -1);
  YOffsetSpecifiedTF = (YOffset != -1);
  if (XOffsetSpecifiedTF || YOffsetSpecifiedTF) {
    /* Flag to use subscript indices rather than a linear index */
    UseLinIdxTF = false;

    /* If XOffset not specified, use 1 */
    if (!XOffsetSpecifiedTF) {
      XOffset = 1;
    }

    /* If YOffset not specified, use 1     */
    if (!YOffsetSpecifiedTF) {
      YOffset = 1;
    }
  }

  /* %%%%% Assign structuring objects for the local range operations %%%%%% */
  /* Note that mex files, as of the time of implementation, cannot accept strel objects as input      */
  /* arguments, so the strel objects are assigned within the current function. Strel objects cannot be */
  /* assigned as constants (i.e., by coder.const), so, for efficiency, they are declared persistent so  */
  /* that assignment occurs only once. */
  /* Note that persistent variables cannot be declared within a parfor call. For this reason, these */
  /* variables are declared here rather than in the function, SkinSegmentMask_Threshold_Range, for  */
  /* which they are used. */
  /* %%%%% Apply thresholds %%%%%% */
  /* %%%%%% --- Compiled version of function %%%%%%  */
  /* Parallel processing operations increase efficiency of the compiled version of the function but  */
  /* decrease the efficiency of Matlab code, so conduct parallel processing operations only for the  */
  /* compiled version of the function. */
  /* code generation running */
  /* %%%%% >>>>>> If IsSkinMask_Range is not provided as input %%%%%% */
  if ((IsSkinMask_Range->size[0] == 0) || (IsSkinMask_Range->size[1] == 0)) {
    emxInitMatrix_cell_wrap_2(ParCell1, true);
    emxInitMatrix_cell_wrap_3(ParCell2, true);

    /* Apply the color thresholds and the local-range threshold in parallel. Note that the   */
    /* parallel-for loop is coded such that it actually acts like a pareval operation. */
    /* Preallocate cells to hold results from parallel operations: */
    /* Cell array to hold YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single, and */
    /* SBounded_Single. */
    /*  cells on this line will not be assigned */
    /* Cell array to hold IsSkinMask and IsSkinMask_Range */
    emlrtEnterParallelRegion(aTLS, omp_in_parallel());
    emlrtPushJmpBuf(aTLS, &emlrtJBStack);

#pragma omp parallel \
 num_threads(emlrtAllocRegionTLSs(aTLS, omp_in_parallel(), omp_get_max_threads(), 2)) \
 private(b_RBounded_Uint8,i2,c_loop_ub,emlrtJBEnviron) \
 firstprivate(aTLS,emlrtHadParallelError)

    {
      aTLS = emlrtAllocTLS(aTLS, omp_get_thread_num());
      emlrtSetJmpBuf(aTLS, &emlrtJBEnviron);
      if (setjmp(emlrtJBEnviron) == 0) {
        emxInit_uint8_T(aTLS, &b_RBounded_Uint8, 2, true);
      } else {
        emlrtHadParallelError = true;
      }

#pragma omp for nowait

      for (i = 0; i < 2; i++) {
        if (emlrtHadParallelError)
          continue;
        if (setjmp(emlrtJBEnviron) == 0) {
          /* Run operations in parallel */
          /* Only use 2 threads. */
          /* Apply YCbCr and HS thresholds:    */
          if (i + 1 == 1) {
            /* Note: SkinSegmentMask_Threshold_Colors is a custom function located within folder  */
            /* 'FacePulseRate'. */
            /*  skin-segmentation mask based on color thresholds */
            /*  Y channel matrix */
            /*  Cb channel matrix */
            /*  Cr channel matrix */
            /*  H channel matrix */
            /*  S channel matrix */
            i2 = ParCell1[0].f1[0].f1->size[0] * ParCell1[0].f1[0].f1->size[1];
            ParCell1[0].f1[0].f1->size[0] = YBounded_Single->size[0];
            ParCell1[0].f1[0].f1->size[1] = YBounded_Single->size[1];
            emxEnsureCapacity_real32_T(ParCell1[0].f1[0].f1, i2);
            c_loop_ub = YBounded_Single->size[0] * YBounded_Single->size[1];
            for (i2 = 0; i2 < c_loop_ub; i2++) {
              ParCell1[0].f1[0].f1->data[i2] = YBounded_Single->data[i2];
            }

            i2 = ParCell1[0].f1[1].f1->size[0] * ParCell1[0].f1[1].f1->size[1];
            ParCell1[0].f1[1].f1->size[0] = CbBounded_Single->size[0];
            ParCell1[0].f1[1].f1->size[1] = CbBounded_Single->size[1];
            emxEnsureCapacity_real32_T(ParCell1[0].f1[1].f1, i2);
            c_loop_ub = CbBounded_Single->size[0] * CbBounded_Single->size[1];
            for (i2 = 0; i2 < c_loop_ub; i2++) {
              ParCell1[0].f1[1].f1->data[i2] = CbBounded_Single->data[i2];
            }

            i2 = ParCell1[0].f1[2].f1->size[0] * ParCell1[0].f1[2].f1->size[1];
            ParCell1[0].f1[2].f1->size[0] = CrBounded_Single->size[0];
            ParCell1[0].f1[2].f1->size[1] = CrBounded_Single->size[1];
            emxEnsureCapacity_real32_T(ParCell1[0].f1[2].f1, i2);
            c_loop_ub = CrBounded_Single->size[0] * CrBounded_Single->size[1];
            for (i2 = 0; i2 < c_loop_ub; i2++) {
              ParCell1[0].f1[2].f1->data[i2] = CrBounded_Single->data[i2];
            }

            i2 = ParCell1[0].f1[3].f1->size[0] * ParCell1[0].f1[3].f1->size[1];
            ParCell1[0].f1[3].f1->size[0] = HBounded_Single->size[0];
            ParCell1[0].f1[3].f1->size[1] = HBounded_Single->size[1];
            emxEnsureCapacity_real32_T(ParCell1[0].f1[3].f1, i2);
            c_loop_ub = HBounded_Single->size[0] * HBounded_Single->size[1];
            for (i2 = 0; i2 < c_loop_ub; i2++) {
              ParCell1[0].f1[3].f1->data[i2] = HBounded_Single->data[i2];
            }

            i2 = ParCell1[0].f1[4].f1->size[0] * ParCell1[0].f1[4].f1->size[1];
            ParCell1[0].f1[4].f1->size[0] = SBounded_Single->size[0];
            ParCell1[0].f1[4].f1->size[1] = SBounded_Single->size[1];
            emxEnsureCapacity_real32_T(ParCell1[0].f1[4].f1, i2);
            c_loop_ub = SBounded_Single->size[0] * SBounded_Single->size[1];
            for (i2 = 0; i2 < c_loop_ub; i2++) {
              ParCell1[0].f1[4].f1->data[i2] = SBounded_Single->data[i2];
            }

            c_SkinSegmentMask_Threshold_Col(RBounded_Uint8, GBounded_Uint8,
              BBounded_Uint8, ParCell1[0].f1[0].f1, ParCell1[0].f1[1].f1,
              ParCell1[0].f1[2].f1, ParCell1[0].f1[3].f1, ParCell1[0].f1[4].f1,
              NRows_Matrix, NCols_Matrix, NElements_Matrix, TailoredThresholdsTF,
              DontUseTailoredTF, YCbCrThresholds_Generic,
              YCbCrThresholds_Tailored, ReturnYTF, ReturnCbCrTF, ReturnHSTF,
              HSThresholds_Generic, HSThresholds_Tailored, UseLinIdxTF, XOffset,
              YOffset, ParCell2[0].f1);

            /* Apply local-range threshold: */
          } else {
            /* i == 2 */
            /* Local range threshold   */
            /* Local function. */
            /* M x N matrix; type logical. */
            /*  skin-segmentation mask based on local color range threshold */
            i2 = b_RBounded_Uint8->size[0] * b_RBounded_Uint8->size[1];
            b_RBounded_Uint8->size[0] = RBounded_Uint8->size[0];
            b_RBounded_Uint8->size[1] = RBounded_Uint8->size[1];
            emxEnsureCapacity_uint8_T(b_RBounded_Uint8, i2);
            c_loop_ub = RBounded_Uint8->size[0] * RBounded_Uint8->size[1] - 1;
            for (i2 = 0; i2 <= c_loop_ub; i2++) {
              b_RBounded_Uint8->data[i2] = RBounded_Uint8->data[i2];
            }

            ApplyRangeThreshold(aTLS, b_RBounded_Uint8, RangeNeighborhoodWidth,
                                RangeThreshold, UseLinIdxTF, XOffset, YOffset,
                                NRows_Matrix, NCols_Matrix, ParCell2[1].f1);

            /* Unused values to satisfy parfor requirements */
          }
        } else {
          emlrtHadParallelError = true;
        }
      }

      if (!emlrtHadParallelError) {
        emlrtHeapReferenceStackLeaveScope(aTLS, 1);
        emxFree_uint8_T(&b_RBounded_Uint8);
      }
    }

    emlrtPopJmpBuf(aTLS, &emlrtJBStack);
    emlrtExitParallelRegion(aTLS, omp_in_parallel());

    /* Extract results from parallel operations: */
    b_i = YBounded_Single->size[0] * YBounded_Single->size[1];
    YBounded_Single->size[0] = ParCell1[0].f1[0].f1->size[0];
    YBounded_Single->size[1] = ParCell1[0].f1[0].f1->size[1];
    emxEnsureCapacity_real32_T(YBounded_Single, b_i);
    loop_ub = ParCell1[0].f1[0].f1->size[1];
    for (b_i = 0; b_i < loop_ub; b_i++) {
      b_loop_ub = ParCell1[0].f1[0].f1->size[0];
      for (i1 = 0; i1 < b_loop_ub; i1++) {
        YBounded_Single->data[i1 + YBounded_Single->size[0] * b_i] = ParCell1[0]
          .f1[0].f1->data[i1 + ParCell1[0].f1[0].f1->size[0] * b_i];
      }
    }

    b_i = CbBounded_Single->size[0] * CbBounded_Single->size[1];
    CbBounded_Single->size[0] = ParCell1[0].f1[1].f1->size[0];
    CbBounded_Single->size[1] = ParCell1[0].f1[1].f1->size[1];
    emxEnsureCapacity_real32_T(CbBounded_Single, b_i);
    loop_ub = ParCell1[0].f1[1].f1->size[1];
    for (b_i = 0; b_i < loop_ub; b_i++) {
      b_loop_ub = ParCell1[0].f1[1].f1->size[0];
      for (i1 = 0; i1 < b_loop_ub; i1++) {
        CbBounded_Single->data[i1 + CbBounded_Single->size[0] * b_i] = ParCell1
          [0].f1[1].f1->data[i1 + ParCell1[0].f1[1].f1->size[0] * b_i];
      }
    }

    b_i = CrBounded_Single->size[0] * CrBounded_Single->size[1];
    CrBounded_Single->size[0] = ParCell1[0].f1[2].f1->size[0];
    CrBounded_Single->size[1] = ParCell1[0].f1[2].f1->size[1];
    emxEnsureCapacity_real32_T(CrBounded_Single, b_i);
    loop_ub = ParCell1[0].f1[2].f1->size[1];
    for (b_i = 0; b_i < loop_ub; b_i++) {
      b_loop_ub = ParCell1[0].f1[2].f1->size[0];
      for (i1 = 0; i1 < b_loop_ub; i1++) {
        CrBounded_Single->data[i1 + CrBounded_Single->size[0] * b_i] = ParCell1
          [0].f1[2].f1->data[i1 + ParCell1[0].f1[2].f1->size[0] * b_i];
      }
    }

    b_i = HBounded_Single->size[0] * HBounded_Single->size[1];
    HBounded_Single->size[0] = ParCell1[0].f1[3].f1->size[0];
    HBounded_Single->size[1] = ParCell1[0].f1[3].f1->size[1];
    emxEnsureCapacity_real32_T(HBounded_Single, b_i);
    loop_ub = ParCell1[0].f1[3].f1->size[1];
    for (b_i = 0; b_i < loop_ub; b_i++) {
      b_loop_ub = ParCell1[0].f1[3].f1->size[0];
      for (i1 = 0; i1 < b_loop_ub; i1++) {
        HBounded_Single->data[i1 + HBounded_Single->size[0] * b_i] = ParCell1[0]
          .f1[3].f1->data[i1 + ParCell1[0].f1[3].f1->size[0] * b_i];
      }
    }

    b_i = SBounded_Single->size[0] * SBounded_Single->size[1];
    SBounded_Single->size[0] = ParCell1[0].f1[4].f1->size[0];
    SBounded_Single->size[1] = ParCell1[0].f1[4].f1->size[1];
    emxEnsureCapacity_real32_T(SBounded_Single, b_i);
    loop_ub = ParCell1[0].f1[4].f1->size[1];
    for (b_i = 0; b_i < loop_ub; b_i++) {
      b_loop_ub = ParCell1[0].f1[4].f1->size[0];
      for (i1 = 0; i1 < b_loop_ub; i1++) {
        SBounded_Single->data[i1 + SBounded_Single->size[0] * b_i] = ParCell1[0]
          .f1[4].f1->data[i1 + ParCell1[0].f1[4].f1->size[0] * b_i];
      }
    }

    emxFreeMatrix_cell_wrap_2(ParCell1);
    b_i = IsSkinMask->size[0] * IsSkinMask->size[1];
    IsSkinMask->size[0] = ParCell2[0].f1->size[0];
    IsSkinMask->size[1] = ParCell2[0].f1->size[1];
    emxEnsureCapacity_boolean_T(IsSkinMask, b_i);
    loop_ub = ParCell2[0].f1->size[0] * ParCell2[0].f1->size[1];
    for (b_i = 0; b_i < loop_ub; b_i++) {
      IsSkinMask->data[b_i] = ParCell2[0].f1->data[b_i];
    }

    b_i = IsSkinMask_Range->size[0] * IsSkinMask_Range->size[1];
    IsSkinMask_Range->size[0] = ParCell2[1].f1->size[0];
    IsSkinMask_Range->size[1] = ParCell2[1].f1->size[1];
    emxEnsureCapacity_boolean_T(IsSkinMask_Range, b_i);
    loop_ub = ParCell2[1].f1->size[1];
    for (b_i = 0; b_i < loop_ub; b_i++) {
      b_loop_ub = ParCell2[1].f1->size[0];
      for (i1 = 0; i1 < b_loop_ub; i1++) {
        IsSkinMask_Range->data[i1 + IsSkinMask_Range->size[0] * b_i] = ParCell2
          [1].f1->data[i1 + ParCell2[1].f1->size[0] * b_i];
      }
    }

    emxFreeMatrix_cell_wrap_3(ParCell2);

    /* %%%%% >>>>>> If IsSkinMask_Range is provided %%%%%% */
  } else {
    /* Note: SkinSegmentMask_Threshold_Colors is a custom function located within folder */
    /* 'FacePulseRate'. */
    c_SkinSegmentMask_Threshold_Col(RBounded_Uint8, GBounded_Uint8,
      BBounded_Uint8, YBounded_Single, CbBounded_Single, CrBounded_Single,
      HBounded_Single, SBounded_Single, NRows_Matrix, NCols_Matrix,
      NElements_Matrix, TailoredThresholdsTF, DontUseTailoredTF,
      YCbCrThresholds_Generic, YCbCrThresholds_Tailored, ReturnYTF, ReturnCbCrTF,
      ReturnHSTF, HSThresholds_Generic, HSThresholds_Tailored, UseLinIdxTF,
      XOffset, YOffset, IsSkinMask);
  }

  /* %%%%%% --- Non-compiled version of function %%%%%%  */
  /* %%%%% Combine skin-segmentation masks %%%%%% */
  /* Loop across skin-segmentation mask elements */
  for (loop_ub = 0; loop_ub < NElements_Matrix; loop_ub++) {
    if (IsSkinMask->data[loop_ub] && IsSkinMask_Range->data[loop_ub]) {
      IsSkinMask->data[loop_ub] = true;
    } else {
      IsSkinMask->data[loop_ub] = false;
    }
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(aTLS);
}

void SkinSegmentMask_Threshold_free(void)
{
  SE3_not_empty = false;
  SE5_not_empty = false;
  SE7_not_empty = false;
  SE9_not_empty = false;
}

void SkinSegmentMask_Threshold_init(void)
{
  /* only need to check one as all assigned at same time */
  /* Assign structuring element */
  /* Note: for code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  width of structuring element */
  SE3_not_empty = true;

  /* Assign structuring element */
  /* Note: for code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  width of structuring element */
  SE5_not_empty = true;

  /* Assign structuring element */
  /* Note: for code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  width of structuring element */
  SE7_not_empty = true;

  /* Assign structuring element */
  /* Note: for code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  width of structuring element */
  SE9_not_empty = true;
}

/* End of code generation (SkinSegmentMask_Threshold.c) */
