/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * IndexAndMean_LogIdx_initialize.c
 *
 * Code generation for function 'IndexAndMean_LogIdx_initialize'
 *
 */

/* Include files */
#include "IndexAndMean_LogIdx_initialize.h"
#include "IndexAndMean_LogIdx.h"
#include "IndexAndMean_LogIdx_data.h"
#include "_coder_IndexAndMean_LogIdx_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void IndexAndMean_LogIdx_initialize(void)
{
  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (IndexAndMean_LogIdx_initialize.c) */
