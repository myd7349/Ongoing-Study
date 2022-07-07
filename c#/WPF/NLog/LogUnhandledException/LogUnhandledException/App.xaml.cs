using System;
using System.Threading.Tasks;
using System.Windows;

using NLog;

namespace LogUnhandledException
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private Logger Log = LogManager.GetCurrentClassLogger();

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            SetupExceptionHandling();
        }

        private void SetupExceptionHandling()
        {
            AppDomain.CurrentDomain.UnhandledException += (s, e) =>
                LogUnhandledException((Exception)e.ExceptionObject, "AppDomain.CurrentDomain.UnhandledException");

            DispatcherUnhandledException += (s, e) =>
            {
                LogUnhandledException(e.Exception, "Application.Current.DispatcherUnhandledException");
                e.Handled = true;
            };

            TaskScheduler.UnobservedTaskException += (s, e) =>
            {
                LogUnhandledException(e.Exception, "TaskScheduler.UnobservedTaskException");
                e.SetObserved();
            };
        }

        private void LogUnhandledException(Exception exception, string source)
        {
            MessageBox.Show(
                $"{source}\r\n{exception.Message}",
                "Unhandled exception:",
                MessageBoxButton.OK,
                MessageBoxImage.Error);

            Log.Error(exception, $"Unhandled exception ({source})");
            LogManager.Shutdown();
        }
    }
}


// References:
// [Globally catch exceptions in a WPF application?](https://stackoverflow.com/questions/793100/globally-catch-exceptions-in-a-wpf-application)
// https://github.com/microsoft/WPF-Samples/blob/main/Application Management/UnhandledExceptionHandling/App.cs
// https://github.com/microsoft/WPF-Samples/blob/main/Application Management/UnhandledExceptionHandling/App.cs
