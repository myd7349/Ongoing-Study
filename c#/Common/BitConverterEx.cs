namespace Common
{
    using System;

    public static class BitConverterEx
    {
        public static byte[] GetBytes(short value, bool tolittleEndian)
        {
            var bytes = BitConverter.GetBytes(value);
            if (!HasSameEndianness(tolittleEndian))
                Array.Reverse(bytes);
            return bytes;
        }
     
        public static byte[] GetBytes(int value, bool tolittleEndian)
        {
            var bytes = BitConverter.GetBytes(value);
            if (!HasSameEndianness(tolittleEndian))
                Array.Reverse(bytes);
            return bytes;
        }
        
        public static byte[] GetBytes(long value, bool tolittleEndian)
        {
            var bytes = BitConverter.GetBytes(value);
            if (!HasSameEndianness(tolittleEndian))
                Array.Reverse(bytes);
            return bytes;
        }
        
        public static byte[] GetBytes(ushort value, bool tolittleEndian)
        {
            var bytes = BitConverter.GetBytes(value);
            if (!HasSameEndianness(tolittleEndian))
                Array.Reverse(bytes);
            return bytes;
        }
        
        public static byte[] GetBytes(uint value, bool tolittleEndian)
        {
            var bytes = BitConverter.GetBytes(value);
            if (!HasSameEndianness(tolittleEndian))
                Array.Reverse(bytes);
            return bytes;
        }
        
        public static byte[] GetBytes(ulong value, bool tolittleEndian)
        {
            var bytes = BitConverter.GetBytes(value);
            if (!HasSameEndianness(tolittleEndian))
                Array.Reverse(bytes);
            return bytes;
        }
        
        public static byte[] GetBytes(float value, bool tolittleEndian)
        {
            var bytes = BitConverter.GetBytes(value);
            if (!HasSameEndianness(tolittleEndian))
                Array.Reverse(bytes);
            return bytes;
        }
        
        public static byte[] GetBytes(double value, bool tolittleEndian)
        {
            var bytes = BitConverter.GetBytes(value);
            if (!HasSameEndianness(tolittleEndian))
                Array.Reverse(bytes);
            return bytes;
        }
        
        public static short ToInt16(byte[] bytes, int startIndex, bool isLittleEndian)
        {
            var value = BitConverter.ToInt16(bytes, startIndex);
            if (!HasSameEndianness(isLittleEndian))
                value = ByteSwap.SwapBytes(value);
            return value;
        }

        public static int ToInt32(byte[] bytes, int startIndex, bool isLittleEndian)
        {
            var value = BitConverter.ToInt32(bytes, startIndex);
            if (!HasSameEndianness(isLittleEndian))
                value = ByteSwap.SwapBytes(value);
            return value;
        }
        
        public static long ToInt64(byte[] bytes, int startIndex, bool isLittleEndian)
        {
            var value = BitConverter.ToInt64(bytes, startIndex);
            if (!HasSameEndianness(isLittleEndian))
                value = ByteSwap.SwapBytes(value);
            return value;
        }
        
        public static ushort ToUInt16(byte[] bytes, int startIndex, bool isLittleEndian) => unchecked((ushort)ToInt16(bytes, startIndex, isLittleEndian));
        
        public static uint ToUInt32(byte[] bytes, int startIndex, bool isLittleEndian) => unchecked((uint)ToInt32(bytes, startIndex, isLittleEndian));
        
        public static ulong ToUInt64(byte[] bytes, int startIndex, bool isLittleEndian) => unchecked((ulong)ToInt64(bytes, startIndex, isLittleEndian));
        
        public static float ToSingle(byte[] bytes, int startIndex, bool isLittleEndian) => Int32BitsToSingle(ToInt32(bytes, startIndex, isLittleEndian));
        
        public static double ToDouble(byte[] bytes, int startIndex, bool isLittleEndian) => BitConverter.Int64BitsToDouble(ToInt64(bytes, startIndex, isLittleEndian));

        public static unsafe int SingleToInt32Bits(float value)
        {
            return *((int*)&value);
        }

        public static unsafe float Int32BitsToSingle(int value)
        {
            return *((float*)&value);
        }

        private static bool HasSameEndianness(bool isLittleEndian)
        {
            return (BitConverter.IsLittleEndian && isLittleEndian)
                || (!BitConverter.IsLittleEndian && !isLittleEndian);
        }
    }
}


// References:
// https://github.com/dotnet/coreclr/blob/master/src/System.Private.CoreLib/shared/System/BitConverter.cs
// https://github.com/dbrant/imageformats/blob/master/ImageFormats/Util.cs
// https://github.com/jk-jeon/fp
// https://github.com/abolz/Drachennest
