/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_insertTextFast_ROIAnnotation20_mex.c
 *
 * Code generation for function '_coder_insertTextFast_ROIAnnotation20_mex'
 *
 */

/* Include files */
#include "_coder_insertTextFast_ROIAnnotation20_mex.h"
#include "_coder_insertTextFast_ROIAnnotation20_api.h"
#include "insertTextFast_ROIAnnotation20.h"
#include "insertTextFast_ROIAnnotation20_data.h"
#include "insertTextFast_ROIAnnotation20_initialize.h"
#include "insertTextFast_ROIAnnotation20_terminate.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void c_insertTextFast_ROIAnnotation2(int32_T nlhs, mxArray
  *plhs[1], int32_T nrhs, const mxArray *prhs[2]);

/* Function Definitions */
void c_insertTextFast_ROIAnnotation2(int32_T nlhs, mxArray *plhs[1], int32_T
  nrhs, const mxArray *prhs[2])
{
  const mxArray *outputs[1];

  /* Check for proper number of arguments. */
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 2, 4, 30, "insertTextFast_ROIAnnotation20");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 30,
                        "insertTextFast_ROIAnnotation20");
  }

  /* Call the function. */
  insertTextFast_ROIAnnotation20_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&insertTextFast_ROIAnnotation20_atexit);

  /* Module initialization. */
  insertTextFast_ROIAnnotation20_initialize();

  /* Dispatch the entry-point. */
  c_insertTextFast_ROIAnnotation2(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  insertTextFast_ROIAnnotation20_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_insertTextFast_ROIAnnotation20_mex.c) */
