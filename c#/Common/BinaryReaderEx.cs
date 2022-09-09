namespace Common.IO
{
    using System;
    using System.IO;
    using System.Text;

    public class BinaryReaderEx : BinaryReader
    {
        public BinaryReaderEx(Stream input, bool isLittleEndian = true)
            : base(input)
        {
            IsLittleEndian = isLittleEndian;
        }

        public BinaryReaderEx(Stream input, Encoding encoding, bool isLittleEndian = true)
            : base(input, encoding)
        {
            IsLittleEndian = isLittleEndian;
        }

        public BinaryReaderEx(Stream input, Encoding encoding, bool leaveOpen, bool isLittleEndian = true)
            : base(input, encoding, leaveOpen)
        {
            IsLittleEndian = isLittleEndian;
        }

        public bool IsLittleEndian
        {
            get;
            private set;
        }

        public override short ReadInt16()
        {
            var value = base.ReadInt16();
            return IsLittleEndian ? value : ByteSwap.SwapBytes(value);
        }

        public override ushort ReadUInt16()
        {
            var value = base.ReadUInt16();
            return IsLittleEndian ? value : ByteSwap.SwapBytes(value);
        }

        public override int ReadInt32()
        {
            var value = base.ReadInt32();
            return IsLittleEndian ? value : ByteSwap.SwapBytes(value);
        }

        public override uint ReadUInt32()
        {
            var value = base.ReadUInt32();
            return IsLittleEndian ? value : ByteSwap.SwapBytes(value);
        }

        public override long ReadInt64()
        {
            var value = base.ReadInt64();
            return IsLittleEndian ? value : ByteSwap.SwapBytes(value);
        }

        public override ulong ReadUInt64()
        {
            var value = base.ReadUInt64();
            return IsLittleEndian ? value : ByteSwap.SwapBytes(value);
        }

        public override unsafe float ReadSingle()
        {
            var value = ReadInt32();
            return *(float*)&value; // BitConverter.Int32BitsToSingle
        }

        public override unsafe double ReadDouble()
        {
            return BitConverter.Int64BitsToDouble(ReadInt64());
        }
    }
}


// References:
// https://github.com/dotnet/coreclr/blob/master/src/System.Private.CoreLib/shared/System/IO/BinaryReader.cs
// https://github.com/dotnet/coreclr/blob/master/tests/src/JIT/Intrinsics/BinaryPrimitivesReverseEndianness.cs
// https://github.com/dotnet/coreclr/blob/master/src/System.Private.CoreLib/shared/System/Buffers/Binary/ReaderBigEndian.cs
// https://github.com/dotnet/coreclr/blob/master/src/System.Private.CoreLib/shared/System/Buffers/Binary/ReaderLittleEndian.cs
// https://github.com/dotnet/coreclr/blob/master/src/System.Private.CoreLib/shared/System/Buffers/Binary/WriterBigEndian.cs
// https://github.com/dotnet/coreclr/blob/master/src/System.Private.CoreLib/shared/System/Buffers/Binary/WriterLittleEndian.cs
// https://github.com/dotnet/coreclr/blob/5068bb8820ebd1820e70aea091bf56b19ae84f13/src/System.Private.CoreLib/shared/System/Buffers/Binary/Reader.cs#L24-L126
// https://sourceforge.net/projects/dicom-cs/files/dicom-cs/dicom-0_3_1/
// > org/dicomcs/util/BEBinaryReader.cs
// https://github.com/ddiakopoulos/tinyply/blob/ca7b279fb6c9af931ffdaed96a3b11ca3ccd79ea/source/tinyply.h#L195-L213
// https://github.com/dbrant/imageformats/blob/master/ImageFormats/Util.cs
// https://github.com/mandreyel/endian/blob/master/endian.hpp
// https://github.com/tge-was-taken/Amicitia.IO
// https://github.com/MediaArea/ZenLib/blob/master/Source/ZenLib/BitStream.h
// https://github.com/aybe/BinaryExtensions/blob/develop/BinaryExtensions/BinaryExtensions/EndiannessExtensions.g.cs
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.Reflection.Metadata/src/System/Reflection/PortableExecutable/PEBinaryReader.cs
// https://github.com/mikeobrien/TDMSReader/blob/master/src/TDMSReader/BinaryReaderExtensions.cs
