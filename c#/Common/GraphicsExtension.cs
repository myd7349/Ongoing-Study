// 2017-04-07T12:17+08:00
using System;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text.RegularExpressions;


namespace Common.Auxiliary.Drawing
{
    using COLORREF = UInt32;

    public static class GraphicsExtension
    {
        public static Color GetPixel(this Graphics g, int x, int y)
        {
            var hdc = g.GetHdc();
            COLORREF rgb = Gdi32Helper.GetPixel(hdc, x, y);
            g.ReleaseHdc(hdc);
            return ColorExtension.FromCOLORREF(rgb);
        }

        public static Color SetPixel(this Graphics g, int x, int y, Color color)
        {
            var hdc = g.GetHdc();
            COLORREF rgb = Gdi32Helper.SetPixel(hdc, x, y, color.ToCOLORREF());
            g.ReleaseHdc(hdc);
            return ColorExtension.FromCOLORREF(rgb);
        }

        public static void SetPixel(this Graphics graphics, float x, float y, Brush brush)
        {
            Debug.Assert(graphics != null);
            Debug.Assert(brush != null);

            graphics.FillRectangle(brush, x, y, 1.0F, 1.0F); // [1]
        }

        public static void DrawRectangle(this Graphics graphics, Pen pen, RectangleF rect)
        {
            Debug.Assert(graphics != null);
            Debug.Assert(pen != null);

            graphics.DrawRectangle(pen, rect.X, rect.Y, rect.Width, rect.Height);
        }

        private static bool DrawSingleLineStringAutoWrap(Graphics g, Font font, Brush brush,
            float left, ref float top, float right, float bottom,
            float textHeight, string text, bool clip)
        {
            Debug.Assert(textHeight > 0.0);

            int start = 0;
            int end = 0;

            while (start < text.Length)
            {
                for (end = start; end <= text.Length; ++end)
                {
                    var partOfTheText = new string(text.Skip(start).Take(end - start).ToArray()); // [5][6][7]
                    var size = g.MeasureString(partOfTheText, font);
                    textHeight = size.Height;
                    if (left + size.Width >= right)
                    {
                        end -= 1;
                        break;
                    }
                }

                if (clip && (top + textHeight > bottom))
                    return false;

                var s = new string(text.Skip(start).Take(end - start).ToArray());
                g.DrawString(s, font, brush, left, top);

                // Auto wrap
                if (end < text.Length)
                    top += textHeight;

                start = end;
            }

            return true;
        }

        public static void DrawStringInRect(this Graphics g, Font font, Brush brush, Rectangle rect, string text, bool clip = true, string templateText = "ABC")
        {
            var rectF = new RectangleF(rect.X, rect.Y, rect.Width, rect.Height);
            DrawStringInRect(g, font, brush, rectF, text, clip, templateText);
        }

        public static void DrawStringInRect(this Graphics g, Font font, Brush brush, RectangleF rect, string text, bool clip = true, string templateText = "ABC")
        {
            Debug.Assert(g != null);
            Debug.Assert(font != null);
            Debug.Assert(brush != null);
            Debug.Assert(templateText.Length > 0);
            if (g == null || font == null || brush == null)
                throw new ArgumentNullException();

            if (templateText.Length == 0)
                throw new ArgumentException("The template text should not be empty");

            float y = rect.Y;
            float textHeight = g.MeasureString(templateText, font).Height;

            //var lines = text.Split(new []{'\r', '\n'}, StringSplitOptions.None);
            var lines = Regex.Split(text, "\r\n|\r|\n", RegexOptions.None); // [4]
            foreach (var line in lines)
            {
                if (!DrawSingleLineStringAutoWrap(g, font, brush,
                    rect.X, ref y, rect.Right, rect.Bottom,
                    textHeight, line, clip))
                    break;

                y += textHeight;

#if DEBUG // [3]
                var pen = new Pen(Color.Black, 1);
                g.DrawLine(pen, rect.X, y, rect.Right, y);
#endif
            }
        }

        public static void DrawStringInRect(this Graphics g, string text, Font font, Brush brush, RectangleF rect, bool clip = true)
        {
            Debug.Assert(g != null);
            Debug.Assert(font != null);
            Debug.Assert(brush != null);

            var format = new StringFormat();
            format.FormatFlags |= clip ? 0 : StringFormatFlags.NoClip;
            g.DrawString(text, font, brush, rect, format);
        }
    }
}

// [1](http://stackoverflow.com/questions/761003/draw-a-single-pixel-on-windows-forms)
// [3](http://stackoverflow.com/questions/2923210/conditional-compilation-and-framework-targets)
// [4](http://stackoverflow.com/questions/1508203/best-way-to-split-string-into-lines)
// [5](http://stackoverflow.com/questions/25100324/array-slice-to-create-new-array)
// [6](http://stackoverflow.com/questions/406485/array-slices-in-c-sharp)
// [7](http://stackoverflow.com/questions/1324009/net-c-sharp-convert-char-to-string)