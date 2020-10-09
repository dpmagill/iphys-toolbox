/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_Interp_info.c
 *
 * Code generation for function '_coder_Interp_info'
 *
 */

/* Include files */
#include "_coder_Interp_info.h"
#include "emlrt.h"
#include "rt_nonfinite.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void);

/* Function Definitions */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  const char * data[17] = {
    "789ced5dcb8fdb4418f7d28710521f548078089a0287a24aebcd3ed2aa1748b2796f924db2af76a9b28e3d4966d7afb59dc4d90b7b421c2a2171e10fe000e580"
    "7a0409a43d00a237a05089331570417045e2801d7b76bdd9b8cec6596f63e653b7c9e44be6f77dbfb17f339e1927c4582a3b4610c459c2b0ef15e3f18cf6f7c1",
    "130471de7cfd0962bf75fbc7ccc7672ce57fded97bff29e264a77cc6e2d73fffbe59a6055e01aa09ce531cd8fd24237090a77865a12d024202b2c03601d3f154"
    "210b1620074ad6424e2f71718b6bb7a0bbf4e7d13aa0374a0d8e90eaf25e84acb5b0cbc7f3637bf9eaf1a37c4ff6e0c3ea477c7c6ec3c779b38cfcabb15b89eb",
    "64b61d9895601390614981340b6452114448cba4586fcb50d87d3910ad53a2022499cc024a6e68ac90e18622f01a557420570a5c4e948a8164f10d3259d4fe05"
    "5aa042531c99a5671bd56a2001957aa3a263b50469838c5334986fb03228520a2093801581548e3778992ce65365ad7eed5902f040a258fd655a8182f64a4a6b",
    "2e491ce7ce9aedb86dc343bf3cbde2c013f2038e2d435e295705891504b12c34815465855699d61bd568373d9eb501e3e936bb789021bc1d97f9af59cabdf090"
    "7f3535b712bb15bd4ece4b424da2b8807e406b874178612e1c218b931393139476d0086c4550498d2c92851592a31496aa748a8fe66faf3dedf83bd7673ed647",
    "6b3e6788273be54fa77e1cb3f277d478dbab5f97bcc443765c78aa4d7dfd1e8fcfd9e0a1e311f9e54c4c8dcd6e6dcda7d5c9e9ece444b4100e4ec4f6e29877c0"
    "718a83b0947be579d4f5ff61f3f97e797cd7a67ec423f21ff5797de9d16f28d73bbaef5e3fc7bade77306f631c00e52ab4f2ec16ef942dde29038f57a6262d78",
    "9fb8c48bdbe21965e41fa85dab50058c286831933a4fe39c773af2e1473f79abcbecd9eb5ee221f3bb2e07c5859b499e9ecea9fc7a333e918b490935e1235d1e"
    "d5f3577419b7f5faa957dcc80f65bec10109d28a7ed9e49daed3754a222c78775de2e51df2457ef7ed64e14b6b30bfea2d71ff8baca778a6f95d6f333319713e",
    "98dc60ea35b099a45a570b0a371df78fdee271f060799fb6cdfb341a9772943abafa9cb6c533cac8efaa5d59ed096930a5f7a5d6f8edf81a969efcf5b3c7e3e1"
    "c20f1f7b8987cceffa3c1d0fa5da55a19d4d2c055b7515f29cc0657d341ec6fa7c74fa0c79accffde933e4b13e0f170f99dff5b9343fb9ce4562ed04132d50cb",
    "20ab2cade71713fed1e7cb63bd3fdf2f8fdfd8d48f7844fe515d47bc1453158912e7200f3a0238ac75c5971d78437e5a6080340ef568788a1d9718d8840cd8ed"
    "6e8e6d5d11ad0f0f9aff92031ef21f5afff5bf2b1dd6c82b8836723f6d5ece5b0bbf793c8fd2feec9ea778a68d6a3ff0ac0d1e3a0e917f255d53634bd1b9ab54",
    "7d239d5bce05d978f406e19f7ec02fe7f3b6cb3c2e3ae481fc5dba0ce54803b24a8acf19b3b59e5d07c890afb1602fffef5ce2d51cf247fe43b5a3ac5d3c0086"
    "345ad1f85f1fa61f68d66e163d9cef1ebfe3f178fda917bff4120fd9a8ea74bfe3f5ad091166e4189d9f9d87f1faccc2b5706526efa3f914acd386051cf240fe",
    "2e9d96698a05aa1815389152608505c7a5d33b2ef16e38e48ffcc369c703b4a1e914eff4f9578ff5f9cdc54d2ff190f95d9fb95aaa105b2f6e86a66642cb5c68"
    "732ac56fc9589f1f3b7d767b3c5c70c803f9bbf4598b673f9f6b2ee338ac2ebb9dd7ce38e48dfcc3693f8d2e53897dabc3175e17bdc443e6771daedf0cd2f148",
    "2dbf70edda46321292272391540dcf6be3796d1b5ef0fd32fde5bf6629f7c2437e7cbfcc80fd01be5fa663f87e99c3d53fe1b23fb867533fe211f947b63f58a2"
    "58c840a5ddb909b5bc9cece26fcd869f7ef93b61cbdf894e99aac843c53becb8dfedbefd842d9e51467e77fb59aa0d9ed498f2725edce3f13ef1e04f3cef420c",
    "7ffd722316a94554e1e69c18a21395a09449e72359c23ffa3eaae7efb6cbb82f3ac48dfc78bd12af57bac1c3eb9586e1f5cac3d5ff7fd5e5171ce246fe1eeb93"
    "94348e46c3a3bbbfafe48087fcc39907bf62f066b6613fbc0d4b371e3ef4787c7c17def614cf34bfeb70a656520ba96273aa100325362e654a2bcdd928d6e1e3",
    "d6e1f75cc6fdaa43dcc8dfa5c39428b2ed524754d05cc97e3e4597719db3947bc585fc5513bd5ca778461b380f6b9e7ad5011ff987a3cf3de8c4eb9643c543e6"
    "779d5e6f25eacb6139b9c5b4c485629aa6ae96164311ffe8f48ecde747f5bc76abdfaf39e483fcddfadd1420139624aa1d672945013ce46bfbe25a1b30ae6eeb",
    "773cbde39287b71df0907f48edda833ea361bdd297db4fdff7765cbdfdfbbf9ee299e677bdde4a27a7a28be20a57a8e499f04a359955b97c12ebf5e3aad7db2e"
    "f3795ce63d069d8fc6f31e071ff1bc877ff5d9eff31e6ef7017e6b533fe211f94776df87b10f3007282d0805ef03c4fb0007d32fbc0ff068f1f03ec0e1d48ff7",
    "853bf407c613fc7d27a6f9edbe2e3bdef0f79df48967daa8f603f8fb4e703f709cfd00be2e78341ef2e3eb027c5d80af0bbcab1fff9e9a37bfa7f692034fc8af"
    "c51466d61bb292aac6541a00468e6b2a08662137dcfb84faf87d9e60c882f796cbe3e41787fc917fd48e13a3b1cada5b3aefb36b3bcfbf37e62be581a7fdcfdf",
    "77364f788987cceffd4f3dda94687eba5053e2a5cd15ba35bb94a62a3ee87ffe0358845028",
    "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 29928U, &nameCaptureInfo);
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
  xInputs = emlrtCreateLogicalMatrix(1, 10);
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString("Interp"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", emlrtMxCreateDoubleScalar
                (10.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (1.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath", emlrtMxCreateString(
    "G:\\My Drive\\Articles\\topics\\physio\\Articles Chapters\\Measures\\Autonomic NS (GSR HR)\\HR\\HR webcam\\McDuff Github\\My work\\FacePulse"
    "Rate\\Helper_Funs\\ROI_Means\\General_Functions\\Interp.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp", emlrtMxCreateDoubleScalar
                (738023.53126157413));
  xResult = emlrtCreateStructMatrix(1, 1, 4, propFieldName);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.8.0.1417392 (R2020a) Update 4"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/* End of code generation (_coder_Interp_info.c) */
