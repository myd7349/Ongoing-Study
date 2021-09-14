https://github.com/aelij/RoslynPad

[FindFirstDescendant fails to find the control if the UI is not in focus](https://github.com/FlaUI/FlaUI/issues/145)

> Here is a RoslynPad script which successfully searches for "Hello" on google (you might need to adjust the name/automation id):
>
> ```csharp
> #r "$NuGet\FlaUI.Core\2.0.0-alpha6\lib\net45\FlaUI.Core.dll"
> #r "$NuGet\FlaUI.UIA3\2.0.0-alpha6\lib\net45\FlaUI.UIA3.dll"
> #r "$NuGet\FlaUI.UIA3\2.0.0-alpha6\lib\net45\Interop.UIAutomationClient.dll"
> #r "PresentationCore"
> #r "PresentationFramework"
> #r "WindowsBase"
> 
> using System.Diagnostics;
> using FlaUI.Core;
> using FlaUI.Core.AutomationElements;
> using FlaUI.UIA3;
> 
> using (var app = Application.Attach(2216))
> {
>     using (var automation = new UIA3Automation())
>     {
>         var window = app.GetAllTopLevelWindows(automation)[0];
>         var input = window.FindFirstDescendant(cf => cf.ByName("Suche").And(cf.ByAutomationId("lst-ib")));
>         input.Patterns.Value.Pattern.SetValue("Hello");
>         var searchButton = window.FindFirstDescendant(cf => cf.ByName("Google-Suche")).AsButton();
>         searchButton.Invoke();
>     }
> }
> ```

