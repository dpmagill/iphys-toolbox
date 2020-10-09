/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sortIdx.h
 *
 * Code generation for function 'sortIdx'
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
void merge(int32_T idx_data[], int16_T x_data[], int32_T offset, int32_T np,
           int32_T nq, int32_T iwork_data[], int16_T xwork_data[]);

/* End of code generation (sortIdx.h) */
