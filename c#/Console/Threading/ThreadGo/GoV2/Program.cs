namespace GoV2
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
                Console.Write("Done");
                done_ = true;
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

