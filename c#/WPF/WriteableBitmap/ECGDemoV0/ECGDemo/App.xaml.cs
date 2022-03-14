using System;
using System.Diagnostics;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;

using NLog;

namespace ECGDemo
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private static Logger Log = LogManager.GetCurrentClassLogger();

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            if (!Debugger.IsAttached)
            {
                AppDomain.CurrentDomain.UnhandledException += CurrentDomain_UnhandledException;
                Dispatcher.UnhandledException += Dispatcher_UnhandledException;
                TaskScheduler.UnobservedTaskException += TaskScheduler_UnobservedTaskException;
            }

            Log.Info("=================================== Startup ====================================");
        }

        private void CurrentDomain_UnhandledException(object sender, UnhandledExceptionEventArgs e)
        {
            Log.Error($"AppDomain unhandled exception: {e.ExceptionObject.ToString()}");
        }

        private void Dispatcher_UnhandledException(object sender, DispatcherUnhandledExceptionEventArgs e)
        {
            Log.Error(e.Exception);
        }

        private void TaskScheduler_UnobservedTaskException(object sender, UnobservedTaskExceptionEventArgs e)
        {
            Log.Error(e.Exception);
        }

        protected override void OnExit(ExitEventArgs e)
        {
            Log.Info("----------------------------------- Shutdown -----------------------------------");

            base.OnExit(e);
        }
    }
}


// References:
// [Globally catch exceptions in a WPF application ?](https://stackoverflow.com/questions/793100/globally-catch-exceptions-in-a-wpf-application)
// [WPF global exception handler](https://stackoverflow.com/questions/1472498/wpf-global-exception-handler)
