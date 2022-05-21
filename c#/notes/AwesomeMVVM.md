##### Articles

- [Patterns - WPF Apps With The Model-View-ViewModel Design Pattern](https://docs.microsoft.com/en-us/archive/msdn-magazine/2009/february/patterns-wpf-apps-with-the-model-view-viewmodel-design-pattern)

  - RelayCommand

  - Prism

  - ViewModelBase

- [ Windows Community Toolkit MVVM RelayCommand and RelayCommand<T>](https://docs.microsoft.com/en-us/windows/communitytoolkit/mvvm/relaycommand)

- [[Windows] 在 Microsoft Docs 网站中挖掘 MVVM 的各种学习资源](https://www.cnblogs.com/dino623/p/mvvm_docs_from_microsoft.html)

  - Prism

- [一篇文章，带你玩转MVVM，Dapper，AutoMapper](https://www.cnblogs.com/Koalin/p/11706420.html)

  - BaseViewModels

- [Design Patterns - Problems and Solutions with Model-View-ViewModel](https://docs.microsoft.com/en-us/archive/msdn-magazine/2010/july/design-patterns-problems-and-solutions-with-model-view-viewmodel)

- [Master the Basics of MVVM for Building WPF Applications](https://intellitect.com/blog/getting-started-model-view-viewmodel-mvvm-pattern-using-windows-presentation-framework-wpf/)

- [Closing Windows and Applications with WPF and MVVM](https://www.codeproject.com/Articles/413517/Closing-Windows-and-Applications-with-WPF-and-MVVM)

- [Showing Dialogs When Using the MVVM Pattern in WPF or UWP](https://www.codeproject.com/Articles/36745/Showing-Dialogs-When-Using-the-MVVM-Pattern-in-WPF)

- [How do I get DelegateCommand CanExecute to update WPF UI using MVVM?](https://stackoverflow.com/questions/58437185/how-do-i-get-delegatecommand-canexecute-to-update-wpf-ui-using-mvvm)

- [Why to avoid the codebehind in WPF MVVM pattern?](https://stackoverflow.com/questions/6421372/why-to-avoid-the-codebehind-in-wpf-mvvm-pattern)

  > In a well-designed MVVM architecture, the codebehind for most Views should be empty, or, at most, only contain code that manipulates the controls and resources contained within that view. (2) Sometimes it is also necessary to write code in a View's codebehind that interacts with a ViewModel object, such as hooking an event or calling a method that would otherwise be very difficult to invoke from the ViewModel itself.

- [WPF how to bind mousedown (command/action) to label](https://stackoverflow.com/questions/47199489/wpf-how-to-bind-mousedown-command-action-to-label)

- [Handling events in an MVVM WPF application](https://blog.magnusmontin.net/2013/06/30/handling-events-in-an-mvvm-wpf-application/)

  > In a WPF application that uses the MVVM (Model-View-ViewModel) design pattern, the view model is the component that is responsible for handling the application’s presentation logic and state. This means that the view’s code-behind file should contain no code to handle events that are raised from any user interface (UI) element such as a Button or a ComboBox nor should it contain any domain specific logic.

  - DelegateCommand

- [Passing a parameter using RelayCommand defined in the ViewModel (from Josh Smith example)](https://stackoverflow.com/questions/810208/passing-a-parameter-using-relaycommand-defined-in-the-viewmodel-from-josh-smith)

- UserControl

  - [Should a user control have its own view model?](https://stackoverflow.com/questions/1939345/should-a-user-control-have-its-own-view-model)

  - [Should a user control have its own view model?](https://stackoverflow.com/questions/1939345/should-a-user-control-have-its-own-view-model/58070227#58070227)

  - [WPF UserControl Reuse With MVVM](https://softwareengineering.stackexchange.com/questions/408890/wpf-usercontrol-reuse-with-mvvm)

  - [Binding UserControl View model on MainWindow with MVVM](https://stackoverflow.com/questions/35395002/binding-usercontrol-view-model-on-mainwindow-with-mvvm)

  - [Pass ViewModel to UserControl](https://stackoverflow.com/questions/39908358/pass-viewmodel-to-usercontrol)

##### YouTube Videos

- [C# WPF UI Tutorials: 02 - TreeViews and Value Converters](https://youtu.be/6OwyNiLPDNw)

  - Fody.PropertyChanged

  - https://github.com/PedramElmi/WPFTreeView
- [C# WPF UI Tutorials: 03 - View Model MVVM Basics](https://www.youtube.com/watch?v=U2ZvZwDZmJU)

  - BaseViewModel

  - Fody.PropertyChanged

  - RelayCommand
- https://github.com/royben/RealTimeGraphX/blob/master/RealTimeGraphX/GraphCommand.cs

  - RelayCommand
- [MVVM for Beginners: Model-View-ViewModel Architecture for Xamarin.Forms, .NET MAUI, WPF, UWP, & More](https://youtu.be/Pso1MeX_HvI)

  - MVVM Basics

  - Data Binding

  - System.Runtime.CompilerServices.CallerMemberName

  - UserViewModel

  - ICommand and Command

    - [Xamarin.Forms.Core.Command](https://github.com/xamarin/Xamarin.Forms/blob/5.0.0/Xamarin.Forms.Core/Command.cs) 

  - BindableObject, Prism, MVVM light
- [WPF Controls with MVVM: ComboBox](https://youtu.be/nKJ_XDoAdtY)
- [WPF in C# with MVVM using Caliburn Micro](https://youtu.be/laPFq3Fhs8k)

  - Caliburn.Micro

    - BindableCollection

    - Screen

    - [Using BindableCollection outside ViewModel](https://stackoverflow.com/questions/25201700/using-bindablecollection-outside-viewmodel)
- [Better MVVM with MVVM Helpers (or Xamarin Community Toolkit)](https://youtu.be/y8ZqEOLDeo8)

  - mvvm-helpers

    - BaseViewModel

    - Command

    - AsyncCommand

  - MVVM light, Prism, MVVMHelpers.Metro

  - [XamarinCommunityToolkit](https://github.com/xamarin/XamarinCommunityToolkit)

- [Communicate Between View Models with Observer Pattern - WPF C# MVVM](https://www.youtube.com/watch?v=-6Td1iLBXGw)

- [How to Close Windows from a ViewModel in C#](https://www.youtube.com/watch?v=U7Qclpe2joo)

  - ICloseWindows
  
  - [Closing Windows and Applications with WPF and MVVM](https://www.codeproject.com/Articles/413517/Closing-Windows-and-Applications-with-WPF-and-MVVM)

- [MVVM Dialogs: Showing Dialogs in an MVVM Application with a Dialog Service](https://www.youtube.com/watch?v=S8hEjLahNtU)

- [Disposing View Models - WPF MVVM NAVIGATION TUTORIAL #6](https://www.youtube.com/watch?v=WBdyiVyBD_0)

##### Libraries

- AsyncAwaitBestPractices

  - [BaseViewModel](https://github.com/brminnick/AsyncAwaitBestPractices/blob/main/Src/HackerNews/ViewModels/Base/BaseViewModel.cs)
  
- Caliburn.Micro

  - [Papercut-SMTP](https://github.com/ChangemakerStudios/Papercut-SMTP)

  - [NWaves.Blueprints](https://github.com/ar1st0crat/NWaves.Blueprints)

- [CommunityToolkit.Mvvm](https://www.nuget.org/packages/CommunityToolkit.Mvvm/)

  - [\[NotifyPropertyChanged\]](https://docs.microsoft.com/en-us/dotnet/api/microsoft.toolkit.mvvm.componentmodel.inotifypropertychangedattribute?view=win-comm-toolkit-dotnet-7.0)

  - [Compiling fails when trying to use to ObservableProperty source generator property](https://github.com/CommunityToolkit/WindowsCommunityToolkit/issues/4174)
 
  - [Picking a New MVVM Framework - Moving from Caliburn Micro](https://www.youtube.com/watch?v=8E000zu8UhQ)

  - [mvvm-dialogs](https://github.com/FantasticFiasco/mvvm-dialogs)

  - [MVVM-Samples](https://github.com/CommunityToolkit/MVVM-Samples)

    - https://github.com/CommunityToolkit/MVVM-Samples/blob/master/samples/MvvmSampleUwp/Services/DialogService.cs

- Fody.PropertyChanged

  - [DataGridExtensionsSample](https://github.com/dotnet/DataGridExtensions/tree/master/src/DataGridExtensionsSample)

  - [YoutubeDownloader](https://github.com/Tyrrrz/YoutubeDownloader)

- [maui-bindableproperty-generator](https://github.com/rrmanzano/maui-bindableproperty-generator)

- [Mvvm](https://github.com/StephenCleary/Mvvm)

- [mvvm-helpers](https://github.com/jamesmontemagno/mvvm-helpers)

  - BaseViewModel

  - ObservableObject

  - [SkiaSharpFiddle](https://github.com/mattleibow/SkiaSharpFiddle)
  
- [MvvmCross](https://github.com/MvvmCross/MvvmCross) - [website](https://www.mvvmcross.com/)

  - [ViewModel Lifecycle](https://www.mvvmcross.com/documentation/fundamentals/viewmodel-lifecycle)

- [Microsoft.Toolkit.Mvvm](https://www.nuget.org/packages/Microsoft.Toolkit.Mvvm)

  - [MVVM-Samples](https://github.com/CommunityToolkit/MVVM-Samples)

  - [\[NotifyPropertyChanged\]](https://docs.microsoft.com/en-us/dotnet/api/microsoft.toolkit.mvvm.componentmodel.inotifypropertychangedattribute?view=win-comm-toolkit-dotnet-7.0)

  - [ObservableProperty & AlsoNotifyChangeFor](https://docs.microsoft.com/en-us/dotnet/api/microsoft.toolkit.mvvm.componentmodel.alsonotifychangeforattribute?view=win-comm-toolkit-dotnet-7.0)

- [MvvmLightLibs](https://www.nuget.org/packages/MvvmLightLibs)

  - [HandyPyditor](https://github.com/HandyOrg/HandyPyditor)

- MVVMHelpers.Metro

- [MVVM Light Toolkit](https://github.com/lbugnion/mvvmlight)

- [ObservableEvents](https://github.com/reactivemarbles/ObservableEvents)

- [Pharmacist](https://github.com/reactiveui/Pharmacist)

- [PostSharp](https://www.postsharp.net/)

  - [PostSharp.Patterns.Xaml](https://www.nuget.org/packages/PostSharp.Patterns.Xaml)
  
  - \[NotifyPropertyChanged]

- Prism

  - [Documentation](https://prismlibrary.com/docs/index.html)
  
  - [wpf && silverlight开发框架(prism)系列教程](https://www.cnblogs.com/Clingingboy/archive/2009/06/01/prsim_tutorial.html)

  - [Adding a Prism Login Screen](https://www.youtube.com/watch?v=pnG9CNfqZzA)

  - [PrismExperiments](https://github.com/yarseyah/PrismExperiments)
  
  - [TodoApp](https://github.com/brianlagunas/TodoApp)

  - [Extending Prism for WPF - Manage Windows with the Dialog Service](https://www.youtube.com/watch?v=fNf5Juz00C4)

- [PropertyChanged](https://github.com/reactivemarbles/PropertyChanged)

- [ReactiveMvvm](https://github.com/reactiveui/ReactiveMvvm)

- [ReactiveProperty](https://github.com/runceel/ReactiveProperty)

- [ReactiveUI](https://github.com/reactiveui/ReactiveUI)
  
- [Stylet](https://github.com/canton7/Stylet)

  - Screen

  - [YoutubeDownloader](https://github.com/Tyrrrz/YoutubeDownloader)

- [TinyMvvm](https://github.com/TinyStuff/TinyMvvm)

- [TomsToolbox.Wpf](https://github.com/tom-englert/TomsToolbox/tree/master/src/TomsToolbox.Wpf)

  - DelegateCommand.cs

  - ObservableObject

  - https://github.com/dotnet/DataGridExtensions

- [XamarinCommunityToolkit](https://github.com/xamarin/XamarinCommunityToolkit)

##### Projects

- [KochSnowFlake](https://github.com/ahass/KochSnowFlake)
  - ViewModelBase

- [RealTimeGraphX](https://github.com/royben/RealTimeGraphX)
  - https://github.com/royben/RealTimeGraphX/blob/master/RealTimeGraphX/GraphObject.cs
  - https://github.com/royben/RealTimeGraphX/blob/master/RealTimeGraphX/GraphCommand.cs

##### MVVMC

- [WPF_MVVMC](https://github.com/michaelscodingspot/WPF_MVVMC)
