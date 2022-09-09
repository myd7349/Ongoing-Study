using Color = System.Windows.Media.Color;

namespace GAL.NET
{
    internal static class ColorHelper
    {
        public static System.Drawing.Color ToDrawingColor(this Color color)
        {
            return System.Drawing.Color.FromArgb(color.A, color.R, color.G, color.B);
        }
    }
}
