namespace MarshalCppClass
{
    using System;
    using System.Runtime.InteropServices;

    static class PersonNativesX86
    {
        // PreLoad
        private static NativeDLLImporter Instance = NativeDLLImporter.Instance;

        [DllImport(NativeDLLImporter.DLLFileName,
            EntryPoint = "?New@Person@@SAPAV1@PBDH@Z",
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.Cdecl)]
        static public extern IntPtr New(
            [MarshalAs(UnmanagedType.LPStr)] string name = "",
            int age = 0);

        [DllImport(NativeDLLImporter.DLLFileName,
            EntryPoint = "?Delete@Person@@SAXPAV1@@Z",
            CallingConvention = CallingConvention.Cdecl)]
        static public extern void Delete(IntPtr person);

        [DllImport(NativeDLLImporter.DLLFileName,
            EntryPoint = "?GetName@Person@@QBEPBDXZ",
            CallingConvention = CallingConvention.ThisCall)]
        static public extern IntPtr GetName(IntPtr person);

        [DllImport(NativeDLLImporter.DLLFileName,
            EntryPoint = "?SetName@Person@@QAEXPBD@Z",
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.ThisCall)]
        static public extern void SetName(
            IntPtr person,
            [MarshalAs(UnmanagedType.LPStr)] string name);

        [DllImport(NativeDLLImporter.DLLFileName,
            EntryPoint = "?GetAge@Person@@QBEHXZ",
            CallingConvention = CallingConvention.ThisCall)]
        static public extern int GetAge(IntPtr person);

        [DllImport(NativeDLLImporter.DLLFileName,
            EntryPoint = "?SetAge@Person@@QAEXH@Z",
            CallingConvention = CallingConvention.ThisCall)]
        static public extern void SetAge(IntPtr person, int age);

        [DllImport(NativeDLLImporter.DLLFileName,
            EntryPoint = "?Say@Person@@QBEXPBD@Z",
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.ThisCall)]
        static public extern void Say(
            IntPtr person,
            [MarshalAs(UnmanagedType.LPStr)] string what);

#if false
        [DllImport(NativeDLLImporter.DLLFileName,
            EntryPoint = "GetArch",
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.Cdecl)]
        public static extern string GetArch();
#elif false
        [DllImport(NativeDLLImporter.DLLFileName)]
        public static extern string GetArch();
#else
        public static string GetArch()
        {
            return Marshal.PtrToStringAnsi(GetArchPrivate());
        }

        [DllImport(NativeDLLImporter.DLLFileName,
            EntryPoint = "GetArch",
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetArchPrivate();
#endif
    }
}

// References:
// [How to Marshal a C++ Class](https://www.codeproject.com/Articles/18032/How-to-Marshal-a-C-Class)
// [PInvoke for C function that returns char *](https://stackoverflow.com/questions/370079/pinvoke-for-c-function-that-returns-char)
// [How do I pass a const char* to a C function from C#?](https://stackoverflow.com/questions/30028593/how-do-i-pass-a-const-char-to-a-c-function-from-c)
