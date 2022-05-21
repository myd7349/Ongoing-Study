1. [How do you stop the Designer generating code for public properties on a User Control?](https://stackoverflow.com/questions/29696/how-do-you-stop-the-designer-generating-code-for-public-properties-on-a-user-con)

   ```csharp
   [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
   public Background Background
   {
       get;
       set;
   }
   ```

2. [Implement System.ComponentModel.BackgroundWorker](https://github.com/inthehand/32feet/blob/main/Legacy/InTheHand.Net.Personal/Windows/Forms/BackgroundWorker.cs)

3. [How to license .NET components and controls using Microsoft’s LicenseProvider Class](https://www.softwarekey.com/blog/licensing-tips/how-to-license-components-controls-microsoft-license-provider-class/)
   - [ILNumerics FFT Spectrum Analyzer example](https://ilnumerics.net/examples.php?exid=16e18c33a0743343c75e6470d07011bd)

4. [Developing . NET Custom Controls and Designers Using C#](https://books.google.com.hk/books?id=f2lcvqNAeo4C&pg=PA449&lpg=PA449&dq=LicenseProvider&source=bl&ots=nyenbLGTkg&sig=ACfU3U3g-HAJ8R4ecIWplHHunXwE0MXXnQ&hl=en&sa=X&redir_esc=y&hl=zh-CN&sourceid=cndr#v=onepage&q=LicenseProvider&f=false)
5. [INotifyPropertyChanged Interface](https://docs.microsoft.com/en-us/dotnet/api/system.componentmodel.inotifypropertychanged?view=net-5.0)
   - [How to: Implement Property Change Notification](https://docs.microsoft.com/en-us/dotnet/desktop/wpf/data/how-to-implement-property-change-notification?view=netframeworkdesktop-4.8)
   - [Raise an event whenever a property's value changed?](https://stackoverflow.com/questions/2246777/raise-an-event-whenever-a-propertys-value-changed)
6. DisplayName
   - [Access DisplayName in xaml](https://stackoverflow.com/questions/6154050/access-displayname-in-xaml)
   - https://github.com/dotnet/DataGridExtensions/blob/master/src/DataGridExtensionsSample/Views/CopyPasteViewModel.cs
7. IEditableObject
   - [How to: Implement Validation with the DataGrid Control](https://learn.microsoft.com/en-us/dotnet/desktop/wpf/controls/how-to-implement-validation-with-the-datagrid-control?view=netframeworkdesktop-4.8)
8. INotifyDataErrorInfo
   - [WPF Datagrid, how to access validation errors from a ControlTemplate](https://stackoverflow.com/questions/60142690/wpf-datagrid-how-to-access-validation-errors-from-a-controltemplate)
   - [INotifyDataErrorInfo implementation for several values, check that there are no errors in Dictionary (WPF MVVM)](https://learn.microsoft.com/en-us/answers/questions/207982/inotifydataerrorinfo-implementation-for-several-va.html)
   - [WPF Validation - Using INotifyDataErrorInfo](https://kmatyaszek.github.io/wpf%20validation/2019/03/13/wpf-validation-using-inotifydataerrorinfo.html)
9. IDataErrorInfo
   - [How do you get WPF DataGrid validation to work reliably](https://stackoverflow.com/questions/70020227/how-do-you-get-wpf-datagrid-validation-to-work-reliably)
   - [How to: Implement Validation Logic on Custom Objects](https://learn.microsoft.com/en-us/dotnet/desktop/wpf/data/how-to-implement-validation-logic-on-custom-objects?view=netframeworkdesktop-4.8)
10. BindingList
    - [List<T> vs BindingList<T> Advantages/DisAdvantages](https://stackoverflow.com/questions/2243950/listt-vs-bindinglistt-advantages-disadvantages)
    - [Difference between ObservableCollection and BindingList](https://stackoverflow.com/questions/4284663/difference-between-observablecollection-and-bindinglist)
    - [BindingList vs ObservableCollection](https://siderite.dev/blog/bindinglist-vs-observablecollection.html/)
    - [BindingList does not scale…](https://www.themissingdocs.net/wordpress/?p=465)
