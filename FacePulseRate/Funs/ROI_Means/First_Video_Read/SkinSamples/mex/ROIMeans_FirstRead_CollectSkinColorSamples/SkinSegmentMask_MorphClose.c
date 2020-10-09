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
#include "ROIMeans_FirstRead_CollectSkinColorSamples.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static boolean_T SE_not_empty;
static boolean_T b_SE_not_empty;

/* Function Definitions */
void ErodeAndDilate_SEWidth22_free(void)
{
  SE_not_empty = false;
}

void ErodeAndDilate_SEWidth22_init(void)
{
  /* Assign structuring element  */
  /* For code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  width of structuring element */
  SE_not_empty = true;
}

void ErodeAndDilate_SEWidth50_free(void)
{
  b_SE_not_empty = false;
}

void ErodeAndDilate_SEWidth50_init(void)
{
  /* Assign structuring element  */
  /* For code generation, the structuring element must be a compile-time constant. */
  /*  shape of structuring element */
  /*  width of structuring element */
  b_SE_not_empty = true;
}

/* End of code generation (SkinSegmentMask_MorphClose.c) */
