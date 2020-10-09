/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIAdjustIfExceedsFrameDims_terminate.c
 *
 * Code generation for function 'ROIAdjustIfExceedsFrameDims_terminate'
 *
 */

/* Include files */
#include "ROIAdjustIfExceedsFrameDims_terminate.h"
#include "ROIAdjustIfExceedsFrameDims.h"
#include "ROIAdjustIfExceedsFrameDims_data.h"
#include "_coder_ROIAdjustIfExceedsFrameDims_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ROIAdjustIfExceedsFrameDims_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void ROIAdjustIfExceedsFrameDims_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (ROIAdjustIfExceedsFrameDims_terminate.c) */
