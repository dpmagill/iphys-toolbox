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
#include "SkinSegmentMask_Ops.h"
#include "SkinSegmentMask_Ops_data.h"
#include "SkinSegmentMask_Ops_emxutil.h"
#include "libmwmorphop_packed.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void b_imdilate(const emxArray_uint32_T *A, emxArray_uint32_T *B)
{
  emxArray_uint32_T *b_A;
  int32_T i;
  int32_T loop_ub;
  uint32_T mask_value;
  emxArray_uint32_T *Apadpre;
  int32_T pad_ul_idx_0;
  int32_T i1;
  int32_T i2;
  int32_T pad_ul_idx_1;
  emxArray_uint32_T *Apad;
  emxArray_uint32_T *b_B;
  real_T sizeB[2];
  boolean_T nhood[5];
  real_T nsizeT[2];
  boolean_T b_nhood[7];
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
      b_A->data[(A->size[0] + b_A->size[0] * i) - 1] = A->data[(A->size[0] +
        A->size[0] * i) - 1] & mask_value;
    }
  }

  emxInit_uint32_T(&Apadpre, 2, true);
  if ((b_A->size[0] == 0) || (b_A->size[1] == 0)) {
    i = (int32_T)(uint32_T)((real_T)b_A->size[0] + 1.0);
    i1 = Apadpre->size[0] * Apadpre->size[1];
    Apadpre->size[0] = i;
    i2 = (int32_T)(uint32_T)((real_T)b_A->size[1] + 13.0);
    Apadpre->size[1] = i2;
    emxEnsureCapacity_uint32_T(Apadpre, i1);
    loop_ub = i * i2;
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
  i1 = Apadpre->size[1] + 13;
  Apad->size[1] = i1;
  emxEnsureCapacity_uint32_T(Apad, i);
  i = Apadpre->size[1] + 1;
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, nhood, nsizeT, 2.0,
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, bv, nsizeT, 2.0, &b_B->data[0],
                       true);
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, bv1, nsizeT, 2.0, &b_B->data
                       [0], true);
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, bv, nsizeT, 2.0, &b_B->data[0],
                       true);
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, nhood, nsizeT, 2.0,
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, bv2, nsizeT, 2.0, &b_B->data
                       [0], true);
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, bv3, nsizeT, 2.0, &b_B->data
                       [0], true);
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, bv4, nsizeT, 2.0, &b_B->data
                       [0], true);
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, b_nhood, nsizeT, 2.0,
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
  nsizeT[0] = 7.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, b_nhood, nsizeT, 2.0,
                       &b_B->data[0], true);
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
  int32_T i;
  int32_T loop_ub;
  uint32_T mask_value;
  emxArray_uint32_T *Apadpre;
  int32_T pad_ul_idx_0;
  int32_T i1;
  int32_T i2;
  int32_T pad_ul_idx_1;
  emxArray_uint32_T *Apad;
  emxArray_uint32_T *b_B;
  boolean_T nhood[3];
  real_T sizeB[2];
  real_T nsizeT[2];
  boolean_T b_nhood;
  boolean_T c_nhood[9];
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
      b_A->data[(A->size[0] + b_A->size[0] * i) - 1] = A->data[(A->size[0] +
        A->size[0] * i) - 1] & mask_value;
    }
  }

  emxInit_uint32_T(&Apadpre, 2, true);
  if ((b_A->size[0] == 0) || (b_A->size[1] == 0)) {
    i = (int32_T)(uint32_T)((real_T)b_A->size[0] + 1.0);
    i1 = Apadpre->size[0] * Apadpre->size[1];
    Apadpre->size[0] = i;
    i2 = (int32_T)(uint32_T)((real_T)b_A->size[1] + 5.0);
    Apadpre->size[1] = i2;
    emxEnsureCapacity_uint32_T(Apadpre, i1);
    loop_ub = i * i2;
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
  i1 = Apadpre->size[1] + 5;
  Apad->size[1] = i1;
  emxEnsureCapacity_uint32_T(Apad, i);
  i = Apadpre->size[1] + 1;
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, nhood, nsizeT, 2.0,
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, &b_nhood, nsizeT, 2.0,
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, &b_nhood, nsizeT, 2.0,
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, &b_nhood, nsizeT, 2.0,
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, nhood, nsizeT, 2.0,
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, &b_nhood, nsizeT, 2.0,
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, &b_nhood, nsizeT, 2.0,
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, &b_nhood, nsizeT, 2.0,
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
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, c_nhood, nsizeT, 2.0,
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
  nsizeT[0] = 9.0;
  sizeB[1] = Apad->size[1];
  nsizeT[1] = 1.0;
  dilate_packed_uint32(&Apad->data[0], sizeB, 2.0, c_nhood, nsizeT, 2.0,
                       &b_B->data[0], true);
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

/* End of code generation (imdilate.c) */
