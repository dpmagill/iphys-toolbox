/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinSegmentMask_Threshold_Colors.h
 *
 * Code generation for function 'SkinSegmentMask_Threshold_Colors'
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
void c_SkinSegmentMask_Threshold_Col(const emxArray_uint8_T *RBounded_Uint8,
  const emxArray_uint8_T *GBounded_Uint8, const emxArray_uint8_T *BBounded_Uint8,
  int32_T NRows_Matrix, int32_T NCols_Matrix, int32_T NElements_Matrix,
  boolean_T DontUseTailoredTF, const real32_T YCbCrThresholds_Generic[7], const
  real32_T YCbCrThresholds_Tailored[8], const real32_T HSThresholds_Generic[2],
  const real32_T HSThresholds_Tailored[3], emxArray_boolean_T *IsSkinMask,
  emxArray_real32_T *YBounded_Single, emxArray_real32_T *CbBounded_Single,
  emxArray_real32_T *CrBounded_Single, int32_T HBounded_Single_size[2], int32_T
  SBounded_Single_size[2]);
void d_SkinSegmentMask_Threshold_Col(const emxArray_uint8_T *RBounded_Uint8,
  const emxArray_uint8_T *GBounded_Uint8, const emxArray_uint8_T *BBounded_Uint8,
  int32_T NRows_Matrix, int32_T NCols_Matrix, int32_T NElements_Matrix,
  boolean_T DontUseTailoredTF, const real32_T YCbCrThresholds_Generic[7], const
  real32_T YCbCrThresholds_Tailored[8], const real32_T HSThresholds_Generic[2],
  const real32_T HSThresholds_Tailored[3], emxArray_boolean_T *IsSkinMask,
  int32_T YBounded_Single_size[2], int32_T CbBounded_Single_size[2], int32_T
  CrBounded_Single_size[2], int32_T HBounded_Single_size[2], int32_T
  SBounded_Single_size[2]);

/* End of code generation (SkinSegmentMask_Threshold_Colors.h) */
