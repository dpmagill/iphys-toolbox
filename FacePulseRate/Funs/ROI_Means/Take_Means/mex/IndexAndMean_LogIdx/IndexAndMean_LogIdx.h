/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * IndexAndMean_LogIdx.h
 *
 * Code generation for function 'IndexAndMean_LogIdx'
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
#include "IndexAndMean_LogIdx_types.h"

/* Function Declarations */
void IndexAndMean_LogIdx(emlrtCTX aTLS, const emxArray_uint8_T *R_Uint8, const
  emxArray_uint8_T *G_Uint8, const emxArray_uint8_T *B_Uint8, const
  emxArray_real32_T *Luminance_Single, const emxArray_boolean_T *LogIdx, int32_T
  NRows, int32_T NCols, uint32_T TrueCount, boolean_T TakeLuminanceMeanTF,
  real_T RGBMeans_Double[3], real_T *LuminanceMean_Double);

/* End of code generation (IndexAndMean_LogIdx.h) */
