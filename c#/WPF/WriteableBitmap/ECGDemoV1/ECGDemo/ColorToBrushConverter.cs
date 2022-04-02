using System;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Media;


namespace ECGDemo
{
    public class ColorToBrushConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            //return brushConverter_.ConvertFrom(value.ToString());
            return new SolidColorBrush((Color)value);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return (value as SolidColorBrush).Color;
        }

        //private static readonly BrushConverter brushConverter_ = new BrushConverter();
    }
}


// References:
// [WPF Binding to change fill color of ellipse](https://stackoverflow.com/questions/2451326/wpf-binding-to-change-fill-color-of-ellipse)
// [C# WPF Rectangle Fill Binding](https://stackoverflow.com/questions/41103795/c-sharp-wpf-rectangle-fill-binding)
