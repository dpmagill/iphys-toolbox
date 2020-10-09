/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * allOrAny.c
 *
 * Code generation for function 'allOrAny'
 *
 */

/* Include files */
#include "allOrAny.h"
#include "rt_nonfinite.h"

/* Function Definitions */
boolean_T vectorAny(const boolean_T x_data[], const int32_T x_size[1])
{
  int32_T k;
  boolean_T exitg1;
  boolean_T y;
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= x_size[0] - 1)) {
    if (!x_data[k]) {
      k++;
    } else {
      y = true;
      exitg1 = true;
    }
  }

  return y;
}

/* End of code generation (allOrAny.c) */
