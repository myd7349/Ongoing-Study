namespace Common.IO
{
    using System;
    using System.IO;
    using System.Text;

    public class BinaryWriterEx : BinaryWriter
    {
        private readonly byte[] buffer_; // temp space for writing primitives to.

        public BinaryWriterEx(Stream output, bool isLittleEndian = true)
            : base(output)
        {
            buffer_ = new byte[16];
            IsLittleEndian = isLittleEndian;
        }

        public BinaryWriterEx(Stream output, Encoding encoding, bool isLittleEndian = true)
            : base(output, encoding)
        {
            buffer_ = new byte[16];
            IsLittleEndian = isLittleEndian;
        }

        public BinaryWriterEx(Stream output, Encoding encoding, bool leaveOpen, bool isLittleEndian = true)
            : base(output, encoding, leaveOpen)
        {
            buffer_ = new byte[16];
            IsLittleEndian = isLittleEndian;
        }

        public bool IsLittleEndian
        {
            get;
            private set;
        }

        public override unsafe void Write(double value)
        {
            // BitConverter.DoubleToInt64Bits:
            // return *((long*)&value);
            //
            if (!IsLittleEndian)
                value = BitConverter.Int64BitsToDouble(ByteSwap.SwapBytes(BitConverter.DoubleToInt64Bits(value)));

            base.Write(value);
        }

        //public virtual void Write(decimal value)

        public override void Write(short value)
        {
            if (!IsLittleEndian)
                value = ByteSwap.SwapBytes(value);

            base.Write(value);
        }

        public override void Write(ushort value)
        {
            if (!IsLittleEndian)
                value = ByteSwap.SwapBytes(value);

            base.Write(value);
        }

        public override void Write(int value)
        {
            if (!IsLittleEndian)
                value = ByteSwap.SwapBytes(value);

            base.Write(value);
        }

        public override void Write(uint value)
        {
            if (!IsLittleEndian)
                value = ByteSwap.SwapBytes(value);

            base.Write(value);
        }

        public override void Write(long value)
        {
            if (!IsLittleEndian)
                value = ByteSwap.SwapBytes(value);

            base.Write(value);
        }

        public override void Write(ulong value)
        {
            if (!IsLittleEndian)
                value = ByteSwap.SwapBytes(value);

            base.Write(value);
        }

        public override unsafe void Write(float value)
        {
            if (!IsLittleEndian)
                value = *(float*)ByteSwap.SwapBytes(*(uint*)&value);

            base.Write(value);
        }
    }
}


// References:
// https://stackoverflow.com/questions/35909877/c-sharp-binarywriter-and-endianness
// > BinaryWriter stores this data type in little endian format.
// https://github.com/dotnet/corefx/blob/master/src/Common/src/CoreLib/System/IO/BinaryWriter.cs
// https://github.com/dotnet/corefx/blob/f66beeec1ab37a8ea8647caae8bb2ae901f01012/src/Common/src/CoreLib/System/IO/BinaryWriter.cs#L239-L251
// https://github.com/dotnet/corefx/blob/f66beeec1ab37a8ea8647caae8bb2ae901f01012/src/Common/src/CoreLib/System/BitConverter.cs#L451-L455
// https://github.com/dotnet/coreclr/blob/master/tests/src/JIT/Intrinsics/BinaryPrimitivesReverseEndianness.cs
// https://github.com/dotnet/coreclr/blob/master/src/System.Private.CoreLib/shared/System/Buffers/Binary/ReaderBigEndian.cs
// https://github.com/dotnet/coreclr/blob/master/src/System.Private.CoreLib/shared/System/Buffers/Binary/ReaderLittleEndian.cs
// https://github.com/dotnet/coreclr/blob/master/src/System.Private.CoreLib/shared/System/Buffers/Binary/WriterBigEndian.cs
// https://github.com/dotnet/coreclr/blob/master/src/System.Private.CoreLib/shared/System/Buffers/Binary/WriterLittleEndian.cs
// https://github.com/ddiakopoulos/tinyply/blob/ca7b279fb6c9af931ffdaed96a3b11ca3ccd79ea/source/tinyply.h#L195-L213
// [Struct.Pack Equivalent in C#](https://stackoverflow.com/questions/19337056/struct-pack-equivalent-in-c-sharp)
// https://github.com/loory/MiscUtil/blob/master/Conversion/LittleEndianBitConverter.cs
