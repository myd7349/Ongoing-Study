// 2016-07-01T10:04+08:00
using System.Runtime.InteropServices;
using System.Security;

namespace ArraysInsideOfStructures
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct Data1
    {
        public int header;
        public int elem0;
        public int elem1;
        public int elem2;
        public int elem3;
        public int elem4;
        public int elem5;
        public int elem6;
        public int elem7;
        public int elem8;
        public int elem9;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Size = 44)]
    public struct Data2
    {
        public int header;
        public int data;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct Data3
    {
        public int header;

        [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.I4, SizeConst = 10)]
        public int[] data;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public unsafe struct Data4
    {
        public int header;
        public fixed int data[10];
    }

    public static class FillStructNative
    {
        [SuppressUnmanagedCodeSecurity]
        [DllImport("FillStruct.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "FillStruct")]
        public static extern void FillStruct1(ref Data1 data);

        [SuppressUnmanagedCodeSecurity]
        [DllImport("FillStruct.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "FillStruct")]
        public static extern void FillStruct2(ref Data2 data);

        [SuppressUnmanagedCodeSecurity]
        [DllImport("FillStruct.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "FillStruct")]
        public static extern void FillStruct3(ref Data3 data);

        [SuppressUnmanagedCodeSecurity]
        [DllImport("FillStruct.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "FillStruct")]
        public static extern void FillStruct4(ref Data4 data);
    }
}

// References:
// [Arrays inside of structures](https://blogs.msdn.microsoft.com/ericgu/2004/08/12/arrays-inside-of-structures/)
// C# 6.0 in a Nutshell/Chapter 4. Advanced C#/Unsafe Code and Pointers/Arrays/Fixed-size buffers
