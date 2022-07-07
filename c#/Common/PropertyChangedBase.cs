using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace Common
{
    public abstract class PropertyChangedBase : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(object sender = null, [CallerMemberName] string name = "")
        {
            var handler = PropertyChanged;
            handler?.Invoke(sender ?? this, new PropertyChangedEventArgs(name));
        }

        protected virtual bool SetProperty<T2>(
            ref T2 backingStore, T2 value,
            [CallerMemberName]string propertyName = "",
            Action onChanged = null,
            Func<T2, T2, bool> validateValue = null)
        {
            if (EqualityComparer<T2>.Default.Equals(backingStore, value))
                return false;

            if (validateValue != null && !validateValue(backingStore, value))
                return false;

            backingStore = value;
            onChanged?.Invoke();
            OnPropertyChanged(propertyName);
            return true;
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
// [MVVM for Beginners: Model-View-ViewModel Architecture for Xamarin.Forms, .NET MAUI, WPF, UWP, & More](https://www.youtube.com/watch?v=Pso1MeX_HvI)
// > UserViewModel
// https://github.com/jamesmontemagno/mvvm-helpers/blob/master/MvvmHelpers/ObservableObject.cs
// [What is the MVVM pattern, What benefits does MVVM have?](https://youtu.be/AXpTeiWtbC8)
// - https://www.nuget.org/packages/Microsoft.Toolkit.Mvvm
//   - ObservableObject
// - https://github.com/CommunityToolkit/MVVM-Samples
// [mvvm-helpers](https://github.com/jamesmontemagno/mvvm-helpers)
// - ObservableObject
// - BaseViewModel
// - [SkiaSharpFiddle](https://github.com/mattleibow/SkiaSharpFiddle)
// [How to: Implement Property Change Notification](https://learn.microsoft.com/en-us/dotnet/desktop/wpf/data/how-to-implement-property-change-notification?view=netframeworkdesktop-4.8)
