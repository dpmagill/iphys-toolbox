/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * abs.c
 *
 * Code generation for function 'abs'
 *
 */

/* Include files */
#include "abs.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Function Definitions */
void b_abs(const real32_T x_data[], const int32_T x_size[1], real32_T y_data[],
           int32_T y_size[1])
{
  int32_T k;
  int32_T nx;
  nx = x_size[0];
  y_size[0] = x_size[0];
  for (k = 0; k < nx; k++) {
    y_data[k] = muSingleScalarAbs(x_data[k]);
  }
}

/* End of code generation (abs.c) */
