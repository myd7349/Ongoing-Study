namespace Common
{
    using System.Runtime.InteropServices;

    public static class StructHelpers
    {
        public static TStruct BytesToStruct<TStruct>(byte[] bytes) where TStruct : struct
        {
            GCHandle handle = GCHandle.Alloc(bytes, GCHandleType.Pinned);
            TStruct structure = (TStruct)Marshal.PtrToStructure(handle.AddrOfPinnedObject(), typeof(TStruct));
            handle.Free();

            return structure;
        }

        public static byte[] StructToBytes<TStruct>(TStruct value) where TStruct : struct
        {
            var size = Marshal.SizeOf(value);
            var bytes = new byte[size];

            var ptr = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(value, ptr, true);
            Marshal.Copy(ptr, bytes, 0, size);
            Marshal.FreeHGlobal(ptr);

            return bytes;
        }
    }
}

// References:
// Ongoing-Study/C#/notes/ReadBytesIntoAStruct.linq
// https://stackoverflow.com/questions/3278827/how-to-convert-a-structure-to-a-byte-array-in-c
// https://stackoverflow.com/questions/7030150/copying-byte-array-to-various-fields-in-class-struct-in-c-sharp
/*
unsafe struct ExampleClass
{
   public ulong field1;
   public uint field2
   public ushort field3
   public fixed byte field4[18];

   public static ExampleClass ReadStruct(byte[] data)
   {
       fixed (byte* pb = &data[0])
       {
           return *(ExampleClass*)pb;
       }
   }
}
*/
