/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ROIMeans_FirstRead_CollectSkinColorSamples_mex.c
 *
 * Code generation for function '_coder_ROIMeans_FirstRead_CollectSkinColorSamples_mex'
 *
 */

/* Include files */
#include "_coder_ROIMeans_FirstRead_CollectSkinColorSamples_mex.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_data.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_initialize.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_mexutil.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_terminate.h"
#include "_coder_ROIMeans_FirstRead_CollectSkinColorSamples_api.h"

/* Variable Definitions */
static jmp_buf emlrtJBEnviron;

/* Function Declarations */
MEXFUNCTION_LINKAGE void d_ROIMeans_FirstRead_CollectSki(int32_T nlhs, mxArray
  *plhs[3], int32_T nrhs, const mxArray *prhs[13]);

/* Function Definitions */
void d_ROIMeans_FirstRead_CollectSki(int32_T nlhs, mxArray *plhs[3], int32_T
  nrhs, const mxArray *prhs[13])
{
  const mxArray *outputs[3];
  int32_T b_nlhs;

  /* Check for proper number of arguments. */
  if (nrhs != 13) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 13, 4, 42,
                        "ROIMeans_FirstRead_CollectSkinColorSamples");
  }

  if (nlhs > 3) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 42,
                        "ROIMeans_FirstRead_CollectSkinColorSamples");
  }

  /* Call the function. */
  ROIMeans_FirstRead_CollectSkinColorSamples_api(prhs, nlhs, outputs);

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

  mexAtExit(&ROIMeans_FirstRead_CollectSkinColorSamples_atexit);
  emlrtLoadLibrary("C:\\ProgramData\\MATLAB\\SupportPackages\\R2020a\\3P.instrset\\mingw_w64.instrset\\bin\\libgomp-1.dll");

  /* Initialize the memory manager. */
  omp_init_lock(&emlrtLockGlobal);
  omp_init_nest_lock(&emlrtNestLockGlobal);

  /* Module initialization. */
  ROIMeans_FirstRead_CollectSkinColorSamples_initialize();
  st.tls = emlrtRootTLSGlobal;
  emlrtSetJmpBuf(&st, &emlrtJBEnviron);
  if (setjmp(emlrtJBEnviron) == 0) {
    /* Dispatch the entry-point. */
    d_ROIMeans_FirstRead_CollectSki(nlhs, plhs, nrhs, prhs);

    /* Module termination. */
    ROIMeans_FirstRead_CollectSkinColorSamples_terminate();
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

/* End of code generation (_coder_ROIMeans_FirstRead_CollectSkinColorSamples_mex.c) */
