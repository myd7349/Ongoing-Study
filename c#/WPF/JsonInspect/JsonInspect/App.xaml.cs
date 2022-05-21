using System;
using System.Windows;

using JsonInspect.Views;

namespace JsonInspect
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            var args = Environment.GetCommandLineArgs();
            if (args.Length <= 1)
                new MainWindow().Show();
            else
                new MainWindow(args[1]).Show();
        }
    }
}


// References:
// [Is there a way to start a WPF application without StartUpUri that doesn't break something else?](https://stackoverflow.com/questions/3439320/is-there-a-way-to-start-a-wpf-application-without-startupuri-that-doesnt-break)
