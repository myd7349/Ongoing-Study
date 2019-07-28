namespace ArchitectureAwarePInvokeV1
{
    using System;
    using static System.Console;

    using Native.Interop;

    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                UnsafeNativeMethods.Foo();
            }
            catch (Exception ex)
            {
                WriteLine(ex.ToString());
            }

            WriteLine("Press any key to quit!");
            ReadKey();
        }
    }
}


// References:
// https://stackoverflow.com/questions/12891383/correct-quoting-for-cmd-exe-for-multiple-arguments
