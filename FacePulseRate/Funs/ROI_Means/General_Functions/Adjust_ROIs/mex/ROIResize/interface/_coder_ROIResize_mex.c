/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ROIResize_mex.c
 *
 * Code generation for function '_coder_ROIResize_mex'
 *
 */

/* Include files */
#include "_coder_ROIResize_mex.h"
#include "ROIResize.h"
#include "ROIResize_data.h"
#include "ROIResize_initialize.h"
#include "ROIResize_terminate.h"
#include "_coder_ROIResize_api.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void ROIResize_mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[6]);

/* Function Definitions */
void ROIResize_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs, const
  mxArray *prhs[6])
{
  const mxArray *outputs[1];

  /* Check for proper number of arguments. */
  if (nrhs != 6) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 6, 4, 9, "ROIResize");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 9,
                        "ROIResize");
  }

  /* Call the function. */
  ROIResize_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&ROIResize_atexit);

  /* Module initialization. */
  ROIResize_initialize();

  /* Dispatch the entry-point. */
  ROIResize_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  ROIResize_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_ROIResize_mex.c) */
