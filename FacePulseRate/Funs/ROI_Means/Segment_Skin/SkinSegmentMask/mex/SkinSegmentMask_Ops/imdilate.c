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
#include "SkinSegmentMask_Ops_data.h"
#include "SkinSegmentMask_Ops_emxutil.h"
#include "SkinSegmentMask_Ops_types.h"
#include "rt_nonfinite.h"
#include "libmwmorphop_packed.h"

/* Function Definitions */
void b_imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B)
{
  emxArray_uint32_T *Apad;
  emxArray_uint32_T *Apadpre;
  emxArray_uint32_T *b_A;
  emxArray_uint32_T *b_B;
  real_T nsizeT[2];
  real_T sizeB[2];
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T loop_ub;
  int32_T pad_ul_idx_0;
  int32_T pad_ul_idx_1;
  uint32_T mask_value;
  uint32_T varargin_1;
  boolean_T c_nhood[9];
  boolean_T nhood[3];
  boolean_T b_nhood;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint32_T(&b_A, 2, true);
  i = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = A->size[1];
  emxEnsureCapacity_uint32_T(b_A, i);
  loop_ub = A->size[0] * A->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_A->data[i] = A->data[i];
  }

  if ((A->size[0] != 0) && (A->size[1] != 0)) {
    mask_value = 0U;
    for (pad_ul_idx_0 = 0; pad_ul_idx_0 < 31; pad_ul_idx_0++) {
      mask_value |= 1U << pad_ul_idx_0;
    }

    loop_ub = A->size[1];
    for (i = 0; i < loop_ub; i++) {
      varargin_1 = A->data[(A->size[0] + A->size[0] * i) - 1];
      b_A->data[(A->size[0] + b_A->size[0] * i) - 1] = varargin_1 & mask_value;
    }
  }

  emxInit_uint32_T(&Apadpre, 2, true);
  if ((b_A->size[0] == 0) || (b_A->size[1] == 0)) {
    i = Apadpre->size[0] * Apadpre->size[1];
    Apadpre->size[0] = (int32_T)(uint32_T)((real_T)b_A->size[0] + 1.0);
    Apadpre->size[1] = (int32_T)(uint32_T)((real_T)b_A->size[1] + 5.0);
    emxEnsureCapacity_uint32_T(Apadpre, i);
    loop_ub = (int32_T)(uint32_T)((real_T)b_A->size[0] + 1.0) * (int32_T)
      (uint32_T)((real_T)b_A->size[1] + 5.0);
    for (i = 0; i < loop_ub; i++) {
      Apadpre->data[i] = 0U;
    }
  } else {
    i = Apadpre->size[0] * Apadpre->size[1];
    Apadpre->size[0] = b_A->size[0] + 1;
    Apadpre->size[1] = b_A->size[1] + 5;
    emxEnsureCapacity_uint32_T(Apadpre, i);
    for (pad_ul_idx_0 = 0; pad_ul_idx_0 < 5; pad_ul_idx_0++) {
      i = Apadpre->size[0];
      for (pad_ul_idx_1 = 0; pad_ul_idx_1 < i; pad_ul_idx_1++) {
        Apadpre->data[pad_ul_idx_1 + Apadpre->size[0] * pad_ul_idx_0] = 0U;
      }
    }

    i = Apadpre->size[1];
    for (pad_ul_idx_0 = 6; pad_ul_idx_0 <= i; pad_ul_idx_0++) {
      Apadpre->data[Apadpre->size[0] * (pad_ul_idx_0 - 1)] = 0U;
    }

    i = b_A->size[1];
    for (pad_ul_idx_0 = 0; pad_ul_idx_0 < i; pad_ul_idx_0++) {
      i1 = b_A->size[0];
      for (pad_ul_idx_1 = 0; pad_ul_idx_1 < i1; pad_ul_idx_1++) {
        Apadpre->data[(pad_ul_idx_1 + Apadpre->size[0] * (pad_ul_idx_0 + 5)) + 1]
          = b_A->data[pad_ul_idx_1 + b_A->size[0] * pad_ul_idx_0];
      }
    }
  }

  emxFree_uint32_T(&b_A);
  emxInit_uint32_T(&Apad, 2, true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = Apadpre->size[0] + 1;
  Apad->size[1] = Apadpre->size[1] + 5;
  emxEnsureCapacity_uint32_T(Apad, i);
  i = Apadpre->size[1] + 1;
  i1 = Apadpre->size[1] + 5;
  for (pad_ul_idx_0 = i; pad_ul_idx_0 <= i1; pad_ul_idx_0++) {
    i2 = Apad->size[0];
    for (pad_ul_idx_1 = 0; pad_ul_idx_1 < i2; pad_ul_idx_1++) {
      Apad->data[pad_ul_idx_1 + Apad->size[0] * (pad_ul_idx_0 - 1)] = 0U;
    }
  }

  i = Apadpre->size[1];
  for (pad_ul_idx_0 = 0; pad_ul_idx_0 < i; pad_ul_idx_0++) {
    i1 = Apadpre->size[0] + 1;
    i2 = Apad->size[0];
    for (pad_ul_idx_1 = i1; pad_ul_idx_1 <= i2; pad_ul_idx_1++) {
      Apad->data[(pad_ul_idx_1 + Apad->size[0] * pad_ul_idx_0) - 1] = 0U;
    }
  }

  i = Apadpre->size[1];
  for (pad_ul_idx_0 = 0; pad_ul_idx_0 < i; pad_ul_idx_0++) {
    i1 = Apadpre->size[0];
    for (pad_ul_idx_1 = 0; pad_ul_idx_1 < i1; pad_ul_idx_1++) {
      Apad->data[pad_ul_idx_1 + Apad->size[0] * pad_ul_idx_0] = Apadpre->
        data[pad_ul_idx_1 + Apadpre->size[0] * pad_ul_idx_0];
    }
  }

  emxFree_uint32_T(&Apadpre);
  emxInit_uint32_T(&b_B, 2, true);
  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  nhood[0] = true;
  nhood[1] = true;
  nhood[2] = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 3.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  b_nhood = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &b_nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  b_nhood = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &b_nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  b_nhood = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &b_nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  nhood[0] = true;
  nhood[1] = true;
  nhood[2] = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 3.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  b_nhood = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &b_nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  b_nhood = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &b_nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  b_nhood = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &b_nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  for (i = 0; i < 9; i++) {
    c_nhood[i] = true;
  }

  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 9.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &c_nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  for (i = 0; i < 9; i++) {
    c_nhood[i] = true;
  }

  sizeB[0] = Apad->size[0];
  nsizeT[0] = 9.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &c_nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  pad_ul_idx_0 = (int32_T)((((real_T)b_B->size[0] + 2.0) - 1.0) - 1.0) - 1;
  pad_ul_idx_1 = (int32_T)((((real_T)b_B->size[1] + 6.0) - 5.0) - 5.0) - 1;
  emxFree_uint32_T(&Apad);
  if (2 > pad_ul_idx_0) {
    i = 0;
    pad_ul_idx_0 = 0;
  } else {
    i = 1;
  }

  if (6 > pad_ul_idx_1) {
    i1 = 0;
    pad_ul_idx_1 = 0;
  } else {
    i1 = 5;
  }

  loop_ub = pad_ul_idx_0 - i;
  i2 = B->size[0] * B->size[1];
  B->size[0] = loop_ub;
  pad_ul_idx_0 = pad_ul_idx_1 - i1;
  B->size[1] = pad_ul_idx_0;
  emxEnsureCapacity_uint32_T(B, i2);
  for (i2 = 0; i2 < pad_ul_idx_0; i2++) {
    for (pad_ul_idx_1 = 0; pad_ul_idx_1 < loop_ub; pad_ul_idx_1++) {
      B->data[pad_ul_idx_1 + B->size[0] * i2] = b_B->data[(i + pad_ul_idx_1) +
        b_B->size[0] * (i1 + i2)];
    }
  }

  emxFree_uint32_T(&b_B);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

void c_imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B)
{
  emxArray_uint32_T *Apad;
  emxArray_uint32_T *Apadpre;
  emxArray_uint32_T *b_A;
  emxArray_uint32_T *b_B;
  real_T nsizeT[2];
  real_T sizeB[2];
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T loop_ub;
  int32_T pad_ul_idx_0;
  int32_T pad_ul_idx_1;
  uint32_T mask_value;
  uint32_T varargin_1;
  boolean_T c_nhood[13];
  boolean_T nhood[3];
  boolean_T b_nhood;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint32_T(&b_A, 2, true);
  i = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = A->size[1];
  emxEnsureCapacity_uint32_T(b_A, i);
  loop_ub = A->size[0] * A->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_A->data[i] = A->data[i];
  }

  if ((A->size[0] != 0) && (A->size[1] != 0)) {
    mask_value = 0U;
    for (pad_ul_idx_0 = 0; pad_ul_idx_0 < 31; pad_ul_idx_0++) {
      mask_value |= 1U << pad_ul_idx_0;
    }

    loop_ub = A->size[1];
    for (i = 0; i < loop_ub; i++) {
      varargin_1 = A->data[(A->size[0] + A->size[0] * i) - 1];
      b_A->data[(A->size[0] + b_A->size[0] * i) - 1] = varargin_1 & mask_value;
    }
  }

  emxInit_uint32_T(&Apadpre, 2, true);
  if ((b_A->size[0] == 0) || (b_A->size[1] == 0)) {
    i = Apadpre->size[0] * Apadpre->size[1];
    Apadpre->size[0] = (int32_T)(uint32_T)((real_T)b_A->size[0] + 1.0);
    Apadpre->size[1] = (int32_T)(uint32_T)((real_T)b_A->size[1] + 9.0);
    emxEnsureCapacity_uint32_T(Apadpre, i);
    loop_ub = (int32_T)(uint32_T)((real_T)b_A->size[0] + 1.0) * (int32_T)
      (uint32_T)((real_T)b_A->size[1] + 9.0);
    for (i = 0; i < loop_ub; i++) {
      Apadpre->data[i] = 0U;
    }
  } else {
    i = Apadpre->size[0] * Apadpre->size[1];
    Apadpre->size[0] = b_A->size[0] + 1;
    Apadpre->size[1] = b_A->size[1] + 9;
    emxEnsureCapacity_uint32_T(Apadpre, i);
    for (pad_ul_idx_0 = 0; pad_ul_idx_0 < 9; pad_ul_idx_0++) {
      i = Apadpre->size[0];
      for (pad_ul_idx_1 = 0; pad_ul_idx_1 < i; pad_ul_idx_1++) {
        Apadpre->data[pad_ul_idx_1 + Apadpre->size[0] * pad_ul_idx_0] = 0U;
      }
    }

    i = Apadpre->size[1];
    for (pad_ul_idx_0 = 10; pad_ul_idx_0 <= i; pad_ul_idx_0++) {
      Apadpre->data[Apadpre->size[0] * (pad_ul_idx_0 - 1)] = 0U;
    }

    i = b_A->size[1];
    for (pad_ul_idx_0 = 0; pad_ul_idx_0 < i; pad_ul_idx_0++) {
      i1 = b_A->size[0];
      for (pad_ul_idx_1 = 0; pad_ul_idx_1 < i1; pad_ul_idx_1++) {
        Apadpre->data[(pad_ul_idx_1 + Apadpre->size[0] * (pad_ul_idx_0 + 9)) + 1]
          = b_A->data[pad_ul_idx_1 + b_A->size[0] * pad_ul_idx_0];
      }
    }
  }

  emxFree_uint32_T(&b_A);
  emxInit_uint32_T(&Apad, 2, true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = Apadpre->size[0] + 1;
  Apad->size[1] = Apadpre->size[1] + 9;
  emxEnsureCapacity_uint32_T(Apad, i);
  i = Apadpre->size[1] + 1;
  i1 = Apadpre->size[1] + 9;
  for (pad_ul_idx_0 = i; pad_ul_idx_0 <= i1; pad_ul_idx_0++) {
    i2 = Apad->size[0];
    for (pad_ul_idx_1 = 0; pad_ul_idx_1 < i2; pad_ul_idx_1++) {
      Apad->data[pad_ul_idx_1 + Apad->size[0] * (pad_ul_idx_0 - 1)] = 0U;
    }
  }

  i = Apadpre->size[1];
  for (pad_ul_idx_0 = 0; pad_ul_idx_0 < i; pad_ul_idx_0++) {
    i1 = Apadpre->size[0] + 1;
    i2 = Apad->size[0];
    for (pad_ul_idx_1 = i1; pad_ul_idx_1 <= i2; pad_ul_idx_1++) {
      Apad->data[(pad_ul_idx_1 + Apad->size[0] * pad_ul_idx_0) - 1] = 0U;
    }
  }

  i = Apadpre->size[1];
  for (pad_ul_idx_0 = 0; pad_ul_idx_0 < i; pad_ul_idx_0++) {
    i1 = Apadpre->size[0];
    for (pad_ul_idx_1 = 0; pad_ul_idx_1 < i1; pad_ul_idx_1++) {
      Apad->data[pad_ul_idx_1 + Apad->size[0] * pad_ul_idx_0] = Apadpre->
        data[pad_ul_idx_1 + Apadpre->size[0] * pad_ul_idx_0];
    }
  }

  emxFree_uint32_T(&Apadpre);
  emxInit_uint32_T(&b_B, 2, true);
  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  nhood[0] = true;
  nhood[1] = true;
  nhood[2] = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 3.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  b_nhood = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &b_nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 3.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 3.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &bv[0], &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  b_nhood = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &b_nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  nhood[0] = true;
  nhood[1] = true;
  nhood[2] = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 3.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  b_nhood = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &b_nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 3.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 3.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &bv1[0], &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  b_nhood = true;
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &b_nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  for (i = 0; i < 13; i++) {
    c_nhood[i] = true;
  }

  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 13.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &c_nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  for (i = 0; i < 13; i++) {
    c_nhood[i] = true;
  }

  sizeB[0] = Apad->size[0];
  nsizeT[0] = 13.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &c_nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  pad_ul_idx_0 = (int32_T)((((real_T)b_B->size[0] + 2.0) - 1.0) - 1.0) - 1;
  pad_ul_idx_1 = (int32_T)((((real_T)b_B->size[1] + 10.0) - 9.0) - 9.0) - 1;
  emxFree_uint32_T(&Apad);
  if (2 > pad_ul_idx_0) {
    i = 0;
    pad_ul_idx_0 = 0;
  } else {
    i = 1;
  }

  if (10 > pad_ul_idx_1) {
    i1 = 0;
    pad_ul_idx_1 = 0;
  } else {
    i1 = 9;
  }

  loop_ub = pad_ul_idx_0 - i;
  i2 = B->size[0] * B->size[1];
  B->size[0] = loop_ub;
  pad_ul_idx_0 = pad_ul_idx_1 - i1;
  B->size[1] = pad_ul_idx_0;
  emxEnsureCapacity_uint32_T(B, i2);
  for (i2 = 0; i2 < pad_ul_idx_0; i2++) {
    for (pad_ul_idx_1 = 0; pad_ul_idx_1 < loop_ub; pad_ul_idx_1++) {
      B->data[pad_ul_idx_1 + B->size[0] * i2] = b_B->data[(i + pad_ul_idx_1) +
        b_B->size[0] * (i1 + i2)];
    }
  }

  emxFree_uint32_T(&b_B);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

void d_imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B)
{
  emxArray_uint32_T *Apad;
  emxArray_uint32_T *Apadpre;
  emxArray_uint32_T *b_A;
  emxArray_uint32_T *b_B;
  real_T nsizeT[2];
  real_T sizeB[2];
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T loop_ub;
  int32_T pad_ul_idx_0;
  int32_T pad_ul_idx_1;
  uint32_T mask_value;
  uint32_T varargin_1;
  boolean_T b_nhood[7];
  boolean_T nhood[5];
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint32_T(&b_A, 2, true);
  i = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = A->size[1];
  emxEnsureCapacity_uint32_T(b_A, i);
  loop_ub = A->size[0] * A->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_A->data[i] = A->data[i];
  }

  if ((A->size[0] != 0) && (A->size[1] != 0)) {
    mask_value = 0U;
    for (pad_ul_idx_0 = 0; pad_ul_idx_0 < 31; pad_ul_idx_0++) {
      mask_value |= 1U << pad_ul_idx_0;
    }

    loop_ub = A->size[1];
    for (i = 0; i < loop_ub; i++) {
      varargin_1 = A->data[(A->size[0] + A->size[0] * i) - 1];
      b_A->data[(A->size[0] + b_A->size[0] * i) - 1] = varargin_1 & mask_value;
    }
  }

  emxInit_uint32_T(&Apadpre, 2, true);
  if ((b_A->size[0] == 0) || (b_A->size[1] == 0)) {
    i = Apadpre->size[0] * Apadpre->size[1];
    Apadpre->size[0] = (int32_T)(uint32_T)((real_T)b_A->size[0] + 1.0);
    Apadpre->size[1] = (int32_T)(uint32_T)((real_T)b_A->size[1] + 13.0);
    emxEnsureCapacity_uint32_T(Apadpre, i);
    loop_ub = (int32_T)(uint32_T)((real_T)b_A->size[0] + 1.0) * (int32_T)
      (uint32_T)((real_T)b_A->size[1] + 13.0);
    for (i = 0; i < loop_ub; i++) {
      Apadpre->data[i] = 0U;
    }
  } else {
    i = Apadpre->size[0] * Apadpre->size[1];
    Apadpre->size[0] = b_A->size[0] + 1;
    Apadpre->size[1] = b_A->size[1] + 13;
    emxEnsureCapacity_uint32_T(Apadpre, i);
    for (pad_ul_idx_0 = 0; pad_ul_idx_0 < 13; pad_ul_idx_0++) {
      i = Apadpre->size[0];
      for (pad_ul_idx_1 = 0; pad_ul_idx_1 < i; pad_ul_idx_1++) {
        Apadpre->data[pad_ul_idx_1 + Apadpre->size[0] * pad_ul_idx_0] = 0U;
      }
    }

    i = Apadpre->size[1];
    for (pad_ul_idx_0 = 14; pad_ul_idx_0 <= i; pad_ul_idx_0++) {
      Apadpre->data[Apadpre->size[0] * (pad_ul_idx_0 - 1)] = 0U;
    }

    i = b_A->size[1];
    for (pad_ul_idx_0 = 0; pad_ul_idx_0 < i; pad_ul_idx_0++) {
      i1 = b_A->size[0];
      for (pad_ul_idx_1 = 0; pad_ul_idx_1 < i1; pad_ul_idx_1++) {
        Apadpre->data[(pad_ul_idx_1 + Apadpre->size[0] * (pad_ul_idx_0 + 13)) +
          1] = b_A->data[pad_ul_idx_1 + b_A->size[0] * pad_ul_idx_0];
      }
    }
  }

  emxFree_uint32_T(&b_A);
  emxInit_uint32_T(&Apad, 2, true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = Apadpre->size[0] + 1;
  Apad->size[1] = Apadpre->size[1] + 13;
  emxEnsureCapacity_uint32_T(Apad, i);
  i = Apadpre->size[1] + 1;
  i1 = Apadpre->size[1] + 13;
  for (pad_ul_idx_0 = i; pad_ul_idx_0 <= i1; pad_ul_idx_0++) {
    i2 = Apad->size[0];
    for (pad_ul_idx_1 = 0; pad_ul_idx_1 < i2; pad_ul_idx_1++) {
      Apad->data[pad_ul_idx_1 + Apad->size[0] * (pad_ul_idx_0 - 1)] = 0U;
    }
  }

  i = Apadpre->size[1];
  for (pad_ul_idx_0 = 0; pad_ul_idx_0 < i; pad_ul_idx_0++) {
    i1 = Apadpre->size[0] + 1;
    i2 = Apad->size[0];
    for (pad_ul_idx_1 = i1; pad_ul_idx_1 <= i2; pad_ul_idx_1++) {
      Apad->data[(pad_ul_idx_1 + Apad->size[0] * pad_ul_idx_0) - 1] = 0U;
    }
  }

  i = Apadpre->size[1];
  for (pad_ul_idx_0 = 0; pad_ul_idx_0 < i; pad_ul_idx_0++) {
    i1 = Apadpre->size[0];
    for (pad_ul_idx_1 = 0; pad_ul_idx_1 < i1; pad_ul_idx_1++) {
      Apad->data[pad_ul_idx_1 + Apad->size[0] * pad_ul_idx_0] = Apadpre->
        data[pad_ul_idx_1 + Apadpre->size[0] * pad_ul_idx_0];
    }
  }

  emxFree_uint32_T(&Apadpre);
  emxInit_uint32_T(&b_B, 2, true);
  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  for (pad_ul_idx_1 = 0; pad_ul_idx_1 < 5; pad_ul_idx_1++) {
    nhood[pad_ul_idx_1] = true;
  }

  sizeB[0] = Apad->size[0];
  nsizeT[0] = 5.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 5.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 3.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &bv2[0], &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 3.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 3.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &bv[0], &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 3.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 5.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &bv2[0], &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  for (pad_ul_idx_1 = 0; pad_ul_idx_1 < 5; pad_ul_idx_1++) {
    nhood[pad_ul_idx_1] = true;
  }

  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 5.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 3.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 5.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &bv3[0], &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 3.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 3.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &bv1[0], &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  sizeB[0] = Apad->size[0];
  nsizeT[0] = 5.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 3.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &bv4[0], &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  for (i = 0; i < 7; i++) {
    b_nhood[i] = true;
  }

  sizeB[0] = Apad->size[0];
  nsizeT[0] = 1.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 7.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &b_nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  i = Apad->size[0] * Apad->size[1];
  Apad->size[0] = b_B->size[0];
  Apad->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(Apad, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    Apad->data[i] = b_B->data[i];
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = Apad->size[0];
  b_B->size[1] = Apad->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  for (i = 0; i < 7; i++) {
    b_nhood[i] = true;
  }

  sizeB[0] = Apad->size[0];
  nsizeT[0] = 7.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], &sizeB[0], 2.0, &b_nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  pad_ul_idx_0 = (int32_T)((((real_T)b_B->size[0] + 2.0) - 1.0) - 1.0) - 1;
  pad_ul_idx_1 = (int32_T)((((real_T)b_B->size[1] + 14.0) - 13.0) - 13.0) - 1;
  emxFree_uint32_T(&Apad);
  if (2 > pad_ul_idx_0) {
    i = 0;
    pad_ul_idx_0 = 0;
  } else {
    i = 1;
  }

  if (14 > pad_ul_idx_1) {
    i1 = 0;
    pad_ul_idx_1 = 0;
  } else {
    i1 = 13;
  }

  loop_ub = pad_ul_idx_0 - i;
  i2 = B->size[0] * B->size[1];
  B->size[0] = loop_ub;
  pad_ul_idx_0 = pad_ul_idx_1 - i1;
  B->size[1] = pad_ul_idx_0;
  emxEnsureCapacity_uint32_T(B, i2);
  for (i2 = 0; i2 < pad_ul_idx_0; i2++) {
    for (pad_ul_idx_1 = 0; pad_ul_idx_1 < loop_ub; pad_ul_idx_1++) {
      B->data[pad_ul_idx_1 + B->size[0] * i2] = b_B->data[(i + pad_ul_idx_1) +
        b_B->size[0] * (i1 + i2)];
    }
  }

  emxFree_uint32_T(&b_B);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

void imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B)
{
  emxArray_uint32_T *b_A;
  emxArray_uint32_T *b_B;
  emxArray_uint32_T *c_B;
  real_T asizeT[2];
  real_T nsizeT[2];
  int32_T i;
  int32_T loop_ub;
  uint32_T mask_value;
  uint32_T varargin_1;
  boolean_T b_nhood[7];
  boolean_T nhood;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_uint32_T(&b_A, 2, true);
  i = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = A->size[1];
  emxEnsureCapacity_uint32_T(b_A, i);
  loop_ub = A->size[0] * A->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_A->data[i] = A->data[i];
  }

  if ((A->size[0] != 0) && (A->size[1] != 0)) {
    mask_value = 0U;
    for (loop_ub = 0; loop_ub < 31; loop_ub++) {
      mask_value |= 1U << loop_ub;
    }

    loop_ub = A->size[1];
    for (i = 0; i < loop_ub; i++) {
      varargin_1 = A->data[(A->size[0] + A->size[0] * i) - 1];
      b_A->data[(A->size[0] + b_A->size[0] * i) - 1] = varargin_1 & mask_value;
    }
  }

  emxInit_uint32_T(&b_B, 2, true);
  i = B->size[0] * B->size[1];
  B->size[0] = b_A->size[0];
  B->size[1] = b_A->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = b_A->size[0];
  b_B->size[1] = b_A->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  loop_ub = b_A->size[0] * b_A->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_B->data[i] = B->data[i];
  }

  emxInit_uint32_T(&c_B, 2, true);
  nhood = true;
  asizeT[0] = b_A->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = b_A->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&b_A->data[0], &asizeT[0], 2.0, &nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = B->size[0] * B->size[1];
  B->size[0] = b_B->size[0];
  B->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  i = c_B->size[0] * c_B->size[1];
  c_B->size[0] = b_B->size[0];
  c_B->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(c_B, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  emxFree_uint32_T(&b_A);
  for (i = 0; i < loop_ub; i++) {
    c_B->data[i] = B->data[i];
  }

  nhood = true;
  asizeT[0] = b_B->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = b_B->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&b_B->data[0], &asizeT[0], 2.0, &nhood, &nsizeT[0], 2.0,
                       &c_B->data[0], true);
  i = B->size[0] * B->size[1];
  B->size[0] = c_B->size[0];
  B->size[1] = c_B->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = c_B->size[0];
  b_B->size[1] = c_B->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  loop_ub = c_B->size[0] * c_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_B->data[i] = B->data[i];
  }

  nhood = true;
  asizeT[0] = c_B->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = c_B->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&c_B->data[0], &asizeT[0], 2.0, &nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = B->size[0] * B->size[1];
  B->size[0] = b_B->size[0];
  B->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  i = c_B->size[0] * c_B->size[1];
  c_B->size[0] = b_B->size[0];
  c_B->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(c_B, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    c_B->data[i] = B->data[i];
  }

  nhood = true;
  asizeT[0] = b_B->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = b_B->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&b_B->data[0], &asizeT[0], 2.0, &nhood, &nsizeT[0], 2.0,
                       &c_B->data[0], true);
  i = B->size[0] * B->size[1];
  B->size[0] = c_B->size[0];
  B->size[1] = c_B->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = c_B->size[0];
  b_B->size[1] = c_B->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  loop_ub = c_B->size[0] * c_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_B->data[i] = B->data[i];
  }

  nhood = true;
  asizeT[0] = c_B->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = c_B->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&c_B->data[0], &asizeT[0], 2.0, &nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = B->size[0] * B->size[1];
  B->size[0] = b_B->size[0];
  B->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  i = c_B->size[0] * c_B->size[1];
  c_B->size[0] = b_B->size[0];
  c_B->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(c_B, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    c_B->data[i] = B->data[i];
  }

  nhood = true;
  asizeT[0] = b_B->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = b_B->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&b_B->data[0], &asizeT[0], 2.0, &nhood, &nsizeT[0], 2.0,
                       &c_B->data[0], true);
  i = B->size[0] * B->size[1];
  B->size[0] = c_B->size[0];
  B->size[1] = c_B->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = c_B->size[0];
  b_B->size[1] = c_B->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  loop_ub = c_B->size[0] * c_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_B->data[i] = B->data[i];
  }

  nhood = true;
  asizeT[0] = c_B->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = c_B->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&c_B->data[0], &asizeT[0], 2.0, &nhood, &nsizeT[0], 2.0,
                       &b_B->data[0], true);
  i = B->size[0] * B->size[1];
  B->size[0] = b_B->size[0];
  B->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  i = c_B->size[0] * c_B->size[1];
  c_B->size[0] = b_B->size[0];
  c_B->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(c_B, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    c_B->data[i] = B->data[i];
  }

  nhood = true;
  asizeT[0] = b_B->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = b_B->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&b_B->data[0], &asizeT[0], 2.0, &nhood, &nsizeT[0], 2.0,
                       &c_B->data[0], true);
  i = B->size[0] * B->size[1];
  B->size[0] = c_B->size[0];
  B->size[1] = c_B->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  for (i = 0; i < 7; i++) {
    b_nhood[i] = true;
  }

  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = c_B->size[0];
  b_B->size[1] = c_B->size[1];
  emxEnsureCapacity_uint32_T(b_B, i);
  loop_ub = c_B->size[0] * c_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_B->data[i] = B->data[i];
  }

  asizeT[0] = c_B->size[0];
  nsizeT[0] = 1.0;
  asizeT[1] = c_B->size[1];
  nsizeT[1] = 7.0;
  dilate_packed_uint32(&c_B->data[0], &asizeT[0], 2.0, &b_nhood[0], &nsizeT[0],
                       2.0, &b_B->data[0], true);
  i = B->size[0] * B->size[1];
  B->size[0] = b_B->size[0];
  B->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  for (i = 0; i < 7; i++) {
    b_nhood[i] = true;
  }

  i = c_B->size[0] * c_B->size[1];
  c_B->size[0] = b_B->size[0];
  c_B->size[1] = b_B->size[1];
  emxEnsureCapacity_uint32_T(c_B, i);
  loop_ub = b_B->size[0] * b_B->size[1];
  for (i = 0; i < loop_ub; i++) {
    c_B->data[i] = B->data[i];
  }

  asizeT[0] = b_B->size[0];
  nsizeT[0] = 7.0;
  asizeT[1] = b_B->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&b_B->data[0], &asizeT[0], 2.0, &b_nhood[0], &nsizeT[0],
                       2.0, &c_B->data[0], true);
  i = B->size[0] * B->size[1];
  B->size[0] = c_B->size[0];
  B->size[1] = c_B->size[1];
  emxEnsureCapacity_uint32_T(B, i);
  loop_ub = c_B->size[0] * c_B->size[1];
  emxFree_uint32_T(&b_B);
  for (i = 0; i < loop_ub; i++) {
    B->data[i] = c_B->data[i];
  }

  emxFree_uint32_T(&c_B);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (imdilate.c) */
