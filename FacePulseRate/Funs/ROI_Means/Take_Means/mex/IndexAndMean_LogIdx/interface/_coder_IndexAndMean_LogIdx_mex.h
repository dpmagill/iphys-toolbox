/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_IndexAndMean_LogIdx_mex.h
 *
 * Code generation for function '_coder_IndexAndMean_LogIdx_mex'
 *
 */

#pragma once

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mex.h"
#include "emlrt.h"
#include "rtwtypes.h"
#include "omp.h"
#include "IndexAndMean_LogIdx_types.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void IndexAndMean_LogIdx_mexFunction(int32_T nlhs, mxArray
  *plhs[2], int32_T nrhs, const mxArray *prhs[9]);
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
  const mxArray *prhs[]);
emlrtCTX mexFunctionCreateRootTLS(void);

/* End of code generation (_coder_IndexAndMean_LogIdx_mex.h) */
