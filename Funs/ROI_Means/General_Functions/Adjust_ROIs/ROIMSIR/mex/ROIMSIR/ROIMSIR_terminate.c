/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIMSIR_terminate.c
 *
 * Code generation for function 'ROIMSIR_terminate'
 *
 */

/* Include files */
#include "ROIMSIR_terminate.h"
#include "ROIMSIR_data.h"
#include "_coder_ROIMSIR_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ROIMSIR_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void ROIMSIR_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (ROIMSIR_terminate.c) */
