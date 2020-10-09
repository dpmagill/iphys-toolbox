/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imdilate.c
 *
 * Code generation for function 'imdilate'
 *
 */

/* Include files */
#include "imdilate.h"
#include "SkinDetect_data.h"
#include "SkinDetect_emxutil.h"
#include "SkinDetect_types.h"
#include "rt_nonfinite.h"
#include "libmwmorphop_packed.h"

/* Function Definitions */
void b_imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B)
{
  emxArray_uint32_T *Apadpack;
  real_T asizeT[2];
  real_T nsizeT[2];
  int32_T b_i;
  int32_T i;
  uint32_T mask_value;
  uint32_T varargin_1;
  boolean_T nhood[22];
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint32_T(&Apadpack, 2, true);
  i = Apadpack->size[0] * Apadpack->size[1];
  Apadpack->size[0] = A->size[0];
  Apadpack->size[1] = A->size[1];
  emxEnsureCapacity_uint32_T(Apadpack, i);
  b_i = A->size[0] * A->size[1];
  for (i = 0; i < b_i; i++) {
    Apadpack->data[i] = A->data[i];
  }

  if ((A->size[0] != 0) && (A->size[1] != 0)) {
    mask_value = 0U;
    for (b_i = 0; b_i < 31; b_i++) {
      mask_value |= 1U << b_i;
    }

    b_i = A->size[1];
    for (i = 0; i < b_i; i++) {
      varargin_1 = A->data[(A->size[0] + A->size[0] * i) - 1];
      Apadpack->data[(A->size[0] + Apadpack->size[0] * i) - 1] = varargin_1 &
        mask_value;
    }
  }

  i = B->size[0] * B->size[1];
  B->size[0] = Apadpack->size[0];
  B->size[1] = Apadpack->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  for (b_i = 0; b_i < 22; b_i++) {
    nhood[b_i] = true;
  }

  asizeT[0] = Apadpack->size[0];
  nsizeT[0] = 22.0;
  asizeT[1] = Apadpack->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apadpack->data[0], &asizeT[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &B->data[0], true);
  i = Apadpack->size[0] * Apadpack->size[1];
  Apadpack->size[0] = B->size[0];
  Apadpack->size[1] = B->size[1];
  emxEnsureCapacity_uint32_T(Apadpack, i);
  b_i = B->size[0] * B->size[1];
  for (i = 0; i < b_i; i++) {
    Apadpack->data[i] = B->data[i];
  }

  i = B->size[0] * B->size[1];
  B->size[0] = Apadpack->size[0];
  B->size[1] = Apadpack->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  for (b_i = 0; b_i < 22; b_i++) {
    nhood[b_i] = true;
  }

  asizeT[0] = Apadpack->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = Apadpack->size[1];
  nsizeT[1] = 22.0;
  dilate_packed_uint32(&Apadpack->data[0], &asizeT[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &B->data[0], true);
  emxFree_uint32_T(&Apadpack);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

void c_imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B)
{
  emxArray_uint32_T *Apadpack;
  real_T asizeT[2];
  real_T nsizeT[2];
  int32_T b_i;
  int32_T i;
  uint32_T mask_value;
  uint32_T varargin_1;
  boolean_T nhood[32];
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint32_T(&Apadpack, 2, true);
  i = Apadpack->size[0] * Apadpack->size[1];
  Apadpack->size[0] = A->size[0];
  Apadpack->size[1] = A->size[1];
  emxEnsureCapacity_uint32_T(Apadpack, i);
  b_i = A->size[0] * A->size[1];
  for (i = 0; i < b_i; i++) {
    Apadpack->data[i] = A->data[i];
  }

  if ((A->size[0] != 0) && (A->size[1] != 0)) {
    mask_value = 0U;
    for (b_i = 0; b_i < 31; b_i++) {
      mask_value |= 1U << b_i;
    }

    b_i = A->size[1];
    for (i = 0; i < b_i; i++) {
      varargin_1 = A->data[(A->size[0] + A->size[0] * i) - 1];
      Apadpack->data[(A->size[0] + Apadpack->size[0] * i) - 1] = varargin_1 &
        mask_value;
    }
  }

  i = B->size[0] * B->size[1];
  B->size[0] = Apadpack->size[0];
  B->size[1] = Apadpack->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  for (b_i = 0; b_i < 32; b_i++) {
    nhood[b_i] = true;
  }

  asizeT[0] = Apadpack->size[0];
  nsizeT[0] = 32.0;
  asizeT[1] = Apadpack->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apadpack->data[0], &asizeT[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &B->data[0], true);
  i = Apadpack->size[0] * Apadpack->size[1];
  Apadpack->size[0] = B->size[0];
  Apadpack->size[1] = B->size[1];
  emxEnsureCapacity_uint32_T(Apadpack, i);
  b_i = B->size[0] * B->size[1];
  for (i = 0; i < b_i; i++) {
    Apadpack->data[i] = B->data[i];
  }

  i = B->size[0] * B->size[1];
  B->size[0] = Apadpack->size[0];
  B->size[1] = Apadpack->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  for (b_i = 0; b_i < 32; b_i++) {
    nhood[b_i] = true;
  }

  asizeT[0] = Apadpack->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = Apadpack->size[1];
  nsizeT[1] = 32.0;
  dilate_packed_uint32(&Apadpack->data[0], &asizeT[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &B->data[0], true);
  emxFree_uint32_T(&Apadpack);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

void d_imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B)
{
  emxArray_uint32_T *Apadpack;
  real_T asizeT[2];
  real_T nsizeT[2];
  int32_T b_i;
  int32_T i;
  uint32_T mask_value;
  uint32_T varargin_1;
  boolean_T nhood[50];
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint32_T(&Apadpack, 2, true);
  i = Apadpack->size[0] * Apadpack->size[1];
  Apadpack->size[0] = A->size[0];
  Apadpack->size[1] = A->size[1];
  emxEnsureCapacity_uint32_T(Apadpack, i);
  b_i = A->size[0] * A->size[1];
  for (i = 0; i < b_i; i++) {
    Apadpack->data[i] = A->data[i];
  }

  if ((A->size[0] != 0) && (A->size[1] != 0)) {
    mask_value = 0U;
    for (b_i = 0; b_i < 31; b_i++) {
      mask_value |= 1U << b_i;
    }

    b_i = A->size[1];
    for (i = 0; i < b_i; i++) {
      varargin_1 = A->data[(A->size[0] + A->size[0] * i) - 1];
      Apadpack->data[(A->size[0] + Apadpack->size[0] * i) - 1] = varargin_1 &
        mask_value;
    }
  }

  i = B->size[0] * B->size[1];
  B->size[0] = Apadpack->size[0];
  B->size[1] = Apadpack->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  for (b_i = 0; b_i < 50; b_i++) {
    nhood[b_i] = true;
  }

  asizeT[0] = Apadpack->size[0];
  nsizeT[0] = 50.0;
  asizeT[1] = Apadpack->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apadpack->data[0], &asizeT[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &B->data[0], true);
  i = Apadpack->size[0] * Apadpack->size[1];
  Apadpack->size[0] = B->size[0];
  Apadpack->size[1] = B->size[1];
  emxEnsureCapacity_uint32_T(Apadpack, i);
  b_i = B->size[0] * B->size[1];
  for (i = 0; i < b_i; i++) {
    Apadpack->data[i] = B->data[i];
  }

  i = B->size[0] * B->size[1];
  B->size[0] = Apadpack->size[0];
  B->size[1] = Apadpack->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  for (b_i = 0; b_i < 50; b_i++) {
    nhood[b_i] = true;
  }

  asizeT[0] = Apadpack->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = Apadpack->size[1];
  nsizeT[1] = 50.0;
  dilate_packed_uint32(&Apadpack->data[0], &asizeT[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &B->data[0], true);
  emxFree_uint32_T(&Apadpack);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

void imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B)
{
  emxArray_uint32_T *Apadpack;
  real_T asizeT[2];
  real_T nsizeT[2];
  int32_T b_i;
  int32_T i;
  uint32_T mask_value;
  uint32_T varargin_1;
  boolean_T nhood[12];
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint32_T(&Apadpack, 2, true);
  i = Apadpack->size[0] * Apadpack->size[1];
  Apadpack->size[0] = A->size[0];
  Apadpack->size[1] = A->size[1];
  emxEnsureCapacity_uint32_T(Apadpack, i);
  b_i = A->size[0] * A->size[1];
  for (i = 0; i < b_i; i++) {
    Apadpack->data[i] = A->data[i];
  }

  if ((A->size[0] != 0) && (A->size[1] != 0)) {
    mask_value = 0U;
    for (b_i = 0; b_i < 31; b_i++) {
      mask_value |= 1U << b_i;
    }

    b_i = A->size[1];
    for (i = 0; i < b_i; i++) {
      varargin_1 = A->data[(A->size[0] + A->size[0] * i) - 1];
      Apadpack->data[(A->size[0] + Apadpack->size[0] * i) - 1] = varargin_1 &
        mask_value;
    }
  }

  i = B->size[0] * B->size[1];
  B->size[0] = Apadpack->size[0];
  B->size[1] = Apadpack->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  for (b_i = 0; b_i < 12; b_i++) {
    nhood[b_i] = true;
  }

  asizeT[0] = Apadpack->size[0];
  nsizeT[0] = 12.0;
  asizeT[1] = Apadpack->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apadpack->data[0], &asizeT[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &B->data[0], true);
  i = Apadpack->size[0] * Apadpack->size[1];
  Apadpack->size[0] = B->size[0];
  Apadpack->size[1] = B->size[1];
  emxEnsureCapacity_uint32_T(Apadpack, i);
  b_i = B->size[0] * B->size[1];
  for (i = 0; i < b_i; i++) {
    Apadpack->data[i] = B->data[i];
  }

  i = B->size[0] * B->size[1];
  B->size[0] = Apadpack->size[0];
  B->size[1] = Apadpack->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  for (b_i = 0; b_i < 12; b_i++) {
    nhood[b_i] = true;
  }

  asizeT[0] = Apadpack->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = Apadpack->size[1];
  nsizeT[1] = 12.0;
  dilate_packed_uint32(&Apadpack->data[0], &asizeT[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &B->data[0], true);
  emxFree_uint32_T(&Apadpack);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (imdilate.c) */
