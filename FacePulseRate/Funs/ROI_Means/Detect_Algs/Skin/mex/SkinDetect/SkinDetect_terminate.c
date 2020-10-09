/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect_terminate.c
 *
 * Code generation for function 'SkinDetect_terminate'
 *
 */

/* Include files */
#include "SkinDetect_terminate.h"
#include "SkinDetect_data.h"
#include "SkinSegmentMask_MorphClose.h"
#include "SkinSegmentMask_Threshold.h"
#include "_coder_SkinDetect_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void SkinDetect_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  ErodeAndDilate_SESquare50_free();
  ErodeAndDilate_SESquare32_free();
  ErodeAndDilate_SESquare22_free();
  ErodeAndDilate_SESquare12_free();
  SkinSegmentMask_Threshold_free();
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void SkinDetect_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (SkinDetect_terminate.c) */
