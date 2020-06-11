namespace DataCachingTest
{
    using System.Collections.Generic;
    using System.Linq;

    public class DataSource
    {
        public DataSource()
        {
            dataSource_ = Enumerable.Range(0, Length).ToArray();
        }

        public int Length => 270000;

        public int Position { get; set; }

        public virtual IEnumerable<int> Read(int dataPackCount)
        {
            while (dataPackCount-- > 0 && Position < Length)
                yield return dataSource_[Position++];
        }

        private int[] dataSource_;
    }
}
