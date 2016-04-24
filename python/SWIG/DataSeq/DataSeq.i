/* 2016-04-01T23:15+08:00 */
%module dataseq

%{
#include "../../../cpp/DLL/DataSequenceV2/DataSeq/DataSeq.h"  
%}

//%rename(Create) DataSeq_CreateV2;
//%rename(GetSize) DataSeq_GetSizeV2;
%rename("%(strip:[DataSeq_])s") "";
/* %rename("%(lower)s", %$isfunction) ""; */

%include "cpointer.i"

%include "../../../cpp/DLL/DataSequenceV2/DataSeq/DataSeq.h"

//%pointer_functions(void, DataSeqPtr); // TODO: So that we can call DataSeq_Create
%pointer_functions(double, DoublePtr); // So that we can call DataSeq_PopBack, DataSeq_GetAt
%pointer_functions(unsigned, UIntPtr); // So that we can call DataSeq_GetSize

// References:
// SWIGDocumentation.pdf
//   -- 9. SWIG library