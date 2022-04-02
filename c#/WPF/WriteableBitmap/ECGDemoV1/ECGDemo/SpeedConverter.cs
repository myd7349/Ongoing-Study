using System;
using System.Globalization;
using System.Windows.Data;

using Common;


namespace ECGDemo
{
    class SpeedConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value == null)
                throw new ArgumentNullException(nameof(value));

            return $"{value}mm/s";
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value == null)
                throw new ArgumentNullException(nameof(value));

            return MSVCRTHelper.strtod((string)value, IntPtr.Zero);
        }
    }
}
