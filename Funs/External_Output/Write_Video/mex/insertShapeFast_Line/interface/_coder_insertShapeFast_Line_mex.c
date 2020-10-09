/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_insertShapeFast_Line_mex.c
 *
 * Code generation for function '_coder_insertShapeFast_Line_mex'
 *
 */

/* Include files */
#include "_coder_insertShapeFast_Line_mex.h"
#include "_coder_insertShapeFast_Line_api.h"
#include "insertShapeFast_Line.h"
#include "insertShapeFast_Line_data.h"
#include "insertShapeFast_Line_initialize.h"
#include "insertShapeFast_Line_terminate.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void c_insertShapeFast_Line_mexFunct(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[3]);

/* Function Definitions */
void c_insertShapeFast_Line_mexFunct(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs, const mxArray *prhs[3])
{
  const mxArray *outputs[1];

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 3, 4, 20, "insertShapeFast_Line");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 20,
                        "insertShapeFast_Line");
  }

  /* Call the function. */
  insertShapeFast_Line_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&insertShapeFast_Line_atexit);

  /* Module initialization. */
  insertShapeFast_Line_initialize();

  /* Dispatch the entry-point. */
  c_insertShapeFast_Line_mexFunct(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  insertShapeFast_Line_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_insertShapeFast_Line_mex.c) */
