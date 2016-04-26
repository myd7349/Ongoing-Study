// 2016-04-26T10:00+08:00
%module CopyArrayNative

%include <arrays_csharp.i>

%apply double INPUT[] {const double *sourceArray}
%apply double OUTPUT[] {double *targetArray}
//%rename(CopyArrayViaDefaultMarshalling) CopyArray;

%include "CopyArray.i"

// References:
// SWIG-3.0 Documentation:
//   -- 20.4.2 Managed arrays using P/Invoke default array marshalling