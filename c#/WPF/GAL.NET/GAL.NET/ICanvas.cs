using Color = System.Windows.Media.Color;

namespace GAL.NET
{
    public interface ICanvas
    {
        object Canvas { get; }

        void DrawLine(int x1, int y1, int x2, int y2, Color color);
        void DrawLine(float x1, float y1, float x2, float y2, Color color);
    }

    public interface ICanvas<T> : ICanvas
    {
        new T Canvas { get; }
    }
}
