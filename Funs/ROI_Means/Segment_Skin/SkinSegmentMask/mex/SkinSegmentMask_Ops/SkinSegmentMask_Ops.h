/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinSegmentMask_Ops.h
 *
 * Code generation for function 'SkinSegmentMask_Ops'
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
#include "SkinSegmentMask_Ops_types.h"

/* Function Declarations */
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
  *HBounded_Single, emxArray_real32_T *SBounded_Single);

/* End of code generation (SkinSegmentMask_Ops.h) */
