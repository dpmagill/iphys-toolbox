/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ConfirmSkinPresent_SkinDetectReject.h
 *
 * Code generation for function 'ConfirmSkinPresent_SkinDetectReject'
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
#include "ConfirmSkinPresent_SkinDetectReject_types.h"

/* Function Declarations */
int32_T ConfirmSkinPresent_SkinDetectReject(emxArray_boolean_T *IsSkinMask,
  const emxArray_uint8_T *RBounded_Uint8, const emxArray_uint8_T *GBounded_Uint8,
  const emxArray_uint8_T *BBounded_Uint8, const emxArray_real32_T
  *YBounded_Single, const emxArray_real32_T *CbBounded_Single, const
  emxArray_real32_T *CrBounded_Single, int32_T NRows_Matrix, int32_T
  NCols_Matrix, const struct0_T *SkinDetectConfig);

/* End of code generation (ConfirmSkinPresent_SkinDetectReject.h) */
