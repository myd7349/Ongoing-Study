namespace HelloNLogV2
{
    using System;

    using NLog;

    using MyLib;

    class Program
    {
        static readonly Logger Log = LogManager.GetCurrentClassLogger();

        static void Main(string[] args)
        {
            try
            {
                Log.Info("Hello, NLog!");
                Log.Debug("This is a debug message.");
                Log.Warn("This is a warning message.");

                MyMath.Sin(Math.PI);
                MyMath.Sin(Math.PI / 2);
                MyMath.Sin(double.PositiveInfinity);
            }
            catch (Exception ex)
            {
                Log.Error(ex, "Goodbye cruel world.");
            }
        }
    }
}

// References:
// [Share nlog config with multiple projects and the proper threadsafe way to all write to the same log file?](https://stackoverflow.com/questions/13854426/share-nlog-config-with-multiple-projects-and-the-proper-threadsafe-way-to-all-wr)
// [How to use NLog from multiple projects in the same solution](https://stackoverflow.com/questions/29188721/how-to-use-nlog-from-multiple-projects-in-the-same-solution)
