/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinSegmentMask_Ops_emxutil.h
 *
 * Code generation for function 'SkinSegmentMask_Ops_emxutil'
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
void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_real32_T(emxArray_real32_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_uint32_T(emxArray_uint32_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_uint8_T(emxArray_uint8_T *emxArray, int32_T oldNumel);
void emxFreeMatrix_cell_wrap_2(cell_wrap_2 pMatrix[2]);
void emxFreeMatrix_cell_wrap_3(cell_wrap_3 pMatrix[2]);
void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
void emxFree_real32_T(emxArray_real32_T **pEmxArray);
void emxFree_real_T(emxArray_real_T **pEmxArray);
void emxFree_uint32_T(emxArray_uint32_T **pEmxArray);
void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
void emxInitMatrix_cell_wrap_2(cell_wrap_2 pMatrix[2], boolean_T doPush);
void emxInitMatrix_cell_wrap_3(cell_wrap_3 pMatrix[2], boolean_T doPush);
void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int32_T numDimensions,
  boolean_T doPush);
void emxInit_real32_T(emxArray_real32_T **pEmxArray, int32_T numDimensions,
                      boolean_T doPush);
void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions,
                    boolean_T doPush);
void emxInit_uint32_T(emxArray_uint32_T **pEmxArray, int32_T numDimensions,
                      boolean_T doPush);
void emxInit_uint8_T(emlrtCTX aTLS, emxArray_uint8_T **pEmxArray, int32_T
                     numDimensions, boolean_T doPush);

/* End of code generation (SkinSegmentMask_Ops_emxutil.h) */
