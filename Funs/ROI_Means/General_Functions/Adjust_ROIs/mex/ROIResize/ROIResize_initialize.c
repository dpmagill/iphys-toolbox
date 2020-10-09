/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIResize_initialize.c
 *
 * Code generation for function 'ROIResize_initialize'
 *
 */

/* Include files */
#include "ROIResize_initialize.h"
#include "ROIResize.h"
#include "ROIResize_data.h"
#include "_coder_ROIResize_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ROIResize_initialize(void)
{
  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (ROIResize_initialize.c) */
