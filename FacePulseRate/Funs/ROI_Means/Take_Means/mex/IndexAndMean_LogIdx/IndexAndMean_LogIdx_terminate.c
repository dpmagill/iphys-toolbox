/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * IndexAndMean_LogIdx_terminate.c
 *
 * Code generation for function 'IndexAndMean_LogIdx_terminate'
 *
 */

/* Include files */
#include "IndexAndMean_LogIdx_terminate.h"
#include "IndexAndMean_LogIdx.h"
#include "IndexAndMean_LogIdx_data.h"
#include "_coder_IndexAndMean_LogIdx_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void IndexAndMean_LogIdx_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void IndexAndMean_LogIdx_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (IndexAndMean_LogIdx_terminate.c) */
