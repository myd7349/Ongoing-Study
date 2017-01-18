// 2017-01-17T13:14:45+08:00
using System;
using System.Runtime.InteropServices;
using System.Text;


namespace ArrayMarshalingTest
{
    class Program
    {
        static void Main(string[] args)
        {
            double[] array = new double[10];
            Native.Fill(array, (uint)array.Length);

            foreach (var v in array)
                Console.WriteLine(v);

            var cwd = new StringBuilder(260);
            Console.WriteLine(Native.GetCurrentDirectory(cwd));
            Console.WriteLine(System.IO.Directory.GetCurrentDirectory());

            Console.ReadKey();
        }
    }

    internal static class Native
    {
        [DllImport("ArrayMarshalingNative.dll", EntryPoint = "Fill", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Fill(double[] array, uint len);

        [DllImport("ArrayMarshalingNative.dll", EntryPoint = "GetCurrentDirectory", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetCurrentDirectory([Out] StringBuilder sb, int len);

        public static StringBuilder GetCurrentDirectory(StringBuilder sb)
        {
#if DEBUG
            sb.Append("Hello, world!");
#endif
            GetCurrentDirectory(sb, sb.Capacity);
            return sb;
        }
    }
}

// References:
// [C# Marshalling double* from C++ DLL?](http://stackoverflow.com/questions/5072340/c-sharp-marshalling-double-from-c-dll)
// [A call to PInvoke function '[…]' has unbalanced the stack](http://stackoverflow.com/questions/2941960/a-call-to-pinvoke-function-has-unbalanced-the-stack)
// [Default Marshaling for Arrays](https://msdn.microsoft.com/en-us/library/z6cfh6e6(v=vs.110).aspx)
// https://github.com/mono/mono/blob/master/mcs/class/Mono.Posix/Mono.Unix.Native/Syscall.cs#L4599
