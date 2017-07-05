// 2017-07-05T11:40+08:00
using System.Windows.Forms;

namespace DragableItem
{
    public interface IMouseAction
    {
        bool OnMouseDown(object sender, MouseEventArgs e);
        bool OnMouseMove(object sender, MouseEventArgs e);
        bool OnMouseUp(object sender, MouseEventArgs e);
    }
}