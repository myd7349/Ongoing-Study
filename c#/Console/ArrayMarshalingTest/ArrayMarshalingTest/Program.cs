// 2017-01-17T13:14:45+08:00
using System;
using System.Runtime.InteropServices;

namespace ArrayMarshalingTest
{
    class Program
    {
        static void Main(string[] args)
        {
            double[] array = new double[10];
            FillAPINative.Fill(array, (uint)array.Length);

            foreach (var v in array)
                Console.WriteLine(v);

            Console.ReadKey();
        }
    }

    internal static class FillAPINative
    {
        [DllImport("ArrayMarshalingNative.dll", EntryPoint = "Fill", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Fill(double[] array, uint len);
    }
}

// References:
// [C# Marshalling double* from C++ DLL?](http://stackoverflow.com/questions/5072340/c-sharp-marshalling-double-from-c-dll)
// [A call to PInvoke function '[…]' has unbalanced the stack](http://stackoverflow.com/questions/2941960/a-call-to-pinvoke-function-has-unbalanced-the-stack)
// [Default Marshaling for Arrays](https://msdn.microsoft.com/en-us/library/z6cfh6e6(v=vs.110).aspx)
