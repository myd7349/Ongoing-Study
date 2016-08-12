// 2016-08-11T11:17+08:00
using System.Drawing;


namespace DragableItem
{
    public interface IDrawable
    {
        Rectangle Bounds { get; set; }
        Point Position { get; set; }
        void Draw(Graphics graphics);
    }
}

