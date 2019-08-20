namespace ByteSwapBenchmark
{
    using BenchmarkDotNet.Attributes;
    using BenchmarkDotNet.Running;

    using static Common.ByteSwap;

    [RPlotExporter, RankColumn]
    public class ByteSwapBenchmark
    {
        [Benchmark]
        public void ByteSwapCSharp() => BytesSwap(0x2010);

        [Benchmark]
        public void ByteSwapV2CSharp() => BytesSwapV2(0x2010);

        [Benchmark]
        public void ByteSwapV3CSharp() => BytesSwapV3(0x2010);

        [Benchmark]
        public void ByteSwapV4CSharpUnsafe() => BytesSwapV4(0x2010);

        //[Benchmark]
        //public void ByteSwapPInvoke() => byteswap_i32(0x2010);
    }

    class Program
    {
        static void Main(string[] args)
        {
            var summary = BenchmarkRunner.Run<ByteSwapBenchmark>();
        }
    }
}


// References:
// https://github.com/dotnet/BenchmarkDotNet
// https://stackoverflow.com/questions/1358747/fast-little-endian-to-big-endian-conversion-in-asm
