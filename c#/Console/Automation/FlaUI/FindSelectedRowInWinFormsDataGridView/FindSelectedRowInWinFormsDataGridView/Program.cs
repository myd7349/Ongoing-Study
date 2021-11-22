namespace FindSelectedRowInWinFormsDataGridView
{
    using System;
    using System.Linq;
    using System.Windows.Forms;

    using FlaUI.Core.AutomationElements;
    using FlaUI.Core.Definitions;
    using FlaUI.Core.WindowsAPI;
    using FlaUI.UIA3;

    using FlaUI.Extensions;

    class Program
    {
        static void Main()
        {
            while (true)
            {
                Console.Write("Please input target window's title> ");
                var title = Console.ReadLine().Trim();
                if (title == "q" || title == "Q")
                    break;

                Run(title);
            }
        }

        static void Run(string title)
        {
            using (var automation = new UIA3Automation())
            {
                var mainWindow = automation.GetDesktop()
                    .FindFirstChild(
                    element =>
                    {
                        if (element.ControlType == ControlType.Window)
                            return element.AsWindow().Title.Contains(title);

                        return false;
                    });
                if (mainWindow == null)
                {
                    Error("Could not find window by title \"{0}\".", title);
                    return;
                }
                else
                {
                    Information("Main window title: {0}.", mainWindow.AsWindow().Title);
                }

                var firstTable = mainWindow.FindFirstDescendant(ControlType.Table);
                if (firstTable == null)
                {
                    Error("No DataGridView is found on this window.");
                    return;
                }

                var dataGridView = firstTable.AsDataGridView();
                var rows = dataGridView.Rows;
                if (rows == null)
                {
                    Error("There are no rows in the DataGridView.");
                    return;
                }
                else
                {
                    Information("There are {0} rows in this DataGridView.", rows.Length);
                }

                if (rows.Length == 0)
                    return;

                foreach (var row in rows)
                {
                    if (row.Patterns.LegacyIAccessible.Pattern.State.Value.HasFlag(
                        AccessibilityState.STATE_SYSTEM_SELECTED))
                    {
                        var cells = row.FindAllChildren(ControlType.DataItem); // In .NET 4.6.1
                        if (cells.Length == 0)
                            cells = row.FindAllChildren(ControlType.Edit); // In .NET 4.7.2

                        var rowContent = string.Join("\n",
                            cells.Select(element => element.GetValue()));
                        Information("Current selected row: {0}, and row content is:\n{1}",
                            row.Name, rowContent);
                        break;
                    }
                }
            }
        }

        static void Error(string message)
        {
            MessageBox.Show(message, "Error:", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        static void Error(string format, params object?[] args)
        {
            Error(string.Format(format, args));
        }

        static void Information(string message)
        {
            MessageBox.Show(message, "Information:", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        static void Information(string format, params object?[] args)
        {
            Information(string.Format(format, args));
        }
    }
}
