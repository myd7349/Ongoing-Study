namespace Common.IO
{
    using System;
    using System.IO;
    using System.Text;

    public class BinaryWriterBE : BinaryWriter
    {
        private readonly byte[] buffer_; // temp space for writing primitives to.

        public BinaryWriterBE(Stream output)
            : base(output)
        {
            buffer_ = new byte[16];
        }

        public BinaryWriterBE(Stream output, Encoding encoding)
            : base(output, encoding)
        {
            buffer_ = new byte[16];
        }

        public BinaryWriterBE(Stream output, Encoding encoding, bool leaveOpen)
            : base(output, encoding, leaveOpen)
        {
            buffer_ = new byte[16];
        }

        public override unsafe void Write(double value)
        {
            ulong tmpValue = *(ulong*)&value;
            buffer_[0] = (byte)(tmpValue >> 56);
            buffer_[1] = (byte)(tmpValue >> 48);
            buffer_[2] = (byte)(tmpValue >> 40);
            buffer_[3] = (byte)(tmpValue >> 32);
            buffer_[4] = (byte)(tmpValue >> 24);
            buffer_[5] = (byte)(tmpValue >> 16);
            buffer_[6] = (byte)(tmpValue >> 8);
            buffer_[7] = (byte)tmpValue;

            OutStream.Write(buffer_, 0, 8);
        }

        //public virtual void Write(decimal value)

        public override void Write(short value)
        {
            buffer_[0] = (byte)(value >> 8);
            buffer_[1] = (byte)value;

            OutStream.Write(buffer_, 0, 2);
        }

        public override void Write(ushort value)
        {
            buffer_[0] = (byte)(value >> 8);
            buffer_[1] = (byte)value;

            OutStream.Write(buffer_, 0, 2);
        }

        public override void Write(int value)
        {
            buffer_[0] = (byte)(value >> 24);
            buffer_[1] = (byte)(value >> 16);
            buffer_[2] = (byte)(value >> 8);
            buffer_[3] = (byte)value;

            OutStream.Write(buffer_, 0, 4);
        }

        public override void Write(uint value)
        {
            buffer_[0] = (byte)(value >> 24);
            buffer_[1] = (byte)(value >> 16);
            buffer_[2] = (byte)(value >> 8);
            buffer_[3] = (byte)value;

            OutStream.Write(buffer_, 0, 4);
        }

        public override void Write(long value)
        {
            buffer_[0] = (byte)(value >> 56);
            buffer_[1] = (byte)(value >> 48);
            buffer_[2] = (byte)(value >> 40);
            buffer_[3] = (byte)(value >> 32);
            buffer_[4] = (byte)(value >> 24);
            buffer_[5] = (byte)(value >> 16);
            buffer_[6] = (byte)(value >> 8);
            buffer_[7] = (byte)value;

            OutStream.Write(buffer_, 0, 8);
        }

        public override void Write(ulong value)
        {
            buffer_[0] = (byte)(value >> 56);
            buffer_[1] = (byte)(value >> 48);
            buffer_[2] = (byte)(value >> 40);
            buffer_[3] = (byte)(value >> 32);
            buffer_[4] = (byte)(value >> 24);
            buffer_[5] = (byte)(value >> 16);
            buffer_[6] = (byte)(value >> 8);
            buffer_[7] = (byte)value;

            OutStream.Write(buffer_, 0, 8);
        }

        public override unsafe void Write(float value)
        {
            uint tmpValue = *(uint*)&value;
            buffer_[0] = (byte)(tmpValue >> 24);
            buffer_[1] = (byte)(tmpValue >> 16);
            buffer_[2] = (byte)(tmpValue >> 8);
            buffer_[3] = (byte)tmpValue;

            OutStream.Write(buffer_, 0, 4);
        }
    }
}


// References:
// https://github.com/dotnet/corefx/blob/master/src/Common/src/CoreLib/System/IO/BinaryWriter.cs
// ./BinaryWriterEx.cs
// https://github.com/caryll/otfcc/blob/master/lib/support/bin-io.h
// https://sourceforge.net/projects/dicom-cs/files/dicom-cs/dicom-0_3_1/
// > org/dicomcs/util/BEBinaryReader.cs
// https://github.com/dbrant/imageformats/blob/master/ImageFormats/Util.cs
// https://github.com/mandreyel/endian/blob/master/endian.hpp
// https://github.com/tge-was-taken/Amicitia.IO
// https://github.com/MediaArea/ZenLib/blob/master/Source/ZenLib/BitStream_LE.h
// [BinaryPrimitives.ReadUInt32BigEndian](https://docs.microsoft.com/en-us/dotnet/api/system.buffers.binary.binaryprimitives.readuint32bigendian?view=net-6.0)
// [C# 大端小端转换](https://blog.lindexi.com/post/C-%E5%A4%A7%E7%AB%AF%E5%B0%8F%E7%AB%AF%E8%BD%AC%E6%8D%A2.html)
// https://github.com/dnSpy/dnSpy/blob/master/dnSpy/dnSpy/Hex/ByteArrayHexBufferStream.cs
