/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * any.c
 *
 * Code generation for function 'any'
 *
 */

/* Include files */
#include "any.h"
#include "ROIMSIR_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
boolean_T any(const emxArray_boolean_T *x)
{
  int32_T ix;
  boolean_T exitg1;
  boolean_T y;
  y = false;
  ix = 1;
  exitg1 = false;
  while ((!exitg1) && (ix <= x->size[0])) {
    if (!x->data[ix - 1]) {
      ix++;
    } else {
      y = true;
      exitg1 = true;
    }
  }

  return y;
}

/* End of code generation (any.c) */
