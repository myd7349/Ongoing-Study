using System;
using System.Windows;

namespace Common.WPF
{
    public static class WindowHelper
    {
        public static bool GetIsCloseable(DependencyObject obj)
        {
            return (bool)obj.GetValue(IsCloseableProperty);
        }

        public static void SetIsCloseable(DependencyObject obj, bool value)
        {
            obj.SetValue(IsCloseableProperty, value);
        }

        public static readonly DependencyProperty IsCloseableProperty =
            DependencyProperty.RegisterAttached(
                "IsCloseable",
                typeof(bool),
                typeof(WindowHelper),
                new UIPropertyMetadata
                {
                    PropertyChangedCallback = (sender, e) =>
                    {
                        Window window = sender as Window;
                        if (window == null)
                            throw new InvalidOperationException("Can only use WindowHelper.IsCloseable on a Window.");

                        var isCloseable = (bool)e.NewValue;
                        window.EnableCloseButton(isCloseable);
                    }
                });
    }
}
