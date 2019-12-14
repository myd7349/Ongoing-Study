namespace FilterManaged
{
    using System;
    using System.Runtime.InteropServices;

    public class Filter
    {
        [DllImport("FilterNative.dll", EntryPoint = "Filter_init", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Initialize(FilterType type);

        [DllImport("FilterNative.dll", EntryPoint = "Filter_run", CallingConvention = CallingConvention.Cdecl)]
        public static extern double Run(IntPtr context, double x);

        public static void Run(IntPtr context, double[] data, double[] result)
        {
            if (data == null)
                throw new ArgumentNullException("data");

            if (result == null)
                throw new ArgumentNullException("result");

            if (data.Length > result.Length)
                throw new ArgumentException("data.Length > result.Length");

            RunMany(context, data, data.Length, result);
        }

        [DllImport("FilterNative.dll", EntryPoint = "Filter_run_many", CallingConvention = CallingConvention.Cdecl)]
        private static extern void RunMany(IntPtr context, double[] data, int length, double[] result);

        [DllImport("FilterNative.dll", EntryPoint = "Filter_free", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Free(ref IntPtr context);
    }
}


// References:
// [How to marshal a C++ enum in C#](https://stackoverflow.com/questions/22176159/how-to-marshal-a-c-enum-in-c-sharp)
// [Opaque pointers with PInvoke in C#](https://stackoverflow.com/questions/20252859/opaque-pointers-with-pinvoke-in-c-sharp)
