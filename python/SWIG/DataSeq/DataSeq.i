/* 2016-04-01T23:15+08:00 */
%module dataseq

%{
#include "../../../cpp/DLL/DataSequenceV2/DataSeq/DataSeq.h"  
%}

%ignore DataSeq_Create;
%ignore DataSeq_GetSize;
%rename(Create) DataSeq_CreateV2;
%rename(GetSize) DataSeq_GetSizeV2;
%rename("%(strip:[DataSeq_])s") "";
/* %rename("%(lower)s", %$isfunction) ""; */

%include "../../../cpp/DLL/DataSequenceV2/DataSeq/DataSeq.h"