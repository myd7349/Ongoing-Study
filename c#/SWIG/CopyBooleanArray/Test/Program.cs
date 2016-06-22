// 2016-06-21T18:20+08:00
using System;
using System.Diagnostics;

using Common;

namespace Test
{
    class Program
    {
        unsafe static void Main(string[] args)
        {
            bool[] source = { true, true, false, true, true, false, true };
            bool[] target = new bool[source.Length];

            Console.WriteLine(sizeof(bool));

            fixed (bool* sourcePtr = source)
            {
                Console.WriteLine(new IntPtr(sourcePtr));
                Console.WriteLine(new IntPtr(sourcePtr + 1));
            }

            CopyBooleanArrayNative.CopyBooleanArray(source, target, source.Length);
            Debug.Assert(target.EqualTo(source));

            Util.Pause();
        }
    }
}

// References:
// [How can I display a pointer address in C#?](http://stackoverflow.com/questions/2057469/how-can-i-display-a-pointer-address-in-c)
