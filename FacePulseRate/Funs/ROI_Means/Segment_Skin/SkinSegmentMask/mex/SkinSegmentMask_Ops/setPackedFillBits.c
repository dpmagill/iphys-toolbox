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
#include "SkinSegmentMask_Ops.h"
#include "SkinSegmentMask_Ops_data.h"
#include "SkinSegmentMask_Ops_emxutil.h"
#include "mwmathutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void setPackedFillBits(emxArray_uint32_T *A, real_T M)
{
  real_T num_pad_bits;
  emxArray_real_T *bit_locations;
  int32_T i;
  int32_T loop_ub;
  uint32_T mask_value;
  emxArray_uint32_T *b_A;
  int32_T c_A;
  int32_T d_A;
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
        mask_value |= 1U << (uint8_T)((uint8_T)muDoubleScalarRound
          (bit_locations->data[loop_ub]) - 1U);
      }

      emxFree_real_T(&bit_locations);
      emxInit_uint32_T(&b_A, 2, true);
      mask_value = ~mask_value;
      loop_ub = A->size[0] - 1;
      c_A = A->size[1] - 1;
      d_A = A->size[0] - 1;
      i = b_A->size[0] * b_A->size[1];
      b_A->size[0] = 1;
      b_A->size[1] = c_A + 1;
      emxEnsureCapacity_uint32_T(b_A, i);
      for (i = 0; i <= c_A; i++) {
        b_A->data[i] = A->data[loop_ub + A->size[0] * i] | mask_value;
      }

      loop_ub = b_A->size[1];
      for (i = 0; i < loop_ub; i++) {
        A->data[d_A + A->size[0] * i] = b_A->data[i];
      }

      emxFree_uint32_T(&b_A);
    }
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (setPackedFillBits.c) */
