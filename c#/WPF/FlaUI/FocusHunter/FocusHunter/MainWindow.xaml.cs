namespace FocusHunter
{
    using System;
    using System.Collections.ObjectModel;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Linq;
    using System.Windows.Controls;

    using FlaUI.Core.AutomationElements;
    using FlaUI.UIA3;

    using MahApps.Metro.Controls;

    using Common.IO;

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : MetroWindow
    {
        public MainWindow()
        {
            FocusEntries = new ObservableCollection<FocusEntryModel>();
            //DataContext = this;

            InitializeComponent();

            automation_.RegisterFocusChangedEvent(OnFocusChanged);
            Closing += MainWindow_Closing;
        }

        // What if we made this private?
#if false
        private ObservableCollection<FocusEntryModel> FocusEntries
        {
            get;
            set;
        }
#else
        public ObservableCollection<FocusEntryModel> FocusEntries
        {
            get;
            private set;
        }
#endif

        private void MainWindow_Closing(object sender, CancelEventArgs e)
        {
            automation_.Dispose();
        }

        private void OnFocusChanged(AutomationElement element)
        {
            try
            {
                // Avoid recursion
                var processId = element.Properties.ProcessId;
                if (processId == Process.GetCurrentProcess().Id)
                    return;
            }
            catch
            {
            }

            Debug.WriteLine(element.ToString());
            Debug.WriteLine("-------------------------------------");

            Dispatcher.BeginInvoke(
                new Action(() =>
                {
                    FocusEntries.Add(new FocusEntryModel(element));

                    var lastItem = focusEntriesListView_.Items.Cast<object>().LastOrDefault();
                    if (lastItem != null)
                        focusEntriesListView_.ScrollIntoView(lastItem);
                }));
        }

        private void ListViewItem_MouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            var focusEntry = ((ListViewItem)sender).Content as FocusEntryModel;
            if (focusEntry == null || string.IsNullOrEmpty(focusEntry.Path))
                return;

            IOHelper.LocateFileInExplorer(focusEntry.Path);
        }

        private UIA3Automation automation_ = new UIA3Automation();
    }
}


// References:
// [How to: Make Data Available for Binding in XAML](https://docs.microsoft.com/en-us/dotnet/desktop/wpf/data/how-to-make-data-available-for-binding-in-xaml?view=netframeworkdesktop-4.8)
// [Bind an ObservableCollection to a ListView](https://stackoverflow.com/questions/10659347/bind-an-observablecollection-to-a-listview)
// [Can't get WPF ListView to bind to ObservableCollection](https://stackoverflow.com/questions/4891533/cant-get-wpf-listview-to-bind-to-observablecollection/4891763)
// https://www.youtube.com/watch?v=_TTQFc_YHTU
// [How to: Create and Bind to an ObservableCollection](https://docs.microsoft.com/en-us/dotnet/desktop/wpf/data/how-to-create-and-bind-to-an-observablecollection?view=netframeworkdesktop-4.8)
// https://github.com/erizet/NlogViewer
// [populate listview dynamically](https://stackoverflow.com/questions/4038444/populate-listview-dynamically)
// [WPF ListView: Attaching a double-click (on an item) event](https://stackoverflow.com/questions/728205/wpf-listview-attaching-a-double-click-on-an-item-event)
// [Basic LINQ expression for an ItemCollection](https://stackoverflow.com/questions/1160854/basic-linq-expression-for-an-itemcollection)
// [WPF Always On Top](https://stackoverflow.com/questions/20050426/wpf-always-on-top)
