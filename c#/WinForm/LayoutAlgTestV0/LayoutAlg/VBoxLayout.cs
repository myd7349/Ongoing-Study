using System.Drawing;
using System.Linq;

namespace LayoutAlg
{
    public class VBoxLayout : CompositeElementBase
    {
        protected override void Layout(RectangleF rectangle)
        {
            if (Children.Count == 0)
                return;

#if true
            var averageHeight = rectangle.Height / Children.Count;

            RectangleF bounds = new RectangleF
            {
                X = Bounds.X,
                Y = Bounds.Y,
                Width = rectangle.Width,
                Height = averageHeight
            };

            foreach (var child in Children)
            {
                child.Bounds = bounds;
                bounds.Offset(0.0F, averageHeight);
            }
#else
            bool firstTime = Children.ToList().TrueForAll(child => child.LayoutHint == 0.0);

            if (firstTime)
            {
                double hint = 1.0 / Children.Count;
                double yStartHint = 0.0;

                foreach (var child in Children)
                {
                    child.LayoutHint = yStartHint;
                    yStartHint += hint;
                }
            }

            var averageHeight = rectangle.Height / Children.Count;

            RectangleF bounds = new RectangleF
            {
                X = Bounds.X,
                Width = rectangle.Width,
                Height = averageHeight
            };

            foreach (var child in Children)
            {
                bounds.Y = Bounds.Y + (float)(rectangle.Height * child.LayoutHint);
                child.Bounds = bounds;
            }
#endif
        }
    }
}
