/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * WriteFaceVideo_MaskOverlay_terminate.c
 *
 * Code generation for function 'WriteFaceVideo_MaskOverlay_terminate'
 *
 */

/* Include files */
#include "WriteFaceVideo_MaskOverlay_terminate.h"
#include "WriteFaceVideo_MaskOverlay.h"
#include "WriteFaceVideo_MaskOverlay_data.h"
#include "_coder_WriteFaceVideo_MaskOverlay_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void WriteFaceVideo_MaskOverlay_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void WriteFaceVideo_MaskOverlay_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (WriteFaceVideo_MaskOverlay_terminate.c) */
