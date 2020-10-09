/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIMeans_FirstRead_CollectSkinColorSamples_mexutil.c
 *
 * Code generation for function 'ROIMeans_FirstRead_CollectSkinColorSamples_mexutil'
 *
 */

/* Include files */
#include "ROIMeans_FirstRead_CollectSkinColorSamples_mexutil.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_data.h"
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

/* End of code generation (ROIMeans_FirstRead_CollectSkinColorSamples_mexutil.c) */
