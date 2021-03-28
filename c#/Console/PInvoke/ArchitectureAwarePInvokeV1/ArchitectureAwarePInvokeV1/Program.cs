namespace ArchitectureAwarePInvokeV1
{
    // TODO:
    // x86/Win32: OK
    // x64: OK
    // AnyCPU: Doesn't work currently.
   
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
// [What does the Visual Studio “Any CPU” target mean?](https://stackoverflow.com/questions/516730/what-does-the-visual-studio-any-cpu-target-mean)
