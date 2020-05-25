// 0. Install-Package NLog.Config
// 1. https://github.com/NLog/NLog/wiki/Tutorial#Configure-NLog-Targets-for-output
namespace HelloNLog
{
    using NLog;

    class Program
    {
        private static readonly Logger Logger = LogManager.GetCurrentClassLogger();

        static void Main(string[] args)
        {
        }
    }
}
