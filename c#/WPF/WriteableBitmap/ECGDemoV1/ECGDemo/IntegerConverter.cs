using System;
using System.Globalization;
using System.Windows.Data;

namespace ECGDemo
{
    class IntegerConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return value;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (!int.TryParse(value.ToString(), out int i))
                return Binding.DoNothing;
            return i;
        }
    }
}


// References:
// [DataBinding Exceptions](https://stackoverflow.com/questions/58437347/databinding-exceptions)
// > No, don't use string properties to hold int and double values.
// [wpf xaml combobox bound to integer data](https://stackoverflow.com/questions/30445915/wpf-xaml-combobox-bound-to-integer-data)
// [WPF Combobox with string Bind to Int property](https://stackoverflow.com/questions/18509316/wpf-combobox-with-string-bind-to-int-property)
