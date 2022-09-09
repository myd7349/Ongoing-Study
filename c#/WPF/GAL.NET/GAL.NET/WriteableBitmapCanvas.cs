using Color = System.Windows.Media.Color;

using System.Windows.Media.Imaging;

namespace GAL.NET
{
    public class WriteableBitmapCanvas : ICanvas<WriteableBitmap>
    {
        public WriteableBitmapCanvas(WriteableBitmap canvas)
        {
            Canvas = canvas;
        }
        
        public WriteableBitmap Canvas { get; }

        object ICanvas.Canvas => Canvas;

        public void DrawLine(int x1, int y1, int x2, int y2, Color color)
        {
            ArgumentNullException.ThrowIfNull(Canvas);

            Canvas.DrawLine(x1, y1, x2, y2, color);
        }
        
        public void DrawLine(float x1, float y1, float x2, float y2, Color color)
        {
            DrawLine((int)x1, (int)y1, (int)x2, (int)y2, color);
        }
    }
}
