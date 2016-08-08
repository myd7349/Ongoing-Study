// 2016-08-07T19:34+08:00
using System;
using System.Diagnostics;

namespace VarargsTest
{
    class Program
    {
        static bool RetrieveDataHelper(IntVector aSampling, uint pos, params int[][] leads)
        {
            const int MaxLeadCount = 18;
            Debug.Assert(leads.Length >= 1 && leads.Length <= MaxLeadCount);

            int[][] allLeads = new int[MaxLeadCount][];
            uint dataLength = 0;

            for (int i = 0; i < allLeads.Length; ++i)
            {
                if (i < leads.Length)
                {
                    Debug.Assert(leads[i] != null);

                    if (dataLength == 0)
                    {
                        dataLength = (uint)leads[i].Length;
                        Debug.Assert(dataLength > 0 && dataLength > pos);
                    }
                    else
                    {
                        // All leads must be the same size.
                        Debug.Assert(leads[i].Length == dataLength);
                    }

                    allLeads[i] = leads[i];
                }
                else
                {
                    allLeads[i] = null;
                }
            }

            return VarargsTestNative.RetrieveASamplingFromMultiLeadsData(
                aSampling, pos, dataLength,
                allLeads[0],
                allLeads[1],
                allLeads[2],
                allLeads[3],
                allLeads[4],
                allLeads[5],
                allLeads[6],
                allLeads[7],
                allLeads[8],
                allLeads[9],
                allLeads[10],
                allLeads[11],
                allLeads[12],
                allLeads[13],
                allLeads[14],
                allLeads[15],
                allLeads[16],
                allLeads[17]);
        }

        private const int DataLength = 5;

        static void Standard12LeadTest()
        {
            const int LeadCount = 12;

#if false
            int[,] data = new int[LeadCount, DataLength];
            for (int i = 0; i < data.GetLength(0); ++i)
                for (int j = 0; j < data.GetLength(1); ++j)
                    data[i, j] = (i + 1) * LeadCount + (j + 1);
#else
            int[][] data = new int[LeadCount][];
            for (int i = 0; i < data.Length; ++i)
            {
                data[i] = new int[DataLength];
                for (int j = 0; j < data[i].Length; ++j)
                    data[i][j] = (i + 1) * 100 + (j + 1);
            }
#endif

            IntVector aSampling = new IntVector();
            RetrieveDataHelper(aSampling, DataLength / 2, data);

            foreach (var i in aSampling)
                Console.WriteLine(i);
        }

        static void FrankLeadTest()
        {
            int[] X = new int[DataLength] { 1, 11, 111, 1111, 11111 };
            int[] Y = new int[DataLength] { 2, 22, 222, 2222, 22222 };
            int[] Z = new int[DataLength] { 3, 33, 333, 3333, 33333 };

            IntVector aSampling = new IntVector();
            RetrieveDataHelper(aSampling, DataLength / 2, X, Y, Z);

            foreach (var data in aSampling)
                Console.WriteLine(data);
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Standard 12-lead test:");
            Standard12LeadTest();

            Console.WriteLine("Frank lead test:");
            FrankLeadTest();

            Console.ReadKey();
        }
    }
}
