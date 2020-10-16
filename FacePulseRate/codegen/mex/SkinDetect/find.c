/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * find.c
 *
 * Code generation for function 'find'
 *
 */

/* Include files */
#include "find.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void eml_find(const boolean_T x_data[], const int32_T x_size[1], int32_T i_data[],
              int32_T i_size[1])
{
  int32_T idx;
  int32_T ii;
  int32_T nx;
  boolean_T exitg1;
  nx = x_size[0];
  idx = 0;
  i_size[0] = x_size[0];
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= nx - 1)) {
    if (x_data[ii]) {
      idx++;
      i_data[idx - 1] = ii + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }

  if (x_size[0] == 1) {
    if (idx == 0) {
      i_size[0] = 0;
    }
  } else if (1 > idx) {
    i_size[0] = 0;
  } else {
    i_size[0] = idx;
  }
}

/* End of code generation (find.c) */
