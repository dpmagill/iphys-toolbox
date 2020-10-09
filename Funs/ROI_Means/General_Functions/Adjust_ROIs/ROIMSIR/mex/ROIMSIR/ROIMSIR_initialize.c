/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIMSIR_initialize.c
 *
 * Code generation for function 'ROIMSIR_initialize'
 *
 */

/* Include files */
#include "ROIMSIR_initialize.h"
#include "ROIMSIR_data.h"
#include "_coder_ROIMSIR_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ROIMSIR_initialize(void)
{
  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (ROIMSIR_initialize.c) */
