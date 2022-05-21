using System.Windows;
using System.Windows.Forms;

using Gma.System.MouseKeyHook;

namespace ShortcutKeyDemo
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            Loaded += MainWindow_Loaded;
            Closing += MainWindow_Closing;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            Subscribe();
        }

        private void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Unsubscribe();
        }

        private void globalHookCheckBox__Click(object sender, RoutedEventArgs e)
        {
            Subscribe();
        }

        private void hookButton__Click(object sender, RoutedEventArgs e)
        {
            if (mainViewModel_.IsHooked)
                Unsubscribe();
            else
                Subscribe();
        }

        private void HotKeyTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            Unsubscribe();
        }

        private void SayHello()
        {
            System.Windows.MessageBox.Show(
                "Hello, world!",
                "A hello message!",
                MessageBoxButton.OK,
                MessageBoxImage.Information);
        }

        private void Minimize()
        {
            WindowState = WindowState.Minimized;
        }

        private void Restore()
        {
            WindowState = WindowState.Normal;
        }

        private void Subscribe()
        {
            if (globalHookCheckBox_.IsEnabled)
                Subscribe(Hook.GlobalEvents());
            else
                Subscribe(Hook.AppEvents());
        }

        private void Subscribe(IKeyboardMouseEvents events)
        {
            if (events == null)
                return;

            Unsubscribe();

            _events = events;
            _events.KeyDown += OnKeyDown;
            mainViewModel_.IsHooked = true;
        }

        private void Unsubscribe()
        {
            if (_events == null)
                return;

            _events.KeyDown -= OnKeyDown;
            _events = null;
            mainViewModel_.IsHooked = false;
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == mainViewModel_.SayHelloShortcut.ToKeys())
                SayHello();
            else if (e.KeyCode == mainViewModel_.MinimizeShortcut.ToKeys())
                Minimize();
            else if (e.KeyCode == mainViewModel_.RestoreShortcut.ToKeys())
                Restore();
        }

        private IKeyboardMouseEvents _events;
    }
}


// References:
// https://github.com/gmamaladze/globalmousekeyhook/blob/master/examples/FormsExample/Main.cs
// https://github.com/gmamaladze/globalmousekeyhook/blob/master/MouseKeyHook/KeyCombinationExtensions.cs
// https://github.com/gmamaladze/globalmousekeyhook/blob/master/examples/ConsoleHook/DetectCombinations.cs
// [Is it OK to enable both Winforms and WPF for a .NET 6.0 application?](https://stackoverflow.com/questions/71374091/is-it-ok-to-enable-both-winforms-and-wpf-for-a-net-6-0-application)
