%{
#include "BooleanArray.h"
%}  

%include <arrays_csharp.i>

%apply bool INPUT[]  { bool source[] }
%apply bool OUTPUT[] { bool target[] }

%include "BooleanArray.h"  
