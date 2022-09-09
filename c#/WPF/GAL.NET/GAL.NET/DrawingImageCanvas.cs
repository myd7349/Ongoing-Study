using System.Windows.Media;

namespace GAL.NET
{
    public class DrawingImageCanvas : ICanvas<DrawingImage>
    {
        public DrawingImage Canvas => throw new NotImplementedException();

        object ICanvas.Canvas => Canvas;

        public void DrawLine(int x1, int y1, int x2, int y2, System.Windows.Media.Color color)
        {
            throw new NotImplementedException();
        }

        public void DrawLine(float x1, float y1, float x2, float y2, System.Windows.Media.Color color)
        {
            throw new NotImplementedException();
        }
    }
}
