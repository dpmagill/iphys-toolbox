/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertShapeFast_Line_terminate.c
 *
 * Code generation for function 'insertShapeFast_Line_terminate'
 *
 */

/* Include files */
#include "insertShapeFast_Line_terminate.h"
#include "_coder_insertShapeFast_Line_mex.h"
#include "insertShapeFast_Line.h"
#include "insertShapeFast_Line_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void insertShapeFast_Line_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void insertShapeFast_Line_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (insertShapeFast_Line_terminate.c) */
