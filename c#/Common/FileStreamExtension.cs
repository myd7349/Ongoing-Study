namespace Common.IO
{
    using System;
    using System.IO;
    using System.Runtime.InteropServices;

    public static class FileStreamExtension
    {
        public static T Read<T>(this FileStream stream, Func<byte[], T> converter) where T : struct
        {
            if (buffer_ == null || buffer_.Length < Marshal.SizeOf(typeof(T)))
                buffer_ = new byte[Marshal.SizeOf(typeof(T))];

            if (stream.Read(buffer_, 0, Marshal.SizeOf(typeof(T))) != Marshal.SizeOf(typeof(T)))
                throw new EndOfStreamException("No enough bytes");

            return converter(buffer_);
        }

        public static short ReadInt16(this FileStream stream, bool isLittleEndian)
        {
            return stream.Read(bytes => BitConverterEx.ToInt16(bytes, 0, isLittleEndian));
        }

        public static ushort ReadUInt16(this FileStream stream, bool isLittleEndian)
        {
            return stream.Read(bytes => BitConverterEx.ToUInt16(bytes, 0, isLittleEndian));
        }

        public static int ReadInt32(this FileStream stream, bool isLittleEndian)
        {
            return stream.Read(bytes => BitConverterEx.ToInt32(bytes, 0, isLittleEndian));
        }

        public static uint ReadUInt32(this FileStream stream, bool isLittleEndian)
        {
            return stream.Read(bytes => BitConverterEx.ToUInt32(bytes, 0, isLittleEndian));
        }

        public static long ReadInt64(this FileStream stream, bool isLittleEndian)
        {
            return stream.Read(bytes => BitConverterEx.ToInt64(bytes, 0, isLittleEndian));
        }

        public static ulong ReadUInt64(this FileStream stream, bool isLittleEndian)
        {
            return stream.Read(bytes => BitConverterEx.ToUInt64(bytes, 0, isLittleEndian));
        }

        public static unsafe float ReadSingle(this FileStream stream, bool isLittleEndian)
        {
            var value = stream.Read(bytes => BitConverterEx.ToInt32(bytes, 0, isLittleEndian));
            return *(float*)&value;
        }

        public static double ReadDouble(this FileStream stream, bool isLittleEndian)
        {
            return BitConverter.Int64BitsToDouble(stream.Read(bytes => BitConverterEx.ToInt64(bytes, 0, isLittleEndian)));
        }

        private static byte[] buffer_;
    }
}


// References:
// https://github.com/dnSpy/dnSpy/blob/master/dnSpy/dnSpy/Hex/ByteArrayHexBufferStream.cs
