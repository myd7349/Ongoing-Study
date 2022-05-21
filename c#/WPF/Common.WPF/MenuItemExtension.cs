using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;

namespace Common.WPF
{
    public class MenuItemExtension
    {
        public static Dictionary<MenuItem, string> ElementToGroupNames = new Dictionary<MenuItem, string>();

        public static readonly DependencyProperty GroupNameProperty =
            DependencyProperty.RegisterAttached("GroupName",
                typeof(string), typeof(MenuItemExtension),
                new PropertyMetadata(string.Empty, OnGroupNameChanged));

        public static void SetGroupName(MenuItem element, string value)
        {
            element.SetValue(GroupNameProperty, value);
        }

        public static string GetGroupName(MenuItem element)
        {
            return element.GetValue(GroupNameProperty).ToString();
        }

        private static void OnGroupNameChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            // Add an entry to the group name collection
            var menuItem = d as MenuItem;

            if (menuItem != null)
            {
                var newGroupName = e.NewValue.ToString();
                var oldGroupName = e.OldValue.ToString();
                if (string.IsNullOrEmpty(newGroupName))
                {
                    // Removing the toggle button from grouping
                    RemoveCheckboxFromGrouping(menuItem);
                }
                else
                {
                    // Switching to a new group
                    if (newGroupName != oldGroupName)
                    {
                        if (!string.IsNullOrEmpty(oldGroupName))
                        {
                            // Remove the old group mapping
                            RemoveCheckboxFromGrouping(menuItem);
                        }
                        ElementToGroupNames.Add(menuItem, e.NewValue.ToString());
                        menuItem.Click += MenuItemClicked;
                    }
                }
            }
        }

        private static void RemoveCheckboxFromGrouping(MenuItem checkBox)
        {
            ElementToGroupNames.Remove(checkBox);
            checkBox.Click -= MenuItemClicked;
        }

        static void MenuItemClicked(object sender, RoutedEventArgs e)
        {
            var menuItem = e.OriginalSource as MenuItem;
            if (menuItem.IsChecked)
            {
                foreach (var item in ElementToGroupNames)
                {
                    if (item.Key != menuItem && item.Value == GetGroupName(menuItem))
                    {
                        item.Key.IsChecked = false;
                    }
                }
            }
            else // It's not possible for the user to deselect an item
            {
                menuItem.IsChecked = true;
            }
        }
    }
}


// References:
// [Mutually exclusive checkable menu items?](https://stackoverflow.com/questions/3652688/mutually-exclusive-checkable-menu-items)
// [Mutually exclusive checkable menu items?](https://stackoverflow.com/questions/3652688/mutually-exclusive-checkable-menu-items/18643222#18643222)
// [setting dependency property in user control style](https://stackoverflow.com/questions/15836548/setting-dependency-property-in-user-control-style)
// https://github.com/PropertyTools/PropertyTools EnumMenuItem
