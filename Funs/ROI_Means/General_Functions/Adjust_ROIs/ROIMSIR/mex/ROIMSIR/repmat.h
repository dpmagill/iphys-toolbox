/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * repmat.h
 *
 * Code generation for function 'repmat'
 *
 */

#pragma once

/* Include files */
#include "ROIMSIR_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void b_repmat(const int16_T a[4], int32_T varargin_1, int16_T b_data[], int32_T
              b_size[2]);
void repmat(const int16_T a[4], real_T varargin_1, emxArray_int16_T *b);

/* End of code generation (repmat.h) */
