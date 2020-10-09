/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIResize_terminate.c
 *
 * Code generation for function 'ROIResize_terminate'
 *
 */

/* Include files */
#include "ROIResize_terminate.h"
#include "ROIResize.h"
#include "ROIResize_data.h"
#include "_coder_ROIResize_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ROIResize_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void ROIResize_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (ROIResize_terminate.c) */
