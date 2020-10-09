/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * WriteFaceVideo_MaskOverlay_initialize.c
 *
 * Code generation for function 'WriteFaceVideo_MaskOverlay_initialize'
 *
 */

/* Include files */
#include "WriteFaceVideo_MaskOverlay_initialize.h"
#include "WriteFaceVideo_MaskOverlay.h"
#include "WriteFaceVideo_MaskOverlay_data.h"
#include "_coder_WriteFaceVideo_MaskOverlay_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void WriteFaceVideo_MaskOverlay_initialize(void)
{
  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (WriteFaceVideo_MaskOverlay_initialize.c) */
