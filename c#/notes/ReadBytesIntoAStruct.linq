<Query Kind="Program">
  <Namespace>System.Runtime.InteropServices</Namespace>
</Query>

[StructLayout(LayoutKind.Sequential)]
public struct DataPack
{
    public double X, Y, Z;
}


public static T BytesToStruct<T>(byte[] bytes) where T : struct
{
    GCHandle handle = GCHandle.Alloc(bytes, GCHandleType.Pinned);
    T structure = (T)Marshal.PtrToStructure(handle.AddrOfPinnedObject(), typeof(T));
    handle.Free();

    return structure;
}

    
void Main()
{
    var rawData = new double[] { 1.0, 3.14, 2.71 };
    var buffer = new byte[rawData.Length * sizeof(double)];

    using (var memoryStream = new MemoryStream(buffer, 0, buffer.Length, true, true))
    using (var binaryWriter = new BinaryWriter(memoryStream))
    using (var binaryReader = new BinaryReader(memoryStream))
    {
        for (int i = 0; i < rawData.Length; ++i)
            binaryWriter.Write(rawData[i]);
            
        var data = memoryStream.GetBuffer();
        Console.WriteLine(data);
        
        var dataPack = BytesToStruct<DataPack>(data);
        Console.WriteLine($"DataPack: {{ {dataPack.X}, {dataPack.Y}, {dataPack.Z} }}");
    }
}

// References:
// https://stackoverflow.com/questions/9057798/cannot-write-to-memorystream-using-binarywriter
// https://stackoverflow.com/questions/2384/read-binary-file-into-a-struct
