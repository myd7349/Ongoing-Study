using System;
using System.Runtime.InteropServices;

namespace FakeAD
{
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate uint FakeADCallback32(IntPtr buffer, uint bytes, IntPtr context);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate ulong FakeADCallback64(IntPtr buffer, ulong bytes, IntPtr context);
}


// References:
// [Set C# callback on a C++ struct obtained via P/Invoke](https://stackoverflow.com/questions/50818345/set-c-sharp-callback-on-a-c-struct-obtained-via-p-invoke)
