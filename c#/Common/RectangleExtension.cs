namespace Common
{
    using System.Drawing;
    using System.Windows.Forms;

    static class RectangleExtension
    {
        public static Point CentralPoint(this Rectangle rectangle)
        {
            return new Point(rectangle.X + rectangle.Width / 2, rectangle.Y + rectangle.Height / 2);
        }

        public static Rectangle Deflate(this Rectangle rectangle, Padding padding)
        {
            rectangle.X += padding.Left;
            rectangle.Y += padding.Top;
            rectangle.Width -= padding.Horizontal;
            rectangle.Height -= padding.Vertical;
            return rectangle;
        }
    }
}


// References:
// https://github.com/dotnet/winforms/blob/a8905ab4ba4981db444644a2b028fbff92f41893/src/System.Windows.Forms/src/System/Windows/Forms/Layout/LayoutUtils.cs#L384-L391
