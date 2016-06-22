%{
#include "BooleanArray.h"
%}  

%include <arrays_csharp.i>

#if 1
%apply bool INPUT[]  { bool source[] }
%apply bool OUTPUT[] { bool target[] }
#else
%apply bool FIXED[]  { bool source[] }
%apply bool FIXED[] { bool target[] }
%csmethodmodifiers CopyBooleanArray "public unsafe";
#endif

%include "BooleanArray.h"  
