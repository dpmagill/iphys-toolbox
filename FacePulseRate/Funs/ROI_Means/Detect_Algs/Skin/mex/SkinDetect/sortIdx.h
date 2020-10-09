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
#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void b_merge_block(int32_T idx_data[], real_T x_data[], int32_T offset, int32_T
                   n, int32_T preSortLevel, int32_T iwork_data[], real_T
                   xwork_data[]);
void c_merge_block(int32_T idx_data[], real32_T x_data[], int32_T offset,
                   int32_T n, int32_T preSortLevel, int32_T iwork_data[],
                   real32_T xwork_data[]);
void d_merge_block(int32_T idx_data[], uint16_T x_data[], int32_T offset,
                   int32_T n, int32_T preSortLevel, int32_T iwork_data[],
                   uint16_T xwork_data[]);
void merge_block(int32_T idx_data[], int16_T x_data[], int32_T offset, int32_T n,
                 int32_T preSortLevel, int32_T iwork_data[], int16_T xwork_data[]);

/* End of code generation (sortIdx.h) */
