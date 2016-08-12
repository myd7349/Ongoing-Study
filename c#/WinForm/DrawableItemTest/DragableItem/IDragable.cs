// 2016-08-11T11:17+08:00
using System;
using System.Drawing;
using System.Collections.Generic;
using System.Windows.Forms;

namespace DragableItem
{
    public interface IDragable
    {
        IEnumerable<Rectangle> HotRectangles { get; set; }
        Cursor HoverCursor { get; set; }
        Cursor DragCursor { get; set; }

        void OnMouseDown(object sender, MouseEventArgs e);
        bool OnMouseMove(object sender, MouseEventArgs e);
        void OnMouseUp(object sender, MouseEventArgs e);
    }
}
