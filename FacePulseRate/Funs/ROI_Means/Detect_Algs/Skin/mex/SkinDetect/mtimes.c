/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mtimes.c
 *
 * Code generation for function 'mtimes'
 *
 */

/* Include files */
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void mtimes(const real_T A_data[], const int32_T A_size[2], const real_T B[4],
            real_T C_data[], int32_T C_size[1])
{
  ptrdiff_t k_t;
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t ldc_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  real_T alpha1;
  real_T beta1;
  int32_T loop_ub;
  char_T TRANSA1;
  char_T TRANSB1;
  if (A_size[1] == 0) {
    C_size[0] = A_size[0];
    loop_ub = A_size[0];
    if (0 <= loop_ub - 1) {
      memset(&C_data[0], 0, loop_ub * sizeof(real_T));
    }
  } else {
    TRANSB1 = 'N';
    TRANSA1 = 'N';
    alpha1 = 1.0;
    beta1 = 0.0;
    m_t = (ptrdiff_t)A_size[0];
    n_t = (ptrdiff_t)1;
    k_t = (ptrdiff_t)4;
    lda_t = (ptrdiff_t)A_size[0];
    ldb_t = (ptrdiff_t)4;
    ldc_t = (ptrdiff_t)A_size[0];
    C_size[0] = A_size[0];
    dgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &A_data[0], &lda_t, &B
          [0], &ldb_t, &beta1, &C_data[0], &ldc_t);
  }
}

/* End of code generation (mtimes.c) */
