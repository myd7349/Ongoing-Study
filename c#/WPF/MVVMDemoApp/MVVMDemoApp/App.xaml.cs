namespace MVVMDemoApp
{
    using System.Windows;

    using MVVMDemoApp.ViewModels;

    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            var mainWindow = new MainWindow();

            // Create the ViewModel to which the main window binds.
            var path = "Data/customers.xml";
            var viewModel = new MainWindowViewModel(path);

            // When the ViewModel asks to be closed, close the window.
            viewModel.RequestClose += delegate { mainWindow.Close(); };

            // Allow all controls in the window to bind to the ViewModel
            // by setting the DataContext, which propagates down the element
            // tree.
            mainWindow.DataContext = viewModel;
            mainWindow.Show();
        }
    }
}
