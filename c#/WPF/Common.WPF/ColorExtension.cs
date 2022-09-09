using System;
using System.Linq;
using System.Reflection;
using System.Windows.Media;
using System.Windows.Media.Imaging;

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

        public static int ToBgr32(this Color color)
        {
            return ((color.R << 16) | (color.G << 8) | (color.B));
        }

        public static uint ToPbgra32(this Color color)
        {
            uint A = color.A;
            uint R = color.R;
            uint G = color.G;
            uint B = color.B;

            if (A != 255)
            {
                R = R * A / 255;
                G = G * A / 255;
                B = B * A / 255;
            }

            return (A << 24) | (R << 16) | (G << 8) | B;
        }
    }
}


// References:
// [Extract color name from a System.Windows.Media.Color](https://stackoverflow.com/questions/24468671/extract-color-name-from-a-system-windows-media-color)
// [WPF Color from friendly name as string](https://stackoverflow.com/questions/5869503/wpf-color-from-friendly-name-as-string)
// [WriteableBitmap Class](https://learn.microsoft.com/en-us/dotnet/api/system.windows.media.imaging.writeablebitmap?view=netframework-4.7.2)
// [When should I use PixelFormats.Pbgra32 in WPF application?](https://stackoverflow.com/questions/40826742/when-should-i-use-pixelformats-pbgra32-in-wpf-application)
