// 2016-07-02T17:50+08:00
using System;
using System.Diagnostics;

namespace CPP11StdArray
{
    class Program
    {
        static void Main(string[] args)
        {
            TestBytes1024();
            TestEmptyBuffer();
            TestGoF();
        }

        static void TestBytes1024()
        {
            Bytes1024 fixedSizeBuffer = new Bytes1024();

            // Count
            Debug.Assert(fixedSizeBuffer.Count == 1024);

            // Fill
            fixedSizeBuffer.Fill(255);
            Random random = new Random();
            for (int i = 0; i < fixedSizeBuffer.Count; ++i)
                Debug.Assert(fixedSizeBuffer[random.Next(fixedSizeBuffer.Count)] == 255);

            // IsEmpty
            Debug.Assert(!fixedSizeBuffer.IsEmpty);
        }

        static void TestEmptyBuffer()
        {
            EmptyBuffer empty = new EmptyBuffer();

            Debug.Assert(empty.IsEmpty);
            Debug.Assert(empty.Count == 0);
        }

        static void TestGoF()
        {
            GoF gof = new GoF();
            gof[0] = "Erich Gamma";

            GoF gof2 = new GoF(gof);
            Debug.Assert(gof2[0] == gof[0]);

            string john = "John Vlissides";

            gof[1] = "Richard Helm";
            gof[2] = "Ralph Johnson";
            gof[3] = john;

            // Swap
            gof.Swap(gof2);
            Debug.Assert(gof2[3] == john && gof[3] == "");
        }
    }
}
