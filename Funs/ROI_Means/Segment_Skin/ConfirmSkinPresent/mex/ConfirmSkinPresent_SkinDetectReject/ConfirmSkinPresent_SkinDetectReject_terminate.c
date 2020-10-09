/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ConfirmSkinPresent_SkinDetectReject_terminate.c
 *
 * Code generation for function 'ConfirmSkinPresent_SkinDetectReject_terminate'
 *
 */

/* Include files */
#include "ConfirmSkinPresent_SkinDetectReject_terminate.h"
#include "ConfirmSkinPresent_SkinDetectReject.h"
#include "ConfirmSkinPresent_SkinDetectReject_data.h"
#include "_coder_ConfirmSkinPresent_SkinDetectReject_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ConfirmSkinPresent_SkinDetectReject_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void ConfirmSkinPresent_SkinDetectReject_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (ConfirmSkinPresent_SkinDetectReject_terminate.c) */
