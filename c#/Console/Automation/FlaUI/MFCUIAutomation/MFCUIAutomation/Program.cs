// Please open Ongoing-Study\cpp\Win32\MFC\DBVListTest\DBVListTest.sln
namespace MFCUIAutomation
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;
    using System.Windows.Forms;

    using FlaUI.Core.AutomationElements;
    using FlaUI.Core.Definitions;
    using FlaUI.Core.WindowsAPI;
    using FlaUI.UIA3;

    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1)
                return;

            int processId;
            if (!int.TryParse(args[0], out processId))
                return;

            bool highlight = true;

            var application = FlaUI.Core.Application.Attach(processId);

            using (var automation = new UIA3Automation())
            {
                var mainWindow = application.GetMainWindow(automation);

                var list = mainWindow.FindFirstChild(ControlType.List);
                if (list == null)
                    return;

                if (highlight)
                    list.DrawHighlight();

                var stopwatch = Stopwatch.StartNew();

                var listItems = list.FindAllChildren(ControlType.ListItem);

                var elapsedMilliseconds = stopwatch.ElapsedMilliseconds;

                foreach (var item in listItems)
                {
                    var isSelected =
                        item.Patterns.LegacyIAccessible.Pattern.State.Value.HasFlag(
                            AccessibilityState.STATE_SYSTEM_SELECTED);
                    if (isSelected)
                    {
                        if (highlight)
                            item.DrawHighlight();

                        var content = string.Join("\n",
                            item.FindAllChildren().Select(element => element.Name));
                        content += string.Format(
                            "\nIt costs {0}ms to get {1} items.",
                            elapsedMilliseconds, listItems.Length);

                        MessageBox.Show(
                            content,
                            "Selected row:",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Information);
                    }
                }
            }
        }
    }
}
