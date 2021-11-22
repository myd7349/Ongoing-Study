### Appium

Website: 

https://github.com/appium/appium

https://github.com/appium/appium-dotnet-driver

According to [UI Automation: Moving from CodedUI to Appium](https://community.devexpress.com/blogs/winforms/archive/2019/11/25/ui-automation-moving-from-codedui-to-appium.aspx):

> In its [release notes for Visual Studio 2019](https://docs.microsoft.com/en-us/visualstudio/releases/2019/release-notes-v16.0), Microsoft announced the end of life for Coded UI test.
>
> > OSS UI test tools such as Selenium and Appium have gained momentum and  have a strong community backing. Because these frameworks have become  industry standards, we deprecated Coded UI test for automated UI-driven  functional testing. Visual Studio 2019 will be the final version of  Visual Studio with Coded UI test features.
>
> Microsoft recommends [Appium with WinAppDriver](https://github.com/Microsoft/WinAppDriver) for testing desktop and UWP apps, and this message has sparked the  interest among our users: are DevExpress controls compatible with  Appium? We have tested a number of our controls, and the short answer is - yes. Here’s what you should do to create automated UI tests with  Appium.

[Waiting for element before clicking with WinAppDriver](https://stackoverflow.com/questions/56117645/waiting-for-element-before-clicking-with-winappdriver)

### Coded UI

[Use Coded UI tests to test your code](https://docs.microsoft.com/en-us/visualstudio/test/use-ui-automation-to-test-your-code?view=vs-2019)

### FlaUI

https://github.com/FlaUI/FlaUI

https://github.com/FlaUI/FlaUInspect

[Performance improvements](https://github.com/FlaUI/FlaUI/issues/368)

[trying to Find First Child element that start with some letters or contains some letters](https://github.com/FlaUI/FlaUI/issues/409)

https://gitter.im/FlaUI/Lobby?at=5943c09b6549436c7d52c510

> if microsoft didn't implement the grid pattern in their winforms datagridview, there is not much flaui can do but working with the headers and the rows is also possible without the grid patter you can also check for modified datagridview controls like above or here: https://github.com/northwoodspd/UIA.Extensions#datagridview they expose some things to uia but I havent tried that

[Element finding mechanisms in FlaUI | Windows Automation](https://www.youtube.com/watch?v=7OwF3oXhw14)

[Issues finding windows in .NET Core app](https://github.com/FlaUI/FlaUI/issues/298)

> ```csharp
> using FlaUI.UIA3;
> 
> var app = FlaUI.Core.Application.Launch(exePath);
> app.WaitWhileMainHandleIsMissing(TimeSpan.FromSeconds(2)); // Or just Thread.Sleep(...)
> using (var automation = new UIA3Automation())
> {
>     var window = app.GetAllTopLevelWindows(automation).First();
> }
> ```

### MS UI Automation Framework

https://docs.microsoft.com/en-us/dotnet/framework/ui-automation/

https://github.com/dotnet/docs/tree/main/docs/framework/ui-automation

[System.Windows.Automation is extremely slow](https://stackoverflow.com/questions/41768046/system-windows-automation-is-extremely-slow)

> `System.Windows.Automation` is EXTREMELY **slow**. 
>
> `System.Windows.Automation` is full of **bugs**. It may not return all children of an AutomationElement, which is a very severe bug.
>
> Apart from that the implementation is **not thread safe**.
>
> `System.Windows.Automation` is deprecated. Do not use it!
>
> In the [MSDN](https://msdn.microsoft.com/en-us/library/windows/desktop/ee684076(v=vs.85).aspx) you find the following note:
>
> > UI Automation was first available in Windows XP as part of the  Microsoft .NET Framework. Although an unmanaged C++ API was also  published at that time, the usefulness of client functions was limited  because of interoperability issues. For Windows 7, the API has been  rewritten in the Component Object Model (COM).   Although the library functions introduced in the earlier version of  UI Automation are still documented, they should not be used in new  applications.
>
> The solution to slow performance is to use the new **IUIAutomationElement** COM interface instead of the old System.Windows.Automation C# interface. After that the code will be running **lightning fast**! 
>
> Apart from that the new interface offers much more patterns and  Microsoft is extending it continously. In the Windows 10 SDK  (UIAutomationClient.h and UIAutomationCore.h) several patterns and  properties have been added which are not available in the .NET  Automation framework.

> For **.NET Forms applications** Microsoft did not make much effort to support them. The .NET **Calendar** control cannot be automated at all. The entire control is not even  recognized as Calendar. It has the ControlType "Pane" with no child  elements in it. The same applies to the **DateTimePicker**. And for complex controls like **DataGrid** and **PropertyGrid** the only implemented pattern is `LegacyIAccessible` which is a poor support. These controls should implement at least the `Table` and the `Grid` and the `ScrollItem` pattern.

[Using UI Automation, Winforms Button Invoking multiple times](https://stackoverflow.com/questions/12591649/using-ui-automation-winforms-button-invoking-multiple-times)

[CUIAutomation object](https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ff384838(v=vs.85))

- [Creating the CUIAutomation Object](https://docs.microsoft.com/en-us/windows/win32/winauto/uiauto-creatingcuiautomation)

[UI Automation Clients Overview](https://docs.microsoft.com/en-us/windows/win32/winauto/uiauto-clientsoverview)

[UI Automation Support for Standard Controls](https://docs.microsoft.com/en-us/dotnet/framework/ui-automation/ui-automation-support-for-standard-controls)

[Bugslayer: GUI Control to Major Tom](https://docs.microsoft.com/en-us/archive/msdn-magazine/2007/march/bugslayer-gui-control-to-major-tom)

[System.Windows.Automation is very slow at enumerating table rows vs. UIAutomationCore](https://stackoverflow.com/questions/28353671/system-windows-automation-is-very-slow-at-enumerating-table-rows-vs-uiautomatio)

[UI Automation Tree Overview](https://docs.microsoft.com/en-us/windows/win32/winauto/uiauto-treeoverview)

[Expose the Content of a Table Using UI Automation](https://docs.microsoft.com/en-us/dotnet/framework/ui-automation/expose-the-content-of-a-table-using-ui-automation)

[Obtaining UI Automation Elements](https://docs.microsoft.com/en-us/windows/win32/winauto/uiauto-obtainingelements)

> Other Ways to Retrieve an Element:
>
> - From an event
> - From a point
> - From a Window handle
> - From the Focused control
>   - [Expose the Content of a Table Using UI Automation](https://docs.microsoft.com/en-us/dotnet/framework/ui-automation/expose-the-content-of-a-table-using-ui-automation)
>   - [TrackFocus Sample](https://docs.microsoft.com/en-us/previous-versions/dotnet/netframework-3.5/ms771428(v=vs.90))

[AutomationElement shows up using Inspect.exe but does show not up when using UIAutomationCore.dll or System.Windows.Automation](https://stackoverflow.com/questions/9282275/automationelement-shows-up-using-inspect-exe-but-does-show-not-up-when-using-uia)

> ```cs
> public class ConditionMatcher : IMatchConditions
> {
>     public bool Matches(AutomationElement element, Condition condition)
>     {
>         return new TreeWalker(condition).Normalize(element) != null;
>     }
> }
> ```

[C# System.Windows.Automation get element text](https://stackoverflow.com/questions/23850176/c-sharp-system-windows-automation-get-element-text)

> ```cs
> public static class AutomationExtensions
> {
>     public static string GetText(this AutomationElement element)
>     {
>         object patternObj;
>         if (element.TryGetCurrentPattern(ValuePattern.Pattern, out patternObj))
>         {
>             var valuePattern = (ValuePattern)patternObj;
>             return valuePattern.Current.Value;
>         }
>         else if (element.TryGetCurrentPattern(TextPattern.Pattern, out patternObj))
>         {
>             var textPattern = (TextPattern)patternObj;
>             return textPattern.DocumentRange.GetText(-1).TrimEnd('\r'); // often there is an extra '\r' hanging off the end.
>         }
>         else
>         {
>             return element.Current.Name;
>         }
>     }
> }
> ```

### TestStack.White

[Looking for a GUI automation framework that works with .NET (WinForms)](https://stackoverflow.com/questions/5562559/looking-for-a-gui-automation-framework-that-works-with-net-winforms)

https://github.com/TestStack/White

### TestStack.UIAComWrapper

[LegacyIAccessible in Windows.Automation](https://stackoverflow.com/questions/6837935/legacyiaccessible-in-windows-automation)

> ```cs
> if ((bool) child.GetCurrentPropertyValue(AutomationElementIdentifiers.IsLegacyIAccessiblePatternAvailableProperty)) {
>     var pattern = ((LegacyIAccessiblePattern) child.GetCurrentPattern(LegacyIAccessiblePattern.Pattern));
>     var state = pattern.GetIAccessible().accState;
> 
>     // Do something with state...
> }
> ```

### WinAppDriver

https://github.com/microsoft/WinAppDriver

[Window App Automation using - Microsoft WinAppDriver](https://www.youtube.com/watch?v=CnwOEkIYSUk)

[UI Tests for Desktop and UWP Apps](https://www.youtube.com/watch?v=zlnq3HAhwr8)

### Winium

https://github.com/2gis/Winium

https://github.com/2gis/Winium.Desktop

