/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertTextFast_Font14LT_terminate.c
 *
 * Code generation for function 'insertTextFast_Font14LT_terminate'
 *
 */

/* Include files */
#include "insertTextFast_Font14LT_terminate.h"
#include "_coder_insertTextFast_Font14LT_mex.h"
#include "insertTextFast_Font14LT.h"
#include "insertTextFast_Font14LT_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void insertTextFast_Font14LT_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void insertTextFast_Font14LT_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (insertTextFast_Font14LT_terminate.c) */