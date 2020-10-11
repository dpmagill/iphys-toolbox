/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * setPackedFillBits.c
 *
 * Code generation for function 'setPackedFillBits'
 *
 */

/* Include files */
#include "setPackedFillBits.h"
#include "SkinSegmentMask_Ops_data.h"
#include "SkinSegmentMask_Ops_emxutil.h"
#include "SkinSegmentMask_Ops_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Function Definitions */
void b_setPackedFillBits(emxArray_uint32_T *A)
{
  emxArray_uint32_T *r;
  int32_T b_A;
  int32_T c_A;
  int32_T i;
  int32_T k;
  uint32_T mask_value;
  uint32_T varargin_1;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  if ((A->size[0] != 0) && (A->size[1] != 0)) {
    mask_value = 0U;
    for (k = 0; k < 31; k++) {
      mask_value |= 1U << k;
    }

    emxInit_uint32_T(&r, 2, true);
    k = A->size[0] - 1;
    b_A = A->size[1] - 1;
    c_A = A->size[0] - 1;
    i = r->size[0] * r->size[1];
    r->size[0] = 1;
    r->size[1] = b_A + 1;
    emxEnsureCapacity_uint32_T(r, i);
    for (i = 0; i <= b_A; i++) {
      varargin_1 = A->data[k + A->size[0] * i];
      r->data[i] = varargin_1 & mask_value;
    }

    k = r->size[1];
    for (i = 0; i < k; i++) {
      A->data[c_A + A->size[0] * i] = r->data[i];
    }

    emxFree_uint32_T(&r);
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

void setPackedFillBits(emxArray_uint32_T *A, real_T M)
{
  emxArray_real_T *bit_locations;
  emxArray_uint32_T *r;
  real_T num_pad_bits;
  int32_T b_A;
  int32_T c_A;
  int32_T i;
  int32_T loop_ub;
  uint32_T mask_value;
  uint32_T varargin_1;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  if ((A->size[0] != 0) && (A->size[1] != 0)) {
    num_pad_bits = 32.0 * muDoubleScalarCeil(M / 32.0) - M;
    if (!(num_pad_bits == 0.0)) {
      emxInit_real_T(&bit_locations, 2, true);
      if (32.0 - num_pad_bits < 1.0) {
        bit_locations->size[0] = 1;
        bit_locations->size[1] = 0;
      } else {
        i = bit_locations->size[0] * bit_locations->size[1];
        bit_locations->size[0] = 1;
        loop_ub = (int32_T)muDoubleScalarFloor((32.0 - num_pad_bits) - 1.0);
        bit_locations->size[1] = loop_ub + 1;
        emxEnsureCapacity_real_T(bit_locations, i);
        for (i = 0; i <= loop_ub; i++) {
          bit_locations->data[i] = (real_T)i + 1.0;
        }
      }

      mask_value = 0U;
      i = bit_locations->size[1];
      for (loop_ub = 0; loop_ub < i; loop_ub++) {
        mask_value |= 1U << (uint8_T)((uint8_T)bit_locations->data[loop_ub] - 1U);
      }

      emxFree_real_T(&bit_locations);
      emxInit_uint32_T(&r, 2, true);
      mask_value = ~mask_value;
      loop_ub = A->size[0] - 1;
      b_A = A->size[1] - 1;
      c_A = A->size[0] - 1;
      i = r->size[0] * r->size[1];
      r->size[0] = 1;
      r->size[1] = b_A + 1;
      emxEnsureCapacity_uint32_T(r, i);
      for (i = 0; i <= b_A; i++) {
        varargin_1 = A->data[loop_ub + A->size[0] * i];
        r->data[i] = varargin_1 | mask_value;
      }

      loop_ub = r->size[1];
      for (i = 0; i < loop_ub; i++) {
        A->data[c_A + A->size[0] * i] = r->data[i];
      }

      emxFree_uint32_T(&r);
    }
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (setPackedFillBits.c) */
