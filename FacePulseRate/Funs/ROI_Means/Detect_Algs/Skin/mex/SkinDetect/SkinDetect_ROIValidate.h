/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect_ROIValidate.h
 *
 * Code generation for function 'SkinDetect_ROIValidate'
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
void CropVidAndSeparateChannels(emlrtCTX aTLS, const emxArray_uint8_T *VidFrame,
  int16_T x_int16, int16_T y_int16, int16_T width_int16, int16_T height_int16,
  int16_T NCols_VidFrame_int16, int16_T NRows_VidFrame_int16, emxArray_uint8_T
  *RUint8, emxArray_uint8_T *GUint8, emxArray_uint8_T *BUint8);

/* End of code generation (SkinDetect_ROIValidate.h) */
