// 2016-04-07T10:01+08:00
// Algorithm interface benchmark for:
// 1. C# safe code;
// 2. C# unsafe code;
// 3. C++/CLI interface(TODO);
// 4. C/C++ interface via PInvoke;
using System;

using Algorithm;
using Common;

namespace AlgorithmInterfaceBenchmark
{
    static class Program
    {
        static void Main(string[] args)
        {
            const int BufferLength = 500;
            IAlgorithm[] algorithms =
            {
                new AlgorithmViaCS(BufferLength, false),
                new AlgorithmViaCS(BufferLength, true),
                new AlgorithmViaUnsafeCode(BufferLength),
                new AlgorithmViaPInvoke(BufferLength)
            };

            double[] data = new double[240];
            int[] src = new int[1024];
            int[] dest = new int[src.Length];
            const int Repeat = 100000;

            foreach (var algo in algorithms)
            {
                Console.WriteLine(new string('-', 79));

                Util.BenchmarkHelper(algo.ToString() + "::ZeroArray", () => algo.ZeroArray(data), Repeat);
                Util.BenchmarkHelper(algo.ToString() + "::MagicFilter", () => algo.MagicFilter(3.1415926), Repeat);
                Util.BenchmarkHelper(algo.ToString() + "::CopyArray", () => algo.CopyArray(dest, src), Repeat);
            }

            Util.Pause();
        }
    }
}

// References:
// C# 6.0 in a Nutshell
// -- Chapter 4. Advanced C#/Unsafe Code and Pointers
// -- Chapter 25. Interoperability