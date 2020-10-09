/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinSegmentMask_Ops_terminate.c
 *
 * Code generation for function 'SkinSegmentMask_Ops_terminate'
 *
 */

/* Include files */
#include "SkinSegmentMask_Ops_terminate.h"
#include "SkinSegmentMask_MorphClose.h"
#include "SkinSegmentMask_Ops.h"
#include "SkinSegmentMask_Ops_data.h"
#include "SkinSegmentMask_Threshold.h"
#include "_coder_SkinSegmentMask_Ops_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void SkinSegmentMask_Ops_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  ErodeAndDilate_SERadius14_free();
  ErodeAndDilate_SERadius6_free();
  ErodeAndDilate_SEWidth50_free();
  ErodeAndDilate_SEWidth22_free();
  SkinSegmentMask_Threshold_free();
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void SkinSegmentMask_Ops_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (SkinSegmentMask_Ops_terminate.c) */
