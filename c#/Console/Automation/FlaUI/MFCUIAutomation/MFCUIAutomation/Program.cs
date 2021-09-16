// Please open Ongoing-Study\cpp\Win32\MFC\DBVListTest\DBVListTest.sln
#define AS_GRID

namespace MFCUIAutomation
{
    using System;
    using System.Diagnostics;
    using System.Linq;
    using System.Windows.Forms;

    using FlaUI.Core.AutomationElements;
    using FlaUI.Core.Definitions;
#if !AS_GRID
    using FlaUI.Core.WindowsAPI;
#endif
    using FlaUI.UIA3;

    using FlaUI.Extensions;

    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Run(args);
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    ex.ToString(),
                    "Error:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }

        static void Run(string[] args)
        {
            if (args.Length != 1)
                return;

            int processId;
            if (!int.TryParse(args[0], out processId))
                return;

            var currentProcessId = Process.GetCurrentProcess().Id;

            bool highlight = (currentProcessId % 10 == 2) || (currentProcessId % 10 == 6);
            if (highlight)
                MessageBox.Show("Highlight.", "Info:", MessageBoxButtons.OK, MessageBoxIcon.Information);
            else
                MessageBox.Show("Will not highlight.", "Info:", MessageBoxButtons.OK, MessageBoxIcon.Information);

            var application = FlaUI.Core.Application.Attach(processId);

            using (var automation = new UIA3Automation())
            {
                var mainWindow = application.GetMainWindow(automation);

                var list = mainWindow.FindFirstChild(ControlType.List);
                if (list == null)
                    return;

                if (highlight)
                    list.DrawHighlight();

#if AS_GRID
                var grid = list.AsGrid();
                if (grid == null)
                    return;

                var stopwatch = Stopwatch.StartNew();

                var selectedRow = grid.SelectedItem;
                if (selectedRow == null)
                    return;

                var elapsedMilliseconds = stopwatch.ElapsedMilliseconds;

                if (highlight)
                    selectedRow.DrawHighlight();

                var content = string.Join("\n",
                    selectedRow.FindAllChildren().Select(element => element.Name));
                content += string.Format(
                    "\nIt costs {0}ms to get the selected item.",
                    elapsedMilliseconds);

                MessageBox.Show(
                    content,
                    "Selected row:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
#else
                var stopwatch = Stopwatch.StartNew();

                // Too slow if the list contains many items.
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
#endif
            }
        }
    }
}


// References:
// [AutomationElement.FindAll() performance issue](https://stackoverflow.com/questions/32970247/automationelement-findall-performance-issue)
// [Why are there no odd Windows process IDs?](https://superuser.com/questions/936773/why-are-there-no-odd-windows-process-ids)
