// 2016-03-16T14:56+08:00
using System;
using System.Diagnostics;

class Test
{
    static void Main(string[] args)
    {
        using (DataSeq dataSeq = new DataSeq())
        {
            dataSeq.PushBack(1.0);
            dataSeq.PushBack(3.14);
            dataSeq.PushBack(2.0);

            foreach (double v in dataSeq)
                Console.WriteLine(v);

            dataSeq.PopBack();

            foreach (double v in dataSeq)
                Console.WriteLine(v);
        }

        Console.ReadKey();
    }
}
