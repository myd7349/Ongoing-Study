namespace Common
{
    using System;
    using System.Runtime.InteropServices;

    public static class ByteSwap
    {
        public static Int16 BytesSwap(Int16 x)
        {
            var bytes = BitConverter.GetBytes(x);
            Array.Reverse(bytes);
            return BitConverter.ToInt16(bytes, 0);
        }

        public static Int32 BytesSwap(Int32 x)
        {
            var bytes = BitConverter.GetBytes(x);
            Array.Reverse(bytes);
            return BitConverter.ToInt32(bytes, 0);
        }

        public static Int64 BytesSwap(Int64 x)
        {
            var bytes = BitConverter.GetBytes(x);
            Array.Reverse(bytes);
            return BitConverter.ToInt64(bytes, 0);
        }

        public static UInt16 BytesSwap(UInt16 x)
        {
            var bytes = BitConverter.GetBytes(x);
            Array.Reverse(bytes);
            return BitConverter.ToUInt16(bytes, 0);
        }

        public static UInt32 BytesSwap(UInt32 x)
        {
            var bytes = BitConverter.GetBytes(x);
            Array.Reverse(bytes);
            return BitConverter.ToUInt32(bytes, 0);
        }

        public static UInt64 BytesSwap(UInt64 x)
        {
            var bytes = BitConverter.GetBytes(x);
            Array.Reverse(bytes);
            return BitConverter.ToUInt64(bytes, 0);
        }

        public static short SwapBytes(short x)
        {
            return (short)SwapBytes((ushort)x);
        }

        public static int SwapBytes(int x)
        {
            return (int)SwapBytes((uint)x);
        }

        public static long SwapBytes(long x)
        {
            return (long)SwapBytes((ulong)x);
        }

        public static ushort SwapBytes(ushort x)
        {
            // swap adjacent 8-bit blocks
            return (ushort)((x >> 8) + (x << 8));
        }

        public static uint SwapBytes(uint x)
        {
            // swap adjacent 16-bit blocks
            x = (x >> 16) | (x << 16);
            // swap adjacent 8-bit blocks
            return ((x & 0xFF00FF00) >> 8) | ((x & 0x00FF00FF) << 8);
        }

        public static ulong SwapBytes(ulong x)
        {
            // swap adjacent 32-bit blocks
            x = (x >> 32) | (x << 32);
            // swap adjacent 16-bit blocks
            x = ((x & 0xFFFF0000FFFF0000) >> 16) | ((x & 0x0000FFFF0000FFFF) << 16);
            // swap adjacent 8-bit blocks
            return ((x & 0xFF00FF00FF00FF00) >> 8) | ((x & 0x00FF00FF00FF00FF) << 8);
        }

        [DllImport("msvcrt.dll", EntryPoint = "_byteswap_ushort", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern Int16 byteswap_i16(Int16 value);

        [DllImport("msvcrt.dll", EntryPoint = "_byteswap_ushort", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern UInt16 byteswap_u16(UInt16 value);

        [DllImport("msvcrt.dll", EntryPoint = "_byteswap_ulong", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern Int32 byteswap_i32(Int32 value);

        [DllImport("msvcrt.dll", EntryPoint = "_byteswap_ulong", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern UInt32 byteswap_u32(UInt32 value);

        [DllImport("msvcrt.dll", EntryPoint = "_byteswap_uint64", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern Int64 byteswap_i64(Int64 value);

        [DllImport("msvcrt.dll", EntryPoint = "_byteswap_uint64", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern UInt64 byteswap_u64(UInt64 value);
    }
}


// References:
// Ongoing-Study/c#/Console/ByteSwapBenchmark
// https://github.com/dotnet/coreclr/blob/5068bb8820ebd1820e70aea091bf56b19ae84f13/src/System.Private.CoreLib/shared/System/Buffers/Binary/Reader.cs#L24-L126
// https://stackoverflow.com/questions/19560436/bitwise-endian-swap-for-various-types
// https://stackoverflow.com/questions/5784365/how-to-reverse-the-order-of-a-byte-array-in-c
// https://stackoverflow.com/questions/1358747/fast-little-endian-to-big-endian-conversion-in-asm
// https://stackoverflow.com/questions/19560436/bitwise-endian-swap-for-various-types
// https://github.com/nemequ/portable-snippets/blob/77654dbc376e0465aaae096553eeb2e95a9f2735/builtin/builtin.h#L974-L980
// https://github.com/dbrant/imageformats/blob/master/ImageFormats/Util.cs
// https://github.com/ciniml/WireGuard-ESP32-Arduino/blob/main/src/crypto.h
// https://github.com/iOrange/QoiFileTypeNet/blob/b8d8f899400cd0edb999294e860a2aa6bd0cffd6/QoiFile.cs#L59-L64
