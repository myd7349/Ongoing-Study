// 2016-04-07T10:01+08:00
// Algorithm interface benchmark for:
// 1. C# safe code;
// 2. C# unsafe code;
// 3. C++/CLI interface;
// 4. C/C++ interface via PInvoke;
using System;
using System.Diagnostics;

using Algorithm;

namespace AlgorithmInterfaceBenchmark
{
    static class Program
    {
        static long Benchmark(Action action, int repeat)
        {
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            for (int i = 0; i < repeat; ++i)
                action();
            stopWatch.Stop();
            return stopWatch.ElapsedMilliseconds;
        }

        static void BenchmarkHelper(string name, Action action, int repeat = 10)
        {
            long elapsedMS = Benchmark(action, repeat);
            Console.WriteLine("Running for {0} times:\n{1}: {2}ms", repeat, name, elapsedMS);
        }

        static void Main(string[] args)
        {
            IAlgorithm[] algorithms =
            {
                new AlgorithmViaCS(),
                new AlgorithmViaUnsafeCode(),
                new AlgorithmViaPInvoke()
            };

            double[] data = new double[240];
            int[] src = new int[1024];
            int[] dest = new int[src.Length];

            foreach (var algo in algorithms)
            {
                Console.WriteLine(new string('-', 79));

                BenchmarkHelper(algo.GetType().Name + "::ZeroArray",
                    () => algo.ZeroArray(data), 100000);

                BenchmarkHelper(algo.GetType().Name + "::CopyArray",
                    () => algo.CopyArray(dest, src), 100000);
            }

            Console.ReadKey();
        }
    }
}

// References:
// C# 6.0 in a Nutshell
// -- Chapter 4. Advanced C#/Unsafe Code and Pointers
// -- Chapter 25. Interoperability