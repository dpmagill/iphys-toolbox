/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect_RegionBoundariesByCategory.c
 *
 * Code generation for function 'SkinDetect_RegionBoundariesByCategory'
 *
 */

/* Include files */
#include "SkinDetect_RegionBoundariesByCategory.h"
#include "SkinDetect_emxutil.h"
#include "SkinDetect_types.h"
#include "bwlookup.h"
#include "rt_nonfinite.h"
#include "libmwmorphop_binary_tbb.h"
#include "mwmathutil.h"

/* Function Declarations */
static void b_Ops(emlrtCTX aTLS, real_T i, boolean_T RegionSelectedAnyTF,
                  uint16_T NRegionsCandidate, uint16_T NRegionsRejected, const
                  uint16_T RegionSelectedLinIdx_data[], const b_struct_T
                  RegionIndices_data[], const uint16_T
                  RegionsCandidateLinIdx_data[], const uint16_T
                  RegionsRejectedLinIdx_data[], int16_T VidObjHeight, const
                  int16_T BoundingBoxSkin[4], const real32_T RegionNPixels_data[],
                  int16_T nRows_IsSkinMask, int16_T nCols_IsSkinMask,
                  emxArray_uint32_T *RegionBoundaries_ith);

/* Function Definitions */
static void b_Ops(emlrtCTX aTLS, real_T i, boolean_T RegionSelectedAnyTF,
                  uint16_T NRegionsCandidate, uint16_T NRegionsRejected, const
                  uint16_T RegionSelectedLinIdx_data[], const b_struct_T
                  RegionIndices_data[], const uint16_T
                  RegionsCandidateLinIdx_data[], const uint16_T
                  RegionsRejectedLinIdx_data[], int16_T VidObjHeight, const
                  int16_T BoundingBoxSkin[4], const real32_T RegionNPixels_data[],
                  int16_T nRows_IsSkinMask, int16_T nCols_IsSkinMask,
                  emxArray_uint32_T *RegionBoundaries_ith)
{
  emxArray_boolean_T *BoundariesLogIdx;
  emxArray_boolean_T *RegionsLogIdx;
  real_T asizeT[2];
  real_T nsizeT[2];
  int32_T RegionNPixels_ith;
  int32_T b_i;
  int32_T c_i;
  int32_T j;
  int32_T loop_ub;
  uint32_T ROIForCrop_uint32_idx_0;
  uint32_T ROIForCrop_uint32_idx_1;
  uint32_T counter;
  uint16_T NRegions;
  boolean_T nhood[4];
  boolean_T guard1 = false;
  emlrtHeapReferenceStackEnterFcnR2012b(aTLS);

  /* end main function  */
  /* ============================================================================================= */
  /* Local functions */
  /* ============================================================================================= */
  /* ============================================================================================= */
  /* Ops   Return regions boundary indices for ith category (selected, candidate, or rejected). */
  /* %%%%% Code-generation settings %%%%% */
  /* Inline function */
  /* Declare variable-size variables: */
  /*                                         Upp. Bounds   Var. Size (T/F) */
  /* Preallocate vector for regions boundary indices */
  /* %%%%% Switch by category %%%%%% */
  emxInit_boolean_T(aTLS, &RegionsLogIdx, 2, true);
  emxInit_boolean_T(aTLS, &BoundariesLogIdx, 2, true);
  switch ((int32_T)i) {
   case 1:
    /* Note: SkinDetect_RegionBoundaries is a custom function located within folder 'FacePulseRate'. */
    /* Selected region */
    /* If there is a selected region */
    if (RegionSelectedAnyTF) {
      /* Scalar; type uint16. */
      NRegions = 1U;
    } else {
      /* Scalar; type uint16. */
      NRegions = 0U;
    }

    /* P pixels x 1 column vector; type uint32. */
    /* SkinDetect_RegionBoundaries   Return linear index of thickened boundaries for specified regions.  */
    /*                                                                                                    */
    /*     Helper function to function FacePulseRate.  */
    /*     Within function FacePulseRate, called by function SkinDetect_RegionBoundariesByCategory. */
    /*   */
    /*  */
    /*     Code Generation */
    /*     --------------- */
    /*  */
    /*     Can be called as a Matlab function or used for C-language code generation. */
    /*  */
    /*  */
    /*     Description */
    /*     ----------- */
    /*  */
    /*     Return a linear index of thickened region boundaries for later use for displaying regions on  */
    /*     output video. The boundaries are thickened for better visibility on output video. */
    /*  */
    /*  */
    /*     License */
    /*     ------- */
    /*  */
    /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
    /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
    /*     licensing, please contact the author. */
    /* %%%%% Code generation specifications %%%%%% */
    /* Specify inlining for faster code execution */
    /* Declare variables: */
    /*                                                  Upp. Bounds    Var. Size (T/F) */
    /* %%%%% Setup %%%%%% */
    /* Cast to type uint32 to prevent integer overflow */
    /* %%%%% Assign logical matrix where pixels corresponding to region pixels are true %%%%%%  */
    /* Assign blank logical matrix */
    b_i = RegionsLogIdx->size[0] * RegionsLogIdx->size[1];
    RegionsLogIdx->size[0] = nRows_IsSkinMask;
    RegionsLogIdx->size[1] = nCols_IsSkinMask;
    emxEnsureCapacity_boolean_T(RegionsLogIdx, b_i);
    loop_ub = nRows_IsSkinMask * nCols_IsSkinMask;
    for (b_i = 0; b_i < loop_ub; b_i++) {
      RegionsLogIdx->data[b_i] = false;
    }

    /* If more than one regions */
    if (NRegions == 1) {
      /* Scalar; type uint16. */
      /* Cast from type single to type int32 */
      loop_ub = RegionSelectedLinIdx_data[0] - 1;
      RegionNPixels_ith = (int32_T)muSingleScalarRound
        (RegionNPixels_data[loop_ub]);

      /* Loop across pixels within the ith region */
      for (j = 0; j < RegionNPixels_ith; j++) {
        /* Scalar; type uint32. */
        /* Reassign jjth pixel as true */
        RegionsLogIdx->data[(int32_T)RegionIndices_data[loop_ub]
          .PixelIdxList->data[j] - 1] = true;
      }

      /* If no regions   */
      /* Note: this is the least likely case, so it is evaluated last. */
      /* %%%%% Find boundary pixels of specified regions %%%%%%  */
      /* Assign look up table for boundary-finding operations */
      /* Return logical matrix where perimeter and hole boundaries of regions are true */
      /* Note: the output argument is equivalent to that produced by bwperim(MatrixLogical) but is faster. */
      /* Note: in this case, using an output name different from the input name results in a faster  */
      /* compiled function compared to using the same name. */
      /*  lookup table */
      bwlookup(RegionsLogIdx, BoundariesLogIdx);

      /* %%%%% Enlarge boundaries for better display %%%%%% */
      /* Enlarge boundaries for display purposes for use in function WriteFaceVideo_SkinDetectDiagnosis. */
      /* Do so by dilation. */
      /* Note: in this case, using an output name different from the input name results in a faster  */
      /* compiled function compared to using the same name. */
      /*  structuring element */
      b_i = RegionsLogIdx->size[0] * RegionsLogIdx->size[1];
      RegionsLogIdx->size[0] = BoundariesLogIdx->size[0];
      RegionsLogIdx->size[1] = BoundariesLogIdx->size[1];
      emxEnsureCapacity_boolean_T(RegionsLogIdx, b_i);
      nhood[0] = true;
      nhood[1] = true;
      nhood[2] = true;
      nhood[3] = true;
      asizeT[0] = BoundariesLogIdx->size[0];
      nsizeT[0] = 2.0;
      asizeT[1] = BoundariesLogIdx->size[1];
      nsizeT[1] = 2.0;
      dilate_binary_twod_tbb(&BoundariesLogIdx->data[0], &asizeT[0], 2.0,
        &nhood[0], &nsizeT[0], 2.0, &RegionsLogIdx->data[0]);

      /* %%%%% Adjust coordinates for use in annotating output video %%%%%% */
      /* The coordinates will be used by function WriteFaceVideo_SkinDetectDiagnosis to display the  */
      /* boundaries of regions.  */
      /* As the index returned by function bwperim corresponds to the ROI, but the index will be used for */
      /* the full video frame, the coordinates are adjusted to align with the full frame.       */
      /* Do so by adding back the [X, Y] coordinates that shifted during cropping. */
      /* Also, convert from [X, Y] coordinates to linear index */
      /* As the border pixels are irregularly distributed, a linear index will be more convenient when */
      /* superimposing pixels in the output video. */
      /* Convert to type uint32 for compatibility with output variable */
      ROIForCrop_uint32_idx_0 = (uint32_T)BoundingBoxSkin[0];
      ROIForCrop_uint32_idx_1 = (uint32_T)BoundingBoxSkin[1];

      /* Preallocate output variable */
      b_i = RegionBoundaries_ith->size[0];
      RegionBoundaries_ith->size[0] = (int32_T)((uint32_T)nRows_IsSkinMask *
        nCols_IsSkinMask);
      emxEnsureCapacity_uint32_T(RegionBoundaries_ith, b_i);
      counter = 0U;

      /* Loop across columns of DilatedBoundariesLogIdx  */
      b_i = nCols_IsSkinMask;
      for (c_i = 0; c_i < b_i; c_i++) {
        /* Loop across rows of DilatedBoundariesLogIdx */
        loop_ub = nRows_IsSkinMask;
        for (j = 0; j < loop_ub; j++) {
          /* Convert from subscript indices to a linear index for more efficient indexing */
          /* Scalar; type uint32. */
          /* Note: In compiled C code, the faster indexing outweighs the cost of this conversion. */
          /* If true value */
          if (RegionsLogIdx->data[(int32_T)(j + (uint32_T)c_i * nRows_IsSkinMask)])
          {
            counter++;

            /* Adjust Y-coordinate to align with full frame */
            /* Adjust X-coordinate to align with full frame */
            /* Convert from [X, Y] coordinates to linear index */
            RegionBoundaries_ith->data[(int32_T)counter - 1] = (j +
              ROIForCrop_uint32_idx_1) + ((c_i + ROIForCrop_uint32_idx_0) - 1U) *
              VidObjHeight;
          }
        }
      }

      /* Reassign to remove unused rows */
      b_i = RegionBoundaries_ith->size[0];
      if (1U > counter) {
        RegionBoundaries_ith->size[0] = 0;
      } else {
        RegionBoundaries_ith->size[0] = (int32_T)counter;
      }

      emxEnsureCapacity_uint32_T(RegionBoundaries_ith, b_i);
    } else {
      /* NRegions == 0     */
      RegionBoundaries_ith->size[0] = 0;
    }

    /* end function */
    /* ============================================================================================= */
    /* Code-generation and build script */
    /* ============================================================================================= */
    /* Code-generation and build script used to generate C-language code and create the compiled version  */
    /* (SkinDetect_RegionBoundaries_mex) of the function. */
    /* Note: at present, a separate compiled version of this function is not used as it is compiled  */
    /* within function SkinDetect. */
    /* { */
    /*  */
    /*  */
    /* %%%%% Modify function files for performance %%%%%% */
    /*  */
    /* Note: before running code generation, input validation was removed from the files for the  */
    /* following functions: */
    /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\bwlookup.m */
    /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\+images\+internal\+coder\morphop.m  */
    /*  */
    /* Specifically, in these files, the following validation functions were commented out: */
    /*  - narginchk */
    /*  - validateattributes */
    /*  */
    /* Note: Seperate files for these functions with these changes could not be made because code  */
    /* generation for these functions expects specific file names. Hence, after code generation, the   */
    /* input validation was added back to the files. */
    /* As these files are located in 'Program Files', admin access is required to edit them. */
    /*  */
    /*  */
    /* %%%%% Specify variable-size input arguments %%%%%% */
    /*  */
    /* See Matlab documentation for coder.typeof. */
    /*  */
    /* Input Argument                    Example Code               Upp. Bounds      Var. Size (T/F)  Type */
    /* RegionsLinIdxCode  = coder.typeof( zeros(400, 1, 'uint32'),   [inf, 1],        [1, 0] );        %uint32 */
    /* RegionNPixelsCode  = coder.typeof( zeros(400, 1, 'single'),   [400, 1],        [1, 0] );        %single */
    /*  */
    /* Specify element properties of RegionIndices.PixelIdxList */
    /* Element1 = ... */
    /*     coder.typeof(uint32(0), ... example code */
    /*                  [inf 1],   ... upper bounds */
    /*                  [1, 0]     ... variable size (T/F) */
    /*     ); */
    /*  */
    /* Non-scalar struct */
    /* RegionIndicesCode = ...  */
    /*     coder.typeof( ... */
    /*         struct( ...                                 */
    /*             'PixelIdxList', ... */
    /*              Element1 ... */
    /*         ), ... */
    /*         [400 1],   ... upper bounds */
    /*         [1, 0]     ... variable size (T/F) */
    /*     ); */
    /*  */
    /*                   */
    /* %%%%% Specify fixed-size input arguments %%%%%% */
    /*  */
    /* NRegionsCode               = uint16(0); */
    /* ROIForCropCode             = zeros(1, 4, 'int16');                                                      */
    /* VidObjHeightCode           = int16(0);                                                                  */
    /* nRows_IsSkinMask_int16Code = int16(0); */
    /* nCols_IsSkinMask_int16Code = int16(0); */
    /*  */
    /* %%%%% Set configurations to increase performance %%%%%% */
    /*  */
    /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
    /* "Optimization Strategies" */
    /*  */
    /* cfg = coder.config('mex'); */
    /* cfg.GlobalDataSyncMethod = 'NoSync'; */
    /* cfg.ConstantInputs = 'IgnoreValues'; */
    /* cfg.ExtrinsicCalls = false; */
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
    /* Argument buildInfo: this variable is assign by the caller (the codegen command executed  */
    /* below) and is not present in the base workspace. */
    /*  */
    /* Second argument: specify a cell array of compiler-specific flags, where each flag is a  */
    /* character vector. As function setbuildargs will be evaluated from text, use double ' quotes for  */
    /* each character vector to maintain the charater vector, */
    /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
    /*  */
    /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast'' ''-fsingle-precision-constant''})'; */
    /*  */
    /* Assign to code-generation configuration object */
    /* cfg.PostCodeGenCommand = setbuildargsAsText; */
    /*  */
    /*  */
    /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
    /*  */
    /* codegen SkinDetect_RegionBoundariesT.m -report -config cfg -args {RegionsLinIdxCode, NRegionsCode, RegionIndicesCode, RegionNPixelsCode, ROIForCropCode, VidObjHeightCode, nRows_IsSkinMask_int16Code, nCols_IsSkinMask_int16Code} */
    /*  */
    /* } */
    /* Candidate regions */
    break;

   case 2:
    /* P pixels x 1 column vector; type uint32. */
    /* SkinDetect_RegionBoundaries   Return linear index of thickened boundaries for specified regions.  */
    /*                                                                                                    */
    /*     Helper function to function FacePulseRate.  */
    /*     Within function FacePulseRate, called by function SkinDetect_RegionBoundariesByCategory. */
    /*   */
    /*  */
    /*     Code Generation */
    /*     --------------- */
    /*  */
    /*     Can be called as a Matlab function or used for C-language code generation. */
    /*  */
    /*  */
    /*     Description */
    /*     ----------- */
    /*  */
    /*     Return a linear index of thickened region boundaries for later use for displaying regions on  */
    /*     output video. The boundaries are thickened for better visibility on output video. */
    /*  */
    /*  */
    /*     License */
    /*     ------- */
    /*  */
    /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
    /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
    /*     licensing, please contact the author. */
    /* %%%%% Code generation specifications %%%%%% */
    /* Specify inlining for faster code execution */
    /* Declare variables: */
    /*                                                  Upp. Bounds    Var. Size (T/F) */
    /* %%%%% Setup %%%%%% */
    /* Cast to type uint32 to prevent integer overflow */
    /* %%%%% Assign logical matrix where pixels corresponding to region pixels are true %%%%%%  */
    /* Assign blank logical matrix */
    b_i = RegionsLogIdx->size[0] * RegionsLogIdx->size[1];
    RegionsLogIdx->size[0] = nRows_IsSkinMask;
    RegionsLogIdx->size[1] = nCols_IsSkinMask;
    emxEnsureCapacity_boolean_T(RegionsLogIdx, b_i);
    loop_ub = nRows_IsSkinMask * nCols_IsSkinMask;
    for (b_i = 0; b_i < loop_ub; b_i++) {
      RegionsLogIdx->data[b_i] = false;
    }

    /* If more than one regions */
    guard1 = false;
    if (NRegionsCandidate > 1) {
      /* Loop across regions */
      b_i = NRegionsCandidate;
      for (c_i = 0; c_i < b_i; c_i++) {
        /* Scalar; type uint16. */
        /* Cast from type single to type int32 */
        loop_ub = RegionsCandidateLinIdx_data[c_i] - 1;
        RegionNPixels_ith = (int32_T)muSingleScalarRound
          (RegionNPixels_data[loop_ub]);

        /* Loop across pixels within the ith region */
        for (j = 0; j < RegionNPixels_ith; j++) {
          /* Scalar; type uint32. */
          /* Reassign jjth pixel as true */
          RegionsLogIdx->data[(int32_T)RegionIndices_data[loop_ub].
            PixelIdxList->data[j] - 1] = true;
        }
      }

      /* If only one region     */
      /* Note: if there is a selected region, it will consist of only 1 region.      */
      guard1 = true;
    } else if (NRegionsCandidate == 1) {
      /* Scalar; type uint16. */
      /* Cast from type single to type int32 */
      loop_ub = RegionsCandidateLinIdx_data[0] - 1;
      RegionNPixels_ith = (int32_T)muSingleScalarRound
        (RegionNPixels_data[RegionsCandidateLinIdx_data[0] - 1]);

      /* Loop across pixels within the ith region */
      for (j = 0; j < RegionNPixels_ith; j++) {
        /* Scalar; type uint32. */
        /* Reassign jjth pixel as true */
        RegionsLogIdx->data[(int32_T)RegionIndices_data[loop_ub]
          .PixelIdxList->data[j] - 1] = true;
      }

      /* If no regions   */
      /* Note: this is the least likely case, so it is evaluated last. */
      guard1 = true;
    } else {
      /* NRegions == 0     */
      RegionBoundaries_ith->size[0] = 0;
    }

    if (guard1) {
      /* %%%%% Find boundary pixels of specified regions %%%%%%  */
      /* Assign look up table for boundary-finding operations */
      /* Return logical matrix where perimeter and hole boundaries of regions are true */
      /* Note: the output argument is equivalent to that produced by bwperim(MatrixLogical) but is faster. */
      /* Note: in this case, using an output name different from the input name results in a faster  */
      /* compiled function compared to using the same name. */
      /*  lookup table */
      bwlookup(RegionsLogIdx, BoundariesLogIdx);

      /* %%%%% Enlarge boundaries for better display %%%%%% */
      /* Enlarge boundaries for display purposes for use in function WriteFaceVideo_SkinDetectDiagnosis. */
      /* Do so by dilation. */
      /* Note: in this case, using an output name different from the input name results in a faster  */
      /* compiled function compared to using the same name. */
      /*  structuring element */
      b_i = RegionsLogIdx->size[0] * RegionsLogIdx->size[1];
      RegionsLogIdx->size[0] = BoundariesLogIdx->size[0];
      RegionsLogIdx->size[1] = BoundariesLogIdx->size[1];
      emxEnsureCapacity_boolean_T(RegionsLogIdx, b_i);
      nhood[0] = true;
      nhood[1] = true;
      nhood[2] = true;
      nhood[3] = true;
      asizeT[0] = BoundariesLogIdx->size[0];
      nsizeT[0] = 2.0;
      asizeT[1] = BoundariesLogIdx->size[1];
      nsizeT[1] = 2.0;
      dilate_binary_twod_tbb(&BoundariesLogIdx->data[0], &asizeT[0], 2.0,
        &nhood[0], &nsizeT[0], 2.0, &RegionsLogIdx->data[0]);

      /* %%%%% Adjust coordinates for use in annotating output video %%%%%% */
      /* The coordinates will be used by function WriteFaceVideo_SkinDetectDiagnosis to display the  */
      /* boundaries of regions.  */
      /* As the index returned by function bwperim corresponds to the ROI, but the index will be used for */
      /* the full video frame, the coordinates are adjusted to align with the full frame.       */
      /* Do so by adding back the [X, Y] coordinates that shifted during cropping. */
      /* Also, convert from [X, Y] coordinates to linear index */
      /* As the border pixels are irregularly distributed, a linear index will be more convenient when */
      /* superimposing pixels in the output video. */
      /* Convert to type uint32 for compatibility with output variable */
      ROIForCrop_uint32_idx_0 = (uint32_T)BoundingBoxSkin[0];
      ROIForCrop_uint32_idx_1 = (uint32_T)BoundingBoxSkin[1];

      /* Preallocate output variable */
      b_i = RegionBoundaries_ith->size[0];
      RegionBoundaries_ith->size[0] = (int32_T)((uint32_T)nRows_IsSkinMask *
        nCols_IsSkinMask);
      emxEnsureCapacity_uint32_T(RegionBoundaries_ith, b_i);
      counter = 0U;

      /* Loop across columns of DilatedBoundariesLogIdx  */
      b_i = nCols_IsSkinMask;
      for (c_i = 0; c_i < b_i; c_i++) {
        /* Loop across rows of DilatedBoundariesLogIdx */
        loop_ub = nRows_IsSkinMask;
        for (j = 0; j < loop_ub; j++) {
          /* Convert from subscript indices to a linear index for more efficient indexing */
          /* Scalar; type uint32. */
          /* Note: In compiled C code, the faster indexing outweighs the cost of this conversion. */
          /* If true value */
          if (RegionsLogIdx->data[(int32_T)(j + (uint32_T)c_i * nRows_IsSkinMask)])
          {
            counter++;

            /* Adjust Y-coordinate to align with full frame */
            /* Adjust X-coordinate to align with full frame */
            /* Convert from [X, Y] coordinates to linear index */
            RegionBoundaries_ith->data[(int32_T)counter - 1] = (j +
              ROIForCrop_uint32_idx_1) + ((c_i + ROIForCrop_uint32_idx_0) - 1U) *
              VidObjHeight;
          }
        }
      }

      /* Reassign to remove unused rows */
      b_i = RegionBoundaries_ith->size[0];
      if (1U > counter) {
        RegionBoundaries_ith->size[0] = 0;
      } else {
        RegionBoundaries_ith->size[0] = (int32_T)counter;
      }

      emxEnsureCapacity_uint32_T(RegionBoundaries_ith, b_i);
    }

    /* end function */
    /* ============================================================================================= */
    /* Code-generation and build script */
    /* ============================================================================================= */
    /* Code-generation and build script used to generate C-language code and create the compiled version  */
    /* (SkinDetect_RegionBoundaries_mex) of the function. */
    /* Note: at present, a separate compiled version of this function is not used as it is compiled  */
    /* within function SkinDetect. */
    /* { */
    /*  */
    /*  */
    /* %%%%% Modify function files for performance %%%%%% */
    /*  */
    /* Note: before running code generation, input validation was removed from the files for the  */
    /* following functions: */
    /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\bwlookup.m */
    /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\+images\+internal\+coder\morphop.m  */
    /*  */
    /* Specifically, in these files, the following validation functions were commented out: */
    /*  - narginchk */
    /*  - validateattributes */
    /*  */
    /* Note: Seperate files for these functions with these changes could not be made because code  */
    /* generation for these functions expects specific file names. Hence, after code generation, the   */
    /* input validation was added back to the files. */
    /* As these files are located in 'Program Files', admin access is required to edit them. */
    /*  */
    /*  */
    /* %%%%% Specify variable-size input arguments %%%%%% */
    /*  */
    /* See Matlab documentation for coder.typeof. */
    /*  */
    /* Input Argument                    Example Code               Upp. Bounds      Var. Size (T/F)  Type */
    /* RegionsLinIdxCode  = coder.typeof( zeros(400, 1, 'uint32'),   [inf, 1],        [1, 0] );        %uint32 */
    /* RegionNPixelsCode  = coder.typeof( zeros(400, 1, 'single'),   [400, 1],        [1, 0] );        %single */
    /*  */
    /* Specify element properties of RegionIndices.PixelIdxList */
    /* Element1 = ... */
    /*     coder.typeof(uint32(0), ... example code */
    /*                  [inf 1],   ... upper bounds */
    /*                  [1, 0]     ... variable size (T/F) */
    /*     ); */
    /*  */
    /* Non-scalar struct */
    /* RegionIndicesCode = ...  */
    /*     coder.typeof( ... */
    /*         struct( ...                                 */
    /*             'PixelIdxList', ... */
    /*              Element1 ... */
    /*         ), ... */
    /*         [400 1],   ... upper bounds */
    /*         [1, 0]     ... variable size (T/F) */
    /*     ); */
    /*  */
    /*                   */
    /* %%%%% Specify fixed-size input arguments %%%%%% */
    /*  */
    /* NRegionsCode               = uint16(0); */
    /* ROIForCropCode             = zeros(1, 4, 'int16');                                                      */
    /* VidObjHeightCode           = int16(0);                                                                  */
    /* nRows_IsSkinMask_int16Code = int16(0); */
    /* nCols_IsSkinMask_int16Code = int16(0); */
    /*  */
    /* %%%%% Set configurations to increase performance %%%%%% */
    /*  */
    /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
    /* "Optimization Strategies" */
    /*  */
    /* cfg = coder.config('mex'); */
    /* cfg.GlobalDataSyncMethod = 'NoSync'; */
    /* cfg.ConstantInputs = 'IgnoreValues'; */
    /* cfg.ExtrinsicCalls = false; */
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
    /* Argument buildInfo: this variable is assign by the caller (the codegen command executed  */
    /* below) and is not present in the base workspace. */
    /*  */
    /* Second argument: specify a cell array of compiler-specific flags, where each flag is a  */
    /* character vector. As function setbuildargs will be evaluated from text, use double ' quotes for  */
    /* each character vector to maintain the charater vector, */
    /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
    /*  */
    /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast'' ''-fsingle-precision-constant''})'; */
    /*  */
    /* Assign to code-generation configuration object */
    /* cfg.PostCodeGenCommand = setbuildargsAsText; */
    /*  */
    /*  */
    /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
    /*  */
    /* codegen SkinDetect_RegionBoundariesT.m -report -config cfg -args {RegionsLinIdxCode, NRegionsCode, RegionIndicesCode, RegionNPixelsCode, ROIForCropCode, VidObjHeightCode, nRows_IsSkinMask_int16Code, nCols_IsSkinMask_int16Code} */
    /*  */
    /* } */
    /* Rejected regions */
    break;

   default:
    /* P pixels x 1 column vector; type uint32. */
    /* SkinDetect_RegionBoundaries   Return linear index of thickened boundaries for specified regions.  */
    /*                                                                                                    */
    /*     Helper function to function FacePulseRate.  */
    /*     Within function FacePulseRate, called by function SkinDetect_RegionBoundariesByCategory. */
    /*   */
    /*  */
    /*     Code Generation */
    /*     --------------- */
    /*  */
    /*     Can be called as a Matlab function or used for C-language code generation. */
    /*  */
    /*  */
    /*     Description */
    /*     ----------- */
    /*  */
    /*     Return a linear index of thickened region boundaries for later use for displaying regions on  */
    /*     output video. The boundaries are thickened for better visibility on output video. */
    /*  */
    /*  */
    /*     License */
    /*     ------- */
    /*  */
    /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
    /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
    /*     licensing, please contact the author. */
    /* %%%%% Code generation specifications %%%%%% */
    /* Specify inlining for faster code execution */
    /* Declare variables: */
    /*                                                  Upp. Bounds    Var. Size (T/F) */
    /* %%%%% Setup %%%%%% */
    /* Cast to type uint32 to prevent integer overflow */
    /* %%%%% Assign logical matrix where pixels corresponding to region pixels are true %%%%%%  */
    /* Assign blank logical matrix */
    b_i = RegionsLogIdx->size[0] * RegionsLogIdx->size[1];
    RegionsLogIdx->size[0] = nRows_IsSkinMask;
    RegionsLogIdx->size[1] = nCols_IsSkinMask;
    emxEnsureCapacity_boolean_T(RegionsLogIdx, b_i);
    loop_ub = nRows_IsSkinMask * nCols_IsSkinMask;
    for (b_i = 0; b_i < loop_ub; b_i++) {
      RegionsLogIdx->data[b_i] = false;
    }

    /* If more than one regions */
    guard1 = false;
    if (NRegionsRejected > 1) {
      /* Loop across regions */
      b_i = NRegionsRejected;
      for (c_i = 0; c_i < b_i; c_i++) {
        /* Scalar; type uint16. */
        /* Cast from type single to type int32 */
        loop_ub = RegionsRejectedLinIdx_data[c_i] - 1;
        RegionNPixels_ith = (int32_T)muSingleScalarRound
          (RegionNPixels_data[loop_ub]);

        /* Loop across pixels within the ith region */
        for (j = 0; j < RegionNPixels_ith; j++) {
          /* Scalar; type uint32. */
          /* Reassign jjth pixel as true */
          RegionsLogIdx->data[(int32_T)RegionIndices_data[loop_ub].
            PixelIdxList->data[j] - 1] = true;
        }
      }

      /* If only one region     */
      /* Note: if there is a selected region, it will consist of only 1 region.      */
      guard1 = true;
    } else if (NRegionsRejected == 1) {
      /* Scalar; type uint16. */
      /* Cast from type single to type int32 */
      loop_ub = RegionsRejectedLinIdx_data[0] - 1;
      RegionNPixels_ith = (int32_T)muSingleScalarRound
        (RegionNPixels_data[RegionsRejectedLinIdx_data[0] - 1]);

      /* Loop across pixels within the ith region */
      for (j = 0; j < RegionNPixels_ith; j++) {
        /* Scalar; type uint32. */
        /* Reassign jjth pixel as true */
        RegionsLogIdx->data[(int32_T)RegionIndices_data[loop_ub]
          .PixelIdxList->data[j] - 1] = true;
      }

      /* If no regions   */
      /* Note: this is the least likely case, so it is evaluated last. */
      guard1 = true;
    } else {
      /* NRegions == 0     */
      RegionBoundaries_ith->size[0] = 0;
    }

    if (guard1) {
      /* %%%%% Find boundary pixels of specified regions %%%%%%  */
      /* Assign look up table for boundary-finding operations */
      /* Return logical matrix where perimeter and hole boundaries of regions are true */
      /* Note: the output argument is equivalent to that produced by bwperim(MatrixLogical) but is faster. */
      /* Note: in this case, using an output name different from the input name results in a faster  */
      /* compiled function compared to using the same name. */
      /*  lookup table */
      bwlookup(RegionsLogIdx, BoundariesLogIdx);

      /* %%%%% Enlarge boundaries for better display %%%%%% */
      /* Enlarge boundaries for display purposes for use in function WriteFaceVideo_SkinDetectDiagnosis. */
      /* Do so by dilation. */
      /* Note: in this case, using an output name different from the input name results in a faster  */
      /* compiled function compared to using the same name. */
      /*  structuring element */
      b_i = RegionsLogIdx->size[0] * RegionsLogIdx->size[1];
      RegionsLogIdx->size[0] = BoundariesLogIdx->size[0];
      RegionsLogIdx->size[1] = BoundariesLogIdx->size[1];
      emxEnsureCapacity_boolean_T(RegionsLogIdx, b_i);
      nhood[0] = true;
      nhood[1] = true;
      nhood[2] = true;
      nhood[3] = true;
      asizeT[0] = BoundariesLogIdx->size[0];
      nsizeT[0] = 2.0;
      asizeT[1] = BoundariesLogIdx->size[1];
      nsizeT[1] = 2.0;
      dilate_binary_twod_tbb(&BoundariesLogIdx->data[0], &asizeT[0], 2.0,
        &nhood[0], &nsizeT[0], 2.0, &RegionsLogIdx->data[0]);

      /* %%%%% Adjust coordinates for use in annotating output video %%%%%% */
      /* The coordinates will be used by function WriteFaceVideo_SkinDetectDiagnosis to display the  */
      /* boundaries of regions.  */
      /* As the index returned by function bwperim corresponds to the ROI, but the index will be used for */
      /* the full video frame, the coordinates are adjusted to align with the full frame.       */
      /* Do so by adding back the [X, Y] coordinates that shifted during cropping. */
      /* Also, convert from [X, Y] coordinates to linear index */
      /* As the border pixels are irregularly distributed, a linear index will be more convenient when */
      /* superimposing pixels in the output video. */
      /* Convert to type uint32 for compatibility with output variable */
      ROIForCrop_uint32_idx_0 = (uint32_T)BoundingBoxSkin[0];
      ROIForCrop_uint32_idx_1 = (uint32_T)BoundingBoxSkin[1];

      /* Preallocate output variable */
      b_i = RegionBoundaries_ith->size[0];
      RegionBoundaries_ith->size[0] = (int32_T)((uint32_T)nRows_IsSkinMask *
        nCols_IsSkinMask);
      emxEnsureCapacity_uint32_T(RegionBoundaries_ith, b_i);
      counter = 0U;

      /* Loop across columns of DilatedBoundariesLogIdx  */
      b_i = nCols_IsSkinMask;
      for (c_i = 0; c_i < b_i; c_i++) {
        /* Loop across rows of DilatedBoundariesLogIdx */
        loop_ub = nRows_IsSkinMask;
        for (j = 0; j < loop_ub; j++) {
          /* Convert from subscript indices to a linear index for more efficient indexing */
          /* Scalar; type uint32. */
          /* Note: In compiled C code, the faster indexing outweighs the cost of this conversion. */
          /* If true value */
          if (RegionsLogIdx->data[(int32_T)(j + (uint32_T)c_i * nRows_IsSkinMask)])
          {
            counter++;

            /* Adjust Y-coordinate to align with full frame */
            /* Adjust X-coordinate to align with full frame */
            /* Convert from [X, Y] coordinates to linear index */
            RegionBoundaries_ith->data[(int32_T)counter - 1] = (j +
              ROIForCrop_uint32_idx_1) + ((c_i + ROIForCrop_uint32_idx_0) - 1U) *
              VidObjHeight;
          }
        }
      }

      /* Reassign to remove unused rows */
      b_i = RegionBoundaries_ith->size[0];
      if (1U > counter) {
        RegionBoundaries_ith->size[0] = 0;
      } else {
        RegionBoundaries_ith->size[0] = (int32_T)counter;
      }

      emxEnsureCapacity_uint32_T(RegionBoundaries_ith, b_i);
    }

    /* end function */
    /* ============================================================================================= */
    /* Code-generation and build script */
    /* ============================================================================================= */
    /* Code-generation and build script used to generate C-language code and create the compiled version  */
    /* (SkinDetect_RegionBoundaries_mex) of the function. */
    /* Note: at present, a separate compiled version of this function is not used as it is compiled  */
    /* within function SkinDetect. */
    /* { */
    /*  */
    /*  */
    /* %%%%% Modify function files for performance %%%%%% */
    /*  */
    /* Note: before running code generation, input validation was removed from the files for the  */
    /* following functions: */
    /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\bwlookup.m */
    /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\+images\+internal\+coder\morphop.m  */
    /*  */
    /* Specifically, in these files, the following validation functions were commented out: */
    /*  - narginchk */
    /*  - validateattributes */
    /*  */
    /* Note: Seperate files for these functions with these changes could not be made because code  */
    /* generation for these functions expects specific file names. Hence, after code generation, the   */
    /* input validation was added back to the files. */
    /* As these files are located in 'Program Files', admin access is required to edit them. */
    /*  */
    /*  */
    /* %%%%% Specify variable-size input arguments %%%%%% */
    /*  */
    /* See Matlab documentation for coder.typeof. */
    /*  */
    /* Input Argument                    Example Code               Upp. Bounds      Var. Size (T/F)  Type */
    /* RegionsLinIdxCode  = coder.typeof( zeros(400, 1, 'uint32'),   [inf, 1],        [1, 0] );        %uint32 */
    /* RegionNPixelsCode  = coder.typeof( zeros(400, 1, 'single'),   [400, 1],        [1, 0] );        %single */
    /*  */
    /* Specify element properties of RegionIndices.PixelIdxList */
    /* Element1 = ... */
    /*     coder.typeof(uint32(0), ... example code */
    /*                  [inf 1],   ... upper bounds */
    /*                  [1, 0]     ... variable size (T/F) */
    /*     ); */
    /*  */
    /* Non-scalar struct */
    /* RegionIndicesCode = ...  */
    /*     coder.typeof( ... */
    /*         struct( ...                                 */
    /*             'PixelIdxList', ... */
    /*              Element1 ... */
    /*         ), ... */
    /*         [400 1],   ... upper bounds */
    /*         [1, 0]     ... variable size (T/F) */
    /*     ); */
    /*  */
    /*                   */
    /* %%%%% Specify fixed-size input arguments %%%%%% */
    /*  */
    /* NRegionsCode               = uint16(0); */
    /* ROIForCropCode             = zeros(1, 4, 'int16');                                                      */
    /* VidObjHeightCode           = int16(0);                                                                  */
    /* nRows_IsSkinMask_int16Code = int16(0); */
    /* nCols_IsSkinMask_int16Code = int16(0); */
    /*  */
    /* %%%%% Set configurations to increase performance %%%%%% */
    /*  */
    /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
    /* "Optimization Strategies" */
    /*  */
    /* cfg = coder.config('mex'); */
    /* cfg.GlobalDataSyncMethod = 'NoSync'; */
    /* cfg.ConstantInputs = 'IgnoreValues'; */
    /* cfg.ExtrinsicCalls = false; */
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
    /* Argument buildInfo: this variable is assign by the caller (the codegen command executed  */
    /* below) and is not present in the base workspace. */
    /*  */
    /* Second argument: specify a cell array of compiler-specific flags, where each flag is a  */
    /* character vector. As function setbuildargs will be evaluated from text, use double ' quotes for  */
    /* each character vector to maintain the charater vector, */
    /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
    /*  */
    /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast'' ''-fsingle-precision-constant''})'; */
    /*  */
    /* Assign to code-generation configuration object */
    /* cfg.PostCodeGenCommand = setbuildargsAsText; */
    /*  */
    /*  */
    /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
    /*  */
    /* codegen SkinDetect_RegionBoundariesT.m -report -config cfg -args {RegionsLinIdxCode, NRegionsCode, RegionIndicesCode, RegionNPixelsCode, ROIForCropCode, VidObjHeightCode, nRows_IsSkinMask_int16Code, nCols_IsSkinMask_int16Code} */
    /*  */
    /* } */
    break;
  }

  emxFree_boolean_T(&BoundariesLogIdx);
  emxFree_boolean_T(&RegionsLogIdx);

  /* end local function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (SkinDetect_RegionBoundariesByCategory_mex) of the function. */
  /* Note: at present, a separate compiled version of this function is not used as it is compiled  */
  /* within function SkinDetect. */
  /* { */
  /*        */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /* Specify element properties of RegionIndices.PixelIdxList */
  /* Element1 = ... */
  /*     coder.typeof(double(0), ... example code */
  /*                  [inf 1],   ... upper bounds */
  /*                  [1, 0]     ... variable size (T/F) */
  /*     ); */
  /*  */
  /* Non-scalar struct */
  /* RegionIndicesCode = ...  */
  /*     coder.typeof( ... */
  /*         struct( ...                                 */
  /*             'PixelIdxList', ... */
  /*              Element1 ... */
  /*         ), ... */
  /*         [400 1],   ... upper bounds */
  /*         [1, 0]     ... variable size (T/F) */
  /*     ); */
  /*  */
  /* Input Argument                            Example Code                 Upp. Bounds     Var. Size (T/F)  Type */
  /* RegionSelectedLinIdxCode   = coder.typeof( zeros(400, 1, 'uint32'),     [400, 1],       [1, 0] );        %uint32 */
  /* RegionsCandidateLinIdxCode = coder.typeof( zeros(400, 1, 'uint32'),     [400, 1],       [1, 0] );        %uint32 */
  /* RegionsRejectedLinIdxCode  = coder.typeof( zeros(400, 1, 'uint32'),     [400, 1],       [1, 0] );        %uint32 */
  /* RegionNPixelsCode          = coder.typeof( zeros(400, 1, 'single'),     [400, 1],       [1, 0] );        %single */
  /* IsSkinMaskCode             = coder.typeof( false(500, 500),             [inf, inf],     [1, 1] );        %logical */
  /*  */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /*                             Example Code                                                                  */
  /* RegionSelectedAnyTFCode    = false; */
  /* RegionsCandidateAnyTFCode  = false; */
  /* RegionsRejectedAnyTFCode   = false;   */
  /* VidObjHeight_SingleCode    = single(0); */
  /* BoundingBoxSkin_SingleCode = zeros(1, 4, 'single'); */
  /*  */
  /*  */
  /* %%%%% Set configurations to increase performance %%%%%% */
  /*  */
  /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
  /* "Optimization Strategies" */
  /* cfg = coder.config('mex'); */
  /* cfg.GlobalDataSyncMethod = 'NoSync'; */
  /* cfg.ConstantInputs = 'IgnoreValues'; */
  /* cfg.ExtrinsicCalls = false; */
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
  /* vector. As function setbuildargs will be evaluated from text, use double ' quotes for each  */
  /* character vector to maintain the charater vector, */
  /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
  /*  */
  /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast'' ''-fsingle-precision-constant''})'; */
  /*  */
  /* Assign to code-generation configuration object */
  /* cfg.PostCodeGenCommand = setbuildargsAsText; */
  /*  */
  /*  */
  /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
  /*  */
  /* codegen SkinDetect_RegionBoundariesByCategory.m -report -config cfg -args {RegionSelectedAnyTFCode, RegionsCandidateAnyTFCode, RegionsRejectedAnyTFCode, RegionSelectedLogIdxCode, RegionIndicesCode, RegionsCandidateLogIdxCode, RegionsRejectedLogIdxCode, VidObjHeight_SingleCode, BoundingBoxSkin_SingleCode, RegionNPixelsCode, IsSkinMaskCode} */
  /*  */
  /* } */
  emlrtHeapReferenceStackLeaveFcnR2012b(aTLS);
}

void c_SkinDetect_RegionBoundariesBy(emlrtCTX aTLS, boolean_T
  RegionSelectedAnyTF, uint16_T NRegionsCandidate, uint16_T NRegionsRejected,
  const uint16_T RegionSelectedLinIdx_data[], const b_struct_T
  RegionIndices_data[], const uint16_T RegionsCandidateLinIdx_data[], const
  uint16_T RegionsRejectedLinIdx_data[], int16_T VidObjHeight, const int16_T
  BoundingBoxSkin[4], const real32_T RegionNPixels_data[], int16_T
  nRows_IsSkinMask, int16_T nCols_IsSkinMask, cell_wrap_32 RegionBoundaries[3])
{
  jmp_buf emlrtJBEnviron;
  jmp_buf * volatile emlrtJBStack;
  int32_T i;
  boolean_T emlrtHadParallelError = false;

  /* SkinDetect_RegionBoundariesByCategory   Return linear indices of thickened boundaries for the  */
  /*                                         regions of each category (selected, candidate, rejected).  */
  /*                                                                                                    */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, called by function SkinDetect_RecordDiagnosticData. */
  /*   */
  /*  */
  /*     Code Generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*     Compiled file: The compiled file included in folder FacePulseRate     */
  /*     (SkinDetect_RegionBoundariesByCategory_mex.mexw64) only compatible on Windows platforms. */
  /*  */
  /*  */
  /*     Description */
  /*     ----------- */
  /*  */
  /*     Return a linear index of thickened region boundaries for later use for displaying regions on  */
  /*     output video. The boundaries are thickened for better visibility on output video. */
  /*  */
  /*     This function acts as a wrapper function to function SkinDetect_RegionBoundaries to facilitate */
  /*     the use of a parallel for loop. */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL  */
  /*     licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial   */
  /*     licensing, please contact the author.           */
  /* %%%%% Code-generation settings %%%%% */
  /* Inline function */
  /* Declare variable-size variables: */
  /*                                         Upp. Bounds   Var. Size (T/F) */
  /* Preallocate variables: */
  /* Column 1 = selected region linear indices */
  /* Column 2 = candidate region(s) linear indices */
  /* Column 3 = rejected region(s) linear indices */
  /* %%%%% Return the linear indices of thickened boundaries for regions %%%%% */
  /* If called during code generation */
  /* If called during code generation, use a parallel for loop (parfor), but use a for loop otherwise. */
  /* The parallel for loop increases the performance of compiled-C code but decreases the performance  */
  /* of Matlab code. */
  emlrtEnterParallelRegion(aTLS, omp_in_parallel());
  emlrtPushJmpBuf(aTLS, &emlrtJBStack);

#pragma omp parallel \
 num_threads(emlrtAllocRegionTLSs(aTLS, omp_in_parallel(), omp_get_max_threads(), 3)) \
 private(emlrtJBEnviron) \
 firstprivate(aTLS,emlrtHadParallelError)

  {
    aTLS = emlrtAllocTLS(aTLS, omp_get_thread_num());
    emlrtSetJmpBuf(aTLS, &emlrtJBEnviron);

#pragma omp for nowait

    for (i = 0; i < 3; i++) {
      if (emlrtHadParallelError)
        continue;
      if (setjmp(emlrtJBEnviron) == 0) {
        /* Loop across categories (selected, candidate, rejected) */
        /* Use a maximum of 3 threads. */
        /* RegionBoundaries{i} = M x 1 column vector; type uint32. */
        /* Local function. */
        b_Ops(aTLS, (real_T)i + 1.0, RegionSelectedAnyTF, NRegionsCandidate,
              NRegionsRejected, RegionSelectedLinIdx_data, RegionIndices_data,
              RegionsCandidateLinIdx_data, RegionsRejectedLinIdx_data,
              VidObjHeight, BoundingBoxSkin, RegionNPixels_data,
              nRows_IsSkinMask, nCols_IsSkinMask, RegionBoundaries[i].f1);
      } else {
        emlrtHadParallelError = true;
      }
    }
  }

  emlrtPopJmpBuf(aTLS, &emlrtJBStack);
  emlrtExitParallelRegion(aTLS, omp_in_parallel());

  /* Not called during code generation     */
}

/* End of code generation (SkinDetect_RegionBoundariesByCategory.c) */
