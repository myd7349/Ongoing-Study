#define ENABLE_UNSAFE

namespace Common
{
    using System;
    using System.Runtime.InteropServices;

    public static class StructHelpers
    {
        public static TStruct BytesToStruct<TStruct>(byte[] bytes, int offset = 0) where TStruct : struct
        {
            if (bytes == null)
                throw new ArgumentNullException("bytes");

            if (offset < 0 || offset >= bytes.Length)
                throw new ArgumentOutOfRangeException("offset");

            var required = Marshal.SizeOf<TStruct>();
            if (offset + required > bytes.Length)
                throw new ArgumentException("Buffer size is too small to hold an instance of this structure.");

#if ENABLE_UNSAFE
            unsafe
            {
                fixed (byte *buffer = bytes)
                {
                    return Marshal.PtrToStructure<TStruct>((IntPtr)(buffer + offset));
                }
            }
#else
            if (offset == 0)
            {
                GCHandle handle = GCHandle.Alloc(bytes, GCHandleType.Pinned);
                TStruct structure = (TStruct)Marshal.PtrToStructure(handle.AddrOfPinnedObject(), typeof(TStruct));
                handle.Free();

                return structure;
            }
            else
            {
                var size = Marshal.SizeOf<TStruct>();
                var ptr = Marshal.AllocHGlobal(size);
                Marshal.Copy(bytes, offset, ptr, size);
                TStruct structure = (TStruct)Marshal.PtrToStructure(ptr, typeof(TStruct));
                Marshal.FreeHGlobal(ptr);

                return structure;
            }
#endif
        }

        public static byte[] StructToBytes<TStruct>(TStruct value) where TStruct : struct
        {
            var size = Marshal.SizeOf<TStruct>();
            var bytes = new byte[size];

#if ENABLE_UNSAFE
            unsafe
            {
                fixed (byte* buffer = bytes)
                {
                    Marshal.StructureToPtr(value, (IntPtr)buffer, false);
                }
            }
#else
            var ptr = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(value, ptr, true);
            Marshal.Copy(ptr, bytes, 0, size);
            Marshal.FreeHGlobal(ptr);
#endif

            return bytes;
        }

        public static void StructToBytes<TStruct>(TStruct value, byte[] bytes, int offset = 0) where TStruct : struct
        {
            if (bytes == null)
                throw new ArgumentNullException("bytes");

            if (offset < 0 || offset >= bytes.Length)
                throw new ArgumentOutOfRangeException("offset");

            var required = Marshal.SizeOf<TStruct>();
            if (offset + required > bytes.Length)
                throw new ArgumentException("Buffer size is too small to hold an instance of this structure.");

            unsafe
            {
                fixed (byte* buffer = bytes)
                {
                    Marshal.StructureToPtr(value, (IntPtr)(buffer + offset), false);
                }
            }
        }
    }
}

// References:
// Ongoing-Study/C#/notes/ReadBytesIntoAStruct.linq
// https://stackoverflow.com/questions/3278827/how-to-convert-a-structure-to-a-byte-array-in-c
// https://stackoverflow.com/questions/7030150/copying-byte-array-to-various-fields-in-class-struct-in-c-sharp
// https://github.com/dorssel/usbipd-win/blob/839d4dcfc841623284e106ba3de877e84a04fe49/UsbIpServer/Tools.cs#L62-L105
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
