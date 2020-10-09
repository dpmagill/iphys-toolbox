/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertTextFast_PulseRate20_initialize.c
 *
 * Code generation for function 'insertTextFast_PulseRate20_initialize'
 *
 */

/* Include files */
#include "insertTextFast_PulseRate20_initialize.h"
#include "_coder_insertTextFast_PulseRate20_mex.h"
#include "insertTextFast_PulseRate20.h"
#include "insertTextFast_PulseRate20_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void insertTextFast_PulseRate20_initialize(void)
{
  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (insertTextFast_PulseRate20_initialize.c) */
