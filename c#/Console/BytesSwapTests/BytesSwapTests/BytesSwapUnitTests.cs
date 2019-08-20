namespace BytesSwapTests
{
    using System;

    using NUnit.Framework;

    using static Common.ByteSwap;
    using static Common.RandomExtension;

    [TestFixture]
    public class BytesSwapUnitTests
    {
        private const int Count = 1000000;
        private Random rand_;

        [SetUp]
        protected void SetUp()
        {
            rand_ = new Random();
        }

        [Test]
        public void TestSwapBytesI16()
        {
            for (short i = short.MinValue; i < short.MaxValue; ++i)
                Assert.AreEqual(BytesSwap(i), SwapBytes(i));
        }

        [Test]
        public void TestSwapBytesI32()
        {
            for (int i = 0; i < Count; ++i)
            {
                var num = rand_.Next(int.MinValue, int.MaxValue);
                Assert.AreEqual(BytesSwap(num), SwapBytes(num));
            }
        }

        [Test]
        public void TestSwapBytesI64()
        {
            for (int i = 0; i < Count; ++i)
            {
                var num = rand_.RandomLong();
                Assert.AreEqual(BytesSwap(num), SwapBytes(num));
            }
        }

        [Test]
        public void TestSwapBytesU16()
        {
            for (ushort i = ushort.MinValue; i < ushort.MaxValue; ++i)
                Assert.AreEqual(BytesSwap(i), SwapBytes(i));
        }

        [Test]
        public void TestSwapBytesU32()
        {
            for (int i = 0; i < Count; ++i)
            {
                var num = (uint)rand_.Next(int.MinValue, int.MaxValue);
                Assert.AreEqual(BytesSwap(num), SwapBytes(num));
            }
        }

        [Test]
        public void TestSwapBytesU64()
        {
            for (int i = 0; i < Count; ++i)
            {
                var num = rand_.RandomULong();
                Assert.AreEqual(BytesSwap(num), SwapBytes(num));
            }
        }
    }
}
