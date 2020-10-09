/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertShapeFast_Line_initialize.c
 *
 * Code generation for function 'insertShapeFast_Line_initialize'
 *
 */

/* Include files */
#include "insertShapeFast_Line_initialize.h"
#include "_coder_insertShapeFast_Line_mex.h"
#include "insertShapeFast_Line.h"
#include "insertShapeFast_Line_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void insertShapeFast_Line_initialize(void)
{
  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (insertShapeFast_Line_initialize.c) */
