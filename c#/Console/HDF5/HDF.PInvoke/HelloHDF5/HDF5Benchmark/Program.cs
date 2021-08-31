namespace HDF5Benchmark
{
    using System.IO;

    using BenchmarkDotNet.Attributes;
    using BenchmarkDotNet.Configs;
    using BenchmarkDotNet.Engines;
    using BenchmarkDotNet.Running;

    using HDF.PInvoke;

    using Common;
    using HDF5.Extension;

    using hid_t = System.Int64;
    using hsize_t = System.UInt64;

    [GroupBenchmarksBy(BenchmarkLogicalGroupRule.ByCategory)]
    [CategoriesColumn]
    [SimpleJob(RunStrategy.ColdStart, launchCount: 1, targetCount: 1000)]
    public class Benchmark
    {
        [GlobalSetup]
        public void Setup()
        {
            bytes_ = RandomExtension.RandomBytes(1024);

            file_ = new FileStream("HDF5Benchmark_FileIO.dat", FileMode.Create, FileAccess.ReadWrite);
            fileRows_ = 0;

            h5file_ = H5F.create("HDF5Benchmark_FileIO.h5", H5F.ACC_TRUNC);
            dataSet_ = HDF5Helper.CreateDataSet(h5file_, "data", H5T.NATIVE_UINT8,
                new ulong[] { 0 }, new ulong[] { H5S.UNLIMITED }, new ulong[] { (ulong)bytes_.Length });
            dataSetRows_ = 0;
        }

        [GlobalCleanup]
        public void Cleanup()
        {
            file_.Close();

            H5D.close(dataSet_);
            H5F.close(h5file_);
        }

        [BenchmarkCategory("Append"), Benchmark(Baseline = true)]
        public void FileIOAppend()
        {
            file_.Write(bytes_, 0, bytes_.Length);
            fileRows_ += (hsize_t)bytes_.Length;
        }

        [BenchmarkCategory("Append"), Benchmark]
        public void HDF5Append()
        {
            var newDimensions = new hsize_t[] { dataSetRows_ + (hsize_t)bytes_.Length };
            if (H5D.set_extent(dataSet_, newDimensions) < 0)
                throw new HDF5Exception("H5D.set_extent failed.");

            AppendData(dataSet_, bytes_, ref dataSetRows_);
        }

        [BenchmarkCategory("Flush"), Benchmark(Baseline = true)]
        public void FileIOFlush()
        {
            file_.Flush();
        }

        [BenchmarkCategory("Flush"), Benchmark]
        public void HDF5Flush()
        {
            H5F.flush(dataSet_, H5F.scope_t.LOCAL);
        }

        private static void AppendData<T>(hid_t dataSet, T[] data, ref hsize_t rows)
        {
            var fileSpace = H5D.get_space(dataSet);
            if (fileSpace < 0)
                throw new HDF5Exception("Failed to get data space of data set.");

            var offset = new ulong[] { rows };
            var count = new ulong[] { (ulong)data.Length };

            if (H5S.select_hyperslab(fileSpace, H5S.seloper_t.SET, offset, null, count, null) < 0)
                throw new HDF5Exception("H5S.select_hyperslab failed.");

            var memSpace = H5S.create_simple(1, count, null);
            if (memSpace < 0)
                throw new HDF5Exception("H5S.create_simple failed.");

            if (H5D.write(dataSet, HDF5Helper.NumericTypeToHDF5Type<T>(), memSpace, fileSpace, H5P.DEFAULT, new PinnedObject(data)) < 0)
                throw new HDF5Exception("H5D.write failed.");

            H5S.close(memSpace);
            H5S.close(fileSpace);

            rows += (hsize_t)data.Length;
        }

        private byte[] bytes_;
        private FileStream file_;
        private hsize_t fileRows_;
        private hid_t h5file_;
        private hid_t dataSet_;
        private hsize_t dataSetRows_;
    }

    class Program
    {
        static void Main(string[] args)
        {
            BenchmarkRunner.Run<Benchmark>();
        }
    }
}


// References:
// https://benchmarkdotnet.org/articles/features/baselines.html
// https://benchmarkdotnet.org/articles/guides/choosing-run-strategy.html
