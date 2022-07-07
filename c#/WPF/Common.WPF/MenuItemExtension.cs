//#define USE_SETVALUE

using System.Collections.Generic;
using System.Windows;
//using System.Windows.Data;
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
                        //var oldBinding = BindingOperations.GetBindingBase(item.Key, MenuItem.IsCheckedProperty);
                        //item.Key.IsChecked = false;
                        //var newBinding = BindingOperations.GetBindingBase(item.Key, MenuItem.IsCheckedProperty); // Got null
                        //if (oldBinding != null && newBinding == null)
                        //    BindingOperations.SetBinding(item.Key, MenuItem.IsCheckedProperty, oldBinding);

#if USE_SETVALUE
                        //item.Key.SetValue(MenuItem.IsCheckedProperty, false);
                        item.Key.IsChecked = false;
#else
                        item.Key.SetCurrentValue(MenuItem.IsCheckedProperty, false);           
#endif
                    }
                }
            }
            else // It's not possible for the user to deselect an item
            {
#if USE_SETVALUE
                menuItem.IsChecked = true;
#else
                menuItem.SetCurrentValue(MenuItem.IsCheckedProperty, true);
#endif
            }
        }
    }
}


// References:
// [Mutually exclusive checkable menu items?](https://stackoverflow.com/questions/3652688/mutually-exclusive-checkable-menu-items)
// [Mutually exclusive checkable menu items?](https://stackoverflow.com/questions/3652688/mutually-exclusive-checkable-menu-items/18643222#18643222)
// [setting dependency property in user control style](https://stackoverflow.com/questions/15836548/setting-dependency-property-in-user-control-style)
// https://github.com/PropertyTools/PropertyTools EnumMenuItem
// [[WPF 自定义控件]在MenuItem上使用RadioButton](https://www.cnblogs.com/dino623/p/Uising_RadioButton_in_MenuItem.html)
// https://github.com/DinoChan/Kino.Toolkit.Wpf/blob/master/Kino.Toolkit.Wpf/Kino.Toolkit.Wpf/RadioButtonMenuItem/RadioButtonMenuItem.cs
// [WPF: How to change value and keep binding](https://stackoverflow.com/questions/46398445/wpf-how-to-change-value-and-keep-binding)
// [Set the binding value directly](https://stackoverflow.com/questions/11121057/set-the-binding-value-directly)
// > The problem when simply setting it via DependencyObject.SetValue is that this effectively removes the binding, but I want to change the underlying bound property.
// [WPF Custom DependencyProperty Binding - SetValue set correct value but binded property set receive null](https://stackoverflow.com/questions/54072179/wpf-custom-dependencyproperty-binding-setvalue-set-correct-value-but-binded-pr)
// > Without going into your code too deeply, have you tried using SetCurrentValue instead of SetValue?
// [What's the difference between Dependency Property SetValue() & SetCurrentValue()](https://stackoverflow.com/questions/4230698/whats-the-difference-between-dependency-property-setvalue-setcurrentvalue)
// > SetCurrentValue method changes the effective value of the property, but existing triggers, data bindings, and styles will continue to work.
