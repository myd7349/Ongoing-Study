// 2018-01-15T11:39+08:00
using System.Drawing;

namespace LayoutAlg
{
    public class RectangleElement : ElementBase
    {
        public Color Color { get; set; }

        public override void Draw(Graphics graphics)
        {
            graphics.FillRectangle(new SolidBrush(Color), Bounds);
        }

        protected override void Layout(RectangleF rectangle)
        {
        }
    }
}
