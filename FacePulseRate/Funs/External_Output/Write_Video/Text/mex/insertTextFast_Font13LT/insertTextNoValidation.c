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
#include "insertTextFast_Font13LT.h"
#include "insertTextFast_Font13LT_data.h"
#include "insertTextFast_Font13LT_emxutil.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Variable Definitions */
static const uint16_T uv[256] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
  3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U, 11U, 12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U,
  20U, 21U, 22U, 23U, 24U, 25U, 26U, 27U, 28U, 29U, 30U, 31U, 32U, 33U, 34U, 35U,
  36U, 37U, 38U, 39U, 40U, 41U, 42U, 43U, 44U, 45U, 46U, 47U, 48U, 49U, 50U, 51U,
  52U, 53U, 54U, 55U, 56U, 57U, 58U, 59U, 60U, 61U, 62U, 63U, 64U, 65U, 66U, 67U,
  68U, 69U, 70U, 71U, 72U, 73U, 74U, 75U, 76U, 77U, 78U, 79U, 80U, 81U, 82U, 83U,
  84U, 85U, 86U, 87U, 88U, 89U, 90U, 91U, 92U, 93U, 94U, 95U, 96U, 97U, 0U, 0U,
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 172U, 163U, 132U, 133U, 189U, 150U,
  232U, 134U, 142U, 139U, 157U, 169U, 164U, 258U, 138U, 259U, 131U, 147U, 242U,
  243U, 141U, 151U, 136U, 260U, 222U, 241U, 158U, 170U, 245U, 244U, 246U, 162U,
  173U, 201U, 199U, 174U, 98U, 99U, 144U, 100U, 203U, 101U, 200U, 202U, 207U,
  204U, 205U, 206U, 233U, 102U, 211U, 208U, 209U, 175U, 103U, 240U, 145U, 214U,
  212U, 213U, 104U, 235U, 237U, 137U, 106U, 105U, 107U, 109U, 108U, 110U, 160U,
  111U, 113U, 112U, 114U, 115U, 117U, 116U, 118U, 119U, 234U, 120U, 122U, 121U,
  123U, 125U, 124U, 184U, 161U, 127U, 126U, 128U, 129U, 236U, 238U, 186U };

static const int8_T iv[261] = { 10, 0, 0, 4, 4, 5, 8, 8, 9, 9, 3, 4, 4, 6, 10, 4,
  8, 4, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 10, 10, 10, 5, 11, 9, 7, 9, 10, 7,
  7, 9, 10, 4, 4, 8, 7, 11, 10, 10, 7, 10, 8, 7, 8, 9, 9, 11, 8, 8, 8, 4, 7, 4,
  8, 7, 8, 7, 8, 7, 8, 7, 5, 8, 8, 4, 4, 8, 4, 12, 8, 8, 8, 8, 5, 7, 5, 8, 7, 10,
  8, 7, 7, 4, 5, 4, 8, 9, 9, 9, 7, 10, 10, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4,
  4, 4, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 6, 8, 8, 8, 0, 8, 8, 8, 11, 0, 8, 8,
  0, 12, 10, 0, 10, 0, 0, 8, 8, 0, 0, 0, 0, 0, 6, 6, 0, 11, 8, 5, 4, 10, 0, 0, 0,
  0, 7, 7, 0, 4, 9, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 7, 0, 0, 8, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 9, 7, 9, 7, 7, 4, 4, 4, 4, 10, 10, 0, 10, 9, 9, 9, 0, 0, 0, 0,
  0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 10, 8, 8, 7, 7, 8, 0, 10, 5, 5, 5,
  10, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 7, 4 };

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
  *tbHeight = 15 * idxNewlineChar->size[1] + 16;
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

void insertGlyphs(emxArray_uint8_T *imgIn, const emxArray_uint16_T *ucTextU16,
                  int32_T textLocationXY_x, int32_T textLocationXY_y, const
                  uint8_T textColor_data[])
{
  emxArray_boolean_T *isNewLineChar;
  int32_T imSize_idx_0;
  int32_T imSize_idx_1;
  int32_T penX;
  int32_T penY;
  int32_T i;
  int32_T bitmapEndIdx_1b;
  int32_T b_i;
  uint16_T thisGlyphIdx;
  int32_T xx;
  static const int8_T b_iv[261] = { 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1,
    1, 0, 1, 1, -2, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0,
    0, 2, 0, 1, 0, 0, 0, 0, 0, 1, 1, -1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    -1, -1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 2,
    2, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, -1, 0, -1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

  int32_T yy;
  static const int8_T iv1[261] = { 9, 0, 0, 0, 10, 10, 10, 11, 10, 10, 10, 10,
    10, 9, 7, 2, 4, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 7, 5, 7,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0, 10, 7, 10, 7, 10, 7,
    10, 7, 10, 10, 10, 10, 10, 7, 7, 7, 7, 7, 7, 7, 8, 7, 7, 7, 7, 7, 7, 10, 10,
    10, 5, 12, 13, 10, 13, 13, 12, 12, 10, 10, 10, 9, 10, 11, 7, 10, 10, 10, 9,
    10, 10, 10, 9, 10, 10, 10, 10, 9, 10, 10, 10, 10, 9, 0, 10, 10, 10, 10, 0,
    10, 10, 10, 10, 0, 10, 9, 0, 10, 10, 0, 7, 0, 0, 10, 7, 0, 0, 0, 0, 0, 10,
    10, 0, 7, 7, 7, 7, 6, 0, 0, 0, 0, 6, 6, 0, 0, 13, 13, 13, 0, 0, 0, 0, 0, 0,
    0, 0, 7, 0, 9, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 13, 13, 12, 13, 13,
    13, 12, 13, 13, 13, 0, 13, 13, 13, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 10, 10, 11, 13, 10, 10, 10, 0, 8, 10, 10, 10, 10, 10, 10, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 10, 5 };

  int32_T endR_im;
  static const int8_T iv2[261] = { 9, 0, 0, 0, 10, 3, 10, 12, 10, 10, 3, 12, 12,
    4, 7, 4, 1, 2, 12, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7, 9, 7, 3, 7, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 12, 10, 10, 10, 10, 10, 10, 12, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 12, 12, 12, 7, 1, 2, 7, 10, 7, 10, 7, 10, 10,
    10, 10, 13, 10, 10, 7, 7, 7, 10, 10, 7, 7, 8, 7, 7, 7, 7, 10, 7, 12, 12, 12,
    2, 12, 13, 13, 13, 13, 12, 12, 10, 10, 10, 9, 10, 11, 10, 10, 10, 10, 9, 10,
    10, 10, 9, 10, 10, 10, 10, 9, 10, 10, 10, 10, 9, 0, 4, 10, 10, 12, 0, 12, 10,
    6, 10, 0, 2, 1, 0, 10, 10, 0, 7, 0, 0, 10, 10, 0, 0, 0, 0, 0, 5, 5, 0, 7, 7,
    10, 10, 4, 0, 0, 0, 0, 5, 5, 0, 0, 13, 13, 13, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0,
    12, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 13, 13, 12, 13, 13, 13, 12, 13,
    13, 13, 0, 13, 13, 13, 13, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    12, 10, 11, 13, 13, 10, 13, 0, 8, 6, 6, 6, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 2 };

  static const int8_T iv3[261] = { 8, 0, 0, 0, 2, 5, 9, 6, 9, 9, 3, 4, 4, 6, 8,
    2, 7, 2, 5, 8, 6, 6, 6, 8, 6, 8, 7, 7, 8, 2, 2, 8, 8, 8, 6, 11, 9, 6, 9, 9,
    6, 6, 9, 8, 2, 5, 8, 6, 9, 8, 10, 6, 11, 8, 7, 9, 7, 9, 12, 8, 8, 8, 3, 5, 3,
    8, 6, 4, 7, 7, 7, 7, 7, 6, 7, 6, 2, 4, 7, 2, 10, 6, 8, 7, 7, 5, 5, 5, 6, 7,
    10, 8, 7, 7, 4, 2, 5, 8, 9, 9, 9, 6, 8, 10, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 4, 4, 6, 4, 6, 8, 8, 8, 8, 8, 6, 6, 6, 6, 0, 5, 6, 6, 6, 0, 6, 7, 6, 11,
    0, 4, 4, 0, 12, 10, 0, 8, 0, 0, 8, 6, 0, 0, 0, 0, 0, 5, 6, 0, 11, 8, 6, 2, 8,
    0, 0, 0, 0, 7, 7, 0, 0, 9, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 7, 0, 0, 8,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 6, 9, 6, 6, 4, 6, 4, 4, 10, 10, 0, 10, 7, 7, 7,
    0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 11, 8, 8, 7, 6, 7, 0,
    8, 4, 5, 4, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 6, 2 };

  int32_T endC_im;
  int32_T glIdx_startR_gl;
  int32_T glIdx_startC_gl;
  int32_T glIdx_endR_gl;
  int32_T glIdx_endC_gl;
  static const int16_T iv4[261] = { 0, 0, 0, 72, 72, 92, 107, 197, 269, 359, 449,
    458, 506, 554, 578, 634, 642, 649, 653, 713, 793, 853, 913, 973, 1053, 1113,
    1193, 1263, 1333, 1413, 1427, 1445, 1501, 1525, 1581, 1641, 1751, 1841, 1901,
    1991, 2081, 2141, 2201, 2291, 2371, 2391, 2451, 2531, 2591, 2681, 2761, 2861,
    2921, 3053, 3133, 3203, 3293, 3363, 3453, 3573, 3653, 3733, 3813, 3849, 3909,
    3945, 4001, 4007, 4015, 4064, 4134, 4183, 4253, 4302, 4362, 4432, 4492, 4512,
    4564, 4634, 4654, 4724, 4766, 4822, 4892, 4962, 4997, 5032, 5072, 5114, 5163,
    5233, 5289, 5359, 5408, 5456, 5480, 5540, 7391, 7499, 7736, 7931, 8499, 9123,
    9680, 10068, 9998, 10138, 10278, 10208, 10341, 10495, 10635, 10565, 10705,
    10775, 10878, 10838, 10918, 10978, 11102, 11242, 11162, 11322, 11482, 11402,
    11726, 11666, 11786, 11846, 0, 6191, 5576, 5636, 5864, 0, 6389, 9928, 6149,
    5940, 0, 6321, 5936, 0, 7616, 9307, 0, 6211, 0, 0, 5760, 6329, 0, 0, 0, 0, 0,
    6050, 6498, 0, 10418, 11610, 6863, 5556, 6110, 0, 0, 0, 0, 6075, 6528, 0,
    5556, 6923, 7274, 8993, 0, 0, 0, 0, 0, 0, 0, 0, 11554, 0, 12082, 0, 0, 5696,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 7157, 8009, 7040, 8087, 7853, 8211, 8263, 8341,
    8159, 8733, 8863, 0, 8603, 9498, 9589, 9407, 0, 0, 0, 0, 0, 0, 0, 6465, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 5840, 8389, 11014, 9764, 11900, 9868, 11991, 0, 9243,
    6474, 6267, 6297, 6663, 6563, 6763, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6142,
    6185, 6461 };

  int32_T i1;
  int32_T i2;
  int32_T num_tmp;
  uint8_T thisGlyphBitmap_data[12166];
  static const uint8_T b_uv[12166] = { 12U, 32U, 32U, 32U, 32U, 32U, 32U, 4U,
    96U, 77U, 72U, 72U, 72U, 72U, 123U, 32U, 96U, 8U, 0U, 0U, 0U, 0U, 72U, 32U,
    96U, 8U, 0U, 0U, 0U, 0U, 72U, 32U, 96U, 8U, 0U, 0U, 0U, 0U, 72U, 32U, 96U,
    8U, 0U, 0U, 0U, 0U, 72U, 32U, 96U, 8U, 0U, 0U, 0U, 0U, 72U, 32U, 96U, 8U, 0U,
    0U, 0U, 0U, 72U, 32U, 96U, 108U, 104U, 104U, 104U, 104U, 146U, 32U, 148U,
    172U, 148U, 171U, 144U, 167U, 136U, 159U, 128U, 151U, 120U, 143U, 112U, 135U,
    0U, 0U, 148U, 172U, 148U, 172U, 70U, 236U, 22U, MAX_uint8_T, 32U, 56U, 223U,
    8U, MAX_uint8_T, 19U, 43U, 210U, 0U, 250U, 6U, 0U, 0U, 0U, 123U, 85U, 6U,
    200U, 0U, 0U, 0U, 0U, 0U, 182U, 25U, 59U, 149U, 0U, 0U, 0U, 0U, 2U, 205U, 0U,
    118U, 89U, 0U, 0U, 60U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 12U, 0U, 0U, 101U, 104U, 1U, 206U, 0U,
    0U, 0U, 0U, 0U, 172U, 34U, 49U, 158U, 0U, 0U, 0U, 212U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 115U, 0U,
    0U, 30U, 173U, 0U, 167U, 41U, 0U, 0U, 0U, 0U, 92U, 113U, 0U, 206U, 1U, 0U,
    0U, 0U, 0U, 153U, 53U, 29U, 177U, 0U, 0U, 0U, 0U, 0U, 0U, 32U, 128U, 0U, 0U,
    0U, 105U, 231U, 247U, 173U, 25U, 41U, 243U, 93U, 138U, 98U, 113U, 82U, 208U,
    32U, 128U, 0U, 0U, 30U, 247U, 104U, 128U, 0U, 0U, 0U, 87U, 247U, 175U, 7U,
    0U, 0U, 0U, 61U, 249U, 206U, 20U, 0U, 0U, 32U, 134U, 193U, 144U, 0U, 0U, 32U,
    128U, 116U, 166U, 131U, 98U, 53U, 154U, 208U, 97U, 28U, 159U, 235U, 243U,
    132U, 1U, 0U, 0U, 32U, 128U, 0U, 0U, 55U, 220U, 232U, 77U, 0U, 0U, 6U, 196U,
    48U, 193U, 84U, 50U, 224U, 0U, 0U, 144U, 107U, 0U, 228U, 11U, 0U, 231U, 7U,
    77U, 173U, 0U, 0U, 192U, 83U, 45U, 223U, 28U, 205U, 17U, 0U, 0U, 55U, 222U,
    231U, 81U, 190U, 57U, 0U, 0U, 0U, 0U, 0U, 0U, 133U, 118U, 146U, 241U, 184U,
    12U, 0U, 0U, 68U, 182U, 54U, 210U, 18U, 162U, 111U, 0U, 23U, 206U, 22U, 88U,
    151U, 0U, 91U, 147U, 1U, 183U, 66U, 0U, 52U, 209U, 17U, 155U, 110U, 121U,
    130U, 0U, 0U, 0U, 147U, 242U, 184U, 12U, 0U, 0U, 42U, 201U, 244U, 172U, 8U,
    0U, 0U, 0U, 0U, 190U, 144U, 13U, 208U, 101U, 0U, 0U, 0U, 0U, 203U, 126U, 0U,
    204U, 99U, 0U, 0U, 0U, 0U, 122U, 222U, 161U, 197U, 8U, 0U, 0U, 0U, 66U, 209U,
    246U, 180U, 6U, 0U, 0U, 0U, 38U, 244U, 59U, 102U, 240U, 23U, 0U, 204U, 105U,
    118U, 195U, 0U, 2U, 200U, 175U, 0U, 231U, 63U, 111U, 228U, 5U, 0U, 40U, 245U,
    166U, 220U, 3U, 30U, 240U, 163U, 26U, 11U, 153U, MAX_uint8_T, 105U, 0U, 0U,
    52U, 189U, 241U, 237U, 183U, 185U, 235U, 37U, 63U, MAX_uint8_T, 54U, 36U,
    MAX_uint8_T, 27U, 9U, 253U, 3U, 0U, 0U, 13U, 128U, 0U, 0U, 184U, 96U, 0U,
    90U, 188U, 0U, 0U, 195U, 88U, 0U, 12U, 254U, 35U, 0U, 42U, MAX_uint8_T, 15U,
    0U, 42U, MAX_uint8_T, 15U, 0U, 12U, 254U, 35U, 0U, 0U, 195U, 87U, 0U, 0U,
    92U, 187U, 0U, 0U, 0U, 185U, 96U, 0U, 0U, 14U, 129U, 103U, 38U, 0U, 0U, 47U,
    218U, 14U, 0U, 0U, 131U, 146U, 0U, 0U, 31U, 242U, 9U, 0U, 0U, 233U, 70U, 0U,
    0U, 212U, 100U, 0U, 0U, 212U, 100U, 0U, 0U, 233U, 70U, 0U, 31U, 242U, 10U,
    0U, 130U, 148U, 0U, 46U, 218U, 15U, 0U, 103U, 38U, 0U, 0U, 0U, 0U, 70U, 140U,
    0U, 0U, 37U, 221U, 143U, 137U, 201U, 104U, 0U, 5U, 148U, 129U, 30U, 0U, 0U,
    90U, 106U, 42U, 154U, 0U, 0U, 0U, 0U, 76U, 164U, 0U, 0U, 0U, 0U, 0U, 0U, 76U,
    164U, 0U, 0U, 0U, 0U, 0U, 0U, 76U, 164U, 0U, 0U, 0U, 152U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 236U, 0U,
    0U, 0U, 76U, 164U, 0U, 0U, 0U, 0U, 0U, 0U, 76U, 164U, 0U, 0U, 0U, 0U, 0U, 0U,
    76U, 164U, 0U, 0U, 0U, 188U, 216U, 188U, 212U, 72U, 182U, 165U, 63U, 16U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 148U, 188U,
    216U, 188U, 216U, 0U, 0U, 0U, 137U, 115U, 0U, 0U, 0U, 209U, 43U, 0U, 0U, 26U,
    225U, 0U, 0U, 0U, 98U, 154U, 0U, 0U, 0U, 170U, 82U, 0U, 0U, 3U, 233U, 14U,
    0U, 0U, 59U, 193U, 0U, 0U, 0U, 131U, 121U, 0U, 0U, 0U, 203U, 48U, 0U, 0U,
    21U, 229U, 1U, 0U, 0U, 92U, 160U, 0U, 0U, 0U, 164U, 88U, 0U, 0U, 0U, 0U, 0U,
    107U, 230U, 242U, 149U, 6U, 0U, 0U, 75U, 236U, 53U, 30U, 201U, 134U, 0U, 0U,
    191U, 126U, 0U, 0U, 68U, 239U, 11U, 4U, 253U, 68U, 0U, 0U, 8U, MAX_uint8_T,
    61U, 30U, MAX_uint8_T, 48U, 0U, 0U, 0U, 244U, 90U, 30U, MAX_uint8_T, 48U, 0U,
    0U, 0U, 246U, 89U, 4U, 253U, 68U, 0U, 0U, 10U, MAX_uint8_T, 60U, 0U, 191U,
    126U, 0U, 0U, 70U, 240U, 11U, 0U, 76U, 235U, 52U, 30U, 204U, 136U, 0U, 0U,
    0U, 110U, 232U, 242U, 149U, 6U, 0U, 0U, 44U, 125U, 207U, 23U, 0U, 11U, 214U,
    172U, MAX_uint8_T, 24U, 0U, 0U, 0U, 44U, MAX_uint8_T, 24U, 0U, 0U, 0U, 44U,
    MAX_uint8_T, 24U, 0U, 0U, 0U, 44U, MAX_uint8_T, 24U, 0U, 0U, 0U, 44U,
    MAX_uint8_T, 24U, 0U, 0U, 0U, 44U, MAX_uint8_T, 24U, 0U, 0U, 0U, 44U,
    MAX_uint8_T, 24U, 0U, 0U, 0U, 44U, MAX_uint8_T, 24U, 0U, 12U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 248U, 36U, 172U, 238U, 227U, 128U, 1U,
    139U, 82U, 14U, 62U, 243U, 102U, 0U, 0U, 0U, 0U, 169U, 170U, 0U, 0U, 0U, 0U,
    193U, 153U, 0U, 0U, 0U, 65U, 247U, 46U, 0U, 0U, 50U, 233U, 82U, 0U, 0U, 52U,
    232U, 74U, 0U, 0U, 26U, 232U, 88U, 0U, 0U, 0U, 170U, 197U, 0U, 0U, 0U, 0U,
    236U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 172U, 25U, 171U,
    242U, 230U, 145U, 3U, 113U, 82U, 12U, 55U, 243U, 91U, 0U, 0U, 0U, 0U, 212U,
    104U, 0U, 1U, 22U, 115U, 210U, 15U, 0U, 208U, MAX_uint8_T, 232U, 63U, 0U, 0U,
    1U, 22U, 107U, 249U, 79U, 0U, 0U, 0U, 0U, 169U, 184U, 0U, 0U, 0U, 0U, 162U,
    181U, 135U, 78U, 13U, 78U, 247U, 99U, 36U, 176U, 243U, 218U, 113U, 0U, 0U,
    0U, 0U, 0U, 118U, MAX_uint8_T, 16U, 0U, 0U, 0U, 0U, 47U, 246U, MAX_uint8_T,
    16U, 0U, 0U, 0U, 8U, 212U, 128U, MAX_uint8_T, 16U, 0U, 0U, 0U, 145U, 188U,
    6U, MAX_uint8_T, 16U, 0U, 0U, 69U, 231U, 24U, 4U, MAX_uint8_T, 16U, 0U, 18U,
    226U, 68U, 0U, 4U, MAX_uint8_T, 16U, 0U, 83U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 84U, 0U, 0U, 0U, 0U, 28U,
    MAX_uint8_T, 16U, 0U, 0U, 0U, 0U, 0U, 28U, MAX_uint8_T, 16U, 0U, 0U, 0U, 0U,
    0U, 28U, MAX_uint8_T, 16U, 0U, 68U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, 128U, 68U, 216U, 0U, 0U, 0U, 0U, 68U, 216U, 0U, 0U, 0U, 0U, 68U,
    216U, 0U, 0U, 0U, 0U, 68U, MAX_uint8_T, 233U, 185U, 60U, 0U, 0U, 4U, 31U,
    132U, 251U, 58U, 0U, 0U, 0U, 0U, 198U, 152U, 0U, 0U, 0U, 0U, 188U, 152U, 89U,
    79U, 12U, 88U, 252U, 70U, 20U, 184U, 243U, 206U, 88U, 0U, 0U, 0U, 65U, 202U,
    249U, MAX_uint8_T, 208U, 0U, 0U, 51U, 245U, 94U, 6U, 0U, 0U, 0U, 0U, 177U,
    162U, 0U, 0U, 0U, 0U, 0U, 2U, 244U, 93U, 0U, 0U, 0U, 0U, 0U, 22U,
    MAX_uint8_T, 118U, 204U, 246U, 200U, 52U, 0U, 23U, MAX_uint8_T, 205U, 42U,
    15U, 152U, 231U, 10U, 2U, 250U, 86U, 0U, 0U, 15U, MAX_uint8_T, 56U, 0U, 199U,
    111U, 0U, 0U, 11U, 254U, 40U, 0U, 86U, 228U, 53U, 13U, 143U, 198U, 1U, 0U,
    0U, 117U, 231U, 239U, 171U, 24U, 0U, 152U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 112U, 0U, 0U, 0U, 0U, 22U, 237U, 41U,
    0U, 0U, 0U, 0U, 154U, 143U, 0U, 0U, 0U, 0U, 46U, 231U, 15U, 0U, 0U, 0U, 0U,
    188U, 115U, 0U, 0U, 0U, 0U, 77U, 233U, 10U, 0U, 0U, 0U, 3U, 213U, 125U, 0U,
    0U, 0U, 0U, 86U, 252U, 28U, 0U, 0U, 0U, 0U, 181U, 191U, 0U, 0U, 0U, 0U, 1U,
    241U, 130U, 0U, 0U, 0U, 0U, 0U, 88U, 216U, 246U, 204U, 58U, 0U, 41U, 237U,
    52U, 10U, 126U, 228U, 0U, 89U, 212U, 0U, 0U, 42U, 241U, 1U, 25U, 240U, 139U,
    9U, 166U, 117U, 0U, 0U, 86U, MAX_uint8_T, 243U, 165U, 0U, 0U, 41U, 227U, 82U,
    152U, 254U, 142U, 0U, 176U, 129U, 0U, 0U, 80U, MAX_uint8_T, 56U, 212U, 111U,
    0U, 0U, 0U, 236U, 89U, 148U, 219U, 46U, 11U, 107U, 241U, 27U, 11U, 148U,
    231U, 243U, 194U, 57U, 0U, 0U, 5U, 133U, 228U, 242U, 157U, 10U, 0U, 0U, 134U,
    194U, 27U, 29U, 192U, 149U, 0U, 0U, 230U, 76U, 0U, 0U, 48U, 247U, 18U, 0U,
    242U, 82U, 0U, 0U, 22U, MAX_uint8_T, 61U, 0U, 160U, 201U, 31U, 20U, 158U,
    MAX_uint8_T, 88U, 0U, 13U, 158U, 239U, 225U, 103U, MAX_uint8_T, 82U, 0U, 0U,
    0U, 0U, 0U, 44U, MAX_uint8_T, 44U, 0U, 0U, 0U, 0U, 0U, 127U, 219U, 0U, 0U,
    0U, 0U, 3U, 72U, 240U, 78U, 0U, 0U, 132U, MAX_uint8_T, 251U, 209U, 81U, 0U,
    0U, 148U, 172U, 148U, 172U, 0U, 0U, 0U, 0U, 0U, 0U, 148U, 172U, 148U, 172U,
    148U, 172U, 148U, 172U, 0U, 0U, 0U, 0U, 0U, 0U, 148U, 172U, 148U, 166U, 62U,
    135U, 123U, 36U, 0U, 0U, 0U, 0U, 0U, 2U, 86U, 185U, 0U, 0U, 0U, 8U, 103U,
    215U, 162U, 43U, 0U, 15U, 121U, 221U, 145U, 30U, 0U, 0U, 41U, 228U, 226U,
    39U, 0U, 0U, 0U, 0U, 0U, 16U, 122U, 222U, 146U, 31U, 0U, 0U, 0U, 0U, 0U, 8U,
    104U, 216U, 164U, 46U, 0U, 0U, 0U, 0U, 0U, 3U, 87U, 185U, 152U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 236U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 152U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 236U, 130U, 124U, 17U, 0U, 0U, 0U, 0U,
    0U, 16U, 122U, 221U, 142U, 29U, 0U, 0U, 0U, 0U, 0U, 8U, 105U, 216U, 160U,
    42U, 0U, 0U, 0U, 0U, 0U, 7U, 174U, 253U, 100U, 0U, 0U, 9U, 106U, 216U, 161U,
    43U, 0U, 18U, 125U, 223U, 143U, 29U, 0U, 0U, 0U, 131U, 126U, 18U, 0U, 0U, 0U,
    0U, 0U, 196U, MAX_uint8_T, 250U, 213U, 86U, 0U, 0U, 0U, 7U, 110U, 252U, 27U,
    0U, 0U, 0U, 50U, MAX_uint8_T, 40U, 0U, 0U, 1U, 186U, 172U, 0U, 0U, 0U, 128U,
    174U, 5U, 0U, 0U, 34U, 244U, 11U, 0U, 0U, 0U, 92U, 218U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 104U, 216U, 0U, 0U, 0U, 0U, 104U, 216U, 0U, 0U, 0U, 0U,
    0U, 0U, 26U, 143U, 221U, 249U, 224U, 131U, 6U, 0U, 0U, 0U, 74U, 218U, 107U,
    28U, 9U, 46U, 163U, 184U, 2U, 0U, 51U, 201U, 23U, 55U, 206U, 253U,
    MAX_uint8_T, 19U, 143U, 90U, 0U, 187U, 27U, 26U, 199U, 43U, 29U, 223U, 0U,
    30U, 159U, 44U, 142U, 0U, 142U, 70U, 0U, 80U, 176U, 0U, 17U, 159U, 92U, 87U,
    0U, 223U, 8U, 13U, 209U, 127U, 0U, 84U, 110U, 93U, 104U, 0U, 249U, 34U, 175U,
    175U, 105U, 56U, 200U, 10U, 36U, 198U, 4U, 176U, 234U, 86U, 129U, 249U, 193U,
    41U, 0U, 0U, 145U, 188U, 58U, 12U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U, 108U,
    214U, 251U, MAX_uint8_T, 209U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 92U, MAX_uint8_T,
    86U, 0U, 0U, 0U, 0U, 0U, 0U, 187U, 250U, 180U, 0U, 0U, 0U, 0U, 0U, 28U, 250U,
    115U, 251U, 22U, 0U, 0U, 0U, 0U, 121U, 181U, 8U, 239U, 112U, 0U, 0U, 0U, 0U,
    216U, 84U, 0U, 153U, 206U, 0U, 0U, 0U, 56U, 237U, 6U, 0U, 56U, MAX_uint8_T,
    44U, 0U, 0U, 151U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, 138U, 0U, 7U, 238U, 51U, 0U, 0U, 0U, 121U, 229U, 2U, 85U, 219U,
    0U, 0U, 0U, 0U, 34U, MAX_uint8_T, 70U, 180U, 131U, 0U, 0U, 0U, 0U, 0U, 203U,
    164U, 200U, MAX_uint8_T, 254U, 232U, 151U, 7U, 200U, 136U, 10U, 79U, 249U,
    111U, 200U, 136U, 0U, 0U, 219U, 124U, 200U, 136U, 16U, 112U, 226U, 26U, 200U,
    MAX_uint8_T, MAX_uint8_T, 239U, 56U, 0U, 200U, 136U, 24U, 130U, 247U, 69U,
    200U, 136U, 0U, 0U, 172U, 201U, 200U, 136U, 0U, 0U, 137U, 228U, 200U, 136U,
    4U, 48U, 225U, 171U, 200U, MAX_uint8_T, MAX_uint8_T, 238U, 173U, 24U, 0U, 0U,
    54U, 179U, 238U, 243U, 195U, 91U, 4U, 0U, 68U, 249U, 140U, 27U, 14U, 68U,
    171U, 64U, 1U, 219U, 177U, 0U, 0U, 0U, 0U, 0U, 0U, 46U, MAX_uint8_T, 72U, 0U,
    0U, 0U, 0U, 0U, 0U, 80U, MAX_uint8_T, 36U, 0U, 0U, 0U, 0U, 0U, 0U, 80U,
    MAX_uint8_T, 35U, 0U, 0U, 0U, 0U, 0U, 0U, 47U, MAX_uint8_T, 75U, 0U, 0U, 0U,
    0U, 0U, 0U, 2U, 223U, 188U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 76U, 252U, 155U, 33U,
    9U, 52U, 155U, 63U, 0U, 0U, 62U, 185U, 241U, 243U, 203U, 102U, 4U, 200U,
    MAX_uint8_T, MAX_uint8_T, 252U, 232U, 171U, 40U, 0U, 0U, 200U, 140U, 0U, 11U,
    55U, 188U, 237U, 31U, 0U, 200U, 140U, 0U, 0U, 0U, 10U, 232U, 157U, 0U, 200U,
    140U, 0U, 0U, 0U, 0U, 138U, 232U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 101U,
    MAX_uint8_T, 10U, 200U, 140U, 0U, 0U, 0U, 0U, 107U, MAX_uint8_T, 7U, 200U,
    140U, 0U, 0U, 0U, 0U, 143U, 223U, 0U, 200U, 140U, 0U, 0U, 0U, 9U, 235U, 137U,
    0U, 200U, 140U, 0U, 5U, 47U, 184U, 216U, 15U, 0U, 200U, MAX_uint8_T,
    MAX_uint8_T, 251U, 224U, 144U, 18U, 0U, 0U, 200U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, 120U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U,
    0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, 212U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U,
    0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 188U, 200U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 120U, 200U, 140U, 0U, 0U, 0U, 0U,
    200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, 212U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U,
    0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U,
    140U, 0U, 0U, 0U, 0U, 0U, 0U, 56U, 180U, 238U, 243U, 199U, 96U, 4U, 0U, 71U,
    250U, 142U, 27U, 14U, 68U, 171U, 64U, 2U, 220U, 179U, 0U, 0U, 0U, 0U, 0U, 0U,
    46U, MAX_uint8_T, 73U, 0U, 0U, 0U, 0U, 0U, 0U, 80U, MAX_uint8_T, 36U, 0U, 0U,
    0U, 0U, 0U, 0U, 80U, MAX_uint8_T, 36U, 0U, 0U, 0U, 0U, 0U, 0U, 48U,
    MAX_uint8_T, 74U, 0U, 0U, 0U, 16U, MAX_uint8_T, 68U, 2U, 223U, 186U, 0U, 0U,
    0U, 16U, MAX_uint8_T, 68U, 0U, 76U, 252U, 155U, 35U, 7U, 51U, MAX_uint8_T,
    68U, 0U, 0U, 61U, 183U, 239U, 250U, 229U, 182U, 39U, 200U, 140U, 0U, 0U, 0U,
    0U, 252U, 88U, 200U, 140U, 0U, 0U, 0U, 0U, 252U, 88U, 200U, 140U, 0U, 0U, 0U,
    0U, 252U, 88U, 200U, 140U, 0U, 0U, 0U, 0U, 252U, 88U, 200U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 88U, 200U,
    140U, 0U, 0U, 0U, 0U, 252U, 88U, 200U, 140U, 0U, 0U, 0U, 0U, 252U, 88U, 200U,
    140U, 0U, 0U, 0U, 0U, 252U, 88U, 200U, 140U, 0U, 0U, 0U, 0U, 252U, 88U, 200U,
    140U, 0U, 0U, 0U, 0U, 252U, 88U, 204U, 140U, 204U, 140U, 204U, 140U, 204U,
    140U, 204U, 140U, 204U, 140U, 204U, 140U, 204U, 140U, 204U, 140U, 204U, 140U,
    0U, 0U, 0U, 116U, 224U, 0U, 0U, 0U, 116U, 224U, 0U, 0U, 0U, 116U, 224U, 0U,
    0U, 0U, 116U, 224U, 0U, 0U, 0U, 116U, 224U, 0U, 0U, 0U, 116U, 224U, 0U, 0U,
    0U, 116U, 224U, 0U, 0U, 0U, 116U, 224U, 0U, 0U, 0U, 116U, 222U, 0U, 0U, 0U,
    129U, 198U, 0U, 0U, 18U, 205U, 129U, 44U, MAX_uint8_T, 234U, 155U, 11U, 200U,
    120U, 0U, 0U, 42U, 239U, 61U, 0U, 200U, 120U, 0U, 12U, 215U, 114U, 0U, 0U,
    200U, 120U, 0U, 169U, 172U, 0U, 0U, 0U, 200U, 120U, 111U, 216U, 13U, 0U, 0U,
    0U, 200U, 177U, 248U, 45U, 0U, 0U, 0U, 0U, 200U, 156U, 238U, 135U, 0U, 0U,
    0U, 0U, 200U, 120U, 70U, 252U, 92U, 0U, 0U, 0U, 200U, 120U, 0U, 116U, 248U,
    56U, 0U, 0U, 200U, 120U, 0U, 0U, 163U, 231U, 29U, 0U, 200U, 120U, 0U, 0U, 8U,
    203U, 206U, 10U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U,
    200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U,
    0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U,
    0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, 196U, 200U, MAX_uint8_T, 59U, 0U, 0U, 0U, 0U, 214U,
    252U, 200U, 253U, 148U, 0U, 0U, 0U, 51U, 254U, 252U, 200U, 192U, 233U, 3U,
    0U, 0U, 143U, 191U, 252U, 200U, 109U, 249U, 70U, 0U, 3U, 230U, 99U, 252U,
    200U, 92U, 178U, 159U, 0U, 71U, 198U, 64U, 252U, 200U, 92U, 88U, 240U, 7U,
    163U, 106U, 64U, 252U, 200U, 92U, 10U, 244U, 92U, 238U, 19U, 64U, 252U, 200U,
    92U, 0U, 166U, 236U, 178U, 0U, 64U, 252U, 200U, 92U, 0U, 77U, MAX_uint8_T,
    86U, 0U, 64U, 252U, 200U, 92U, 0U, 0U, 0U, 0U, 0U, 64U, 252U, 200U, 206U, 3U,
    0U, 0U, 0U, 192U, 100U, 200U, MAX_uint8_T, 111U, 0U, 0U, 0U, 192U, 100U,
    200U, 215U, 242U, 26U, 0U, 0U, 192U, 100U, 200U, 100U, 220U, 169U, 0U, 0U,
    192U, 100U, 200U, 92U, 72U, MAX_uint8_T, 70U, 0U, 192U, 100U, 200U, 92U, 0U,
    171U, 219U, 7U, 192U, 100U, 200U, 92U, 0U, 27U, 242U, 128U, 192U, 100U, 200U,
    92U, 0U, 0U, 113U, 248U, 223U, 100U, 200U, 92U, 0U, 0U, 3U, 208U,
    MAX_uint8_T, 100U, 200U, 92U, 0U, 0U, 0U, 56U, 254U, 100U, 0U, 0U, 56U, 185U,
    242U, 245U, 195U, 69U, 0U, 0U, 0U, 65U, 248U, 125U, 19U, 13U, 107U, 249U,
    85U, 0U, 1U, 216U, 167U, 0U, 0U, 0U, 0U, 143U, 234U, 8U, 44U, MAX_uint8_T,
    68U, 0U, 0U, 0U, 0U, 41U, MAX_uint8_T, 71U, 79U, MAX_uint8_T, 34U, 0U, 0U,
    0U, 0U, 7U, 254U, 106U, 80U, MAX_uint8_T, 35U, 0U, 0U, 0U, 0U, 8U,
    MAX_uint8_T, 106U, 43U, MAX_uint8_T, 70U, 0U, 0U, 0U, 0U, 42U, MAX_uint8_T,
    71U, 1U, 214U, 168U, 0U, 0U, 0U, 0U, 141U, 235U, 9U, 0U, 63U, 247U, 122U,
    17U, 14U, 106U, 249U, 88U, 0U, 0U, 0U, 55U, 187U, 244U, 245U, 194U, 70U, 0U,
    0U, 200U, MAX_uint8_T, MAX_uint8_T, 236U, 181U, 36U, 200U, 136U, 5U, 48U,
    218U, 187U, 200U, 136U, 0U, 0U, 128U, 234U, 200U, 136U, 0U, 0U, 156U, 213U,
    200U, 136U, 15U, 96U, 250U, 106U, 200U, MAX_uint8_T, 242U, 203U, 89U, 0U,
    200U, 136U, 0U, 0U, 0U, 0U, 200U, 136U, 0U, 0U, 0U, 0U, 200U, 136U, 0U, 0U,
    0U, 0U, 200U, 136U, 0U, 0U, 0U, 0U, 0U, 0U, 56U, 185U, 242U, 245U, 195U, 70U,
    0U, 0U, 0U, 0U, 65U, 248U, 125U, 19U, 13U, 107U, 249U, 85U, 0U, 0U, 1U, 216U,
    167U, 0U, 0U, 0U, 0U, 143U, 234U, 8U, 0U, 44U, MAX_uint8_T, 68U, 0U, 0U, 0U,
    0U, 41U, MAX_uint8_T, 70U, 0U, 79U, MAX_uint8_T, 34U, 0U, 0U, 0U, 0U, 7U,
    254U, 106U, 0U, 80U, MAX_uint8_T, 35U, 0U, 0U, 0U, 0U, 8U, MAX_uint8_T, 103U,
    0U, 42U, MAX_uint8_T, 70U, 0U, 0U, 0U, 0U, 42U, MAX_uint8_T, 70U, 0U, 0U,
    212U, 168U, 0U, 0U, 0U, 0U, 141U, 236U, 6U, 0U, 0U, 60U, 247U, 122U, 17U,
    14U, 106U, 248U, 82U, 0U, 0U, 0U, 0U, 56U, 189U, 245U, 249U, MAX_uint8_T,
    114U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 96U, 238U, 175U, 76U, 6U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 21U, 131U, 207U, 23U, 200U, MAX_uint8_T, MAX_uint8_T,
    239U, 172U, 20U, 0U, 0U, 200U, 136U, 5U, 57U, 231U, 155U, 0U, 0U, 200U, 136U,
    0U, 0U, 145U, 205U, 0U, 0U, 200U, 136U, 0U, 0U, 170U, 177U, 0U, 0U, 200U,
    136U, 17U, 99U, 246U, 60U, 0U, 0U, 200U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, 66U, 0U, 0U, 0U, 200U, 136U, 9U, 217U, 162U, 0U, 0U, 0U, 200U,
    136U, 0U, 58U, 253U, 85U, 0U, 0U, 200U, 136U, 0U, 0U, 141U, 238U, 27U, 0U,
    200U, 136U, 0U, 0U, 9U, 216U, 188U, 1U, 0U, 67U, 207U, 243U, 188U, 47U, 0U,
    22U, 243U, 103U, 12U, 77U, 152U, 0U, 68U, 254U, 9U, 0U, 0U, 0U, 0U, 24U,
    246U, 169U, 14U, 0U, 0U, 0U, 0U, 72U, 237U, 231U, 91U, 0U, 0U, 0U, 0U, 23U,
    163U, MAX_uint8_T, 152U, 0U, 0U, 0U, 0U, 0U, 105U, MAX_uint8_T, 53U, 0U, 0U,
    0U, 0U, 15U, MAX_uint8_T, 76U, 83U, 141U, 41U, 12U, 132U, 235U, 19U, 9U,
    123U, 223U, 240U, 186U, 49U, 0U, 228U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 28U, 0U, 0U, 0U, 140U,
    200U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 140U, 200U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    140U, 200U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 140U, 200U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 140U, 200U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 140U, 200U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 140U, 200U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 140U, 200U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 140U, 200U, 0U, 0U, 0U, 0U, 220U, 120U, 0U, 0U, 0U, 76U, 224U,
    220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U,
    120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U,
    0U, 0U, 0U, 76U, 224U, 214U, 128U, 0U, 0U, 0U, 82U, 219U, 184U, 166U, 0U, 0U,
    0U, 115U, 192U, 95U, 248U, 82U, 11U, 46U, 220U, 109U, 0U, 105U, 214U, 246U,
    220U, 123U, 3U, 151U, 188U, 0U, 0U, 0U, 0U, 1U, 226U, 67U, 60U, 253U, 25U,
    0U, 0U, 0U, 58U, 233U, 3U, 1U, 224U, 111U, 0U, 0U, 0U, 145U, 149U, 0U, 0U,
    134U, 201U, 0U, 0U, 2U, 229U, 62U, 0U, 0U, 43U, MAX_uint8_T, 35U, 0U, 63U,
    229U, 2U, 0U, 0U, 0U, 209U, 125U, 0U, 149U, 143U, 0U, 0U, 0U, 0U, 118U, 214U,
    3U, 232U, 56U, 0U, 0U, 0U, 0U, 29U, 254U, 115U, 224U, 1U, 0U, 0U, 0U, 0U, 0U,
    192U, 248U, 138U, 0U, 0U, 0U, 0U, 0U, 0U, 101U, MAX_uint8_T, 51U, 0U, 0U, 0U,
    222U, 106U, 0U, 0U, 33U, MAX_uint8_T, 94U, 0U, 0U, 29U, 244U, 5U, 160U, 167U,
    0U, 0U, 89U, MAX_uint8_T, 149U, 0U, 0U, 96U, 182U, 0U, 98U, 228U, 0U, 0U,
    145U, 215U, 204U, 0U, 0U, 163U, 114U, 0U, 36U, MAX_uint8_T, 34U, 0U, 201U,
    105U, 250U, 8U, 0U, 228U, 47U, 0U, 0U, 229U, 95U, 7U, 237U, 12U, 251U, 57U,
    40U, 234U, 1U, 0U, 0U, 168U, 156U, 58U, 189U, 0U, 207U, 111U, 107U, 167U, 0U,
    0U, 0U, 106U, 217U, 114U, 133U, 0U, 153U, 166U, 173U, 100U, 0U, 0U, 0U, 44U,
    MAX_uint8_T, 194U, 76U, 0U, 99U, 222U, 237U, 32U, 0U, 0U, 0U, 1U, 236U,
    MAX_uint8_T, 20U, 0U, 45U, MAX_uint8_T, 221U, 0U, 0U, 0U, 0U, 0U, 175U, 220U,
    0U, 0U, 3U, 244U, 153U, 0U, 0U, 0U, 116U, 249U, 39U, 0U, 0U, 5U, 211U, 103U,
    5U, 214U, 186U, 0U, 0U, 122U, 199U, 1U, 0U, 67U, MAX_uint8_T, 85U, 36U, 242U,
    46U, 0U, 0U, 0U, 171U, 227U, 192U, 138U, 0U, 0U, 0U, 0U, 29U, 244U, 229U,
    11U, 0U, 0U, 0U, 0U, 34U, 246U, 249U, 37U, 0U, 0U, 0U, 0U, 184U, 144U, 220U,
    182U, 0U, 0U, 0U, 87U, 223U, 10U, 74U, MAX_uint8_T, 78U, 0U, 15U, 230U, 74U,
    0U, 0U, 176U, 222U, 8U, 149U, 171U, 0U, 0U, 0U, 31U, 245U, 127U, 155U, 224U,
    8U, 0U, 0U, 0U, 156U, 160U, 22U, 241U, 124U, 0U, 0U, 60U, 236U, 21U, 0U,
    116U, 244U, 27U, 5U, 213U, 100U, 0U, 0U, 6U, 219U, 163U, 123U, 196U, 1U, 0U,
    0U, 0U, 78U, 254U, 244U, 45U, 0U, 0U, 0U, 0U, 0U, 208U, 163U, 0U, 0U, 0U, 0U,
    0U, 0U, 192U, 148U, 0U, 0U, 0U, 0U, 0U, 0U, 192U, 148U, 0U, 0U, 0U, 0U, 0U,
    0U, 192U, 148U, 0U, 0U, 0U, 0U, 0U, 0U, 192U, 148U, 0U, 0U, 0U, 20U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    64U, 0U, 0U, 0U, 0U, 0U, 169U, 226U, 12U, 0U, 0U, 0U, 0U, 74U, MAX_uint8_T,
    77U, 0U, 0U, 0U, 0U, 11U, 224U, 171U, 0U, 0U, 0U, 0U, 0U, 142U, 240U, 25U,
    0U, 0U, 0U, 0U, 50U, 252U, 104U, 0U, 0U, 0U, 0U, 3U, 205U, 197U, 1U, 0U, 0U,
    0U, 0U, 114U, 250U, 43U, 0U, 0U, 0U, 0U, 30U, 244U, 132U, 0U, 0U, 0U, 0U, 0U,
    100U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, 64U, 192U, MAX_uint8_T, 196U, 192U, 88U, 0U, 192U, 88U, 0U,
    192U, 88U, 0U, 192U, 88U, 0U, 192U, 88U, 0U, 192U, 88U, 0U, 192U, 88U, 0U,
    192U, 88U, 0U, 192U, 88U, 0U, 192U, 88U, 0U, 192U, MAX_uint8_T, 196U, 164U,
    87U, 0U, 0U, 0U, 91U, 159U, 0U, 0U, 0U, 21U, 229U, 1U, 0U, 0U, 0U, 203U, 48U,
    0U, 0U, 0U, 130U, 120U, 0U, 0U, 0U, 58U, 192U, 0U, 0U, 0U, 3U, 233U, 14U, 0U,
    0U, 0U, 169U, 81U, 0U, 0U, 0U, 97U, 153U, 0U, 0U, 0U, 26U, 225U, 0U, 0U, 0U,
    0U, 208U, 42U, 0U, 0U, 0U, 136U, 115U, 135U, MAX_uint8_T, 251U, 0U, 27U,
    251U, 0U, 27U, 251U, 0U, 27U, 251U, 0U, 27U, 251U, 0U, 27U, 251U, 0U, 27U,
    251U, 0U, 27U, 251U, 0U, 27U, 251U, 0U, 27U, 251U, 0U, 27U, 251U, 135U,
    MAX_uint8_T, 251U, 0U, 0U, 0U, 37U, 87U, 0U, 0U, 0U, 0U, 0U, 0U, 161U, 214U,
    2U, 0U, 0U, 0U, 0U, 34U, 228U, 186U, 87U, 0U, 0U, 0U, 0U, 156U, 115U, 53U,
    211U, 1U, 0U, 0U, 31U, 228U, 10U, 0U, 183U, 84U, 0U, 0U, 152U, 117U, 0U, 0U,
    57U, 208U, 1U, 28U, 228U, 11U, 0U, 0U, 0U, 187U, 80U, 116U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 244U, 31U, 221U, 85U, 0U, 0U, 28U,
    205U, 38U, 0U, 43U, 181U, 242U, 220U, 70U, 0U, 0U, 143U, 63U, 11U, 159U,
    202U, 0U, 0U, 0U, 0U, 0U, 96U, 223U, 0U, 0U, 73U, 191U, 236U, 253U, 224U, 0U,
    38U, 251U, 99U, 14U, 96U, 224U, 0U, 70U, 248U, 46U, 24U, 160U, 241U, 13U, 3U,
    164U, 243U, 199U, 66U, 209U, 182U, 192U, 128U, 0U, 0U, 0U, 0U, 0U, 192U,
    128U, 0U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 0U, 0U, 192U, 137U, 162U,
    244U, 219U, 81U, 0U, 192U, 227U, 84U, 11U, 111U, 248U, 28U, 192U, 130U, 0U,
    0U, 2U, 242U, 97U, 192U, 128U, 0U, 0U, 0U, 227U, 113U, 192U, 183U, 0U, 0U,
    9U, 249U, 80U, 192U, MAX_uint8_T, 120U, 15U, 137U, 227U, 7U, 192U, 133U,
    183U, 245U, 207U, 53U, 0U, 0U, 20U, 158U, 229U, 228U, 91U, 0U, 0U, 191U,
    214U, 46U, 26U, 153U, 0U, 37U, MAX_uint8_T, 76U, 0U, 0U, 0U, 0U, 65U,
    MAX_uint8_T, 37U, 0U, 0U, 0U, 0U, 30U, MAX_uint8_T, 77U, 0U, 0U, 0U, 0U, 0U,
    173U, 216U, 49U, 21U, 143U, 7U, 0U, 13U, 154U, 233U, 218U, 90U, 0U, 0U, 0U,
    0U, 0U, 0U, 84U, 240U, 0U, 0U, 0U, 0U, 0U, 84U, 240U, 0U, 0U, 0U, 0U, 0U,
    84U, 240U, 0U, 28U, 186U, 246U, 202U, 131U, 240U, 0U, 188U, 174U, 19U, 45U,
    192U, 240U, 32U, MAX_uint8_T, 45U, 0U, 0U, 84U, 240U, 66U, MAX_uint8_T, 14U,
    0U, 0U, 84U, 240U, 50U, MAX_uint8_T, 32U, 0U, 0U, 86U, 240U, 6U, 226U, 149U,
    12U, 60U, 209U, 240U, 0U, 55U, 207U, 247U, 187U, 109U, 240U, 0U, 21U, 173U,
    240U, 210U, 55U, 0U, 0U, 191U, 154U, 13U, 101U, 224U, 4U, 37U, MAX_uint8_T,
    32U, 0U, 1U, 248U, 51U, 65U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, 78U, 31U, MAX_uint8_T, 33U, 0U, 0U, 0U, 0U, 0U,
    172U, 189U, 39U, 2U, 0U, 0U, 0U, 11U, 144U, 227U, MAX_uint8_T, MAX_uint8_T,
    76U, 0U, 9U, 177U, 246U, MAX_uint8_T, 40U, 0U, 100U, 224U, 15U, 0U, 0U, 0U,
    130U, 192U, 0U, 0U, 0U, 124U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 120U,
    0U, 0U, 132U, 192U, 0U, 0U, 0U, 0U, 132U, 192U, 0U, 0U, 0U, 0U, 132U, 192U,
    0U, 0U, 0U, 0U, 132U, 192U, 0U, 0U, 0U, 0U, 132U, 192U, 0U, 0U, 0U, 0U, 132U,
    192U, 0U, 0U, 0U, 0U, 26U, 182U, 246U, 203U, 131U, 240U, 0U, 186U, 189U, 24U,
    39U, 188U, 240U, 34U, MAX_uint8_T, 53U, 0U, 0U, 84U, 240U, 66U, MAX_uint8_T,
    15U, 0U, 0U, 84U, 240U, 47U, MAX_uint8_T, 32U, 0U, 0U, 86U, 240U, 3U, 220U,
    149U, 12U, 58U, 208U, 237U, 0U, 48U, 203U, 246U, 192U, 114U, 229U, 0U, 0U,
    0U, 0U, 0U, 114U, 202U, 0U, 136U, 78U, 13U, 53U, 224U, 123U, 0U, 44U, 186U,
    243U, 221U, 129U, 5U, 192U, 128U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 0U,
    192U, 128U, 0U, 0U, 0U, 0U, 192U, 132U, 142U, 240U, 225U, 66U, 192U, 238U,
    117U, 12U, 148U, 201U, 192U, 153U, 0U, 0U, 94U, 227U, 192U, 128U, 0U, 0U,
    92U, 228U, 192U, 128U, 0U, 0U, 92U, 228U, 192U, 128U, 0U, 0U, 92U, 228U,
    192U, 128U, 0U, 0U, 92U, 228U, 192U, 128U, 0U, 0U, 0U, 0U, 192U, 128U, 192U,
    128U, 192U, 128U, 192U, 128U, 192U, 128U, 192U, 128U, 192U, 128U, 0U, 0U,
    140U, 180U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 140U, 180U, 0U, 0U, 140U,
    180U, 0U, 0U, 140U, 180U, 0U, 0U, 140U, 180U, 0U, 0U, 140U, 180U, 0U, 0U,
    140U, 180U, 0U, 0U, 140U, 180U, 0U, 0U, 145U, 170U, 0U, 9U, 196U, 126U, 252U,
    249U, 186U, 18U, 192U, 128U, 0U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 0U,
    0U, 192U, 128U, 0U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 28U, 228U, 87U, 0U, 192U,
    128U, 13U, 209U, 124U, 0U, 0U, 192U, 131U, 183U, 162U, 0U, 0U, 0U, 192U,
    198U, MAX_uint8_T, 65U, 0U, 0U, 0U, 192U, 128U, 131U, 237U, 41U, 0U, 0U,
    192U, 128U, 0U, 155U, 226U, 27U, 0U, 192U, 128U, 0U, 3U, 176U, 211U, 16U,
    192U, 128U, 192U, 128U, 192U, 128U, 192U, 128U, 192U, 128U, 192U, 128U, 192U,
    128U, 192U, 128U, 192U, 128U, 192U, 128U, 192U, 136U, 155U, 243U, 219U, 49U,
    107U, 232U, 235U, 90U, 192U, 242U, 106U, 11U, 181U, 229U, 150U, 17U, 127U,
    226U, 192U, 143U, 0U, 0U, 132U, 203U, 0U, 0U, 76U, 247U, 192U, 128U, 0U, 0U,
    132U, 188U, 0U, 0U, 76U, 248U, 192U, 128U, 0U, 0U, 132U, 188U, 0U, 0U, 76U,
    248U, 192U, 128U, 0U, 0U, 132U, 188U, 0U, 0U, 76U, 248U, 192U, 128U, 0U, 0U,
    132U, 188U, 0U, 0U, 76U, 248U, 192U, 132U, 142U, 240U, 225U, 66U, 192U, 238U,
    117U, 12U, 148U, 201U, 192U, 153U, 0U, 0U, 94U, 227U, 192U, 128U, 0U, 0U,
    92U, 228U, 192U, 128U, 0U, 0U, 92U, 228U, 192U, 128U, 0U, 0U, 92U, 228U,
    192U, 128U, 0U, 0U, 92U, 228U, 0U, 22U, 165U, 233U, 233U, 162U, 19U, 0U, 0U,
    192U, 178U, 23U, 25U, 182U, 186U, 0U, 37U, MAX_uint8_T, 43U, 0U, 0U, 48U,
    MAX_uint8_T, 32U, 66U, MAX_uint8_T, 15U, 0U, 0U, 19U, MAX_uint8_T, 61U, 36U,
    MAX_uint8_T, 43U, 0U, 0U, 49U, MAX_uint8_T, 31U, 0U, 190U, 177U, 23U, 26U,
    183U, 186U, 0U, 0U, 21U, 165U, 235U, 232U, 161U, 19U, 0U, 192U, 137U, 162U,
    244U, 219U, 81U, 0U, 192U, 227U, 84U, 11U, 111U, 248U, 28U, 192U, 130U, 0U,
    0U, 2U, 242U, 97U, 192U, 128U, 0U, 0U, 0U, 227U, 113U, 192U, 159U, 0U, 0U,
    9U, 249U, 80U, 192U, 224U, 104U, 14U, 137U, 227U, 7U, 192U, 130U, 153U, 247U,
    207U, 53U, 0U, 192U, 128U, 0U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 0U,
    0U, 192U, 128U, 0U, 0U, 0U, 0U, 0U, 0U, 28U, 186U, 246U, 202U, 131U, 240U,
    0U, 188U, 174U, 19U, 45U, 192U, 240U, 32U, MAX_uint8_T, 45U, 0U, 0U, 84U,
    240U, 66U, MAX_uint8_T, 14U, 0U, 0U, 84U, 240U, 50U, MAX_uint8_T, 32U, 0U,
    0U, 86U, 240U, 6U, 226U, 149U, 12U, 60U, 209U, 240U, 0U, 55U, 207U, 247U,
    187U, 109U, 240U, 0U, 0U, 0U, 0U, 0U, 84U, 240U, 0U, 0U, 0U, 0U, 0U, 84U,
    240U, 0U, 0U, 0U, 0U, 0U, 84U, 240U, 192U, 138U, 169U, 248U, 16U, 192U, 235U,
    85U, 4U, 0U, 192U, 142U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 192U, 128U, 0U,
    0U, 0U, 192U, 128U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 74U, 217U, 253U,
    MAX_uint8_T, 28U, 226U, 105U, 2U, 0U, 0U, 204U, 192U, 43U, 0U, 0U, 29U, 174U,
    252U, 171U, 15U, 0U, 0U, 42U, 226U, 132U, 0U, 0U, 27U, 205U, 126U,
    MAX_uint8_T, MAX_uint8_T, 241U, 164U, 11U, 0U, 167U, 137U, 0U, 0U, 144U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 92U, 0U, 180U, 140U, 0U, 0U, 0U, 180U,
    140U, 0U, 0U, 0U, 180U, 140U, 0U, 0U, 0U, 179U, 141U, 0U, 0U, 0U, 157U, 198U,
    13U, 0U, 0U, 40U, 210U, 254U, 84U, 212U, 108U, 0U, 0U, 112U, 208U, 212U,
    108U, 0U, 0U, 112U, 208U, 212U, 108U, 0U, 0U, 112U, 208U, 212U, 108U, 0U, 0U,
    112U, 208U, 211U, 109U, 0U, 0U, 137U, 208U, 186U, 161U, 11U, 104U, 235U,
    208U, 55U, 220U, 242U, 151U, 119U, 208U, 182U, 138U, 0U, 0U, 0U, 182U, 117U,
    88U, 230U, 3U, 0U, 27U, 247U, 22U, 8U, 240U, 71U, 0U, 123U, 173U, 0U, 0U,
    156U, 166U, 1U, 220U, 73U, 0U, 0U, 63U, 246U, 78U, 226U, 2U, 0U, 0U, 1U,
    223U, 234U, 129U, 0U, 0U, 0U, 0U, 131U, 254U, 31U, 0U, 0U, 201U, 111U, 0U,
    0U, 183U, 209U, 0U, 0U, 77U, 194U, 129U, 182U, 0U, 11U, 236U, 251U, 22U, 0U,
    159U, 113U, 57U, 246U, 8U, 80U, 173U, 199U, 89U, 3U, 235U, 32U, 2U, 237U,
    69U, 156U, 96U, 131U, 156U, 66U, 205U, 0U, 0U, 169U, 141U, 228U, 21U, 63U,
    224U, 148U, 124U, 0U, 0U, 97U, 241U, 196U, 0U, 6U, 244U, 241U, 42U, 0U, 0U,
    25U, MAX_uint8_T, 118U, 0U, 0U, 182U, 216U, 0U, 0U, 22U, 230U, 127U, 0U, 0U,
    99U, 208U, 5U, 0U, 63U, 249U, 66U, 29U, 235U, 47U, 0U, 0U, 0U, 124U, 231U,
    193U, 124U, 0U, 0U, 0U, 0U, 13U, 243U, 238U, 6U, 0U, 0U, 0U, 0U, 159U, 170U,
    230U, 127U, 0U, 0U, 0U, 88U, 217U, 11U, 64U, 249U, 65U, 0U, 33U, 234U, 50U,
    0U, 0U, 124U, 231U, 23U, 180U, 163U, 0U, 0U, 0U, 171U, 135U, 82U, 246U, 14U,
    0U, 22U, 249U, 39U, 5U, 235U, 100U, 0U, 119U, 198U, 0U, 0U, 144U, 197U, 1U,
    219U, 102U, 0U, 0U, 47U, MAX_uint8_T, 104U, 246U, 15U, 0U, 0U, 0U, 206U,
    248U, 165U, 0U, 0U, 0U, 0U, 109U, MAX_uint8_T, 69U, 0U, 0U, 0U, 0U, 108U,
    226U, 2U, 0U, 0U, 0U, 0U, 202U, 132U, 0U, 0U, 0U, 0U, 40U, MAX_uint8_T, 36U,
    0U, 0U, 0U, 4U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, 152U, 0U, 0U, 0U, 0U, 97U, 245U, 52U, 0U, 0U, 0U, 65U, 248U,
    82U, 0U, 0U, 0U, 39U, 238U, 117U, 0U, 0U, 0U, 20U, 220U, 155U, 0U, 0U, 0U,
    7U, 195U, 188U, 4U, 0U, 0U, 0U, 56U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, 172U, 0U, 62U, 208U, 92U, 0U, 213U, 94U, 1U, 0U,
    207U, 79U, 0U, 0U, 161U, 107U, 0U, 11U, 190U, 61U, 0U, 216U, 182U, 0U, 0U,
    6U, 186U, 44U, 0U, 0U, 154U, 103U, 0U, 0U, 188U, 99U, 0U, 0U, 221U, 67U, 0U,
    0U, 197U, 103U, 1U, 0U, 47U, 202U, 92U, 12U, 228U, 12U, 228U, 12U, 228U, 12U,
    228U, 12U, 228U, 12U, 228U, 12U, 228U, 12U, 228U, 12U, 228U, 12U, 228U, 12U,
    228U, 12U, 228U, 35U, 225U, 102U, 0U, 0U, 0U, 40U, 251U, 18U, 0U, 0U, 19U,
    254U, 12U, 0U, 0U, 47U, 221U, 0U, 0U, 0U, 12U, 226U, 24U, 0U, 0U, 0U, 123U,
    MAX_uint8_T, 19U, 0U, 5U, 211U, 20U, 0U, 0U, 44U, 213U, 0U, 0U, 0U, 40U,
    245U, 2U, 0U, 0U, 9U, 254U, 25U, 0U, 0U, 49U, 244U, 9U, 0U, 35U, 221U, 83U,
    0U, 0U, 1U, 169U, 245U, 194U, 103U, 18U, 144U, 119U, 62U, 198U, 17U, 82U,
    176U, 241U, 212U, 25U, 148U, 172U, 148U, 172U, 0U, 0U, 112U, 135U, 120U,
    143U, 128U, 151U, 136U, 159U, 144U, 167U, 148U, 171U, 148U, 172U, 0U, 0U, 0U,
    164U, 0U, 0U, 0U, 0U, 0U, 164U, 0U, 0U, 0U, 70U, 202U, 254U, MAX_uint8_T,
    164U, 46U, 251U, 93U, 168U, 0U, 0U, 144U, 203U, 0U, 164U, 0U, 0U, 170U, 178U,
    0U, 164U, 0U, 0U, 138U, 212U, 0U, 164U, 0U, 0U, 35U, 249U, 124U, 169U, 0U,
    0U, 0U, 62U, 203U, 254U, MAX_uint8_T, 164U, 0U, 0U, 0U, 164U, 0U, 0U, 0U, 0U,
    60U, 211U, 235U, 90U, 0U, 0U, 222U, 110U, 21U, 127U, 0U, 15U, MAX_uint8_T,
    41U, 0U, 0U, 0U, 24U, MAX_uint8_T, 40U, 0U, 0U, 60U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, 132U, 0U, 0U, 24U, MAX_uint8_T, 39U, 0U, 0U, 0U,
    25U, MAX_uint8_T, 31U, 0U, 0U, 0U, 54U, 242U, 4U, 0U, 0U, 13U, 183U, 115U,
    0U, 0U, 0U, 112U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 240U,
    41U, 139U, 0U, 0U, 0U, 0U, 88U, 93U, 0U, 166U, 155U, 227U, 238U, 154U, 201U,
    9U, 0U, 81U, 211U, 40U, 22U, 176U, 136U, 0U, 0U, 164U, 84U, 0U, 0U, 29U,
    216U, 0U, 0U, 164U, 84U, 0U, 0U, 29U, 216U, 0U, 0U, 81U, 211U, 38U, 23U,
    176U, 136U, 0U, 0U, 165U, 152U, 226U, 237U, 152U, 200U, 9U, 41U, 138U, 0U,
    0U, 0U, 0U, 88U, 93U, 51U, 253U, 67U, 0U, 0U, 0U, 147U, 142U, 0U, 155U, 209U,
    2U, 0U, 49U, 221U, 11U, 0U, 21U, 239U, 100U, 1U, 200U, 74U, 0U, 0U, 0U, 110U,
    231U, 115U, 167U, 0U, 0U, 0U, 0U, 4U, 211U, 238U, 23U, 0U, 0U, 0U, 112U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 148U, 0U, 0U, 0U, 0U,
    140U, 180U, 0U, 0U, 0U, 0U, 112U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, 148U, 0U, 0U, 0U, 0U, 140U, 180U, 0U, 0U, 0U, 0U, 0U, 0U, 140U,
    180U, 0U, 0U, 0U, 12U, 228U, 12U, 228U, 12U, 228U, 12U, 228U, 12U, 228U, 0U,
    0U, 0U, 0U, 12U, 228U, 12U, 228U, 12U, 228U, 12U, 228U, 12U, 228U, 1U, 126U,
    224U, 252U, MAX_uint8_T, 164U, 94U, 220U, 44U, 2U, 0U, 0U, 104U, 198U, 6U,
    0U, 0U, 0U, 3U, 216U, 226U, 90U, 0U, 0U, 68U, 206U, 91U, 214U, 183U, 17U,
    131U, 146U, 0U, 2U, 148U, 172U, 73U, 221U, 21U, 0U, 61U, 217U, 0U, 103U,
    223U, 100U, 116U, 145U, 0U, 0U, 31U, 170U, 254U, 55U, 0U, 0U, 0U, 0U, 99U,
    221U, 0U, 0U, 0U, 13U, 126U, 222U, 152U, MAX_uint8_T, MAX_uint8_T, 240U,
    186U, 48U, 208U, 72U, 76U, 204U, 0U, 0U, 14U, 134U, 221U, 249U, 227U, 148U,
    22U, 0U, 0U, 0U, 21U, 209U, 134U, 36U, 5U, 30U, 119U, 218U, 36U, 0U, 0U,
    177U, 75U, 18U, 170U, 242U, MAX_uint8_T, 92U, 57U, 198U, 2U, 35U, 166U, 0U,
    161U, 153U, 15U, 0U, 0U, 0U, 140U, 66U, 85U, 97U, 0U, 231U, 12U, 0U, 0U, 0U,
    0U, 69U, 116U, 84U, 96U, 0U, 230U, 11U, 0U, 0U, 0U, 0U, 80U, 115U, 34U, 167U,
    0U, 156U, 154U, 18U, 0U, 0U, 0U, 151U, 65U, 0U, 175U, 75U, 16U, 166U, 242U,
    MAX_uint8_T, 92U, 60U, 204U, 2U, 0U, 21U, 209U, 131U, 33U, 5U, 30U, 118U,
    217U, 37U, 0U, 0U, 0U, 15U, 138U, 224U, 250U, 226U, 148U, 23U, 0U, 0U, 128U,
    MAX_uint8_T, 242U, 106U, 0U, 0U, 0U, 89U, 200U, 0U, 83U, 220U, 253U, 204U,
    0U, 217U, 83U, 85U, 216U, 2U, 137U, 242U, 157U, 229U, 85U, 0U, 0U, 78U, 134U,
    10U, 178U, 26U, 0U, 80U, 199U, 23U, 188U, 95U, 0U, 22U, 244U, 46U, 136U,
    177U, 0U, 0U, 0U, 80U, 199U, 23U, 189U, 95U, 0U, 0U, 0U, 79U, 134U, 10U,
    178U, 26U, 152U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, 236U, 0U, 0U, 0U, 0U, 0U, 0U, 4U, 236U, 0U, 0U, 0U,
    0U, 0U, 0U, 4U, 236U, 0U, 0U, 0U, 0U, 0U, 0U, 4U, 236U, 16U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 148U, 0U, 99U, 223U,
    235U, 141U, 5U, 69U, 179U, 32U, 18U, 137U, 128U, 153U, 18U, MAX_uint8_T,
    232U, 32U, 168U, 154U, 18U, MAX_uint8_T, 221U, 16U, 167U, 71U, 182U, 189U,
    182U, 156U, 128U, 0U, 103U, 225U, 234U, 140U, 5U, 116U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 244U, 0U, 91U, 236U, 205U, 30U, 2U,
    212U, 25U, 85U, 153U, 2U, 211U, 24U, 84U, 153U, 0U, 92U, 237U, 206U, 31U, 0U,
    0U, 0U, 76U, 164U, 0U, 0U, 0U, 0U, 0U, 0U, 76U, 164U, 0U, 0U, 0U, 152U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    236U, 0U, 0U, 0U, 76U, 164U, 0U, 0U, 0U, 0U, 0U, 0U, 76U, 164U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 152U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 236U, 0U, 236U, 254U, 208U, 33U, 0U,
    0U, 3U, 157U, 123U, 0U, 0U, 4U, 200U, 57U, 0U, 1U, 158U, 119U, 0U, 0U, 150U,
    130U, 0U, 0U, 12U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 128U, 236U, 253U,
    210U, 24U, 0U, 22U, 209U, 47U, 120U, MAX_uint8_T, 160U, 1U, 0U, 22U, 190U,
    88U, 0U, 16U, 178U, 105U, MAX_uint8_T, 250U, 187U, 14U, 0U, 90U, 219U, 29U,
    41U, 204U, 26U, 0U, 192U, 128U, 0U, 0U, 92U, 228U, 192U, 128U, 0U, 0U, 92U,
    228U, 192U, 128U, 0U, 0U, 92U, 228U, 192U, 128U, 0U, 0U, 92U, 228U, 192U,
    131U, 0U, 0U, 121U, 228U, 192U, 199U, 15U, 81U, 227U, 228U, 192U, 230U, 246U,
    182U, 107U, 228U, 192U, 128U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 0U,
    192U, 128U, 0U, 0U, 0U, 0U, 23U, 186U, 242U, MAX_uint8_T, MAX_uint8_T, 136U,
    131U, MAX_uint8_T, MAX_uint8_T, 208U, 64U, 136U, 146U, MAX_uint8_T,
    MAX_uint8_T, 208U, 64U, 136U, 79U, MAX_uint8_T, MAX_uint8_T, 208U, 64U, 136U,
    0U, 116U, 225U, 207U, 64U, 136U, 0U, 0U, 0U, 200U, 64U, 136U, 0U, 0U, 0U,
    200U, 64U, 136U, 0U, 0U, 0U, 200U, 64U, 136U, 0U, 0U, 0U, 200U, 64U, 136U,
    0U, 0U, 0U, 200U, 64U, 136U, 0U, 0U, 0U, 200U, 64U, 136U, 0U, 0U, 0U, 200U,
    64U, 136U, 188U, 216U, 188U, 216U, 84U, 228U, 32U, 3U, 158U, 101U, 196U,
    226U, 32U, 32U, 145U, 100U, 0U, 174U, 224U, 112U, 0U, 0U, 128U, 112U, 0U, 0U,
    128U, 112U, 0U, 0U, 128U, 112U, 0U, 192U, MAX_uint8_T, MAX_uint8_T, 180U, 0U,
    92U, 229U, 235U, 111U, 0U, 15U, 243U, 52U, 35U, 239U, 32U, 47U, 230U, 0U, 0U,
    203U, 70U, 15U, 244U, 50U, 35U, 239U, 33U, 0U, 95U, 231U, 234U, 110U, 0U,
    64U, 149U, 1U, 167U, 45U, 0U, 0U, 0U, 143U, 149U, 36U, 212U, 46U, 0U, 0U, 3U,
    222U, 87U, 93U, 216U, 3U, 0U, 142U, 150U, 35U, 212U, 46U, 0U, 64U, 150U, 1U,
    167U, 45U, 0U, 0U, 16U, 119U, 145U, 0U, 0U, 0U, 0U, 125U, 91U, 0U, 127U,
    214U, 172U, 0U, 0U, 0U, 50U, 166U, 0U, 0U, 0U, 68U, 172U, 0U, 0U, 8U, 188U,
    19U, 0U, 0U, 0U, 68U, 172U, 0U, 0U, 142U, 74U, 0U, 0U, 0U, 0U, 68U, 172U, 0U,
    65U, 151U, 0U, 52U, 252U, 0U, 0U, 68U, 172U, 14U, 190U, 12U, 4U, 182U, 231U,
    0U, 0U, 0U, 0U, 158U, 60U, 0U, 119U, 83U, 220U, 0U, 0U, 0U, 82U, 136U, 0U,
    35U, 167U, 0U, 220U, 0U, 0U, 23U, 189U, 6U, 0U, 111U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, 200U, 0U, 172U, 46U, 0U, 0U, 0U, 0U, 0U, 220U, 0U,
    16U, 119U, 145U, 0U, 0U, 0U, 4U, 187U, 28U, 0U, 127U, 214U, 172U, 0U, 0U, 0U,
    129U, 90U, 0U, 0U, 0U, 68U, 172U, 0U, 0U, 54U, 165U, 0U, 0U, 0U, 0U, 68U,
    172U, 0U, 9U, 191U, 18U, 0U, 0U, 0U, 0U, 68U, 172U, 0U, 147U, 72U, 168U,
    MAX_uint8_T, 229U, 74U, 0U, 68U, 172U, 69U, 149U, 0U, 0U, 0U, 93U, 187U, 0U,
    0U, 17U, 191U, 11U, 0U, 0U, 0U, 140U, 111U, 0U, 0U, 163U, 57U, 0U, 0U, 0U,
    105U, 160U, 1U, 0U, 86U, 132U, 0U, 0U, 0U, 91U, 177U, 3U, 0U, 25U, 188U, 5U,
    0U, 0U, 0U, 204U, MAX_uint8_T, MAX_uint8_T, 196U, 76U, MAX_uint8_T, 246U,
    144U, 0U, 0U, 0U, 7U, 190U, 21U, 0U, 1U, 72U, 204U, 0U, 0U, 0U, 141U, 79U,
    0U, 0U, 216U, 247U, 74U, 0U, 0U, 63U, 155U, 0U, 0U, 0U, 3U, 56U, 234U, 7U,
    14U, 191U, 13U, 0U, 0U, 0U, 0U, 46U, 243U, 11U, 158U, 62U, 52U, 252U, 0U,
    96U, MAX_uint8_T, 239U, 117U, 80U, 138U, 4U, 182U, 231U, 0U, 0U, 0U, 0U, 22U,
    189U, 7U, 119U, 83U, 220U, 0U, 0U, 0U, 0U, 171U, 47U, 35U, 167U, 0U, 220U,
    0U, 0U, 0U, 99U, 120U, 0U, 111U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 200U,
    0U, 32U, 184U, 3U, 0U, 0U, 0U, 0U, 220U, 0U, 0U, 0U, 88U, 232U, 0U, 0U, 0U,
    0U, 88U, 232U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 90U, 220U, 0U, 0U, 0U,
    0U, 133U, 157U, 0U, 0U, 0U, 65U, 222U, 23U, 0U, 0U, 57U, 243U, 63U, 0U, 0U,
    0U, 172U, 178U, 0U, 0U, 0U, 0U, 157U, 211U, 31U, 0U, 0U, 0U, 21U, 171U, 239U,
    MAX_uint8_T, MAX_uint8_T, 64U, 0U, 0U, 37U, 226U, 74U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 34U, 206U, 31U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 92U, MAX_uint8_T, 86U, 0U, 0U, 0U, 0U, 0U, 0U, 187U, 250U, 180U, 0U,
    0U, 0U, 0U, 0U, 28U, 250U, 115U, 251U, 22U, 0U, 0U, 0U, 0U, 121U, 181U, 8U,
    239U, 112U, 0U, 0U, 0U, 0U, 216U, 84U, 0U, 153U, 206U, 0U, 0U, 0U, 56U, 237U,
    6U, 0U, 56U, MAX_uint8_T, 44U, 0U, 0U, 151U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 138U, 0U, 7U, 238U, 51U, 0U, 0U, 0U,
    121U, 229U, 2U, 85U, 219U, 0U, 0U, 0U, 0U, 34U, MAX_uint8_T, 70U, 180U, 131U,
    0U, 0U, 0U, 0U, 0U, 203U, 164U, 0U, 0U, 0U, 0U, 79U, 224U, 35U, 0U, 0U, 0U,
    0U, 0U, 34U, 206U, 32U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 92U, MAX_uint8_T, 86U, 0U, 0U, 0U, 0U, 0U, 0U, 187U, 250U, 180U, 0U,
    0U, 0U, 0U, 0U, 28U, 250U, 115U, 251U, 22U, 0U, 0U, 0U, 0U, 121U, 181U, 8U,
    239U, 112U, 0U, 0U, 0U, 0U, 216U, 84U, 0U, 153U, 206U, 0U, 0U, 0U, 56U, 237U,
    6U, 0U, 56U, MAX_uint8_T, 44U, 0U, 0U, 151U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 138U, 0U, 7U, 238U, 51U, 0U, 0U, 0U,
    121U, 229U, 2U, 85U, 219U, 0U, 0U, 0U, 0U, 34U, MAX_uint8_T, 70U, 180U, 131U,
    0U, 0U, 0U, 0U, 0U, 203U, 164U, 0U, 0U, 0U, 151U, 240U, 145U, 0U, 0U, 0U, 0U,
    0U, 89U, 177U, 15U, 180U, 86U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 92U, MAX_uint8_T, 86U, 0U, 0U, 0U, 0U, 0U, 0U, 187U, 250U, 180U,
    0U, 0U, 0U, 0U, 0U, 28U, 250U, 115U, 251U, 22U, 0U, 0U, 0U, 0U, 121U, 181U,
    8U, 239U, 112U, 0U, 0U, 0U, 0U, 216U, 84U, 0U, 153U, 206U, 0U, 0U, 0U, 56U,
    237U, 6U, 0U, 56U, MAX_uint8_T, 44U, 0U, 0U, 151U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 138U, 0U, 7U, 238U, 51U, 0U, 0U, 0U,
    121U, 229U, 2U, 85U, 219U, 0U, 0U, 0U, 0U, 34U, MAX_uint8_T, 70U, 180U, 131U,
    0U, 0U, 0U, 0U, 0U, 203U, 164U, 0U, 0U, 68U, 241U, 136U, 92U, 132U, 0U, 0U,
    0U, 0U, 153U, 75U, 149U, 239U, 52U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 92U, MAX_uint8_T, 86U, 0U, 0U, 0U, 0U, 0U, 0U, 187U, 250U,
    180U, 0U, 0U, 0U, 0U, 0U, 28U, 250U, 115U, 251U, 22U, 0U, 0U, 0U, 0U, 121U,
    181U, 8U, 239U, 112U, 0U, 0U, 0U, 0U, 216U, 84U, 0U, 153U, 206U, 0U, 0U, 0U,
    56U, 237U, 6U, 0U, 56U, MAX_uint8_T, 44U, 0U, 0U, 151U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 138U, 0U, 7U, 238U, 51U,
    0U, 0U, 0U, 121U, 229U, 2U, 85U, 219U, 0U, 0U, 0U, 0U, 34U, MAX_uint8_T, 70U,
    180U, 131U, 0U, 0U, 0U, 0U, 0U, 203U, 164U, 0U, 0U, 88U, 192U, 0U, 212U, 68U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 92U, MAX_uint8_T,
    86U, 0U, 0U, 0U, 0U, 0U, 0U, 187U, 250U, 180U, 0U, 0U, 0U, 0U, 0U, 28U, 250U,
    115U, 251U, 22U, 0U, 0U, 0U, 0U, 121U, 181U, 8U, 239U, 112U, 0U, 0U, 0U, 0U,
    216U, 84U, 0U, 153U, 206U, 0U, 0U, 0U, 56U, 237U, 6U, 0U, 56U, MAX_uint8_T,
    44U, 0U, 0U, 151U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, 138U, 0U, 7U, 238U, 51U, 0U, 0U, 0U, 121U, 229U, 2U, 85U, 219U,
    0U, 0U, 0U, 0U, 34U, MAX_uint8_T, 70U, 180U, 131U, 0U, 0U, 0U, 0U, 0U, 203U,
    164U, 0U, 0U, 0U, 127U, 243U, 123U, 0U, 0U, 0U, 0U, 0U, 0U, 180U, 29U, 174U,
    0U, 0U, 0U, 0U, 0U, 0U, 130U, 244U, 126U, 0U, 0U, 0U, 0U, 0U, 0U, 92U,
    MAX_uint8_T, 86U, 0U, 0U, 0U, 0U, 0U, 0U, 187U, 250U, 180U, 0U, 0U, 0U, 0U,
    0U, 28U, 250U, 115U, 251U, 22U, 0U, 0U, 0U, 0U, 121U, 181U, 8U, 239U, 112U,
    0U, 0U, 0U, 0U, 216U, 84U, 0U, 153U, 206U, 0U, 0U, 0U, 56U, 237U, 6U, 0U,
    56U, MAX_uint8_T, 44U, 0U, 0U, 151U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, 138U, 0U, 7U, 238U, 51U, 0U, 0U, 0U, 121U, 229U,
    2U, 85U, 219U, 0U, 0U, 0U, 0U, 34U, MAX_uint8_T, 70U, 180U, 131U, 0U, 0U, 0U,
    0U, 0U, 203U, 164U, 0U, 0U, 0U, 0U, 0U, 179U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 48U, 0U, 0U, 0U, 0U, 62U, 238U,
    MAX_uint8_T, 68U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 201U, 115U, MAX_uint8_T,
    68U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 87U, 206U, 22U, MAX_uint8_T, 68U, 0U, 0U,
    0U, 0U, 0U, 0U, 5U, 220U, 66U, 20U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, 140U, 0U, 0U, 0U, 111U, 179U, 0U, 20U, MAX_uint8_T, 68U, 0U, 0U,
    0U, 0U, 0U, 14U, 235U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    68U, 0U, 0U, 0U, 0U, 0U, 135U, 154U, 0U, 0U, 20U, MAX_uint8_T, 68U, 0U, 0U,
    0U, 0U, 27U, 239U, 30U, 0U, 0U, 20U, MAX_uint8_T, 68U, 0U, 0U, 0U, 0U, 158U,
    149U, 0U, 0U, 0U, 20U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, 124U, 0U, 0U, 54U, 179U, 238U, 243U, 195U, 91U, 4U, 0U, 68U,
    249U, 140U, 27U, 14U, 68U, 171U, 64U, 1U, 219U, 177U, 0U, 0U, 0U, 0U, 0U, 0U,
    46U, MAX_uint8_T, 72U, 0U, 0U, 0U, 0U, 0U, 0U, 80U, MAX_uint8_T, 36U, 0U, 0U,
    0U, 0U, 0U, 0U, 80U, MAX_uint8_T, 35U, 0U, 0U, 0U, 0U, 0U, 0U, 47U,
    MAX_uint8_T, 75U, 0U, 0U, 0U, 0U, 0U, 0U, 2U, 223U, 188U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 76U, 252U, 155U, 33U, 9U, 52U, 155U, 63U, 0U, 0U, 62U, 185U, 241U,
    243U, 203U, 102U, 4U, 0U, 0U, 0U, 0U, 104U, 220U, 21U, 0U, 0U, 0U, 0U, 0U,
    0U, 6U, 176U, 81U, 0U, 0U, 0U, 0U, 0U, 0U, 216U, 218U, 20U, 0U, 0U, 2U, 155U,
    179U, 1U, 0U, 0U, 0U, 1U, 149U, 121U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 200U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 120U, 200U, 140U, 0U, 0U,
    0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 212U, 0U, 200U, 140U, 0U, 0U, 0U, 0U,
    200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U,
    0U, 0U, 200U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 188U, 0U,
    0U, 19U, 223U, 95U, 0U, 0U, 1U, 180U, 90U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    200U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 120U, 200U, 140U,
    0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 212U, 0U, 200U, 140U, 0U, 0U, 0U, 0U,
    200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U,
    0U, 0U, 200U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 188U, 0U,
    53U, 236U, 225U, 21U, 0U, 17U, 205U, 51U, 89U, 182U, 2U, 0U, 0U, 0U, 0U, 0U,
    0U, 200U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 120U, 200U,
    140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U,
    200U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 212U, 0U, 200U, 140U, 0U, 0U,
    0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U,
    0U, 0U, 0U, 0U, 200U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    188U, 0U, 212U, 68U, 80U, 200U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 200U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 120U, 200U, 140U, 0U, 0U,
    0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 212U, 0U, 200U, 140U, 0U, 0U, 0U, 0U,
    200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 0U,
    0U, 0U, 200U, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 188U, 3U,
    165U, 168U, 0U, 0U, 2U, 160U, 109U, 0U, 0U, 0U, 0U, 0U, 0U, 204U, 140U, 0U,
    0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U,
    0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U,
    140U, 0U, 0U, 204U, 140U, 0U, 16U, 220U, 102U, 1U, 174U, 97U, 0U, 0U, 0U, 0U,
    0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U,
    140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U,
    204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 59U, 237U, 221U,
    17U, 0U, 21U, 206U, 46U, 96U, 177U, 1U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 204U,
    140U, 0U, 0U, 0U, 0U, 204U, 140U, 0U, 0U, 0U, 0U, 204U, 140U, 0U, 0U, 0U, 0U,
    204U, 140U, 0U, 0U, 0U, 0U, 204U, 140U, 0U, 0U, 0U, 0U, 204U, 140U, 0U, 0U,
    0U, 0U, 204U, 140U, 0U, 0U, 0U, 0U, 204U, 140U, 0U, 0U, 0U, 0U, 204U, 140U,
    0U, 0U, 0U, 0U, 204U, 140U, 0U, 0U, 240U, 40U, 108U, 172U, 0U, 0U, 0U, 0U,
    0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U,
    0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U,
    140U, 0U, 0U, 204U, 140U, 0U, 0U, 204U, 140U, 0U, 0U, 0U, 200U, MAX_uint8_T,
    MAX_uint8_T, 252U, 232U, 171U, 40U, 0U, 0U, 0U, 0U, 200U, 140U, 0U, 11U, 55U,
    188U, 237U, 31U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 10U, 232U, 157U, 0U, 0U,
    0U, 200U, 140U, 0U, 0U, 0U, 0U, 138U, 232U, 0U, 52U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 168U, 0U, 0U, 101U, MAX_uint8_T, 10U,
    0U, 0U, 200U, 140U, 0U, 0U, 0U, 0U, 107U, MAX_uint8_T, 7U, 0U, 0U, 200U,
    140U, 0U, 0U, 0U, 0U, 143U, 223U, 0U, 0U, 0U, 200U, 140U, 0U, 0U, 0U, 9U,
    235U, 137U, 0U, 0U, 0U, 200U, 140U, 0U, 5U, 47U, 184U, 216U, 15U, 0U, 0U, 0U,
    200U, MAX_uint8_T, MAX_uint8_T, 251U, 224U, 144U, 18U, 0U, 0U, 0U, 0U, 186U,
    215U, 50U, 210U, 6U, 0U, 0U, 25U, 194U, 59U, 222U, 167U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 200U, 206U, 3U, 0U, 0U, 0U, 192U, 100U, 200U,
    MAX_uint8_T, 111U, 0U, 0U, 0U, 192U, 100U, 200U, 215U, 242U, 26U, 0U, 0U,
    192U, 100U, 200U, 100U, 220U, 169U, 0U, 0U, 192U, 100U, 200U, 92U, 72U,
    MAX_uint8_T, 70U, 0U, 192U, 100U, 200U, 92U, 0U, 171U, 219U, 7U, 192U, 100U,
    200U, 92U, 0U, 27U, 242U, 128U, 192U, 100U, 200U, 92U, 0U, 0U, 113U, 248U,
    223U, 100U, 200U, 92U, 0U, 0U, 3U, 208U, MAX_uint8_T, 100U, 200U, 92U, 0U,
    0U, 0U, 56U, 254U, 100U, 0U, 0U, 0U, 122U, 208U, 8U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 116U, 157U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 56U, 185U, 242U, 245U, 195U, 69U, 0U, 0U, 0U, 65U, 248U, 125U, 19U,
    13U, 107U, 249U, 85U, 0U, 1U, 216U, 167U, 0U, 0U, 0U, 0U, 143U, 234U, 8U,
    44U, MAX_uint8_T, 68U, 0U, 0U, 0U, 0U, 41U, MAX_uint8_T, 71U, 79U,
    MAX_uint8_T, 34U, 0U, 0U, 0U, 0U, 7U, 254U, 106U, 80U, MAX_uint8_T, 35U, 0U,
    0U, 0U, 0U, 8U, MAX_uint8_T, 106U, 43U, MAX_uint8_T, 70U, 0U, 0U, 0U, 0U,
    42U, MAX_uint8_T, 71U, 1U, 214U, 168U, 0U, 0U, 0U, 0U, 141U, 235U, 9U, 0U,
    63U, 247U, 122U, 17U, 14U, 106U, 249U, 88U, 0U, 0U, 0U, 55U, 187U, 244U,
    245U, 194U, 70U, 0U, 0U, 0U, 0U, 0U, 0U, 2U, 187U, 147U, 1U, 0U, 0U, 0U, 0U,
    0U, 0U, 130U, 142U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 56U, 185U, 242U, 245U, 195U, 69U, 0U, 0U, 0U, 65U, 248U, 125U, 19U,
    13U, 107U, 249U, 85U, 0U, 1U, 216U, 167U, 0U, 0U, 0U, 0U, 143U, 234U, 8U,
    44U, MAX_uint8_T, 68U, 0U, 0U, 0U, 0U, 41U, MAX_uint8_T, 71U, 79U,
    MAX_uint8_T, 34U, 0U, 0U, 0U, 0U, 7U, 254U, 106U, 80U, MAX_uint8_T, 35U, 0U,
    0U, 0U, 0U, 8U, MAX_uint8_T, 106U, 43U, MAX_uint8_T, 70U, 0U, 0U, 0U, 0U,
    42U, MAX_uint8_T, 71U, 1U, 214U, 168U, 0U, 0U, 0U, 0U, 141U, 235U, 9U, 0U,
    63U, 247U, 122U, 17U, 14U, 106U, 249U, 88U, 0U, 0U, 0U, 55U, 187U, 244U,
    245U, 194U, 70U, 0U, 0U, 0U, 0U, 0U, 27U, 229U, 234U, 44U, 0U, 0U, 0U, 0U,
    0U, 4U, 190U, 79U, 59U, 202U, 13U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 56U, 185U, 242U, 245U, 195U, 69U, 0U, 0U, 0U, 65U, 248U,
    125U, 19U, 13U, 107U, 249U, 85U, 0U, 1U, 216U, 167U, 0U, 0U, 0U, 0U, 143U,
    234U, 8U, 44U, MAX_uint8_T, 68U, 0U, 0U, 0U, 0U, 41U, MAX_uint8_T, 71U, 79U,
    MAX_uint8_T, 34U, 0U, 0U, 0U, 0U, 7U, 254U, 106U, 80U, MAX_uint8_T, 35U, 0U,
    0U, 0U, 0U, 8U, MAX_uint8_T, 106U, 43U, MAX_uint8_T, 70U, 0U, 0U, 0U, 0U,
    42U, MAX_uint8_T, 71U, 1U, 214U, 168U, 0U, 0U, 0U, 0U, 141U, 235U, 9U, 0U,
    63U, 247U, 122U, 17U, 14U, 106U, 249U, 88U, 0U, 0U, 0U, 55U, 187U, 244U,
    245U, 194U, 70U, 0U, 0U, 0U, 0U, 0U, 163U, 225U, 61U, 190U, 28U, 0U, 0U, 0U,
    0U, 4U, 212U, 48U, 212U, 191U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 56U, 185U, 242U, 245U, 195U, 69U, 0U, 0U, 0U, 65U, 248U,
    125U, 19U, 13U, 107U, 249U, 85U, 0U, 1U, 216U, 167U, 0U, 0U, 0U, 0U, 143U,
    234U, 8U, 44U, MAX_uint8_T, 68U, 0U, 0U, 0U, 0U, 41U, MAX_uint8_T, 71U, 79U,
    MAX_uint8_T, 34U, 0U, 0U, 0U, 0U, 7U, 254U, 106U, 80U, MAX_uint8_T, 35U, 0U,
    0U, 0U, 0U, 8U, MAX_uint8_T, 106U, 43U, MAX_uint8_T, 70U, 0U, 0U, 0U, 0U,
    42U, MAX_uint8_T, 71U, 1U, 214U, 168U, 0U, 0U, 0U, 0U, 141U, 235U, 9U, 0U,
    63U, 247U, 122U, 17U, 14U, 106U, 249U, 88U, 0U, 0U, 0U, 55U, 187U, 244U,
    245U, 194U, 70U, 0U, 0U, 0U, 0U, 0U, 192U, 88U, 60U, 220U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 56U, 185U, 242U, 245U, 195U, 69U,
    0U, 0U, 0U, 65U, 248U, 125U, 19U, 13U, 107U, 249U, 85U, 0U, 1U, 216U, 167U,
    0U, 0U, 0U, 0U, 143U, 234U, 8U, 44U, MAX_uint8_T, 68U, 0U, 0U, 0U, 0U, 41U,
    MAX_uint8_T, 71U, 79U, MAX_uint8_T, 34U, 0U, 0U, 0U, 0U, 7U, 254U, 106U, 80U,
    MAX_uint8_T, 35U, 0U, 0U, 0U, 0U, 8U, MAX_uint8_T, 106U, 43U, MAX_uint8_T,
    70U, 0U, 0U, 0U, 0U, 42U, MAX_uint8_T, 71U, 1U, 214U, 168U, 0U, 0U, 0U, 0U,
    141U, 235U, 9U, 0U, 63U, 247U, 122U, 17U, 14U, 106U, 249U, 88U, 0U, 0U, 0U,
    55U, 187U, 244U, 245U, 194U, 70U, 0U, 0U, 81U, 145U, 0U, 0U, 0U, 0U, 69U,
    156U, 3U, 178U, 146U, 0U, 0U, 69U, 223U, 33U, 0U, 10U, 201U, 146U, 69U, 234U,
    51U, 0U, 0U, 0U, 21U, 220U, 249U, 73U, 0U, 0U, 0U, 0U, 21U, 220U, 249U, 73U,
    0U, 0U, 0U, 10U, 201U, 147U, 70U, 235U, 51U, 0U, 3U, 178U, 147U, 0U, 0U, 69U,
    223U, 32U, 81U, 147U, 0U, 0U, 0U, 0U, 69U, 156U, 0U, 0U, 56U, 186U, 242U,
    238U, 188U, 94U, 217U, 23U, 0U, 65U, 248U, 124U, 18U, 20U, 120U, MAX_uint8_T,
    121U, 0U, 1U, 216U, 167U, 0U, 0U, 0U, 156U, 216U, 232U, 7U, 44U, MAX_uint8_T,
    68U, 0U, 0U, 93U, 183U, 42U, MAX_uint8_T, 70U, 79U, MAX_uint8_T, 34U, 0U,
    41U, 216U, 20U, 5U, 254U, 106U, 80U, MAX_uint8_T, 32U, 10U, 208U, 60U, 0U,
    8U, MAX_uint8_T, 106U, 43U, MAX_uint8_T, 69U, 160U, 119U, 0U, 0U, 42U,
    MAX_uint8_T, 71U, 0U, 214U, 218U, 182U, 1U, 0U, 0U, 143U, 234U, 8U, 0U, 97U,
    MAX_uint8_T, 143U, 24U, 13U, 107U, 249U, 85U, 0U, 11U, 211U, 101U, 180U,
    236U, 246U, 196U, 71U, 0U, 0U, 0U, 26U, 215U, 97U, 0U, 0U, 0U, 0U, 0U, 23U,
    202U, 47U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 220U, 120U, 0U, 0U, 0U, 76U,
    224U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U, 0U, 76U, 224U,
    220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U,
    120U, 0U, 0U, 0U, 76U, 224U, 214U, 128U, 0U, 0U, 0U, 82U, 219U, 184U, 166U,
    0U, 0U, 0U, 115U, 192U, 95U, 248U, 82U, 11U, 46U, 220U, 109U, 0U, 105U, 214U,
    246U, 220U, 123U, 3U, 0U, 0U, 0U, 59U, 231U, 48U, 0U, 0U, 0U, 21U, 206U, 45U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U,
    120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U,
    0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U,
    0U, 76U, 224U, 214U, 128U, 0U, 0U, 0U, 82U, 219U, 184U, 166U, 0U, 0U, 0U,
    115U, 192U, 95U, 248U, 82U, 11U, 46U, 220U, 109U, 0U, 105U, 214U, 246U, 220U,
    123U, 3U, 0U, 0U, 127U, 240U, 168U, 0U, 0U, 0U, 68U, 192U, 17U, 161U, 109U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U,
    120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U,
    0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U,
    0U, 76U, 224U, 214U, 128U, 0U, 0U, 0U, 82U, 219U, 184U, 166U, 0U, 0U, 0U,
    115U, 192U, 95U, 248U, 82U, 11U, 46U, 220U, 109U, 0U, 105U, 214U, 246U, 220U,
    123U, 3U, 0U, 76U, 204U, 0U, 200U, 80U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 220U,
    120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U,
    0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 220U, 120U, 0U, 0U,
    0U, 76U, 224U, 220U, 120U, 0U, 0U, 0U, 76U, 224U, 214U, 128U, 0U, 0U, 0U,
    82U, 219U, 184U, 166U, 0U, 0U, 0U, 115U, 192U, 95U, 248U, 82U, 11U, 46U,
    220U, 109U, 0U, 105U, 214U, 246U, 220U, 123U, 3U, 0U, 0U, 0U, 2U, 184U, 151U,
    1U, 0U, 0U, 0U, 0U, 126U, 146U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    155U, 224U, 8U, 0U, 0U, 0U, 156U, 160U, 22U, 241U, 124U, 0U, 0U, 60U, 236U,
    21U, 0U, 116U, 244U, 27U, 5U, 213U, 100U, 0U, 0U, 6U, 219U, 163U, 123U, 196U,
    1U, 0U, 0U, 0U, 78U, 254U, 244U, 45U, 0U, 0U, 0U, 0U, 0U, 208U, 163U, 0U, 0U,
    0U, 0U, 0U, 0U, 192U, 148U, 0U, 0U, 0U, 0U, 0U, 0U, 192U, 148U, 0U, 0U, 0U,
    0U, 0U, 0U, 192U, 148U, 0U, 0U, 0U, 0U, 0U, 0U, 192U, 148U, 0U, 0U, 0U, 200U,
    136U, 0U, 0U, 0U, 0U, 200U, 136U, 0U, 0U, 0U, 0U, 200U, MAX_uint8_T,
    MAX_uint8_T, 236U, 181U, 36U, 200U, 136U, 5U, 46U, 216U, 187U, 200U, 136U,
    0U, 0U, 128U, 234U, 200U, 136U, 0U, 0U, 154U, 213U, 200U, 136U, 11U, 86U,
    248U, 106U, 200U, MAX_uint8_T, 242U, 203U, 89U, 0U, 200U, 136U, 0U, 0U, 0U,
    0U, 200U, 136U, 0U, 0U, 0U, 0U, 31U, 198U, 246U, 214U, 64U, 0U, 0U, 146U,
    187U, 11U, 138U, 209U, 0U, 0U, 183U, 129U, 0U, 136U, 182U, 0U, 0U, 192U,
    128U, 26U, 242U, 59U, 0U, 0U, 192U, 128U, 117U, 179U, 0U, 0U, 0U, 192U, 128U,
    46U, 218U, 33U, 0U, 0U, 192U, 128U, 0U, 32U, 166U, 127U, 0U, 192U, 128U, 0U,
    0U, 0U, 224U, 72U, 192U, 128U, 121U, 66U, 32U, 242U, 74U, 192U, 128U, 40U,
    202U, 242U, 157U, 2U, 0U, 19U, 206U, 113U, 0U, 0U, 0U, 0U, 0U, 17U, 197U,
    58U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 43U, 181U, 242U, 220U, 70U, 0U,
    0U, 143U, 63U, 11U, 159U, 202U, 0U, 0U, 0U, 0U, 0U, 96U, 223U, 0U, 0U, 73U,
    191U, 236U, 253U, 224U, 0U, 38U, 251U, 99U, 14U, 96U, 224U, 0U, 70U, 248U,
    46U, 24U, 160U, 241U, 13U, 3U, 164U, 243U, 199U, 66U, 209U, 182U, 0U, 0U, 0U,
    47U, 232U, 58U, 0U, 0U, 0U, 14U, 203U, 55U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 43U, 181U, 242U, 220U, 70U, 0U, 0U, 143U, 63U, 11U, 159U, 202U, 0U,
    0U, 0U, 0U, 0U, 96U, 223U, 0U, 0U, 73U, 191U, 236U, 253U, 224U, 0U, 38U,
    251U, 99U, 14U, 96U, 224U, 0U, 70U, 248U, 46U, 24U, 160U, 241U, 13U, 3U,
    164U, 243U, 199U, 66U, 209U, 182U, 0U, 0U, 119U, 240U, 176U, 0U, 0U, 0U, 61U,
    196U, 18U, 154U, 117U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 43U, 181U, 242U,
    220U, 70U, 0U, 0U, 143U, 63U, 11U, 159U, 202U, 0U, 0U, 0U, 0U, 0U, 96U, 223U,
    0U, 0U, 73U, 191U, 236U, 253U, 224U, 0U, 38U, 251U, 99U, 14U, 96U, 224U, 0U,
    70U, 248U, 46U, 24U, 160U, 241U, 13U, 3U, 164U, 243U, 199U, 66U, 209U, 182U,
    0U, 40U, 235U, 162U, 62U, 168U, 0U, 0U, 117U, 106U, 122U, 241U, 82U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 43U, 181U, 242U, 220U, 70U, 0U, 0U, 143U, 63U,
    11U, 159U, 202U, 0U, 0U, 0U, 0U, 0U, 96U, 223U, 0U, 0U, 73U, 191U, 236U,
    253U, 224U, 0U, 38U, 251U, 99U, 14U, 96U, 224U, 0U, 70U, 248U, 46U, 24U,
    160U, 241U, 13U, 3U, 164U, 243U, 199U, 66U, 209U, 182U, 0U, 52U, 228U, 0U,
    176U, 104U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 43U, 181U, 242U, 220U, 70U,
    0U, 0U, 143U, 63U, 11U, 159U, 202U, 0U, 0U, 0U, 0U, 0U, 96U, 223U, 0U, 0U,
    73U, 191U, 236U, 253U, 224U, 0U, 38U, 251U, 99U, 14U, 96U, 224U, 0U, 70U,
    248U, 46U, 24U, 160U, 241U, 13U, 3U, 164U, 243U, 199U, 66U, 209U, 182U, 0U,
    0U, 102U, 242U, 149U, 0U, 0U, 0U, 0U, 173U, 30U, 176U, 3U, 0U, 0U, 0U, 105U,
    243U, 151U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 43U, 181U, 242U, 220U,
    70U, 0U, 0U, 143U, 63U, 11U, 159U, 202U, 0U, 0U, 0U, 0U, 0U, 96U, 223U, 0U,
    0U, 73U, 191U, 236U, 253U, 224U, 0U, 38U, 251U, 99U, 14U, 96U, 224U, 0U, 70U,
    248U, 46U, 24U, 160U, 241U, 13U, 3U, 164U, 243U, 199U, 66U, 209U, 182U, 0U,
    43U, 181U, 242U, 185U, 18U, 160U, 243U, 188U, 25U, 0U, 0U, 143U, 63U, 11U,
    159U, 222U, 122U, 13U, 158U, 171U, 0U, 0U, 0U, 0U, 0U, 96U, 251U, 7U, 0U,
    61U, 250U, 2U, 0U, 73U, 191U, 236U, 253U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 23U, 38U, 251U, 99U, 14U, 96U, 247U,
    8U, 0U, 0U, 0U, 0U, 70U, 248U, 46U, 30U, 170U, 231U, 160U, 26U, 0U, 0U, 0U,
    3U, 164U, 245U, 209U, 64U, 39U, 188U, 246U, MAX_uint8_T, MAX_uint8_T, 36U,
    0U, 20U, 158U, 229U, 228U, 91U, 0U, 0U, 191U, 214U, 46U, 26U, 153U, 0U, 37U,
    MAX_uint8_T, 76U, 0U, 0U, 0U, 0U, 65U, MAX_uint8_T, 37U, 0U, 0U, 0U, 0U, 30U,
    MAX_uint8_T, 77U, 0U, 0U, 0U, 0U, 0U, 173U, 216U, 49U, 21U, 143U, 7U, 0U,
    13U, 154U, 233U, 218U, 90U, 0U, 0U, 0U, 0U, 136U, 201U, 7U, 0U, 0U, 0U, 0U,
    11U, 203U, 49U, 0U, 0U, 0U, 0U, 247U, 200U, 7U, 0U, 0U, 24U, 213U, 101U, 0U,
    0U, 0U, 0U, 0U, 21U, 201U, 49U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 21U,
    173U, 240U, 210U, 55U, 0U, 0U, 191U, 154U, 13U, 101U, 224U, 4U, 37U,
    MAX_uint8_T, 32U, 0U, 1U, 248U, 51U, 65U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 78U, 31U, MAX_uint8_T, 33U, 0U, 0U,
    0U, 0U, 0U, 172U, 189U, 39U, 2U, 0U, 0U, 0U, 11U, 144U, 227U, MAX_uint8_T,
    MAX_uint8_T, 76U, 0U, 0U, 0U, 53U, 232U, 53U, 0U, 0U, 0U, 17U, 205U, 49U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 21U, 173U, 240U, 210U, 55U, 0U, 0U, 191U,
    154U, 13U, 101U, 224U, 4U, 37U, MAX_uint8_T, 32U, 0U, 1U, 248U, 51U, 65U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 78U, 31U,
    MAX_uint8_T, 33U, 0U, 0U, 0U, 0U, 0U, 172U, 189U, 39U, 2U, 0U, 0U, 0U, 11U,
    144U, 227U, MAX_uint8_T, MAX_uint8_T, 76U, 0U, 0U, 94U, 240U, 196U, 4U, 0U,
    0U, 44U, 204U, 26U, 133U, 141U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 21U,
    173U, 240U, 210U, 55U, 0U, 0U, 191U, 154U, 13U, 101U, 224U, 4U, 37U,
    MAX_uint8_T, 32U, 0U, 1U, 248U, 51U, 65U, MAX_uint8_T, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 78U, 31U, MAX_uint8_T, 33U, 0U, 0U,
    0U, 0U, 0U, 172U, 189U, 39U, 2U, 0U, 0U, 0U, 11U, 144U, 227U, MAX_uint8_T,
    MAX_uint8_T, 76U, 0U, 12U, MAX_uint8_T, 12U, 136U, 144U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 21U, 173U, 240U, 210U, 55U, 0U, 0U, 191U, 154U, 13U, 101U,
    224U, 4U, 37U, MAX_uint8_T, 32U, 0U, 1U, 248U, 51U, 65U, MAX_uint8_T,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, 78U, 31U, MAX_uint8_T,
    33U, 0U, 0U, 0U, 0U, 0U, 172U, 189U, 39U, 2U, 0U, 0U, 0U, 11U, 144U, 227U,
    MAX_uint8_T, MAX_uint8_T, 76U, 3U, 165U, 168U, 0U, 0U, 2U, 160U, 109U, 0U,
    0U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 192U, 128U, 0U, 0U, 192U, 128U, 0U,
    0U, 192U, 128U, 0U, 0U, 192U, 128U, 0U, 0U, 192U, 128U, 0U, 0U, 192U, 128U,
    0U, 14U, 218U, 106U, 0U, 171U, 100U, 0U, 0U, 0U, 0U, 0U, 0U, 192U, 128U, 0U,
    0U, 192U, 128U, 0U, 0U, 192U, 128U, 0U, 0U, 192U, 128U, 0U, 0U, 192U, 128U,
    0U, 0U, 192U, 128U, 0U, 0U, 192U, 128U, 0U, 0U, 56U, 236U, 223U, 19U, 0U,
    19U, 206U, 49U, 92U, 179U, 1U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 192U, 128U,
    0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 0U, 192U,
    128U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 0U,
    192U, 128U, 0U, 0U, 236U, 44U, 104U, 176U, 0U, 0U, 0U, 0U, 0U, 192U, 128U,
    0U, 0U, 192U, 128U, 0U, 0U, 192U, 128U, 0U, 0U, 192U, 128U, 0U, 0U, 192U,
    128U, 0U, 0U, 192U, 128U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 0U, 40U, 142U, 0U,
    0U, 0U, 75U, 242U, 207U, 225U, 48U, 0U, 0U, 0U, 1U, 22U, 215U, 228U, 209U,
    30U, 0U, 0U, 0U, 61U, 121U, 15U, 200U, 209U, 9U, 0U, 0U, 21U, 168U, 238U,
    242U, MAX_uint8_T, 124U, 0U, 0U, 192U, 187U, 26U, 28U, 195U, 222U, 0U, 41U,
    MAX_uint8_T, 47U, 0U, 0U, 68U, MAX_uint8_T, 10U, 70U, MAX_uint8_T, 15U, 0U,
    0U, 44U, MAX_uint8_T, 18U, 38U, MAX_uint8_T, 50U, 0U, 0U, 81U, 235U, 0U, 0U,
    190U, 188U, 25U, 37U, 210U, 123U, 0U, 0U, 20U, 166U, 236U, 237U, 141U, 4U,
    0U, 0U, 122U, 236U, 91U, 148U, 72U, 0U, 205U, 39U, 188U, 220U, 13U, 0U, 0U,
    0U, 0U, 0U, 0U, 192U, 132U, 142U, 240U, 225U, 66U, 192U, 238U, 117U, 12U,
    148U, 201U, 192U, 153U, 0U, 0U, 94U, 227U, 192U, 128U, 0U, 0U, 92U, 228U,
    192U, 128U, 0U, 0U, 92U, 228U, 192U, 128U, 0U, 0U, 92U, 228U, 192U, 128U, 0U,
    0U, 92U, 228U, 0U, 0U, 137U, 196U, 4U, 0U, 0U, 0U, 0U, 0U, 0U, 131U, 141U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 22U, 165U, 233U, 233U, 162U,
    19U, 0U, 0U, 192U, 178U, 23U, 25U, 182U, 186U, 0U, 37U, MAX_uint8_T, 43U, 0U,
    0U, 48U, MAX_uint8_T, 32U, 66U, MAX_uint8_T, 15U, 0U, 0U, 19U, MAX_uint8_T,
    61U, 36U, MAX_uint8_T, 43U, 0U, 0U, 49U, MAX_uint8_T, 31U, 0U, 190U, 177U,
    23U, 26U, 183U, 186U, 0U, 0U, 21U, 165U, 235U, 232U, 161U, 19U, 0U, 0U, 0U,
    0U, 5U, 200U, 132U, 0U, 0U, 0U, 0U, 0U, 146U, 127U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 22U, 165U, 233U, 233U, 162U, 19U, 0U, 0U, 192U, 178U,
    23U, 25U, 182U, 186U, 0U, 37U, MAX_uint8_T, 43U, 0U, 0U, 48U, MAX_uint8_T,
    32U, 66U, MAX_uint8_T, 15U, 0U, 0U, 19U, MAX_uint8_T, 61U, 36U, MAX_uint8_T,
    43U, 0U, 0U, 49U, MAX_uint8_T, 31U, 0U, 190U, 177U, 23U, 26U, 183U, 186U, 0U,
    0U, 21U, 165U, 235U, 232U, 161U, 19U, 0U, 0U, 0U, 36U, 233U, 232U, 33U, 0U,
    0U, 0U, 9U, 198U, 67U, 70U, 195U, 7U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    22U, 165U, 233U, 233U, 162U, 19U, 0U, 0U, 192U, 178U, 23U, 25U, 182U, 186U,
    0U, 37U, MAX_uint8_T, 43U, 0U, 0U, 48U, MAX_uint8_T, 32U, 66U, MAX_uint8_T,
    15U, 0U, 0U, 19U, MAX_uint8_T, 61U, 36U, MAX_uint8_T, 43U, 0U, 0U, 49U,
    MAX_uint8_T, 31U, 0U, 190U, 177U, 23U, 26U, 183U, 186U, 0U, 0U, 21U, 165U,
    235U, 232U, 161U, 19U, 0U, 0U, 0U, 179U, 219U, 53U, 205U, 13U, 0U, 0U, 17U,
    201U, 55U, 219U, 175U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 22U, 165U,
    233U, 233U, 162U, 19U, 0U, 0U, 192U, 178U, 23U, 25U, 182U, 186U, 0U, 37U,
    MAX_uint8_T, 43U, 0U, 0U, 48U, MAX_uint8_T, 32U, 66U, MAX_uint8_T, 15U, 0U,
    0U, 19U, MAX_uint8_T, 61U, 36U, MAX_uint8_T, 43U, 0U, 0U, 49U, MAX_uint8_T,
    31U, 0U, 190U, 177U, 23U, 26U, 183U, 186U, 0U, 0U, 21U, 165U, 235U, 232U,
    161U, 19U, 0U, 0U, 0U, 208U, 72U, 76U, 204U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 22U, 165U, 233U, 233U, 162U, 19U, 0U, 0U, 192U, 178U, 23U, 25U,
    182U, 186U, 0U, 37U, MAX_uint8_T, 43U, 0U, 0U, 48U, MAX_uint8_T, 32U, 66U,
    MAX_uint8_T, 15U, 0U, 0U, 19U, MAX_uint8_T, 61U, 36U, MAX_uint8_T, 43U, 0U,
    0U, 49U, MAX_uint8_T, 31U, 0U, 190U, 177U, 23U, 26U, 183U, 186U, 0U, 0U, 21U,
    165U, 235U, 232U, 161U, 19U, 0U, 0U, 0U, 0U, 156U, 244U, 0U, 0U, 0U, 0U, 0U,
    0U, 156U, 244U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 152U,
    MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T, MAX_uint8_T,
    236U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 156U, 244U, 0U, 0U, 0U, 0U,
    0U, 0U, 156U, 244U, 0U, 0U, 0U, 0U, 20U, 163U, 233U, 239U, 169U, 193U, 12U,
    0U, 190U, 178U, 24U, 33U, 241U, 183U, 0U, 37U, MAX_uint8_T, 42U, 0U, 161U,
    129U, MAX_uint8_T, 31U, 66U, MAX_uint8_T, 13U, 122U, 121U, 18U, MAX_uint8_T,
    62U, 38U, MAX_uint8_T, 126U, 161U, 0U, 47U, MAX_uint8_T, 32U, 0U, 190U, 241U,
    32U, 24U, 181U, 185U, 0U, 13U, 194U, 170U, 240U, 234U, 162U, 19U, 0U, 0U,
    137U, 196U, 4U, 0U, 0U, 0U, 0U, 131U, 141U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    212U, 108U, 0U, 0U, 112U, 208U, 212U, 108U, 0U, 0U, 112U, 208U, 212U, 108U,
    0U, 0U, 112U, 208U, 212U, 108U, 0U, 0U, 112U, 208U, 211U, 109U, 0U, 0U, 137U,
    208U, 186U, 161U, 11U, 104U, 235U, 208U, 55U, 220U, 242U, 151U, 119U, 208U,
    0U, 0U, 5U, 200U, 132U, 0U, 0U, 0U, 146U, 127U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 212U, 108U, 0U, 0U, 112U, 208U, 212U, 108U, 0U, 0U, 112U, 208U, 212U,
    108U, 0U, 0U, 112U, 208U, 212U, 108U, 0U, 0U, 112U, 208U, 211U, 109U, 0U, 0U,
    137U, 208U, 186U, 161U, 11U, 104U, 235U, 208U, 55U, 220U, 242U, 151U, 119U,
    208U, 0U, 36U, 233U, 232U, 33U, 0U, 9U, 198U, 67U, 70U, 195U, 7U, 0U, 0U, 0U,
    0U, 0U, 0U, 212U, 108U, 0U, 0U, 112U, 208U, 212U, 108U, 0U, 0U, 112U, 208U,
    212U, 108U, 0U, 0U, 112U, 208U, 212U, 108U, 0U, 0U, 112U, 208U, 211U, 109U,
    0U, 0U, 137U, 208U, 186U, 161U, 11U, 104U, 235U, 208U, 55U, 220U, 242U, 151U,
    119U, 208U, 0U, 208U, 72U, 76U, 204U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 212U, 108U,
    0U, 0U, 112U, 208U, 212U, 108U, 0U, 0U, 112U, 208U, 212U, 108U, 0U, 0U, 112U,
    208U, 212U, 108U, 0U, 0U, 112U, 208U, 211U, 109U, 0U, 0U, 137U, 208U, 186U,
    161U, 11U, 104U, 235U, 208U, 55U, 220U, 242U, 151U, 119U, 208U, 0U, 0U, 0U,
    94U, 217U, 27U, 0U, 0U, 0U, 44U, 204U, 24U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 180U, 163U, 0U, 0U, 0U, 171U, 135U, 82U, 246U, 14U, 0U, 22U, 249U, 39U,
    5U, 235U, 100U, 0U, 119U, 198U, 0U, 0U, 144U, 197U, 1U, 219U, 102U, 0U, 0U,
    47U, MAX_uint8_T, 104U, 246U, 15U, 0U, 0U, 0U, 206U, 248U, 165U, 0U, 0U, 0U,
    0U, 109U, MAX_uint8_T, 69U, 0U, 0U, 0U, 0U, 108U, 226U, 2U, 0U, 0U, 0U, 0U,
    202U, 132U, 0U, 0U, 0U, 0U, 40U, MAX_uint8_T, 36U, 0U, 0U, 0U, 192U, 128U,
    0U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U,
    0U, 0U, 192U, 136U, 158U, 244U, 219U, 81U, 0U, 192U, 227U, 87U, 11U, 113U,
    248U, 28U, 192U, 132U, 0U, 0U, 2U, 242U, 97U, 192U, 128U, 0U, 0U, 0U, 227U,
    113U, 192U, 159U, 0U, 0U, 9U, 249U, 80U, 192U, 224U, 104U, 14U, 137U, 227U,
    7U, 192U, 130U, 153U, 247U, 207U, 53U, 0U, 192U, 128U, 0U, 0U, 0U, 0U, 0U,
    192U, 128U, 0U, 0U, 0U, 0U, 0U, 192U, 128U, 0U, 0U, 0U, 0U, 0U, 0U, 80U,
    200U, 0U, 204U, 76U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 180U, 163U, 0U, 0U, 0U,
    171U, 135U, 82U, 246U, 14U, 0U, 22U, 249U, 39U, 5U, 235U, 100U, 0U, 119U,
    198U, 0U, 0U, 144U, 197U, 1U, 219U, 102U, 0U, 0U, 47U, MAX_uint8_T, 104U,
    246U, 15U, 0U, 0U, 0U, 206U, 248U, 165U, 0U, 0U, 0U, 0U, 109U, MAX_uint8_T,
    69U, 0U, 0U, 0U, 0U, 108U, 226U, 2U, 0U, 0U, 0U, 0U, 202U, 132U, 0U, 0U, 0U,
    0U, 40U, MAX_uint8_T, 36U, 0U, 0U, 0U };

  int32_T b_num_tmp;
  uint8_T b_thisGlyphBitmap_data[156];
  uint8_T c_thisGlyphBitmap_data[169];
  real_T cg;
  uint8_T glyphVal;
  uint16_T x;
  uint16_T tmp3;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_boolean_T(&isNewLineChar, 2, true);
  imSize_idx_0 = imgIn->size[0];
  imSize_idx_1 = imgIn->size[1];
  penX = textLocationXY_x;
  penY = textLocationXY_y + 13;
  i = isNewLineChar->size[0] * isNewLineChar->size[1];
  isNewLineChar->size[0] = 1;
  isNewLineChar->size[1] = ucTextU16->size[1];
  emxEnsureCapacity_boolean_T(isNewLineChar, i);
  bitmapEndIdx_1b = ucTextU16->size[0] * ucTextU16->size[1];
  for (i = 0; i < bitmapEndIdx_1b; i++) {
    isNewLineChar->data[i] = (ucTextU16->data[i] == 10);
  }

  i = ucTextU16->size[1];
  for (b_i = 0; b_i < i; b_i++) {
    if (isNewLineChar->data[b_i]) {
      penY += 15;
      penX = textLocationXY_x;
    } else {
      thisGlyphIdx = uv[(uint16_T)(ucTextU16->data[b_i] + 1U) - 1];
      if (thisGlyphIdx == 0) {
        penX += 4;
      } else {
        xx = penX + b_iv[thisGlyphIdx];
        yy = penY - iv1[thisGlyphIdx];
        endR_im = (yy + (uint16_T)iv2[thisGlyphIdx]) - 1;
        bitmapEndIdx_1b = iv3[thisGlyphIdx];
        endC_im = (xx + bitmapEndIdx_1b) - 1;
        if ((yy <= imSize_idx_0) && (endR_im >= 1) && (xx <= imSize_idx_1) &&
            (endC_im >= 1)) {
          glIdx_startR_gl = 1;
          glIdx_startC_gl = 1;
          glIdx_endR_gl = (uint16_T)iv2[thisGlyphIdx];
          glIdx_endC_gl = bitmapEndIdx_1b;
          if (yy < 1) {
            glIdx_startR_gl = 2 - yy;
            yy = 1;
          }

          if (endR_im > imSize_idx_0) {
            glIdx_endR_gl = ((uint16_T)iv2[thisGlyphIdx] - endR_im) +
              imSize_idx_0;
            endR_im = imSize_idx_0;
          }

          if (xx < 1) {
            glIdx_startC_gl = 2 - xx;
            xx = 1;
          }

          if (endC_im > imSize_idx_1) {
            glIdx_endC_gl = (bitmapEndIdx_1b - endC_im) + imSize_idx_1;
            endC_im = imSize_idx_1;
          }

          bitmapEndIdx_1b = (int32_T)((uint32_T)iv4[thisGlyphIdx] +
            bitmapEndIdx_1b * (uint16_T)iv2[thisGlyphIdx]);
          if (iv4[thisGlyphIdx] + 1U > (uint32_T)bitmapEndIdx_1b) {
            i1 = 0;
            bitmapEndIdx_1b = 0;
          } else {
            i1 = iv4[thisGlyphIdx];
          }

          bitmapEndIdx_1b -= i1;
          for (i2 = 0; i2 < bitmapEndIdx_1b; i2++) {
            thisGlyphBitmap_data[i2] = b_uv[i1 + i2];
          }

          num_tmp = iv3[thisGlyphIdx];
          b_num_tmp = iv2[thisGlyphIdx];
          for (i1 = 0; i1 < num_tmp; i1++) {
            bitmapEndIdx_1b = (uint16_T)iv2[thisGlyphIdx];
            for (i2 = 0; i2 < bitmapEndIdx_1b; i2++) {
              c_thisGlyphBitmap_data[i2 + b_num_tmp * i1] =
                thisGlyphBitmap_data[i1 + num_tmp * i2];
            }
          }

          bitmapEndIdx_1b = iv2[thisGlyphIdx] * iv3[thisGlyphIdx];
          if (0 <= bitmapEndIdx_1b - 1) {
            memcpy(&b_thisGlyphBitmap_data[0], &c_thisGlyphBitmap_data[0],
                   bitmapEndIdx_1b * sizeof(uint8_T));
          }

          if (glIdx_startR_gl > glIdx_endR_gl) {
            glIdx_startR_gl = 1;
          }

          if (glIdx_startC_gl > glIdx_endC_gl) {
            i1 = -1;
          } else {
            i1 = glIdx_startC_gl - 2;
          }

          for (num_tmp = 0; num_tmp < 3; num_tmp++) {
            cg = 1.0;
            for (glIdx_startC_gl = xx; glIdx_startC_gl <= endC_im;
                 glIdx_startC_gl++) {
              bitmapEndIdx_1b = 0;
              for (glIdx_endR_gl = yy; glIdx_endR_gl <= endR_im; glIdx_endR_gl++)
              {
                glyphVal = b_thisGlyphBitmap_data[((glIdx_startR_gl +
                  bitmapEndIdx_1b) + b_num_tmp * (i1 + (int32_T)cg)) - 1];
                if (glyphVal == 255) {
                  imgIn->data[((glIdx_endR_gl + imgIn->size[0] *
                                (glIdx_startC_gl - 1)) + imgIn->size[0] *
                               imgIn->size[1] * num_tmp) - 1] =
                    textColor_data[num_tmp];
                } else {
                  if (glyphVal != 0) {
                    x = (uint16_T)((uint32_T)(imgIn->data[((glIdx_endR_gl +
                      imgIn->size[0] * (glIdx_startC_gl - 1)) + imgIn->size[0] *
                      imgIn->size[1] * num_tmp) - 1] * (255 - glyphVal)) +
                                   textColor_data[num_tmp] * glyphVal);
                    tmp3 = (uint16_T)(x / 255U);
                    x = (uint16_T)((uint32_T)x - tmp3 * 255);
                    if ((x > 0) && (x >= 128)) {
                      tmp3++;
                    }

                    imgIn->data[((glIdx_endR_gl + imgIn->size[0] *
                                  (glIdx_startC_gl - 1)) + imgIn->size[0] *
                                 imgIn->size[1] * num_tmp) - 1] = (uint8_T)tmp3;
                  }
                }

                bitmapEndIdx_1b++;
              }

              cg++;
            }
          }
        }

        penX += iv[thisGlyphIdx];
      }
    }
  }

  emxFree_boolean_T(&isNewLineChar);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (insertTextNoValidation.c) */
