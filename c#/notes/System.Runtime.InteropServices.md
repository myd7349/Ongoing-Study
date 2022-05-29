https://github.com/naudio/NAudio/blob/1f2cbc729c3cdbce2229edb1e0d617e9af35b555/NAudio/Wave/WaveStreams/WaveOutBuffer.cs#L31-L39

```csharp
var buffer = new byte[bufferSize];
GCHandle hBuffer = GCHandle.Alloc(buffer, GCHandleType.Pinned);
```

[Passing a char array from c# to c++ dll](https://stackoverflow.com/questions/38146181/passing-a-char-array-from-c-sharp-to-c-dll)

```cpp
int LZ4_compress_default(const unsigned char* source, unsigned char* dest,
    int sourceLength, int maxDestLength);
```

```csharp
[DllImport(@"...", CallingConvention = CallingConvention.Cdecl)] 
static extern int LZ4_compress_default(
    [In] byte[] source, 
    [Out] byte[] dest, 
    int sourceLength, 
    int maxDestLength
);
```

Bytes to Struct:

```csharp
public static MyPacket FromBytes(byte[] bytes, int offset, int count)
{
    Debug.Assert(offset + count <= bytes.Length);

    fixed (byte *pb = &bytes[offset])
    {
        return *(MyPacket *)pb;
    }
}
```

or:

```csharp
public static MyPacket FromBytes(byte[] bytes, int offset, int count)
{
    Debug.Assert(offset + count <= bytes.Length);

    // .NET 4.0:
    return (MyPacket)Marshal.PtrToStructure(
        Marshal.UnsafeAddrOfPinnedArrayElement(bytes, offset),
        typeof(MyPacket));
    // https://github.com/naudio/NAudio/blob/a2cc704b6cf9e1bbefd2e7fff14d5c5e19e8c2a0/NAudio/Utils/MarshalHelpers.cs#L38-L44
    return Marshal.PtrToStructure<MyPacket>(
        Marshal.UnsafeAddrOfPinnedArrayElement(bytes, offset),
        typeof(MyPacket));    
}
```

ILSpy + System.Core.dll:

> [assembly: DefaultDllImportSearchPaths(DllImportSearchPath.System32 | DllImportSearchPath.AssemblyDirectory)]

[Converting string to byte array in C#](https://stackoverflow.com/questions/16072709/converting-string-to-byte-array-in-c-sharp)

> You could use MemoryMarshal API to perform very fast and efficient conversion. String will implicitly be cast to ReadOnlySpan<byte>, as MemoryMarshal.Cast accepts either Span<byte> or ReadOnlySpan<byte> as an input parameter.
> 
> ```csharp
> public static class StringExtensions
> {
>     public static byte[] ToByteArray(this string s) => s.ToByteSpan().ToArray(); //  heap allocation, use only when you cannot operate on spans
>     public static ReadOnlySpan<byte> ToByteSpan(this string s) => MemoryMarshal.Cast<char, byte>(s);
> }
> ```

NativeLibrary.SetDllImportResolver

https://github.com/microsoft/msquic/blob/v2.0.3/src/cs/tool/Program.cs

```csharp
NativeLibrary.SetDllImportResolver(typeof(MsQuic).Assembly, (libraryName, assembly, searchPath) =>
{
    if (libraryName != "msquic") return IntPtr.Zero;
    if (NativeLibrary.TryLoad(args[0], out var ptr))
    {
        return ptr;
    }
    return IntPtr.Zero;
});
```

[Native interoperability best practices](https://docs.microsoft.com/en-us/dotnet/standard/native-interop/best-practices?source=recommendations)

[WinApi - GetLastError vs. Marshal.GetLastWin32Error](https://stackoverflow.com/questions/17918266/winapi-getlasterror-vs-marshal-getlastwin32error)
