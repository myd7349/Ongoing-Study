// 2018-01-15T11:38+08:00
using System;

namespace LayoutAlg
{
    public interface ILayoutChanged
    {
        event EventHandler<LayoutChangedEventArgs> LayoutChanged;
    }
}
