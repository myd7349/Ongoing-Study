using System;
using System.Globalization;
using System.Windows.Data;

namespace Common.WPF.Converters
{
    public class EnumToDescriptionConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value == null)
                return string.Empty;

            if (targetType != typeof(string))
                throw new ArgumentException(nameof(targetType));

            if (value is Enum enumValue)
                return enumValue.GetDescription();

            throw new ArgumentException($"{value} is not type of Enum.");
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
