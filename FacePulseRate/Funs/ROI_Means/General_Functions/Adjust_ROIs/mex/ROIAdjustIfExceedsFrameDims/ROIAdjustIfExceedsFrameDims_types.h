/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIAdjustIfExceedsFrameDims_types.h
 *
 * Code generation for function 'ROIAdjustIfExceedsFrameDims_types'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_int16_T
#define struct_emxArray_int16_T

struct emxArray_int16_T
{
  int16_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_int16_T*/

#ifndef typedef_emxArray_int16_T
#define typedef_emxArray_int16_T

typedef struct emxArray_int16_T emxArray_int16_T;

#endif                                 /*typedef_emxArray_int16_T*/

/* End of code generation (ROIAdjustIfExceedsFrameDims_types.h) */
