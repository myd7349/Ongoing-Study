[C# 调用 C++ API 时，函数的参数类型该怎么转换？](https://www.zhihu.com/question/34670135/answer/100024595)

1.  [PInvoke Interop Assistant/clrinterop](https://archive.codeplex.com/?p=clrinterop)

2.  If you want to use Win32 APIs in C#, then you should take a look at [pinvoke.net](http://pinvoke.net/). BTW, a Visual Studio plugin for `pinvoke.net` is also available.

   _Update_: Finally, we have pre-built binarys:

   * [PInvoke.Kernel32](https://www.nuget.org/packages/PInvoke.Kernel32/)
   * [dotnet/pinvoke](https://github.com/dotnet/pinvoke)

3. SWIG, CXXI, CppSharp

4. [C#/Win32 P/Invoke Source Generator](https://github.com/microsoft/CsWin32)

5. Book: [.NET and COM: The Complete Interoperability Guide](https://www.oreilly.com/library/view/net-and-com/9780672333583/)

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
