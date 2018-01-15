// 2017-02-22T13:57+08:00
using System;
using System.Drawing;

namespace LayoutAlg
{
    public class LayoutChangedEventArgs : EventArgs
    {
        public readonly RectangleF LayoutArea;

        public LayoutChangedEventArgs(RectangleF rectangle)
        {
            LayoutArea = rectangle;
        }
    }
}
