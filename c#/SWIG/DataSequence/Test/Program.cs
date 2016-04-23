using System;

using Common;

class Program
{
    static void Main(string[] args)
    {
        using (DataSequence ds = new DataSequence())
        {
            ds.PushBack(3.14);
            Console.WriteLine(ds);

            ds.PushBack(2.71);
            ds.PushBack(100);
            Console.WriteLine(ds);

            ds.PopBack();
            Console.WriteLine(ds);

            ds.PopBack();
            ds.PopBack();
            Console.WriteLine(ds);

            try
            {
                ds.PopBack();
            }
            catch (Exception e)
            {

            }
        }

        Util.Pause();
    }
}

