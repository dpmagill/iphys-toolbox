function [ithPrimaryROIRGBMeans, ithPrimaryROIYCbCrMeans, ithPrimaryROIYCbCrHSMinsMaxs] = ...          
             ROIMeans_FirstRead_CollectSkinColorSamples(YSingle, CbSingle, CrSingle, RUint8, ...
                 GUint8, BUint8, HSingle, SSingle, IsSkinMask_LocalRange, NRows_Matrix, ...
                 NCols_Matrix, SkinSegmentConfig_Args, UseCompiledFunctionsTF) %#codegen                                                             
%ROIMeans_FirstRead_CollectSkinColorSamples   Collect skin-color samples from the ROI of the ith    
%                                             frame for later use in setting thresholds for   
%                                             tailored skin segmentation and the skin-detection 
%                                             algorithm.
%  
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function ROIMeans_FirstRead.
%
%
%    Code Generation
%    ---------------
%
%    Can be called as a Matlab function or used for C-language code generation.
%
%
%    Description
%    -----------
%
%    Collect skin-colors samples from the ROI of the ith frame for later use setting thresholds for  
%    tailored skin segmentation and the skin-detection algorithm (see function 
%    ROIMeans_FirstRead_SetThresholds). The skin-color samples consist of minimums, maximums, and 
%    means from the RGB, YCbCr, and HSV colorspaces. This function is called repeatedly to collect
%    samples across many frames.
%
%    The minimums and maximums are taken from the RGB, YCbCr, and HSV colorspaces. These samples 
%    are used as input to set thresholds for tailored skin segmentation (see function 
%    SkinSegment_SetThresholds).
%
%    The following minimums and maximums are returned:
%    [RegionMaxN_YMin,          RegionMaxN_YMax,  ...
%     RegionMaxN_CbMin,         RegionMaxN_CbMax, ...
%     RegionMaxN_CrMin,         RegionMaxN_CrMax, ...
%     RegionMaxN_CbCrRatioMin,  RegionMaxN_CbCrRatioMax ...
%     RegionMaxN_HMax,          RegionMaxN_SMin, ...
%     RegionMaxN_SMax]; 
%                                
%    The means are taken from the RGB and YCbCr colorspaces. These samples are used as input to set 
%    thresholds for the skin-detection algorithm (see function SkinDetect_SetThresholds).    
%
%    Skin-color samples are only collected from the primary face-detection algorithm as the primary   
%    algorithm is assumed to contain the least false positives. Also, the ROI of the primary 
%    algorithm is expected to be comprised almost entirely of pixels corresponding to skin because    
%    it is assumed that the Viola-Jones face detector specified will detect the face in a frontal  
%    orientation (the default Viola-Jones face detector for the primary algorithm detects frontal 
%    orientations, but this can be changed by specifying argument ROIFacePrimaryXML to function   
%    FacePulseRate). If the specified secondary face-detection algorithms detect profile    
%    orientations (the default secondary #1 algorithm detects profile orientations, but this can be   
%    changed by specifying argument ROIFaceSecondary1XML to function FacePulseRate), pixels that do  
%    not correspond to skin may be incorrectly collected.
%     
%    Before taking metrics from the ROIs, several steps are taken to exclude non-skin pixels:
%    (1) The size of the ROI, as well as the corresponding color channels, is reduced. 
%    (2) A skin-segmentation mask is used to filter out pixels classified as non-skin.         
%    (3) The skin-segmentation mask is analyzed for connected regions, and only pixels from the 
%        region with the most connections are used. Using the region with the most connections is 
%        based on the assumption that skin tends to occur in large, contiguous regions rather than  
%        small regions.                                                                                        
%
%
%    License
%    -------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Reduce size of ROI and color channels %%%%%% 

%Reduce size of ROI by 2/3 to reduce likelihood of non-skin pixels in ROI.
%Also reduce corresponding color channel sizes.

%Reduce the size of the ROI values:

%Reduce the height (number of rows) and width (number of columns)
NRows_Matrix_Reduced = NRows_Matrix * int32(2) / int32(3);
NCols_Matrix_Reduced = NCols_Matrix * int32(2) / int32(3);

%Calculate new X- and Y-coordinates based upon reduced size
X_Matrix_Reduced = (NCols_Matrix - NCols_Matrix_Reduced) / int32(2);
Y_Matrix_Reduced = (NRows_Matrix - NRows_Matrix_Reduced) / int32(2);

%Reduce the size of the IsSkinMask_LocalRange channels
%All matrices except IsSkinMask_LocalRange are cropped within function SkinSegmentMask. Hence, crop
%IsSkinMask_LocalRange before entered as argument to SkinSegmentMask.
%Local function.
IsSkinMask_LocalRange_Reduced = ...
    CropMatrix(IsSkinMask_LocalRange, NRows_Matrix, NRows_Matrix_Reduced, ...
        NCols_Matrix_Reduced, X_Matrix_Reduced, Y_Matrix_Reduced);


%%%%%% Conduct skin segmentation %%%%%% 

%Arguments to function SkinSegmentMask, which returns the skin-segmentation mask:

%Flag whether to use tailored thresholds during segmentation
%Tailored thresholds include the tailored-YCbCr thresholds and the tailored-HS tresholds.
%Do not use tailored tresholds here in order to permit color values in ranges outside of tailored
%thresholds. As the skin-segmentation mask returned here is used reset the tailored thresholds, a 
%greater range permits the new thresholds to change alongside environmental changes.
TailoredThresholdsTF = false;

%Do not return the Y channel of the YCbCr colorspace
ReturnYTF = false;

%Do not return the Cb and Cr channels of the YCbCr colorspace
ReturnCbCrTF = false;

%Do not return the H and S channels of the HSV colorspace
ReturnHSTF = false;  

%Whether to return a count of pixels classified as skin. 
CountTrueTF = false;

%Use severe tailored thresholds
TailoredThresholdsSevereTF = false;          

%MorphCloseSevereTF is set as true to rule out false positives, although at the expense of false  
%negatives.
MorphCloseSevereTF = true; 

%Note: SkinSegmentMask is a custom function located within folder FacePulseRate. 
IsSkinMask = ... logical matrix where pixels classified as skin = true
    SkinSegmentMask( ...
        RUint8,                                  ... Bounded frame in RGB colorspace 
                                                 ... separated by channel; type uint8.
        GUint8, ...
        BUint8, ... 
        YSingle,                                 ... Bounded frame in YCbCr colorspace, 
                                                 ... separated by channel; type single.
        CbSingle, ...
        CrSingle, ...
        HSingle,                                 ... Bounded frame in H and S channels of 
                                                 ... HSV colorspace; type single.
        SSingle, ...
        IsSkinMask_LocalRange_Reduced,           ... Skin-segmentation mask based upon 
                                                 ... local range threshold; type logical.                
        NRows_Matrix_Reduced,                    ... Number of rows of an input matrix. If 
                                                 ... Y_Matrix_Reduced non-empty, then this value
                                                 ... indicates the number of rows to index into,
                                                 ... which can be different from the height of the
                                                 ... input matrices. Note that this indexing is 
                                                 ... not applied to input IsSkinMask_LocalRange;
                                                 ... IsSkinMask_LocalRange should be cropped to 
                                                 ... the height of NRowss_Matrix_Reduced before
                                                 ... entered as an argument.
        NCols_Matrix_Reduced,                    ... Number of columns of an input matrix. If 
                                                 ... X_Matrix_Reduced non-empty, then this value
                                                 ... indicates the number of columns to index into,
                                                 ... which can be different from the width of the
                                                 ... input matrices. Note that this indexing is 
                                                 ... not applied to input IsSkinMask_LocalRange;
                                                 ... IsSkinMask_LocalRange should be cropped to 
                                                 ... the width of NCols_Matrix_Reduced before
                                                 ... entered as an argument.
        CountTrueTF,                             ... Whether to return a count of pixels 
                                                 ... classified as skin.
        TailoredThresholdsTF,                    ... Whether to use thresholds that are 
                                                 ... tailored.
        ReturnYTF,                               ... Whether to return Y channel of the 
                                                 ... YCbCr colorspace.
        ReturnCbCrTF,                            ... Whether to return Cb and Cr channels 
                                                 ... of the YCbCr colorspace.
        ReturnHSTF,                              ... Whether to return the H and S channels 
                                                 ... of the HSV colorspace (HSingle).                                                  
        TailoredThresholdsSevereTF,              ... Whether to use severe tailored 
                                                 ... thresholds.                    
        MorphCloseSevereTF,                      ... Whether the morphological close operation will  
                                                 ... be conducted with a high level of severity.
        X_Matrix_Reduced,                        ... Optional X-coordinate offset applied to input
                                                 ... matrices. However, does not apply to input 
                                                 ... IsSkinMask_LocalRange. Use 0 x 1 value to  
                                                 ... ignore. If used, adjust NCols_Matrix 
                                                 ... accordingly. NCols_Matrix can be set to an 
                                                 ... arbitrary value when XOffset is non-empty. 
                                                 ... Scalar; type int32.
        Y_Matrix_Reduced,                        ... Optional Y-coordinate offset applied to input
                                                 ... matrices. However, does not apply to input 
                                                 ... IsSkinMask_LocalRange. Use 0 x 1 value to  
                                                 ... ignore. If used, adjust NRows_Matrix 
                                                 ... accordingly. NRows_Matrix can be set to an 
                                                 ... arbitrary value when YOffset is non-empty. 
                                                 ... Scalar; type int32.      
        SkinSegmentConfig_Args,                  ... Configurations
        UseCompiledFunctionsTF                   ... Whether to use compiled functions
    );


%%%%%% Determine largest region in skin-segmentation mask %%%%%%

%Group pixels into connected regions, using the connection criteria of 8, which is the default   
%setting for function bwconncomp.

%Code generation running
if ~ coder.target('MATLAB')

    %Note: FindLargestRegion is a custom function located within folder 'FacePulseRate'.
    [RegionMaxPixelIdx,  ... The linear indices of pixels corresponding to the largest region. N
                         ... pixels x 1 column vector; type int32.
     NPixelsMax,         ... The number of pixels in the largest region identified. Scalar; type 
                         ... int32.
     NRegions] =         ... The number of regions identified. Scalar; type int32. 
        FindLargestRegion(IsSkinMask);

%Code generation not running
else

    CC = bwconncomp(IsSkinMask); 
    
    %The linear indices of pixels of each region. 
    %Cell array of 1 x M regions; elements of type double. 
    PixelIdxList = CC.PixelIdxList;
    
    %The number of regions identified. 
    %Scalar; type int32. 
    NRegions = int32( CC.NumObjects );
    
    %The number of pixels in each region. 
    %M regions x 1 column vector; type int32.
    NPixelsEachRegion = zeros(CC.NumObjects, 1, 'int32'); 

    for j = 1 : CC.NumObjects
         
         NPixelsEachRegion(j) = numel( PixelIdxList{j} ); 
    end        

    %Note: function max returns the index of only one region, even if multiple regions have the 
    %same number of pixels.
    [NPixelsMax,            ... The number of pixels in the largest region identified. Scalar; type 
                            ... int32.                      
     RegionMaxIdx_Double] = ... The index of the largest region. The index corresponds to a 
                            ... position in PixelIdxList. Scalar; type double.
        max(NPixelsEachRegion);
    
    RegionMaxIdx = int32(RegionMaxIdx_Double);
     
    %Extract linear indices of pixels corresponding to the largest region
    %Cast to type int32 for use in other functions.
    %Column vector; type int32.
    RegionMaxPixelIdx = PixelIdxList{RegionMaxIdx};
end


%%%%%% Take minimums, maximums, and means of the largest region %%%%%%

%Metrics for tailored skin segmentation:

% - Mins and maxes of indexed Y, Cb, Cr, H, and S channels.

%Metrics for the skin-detection algorithm thresholds:   

% - Indexed RGB means.
% - Indexed YCbCr means.    

%Note: Type double R, G, and B means required for function SkinDetect_RGBProbSkinTrain, which uses 
%function fminunc, which requires type double.      

%If no region identified, skip over the remaining sections of the function and set outputs (color
%values) to NaN. Subsequent functions that depend upon these color values are set to omit values
%that equal NaN.
if NRegions == 0
    
    ithPrimaryROIRGBMeans        = nan(1, 3);
    ithPrimaryROIYCbCrMeans      = nan(1, 3,  'single');
    ithPrimaryROIYCbCrHSMinsMaxs = nan(1, 11, 'single');
        
%At least one region is available    
else           
    
    %Return minimums, maximums, and means                            
    %Note: MeansMinsMaxes is custom function located within folder FacePulseRate.         
    [ithPrimaryROIYCbCrHSMinsMaxs, ... Minimums and maximums. 1 x 11 row vector; type single.  
     ithPrimaryROIYCbCrMeans,      ... Means of indexed Y, Cb, and Cr channels; 1 x 3 row vector, 
                                   ... type single.
     ithPrimaryROIRGBMeans] =      ... Means of indexed R, G, and B channels; 1 x 3 row vector,  
                                   ... type double.                              
        MeansMinsMaxes( ...
            YSingle,  ... 
            CbSingle, ...
            CrSingle, ...
            HSingle,  ... 
            SSingle,  ...
            RUint8,   ...
            GUint8,   ...
            BUint8,   ...
            RegionMaxPixelIdx, ...       
            NPixelsMax, ...               
            X_Matrix_Reduced, ...
            Y_Matrix_Reduced, ...
            NRows_Matrix_Reduced, ...
            NRows_Matrix);    
                  
end %end if any region available
                                     

end %end main function


%=============================================================================================
%Local functions
%=============================================================================================


%=============================================================================================
function IsSkinMask_LocalRange_Reduced = ...
             CropMatrix(IsSkinMask_LocalRange, NRows_Matrix, NRows_Matrix_Reduced, ...
                 NCols_Matrix_Reduced, X_Matrix_Reduced, Y_Matrix_Reduced)
%CropMatrix   Crop matrix according to specified X- and Y-coordinates and width and height.
             

%Inline function
coder.inline('always');             
             
             
%Preallocate reduced-size matrix
IsSkinMask_LocalRange_Reduced = ...
    coder.nullcopy( false(NRows_Matrix_Reduced, NCols_Matrix_Reduced) );

%Initialize column index for reduced-size matrix                                  
ColIdx_Reduced = uint16(0);

%Loop across columns
for i = X_Matrix_Reduced : X_Matrix_Reduced + NCols_Matrix_Reduced - 1 

    %Advance index
    ColIdx_Reduced = ColIdx_Reduced + 1;    
    
    %Initialize row index for reduced-size matrix                                  
    RowIdx_Reduced = uint16(0);    
    
    %Loop across rows
    for j = Y_Matrix_Reduced : Y_Matrix_Reduced + NRows_Matrix_Reduced - 1       

        %Advance index
        RowIdx_Reduced = RowIdx_Reduced + 1;                    

        %Linear index corresponding to the full matrix
        %Convert from subscript indices to a linear index for more efficient indexing
        %Note: In compiled C code, the faster indexing outweighs the cost of this 
        %conversion.
        LinIdx_Full = j + (i - 1) * NRows_Matrix;        
        
        IsSkinMask_LocalRange_Reduced(RowIdx_Reduced, ColIdx_Reduced) = ...    
            IsSkinMask_LocalRange(LinIdx_Full);
    end
end


end %end local function


%=============================================================================================
%Code-generation and build script
%=============================================================================================

%Code-generation and build script used to generate C-language code and create the compiled version 
%(SkinDetect_RegionMetrics_mex) of the function.

%{

%%%%%% Specify variable-size input arguments %%%%%%

%See Matlab documentation for coder.typeof.

%Input Argument                           Example Code                 Upp. Bounds     Var. Size (T/F)  Type
YSingleCode               = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single
CbSingleCode              = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single
CrSingleCode              = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single 
RUint8Code                = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8
GUint8Code                = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8
BUint8Code                = coder.typeof( zeros(500, 500, 'uint8'),    [inf, inf],     [1, 1] );        %uint8
HSingleCode               = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single
SSingleCode               = coder.typeof( zeros(500, 500, 'single'),   [inf, inf],     [1, 1] );        %single
IsSkinMask_LocalRangeCode = coder.typeof( false(500, 500),             [inf, inf],     [1, 1] );        %logical


%%%%%% Specify fixed-size input arguments %%%%%%

%                                       Example Code                                                                 
NRows_MatrixCode                      = int32(1);                                                                  
NCols_MatrixCode                      = int32(1); 
UseCompiledFunctionsTFCode            = false;                                                              
SkinDetectConfig_Thresholds_SetTFCode = false;

SkinSegmentConfig_ArgsCode = ...                                                                                              
    struct( ...
        'SkinColorSamples_NThresholdPassedTF', false, ...
        'YCbCrThresholdsGeneric', zeros(1, 7, 'single'), ...
        'HSThresholdsGeneric', zeros(1, 2, 'single'), ...
        'YCbCrThresholdsTailored', zeros(1, 8, 'single'), ...
        'YCbCrThresholdsTailored_Sev', zeros(1, 8, 'single'), ...
        'HSThresholdsTailored', zeros(1, 3, 'single'), ...
        'HSThresholdsTailored_Sev', zeros(1, 3, 'single'), ...
        'RangeSEWidth', int16(0), ...
        'RangeThreshold', uint8(0), ...
        'MorphCloseSEMediumWidth_Tuned', int16(0), ...
        'MorphCloseSELargeWidth_Tuned', int16(0) ...    
    );   


%%%%%% Set configurations to increase performance %%%%%%

%Note: see Matlab Coder documention for coder.MexCodeConfig and documentation topic 
%"Optimization Strategies"
cfg = coder.config('mex');
cfg.GlobalDataSyncMethod = 'NoSync';
cfg.ConstantInputs = 'IgnoreValues';
cfg.ExtrinsicCalls = false;
cfg.SaturateOnIntegerOverflow = false;
cfg.IntegrityChecks = false;
cfg.ResponsivenessChecks = false;


%%%%%% Specify flags to minGW compiler to optimize execution speed %%%%%%

%For documentation on minGW compiler flags, see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

%The flags are specified as part of the code-generation configuration object. A custom function,
%setbuildargs, is used to specify these flags. For details on the function implementation, see the 
%function file, which is located within folder FacePulseRate. This custom function is based upon 
%Matlab guidance found in
%https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function

%setbuildargs will be evaluated from text within the code-generation object, so it is converted to 
%a character vector prior to execution of the codegen command.

%%%%%% --- Specify the flags as arguments to function setbuildargs %%%%%%

%Argument buildInfo: this variable is assign by the caller (the codegen command executed below) and 
%is not present in the base workspace.

%Second argument: specify a cell array of compiler-specific flags, where each flag is a character 
%vector. As function setbuildargs will be evaluated from text, use double ' quotes for each 
%character vector to maintain the charater vector,
%e.g., {''-Ofast'' ''-fsingle-precision-constant''}.

setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast''})';

%Assign to code-generation configuration object
cfg.PostCodeGenCommand = setbuildargsAsText;


%%%%%% Execute codegen command to generate code and build compiled mex file %%%%%%

codegen ROIMeans_FirstRead_CollectSkinColorSamples.m -report -config cfg -args {YSingleCode, CbSingleCode, CrSingleCode, RUint8Code, GUint8Code, BUint8Code, HSingleCode, SSingleCode, IsSkinMask_LocalRangeCode, NRows_MatrixCode, NCols_MatrixCode, SkinSegmentConfig_ArgsCode, UseCompiledFunctionsTFCode}

%}

                 
                 
