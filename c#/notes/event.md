[Using the same EventArgs instance for multiple events, is this code smell?](https://stackoverflow.com/questions/24891558/using-the-same-eventargs-instance-for-multiple-events-is-this-code-smell)

[How can I clear event subscriptions in C#?](https://stackoverflow.com/questions/153573/how-can-i-clear-event-subscriptions-in-c)

[Check the eventhandler exist for particular event present in the object](https://stackoverflow.com/questions/18112391/check-the-eventhandler-exist-for-particular-event-present-in-the-object)

[How to remove all event handlers from an event](https://stackoverflow.com/questions/91778/how-to-remove-all-event-handlers-from-an-event)

[How to manually invoke an event?](https://stackoverflow.com/questions/8734700/how-to-manually-invoke-an-event)

```csharp
using CommunityToolkit.Mvvm.ComponentModel;

class MyViewModel : ObservableObject
{
    public string Property
    {
        get => property_;
        set => SetProperty(ref property_, value);
    }

    public void NotifyPropertyChanged() => OnPropertyChanged(nameof(Property));

    private string property_;
}

ObservableCollection<MyViewModel> ViewModels { get; }

// Not work.
foreach (var viewModel in ViewModels)
    viewModel.OnPropertyChanged(nameof(MyViewModel.Property));

// Not work.
foreach (var viewModel in ViewModels)
    viewModel.PropertyChanged?.Invoke(new new PropertyChangedEventArgs(nameof(MyViewModel.Property)));

foreach (var viewModel in ViewModels)
    viewModel.NotifyPropertyChanged();
```

https://github.com/anakic/Jot/blob/master/Jot/Configuration/Trigger.cs
