[CollectionViewSource](https://docs.microsoft.com/en-us/dotnet/api/system.windows.data.collectionviewsource?redirectedfrom=MSDN&view=windowsdesktop-6.0)

[wpf sorting combobox item in alphabetical order](https://stackoverflow.com/questions/40248742/wpf-sorting-combobox-item-in-alphabetical-order)

[Sorting a combobox purely in XAML](https://stackoverflow.com/questions/2274690/sorting-a-combobox-purely-in-xaml)

BindingOperations.EnableCollectionSynchronization

- [Using ObservableCollection across UI and Non-UI threads](https://stackoverflow.com/questions/51348527/using-observablecollection-across-ui-and-non-ui-threads)

- [.Net 4.5 Access ObservableCollection from Background Thread without Dispatcher.Invoke()](https://github.com/Dirkster99/FilterTreeView/releases/tag/v1.0.3)

  > No longer using the Dispatcher thread to access ObservableCollection from Non-UI Background Thread:
  > 
  > https://docs.microsoft.com/en-us/dotnet/framework/wpf/getting-started/whats-new#xthread_access

- [What's New in WPF Version 4.5](https://learn.microsoft.com/en-us/dotnet/desktop/wpf/getting-started/whats-new?view=netframeworkdesktop-4.8#xthread_access)

  > Accessing collections on non-UI Threads
  > 
  > WPF enables you to access and modify data collections on threads other than the one that created the collection. This enables you to use a background thread to receive data from an external source, such as a database, and display the data on the UI thread. By using another thread to modify the collection, your user interface remains responsive to user interaction.

- [Modifying collections from different threads and still binding it via WPF](https://siderite.dev/blog/modifying-collections-from-different.html/)

- [Using ObservableCollection across UI and Non-UI threads](https://stackoverflow.com/questions/51348527/using-observablecollection-across-ui-and-non-ui-threads)

- [DataBindEngine](https://github.com/dotnet/wpf/blob/main/src/Microsoft.DotNet.Wpf/src/PresentationFramework/MS/Internal/Data/DataBindEngine.cs)

- [WPF 4.5 : EnableCollectionSynchronization](https://www.wittycoding.com/wpf-4.5-enablecollectionsynchronization)

- [BindingOperations.EnableCollectionSynchronization mystery in WPF](https://stackoverflow.com/questions/19734782/bindingoperations-enablecollectionsynchronization-mystery-in-wpf)
