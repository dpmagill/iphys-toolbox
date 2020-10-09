/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect_PartitionRegions.h
 *
 * Code generation for function 'SkinDetect_PartitionRegions'
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
void BoundSeparateChannels(emlrtCTX aTLS, const emxArray_uint8_T *VidFrame,
  const int16_T BoundingBoxSkin[4], int16_T nRows_IsSkinMask_int16, int16_T
  nCols_IsSkinMask_int16, int16_T nCols_Full_int16, int16_T nRows_Full_int16,
  emxArray_uint8_T *RBounded_Uint8, emxArray_uint8_T *GBounded_Uint8,
  emxArray_uint8_T *BBounded_Uint8);

/* End of code generation (SkinDetect_PartitionRegions.h) */
