namespace Common
{
    using System;
    using System.Runtime.InteropServices;

    public static class MarshalHelper
    {
        public static sbyte ReadSByte(IntPtr ptr)
        {
            byte[] bytes = new byte[1];
            Marshal.Copy(ptr, bytes, 0, 1);
            return Convert.ToSByte(bytes[0]);
        }

        public static ushort ReadUInt16(IntPtr ptr)
        {
            byte[] bytes = new byte[sizeof(ushort)];
            Marshal.Copy(ptr, bytes, 0, 2);
            return BitConverter.ToUInt16(bytes, 0);
        }

        public static uint ReadUInt32(IntPtr ptr)
        {
            byte[] bytes = new byte[sizeof(uint)];
            Marshal.Copy(ptr, bytes, 0, 4);
            return BitConverter.ToUInt32(bytes, 0);
        }

        public static ulong ReadUInt64(IntPtr ptr)
        {
            byte[] bytes = new byte[sizeof(ulong)];
            Marshal.Copy(ptr, bytes, 0, 8);
            return BitConverter.ToUInt64(bytes, 0);
        }

        public static void WriteSByte(IntPtr ptr, sbyte value)
        {
            var bytes = BitConverter.GetBytes(value);
            Marshal.Copy(bytes, 0, ptr, bytes.Length);
        }

        public static void WriteUInt16(IntPtr ptr, ushort value)
        {
            var bytes = BitConverter.GetBytes(value);
            Marshal.Copy(bytes, 0, ptr, bytes.Length);
        }

        public static void WriteUInt32(IntPtr ptr, uint value)
        {
            var bytes = BitConverter.GetBytes(value);
            Marshal.Copy(bytes, 0, ptr, bytes.Length);
        }

        public static void WriteUInt64(IntPtr ptr, ulong value)
        {
            var bytes = BitConverter.GetBytes(value);
            Marshal.Copy(bytes, 0, ptr, bytes.Length);
        }
    }
}


// References:
// [Getting an IntPtr to a ulong variable in C#](https://stackoverflow.com/questions/689975/getting-an-intptr-to-a-ulong-variable-in-c-sharp)
// [How to find out if a numeric type is signed or unsigned in C#](https://stackoverflow.com/questions/53300136/how-to-find-out-if-a-numeric-type-is-signed-or-unsigned-in-c-sharp)
// [How to parse long.MaxValue and ulong.MaxValue when doing conversion](https://stackoverflow.com/questions/58618701/how-to-parse-long-maxvalue-and-ulong-maxvalue-when-doing-conversion)
