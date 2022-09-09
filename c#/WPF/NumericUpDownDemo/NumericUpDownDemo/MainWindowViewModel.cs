using CommunityToolkit.Mvvm.ComponentModel;

namespace NumericUpDownDemo
{
    internal partial class MainWindowViewModel : ObservableObject
    {
        [ObservableProperty]
        private double value = 500;
    }
}
