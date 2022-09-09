using CommunityToolkit.Mvvm.ComponentModel;

namespace SpinControlDemo
{
    internal partial class MainWindowViewModel : ObservableObject
    {
        [ObservableProperty]
        private double value = 500;

        [ObservableProperty]
        private double minimum = 10;

        [ObservableProperty]
        private double maximum = 500;
    }
}
