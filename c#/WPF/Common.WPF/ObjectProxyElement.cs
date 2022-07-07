using System;
using System.Windows;
using System.Windows.Data;
using System.Windows.Threading;

namespace Common.WPF
{
    /// <summary>
    /// This proxy is from: http://www.11011.net/wpf-binding-properties
    /// Thanks!
    /// </summary>
    public class ObjectProxyElement : FrameworkElement
    {
        public static readonly DependencyProperty InProperty;
        public static readonly DependencyProperty OutProperty;

        public ObjectProxyElement()
        {
            Visibility = Visibility.Collapsed;
        }

        static ObjectProxyElement()
        {
            var inMetadata = new FrameworkPropertyMetadata(
                delegate (DependencyObject p, DependencyPropertyChangedEventArgs args)
                {
                    if (null != BindingOperations.GetBinding(p, OutProperty))
                        (p as ObjectProxyElement).Out = args.NewValue;
                });

            inMetadata.BindsTwoWayByDefault = false;
            inMetadata.DefaultUpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged;

            InProperty = DependencyProperty.Register("In",
                                                     typeof(object),
                                                     typeof(ObjectProxyElement),
                                                     inMetadata);

            var outMetadata = new FrameworkPropertyMetadata(
                delegate (DependencyObject p, DependencyPropertyChangedEventArgs args)
                {
                    ValueSource source = DependencyPropertyHelper.GetValueSource(p, args.Property);

                    if (source.BaseValueSource != BaseValueSource.Local)
                    {
                        ObjectProxyElement proxy = p as ObjectProxyElement;
                        object expected = proxy.In;
                        if (!ReferenceEquals(args.NewValue, expected))
                        {
                            Dispatcher.CurrentDispatcher.BeginInvoke(
                                DispatcherPriority.DataBind, new Action(delegate
                                {
                                    proxy.Out = proxy.In;
                                }));
                        }
                    }
                });

            outMetadata.BindsTwoWayByDefault = true;
            outMetadata.DefaultUpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged;

            OutProperty = DependencyProperty.Register("Out", typeof(object), typeof(ObjectProxyElement), outMetadata);
        }

        public object In
        {
            get { return GetValue(InProperty); }
            set { SetValue(InProperty, value); }
        }

        public object Out
        {
            get { return GetValue(OutProperty); }
            set { SetValue(OutProperty, value); }
        }
    }
}


// References:
// [Is it possible to bind two source properties to one control property?](https://stackoverflow.com/questions/2002489/is-it-possible-to-bind-two-source-properties-to-one-control-property)
// [[WPF] Custom ValidationRule with an additional parameter](https://michlg.wordpress.com/2010/01/29/wpf-custom-validationrule-with-an-additional-parameter/)
// [WPF Error: Cannot find governing FrameworkElement for target element](https://stackoverflow.com/questions/7660967/wpf-error-cannot-find-governing-frameworkelement-for-target-element)
