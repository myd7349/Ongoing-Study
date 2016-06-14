// 2016-06-14T18:55+08:00
using System;

using Common;
using Common.IO;


namespace DirWalkerTest
{
    class Program
    {
        static void Main(string[] args)
        {
            foreach (var entry in DirUtils.Walk(@"..\..\", true, false))
                Console.WriteLine(entry);

            Util.Pause();
        }
    }
}
