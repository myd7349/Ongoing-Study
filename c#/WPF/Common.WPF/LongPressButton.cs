using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;

namespace Common.WPF
{
    //public class LongPressButton : ButtonBase
    public class LongPressButton : Button
    {
        static LongPressButton()
        {
            //ClickModeProperty.OverrideMetadata(typeof(LongPressButton), new FrameworkPropertyMetadata(ClickMode.Press));
        }

        public LongPressButton()
            : base()
        {
        }

        public event RoutedEventHandler Press
        {
            add => AddHandler(PressEvent, value);
            remove => RemoveHandler(PressEvent, value);
        }

        public static readonly RoutedEvent PressEvent =
            EventManager.RegisterRoutedEvent(
                nameof(Press),
                RoutingStrategy.Bubble,
                typeof(RoutedEventHandler),
                typeof(LongPressButton));

        public event RoutedEventHandler Release
        {
            add => AddHandler(ReleaseEvent, value);
            remove => RemoveHandler(ReleaseEvent, value);
        }

        public static readonly RoutedEvent ReleaseEvent =
            EventManager.RegisterRoutedEvent(
                nameof(Release),
                RoutingStrategy.Bubble,
                typeof(RoutedEventHandler),
                typeof(LongPressButton));

        protected virtual void OnPress()
        {
            RaiseEvent(new RoutedEventArgs(PressEvent, this));
        }

        protected virtual void OnRelease()
        {
            RaiseEvent(new RoutedEventArgs(ReleaseEvent, this));
        }

        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);

            if (IsPressed && (ClickMode != ClickMode.Hover))
                OnPress();
        }

        protected override void OnMouseLeftButtonUp(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonUp(e);

            if (ClickMode != ClickMode.Hover)
                OnRelease();
        }

        //protected override void OnLostMouseCapture(MouseEventArgs e)
        //{
        //    base.OnLostMouseCapture(e);
        //    OnRelease();
        //}

        protected override void OnMouseEnter(MouseEventArgs e)
        {
            base.OnMouseEnter(e);

            if (HandleIsMouseOverChanged())
                e.Handled = true;
        }

        protected override void OnMouseLeave(MouseEventArgs e)
        {
            base.OnMouseLeave(e);

            if (HandleIsMouseOverChanged())
                e.Handled = true;
        }

        private bool HandleIsMouseOverChanged()
        {
            if (ClickMode == ClickMode.Hover)
            {
                if (IsMouseOver)
                    OnPress();
                else
                    OnRelease();

                return true;
            }

            return false;
        }

        protected override void OnKeyDown(KeyEventArgs e)
        {
            base.OnKeyDown(e);

            if ((e.Key == Key.Space) && (ClickMode != ClickMode.Hover))
                OnPress();
        }

        protected override void OnKeyUp(KeyEventArgs e)
        {
            if ((e.Key == Key.Space) && (ClickMode != ClickMode.Hover))
                OnRelease();

            base.OnKeyUp(e);
        }
    }
}


// References:
// [#661 – ButtonBase.Click Event vs. Mouse Click Events](https://wpf.2000things.com/tag/buttonbase/)
// https://learn.microsoft.com/en-us/dotnet/api/system.windows.controls.clickmode?view=windowsdesktop-6.0
// [What is the best way to simulate a Click with MouseUp & MouseDown events or otherwise?](https://stackoverflow.com/questions/4830164/what-is-the-best-way-to-simulate-a-click-with-mouseup-mousedown-events-or-othe)
// https://github.com/dotnet/wpf/blob/main/src/Microsoft.DotNet.Wpf/src/PresentationFramework/System/Windows/Controls/Primitives/ButtonBase.cs#L164
// [WPF Button isPressed and isEnabled problem](https://stackoverflow.com/questions/3518146/wpf-button-ispressed-and-isenabled-problem)
// [ButtonBase.IsPressed Property](https://learn.microsoft.com/en-us/dotnet/api/system.windows.controls.primitives.buttonbase.ispressed?view=windowsdesktop-7.0)
