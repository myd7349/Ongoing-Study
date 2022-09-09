using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

using Color = System.Windows.Media.Color;

namespace GAL.NET
{
    public class ShapeCanvas : ICanvas<Canvas>
    {
        public ShapeCanvas(Canvas canvas)
        {
            Canvas = canvas;
        }
        
        public Canvas Canvas { get; }

        object ICanvas.Canvas => Canvas;

        public void DrawLine(int x1, int y1, int x2, int y2, Color color)
        {
            ArgumentNullException.ThrowIfNull(Canvas);

            var line = new Line
            {
                X1 = x1,
                Y1 = y1,
                X2 = x2,
                Y2 = y2,
            };
            line.Stroke = new SolidColorBrush(color);

            Canvas.Children.Add(line);
        }
        
        public void DrawLine(float x1, float y1, float x2, float y2, Color color)
        {
            ArgumentNullException.ThrowIfNull(Canvas);

            var line = new Line
            {
                X1 = x1,
                Y1 = y1,
                X2 = x2,
                Y2 = y2,
            };
            line.Stroke = new SolidColorBrush(color);

            Canvas.Children.Add(line);
        }
    }
}
