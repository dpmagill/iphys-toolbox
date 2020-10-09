/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ROIMeans_FirstRead_CollectSkinColorSamples.c
 *
 * Code generation for function 'ROIMeans_FirstRead_CollectSkinColorSamples'
 *
 */

/* Include files */
#include "ROIMeans_FirstRead_CollectSkinColorSamples.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_data.h"
#include "ROIMeans_FirstRead_CollectSkinColorSamples_emxutil.h"
#include "SkinSegmentMask_Threshold.h"
#include "bwconncomp.h"
#include "imdilate.h"
#include "imerode.h"
#include "libmwbwpackctbb.h"
#include "libmwbwunpackctbb.h"
#include "mwmathutil.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static int32_T div_s32(int32_T numerator, int32_T denominator);

/* Function Definitions */
static int32_T div_s32(int32_T numerator, int32_T denominator)
{
  int32_T quotient;
  uint32_T b_numerator;
  uint32_T b_denominator;
  if (denominator == 0) {
    emlrtDivisionByZeroErrorR2012b(NULL, emlrtRootTLSGlobal);
  } else {
    if (numerator < 0) {
      b_numerator = ~(uint32_T)numerator + 1U;
    } else {
      b_numerator = (uint32_T)numerator;
    }

    if (denominator < 0) {
      b_denominator = ~(uint32_T)denominator + 1U;
    } else {
      b_denominator = (uint32_T)denominator;
    }

    b_numerator /= b_denominator;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -(int32_T)b_numerator;
    } else {
      quotient = (int32_T)b_numerator;
    }
  }

  return quotient;
}

void ROIMeans_FirstRead_CollectSkinColorSamples(const emxArray_real32_T *YSingle,
  const emxArray_real32_T *CbSingle, const emxArray_real32_T *CrSingle, const
  emxArray_uint8_T *RUint8, const emxArray_uint8_T *GUint8, const
  emxArray_uint8_T *BUint8, const emxArray_real32_T *HSingle, const
  emxArray_real32_T *SSingle, const emxArray_boolean_T *IsSkinMask_LocalRange,
  int32_T NRows_Matrix, int32_T NCols_Matrix, const struct0_T
  *SkinSegmentConfig_Args, boolean_T UseCompiledFunctionsTF, real_T
  ithPrimaryROIRGBMeans[3], real32_T ithPrimaryROIYCbCrMeans[3], real32_T
  ithPrimaryROIYCbCrHSMinsMaxs[11])
{
  int32_T x;
  uint32_T b_x;
  uint32_T q;
  int32_T NRows_Matrix_Reduced;
  int32_T NCols_Matrix_Reduced;
  int32_T X_Matrix_Reduced;
  int32_T Y_Matrix_Reduced;
  emxArray_boolean_T *IsSkinMask_LocalRange_Reduced;
  int32_T i;
  uint16_T ColIdx_Reduced;
  int32_T b_i;
  uint16_T RowIdx_Reduced;
  int32_T RegionMaxIdx;
  int32_T j;
  emxArray_real32_T *YBounded_Single;
  real32_T YCbCrThresholds_Generic[7];
  real32_T HSThresholds_Generic[2];
  emxArray_real32_T *CbBounded_Single;
  emxArray_real32_T *CrBounded_Single;
  emxArray_real32_T *HBounded_Single;
  emxArray_real32_T *SBounded_Single;
  emxArray_boolean_T *IsSkinMask;
  emxArray_uint32_T *IsSkinMask_PixelColorPacked;
  real_T b_IsSkinMask[2];
  real_T c_x[2];
  emxArray_uint32_T *c_IsSkinMask_PixelColor_ErodePa;
  boolean_T guard1 = false;
  emxArray_real_T *t0_RegionIndices;
  emxArray_int32_T *t0_RegionLengths;
  real_T expl_temp;
  real_T t0_NumObjects;
  int32_T NPixelsMax;
  int32_T RegionEndIndex_ith;
  real32_T RegionMaxN_YMin;
  real32_T RegionMaxN_YMax;
  real32_T RegionMaxN_CbMin;
  real32_T RegionMaxN_CbMax;
  real32_T RegionMaxN_CrMin;
  real32_T RegionMaxN_CrMax;
  real32_T RegionMaxN_HMax;
  real32_T RegionMaxN_SMin;
  real32_T RegionMaxN_SMax;
  real32_T RegionMaxN_CbCrRatioMin;
  real32_T RegionMaxN_CbCrRatioMax;
  real32_T SumY;
  real32_T SumCb;
  real32_T SumCr;
  uint32_T SumR;
  uint32_T SumG;
  uint32_T SumB;
  real32_T RegionMaxN_CbCrRatio_ith;
  (void)UseCompiledFunctionsTF;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

  /* ROIMeans_FirstRead_CollectSkinColorSamples   Take colors metrics from an ROI for later use in  */
  /*                                              setting thresholds for tailored skin segmentation and   */
  /*                                              the skin-detection algorithm. */
  /*    */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by function ROIMeans_FirstRead. */
  /*  */
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
  /*     Take colors samples from ROIs for later use setting thresholds for tailored skin  */
  /*     segmentation and the skin-detection algorithm (see function ROIMeans_FirstRead_SetThresholds).                                              */
  /*     The color samples consist of minimums, maximums, and means from the RGB, YCbCr, and HSV   */
  /*     colorspaces. */
  /*  */
  /*     The minimums and maximums are taken from the RGB, YCbCr, and HSV colorspaces. These samples  */
  /*     are used as input to set thresholds for tailored skin segmentation (see function  */
  /*     SkinSegment_SetThresholds). */
  /*  */
  /*     The following minimums and maximums are returned: */
  /*     [RegionMaxN_YMin,          RegionMaxN_YMax,  ... */
  /*      RegionMaxN_CbMin,         RegionMaxN_CbMax, ... */
  /*      RegionMaxN_CrMin,         RegionMaxN_CrMax, ... */
  /*      RegionMaxN_CbCrRatioMin,  RegionMaxN_CbCrRatioMax ... */
  /*      RegionMaxN_HMax,          RegionMaxN_SMin, ... */
  /*      RegionMaxN_SMax];  */
  /*                                  */
  /*     The means are taken from the RGB and YCbCr colorspaces. These samples are used as input to set  */
  /*     thresholds for the skin-detection algorithm (see function SkinDetect_SetThresholds).     */
  /*  */
  /*     Skin-color samples are only collected from the primary face-detection algorithm as the primary    */
  /*     algorithm is assumed to contain the least false positives. Also, the ROI of the primary  */
  /*     algorithm is expected to be comprised almost entirely of pixels corresponding to skin because     */
  /*     it is assumed that the Viola-Jones face detector specified will detect the face in a frontal   */
  /*     orientation (the default Viola-Jones face detector for the primary algorithm detects frontal  */
  /*     orientations, but this can be changed by specifying argument ROIFacePrimaryXML to function    */
  /*     FacePulseRate). If the specified secondary face-detection algorithms detect profile     */
  /*     orientations (the default secondary #1 algorithm detects profile orientations, but this can be    */
  /*     changed by specifying argument ROIFaceSecondary1XML to function FacePulseRate), pixels that do   */
  /*     not correspond to skin may be incorrectly collected. */
  /*       */
  /*     Before taking metrics from the ROIs, several steps are taken to exclude non-skin pixels: */
  /*     (1) The size of the ROI, as well as the corresponding color channels, is reduced.  */
  /*     (2) A skin-segmentation mask is used to filter out pixels classified as non-skin.          */
  /*     (3) The skin-segmentation mask is analyzed for connected regions, and only pixels from the  */
  /*         region with the most connections are used. Using the region with the most connections is  */
  /*         based on the assumption that skin tends to occur in large, contiguous regions rather than   */
  /*         small regions.                                                                                         */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
  /*     the Responsible AI License (RAIL). */
  /* %%%%% Reduce size of ROI and color channels %%%%%%  */
  /* Reduce size of ROI by 2/3 to reduce likelihood of non-skin pixels in ROI. */
  /* Also reduce corresponding color channel sizes. */
  /* Reduce the size of the ROI values: */
  /* Reduce the height (number of rows) and width (number of columns) */
  x = NRows_Matrix << 1;
  if (x >= 0) {
    b_x = (uint32_T)x;
  } else if (x == MIN_int32_T) {
    b_x = 2147483648U;
  } else {
    b_x = (uint32_T)-x;
  }

  q = b_x / 3U;
  b_x -= q * 3U;
  if ((b_x > 0U) && (b_x >= 2U)) {
    q++;
  }

  NRows_Matrix_Reduced = (int32_T)q;
  if (x < 0) {
    NRows_Matrix_Reduced = -(int32_T)q;
  }

  x = NCols_Matrix << 1;
  if (x >= 0) {
    b_x = (uint32_T)x;
  } else if (x == MIN_int32_T) {
    b_x = 2147483648U;
  } else {
    b_x = (uint32_T)-x;
  }

  q = b_x / 3U;
  b_x -= q * 3U;
  if ((b_x > 0U) && (b_x >= 2U)) {
    q++;
  }

  NCols_Matrix_Reduced = (int32_T)q;
  if (x < 0) {
    NCols_Matrix_Reduced = -(int32_T)q;
  }

  /* Calculate new X- and Y-coordinates based upon reduced size */
  x = NCols_Matrix - NCols_Matrix_Reduced;
  if (x >= 0) {
    b_x = (uint32_T)x;
  } else if (x == MIN_int32_T) {
    b_x = 2147483648U;
  } else {
    b_x = (uint32_T)-x;
  }

  q = b_x >> 1;
  b_x -= q << 1;
  if (b_x > 0U) {
    q++;
  }

  X_Matrix_Reduced = (int32_T)q;
  if (x < 0) {
    X_Matrix_Reduced = -(int32_T)q;
  }

  x = NRows_Matrix - NRows_Matrix_Reduced;
  if (x >= 0) {
    b_x = (uint32_T)x;
  } else if (x == MIN_int32_T) {
    b_x = 2147483648U;
  } else {
    b_x = (uint32_T)-x;
  }

  q = b_x >> 1;
  b_x -= q << 1;
  if (b_x > 0U) {
    q++;
  }

  Y_Matrix_Reduced = (int32_T)q;
  if (x < 0) {
    Y_Matrix_Reduced = -(int32_T)q;
  }

  emxInit_boolean_T(&IsSkinMask_LocalRange_Reduced, 2, true);

  /* Reduce the size of the IsSkinMask_LocalRange channels */
  /* All matrices except IsSkinMask_LocalRange are cropped within function SkinSegmentMask. Hence, crop */
  /* IsSkinMask_LocalRange before entered as argument to SkinSegmentMask. */
  /* Local function. */
  /* end main function */
  /* ============================================================================================= */
  /* Local functions */
  /* ============================================================================================= */
  /* ============================================================================================= */
  /* CropMatrix   Crop matrix according to specified X- and Y-coordinates and width and height. */
  /* Inline function */
  /* Preallocate reduced-size matrix */
  i = IsSkinMask_LocalRange_Reduced->size[0] *
    IsSkinMask_LocalRange_Reduced->size[1];
  IsSkinMask_LocalRange_Reduced->size[0] = NRows_Matrix_Reduced;
  IsSkinMask_LocalRange_Reduced->size[1] = NCols_Matrix_Reduced;
  emxEnsureCapacity_boolean_T(IsSkinMask_LocalRange_Reduced, i);

  /* Initialize column index for reduced-size matrix                                   */
  ColIdx_Reduced = 0U;

  /* Loop across columns */
  i = (X_Matrix_Reduced + NCols_Matrix_Reduced) - 1;
  for (b_i = X_Matrix_Reduced; b_i <= i; b_i++) {
    /* Advance index */
    ColIdx_Reduced++;

    /* Initialize row index for reduced-size matrix                                   */
    RowIdx_Reduced = 0U;

    /* Loop across rows */
    RegionMaxIdx = (Y_Matrix_Reduced + NRows_Matrix_Reduced) - 1;
    for (j = Y_Matrix_Reduced; j <= RegionMaxIdx; j++) {
      /* Advance index */
      RowIdx_Reduced++;

      /* Linear index corresponding to the full matrix */
      /* Convert from subscript indices to a linear index for more efficient indexing */
      /* Note: In compiled C code, the faster indexing outweighs the cost of this  */
      /* conversion. */
      IsSkinMask_LocalRange_Reduced->data[(RowIdx_Reduced +
        IsSkinMask_LocalRange_Reduced->size[0] * (ColIdx_Reduced - 1)) - 1] =
        IsSkinMask_LocalRange->data[(j + (b_i - 1) * NRows_Matrix) - 1];
    }
  }

  /* end local function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (SkinDetect_RegionMetrics_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /* Input Argument                           Example Code                 Upp. Bounds     Var. Size (T/F)  Type */
  /* YSingleCode               = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single */
  /* CbSingleCode              = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single */
  /* CrSingleCode              = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single  */
  /* RUint8Code                = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8 */
  /* GUint8Code                = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8 */
  /* BUint8Code                = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8 */
  /* HSingleCode               = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single */
  /* SSingleCode               = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single */
  /* IsSkinMask_LocalRangeCode = coder.typeof( false(500, 500),             [inf, inf],     [1, 1] );        %logical */
  /*  */
  /*  */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /*                                        Example Code                                                                  */
  /* NRows_MatrixCode                      = int32(1);                                                                   */
  /* NCols_MatrixCode                      = int32(1);  */
  /* UseCompiledFunctionsTFCode            = false;                                                               */
  /* SkinDetectConfig_Thresholds_SetTFCode = false; */
  /*  */
  /* SkinSegmentConfig_ArgsCode = ...                                                                                               */
  /*     struct( ... */
  /*         'SkinColorSamples_NThresholdPassedTF', false, ... */
  /*         'YCbCrThresholdsGeneric', zeros(1, 7, 'single'), ... */
  /*         'HSThresholdsGeneric', zeros(1, 2, 'single'), ... */
  /*         'YCbCrThresholdsTailored', zeros(1, 8, 'single'), ... */
  /*         'YCbCrThresholdsTailored_Sev', zeros(1, 8, 'single'), ... */
  /*         'HSThresholdsTailored', zeros(1, 3, 'single'), ... */
  /*         'HSThresholdsTailored_Sev', zeros(1, 3, 'single'), ... */
  /*         'RangeSEWidth', int16(0), ... */
  /*         'RangeThreshold', uint8(0), ... */
  /*         'MorphCloseSEMediumWidth_Tuned', int16(0), ... */
  /*         'MorphCloseSELargeWidth_Tuned', int16(0) ...     */
  /*     );    */
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
  /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})'; */
  /*  */
  /* Assign to code-generation configuration object */
  /* cfg.PostCodeGenCommand = setbuildargsAsText; */
  /*  */
  /*  */
  /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
  /*  */
  /* codegen ROIMeans_FirstRead_CollectSkinColorSamples.m -report -config cfg -args {YSingleCode, CbSingleCode, CrSingleCode, RUint8Code, GUint8Code, BUint8Code, HSingleCode, SSingleCode, IsSkinMask_LocalRangeCode, NRows_MatrixCode, NCols_MatrixCode, SkinSegmentConfig_ArgsCode, UseCompiledFunctionsTFCode} */
  /*  */
  /* } */
  /* %%%%% Conduct skin segmentation %%%%%%  */
  /* Arguments to function SkinSegmentMask, which returns the skin-segmentation mask: */
  /* Flag whether to use tailored thresholds during segmentation */
  /* Tailored thresholds include the tailored-YCbCr thresholds and the tailored-HS tresholds. */
  /* Do not use tailored tresholds here in order to permit color values in ranges outside of tailored */
  /* thresholds. As the skin-segmentation mask returned here is used reset the tailored thresholds, a  */
  /* greater range permits the new thresholds to change alongside environmental changes. */
  /* Do not return the Y channel of the YCbCr colorspace */
  /* Do not return the Cb and Cr channels of the YCbCr colorspace */
  /* Do not return the H and S channels of the HSV colorspace */
  /* Whether to return a count of pixels classified as skin.  */
  /* Use severe tailored thresholds */
  /* MorphCloseSevereTF is set as true to rule out false positives, although at the expense of false   */
  /* negatives. */
  /* Note: SkinSegmentMask is a custom function located within folder FacePulseRate.  */
  /*  logical matrix where pixels classified as skin = true */
  /*  Bounded frame in RGB colorspace */
  /*  separated by channel; type uint8. */
  /*  Bounded frame in YCbCr colorspace, */
  /*  separated by channel; type single. */
  /*  Bounded frame in H and S channels of */
  /*  HSV colorspace; type single. */
  /*  Skin-segmentation mask based upon */
  /*  local range threshold; type logical. */
  /*  Number of rows of an input matrix. If */
  /*  Y_Matrix_Reduced non-empty, then this value */
  /*  indicates the number of rows to index into, */
  /*  which can be different from the height of the */
  /*  input matrices. Note that this indexing is */
  /*  not applied to input IsSkinMask_LocalRange; */
  /*  IsSkinMask_LocalRange should be cropped to */
  /*  the height of NRowss_Matrix_Reduced before */
  /*  entered as an argument. */
  /*  Number of columns of an input matrix. If */
  /*  X_Matrix_Reduced non-empty, then this value */
  /*  indicates the number of columns to index into, */
  /*  which can be different from the width of the */
  /*  input matrices. Note that this indexing is */
  /*  not applied to input IsSkinMask_LocalRange; */
  /*  IsSkinMask_LocalRange should be cropped to */
  /*  the width of NCols_Matrix_Reduced before */
  /*  entered as an argument. */
  /*  Whether to return a count of pixels */
  /*  classified as skin. */
  /*  Whether to use thresholds that are */
  /*  tailored. */
  /*  Whether to return Y channel of the */
  /*  YCbCr colorspace. */
  /*  Whether to return Cb and Cr channels */
  /*  of the YCbCr colorspace. */
  /*  Whether to return the H and S channels */
  /*  of the HSV colorspace (HSingle). */
  /*  Whether to use severe tailored */
  /*  thresholds. */
  /*  Whether the morphological close operation will */
  /*  be conducted with a high level of severity. */
  /*  Optional X-coordinate offset applied to input */
  /*  matrices. However, does not apply to input */
  /*  IsSkinMask_LocalRange. Use 0 x 1 value to */
  /*  ignore. If used, adjust NCols_Matrix */
  /*  accordingly. NCols_Matrix can be set to an */
  /*  arbitrary value when XOffset is non-empty. */
  /*  Scalar; type int32. */
  /*  Optional Y-coordinate offset applied to input */
  /*  matrices. However, does not apply to input */
  /*  IsSkinMask_LocalRange. Use 0 x 1 value to */
  /*  ignore. If used, adjust NRows_Matrix */
  /*  accordingly. NRows_Matrix can be set to an */
  /*  arbitrary value when YOffset is non-empty. */
  /*  Scalar; type int32. */
  /*  Configurations */
  /*  Whether to use compiled functions */
  /* SkinSegmentMask   Return logical matrix, or skin-segmentation mask, where pixels classified as  */
  /*                   skin are true. Wrapper function for function SkinSegmentMask_Ops. */
  /*    */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, this function is called by functions ... */
  /*         - ConfirmSkinPresent (which is called by functions FaceDetect,   */
  /*           SkinDetect_SelectedRegionROI, and ROIMeans_TakeMeans) */
  /*         - SkinDetect_PartitionRegions (which is called by function SkinDetect)           */
  /*         - ROIMeans_TakeMeans (which is called by functions ROIMeans_FirstRead_TakeMeans and */
  /*           ROIMeans_SecondRead_TakeMeans) */
  /*         - ROIMeans_FirstRead_CollectSkinColorSamples (which is called by function */
  /*           ROIMeans_FirstRead) */
  /*  */
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
  /*     Return logical matrix, or skin-segmentation mask, where pixels classified as skin are true. */
  /*     This is a wrapper function for function SkinSegmentMask_Ops. For a description of the  */
  /*     skin-segmentation operations, see function SkinSegmentMask_Ops. */
  /*  */
  /*     Execute either the compiled or non-compiled function depending on argument  */
  /*     UseCompiledFunctionsTF. */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
  /*     the Responsible AI License (RAIL). */
  /* %%%%% Code-generation settings %%%%%% */
  /* Inline function */
  /* Compiled functions enabled and code generation not running */
  /* Value of SkinSegmentConfig.UseCompiledFunctionsTF assigned in function  */
  /* SkinSegment_ConfigSetup.  */
  /* Note: SkinSegmentMask_Ops is a custom function located within folder FacePulseRate. */
  /* SkinSegmentMask_Ops   Return logical matrix, or skin-segmentation mask, where pixels classified as   */
  /*                       skin are true. */
  /*                                                */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, called by function SkinSegmentMask. */
  /*  */
  /*  */
  /*     Code generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*     Compiled file: The compiled file included in folder FacePulseRate  */
  /*     (SkinSegmentMask_Ops_mex.mexw64) only compatible on Windows platforms.        */
  /*  */
  /*  */
  /*     Description */
  /*     ----------- */
  /*  */
  /*     -- YCbCr Pixel-Color Thresholds --  */
  /*  */
  /*     YCbCr color thresholds in use: */
  /*  */
  /*     - Y-channel minimum */
  /*     - Y-channel maximum (tailored-thresholds only) */
  /*     - Cb-channel minimum */
  /*     - Cb-channel maximum  */
  /*     - Cr-channel minimum */
  /*     - Cr-channel maximum  */
  /*  */
  /*     Apply color thresholds to individual pixels from the luminance (Y), Cb chroma (Cb), and Cr  */
  /*     chroma (Cr) channels of the YCbCr colorspace. */
  /*  */
  /*     Use either the generic YCbCr color thresholds or tailored YCbCr color thresholds. The use of */
  /*     tailored thresholds is specified by argument TailoredThresholdsTF. However, generic thresholds */
  /*     are used when TailoredThresholdsTF is true if the criterion for using tailored thresholds has */
  /*     not been satisfied, which is indicated by DontUseTailoredTF == true.  */
  /*  */
  /*         Generic Thresholds */
  /*  */
  /*     The YCbCr generic color thresholds (SkinSegmentArgs.YCbCrThresholdsGeneric) are used when */
  /*     TailoredThresholdsTF is set to false. Thresholds include a Y-channel minimum, Cb-channel  */
  /*     minimum and maximum, Cr-channel minimum and maximum, and Cb-to-Cr ratio minimum and maximum. */
  /*      */
  /*     The threshold values are set by an argument, SkinSegmentYCbCrThresholdsGeneric, to function  */
  /*     FacePulseRate. If the argument is not specified, default values are used. The default Y, Cb,   */
  /*     and Cr minimums and maximums are based on a consultation of the values provided in iphys  */
  /*     toolbox (McDuff & Blackford, 2019). These values were modified somewhat as a result of   */
  /*     testing. The Cb-to-Cr ratio minimum and maximum and not used in iphys toolbox; these values  */
  /*     were developed through testing. */
  /*       */
  /*     Function SkinSegment_ConfigSetup sets the values for SkinSegmentArgs.YCbCrThresholdsGeneric */
  /*     based on argument SkinSegmentThresholdsGenericYCbCr.     */
  /*  */
  /*     Within the current function, the YCbCr generic threshold operations are conducted by function   */
  /*     SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold. */
  /*  */
  /*         Tailored Thresholds */
  /*  */
  /*     The YCbCr tailored thresholds (SkinSegmentArgs.YCbCrThresholdsGeneric) are used when */
  /*     TailoredThresholdsTF is set to true. The threshold values are set based upon skin-color   */
  /*     samples collected from the input video. The threshold types include those used in the generic */
  /*     thresholds as well as a Y-channel maximum. The Y-channel maximum may be more sensitive than */
  /*     other thresholds to individual differences in facial colors. Due to this sensitivity, this */
  /*     value is not used for generic thresholds but is used for tailored thresholds as tailored */
  /*     thresholds are based upon the face in the video. */
  /*  */
  /*     The skin-color samples are collected from the input video. For details on the collection of  */
  /*     skin-color samples, see function ROIMeans_FirstRead_CollectSkinColorSamples. Before a */
  /*     sample is collected by function ROIMeans_FirstRead_CollectSkinColorSamples, function  */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples calls function SkinSegmentMask to attempt to  */
  /*     isolate pixel colors corresponding to skin. When SkinSegmentMask is called by function  */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples samples, TailoredThresholdsTF is set to false; that  */
  /*     is, generic thresholds are used. As tailored thresholds are based upon skin-color samples that */
  /*     were filtered by the generic thresholds, the tailored thresholds can be expected to be more */
  /*     stringent compared to the generic thresholds. The term "sample" refers to two values taken  */
  /*     from each YCbCr color channel of skin-segmented ROI. Specifically, the the minimum and maximum */
  /*     color values are taken from each channel.  */
  /*      */
  /*     Skin-color samples used for tailored YCbCr thresholds are collected by function  */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples, which is called by function ROIMeans_FirstRead.  */
  /*     See function ROIMeans_FirstRead for details on the implementation of collecting skin-color  */
  /*     samples. */
  /*  */
  /*     After a certain number of samples has been collected, the samples are used to set the tailored  */
  /*     threshold values. The setting of thresholds from skin-color samples is conduted by function */
  /*     SkinSegment_SetThresholds. The number of samples required to set the tailored threshold  */
  /*     values, SkinSegmentConfig.TailoredData.PriAlgROIs_NThreshold, is specified by function  */
  /*     SkinSegment_ConfigSetup. This value can only be modified by adjusting the code within this */
  /*     function.  */
  /*  */
  /*     It has been observed that if the skin-color samples are too heavily concentrated within a  */
  /*     particular portion of the video, the thresholds that come from them can be too restrictive.  */
  /*     This is likey because samples limited to a brief portion of the video do not contain a */
  /*     sufficient level enough heterogeneity to reflect the color variations across the video. To  */
  /*     address this restrictiveness, the thresholds are reset periodically. Specifically, the  */
  /*     thresholds are reset after a specified number of frames has elapsed since the thresholds were  */
  /*     last set or reset. This number of frames is specified by  */
  /*     SkinSegmentConfig.TailoredData.ThresholdOpsInterval, which is set by function */
  /*     SkinSegment_ConfigSetup. This value can only be modified by adjusting the code within function */
  /*     SkinSegment_ConfigSetup. */
  /*  */
  /*     Although resetting the thresholds addresses the lack of heterogeneity across most of the  */
  /*     video, heterogeneity may still be unacceptably low between the first setting of the thresholds */
  /*     and the first resetting of the thresholds. This may occur if the skin-color samples are */
  /*     collected within close proximity. One condition that causes samples to be collected within  */
  /*     close proximity is a low frame-skipping rate (ROIGeneralConfig.ROISkipFrameThreshold; see */
  /*     function ROIGeneralConfig_Setup). To increase the heterogeneity in this case, the number of  */
  /*     skin-color samples required before the first thresholds are set  */
  /*     (SkinSegmentConfig.TailoredData.PriAlgROIs_NThreshold) is increased when the frame-skipping  */
  /*     rate is relatively low (see funtion SkinSegment_ConfigSetup).  */
  /*  */
  /*     Before the required number of skin-color samples has been collected, generic thresholds are */
  /*     used in place of tailored thresholds. If argument TailoredThresholdsTF is set to true,  */
  /*     specifying that tailored thresholds should be used, generic thresholds will be used if the  */
  /*     required number of samples has not been collected. Within the current function, the flag */
  /*     DontUseTailoredTF is set to true in this case to indicate that generic thresholds should be   */
  /*     used in place of tailored thresholds. */
  /*      */
  /*     For each skin-color sample, minimums and maximums are taken from each colorspace channel.  */
  /*     These values are set aside until the thresholds are to be set or reset. When setting or  */
  /*     resetting occurs, percentiles are applied to these values to extract the values at lower and */
  /*     upper percentiles. The value at the lower percentile becomes the lower threshold and the */
  /*     value at the upper percentile becomes the upper percentile. For example, suppose the lower and  */
  /*     upper percentiles are specified as 1.5 and 98.5, respecively. From all skin-color samples */
  /*     previously collected, the sample values from each channel that occur at the 1.5th percentile   */
  /*     and 98.5th percentile become the lower the upper thresholds, respectively. One point of  */
  /*     confusion may be that the terms "minimum" and "maximum" are used for two purposes here. */
  /*     The first use is in taking the minimum and maximum of each skin-color sample. These minimums */
  /*     and maximums are set aside until the percentiles are applied. When the percentiles are  */
  /*     applied, the lower percentile becomes the lower threshold and the upper percentile becomes the */
  /*     upper threshold. Although the terms "upper" and "lower" and used to refer to these thresholds */
  /*     for clarity, the terms "minimum" and "maximum" would also be appropriate. That is, the lower, */
  /*     or minimum, threshold is selected from a collection of minimum values; the upper, or maximum, */
  /*     threshold is selected from a collection of maximum values. */
  /*  */
  /*     One set of percentiles is used for the Y, Cb, Cr, Cb-to-Cr ratio, and H thresholds, and a  */
  /*     separate set of percentiles is used for the S thresholds. A separate set of percentiles is  */
  /*     used for the S thresholds because it has been observed that a wider range is appropriate for */
  /*     the S color channel. These percentiles are specified by function SkinSegmentConfig_Setup. The */
  /*     percentiles can be modified only by adjusting the code within SkinSegmentConfig_Setup. */
  /*  */
  /*     Within the current function, the YCbCr tailored threshold operations are conducted by function   */
  /*     SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold. */
  /*  */
  /*     -- HSV Pixel-Color Thresholds -- */
  /*    */
  /*     HSV color thresholds in use: */
  /*  */
  /*     - H-channel maximum */
  /*     - S-channel minimum */
  /*     - S-channel maximum (tailored-thresholds only) */
  /*  */
  /*     Apply color thresholds to individual pixels from the hue (H) and saturation (S) channels of   */
  /*     the HSV colorspace. */
  /*  */
  /*     The concomitant use of tresholds from the YCbCr and HSV colorspaces also is based on Dahmani  */
  /*     et al. (2020). */
  /*      */
  /*     Use either the generic HSV color thresholds or tailored HSV color thresholds. The use of */
  /*     tailored thresholds is specified by argument TailoredThresholdsTF. However, generic  */
  /*     thresholds are used when TailoredThresholdsTF is true if the criterion for using tailored  */
  /*     thresholds has not been satisfied, which is indicated by DontUseTailoredTF == true. */
  /*  */
  /*         Generic Thresholds */
  /*  */
  /*     The HSV generic color thresholds (SkinSegmentArgs.HSVThresholdsGeneric) are used when */
  /*     TailoredThresholdsTF is set to false. Thresholds include an H-channel maximum and an S-channel */
  /*     minimum. */
  /*      */
  /*     The threshold values are set by an argument, SkinSegmentThresholdsGenericHSV, to function  */
  /*     FacePulseRate. If the argument is not specified, default values are used. The default H and S   */
  /*     minimums and maximums are based on testing by DPM.  */
  /*       */
  /*     Function SkinSegment_ConfigSetup sets the values for SkinSegmentArgs.HSVThresholdsGeneric */
  /*     based on argument SkinSegmentThresholdsGenericHSV.     */
  /*  */
  /*     Within the current function, the HSV generic threshold operations are conducted by function   */
  /*     SkinSegmentMask_Threshold_Colors, which is called by function SkinSegmentMask_Threshold. */
  /*  */
  /*         Tailored Thresholds */
  /*  */
  /*     The H and S tailored color thresholds (SkinSegmentArgs.HSThresholdsTailored) are used when */
  /*     TailoredThresholdsTF is set to true. The combination of a maximum for the H channel and a   */
  /*     minimum and a maximum for the S channel is based on Dahmani et al. (2020).  */
  /*      */
  /*     As with the tailored YCbCr thresholds, these thresholds are set based upon skin-color samples  */
  /*     collected from the input video. The process of setting the H and S tailored thresholds is   */
  /*     identical to the process of setting the tailored YCbCr thresholds.  */
  /*  */
  /*     If argument TailoredThresholdsTF is specified as true but the required number of samples has */
  /*     not been acquired, the H and S tailored thresholds will not be used. As with the tailored  */
  /*     YCbCr thresholds, the flag DontUseTailoredTF will be set to true to cause the H and S tailored  */
  /*     thresholds not to be used. */
  /*  */
  /*     Within the current function, the H and S tailored threshold operations are conducted by    */
  /*     function SkinSegmentMask_Threshold_Colors, which is called by function  */
  /*     SkinSegmentMask_Threshold. */
  /*  */
  /*     -- Low- and High-Severity Tailored Thresholds --  */
  /*  */
  /*     When TailoredThresholdsSevereTF == true, high-severity thresholds are used when conducting */
  /*     segmentation with the tailored YCbCr and HSV thresholds. High-severity thresholds are used for  */
  /*     applications where the priority is to reduce false positives (pixels incorrectly classified as */
  /*     skin) at the expense of a greater number false negatives (pixels incorrectly classified as  */
  /*     non-skin). When false, low-severity thresholds are used. Low-severity thresholds are used for  */
  /*     applications where a balance is desired between false positives and false negatives.      */
  /*  */
  /*     -- Local-Range Pixel Threshold --  */
  /*  */
  /*     The local-range pixel threshold classifies pixels based upon the homogeneity of color values */
  /*     of nearby, or local, pixels. When the local range is relatively homogeneous rather than */
  /*     heterogeneous, the value of the local range will be lower. A relatively homogeneous color  */
  /*     range of a given pixel is used as a heuristic of a pixel corresponding to skin. This is based   */
  /*     on the assumption that true skin tends to occur in regions of homogeneous color. When the  */
  /*     local range of a pixel falls below a specified threshold (SkinSegmentArgs.HThresholdTailored),  */
  /*     the pixel is classified as skin. */
  /*  */
  /*     The threshold for local range is a static value; that is, it is not set by assessment of color  */
  /*     samples. The threshold value is set by function SkinSegmentConfig_Setup. The value can only be  */
  /*     modified by adjusting the code within SkinSegmentConfig_Setup. The effectiveness of the value  */
  /*     used was established through testing.  */
  /*  */
  /*     Within the current function, the local-range pixel threshold operations are conducted by    */
  /*     function SkinSegmentMask_Threshold_Range, which is called by function  */
  /*     SkinSegmentMask_Threshold. */
  /*  */
  /*     -- Morphological Close of Patchy Regions --  */
  /*  */
  /*     Following the application of these thresholds, a two-dimensional logical matrix is assigned  */
  /*     where pixels that satisfied all thresholds are classified as true and pixels that did not are */
  /*     classified as false. A morphological close operation is then applied to the logical matrix.  */
  /*     The morphological close tends to fill in classification holes, where a hole is loosely defined  */
  /*     as a region of pixels classified as true that are enclosed by pixels classified as false.   */
  /*     Holes are filled in based on the assumption that true skin tends to be distributed in the face   */
  /*     in contiguous, rather than patchy, regions. */
  /*      */
  /*     The morphological close fills in holes only below a certain shape and size, which are    */
  /*     determined by the shape and size of the morphological structuring element, such that many  */
  /*     holes are not filled. Otherwise, large regions classified as true -- which are assumed to be  */
  /*     regions of skin -- may be erroneously filled. For a description on the choice of structuring  */
  /*     element used, see function SkinSegmentMask_MorphClose.  */
  /*  */
  /*     Within the current function, the morphological close operations are conducted by function   */
  /*     SkinSegmentMask_Threshold_MorphClose, which is called by function SkinSegmentMask_Threshold. */
  /*  */
  /*     -- Return Skin-Segmentation Mask Without Performing Colorspace Conversion -- */
  /*  */
  /*     To return a skin-segmentation mask without performing colorspace conversion, the colorspaces */
  /*     needed for skin-segmentation can be entered as input. These include YSingle, CbSingle,  */
  /*     CrSingle, HSingle, and SSingle. If all of these color channels are non-empty, colorspace */
  /*     conversion will not be performed. */
  /*  */
  /*     Additionally, IsSkinMask_Range, a skin-segmentation based upon the local range, can also be */
  /*     be entered as input.  */
  /*  */
  /*     A case where these may be entered is where skin segmentation is first run with either tailored */
  /*     thresholds on or off and it is desired to rerun the skin segmentation using tailored or non- */
  /*     tailored thresholds. In this case, the color channels and IsSkinMask_Range would have been */
  /*     assigned previously and can be reused. */
  /*  */
  /*     -- Color Channel Return Values -- */
  /*  */
  /*     The H and S channels of the HSV colorspace and the Y, Cb, and Cr channels of the YCbCr  */
  /*     colorspace are assigned during the operations of function SkinSegmentMask_Threshold. For  */
  /*     efficiency, these channels can be returned for reuse by other functions within function  */
  /*     FacePulseRate. One use of these values by another function is to periodically reset the color   */
  /*     thresholds (YCbCrThresholds_Tailored, HSThresholds_Tailored) used by the current function;   */
  /*     this is conducted by function SkinSegment_SetThresholds. To return these channels for reuse by */
  /*     other functions, the values are assigned to matrices, which are quite large due to the number  */
  /*     of pixels processed. Assignment to these large matrices may incur additional processing time.  */
  /*     To avoid this processing time when values are not to be reused, whether the channels are  */
  /*     returned can be controlled by arguments.  */
  /*  */
  /*     Argument ReturnYTF determines whether the Y channel is returned. Argument ReturnCbCrTF  */
  /*     determines whether the Cb and Cr channels are returned. Argument ReturnHSTF determines whether  */
  /*     the H and S channels are returned.     */
  /*            */
  /*  */
  /*     Notes */
  /*     ----- */
  /*  */
  /*     For detailed descriptions of the implementation of settings used in this function, see  */
  /*     function SkinSegmentConfig_Setup, which sets the settings. */
  /*  */
  /*     To view an image segmented with the skin-segmentation mask returned by this function, run the */
  /*     following code. The resulting image will be segmented in the same manner it is segmented in */
  /*     function FacePulseRate. */
  /*     SkinSegmented =        ... Segmented image */
  /*         AreaToSegment .*   ... Original image prior to segmentation */
  /*         uint8(IsSkinMask); %   Segmentation mask */
  /*  */
  /*  */
  /*     Requires */
  /*     -------- */
  /*  */
  /*         - Image Processing Toolbox (when non-compiled functions are used) */
  /*  */
  /*  */
  /*     References */
  /*     ---------- */
  /*  */
  /*     For helpful Matlab documentation on image segmentation operations, see the Matlab   */
  /*     documentation topic "image segmentation". */
  /*  */
  /*     Dahmani, D., Cheref, M., & Larabi, S. (2020). Zero-sum game theory model for segmenting skin  */
  /*     regions. Image and Vision Computing, 103925. */
  /*  */
  /*     McDuff, D., & Blackford, E. (2019, July). iphys: An open non-contact imaging-based  */
  /*     physiological measurement toolbox. In 2019 41st Annual International Conference of the IEEE  */
  /*     Engineering in Medicine and Biology Society (EMBC) (pp. 6521-6524). IEEE. */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
  /*     the Responsible AI License (RAIL). */
  /* %%%%% Code generation specifications %%%%%% */
  /* Inline function */
  /* Declare variables: */
  /*                               Upp. Bounds    Var. Size (T/F) */
  /* %%%%% Parse input arguments %%%%%% */
  /*  - Structuring element width for calculating local range for a given pixel */
  /* Value assigned in function SkinSegment_ConfigSetup. */
  /*  - Individual pixel local color range threshold  */
  /* Value assigned in function SkinSegment_ConfigSetup. */
  /* Should be type uint8 for fastest evaluation.  */
  /*  - Individual pixel YCbCr colorspace skin-segmentation generic thresholds */
  /* Values assigned in function SkinSegment_ConfigSetup.   */
  /* Note: these should be in type single for fastest evaluation. */
  for (i = 0; i < 7; i++) {
    YCbCrThresholds_Generic[i] = SkinSegmentConfig_Args->
      YCbCrThresholdsGeneric[i];
  }

  emxInit_real32_T(emlrtRootTLSGlobal, &YBounded_Single, 2, true);

  /* Function SkinSegmentMask_Threshold_Colors will only use < and > rather than <= and >=, so these  */
  /* values are adjusted so that < and > are equivalent to <= and >=, respectively. */
  YCbCrThresholds_Generic[0] = SkinSegmentConfig_Args->YCbCrThresholdsGeneric[0]
    - 1.0F;

  /* Y min */
  YCbCrThresholds_Generic[1] = SkinSegmentConfig_Args->YCbCrThresholdsGeneric[1]
    - 1.0F;

  /* Cb min */
  /* Cr min */
  YCbCrThresholds_Generic[5] = SkinSegmentConfig_Args->YCbCrThresholdsGeneric[5]
    - 0.1F;

  /* Cb-to-Cr ratio min */
  YCbCrThresholds_Generic[2] = SkinSegmentConfig_Args->YCbCrThresholdsGeneric[2]
    + 1.0F;

  /* Cb max */
  YCbCrThresholds_Generic[4] = SkinSegmentConfig_Args->YCbCrThresholdsGeneric[4]
    + 1.0F;

  /* Cr max */
  YCbCrThresholds_Generic[3] = (SkinSegmentConfig_Args->YCbCrThresholdsGeneric[3]
    - 1.0F) + 0.1F;

  /* Cb-to-Cr ratio max */
  /*  - Individual pixel HSV colorspace skin-segmentation generic thresholds */
  /* Values assigned in function SkinSegment_ConfigSetup.   */
  /* Note: these should be in type single for fastest evaluation. */
  /* Function SkinSegmentMask_Threshold_Colors will only use < and > rather than <= and >=, so these  */
  /* values are adjusted so that < and > are equivalent to <= and >=, respectively. */
  HSThresholds_Generic[1] = SkinSegmentConfig_Args->HSThresholdsGeneric[1] -
    0.1F;

  /* S min */
  HSThresholds_Generic[0] = SkinSegmentConfig_Args->HSThresholdsGeneric[0] +
    0.1F;

  /* H max */
  /*  - Individual pixel YCbCr and HSV colorspaces skin-segmentation tailored thresholds */
  /* Values assigned in function SkinSegment_SetThresholds. */
  /* Note: a threshold is not used for the value (V) channel of the HSV colorspace.  */
  /* Note: these should be in type single for fastest evaluation.  */
  /*    - Low-severity tailored thresholds */
  /* YCbCr channels */
  /* H and S channels */
  /*    - High-severity tailored thresholds     */
  /*  - Flag not to use tailored thresholds */
  /* Whether a sufficient number of skin-color samples was collected to activate tailored skin */
  /* segmentation. For details on the collection skin-color samples, see function */
  /* ROIMeans_FirstRead_CollectSkinColorSamples. */
  /* Value assigned by function SkinSegment_SetThresholds. */
  /*  - Severity of morphological close */
  /*    - High severity of morphological close operation */
  /*    - Low severity of morphological close operation */
  /* Number of elements of a given matrix */
  /* Scalar; type int32. */
  /* %%%%% Apply pixel-color and pixel-color local range thresholds %%%%%% */
  /* Apply individual pixel-color and pixel-color local range thresholds to assign a skin-segmentation  */
  /* mask. */
  /* Note: SkinSegmentMask_Threshold is a custom function located within folder FacePulseRate. */
  i = YBounded_Single->size[0] * YBounded_Single->size[1];
  YBounded_Single->size[0] = YSingle->size[0];
  YBounded_Single->size[1] = YSingle->size[1];
  emxEnsureCapacity_real32_T(YBounded_Single, i);
  RegionMaxIdx = YSingle->size[0] * YSingle->size[1];
  for (i = 0; i < RegionMaxIdx; i++) {
    YBounded_Single->data[i] = YSingle->data[i];
  }

  emxInit_real32_T(emlrtRootTLSGlobal, &CbBounded_Single, 2, true);
  i = CbBounded_Single->size[0] * CbBounded_Single->size[1];
  CbBounded_Single->size[0] = CbSingle->size[0];
  CbBounded_Single->size[1] = CbSingle->size[1];
  emxEnsureCapacity_real32_T(CbBounded_Single, i);
  RegionMaxIdx = CbSingle->size[0] * CbSingle->size[1];
  for (i = 0; i < RegionMaxIdx; i++) {
    CbBounded_Single->data[i] = CbSingle->data[i];
  }

  emxInit_real32_T(emlrtRootTLSGlobal, &CrBounded_Single, 2, true);
  i = CrBounded_Single->size[0] * CrBounded_Single->size[1];
  CrBounded_Single->size[0] = CrSingle->size[0];
  CrBounded_Single->size[1] = CrSingle->size[1];
  emxEnsureCapacity_real32_T(CrBounded_Single, i);
  RegionMaxIdx = CrSingle->size[0] * CrSingle->size[1];
  for (i = 0; i < RegionMaxIdx; i++) {
    CrBounded_Single->data[i] = CrSingle->data[i];
  }

  emxInit_real32_T(emlrtRootTLSGlobal, &HBounded_Single, 2, true);
  i = HBounded_Single->size[0] * HBounded_Single->size[1];
  HBounded_Single->size[0] = HSingle->size[0];
  HBounded_Single->size[1] = HSingle->size[1];
  emxEnsureCapacity_real32_T(HBounded_Single, i);
  RegionMaxIdx = HSingle->size[0] * HSingle->size[1];
  for (i = 0; i < RegionMaxIdx; i++) {
    HBounded_Single->data[i] = HSingle->data[i];
  }

  emxInit_real32_T(emlrtRootTLSGlobal, &SBounded_Single, 2, true);
  i = SBounded_Single->size[0] * SBounded_Single->size[1];
  SBounded_Single->size[0] = SSingle->size[0];
  SBounded_Single->size[1] = SSingle->size[1];
  emxEnsureCapacity_real32_T(SBounded_Single, i);
  RegionMaxIdx = SSingle->size[0] * SSingle->size[1];
  for (i = 0; i < RegionMaxIdx; i++) {
    SBounded_Single->data[i] = SSingle->data[i];
  }

  emxInit_boolean_T(&IsSkinMask, 2, true);
  SkinSegmentMask_Threshold(emlrtRootTLSGlobal, RUint8, GUint8, BUint8,
    YBounded_Single, CbBounded_Single, CrBounded_Single, HBounded_Single,
    SBounded_Single, IsSkinMask_LocalRange_Reduced, NRows_Matrix_Reduced,
    NCols_Matrix_Reduced, NRows_Matrix_Reduced * NCols_Matrix_Reduced,
    YCbCrThresholds_Generic, HSThresholds_Generic,
    SkinSegmentConfig_Args->RangeSEWidth, SkinSegmentConfig_Args->RangeThreshold,
    X_Matrix_Reduced, Y_Matrix_Reduced, IsSkinMask);

  /* %%%%% Morphologically close skin-segmentation mask regions with patchy classifications %%%%%% */
  /* Note: SkinSegmentMask_MorphClose is a custom function located within folder FacePulseRate. */
  /* SkinSegmentMask_MorphClose    Morphologically close regions with patchy skin classification to  */
  /*                               refine the skin-segmentation mask previously assigned by comparison  */
  /*                               to thresholds. */
  /*                                                                            */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by function SkinSegmentMask_Ops. */
  /*  */
  /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*     Description: */
  /*  */
  /*     For a description of the assumptions behind the use of a morphological close to classify */
  /*     pixels as skin, see function SkinSegmentMask_Ops.   */
  /*  */
  /*     Apply a morphological close operation to the skin-segmentation mask resulting from thresholds */
  /*     previously applied (by function SkinSegmentMask_Threshold). The morphological close tends to  */
  /*     fill in classification holes, where a hole is loosely defined as a region of pixels classified  */
  /*     as true that are enclosed by pixels classified as false. The morphological close fills in  */
  /*     holes only below a specified size (specified by a morphological structuring element), such  */
  /*     that many holes are not filled.     */
  /*       */
  /*     A morphological dilation followed by a morphological erosion is conducted to perform the   */
  /*     morphological close. These operations are conducted by Matlab functions imerode and imdilate. */
  /*     Although a Matlab function is available to conduct a close (imclose), it has been observed   */
  /*     that using imerode followed by imdilate is more efficient. */
  /*  */
  /*     For a description of the choice of structuring element used in the morphological close, see  */
  /*     the description below in section "Assign structuring element".   */
  /*  */
  /*     Structuring element specifications: */
  /*  */
  /*     - Severity == high: */
  /*  */
  /*     Use liberal dilation and erosion to mask non-skin pixels  */
  /*     Do so by using a large morphological structuring element (SE), which specifies the size of     */
  /*     dilation and erosion to carry out on each pixel (where pixel == 0). High severity may favor */
  /*     the rejection of non-skin pixels over the retention of of true-skin pixels. Function  */
  /*     FaceDetect and SkinDetect specify skin segmentation with high severity. This severity may be   */
  /*     useful for these functions because the priority in these functions is avoiding non-skin  */
  /*     pixels rather than retaining as many pixels as possible that are actually skin.     */
  /*  */
  /*     - Severity == low: */
  /*  */
  /*     Use moderate dilation and erosion to mask non-skin pixels. */
  /*     Do so by using a medium morphological structuring element (SE), which specifies the size of   */
  /*     dilation to carry out on each pixel (where pixel == 0). Compared to high severity, low  */
  /*     severity is intended to strike a balance between rejecting pixels and accepting pixels that    */
  /*     are actually skin. Function ROIMeans_TakeMeans specifies skin segmentation with low severity.  */
  /*     This low severity may be useful for the purpose of function ROIMeans_TakeMeans, which is to    */
  /*     calculate the accurate mean of an ROI. The ROIs that ROIMeans_TakeMeans processes have been  */
  /*     previously processed by functions FaceDetect and SkinDetect, which specify high severity, so  */
  /*     these ROIs may already be expected to have benefited from adjustment based upon avoidance of   */
  /*     non-skin pixels. */
  /*  */
  /*     Notes:  */
  /*  */
  /*     By default, Matlab's morphological operations act on true values, not false values, although */
  /*     false values (non-skin) are the target. */
  /*     */
  /*     For Matlab documentation discussing removal of patchy regions, see the Matlab documentation */
  /*     topic "Detect Cell Using Edge Detection and Morphology"  */
  /*     (https://www.mathworks.com/help/images/detecting-a-cell-using-image-segmentation.html). */
  /*  */
  /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
  /*     the Responsible AI License (RAIL). */
  /* %%%%% Code-generation settings %%%%%% */
  /* Inline function */
  /* %%%%% Binary Packing %%%%%% */
  /* Note: For use as a Matlab function rather than code generation for a mex function, it is faster  */
  /* not to pack the logical matrix. */
  /* Pack logical image for increased performance of morphological functions  */
  x = (int32_T)muDoubleScalarCeil((real_T)IsSkinMask->size[0] / 32.0);
  emxFree_real32_T(&SBounded_Single);
  emxFree_real32_T(&HBounded_Single);
  emxFree_real32_T(&CrBounded_Single);
  emxFree_real32_T(&CbBounded_Single);
  emxFree_real32_T(&YBounded_Single);
  emxFree_boolean_T(&IsSkinMask_LocalRange_Reduced);
  emxInit_uint32_T(&IsSkinMask_PixelColorPacked, 2, true);
  if ((IsSkinMask->size[0] == 0) || (IsSkinMask->size[1] == 0)) {
    i = IsSkinMask_PixelColorPacked->size[0] * IsSkinMask_PixelColorPacked->
      size[1];
    IsSkinMask_PixelColorPacked->size[0] = x;
    IsSkinMask_PixelColorPacked->size[1] = IsSkinMask->size[1];
    emxEnsureCapacity_uint32_T(IsSkinMask_PixelColorPacked, i);
    RegionMaxIdx = x * IsSkinMask->size[1];
    for (i = 0; i < RegionMaxIdx; i++) {
      IsSkinMask_PixelColorPacked->data[i] = 0U;
    }
  } else {
    i = IsSkinMask_PixelColorPacked->size[0] * IsSkinMask_PixelColorPacked->
      size[1];
    IsSkinMask_PixelColorPacked->size[0] = x;
    IsSkinMask_PixelColorPacked->size[1] = IsSkinMask->size[1];
    emxEnsureCapacity_uint32_T(IsSkinMask_PixelColorPacked, i);
    b_IsSkinMask[0] = IsSkinMask->size[0];
    b_IsSkinMask[1] = IsSkinMask->size[1];
    c_x[0] = x;
    c_x[1] = IsSkinMask->size[1];
    bwPackingtbb(&IsSkinMask->data[0], b_IsSkinMask,
                 &IsSkinMask_PixelColorPacked->data[0], c_x, true);
  }

  /* %%%%% Assign structuring element %%%%%% */
  /* Because structuring element objects are compile-time constants, only four structuring element  */
  /* objects are made available, each of which has a corresponding function. The function with the  */
  /* structuring element closest in size to the specified structuring element size is used.   */
  /* Select function from available functions */
  /* Select the function with the SE width most similar to the specified SE width. */
  /* Local function. */
  /* Scalar; type int16. */
  /* end main function */
  /* ============================================================================================= */
  /* Local functions  */
  /* ============================================================================================= */
  /* ============================================================================================= */
  /* SelectFunction   Select the function with the SE width most similar to  */
  /*                  MorphCloseNeighborhoodWidth.    */
  /* Inline function */
  /* High severity */
  /* Low severity     */
  /* %%%%% Erosion followed by dilation %%%%%% */
  /* Cast to type double for use by function imerode */
  /* Scalar; type double. */
  /* %%%%% --- High severity erosion and dilation %%%%%%  */
  /* Use function corresponding to closest SE width */
  emxInit_uint32_T(&c_IsSkinMask_PixelColor_ErodePa, 2, true);
  if ((int16_T)(22 - SkinSegmentConfig_Args->MorphCloseSELargeWidth_Tuned) < 0)
  {
    i = (int16_T)(SkinSegmentConfig_Args->MorphCloseSELargeWidth_Tuned - 22);
  } else {
    i = (int16_T)(22 - SkinSegmentConfig_Args->MorphCloseSELargeWidth_Tuned);
  }

  if ((int16_T)(50 - SkinSegmentConfig_Args->MorphCloseSELargeWidth_Tuned) < 0)
  {
    x = (int16_T)(SkinSegmentConfig_Args->MorphCloseSELargeWidth_Tuned - 50);
  } else {
    x = (int16_T)(50 - SkinSegmentConfig_Args->MorphCloseSELargeWidth_Tuned);
  }

  if (i < x) {
    i = 22;
  } else {
    i = 50;
  }

  guard1 = false;
  switch ((int16_T)i) {
   case 22:
    /* Square structuring element with width of 22 pixels     */
    /* Packed binary image */
    /* Local function. */
    /* Type uint32. */
    /* end local function */
    /* ============================================================================================= */
    /* ErodeAndDilate_SEWidth22    Erode and dilate with square structuring element of width 22. */
    /* Inline function */
    /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
    /* Type uint32. */
    /*  eroded logical image */
    /*  logical image */
    /*  structuring element */
    /*  flag for packed image */
    /*  number of rows in unpacked image */
    imerode(IsSkinMask_PixelColorPacked, NRows_Matrix_Reduced,
            c_IsSkinMask_PixelColor_ErodePa);

    /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
    /* Type uint32. */
    /*  dilated logical image */
    /*  structuring element */
    /*  flag for packed image */
    imdilate(c_IsSkinMask_PixelColor_ErodePa, IsSkinMask_PixelColorPacked);

    /* Square structuring element with width of 50 pixels     */
    guard1 = true;
    break;

   case 50:
    /* Packed binary image */
    /* Local function. */
    /* Type uint32. */
    /* end local function */
    /* ============================================================================================= */
    /* ErodeAndDilate_SEWidth50    Erode and dilate with square structuring element of width 50. */
    /* Inline function */
    /* Erode pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
    /* Type uint32. */
    /*  eroded packed logical image */
    /*  packed logical image */
    /*  structuring element */
    /*  flag for packed image */
    /*  number of rows in unpacked image */
    b_imerode(IsSkinMask_PixelColorPacked, NRows_Matrix_Reduced,
              c_IsSkinMask_PixelColor_ErodePa);

    /* Dilate pixels that equal true, which is equivalent to dilating pixels that equal false (non-skin) */
    /* Type uint32. */
    /*  dilated packed logical image */
    /*  packed logical image */
    /*  structuring element */
    /*  flag for packed image */
    b_imdilate(c_IsSkinMask_PixelColor_ErodePa, IsSkinMask_PixelColorPacked);

    /* (Required for code generation)     */
    guard1 = true;
    break;
  }

  if (guard1) {
    /* %%%%% --- Low severity erosion and dilation %%%%%%    */
    /* %%%%% --- Unpack %%%%%%    */
    /* Unpack packed binary image */
    /* M x N matrix; type logical. */
    if ((IsSkinMask_PixelColorPacked->size[0] == 0) ||
        (IsSkinMask_PixelColorPacked->size[1] == 0)) {
      i = IsSkinMask->size[0] * IsSkinMask->size[1];
      IsSkinMask->size[0] = NRows_Matrix_Reduced;
      IsSkinMask->size[1] = IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_boolean_T(IsSkinMask, i);
      RegionMaxIdx = NRows_Matrix_Reduced * IsSkinMask_PixelColorPacked->size[1];
      for (i = 0; i < RegionMaxIdx; i++) {
        IsSkinMask->data[i] = false;
      }
    } else {
      i = IsSkinMask->size[0] * IsSkinMask->size[1];
      IsSkinMask->size[0] = NRows_Matrix_Reduced;
      IsSkinMask->size[1] = IsSkinMask_PixelColorPacked->size[1];
      emxEnsureCapacity_boolean_T(IsSkinMask, i);
      c_x[0] = IsSkinMask_PixelColorPacked->size[0];
      b_IsSkinMask[0] = NRows_Matrix_Reduced;
      c_x[1] = IsSkinMask_PixelColorPacked->size[1];
      b_IsSkinMask[1] = IsSkinMask_PixelColorPacked->size[1];
      bwUnpackingtbb(&IsSkinMask_PixelColorPacked->data[0], c_x,
                     &IsSkinMask->data[0], b_IsSkinMask, true);
    }
  }

  emxFree_uint32_T(&c_IsSkinMask_PixelColor_ErodePa);
  emxFree_uint32_T(&IsSkinMask_PixelColorPacked);
  emxInit_real_T(&t0_RegionIndices, 1, true);
  emxInit_int32_T(&t0_RegionLengths, 1, true);

  /* %%%%% Count the number of pixels classified as skin (true) %%%%%% */
  /* If returning a count of the pixels classified as true is enabled */
  /* end function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (SkinSegmentMask_Ops_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Modify function files for performance %%%%%% */
  /*  */
  /* Before running code generation, input validation was removed from the files for the  */
  /* following functions: */
  /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\bwpack.m */
  /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\bwunpack.m */
  /*  - \Program Files\MATLAB\R2020a\toolbox\images\images\+images\+internal\+coder\morphop.m  */
  /*  */
  /* Specifically, in these files, the following validation functions were commented out: */
  /*  - narginchk */
  /*  - validateattributes */
  /*  */
  /* Note: Seperate files for these functions with these changes could not be made because code   */
  /* generation for these functions expects specific file names. Hence, after code generation, the   */
  /* input validation was added back to the files. */
  /* Note: as these files are located in 'Program Files', admin access is required to edit them. */
  /*  */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /*                                              Example Code                 Upp. Bounds  Var. Size (T/F)  Type */
  /* RUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8 */
  /* GUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8 */
  /* BUint8Code                    = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],  [1, 1] );        %uint8 */
  /* YSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single                       */
  /* CbSingleCode                  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single */
  /* CrSingleCode                  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single */
  /* HSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single                                  */
  /* SSingleCode                   = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],  [1, 1] );        %single  */
  /* IsSkinMask_RangeCode          = coder.typeof( false(500, 500         ),    [inf, inf],  [1, 1] );        %logical            */
  /*                   */
  /*                      */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /* NRows_MatrixCode               = int32(0); */
  /* NCols_MatrixCode               = int32(0); */
  /* CountTrueTFCode                = false; */
  /* TailoredThresholdsTFCode       = false; */
  /* ReturnYTFCode                  = false; */
  /* ReturnCbCrTFCode               = false; */
  /* ReturnHSTFCode                 = false; */
  /* TailoredThresholdsSevereTFCode = false; */
  /* MorphCloseSevereTFCode         = false; */
  /* XOffsetCode                    = int32(0); */
  /* YOffsetCode                    = int32(0); */
  /*  */
  /* Struct with fixed-size fields */
  /* Note: the order and names of fields are compile-time constants. */
  /*  */
  /* SkinSegmentArgsCode = ...                                                                                               */
  /*     struct( ... */
  /*         'SkinColorSamples_NThresholdPassedTF', false, ... */
  /*         'YCbCrThresholdsGeneric', zeros(1, 7, 'single'), ... */
  /*         'HSThresholdsGeneric', zeros(1, 2, 'single'), ... */
  /*         'YCbCrThresholdsTailored', zeros(1, 8, 'single'), ... */
  /*         'YCbCrThresholdsTailored_Sev', zeros(1, 8, 'single'), ... */
  /*         'HSThresholdsTailored', zeros(1, 3, 'single'), ... */
  /*         'HSThresholdsTailored_Sev', zeros(1, 3, 'single'), ... */
  /*         'RangeSEWidth', int16(0), ... */
  /*         'RangeThreshold', uint8(0), ... */
  /*         'MorphCloseSEMediumWidth_Tuned', int16(0), ... */
  /*         'MorphCloseSELargeWidth_Tuned', int16(0) ...    */
  /*     );                                                                    */
  /*  */
  /*  */
  /* %%%%% Set configurations to increase performance %%%%%% */
  /*  */
  /* Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic  */
  /* "Optimization Strategies" */
  /*  */
  /* cfg = coder.config('mex'); */
  /* cfg.GlobalDataSyncMethod = 'NoSync'; */
  /* cfg.ConstantInputs = 'IgnoreValues'; */
  /* cfg.ExtrinsicCalls = false;  */
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
  /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})'; */
  /*  */
  /* Assign to code-generation configuration object */
  /* cfg.PostCodeGenCommand = setbuildargsAsText; */
  /*  */
  /*  */
  /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
  /*  */
  /* codegen SkinSegmentMask_Ops.m -report -config cfg -args {RUint8Code, GUint8Code, BUint8Code, YSingleCode, CbSingleCode, CrSingleCode, HSingleCode, SSingleCode, IsSkinMask_RangeCode, NRows_MatrixCode, NCols_MatrixCode, CountTrueTFCode, TailoredThresholdsTFCode, ReturnYTFCode, ReturnCbCrTFCode, ReturnHSTFCode, TailoredThresholdsSevereTFCode, MorphCloseSevereTFCode, XOffsetCode, YOffsetCode, SkinSegmentArgsCode} */
  /*               */
  /* } */
  /* end function */
  /* %%%%% Determine largest region in skin-segmentation mask %%%%%% */
  /* Group pixels into connected regions, using the connection criteria of 8, which is the default    */
  /* setting for function bwconncomp. */
  /* Code generation running */
  /* Note: FindLargestRegion is a custom function located within folder 'FacePulseRate'. */
  /*  The linear indices of pixels corresponding to the largest region. N */
  /*  pixels x 1 column vector; type int32. */
  /*  The number of pixels in the largest region identified. Scalar; type */
  /*  int32. */
  /*  The number of regions identified. Scalar; type int32. */
  /* FindLargestRegion   Identify the largest region in the skin-segmentation mask and return the  */
  /*                     linear indices corresponding to its pixels.  */
  /*                   */
  /*     Helper function to function FacePulseRate. */
  /*     Within function FacePulseRate, called by function */
  /*     ROIMeans_FirstRead_CollectSkinColorSamples. */
  /*  */
  /*     Code generation: This function intended only for code generation (C language). */
  /*  */
  /*     Output: */
  /*  */
  /*         RegionMaxPixelIdx = Linear indices corresponding to pixels of the largest region. Type  */
  /*                             int32. */
  /*         NPixelsMax        = The number of pixels in the largest region identified. */
  /*         NRegions          = The number of regions identified. */
  /*  */
  /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
  /*     the Responsible AI License (RAIL). */
  /* %%%%% Code generation settings %%%%%% */
  /* Inline function */
  /* Specify variable-size variables */
  /* Note: Improve efficiency by capping row length at 400 to prevent dynamic memory allocation. */
  /*                                    Upp. Bounds   Var. Size (T/F) */
  /* scalar struct */
  /* cell array */
  /* %%%%% Find connected regions %%%%%% */
  /* Scalar struct. */
  bwconncomp(IsSkinMask, &expl_temp, c_x, &t0_NumObjects, t0_RegionIndices,
             t0_RegionLengths);

  /* %%%%% Find the largest region %%%%%% */
  /* The number of regions identified */
  /* Scalar; type int32. */
  x = (int32_T)muDoubleScalarRound(t0_NumObjects);

  /* Prevent dynamic memory allocation from colon operator by asserting length */
  /* Initialize index of region with the maximum number of pixels */
  RegionMaxIdx = -1;

  /* Initialize the number of pixels corresponding to the region with the maximum number of pixels */
  /* Note: this value should be less than the smallest possible value. */
  NPixelsMax = -1;

  /* If at least one region identified */
  emxFree_boolean_T(&IsSkinMask);
  if (x != 0) {
    /* Loop across regions */
    for (b_i = 0; b_i < x; b_i++) {
      /* The number of pixel indices in the ith region */
      /* Cast from type coder.internal.indexInt to type int32. */
      /* Determine whether the ith region is larger than other regions previously iterated */
      if (t0_RegionLengths->data[b_i] > NPixelsMax) {
        NPixelsMax = t0_RegionLengths->data[b_i];
        RegionMaxIdx = b_i;
      }
    }

    /* %%%%% Return the pixel indices of the largest region %%%%%% */
    /* Preallocate the linear index of the first pixel of the ith region */
    /* Initialize the linear index of the last pixel of the ith region */
    RegionEndIndex_ith = 0;

    /* Prevent dynamic memory allocation from colon operator by asserting length */
    /* Loop up to index of largest region */
    for (b_i = 0; b_i <= RegionMaxIdx; b_i++) {
      /* The number of pixel indices in the ith region */
      /* Cast from type coder.internal.indexInt to type int32. */
      /* Linear index of the first pixel in the ith region */
      NCols_Matrix_Reduced = RegionEndIndex_ith + 1;

      /* Linear index of the last pixel in the ith region */
      RegionEndIndex_ith += t0_RegionLengths->data[b_i];
    }

    /* Preallocate pixel indices for the largest region */
    i = t0_RegionLengths->size[0];
    t0_RegionLengths->size[0] = t0_RegionLengths->data[RegionMaxIdx];
    emxEnsureCapacity_int32_T(t0_RegionLengths, i);

    /* Initialize index for pixel indices of the largest region */
    RegionMaxIdx = -1;

    /* Loop across pixels indices of ith region */
    for (j = NCols_Matrix_Reduced; j <= RegionEndIndex_ith; j++) {
      RegionMaxIdx++;

      /* Assign pixel index to cell array */
      t0_RegionLengths->data[RegionMaxIdx] = (int32_T)muDoubleScalarRound
        (t0_RegionIndices->data[j - 1]);
    }

    /* If no regions identified */
  } else {
    i = t0_RegionLengths->size[0];
    t0_RegionLengths->size[0] = 1;
    emxEnsureCapacity_int32_T(t0_RegionLengths, i);
    t0_RegionLengths->data[0] = 0;
  }

  emxFree_real_T(&t0_RegionIndices);

  /* end function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (FindLargestRegion_mex) of the function. */
  /* { */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
  /*  */
  /*                               Example Code         Upp. Bounds      Var. Size (T/F)  Type */
  /* IsSkinMaskCode = coder.typeof( false(500, 500),     [inf, inf],      [1, 1] );        %logical */
  /*      */
  /*        */
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
  /* Argument buildInfo: this variable is assign by the caller (the codegen command executed  */
  /* below) and is not present in the base workspace. */
  /*  */
  /* Second argument: specify a cell array of compiler-specific flags, where each flag is a  */
  /* character vector. As function setbuildargs will be evaluated from text, use double ' quotes for  */
  /* each character vector to maintain the charater vector, */
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
  /* codegen FindLargestRegion.m -report -config cfg -args {IsSkinMaskCode} */
  /*  */
  /* }         */
  /* Code generation not running */
  /* %%%%% Take minimums, maximums, and means of the largest region %%%%%% */
  /* Metrics for tailored skin segmentation: */
  /*  - Mins and maxes of indexed Y, Cb, Cr, H, and S channels. */
  /* Metrics for the skin-detection algorithm thresholds:    */
  /*  - Indexed RGB means. */
  /*  - Indexed YCbCr means.     */
  /* Note: Type double R, G, and B means required for function SkinDetect_RGBProbSkinTrain, which uses  */
  /* function fminunc, which requires type double.       */
  /* If no region identified, skip over the remaining sections of the function and set outputs (color */
  /* values) to NaN. Subsequent functions that depend upon these color values are set to omit values */
  /* that equal NaN. */
  if (x == 0) {
    ithPrimaryROIRGBMeans[0] = rtNaN;
    ithPrimaryROIYCbCrMeans[0] = rtNaNF;
    ithPrimaryROIRGBMeans[1] = rtNaN;
    ithPrimaryROIYCbCrMeans[1] = rtNaNF;
    ithPrimaryROIRGBMeans[2] = rtNaN;
    ithPrimaryROIYCbCrMeans[2] = rtNaNF;
    for (i = 0; i < 11; i++) {
      ithPrimaryROIYCbCrHSMinsMaxs[i] = rtNaNF;
    }

    /* At least one region is available     */
  } else {
    /* Return minimums, maximums, and means                             */
    /* Note: MeansMinsMaxes is custom function located within folder FacePulseRate.          */
    /*  Minimums and maximums. 1 x 11 row vector; type single. */
    /*  Means of indexed Y, Cb, and Cr channels; 1 x 3 row vector, */
    /*  type single. */
    /*  Means of indexed R, G, and B channels; 1 x 3 row vector, */
    /*  type double. */
    /* MeansMinsMaxes   Returns the means, minimums, and maximums from the YCbCr, HSV, and RGB color */
    /*                  channels according to a linear index.                            */
    /*  */
    /*     Helper function to function FacePulseRate. */
    /*     Within function FacePulseRate, called by function ROIMeans_FirstRead_CollectSkinColorSamples. */
    /*     */
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
    /*     Inputs */
    /*  */
    /*         Y_Single,  */
    /*         Cb_Single,  */
    /*         Cr_Single,      */
    /*         H_Single, */
    /*         S_Single, */
    /*         R_Uint8, */
    /*         G_Uint8, */
    /*         B_Uint8, */
    /*                                = R, G, B, Y, Cb, Cr, H, and S color channels (matrices) to be     */
    /*                                  indexed. M x N matrices; type single or type uint8 as indicated. */
    /*         LinearIdx              = Linear index for indexing values in each of the matrices. P x 1  */
    /*                                  column vector; type int32. */
    /*         LinearIdx_N            = Length of the linear index; used as the divisor for the mean.   */
    /*                                  Although this value could be found here (i.e.,    */
    /*                                  length(LinearIdx_Double)), this value is assumed to be available   */
    /*                                  for input. Scalar; type int32. */
    /*         TakeMeansTF            = Whether to return the Y, Cb, and Cr means. */
    /*  */
    /*         The following inputs used to align the coordinate plane from that of the reduced-size ROI  */
    /*         to that of the full-size ROI:                        */
    /*                                   */
    /*         X_Matrix_Reduced       = The X-coordinate offset for the reduced matrix. Scalar; type  */
    /*                                  int32. */
    /*         Y_Matrix_Reduced       = The Y-coordinate offset for the reduced matrix. Scalar; type  */
    /*                                  int32. */
    /*         NRows_Matrix_Reduced   = Number of rows for the reduced matrix. Scalar; type int32. */
    /*         NRows_Matrix           = Number of rows for the full matrix. Scalar; type int32. */
    /*  */
    /*     Outputs */
    /*  */
    /*         YCbCrHSMinsMaxs_Single = Minimums and maximums of the Y, Cb, Cr, H, and S channels and the */
    /*                                  Cb-to-Cr proportion. I.e.,     */
    /*                                  [RegionMaxN_YMin,          RegionMaxN_YMax,  ... */
    /*                                   RegionMaxN_CbMin,         RegionMaxN_CbMax, ... */
    /*                                   RegionMaxN_CrMin,         RegionMaxN_CrMax, ... */
    /*                                   RegionMaxN_CbCrRatioMin,  RegionMaxN_CbCrRatioMax ... */
    /*                                   RegionMaxN_HMax,          RegionMaxN_SMin, ... */
    /*                                   RegionMaxN_SMax];  */
    /*                                  %1 x 11 row vector; type single. */
    /*         YCbCrMeans_Single      = Means of Y, Cb, and Cr channels. 1 x 3 row vector; type single. */
    /*         RGBMeans_Double        = Means of R, G, and B channels. 1 x 3 row vector; type double. */
    /*  */
    /*     Performance Notes:  */
    /*  */
    /*     - It has been observed that linear indexing is faster with C-compiled code than with Matlab  */
    /*       code, which plays a role in the speed improvement. This same improvement is not evident by */
    /*       logical indexing. The speed improvement may still be retained even after converting from a  */
    /*       logical index to a linear index prior to entry to the function. */
    /*     - sum() / N shows better performance than mean().   */
    /*     - The divisor should be of the same type as the dividend for fastest evaluation. */
    /*     - Testing has found that performance is fastest with uint8 as input rather than single; this  */
    /*       is true even when the divisor (NDouble) is of type single. However, note that conversion  */
    /*       from from floating point to uint8 for the purpose of using as input is inefficient. */
    /*  */
    /*  */
    /*     Copyright */
    /*     --------- */
    /*  */
    /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
    /*     the Responsible AI License (RAIL). */
    /* Inline function */
    /* %%%%% Setup %%%%%% */
    /* Preallocate output vector for the Y, Cb, and Cr means */
    /* Preallocate output vector for the R, G, and B means */
    /* Initialize running minimums and maximums */
    /* Note: the initial minimums and maximums should be outside the range of possible values. */
    RegionMaxN_YMin = 300.0F;
    RegionMaxN_YMax = -1.0F;
    RegionMaxN_CbMin = 300.0F;
    RegionMaxN_CbMax = -1.0F;
    RegionMaxN_CrMin = 300.0F;
    RegionMaxN_CrMax = -1.0F;
    RegionMaxN_HMax = -1.0F;
    RegionMaxN_SMin = 300.0F;
    RegionMaxN_SMax = -1.0F;
    RegionMaxN_CbCrRatioMin = 300.0F;
    RegionMaxN_CbCrRatioMax = -1.0F;

    /* Initialize sum accumulators for means */
    SumY = 0.0F;
    SumCb = 0.0F;
    SumCr = 0.0F;
    SumR = 0U;
    SumG = 0U;
    SumB = 0U;

    /* %%%%% Take mins, maxes, and means %%%%%% */
    /* %%%%% --- Loop across elements of color channels %%%%%%     */
    /* Loop across elements */
    for (b_i = 0; b_i < NPixelsMax; b_i++) {
      /* %%%%% >>>>>> Extract ith elements of color channels %%%%%%         */
      /* Extract ith linear index */
      /* Scalar; type int32. */
      /* Convert the linear index to align with the coordinate plane of the full ROI */
      /* Local function. */
      /* Scalars; type int32. */
      /* end main function */
      /* ============================================================================================= */
      /* Local functions */
      /* ============================================================================================= */
      /* ============================================================================================= */
      /* AdjustLinIdxCoordinatePlane   Adjust a scalar linear index to align with a different coordinate  */
      /*                               plane. */
      /*  */
      /*     Description:  */
      /*  */
      /*     Adjust a scalar linear index in coordinate plane A to align with coordinate plane B. To adjust */
      /*     between planes, known offsets between the planes are used. The offsets are given in X- and  */
      /*     Y-coordinates. */
      /*  */
      /*     During the alignment, the linear index is converted into subscripts. An additional step then */
      /*     converts the subscripts back to a linear index. Although there is a cost to converting back  */
      /*     to a linear index, this cost should be made up for by the greater efficiency of indexing with */
      /*     a linear index where the linear index is used. */
      /*  */
      /*     Inputs: */
      /*  */
      /*         LinIdx   = Linear index of coordinate plane A. Scalar. */
      /*         Offset_X = X-coordinate offset giving difference between coordinate plane B and coordinate */
      /*                    plane A. */
      /*         Offset_Y = Y-coordinate offset giving difference between coordinate plane B and coordinate */
      /*                    plane A. */
      /*         NRows_A  = Number of rows of coordinate plane A. */
      /*         NRows_B  = Number of rows of coordinate plane B. */
      /* Inline function */
      /* Convert to row subscript  */
      /* Scalar; type int32.        */
      if (NRows_Matrix_Reduced == 0) {
        RegionMaxIdx = -1;
      } else {
        RegionMaxIdx = (t0_RegionLengths->data[b_i] - NRows_Matrix_Reduced *
                        div_s32(t0_RegionLengths->data[b_i] - 1,
          NRows_Matrix_Reduced)) - 2;
      }

      /* Convert to column subscript  */
      /* Scalar; type int32. */
      x = (t0_RegionLengths->data[b_i] - RegionMaxIdx) - 2;
      if (NRows_Matrix_Reduced == 0) {
        if (x == 0) {
          NCols_Matrix_Reduced = 0;
        } else if (x < 0) {
          NCols_Matrix_Reduced = MIN_int32_T;
        } else {
          NCols_Matrix_Reduced = MAX_int32_T;
        }
      } else if (NRows_Matrix_Reduced == 1) {
        NCols_Matrix_Reduced = x;
      } else {
        if (x >= 0) {
          b_x = (uint32_T)x;
        } else if (x == MIN_int32_T) {
          b_x = 2147483648U;
        } else {
          b_x = (uint32_T)-x;
        }

        q = (uint32_T)NRows_Matrix_Reduced;
        if (q == 0U) {
          q = MAX_uint32_T;
        } else {
          q = b_x / q;
        }

        b_x -= q * NRows_Matrix_Reduced;
        if ((b_x > 0U) && (b_x >= ((uint32_T)NRows_Matrix_Reduced >> 1U) +
                           (NRows_Matrix_Reduced & 1U))) {
          q++;
        }

        NCols_Matrix_Reduced = (int32_T)q;
        if (x < 0) {
          NCols_Matrix_Reduced = -(int32_T)q;
        }
      }

      /* Use offset to align with coordinate plane B */
      /* Adjust from subscripts to linear index for indexing efficiency */
      /* Note: as we are in the coordinate plane B now, the rows of coordinate plane B (NRows_B) are used. */
      RegionMaxIdx = (RegionMaxIdx + Y_Matrix_Reduced) + ((NCols_Matrix_Reduced
        + X_Matrix_Reduced) - 1) * NRows_Matrix;

      /* end local function */
      /* ============================================================================================= */
      /* Code-generation and build script */
      /* ============================================================================================= */
      /* Code-generation and build script used to generate C-language code and create the compiled version  */
      /* (MeansMinsMaxes) of the function. */
      /* Note: as of the current implementation of FacePulseRate, a compiled version of this function is */
      /* not produced because it is compiled within function ROIMeans_FirstRead_CollectSkinColorSamples.  */
      /* { */
      /*  */
      /* %%%%% Specify variable-size input arguments %%%%%% */
      /*  */
      /* See Matlab documentation for coder.typeof. */
      /*                              Example Code                 Upp. Bounds    Var. Size (T/F)   Type */
      /* Y_SingleCode  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],    [1, 1] );         %single */
      /* Cb_SingleCode = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],    [1, 1] );         %single */
      /* Cr_SingleCode = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],    [1, 1] );         %single */
      /* H_SingleCode  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],    [1, 1] );         %single */
      /* S_SingleCode  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],    [1, 1] );         %single */
      /* LinearIdxCode = coder.typeof( zeros(500, 1,   'double'),   [inf, 1],      [1, 0] );         %double */
      /*  */
      /*  */
      /* %%%%% Specify fixed-size input arguments %%%%%% */
      /*  */
      /* LinearIdx_NCode          = int32(0); */
      /* X_Matrix_ReducedCode     = int32(0);  */
      /* Y_Matrix_ReducedCode     = int32(0); */
      /* NRows_Matrix_ReducedCode = int32(0); */
      /* NRows_MatrixCode         = int32(0); */
      /* TakeMeansTFCode          = false; */
      /*  */
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
      /* Argument buildInfo: this variable is assign by the caller (the codegen command executed below) and  */
      /* is not present in the base workspace. */
      /*  */
      /* Second argument: specify a cell array of compiler-specific flags, where each flag is a character  */
      /* vector. As function setbuildargs will be evaluated from text, use double ' quotes for each  */
      /* character vector to maintain the charater vector, */
      /* e.g., {''-Ofast'' ''-fsingle-precision-constant''}. */
      /*  */
      /* setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})'; */
      /*  */
      /* cfg.PostCodeGenCommand = setbuildargsAsText; */
      /*  */
      /*  */
      /* %%%%% Execute codegen command to generate code and build compiled mex file %%%%%% */
      /*  */
      /* codegen MeansMinsMaxesYCbCrHSV.m -report -config cfg -args {Y_SingleCode, Cb_SingleCode, Cr_SingleCode, H_SingleCode, S_SingleCode, LinearIdxCode, LinearIdx_NCode, X_Matrix_ReducedCode, Y_Matrix_ReducedCode, NRows_Matrix_ReducedCode, NRows_MatrixCode, TakeMeansTFCode} */
      /*               */
      /* } */
      /* Extract from input matrices */
      /* Scalars; type single. */
      /* Note: H_Single and S_Single elements extracted directly. */
      /* %%%%% >>>>>> Take minimums and maximums of ith elements or element ratios %%%%%%  */
      /* Ratio of Cb to Cr */
      RegionMaxN_CbCrRatio_ith = CbSingle->data[RegionMaxIdx] / CrSingle->
        data[RegionMaxIdx];

      /* Minimums and maximums: */
      if (YSingle->data[RegionMaxIdx] < RegionMaxN_YMin) {
        RegionMaxN_YMin = YSingle->data[RegionMaxIdx];
      }

      if (YSingle->data[RegionMaxIdx] > RegionMaxN_YMax) {
        RegionMaxN_YMax = YSingle->data[RegionMaxIdx];
      }

      if (CbSingle->data[RegionMaxIdx] < RegionMaxN_CbMin) {
        RegionMaxN_CbMin = CbSingle->data[RegionMaxIdx];
      }

      if (CbSingle->data[RegionMaxIdx] > RegionMaxN_CbMax) {
        RegionMaxN_CbMax = CbSingle->data[RegionMaxIdx];
      }

      if (CrSingle->data[RegionMaxIdx] < RegionMaxN_CrMin) {
        RegionMaxN_CrMin = CrSingle->data[RegionMaxIdx];
      }

      if (CrSingle->data[RegionMaxIdx] > RegionMaxN_CrMax) {
        RegionMaxN_CrMax = CrSingle->data[RegionMaxIdx];
      }

      if (HSingle->data[RegionMaxIdx] > RegionMaxN_HMax) {
        RegionMaxN_HMax = HSingle->data[RegionMaxIdx];
      }

      if (SSingle->data[RegionMaxIdx] < RegionMaxN_SMin) {
        RegionMaxN_SMin = SSingle->data[RegionMaxIdx];
      }

      if (SSingle->data[RegionMaxIdx] > RegionMaxN_SMax) {
        RegionMaxN_SMax = SSingle->data[RegionMaxIdx];
      }

      if (RegionMaxN_CbCrRatio_ith < RegionMaxN_CbCrRatioMin) {
        RegionMaxN_CbCrRatioMin = RegionMaxN_CbCrRatio_ith;
      }

      if (RegionMaxN_CbCrRatio_ith > RegionMaxN_CbCrRatioMax) {
        RegionMaxN_CbCrRatioMax = RegionMaxN_CbCrRatio_ith;
      }

      /* %%%%% >>>>>> Accumulate sums of ith elements %%%%%%              */
      /* Sums of Y, Cb and Cr elements */
      /* Scalars; type single. */
      SumY += YSingle->data[RegionMaxIdx];
      SumCb += CbSingle->data[RegionMaxIdx];
      SumCr += CrSingle->data[RegionMaxIdx];

      /* Sums of R, G and B elements */
      /* Cast to larger-size type to prevent overflow; use type uint32 for integer arithmetic. */
      /* Scalars; type uint32. */
      SumR += RUint8->data[RegionMaxIdx];
      SumG += GUint8->data[RegionMaxIdx];
      SumB += BUint8->data[RegionMaxIdx];
    }

    /* %%%%% Take and assign means %%%%%% */
    /* denominator */
    ithPrimaryROIYCbCrMeans[0] = SumY / (real32_T)NPixelsMax;
    ithPrimaryROIYCbCrMeans[1] = SumCb / (real32_T)NPixelsMax;
    ithPrimaryROIYCbCrMeans[2] = SumCr / (real32_T)NPixelsMax;

    /* denominator */
    ithPrimaryROIRGBMeans[0] = (real_T)SumR / (real32_T)NPixelsMax;
    ithPrimaryROIRGBMeans[1] = (real_T)SumG / (real32_T)NPixelsMax;
    ithPrimaryROIRGBMeans[2] = (real_T)SumB / (real32_T)NPixelsMax;

    /* %%%%% Assign mins and maxes %%%%%% */
    ithPrimaryROIYCbCrHSMinsMaxs[0] = RegionMaxN_YMin;
    ithPrimaryROIYCbCrHSMinsMaxs[1] = RegionMaxN_YMax;
    ithPrimaryROIYCbCrHSMinsMaxs[2] = RegionMaxN_CbMin;
    ithPrimaryROIYCbCrHSMinsMaxs[3] = RegionMaxN_CbMax;
    ithPrimaryROIYCbCrHSMinsMaxs[4] = RegionMaxN_CrMin;
    ithPrimaryROIYCbCrHSMinsMaxs[5] = RegionMaxN_CrMax;
    ithPrimaryROIYCbCrHSMinsMaxs[6] = RegionMaxN_CbCrRatioMin;
    ithPrimaryROIYCbCrHSMinsMaxs[7] = RegionMaxN_CbCrRatioMax;
    ithPrimaryROIYCbCrHSMinsMaxs[8] = RegionMaxN_HMax;
    ithPrimaryROIYCbCrHSMinsMaxs[9] = RegionMaxN_SMin;
    ithPrimaryROIYCbCrHSMinsMaxs[10] = RegionMaxN_SMax;
  }

  emxFree_int32_T(&t0_RegionLengths);

  /* end if any region available */
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (ROIMeans_FirstRead_CollectSkinColorSamples.c) */
