/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinSegmentMask_Ops_initialize.c
 *
 * Code generation for function 'SkinSegmentMask_Ops_initialize'
 *
 */

/* Include files */
#include "SkinSegmentMask_Ops_initialize.h"
#include "SkinSegmentMask_MorphClose.h"
#include "SkinSegmentMask_Ops_data.h"
#include "SkinSegmentMask_Threshold.h"
#include "_coder_SkinSegmentMask_Ops_mex.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void SkinSegmentMask_Ops_once(void);

/* Function Definitions */
static void SkinSegmentMask_Ops_once(void)
{
  mex_InitInfAndNan();
  SkinSegmentMask_Threshold_init();
  ErodeAndDilate_SESquare12_init();
  ErodeAndDilate_SESquare22_init();
  ErodeAndDilate_SESquare32_init();
  ErodeAndDilate_SESquare50_init();
  ErodeAndDilate_SEDisk4_init();
  ErodeAndDilate_SEDisk6_init();
  ErodeAndDilate_SEDisk10_init();
  ErodeAndDilate_SEDisk14_init();
}

void SkinSegmentMask_Ops_initialize(void)
{
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLicenseCheckR2012b(emlrtRootTLSGlobal, "image_toolbox", 2);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    SkinSegmentMask_Ops_once();
  }
}

/* End of code generation (SkinSegmentMask_Ops_initialize.c) */
