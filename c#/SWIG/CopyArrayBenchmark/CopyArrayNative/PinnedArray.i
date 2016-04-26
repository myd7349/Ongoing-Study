// 2016-04-26T09:58+08:00
%module CopyArrayNative

%include <arrays_csharp.i>

%apply double FIXED[] {const double *sourceArray}
%apply double FIXED[] {double *targetArray}
//%rename(CopyArrayViaPinning) CopyArray;
%csmethodmodifiers CopyArray "public unsafe";

%include "CopyArray.i"

// References:
// SWIG-3.0 Documentation:
//   -- 20.4.3 Managed arrays using pinning