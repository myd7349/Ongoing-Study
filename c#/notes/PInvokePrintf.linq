<Query Kind="Program">
  <Namespace>System.Runtime.InteropServices</Namespace>
</Query>

void Main()
{
    Printf("%d 42");
    printf_fmt("Hello %s!\n", __arglist("World"));
}

[DllImport("msvcrt.dll", EntryPoint = "printf", CallingConvention = CallingConvention.Cdecl)]
private static extern unsafe int printf(byte* fmtAndArglist);

public static unsafe void Printf(string fmtAndArglist)
{
    int utf8FmtAndArglistBufSize = Utf8Size(fmtAndArglist);
    byte* utf8FmtAndArglist = stackalloc byte[utf8FmtAndArglistBufSize];
    printf(Utf8Encode(fmtAndArglist, utf8FmtAndArglist, utf8FmtAndArglistBufSize));
}


internal static int Utf8Size(string str)
{
    if (str == null)
        return 0;

    return (str.Length * 4) + 1;
}

internal static unsafe byte* Utf8Encode(string str, byte* buffer, int bufferSize)
{
    if (str == null)
        return (byte*) 0;

    fixed (char* strPtr = str)
    {
        Encoding.UTF8.GetBytes(strPtr, str.Length + 1, buffer, bufferSize);
    }
    return buffer;
}

[DllImport("msvcr120.dll", EntryPoint = "printf")]
public static extern int printf_fmt(string format, __arglist);

// References:
// https://github.com/flibitijibibo/SDL2-CS/blob/904eed3cb04319c4e3e360360943e39080f80d7b/src/SDL2.cs#L902-L917
// ["Hello World" via PInvoke](https://stackoverflow.com/questions/34302729/hello-world-via-pinvoke)
