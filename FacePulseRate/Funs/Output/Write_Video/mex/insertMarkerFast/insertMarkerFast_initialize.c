/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertMarkerFast_initialize.c
 *
 * Code generation for function 'insertMarkerFast_initialize'
 *
 */

/* Include files */
#include "insertMarkerFast_initialize.h"
#include "_coder_insertMarkerFast_mex.h"
#include "insertMarkerFast.h"
#include "insertMarkerFast_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void insertMarkerFast_initialize(void)
{
  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (insertMarkerFast_initialize.c) */
