using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;

using static Native.Interop.UnsafeNativeMethodsWin32;

namespace FakeAD
{
    internal static class Natives
    {
        static Natives()
        {
#if false
            Is64Bit = IntPtr.Size == 8;
#else
            Is64Bit = Environment.Is64BitProcess;
#endif

            Trace.WriteLine($"Is 64-bit? {Is64Bit}");

            var searchPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            if (Is64Bit)
                searchPath = Path.Combine(searchPath, "x64");
            else
                searchPath = Path.Combine(searchPath, "x86");

#if false
            Trace.WriteLine($"Search {DllName} in {searchPath}");
            var fullPath = Path.Combine(searchPath, DllName);
            DllHandle = LoadLibrary(fullPath);
            if (DllHandle != IntPtr.Zero)
                Trace.WriteLine($"Load {DllName} successfully!");
            else
                Trace.WriteLine($"Failed to load {fullPath}!");
#else
            SetDllDirectory(searchPath);
#endif
            NativeLibrary.SetDllImportResolver(
                typeof(FakeADWrapper).Assembly,
                (libraryName, assembly, searchPath) =>
                {
                    Trace.Write($"Try to load native library {libraryName}. ");
                    if (NativeLibrary.TryLoad(libraryName, out var handle))
                    {
                        Trace.WriteLine("OK!");
                        return handle;
                    }

                    Trace.WriteLine("Failed!");
                    return IntPtr.Zero;
                });
        }

        public const string DllName = "fakead.dll";

        public static readonly bool Is64Bit;

        [DllImport(DllName, EntryPoint = "fake_ad_init")]
        public static extern IntPtr Init32(ref Config32 config);

        [DllImport(DllName, EntryPoint = "fake_ad_init")]
        public static extern IntPtr Init64(ref Config64 config);

        [DllImport(DllName, EntryPoint = "fake_ad_read")]
        public static extern uint Read32([In] IntPtr context, IntPtr buffer, uint size);

        [DllImport(DllName, EntryPoint = "fake_ad_read")]
        public static extern ulong Read64([In] IntPtr context, IntPtr buffer, ulong size);

        [DllImport(DllName, EntryPoint = "fake_ad_free")]
        public static extern void Free(ref IntPtr context);

        [DllImport(DllName, EntryPoint = "fake_ad_errno")]
        public static extern Error GetError();

        [DllImport(DllName, EntryPoint = "fake_ad_strerror")]
        public static extern IntPtr ErrorToCStr(Error error);

        public static string ErrorToString(Error error)
        {
            return Marshal.PtrToStringAnsi(ErrorToCStr(error));
        }

        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern bool SetDllDirectory(string path);

#if false
        private static readonly IntPtr DllHandle;
#endif
    }
}


// References:
// [Anycpu nuget package the requires either 32 bit or 64 bit package](https://stackoverflow.com/questions/28569979/anycpu-nuget-package-the-requires-either-32-bit-or-64-bit-package/28771413#28771413)
// [Can a .NET application targeted for "Any CPU" use P/Invoke calls in multiple environments?](https://stackoverflow.com/questions/2632458/can-a-net-application-targeted-for-any-cpu-use-p-invoke-calls-in-multiple-env)
// [C# Pinvoke with C struct contains function pointer](https://stackoverflow.com/questions/20691786/c-sharp-pinvoke-with-c-struct-contains-function-pointer)
// [Set C# callback on a C++ struct obtained via P/Invoke](https://stackoverflow.com/questions/50818345/set-c-sharp-callback-on-a-c-struct-obtained-via-p-invoke)
// [Copy dll modified in post-build to obj folder](https://stackoverflow.com/questions/42923446/copy-dll-modified-in-post-build-to-obj-folder)
// > xcopy.exe "$(ProjectDir)TheModifyiedFolder\Modifying.dll" "$(ProjectDir)obj" /y /s
// [Are there any better ways to copy a native dll to the bin folder?](https://stackoverflow.com/questions/3863419/are-there-any-better-ways-to-copy-a-native-dll-to-the-bin-folder)
// [Correct way to marshal SIZE_T*?](https://stackoverflow.com/questions/1309509/correct-way-to-marshal-size-t)
// https://github.com/microsoft/msquic/blob/v2.0.3/src/cs/tool/Program.cs
// https://docs.microsoft.com/en-us/dotnet/api/system.runtime.interopservices.nativelibrary.setdllimportresolver?view=net-6.0
// [Native interoperability best practices](https://docs.microsoft.com/en-us/dotnet/standard/native-interop/best-practices?source=recommendations)
// https://docs.microsoft.com/en-us/dotnet/api/system.runtime.interopservices.nativelibrary.load?source=recommendations&view=net-6.0
// https://docs.microsoft.com/en-us/dotnet/api/system.runtime.interopservices.defaultdllimportsearchpathsattribute?view=net-6.0
// https://github.com/mono/SkiaSharp/blob/main/binding/Binding.Shared/LibraryLoader.cs
// [PInvoke with 32 and 64 bit machines](file:///C:/Users/hp/Downloads/PInvoke%20with%2032%20and%2064%20bit%20machines%20_%20Microsoft%20Learn%20(2022_10_21%2013_44_04).html)
// [.NET equivalent of size_t](https://stackoverflow.com/questions/772531/net-equivalent-of-size-t)
// https://github.com/AgigoNoTana/HiddenDesktopViewer/blob/master/HiddenDesktopViewer/Form1.cs#L754
// System.Environment.Is64BitOperatingSystem
