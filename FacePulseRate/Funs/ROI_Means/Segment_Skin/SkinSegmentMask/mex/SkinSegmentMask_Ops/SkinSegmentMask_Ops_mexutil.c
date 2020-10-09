/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinSegmentMask_Ops_mexutil.c
 *
 * Code generation for function 'SkinSegmentMask_Ops_mexutil'
 *
 */

/* Include files */
#include "SkinSegmentMask_Ops_mexutil.h"
#include "SkinSegmentMask_Ops.h"
#include "SkinSegmentMask_Ops_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
emlrtCTX emlrtGetRootTLSGlobal(void)
{
  return emlrtRootTLSGlobal;
}

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, const emlrtConstCTX aTLS,
  void *aData)
{
  omp_set_lock(&emlrtLockGlobal);
  emlrtCallLockeeFunction(aLockee, aTLS, aData);
  omp_unset_lock(&emlrtLockGlobal);
}

/* End of code generation (SkinSegmentMask_Ops_mexutil.c) */
