using System.Drawing;

namespace LayoutAlg
{
    public class HBoxLayout : CompositeElementBase
    {
        protected override void Layout(RectangleF rectangle)
        {
            if (Children.Count == 0)
                return;

            var averageWidth = rectangle.Width / Children.Count;

            RectangleF bounds = new RectangleF
            {
                X = Bounds.X,
                Y = Bounds.Y,
                Width = averageWidth,
                Height = rectangle.Height
            };

            foreach (var child in Children)
            {
                child.Bounds = bounds;
                bounds.Offset(averageWidth, 0.0F);
            }
        }
    }
}
