// Please open Ongoing-Study\c#\WinForm\FastMemberDemo\FastMemberDemo.sln
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
    using FlaUI.UIA2;

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

            using (var automation = new UIA2Automation())
            {
                labels.Add("Create UIA2Automation");
                mss.Add(stopwatch.ElapsedMilliseconds);

                var mainWindow = application.GetMainWindow(automation);

                labels.Add("GetMainWindow");
                mss.Add(stopwatch.ElapsedMilliseconds);

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

                foreach (var row in dataGridView.Rows)
                {
                    labels.Add("Iterate row");
                    mss.Add(stopwatch.ElapsedMilliseconds);

#if true
                    if (row.Properties.BoundingRectangle.Value.Contains(point))
#else
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

                        var rowContent = string.Join("\n", 
                            row.FindAllChildren(ControlType.Custom)
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
                        break;
                    }
                }
            }
        }
    }
}


// References:
// [c# FlaUi get all the Values from DataGridView of another program](https://stackoverflow.com/questions/59625560/c-sharp-flaui-get-all-the-values-from-datagridview-of-another-program)
// [LegacyIAccessiblePattern for DataGrids](https://github.com/FlaUI/FlaUI/issues/165)
