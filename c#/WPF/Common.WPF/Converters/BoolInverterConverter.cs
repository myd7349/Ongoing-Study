using System;
using System.Globalization;
using System.Windows.Data;

namespace Common.WPF.Converters
{
    public class BoolInverterConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is bool)
                return !(bool)value;

            return value;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is bool)
                return !(bool)value;

            return value;
        }
    }
}


// References:
// [WPF Radiobutton (two) (binding to boolean value)](https://stackoverflow.com/questions/3361362/wpf-radiobutton-two-binding-to-boolean-value)
// https://github.com/BornToBeRoot/NETworkManager/blob/main/Source/NETworkManager.Converters/BooleanReverseConverter.cs
// https://github.com/xceedsoftware/wpftoolkit/blob/master/ExtendedWPFToolkitSolution/Src/Xceed.Wpf.Toolkit/Core/Converters/InverseBoolConverter.cs
