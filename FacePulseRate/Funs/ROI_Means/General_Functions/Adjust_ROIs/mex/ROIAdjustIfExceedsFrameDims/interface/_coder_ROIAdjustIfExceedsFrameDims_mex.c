/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ROIAdjustIfExceedsFrameDims_mex.c
 *
 * Code generation for function '_coder_ROIAdjustIfExceedsFrameDims_mex'
 *
 */

/* Include files */
#include "_coder_ROIAdjustIfExceedsFrameDims_mex.h"
#include "ROIAdjustIfExceedsFrameDims.h"
#include "ROIAdjustIfExceedsFrameDims_data.h"
#include "ROIAdjustIfExceedsFrameDims_initialize.h"
#include "ROIAdjustIfExceedsFrameDims_terminate.h"
#include "_coder_ROIAdjustIfExceedsFrameDims_api.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void c_ROIAdjustIfExceedsFrameDims_m(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[3]);

/* Function Definitions */
void c_ROIAdjustIfExceedsFrameDims_m(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs, const mxArray *prhs[3])
{
  const mxArray *outputs[1];

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 3, 4, 27, "ROIAdjustIfExceedsFrameDims");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 27,
                        "ROIAdjustIfExceedsFrameDims");
  }

  /* Call the function. */
  ROIAdjustIfExceedsFrameDims_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&ROIAdjustIfExceedsFrameDims_atexit);

  /* Module initialization. */
  ROIAdjustIfExceedsFrameDims_initialize();

  /* Dispatch the entry-point. */
  c_ROIAdjustIfExceedsFrameDims_m(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  ROIAdjustIfExceedsFrameDims_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_ROIAdjustIfExceedsFrameDims_mex.c) */
