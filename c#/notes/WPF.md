[What is the different between 'Auto' and '\*' when setting width/height for a grid column?](https://stackoverflow.com/questions/3164651/what-is-the-different-between-auto-and-when-setting-width-height-for-a-gri)

[Dispatcher.BeginInvoke never execute action?](https://stackoverflow.com/questions/34217259/dispatcher-begininvoke-never-execute-action)

[Difference between Synchronization Context and Dispatcher](https://stackoverflow.com/questions/24671883/difference-between-synchronization-context-and-dispatcher)

[How to control frame rate in WPF by using dispatcher timer accurately?](https://stackoverflow.com/questions/31237266/how-to-control-frame-rate-in-wpf-by-using-dispatcher-timer-accurately)

[WPF - A more accurate Timer](https://stackoverflow.com/questions/51389647/wpf-a-more-accurate-timer)

Awesome WPF projects:

- https://github.com/files-community/Files

[WPF Dynamic GUI elements](https://stackoverflow.com/questions/2382704/wpf-dynamic-gui-elements)

[YoutubeDownloader/App.xaml.cs at 8fb15513fb7dea72925278024904617bfa2285c3 · Tyrrrz/YoutubeDownloader · GitHub](https://github.com/Tyrrrz/YoutubeDownloader/blob/8fb15513fb7dea72925278024904617bfa2285c3/YoutubeDownloader/App.xaml.cs#L6-L12)

> ```csharp
> using System.Windows;
> using System.Windows.Threading;
> 
> namespace YoutubeDownloader
> {
>     public partial class App
>     {
>         private void App_OnDispatcherUnhandledException(object sender, DispatcherUnhandledExceptionEventArgs args)
>         {
>             MessageBox.Show(args.Exception.ToString(), "Error occured", MessageBoxButton.OK, MessageBoxImage.Error);
>         }
>     }
> }
> ```

and in App.xaml:

> ```xml
> <Application
>     x:Class="YoutubeDownloader.App"
>     xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
>     xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
>     xmlns:local="clr-namespace:YoutubeDownloader"
>     xmlns:s="https://github.com/canton7/Stylet"
>     DispatcherUnhandledException="App_OnDispatcherUnhandledException">
> ```

MVVM

- [Model–view–controller - Wikipedia](https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller)

- [Model–view–viewmodel - Wikipedia](https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93viewmodel)

- [Patterns - WPF Apps With The Model-View-ViewModel Design Pattern | Microsoft Docs](https://docs.microsoft.com/en-us/archive/msdn-magazine/2009/february/patterns-wpf-apps-with-the-model-view-viewmodel-design-pattern)

[Expected performance in a real-time plot · Issue #1801 · oxyplot/oxyplot · GitHub](https://github.com/oxyplot/oxyplot/issues/1801)

> In the WPF we have two threads:
> 
> - **UI thread**, running on CPU
> - **Rendering thread**, running on GPU with the help of Direct3D
> 
> The UI thread make a *composition*, it means that 
> the UI thread put all vector graphical object into the scene. The 
> Rendering thread takes the composition of the vector objects and 
> produces the actual visual screen.
> 
> Large windows should increase GPU times, not CPU. And I 
> don't worry to much about GPU time. On a typical machine GPU is not a 
> bottleneck.
> 
> The UI thread performance does not depend on the screen resolution. Only Rendering thread can be slow on large windows.

[Alternative to BitmapImage to load a PNG](https://stackoverflow.com/questions/31701159/alternative-to-bitmapimage-to-load-a-png)

>Unlike BitmapImage, BitmapFrame supports the Metadata property:
>
>So you may replace
>
>Avatar = new BitmapImage(new Uri(...));
>
>by
>
>Avatar = BitmapFrame.Create(new Uri(...));

[Inserting Images to a Grid in Code Behind](https://stackoverflow.com/questions/24749782/inserting-images-to-a-grid-in-code-behind)

[How to change StartupUri of WPF Application?](https://stackoverflow.com/questions/1945843/how-to-change-startupuri-of-wpf-application)

[wpf datagrid vs listbox](https://stackoverflow.com/questions/3211057/wpf-datagrid-vs-listbox)

[How to: Resize Rows with a GridSplitter](https://docs.microsoft.com/en-us/dotnet/desktop/wpf/controls/how-to-resize-rows-with-a-gridsplitter?view=netframeworkdesktop-4.8)

[How do I space out the child elements of a StackPanel?](https://stackoverflow.com/questions/932510/how-do-i-space-out-the-child-elements-of-a-stackpanel)

[Raise an event whenever a property's value changed?](https://stackoverflow.com/questions/2246777/raise-an-event-whenever-a-propertys-value-changed)

```csharp
protected void OnPropertyChanged(
    [System.Runtime.CompilerServices.CallerMemberName] string propertyName = "")
{
    OnPropertyChanged(new PropertyChangedEventArgs(propertyName));
}

public string ImageFullPath
{
    get { return imageFullPath; }
    set
    {
        if (value != imageFullPath)
        {
            imageFullPath = value;
            OnPropertyChanged();
        }
    }
}
```

[Use of Attributes... INotifyPropertyChanged](https://stackoverflow.com/questions/1662745/use-of-attributes-inotifypropertychanged)

[C# WPF UI Tutorials: 03 - View Model MVVM Basics](https://www.youtube.com/watch?v=U2ZvZwDZmJU)

- [Fody.PropertyChanged](https://github.com/Fody/PropertyChanged)

[Difference between Synchronization Context and Dispatcher](https://stackoverflow.com/questions/24671883/difference-between-synchronization-context-and-dispatcher)

[In WPF, is there a "render complete" event?](https://stackoverflow.com/questions/52162647/in-wpf-is-there-a-render-complete-event)

##### Real Time rendering

- WriteableBitmap

  - [WPF - Rendering "Real Time" Best Practice](https://stackoverflow.com/questions/23854176/wpf-rendering-real-time-best-practice)

- CompositionTarget.Rendering

  - [How to: Render on a Per Frame Interval Using CompositionTarget](https://docs.microsoft.com/en-us/dotnet/desktop/wpf/graphics-multimedia/how-to-render-on-a-per-frame-interval-using-compositiontarget?view=netframeworkdesktop-4.8)
  - [CompositionTarget.Rendering Event](https://docs.microsoft.com/en-us/dotnet/api/system.windows.media.compositiontarget.rendering?view=windowsdesktop-6.0)
  - [What can I do inside CompositionTarget.Rendering?](https://stackoverflow.com/questions/18353225/what-can-i-do-inside-compositiontarget-rendering)

  - [Why is Frame Rate in WPF Irregular and Not Limited To Monitor Refresh?](https://stackoverflow.com/questions/5812384/why-is-frame-rate-in-wpf-irregular-and-not-limited-to-monitor-refresh)
