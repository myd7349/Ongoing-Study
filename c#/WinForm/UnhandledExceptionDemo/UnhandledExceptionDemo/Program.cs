namespace UnhandledExceptionDemo
{
    using System;
#if !DEBUG
    using System.Threading;
    using System.Threading.Tasks;
#endif
    using System.Windows.Forms;

    using Serilog;

    static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Log.Logger = new LoggerConfiguration()
                .MinimumLevel.Information()
                .WriteTo.File("Log-.log", rollingInterval: RollingInterval.Day, rollOnFileSizeLimit: true)
                .CreateLogger();

            Log.Information("---------------------------------------- Startup ----------------------------------------");

            Application.SetHighDpiMode(HighDpiMode.SystemAware);
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
#if !DEBUG
            Application.ThreadException += UnhandledThreadException;
            TaskScheduler.UnobservedTaskException += UnobservedTaskException;
#endif
            Application.Run(new MainForm());

            Log.Information("---------------------------------------- Shutdown ---------------------------------------");

            Log.CloseAndFlush();
        }

#if !DEBUG
        private static void UnhandledThreadException(object sender, ThreadExceptionEventArgs e)
        {
            Log.Error("Unhandled exception:\n{Exception}", e.Exception);

            MessageBox.Show(e.Exception.ToString(), "Unhanled exception:", MessageBoxButtons.OK, MessageBoxIcon.Error);

            Log.CloseAndFlush();
        }

        private static void UnobservedTaskException(object sender, UnobservedTaskExceptionEventArgs e)
        {
            Log.Error("Unobserved task exception:\n{Exception}", e.Exception);

            MessageBox.Show(e.Exception.ToString(), "Unobserved task exception:", MessageBoxButtons.OK, MessageBoxIcon.Error);

            Log.CloseAndFlush();
        }
#endif
    }
}


// References:
// https://github.com/cyanfish/naps2/blob/master/NAPS2.DI/EntryPoints/WinFormsEntryPoint.cs
// [Enable code on Release compilation](https://stackoverflow.com/questions/6927263/enable-code-on-release-compilation)
