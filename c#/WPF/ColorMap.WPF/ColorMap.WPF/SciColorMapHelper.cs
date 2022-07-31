using System;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

using SciColorMap = SciColorMaps.Portable.ColorMap;

namespace ColorMap.WPF
{
    public static class SciColorMapHelper
    {
        public static Color ToMediaColor(this byte[] rgb)
        {
            return Color.FromRgb(rgb[0], rgb[1], rgb[2]);
        }

        public static Brush CreatePaletteBrush(string palette, int colorCount)
        {
            if (string.IsNullOrEmpty(palette))
                return TransparentBrush;

            if (colorCount < 2 || colorCount > 256)
                throw new ArgumentOutOfRangeException(nameof(colorCount));
            
            var colorMap = new SciColorMap(palette, colorCount: colorCount);
            return colorMap.CreatePaletteBrush(colorCount);
        }
        
        public static Brush CreatePaletteBrush(this SciColorMap cmap, int colorCount)
        {
            ArgumentNullException.ThrowIfNull(cmap);

            if (colorCount < 2 || colorCount > 256)
                throw new ArgumentOutOfRangeException(nameof(colorCount));

            return new LinearGradientBrush
            {
                StartPoint = new Point(0, 0),
                EndPoint = new Point(1, 0),
                GradientStops = new GradientStopCollection(
                    cmap.Colors()
                         .Select((color, i) => new GradientStop()
                         {
                             Color = color.ToMediaColor(),
                             Offset = (float)i / colorCount
                         })
                         .ToList())
            };
        }

        public static Brush CreatePaletteBrush(string palette, int colorCount, double width, double height)
        {
            if (string.IsNullOrEmpty(palette))
                return TransparentBrush;

            if (colorCount < 2 || colorCount > 256)
                throw new ArgumentOutOfRangeException(nameof(colorCount));

            var cmap = new SciColorMap(palette, colorCount: colorCount);

            if (height < colorCount)
                return cmap.CreatePaletteBrush(colorCount);

            var colors = cmap.Colors().ToArray();
            var colorIndex = 0;
            
            var drawingGroup = new DrawingGroup();

            var step = height / colorCount;
            
            var yStart = 0.0;
            while (yStart < height)
            {
                var rect = new Rect(0, yStart, width, step);
                var rectangleGeometry = new RectangleGeometry(rect);

                var geometryDrawing = new GeometryDrawing
                {
                    Brush = new SolidColorBrush(colors[colorIndex].ToMediaColor()),
                    Geometry = rectangleGeometry,
                };

                drawingGroup.Children.Add(geometryDrawing);
                
                yStart += step;

                if (colorIndex < colors.Length - 1)
                    colorIndex += 1;
            }

            var brush = new DrawingBrush
            {
                Drawing = drawingGroup,
            };

            return brush;
        }

        public static DrawingImage CreateDrawingImage(string palette, int colorCount)
        {
            if (string.IsNullOrEmpty(palette))
                return null;

            if (colorCount < 2 || colorCount > 256)
                throw new ArgumentOutOfRangeException(nameof(colorCount));

            var cmap = new SciColorMap(palette, colorCount: colorCount);
            
            var colors = cmap.Colors().ToArray();
            
            var drawingGroup = new DrawingGroup();
            
            for (int i = 0; i < colors.Length; ++i)
            {
                var rect = new Rect(0, i, 1, 1);
                var rectangleGeometry = new RectangleGeometry(rect);

                var geometryDrawing = new GeometryDrawing
                {
                    Brush = new SolidColorBrush(colors[i].ToMediaColor()),
                    Geometry = rectangleGeometry,
                };

                drawingGroup.Children.Add(geometryDrawing);
            }

            var drawingImage = new DrawingImage(drawingGroup);
            drawingImage.Freeze();

            return drawingImage;
        }

        public static WriteableBitmap CreateColorMapImage(
            string palette, int colorCount,
            double width, double height,
            Orientation orientation,
            bool showTicks,
            Color tickColor)
        {
            if (orientation == Orientation.Horizontal)
            {
                return CreateHorizontalColorMapImage(
                    palette, colorCount, width, height, showTicks, tickColor);
            }
            else
            {
                return CreateVerticalColorMapImage(
                    palette, colorCount, width, height, showTicks, tickColor);
            }
        }

        public static WriteableBitmap CreateHorizontalColorMapImage(
            string palette, int colorCount,
            double width, double height,
            bool showTicks, Color tickColor)
        {
            if (width <= 0 || height <= 0)
                return null;

            if (string.IsNullOrEmpty(palette))
                return null;

            if (colorCount < 2 || colorCount > 256)
                throw new ArgumentOutOfRangeException(nameof(colorCount));

            var cmap = new SciColorMap(palette, colorCount: colorCount);
            var colors = cmap.Colors().ToArray();

            var bitmap = BitmapFactory.New((int)width, (int)height);

            var xStart = 0.0;
            var step = width / colorCount;

            using (var bitmapContext = bitmap.GetBitmapContext())
            {
                for (int i = 0; i < colors.Length; ++i)
                {
                    bitmap.FillRectangle(
                        (int)xStart,
                        0,
                        (int)(xStart + step),
                        (int)height,
                        colors[i].ToMediaColor());

                    xStart += step;
                }

                if (showTicks)
                {
                    bitmap.DrawRectangle(
                        0,
                        0,
                        (int)width,
                        (int)height,
                        tickColor);

                    int stepFactor = 1;

                    if (step < 5)
                    {
                        stepFactor = (int)Math.Ceiling(5 / step);
                        step *= stepFactor;
                    }

                    xStart = 0;

                    for (int i = 0; i < colors.Length; i += stepFactor)
                    {
                        bitmap.DrawLine(
                            (int)xStart,
                            0,
                            (int)xStart,
                            5,
                            Colors.Black);
                        bitmap.DrawLine(
                            (int)xStart,
                            (int)height - 5,
                            (int)xStart,
                            (int)height,
                            tickColor);

                        xStart += step;
                    }
                }
            }

            return bitmap;
        }

        public static WriteableBitmap CreateVerticalColorMapImage(
            string palette, int colorCount,
            double width, double height,
            bool showTicks, Color tickColor)
        {
            if (width <= 0 || height <= 0)
                return null;

            if (string.IsNullOrEmpty(palette))
                return null;

            if (colorCount < 2 || colorCount > 256)
                throw new ArgumentOutOfRangeException(nameof(colorCount));

            var cmap = new SciColorMap(palette, colorCount: colorCount);
            var colors = cmap.Colors().ToArray();

            var bitmap = BitmapFactory.New((int)width, (int)height);

            var yStart = 0.0;
            var step = height / colorCount;

            using (var bitmapContext = bitmap.GetBitmapContext())
            {
                for (int i = 0; i < colors.Length; ++i)
                {
                    bitmap.FillRectangle(
                        0,
                        (int)yStart,
                        (int)width,
                        (int)(yStart + step),
                        colors[i].ToMediaColor());

                    yStart += step;
                }

                if (showTicks)
                {
                    bitmap.DrawRectangle(
                        0,
                        0,
                        (int)width,
                        (int)height,
                        tickColor);

                    int stepFactor = 1;

                    if (step < 5)
                    {
                        stepFactor = (int)Math.Ceiling(5 / step);
                        step *= stepFactor;
                    }

                    yStart = 0;

                    for (int i = 0; i < colors.Length; i += stepFactor)
                    {
                        bitmap.DrawLine(
                            0,
                            (int)yStart,
                            5,
                            (int)yStart,
                            Colors.Black);
                        bitmap.DrawLine(
                            (int)width - 5,
                            (int)yStart,
                            (int)width,
                            (int)yStart,
                            tickColor);

                        yStart += step;
                    }
                }
            }

            return bitmap;
        }

        public static readonly Brush TransparentBrush = new DrawingBrush
        {
            TileMode = TileMode.Tile,
            Viewport = new Rect(0, 0, 8, 8),
            ViewportUnits = BrushMappingMode.Absolute,
            Opacity = 0.5,
            Drawing = new GeometryDrawing
            {
                Brush = Brushes.LightGray,
                Geometry = Geometry.Parse("M0,0 H1 V1 H2 V2 H1 V1 H0Z")
            }
        };
    }
}


// References:
// https://github.com/ar1st0crat/SciColorMaps/blob/master/SciColorMaps.DemoWpf/MainViewModel.cs
// https://github.com/ElinamLLC/SharpVectors/blob/master/Samples/WpfTestSvgControl/DrawingPage.xaml
// PixiEditor also has a transparent background brush.
// [Creating line pattern in code behind with WPF](https://stackoverflow.com/questions/57674799/creating-line-pattern-in-code-behind-with-wpf)
// [DrawingBrush.GeometryDrawing with dynamic Brush property](https://stackoverflow.com/questions/63852845/drawingbrush-geometrydrawing-with-dynamic-brush-property)
// [How to: Paint an Area with a Drawing](https://learn.microsoft.com/en-us/dotnet/desktop/wpf/graphics-multimedia/how-to-paint-an-area-with-a-drawing?view=netframeworkdesktop-4.8)
// [Changing color of the GeometryDrawing Brush when Button is pressed](https://stackoverflow.com/questions/43932907/changing-color-of-the-geometrydrawing-brush-when-button-is-pressed)
