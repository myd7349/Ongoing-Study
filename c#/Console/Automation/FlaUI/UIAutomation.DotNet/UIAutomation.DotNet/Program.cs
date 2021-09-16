// Please open Ongoing-Study\c#\WinForm\FastMemberDemoDotNet\FastMemberDemoDotNet.sln
#define USE_TREE_WALKER
namespace UIAutomation
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;
    using System.Windows.Forms;

    using FlaUI.Core.AutomationElements;
    using FlaUI.Core.Definitions;
    using FlaUI.UIA2;

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

            if (args.Length != 1 && args.Length != 2)
                return;

            int processId;
            if (!int.TryParse(args[0], out processId))
                return;

            labels.Add("Parse CLI");
            mss.Add(stopwatch.ElapsedMilliseconds);

            bool highlight = args.Length == 2;

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

                // Don't work.
                //var selectedRow = grid.SelectedItem;
                // Still don't work. WinForms DataGridView supports SelectionItemPattern.
                //var selectedRow = grid.Patterns.SelectionItem.Pattern.SelectionContainer.Value;
                //if (selectedRow == null)
                //    return;

                
#if USE_TREE_WALKER
                var selectedRow = grid.FindFirstChild(
                    element =>
                    {
                        if (element.ControlType != ControlType.DataItem)
                            return false;
                        else
                            return element.Patterns.SelectionItem.Pattern.IsSelected;
                    });
                if (selectedRow == null)
                    return;

                labels.Add("Find selected row");
                mss.Add(stopwatch.ElapsedMilliseconds);

                var rowContent = string.Join(" ",
                    selectedRow.FindAllChildren(ControlType.Text)
                    .Select(element => element.Name));

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
#if true
                // Not very slow.
                var rows = grid.Rows;
#else
                var rows = grid.FindAllChildren(ControlType.DataItem);
#endif

                labels.Add("Get all rows");
                mss.Add(stopwatch.ElapsedMilliseconds);

                labels.Add("Get all rows");
                mss.Add(stopwatch.ElapsedMilliseconds);

                foreach (var row in rows)
                {
                    labels.Add("Iterate row");
                    mss.Add(stopwatch.ElapsedMilliseconds);

                    // OK. Now DataGridView supports this pattern.
                    if (row.Patterns.SelectionItem.Pattern.IsSelected)
                    {
                        if (highlight)
                        {
                            // Doesn't support this pattern.
                            //row.DrawHighlight();

                            labels.Add("Highlight row");
                            mss.Add(stopwatch.ElapsedMilliseconds);
                        }

                        var rowContent = string.Join(" ",
                            row.FindAllChildren(ControlType.Text)
                            .Select(element => element.Name));

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
