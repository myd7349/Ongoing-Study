%module CopyBooleanArrayNative

%{
#include "CopyCppBooleanArray.h"
%}

%include "cpp_boolean_arrays_csharp.i"

%apply bool INPUT[]  { bool source[] }
%apply bool OUTPUT[] { bool target[] }

%include "CopyCppBooleanArray.h"