using System;
using System.Linq;

using Common;

namespace MaxMinTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var array = new int[100000];
            array[0] = -88;
            array[array.Length - 1] = 42;

            var minmax = array.MinMax();
            Console.WriteLine("MinMax: <{0}, {1}>", minmax.First, minmax.Second);

            const int REPEAT = 1000;
            Util.BenchmarkHelper("Using MinMax", () => array.MinMax(), REPEAT);
            Util.BenchmarkHelper("Using Min, Max", () => { array.Min(); array.Max(); }, REPEAT);

            Console.ReadKey();
        }
    }
}
