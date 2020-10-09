/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertTextFast_ROIAnnotation13_terminate.c
 *
 * Code generation for function 'insertTextFast_ROIAnnotation13_terminate'
 *
 */

/* Include files */
#include "insertTextFast_ROIAnnotation13_terminate.h"
#include "_coder_insertTextFast_ROIAnnotation13_mex.h"
#include "insertTextFast_ROIAnnotation13.h"
#include "insertTextFast_ROIAnnotation13_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void insertTextFast_ROIAnnotation13_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void insertTextFast_ROIAnnotation13_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (insertTextFast_ROIAnnotation13_terminate.c) */
