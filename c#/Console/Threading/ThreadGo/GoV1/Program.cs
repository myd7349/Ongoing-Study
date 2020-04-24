namespace GoV1
{
    using System;
    using System.Threading;

    class Program
    {
        bool done_;

        void Go()
        {
            if (!done_)
            {
                done_ = true;
                Console.Write("Done");
            }
        }

        static void Main(string[] args)
        {
            var program = new Program();
            new Thread(program.Go).Start();
            program.Go();
        }
    }
}

// References:
// C# 6.0 in a Nutshell, P569
