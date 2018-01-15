// 2017-02-23T09:31+08:00
using System;
using System.Drawing;

namespace LayoutAlg
{
    public abstract class ElementBase : ILayoutChanged
    {
        public RectangleF Bounds
        {
            get
            {
                return bounds;
            }

            set
            {
                if (bounds == value)
                    return;

                bounds = value;
                OnLayoutChanged(new LayoutChangedEventArgs(bounds));
            }
        }

        public event EventHandler<LayoutChangedEventArgs> LayoutChanged;

        public bool SuspendLayout
        {
            get
            {
                return suspendLayout;
            }

            set
            {
                if (value == suspendLayout)
                    return;

                suspendLayout = value;
                OnLayoutChanged(new LayoutChangedEventArgs(Bounds));
            }
        }

        public abstract void Draw(Graphics graphics);

        public double LayoutHint { get; set; }

        protected abstract void Layout(RectangleF rectangle);

        protected virtual void OnLayoutChanged(LayoutChangedEventArgs e)
        {
            if (!SuspendLayout)
            {
                Layout(e.LayoutArea);

                if (LayoutChanged != null)
                    LayoutChanged(this, e);
            }
        }

        private RectangleF bounds;
        private bool suspendLayout;
    }
}
