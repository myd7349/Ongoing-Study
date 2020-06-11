namespace DataCachingTest
{
    using System;
    using System.Linq;
    using NUnit.Framework;

    [TestFixture]
    public class DataCachingUnitTest
    {
        [SetUp]
        protected void SetUp()
        {
            random_ = new Random();

            var cacheSizeFactor = random_.Next(1, 10);

            count_ = 10890; // random_.Next(100, 20000);

            dataSourceView_ = new DataSourceView(cacheSizeFactor)
            {
                DataSource = new DataSource()
            };
        }

        [Test]
        public void TestMoveForward()
        {
            for (var i = 0; i < 1000; ++i)
            {
                var data = dataSourceView_.Read(i * count_, count_).ToArray();

                for (var j = 0; j < dataSourceView_.CachedData.Length; ++j)
                    Assert.AreEqual(dataSourceView_.CachedData[j], dataSourceView_.CachedDataStartPosition + j);

                for (var j = 0; j < data.Length; ++j)
                    Assert.AreEqual(data[j], i * count_ + j);
            }
        }

        [Test]
        public void TestRandomly()
        {
            var positions = Enumerable.Range(100, 1000).Select(i => random_.Next(0, dataSourceView_.DataSource.Length)).ToArray();
            for (var i = 0; i < positions.Length; ++i)
            {
                var data = dataSourceView_.Read(positions[i], count_).ToArray();

                for (var j = 0; j < dataSourceView_.CachedData.Length; ++j)
                    Assert.AreEqual(dataSourceView_.CachedData[j], dataSourceView_.CachedDataStartPosition + j);

                for (var j = 0; j < data.Length; ++j)
                    Assert.AreEqual(data[j], positions[i] + j);
            }
        }

        private Random random_;
        private int count_;
        private DataSourceView dataSourceView_;
    }
}
