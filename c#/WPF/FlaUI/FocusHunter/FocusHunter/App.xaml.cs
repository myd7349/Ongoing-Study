namespace FocusHunter
{
    using System.Windows;
    using System.Windows.Threading;

    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private void Application_DispatcherUnhandledException(object sender, DispatcherUnhandledExceptionEventArgs e)
        {
            MessageBox.Show(e.ToString(), "Unhandled exception:", MessageBoxButton.OK, MessageBoxImage.Error);
        }
    }
}
