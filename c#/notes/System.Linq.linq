<Query Kind="Program">
  <Namespace>System.Runtime.InteropServices</Namespace>
</Query>

[StructLayout(LayoutKind.Sequential)]
struct DataPack
{
    public short X, Y;
}

TStruct BytesToStruct<TStruct>(byte[] bytes) where TStruct : struct
{
    GCHandle handle = GCHandle.Alloc(bytes, GCHandleType.Pinned);
    TStruct structure = (TStruct)Marshal.PtrToStructure(handle.AddrOfPinnedObject(), typeof(TStruct));
    handle.Free();

    return structure;
}
        
IEnumerable<DataPack> ReadDataPacks(BinaryReader reader, int count)
{
    for (int i = 0; i < count; ++i)
        yield return BytesToStruct<DataPack>(reader.ReadBytes(Marshal.SizeOf(typeof(DataPack))));
}

IEnumerable<short> Unpack(DataPack dataPack)
{
    return new short[2] { dataPack.X, dataPack.Y };
}

IEnumerable<short> ReadData(BinaryReader reader, int ch, int count)
{
    foreach (var dataPack in ReadDataPacks(reader, count))
        yield return Unpack(dataPack).ToArray()[ch];
}

void Main()
{
    var ch1 = new short[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    var ch2 = ch1.Select(x => (short)(x * 1000)).ToArray();
    
    using (var memoryStream = new MemoryStream())
    using (var binaryWriter = new BinaryWriter(memoryStream))
    {
        for (int i = 0; i < ch1.Length; ++i)
        {
            binaryWriter.Write(ch1[i]);
            binaryWriter.Write(ch2[i]);
        }
        
        using (var binaryReader = new BinaryReader(memoryStream))
        {
            {
                memoryStream.Position = 0;
                var ch1Read = ReadData(binaryReader, 0, ch1.Length);

                memoryStream.Position = 0;
                var ch2Read = ReadData(binaryReader, 1, ch1.Length);
            
                var ch3 = ch1Read.Zip(ch2Read, (i, ii) => (short)(ii - i));
            
                foreach (var data in ch3)
                    Console.WriteLine(data);
            }
            
            {
                memoryStream.Position = 0;
                var ch1Read = ReadData(binaryReader, 0, ch1.Length).ToArray();

                memoryStream.Position = 0;
                var ch2Read = ReadData(binaryReader, 1, ch1.Length).ToArray();
            
                var ch3 = ch1Read.Zip(ch2Read, (i, ii) => (short)(ii - i));
            
                foreach (var data in ch3)
                    Console.WriteLine(data);
            }           
        }
    }
}
