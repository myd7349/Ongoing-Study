using System;
using System.Linq;
using System.Windows;
using System.Windows.Media;

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

            if (colorCount < 2 || colorCount > 256)
                throw new ArgumentOutOfRangeException(nameof(colorCount));

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
            }

            var brush = new DrawingBrush
            {
                Drawing = drawingGroup,
            };

            return brush;
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
