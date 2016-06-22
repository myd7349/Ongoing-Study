%module CopyBooleanArrayNative

%{
#include "CopyCppBooleanArray.h"
%}

#if 0

%include "cpp_boolean_arrays_csharp.i"

%apply bool INPUT[]  { bool source[] }
%apply bool OUTPUT[] { bool target[] }

#else

%include <arrays_csharp.i>

%apply bool FIXED[]  { bool source[] }
%apply bool FIXED[] { bool target[] }
%csmethodmodifiers CopyBooleanArray "public unsafe";

#endif

%include "CopyCppBooleanArray.h"