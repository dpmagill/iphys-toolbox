/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIMSIR_emxutil.h
 *
 * Code generation for function 'ROIMSIR_emxutil'
 *
 */

#pragma once

/* Include files */
#include "ROIMSIR_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void c_emxFreeStruct_coder_internal_(coder_internal_SortedBuffer *pStruct);
void c_emxInitStruct_coder_internal_(coder_internal_SortedBuffer *pStruct,
  boolean_T doPush);
void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_char_T(emxArray_char_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_int16_T(emxArray_int16_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_real32_T(emxArray_real32_T *emxArray, int32_T oldNumel);
void emxFreeStruct_struct0_T(struct0_T *pStruct);
void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
void emxFree_char_T(emxArray_char_T **pEmxArray);
void emxFree_int16_T(emxArray_int16_T **pEmxArray);
void emxFree_int32_T(emxArray_int32_T **pEmxArray);
void emxFree_real32_T(emxArray_real32_T **pEmxArray);
void emxInitStruct_struct0_T(struct0_T *pStruct, boolean_T doPush);
void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int32_T numDimensions,
  boolean_T doPush);
void emxInit_char_T(emxArray_char_T **pEmxArray, int32_T numDimensions,
                    boolean_T doPush);
void emxInit_int16_T(emxArray_int16_T **pEmxArray, int32_T numDimensions,
                     boolean_T doPush);
void emxInit_int32_T(emxArray_int32_T **pEmxArray, int32_T numDimensions,
                     boolean_T doPush);
void emxInit_real32_T(emxArray_real32_T **pEmxArray, int32_T numDimensions,
                      boolean_T doPush);

/* End of code generation (ROIMSIR_emxutil.h) */
