/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect_emxutil.h
 *
 * Code generation for function 'SkinDetect_emxutil'
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
void emxCopyMatrix_real_T(real_T dst[2], const real_T src[2]);
void emxCopyMatrix_real_T1(real_T dst[4], const real_T src[4]);
void emxCopyMatrix_real_T2(real_T dst[16], const real_T src[16]);
void emxCopyStruct_struct_T(c_struct_T *dst, const c_struct_T *src);
void emxCopy_boolean_T_0x0(emxArray_boolean_T_0x0 *dst, const
  emxArray_boolean_T_0x0 *src);
void emxCopy_real_T(emxArray_real_T **dst, emxArray_real_T * const *src);
void emxCopy_real_T_0(emxArray_real_T_0 *dst, const emxArray_real_T_0 *src);
void emxCopy_real_T_1x0(emxArray_real_T_1x0 *dst, const emxArray_real_T_1x0 *src);
void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_int16_T(emxArray_int16_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_real32_T(emxArray_real32_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_struct_T(b_struct_T data[400], const int32_T size[1],
  int32_T oldNumel);
void emxEnsureCapacity_struct_T1(emxArray_struct_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_struct_T2(b_emxArray_struct_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_uint32_T(emxArray_uint32_T *emxArray, int32_T oldNumel);
void emxEnsureCapacity_uint8_T(emxArray_uint8_T *emxArray, int32_T oldNumel);
void emxExpand_struct_T(b_emxArray_struct_T *emxArray, int32_T fromIndex,
  int32_T toIndex);
void emxExpand_struct_T_400(b_struct_T data[400], int32_T fromIndex, int32_T
  toIndex);
void emxFreeMatrix_cell_wrap_1(cell_wrap_1 pMatrix[5]);
void emxFreeMatrix_cell_wrap_2(cell_wrap_2 pMatrix[2]);
void emxFreeMatrix_cell_wrap_3(cell_wrap_3 pMatrix[2]);
void emxFreeMatrix_cell_wrap_32(cell_wrap_32 pMatrix[3]);
void emxFreeStruct_cell_wrap_1(cell_wrap_1 *pStruct);
void emxFreeStruct_cell_wrap_2(cell_wrap_2 *pStruct);
void emxFreeStruct_cell_wrap_3(cell_wrap_3 *pStruct);
void emxFreeStruct_cell_wrap_32(cell_wrap_32 *pStruct);
void emxFreeStruct_struct5_T(struct5_T *pStruct);
void emxFreeStruct_struct8_T(struct8_T *pStruct);
void emxFreeStruct_struct_T(b_struct_T *pStruct);
void emxFreeStruct_struct_T1(d_struct_T *pStruct);
void emxFreeStruct_struct_T2(c_struct_T *pStruct);
void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
void emxFree_int16_T(emxArray_int16_T **pEmxArray);
void emxFree_int32_T(emxArray_int32_T **pEmxArray);
void emxFree_real32_T(emxArray_real32_T **pEmxArray);
void emxFree_real_T(emxArray_real_T **pEmxArray);
void emxFree_struct_T(emxArray_struct_T **pEmxArray);
void emxFree_struct_T1(b_emxArray_struct_T **pEmxArray);
void emxFree_struct_T_400(emxArray_struct_T_400 *pEmxArray);
void emxFree_uint32_T(emxArray_uint32_T **pEmxArray);
void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
void emxInitMatrix_cell_wrap_1(cell_wrap_1 pMatrix[5], boolean_T doPush);
void emxInitMatrix_cell_wrap_2(cell_wrap_2 pMatrix[2], boolean_T doPush);
void emxInitMatrix_cell_wrap_3(cell_wrap_3 pMatrix[2], boolean_T doPush);
void emxInitMatrix_cell_wrap_32(cell_wrap_32 pMatrix[3], boolean_T doPush);
void emxInitStruct_cell_wrap_1(cell_wrap_1 *pStruct, boolean_T doPush);
void emxInitStruct_cell_wrap_2(cell_wrap_2 *pStruct, boolean_T doPush);
void emxInitStruct_cell_wrap_3(cell_wrap_3 *pStruct, boolean_T doPush);
void emxInitStruct_cell_wrap_32(cell_wrap_32 *pStruct, boolean_T doPush);
void emxInitStruct_struct5_T(struct5_T *pStruct, boolean_T doPush);
void emxInitStruct_struct8_T(struct8_T *pStruct, boolean_T doPush);
void emxInitStruct_struct_T(b_struct_T *pStruct, boolean_T doPush);
void emxInitStruct_struct_T1(d_struct_T *pStruct, boolean_T doPush);
void emxInitStruct_struct_T2(c_struct_T *pStruct, boolean_T doPush);
void emxInit_boolean_T(emlrtCTX aTLS, emxArray_boolean_T **pEmxArray, int32_T
  numDimensions, boolean_T doPush);
void emxInit_int16_T(emxArray_int16_T **pEmxArray, int32_T numDimensions,
                     boolean_T doPush);
void emxInit_int32_T(emxArray_int32_T **pEmxArray, int32_T numDimensions,
                     boolean_T doPush);
void emxInit_real32_T(emxArray_real32_T **pEmxArray, int32_T numDimensions,
                      boolean_T doPush);
void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions,
                    boolean_T doPush);
void emxInit_struct_T(emxArray_struct_T **pEmxArray, int32_T numDimensions,
                      boolean_T doPush);
void emxInit_struct_T1(b_emxArray_struct_T **pEmxArray, int32_T numDimensions,
  boolean_T doPush);
void emxInit_struct_T_400(emxArray_struct_T_400 *pEmxArray);
void emxInit_uint32_T(emxArray_uint32_T **pEmxArray, int32_T numDimensions,
                      boolean_T doPush);
void emxInit_uint8_T(emlrtCTX aTLS, emxArray_uint8_T **pEmxArray, int32_T
                     numDimensions, boolean_T doPush);
void emxTrim_struct_T(b_emxArray_struct_T *emxArray, int32_T fromIndex, int32_T
                      toIndex);
void emxTrim_struct_T_400(b_struct_T data[400], int32_T fromIndex, int32_T
  toIndex);

/* End of code generation (SkinDetect_emxutil.h) */
