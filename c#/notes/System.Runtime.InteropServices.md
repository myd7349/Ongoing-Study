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
