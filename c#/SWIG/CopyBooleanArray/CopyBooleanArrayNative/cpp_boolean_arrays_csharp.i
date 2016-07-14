%define CSHARP_ARRAYS( CTYPE, CSTYPE )

// input only arrays

%typemap(ctype)   CTYPE INPUT[] "CTYPE*"
%typemap(cstype)  CTYPE INPUT[] "CSTYPE[]"
%typemap(imtype, inattributes="[global::System.Runtime.InteropServices.In, global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.LPArray, ArraySubType = System.Runtime.InteropServices.UnmanagedType.U1)]") CTYPE INPUT[] "CSTYPE[]"
%typemap(csin)    CTYPE INPUT[] "$csinput"

%typemap(in)      CTYPE INPUT[] "$1 = $input;"
%typemap(freearg) CTYPE INPUT[] ""
%typemap(argout)  CTYPE INPUT[] ""

// output only arrays

%typemap(ctype)   CTYPE OUTPUT[] "CTYPE*"
%typemap(cstype)  CTYPE OUTPUT[] "CSTYPE[]"
%typemap(imtype, inattributes="[global::System.Runtime.InteropServices.Out, global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.LPArray, ArraySubType = System.Runtime.InteropServices.UnmanagedType.U1)]") CTYPE OUTPUT[] "CSTYPE[]"
%typemap(csin)    CTYPE OUTPUT[] "$csinput"

%typemap(in)      CTYPE OUTPUT[] "$1 = $input;"
%typemap(freearg) CTYPE OUTPUT[] ""
%typemap(argout)  CTYPE OUTPUT[] ""

// inout arrays

%typemap(ctype)   CTYPE INOUT[] "CTYPE*"
%typemap(cstype)  CTYPE INOUT[] "CSTYPE[]"
%typemap(imtype, inattributes="[global::System.Runtime.InteropServices.In, global::System.Runtime.InteropServices.Out, global::System.Runtime.InteropServices.MarshalAs(global::System.Runtime.InteropServices.UnmanagedType.LPArray, ArraySubType = System.Runtime.InteropServices.UnmanagedType.U1)]") CTYPE INOUT[] "CSTYPE[]"
%typemap(csin)    CTYPE INOUT[] "$csinput"

%typemap(in)      CTYPE INOUT[] "$1 = $input;"
%typemap(freearg) CTYPE INOUT[] ""
%typemap(argout)  CTYPE INOUT[] ""

%enddef // CSHARP_ARRAYS


CSHARP_ARRAYS(bool, bool)


// References:
// https://github.com/swig/swig/issues/616
// [Interop with Native Libraries](http://www.mono-project.com/docs/advanced/pinvoke/#boolean-members)
// [Passing Array of Bool to C++ Code from C#](http://stackoverflow.com/questions/31410324/passing-array-of-bool-to-c-code-from-c-sharp)
// [CA1414: Mark boolean P/Invoke arguments with MarshalAs](https://msdn.microsoft.com/en-us/library/ms182206.aspx)
// [Marshaling with C# ¨C Chapter 2: Marshaling Simple Types](http://www.codeproject.com/Articles/66244/Marshaling-with-Csharp-Chapter-2-Marshaling-Simple.aspx)
