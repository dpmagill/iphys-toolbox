/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertTextFast_Font14LT_emxutil.h
 *
 * Code generation for function 'insertTextFast_Font14LT_emxutil'
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
#include "insertTextFast_Font14LT_types.h"

/* Function Declarations */
void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_cell_wrap_0(emxArray_cell_wrap_0 *emxArray, int32_T
  oldNumel);
void emxEnsureCapacity_char_T(emxArray_char_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_int16_T(emxArray_int16_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_int8_T(emxArray_int8_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_uint16_T(emxArray_uint16_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_uint32_T(emxArray_uint32_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_uint8_T(emxArray_uint8_T *emxArray, int32_T oldNumel);
void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
void emxFree_cell_wrap_0(emxArray_cell_wrap_0 **pEmxArray);
void emxFree_int16_T(emxArray_int16_T **pEmxArray);
void emxFree_int32_T(emxArray_int32_T **pEmxArray);
void emxFree_int8_T(emxArray_int8_T **pEmxArray);
void emxFree_real_T(emxArray_real_T **pEmxArray);
void emxFree_uint16_T(emxArray_uint16_T **pEmxArray);
void emxFree_uint32_T(emxArray_uint32_T **pEmxArray);
void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int32_T numDimensions,
  boolean_T doPush);
void emxInit_cell_wrap_0(emxArray_cell_wrap_0 **pEmxArray, int32_T numDimensions,
  boolean_T doPush);
void emxInit_int16_T(emxArray_int16_T **pEmxArray, int32_T numDimensions,
                     boolean_T doPush);
void emxInit_int32_T(emxArray_int32_T **pEmxArray, int32_T numDimensions,
                     boolean_T doPush);
void emxInit_int8_T(emxArray_int8_T **pEmxArray, int32_T numDimensions,
                    boolean_T doPush);
void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions,
                    boolean_T doPush);
void emxInit_uint16_T(emxArray_uint16_T **pEmxArray, int32_T numDimensions,
                      boolean_T doPush);
void emxInit_uint32_T(emxArray_uint32_T **pEmxArray, int32_T numDimensions,
                      boolean_T doPush);
void emxInit_uint8_T(emxArray_uint8_T **pEmxArray, int32_T numDimensions,
                     boolean_T doPush);

/* End of code generation (insertTextFast_Font14LT_emxutil.h) */
