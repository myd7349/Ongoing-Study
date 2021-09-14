namespace HelloNotepad
{
    using System;

    using FlaUI.Core;
    using FlaUI.Core.AutomationElements;
    using FlaUI.Core.Definitions;
    using FlaUI.UIA2;

    class Program
    {
        static void Main(string[] args)
        {
#if true
            var notepad = Application.Launch("notepad.exe");
#else
            var notepadProcess = System.Diagnostics.Process.Start("notepad.exe");
            var notepad = Application.Attach(notepadProcess.Id);
#endif

            using (var automation = new UIA2Automation())
            {
                var notepadMainWindow = notepad.GetMainWindow(automation);
                notepadMainWindow.SetForeground();

                var menuBar = notepadMainWindow.FindFirstChild(ControlType.MenuBar);
                menuBar.DrawHighlight();

                var menuBarItems = menuBar.FindAllChildren(ControlType.MenuItem);
#if false
                var helpMenu = menuBarItems[4] as MenuItem; // SO WRONG!!!
#else
                var helpMenu = menuBarItems[4].AsMenuItem();
#endif
                helpMenu.DrawHighlight();
                helpMenu.Expand();

                var expandedHelpMenu = FlaUIHelper.WaitForElement(
#if false
                    () => notepadMainWindow.FindFirstChild(ControlType.Menu)
#else
                    () => notepadMainWindow.FindFirstDescendant(ControlType.Menu)
#endif
                    );
                expandedHelpMenu.DrawHighlight();

                var helpMenuItems = expandedHelpMenu.FindAllChildren(ControlType.MenuItem);
                var aboutMenuItem = helpMenuItems[2].AsMenuItem();
                aboutMenuItem.Invoke();
            }

            notepad.Close();

            Console.ReadKey();
        }
    }
}


// References:
// https://github.com/FlaUI/FlaUI
