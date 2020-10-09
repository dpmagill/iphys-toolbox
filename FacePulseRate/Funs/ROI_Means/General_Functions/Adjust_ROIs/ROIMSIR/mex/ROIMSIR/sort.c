/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sort.c
 *
 * Code generation for function 'sort'
 *
 */

/* Include files */
#include "sort.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include <string.h>

/* Function Definitions */
void sort(int16_T x_data[], const int32_T x_size[2])
{
  int32_T idx_data[458];
  int32_T b_iwork_data[229];
  int32_T iwork_data[229];
  int32_T b_i;
  int32_T b_n;
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T idx_size_idx_0;
  int32_T j;
  int32_T k;
  int32_T loop_ub;
  int32_T n;
  int32_T nDone;
  int32_T nLeft;
  int32_T nQuartets;
  int32_T offset;
  int32_T quartetOffset;
  int16_T b_xwork_data[229];
  int16_T xwork_data[229];
  int16_T idx4[4];
  int16_T x4[4];
  int16_T b_x4_tmp;
  int16_T c_x4_tmp;
  int16_T x4_tmp;
  int8_T perm[4];
  uint8_T unnamed_idx_0;
  n = x_size[0];
  unnamed_idx_0 = (uint8_T)x_size[0];
  idx_size_idx_0 = unnamed_idx_0;
  loop_ub = unnamed_idx_0 << 1;
  if (0 <= loop_ub - 1) {
    memset(&idx_data[0], 0, loop_ub * sizeof(int32_T));
  }

  if (x_size[0] != 0) {
    b_n = x_size[0];
    loop_ub = x_size[0];
    nQuartets = x_size[0] >> 2;
    nDone = nQuartets << 2;
    nLeft = x_size[0] - nDone;
    for (k = 0; k < 2; k++) {
      offset = k * n;
      x4[0] = 0;
      idx4[0] = 0;
      x4[1] = 0;
      idx4[1] = 0;
      x4[2] = 0;
      idx4[2] = 0;
      x4[3] = 0;
      idx4[3] = 0;
      if (0 <= idx_size_idx_0 - 1) {
        memset(&iwork_data[0], 0, idx_size_idx_0 * sizeof(int32_T));
      }

      if (0 <= loop_ub - 1) {
        memset(&xwork_data[0], 0, loop_ub * sizeof(int16_T));
      }

      for (j = 0; j < nQuartets; j++) {
        i = j << 2;
        quartetOffset = offset + i;
        idx4[0] = (int16_T)(i + 1);
        idx4[1] = (int16_T)(i + 2);
        idx4[2] = (int16_T)(i + 3);
        idx4[3] = (int16_T)(i + 4);
        x4[0] = x_data[quartetOffset];
        x4_tmp = x_data[quartetOffset + 1];
        x4[1] = x4_tmp;
        b_x4_tmp = x_data[quartetOffset + 2];
        x4[2] = b_x4_tmp;
        c_x4_tmp = x_data[quartetOffset + 3];
        x4[3] = c_x4_tmp;
        if (x_data[quartetOffset] <= x4_tmp) {
          i = 1;
          i2 = 2;
        } else {
          i = 2;
          i2 = 1;
        }

        if (b_x4_tmp <= c_x4_tmp) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }

        b_i = x4[i - 1];
        i1 = x4[i3 - 1];
        if (b_i <= i1) {
          b_i = x4[i2 - 1];
          if (b_i <= i1) {
            perm[0] = (int8_T)i;
            perm[1] = (int8_T)i2;
            perm[2] = (int8_T)i3;
            perm[3] = (int8_T)i4;
          } else if (b_i <= x4[i4 - 1]) {
            perm[0] = (int8_T)i;
            perm[1] = (int8_T)i3;
            perm[2] = (int8_T)i2;
            perm[3] = (int8_T)i4;
          } else {
            perm[0] = (int8_T)i;
            perm[1] = (int8_T)i3;
            perm[2] = (int8_T)i4;
            perm[3] = (int8_T)i2;
          }
        } else {
          i1 = x4[i4 - 1];
          if (b_i <= i1) {
            if (x4[i2 - 1] <= i1) {
              perm[0] = (int8_T)i3;
              perm[1] = (int8_T)i;
              perm[2] = (int8_T)i2;
              perm[3] = (int8_T)i4;
            } else {
              perm[0] = (int8_T)i3;
              perm[1] = (int8_T)i;
              perm[2] = (int8_T)i4;
              perm[3] = (int8_T)i2;
            }
          } else {
            perm[0] = (int8_T)i3;
            perm[1] = (int8_T)i4;
            perm[2] = (int8_T)i;
            perm[3] = (int8_T)i2;
          }
        }

        idx_data[quartetOffset] = idx4[perm[0] - 1];
        idx_data[quartetOffset + 1] = idx4[perm[1] - 1];
        idx_data[quartetOffset + 2] = idx4[perm[2] - 1];
        idx_data[quartetOffset + 3] = idx4[perm[3] - 1];
        x_data[quartetOffset] = x4[perm[0] - 1];
        x_data[quartetOffset + 1] = x4[perm[1] - 1];
        x_data[quartetOffset + 2] = x4[perm[2] - 1];
        x_data[quartetOffset + 3] = x4[perm[3] - 1];
      }

      i = offset + nDone;
      if (nLeft > 0) {
        for (i2 = 0; i2 < nLeft; i2++) {
          idx4[i2] = (int16_T)((nDone + i2) + 1);
          x4[i2] = x_data[i + i2];
        }

        perm[1] = 0;
        perm[2] = 0;
        perm[3] = 0;
        if (nLeft == 1) {
          perm[0] = 1;
        } else if (nLeft == 2) {
          if (x4[0] <= x4[1]) {
            perm[0] = 1;
            perm[1] = 2;
          } else {
            perm[0] = 2;
            perm[1] = 1;
          }
        } else if (x4[0] <= x4[1]) {
          if (x4[1] <= x4[2]) {
            perm[0] = 1;
            perm[1] = 2;
            perm[2] = 3;
          } else if (x4[0] <= x4[2]) {
            perm[0] = 1;
            perm[1] = 3;
            perm[2] = 2;
          } else {
            perm[0] = 3;
            perm[1] = 1;
            perm[2] = 2;
          }
        } else if (x4[0] <= x4[2]) {
          perm[0] = 2;
          perm[1] = 1;
          perm[2] = 3;
        } else if (x4[1] <= x4[2]) {
          perm[0] = 2;
          perm[1] = 3;
          perm[2] = 1;
        } else {
          perm[0] = 3;
          perm[1] = 2;
          perm[2] = 1;
        }

        for (i2 = 0; i2 < nLeft; i2++) {
          b_i = perm[i2] - 1;
          i1 = i + i2;
          idx_data[i1] = idx4[b_i];
          x_data[i1] = x4[b_i];
        }
      }

      if (b_n > 1) {
        i4 = b_n >> 2;
        i3 = 4;
        while (i4 > 1) {
          if ((i4 & 1) != 0) {
            i4--;
            i = i3 * i4;
            i2 = b_n - i;
            if (i2 > i3) {
              merge(idx_data, x_data, offset + i, i3, i2 - i3, iwork_data,
                    xwork_data);
            }
          }

          i = i3 << 1;
          i4 >>= 1;
          for (i2 = 0; i2 < i4; i2++) {
            merge(idx_data, x_data, offset + i2 * i, i3, i3, iwork_data,
                  xwork_data);
          }

          i3 = i;
        }

        if (b_n > i3) {
          if (0 <= idx_size_idx_0 - 1) {
            memcpy(&b_iwork_data[0], &iwork_data[0], idx_size_idx_0 * sizeof
                   (int32_T));
          }

          if (0 <= loop_ub - 1) {
            memcpy(&b_xwork_data[0], &xwork_data[0], loop_ub * sizeof(int16_T));
          }

          merge(idx_data, x_data, offset, i3, b_n - i3, b_iwork_data,
                b_xwork_data);
        }
      }
    }
  }
}

/* End of code generation (sort.c) */
