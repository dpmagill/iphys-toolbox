/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertShapeFast_FilledCircles_terminate.c
 *
 * Code generation for function 'insertShapeFast_FilledCircles_terminate'
 *
 */

/* Include files */
#include "insertShapeFast_FilledCircles_terminate.h"
#include "_coder_insertShapeFast_FilledCircles_mex.h"
#include "insertShapeFast_FilledCircles.h"
#include "insertShapeFast_FilledCircles_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void insertShapeFast_FilledCircles_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void insertShapeFast_FilledCircles_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (insertShapeFast_FilledCircles_terminate.c) */
