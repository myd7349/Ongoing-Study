using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

using EnumMenuDemo.Models;

namespace EnumMenuDemo.ViewModels
{
    internal partial class MainWindowViewModel : ObservableObject
    {
        [ObservableProperty]
        private Month month = Month.January;

        public IRelayCommand ChangeWeekdayCommand =>
            _changeWeekdayCommand ??
            (_changeWeekdayCommand = new RelayCommand<Weekday>(ChangeWeekday));

        [ObservableProperty]
        private Weekday weekday;

        //[RelayCommand]
        private void ChangeWeekday(Weekday newWeekday)
        {
            Weekday = newWeekday;
        }

        private IRelayCommand _changeWeekdayCommand;
    }
}
