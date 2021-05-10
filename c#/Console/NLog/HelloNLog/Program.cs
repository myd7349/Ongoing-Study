namespace HelloNLog
{
    using System;

    using NLog;

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

                throw new Exception("Goodbye.");
            }
            catch (Exception ex)
            {
                Log.Error(ex, "Goodbye cruel world.");
            }
        }
    }
}


// References:
// https://github.com/NLog/NLog/wiki/Tutorial
