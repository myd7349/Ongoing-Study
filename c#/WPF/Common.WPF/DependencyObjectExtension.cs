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

        // TODO:
        // public static IEnumerable<T> FindDescendents<T>(this DependencyObject parent)

        public static T FindDescendent<T>(this DependencyObject parent, string childName = null)
            where T : DependencyObject
        {
            if (parent == null)
                return null;

            T foundChild = null;

            int childrenCount = VisualTreeHelper.GetChildrenCount(parent);
            for (int i = 0; i < childrenCount; i++)
            {
                var child = VisualTreeHelper.GetChild(parent, i);
                // If the child is not of the request child type child
                T childType = child as T;
                if (childType == null)
                {
                    // recursively drill down the tree
                    foundChild = FindDescendent<T>(child, childName);

                    // If the child is found, break so we do not overwrite the found child. 
                    if (foundChild != null)
                        break;
                }
                else if (!string.IsNullOrEmpty(childName))
                {
                    var frameworkElement = child as FrameworkElement;
                    // If the child's name is set for search
                    if (frameworkElement != null && frameworkElement.Name == childName)
                    {
                        // if the child's name is of the request name
                        foundChild = (T)child;
                        break;
                    }
                }
                else
                {
                    // child element found.
                    foundChild = (T)child;
                    break;
                }
            }

            return foundChild;
        }
    }
}


// References:
// [Navigating up the visual tree in WPF](https://stackoverflow.com/questions/5954948/navigating-up-the-visual-tree-in-wpf)
// [Single click edit in WPF DataGrid](https://stackoverflow.com/questions/3426765/single-click-edit-in-wpf-datagrid)
// [How can I find WPF controls by name or type?](https://stackoverflow.com/questions/636383/how-can-i-find-wpf-controls-by-name-or-type)
// [How to properly throw an Exception inside yield return method in C#](https://stackoverflow.com/questions/38249895/how-to-properly-throw-an-exception-inside-yield-return-method-in-c-sharp)
// [Inspect XAML properties while debugging](https://learn.microsoft.com/en-us/visualstudio/xaml-tools/inspect-xaml-properties-while-debugging?view=vs-2022)
// [WPF: In an attached property, how to wait until visual tree loaded properly?](https://stackoverflow.com/questions/36037963/wpf-in-an-attached-property-how-to-wait-until-visual-tree-loaded-properly)
