namespace RegistryExtensionTest
{
    using System;
    using System.Linq;

    using Microsoft.Win32;

    using Common;
    using Common.Configuration.Registry;

    class Program
    {
        static void Main(string[] args)
        {
            Registry.LocalMachine.
                EnumerateSubKeys(@"SYSTEM\ControlSet001\Control\GraphicsDrivers\Configuration", true).
                ForEach(tuple => Console.WriteLine(tuple.Item1 + "\\" + tuple.Item2));

            Registry.LocalMachine.
                EnumerateValues(@"SYSTEM\ControlSet001\Control\GraphicsDrivers\Configuration", true).
                Where(tuple => tuple.Item2 == "Scaling").
                ForEach(tuple => Console.WriteLine("{0} = {1}({2})", tuple.Item2, tuple.Item3, tuple.Item4));

            Util.Pause();
        }
    }
}
