/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIAdjustIfExceedsFrameDims.c
 *
 * Code generation for function 'ROIAdjustIfExceedsFrameDims'
 *
 */

/* Include files */
#include "ROIAdjustIfExceedsFrameDims.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ROIAdjustIfExceedsFrameDims(emxArray_int16_T *ROIsProposed, int16_T
  VidObjWidth, int16_T VidObjHeight)
{
  int32_T i;
  int32_T b_i;
  int16_T ROI_left_X_ith;
  int16_T ROI_right_X_ith;

  /* ROIAdjustIfExceedsFrameDims   Verify whether proposed widths and heights of ROIs exceed frame  */
  /*                               dimensions and, if so, modify them to conform to frame dimensions. */
  /*                                */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by functions ROIResize, ROIMeans_FirstRead_Extrapolate, */
  /*     SkinDetect_EnlargeROI, ROIMSIR, ROIMSIR_MatchSize, ROIMSIR_DetectionSmooth,   */
  /*     ROIMSIR_Interpolate, and ROIMSIR_FrameByFrameSmooth.    */
  /*  */
  /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*     Description: */
  /*  */
  /*     This function verifies that ROIs that have had modifications to their sizes are still within */
  /*     the dimensions of the frame. If not, this function adjusts the dimensions (and, consequently,   */
  /*     the spatial coordinates) to conform to the frame dimensions. */
  /*  */
  /*     Note:  */
  /*  */
  /*     Intended only for use with integer types as rounding is not conducted. For modification for  */
  /*     use with floating-point types, rounding would be necessary as ROI values should be integers. */
  /*  */
  /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
  /*     the Responsible AI License (RAIL). */
  /* %%%%% Validate inputs %%%%%% */
  /* Exit if empty */
  if (ROIsProposed->size[0] != 0) {
    /* Validate whether input ROIsProposed is type int16. */
    /* Must be an integer type because no rounding is conducted. */
    /* Should be type int16 because the function is implemented to assign values of this type. */
    /* A non-matching type would be due to an implementation error. */
    /* %%%%% Running in code generation %%%%%% */
    /* When running in code generation, use for-loops. When running in Matlab code, use vectorization. */
    /* code generation running */
    /* Inline function */
    i = ROIsProposed->size[0];
    for (b_i = 0; b_i < i; b_i++) {
      /* %%%%% --- Verify, and adjust if necessary, X-coordinates and widths %%%%%% */
      /* Adjust left-side X-coordinate if exceeds frame dimensions: */
      ROI_left_X_ith = ROIsProposed->data[b_i];
      if (ROI_left_X_ith < 1) {
        ROI_left_X_ith = 1;

        /* recent code mod */
        ROIsProposed->data[b_i] = 1;
      } else {
        if (ROI_left_X_ith > VidObjWidth) {
          ROI_left_X_ith = VidObjWidth;

          /* recent code mod */
          ROIsProposed->data[b_i] = VidObjWidth;
        }
      }

      /* Adjust right-side X-coordinate if exceeds frame dimensions: */
      ROI_right_X_ith = (int16_T)((int16_T)(ROI_left_X_ith + ROIsProposed->
        data[b_i + ROIsProposed->size[0] * 2]) - 1);
      if (ROI_right_X_ith > VidObjWidth) {
        ROI_right_X_ith = VidObjWidth;
        ROIsProposed->data[b_i + ROIsProposed->size[0] * 2] = (int16_T)((int16_T)
          (VidObjWidth - ROI_left_X_ith) + 1);
      } else {
        if (ROI_right_X_ith < 1) {
          ROI_right_X_ith = 1;
          ROI_left_X_ith = 1;
          ROIsProposed->data[b_i] = 1;
          ROIsProposed->data[b_i + ROIsProposed->size[0] * 2] = 1;
        }
      }

      /* Adjust width if exceeds frame dimensions: */
      ROI_left_X_ith = (int16_T)((int16_T)(ROI_right_X_ith - ROI_left_X_ith) + 1);
      if (ROI_left_X_ith > VidObjWidth) {
        ROIsProposed->data[b_i + ROIsProposed->size[0] * 2] = VidObjWidth;
      } else {
        if (ROI_left_X_ith < 1) {
          ROIsProposed->data[b_i + ROIsProposed->size[0] * 2] = 1;
        }
      }

      /* %%%%% --- Verify, and adjust if necessary, Y-coordinates and heights %%%%%% */
      /* Adjust top-side Y-coordinate if exceeds frame dimensions: */
      ROI_left_X_ith = ROIsProposed->data[b_i + ROIsProposed->size[0]];
      if (ROI_left_X_ith < 1) {
        ROI_left_X_ith = 1;

        /* recent code mod */
        ROIsProposed->data[b_i + ROIsProposed->size[0]] = 1;
      } else {
        if (ROI_left_X_ith > VidObjHeight) {
          ROI_left_X_ith = VidObjHeight;

          /* recent code mod */
          ROIsProposed->data[b_i + ROIsProposed->size[0]] = VidObjHeight;
        }
      }

      /* Adjust bottom-side Y-coordinate if exceeds frame dimensions: */
      ROI_right_X_ith = (int16_T)((int16_T)(ROI_left_X_ith + ROIsProposed->
        data[b_i + ROIsProposed->size[0] * 3]) - 1);
      if (ROI_right_X_ith > VidObjHeight) {
        ROI_right_X_ith = VidObjHeight;
        ROIsProposed->data[b_i + ROIsProposed->size[0] * 3] = (int16_T)((int16_T)
          (VidObjHeight - ROI_left_X_ith) + 1);
      } else {
        if (ROI_right_X_ith < 1) {
          ROI_right_X_ith = 1;
          ROI_left_X_ith = 1;
          ROIsProposed->data[b_i + ROIsProposed->size[0]] = 1;
          ROIsProposed->data[b_i + ROIsProposed->size[0] * 3] = 1;
        }
      }

      /* Adjust height value if exceeds frame dimensions: */
      ROI_left_X_ith = (int16_T)((int16_T)(ROI_right_X_ith - ROI_left_X_ith) + 1);
      if (ROI_left_X_ith > VidObjHeight) {
        ROIsProposed->data[b_i + ROIsProposed->size[0] * 3] = VidObjHeight;
      } else {
        if (ROI_left_X_ith < 1) {
          ROIsProposed->data[b_i + ROIsProposed->size[0] * 3] = 1;
        }
      }
    }

    /* %%%%% Code generation not running %%%%%% */
  } else {
    /* Exit function */
  }

  /* end function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (ROIAdjustIfExceedsFrameDims_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /*                                   Example Code               Upp. Bounds   Var. Size (T/F)  Type */
  /* ROIsProposedCode   = coder.typeof( zeros(500, 4, 'int16'),    [inf, 4],     [1, 0] );        %int16 */
  /*            */
  /*        */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /* VidObjWidthCode  = int16(0);          */
  /* VidObjHeightCode = int16(0); */
  /*                    */
  /*  */
  /* %%%%% Set configurations to increase performance %%%%%% */
  /*  */
  /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
  /* "Optimization Strategies" */
  /*  */
  /* cfg = coder.config('mex'); */
  /* cfg.GlobalDataSyncMethod = 'NoSync'; */
  /* cfg.ConstantInputs = 'IgnoreValues'; */
  /* cfg.ExtrinsicCalls = true; %permit to show assert error */
  /* cfg.SaturateOnIntegerOverflow = false; */
  /* cfg.IntegrityChecks = false; */
  /* cfg.ResponsivenessChecks = false; */
  /*  */
  /*  */
  /* %%%%% Specify flags to minGW compiler to optimize execution speed %%%%%% */
  /*  */
  /* For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html */
  /*  */
  /* The flags are specified as part of the code-generation configuration object. A custom function, */
  /* setbuildargs, is used to specify these flags. For details on the function implementation, see the  */
  /* function file, which is located within folder FacePulseRate. This custom function is based upon  */
  /* Matlab guidance found in */
  /* https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function */
  /*  */
  /* setbuildargs will be evaluated from text within the code-generation object, so it is converted to  */
  /* a character vector prior to execution of the codegen command. */
  /*  */
  /* %%%%% --- Specify the flags as arguments to function setbuildargs %%%%%% */
  /*  */
  /* Argument buildInfo: this variable is assign by the caller (the codegen command executed below) and  */
  /* is not present in the base workspace. */
  /*  */
  /* Second argument: specify a cell array of compiler-specific flags, where each flag is a character  */
  /* vector. As function setbuildargs will be evaluated from text, use double ' quotes for each */
  /* character vector to maintain the charater vector, */
  /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
  /*  */
  /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})'; */
  /*  */
  /* Assign to code-generation configuration object */
  /* cfg.PostCodeGenCommand = setbuildargsAsText; */
  /*  */
  /*  */
  /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
  /*  */
  /* codegen ROIAdjustIfExceedsFrameDims.m -report -config cfg -args {ROIsProposedCode, VidObjWidthCode, VidObjHeightCode} */
  /*                  */
  /* } */
}

/* End of code generation (ROIAdjustIfExceedsFrameDims.c) */
