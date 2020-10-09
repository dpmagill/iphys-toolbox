/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * repmat.c
 *
 * Code generation for function 'repmat'
 *
 */

/* Include files */
#include "repmat.h"
#include "ROIMSIR_emxutil.h"
#include "ROIMSIR_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void b_repmat(const int16_T a[4], int32_T varargin_1, int16_T b_data[], int32_T
              b_size[2])
{
  int32_T ibmat;
  int32_T itilerow;
  b_size[0] = (uint8_T)varargin_1;
  b_size[1] = 4;
  for (itilerow = 0; itilerow < varargin_1; itilerow++) {
    b_data[itilerow] = a[0];
    b_data[varargin_1 + itilerow] = a[1];
  }

  ibmat = varargin_1 << 1;
  for (itilerow = 0; itilerow < varargin_1; itilerow++) {
    b_data[ibmat + itilerow] = a[2];
  }

  ibmat = 3 * varargin_1;
  for (itilerow = 0; itilerow < varargin_1; itilerow++) {
    b_data[ibmat + itilerow] = a[3];
  }
}

void repmat(const int16_T a[4], real_T varargin_1, emxArray_int16_T *b)
{
  int32_T ibmat;
  int32_T itilerow;
  int32_T ntilerows;
  ntilerows = b->size[0] * b->size[1];
  b->size[0] = (int32_T)varargin_1;
  b->size[1] = 4;
  emxEnsureCapacity_int16_T(b, ntilerows);
  ntilerows = (int32_T)varargin_1;
  for (itilerow = 0; itilerow < ntilerows; itilerow++) {
    b->data[itilerow] = a[0];
  }

  for (itilerow = 0; itilerow < ntilerows; itilerow++) {
    b->data[(int32_T)varargin_1 + itilerow] = a[1];
  }

  ibmat = (int32_T)varargin_1 << 1;
  for (itilerow = 0; itilerow < ntilerows; itilerow++) {
    b->data[ibmat + itilerow] = a[2];
  }

  ibmat = 3 * (int32_T)varargin_1;
  for (itilerow = 0; itilerow < ntilerows; itilerow++) {
    b->data[ibmat + itilerow] = a[3];
  }
}

/* End of code generation (repmat.c) */
