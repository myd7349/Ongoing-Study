namespace GetWeChatGroupMembers
{
    using System.Drawing;

    static class RectangleExtension
    {
        public static Point CentralPoint(this Rectangle rectangle)
        {
            return new Point(rectangle.X + rectangle.Width / 2, rectangle.Y + rectangle.Height / 2);
        }
    }
}
