using System;
using System.Globalization;
using System.Windows;
using System.Windows.Data;

namespace Common.WPF.Converters
{
    public class EqualityToVisibilityConverter : IValueConverter
    {
        public EqualityToVisibilityConverter()
        {
            FalseToVisibility = FalseToVisibility.Collapsed;
        }

        public EqualityToVisibilityConverter(FalseToVisibility falseToVisibility)
        {
            FalseToVisibility = falseToVisibility;
        }

        public FalseToVisibility FalseToVisibility { get; set; }

        public bool Invert { get; set; }

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value == null)
                return Invert;

            if (value is Enum && parameter is string s)
            {
                parameter = Enum.Parse(value.GetType(), s);
            }
            else
            {
                parameter = System.Convert.ChangeType(parameter, value.GetType());
            }

            if (value.Equals(parameter) != Invert)
            {
                return Visibility.Visible;
            }
            else
            {
                if (FalseToVisibility == FalseToVisibility.Collapsed)
                    return Visibility.Collapsed;
                else
                    return Visibility.Hidden;
            }
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}


// References:
// https://github.com/PixiEditor/PixiEditor/blob/master/src/PixiEditor/Helpers/Converters/EqualityBoolToVisibilityConverter.cs
// [binding radiobuttons group to a property in WPF](https://stackoverflow.com/questions/9212873/binding-radiobuttons-group-to-a-property-in-wpf)
