/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * movmedian.c
 *
 * Code generation for function 'movmedian'
 *
 */

/* Include files */
#include "movmedian.h"
#include "ROIMSIR_data.h"
#include "ROIMSIR_emxutil.h"
#include "ROIMSIR_types.h"
#include "SortedBuffer.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Function Definitions */
void movmedian(const emxArray_int16_T *x, int32_T k, emxArray_int16_T *y)
{
  coder_internal_SortedBuffer s;
  real_T khalf;
  int32_T b_szy[2];
  int32_T b_k;
  int32_T b_tunableEnvironment_idx_0;
  int32_T i;
  int32_T iLeftLast;
  int32_T iRightLast;
  int32_T ipnf;
  int32_T j;
  int32_T k0;
  int32_T k1;
  int32_T kleft;
  int32_T kright;
  int32_T npages;
  int32_T nx;
  int32_T ny;
  int32_T p;
  int32_T stride;
  int32_T tunableEnvironment_idx_0;
  int32_T xpageoffset;
  int32_T xpagesize;
  int32_T ypageoffset;
  int32_T ypagesize;
  uint32_T szy[2];
  int16_T xnew;
  int16_T xold;
  boolean_T b_remove;
  boolean_T guard1 = false;
  boolean_T insert;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  ipnf = (x->size[0] == 1);
  k1 = x->size[ipnf];
  khalf = (real_T)k / 2.0;
  k0 = (int32_T)muDoubleScalarFloor(khalf);
  kright = k0;
  if (k0 == khalf) {
    kright = k0 - 1;
  }

  kleft = muIntScalarMin_sint32(k0, k1);
  kright = muIntScalarMin_sint32(kright, k1) + 1;
  ny = x->size[ipnf];
  nx = x->size[ipnf];
  szy[0] = (uint32_T)x->size[0];
  szy[1] = (uint32_T)x->size[1];
  szy[ipnf] = (uint32_T)x->size[ipnf];
  i = y->size[0] * y->size[1];
  y->size[0] = (int32_T)szy[0];
  y->size[1] = (int32_T)szy[1];
  emxEnsureCapacity_int16_T(y, i);
  k0 = (int32_T)szy[0] * (int32_T)szy[1];
  for (i = 0; i < k0; i++) {
    y->data[i] = 0;
  }

  npages = 1;
  i = ipnf + 2;
  for (b_k = i; b_k < 3; b_k++) {
    npages <<= 1;
  }

  stride = 1;
  for (b_k = 0; b_k < ipnf; b_k++) {
    stride *= x->size[0];
  }

  xpagesize = stride * x->size[ipnf];
  b_szy[0] = (int32_T)szy[0];
  b_szy[1] = (int32_T)szy[1];
  ypagesize = stride * b_szy[ipnf];
  c_emxInitStruct_coder_internal_(&s, true);
  for (p = 0; p < npages; p++) {
    xpageoffset = p * xpagesize;
    ypageoffset = p * ypagesize;
    for (j = 0; j < stride; j++) {
      tunableEnvironment_idx_0 = (xpageoffset + j) + 1;
      b_tunableEnvironment_idx_0 = (ypageoffset + j) + 1;
      if ((y->size[0] != 0) && (y->size[1] != 0)) {
        xold = 0;
        xnew = 0;
        ipnf = kleft + kright;
        i = s.buf->size[0];
        s.buf->size[0] = ipnf;
        emxEnsureCapacity_int16_T(s.buf, i);
        for (i = 0; i < ipnf; i++) {
          s.buf->data[i] = 0;
        }

        s.nbuf = 0;
        if (1 <= kleft) {
          iLeftLast = 1;
        } else {
          iLeftLast = 1 - kleft;
        }

        if (kright > nx) {
          iRightLast = nx;
        } else {
          iRightLast = kright;
        }

        for (b_k = iLeftLast; b_k <= iRightLast; b_k++) {
          SortedBuffer_insert(&s, x->data[(tunableEnvironment_idx_0 + (b_k - 1) *
            stride) - 1]);
        }

        y->data[b_tunableEnvironment_idx_0 - 1] = SortedBuffer_median(s.buf,
          s.nbuf);
        if (ipnf > nx) {
          for (b_k = 2; b_k <= ny; b_k++) {
            if (b_k <= kleft) {
              k1 = 1;
            } else {
              k1 = b_k - kleft;
            }

            ipnf = (b_k + kright) - 1;
            if (ipnf > ny) {
              k0 = ny;
            } else {
              k0 = ipnf;
            }

            if (k1 > iLeftLast) {
              xold = x->data[(tunableEnvironment_idx_0 + (iLeftLast - 1) *
                              stride) - 1];
              b_remove = true;
              iLeftLast = k1;
            } else {
              b_remove = false;
            }

            guard1 = false;
            if (k0 > iRightLast) {
              xnew = x->data[(tunableEnvironment_idx_0 + (k0 - 1) * stride) - 1];
              insert = true;
              iRightLast = k0;
              if (b_remove) {
                SortedBuffer_replace(&s, xold, xnew);
              } else {
                guard1 = true;
              }
            } else {
              insert = false;
              guard1 = true;
            }

            if (guard1) {
              if (insert) {
                SortedBuffer_insert(&s, xnew);
              } else {
                if (b_remove) {
                  if (s.nbuf == 1) {
                    if (xold == s.buf->data[0]) {
                      s.nbuf = 0;
                    }
                  } else {
                    k0 = SortedBuffer_locateElement(s.buf, s.nbuf, xold);
                    if ((k0 > 0) && (xold == s.buf->data[k0 - 1])) {
                      i = k0 + 1;
                      k1 = s.nbuf;
                      for (k0 = i; k0 <= k1; k0++) {
                        s.buf->data[k0 - 2] = s.buf->data[k0 - 1];
                      }

                      s.nbuf--;
                    }
                  }
                }
              }
            }

            y->data[(b_tunableEnvironment_idx_0 + (b_k - 1) * stride) - 1] =
              SortedBuffer_median(s.buf, s.nbuf);
          }
        } else {
          k0 = kleft + 2;
          k1 = (nx - kright) + 1;
          i = kleft + 1;
          for (b_k = 2; b_k <= i; b_k++) {
            SortedBuffer_insert(&s, x->data[(tunableEnvironment_idx_0 + ((b_k +
              kright) - 2) * stride) - 1]);
            y->data[(b_tunableEnvironment_idx_0 + (b_k - 1) * stride) - 1] =
              SortedBuffer_median(s.buf, s.nbuf);
          }

          for (b_k = k0; b_k <= k1; b_k++) {
            SortedBuffer_replace(&s, x->data[(tunableEnvironment_idx_0 + ((b_k -
              kleft) - 2) * stride) - 1], x->data[(tunableEnvironment_idx_0 +
              ((b_k + kright) - 2) * stride) - 1]);
            y->data[(b_tunableEnvironment_idx_0 + (b_k - 1) * stride) - 1] =
              SortedBuffer_median(s.buf, s.nbuf);
          }

          i = k1 + 1;
          for (b_k = i; b_k <= ny; b_k++) {
            k1 = (tunableEnvironment_idx_0 + ((b_k - kleft) - 2) * stride) - 1;
            if (s.nbuf == 1) {
              if (x->data[k1] == s.buf->data[0]) {
                s.nbuf = 0;
              }
            } else {
              k0 = SortedBuffer_locateElement(s.buf, s.nbuf, x->data[k1]);
              if ((k0 > 0) && (x->data[k1] == s.buf->data[k0 - 1])) {
                k1 = k0 + 1;
                ipnf = s.nbuf;
                for (k0 = k1; k0 <= ipnf; k0++) {
                  s.buf->data[k0 - 2] = s.buf->data[k0 - 1];
                }

                s.nbuf--;
              }
            }

            y->data[(b_tunableEnvironment_idx_0 + (b_k - 1) * stride) - 1] =
              SortedBuffer_median(s.buf, s.nbuf);
          }
        }
      }
    }
  }

  c_emxFreeStruct_coder_internal_(&s);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (movmedian.c) */
