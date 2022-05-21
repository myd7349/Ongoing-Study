using System;
using System.IO;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace SkiaSharp.WPF
{
    public static class SkiaExtensions
    {
        public static SKSurfaceContext CreateSurfaceContext(this WriteableBitmap bitmap)
        {
            return SKSurfaceContext.Create(bitmap);
        }

        // SkiaSharp.Views.WPF.WPFExtensions.ToColor(SKColor)
        public static SKColor ToSKColor(this Color color)
        {
            return new SKColor(color.R, color.G, color.B, color.A);
        }

        public static SKRect ToSKRect(this Rect rect)
        {
            return new SKRect((float)rect.Left, (float)rect.Top, (float)rect.Right, (float)rect.Bottom);
        }

        public static void DrawLine(this SKCanvas canvas, float x0, float y0, float x1, float y1, SKColor color)
        {
            var paint = linePaint.Value;
            paint.Color = color;
            canvas.DrawLine(x0, y0, x1, y1, paint);
        }

        public static void Save(this SKBitmap bitmap, string filePath, SKEncodedImageFormat format, int quality)
        {
            using (var fileStream = File.OpenWrite(filePath))
                bitmap.Encode(fileStream, format, quality);
        }

        public static void Save(this SKImage image, string filePath, SKEncodedImageFormat format, int quality)
        {
            using (var fileStream = File.OpenWrite(filePath))
            {
                var encodedData = image.Encode(format, quality);
                encodedData.SaveTo(fileStream);
                //encodedData.Dispose();
            }
        }

        private static Lazy<SKPaint> linePaint = new Lazy<SKPaint>();
    }
}


// References:
// https://api.skia.org/classSkCanvas.html
// https://github.com/oxyplot/oxyplot/blob/develop/Source/OxyPlot.SkiaSharp/SkiaExtensions.cs
// https://docs.microsoft.com/en-us/dotnet/api/system.windows.media.imaging.writeablebitmap?view=windowsdesktop-6.0
// https://api.skia.org/classSkSurface.html#a351ef72e03fba91865a321e8e081a842
// https://stackoverflow.com/questions/50288603/dynamically-draw-lines-with-skiasharp-in-xamarin
// https://github.com/mono/SkiaSharp/blob/main/source/SkiaSharp.Views/SkiaSharp.Views.WPF/SKElement.cs
// https://docs.microsoft.com/en-us/dotnet/api/skiasharp.views.wpf.wpfextensions.tocolor?view=skiasharp-views-2.88
// https://swharden.com/csdv/maui.graphics/quickstart-wpf/
// https://github.com/mono/SkiaSharp/blob/main/source/SkiaSharp.Views/SkiaSharp.Views.WPF/WPFExtensions.cs
// https://github.com/oxyplot/oxyplot/blob/develop/Source/OxyPlot.SkiaSharp/SkiaExtensions.cs
// https://github.com/oxyplot/oxyplot/blob/develop/Source/OxyPlot.SkiaSharp/SkiaRenderContext.cs
