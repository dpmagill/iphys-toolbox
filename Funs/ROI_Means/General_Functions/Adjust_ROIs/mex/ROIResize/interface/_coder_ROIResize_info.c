/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ROIResize_info.c
 *
 * Code generation for function '_coder_ROIResize_info'
 *
 */

/* Include files */
#include "_coder_ROIResize_info.h"
#include "emlrt.h"
#include "rt_nonfinite.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void);

/* Function Definitions */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  const char * data[12] = {
    "789ced5bcb6fe3441c766017a19596ed89037b2070da55a54ebab4d96e3940de49b779e0a4d93eb46ac7cea41e3a7ec463b7492ff48456e200ffc6de38a21548"
    "5c1008ed09108233e28e3871033bce244eb6c6ed3a785b939f9a38e3cff1f77bd8df8ca7132e562ac7388e7b8d732cb1ea6caf5baf27163037d8ff12376e9378",
    "6cb0bde66a3f898d8ebfca5d197ecf8d7f3a688baa62a0aee1341428a3e1375baa8c15a8188d9e86381d51951ca2561f6963821a58467577a362b7e4bc0b1a36"
    "6cc8fe9c9190785037654e97e8c843e26e0cf3712b368af7ef8f46f15e39251f6e9c85feadab6de3cce626f09ddcc3c22a28f7e2591d1f2290d20d2c124481a1",
    "6a58a440937a14abc3ddf18c043503e9149411a4a6951590320d55b15225c62bf5f8ad429d8f17f9dba0c85b7ff1232488500665316bb6dbf102362453b0b98e"
    "54fd00e4a1886a26a188870602454434a4efe64d8502be5adab5ce6f7d2a2005e990d8bb4503abd69e54eb43931abbd621fde37844f1315a90fb79b3ebbae791",
    "97b3e6ed55cfbc3988800d2ae1b6312dbeab9e7c0e82156331c971c3f83e0fc8b7e6c9378eef94d637730f33aba0a6abfb3a94e3f6056c953dd5584fa5017f27"
    "712701ad8b442582da054826806001c8d0205000aa4601cb93559abef9e5ebc619fd776fddfe5fb7ea63b773effe100b938f238fbe09956f602f8aafeb71beb3",
    "5e7faf7bf0cd4de0f797cc7a7e7b7d93d77a0fa4a3e575b5c2afb4b3233f6a3e3c7e7e70aef66971fed7e7bfecf7f14940ff6ffaf8cf70516d217dc15241a42b"
    "902c501112d4d55284a8e2983f7b01fd39af0e7f1190afe1133fc3cf5d3ffb35dfcf1a98676903eeb439950c4b3f167efb29543d3e796fa313261fb3a8ebf1d6",
    "5ad7d82c6733345de965bab0796fe9582917a3a3c751b99f1f058ce36d9f3818fe2fba5c51fb0f3ae3f9dd0be8d779f5f9eb807c3b3e7960f8f4eb3948dfa0c3"
    "9de9f474f898455da7a57a37d1dcb8db78872c1696452d51abd68d6661a6d3ecfc1b1ee79f9bc0a7376e7e0b1262dfe8fb48e7c2d3c33651d569f2bde2c9e720",
    "2dd514089adef34dc9936f1c0f522744daa602fa99628f37d1d55bf2b11e261fb3a8ebed7179f130238a52816ca0664e4e2cd5925a32427a7bd9efe39380febf"
    "e9e33fc327c6c398a64d4c8c92523165a463f185e9f07701f9f67de267f8b9ea4725a8a3167046c1cebb5dce6786c593593cc33cffd4f4f971c8fa7ced8d2fc3",
    "e46316797d4e68f83ecd89d56c0de7a5e5c64a4a58aee666fa1c157d0e308f0cf505364a0e3e4e9e342f7f985df8e79953e729e69dbcb96a19d9f1f2ef7f2a61"
    "f2318bba1e37ab9daca9a7d7b32925d9d95a4187996abb979ee9f145d1e3cf02fa7fdbc77f864fe831d434d2abf7c585adf52829350245b61e87f9a705f4ef86",
    "ab7d9a7f0c6f0fbcd895a0d2b206d4d31a4f0b3efc0c9f8e5e7ba735ec75199ffc18ae7e7366f1af50f9061675fd4e1e2c1f3ca86fb614816cdf5b53e9f6562d"
    "8d2334dff17fbbbfa7b52e0e53aa419da2cb3adf5cf1e41bc783f4bb7686ec9e97e5caae51587af1f4fb90f5173dfd2554be81455d7f3b1995af258504bf522c",
    "f3ad84d4bc6b924684d6c545557f4f02c67551e6399e579f67f31ccf6e67f31cd1d5e9a8cf73cc7e9ff27cbf4f39f1c8cbb4fb018bdb71a5d4ce7545845a346f"
    "a921ca62998ed5712fa03fe75d97f77ec0ebe6579ff8197ec9af1bafda85be4ee52be3e750fba33f1e775e0e938f59d4fb232973a88bcad207fb46beded9148f",
    "b2cd352844e0ffa0ff007108b9b3", "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 14920U, &nameCaptureInfo);
  return nameCaptureInfo;
}

mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xResult;
  mxArray *xEntryPoints;
  const char * epFieldName[6] = { "Name", "NumberOfInputs", "NumberOfOutputs",
    "ConstantInputs", "FullPath", "TimeStamp" };

  mxArray *xInputs;
  const char * propFieldName[4] = { "Version", "ResolvedFunctions",
    "EntryPoints", "CoverageInfo" };

  xEntryPoints = emlrtCreateStructMatrix(1, 1, 6, epFieldName);
  xInputs = emlrtCreateLogicalMatrix(1, 6);
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString("ROIResize"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", emlrtMxCreateDoubleScalar(6.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (1.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath", emlrtMxCreateString(
    "G:\\My Drive\\Articles\\topics\\physio\\Articles Chapters\\Measures\\Autonomic NS (GSR HR)\\HR\\HR webcam\\McDuff Github\\My work\\FacePulse"
    "Rate\\Helper_Funs\\ROI_Means\\General_Functions\\Adjust_ROIs\\ROIResize.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp", emlrtMxCreateDoubleScalar
                (738041.75824074075));
  xResult = emlrtCreateStructMatrix(1, 1, 4, propFieldName);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.8.0.1451342 (R2020a) Update 5"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/* End of code generation (_coder_ROIResize_info.c) */
