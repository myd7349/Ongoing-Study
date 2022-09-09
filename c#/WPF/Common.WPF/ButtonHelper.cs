using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;

namespace Common.WPF
{
    public class ButtonHelper
    {
        public static bool? GetDialogResult(DependencyObject obj)
        {
            return (bool?)obj.GetValue(DialogResultProperty);
        }

        public static void SetDialogResult(DependencyObject obj, bool? value)
        {
            obj.SetValue(DialogResultProperty, value);
        }

        public static readonly DependencyProperty DialogResultProperty = DependencyProperty.RegisterAttached("DialogResult", typeof(bool?), typeof(ButtonHelper), new UIPropertyMetadata
        {
            PropertyChangedCallback = (obj, e) =>
            {
                // Implementation of DialogResult functionality
                Button button = obj as Button;
                if (button == null)
                    throw new InvalidOperationException("Can only use ButtonHelper.DialogResult on a Button control");

                button.Click += (sender, e2) =>
                {
                    Window.GetWindow(button).DialogResult = GetDialogResult(button);
                };
            }
        });

        public static readonly DependencyProperty ShowContextMenuOnClickProperty =
            DependencyProperty.RegisterAttached(
                "ShowContextMenuOnClick",
                typeof(bool),
                typeof(ButtonHelper),
                new UIPropertyMetadata(OnShowContextMenuOnClickPropertyChanged));

        public static bool GetShowContextMenuOnClick(DependencyObject obj)
        {
            return (bool)obj.GetValue(ShowContextMenuOnClickProperty);
        }

        public static void SetShowContextMenuOnClick(DependencyObject obj, bool value)
        {
            obj.SetValue(ShowContextMenuOnClickProperty, value);
        }

        private static void OnShowContextMenuOnClickPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var button = d as Button;
            if (button == null)
                throw new InvalidOperationException("Can only use ButtonHelper.ShowContextMenuOnClick on a Button control.");

            var showContextMenu = (bool)e.NewValue;
            if (showContextMenu)
                button.Click += Button_Click;
            else
                button.Click -= Button_Click;
        }

        private static void Button_Click(object sender, RoutedEventArgs e)
        {
            var button = sender as Button;
            var menu = button.ContextMenu;
            menu.PlacementTarget = button;
            menu.Placement = PlacementMode.MousePoint;
            menu.IsOpen = true;
        }
    }
}

// References:
// [Where is Button.DialogResult in WPF?](https://stackoverflow.com/questions/1759372/where-is-button-dialogresult-in-wpf)
// https://github.com/yck1509/ConfuserEx/blob/master/ConfuserEx/MainWindow.xaml
// https://github.com/yck1509/ConfuserEx/blob/master/ConfuserEx/MainWindow.xaml.cs
