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

### MS UI Automation Framework

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

[Using UI Automation, Winforms Button Invoking multiple times](https://stackoverflow.com/questions/12591649/using-ui-automation-winforms-button-invoking-multiple-times)

[CUIAutomation object](https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ff384838(v=vs.85))

[UI Automation Clients Overview](https://docs.microsoft.com/en-us/windows/win32/winauto/uiauto-clientsoverview)

[UI Automation Support for Standard Controls](https://docs.microsoft.com/en-us/dotnet/framework/ui-automation/ui-automation-support-for-standard-controls)

[Bugslayer: GUI Control to Major Tom](https://docs.microsoft.com/en-us/archive/msdn-magazine/2007/march/bugslayer-gui-control-to-major-tom)

### TestStack.White

[Looking for a GUI automation framework that works with .NET (WinForms)](https://stackoverflow.com/questions/5562559/looking-for-a-gui-automation-framework-that-works-with-net-winforms)

https://github.com/TestStack/White

### WinAppDriver

https://github.com/microsoft/WinAppDriver

### Winium

https://github.com/2gis/Winium

https://github.com/2gis/Winium.Desktop

