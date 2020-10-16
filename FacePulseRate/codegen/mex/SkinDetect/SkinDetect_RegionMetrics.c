/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * SkinDetect_RegionMetrics.c
 *
 * Code generation for function 'SkinDetect_RegionMetrics'
 *
 */

/* Include files */
#include "SkinDetect_RegionMetrics.h"
#include "SkinDetect_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <string.h>

/* Function Declarations */
static void Ops(int32_T i, const b_struct_T RegionIndices_data[], const real32_T
                RegionNPixels_Single_data[], const emxArray_uint8_T
                *RBounded_Uint8, const emxArray_uint8_T *GBounded_Uint8, const
                emxArray_uint8_T *BBounded_Uint8, const emxArray_real32_T
                *YBounded_Single, const emxArray_real32_T *CbBounded_Single,
                const emxArray_real32_T *CrBounded_Single, real32_T MeanOfMeansY,
                real32_T MeanOfMeansCb, real32_T MeanOfMeansCr, real32_T
                StdDevOfMeansY, real32_T StdDevOfMeansCb, real32_T
                StdDevOfMeansCr, real_T *region_M_R_ith, real_T *region_M_G_ith,
                real_T *region_M_B_ith, real32_T *region_Z_Y_ith, real32_T
                *region_Z_Cb_ith, real32_T *region_Z_Cr_ith, real32_T
                *region_SD_Cr_ith);

/* Function Definitions */
static void Ops(int32_T i, const b_struct_T RegionIndices_data[], const real32_T
                RegionNPixels_Single_data[], const emxArray_uint8_T
                *RBounded_Uint8, const emxArray_uint8_T *GBounded_Uint8, const
                emxArray_uint8_T *BBounded_Uint8, const emxArray_real32_T
                *YBounded_Single, const emxArray_real32_T *CbBounded_Single,
                const emxArray_real32_T *CrBounded_Single, real32_T MeanOfMeansY,
                real32_T MeanOfMeansCb, real32_T MeanOfMeansCr, real32_T
                StdDevOfMeansY, real32_T StdDevOfMeansCb, real32_T
                StdDevOfMeansCr, real_T *region_M_R_ith, real_T *region_M_G_ith,
                real_T *region_M_B_ith, real32_T *region_Z_Y_ith, real32_T
                *region_Z_Cb_ith, real32_T *region_Z_Cr_ith, real32_T
                *region_SD_Cr_ith)
{
  int32_T SumR_tmp;
  int32_T b_i;
  int32_T j;
  real32_T SumB;
  real32_T SumCb;
  real32_T SumCr;
  real32_T SumG;
  real32_T SumR;
  real32_T SumY;
  real32_T f;
  uint32_T SumB_uint32;
  uint32_T SumG_uint32;
  uint32_T SumR_uint32;

  /* end main function */
  /* ============================================================================================= */
  /* Local functions */
  /* ============================================================================================= */
  /* ============================================================================================= */
  /* Ops   Take means, z-scores, and a standard deviation of the ith region.   */
  /*  */
  /*     Description: */
  /*  */
  /*     - Take the means of the R, G, and B channels of the ith region. */
  /*  */
  /*     - Take the z-scores of the Y, Cb, and Cr channels of the ith region. */
  /*  */
  /*       The z-score for a region is calculated by subtracting its mean from the reference mean and */
  /*       dividing by the reference standard deviation. The reference mean and standard deviation are */
  /*       from skin-color samples collected from ROIs of the video (see function  */
  /*       ROIMeans_FirstRead_CollectSkinColorSamples). */
  /*  */
  /*     - Take the standard deviation of the Cr channel of the ith region. */
  /*  */
  /*     Use integer arithmetic rather than floating-point arithmetic for efficiency if overflow will */
  /*     not occur. */
  /*  */
  /*     Note: Different implements are used for code generation and Matlab code. */
  /* %%%%% Extract linear indices of ith region %%%%%%  */
  /* Note: RegionIndices.PixelIdxList is a N x 1 non-scalar struct, where N equals the number of */
  /* regions. Each row contains the pixel indices of a given region. */
  /* P x 1 column vector; type double. */
  /* %%%%% If called during code generation %%%%%% */
  /* If called during code generation, use for loop; if using Matlab code, use vectorization. */
  /* if code generation */
  /* Inline function */
  /* Denominator for ith region  */
  /* Scalar; type single. */
  /* %%%%% --- Optimized by integer arithmetic %%%%%% */
  /* Use algorithm optimized by integer arithmetic if all indices less than specified length */
  f = RegionNPixels_Single_data[i - 1];
  if (f < 1.5686E+7F) {
    /* Accumulators for ith region */
    /* Scalars; type uint32 or single. */
    SumR_uint32 = 0U;
    SumG_uint32 = 0U;
    SumB_uint32 = 0U;
    SumY = 0.0F;
    SumCb = 0.0F;
    SumCr = 0.0F;

    /* Loop across elements, j, corresponding to ith region index  */
    b_i = (int32_T)RegionNPixels_Single_data[i - 1];
    for (j = 0; j < b_i; j++) {
      /* jth element of ith region index */
      /* Scalar; type uint32. */
      /* RGB colorspace sums */
      /* Cast to type uint32 for efficiency. */
      /* Scalars; type uint32. */
      SumR_tmp = (int32_T)RegionIndices_data[i - 1].PixelIdxList->data[(int32_T)
        ((real32_T)j + 1.0F) - 1] - 1;
      SumR_uint32 += RBounded_Uint8->data[SumR_tmp];
      SumG_uint32 += GBounded_Uint8->data[SumR_tmp];
      SumB_uint32 += BBounded_Uint8->data[SumR_tmp];

      /* YCbCr colorspace sums */
      /* Scalars; type single. */
      SumY += YBounded_Single->data[SumR_tmp];
      SumCb += CbBounded_Single->data[SumR_tmp];
      SumCr += CrBounded_Single->data[SumR_tmp];
    }

    /* %%%%% >>>>>> Take RGB means of ith region %%%%%%  */
    /* Take means and cast to type double for output. */
    /* Scalars; type double. */
    /* Red channel mean */
    *region_M_R_ith = (real32_T)SumR_uint32 / f;

    /* Green channel mean */
    *region_M_G_ith = (real32_T)SumG_uint32 / f;

    /* Blue channel mean */
    *region_M_B_ith = (real32_T)SumB_uint32 / f;

    /* %%%%% --- Not optimized by integer arithmetic %%%%%%         */
  } else {
    /* Accumulators for ith region */
    /* Scalars; type single. */
    SumR = 0.0F;
    SumG = 0.0F;
    SumB = 0.0F;
    SumY = 0.0F;
    SumCb = 0.0F;
    SumCr = 0.0F;

    /* Loop across elements, j, corresponding to ith region index  */
    b_i = (int32_T)f;
    for (j = 0; j < b_i; j++) {
      /* jth element of ith region index */
      /* Scalar; type uint32. */
      /* RGB colorspace sums */
      /* Cast to type uint32 for efficiency. */
      /* Scalars; type single. */
      SumR_tmp = (int32_T)RegionIndices_data[i - 1].PixelIdxList->data[(int32_T)
        ((real32_T)j + 1.0F) - 1] - 1;
      SumR += (real32_T)RBounded_Uint8->data[SumR_tmp];
      SumG += (real32_T)GBounded_Uint8->data[SumR_tmp];
      SumB += (real32_T)BBounded_Uint8->data[SumR_tmp];

      /* YCbCr colorspace sums */
      /* Scalars; type single. */
      SumY += YBounded_Single->data[SumR_tmp];
      SumCb += CbBounded_Single->data[SumR_tmp];
      SumCr += CrBounded_Single->data[SumR_tmp];
    }

    /* %%%%% >>>>>> Take RGB means of ith region %%%%%%  */
    /* Take means and cast to type double for output. */
    /* Scalars; type double. */
    /* Red channel mean */
    *region_M_R_ith = SumR / f;

    /* Green channel mean */
    *region_M_G_ith = SumG / f;

    /* Blue channel mean */
    *region_M_B_ith = SumB / f;
  }

  /* %%%%% --- Take YCbCr z-scores and Cr standard deviation of ith region %%%%%%     */
  /* Scalars; type single. */
  /* ith region YCbCr z-scores:    */
  /* Y channel z-score */
  *region_Z_Y_ith = (SumY / f - MeanOfMeansY) / StdDevOfMeansY;

  /* Cb channel z-score */
  *region_Z_Cb_ith = (SumCb / f - MeanOfMeansCb) / StdDevOfMeansCb;

  /* Cr channel mean */
  SumR = SumCr / f;

  /* Cr channel z-score */
  *region_Z_Cr_ith = (SumR - MeanOfMeansCr) / StdDevOfMeansCr;

  /* ith region Cr standard deviation: */
  /* If more than 1 pixel for the region  */
  if (f > 1.0F) {
    /* Initialize accumulator */
    SumG = 0.0F;
    b_i = (int32_T)RegionNPixels_Single_data[i - 1];
    for (j = 0; j < b_i; j++) {
      SumB = CrBounded_Single->data[(int32_T)RegionIndices_data[i - 1].
        PixelIdxList->data[(int32_T)((real32_T)j + 1.0F) - 1] - 1] - SumR;

      /* Note: use multiply rather than ^2 for efficiency */
      SumB *= SumB;
      SumG += SumB;
    }

    /* Cr channel standard deviation        */
    *region_SD_Cr_ith = muSingleScalarSqrt(SumG / (f - 1.0F));
  } else {
    *region_SD_Cr_ith = 0.0F;
  }

  /* %%%%% Using Matlab Code %%%%%% */
  /* end local function */
  /* ============================================================================================= */
  /* Code-generation and build script */
  /* ============================================================================================= */
  /* Code-generation and build script used to generate C-language code and create the compiled version  */
  /* (SkinDetect_RegionMetrics_mex) of the function. */
  /* Note: at present, a separate compiled version of this function is not used as it is compiled  */
  /* within function SkinDetect. */
  /* { */
  /*  */
  /* %%%%% Specify variable-size input arguments %%%%%% */
  /*  */
  /* See Matlab documentation for coder.typeof. */
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
  /* Input Argument                           Example Code                 Upp. Bounds     Var. Size (T/F)  Type */
  /* RegionNPixels_SingleCode  = coder.typeof( zeros(50, 1, 'single'),      [400, 1],       [1, 0] );        %single */
  /* RUint8Code                = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8 */
  /* GUint8Code                = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8 */
  /* BUint8Code                = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8 */
  /* YSingleCode               = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single */
  /* CbSingleCode              = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single */
  /* CrSingleCode              = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single */
  /*  */
  /*  */
  /* %%%%% Specify fixed-size input arguments %%%%%% */
  /*  */
  /*                        Example Code                                                                  */
  /* NRegionsCode          = int32(1);                                                                   */
  /* MeanOfMeansYCode      = single(1);                                                                   */
  /* MeanOfMeansCbCode     = single(1);                                                                   */
  /* MeanOfMeansCrCode     = single(1);                                                                     */
  /* StdDevOfMeansYCode    = single(1);                                                                  */
  /* StdDevOfMeansCbCode   = single(1);                                                                    */
  /* StdDevOfMeansCrCode   = single(1);                                                                     */
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
  /* codegen SkinDetect_RegionMetrics.m -report -config cfg -args {RegionIndicesCode, NRegionsCode, RegionNPixels_SingleCode, RUint8Code, GUint8Code, BUint8Code, YSingleCode, CbSingleCode, CrSingleCode, MeanOfMeansYCode, MeanOfMeansCbCode, MeanOfMeansCrCode, StdDevOfMeansYCode, StdDevOfMeansCbCode, StdDevOfMeansCrCode} */
  /*  */
  /* } */
}

void SkinDetect_RegionMetrics(emlrtCTX aTLS, const b_struct_T
  RegionIndices_data[], int32_T NRegions, const real32_T
  RegionNPixels_Single_data[], const emxArray_uint8_T *RBounded_Uint8, const
  emxArray_uint8_T *GBounded_Uint8, const emxArray_uint8_T *BBounded_Uint8,
  const emxArray_real32_T *YBounded_Single, const emxArray_real32_T
  *CbBounded_Single, const emxArray_real32_T *CrBounded_Single, real32_T
  MeanOfMeansY, real32_T MeanOfMeansCb, real32_T MeanOfMeansCr, real32_T
  StdDevOfMeansY, real32_T StdDevOfMeansCb, real32_T StdDevOfMeansCr, real_T
  RegionRGBMeans_data[], int32_T RegionRGBMeans_size[2], real32_T
  region_Z_Y_data[], int32_T region_Z_Y_size[1], real32_T region_Z_Cb_data[],
  int32_T region_Z_Cb_size[1], real32_T region_Z_Cr_data[], int32_T
  region_Z_Cr_size[1], real32_T region_SD_Cr_data[], int32_T region_SD_Cr_size[1])
{
  jmp_buf * volatile emlrtJBStack;
  real_T region_M_B_data[400];
  real_T region_M_G_data[400];
  real_T region_M_R_data[400];
  real_T d;
  real_T d1;
  real_T d2;
  int32_T i;
  int32_T ub_loop;
  real32_T f;
  real32_T f1;
  real32_T f2;
  real32_T f3;

  /* SkinDetect_RegionMetrics   Calculate region RGB means and YCbCr Z-Scores within the skin-detection */
  /*                            algorithm.  */
  /*                                                                 */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, called by function SkinDetect_RejectRegions. */
  /*  */
  /*  */
  /*     Code Generation */
  /*     --------------- */
  /*  */
  /*     Can be called as a Matlab function or used for C-language code generation. */
  /*  */
  /*     This function uses a bounded variable size for variable NPixelsEachRegion_SingleCode to   */
  /*     improve efficiency. Ensure that this input does not exceed these bounds. */
  /*   */
  /*  */
  /*     Description */
  /*     ----------- */
  /*  */
  /*     Calculate region RGB means and YCbCr Z-Scores within the skin-detection algorithm. */
  /*  */
  /*     See the file for function SkinDetect for additional description. */
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
  /* Declare variable-size variables: */
  /* Note: Improve efficiency by capping row length at 400 to prevent dynamic memory allocation. */
  /*                                Upp. Bounds  Var. Size (T/F) */
  /* %%%%% Preallocate variables %%%%%% */
  /* Preallocate matrix to store R, G, and B means for each region */
  /* Preallocate vectors to store Y, Cb, and Cr z-scores for each region     */
  region_Z_Y_size[0] = NRegions;
  region_Z_Cb_size[0] = NRegions;
  region_Z_Cr_size[0] = NRegions;

  /* Preallocate vector to store Cr standard deviation for each region */
  region_SD_Cr_size[0] = NRegions;

  /* %%%%% Take calculations across regions %%%%%% */
  /* If called during code generation */
  /* If called during code generation, use a parallel for loop (parfor), but use a for loop otherwise. */
  /* The parallel for loop increases the performance of compiled-C code but decreases the performance  */
  /* of Matlab code. */
  /* Prevent dynamic memory allocation from colon operator by asserting length */
  ub_loop = NRegions - 1;
  emlrtEnterParallelRegion(aTLS, omp_in_parallel());
  emlrtPushJmpBuf(aTLS, &emlrtJBStack);

#pragma omp parallel for \
 num_threads(emlrtAllocRegionTLSs(aTLS, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs())) \
 private(f,f1,f2,f3,d,d1,d2)

  for (i = 0; i <= ub_loop; i++) {
    /* Loop across regions */
    /* Local function */
    Ops(i + 1, RegionIndices_data, RegionNPixels_Single_data, RBounded_Uint8,
        GBounded_Uint8, BBounded_Uint8, YBounded_Single, CbBounded_Single,
        CrBounded_Single, MeanOfMeansY, MeanOfMeansCb, MeanOfMeansCr,
        StdDevOfMeansY, StdDevOfMeansCb, StdDevOfMeansCr, &d2, &d1, &d, &f3, &f2,
        &f1, &f);
    region_M_R_data[i] = d2;
    region_M_G_data[i] = d1;
    region_M_B_data[i] = d;
    region_Z_Y_data[i] = f3;
    region_Z_Cb_data[i] = f2;
    region_Z_Cr_data[i] = f1;
    region_SD_Cr_data[i] = f;
  }

  emlrtPopJmpBuf(aTLS, &emlrtJBStack);
  emlrtExitParallelRegion(aTLS, omp_in_parallel());

  /* Not called during code generation     */
  /* %%%%% --- Concatenate R, G, and B means %%%%%%  */
  RegionRGBMeans_size[0] = NRegions;
  RegionRGBMeans_size[1] = 3;
  if (0 <= NRegions - 1) {
    memcpy(&RegionRGBMeans_data[0], &region_M_R_data[0], NRegions * sizeof
           (real_T));
  }

  for (ub_loop = 0; ub_loop < NRegions; ub_loop++) {
    RegionRGBMeans_data[ub_loop + NRegions] = region_M_G_data[ub_loop];
  }

  for (ub_loop = 0; ub_loop < NRegions; ub_loop++) {
    RegionRGBMeans_data[ub_loop + NRegions * 2] = region_M_B_data[ub_loop];
  }
}

/* End of code generation (SkinDetect_RegionMetrics.c) */
