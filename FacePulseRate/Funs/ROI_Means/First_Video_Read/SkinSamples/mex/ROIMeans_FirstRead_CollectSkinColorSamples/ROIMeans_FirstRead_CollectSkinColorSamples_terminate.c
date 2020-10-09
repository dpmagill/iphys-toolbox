/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIMeans_FirstRead_CollectSkinColorSamples_terminate.c
 *
 * Code generation for function 'ROIMeans_FirstRead_CollectSkinColorSamples_terminate'
 *
 */

/* Include files */
#include "ROIMeans_FirstRead_CollectSkinColorSamples_terminate.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_data.h"
#include "SkinSegmentMask_MorphClose.h"
#include "SkinSegmentMask_Threshold.h"
#include "_coder_ROIMeans_FirstRead_CollectSkinColorSamples_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ROIMeans_FirstRead_CollectSkinColorSamples_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  ErodeAndDilate_SEWidth50_free();
  ErodeAndDilate_SEWidth22_free();
  SkinSegmentMask_Threshold_free();
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void ROIMeans_FirstRead_CollectSkinColorSamples_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (ROIMeans_FirstRead_CollectSkinColorSamples_terminate.c) */
