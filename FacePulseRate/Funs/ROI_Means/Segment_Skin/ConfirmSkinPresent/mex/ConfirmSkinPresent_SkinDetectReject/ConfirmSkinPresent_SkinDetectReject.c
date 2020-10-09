/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ConfirmSkinPresent_SkinDetectReject.c
 *
 * Code generation for function 'ConfirmSkinPresent_SkinDetectReject'
 *
 */

/* Include files */
#include "ConfirmSkinPresent_SkinDetectReject.h"
#include "ConfirmSkinPresent_SkinDetectReject_data.h"
#include "ConfirmSkinPresent_SkinDetectReject_emxutil.h"
#include "bwconncomp.h"
#include "mwmathutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
int32_T ConfirmSkinPresent_SkinDetectReject(emxArray_boolean_T *IsSkinMask,
  const emxArray_uint8_T *RBounded_Uint8, const emxArray_uint8_T *GBounded_Uint8,
  const emxArray_uint8_T *BBounded_Uint8, const emxArray_real32_T
  *YBounded_Single, const emxArray_real32_T *CbBounded_Single, const
  emxArray_real32_T *CrBounded_Single, int32_T NRows_Matrix, int32_T
  NCols_Matrix, const struct0_T *SkinDetectConfig)
{
  int32_T SumPixelsPass;
  int16_T Col_ith;
  int32_T j;
  int32_T i;
  emxArray_real_T *ConnComp_RegionIndices;
  emxArray_int32_T *ConnComp_RegionLengths;
  real_T region_M_R_ith;
  real_T expl_temp[2];
  real_T region_M_G_ith;
  int32_T NRegions;
  int32_T RegionEndIndex_ith;
  int32_T RegionNPixels_int32_ith;
  int32_T RegionBeginIndex_ith;
  boolean_T PassTF;
  real32_T SumR;
  uint32_T SumR_uint32;
  real32_T SumG;
  uint32_T SumG_uint32;
  real32_T SumB;
  uint32_T SumB_uint32;
  real32_T SumCb;
  real32_T SumCr;
  int32_T SumR_tmp;
  real_T region_M_B_ith;
  (void)YBounded_Single;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);

  /* ConfirmSkinPresent_SkinDetectReject   Determine the number of pixels that pass the rejection */
  /*                                       procedure from the skin-detection algorithm. */
  /*                                                                 */
  /*     Helper function to function FacePulseRate.  */
  /*     Within function FacePulseRate, called by function ConfirmSkinPresent. */
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
  /*     Use the rejection procedure from the skin-detection algorithm (see functions */
  /*     SkinDetect_RejectRegions and SkinDetect) to refine the skin-segmentation mask (IsSkinMask).  */
  /*     Specifically, partition the mask into regions and exclude regions that do not pass all  */
  /*     rejection thresholds. Then, return the number of remaining pixels classified as skin (true). */
  /*  */
  /*     The rejection thresholds used on each region include a minimum pixel count threshold, a */
  /*     probability threshold based on the R, G, and B channels of the ROI, and z-score thresholds */
  /*     based on the Cb and Cr channels of the ROI. */
  /*  */
  /*  */
  /*     Copyright */
  /*     --------- */
  /*  */
  /*     Copyright (c) Douglas Magill (dpmdpm@vt.edu), August, 2020. Licensed under the MIT License and   */
  /*     the Responsible AI License (RAIL). */
  /* %%%%% Extract information for the rejection thresholds from the skin-detection algorithm %%%%%% */
  /* Thresholds: */
  /* Note: values assigned by function SkinDetectConfig_Setup. */
  /* RGB probability threshold */
  /* Scalar; type single. */
  /* Cb and Cr z-score thresholds */
  /* Scalars; type single. */
  /* Region pixel count threshold */
  /* Scalar; type single. */
  /* Theta values for determining RGB probability: */
  /* Note: values assigned by function function SkinDetect_RGBProbSkinTrain. */
  /* 4 x 1 column vector; type double. */
  /* Reference means and standard deviations for determining Cb and Cr z-scores for each region: */
  /* Note: values assigned by function SkinDetect_SetThresholds.  */
  /* Scalars; type single. */
  /* %%%%% Partition skin-segmentation mask into smaller regions using grid lines %%%%%% */
  /* Note: a similar procedure is conducted in function SkinDetect_PartitionRegions. */
  /* Specify the intervals to use to partition the skin-segmentation mask */
  /* Scalar; type single. */
  /* Note: values assigned by function SkinDetectConfig_Setup. */
  /* Insert vertical lines: */
  for (Col_ith = 1; Col_ith <= NCols_Matrix; Col_ith +=
       SkinDetectConfig->PartitionColInterval) {
    for (j = 0; j < NRows_Matrix; j++) {
      IsSkinMask->data[j + IsSkinMask->size[0] * (Col_ith - 1)] = false;
    }
  }

  /* Insert horizontal lines:  */
  for (i = 0; i < NCols_Matrix; i++) {
    for (Col_ith = 1; Col_ith <= NRows_Matrix; Col_ith +=
         SkinDetectConfig->PartitionRowInterval) {
      IsSkinMask->data[(Col_ith + IsSkinMask->size[0] * i) - 1] = false;
    }
  }

  emxInit_real_T(&ConnComp_RegionIndices, 1, true);
  emxInit_int32_T(&ConnComp_RegionLengths, 1, true);

  /* %%%%% Find connected regions and return pixel indices and pixel counts corresponding to each region %%%%%% */
  /* Group pixels into connected regions, using the connection criteria of 8, which is the default    */
  /* setting for function bwconncomp.      */
  bwconncomp(IsSkinMask, &region_M_R_ith, expl_temp, &region_M_G_ith,
             ConnComp_RegionIndices, ConnComp_RegionLengths);

  /* Output indicating the number of pixels in each region */
  /* M regions x 1 column vector; type double. */
  /* Output indicating number of regions */
  /* Scalar; type int32. */
  NRegions = ConnComp_RegionLengths->size[0];

  /* Prevent dynamic memory allocation from colon operator by asserting maximum value */
  /* %%%%% Determine which regions pass the thresholds and count the number of pixels of passing regions %%%%%% */
  /* If no regions present */
  if (ConnComp_RegionLengths->size[0] == 0) {
    SumPixelsPass = 0;
  } else {
    /* Initialize sum accumulator for total pixels classified as true */
    SumPixelsPass = 0;

    /* Initialize the last linear index of the ith region */
    RegionEndIndex_ith = 0;

    /* Loop across regions */
    /* Set Centroids_Struct_Length, the length of Centroids_Struct.Centroid, as the maximum  */
    /* iteration because sometimes the length of Centroids_Struct.Centroid can be less than the  */
    /* length of RegionIndices.PixelIdxList.  */
    for (i = 0; i < NRegions; i++) {
      /* The number of pixels in the ith region */
      /* Cast to type int32. */
      /* Scalar; type int32. */
      RegionNPixels_int32_ith = (int32_T)(real32_T)ConnComp_RegionLengths->
        data[i];

      /* The first linear index of the ith region */
      /* Scalar; type int32. */
      RegionBeginIndex_ith = RegionEndIndex_ith + 1;

      /* The last linear index of the ith region: */
      /* Scalar; type int32. */
      RegionEndIndex_ith += RegionNPixels_int32_ith;

      /* Determine whether the ith region passes the thresholds */
      /* Local function. */
      /* Scalar; type logical. */
      /* end main function */
      /* ============================================================================================= */
      /* Local functions */
      /* ============================================================================================= */
      /* ============================================================================================= */
      /* Ops   Take means and z-scores of the ith region.   */
      /*  */
      /*     Description: */
      /*  */
      /*     - Take the means of the R, G, and B channels of the ith region. */
      /*  */
      /*     - Take the z-scores of the Cb and Cr channels of the ith region. */
      /*  */
      /*       The z-score for a region is calculated by subtracting its mean from the reference mean and */
      /*       dividing by the reference standard deviation. The reference mean and standard deviation are */
      /*       from skin-color samples collected from ROIs of the video (see function  */
      /*       ROIMeans_FirstRead_CollectSkinColorSamples). */
      /*  */
      /*     Use integer arithmetic rather than floating-point arithmetic for efficiency if overflow will */
      /*     not occur. */
      /*  */
      /*     Note: Different implements are used for code generation and Matlab code.     */
      /* Inline function */
      /* %%%%% Determine whether ith region passed pixel-count threshold %%%%%% */
      /* Determine whether (pass/not pass) ith region has a quantity of pixels  */
      /* greater than or equal to the threshold for minimum quantity of pixels. */
      /* Variable specifying threshold (RegionNThreshold) assigned at top. */
      /* Scalar; type logical. */
      PassTF = (ConnComp_RegionLengths->data[i] >
                SkinDetectConfig->Thresholds.RegionNThreshold);

      /* %%%%% Determine whether ith region passed color thresholds %%%%%% */
      if (PassTF) {
        /* %%%%% --- Optimized by integer arithmetic %%%%%% */
        /* Use algorithm optimized by integer arithmetic if all indices less than specified length */
        if (ConnComp_RegionLengths->data[i] < 1.5686E+7F) {
          /* Accumulators for ith region */
          /* Scalars; type uint32 or single. */
          SumR_uint32 = 0U;
          SumG_uint32 = 0U;
          SumB_uint32 = 0U;
          SumCb = 0.0F;
          SumCr = 0.0F;

          /* Loop across elements, j, corresponding to ith region index      */
          for (j = RegionBeginIndex_ith; j <= RegionEndIndex_ith; j++) {
            /* RGB colorspace sums */
            /* Cast to type uint32 for efficiency. */
            /* Scalars; type uint32. */
            SumR_tmp = (int32_T)ConnComp_RegionIndices->data[j - 1] - 1;
            SumR_uint32 += RBounded_Uint8->data[SumR_tmp];
            SumG_uint32 += GBounded_Uint8->data[SumR_tmp];
            SumB_uint32 += BBounded_Uint8->data[SumR_tmp];

            /* YCbCr colorspace sums */
            /* Scalars; type single. */
            SumCb += CbBounded_Single->data[SumR_tmp];
            SumCr += CrBounded_Single->data[SumR_tmp];
          }

          /* %%%%% >>>>>> Take RGB means of ith region %%%%%%  */
          /* Take means and cast to type double for output. */
          /* Scalars; type double. */
          /* Red channel mean */
          region_M_R_ith = (real32_T)SumR_uint32 / (real32_T)
            ConnComp_RegionLengths->data[i];

          /* Green channel mean */
          region_M_G_ith = (real32_T)SumG_uint32 / (real32_T)
            ConnComp_RegionLengths->data[i];

          /* Blue channel mean */
          region_M_B_ith = (real32_T)SumB_uint32 / (real32_T)
            ConnComp_RegionLengths->data[i];

          /* %%%%% --- Not optimized by integer arithmetic %%%%%%         */
        } else {
          /* Accumulators for ith region */
          /* Scalars; type single. */
          SumR = 0.0F;
          SumG = 0.0F;
          SumB = 0.0F;
          SumCb = 0.0F;
          SumCr = 0.0F;

          /* Loop across elements, j, corresponding to ith region index      */
          for (j = RegionBeginIndex_ith; j <= RegionEndIndex_ith; j++) {
            /* RGB colorspace sums */
            /* Cast to type uint32 for efficiency. */
            /* Scalars; type single. */
            SumR_tmp = (int32_T)ConnComp_RegionIndices->data[j - 1] - 1;
            SumR += (real32_T)RBounded_Uint8->data[SumR_tmp];
            SumG += (real32_T)GBounded_Uint8->data[SumR_tmp];
            SumB += (real32_T)BBounded_Uint8->data[SumR_tmp];

            /* YCbCr colorspace sums */
            /* Scalars; type single. */
            SumCb += CbBounded_Single->data[SumR_tmp];
            SumCr += CrBounded_Single->data[SumR_tmp];
          }

          /* %%%%% >>>>>> Take RGB means of ith region %%%%%%  */
          /* Take means and cast to type double for output. */
          /* Scalars; type double. */
          /* Red channel mean */
          region_M_R_ith = SumR / (real32_T)ConnComp_RegionLengths->data[i];

          /* Green channel mean */
          region_M_G_ith = SumG / (real32_T)ConnComp_RegionLengths->data[i];

          /* Blue channel mean */
          region_M_B_ith = SumB / (real32_T)ConnComp_RegionLengths->data[i];
        }

        /* %%%%% --- Take Cb and Cr z-scores of the ith region %%%%%%     */
        /* Scalars; type single. */
        /* ith region z-scores:    */
        /* Cb channel z-score */
        /* Cr channel z-score */
        /* %%%%% --- Calculate RGB probabilities and determine whether threshold passed %%%%%% */
        /* Concatenate the R, G, and B means */
        /* 1 x 3 row vector; type double. */
        /* Return probabilities for ith region that ROI RGB means are skin. */
        /* To do so, use function SkinDetect_RGBProbSkin. This function is also supplied with theta  */
        /* parameters, which were calculated from color means across ROIs from the primary face-detection  */
        /* algorithm and from colors means from external sources. The theta parameters were returned by  */
        /* function SkinDetect_RGBProbSkinTrain, which was called by function SkinDetect_SetThresholds,  */
        /* which was called by function ROIMeans_FirstRead_SetThresholds.  */
        /* Scalar; type double. */
        /* Note: 'SkinDetect_RGBProbSkin' is a custom function located within folder 'FacePulseRate'.   */
        /* SkinDetect_RGBProbSkin   Estimates probability that mean RGB of an ROI is skin. */
        /*     */
        /*     Helper function to function FacePulseRate. */
        /*     Within function FacePulseRate, called by function SkinDetect_RejectRegions. */
        /*  */
        /*     Code generation: Can be called as a Matlab function or used for C-language code generation. */
        /*  */
        /*     Note: The theta parameters used by the function are supplied by function */
        /*     SkinDetect_RGBProbSkinTrain. */
        /*  */
        /*     Input */
        /*  */
        /*         RGB_mean   = N-by-3 matrix of skin sample RGB means. Each row corresponds to a skin sample  */
        /*                      and the columns correspond to means of R, G, and B, respectively.                    */
        /*         theta      = Probability criteria. */
        /*  */
        /*     Output */
        /*  */
        /*         prob_skin  = The probability(ies) that the means of R, G and B represent skin, based upon */
        /*                      theta, which was produced by training with a sample of skin and non-skin  */
        /*                      means.  */
        /*                       */
        /*     Note: this function is compatible with code generation. This compatability was used for  */
        /*     testing purposes, but a compiled funtion is not used in FacePulseRate toolbox as it was not */
        /*     observed to provide a performance benefit. */
        /*  */
        /*     This function is adapted from the Skin Segmentation toolbox, which was obtained from Madhav */
        /*     Rajan (2014). See discussion on Github (https://github.com/madhrajan91/Skin-Segmentation).  */
        /*     For usage notes in toolbox FacePulseRate, see function SkinDetect_RGBProbSkinTrain.      */
        /* Inline function */
        /* Add column to right equal to 1 */
        /* Calculate probability that means of R, G, and B do not represent skin */
        /* SIGMOID   Compute sigmoid function. */
        /*  */
        /*    Helper function to function FacePulseRate. */
        /*    Within function FacePulseRate, called by functions SkinDetect_RGBProbSkinTrain and */
        /*    SkinDetect_RGBProbSkin. */
        /*  */
        /*    Code generation: Can be called as a Matlab function or used for C-language code generation. */
        /*  */
        /*    Description: */
        /*  */
        /*    J = SIGMOID(z) computes the sigmoid/ Logistic function of z. */
        /*  */
        /*    Adapted from the Skin Segmentation toolbox, which was obtained from Madhav */
        /*    Rajan (2014). See discussion on Github (https://github.com/madhrajan91/Skin-Segmentation). */
        /* Inline function */
        /* end function */
        /* Convert to probabilty of skin */
        /* end function */
        /* Determine whether (pass/not pass) the region is above the RGB probability threshold. */
        /* This threshold is specified as an argument (SkinClassifyRegionColorThresholds(1)) to function */
        /* FacePulseRate. */
        /* Scalar; type logical. */
        PassTF = (1.0 - 1.0 / (muDoubleScalarExp
                   (-(((SkinDetectConfig->Thresholds.RGBProbTheta[0] +
                        region_M_R_ith *
                        SkinDetectConfig->Thresholds.RGBProbTheta[1]) +
                       region_M_G_ith *
                       SkinDetectConfig->Thresholds.RGBProbTheta[2]) +
                      region_M_B_ith * SkinDetectConfig->
                      Thresholds.RGBProbTheta[3])) + 1.0) >=
                  SkinDetectConfig->Thresholds.ColorThreshold[0]);

        /* %%%%% --- Determine whether passes YCbCr z-score thresholds %%%%%% */
        /* If the ith region passed the RGB probability thresholds */
        if (PassTF) {
          /* See notes in function SkinDetect. */
          /* Skin-detection candidates are rejected if outside thresholds, which are determined by the */
          /* mean +/- a specified standard deviation.  */
          /* Determine whether (pass/not pass) the region is within the Cb and Cr thresholds  */
          /* These thresholds are specified as an argument (SkinClassifyRegionColorThresholds(2 : 3))  */
          /* to function FacePulseRate.  */
          /* Scalar; type logical. */
          /*  compare against Cb z-score threshold */
          if ((!(muSingleScalarAbs((SumCb / (real32_T)
                  ConnComp_RegionLengths->data[i] -
                  SkinDetectConfig->Thresholds.YCbCrMeanOfMeans[1]) /
                 SkinDetectConfig->Thresholds.YCbCrStdDevOfMeans[1]) <=
                 SkinDetectConfig->Thresholds.ColorThreshold[1])) ||
              (!(muSingleScalarAbs((SumCr / (real32_T)
                  ConnComp_RegionLengths->data[i] -
                  SkinDetectConfig->Thresholds.YCbCrMeanOfMeans[2]) /
                 SkinDetectConfig->Thresholds.YCbCrStdDevOfMeans[2]) <=
                 SkinDetectConfig->Thresholds.ColorThreshold[2]))) {
            PassTF = false;
          }

          /*    compare against Cr z-score threshold */
        }
      }

      /* end local function */
      /* ============================================================================================= */
      /* Code-generation and build script */
      /* ============================================================================================= */
      /* Code-generation and build script used to generate C-language code and create the compiled version  */
      /* (ConfirmSkinPresent_SkinDetectReject_mex) of the function. */
      /* { */
      /*  */
      /* %%%%% Specify variable-size input arguments %%%%%% */
      /*  */
      /* Input Argument                      Example Code                 Upp. Bounds     Var. Size (T/F)  Type */
      /* IsSkinMaskCode       = coder.typeof( zeros(500, 500, 'logical'),  [inf, inf],     [1, 1] );        %logical */
      /* RBounded_Uint8Code   = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8 */
      /* GBounded_Uint8Code   = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8 */
      /* BBounded_Uint8Code   = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8 */
      /* YBounded_SingleCode  = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single */
      /* CbBounded_SingleCode = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single */
      /* CrBounded_SingleCode = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single */
      /*                  */
      /*  */
      /* %%%%% Specify fixed-size input arguments %%%%%% */
      /*  */
      /* NRows_MatrixCode = int32(0); */
      /* NCols_MatrixCode = int32(0); */
      /*  */
      /* SkinDetectConfigCode = ...  */
      /*     struct( ... */
      /*         'ROISkinTF', false, ... */
      /*         'Thresholds', ... */
      /*         struct( ...    */
      /*             'SetTF', false, ... */
      /*             'SkinColorSamples_NThreshold', double(0), ... */
      /*             'SkinColorSamples_NThresholdPassedTF', false, ... */
      /*             'SkinColorSamples_HighNThreshold', double(0), ...  */
      /*             'SkinColorSamples_HighNThresholdPassedTF', false, ... */
      /*             'SkinColorSamples_HighNThresholdIdx', int32(0), ...  */
      /*             'ColorThreshold', zeros(1, 3, 'single'), ... */
      /*             'ColorThresholdHighN', zeros(1, 3, 'single'), ... */
      /*             'RecentThresholdOpsFrameIdx', int32(0), ... */
      /*             'ThresholdOpsInterval', int32(0), ... */
      /*             'ThresholdOpsRunCurrentFrameTF', false, ... */
      /*             'ColorSDThreshold', single(0), ... */
      /*             'RGBProbTheta', zeros(4, 1, 'double'), ... */
      /*             'YCbCrMeanOfMeans', zeros(1, 3, 'single'), ... */
      /*             'YCbCrStdDevOfMeans', zeros(1, 3, 'single'), ... */
      /*             'RegionNThreshold', single(0) ... */
      /*         ), ... */
      /*         'ROISkinSkipFrameThreshold', int32(0), ... */
      /*         'ROISkin_BoundingBoxGrowthThreshold', int32(0), ... */
      /*         'ROISkin_BoundingBoxGrowthFactor', double(0), ... */
      /*         'ROISkin_InitialBoundingBoxScale', double(0), ... */
      /*         'ROISkinRegionMinSizeFactor', single(0), ... */
      /*         'ROISkinRegionProximityWeight', double(0), ... */
      /*         'ROISkinSmoothingWindow', double(0), ... */
      /*         'PartitionColInterval', int16(0), ... */
      /*         'PartitionRowInterval', int16(0), ... */
      /*         'SkinDetectionReadyTF', false, ... */
      /*         'ROISkin_BoundingBoxEnlargementFactor', double(0), ... */
      /*         'ROISkinSkipFrameThreshold_adjusted', int32(0), ... */
      /*         'UseCompiledFunctionsTF', false ... */
      /*     );                                                          */
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
      /* codegen ConfirmSkinPresent_SkinDetectReject.m -report -config cfg -args {IsSkinMaskCode, RBounded_Uint8Code, GBounded_Uint8Code, BBounded_Uint8Code, YBounded_SingleCode, CbBounded_SingleCode, CrBounded_SingleCode, NRows_MatrixCode, NCols_MatrixCode, SkinDetectConfigCode} */
      /*  */
      /* } */
      /* If the ith region passed the thresholds */
      if (PassTF) {
        /* Sum of pixels across all regions that passed thresholds */
        /* Scalar; type int32. */
        SumPixelsPass += RegionNPixels_int32_ith;
      }
    }
  }

  emxFree_int32_T(&ConnComp_RegionLengths);
  emxFree_real_T(&ConnComp_RegionIndices);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  return SumPixelsPass;
}

/* End of code generation (ConfirmSkinPresent_SkinDetectReject.c) */
