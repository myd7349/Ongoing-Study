using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace Common
{
    public class PropertyChangedBase : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(object sender = null, [CallerMemberName] string name = "")
        {
            var handler = PropertyChanged;
            handler?.Invoke(sender ?? this, new PropertyChangedEventArgs(name));
        }
    }
}


// References:
// [C# WPF UI Tutorials: 03 - View Model MVVM Basics](https://www.youtube.com/watch?v=U2ZvZwDZmJU)
// > BaseViewModel
// > Fody.PropertyChanged
// [一篇文章，带你玩转MVVM，Dapper，AutoMapper](https://www.cnblogs.com/Koalin/p/11706420.html)
// > BaseViewModel
// [WPF Countdown Timer Binding to different window](https://stackoverflow.com/questions/28272603/wpf-countdown-timer-binding-to-different-window)
