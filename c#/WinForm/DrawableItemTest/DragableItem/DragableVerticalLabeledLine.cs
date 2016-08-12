// 2016-08-11T11:40+08:00
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;


namespace DragableItem
{
    // TODO:
    // Rectangle: TopLeft, BottomRight, Normalize
    // Make one element enumerable
    public class DragableVerticalLabeledLine : IDragable, IDrawable
    {
        public DragableVerticalLabeledLine(Control parent)
        {
            this.parent = parent;
            Debug.Assert(this.parent != null);
        }

        public Rectangle Bounds
        {
            get
            {
                throw new NotImplementedException();
            }

            set
            {
                throw new NotImplementedException();
            }
        }

        public Rectangle LabelBounds { get; set; }

        public Point Position { get; set; }
        public string Label { get; set; }
        public Point Start
        {
            get
            {
                return Position;
            }

            set
            {
                Position = value;
                height = End.Y - value.Y;
                LabelBounds = new Rectangle();
            }
        }
        public Point End
        {
            get
            {
                return new Point(Position.X, Position.Y + height);
            }

            set
            {
                height = value.Y - Start.Y;
                LabelBounds = new Rectangle();
            }
        }

        public Pen LinePen { get; set; }
        public Brush LabelBackgroundBrush { get; set; }
        public Brush LabelBrush { get; set; }
        public Pen LabelEdgePen { get; set; }
        public Font LabelFont { get; set; }

        public IEnumerable<Rectangle> HotRectangles
        {
            get
            {
                throw new NotImplementedException();
            }

            set
            {
                throw new NotImplementedException();
            }
        }

        public Cursor HoverCursor { get; set; }

        public Cursor DragCursor
        {
            get
            {
                throw new NotImplementedException();
            }

            set
            {
                throw new NotImplementedException();
            }
        }

        public void Draw(Graphics graphics)
        {
            Debug.Assert(graphics != null);
            Debug.Assert(LinePen != null);
            Debug.Assert(LabelEdgePen != null);
            Debug.Assert(LabelBackgroundBrush != null);
            Debug.Assert(LabelFont != null);
            Debug.Assert(LabelBrush != null);

            if (LabelBounds.IsEmpty)
            {
                var labelSize = graphics.MeasureString(Label, LabelFont);
                Rectangle bounds = new Rectangle(new Point(), labelSize.ToSize());
                bounds.Width += (int)(LabelEdgePen.Width * 2);
                bounds.Height += (int)(LabelEdgePen.Width * 2);
                bounds.Offset(Start.X, Start.Y + height / 2);
                bounds.Offset(-bounds.Width / 2, -bounds.Height / 2);
                LabelBounds = bounds;
            }

            graphics.DrawLine(LinePen, Start, End);
            graphics.FillRectangle(LabelBackgroundBrush, LabelBounds);
            graphics.DrawRectangle(LabelEdgePen, LabelBounds);

            var rect = LabelBounds;
            rect.Offset((int)(LabelEdgePen.Width / 2), (int)(LabelEdgePen.Width / 2));
            graphics.DrawString(Label, LabelFont, LabelBrush, rect);
        }

        public void OnMouseDown(object sender, MouseEventArgs e)
        {
            if (!LabelBounds.Contains(e.X, e.Y))
                return;

            if (!isMoving)
                isMoving = true;
        }

        public bool OnMouseMove(object sender, MouseEventArgs e)
        {
            Debug.Assert(parent != null);

            if (LabelBounds.Contains(e.X, e.Y))
            {
                if (!isHoving)
                {
                    isHoving = true;

                    if (controlCursor == null)
                        controlCursor = parent.Cursor;
                    Debug.Assert(HoverCursor != null);

                    if (parent.Cursor != HoverCursor)
                        parent.Cursor = HoverCursor;
                }
            }
            else
            {
                if (isHoving)
                {
                    isHoving = false;

                    // If we are moving the line, the cursor will not be changed.
                    if (!isMoving)
                    {
                        if (controlCursor != null && parent.Cursor != controlCursor) // [1]
                            parent.Cursor = controlCursor;

                        return false;
                    }
                }
            }

            if (isMoving)
            {
                Point pt = Position;
                pt.X = e.X;
                Start = pt;
            }

            return true;
        }

        public void OnMouseUp(object sender, MouseEventArgs e)
        {
            Debug.Assert(parent != null);

            if (isMoving)
            {
                isMoving = false;

                // At [1], we didn't restore the parent control's original cursor, so
                // let's finish this work here.
                if (controlCursor != null && parent.Cursor != controlCursor)
                    parent.Cursor = controlCursor;
            }

            if (!LabelBounds.Contains(e.X, e.Y))
                return;
        }

        private int height;
        private Cursor controlCursor;
        private bool isHoving = false;
        private bool isMoving = false;
        private Control parent = null;
    }
}

