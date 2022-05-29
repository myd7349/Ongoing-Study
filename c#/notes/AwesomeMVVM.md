##### Articles

- [Patterns - WPF Apps With The Model-View-ViewModel Design Pattern](https://docs.microsoft.com/en-us/archive/msdn-magazine/2009/february/patterns-wpf-apps-with-the-model-view-viewmodel-design-pattern)

  - RelayCommand

  - Prism

  - ViewModelBase

- [Windows Community Toolkit MVVM RelayCommand and RelayCommand<T>](https://docs.microsoft.com/en-us/windows/communitytoolkit/mvvm/relaycommand)

- [\[Windows\] 在 Microsoft Docs 网站中挖掘 MVVM 的各种学习资源](https://www.cnblogs.com/dino623/p/mvvm_docs_from_microsoft.html)

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

- [M-V-VM Design Question. Calling View from ViewModel](https://stackoverflow.com/questions/303006/m-v-vm-design-question-calling-view-from-viewmodel)

  - Catel

- [Create view object in ViewModel](https://stackoverflow.com/questions/18204199/create-view-object-in-viewmodel)

- [Open a new Window in MVVM](https://stackoverflow.com/questions/16652501/open-a-new-window-in-mvvm/16653029#16653029)

- [Passing a parameter using RelayCommand defined in the ViewModel (from Josh Smith example)](https://stackoverflow.com/questions/810208/passing-a-parameter-using-relaycommand-defined-in-the-viewmodel-from-josh-smith)

- [MVVM Light Message not received when sending from ViewModel constructor](https://stackoverflow.com/questions/19606680/mvvm-light-message-not-received-when-sending-from-viewmodel-constructor)

- [MVVM - Messenger and View Services in MVVM](https://learn.microsoft.com/en-us/archive/msdn-magazine/2013/march/mvvm-messenger-and-view-services-in-mvvm)

  - IDialogService
  
  - Messaging

- [A lap around the Microsoft MVVM Toolkit](https://xamlbrewer.wordpress.com/2020/11/16/a-lap-around-the-microsoft-mvvm-toolkit/comment-page-1/)

  - Prism

  - SetPropertyAndNotifyOnCompletion

  - [UWP-MVVM-Toolkit-Sample](https://github.com/XamlBrewer/UWP-MVVM-Toolkit-Sample)

- [MVVM closing dialog form from ViewModel](https://stackoverflow.com/questions/59066988/mvvm-closing-dialog-form-from-viewmodel)

- [MVVM-Light Toolkit -- How To Use PropertyChangedMessage](https://stackoverflow.com/questions/13461278/mvvm-light-toolkit-how-to-use-propertychangedmessage/13461450)

- [WPF: how to signal an event from ViewModel to View without code in codebehind?](https://stackoverflow.com/questions/1894329/wpf-how-to-signal-an-event-from-viewmodel-to-view-without-code-in-codebehind)

- [Weak event patterns (WPF .NET)](https://learn.microsoft.com/en-us/dotnet/desktop/wpf/events/weak-event-patterns?view=netdesktop-6.0&redirectedfrom=MSDN)

- [Good or bad practice for Dialogs in wpf with MVVM?](https://stackoverflow.com/questions/3801681/good-or-bad-practice-for-dialogs-in-wpf-with-mvvm)

  > All I want to do in my code was something like this. (I mostly use viewmodel first approach with mvvm)

- [Handling Dialogs in WPF with MVVM](https://stackoverflow.com/questions/454868/handling-dialogs-in-wpf-with-mvvm)

- d:DesignInstance

  - https://github.com/FantasticFiasco/mvvm-dialogs/blob/v8.0.0/samples/net-framework/Demo.ActivateNonModalDialog/CurrentTimeDialog.xaml

  - [How to use d:DesignInstance with types that don't have default constructor?](https://stackoverflow.com/questions/8472228/how-to-use-ddesigninstance-with-types-that-dont-have-default-constructor)

- [MVVM pattern and dialogs](https://www.plainionist.net/Mvvm-Dialogs/)

  - Services
  
  - Prism

  - System.Windows.Interactivity

- Is Model necessary?

  - [The role of the model in MVVM](https://stackoverflow.com/questions/5027562/the-role-of-the-model-in-mvvm)

  - :star: [What goes in Model in MVVM?](https://stackoverflow.com/questions/4453352/what-goes-in-model-in-mvvm/4453396#4453396)

    > INotifyPropertyChanged is NOT an UI concern. It's an interface for the notification of changed properties, not more, not less. So it's perfectly fine to use in the Model if you wish.
    >
    > Actually, having the model implement INPC can save a lot of boilerplate re-passing properties from model through viewmodel to the view.

  - [Do we need Models if we are using ViewModels?](https://softwareengineering.stackexchange.com/questions/389086/do-we-need-models-if-we-are-using-viewmodels)

- Close a dialog

  - [How should the ViewModel close the form?](https://stackoverflow.com/questions/501886/how-should-the-viewmodel-close-the-form)

  - [WPF DialogResult declaratively?](https://stackoverflow.com/questions/2543014/wpf-dialogresult-declaratively)

  - [Where is Button.DialogResult in WPF?](https://stackoverflow.com/questions/1759372/where-is-button-dialogresult-in-wpf)

  - [Why does unloaded event of window do not fire in WPF?](https://stackoverflow.com/questions/8908276/why-does-unloaded-event-of-window-do-not-fire-in-wpf)

  - [C# – Disposing WPF User Controls](https://itecnote.com/tecnote/c-disposing-wpf-user-controls/)

  - [Dispose of a WPF UserControl (ish)](https://web.archive.org/web/20091029112834/http://geekswithblogs.net/cskardon/archive/2008/06/23/dispose-of-a-wpf-usercontrol-ish.aspx)

- Can I use a virtual function when creating ICommand?

  - [Call RelayCommand in another class MVVM](https://stackoverflow.com/questions/37875837/call-relaycommand-in-another-class-mvvm)

- [How to build a generic/re-usable modal dialog for WPF following MVVM](https://stackoverflow.com/questions/2956027/how-to-build-a-generic-re-usable-modal-dialog-for-wpf-following-mvvm)

- [WPF MVVM Modal Overlay Dialog only over a View (not Window)](https://stackoverflow.com/questions/6351612/wpf-mvvm-modal-overlay-dialog-only-over-a-view-not-window)

- [MVVM-Light Toolkit -- How To Use PropertyChangedMessage](https://stackoverflow.com/questions/13461278/mvvm-light-toolkit-how-to-use-propertychangedmessage/13461450)

- [How to use MVVM-Light with tokens?](https://stackoverflow.com/questions/3393286/how-to-use-mvvm-light-with-tokens)

- [How do I use EventToCommand to handle routed event from a child control of a WPF panel?](https://stackoverflow.com/questions/19686304/how-do-i-use-eventtocommand-to-handle-routed-event-from-a-child-control-of-a-wpf)

  - EventToCommand

- [MVVM - Commands, RelayCommands and EventToCommand](https://learn.microsoft.com/en-us/archive/msdn-magazine/2013/may/mvvm-commands-relaycommands-and-eventtocommand)

- [Advanced MVVM Scenarios Using the Prism Library for WPF](https://github.com/PrismLibrary/Prism-Documentation/blob/master/docs/wpf/legacy/Advanced-MVVM.md)

- [Handling events in an MVVM WPF application](https://blog.magnusmontin.net/2013/06/30/handling-events-in-an-mvvm-wpf-application/)

  - Commands

  - EventTriggers

  - CallMethodAction

- [Routed event from user control in MVVM application](https://stackoverflow.com/questions/11887141/routed-event-from-user-control-in-mvvm-application)

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

- [Communicate Between View Models with Observer Pattern - WPF C# MVVM](https://www.youtube.com/watch?v=-6Td1iLBXGw): [code](https://github.com/centrolutions/BuildYourOwnMessenger)

  - IDialogService

  - ConcurrentDictonary

  - Microsoft.Toolkit.Mvvm.DependencyInjection

  - Messager

  - Xunit + Moq

- [View Model Communication/Messaging - EASY WPF (.NET 5)](https://www.youtube.com/watch?v=o62iFhXkWS4)

- [How to Close Windows from a ViewModel in C#](https://www.youtube.com/watch?v=U7Qclpe2joo)

  - ICloseWindows
  
  - [Closing Windows and Applications with WPF and MVVM](https://www.codeproject.com/Articles/413517/Closing-Windows-and-Applications-with-WPF-and-MVVM)

- [MVVM Dialogs: Showing Dialogs in an MVVM Application with a Dialog Service](https://www.youtube.com/watch?v=S8hEjLahNtU)

- [Disposing View Models - WPF MVVM NAVIGATION TUTORIAL #6](https://www.youtube.com/watch?v=WBdyiVyBD_0)

- [WPF and C# - MVVM Pattern - Let's Make It Better #1 Part 3](https://www.youtube.com/watch?v=Nut-KSAM0As)

- [How should the ViewModel close the form?](https://stackoverflow.com/questions/501886/how-should-the-viewmodel-close-the-form)

- [MVVM Source Generators: Never Write MVVM Boilerplate Code Again!](https://www.youtube.com/watch?v=aCxl0z04BN8)

##### Libraries

- AsyncAwaitBestPractices

  - [BaseViewModel](https://github.com/brminnick/AsyncAwaitBestPractices/blob/main/Src/HackerNews/ViewModels/Base/BaseViewModel.cs)
  
- Caliburn.Micro

  - [Papercut-SMTP](https://github.com/ChangemakerStudios/Papercut-SMTP)

  - [NWaves.Blueprints](https://github.com/ar1st0crat/NWaves.Blueprints)

- [CommunityToolkit.Mvvm](https://www.nuget.org/packages/CommunityToolkit.Mvvm/)

  - [Introduction to the MVVM Toolkit](https://learn.microsoft.com/en-us/windows/communitytoolkit/mvvm/introduction)

  - [Putting things together](https://learn.microsoft.com/en-us/windows/communitytoolkit/mvvm/puttingthingstogether?source=recommendations)

  - [A lap around the Microsoft MVVM Toolkit](https://xamlbrewer.wordpress.com/2020/11/16/a-lap-around-the-microsoft-mvvm-toolkit/comment-page-1/)

    - [UWP-MVVM-Toolkit-Sample](https://github.com/XamlBrewer/UWP-MVVM-Toolkit-Sample)

  - [\[NotifyPropertyChanged\]](https://docs.microsoft.com/en-us/dotnet/api/microsoft.toolkit.mvvm.componentmodel.inotifypropertychangedattribute?view=win-comm-toolkit-dotnet-7.0)

  - [Compiling fails when trying to use to ObservableProperty source generator property](https://github.com/CommunityToolkit/WindowsCommunityToolkit/issues/4174)
 
  - [Picking a New MVVM Framework - Moving from Caliburn Micro](https://www.youtube.com/watch?v=8E000zu8UhQ)

  - [mvvm-dialogs](https://github.com/FantasticFiasco/mvvm-dialogs)

  - [MVVM-Samples](https://github.com/CommunityToolkit/MVVM-Samples)

    - https://github.com/CommunityToolkit/MVVM-Samples/blob/master/samples/MvvmSampleUwp/Services/DialogService.cs

- [DynamicData](https://github.com/reactivemarbles/DynamicData)

  - [Camelotia](https://github.com/reactiveui/Camelotia)

  - [Dynamic.Trader](https://github.com/RolandPheasant/Dynamic.Trader)

- [EssentialMVVM](https://github.com/thomaslevesque/EssentialMVVM)

- Fody.PropertyChanged

  - [DataGridExtensionsSample](https://github.com/dotnet/DataGridExtensions/tree/master/src/DataGridExtensionsSample)

  - [fasetto-word](https://github.com/angelsix/fasetto-word)

  - [YoutubeDownloader](https://github.com/Tyrrrz/YoutubeDownloader)

- [JustMVVM](https://github.com/chris84948/JustMVVM)
  
- MahApps.Metro

  - [IDialogCoordinator](https://github.com/MahApps/MahApps.Metro/blob/develop/src/MahApps.Metro/Controls/Dialogs/IDialogCoordinator.cs)

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

  - [ToastFish](https://github.com/Uahh/ToastFish)

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

  - [Prism grows up](https://devblogs.microsoft.com/dotnet/prism-grows-up/)

- [PropertyChanged](https://github.com/reactivemarbles/PropertyChanged)

- [PropertyChanged.SourceGenerator](https://github.com/canton7/PropertyChanged.SourceGenerator)

- [ReactiveMvvm](https://github.com/reactiveui/ReactiveMvvm)

- [ReactiveProperty](https://github.com/runceel/ReactiveProperty)

- [ReactiveUI](https://github.com/reactiveui/ReactiveUI)
  
- [Stylet](https://github.com/canton7/Stylet): A very lightweight but powerful ViewModel-First MVVM framework for WPF for .NET Framework and .NET Core, inspired by Caliburn.Micro.

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
