/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinSegmentMask_MorphClose.c
 *
 * Code generation for function 'SkinSegmentMask_MorphClose'
 *
 */

/* Include files */
#include "SkinSegmentMask_MorphClose.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static boolean_T SE_not_empty;
static boolean_T b_SE_not_empty;
static boolean_T c_SE_not_empty;
static boolean_T d_SE_not_empty;
static boolean_T e_SE_not_empty;
static boolean_T f_SE_not_empty;
static boolean_T g_SE_not_empty;
static boolean_T h_SE_not_empty;

/* Function Definitions */
void ErodeAndDilate_SEDisk10_free(void)
{
  g_SE_not_empty = false;
}

void ErodeAndDilate_SEDisk10_init(void)
{
  /* Assign structuring element */
  /* For code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  radius of structuring element */
  /*  approximations to use during operations; non-zero for better */
  g_SE_not_empty = true;

  /*    performance. */
}

void ErodeAndDilate_SEDisk14_free(void)
{
  h_SE_not_empty = false;
}

void ErodeAndDilate_SEDisk14_init(void)
{
  /* Assign structuring element */
  /* For code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  radius of structuring element */
  /*  approximations to use during operations; non-zero for better */
  h_SE_not_empty = true;

  /*    performance. */
}

void ErodeAndDilate_SEDisk4_free(void)
{
  e_SE_not_empty = false;
}

void ErodeAndDilate_SEDisk4_init(void)
{
  /* Assign structuring element  */
  /* For code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  radius of structuring element */
  /*  approximations to use during operations; non-zero for better */
  e_SE_not_empty = true;

  /*    performance. */
}

void ErodeAndDilate_SEDisk6_free(void)
{
  f_SE_not_empty = false;
}

void ErodeAndDilate_SEDisk6_init(void)
{
  /* Assign structuring element  */
  /* For code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  radius of structuring element */
  /*  approximations to use during operations; non-zero for better */
  f_SE_not_empty = true;

  /*    performance. */
}

void ErodeAndDilate_SESquare12_free(void)
{
  SE_not_empty = false;
}

void ErodeAndDilate_SESquare12_init(void)
{
  /* Assign structuring element  */
  /* For code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  width of structuring element */
  SE_not_empty = true;
}

void ErodeAndDilate_SESquare22_free(void)
{
  b_SE_not_empty = false;
}

void ErodeAndDilate_SESquare22_init(void)
{
  /* Assign structuring element  */
  /* For code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  width of structuring element */
  b_SE_not_empty = true;
}

void ErodeAndDilate_SESquare32_free(void)
{
  c_SE_not_empty = false;
}

void ErodeAndDilate_SESquare32_init(void)
{
  /* Assign structuring element  */
  /* For code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  width of structuring element */
  c_SE_not_empty = true;
}

void ErodeAndDilate_SESquare50_free(void)
{
  d_SE_not_empty = false;
}

void ErodeAndDilate_SESquare50_init(void)
{
  /* Assign structuring element  */
  /* For code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  width of structuring element */
  d_SE_not_empty = true;
}

/* End of code generation (SkinSegmentMask_MorphClose.c) */
