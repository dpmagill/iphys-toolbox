/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ConfirmSkinPresent_SkinDetectReject_mex.c
 *
 * Code generation for function '_coder_ConfirmSkinPresent_SkinDetectReject_mex'
 *
 */

/* Include files */
#include "_coder_ConfirmSkinPresent_SkinDetectReject_mex.h"
#include "ConfirmSkinPresent_SkinDetectReject.h"
#include "ConfirmSkinPresent_SkinDetectReject_data.h"
#include "ConfirmSkinPresent_SkinDetectReject_initialize.h"
#include "ConfirmSkinPresent_SkinDetectReject_terminate.h"
#include "_coder_ConfirmSkinPresent_SkinDetectReject_api.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void c_ConfirmSkinPresent_SkinDetect(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[10]);

/* Function Definitions */
void c_ConfirmSkinPresent_SkinDetect(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs, const mxArray *prhs[10])
{
  const mxArray *outputs[1];

  /* Check for proper number of arguments. */
  if (nrhs != 10) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 10, 4, 35, "ConfirmSkinPresent_SkinDetectReject");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 35,
                        "ConfirmSkinPresent_SkinDetectReject");
  }

  /* Call the function. */
  ConfirmSkinPresent_SkinDetectReject_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&ConfirmSkinPresent_SkinDetectReject_atexit);

  /* Module initialization. */
  ConfirmSkinPresent_SkinDetectReject_initialize();

  /* Dispatch the entry-point. */
  c_ConfirmSkinPresent_SkinDetect(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  ConfirmSkinPresent_SkinDetectReject_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_ConfirmSkinPresent_SkinDetectReject_mex.c) */
