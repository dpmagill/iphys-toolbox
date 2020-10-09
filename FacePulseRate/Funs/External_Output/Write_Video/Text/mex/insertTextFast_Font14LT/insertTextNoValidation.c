/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertTextNoValidation.c
 *
 * Code generation for function 'insertTextNoValidation'
 *
 */

/* Include files */
#include "insertTextNoValidation.h"
#include "insertTextFast_Font14LT.h"
#include "insertTextFast_Font14LT_data.h"
#include "insertTextFast_Font14LT_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void getTextboxWidthHeight(const emxArray_uint16_T *ucTextU16, int32_T *tbWidth,
  int32_T *tbHeight)
{
  emxArray_boolean_T *x;
  int32_T i;
  int32_T lenThisSegment;
  emxArray_int32_T *ii;
  int32_T nx;
  int32_T idx;
  boolean_T exitg1;
  emxArray_uint32_T *idxNewlineChar;
  emxArray_uint16_T *thisCharcodes_1b;
  emxArray_int8_T *b_x;
  int32_T nz;
  real_T lenFirstSegment;
  real_T y;
  int32_T b_i;
  uint32_T u;
  int32_T i1;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_boolean_T(&x, 2, true);
  i = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = ucTextU16->size[1];
  emxEnsureCapacity_boolean_T(x, i);
  lenThisSegment = ucTextU16->size[0] * ucTextU16->size[1];
  for (i = 0; i < lenThisSegment; i++) {
    x->data[i] = (ucTextU16->data[i] == 10);
  }

  emxInit_int32_T(&ii, 2, true);
  nx = x->size[1];
  idx = 0;
  i = ii->size[0] * ii->size[1];
  ii->size[0] = 1;
  ii->size[1] = x->size[1];
  emxEnsureCapacity_int32_T(ii, i);
  lenThisSegment = 0;
  exitg1 = false;
  while ((!exitg1) && (lenThisSegment <= nx - 1)) {
    if (x->data[lenThisSegment]) {
      idx++;
      ii->data[idx - 1] = lenThisSegment + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        lenThisSegment++;
      }
    } else {
      lenThisSegment++;
    }
  }

  if (x->size[1] == 1) {
    if (idx == 0) {
      ii->size[0] = 1;
      ii->size[1] = 0;
    }
  } else {
    i = ii->size[0] * ii->size[1];
    if (1 > idx) {
      ii->size[1] = 0;
    } else {
      ii->size[1] = idx;
    }

    emxEnsureCapacity_int32_T(ii, i);
  }

  emxInit_uint32_T(&idxNewlineChar, 2, true);
  i = idxNewlineChar->size[0] * idxNewlineChar->size[1];
  idxNewlineChar->size[0] = 1;
  idxNewlineChar->size[1] = ii->size[1];
  emxEnsureCapacity_uint32_T(idxNewlineChar, i);
  lenThisSegment = ii->size[0] * ii->size[1];
  for (i = 0; i < lenThisSegment; i++) {
    idxNewlineChar->data[i] = (uint32_T)ii->data[i];
  }

  emxFree_int32_T(&ii);
  *tbHeight = (idxNewlineChar->size[1] << 4) + 17;
  emxInit_uint16_T(&thisCharcodes_1b, 2, true);
  emxInit_int8_T(&b_x, 2, true);
  if (idxNewlineChar->size[1] == 0) {
    i = thisCharcodes_1b->size[0] * thisCharcodes_1b->size[1];
    thisCharcodes_1b->size[0] = 1;
    thisCharcodes_1b->size[1] = ucTextU16->size[1];
    emxEnsureCapacity_uint16_T(thisCharcodes_1b, i);
    lenThisSegment = ucTextU16->size[0] * ucTextU16->size[1];
    for (i = 0; i < lenThisSegment; i++) {
      thisCharcodes_1b->data[i] = (uint16_T)(ucTextU16->data[i] + 1U);
    }

    i = x->size[0] * x->size[1];
    x->size[0] = 1;
    x->size[1] = thisCharcodes_1b->size[1];
    emxEnsureCapacity_boolean_T(x, i);
    lenThisSegment = thisCharcodes_1b->size[0] * thisCharcodes_1b->size[1];
    for (i = 0; i < lenThisSegment; i++) {
      x->data[i] = (uv[thisCharcodes_1b->data[i] - 1] == 0);
    }

    nx = x->size[1];
    if (x->size[1] == 0) {
      nz = 0;
    } else {
      nz = x->data[0];
      for (lenThisSegment = 2; lenThisSegment <= nx; lenThisSegment++) {
        nz += x->data[lenThisSegment - 1];
      }
    }

    i = b_x->size[0] * b_x->size[1];
    b_x->size[0] = 1;
    b_x->size[1] = thisCharcodes_1b->size[1];
    emxEnsureCapacity_int8_T(b_x, i);
    lenThisSegment = thisCharcodes_1b->size[0] * thisCharcodes_1b->size[1];
    for (i = 0; i < lenThisSegment; i++) {
      b_x->data[i] = iv[uv[thisCharcodes_1b->data[i] - 1]];
    }

    nx = b_x->size[1];
    if (b_x->size[1] == 0) {
      y = 0.0;
    } else {
      y = b_x->data[0];
      for (lenThisSegment = 2; lenThisSegment <= nx; lenThisSegment++) {
        y += (real_T)b_x->data[lenThisSegment - 1];
      }
    }

    *tbWidth = (int32_T)y + (nz << 2);
  } else {
    lenThisSegment = (int32_T)idxNewlineChar->data[0] - 1;
    if (1 > lenThisSegment) {
      lenThisSegment = 0;
    }

    i = thisCharcodes_1b->size[0] * thisCharcodes_1b->size[1];
    thisCharcodes_1b->size[0] = 1;
    thisCharcodes_1b->size[1] = lenThisSegment;
    emxEnsureCapacity_uint16_T(thisCharcodes_1b, i);
    for (i = 0; i < lenThisSegment; i++) {
      thisCharcodes_1b->data[i] = (uint16_T)(ucTextU16->data[i] + 1U);
    }

    i = b_x->size[0] * b_x->size[1];
    b_x->size[0] = 1;
    b_x->size[1] = thisCharcodes_1b->size[1];
    emxEnsureCapacity_int8_T(b_x, i);
    lenThisSegment = thisCharcodes_1b->size[0] * thisCharcodes_1b->size[1];
    for (i = 0; i < lenThisSegment; i++) {
      b_x->data[i] = iv[uv[thisCharcodes_1b->data[i] - 1]];
    }

    nx = b_x->size[1];
    if (b_x->size[1] == 0) {
      lenFirstSegment = 0.0;
    } else {
      lenFirstSegment = b_x->data[0];
      for (lenThisSegment = 2; lenThisSegment <= nx; lenThisSegment++) {
        lenFirstSegment += (real_T)b_x->data[lenThisSegment - 1];
      }
    }

    i = x->size[0] * x->size[1];
    x->size[0] = 1;
    x->size[1] = thisCharcodes_1b->size[1];
    emxEnsureCapacity_boolean_T(x, i);
    lenThisSegment = thisCharcodes_1b->size[0] * thisCharcodes_1b->size[1];
    for (i = 0; i < lenThisSegment; i++) {
      x->data[i] = (uv[thisCharcodes_1b->data[i] - 1] == 0);
    }

    nx = x->size[1];
    if (x->size[1] == 0) {
      nz = 0;
    } else {
      nz = x->data[0];
      for (lenThisSegment = 2; lenThisSegment <= nx; lenThisSegment++) {
        nz += x->data[lenThisSegment - 1];
      }
    }

    *tbWidth = 0;
    i = idxNewlineChar->size[1];
    for (b_i = 0; b_i <= i - 3; b_i++) {
      u = idxNewlineChar->data[b_i + 1];
      i1 = (int32_T)idxNewlineChar->data[b_i + 2] - 1;
      if (u + 1U > (uint32_T)i1) {
        nx = 0;
        i1 = 0;
      } else {
        nx = (int32_T)u;
      }

      idx = thisCharcodes_1b->size[0] * thisCharcodes_1b->size[1];
      thisCharcodes_1b->size[0] = 1;
      lenThisSegment = i1 - nx;
      thisCharcodes_1b->size[1] = lenThisSegment;
      emxEnsureCapacity_uint16_T(thisCharcodes_1b, idx);
      for (i1 = 0; i1 < lenThisSegment; i1++) {
        thisCharcodes_1b->data[i1] = (uint16_T)(ucTextU16->data[nx + i1] + 1U);
      }

      i1 = x->size[0] * x->size[1];
      x->size[0] = 1;
      x->size[1] = thisCharcodes_1b->size[1];
      emxEnsureCapacity_boolean_T(x, i1);
      lenThisSegment = thisCharcodes_1b->size[0] * thisCharcodes_1b->size[1];
      for (i1 = 0; i1 < lenThisSegment; i1++) {
        x->data[i1] = (uv[thisCharcodes_1b->data[i1] - 1] == 0);
      }

      nx = x->size[1];
      if (x->size[1] == 0) {
        idx = 0;
      } else {
        idx = x->data[0];
        for (lenThisSegment = 2; lenThisSegment <= nx; lenThisSegment++) {
          idx += x->data[lenThisSegment - 1];
        }
      }

      i1 = b_x->size[0] * b_x->size[1];
      b_x->size[0] = 1;
      b_x->size[1] = thisCharcodes_1b->size[1];
      emxEnsureCapacity_int8_T(b_x, i1);
      lenThisSegment = thisCharcodes_1b->size[0] * thisCharcodes_1b->size[1];
      for (i1 = 0; i1 < lenThisSegment; i1++) {
        b_x->data[i1] = iv[uv[thisCharcodes_1b->data[i1] - 1]];
      }

      nx = b_x->size[1];
      if (b_x->size[1] == 0) {
        y = 0.0;
      } else {
        y = b_x->data[0];
        for (lenThisSegment = 2; lenThisSegment <= nx; lenThisSegment++) {
          y += (real_T)b_x->data[lenThisSegment - 1];
        }
      }

      lenThisSegment = (int32_T)(y + (real_T)(idx << 2));
      if (lenThisSegment > *tbWidth) {
        *tbWidth = lenThisSegment;
      }
    }

    if (idxNewlineChar->data[idxNewlineChar->size[1] - 1] + 1U > (uint32_T)
        ucTextU16->size[1]) {
      i = 0;
      i1 = 0;
    } else {
      i = (int32_T)idxNewlineChar->data[idxNewlineChar->size[1] - 1];
      i1 = ucTextU16->size[1];
    }

    nx = thisCharcodes_1b->size[0] * thisCharcodes_1b->size[1];
    thisCharcodes_1b->size[0] = 1;
    lenThisSegment = i1 - i;
    thisCharcodes_1b->size[1] = lenThisSegment;
    emxEnsureCapacity_uint16_T(thisCharcodes_1b, nx);
    for (i1 = 0; i1 < lenThisSegment; i1++) {
      thisCharcodes_1b->data[i1] = (uint16_T)(ucTextU16->data[i + i1] + 1U);
    }

    i = x->size[0] * x->size[1];
    x->size[0] = 1;
    x->size[1] = thisCharcodes_1b->size[1];
    emxEnsureCapacity_boolean_T(x, i);
    lenThisSegment = thisCharcodes_1b->size[0] * thisCharcodes_1b->size[1];
    for (i = 0; i < lenThisSegment; i++) {
      x->data[i] = (uv[thisCharcodes_1b->data[i] - 1] == 0);
    }

    nx = x->size[1];
    if (x->size[1] == 0) {
      idx = 0;
    } else {
      idx = x->data[0];
      for (lenThisSegment = 2; lenThisSegment <= nx; lenThisSegment++) {
        idx += x->data[lenThisSegment - 1];
      }
    }

    i = b_x->size[0] * b_x->size[1];
    b_x->size[0] = 1;
    b_x->size[1] = thisCharcodes_1b->size[1];
    emxEnsureCapacity_int8_T(b_x, i);
    lenThisSegment = thisCharcodes_1b->size[0] * thisCharcodes_1b->size[1];
    for (i = 0; i < lenThisSegment; i++) {
      b_x->data[i] = iv[uv[thisCharcodes_1b->data[i] - 1]];
    }

    nx = b_x->size[1];
    if (b_x->size[1] == 0) {
      y = 0.0;
    } else {
      y = b_x->data[0];
      for (lenThisSegment = 2; lenThisSegment <= nx; lenThisSegment++) {
        y += (real_T)b_x->data[lenThisSegment - 1];
      }
    }

    nx = *tbWidth;
    lenThisSegment = (int32_T)(y + (real_T)(idx << 2));
    *tbWidth = (int32_T)(lenFirstSegment + (real_T)(nz << 2));
    if (*tbWidth < nx) {
      *tbWidth = nx;
    }

    if (*tbWidth < lenThisSegment) {
      *tbWidth = lenThisSegment;
    }
  }

  emxFree_int8_T(&b_x);
  emxFree_boolean_T(&x);
  emxFree_uint16_T(&thisCharcodes_1b);
  emxFree_uint32_T(&idxNewlineChar);
  if (*tbWidth < 0) {
    *tbWidth = 0;
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (insertTextNoValidation.c) */
