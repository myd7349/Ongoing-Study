// 2016-08-07T20:01+08:00
%module VarargsTestNative

%{
#include "VarargsTestNative.h"
%}

%include <arrays_csharp.i>
%include <std_vector.i>

%apply int FIXED[] { const int * }
%csmethodmodifiers RetrieveASamplingFromMultiLeadsData "public unsafe";
%template(IntVector) std::vector<int>;

%feature("compactdefaultargs") RetrieveASamplingFromMultiLeadsData;
%varargs(18, const int *lead = NULL) RetrieveASamplingFromMultiLeadsData;
%typemap(in, numinputs=0) const int *lead18 ""

%include "VarargsTestNative.h"

// References:
// SWIG 3.0 Documentation/14 Variable Length Arguments
