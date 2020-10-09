/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_SkinDetect_mex.c
 *
 * Code generation for function '_coder_SkinDetect_mex'
 *
 */

/* Include files */
#include "_coder_SkinDetect_mex.h"
#include "SkinDetect.h"
#include "SkinDetect_data.h"
#include "SkinDetect_initialize.h"
#include "SkinDetect_terminate.h"
#include "_coder_SkinDetect_api.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static jmp_buf emlrtJBEnviron;

/* Function Definitions */
void SkinDetect_mexFunction(int32_T nlhs, mxArray *plhs[5], int32_T nrhs, const
  mxArray *prhs[16])
{
  const mxArray *outputs[5];
  int32_T b_nlhs;

  /* Check for proper number of arguments. */
  if (nrhs != 16) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 16, 4, 10, "SkinDetect");
  }

  if (nlhs > 5) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 10,
                        "SkinDetect");
  }

  /* Call the function. */
  SkinDetect_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexAtExit(&SkinDetect_atexit);
  emlrtLoadLibrary("C:\\ProgramData\\MATLAB\\SupportPackages\\R2020a\\3P.instrset\\mingw_w64.instrset\\bin\\libgomp-1.dll");

  /* Initialize the memory manager. */
  omp_init_lock(&emlrtLockGlobal);
  omp_init_nest_lock(&emlrtNestLockGlobal);

  /* Module initialization. */
  SkinDetect_initialize();
  st.tls = emlrtRootTLSGlobal;
  emlrtSetJmpBuf(&st, &emlrtJBEnviron);
  if (setjmp(emlrtJBEnviron) == 0) {
    /* Dispatch the entry-point. */
    SkinDetect_mexFunction(nlhs, plhs, nrhs, prhs);

    /* Module termination. */
    SkinDetect_terminate();
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&emlrtNestLockGlobal);
  } else {
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&emlrtNestLockGlobal);
    emlrtReportParallelRunTimeError(&st);
  }
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal,
                     &emlrtLockerFunction, omp_get_num_procs());
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_SkinDetect_mex.c) */
