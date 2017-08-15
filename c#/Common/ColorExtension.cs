// 2017-08-15T16:33+08:00

namespace Common.Auxiliary.Drawing
{
    using System;
    using System.Collections.Generic;
    using System.Drawing;
    using System.Text.RegularExpressions;


    public interface IColorConverter
    {
        string ToString(Color color);

        Color FromString(string color);
    }

    public delegate string ColorToStringDelegate(Color color);

    public delegate Color StringToColorDelegate(string color);

    public static partial class ColorExtension
    {
        public static string ToString(this Color color, ColorToStringDelegate toString)
        {
            if (toString == null)
                throw new ArgumentNullException("toString");

            return toString(color);
        }

        public static string ToString(this Color color, IColorConverter converter)
        {
            if (converter == null)
                throw new ArgumentNullException("converter");

            return converter.ToString(color);
        }

        public static Color FromString(string color, StringToColorDelegate fromString)
        {
            if (string.IsNullOrWhiteSpace(color))
                return Color.Empty;

            if (fromString == null)
                throw new ArgumentNullException("fromString");

            return fromString(color);
        }

        public static Color FromString(string color, IColorConverter converter)
        {
            if (converter == null)
                throw new ArgumentNullException("converter");

            return converter.FromString(color);
        }
    }

    public class DelegateColorConverter : IColorConverter
    {
        public DelegateColorConverter(ColorToStringDelegate toString, StringToColorDelegate fromString)
        {
            this.toString = toString;
            this.fromString = fromString;
        }

        public string ToString(Color color)
        {
            return color.ToString(toString);
        }

        public Color FromString(string color)
        {
            return ColorExtension.FromString(color, fromString);
        }

        private ColorToStringDelegate toString;
        private StringToColorDelegate fromString;
    }

    public enum ColorFormat
    {
        RGBA,
        RGB,
        Web,
        ARGB,
        BGR,
        COLORREF,
        Auto,
    }

    public class InvalidColorStringException : ArgumentException
    {
    }

    public static partial class ColorExtension
    {
        private static Dictionary<ColorFormat, IColorConverter> converters;

        static ColorExtension()
        {
            converters = new Dictionary<ColorFormat, IColorConverter>();
            converters[ColorFormat.RGBA] = new DelegateColorConverter((color) => ToRGBA(color), FromRGBA);
            converters[ColorFormat.RGB] = new DelegateColorConverter((color) => ToRGB(color), FromRGB);
            converters[ColorFormat.Web] = new DelegateColorConverter(ToWeb, FromWeb);
            converters[ColorFormat.ARGB] = new DelegateColorConverter((color) => ToARGB(color), FromARGB);
            converters[ColorFormat.BGR] = new DelegateColorConverter((color) => ToBGR(color), FromBGR);
            converters[ColorFormat.COLORREF] = new DelegateColorConverter((color) => ToCOLORREF(color, true), FromCOLORREF);
            converters[ColorFormat.Auto] = new DelegateColorConverter(ToStringAuto, FromStringAuto);
        }

        public static string ToStringAuto(this Color color)
        {
            if (color.IsNamedColor)
                return color.Name;

            if (color.A == 255)
                return color.ToWeb();

            return color.ToRGBA();
        }

        public static string ToString(this Color color, ColorFormat format = ColorFormat.Auto)
        {
            if (!Enum.IsDefined(typeof(ColorFormat), format))
                throw new ArgumentException("format");

            return converters[format].ToString(color);
        }

        public static Color FromString(string color, ColorFormat format = ColorFormat.Auto)
        {
            if (color == null)
                throw new ArgumentNullException("color");

            if (!Enum.IsDefined(typeof(ColorFormat), format))
                throw new ArgumentException("format");

            if (string.IsNullOrWhiteSpace(color))
                return Color.Empty;

            return converters[format].FromString(color);
        }

        public static string ToRGBA(this Color color, bool marker = true, bool hex = false)
        {
            if (hex)
                return string.Format(
                    marker ? "rgba({0:x2},{1:x2},{2:x2},{3:x2})" : "{0:x2},{1:x2},{2:x2},{3:x2}",
                    color.R, color.G, color.B, color.A);
            else
                return string.Format(
                    marker ? "rgba({0},{1},{2},{3})" : "{0},{1},{2},{3}",
                    color.R, color.G, color.B, color.A);
        }

        public static string ToRGB(this Color color, bool marker = true, bool hex = false)
        {
            if (hex)
                return string.Format(
                    marker ? "rgb({0:x2},{1:x2},{2:x2})" : "{0:x2},{1:x2},{2:x2}",
                    color.R, color.G, color.B);
            else
                return string.Format(
                    marker ? "rgb({0},{1},{2})" : "{0},{1},{2}",
                    color.R, color.G, color.B);
        }

        private static string ToWeb(this Color color)
        {
            return ColorTranslator.ToHtml(color);
        }

        public static string ToARGB(this Color color, bool marker = true, bool hex = false)
        {
            if (hex)
                return string.Format(
                    marker ? "argb(0x{0:x2},0x{1:x2},0x{2:x2},0x{3:x2})" : "0x{0:x2},0x{1:x2},0x{2:x2},0x{3:x2}",
                    color.A, color.R, color.G, color.B);
            else
                return string.Format(
                    marker ? "argb({0},{1},{2},{3})" : "{0},{1},{2},{3}",
                    color.A, color.R, color.G, color.B);
        }

        public static string ToBGR(this Color color, bool marker = true, bool hex = false)
        {
            if (hex)
                return string.Format(
                    marker ? "bgr(0x{0:x2},0x{1:x2},0x{2:x2})" : "0x{0:x2},0x{1:x2},0x{2:x2}",
                    color.B, color.G, color.R);
            else
                return string.Format(
                    marker ? "bgr({0},{1},{2})" : "{0},{1},{2}",
                    color.B, color.G, color.R);
        }

        public static string ToCOLORREF(this Color color, bool hex = true)
        {
            return string.Format(hex ? "0x{0:x}" : "{0}", ColorTranslator.ToWin32(color));
        }

        public static Color FromStringAuto(string color)
        {
            throw new NotImplementedException();
        }

        public static Color FromRGBA(string color)
        {
            throw new NotImplementedException();
        }

        public static Color FromRGB(string color)
        {
            throw new NotImplementedException();
        }

        public static Color FromWeb(string color)
        {
            return ColorTranslator.FromHtml(color);
        }

        public static Color FromARGB(string color)
        {
            throw new NotImplementedException();
        }

        public static Color FromBGR(string color)
        {
            throw new NotImplementedException();
        }

        public static Color FromCOLORREF(string color)
        {
            throw new NotImplementedException();
        }
    }
}

// References:
// [Web colors](https://en.wikipedia.org/wiki/Web_colors)
// [contrast-ratio](https://github.com/LeaVerou/contrast-ratio)
