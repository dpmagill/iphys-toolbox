/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect_ROIValidate.c
 *
 * Code generation for function 'SkinDetect_ROIValidate'
 *
 */

/* Include files */
#include "SkinDetect_ROIValidate.h"
#include "SkinDetect_emxutil.h"
#include "SkinDetect_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void CropVidAndSeparateChannels(emlrtCTX aTLS, const emxArray_uint8_T *VidFrame,
  int16_T x_int16, int16_T y_int16, int16_T width_int16, int16_T height_int16,
  int16_T NCols_VidFrame_int16, int16_T NRows_VidFrame_int16, emxArray_uint8_T
  *RUint8, emxArray_uint8_T *GUint8, emxArray_uint8_T *BUint8)
{
  jmp_buf * volatile emlrtJBStack;
  int32_T ColOffset;
  int32_T LinIdxFull;
  int32_T NPageElements;
  int32_T NPageElementsBy2;
  int32_T NRows_VidFrame;
  int32_T RowOffset;
  int32_T height;
  int32_T i;
  int32_T iFull;
  int32_T j;
  int32_T ub_loop;
  uint8_T jth;

  /* end local function */
  /* ============================================================================================= */
  /* CropVidAndSeparateChannels  Crop the video and separate it by color channels. */
  /* Inline function */
  /* Cast to int32 to prevent overflow when converting to linear index */
  /* Scalars; type int32. */
  /* ROI values of selected ROI */
  height = height_int16;

  /* Dimensions of the full frame */
  NRows_VidFrame = NRows_VidFrame_int16;

  /* Number of elements in one color channel of the full frame */
  /* Scalar; type int32. */
  NPageElements = NCols_VidFrame_int16 * NRows_VidFrame_int16;

  /* Number multiplied by 2 */
  /* Scalar; type int32. */
  NPageElementsBy2 = NPageElements << 1;

  /* Preallocate */
  ColOffset = RUint8->size[0] * RUint8->size[1];
  RUint8->size[0] = height_int16;
  RUint8->size[1] = width_int16;
  emxEnsureCapacity_uint8_T(RUint8, ColOffset);
  ColOffset = GUint8->size[0] * GUint8->size[1];
  GUint8->size[0] = height_int16;
  GUint8->size[1] = width_int16;
  emxEnsureCapacity_uint8_T(GUint8, ColOffset);
  ColOffset = BUint8->size[0] * BUint8->size[1];
  BUint8->size[0] = height_int16;
  BUint8->size[1] = width_int16;
  emxEnsureCapacity_uint8_T(BUint8, ColOffset);

  /* Cropping offsets */
  /* Scalars; type int32. */
  /* Note: the step prevents repeated subtraction by one in the parfor loop. */
  ColOffset = x_int16 - 1;
  RowOffset = y_int16 - 1;

  /* Prevent dynamic memory allocation from colon operator by asserting lengths */
  /* Note: these values also constrain the maximum frame dimensions that can be used in function */
  /* FacePulseRate. If modified, modify the maximum frame dimensions stated in the description in */
  /* function FacePulseRate.  */
  ub_loop = width_int16 - 1;
  emlrtEnterParallelRegion(aTLS, omp_in_parallel());
  emlrtPushJmpBuf(aTLS, &emlrtJBStack);

#pragma omp parallel for \
 num_threads(emlrtAllocRegionTLSs(aTLS, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs())) \
 private(jth,LinIdxFull,iFull,j)

  for (i = 0; i <= ub_loop; i++) {
    /* Bound frame and separate to channels: */
    /* Loop across columns */
    /* Column index for full frame */
    iFull = (i + ColOffset) + 1;

    /* Loop across rows */
    for (j = 0; j < height; j++) {
      /* Row index for full frame */
      LinIdxFull = (j + RowOffset) + 1;

      /* Convert from subscript indices to a linear index for more efficient indexing */
      /* Scalar; type int32. */
      /* Note: In compiled C code, the faster indexing outweighs the cost of this conversion. */
      LinIdxFull += (iFull - 1) * NRows_VidFrame;

      /* Red channel element: */
      /* Extract value from full frame                       */
      RUint8->data[j + RUint8->size[0] * i] = VidFrame->data[LinIdxFull - 1];

      /* Insert value into bounded frame */
      /* Green channel element: */
      /* Extract value from full frame */
      GUint8->data[j + GUint8->size[0] * i] = VidFrame->data[(LinIdxFull +
        NPageElements) - 1];

      /* Insert value into bounded frame */
      /* Blue channel element: */
      /* Extract value from full frame */
      jth = VidFrame->data[(LinIdxFull + NPageElementsBy2) - 1];

      /* Insert value into bounded frame */
      BUint8->data[j + BUint8->size[0] * i] = jth;
    }
  }

  emlrtPopJmpBuf(aTLS, &emlrtJBStack);
  emlrtExitParallelRegion(aTLS, omp_in_parallel());

  /* end local function */
}

/* End of code generation (SkinDetect_ROIValidate.c) */
