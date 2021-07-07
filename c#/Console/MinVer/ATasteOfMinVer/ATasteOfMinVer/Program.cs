namespace ATasteOfMinVer
{
    using System;
    using System.Reflection;

    using Common;

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            Console.WriteLine($"Produce version: {Assembly.GetEntryAssembly().GetBuildVersion()}");
            Console.ReadKey();
        }
    }
}
