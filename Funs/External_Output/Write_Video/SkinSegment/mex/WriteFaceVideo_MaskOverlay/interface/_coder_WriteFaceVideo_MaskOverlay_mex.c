/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_WriteFaceVideo_MaskOverlay_mex.c
 *
 * Code generation for function '_coder_WriteFaceVideo_MaskOverlay_mex'
 *
 */

/* Include files */
#include "_coder_WriteFaceVideo_MaskOverlay_mex.h"
#include "WriteFaceVideo_MaskOverlay.h"
#include "WriteFaceVideo_MaskOverlay_data.h"
#include "WriteFaceVideo_MaskOverlay_initialize.h"
#include "WriteFaceVideo_MaskOverlay_terminate.h"
#include "_coder_WriteFaceVideo_MaskOverlay_api.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void c_WriteFaceVideo_MaskOverlay_me(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[6]);

/* Function Definitions */
void c_WriteFaceVideo_MaskOverlay_me(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs, const mxArray *prhs[6])
{
  const mxArray *outputs[1];

  /* Check for proper number of arguments. */
  if (nrhs != 6) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 6, 4, 26, "WriteFaceVideo_MaskOverlay");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 26,
                        "WriteFaceVideo_MaskOverlay");
  }

  /* Call the function. */
  WriteFaceVideo_MaskOverlay_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&WriteFaceVideo_MaskOverlay_atexit);

  /* Module initialization. */
  WriteFaceVideo_MaskOverlay_initialize();

  /* Dispatch the entry-point. */
  c_WriteFaceVideo_MaskOverlay_me(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  WriteFaceVideo_MaskOverlay_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_WriteFaceVideo_MaskOverlay_mex.c) */
