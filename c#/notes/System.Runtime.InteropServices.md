https://github.com/naudio/NAudio/blob/1f2cbc729c3cdbce2229edb1e0d617e9af35b555/NAudio/Wave/WaveStreams/WaveOutBuffer.cs#L31-L39
```csharp
var buffer = new byte[bufferSize];
GCHandle hBuffer = GCHandle.Alloc(buffer, GCHandleType.Pinned);
```
