<Query Kind="Program">
  <Namespace>System.Runtime.InteropServices</Namespace>
</Query>

void Main()
{
    Console.WriteLine(Marshal.SizeOf(typeof(DataV1)));
    Console.WriteLine(Marshal.SizeOf(typeof(DataV2)));
}

unsafe struct DataV1
{
    public fixed byte Data[3];
}

struct DataV2
{
    public byte B1;
    public byte B2;
    public byte B3;
}
