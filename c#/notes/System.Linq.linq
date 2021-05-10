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

// [Get indexes of all matching values from list using Linq](https://stackoverflow.com/questions/13055391/get-indexes-of-all-matching-values-from-list-using-linq)
void FindAllOnesV1()
{
    var result = new int[] { 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 };
    var indices = Enumerable.Range(0, result.Length)
        .Where(i => result[i] == 1).ToArray();

    Console.Write("Indices: ");
    foreach (var i in indices)
        Console.Write("{0} ", i);
    Console.Write('\n');
}

// [LINQ to find array indexes of a value](https://stackoverflow.com/questions/13291788/linq-to-find-array-indexes-of-a-value)
void FindAllOnesV2()
{
    var result = new int[] { 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 };
    var indices = result.Select((r, i) => new {i, r})
        .Where(t => t.r == 1)
        .Select(t => t.i);

    Console.Write("Indices: ");
    foreach (var i in indices)
        Console.Write("{0} ", i);
    Console.Write('\n');
}

void CastTest()
{
    var range = Enumerable.Range(0, 10);
    Console.WriteLine("{0}", range.ToArray());

    try
    {
        var numbers = range.Cast<ulong>().ToArray();
        Console.WriteLine("{0}", numbers);
    }
    catch (Exception ex)
    {
        Console.WriteLine("{0}", ex);

        var numbers = range.Select(num => (ulong)num).ToArray();
        Console.WriteLine("{0}", numbers);

        var numbers2 = range.ToList().ConvertAll(num => (ulong)num);
        Console.WriteLine("{0}", numbers2);
    }
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

    FindAllOnesV1();
    FindAllOnesV2();

    CastTest();
}


// References:
// [Using linq what is the easiest way to conv list<long> to list<int>?](https://stackoverflow.com/questions/2743819/using-linq-what-is-the-easiest-way-to-conv-listlong-to-listint/2743846)
// [LINQ .Cast() extension method fails but (type)object works](https://stackoverflow.com/questions/2819473/linq-cast-extension-method-fails-but-typeobject-works)
