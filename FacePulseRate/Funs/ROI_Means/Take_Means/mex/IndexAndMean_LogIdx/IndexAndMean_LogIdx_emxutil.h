/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * IndexAndMean_LogIdx_emxutil.h
 *
 * Code generation for function 'IndexAndMean_LogIdx_emxutil'
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
void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_real32_T(emxArray_real32_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_uint8_T(emxArray_uint8_T *emxArray, int32_T oldNumel);
void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
void emxFree_real32_T(emxArray_real32_T **pEmxArray);
void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int32_T numDimensions,
  boolean_T doPush);
void emxInit_real32_T(emxArray_real32_T **pEmxArray, int32_T numDimensions,
                      boolean_T doPush);
void emxInit_uint8_T(emxArray_uint8_T **pEmxArray, int32_T numDimensions,
                     boolean_T doPush);

/* End of code generation (IndexAndMean_LogIdx_emxutil.h) */
