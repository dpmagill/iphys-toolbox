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
#include "mwmathutil.h"
#include <string.h>

/* Function Definitions */
void b_sort(real_T x_data[], const int32_T x_size[1], int32_T idx_data[],
            int32_T idx_size[1])
{
  real_T b_xwork_data[400];
  real_T vwork_data[400];
  real_T xwork_data[400];
  real_T xwork[256];
  real_T x4[4];
  real_T d;
  real_T d1;
  int32_T b_iwork_data[400];
  int32_T iidx_data[400];
  int32_T iwork_data[400];
  int32_T b;
  int32_T bLen;
  int32_T bLen2;
  int32_T b_b;
  int32_T dim;
  int32_T exitg1;
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T iidx_tmp;
  int32_T iwork_size_idx_0;
  int32_T j;
  int32_T k;
  int32_T nBlocks;
  int32_T nNonNaN;
  int32_T nPairs;
  int32_T vlen;
  int32_T vstride;
  int32_T vwork_size_idx_0;
  int16_T iwork[256];
  int16_T idx4[4];
  int8_T perm[4];
  dim = 0;
  if (x_size[0] != 1) {
    dim = -1;
  }

  if (dim + 2 <= 1) {
    vwork_size_idx_0 = x_size[0];
  } else {
    vwork_size_idx_0 = 1;
  }

  vlen = vwork_size_idx_0 - 1;
  idx_size[0] = x_size[0];
  vstride = 1;
  for (k = 0; k <= dim; k++) {
    vstride *= x_size[0];
  }

  for (j = 0; j < vstride; j++) {
    for (k = 0; k <= vlen; k++) {
      vwork_data[k] = x_data[j + k * vstride];
    }

    dim = (int16_T)vwork_size_idx_0;
    x4[0] = 0.0;
    idx4[0] = 0;
    x4[1] = 0.0;
    idx4[1] = 0;
    x4[2] = 0.0;
    idx4[2] = 0;
    x4[3] = 0.0;
    idx4[3] = 0;
    iwork_size_idx_0 = (int16_T)vwork_size_idx_0;
    if (0 <= dim - 1) {
      memset(&iidx_data[0], 0, dim * sizeof(int32_T));
      memset(&iwork_data[0], 0, dim * sizeof(int32_T));
    }

    if (0 <= vwork_size_idx_0 - 1) {
      memset(&xwork_data[0], 0, vwork_size_idx_0 * sizeof(real_T));
    }

    bLen = 0;
    dim = -1;
    for (k = 0; k < vwork_size_idx_0; k++) {
      if (muDoubleScalarIsNaN(vwork_data[k])) {
        iidx_tmp = (vwork_size_idx_0 - bLen) - 1;
        iidx_data[iidx_tmp] = k + 1;
        xwork_data[iidx_tmp] = vwork_data[k];
        bLen++;
      } else {
        dim++;
        idx4[dim] = (int16_T)(k + 1);
        x4[dim] = vwork_data[k];
        if (dim + 1 == 4) {
          dim = k - bLen;
          if (x4[0] <= x4[1]) {
            i1 = 1;
            i2 = 2;
          } else {
            i1 = 2;
            i2 = 1;
          }

          if (x4[2] <= x4[3]) {
            i3 = 3;
            i4 = 4;
          } else {
            i3 = 4;
            i4 = 3;
          }

          d = x4[i1 - 1];
          d1 = x4[i3 - 1];
          if (d <= d1) {
            d = x4[i2 - 1];
            if (d <= d1) {
              perm[0] = (int8_T)i1;
              perm[1] = (int8_T)i2;
              perm[2] = (int8_T)i3;
              perm[3] = (int8_T)i4;
            } else if (d <= x4[i4 - 1]) {
              perm[0] = (int8_T)i1;
              perm[1] = (int8_T)i3;
              perm[2] = (int8_T)i2;
              perm[3] = (int8_T)i4;
            } else {
              perm[0] = (int8_T)i1;
              perm[1] = (int8_T)i3;
              perm[2] = (int8_T)i4;
              perm[3] = (int8_T)i2;
            }
          } else {
            d1 = x4[i4 - 1];
            if (d <= d1) {
              if (x4[i2 - 1] <= d1) {
                perm[0] = (int8_T)i3;
                perm[1] = (int8_T)i1;
                perm[2] = (int8_T)i2;
                perm[3] = (int8_T)i4;
              } else {
                perm[0] = (int8_T)i3;
                perm[1] = (int8_T)i1;
                perm[2] = (int8_T)i4;
                perm[3] = (int8_T)i2;
              }
            } else {
              perm[0] = (int8_T)i3;
              perm[1] = (int8_T)i4;
              perm[2] = (int8_T)i1;
              perm[3] = (int8_T)i2;
            }
          }

          iidx_data[dim - 3] = idx4[perm[0] - 1];
          iidx_data[dim - 2] = idx4[perm[1] - 1];
          iidx_data[dim - 1] = idx4[perm[2] - 1];
          iidx_data[dim] = idx4[perm[3] - 1];
          vwork_data[dim - 3] = x4[perm[0] - 1];
          vwork_data[dim - 2] = x4[perm[1] - 1];
          vwork_data[dim - 1] = x4[perm[2] - 1];
          vwork_data[dim] = x4[perm[3] - 1];
          dim = -1;
        }
      }
    }

    i3 = (vwork_size_idx_0 - bLen) - 1;
    if (dim + 1 > 0) {
      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (dim + 1 == 1) {
        perm[0] = 1;
      } else if (dim + 1 == 2) {
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

      for (k = 0; k <= dim; k++) {
        iidx_tmp = perm[k] - 1;
        i1 = (i3 - dim) + k;
        iidx_data[i1] = idx4[iidx_tmp];
        vwork_data[i1] = x4[iidx_tmp];
      }
    }

    dim = (bLen >> 1) + 1;
    for (k = 0; k <= dim - 2; k++) {
      i1 = (i3 + k) + 1;
      i2 = iidx_data[i1];
      iidx_tmp = (vwork_size_idx_0 - k) - 1;
      iidx_data[i1] = iidx_data[iidx_tmp];
      iidx_data[iidx_tmp] = i2;
      vwork_data[i1] = xwork_data[iidx_tmp];
      vwork_data[iidx_tmp] = xwork_data[i1];
    }

    if ((bLen & 1) != 0) {
      dim += i3;
      vwork_data[dim] = xwork_data[dim];
    }

    nNonNaN = vwork_size_idx_0 - bLen;
    dim = 2;
    if (nNonNaN > 1) {
      if (vwork_size_idx_0 >= 256) {
        nBlocks = nNonNaN >> 8;
        if (nBlocks > 0) {
          for (b = 0; b < nBlocks; b++) {
            i4 = (b << 8) - 1;
            for (b_b = 0; b_b < 6; b_b++) {
              bLen = 1 << (b_b + 2);
              bLen2 = bLen << 1;
              nPairs = 256 >> (b_b + 3);
              for (k = 0; k < nPairs; k++) {
                i2 = (i4 + k * bLen2) + 1;
                for (i1 = 0; i1 < bLen2; i1++) {
                  dim = i2 + i1;
                  iwork[i1] = (int16_T)iidx_data[dim];
                  xwork[i1] = vwork_data[dim];
                }

                i3 = 0;
                i1 = bLen;
                dim = i2 - 1;
                do {
                  exitg1 = 0;
                  dim++;
                  if (xwork[i3] <= xwork[i1]) {
                    iidx_data[dim] = iwork[i3];
                    vwork_data[dim] = xwork[i3];
                    if (i3 + 1 < bLen) {
                      i3++;
                    } else {
                      exitg1 = 1;
                    }
                  } else {
                    iidx_data[dim] = iwork[i1];
                    vwork_data[dim] = xwork[i1];
                    if (i1 + 1 < bLen2) {
                      i1++;
                    } else {
                      dim -= i3;
                      for (i1 = i3 + 1; i1 <= bLen; i1++) {
                        iidx_tmp = dim + i1;
                        iidx_data[iidx_tmp] = iwork[i1 - 1];
                        vwork_data[iidx_tmp] = xwork[i1 - 1];
                      }

                      exitg1 = 1;
                    }
                  }
                } while (exitg1 == 0);
              }
            }
          }

          dim = nBlocks << 8;
          i1 = nNonNaN - dim;
          if (i1 > 0) {
            b_merge_block(iidx_data, vwork_data, dim, i1, 2, iwork_data,
                          xwork_data);
          }

          dim = 8;
        }
      }

      if (0 <= iwork_size_idx_0 - 1) {
        memcpy(&b_iwork_data[0], &iwork_data[0], iwork_size_idx_0 * sizeof
               (int32_T));
      }

      if (0 <= vwork_size_idx_0 - 1) {
        memcpy(&b_xwork_data[0], &xwork_data[0], vwork_size_idx_0 * sizeof
               (real_T));
      }

      b_merge_block(iidx_data, vwork_data, 0, nNonNaN, dim, b_iwork_data,
                    b_xwork_data);
    }

    for (k = 0; k <= vlen; k++) {
      dim = j + k * vstride;
      x_data[dim] = vwork_data[k];
      idx_data[dim] = iidx_data[k];
    }
  }
}

void c_sort(real32_T x_data[], const int32_T x_size[1], int32_T idx_data[],
            int32_T idx_size[1])
{
  int32_T iidx_data[400];
  int32_T iwork_data[400];
  int32_T b;
  int32_T bLen;
  int32_T bLen2;
  int32_T b_b;
  int32_T dim;
  int32_T exitg1;
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T iidx_tmp;
  int32_T j;
  int32_T k;
  int32_T nBlocks;
  int32_T nNaNs;
  int32_T nNonNaN;
  int32_T nPairs;
  int32_T vlen;
  int32_T vstride;
  int32_T vwork_size_idx_0;
  real32_T vwork_data[400];
  real32_T xwork_data[400];
  real32_T xwork[256];
  real32_T x4[4];
  real32_T f;
  real32_T f1;
  int16_T iwork[256];
  int16_T idx4[4];
  int8_T perm[4];
  dim = 0;
  if (x_size[0] != 1) {
    dim = -1;
  }

  if (dim + 2 <= 1) {
    vwork_size_idx_0 = x_size[0];
  } else {
    vwork_size_idx_0 = 1;
  }

  vlen = vwork_size_idx_0 - 1;
  idx_size[0] = x_size[0];
  vstride = 1;
  for (k = 0; k <= dim; k++) {
    vstride *= x_size[0];
  }

  for (j = 0; j < vstride; j++) {
    for (k = 0; k <= vlen; k++) {
      vwork_data[k] = x_data[j + k * vstride];
    }

    dim = (int16_T)vwork_size_idx_0;
    x4[0] = 0.0F;
    idx4[0] = 0;
    x4[1] = 0.0F;
    idx4[1] = 0;
    x4[2] = 0.0F;
    idx4[2] = 0;
    x4[3] = 0.0F;
    idx4[3] = 0;
    if (0 <= dim - 1) {
      memset(&iidx_data[0], 0, dim * sizeof(int32_T));
      memset(&iwork_data[0], 0, dim * sizeof(int32_T));
    }

    if (0 <= vwork_size_idx_0 - 1) {
      memset(&xwork_data[0], 0, vwork_size_idx_0 * sizeof(real32_T));
    }

    nNaNs = 0;
    dim = -1;
    for (k = 0; k < vwork_size_idx_0; k++) {
      if (muSingleScalarIsNaN(vwork_data[k])) {
        iidx_tmp = (vwork_size_idx_0 - nNaNs) - 1;
        iidx_data[iidx_tmp] = k + 1;
        xwork_data[iidx_tmp] = vwork_data[k];
        nNaNs++;
      } else {
        dim++;
        idx4[dim] = (int16_T)(k + 1);
        x4[dim] = vwork_data[k];
        if (dim + 1 == 4) {
          dim = k - nNaNs;
          if (x4[0] >= x4[1]) {
            i1 = 1;
            i2 = 2;
          } else {
            i1 = 2;
            i2 = 1;
          }

          if (x4[2] >= x4[3]) {
            i3 = 3;
            i4 = 4;
          } else {
            i3 = 4;
            i4 = 3;
          }

          f = x4[i1 - 1];
          f1 = x4[i3 - 1];
          if (f >= f1) {
            f = x4[i2 - 1];
            if (f >= f1) {
              perm[0] = (int8_T)i1;
              perm[1] = (int8_T)i2;
              perm[2] = (int8_T)i3;
              perm[3] = (int8_T)i4;
            } else if (f >= x4[i4 - 1]) {
              perm[0] = (int8_T)i1;
              perm[1] = (int8_T)i3;
              perm[2] = (int8_T)i2;
              perm[3] = (int8_T)i4;
            } else {
              perm[0] = (int8_T)i1;
              perm[1] = (int8_T)i3;
              perm[2] = (int8_T)i4;
              perm[3] = (int8_T)i2;
            }
          } else {
            f1 = x4[i4 - 1];
            if (f >= f1) {
              if (x4[i2 - 1] >= f1) {
                perm[0] = (int8_T)i3;
                perm[1] = (int8_T)i1;
                perm[2] = (int8_T)i2;
                perm[3] = (int8_T)i4;
              } else {
                perm[0] = (int8_T)i3;
                perm[1] = (int8_T)i1;
                perm[2] = (int8_T)i4;
                perm[3] = (int8_T)i2;
              }
            } else {
              perm[0] = (int8_T)i3;
              perm[1] = (int8_T)i4;
              perm[2] = (int8_T)i1;
              perm[3] = (int8_T)i2;
            }
          }

          iidx_data[dim - 3] = idx4[perm[0] - 1];
          iidx_data[dim - 2] = idx4[perm[1] - 1];
          iidx_data[dim - 1] = idx4[perm[2] - 1];
          iidx_data[dim] = idx4[perm[3] - 1];
          vwork_data[dim - 3] = x4[perm[0] - 1];
          vwork_data[dim - 2] = x4[perm[1] - 1];
          vwork_data[dim - 1] = x4[perm[2] - 1];
          vwork_data[dim] = x4[perm[3] - 1];
          dim = -1;
        }
      }
    }

    i3 = (vwork_size_idx_0 - nNaNs) - 1;
    if (dim + 1 > 0) {
      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (dim + 1 == 1) {
        perm[0] = 1;
      } else if (dim + 1 == 2) {
        if (x4[0] >= x4[1]) {
          perm[0] = 1;
          perm[1] = 2;
        } else {
          perm[0] = 2;
          perm[1] = 1;
        }
      } else if (x4[0] >= x4[1]) {
        if (x4[1] >= x4[2]) {
          perm[0] = 1;
          perm[1] = 2;
          perm[2] = 3;
        } else if (x4[0] >= x4[2]) {
          perm[0] = 1;
          perm[1] = 3;
          perm[2] = 2;
        } else {
          perm[0] = 3;
          perm[1] = 1;
          perm[2] = 2;
        }
      } else if (x4[0] >= x4[2]) {
        perm[0] = 2;
        perm[1] = 1;
        perm[2] = 3;
      } else if (x4[1] >= x4[2]) {
        perm[0] = 2;
        perm[1] = 3;
        perm[2] = 1;
      } else {
        perm[0] = 3;
        perm[1] = 2;
        perm[2] = 1;
      }

      for (k = 0; k <= dim; k++) {
        iidx_tmp = perm[k] - 1;
        i1 = (i3 - dim) + k;
        iidx_data[i1] = idx4[iidx_tmp];
        vwork_data[i1] = x4[iidx_tmp];
      }
    }

    dim = (nNaNs >> 1) + 1;
    for (k = 0; k <= dim - 2; k++) {
      i1 = (i3 + k) + 1;
      i2 = iidx_data[i1];
      iidx_tmp = (vwork_size_idx_0 - k) - 1;
      iidx_data[i1] = iidx_data[iidx_tmp];
      iidx_data[iidx_tmp] = i2;
      vwork_data[i1] = xwork_data[iidx_tmp];
      vwork_data[iidx_tmp] = xwork_data[i1];
    }

    if ((nNaNs & 1) != 0) {
      dim += i3;
      vwork_data[dim] = xwork_data[dim];
    }

    nNonNaN = vwork_size_idx_0 - nNaNs;
    dim = 2;
    if (nNonNaN > 1) {
      if (vwork_size_idx_0 >= 256) {
        nBlocks = nNonNaN >> 8;
        if (nBlocks > 0) {
          for (b = 0; b < nBlocks; b++) {
            i4 = (b << 8) - 1;
            for (b_b = 0; b_b < 6; b_b++) {
              bLen = 1 << (b_b + 2);
              bLen2 = bLen << 1;
              nPairs = 256 >> (b_b + 3);
              for (k = 0; k < nPairs; k++) {
                i2 = (i4 + k * bLen2) + 1;
                for (i1 = 0; i1 < bLen2; i1++) {
                  dim = i2 + i1;
                  iwork[i1] = (int16_T)iidx_data[dim];
                  xwork[i1] = vwork_data[dim];
                }

                i3 = 0;
                i1 = bLen;
                dim = i2 - 1;
                do {
                  exitg1 = 0;
                  dim++;
                  if (xwork[i3] >= xwork[i1]) {
                    iidx_data[dim] = iwork[i3];
                    vwork_data[dim] = xwork[i3];
                    if (i3 + 1 < bLen) {
                      i3++;
                    } else {
                      exitg1 = 1;
                    }
                  } else {
                    iidx_data[dim] = iwork[i1];
                    vwork_data[dim] = xwork[i1];
                    if (i1 + 1 < bLen2) {
                      i1++;
                    } else {
                      dim -= i3;
                      for (i1 = i3 + 1; i1 <= bLen; i1++) {
                        iidx_tmp = dim + i1;
                        iidx_data[iidx_tmp] = iwork[i1 - 1];
                        vwork_data[iidx_tmp] = xwork[i1 - 1];
                      }

                      exitg1 = 1;
                    }
                  }
                } while (exitg1 == 0);
              }
            }
          }

          dim = nBlocks << 8;
          i1 = nNonNaN - dim;
          if (i1 > 0) {
            c_merge_block(iidx_data, vwork_data, dim, i1, 2, iwork_data,
                          xwork_data);
          }

          dim = 8;
        }
      }

      c_merge_block(iidx_data, vwork_data, 0, nNonNaN, dim, iwork_data,
                    xwork_data);
    }

    if ((nNaNs > 0) && (nNonNaN > 0)) {
      for (k = 0; k < nNaNs; k++) {
        dim = nNonNaN + k;
        xwork_data[k] = vwork_data[dim];
        iwork_data[k] = iidx_data[dim];
      }

      for (k = nNonNaN; k >= 1; k--) {
        dim = (nNaNs + k) - 1;
        vwork_data[dim] = vwork_data[k - 1];
        iidx_data[dim] = iidx_data[k - 1];
      }

      if (0 <= nNaNs - 1) {
        memcpy(&vwork_data[0], &xwork_data[0], nNaNs * sizeof(real32_T));
        memcpy(&iidx_data[0], &iwork_data[0], nNaNs * sizeof(int32_T));
      }
    }

    for (k = 0; k <= vlen; k++) {
      dim = j + k * vstride;
      x_data[dim] = vwork_data[k];
      idx_data[dim] = iidx_data[k];
    }
  }
}

void d_sort(uint16_T x_data[], const int32_T x_size[1], int32_T idx_data[],
            int32_T idx_size[1])
{
  int32_T b_iwork_data[400];
  int32_T iidx_data[400];
  int32_T iwork_data[400];
  int32_T b;
  int32_T bLen2;
  int32_T b_b;
  int32_T b_j;
  int32_T dim;
  int32_T exitg1;
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T iwork_size_idx_0;
  int32_T j;
  int32_T k;
  int32_T nPairs;
  int32_T vlen;
  int32_T vstride;
  int32_T vwork_size_idx_0;
  int16_T iwork[256];
  int16_T idx4[4];
  uint16_T b_xwork_data[400];
  uint16_T vwork_data[400];
  uint16_T xwork_data[400];
  uint16_T xwork[256];
  uint16_T x4[4];
  uint16_T b_x4_tmp;
  uint16_T c_x4_tmp;
  uint16_T u;
  uint16_T x4_tmp;
  int8_T perm[4];
  dim = 0;
  if (x_size[0] != 1) {
    dim = -1;
  }

  if (dim + 2 <= 1) {
    vwork_size_idx_0 = x_size[0];
  } else {
    vwork_size_idx_0 = 1;
  }

  vlen = vwork_size_idx_0 - 1;
  idx_size[0] = x_size[0];
  vstride = 1;
  for (k = 0; k <= dim; k++) {
    vstride *= x_size[0];
  }

  for (j = 0; j < vstride; j++) {
    for (k = 0; k <= vlen; k++) {
      vwork_data[k] = x_data[j + k * vstride];
    }

    dim = (int16_T)vwork_size_idx_0;
    if (0 <= dim - 1) {
      memset(&iidx_data[0], 0, dim * sizeof(int32_T));
    }

    if (vwork_size_idx_0 != 0) {
      x4[0] = 0U;
      idx4[0] = 0;
      x4[1] = 0U;
      idx4[1] = 0;
      x4[2] = 0U;
      idx4[2] = 0;
      x4[3] = 0U;
      idx4[3] = 0;
      dim = (int16_T)vwork_size_idx_0;
      iwork_size_idx_0 = (int16_T)vwork_size_idx_0;
      if (0 <= dim - 1) {
        memset(&iwork_data[0], 0, dim * sizeof(int32_T));
      }

      if (0 <= vwork_size_idx_0 - 1) {
        memset(&xwork_data[0], 0, vwork_size_idx_0 * sizeof(uint16_T));
      }

      dim = vwork_size_idx_0 >> 2;
      for (b_j = 0; b_j < dim; b_j++) {
        i = b_j << 2;
        idx4[0] = (int16_T)(i + 1);
        idx4[1] = (int16_T)(i + 2);
        idx4[2] = (int16_T)(i + 3);
        idx4[3] = (int16_T)(i + 4);
        u = vwork_data[i];
        x4[0] = u;
        x4_tmp = vwork_data[i + 1];
        x4[1] = x4_tmp;
        b_x4_tmp = vwork_data[i + 2];
        x4[2] = b_x4_tmp;
        c_x4_tmp = vwork_data[i + 3];
        x4[3] = c_x4_tmp;
        if (u >= x4_tmp) {
          i1 = 1;
          i2 = 2;
        } else {
          i1 = 2;
          i2 = 1;
        }

        if (b_x4_tmp >= c_x4_tmp) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }

        nPairs = x4[i1 - 1];
        bLen2 = x4[i3 - 1];
        if (nPairs >= bLen2) {
          nPairs = x4[i2 - 1];
          if (nPairs >= bLen2) {
            perm[0] = (int8_T)i1;
            perm[1] = (int8_T)i2;
            perm[2] = (int8_T)i3;
            perm[3] = (int8_T)i4;
          } else if (nPairs >= x4[i4 - 1]) {
            perm[0] = (int8_T)i1;
            perm[1] = (int8_T)i3;
            perm[2] = (int8_T)i2;
            perm[3] = (int8_T)i4;
          } else {
            perm[0] = (int8_T)i1;
            perm[1] = (int8_T)i3;
            perm[2] = (int8_T)i4;
            perm[3] = (int8_T)i2;
          }
        } else {
          bLen2 = x4[i4 - 1];
          if (nPairs >= bLen2) {
            if (x4[i2 - 1] >= bLen2) {
              perm[0] = (int8_T)i3;
              perm[1] = (int8_T)i1;
              perm[2] = (int8_T)i2;
              perm[3] = (int8_T)i4;
            } else {
              perm[0] = (int8_T)i3;
              perm[1] = (int8_T)i1;
              perm[2] = (int8_T)i4;
              perm[3] = (int8_T)i2;
            }
          } else {
            perm[0] = (int8_T)i3;
            perm[1] = (int8_T)i4;
            perm[2] = (int8_T)i1;
            perm[3] = (int8_T)i2;
          }
        }

        iidx_data[i] = idx4[perm[0] - 1];
        iidx_data[i + 1] = idx4[perm[1] - 1];
        iidx_data[i + 2] = idx4[perm[2] - 1];
        iidx_data[i + 3] = idx4[perm[3] - 1];
        vwork_data[i] = x4[perm[0] - 1];
        vwork_data[i + 1] = x4[perm[1] - 1];
        vwork_data[i + 2] = x4[perm[2] - 1];
        vwork_data[i + 3] = x4[perm[3] - 1];
      }

      i = dim << 2;
      i1 = (vwork_size_idx_0 - i) - 1;
      if (i1 + 1 > 0) {
        for (k = 0; k <= i1; k++) {
          dim = i + k;
          idx4[k] = (int16_T)(dim + 1);
          x4[k] = vwork_data[dim];
        }

        perm[1] = 0;
        perm[2] = 0;
        perm[3] = 0;
        if (i1 + 1 == 1) {
          perm[0] = 1;
        } else if (i1 + 1 == 2) {
          if (x4[0] >= x4[1]) {
            perm[0] = 1;
            perm[1] = 2;
          } else {
            perm[0] = 2;
            perm[1] = 1;
          }
        } else if (x4[0] >= x4[1]) {
          if (x4[1] >= x4[2]) {
            perm[0] = 1;
            perm[1] = 2;
            perm[2] = 3;
          } else if (x4[0] >= x4[2]) {
            perm[0] = 1;
            perm[1] = 3;
            perm[2] = 2;
          } else {
            perm[0] = 3;
            perm[1] = 1;
            perm[2] = 2;
          }
        } else if (x4[0] >= x4[2]) {
          perm[0] = 2;
          perm[1] = 1;
          perm[2] = 3;
        } else if (x4[1] >= x4[2]) {
          perm[0] = 2;
          perm[1] = 3;
          perm[2] = 1;
        } else {
          perm[0] = 3;
          perm[1] = 2;
          perm[2] = 1;
        }

        for (k = 0; k <= i1; k++) {
          i2 = perm[k] - 1;
          dim = i + k;
          iidx_data[dim] = idx4[i2];
          vwork_data[dim] = x4[i2];
        }
      }

      dim = 2;
      if (vwork_size_idx_0 > 1) {
        if (vwork_size_idx_0 >= 256) {
          for (b = 0; b < 1; b++) {
            for (b_b = 0; b_b < 6; b_b++) {
              i4 = 1 << (b_b + 2);
              bLen2 = i4 << 1;
              nPairs = 256 >> (b_b + 3);
              for (k = 0; k < nPairs; k++) {
                i1 = k * bLen2;
                for (b_j = 0; b_j < bLen2; b_j++) {
                  dim = i1 + b_j;
                  iwork[b_j] = (int16_T)iidx_data[dim];
                  xwork[b_j] = vwork_data[dim];
                }

                i3 = 0;
                i = i4;
                dim = i1 - 1;
                do {
                  exitg1 = 0;
                  dim++;
                  if (xwork[i3] >= xwork[i]) {
                    iidx_data[dim] = iwork[i3];
                    vwork_data[dim] = xwork[i3];
                    if (i3 + 1 < i4) {
                      i3++;
                    } else {
                      exitg1 = 1;
                    }
                  } else {
                    iidx_data[dim] = iwork[i];
                    vwork_data[dim] = xwork[i];
                    if (i + 1 < bLen2) {
                      i++;
                    } else {
                      dim -= i3;
                      for (b_j = i3 + 1; b_j <= i4; b_j++) {
                        i2 = dim + b_j;
                        iidx_data[i2] = iwork[b_j - 1];
                        vwork_data[i2] = xwork[b_j - 1];
                      }

                      exitg1 = 1;
                    }
                  }
                } while (exitg1 == 0);
              }
            }
          }

          if (vwork_size_idx_0 - 256 > 0) {
            d_merge_block(iidx_data, vwork_data, 256, vwork_size_idx_0 - 256, 2,
                          iwork_data, xwork_data);
          }

          dim = 8;
        }

        if (0 <= iwork_size_idx_0 - 1) {
          memcpy(&b_iwork_data[0], &iwork_data[0], iwork_size_idx_0 * sizeof
                 (int32_T));
        }

        if (0 <= vwork_size_idx_0 - 1) {
          memcpy(&b_xwork_data[0], &xwork_data[0], vwork_size_idx_0 * sizeof
                 (uint16_T));
        }

        d_merge_block(iidx_data, vwork_data, 0, vwork_size_idx_0, dim,
                      b_iwork_data, b_xwork_data);
      }
    }

    for (k = 0; k <= vlen; k++) {
      nPairs = j + k * vstride;
      x_data[nPairs] = vwork_data[k];
      idx_data[nPairs] = iidx_data[k];
    }
  }
}

void sort(int16_T x_data[], const int32_T x_size[1], int32_T idx_data[], int32_T
          idx_size[1])
{
  int32_T b_iwork_data[400];
  int32_T iidx_data[400];
  int32_T iwork_data[400];
  int32_T b;
  int32_T bLen2;
  int32_T b_b;
  int32_T b_j;
  int32_T dim;
  int32_T exitg1;
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T iwork_size_idx_0;
  int32_T j;
  int32_T k;
  int32_T nPairs;
  int32_T vlen;
  int32_T vstride;
  int32_T vwork_size_idx_0;
  int16_T b_xwork_data[400];
  int16_T vwork_data[400];
  int16_T xwork_data[400];
  int16_T iwork[256];
  int16_T xwork[256];
  int16_T idx4[4];
  int16_T x4[4];
  int16_T b_i;
  int16_T b_x4_tmp;
  int16_T c_x4_tmp;
  int16_T x4_tmp;
  int8_T perm[4];
  dim = 0;
  if (x_size[0] != 1) {
    dim = -1;
  }

  if (dim + 2 <= 1) {
    vwork_size_idx_0 = x_size[0];
  } else {
    vwork_size_idx_0 = 1;
  }

  vlen = vwork_size_idx_0 - 1;
  idx_size[0] = x_size[0];
  vstride = 1;
  for (k = 0; k <= dim; k++) {
    vstride *= x_size[0];
  }

  for (j = 0; j < vstride; j++) {
    for (k = 0; k <= vlen; k++) {
      vwork_data[k] = x_data[j + k * vstride];
    }

    dim = (int16_T)vwork_size_idx_0;
    x4[0] = 0;
    idx4[0] = 0;
    x4[1] = 0;
    idx4[1] = 0;
    x4[2] = 0;
    idx4[2] = 0;
    x4[3] = 0;
    idx4[3] = 0;
    iwork_size_idx_0 = (int16_T)vwork_size_idx_0;
    if (0 <= dim - 1) {
      memset(&iidx_data[0], 0, dim * sizeof(int32_T));
      memset(&iwork_data[0], 0, dim * sizeof(int32_T));
    }

    if (0 <= vwork_size_idx_0 - 1) {
      memset(&xwork_data[0], 0, vwork_size_idx_0 * sizeof(int16_T));
    }

    dim = vwork_size_idx_0 >> 2;
    for (b_j = 0; b_j < dim; b_j++) {
      i = b_j << 2;
      idx4[0] = (int16_T)(i + 1);
      idx4[1] = (int16_T)(i + 2);
      idx4[2] = (int16_T)(i + 3);
      idx4[3] = (int16_T)(i + 4);
      b_i = vwork_data[i];
      x4[0] = b_i;
      x4_tmp = vwork_data[i + 1];
      x4[1] = x4_tmp;
      b_x4_tmp = vwork_data[i + 2];
      x4[2] = b_x4_tmp;
      c_x4_tmp = vwork_data[i + 3];
      x4[3] = c_x4_tmp;
      if (b_i >= x4_tmp) {
        i1 = 1;
        i2 = 2;
      } else {
        i1 = 2;
        i2 = 1;
      }

      if (b_x4_tmp >= c_x4_tmp) {
        i3 = 3;
        i4 = 4;
      } else {
        i3 = 4;
        i4 = 3;
      }

      nPairs = x4[i1 - 1];
      bLen2 = x4[i3 - 1];
      if (nPairs >= bLen2) {
        nPairs = x4[i2 - 1];
        if (nPairs >= bLen2) {
          perm[0] = (int8_T)i1;
          perm[1] = (int8_T)i2;
          perm[2] = (int8_T)i3;
          perm[3] = (int8_T)i4;
        } else if (nPairs >= x4[i4 - 1]) {
          perm[0] = (int8_T)i1;
          perm[1] = (int8_T)i3;
          perm[2] = (int8_T)i2;
          perm[3] = (int8_T)i4;
        } else {
          perm[0] = (int8_T)i1;
          perm[1] = (int8_T)i3;
          perm[2] = (int8_T)i4;
          perm[3] = (int8_T)i2;
        }
      } else {
        bLen2 = x4[i4 - 1];
        if (nPairs >= bLen2) {
          if (x4[i2 - 1] >= bLen2) {
            perm[0] = (int8_T)i3;
            perm[1] = (int8_T)i1;
            perm[2] = (int8_T)i2;
            perm[3] = (int8_T)i4;
          } else {
            perm[0] = (int8_T)i3;
            perm[1] = (int8_T)i1;
            perm[2] = (int8_T)i4;
            perm[3] = (int8_T)i2;
          }
        } else {
          perm[0] = (int8_T)i3;
          perm[1] = (int8_T)i4;
          perm[2] = (int8_T)i1;
          perm[3] = (int8_T)i2;
        }
      }

      iidx_data[i] = idx4[perm[0] - 1];
      iidx_data[i + 1] = idx4[perm[1] - 1];
      iidx_data[i + 2] = idx4[perm[2] - 1];
      iidx_data[i + 3] = idx4[perm[3] - 1];
      vwork_data[i] = x4[perm[0] - 1];
      vwork_data[i + 1] = x4[perm[1] - 1];
      vwork_data[i + 2] = x4[perm[2] - 1];
      vwork_data[i + 3] = x4[perm[3] - 1];
    }

    i = dim << 2;
    i1 = (vwork_size_idx_0 - i) - 1;
    if (i1 + 1 > 0) {
      for (k = 0; k <= i1; k++) {
        dim = i + k;
        idx4[k] = (int16_T)(dim + 1);
        x4[k] = vwork_data[dim];
      }

      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (i1 + 1 == 1) {
        perm[0] = 1;
      } else if (i1 + 1 == 2) {
        if (x4[0] >= x4[1]) {
          perm[0] = 1;
          perm[1] = 2;
        } else {
          perm[0] = 2;
          perm[1] = 1;
        }
      } else if (x4[0] >= x4[1]) {
        if (x4[1] >= x4[2]) {
          perm[0] = 1;
          perm[1] = 2;
          perm[2] = 3;
        } else if (x4[0] >= x4[2]) {
          perm[0] = 1;
          perm[1] = 3;
          perm[2] = 2;
        } else {
          perm[0] = 3;
          perm[1] = 1;
          perm[2] = 2;
        }
      } else if (x4[0] >= x4[2]) {
        perm[0] = 2;
        perm[1] = 1;
        perm[2] = 3;
      } else if (x4[1] >= x4[2]) {
        perm[0] = 2;
        perm[1] = 3;
        perm[2] = 1;
      } else {
        perm[0] = 3;
        perm[1] = 2;
        perm[2] = 1;
      }

      for (k = 0; k <= i1; k++) {
        i2 = perm[k] - 1;
        dim = i + k;
        iidx_data[dim] = idx4[i2];
        vwork_data[dim] = x4[i2];
      }
    }

    dim = 2;
    if (vwork_size_idx_0 > 1) {
      if (vwork_size_idx_0 >= 256) {
        for (b = 0; b < 1; b++) {
          for (b_b = 0; b_b < 6; b_b++) {
            i4 = 1 << (b_b + 2);
            bLen2 = i4 << 1;
            nPairs = 256 >> (b_b + 3);
            for (k = 0; k < nPairs; k++) {
              i1 = k * bLen2;
              for (b_j = 0; b_j < bLen2; b_j++) {
                dim = i1 + b_j;
                iwork[b_j] = (int16_T)iidx_data[dim];
                xwork[b_j] = vwork_data[dim];
              }

              i3 = 0;
              i = i4;
              dim = i1 - 1;
              do {
                exitg1 = 0;
                dim++;
                if (xwork[i3] >= xwork[i]) {
                  iidx_data[dim] = iwork[i3];
                  vwork_data[dim] = xwork[i3];
                  if (i3 + 1 < i4) {
                    i3++;
                  } else {
                    exitg1 = 1;
                  }
                } else {
                  iidx_data[dim] = iwork[i];
                  vwork_data[dim] = xwork[i];
                  if (i + 1 < bLen2) {
                    i++;
                  } else {
                    dim -= i3;
                    for (b_j = i3 + 1; b_j <= i4; b_j++) {
                      i2 = dim + b_j;
                      iidx_data[i2] = iwork[b_j - 1];
                      vwork_data[i2] = xwork[b_j - 1];
                    }

                    exitg1 = 1;
                  }
                }
              } while (exitg1 == 0);
            }
          }
        }

        if (vwork_size_idx_0 - 256 > 0) {
          merge_block(iidx_data, vwork_data, 256, vwork_size_idx_0 - 256, 2,
                      iwork_data, xwork_data);
        }

        dim = 8;
      }

      if (0 <= iwork_size_idx_0 - 1) {
        memcpy(&b_iwork_data[0], &iwork_data[0], iwork_size_idx_0 * sizeof
               (int32_T));
      }

      if (0 <= vwork_size_idx_0 - 1) {
        memcpy(&b_xwork_data[0], &xwork_data[0], vwork_size_idx_0 * sizeof
               (int16_T));
      }

      merge_block(iidx_data, vwork_data, 0, vwork_size_idx_0, dim, b_iwork_data,
                  b_xwork_data);
    }

    for (k = 0; k <= vlen; k++) {
      nPairs = j + k * vstride;
      x_data[nPairs] = vwork_data[k];
      idx_data[nPairs] = iidx_data[k];
    }
  }
}

/* End of code generation (sort.c) */
