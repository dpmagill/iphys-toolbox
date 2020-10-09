/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect_PartitionRegions.c
 *
 * Code generation for function 'SkinDetect_PartitionRegions'
 *
 */

/* Include files */
#include "SkinDetect_PartitionRegions.h"
#include "SkinDetect_emxutil.h"
#include "SkinDetect_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void BoundSeparateChannels(emlrtCTX aTLS, const emxArray_uint8_T *VidFrame,
  const int16_T BoundingBoxSkin[4], int16_T nRows_IsSkinMask_int16, int16_T
  nCols_IsSkinMask_int16, int16_T nCols_Full_int16, int16_T nRows_Full_int16,
  emxArray_uint8_T *RBounded_Uint8, emxArray_uint8_T *GBounded_Uint8,
  emxArray_uint8_T *BBounded_Uint8)
{
  jmp_buf * volatile emlrtJBStack;
  int32_T ColOffset;
  int32_T LinIdxFull;
  int32_T NPageElements;
  int32_T NPageElementsBy2;
  int32_T RowOffset;
  int32_T i;
  int32_T iFull;
  int32_T j;
  int32_T nRows_Full;
  int32_T nRows_IsSkinMask;
  int32_T ub_loop;
  uint8_T jth;

  /* end main function */
  /* ============================================================================================= */
  /* Local functions  */
  /* ============================================================================================= */
  /* ============================================================================================= */
  /* BoundSeparateChannels  Bound the input frame and separate it into its colorspace channels. */
  /*  */
  /*     Note:  */
  /*  */
  /*     The parfor-loop is slower than a for-loop when run in Matlab code, so use the parfor-loop only   */
  /*     for code generation. */
  /* %%%%% Code-generation settings %%%%%% */
  /* Inline function */
  /* %%%%% Code generation running %%%%%% */
  /* code generation running */
  /* Cast to int32 to prevent overflow when converting to linear index */
  /* Scalars; type int32. */
  nRows_IsSkinMask = nRows_IsSkinMask_int16;
  nRows_Full = nRows_Full_int16;

  /* X and Y-coordinates */
  /* Cast to int32 to prevent overflow when converting to linear index. */
  /* Scalars; type int32. */
  /* Preallocate channel matrices: */
  /* Red channel  */
  /* M x N matrix; type uint8. */
  ColOffset = RBounded_Uint8->size[0] * RBounded_Uint8->size[1];
  RBounded_Uint8->size[0] = nRows_IsSkinMask_int16;
  RBounded_Uint8->size[1] = nCols_IsSkinMask_int16;
  emxEnsureCapacity_uint8_T(RBounded_Uint8, ColOffset);

  /* Green channel  */
  /* M x N matrix; type uint8.     */
  ColOffset = GBounded_Uint8->size[0] * GBounded_Uint8->size[1];
  GBounded_Uint8->size[0] = nRows_IsSkinMask_int16;
  GBounded_Uint8->size[1] = nCols_IsSkinMask_int16;
  emxEnsureCapacity_uint8_T(GBounded_Uint8, ColOffset);

  /* Blue channel  */
  /* M x N matrix; type uint8.     */
  ColOffset = BBounded_Uint8->size[0] * BBounded_Uint8->size[1];
  BBounded_Uint8->size[0] = nRows_IsSkinMask_int16;
  BBounded_Uint8->size[1] = nCols_IsSkinMask_int16;
  emxEnsureCapacity_uint8_T(BBounded_Uint8, ColOffset);

  /* Bounding offsets */
  /* Scalars; type int32. */
  /* Note: the step prevents repeated subtraction by one in the parfor loop. */
  ColOffset = BoundingBoxSkin[0] - 1;
  RowOffset = BoundingBoxSkin[1] - 1;

  /* Number of elements in one color channel of the full frame */
  /* Scalar; type int32. */
  NPageElements = nCols_Full_int16 * nRows_Full_int16;

  /* Number multiplied by 2 */
  /* Scalar; type int32. */
  NPageElementsBy2 = NPageElements << 1;
  ub_loop = nCols_IsSkinMask_int16 - 1;
  emlrtEnterParallelRegion(aTLS, omp_in_parallel());
  emlrtPushJmpBuf(aTLS, &emlrtJBStack);

#pragma omp parallel for \
 num_threads(emlrtAllocRegionTLSs(aTLS, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs())) \
 private(jth,LinIdxFull,iFull,j)

  for (i = 0; i <= ub_loop; i++) {
    /* Bound frame and separate to channels: */
    /* Loop across columns */
    /* Adjust column index to align with coordinate plane of full frame */
    iFull = (i + ColOffset) + 1;

    /* Loop across rows */
    for (j = 0; j < nRows_IsSkinMask; j++) {
      /* Adjust row index to align with coordinate plane of full frame */
      LinIdxFull = (j + RowOffset) + 1;

      /* Convert from subscript indices to a linear index for more efficient indexing */
      /* Scalar; type int32. */
      /* Note: In compiled C code, the faster indexing outweighs the cost of this conversion. */
      LinIdxFull += (iFull - 1) * nRows_Full;

      /* Red channel element: */
      /* Extract value from full frame                       */
      RBounded_Uint8->data[j + RBounded_Uint8->size[0] * i] = VidFrame->
        data[LinIdxFull - 1];

      /* Insert value into bounded frame */
      /* Green channel element: */
      /* Extract value from full frame */
      GBounded_Uint8->data[j + GBounded_Uint8->size[0] * i] = VidFrame->data
        [(LinIdxFull + NPageElements) - 1];

      /* Insert value into bounded frame */
      /* Blue channel element: */
      /* Extract value from full frame */
      jth = VidFrame->data[(LinIdxFull + NPageElementsBy2) - 1];

      /* Insert value into bounded frame */
      BBounded_Uint8->data[j + BBounded_Uint8->size[0] * i] = jth;
    }
  }

  emlrtPopJmpBuf(aTLS, &emlrtJBStack);
  emlrtExitParallelRegion(aTLS, omp_in_parallel());

  /* %%%%% Code generation not running %%%%%%    */
}

/* End of code generation (SkinDetect_PartitionRegions.c) */
