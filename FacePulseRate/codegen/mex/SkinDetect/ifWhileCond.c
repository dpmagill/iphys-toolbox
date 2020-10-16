/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ifWhileCond.c
 *
 * Code generation for function 'ifWhileCond'
 *
 */

/* Include files */
#include "ifWhileCond.h"
#include "rt_nonfinite.h"

/* Function Definitions */
boolean_T b_ifWhileCond(const boolean_T x_data[], const int32_T x_size[2])
{
  int32_T i;
  int32_T k;
  boolean_T exitg1;
  boolean_T y;
  y = ((x_size[0] != 0) && (x_size[1] != 0));
  if (y) {
    i = x_size[0] * x_size[1];
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= i - 1)) {
      if (!x_data[0]) {
        y = false;
        exitg1 = true;
      } else {
        k = 1;
      }
    }
  }

  return y;
}

boolean_T ifWhileCond(const boolean_T x_data[])
{
  boolean_T y;
  y = true;
  if (!x_data[0]) {
    y = false;
  }

  return y;
}

/* End of code generation (ifWhileCond.c) */
