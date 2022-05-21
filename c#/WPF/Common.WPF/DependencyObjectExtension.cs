using System.Windows;
using System.Windows.Media;

namespace Common.WPF
{
    public static class DependencyObjectExtension
    {
        public static T FindParentOfType<T>(this DependencyObject child) where T : DependencyObject
        {
            DependencyObject parentDepObj = child;
            do
            {
                parentDepObj = VisualTreeHelper.GetParent(parentDepObj);
                T parent = parentDepObj as T;
                if (parent != null) return parent;
            }
            while (parentDepObj != null);
            return null;
        }
    }
}


// References:
// [Navigating up the visual tree in WPF](https://stackoverflow.com/questions/5954948/navigating-up-the-visual-tree-in-wpf)
// [Single click edit in WPF DataGrid](https://stackoverflow.com/questions/3426765/single-click-edit-in-wpf-datagrid)
