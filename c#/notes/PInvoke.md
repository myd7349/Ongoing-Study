[Platform Invocation Services](https://en.wikipedia.org/wiki/Platform_Invocation_Services)

[C# 调用 C++ API 时，函数的参数类型该怎么转换？](https://www.zhihu.com/question/34670135/answer/100024595)

1.  [PInvoke Interop Assistant/clrinterop](https://archive.codeplex.com/?p=clrinterop)

2. If you want to use Win32 APIs in C#, then you should take a look at [pinvoke.net](http://pinvoke.net/). BTW, a Visual Studio plugin for `pinvoke.net` is also available.

   _Update_: Finally, we have pre-built binarys:

   * [PInvoke.Kernel32](https://www.nuget.org/packages/PInvoke.Kernel32/)

   * [dotnet/pinvoke](https://github.com/dotnet/pinvoke)

     - [New Source Generator based approach to getting all the Win32 methods and types you need](https://github.com/dotnet/pinvoke/issues/565)

     - [Making Win32 APIs More Accessible to More Languages](https://blogs.windows.com/windowsdeveloper/2021/01/21/making-win32-apis-more-accessible-to-more-languages/)

3. SWIG, CXXI, CppSharp

4. [C#/Win32 P/Invoke Source Generator](https://github.com/microsoft/CsWin32)

   - [win32metadata](https://github.com/microsoft/win32metadata)

5.  [Vanara](https://github.com/dahall/Vanara) - A set of .NET libraries for Windows implementing PInvoke calls to many native Windows APIs with supporting wrappers.

6. Book: [.NET and COM: The Complete Interoperability Guide](https://www.oreilly.com/library/view/net-and-com/9780672333583/)

[NNanomsg](https://github.com/mhowlett/NNanomsg/blob/master/NNanomsg/Interop.cs)

[P/Invoke pointer to pointer?](https://stackoverflow.com/questions/6033346/p-invoke-pointer-to-pointer)

[How to import void * C API into C#?](https://stackoverflow.com/questions/521774/how-to-import-void-c-api-into-c)

https://github.com/labstreaminglayer/liblsl-Csharp/blob/master/LSL.cs

[PInvoke for C function that returns char \*](https://stackoverflow.com/questions/370079/pinvoke-for-c-function-that-returns-char)

C:
```c
TCHAR *ReadFileContents(LPCTSTR lpcszFilePath)
{
    DWORD dwBytes = GetFileLength(lpcszFilePath);
    TCHAR *pszBuffer = new TCHAR[dwBytes + 1](); // `\0` terminated.
    if (pszBuffer != nullptr)
    {
        // ...
        // Read file contents
    }

    return pszBuffer;
}

void FreeFileContents(TCHAR *pszText)
{
    if (pszText != nullptr)
        delete[] pszText;
}
```

C#
```csharp
using System.Runtime.InteropServices;

public static string ReadFileContents(string filePath)
{
    var contentPtr = ReadFileContentsNative(filePath);
    if (contentPtr == IntPtr.Zero)
        return "";

    var content = Marshal.PtrToStringAuto(contentPtr);
    FreeFileContentsNative(contentPtr);
    return content;
}

[DllImport("NativeDLL.dll", EntryPoint = "ReadFileContents", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
private static extern IntPtr ReadFileContentsNative(string filePath);

\[DllImport("NativeDLL.dll", EntryPoint = "FreeFileContents", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
private static extern void FreeFileContentsNative(IntPtr text);
```

[pinvoke to function which returns string array](https://stackoverflow.com/questions/22126172/pinvoke-to-function-which-returns-string-array)

https://github.com/texus/TGUI.Net/blob/ff5804eb082c3677d5b2bbe13be1b48b63397407/src/Global.cs#L35-L41

https://github.com/microsoft/win32metadata

[How to Marshal a C++ Class](https://www.codeproject.com/Articles/18032/How-to-Marshal-a-C-Class)

[Native interoperability best practices](https://docs.microsoft.com/en-us/dotnet/standard/native-interop/best-practices)

[UnmanagedFunctionPointer - FreeRDP example](https://github.com/FreeRDP/FreeRDP-Sharp/blob/0334b0dcc785243ba752b1731f123212a733fdc2/FreeRDP/Core/FreeRDP.cs#L25)

https://github.com/HDFGroup/HDF.PInvoke/blob/d281aa75f1562e677d1307cc1a234f9079cd76c3/HDF5/H5Spublic.cs#L601-L609

> ```c#
> [DllImport(Constants.DLLFileName, EntryPoint = "H5Sselect_hyperslab", CallingConvention = CallingConvention.Cdecl),
> SuppressUnmanagedCodeSecurity, SecuritySafeCritical]
> public static extern herr_t select_hyperslab(hid_t space_id, seloper_t op,
>     [MarshalAs(UnmanagedType.LPArray)] hsize_t[] start,
>     [MarshalAs(UnmanagedType.LPArray)] hsize_t[] stride,
>     [MarshalAs(UnmanagedType.LPArray)] hsize_t[] count,
>     [MarshalAs(UnmanagedType.LPArray)] hsize_t[] block);
> ```

[How to marshal collection in c# to pass to native (C++) code](https://stackoverflow.com/questions/5102436/how-to-marshal-collection-in-c-sharp-to-pass-to-native-c-code) - Marshal a string array.

[Return contents of a std::wstring from C++ into C#](https://stackoverflow.com/questions/7051097/return-contents-of-a-stdwstring-from-c-into-c-sharp)

[board_controller_library.cs](https://github.com/brainflow-dev/brainflow/blob/bb6883783badcc5303570b0d6783687a30d43f12/csharp-package/brainflow/brainflow/board_controller_library.cs#L395-L410)

> ```csharp
> public static int start_stream (int buffer_size, string streamer_params, int board_id, string input_json)
> {
>     switch (PlatformHelper.get_library_environment ())
>     {
>         case LibraryEnvironment.x64:
>             return BoardControllerLibrary64.start_stream (buffer_size, streamer_params, board_id, input_json);
>         case LibraryEnvironment.x86:
>             return BoardControllerLibrary32.start_stream (buffer_size, streamer_params, board_id, input_json);
>         case LibraryEnvironment.Linux:
>             return BoardControllerLibraryLinux.start_stream (buffer_size, streamer_params, board_id, input_json);
>         case LibraryEnvironment.MacOS:
>             return BoardControllerLibraryMac.start_stream (buffer_size, streamer_params, board_id, input_json);
>     }
> 
>     return (int)CustomExitCodes.GENERAL_ERROR;
> }
> ```

https://github.com/CodefoundryDE/LegacyWrapper

[COM or C++/CLI layer for long-term maintenance?](https://www.reddit.com/r/cpp/comments/nonhuk/com_or_ccli_layer_for_longterm_maintenance/)

https://github.com/ookii-dialogs/ookii-dialogs-winforms/blob/master/src/Ookii.Dialogs.WinForms/Interop/IProgressDialog.cs