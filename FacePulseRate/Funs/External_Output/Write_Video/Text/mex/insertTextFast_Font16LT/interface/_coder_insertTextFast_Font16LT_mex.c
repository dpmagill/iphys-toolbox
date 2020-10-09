/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_insertTextFast_Font16LT_mex.c
 *
 * Code generation for function '_coder_insertTextFast_Font16LT_mex'
 *
 */

/* Include files */
#include "_coder_insertTextFast_Font16LT_mex.h"
#include "_coder_insertTextFast_Font16LT_api.h"
#include "insertTextFast_Font16LT.h"
#include "insertTextFast_Font16LT_data.h"
#include "insertTextFast_Font16LT_initialize.h"
#include "insertTextFast_Font16LT_terminate.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void c_insertTextFast_Font16LT_mexFu(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[5]);

/* Function Definitions */
void c_insertTextFast_Font16LT_mexFu(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs, const mxArray *prhs[5])
{
  const mxArray *outputs[1];

  /* Check for proper number of arguments. */
  if (nrhs != 5) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 5, 4, 23, "insertTextFast_Font16LT");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 23,
                        "insertTextFast_Font16LT");
  }

  /* Call the function. */
  insertTextFast_Font16LT_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&insertTextFast_Font16LT_atexit);

  /* Module initialization. */
  insertTextFast_Font16LT_initialize();

  /* Dispatch the entry-point. */
  c_insertTextFast_Font16LT_mexFu(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  insertTextFast_Font16LT_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_insertTextFast_Font16LT_mex.c) */
