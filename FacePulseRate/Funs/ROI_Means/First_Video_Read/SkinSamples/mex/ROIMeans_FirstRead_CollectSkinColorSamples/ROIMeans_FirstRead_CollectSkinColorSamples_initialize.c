/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIMeans_FirstRead_CollectSkinColorSamples_initialize.c
 *
 * Code generation for function 'ROIMeans_FirstRead_CollectSkinColorSamples_initialize'
 *
 */

/* Include files */
#include "ROIMeans_FirstRead_CollectSkinColorSamples_initialize.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_data.h"
#include "SkinSegmentMask_MorphClose.h"
#include "SkinSegmentMask_Threshold.h"
#include "_coder_ROIMeans_FirstRead_CollectSkinColorSamples_mex.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void c_ROIMeans_FirstRead_CollectSki(void);

/* Function Definitions */
static void c_ROIMeans_FirstRead_CollectSki(void)
{
  mex_InitInfAndNan();
  SkinSegmentMask_Threshold_init();
  ErodeAndDilate_SEWidth22_init();
  ErodeAndDilate_SEWidth50_init();
}

void ROIMeans_FirstRead_CollectSkinColorSamples_initialize(void)
{
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLicenseCheckR2012b(emlrtRootTLSGlobal, "Image_Toolbox", 2);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    c_ROIMeans_FirstRead_CollectSki();
  }
}

/* End of code generation (ROIMeans_FirstRead_CollectSkinColorSamples_initialize.c) */
