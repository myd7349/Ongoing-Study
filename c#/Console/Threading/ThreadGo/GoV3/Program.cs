namespace GoV3
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
                // P566:
                // >if inserting Thread.Yield() anywhere in your code breaks
                //  the program, you almost certainly have a bug.
                Thread.Yield();
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

