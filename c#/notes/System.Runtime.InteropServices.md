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
