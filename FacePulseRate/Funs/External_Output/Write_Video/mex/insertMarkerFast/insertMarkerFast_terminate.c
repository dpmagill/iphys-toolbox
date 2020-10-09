/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertMarkerFast_terminate.c
 *
 * Code generation for function 'insertMarkerFast_terminate'
 *
 */

/* Include files */
#include "insertMarkerFast_terminate.h"
#include "_coder_insertMarkerFast_mex.h"
#include "insertMarkerFast.h"
#include "insertMarkerFast_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void insertMarkerFast_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void insertMarkerFast_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (insertMarkerFast_terminate.c) */
