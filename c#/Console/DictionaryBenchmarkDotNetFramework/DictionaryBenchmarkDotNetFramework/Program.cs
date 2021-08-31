namespace DictionaryBenchmarkDotNetFramework
{
    using System.Collections.Generic;

    using BenchmarkDotNet.Attributes;
    using BenchmarkDotNet.Configs;
    using BenchmarkDotNet.Running;

    [GroupBenchmarksBy(BenchmarkLogicalGroupRule.ByCategory)]
    [CategoriesColumn]
    public class BenchmarkInstance
    {
        [Params(10000, 1000000)]
        public int Count;

        [GlobalSetup]
        public void Setup()
        {
            array_ = new double[Count];

            dictionary_ = new Dictionary<int, double>();
            for (int i = 0; i < Count; ++i)
                dictionary_[i] = i * 2;
        }

        [BenchmarkCategory("Set")]
        [Benchmark]
        public void ArraySet()
        {
            for (int i = 0; i < array_.Length; ++i)
                array_[i] = i;
        }

        [BenchmarkCategory("Set")]
        [Benchmark]
        public void DictionarySet()
        {
            for (int i = 0; i < dictionary_.Count; ++i)
                dictionary_[i] = i;
        }

        [BenchmarkCategory("Get")]
        [Benchmark]
        public void ArrayGet()
        {
            double v;
            for (int i = 0; i < array_.Length; ++i)
                v = array_[i];
        }

        [BenchmarkCategory("Get")]
        [Benchmark]
        public void DictionaryGet()
        {
            double v;
            for (int i = 0; i < dictionary_.Count; ++i)
                v = dictionary_[i];
        }

        private double[] array_;
        private Dictionary<int, double> dictionary_;
    }

    class Program
    {
        static void Main()
        {
            var summary = BenchmarkRunner.Run<BenchmarkInstance>();
        }
    }
}
