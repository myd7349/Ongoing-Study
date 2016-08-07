// 2016-08-07T19:34+08:00
using System;

namespace VarargsTest
{
    class Program
    {
        static void Standard12LeadTest()
        {
        }

        static void FrankLeadTest()
        {
            const int DataLength = 20;

            int[] X = new int[DataLength];
            int[] Y = X.Clone() as int[];
            int[] Z = X.Clone() as int[];

            for (int i = 0; i < DataLength; ++i)
            {
                X[i] = i + 1;
                Y[i] = X[i] * 10;
                Z[i] = X[i] * 100;
            }

            IntVector aSampling = new IntVector();
            VarargsTestNative.RetrieveASamplingFromMultiLeadsData(
                aSampling, DataLength / 2, DataLength, 
                X, Y, Z,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null,
                null);

            foreach (var data in aSampling)
                Console.WriteLine(data);
        }

        static void Main(string[] args)
        {
            Standard12LeadTest();
            FrankLeadTest();
            Console.ReadKey();
        }
    }
}
