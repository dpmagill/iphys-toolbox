/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sortIdx.c
 *
 * Code generation for function 'sortIdx'
 *
 */

/* Include files */
#include "sortIdx.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void b_merge(int32_T idx_data[], real_T x_data[], int32_T offset, int32_T
                    np, int32_T nq, int32_T iwork_data[], real_T xwork_data[]);
static void c_merge(int32_T idx_data[], real32_T x_data[], int32_T offset,
                    int32_T np, int32_T nq, int32_T iwork_data[], real32_T
                    xwork_data[]);
static void d_merge(int32_T idx_data[], uint16_T x_data[], int32_T offset,
                    int32_T np, int32_T nq, int32_T iwork_data[], uint16_T
                    xwork_data[]);
static void merge(int32_T idx_data[], int16_T x_data[], int32_T offset, int32_T
                  np, int32_T nq, int32_T iwork_data[], int16_T xwork_data[]);

/* Function Definitions */
static void b_merge(int32_T idx_data[], real_T x_data[], int32_T offset, int32_T
                    np, int32_T nq, int32_T iwork_data[], real_T xwork_data[])
{
  int32_T exitg1;
  int32_T iout;
  int32_T j;
  int32_T n_tmp;
  int32_T p;
  int32_T q;
  if (nq != 0) {
    n_tmp = np + nq;
    for (j = 0; j < n_tmp; j++) {
      iout = offset + j;
      iwork_data[j] = idx_data[iout];
      xwork_data[j] = x_data[iout];
    }

    p = 0;
    q = np;
    iout = offset - 1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork_data[p] <= xwork_data[q]) {
        idx_data[iout] = iwork_data[p];
        x_data[iout] = xwork_data[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx_data[iout] = iwork_data[q];
        x_data[iout] = xwork_data[q];
        if (q + 1 < n_tmp) {
          q++;
        } else {
          q = iout - p;
          for (j = p + 1; j <= np; j++) {
            iout = q + j;
            idx_data[iout] = iwork_data[j - 1];
            x_data[iout] = xwork_data[j - 1];
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

static void c_merge(int32_T idx_data[], real32_T x_data[], int32_T offset,
                    int32_T np, int32_T nq, int32_T iwork_data[], real32_T
                    xwork_data[])
{
  int32_T exitg1;
  int32_T iout;
  int32_T j;
  int32_T n_tmp;
  int32_T p;
  int32_T q;
  if (nq != 0) {
    n_tmp = np + nq;
    for (j = 0; j < n_tmp; j++) {
      iout = offset + j;
      iwork_data[j] = idx_data[iout];
      xwork_data[j] = x_data[iout];
    }

    p = 0;
    q = np;
    iout = offset - 1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork_data[p] >= xwork_data[q]) {
        idx_data[iout] = iwork_data[p];
        x_data[iout] = xwork_data[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx_data[iout] = iwork_data[q];
        x_data[iout] = xwork_data[q];
        if (q + 1 < n_tmp) {
          q++;
        } else {
          q = iout - p;
          for (j = p + 1; j <= np; j++) {
            iout = q + j;
            idx_data[iout] = iwork_data[j - 1];
            x_data[iout] = xwork_data[j - 1];
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

static void d_merge(int32_T idx_data[], uint16_T x_data[], int32_T offset,
                    int32_T np, int32_T nq, int32_T iwork_data[], uint16_T
                    xwork_data[])
{
  int32_T exitg1;
  int32_T iout;
  int32_T j;
  int32_T n_tmp;
  int32_T p;
  int32_T q;
  if (nq != 0) {
    n_tmp = np + nq;
    for (j = 0; j < n_tmp; j++) {
      iout = offset + j;
      iwork_data[j] = idx_data[iout];
      xwork_data[j] = x_data[iout];
    }

    p = 0;
    q = np;
    iout = offset - 1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork_data[p] >= xwork_data[q]) {
        idx_data[iout] = iwork_data[p];
        x_data[iout] = xwork_data[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx_data[iout] = iwork_data[q];
        x_data[iout] = xwork_data[q];
        if (q + 1 < n_tmp) {
          q++;
        } else {
          q = iout - p;
          for (j = p + 1; j <= np; j++) {
            iout = q + j;
            idx_data[iout] = iwork_data[j - 1];
            x_data[iout] = xwork_data[j - 1];
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

static void merge(int32_T idx_data[], int16_T x_data[], int32_T offset, int32_T
                  np, int32_T nq, int32_T iwork_data[], int16_T xwork_data[])
{
  int32_T exitg1;
  int32_T iout;
  int32_T j;
  int32_T n_tmp;
  int32_T p;
  int32_T q;
  if (nq != 0) {
    n_tmp = np + nq;
    for (j = 0; j < n_tmp; j++) {
      iout = offset + j;
      iwork_data[j] = idx_data[iout];
      xwork_data[j] = x_data[iout];
    }

    p = 0;
    q = np;
    iout = offset - 1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork_data[p] >= xwork_data[q]) {
        idx_data[iout] = iwork_data[p];
        x_data[iout] = xwork_data[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx_data[iout] = iwork_data[q];
        x_data[iout] = xwork_data[q];
        if (q + 1 < n_tmp) {
          q++;
        } else {
          q = iout - p;
          for (j = p + 1; j <= np; j++) {
            iout = q + j;
            idx_data[iout] = iwork_data[j - 1];
            x_data[iout] = xwork_data[j - 1];
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

void b_merge_block(int32_T idx_data[], real_T x_data[], int32_T offset, int32_T
                   n, int32_T preSortLevel, int32_T iwork_data[], real_T
                   xwork_data[])
{
  int32_T bLen;
  int32_T nPairs;
  int32_T nTail;
  int32_T tailOffset;
  nPairs = n >> preSortLevel;
  bLen = 1 << preSortLevel;
  while (nPairs > 1) {
    if ((nPairs & 1) != 0) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        b_merge(idx_data, x_data, offset + tailOffset, bLen, nTail - bLen,
                iwork_data, xwork_data);
      }
    }

    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (nTail = 0; nTail < nPairs; nTail++) {
      b_merge(idx_data, x_data, offset + nTail * tailOffset, bLen, bLen,
              iwork_data, xwork_data);
    }

    bLen = tailOffset;
  }

  if (n > bLen) {
    b_merge(idx_data, x_data, offset, bLen, n - bLen, iwork_data, xwork_data);
  }
}

void c_merge_block(int32_T idx_data[], real32_T x_data[], int32_T offset,
                   int32_T n, int32_T preSortLevel, int32_T iwork_data[],
                   real32_T xwork_data[])
{
  int32_T bLen;
  int32_T nPairs;
  int32_T nTail;
  int32_T tailOffset;
  nPairs = n >> preSortLevel;
  bLen = 1 << preSortLevel;
  while (nPairs > 1) {
    if ((nPairs & 1) != 0) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        c_merge(idx_data, x_data, offset + tailOffset, bLen, nTail - bLen,
                iwork_data, xwork_data);
      }
    }

    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (nTail = 0; nTail < nPairs; nTail++) {
      c_merge(idx_data, x_data, offset + nTail * tailOffset, bLen, bLen,
              iwork_data, xwork_data);
    }

    bLen = tailOffset;
  }

  if (n > bLen) {
    c_merge(idx_data, x_data, offset, bLen, n - bLen, iwork_data, xwork_data);
  }
}

void d_merge_block(int32_T idx_data[], uint16_T x_data[], int32_T offset,
                   int32_T n, int32_T preSortLevel, int32_T iwork_data[],
                   uint16_T xwork_data[])
{
  int32_T bLen;
  int32_T nPairs;
  int32_T nTail;
  int32_T tailOffset;
  nPairs = n >> preSortLevel;
  bLen = 1 << preSortLevel;
  while (nPairs > 1) {
    if ((nPairs & 1) != 0) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        d_merge(idx_data, x_data, offset + tailOffset, bLen, nTail - bLen,
                iwork_data, xwork_data);
      }
    }

    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (nTail = 0; nTail < nPairs; nTail++) {
      d_merge(idx_data, x_data, offset + nTail * tailOffset, bLen, bLen,
              iwork_data, xwork_data);
    }

    bLen = tailOffset;
  }

  if (n > bLen) {
    d_merge(idx_data, x_data, offset, bLen, n - bLen, iwork_data, xwork_data);
  }
}

void merge_block(int32_T idx_data[], int16_T x_data[], int32_T offset, int32_T n,
                 int32_T preSortLevel, int32_T iwork_data[], int16_T xwork_data[])
{
  int32_T bLen;
  int32_T nPairs;
  int32_T nTail;
  int32_T tailOffset;
  nPairs = n >> preSortLevel;
  bLen = 1 << preSortLevel;
  while (nPairs > 1) {
    if ((nPairs & 1) != 0) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        merge(idx_data, x_data, offset + tailOffset, bLen, nTail - bLen,
              iwork_data, xwork_data);
      }
    }

    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (nTail = 0; nTail < nPairs; nTail++) {
      merge(idx_data, x_data, offset + nTail * tailOffset, bLen, bLen,
            iwork_data, xwork_data);
    }

    bLen = tailOffset;
  }

  if (n > bLen) {
    merge(idx_data, x_data, offset, bLen, n - bLen, iwork_data, xwork_data);
  }
}

/* End of code generation (sortIdx.c) */
