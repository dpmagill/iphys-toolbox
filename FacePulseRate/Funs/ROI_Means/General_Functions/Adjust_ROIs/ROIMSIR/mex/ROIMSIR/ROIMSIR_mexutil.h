/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIMSIR_mexutil.h
 *
 * Code generation for function 'ROIMSIR_mexutil'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
real_T b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *parentId);
real_T bb_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *msgId);
const mxArray *d_emlrt_marshallOut(const int32_T u);
real_T emlrt_marshallIn(const mxArray *a__output_of_length_, const char_T
  *identifier);

/* End of code generation (ROIMSIR_mexutil.h) */
