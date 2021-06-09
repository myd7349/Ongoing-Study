namespace HelloNLog
{
    using System;

    using NLog;

    class Program
    {
        static readonly Logger Log = LogManager.GetCurrentClassLogger();

        static void Main(string[] args)
        {
            // In early version of NLog, the output might be:
            // Hi! I'm Bob.
            // not:
            // Bob: Hi! I'm Bob.
            Log.Debug("Bob: Hi! I'm Bob.");
            Log.Trace("Bob: Hi! I'm Bob.");
            Log.Info("Bob: Hi! I'm Bob.");

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
// [Text cut off when using When layout renderer combined with a colon](https://github.com/NLog/NLog/issues/444)
// [Text cut off when using When layout renderer combined with a colon](https://stackoverflow.com/questions/26911587/text-cut-off-when-using-when-layout-renderer-combined-with-a-colon)
