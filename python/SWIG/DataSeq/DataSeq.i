/* 2016-04-01T23:15+08:00 */
%module dataseq

%{
#include "../../../cpp/DLL/DataSequenceV2/DataSeq/DataSeq.h"  
%}

%rename("%(strip:[DataSeq_])s") "";
/* %rename("%(lower)s", %$isfunction) ""; */
%include "../../../cpp/DLL/DataSequenceV2/DataSeq/DataSeq.h"