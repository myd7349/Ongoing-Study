namespace Common
{
    using System;

    using static ByteSwap;

    public class EndianUtility
    {
        public EndianUtility(bool isLittleEndian)
        {
            SameEndianess =
                (isLittleEndian && BitConverter.IsLittleEndian) ||
                (!isLittleEndian && !BitConverter.IsLittleEndian);

            if (SameEndianess)
            {
                convertI16_ = x => x;
                convertI32_ = x => x;
                convertI64_ = x => x;

                convertU16_ = x => x;
                convertU32_ = x => x;
                convertU64_ = x => x;
            }
            else
            {
                convertI16_ = SwapBytes;
                convertI32_ = SwapBytes;
                convertI64_ = SwapBytes;

                convertU16_ = SwapBytes;
                convertU32_ = SwapBytes;
                convertU64_ = SwapBytes;
            }
        }

        public bool SameEndianess
        {
            get;
            private set;
        }

        public Int16 Convert(Int16 x)
        {
            return convertI16_(x);
        }

        public Int32 Convert(Int32 x)
        {
            return convertI32_(x);
        }

        public Int64 Convert(Int64 x)
        {
            return convertI64_(x);
        }

        public UInt16 Convert(UInt16 x)
        {
            return convertU16_(x);
        }

        public UInt32 Convert(UInt32 x)
        {
            return convertU32_(x);
        }

        public UInt64 Convert(UInt64 x)
        {
            return convertU64_(x);
        }

        private Func<short, short> convertI16_;
        private Func<int, int> convertI32_;
        private Func<long, long> convertI64_;

        private Func<ushort, ushort> convertU16_;
        private Func<uint, uint> convertU32_;
        private Func<ulong, ulong> convertU64_;
    }
}
