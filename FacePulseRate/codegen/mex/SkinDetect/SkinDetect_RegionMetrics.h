/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect_RegionMetrics.h
 *
 * Code generation for function 'SkinDetect_RegionMetrics'
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
void SkinDetect_RegionMetrics(emlrtCTX aTLS, const b_struct_T
  RegionIndices_data[], int32_T NRegions, const real32_T
  RegionNPixels_Single_data[], const emxArray_uint8_T *RBounded_Uint8, const
  emxArray_uint8_T *GBounded_Uint8, const emxArray_uint8_T *BBounded_Uint8,
  const emxArray_real32_T *YBounded_Single, const emxArray_real32_T
  *CbBounded_Single, const emxArray_real32_T *CrBounded_Single, real32_T
  MeanOfMeansY, real32_T MeanOfMeansCb, real32_T MeanOfMeansCr, real32_T
  StdDevOfMeansY, real32_T StdDevOfMeansCb, real32_T StdDevOfMeansCr, real_T
  RegionRGBMeans_data[], int32_T RegionRGBMeans_size[2], real32_T
  region_Z_Y_data[], int32_T region_Z_Y_size[1], real32_T region_Z_Cb_data[],
  int32_T region_Z_Cb_size[1], real32_T region_Z_Cr_data[], int32_T
  region_Z_Cr_size[1], real32_T region_SD_Cr_data[], int32_T region_SD_Cr_size[1]);

/* End of code generation (SkinDetect_RegionMetrics.h) */
