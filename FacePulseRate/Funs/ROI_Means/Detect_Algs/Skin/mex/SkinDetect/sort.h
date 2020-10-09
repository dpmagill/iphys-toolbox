/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sort.h
 *
 * Code generation for function 'sort'
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
void b_sort(real_T x_data[], const int32_T x_size[1], int32_T idx_data[],
            int32_T idx_size[1]);
void c_sort(real32_T x_data[], const int32_T x_size[1], int32_T idx_data[],
            int32_T idx_size[1]);
void d_sort(uint16_T x_data[], const int32_T x_size[1], int32_T idx_data[],
            int32_T idx_size[1]);
void sort(int16_T x_data[], const int32_T x_size[1], int32_T idx_data[], int32_T
          idx_size[1]);

/* End of code generation (sort.h) */
