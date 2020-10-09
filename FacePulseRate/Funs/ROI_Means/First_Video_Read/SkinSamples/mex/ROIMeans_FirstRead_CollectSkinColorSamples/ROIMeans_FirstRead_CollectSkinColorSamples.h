/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIMeans_FirstRead_CollectSkinColorSamples.h
 *
 * Code generation for function 'ROIMeans_FirstRead_CollectSkinColorSamples'
 *
 */

#pragma once

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mex.h"
#include "emlrt.h"
#include "rtwtypes.h"
#include "omp.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_types.h"

/* Function Declarations */
void ROIMeans_FirstRead_CollectSkinColorSamples(const emxArray_real32_T *YSingle,
  const emxArray_real32_T *CbSingle, const emxArray_real32_T *CrSingle, const
  emxArray_uint8_T *RUint8, const emxArray_uint8_T *GUint8, const
  emxArray_uint8_T *BUint8, const emxArray_real32_T *HSingle, const
  emxArray_real32_T *SSingle, const emxArray_boolean_T *IsSkinMask_LocalRange,
  int32_T NRows_Matrix, int32_T NCols_Matrix, const struct0_T
  *SkinSegmentConfig_Args, boolean_T UseCompiledFunctionsTF, real_T
  ithPrimaryROIRGBMeans[3], real32_T ithPrimaryROIYCbCrMeans[3], real32_T
  ithPrimaryROIYCbCrHSMinsMaxs[11]);

/* End of code generation (ROIMeans_FirstRead_CollectSkinColorSamples.h) */
