using System;

using Common;

class Program
{
    static void Main(string[] args)
    {
        using (DataSequence ds = new DataSequence())
        {
            ds.push_back(3.14);
            DumpDataSequence(ds);

            ds.push_back(2.71);
            ds.push_back(100);
            DumpDataSequence(ds);

            ds.pop_back();
            DumpDataSequence(ds);

            ds.pop_back();
            ds.pop_back();
            //ds.pop_back();
            DumpDataSequence(ds);
        }

        Util.Pause();
    }

    static void DumpDataSequence(DataSequence ds)
    {
        if (ds == null)
            return;

        uint size = ds.size();
        if (size == unchecked((uint)-1))
        {
            return;
        }
        else if (size == 0)
        {
            Console.WriteLine("[]");
            return;
        }

        Console.Write("[{0}", ds.at(0));
        for (uint i = 1; i < size; ++i)
            Console.Write(", {0}", ds.at(i));
        Console.WriteLine("]");
    }
}

