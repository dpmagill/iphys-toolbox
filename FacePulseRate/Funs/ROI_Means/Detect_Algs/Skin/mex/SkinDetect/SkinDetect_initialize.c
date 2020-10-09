/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect_initialize.c
 *
 * Code generation for function 'SkinDetect_initialize'
 *
 */

/* Include files */
#include "SkinDetect_initialize.h"
#include "SkinDetect_data.h"
#include "SkinSegmentMask_MorphClose.h"
#include "SkinSegmentMask_Threshold.h"
#include "_coder_SkinDetect_mex.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void SkinDetect_once(void);

/* Function Definitions */
static void SkinDetect_once(void)
{
  mex_InitInfAndNan();
  SkinSegmentMask_Threshold_init();
  ErodeAndDilate_SESquare12_init();
  ErodeAndDilate_SESquare22_init();
  ErodeAndDilate_SESquare32_init();
  ErodeAndDilate_SESquare50_init();
}

void SkinDetect_initialize(void)
{
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLicenseCheckR2012b(emlrtRootTLSGlobal, "image_toolbox", 2);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    SkinDetect_once();
  }
}

/* End of code generation (SkinDetect_initialize.c) */
