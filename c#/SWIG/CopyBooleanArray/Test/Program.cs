// 2016-06-21T18:20+08:00
using System;
using System.Diagnostics;

using Common;

namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
            bool[] source = { true, true, false, true, true, false, true };
            bool[] target = new bool[source.Length];

            CopyBooleanArrayNative.CopyBooleanArray(source, target, source.Length);
            Debug.Assert(target.EqualTo(source));

            Util.Pause();
        }
    }
}
