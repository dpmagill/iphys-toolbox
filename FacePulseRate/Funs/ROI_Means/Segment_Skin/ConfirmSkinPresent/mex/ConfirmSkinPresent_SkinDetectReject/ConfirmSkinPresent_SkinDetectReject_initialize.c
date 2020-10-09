/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ConfirmSkinPresent_SkinDetectReject_initialize.c
 *
 * Code generation for function 'ConfirmSkinPresent_SkinDetectReject_initialize'
 *
 */

/* Include files */
#include "ConfirmSkinPresent_SkinDetectReject_initialize.h"
#include "ConfirmSkinPresent_SkinDetectReject.h"
#include "ConfirmSkinPresent_SkinDetectReject_data.h"
#include "_coder_ConfirmSkinPresent_SkinDetectReject_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ConfirmSkinPresent_SkinDetectReject_initialize(void)
{
  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLicenseCheckR2012b(emlrtRootTLSGlobal, "Image_Toolbox", 2);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (ConfirmSkinPresent_SkinDetectReject_initialize.c) */
