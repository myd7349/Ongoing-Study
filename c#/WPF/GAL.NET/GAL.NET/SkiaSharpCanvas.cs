using Color = System.Windows.Media.Color;

using SkiaSharp;

using SkiaSharp.WPF;

namespace GAL.NET
{
    public class SkiaSharpCanvas : ICanvas<SKCanvas>
    {
        public SkiaSharpCanvas(SKCanvas canvas)
        {
            Canvas = canvas;
        }
        
        public SKCanvas Canvas { get; }

        object ICanvas.Canvas => Canvas;

        public void DrawLine(int x1, int y1, int x2, int y2, Color color)
        {
            DrawLine((float)x1, y1, x2, y2, color);
        }

        public void DrawLine(float x1, float y1, float x2, float y2, Color color)
        {
            ArgumentNullException.ThrowIfNull(Canvas);

            Canvas.DrawLine(x1, y1, x2, y2, color.ToSKColor());
        }
    }
}
