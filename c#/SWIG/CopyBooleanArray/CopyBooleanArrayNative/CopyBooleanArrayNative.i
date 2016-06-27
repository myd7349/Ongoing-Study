%module CopyBooleanArrayNative

%{
#include "CopyCppBooleanArray.h"
%}

//#define USE_USER_DEFINED_TYPEMAPS
//#define USE_FIXED_TYPEMAP
#define USE_IN_OUT_TYPEMAPS // issue 616

#ifdef USE_USER_DEFINED_TYPEMAPS

%include "cpp_boolean_arrays_csharp.i"

%apply bool INPUT[]  { bool source[] }
%apply bool OUTPUT[] { bool target[] }

#elif defined(USE_FIXED_TYPEMAP)

%include <arrays_csharp.i>

%apply bool FIXED[]  { bool source[] }
%apply bool FIXED[] { bool target[] }
%csmethodmodifiers CopyBooleanArray "public unsafe";

#elif defined(USE_IN_OUT_TYPEMAPS)

%include <arrays_csharp.i>

%apply bool INPUT[]  { bool source[] }
%apply bool OUTPUT[] { bool target[] }

#endif

%include "CopyCppBooleanArray.h"

// References:
// SWIG 3.0 Documentation
//   -- 11.3.6 Debugging typemap pattern matching