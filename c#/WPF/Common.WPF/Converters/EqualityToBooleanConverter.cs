using System;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using System.Windows.Data;

namespace Common.WPF.Converters
{
    public class EqualityToBooleanConverter : IMultiValueConverter
    {
        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            Debug.Assert(values != null);

            if (values.Length < 2)
                throw new ArgumentException(nameof(values));

            var first = values[0];
            if (first == null)
                return values.All(value => value == null);

            for (int i = 1; i < values.Length; ++i)
            {
                if (!first.Equals(values[i]))
                    return false;
            }

            return true;
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}

// References:
// [comparing two dynamic values in DataTrigger](https://stackoverflow.com/questions/37302270/comparing-two-dynamic-values-in-datatrigger)
