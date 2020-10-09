/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertShapeFast_FilledCircles_initialize.c
 *
 * Code generation for function 'insertShapeFast_FilledCircles_initialize'
 *
 */

/* Include files */
#include "insertShapeFast_FilledCircles_initialize.h"
#include "_coder_insertShapeFast_FilledCircles_mex.h"
#include "insertShapeFast_FilledCircles.h"
#include "insertShapeFast_FilledCircles_data.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static const volatile char_T *emlrtBreakCheckR2012bFlagVar = NULL;

/* Function Definitions */
void insertShapeFast_FilledCircles_initialize(void)
{
  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (insertShapeFast_FilledCircles_initialize.c) */
