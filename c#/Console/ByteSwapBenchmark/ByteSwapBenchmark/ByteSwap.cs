namespace Common
{
    using System;
    using System.Runtime.InteropServices;

    public static class ByteSwap
    {
        public static Int32 BytesSwap(Int32 x)
        {
            var bytes = BitConverter.GetBytes(x);
            Array.Reverse(bytes);
            return BitConverter.ToInt32(bytes, 0);
        }

        public static Int32 BytesSwapV2(Int32 x)
        {
            return (Int32)BytesSwapV2((UInt32)x);
        }

        public static UInt32 BytesSwapV2(UInt32 x)
        {
            return
                ((x & 0xff000000) >> 24) |
                ((x & 0x00ff0000) >> 8) |
                ((x & 0x0000ff00) << 8) |
                ((x & 0x000000ff) << 24)
                ;
        }

        [StructLayout(LayoutKind.Explicit)]
        internal struct UInt32Union
        {
            [FieldOffset(0)] public UInt32 Value;
            [FieldOffset(0)] public byte Byte1;
            [FieldOffset(1)] public byte Byte2;
            [FieldOffset(2)] public byte Byte3;
            [FieldOffset(3)] public byte Byte4;
        }

        public static Int32 BytesSwapV3(Int32 x)
        {
            return (Int32)BytesSwapV3((UInt32)x);
        }

        public static UInt32 BytesSwapV3(UInt32 value)
        {
            UInt32Union src = new UInt32Union();
            src.Value = value;

            UInt32Union dest = new UInt32Union
            {
                Byte1 = src.Byte4,
                Byte2 = src.Byte3,
                Byte3 = src.Byte2,
                Byte4 = src.Byte1
            };

            return dest.Value;
        }

        public static unsafe Int32 BytesSwapV4(Int32 x)
        {
            var pi = &x;
            var pb = (byte*)pi;

            var temp = *pb;
            *pb = *(pb + 3);
            *(pb + 3) = temp;

            temp = *(pb + 1);
            *(pb + 1) = *(pb + 2);
            *(pb + 2) = temp;

            return x;
        }

        [DllImport("msvcrt.dll", EntryPoint = "_byteswap_ulong", CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 byteswap_i32(Int32 value);
    }
}


// References:
// https://github.com/dotnet/coreclr/blob/5068bb8820ebd1820e70aea091bf56b19ae84f13/src/System.Private.CoreLib/shared/System/Buffers/Binary/Reader.cs#L24-L126
// https://stackoverflow.com/questions/19560436/bitwise-endian-swap-for-various-types
// https://stackoverflow.com/questions/5784365/how-to-reverse-the-order-of-a-byte-array-in-c
// https://stackoverflow.com/questions/1358747/fast-little-endian-to-big-endian-conversion-in-asm
// https://stackoverflow.com/questions/17251700/net-equivalent-of-byteswap-ulong-osswapint32-or-bswap32
// https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library/reference/byteswap-uint64-byteswap-ulong-byteswap-ushort.md
// https://social.msdn.microsoft.com/Forums/vstudio/en-US/c878e72e-d42e-417d-b4f6-1935ad96d8ae/converting-small-endian-to-big-endian-using-clong-value?forum=csharpgeneral
// https://stackoverflow.com/questions/19560436/bitwise-endian-swap-for-various-types
