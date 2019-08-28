namespace CircularBuffer.UnitTests
{
    using System;

    using NUnit.Framework;

    using Common;
    using Common.Collections.Generic;

    [TestFixture]
    public class CircularBufferUnitTests 
    {
        private int[] array_ = new int[] { 1, 2, 3, 4, 5 };
        private CircularBuffer<int> buffer0_;
        private CircularBuffer<int> buffer1_;
        private CircularBuffer<int> buffer2_;

        [SetUp]
        protected void SetUp()
        {
            buffer1_ = new CircularBuffer<int>(array_.Length);
            buffer1_.AddMany(new int[] { 1, 2, 3, 4 }, 0, 4);
            buffer1_.Remove();
        }

        [Test]
        public void TestNew()
        {
            Assert.That(() => new CircularBuffer<int>(-1), Throws.ArgumentException);
            Assert.That(() => new CircularBuffer<int>(0), Throws.ArgumentException);
        }

        [Test]
        public void TestIsReadOnly()
        {
            var buffer = new CircularBuffer<int>(10);
            Assert.IsFalse(buffer.IsReadOnly);
        }

        [Test]
        public void TestCount()
        {
            var buffer = new CircularBuffer<int>(10);
            Assert.IsTrue(buffer.Capacity == 10);
            Assert.IsTrue(buffer.Count == 0);
            Assert.IsTrue(buffer.IsEmpty);

            buffer.Add(1);
            Assert.AreEqual(buffer.Count, 1);

            var array = new int[] { 1, 2, 3 };
            buffer.AddMany(array, 0, array.Length);
            Assert.AreEqual(buffer.Count, 4);
        }

        [Test]
        public void TestAdd()
        {
            var buffer = new CircularBuffer<int>(5);
            buffer.Add(1);
            buffer.Add(2);

            var array = new int[] { 3, 4, 5 };
            buffer.AddMany(array, 0, array.Length);

            for (int i = 0; i < buffer.Count; ++i)
                Assert.AreEqual(buffer[i], i + 1);

            Assert.That(() => buffer.Add(100), Throws.InvalidOperationException);

            buffer.Remove();
            buffer.Add(100);
            Assert.AreEqual(buffer[buffer.Count - 1], 100);
        }

        [Test]
        public void TestClear()
        {
            var buffer = new CircularBuffer<int>(3);
            Assert.IsTrue(buffer.IsEmpty);
            buffer.Add(100);
            Assert.IsFalse(buffer.IsEmpty);
            buffer.Clear();
            Assert.IsTrue(buffer.IsEmpty);
        }

        [Test]
        public void TestContains()
        {
            var buffer = new CircularBuffer<int>(3);

            Assert.IsFalse(buffer.Contains(1));

            buffer.Add(1);
            Assert.IsTrue(buffer.Contains(1));
            Assert.IsFalse(buffer.Contains(2));

            buffer.Remove();
            Assert.IsFalse(buffer.Contains(1));

            buffer.Add(1);
            buffer.Add(2);
            buffer.Add(3);

            Assert.IsTrue(buffer.Contains(1));

            buffer.Remove();

            Assert.IsFalse(buffer.Contains(1));

            Assert.IsTrue(buffer.Contains(2));
            Assert.IsTrue(buffer.Contains(3));

            buffer.Add(4);

            Assert.IsTrue(buffer.Contains(4));
        }

        [Test]
        public void TestCopyTo()
        {
            var buffer = new CircularBuffer<int>(5);

            Assert.That(() => buffer.CopyTo(null, 0), Throws.ArgumentNullException);

            Assert.That(() => buffer[0], Throws.TypeOf<IndexOutOfRangeException>());

            var array = new int[] { 1, 2, 3, 4, 5 };
            buffer.AddMany(array, 1, array.Length);

            Assert.AreEqual(buffer[0], 2);
            Assert.AreEqual(buffer[1], 3);
            Assert.AreEqual(buffer[2], 4);
            Assert.AreEqual(buffer[3], 5);

            Assert.That(() => buffer[4], Throws.TypeOf<IndexOutOfRangeException>());

            int[] array2 = new int[buffer.Count - 1];

            Assert.That(() => buffer.CopyTo(array2, -1), Throws.TypeOf<ArgumentOutOfRangeException>());
            Assert.That(() => buffer.CopyTo(array2, 0), Throws.ArgumentException);

            array2 = new int[buffer.Count];
            buffer.CopyTo(array2, 0);
            Assert.IsTrue(array2.EqualTo(new int[] { 2, 3, 4, 5 }));

            buffer.Clear();
            buffer.CopyTo(array2, 0);

            buffer.AddMany(array, 0, array.Length);
            buffer.Remove();
            buffer.Remove();
            buffer.Remove();
            buffer.Add(6);
            buffer.Add(7);

            buffer.CopyTo(array2, 0);
            Assert.IsTrue(array2.EqualTo(new int[] { 4, 5, 6, 7 }));
        }
    }
}


// References:
// https://github.com/nunit/nunit-csharp-samples
