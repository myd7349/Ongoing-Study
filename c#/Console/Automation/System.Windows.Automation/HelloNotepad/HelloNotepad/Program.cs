namespace HelloNotepad
{
    using System;
    using System.Diagnostics;
    using System.Windows.Automation;

    using Common;

    class Program
    {
        static void Main()
        {
            var notepadProcess = Process.Start("notepad.exe");
            WaitUntilWindowIsVisible(notepadProcess.MainWindowHandle);

#if false
            var notepadWindow = AutomationElement.FromHandle(notepadProcess.MainWindowHandle);
#else
            var notepadWindow = AutomationElement.RootElement.FindFirstChild("无标题 - 记事本", ControlType.Window);
#endif
            var notepadMenuBar = notepadWindow.FindFirstChild(ControlType.MenuBar);

            var notepadMenuItems = notepadMenuBar.FindAllChildren(ControlType.MenuItem);
            Debug.Assert(notepadMenuItems.Count == 5);
            Console.WriteLine(notepadMenuItems.Count);

            var helpMenu = notepadMenuItems[4];
            helpMenu.Expand();

            var expandedHelpMenu = notepadWindow.FindFirstDescendant(ControlType.Menu);
            var expandedHelpMenuItems = expandedHelpMenu.FindAllChildren(ControlType.MenuItem);
            Debug.Assert(expandedHelpMenuItems.Count == 3);

            Console.ReadKey();
        }

        static void WaitUntilWindowIsVisible(IntPtr window)
        {
            while (window == IntPtr.Zero)
            {
            }
        }
    }
}


// References:
// [Invoking windows task manager with 'performance' tab selected](https://stackoverflow.com/questions/6987130/invoking-windows-task-manager-with-performance-tab-selected)
// [Waiting for window to be ready before calling AutomationElement.FromHandle](https://stackoverflow.com/questions/49611816/waiting-for-window-to-be-ready-before-calling-automationelement-fromhandle)
// [Invoke a Control Using UI Automation](https://docs.microsoft.com/en-us/dotnet/framework/ui-automation/invoke-a-control-using-ui-automation)
// [Invoke method not working on a windows open dialog box](https://stackoverflow.com/questions/58022941/invoke-method-not-working-on-a-windows-open-dialog-box)
// [UIAutomation - InvokePattern only works while Debugging - Button is not Recognized as a Button](https://stackoverflow.com/questions/18641521/uiautomation-invokepattern-only-works-while-debugging-button-is-not-recogniz)
// [Microsoft UIAutomation isn't ALWAYS working on some computers. C#](https://stackoverflow.com/questions/25613115/microsoft-uiautomation-isnt-always-working-on-some-computers-c-sharp)
