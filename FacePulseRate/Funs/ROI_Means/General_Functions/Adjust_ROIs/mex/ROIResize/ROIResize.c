/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIResize.c
 *
 * Code generation for function 'ROIResize'
 *
 */

/* Include files */
#include "ROIResize.h"
#include "ROIResize_emxutil.h"
#include "mwmathutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ROIResize(const emxArray_int16_T *ROI, const emxArray_int32_T
               *ROIsToResizeLinIdx, real_T ROIWidthResizeFactor, real_T
               ROIHeightResizeFactor, int16_T VidObjWidth, int16_T VidObjHeight,
               emxArray_int16_T *b_ROIResize)
{
  int32_T i;
  int32_T b_i;
  int32_T i1;
  int16_T ROI_width_ith;
  int16_T ROI_height_ith;

  /* ROIResize   Resize ROI(s) according to specifed scaling factors. */
  /*              */
  /*    Helper function to function FacePulseRate. */
  /*    Within function FacePulseRate, called by functions ROIMeans_FirstRead,  */
  /*    ROIMeans_FirstRead_CollectSkinColorSamples, ROIMeans_FirstRead_SetBoundingBoxes,   */
  /*    ROIMeans_SecondRead_SkinDetect, ROIMSIR, ROIMSIR_Interpolate, and ROIMSIR_FrameByFrameSmooth.  */
  /*  */
  /*    Code generation: Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*    Description: */
  /*  */
  /*    Resize the width and height of ROIs (ROI(:, 3 : 4)) of specified frames (ROIsToResizeLinIdx)    */
  /*    by specified scaling factors (ROIWidthResizeFactor and ROIHeightResizeFactor). After modifying  */
  /*    the width and height, adjust the upper-left X- and Y-coordinates (ROI(:, 1 : 2)) so that they */
  /*    are located at half the width and half the height from the unmodified centerpoint; by making  */
  /*    this adjustment, the resizing will have expanded from the centerpoint rather than from the */
  /*    upper-left corner. Then, adjust the ROI values so that none exceed the frame dimensions  */
  /*    (VidObjWidth and VidObjHeight). */
  /*  */
  /*    Inputs: */
  /*  */
  /*       ROI                     = ROI matrix (multiple ROIs) or row vector (one ROI). */
  /*                                 The columns in the ROI matrix or row vector indicate X-upper-left    */
  /*                                 corner, Y-upper-left corner width, and height, in pixels. Note */
  /*                                 that X refers to column indexing and Y refers to row indexing; */
  /*                                 because Y refers to row indexing, Y == 0 is located at the top, */
  /*                                 rather than the bottom, of the plane. */
  /*       ROIsToResizeLinIdx      = Linear index corresponding to the ROI matrix indicating ROIs to */
  /*                                 resize. Index can be non-consecutive. If resizing one ROI (a row */
  /*                                 vector), specify 1 for this argument. */
  /*       ROIWidthResizeFactor    = Width resizing factor. */
  /*       ROIHeightResizeFactor   = Height resizing factor. */
  /*       VidObjWidth             = Frame width (pixels).  */
  /*       VidObjHeight            = Frame height (pixels). */
  /*  */
  /*    Output: */
  /*  */
  /*       ROIResize               = Resized ROI matrix (multiple ROIs) or row vector (one ROI).                                 */
  /*  */
  /*    Note:  */
  /*  */
  /*    Intended only for use with integer types as rounding is not conducted. For modification for use  */
  /*    with floating-point types, rounding would be necessary as ROI values should be integers. */
  /*  */
  /*    Copyright (c) Douglas Magill (dpmdpm@vt.edu), June, 2020. Licensed under the MIT License and   */
  /*    the Responsible AI License (RAIL). */
  /* %%%%% Input validation %%%%%% */
  /* Validate whether input ROI is type int16. */
  /* Must be an integer type because no rounding is conducted. */
  /* Should be type int16 because the function is implemented to assign values of this type. */
  /* A non-matching type would be due to an implementation error. */
  /* %%%%% Running in code generation %%%%%% */
  /* When running in code generation, use for-loops. When running in Matlab code, use vectorization. */
  /* code generation running */
  /* Inline function */
  /* Preallocate output */
  i = b_ROIResize->size[0] * b_ROIResize->size[1];
  b_ROIResize->size[0] = ROIsToResizeLinIdx->size[1];
  b_ROIResize->size[1] = 4;
  emxEnsureCapacity_int16_T(b_ROIResize, i);

  /* Cast resizing factors to type single for efficiency */
  i = ROIsToResizeLinIdx->size[1];
  for (b_i = 0; b_i < i; b_i++) {
    /* %%%%% --- Resize width(s) and height(s) %%%%%%  */
    /* Convert to index of input ROI */
    i1 = ROIsToResizeLinIdx->data[b_i];
    ROI_width_ith = (int16_T)muSingleScalarRound((real32_T)ROI->data[(i1 +
      ROI->size[0] * 2) - 1] * (real32_T)ROIWidthResizeFactor);
    b_ROIResize->data[b_i + b_ROIResize->size[0] * 2] = ROI_width_ith;
    ROI_height_ith = (int16_T)muSingleScalarRound((real32_T)ROI->data[(i1 +
      ROI->size[0] * 3) - 1] * (real32_T)ROIHeightResizeFactor);
    b_ROIResize->data[b_i + b_ROIResize->size[0] * 3] = ROI_height_ith;

    /* %%%%% Adjust X- and Y-coordinates %%%%%% */
    /* Adjust the upper-left X- and Y-coordinates (ROI(:, 1 : 2)) so that they are located at half the */
    /* width and half the height from the unmodified centerpoint; by making this adjustment, the resizing  */
    /* will have expanded from the centerpoint rather than from the upper-left corner. */
    /* Optimize division by 2 by bit-wise operations. */
    /* Find centerpoint */
    /* Assign new X- and Y-coordinates */
    /* Expand from centerpoint based upon new height and width     */
    b_ROIResize->data[b_i] = (int16_T)((int16_T)(ROI->data[i1 - 1] + (ROI->data
      [(i1 + ROI->size[0] * 2) - 1] >> 1)) - (ROI_width_ith >> 1));
    b_ROIResize->data[b_i + b_ROIResize->size[0]] = (int16_T)((int16_T)
      (ROI->data[(i1 + ROI->size[0]) - 1] + (ROI->data[(i1 + ROI->size[0] * 3) -
      1] >> 1)) - (ROI_height_ith >> 1));
  }

  /* %%%%% --- Modify new ROI dimensions that exceed frame dimensions %%%%%%   */
  /* Function ROIAdjustIfExceedsFrameDims verifies if adjusted ROIs are within frame dimensions and, if  */
  /* not, adjusts the ROI values to conform to frame dimensions. */
  /* Note: ROIAdjustIfExceedsFrameDims is a custom function located within folder 'FacePulseRate'. */
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
  if (b_ROIResize->size[0] != 0) {
    /* Validate whether input ROIsProposed is type int16. */
    /* Must be an integer type because no rounding is conducted. */
    /* Should be type int16 because the function is implemented to assign values of this type. */
    /* A non-matching type would be due to an implementation error. */
    /* %%%%% Running in code generation %%%%%% */
    /* When running in code generation, use for-loops. When running in Matlab code, use vectorization. */
    /* code generation running */
    /* Inline function */
    i = b_ROIResize->size[0];
    for (b_i = 0; b_i < i; b_i++) {
      /* %%%%% --- Verify, and adjust if necessary, X-coordinates and widths %%%%%% */
      /* Adjust left-side X-coordinate if exceeds frame dimensions: */
      ROI_width_ith = b_ROIResize->data[b_i];
      if (ROI_width_ith < 1) {
        ROI_width_ith = 1;

        /* recent code mod */
        b_ROIResize->data[b_i] = 1;
      } else {
        if (ROI_width_ith > VidObjWidth) {
          ROI_width_ith = VidObjWidth;

          /* recent code mod */
          b_ROIResize->data[b_i] = VidObjWidth;
        }
      }

      /* Adjust right-side X-coordinate if exceeds frame dimensions: */
      ROI_height_ith = (int16_T)((int16_T)(ROI_width_ith + b_ROIResize->data[b_i
        + b_ROIResize->size[0] * 2]) - 1);
      if (ROI_height_ith > VidObjWidth) {
        ROI_height_ith = VidObjWidth;
        b_ROIResize->data[b_i + b_ROIResize->size[0] * 2] = (int16_T)((int16_T)
          (VidObjWidth - ROI_width_ith) + 1);
      } else {
        if (ROI_height_ith < 1) {
          ROI_height_ith = 1;
          ROI_width_ith = 1;
          b_ROIResize->data[b_i] = 1;
          b_ROIResize->data[b_i + b_ROIResize->size[0] * 2] = 1;
        }
      }

      /* Adjust width if exceeds frame dimensions: */
      ROI_width_ith = (int16_T)((int16_T)(ROI_height_ith - ROI_width_ith) + 1);
      if (ROI_width_ith > VidObjWidth) {
        b_ROIResize->data[b_i + b_ROIResize->size[0] * 2] = VidObjWidth;
      } else {
        if (ROI_width_ith < 1) {
          b_ROIResize->data[b_i + b_ROIResize->size[0] * 2] = 1;
        }
      }

      /* %%%%% --- Verify, and adjust if necessary, Y-coordinates and heights %%%%%% */
      /* Adjust top-side Y-coordinate if exceeds frame dimensions: */
      ROI_width_ith = b_ROIResize->data[b_i + b_ROIResize->size[0]];
      if (ROI_width_ith < 1) {
        ROI_width_ith = 1;

        /* recent code mod */
        b_ROIResize->data[b_i + b_ROIResize->size[0]] = 1;
      } else {
        if (ROI_width_ith > VidObjHeight) {
          ROI_width_ith = VidObjHeight;

          /* recent code mod */
          b_ROIResize->data[b_i + b_ROIResize->size[0]] = VidObjHeight;
        }
      }

      /* Adjust bottom-side Y-coordinate if exceeds frame dimensions: */
      ROI_height_ith = (int16_T)((int16_T)(ROI_width_ith + b_ROIResize->data[b_i
        + b_ROIResize->size[0] * 3]) - 1);
      if (ROI_height_ith > VidObjHeight) {
        ROI_height_ith = VidObjHeight;
        b_ROIResize->data[b_i + b_ROIResize->size[0] * 3] = (int16_T)((int16_T)
          (VidObjHeight - ROI_width_ith) + 1);
      } else {
        if (ROI_height_ith < 1) {
          ROI_height_ith = 1;
          ROI_width_ith = 1;
          b_ROIResize->data[b_i + b_ROIResize->size[0]] = 1;
          b_ROIResize->data[b_i + b_ROIResize->size[0] * 3] = 1;
        }
      }

      /* Adjust height value if exceeds frame dimensions: */
      ROI_height_ith = (int16_T)((int16_T)(ROI_height_ith - ROI_width_ith) + 1);
      if (ROI_height_ith > VidObjHeight) {
        b_ROIResize->data[b_i + b_ROIResize->size[0] * 3] = VidObjHeight;
      } else {
        if (ROI_height_ith < 1) {
          b_ROIResize->data[b_i + b_ROIResize->size[0] * 3] = 1;
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
  /* %%%%% Code generation not running %%%%%%     */
  /* end function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (ROIResize_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /*                                       Example Code               Upp. Bounds   Var. Size (T/F)  Type */
  /* ROICode                = coder.typeof( zeros(500, 4, 'int16'),    [inf, 4],     [1, 0] );        %int16 */
  /* ROIsToResizeLinIdxCode = coder.typeof( zeros(1, 500, 'int32'),   [1, inf],     [0, 1] );        %int32 */
  /*            */
  /*                       */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /* ROIWidthResizeFactorCode  = double(0); */
  /* ROIHeightResizeFactorCode = double(0); */
  /* VidObjWidthCode           = int16(0);          */
  /* VidObjHeightCode          = int16(0); */
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
  /* codegen ROIResize.m -report -config cfg -args {ROICode, ROIsToResizeLinIdxCode, ROIWidthResizeFactorCode, ROIHeightResizeFactorCode, VidObjWidthCode, VidObjHeightCode} */
  /*                  */
  /* } */
}

/* End of code generation (ROIResize.c) */
