/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * insertTextFast_Font14LT_data.c
 *
 * Code generation for function 'insertTextFast_Font14LT_data'
 *
 */

/* Include files */
#include "insertTextFast_Font14LT_data.h"
#include "insertTextFast_Font14LT.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131594U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "insertTextFast_Font14LT",           /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

const uint16_T uv[256] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 3U,
  4U, 5U, 6U, 7U, 8U, 9U, 10U, 11U, 12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U, 20U,
  21U, 22U, 23U, 24U, 25U, 26U, 27U, 28U, 29U, 30U, 31U, 32U, 33U, 34U, 35U, 36U,
  37U, 38U, 39U, 40U, 41U, 42U, 43U, 44U, 45U, 46U, 47U, 48U, 49U, 50U, 51U, 52U,
  53U, 54U, 55U, 56U, 57U, 58U, 59U, 60U, 61U, 62U, 63U, 64U, 65U, 66U, 67U, 68U,
  69U, 70U, 71U, 72U, 73U, 74U, 75U, 76U, 77U, 78U, 79U, 80U, 81U, 82U, 83U, 84U,
  85U, 86U, 87U, 88U, 89U, 90U, 91U, 92U, 93U, 94U, 95U, 96U, 97U, 0U, 0U, 0U,
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 172U, 163U, 132U, 133U, 189U, 150U,
  232U, 134U, 142U, 139U, 157U, 169U, 164U, 258U, 138U, 259U, 131U, 147U, 242U,
  243U, 141U, 151U, 136U, 260U, 222U, 241U, 158U, 170U, 245U, 244U, 246U, 162U,
  173U, 201U, 199U, 174U, 98U, 99U, 144U, 100U, 203U, 101U, 200U, 202U, 207U,
  204U, 205U, 206U, 233U, 102U, 211U, 208U, 209U, 175U, 103U, 240U, 145U, 214U,
  212U, 213U, 104U, 235U, 237U, 137U, 106U, 105U, 107U, 109U, 108U, 110U, 160U,
  111U, 113U, 112U, 114U, 115U, 117U, 116U, 118U, 119U, 234U, 120U, 122U, 121U,
  123U, 125U, 124U, 184U, 161U, 127U, 126U, 128U, 129U, 236U, 238U, 186U };

const int8_T iv[261] = { 11, 0, 0, 4, 4, 5, 9, 9, 9, 10, 3, 5, 5, 7, 11, 4, 8, 4,
  7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4, 4, 11, 11, 11, 6, 12, 10, 8, 10, 10, 8, 8,
  10, 10, 4, 4, 9, 7, 12, 10, 11, 8, 11, 9, 8, 9, 10, 9, 12, 9, 9, 8, 5, 7, 5, 9,
  7, 9, 8, 9, 7, 9, 8, 5, 9, 9, 4, 4, 8, 4, 13, 9, 9, 9, 9, 6, 7, 5, 9, 7, 11, 9,
  7, 8, 5, 5, 5, 9, 10, 10, 10, 8, 10, 11, 10, 8, 8, 8, 8, 8, 8, 7, 8, 8, 8, 8,
  4, 4, 4, 4, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 6, 9, 9, 9, 0, 9, 8, 9, 12, 0, 9,
  9, 0, 13, 11, 0, 11, 0, 0, 9, 9, 0, 0, 0, 0, 0, 7, 7, 0, 12, 9, 6, 4, 11, 0, 0,
  0, 0, 7, 7, 0, 4, 10, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 7, 0, 0, 9, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 10, 8, 10, 8, 8, 4, 4, 4, 4, 11, 11, 0, 11, 10, 10, 10, 0,
  0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 10, 8, 9, 7, 8, 9, 0, 11, 6,
  6, 6, 11, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 7, 4 };

/* End of code generation (insertTextFast_Font14LT_data.c) */
