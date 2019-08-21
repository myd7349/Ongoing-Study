namespace BinaryWriterBEBenchmark
{
    using System;
    using System.IO;

    using BenchmarkDotNet.Attributes;

    using Common.IO;

    [RPlotExporter, RankColumn]
    public class BinaryWriterBenchmark
    {
        private byte[] buffer0_;
        private byte[] buffer1_;
        private byte[] buffer2_;

        private MemoryStream memoryStream0_;
        private MemoryStream memoryStream1_;
        private MemoryStream memoryStream2_;

        private BinaryWriter binaryWriter_;
        private BinaryWriterBE binaryWriterBE_;
        private BinaryWriterEx binaryWriterEx_;

        [Params(100000, 1000000)]
        public int N;

        [GlobalSetup]
        public void Setup()
        {
            buffer0_ = new byte[N * sizeof(double)];
            buffer1_ = new byte[N * sizeof(double)];
            buffer2_ = new byte[N * sizeof(double)];

            memoryStream0_ = new MemoryStream(buffer0_);
            memoryStream1_ = new MemoryStream(buffer1_);
            memoryStream2_ = new MemoryStream(buffer2_);

            binaryWriter_ = new BinaryWriterBE(memoryStream0_);
            binaryWriterBE_ = new BinaryWriterBE(memoryStream1_);
            binaryWriterEx_ = new BinaryWriterEx(memoryStream2_, false);
        }

        [Benchmark]
        public void BinaryWriterBench()
        {
            binaryWriter_.Seek(0, SeekOrigin.Begin);

            for (int i = 0; i < N; ++i)
                binaryWriter_.Write(Math.PI);
        }

        [Benchmark]
        public void BinaryWriterBEBench()
        {
            binaryWriterBE_.Seek(0, SeekOrigin.Begin);

            for (int i = 0; i < N; ++i)
                binaryWriterBE_.Write(Math.PI);
        }

        [Benchmark]
        public void BinaryWriterExBench()
        {
            binaryWriterEx_.Seek(0, SeekOrigin.Begin);

            for (int i = 0; i < N; ++i)
                binaryWriterEx_.Write(Math.PI);
        }
    }
}
