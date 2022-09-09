using Color = System.Windows.Media.Color;

namespace GAL.NET
{
    public class GraphicsCanvas : ICanvas<Graphics>
    {
        public GraphicsCanvas(Graphics canvas)
        {
            Canvas = canvas;
        }
        
        public Graphics Canvas { get; }

        object ICanvas.Canvas => Canvas;

        public void DrawLine(int x1, int y1, int x2, int y2, Color color)
        {
            ArgumentNullException.ThrowIfNull(Canvas);

            Canvas.DrawLine(
                new Pen(color.ToDrawingColor()),
                x1, y1, x2, y2);
        }
        
        public void DrawLine(float x1, float y1, float x2, float y2, Color color)
        {
            ArgumentNullException.ThrowIfNull(Canvas);

            Canvas.DrawLine(
                new Pen(color.ToDrawingColor()),
                x1, y1, x2, y2);
        }
    }
}
