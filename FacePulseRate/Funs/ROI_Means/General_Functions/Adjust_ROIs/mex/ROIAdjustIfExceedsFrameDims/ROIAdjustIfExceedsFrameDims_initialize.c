/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIAdjustIfExceedsFrameDims_initialize.c
 *
 * Code generation for function 'ROIAdjustIfExceedsFrameDims_initialize'
 *
 */

/* Include files */
#include "ROIAdjustIfExceedsFrameDims_initialize.h"
#include "ROIAdjustIfExceedsFrameDims.h"
#include "ROIAdjustIfExceedsFrameDims_data.h"
#include "_coder_ROIAdjustIfExceedsFrameDims_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ROIAdjustIfExceedsFrameDims_initialize(void)
{
  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (ROIAdjustIfExceedsFrameDims_initialize.c) */
