/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_Interp_mex.c
 *
 * Code generation for function '_coder_Interp_mex'
 *
 */

/* Include files */
#include "_coder_Interp_mex.h"
#include "Interp.h"
#include "Interp_data.h"
#include "Interp_initialize.h"
#include "Interp_terminate.h"
#include "_coder_Interp_api.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void Interp_mexFunction(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[10]);

/* Function Definitions */
void Interp_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs, const
  mxArray *prhs[10])
{
  const mxArray *outputs[1];

  /* Check for proper number of arguments. */
  if (nrhs != 10) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 10, 4, 6, "Interp");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 6,
                        "Interp");
  }

  /* Call the function. */
  Interp_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&Interp_atexit);

  /* Module initialization. */
  Interp_initialize();

  /* Dispatch the entry-point. */
  Interp_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  Interp_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_Interp_mex.c) */
