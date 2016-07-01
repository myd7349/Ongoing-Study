/* 2016-04-01T23:15+08:00 */
%module dataseq

%{
#include "../../../cpp/DLL/DataSequenceV2/DataSeq/DataSeq.h"  
%}

%rename("%(strip:[DataSeq_])s") "";
/* %rename("%(lower)s", %$isfunction) ""; */
%rename(DSMemoryError) MemoryError;
%feature("except") DataSeq_Create(DataSeqHandle *, Size size = 0);
%feature("except") DataSeq_CreateV2(Size size = 0);

%include <cpointer.i>
%include <typemaps.i>

//%pointer_functions(DataSeqHandle, DataSeqHandlePtr); // So that we can call DataSeq_Create. Not work yet!
%pointer_functions(double, DoublePtr); // So that we can call DataSeq_PopBack, DataSeq_GetAt
%pointer_functions(unsigned, UIntPtr); // So that we can call DataSeq_GetSize

//%apply DataSeqHandle *OUTPUT { DataSeqHandle *dataSeqPtr };

%newobject DataSeq_CreateV2;
%delobject DataSeq_Free;



%include "../../../cpp/DLL/DataSequenceV2/DataSeq/DataSeq.h"

// References:
// SWIGDocumentation.pdf
//   -- 9. SWIG library
//   -- 11.5.7 "argout" typemap
//   -- 11.5.9 "newfree" typemap
//   -- 11.6.2 Implementing constraints with typemaps
//   -- 12.2 Object ownership and %newobject