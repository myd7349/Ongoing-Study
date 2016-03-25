// 2016-03-16T14:56+08:00
using System;
using System.Diagnostics;

using Common;
using DataSeq.CSharp;


class Test
{
    static void Main(string[] args)
    {
        using (DataSequence dataSeq = new DataSequence())
        {
            dataSeq.PushBack(1.0);
            dataSeq.PushBack(3.14);
            dataSeq.PushBack(2.0);

            foreach (double v in dataSeq)
                Console.WriteLine(v);

            dataSeq.PopBack();

            foreach (double v in dataSeq)
                Console.WriteLine(v);

            dataSeq[0] = 2.71828;
            Console.WriteLine(dataSeq[0]);

            double[] data = dataSeq.GetData();
            foreach (double v in data)
                Console.WriteLine(v);
        }

        DataSequence dataSeq2 = new DataSequence(10);
        Debug.Assert(dataSeq2.Size == 10);
        try
        {
            dataSeq2[10] = 100.0;
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }

        dataSeq2.PushBack(100.0);
        UInt32 size = dataSeq2.Size;
        for (UInt32 i = 0; i < size; ++i)
            Console.WriteLine(dataSeq2[i]);

        Util.Pause();
    }
}
