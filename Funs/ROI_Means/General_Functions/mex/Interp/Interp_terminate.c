/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Interp_terminate.c
 *
 * Code generation for function 'Interp_terminate'
 *
 */

/* Include files */
#include "Interp_terminate.h"
#include "Interp.h"
#include "Interp_data.h"
#include "_coder_Interp_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void Interp_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void Interp_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (Interp_terminate.c) */
