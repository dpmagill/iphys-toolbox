/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_insertShapeFast_FilledCircles_mex.c
 *
 * Code generation for function '_coder_insertShapeFast_FilledCircles_mex'
 *
 */

/* Include files */
#include "_coder_insertShapeFast_FilledCircles_mex.h"
#include "_coder_insertShapeFast_FilledCircles_api.h"
#include "insertShapeFast_FilledCircles.h"
#include "insertShapeFast_FilledCircles_data.h"
#include "insertShapeFast_FilledCircles_initialize.h"
#include "insertShapeFast_FilledCircles_terminate.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void c_insertShapeFast_FilledCircles(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[2]);

/* Function Definitions */
void c_insertShapeFast_FilledCircles(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs, const mxArray *prhs[2])
{
  const mxArray *outputs[1];

  /* Check for proper number of arguments. */
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 2, 4, 29, "insertShapeFast_FilledCircles");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 29,
                        "insertShapeFast_FilledCircles");
  }

  /* Call the function. */
  insertShapeFast_FilledCircles_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&insertShapeFast_FilledCircles_atexit);

  /* Module initialization. */
  insertShapeFast_FilledCircles_initialize();

  /* Dispatch the entry-point. */
  c_insertShapeFast_FilledCircles(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  insertShapeFast_FilledCircles_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_insertShapeFast_FilledCircles_mex.c) */
