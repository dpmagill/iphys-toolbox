/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_insertMarkerFast_mex.c
 *
 * Code generation for function '_coder_insertMarkerFast_mex'
 *
 */

/* Include files */
#include "_coder_insertMarkerFast_mex.h"
#include "_coder_insertMarkerFast_api.h"
#include "insertMarkerFast.h"
#include "insertMarkerFast_data.h"
#include "insertMarkerFast_initialize.h"
#include "insertMarkerFast_terminate.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void insertMarkerFast_mexFunction(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[3]);

/* Function Definitions */
void insertMarkerFast_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
  const mxArray *prhs[3])
{
  const mxArray *outputs[1];

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 3, 4, 16, "insertMarkerFast");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 16,
                        "insertMarkerFast");
  }

  /* Call the function. */
  insertMarkerFast_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&insertMarkerFast_atexit);

  /* Module initialization. */
  insertMarkerFast_initialize();

  /* Dispatch the entry-point. */
  insertMarkerFast_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  insertMarkerFast_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_insertMarkerFast_mex.c) */
