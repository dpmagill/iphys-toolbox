/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * bwpack.c
 *
 * Code generation for function 'bwpack'
 *
 */

/* Include files */
#include "bwpack.h"
#include "SkinDetect_emxutil.h"
#include "SkinDetect_types.h"
#include "rt_nonfinite.h"
#include "libmwbwpackctbb.h"
#include "mwmathutil.h"

/* Function Definitions */
void bwpack(const emxArray_boolean_T *varargin_1, emxArray_uint32_T *BWP)
{
  real_T bwSize[2];
  real_T bwpSize[2];
  int32_T i;
  int32_T x;
  x = (int32_T)muDoubleScalarCeil((real_T)varargin_1->size[0] / 32.0);
  if ((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0)) {
    i = BWP->size[0] * BWP->size[1];
    BWP->size[0] = x;
    BWP->size[1] = varargin_1->size[1];
    emxEnsureCapacity_uint32_T(BWP, i);
    x *= varargin_1->size[1];
    for (i = 0; i < x; i++) {
      BWP->data[i] = 0U;
    }
  } else {
    i = BWP->size[0] * BWP->size[1];
    BWP->size[0] = x;
    BWP->size[1] = varargin_1->size[1];
    emxEnsureCapacity_uint32_T(BWP, i);
    bwSize[0] = varargin_1->size[0];
    bwSize[1] = varargin_1->size[1];
    bwpSize[0] = x;
    bwpSize[1] = varargin_1->size[1];
    bwPackingtbb(&varargin_1->data[0], &bwSize[0], &BWP->data[0], &bwpSize[0],
                 true);
  }
}

/* End of code generation (bwpack.c) */
