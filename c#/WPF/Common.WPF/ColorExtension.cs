using System;
using System.Linq;
using System.Reflection;
using System.Windows.Media;

namespace Common.WPF
{
    public static class ColorExtension
    {
        public static string GetColorName(this Color color)
        {
            PropertyInfo colorProperty = typeof(Colors).GetProperties()
                .FirstOrDefault(p => Color.AreClose((Color)p.GetValue(null), color));
            return colorProperty != null ? colorProperty.Name : string.Empty;
        }

        public static Color? ToColor(this string colorName)
        {
            if (string.IsNullOrWhiteSpace(colorName))
                return null;

            try
            {
                return (Color)ColorConverter.ConvertFromString(colorName);
            }
            catch (FormatException)
            {
                return null;
            }
        }
    }
}


// References:
// [Extract color name from a System.Windows.Media.Color](https://stackoverflow.com/questions/24468671/extract-color-name-from-a-system-windows-media-color)
// [WPF Color from friendly name as string](https://stackoverflow.com/questions/5869503/wpf-color-from-friendly-name-as-string)
