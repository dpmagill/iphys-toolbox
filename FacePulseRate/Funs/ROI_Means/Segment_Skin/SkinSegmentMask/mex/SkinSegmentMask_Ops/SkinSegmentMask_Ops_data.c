/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinSegmentMask_Ops_data.c
 *
 * Code generation for function 'SkinSegmentMask_Ops_data'
 *
 */

/* Include files */
#include "SkinSegmentMask_Ops_data.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
omp_lock_t emlrtLockGlobal;
omp_nest_lock_t emlrtNestLockGlobal;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131595U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "SkinSegmentMask_Ops",               /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 3334497894U, 1318968193U, 3466680636U, 2802620837U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

const boolean_T bv[9] = { true, false, false, false, true, false, false, false,
  true };

const boolean_T bv1[9] = { false, false, true, false, true, false, true, false,
  false };

const boolean_T bv2[15] = { true, false, false, false, false, false, false, true,
  false, false, false, false, false, false, true };

const boolean_T bv3[15] = { false, false, true, false, false, false, false, true,
  false, false, false, false, true, false, false };

const boolean_T bv4[15] = { false, false, false, false, true, false, false, true,
  false, false, true, false, false, false, false };

/* End of code generation (SkinSegmentMask_Ops_data.c) */
