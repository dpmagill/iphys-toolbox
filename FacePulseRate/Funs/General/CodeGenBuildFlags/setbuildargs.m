function setbuildargs(buildInfo, linkFlags)
%setbuildargs    Set the build flags for the compiler when compiling generated C code.
%
%    Used when running a built script to compile functions for use in function FacePulseRate. 
%
%
%    Description
%    -----------
%
%    Set the build flags for the compiler when compiling generated C code.
%
%    This function is not called by function FacePulseRate, but is called when manually generating
%    C code and compiling a function by running a code-generation/build script. The 
%    code-generation/build script used for each compiled function in FacePulseRate is located at
%    the bottom of the function file used to generate code for the function. For example, the
%    code-generation/build script for function SkinSegmentMask_mex is located at the bottom of file
%    SkinSegmentMask.m.
%
%    Inputs:
%
%        buildInfo = the compiler settings object (PostCodeGenCommand) for a Matlab  
%                    code-generation configuration object. 
%                    Note: this variable is only accessible to an internal Matlab function.                   
%        linkFlags = a cell array of compiler-specific flags to use, where each flag is a character
%                    vector.
%
%    -- Usage Notes --
%
%    Within the code-generation/build script, after assigning a Matlab code-generation 
%    configuration object 
%    e.g., cfg = coder.config('mex'), 
%    specify the current function as a character vector to option PostCodeGenCommand. For argument
%    linkFlags, use double ' quotes for each character vector in the cell array to maitain as type 
%    char,  
%    e.g.,
%    setbuildargsAsText = 'setbuildargs(buildInfo, {''-Ofast'' ''-fsingle-precision-constant''})'
%    cfg.PostCodeGenCommand = setbuildargsAsText
%
%    Code adapted from 
%    https://www.mathworks.com/matlabcentral/answers/345549-how-can-i-modify-the-build-information-for-mex-code-generation-with-the-codegen-function
%
%    -- Compiler Notes --
%
%    MinGW is the compiler specified in all code-generation/build scripts for the FacePulseRate 
%    toolbox, so flags used will be specific to this compiler. Other compilers can be used based 
%    upon compatibility with Matlab code generation (see 
%    https://www.mathworks.com/support/requirements/supported-compilers.html). For certain 
%    functions, which are not currently compiled in FacePulseRate, a compiler other than MinGW 
%    is required. For example, to compile some OpenCV functions, such as 
%    vision.CascadeObjectDetector, a specified version of Windows Visual Studio is required (see
%    https://www.mathworks.com/help/vision/ug/portable-c-code-generation-for-functions-that-use-opencv-library.html).
%
%    For documentation on MinGW compiler flags, see
%    https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html.
%
%    For documentation on Windows Visual Studio (not currently used), see
%    https://docs.microsoft.com/en-us/cpp/build/reference/o1-o2-minimize-size-maximize-speed?view=vs-2019
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Assign flag(s) to configuration object %%%%%%

buildInfo.addLinkFlags(linkFlags);


end %end function
