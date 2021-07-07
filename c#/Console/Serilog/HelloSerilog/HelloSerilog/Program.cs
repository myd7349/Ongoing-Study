namespace HelloSerilog
{
    using static System.Console;

    using Serilog;

    using FooLib;

    class Program
    {
        static void Main(string[] args)
        {
            Log.Logger = new LoggerConfiguration()
                .MinimumLevel.Information()
                .WriteTo.Console()
                .WriteTo.File("log.txt", rollingInterval: RollingInterval.Day, rollOnFileSizeLimit: true)
                .CreateLogger();

            Log.Information("Hello, Serilog!");
            Log.Debug("This is a debug message.");
            Log.Warning("This is a warning message.");

            Foo.Bar("Good Luck!");

            Log.CloseAndFlush();

            ReadKey();
        }
    }
}
