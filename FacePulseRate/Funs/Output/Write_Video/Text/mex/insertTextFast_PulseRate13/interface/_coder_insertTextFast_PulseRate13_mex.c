/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_insertTextFast_PulseRate13_mex.c
 *
 * Code generation for function '_coder_insertTextFast_PulseRate13_mex'
 *
 */

/* Include files */
#include "_coder_insertTextFast_PulseRate13_mex.h"
#include "_coder_insertTextFast_PulseRate13_api.h"
#include "insertTextFast_PulseRate13.h"
#include "insertTextFast_PulseRate13_data.h"
#include "insertTextFast_PulseRate13_initialize.h"
#include "insertTextFast_PulseRate13_terminate.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void c_insertTextFast_PulseRate13_me(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[2]);

/* Function Definitions */
void c_insertTextFast_PulseRate13_me(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs, const mxArray *prhs[2])
{
  const mxArray *outputs[1];

  /* Check for proper number of arguments. */
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 2, 4, 26, "insertTextFast_PulseRate13");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 26,
                        "insertTextFast_PulseRate13");
  }

  /* Call the function. */
  insertTextFast_PulseRate13_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&insertTextFast_PulseRate13_atexit);

  /* Module initialization. */
  insertTextFast_PulseRate13_initialize();

  /* Dispatch the entry-point. */
  c_insertTextFast_PulseRate13_me(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  insertTextFast_PulseRate13_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_insertTextFast_PulseRate13_mex.c) */
