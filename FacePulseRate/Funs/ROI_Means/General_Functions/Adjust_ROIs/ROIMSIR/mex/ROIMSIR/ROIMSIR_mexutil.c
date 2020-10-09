/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIMSIR_mexutil.c
 *
 * Code generation for function 'ROIMSIR_mexutil'
 *
 */

/* Include files */
#include "ROIMSIR_mexutil.h"
#include "ROIMSIR_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
real_T b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = bb_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

real_T bb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 0U,
    &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

const mxArray *d_emlrt_marshallOut(const int32_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m) = u;
  emlrtAssign(&y, m);
  return y;
}

real_T emlrt_marshallIn(const mxArray *a__output_of_length_, const char_T
  *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(emlrtAlias(a__output_of_length_), &thisId);
  emlrtDestroyArray(&a__output_of_length_);
  return y;
}

/* End of code generation (ROIMSIR_mexutil.c) */
