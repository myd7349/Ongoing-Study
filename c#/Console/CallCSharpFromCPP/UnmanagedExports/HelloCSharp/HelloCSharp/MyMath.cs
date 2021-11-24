namespace HelloCSharp
{
    using System.Runtime.InteropServices;

    using RGiesecke.DllExport;

    public static class MyMath
    {
        [DllExport("AddI", CallingConvention = CallingConvention.Cdecl)]
        public static int Add(int a, int b)
        {
            return a + b;
        }
    }
}


// References:
// [Calling C# code from C++](https://stackoverflow.com/questions/778590/calling-c-sharp-code-from-c)
// [Unmanaged Exports](https://sites.google.com/site/robertgiesecke/Home/uploads/unmanagedexports) - [NuGet package](https://www.nuget.org/packages/UnmanagedExports)
// [DllExport](https://github.com/3F/DllExport)
// https://github.com/3F/Examples/tree/master/DllExport/BasicExport
