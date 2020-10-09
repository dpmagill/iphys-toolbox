/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * colon.c
 *
 * Code generation for function 'colon'
 *
 */

/* Include files */
#include "colon.h"
#include "ROIMSIR_emxutil.h"
#include "ROIMSIR_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Function Definitions */
void eml_float_colon(real32_T a, real32_T b, emxArray_real32_T *y)
{
  real_T apnd;
  real_T cdiff;
  real_T ndbl;
  int32_T k;
  int32_T n;
  int32_T nm1d2;
  real32_T b1;
  ndbl = muDoubleScalarFloor(((real_T)b - a) / 0.05 + 0.5);
  apnd = a + ndbl * 0.05;
  cdiff = apnd - b;
  if (muDoubleScalarAbs(cdiff) < 2.384185791015625E-7 * muDoubleScalarMax
      (muDoubleScalarAbs(a), muDoubleScalarAbs(b))) {
    ndbl++;
    b1 = b;
  } else if (cdiff > 0.0) {
    b1 = (real32_T)(a + (ndbl - 1.0) * 0.05);
  } else {
    ndbl++;
    b1 = (real32_T)apnd;
  }

  if (ndbl >= 0.0) {
    n = (int32_T)ndbl;
  } else {
    n = 0;
  }

  nm1d2 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity_real32_T(y, nm1d2);
  if (n > 0) {
    y->data[0] = a;
    if (n > 1) {
      y->data[n - 1] = b1;
      nm1d2 = (n - 1) / 2;
      for (k = 0; k <= nm1d2 - 2; k++) {
        ndbl = ((real_T)k + 1.0) * 0.05;
        y->data[k + 1] = a + (real32_T)ndbl;
        y->data[(n - k) - 2] = b1 - (real32_T)ndbl;
      }

      if (nm1d2 << 1 == n - 1) {
        y->data[nm1d2] = (a + b1) / 2.0F;
      } else {
        ndbl = (real_T)nm1d2 * 0.05;
        y->data[nm1d2] = a + (real32_T)ndbl;
        y->data[nm1d2 + 1] = b1 - (real32_T)ndbl;
      }
    }
  }
}

void eml_integer_colon_dispatcher(int32_T a, int32_T b, emxArray_int32_T *y)
{
  int32_T k;
  int32_T n;
  int32_T yk;
  uint32_T nm1;
  if (b < a) {
    n = 0;
  } else {
    if ((a < 0) && (b >= 0)) {
      nm1 = (uint32_T)b - a;
    } else {
      nm1 = (uint32_T)(b - a);
    }

    n = (int32_T)nm1 + 1;
  }

  yk = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity_int32_T(y, yk);
  if (n > 0) {
    y->data[0] = a;
    yk = a;
    for (k = 2; k <= n; k++) {
      yk++;
      y->data[k - 1] = yk;
    }
  }
}

void eml_signed_integer_colon(int32_T b, emxArray_int32_T *y)
{
  int32_T k;
  int32_T n;
  int32_T yk;
  if (b < 1) {
    n = 0;
  } else {
    n = b;
  }

  yk = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity_int32_T(y, yk);
  if (n > 0) {
    y->data[0] = 1;
    yk = 1;
    for (k = 2; k <= n; k++) {
      yk++;
      y->data[k - 1] = yk;
    }
  }
}

/* End of code generation (colon.c) */
