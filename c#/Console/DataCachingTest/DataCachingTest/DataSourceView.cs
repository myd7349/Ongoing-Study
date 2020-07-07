namespace DataCachingTest
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;

    public class DataSourceView
    {
        public DataSourceView(int cacheSizeFactor = 10)
        {
            Debug.Assert(cacheSizeFactor >= 1);
            cacheSizeFactor_ = cacheSizeFactor;
        }

        public DataSource DataSource
        {
            get
            {
                return dataSource_;
            }

            set
            {
                if (dataSource_ == value)
                    return;

                dataSource_ = value;
            }
        }

        public IEnumerable<int> Read(int start, int count)
        {
            if (DataSource == null)
                return new int[0];

            if (start < 0 || count < 0)
                throw new ArgumentOutOfRangeException();

            count = Math.Min(count, DataSource.Length - start);

            if (start >= DataSource.Length || count == 0)
                return new int[0];

            if (UpdateDataCache(start, count))
            {
                Debug.WriteLine("Expected data range: [{0}, {1}), data cache range: [{2}, {3})",
                    start, start + count, cachedDataStartPosition_, cachedDataStartPosition_ + cachedData_.Length);
                return cachedData_.Skip(start - cachedDataStartPosition_).Take(count);
            }
            else
            {
                throw new ApplicationException("Failed to update data cache.");
            }
        }

        public int[] CachedData => cachedData_;

        public int CachedDataStartPosition => cachedDataStartPosition_;

        private bool UpdateDataCache(int start, int count)
        {
            Debug.Assert(DataSource != null);

            if (cachedData_ == null || count > cachedData_.Length)
            {
                int cachedDataLength = Math.Min(count * cacheSizeFactor_, DataSource.Length);

                try
                {
                    cachedData_ = new int[cachedDataLength];

                    cachedDataStartPosition_ = -1;
                }
                catch (OutOfMemoryException)
                {
                    cachedData_ = null;
                    return false;
                }
            }

            if (cachedDataStartPosition_ != -1 &&
                start >= cachedDataStartPosition_ &&
                start + count <= cachedDataStartPosition_ + cachedData_.Length)
                return true;

            if (cachedDataStartPosition_ == -1 ||
                start + count <= cachedDataStartPosition_ ||
                start >= cachedDataStartPosition_ + cachedData_.Length)
            {
                if (start + cachedData_.Length > DataSource.Length)
                    start = DataSource.Length - cachedData_.Length;

                DataSource.Position = start;

                int position = 0;
                foreach (var data in DataSource.Read(cachedData_.Length))
                    cachedData_[position++] = data;

                cachedDataStartPosition_ = start;
                return true;
            }
            else
            {
                if (start < cachedDataStartPosition_)
                {
                    Debug.Assert(start + count > cachedDataStartPosition_);

                    int freshDataPackToRead = cachedDataStartPosition_ - start;

                    Array.Copy(
                        cachedData_, 0,
                        cachedData_, freshDataPackToRead,
                        cachedData_.Length - freshDataPackToRead);

                    DataSource.Position = start;

                    int position = 0;
                    foreach (var data in DataSource.Read(freshDataPackToRead))
                        cachedData_[position++] = data;

                    cachedDataStartPosition_ = start;
                }
                else
                {
                    Debug.Assert(start < cachedDataStartPosition_ + cachedData_.Length);

                    int freshDataPackToRead = (start + count) - (cachedDataStartPosition_ + cachedData_.Length);
                    Debug.Assert(freshDataPackToRead > 0);

                    Array.Copy(
                        cachedData_, freshDataPackToRead,
                        cachedData_, 0,
                        cachedData_.Length - freshDataPackToRead);

                    DataSource.Position = cachedDataStartPosition_ + cachedData_.Length;

                    int position = cachedData_.Length - freshDataPackToRead;
                    foreach (var data in DataSource.Read(freshDataPackToRead))
                        cachedData_[position++] = data;

                    cachedDataStartPosition_ += freshDataPackToRead;
                }
            }

            return true;
        }

        private DataSource dataSource_;
        private readonly int cacheSizeFactor_;
        private int[] cachedData_;
        private int cachedDataStartPosition_ = -1;
    }
}
