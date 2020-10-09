/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinSegmentMask_Threshold.h
 *
 * Code generation for function 'SkinSegmentMask_Threshold'
 *
 */

#pragma once

/* Include files */
#include "SkinDetect_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void SkinSegmentMask_Threshold(emlrtCTX aTLS, const emxArray_uint8_T
  *RBounded_Uint8, const emxArray_uint8_T *GBounded_Uint8, const
  emxArray_uint8_T *BBounded_Uint8, emxArray_boolean_T *IsSkinMask_Range,
  int32_T NRows_Matrix, int32_T NCols_Matrix, int32_T NElements_Matrix, const
  real32_T YCbCrThresholds_Generic[7], boolean_T DontUseTailoredTF, const
  real32_T YCbCrThresholds_Tailored[8], const real32_T HSThresholds_Generic[2],
  const real32_T HSThresholds_Tailored[3], int16_T RangeNeighborhoodWidth,
  uint8_T RangeThreshold, emxArray_boolean_T *IsSkinMask, emxArray_real32_T
  *YBounded_Single, emxArray_real32_T *CbBounded_Single, emxArray_real32_T
  *CrBounded_Single, real32_T HBounded_Single_data[], int32_T
  HBounded_Single_size[2], real32_T SBounded_Single_data[], int32_T
  SBounded_Single_size[2]);
void SkinSegmentMask_Threshold_free(void);
void SkinSegmentMask_Threshold_init(void);
void b_SkinSegmentMask_Threshold(emlrtCTX aTLS, const emxArray_uint8_T
  *RBounded_Uint8, const emxArray_uint8_T *GBounded_Uint8, const
  emxArray_uint8_T *BBounded_Uint8, emxArray_boolean_T *IsSkinMask_Range,
  int32_T NRows_Matrix, int32_T NCols_Matrix, int32_T NElements_Matrix, const
  real32_T YCbCrThresholds_Generic[7], boolean_T DontUseTailoredTF, const
  real32_T YCbCrThresholds_Tailored[8], const real32_T HSThresholds_Generic[2],
  const real32_T HSThresholds_Tailored[3], int16_T RangeNeighborhoodWidth,
  uint8_T RangeThreshold, emxArray_boolean_T *IsSkinMask, real32_T
  YBounded_Single_data[], int32_T YBounded_Single_size[2], real32_T
  CbBounded_Single_data[], int32_T CbBounded_Single_size[2], real32_T
  CrBounded_Single_data[], int32_T CrBounded_Single_size[2], real32_T
  HBounded_Single_data[], int32_T HBounded_Single_size[2], real32_T
  SBounded_Single_data[], int32_T SBounded_Single_size[2]);

/* End of code generation (SkinSegmentMask_Threshold.h) */
