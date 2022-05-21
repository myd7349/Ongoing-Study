using System.Windows;

namespace TTSDemo
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void speakButton__Click(object sender, RoutedEventArgs e)
        {
            mainWindowViewModel_.Speak();
        }
    }
}
