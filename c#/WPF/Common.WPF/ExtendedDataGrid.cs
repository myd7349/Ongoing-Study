using System.Collections;
using System.Windows;
using System.Windows.Controls;

namespace Common.WPF
{
    public class ExtendedDataGrid : DataGrid
    {
        public ExtendedDataGrid()
        {
            SelectionChanged += ExtendedDataGrid_SelectionChanged;
        }

        void ExtendedDataGrid_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            SelectedItemsList = SelectedItems;
            
        }

        public IList SelectedItemsList
        {
            get { return (IList)GetValue(SelectedItemsListProperty); }
            set { SetValue(SelectedItemsListProperty, value); }
        }

        public static readonly DependencyProperty SelectedItemsListProperty =
            DependencyProperty.Register(
                "SelectedItemsList",
                typeof(IList),
                typeof(ExtendedDataGrid),
                new PropertyMetadata(null));
    }
}


// References:
// [Select multiple items from a DataGrid in an MVVM WPF project](https://stackoverflow.com/questions/22868445/select-multiple-items-from-a-datagrid-in-an-mvvm-wpf-project)
// [Custom control not inheriting parent's styles](https://stackoverflow.com/questions/37754421/custom-control-not-inheriting-parents-styles)
