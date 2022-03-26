using System;
using System.Globalization;
using System.Windows.Data;

namespace ECGDemo
{
    class TimeSpanConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var timeSpan = (TimeSpan)value;
            return string.Format("{0:00}:{1:mm}:{1:ss}", (int)timeSpan.TotalHours, timeSpan);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}


// References:
// [How to format TimeSpan in XAML](https://stackoverflow.com/questions/4563081/how-to-format-timespan-in-xaml)
// [Format TimeSpan greater than 24 hour](https://stackoverflow.com/questions/3505230/format-timespan-greater-than-24-hour)
// [C# convert int to string with padding zeros?](https://stackoverflow.com/questions/4325267/c-sharp-convert-int-to-string-with-padding-zeros)
