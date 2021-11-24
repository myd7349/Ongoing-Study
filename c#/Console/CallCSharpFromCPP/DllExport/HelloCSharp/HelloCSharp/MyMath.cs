namespace HelloCSharp
{
    public static class MyMath
    {
        [DllExport]
        public static int Add(int a, int b)
        {
            return a + b;
        }
    }
}


// References:
// https://github.com/3F/DllExport/wiki/Quick-start
// [Calling C# code from C++](https://stackoverflow.com/questions/778590/calling-c-sharp-code-from-c)
// [Unmanaged Exports](https://sites.google.com/site/robertgiesecke/Home/uploads/unmanagedexports) - [NuGet package](https://www.nuget.org/packages/UnmanagedExports)
// [DllExport](https://github.com/3F/DllExport)
// https://github.com/3F/Examples/tree/master/DllExport/BasicExport
// [Conari vs .NET DllExport; Unmanaged C++ and C# [ Part-1 ]](https://www.youtube.com/watch?v=9Hyg3_WE9Ks)
