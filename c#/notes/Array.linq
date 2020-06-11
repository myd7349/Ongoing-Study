<Query Kind="Program">
  <Namespace>System</Namespace>
  <Namespace>System.Runtime.InteropServices</Namespace>
</Query>

[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
public unsafe struct DataPacket
{
    public fixed ushort Data[6];

    public static DataPacket FromBytes(byte[] bytes, int offset, int count)
    {
        Debug.Assert(sizeof(DataPacket) == 6 * sizeof(ushort));
        Debug.Assert(count == 6 * sizeof(ushort));
        Debug.Assert(offset + count <= bytes.Length);

        fixed (byte* pb = &bytes[offset])
        {
            return *(DataPacket *)pb;
        }
    }
}

unsafe void Main()
{
    var data = new int[] { 0, 1, 2, 3, 4 };
    for (int i = 5; i <= 10; ++i)
    {
        Console.WriteLine(data);
        Array.Copy(data, 1, data, 0, data.Length - 1);
        data[data.Length - 1] = i;
    }
    
    var rawData = new ushort[] { 1, 22, 333, 4444, 0xFFFF, 0xFEFF };
    var rawBytes = new byte[rawData.Length * sizeof(ushort)];
    Buffer.BlockCopy(rawData, 0, rawBytes, 0, rawBytes.Length);
    
    foreach (var b in rawBytes)
        Console.Write("{0:X} ", b);
    Console.WriteLine();
    
    var packet = DataPacket.FromBytes(rawBytes, 0, rawBytes.Length);
    
    var rawData2 = new short[rawData.Length];
    
    short *p = (short *)packet.Data;
    Marshal.Copy((IntPtr)p, rawData2, 0, rawData2.Length);

    foreach (var s in rawData2)
        Console.Write("{0:X} ", (ushort)s);
    Console.WriteLine();
}

// References:
// https://stackoverflow.com/questions/11149668/is-array-copy-safe-when-the-source-and-destination-are-the-same-array
// [Convert byte array to short array in C#](https://stackoverflow.com/questions/1104599/convert-byte-array-to-short-array-in-c-sharp)
// [C# — Create Managed Array from Pointer](https://stackoverflow.com/questions/1916189/c-sharp-create-managed-array-from-pointer)
// [Copy unmanaged data into managed array](https://stackoverflow.com/questions/6403005/copy-unmanaged-data-into-managed-array)
