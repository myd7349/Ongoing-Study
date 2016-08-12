// 2016-08-12T09:52+08:00
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;

namespace DragableItem
{
    public class DragableItemsCollection
    {
        public DragableItemsCollection(IEnumerable<IDragable> coll)
        {
            this.coll = coll;
            Debug.Assert(this.coll != null);
        }

        public void OnMouseDown(object sender, MouseEventArgs e)
        {
            foreach (var item in coll)
                item.OnMouseDown(sender, e);
        }

        public bool OnMouseMove(object sender, MouseEventArgs e)
        {
            foreach (var item in coll)
            {
                if (item.OnMouseMove(sender, e, coll))
                {
                    if (onMovingItem != item)
                        onMovingItem = item;

                    return true;
                }
            }

            onMovingItem = null;
            return false;
        }

        public void OnMouseUp(object sender, MouseEventArgs e)
        {
            foreach (var item in coll)
                item.OnMouseUp(sender, e);
        }

        private IEnumerable<IDragable> coll;
        private IDragable onMovingItem;
    }
}
