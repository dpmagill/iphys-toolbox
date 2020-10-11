/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * bwunpack.c
 *
 * Code generation for function 'bwunpack'
 *
 */

/* Include files */
#include "bwunpack.h"
#include "SkinSegmentMask_Ops_emxutil.h"
#include "SkinSegmentMask_Ops_types.h"
#include "rt_nonfinite.h"
#include "libmwbwunpackctbb.h"

/* Function Definitions */
void bwunpack(const emxArray_uint32_T *varargin_1, real_T varargin_2,
              emxArray_boolean_T *BW)
{
  real_T bwSize[2];
  real_T bwpSize[2];
  int32_T i;
  int32_T loop_ub;
  if ((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0)) {
    i = BW->size[0] * BW->size[1];
    BW->size[0] = (int32_T)varargin_2;
    BW->size[1] = varargin_1->size[1];
    emxEnsureCapacity_boolean_T(BW, i);
    loop_ub = (int32_T)varargin_2 * varargin_1->size[1];
    for (i = 0; i < loop_ub; i++) {
      BW->data[i] = false;
    }
  } else {
    i = BW->size[0] * BW->size[1];
    BW->size[0] = (int32_T)varargin_2;
    BW->size[1] = varargin_1->size[1];
    emxEnsureCapacity_boolean_T(BW, i);
    bwpSize[0] = varargin_1->size[0];
    bwSize[0] = (int32_T)varargin_2;
    bwpSize[1] = varargin_1->size[1];
    bwSize[1] = varargin_1->size[1];
    bwUnpackingtbb(&varargin_1->data[0], &bwpSize[0], &BW->data[0], &bwSize[0],
                   true);
  }
}

/* End of code generation (bwunpack.c) */
