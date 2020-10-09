/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Interp_initialize.c
 *
 * Code generation for function 'Interp_initialize'
 *
 */

/* Include files */
#include "Interp_initialize.h"
#include "Interp.h"
#include "Interp_data.h"
#include "_coder_Interp_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void Interp_initialize(void)
{
  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (Interp_initialize.c) */
