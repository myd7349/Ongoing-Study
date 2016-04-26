// 2016-04-26T10:32+08:00
%module CopyArrayNative

%include <carrays.i>

%array_functions(double, doubleArray);

%inline %{
extern void CopyArray(const double *sourceArray, double *targetArray, int items);
%}

// References:
// SWIG-3.0 Documentation:
//   -- 16 Working with Modules
//   -- 20.4.1 The SWIG C arrays library