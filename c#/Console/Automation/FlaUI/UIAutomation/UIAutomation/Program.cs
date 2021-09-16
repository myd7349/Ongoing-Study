// Please open Ongoing-Study\c#\WinForm\FastMemberDemo\FastMemberDemo.sln

//#define AS_GRID
//#define USE_UIA2

namespace UIAutomation
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Drawing;
    using System.Linq;
    using System.Windows.Forms;

    using FlaUI.Core.AutomationElements;
    using FlaUI.Core.Definitions;
    using FlaUI.Core.WindowsAPI;
#if USE_UIA2
    using FlaUI.UIA2;
#else
    using FlaUI.UIA3;
#endif

    using Common;
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
            var stopwatch = Stopwatch.StartNew();

            var labels = new List<string>();
            var mss = new List<long>();

            if (args.Length != 3 && args.Length != 4)
                return;

            int processId;
            if (!int.TryParse(args[0], out processId))
                return;

            int x;
            int y;
            if (!int.TryParse(args[1], out x) || !int.TryParse(args[2], out y))
                return;

            labels.Add("Parse CLI");
            mss.Add(stopwatch.ElapsedMilliseconds);

            bool highlight = args.Length == 4;

            Point point = new Point(x, y);

            var application = FlaUI.Core.Application.Attach(processId);

            labels.Add("Attach");
            mss.Add(stopwatch.ElapsedMilliseconds);

#if USE_UIA2
            using (var automation = new UIA2Automation())
#else
            using (var automation = new UIA3Automation())
#endif
            {
                labels.Add("Create UIA2Automation");
                mss.Add(stopwatch.ElapsedMilliseconds);

                var mainWindow = application.GetMainWindow(automation);

                labels.Add("GetMainWindow");
                mss.Add(stopwatch.ElapsedMilliseconds);

#if AS_GRID
                var grid = mainWindow.FindFirstChild(ControlType.Table).AsGrid();
                if (grid == null)
                    return;

                labels.Add("Find DataGridView");
                mss.Add(stopwatch.ElapsedMilliseconds);

                if (highlight)
                {
                    grid.DrawHighlight();

                    labels.Add("Highlight DataGridView");
                    mss.Add(stopwatch.ElapsedMilliseconds);
                }

                // WinForms DataGridView doesn't support this pattern.
                var selectedRow = grid.SelectedItem;
                if (selectedRow == null)
                    return;

                if (highlight)
                {
                    selectedRow.DrawHighlight();

                    labels.Add("Highlight row");
                    mss.Add(stopwatch.ElapsedMilliseconds);
                }

                var rowContent = string.Join("\n",
                    selectedRow.FindAllChildren(ControlType.Custom)
                    .Select(element => element.Patterns.Value.Pattern.Value.ToString()));

                labels.Add("Get row content");
                mss.Add(stopwatch.ElapsedMilliseconds);

                var performance = string.Join("\n",
                    labels.Zip(mss, (label, t) => string.Format("{0}: {1}", label, t)));

                MessageBox.Show(
                    rowContent + '\n' + performance,
                    "Selected row:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
#else
                var dataGridView = mainWindow.FindFirstChild(ControlType.Table).AsDataGridView();
                if (dataGridView == null)
                    return;

                labels.Add("Find DataGridView");
                mss.Add(stopwatch.ElapsedMilliseconds);

                if (highlight)
                {
                    dataGridView.DrawHighlight();

                    labels.Add("Highlight DataGridView");
                    mss.Add(stopwatch.ElapsedMilliseconds);
                }

                // Too slow if the DataGridView contains many rows.
                var rows = dataGridView.Rows;

                labels.Add("Get all rows");
                mss.Add(stopwatch.ElapsedMilliseconds);

                foreach (var row in rows)
                {
                    labels.Add("Iterate row");
                    mss.Add(stopwatch.ElapsedMilliseconds);

#if false
                    // WinForms DataGridView doesn't support this pattern.
                    if (row.Patterns.SelectionItem.Pattern.IsSelected)
#elif USE_UIA2
                    if (row.Properties.BoundingRectangle.Value.Contains(point))
#else
                    // FlaUI.UIA2 doesn't support this pattern.
                    // FlaUI.UIA3 supports this pattern.
                    // References:
                    // [LegacyIAccessible in Windows.Automation](https://stackoverflow.com/questions/6837935/legacyiaccessible-in-windows-automation)
                    // https://github.com/TestStack/UIAComWrapper/blob/master/UiaComWrapper/LegacyIAccessiblePattern.cs
                    // https://github.com/FlaUI/FlaUI/blob/master/src/FlaUI.Core/Patterns/LegacyIAccessiblePattern.cs
                    // https://github.com/FlaUI/FlaUI/blob/master/src/FlaUI.UIA2/Patterns/UnsupportedPatterns.cs
                    // https://github.com/FlaUI/FlaUI/blob/master/src/FlaUI.UIA3/Patterns/LegacyIAccessiblePattern.cs
                    if (row.Patterns.LegacyIAccessible.Pattern.State.Value.HasFlag(
                        AccessibilityState.STATE_SYSTEM_SELECTED))
#endif
                    {
                        if (highlight)
                        {
                            row.DrawHighlight();

                            labels.Add("Highlight row");
                            mss.Add(stopwatch.ElapsedMilliseconds);
                        }


                        // In .NET 4.6.1, each cell is DateItem(UIA3) or Custom(UIA2).
                        // In .NET 4.7.2, each cell is a Edit(UIA3) or Custom(UIA2).
                        var cells =
#if USE_UIA2
                            row.FindAllChildren(ControlType.Custom);
#else
                            row.FindAllChildren(ControlType.DataItem);

                        if (cells.Length == 0)
                        {
                            cells = row.FindAllChildren(ControlType.Edit);
                            if (cells.Length > 0)
                                MsgBox.Information("Each cell is a Edit.");
                        }
#endif

                        var rowContent = string.Join("\n",
                            cells.Select(element => element.Name + ' ' + element.Patterns.Value.Pattern.Value.ToString()));

                        labels.Add("Get row content");
                        mss.Add(stopwatch.ElapsedMilliseconds);

                        var performance = string.Join("\n",
                            labels.Zip(mss, (label, t) => string.Format("{0}: {1}", label, t)));

                        MessageBox.Show(
                            rowContent + '\n' + performance,
                            "Selected row:",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Information);
                        break;
                    }
                }
#endif
            }
        }
    }
}


// References:
// [c# FlaUi get all the Values from DataGridView of another program](https://stackoverflow.com/questions/59625560/c-sharp-flaui-get-all-the-values-from-datagridview-of-another-program)
// [LegacyIAccessiblePattern for DataGrids](https://github.com/FlaUI/FlaUI/issues/165)
// [Easy generation of fake/dummy data in C# with Faker.Net](https://blog.elmah.io/easy-generation-of-fake-dummy-data-in-c-with-faker-net/)
// [AutomationElement.FindAll() performance issue](https://stackoverflow.com/questions/32970247/automationelement-findall-performance-issue)
// [trying to Find First Child element that start with some letters or contains some letters](https://github.com/FlaUI/FlaUI/issues/409)
// https://gitter.im/FlaUI/Lobby?at=5943c09b6549436c7d52c510
// > if microsoft didn't implement the grid pattern in their winforms datagridview, there is not much flaui can do
// > but working with the headers and the rows is also possible without the grid patter
// > you can also check for modified datagridview controls
// > like above or here: https://github.com/northwoodspd/UIA.Extensions#datagridview
// > they expose some things to uia
// > but I havent tried that
// [Reading properites from Pane](https://github.com/FlaUI/FlaUI/issues/342)
