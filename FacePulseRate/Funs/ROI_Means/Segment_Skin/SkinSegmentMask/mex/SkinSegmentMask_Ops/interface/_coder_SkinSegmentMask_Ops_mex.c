/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_SkinSegmentMask_Ops_mex.c
 *
 * Code generation for function '_coder_SkinSegmentMask_Ops_mex'
 *
 */

/* Include files */
#include "_coder_SkinSegmentMask_Ops_mex.h"
#include "SkinSegmentMask_Ops.h"
#include "SkinSegmentMask_Ops_data.h"
#include "SkinSegmentMask_Ops_initialize.h"
#include "SkinSegmentMask_Ops_terminate.h"
#include "_coder_SkinSegmentMask_Ops_api.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static jmp_buf emlrtJBEnviron;

/* Function Definitions */
void SkinSegmentMask_Ops_mexFunction(int32_T nlhs, mxArray *plhs[8], int32_T
  nrhs, const mxArray *prhs[21])
{
  const mxArray *outputs[8];
  int32_T b_nlhs;

  /* Check for proper number of arguments. */
  if (nrhs != 21) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 21, 4, 19, "SkinSegmentMask_Ops");
  }

  if (nlhs > 8) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 19,
                        "SkinSegmentMask_Ops");
  }

  /* Call the function. */
  SkinSegmentMask_Ops_api(prhs, nlhs, outputs);

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

  mexAtExit(&SkinSegmentMask_Ops_atexit);
  emlrtLoadLibrary("C:\\ProgramData\\MATLAB\\SupportPackages\\R2020a\\3P.instrset\\mingw_w64.instrset\\bin\\libgomp-1.dll");

  /* Initialize the memory manager. */
  omp_init_lock(&emlrtLockGlobal);
  omp_init_nest_lock(&emlrtNestLockGlobal);

  /* Module initialization. */
  SkinSegmentMask_Ops_initialize();
  st.tls = emlrtRootTLSGlobal;
  emlrtSetJmpBuf(&st, &emlrtJBEnviron);
  if (setjmp(emlrtJBEnviron) == 0) {
    /* Dispatch the entry-point. */
    SkinSegmentMask_Ops_mexFunction(nlhs, plhs, nrhs, prhs);

    /* Module termination. */
    SkinSegmentMask_Ops_terminate();
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

/* End of code generation (_coder_SkinSegmentMask_Ops_mex.c) */
