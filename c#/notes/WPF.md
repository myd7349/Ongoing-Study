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
