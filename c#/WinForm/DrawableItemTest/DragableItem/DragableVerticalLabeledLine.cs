// 2016-08-11T11:40+08:00
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;


namespace DragableItem
{
    // TODO:
    // Rectangle: TopLeft, BottomRight, Normalize
    // Make one element enumerable
    // Swap<T>
    public class DragableVerticalLabeledLine : IDragable, IDrawable
    {
        [DllImport("user32.dll")]
        private static extern IntPtr SetCapture(IntPtr hwnd);

        [DllImport("user32.dll")]
        private static extern bool ReleaseCapture();

        public DragableVerticalLabeledLine(Control parent)
        {
            this.parent = parent;
            Debug.Assert(this.parent != null);
        }

        public Rectangle Bounds
        {
            get
            {
                int penWidth = LinePen == null ? 1 : (int)LinePen.Width;
                Rectangle rect = new Rectangle();
                rect.X = Position.X;
                rect.Y = Position.Y;
                rect.Width = penWidth;
                rect.Height = Length;
                return rect; 
            }

            set
            {
                Point pt = Position;
                pt.X = value.X;
                pt.Y = value.Y;
                Position = pt;
                Length = value.Height;
            }
        }

        public Point Position
        {
            get
            {
                return position;
            }

            set
            {
                int xOffset = value.X - position.X;
                int yOffset = value.Y - position.Y;
                position = value;
                if (labelBounds.HasValue)
                {
#if false
                    Debug.WriteLine("{0}, {1}", xOffset, yOffset);
                    Debug.WriteLine("Before: {0}, {1}", labelBounds?.X, labelBounds?.Y);

                    labelBounds?.Offset(xOffset, yOffset); // Execuse me???

                    Debug.WriteLine("After: {0}, {1}", labelBounds?.X, labelBounds?.Y);
#else
                    var bounds = labelBounds.Value;
                    bounds.Offset(xOffset, yOffset);
                    labelBounds = bounds;
#endif
                }
            }
        }
        public int Length { get; set; }
        public string Label
        {
            get
            {
                return label;
            }
            set
            {
                label = value;
                labelBounds = null;
            }
        }
        public int LabelYStart
        {
            get
            {
                return labelYStartFromTop;
            }

            set
            {
                labelYStartFromTop = value;
                labelBounds = null;
            }
        }
        public Rectangle? LabelBounds { get { return labelBounds; } }
        public Brush LabelBackgroundBrush { get; set; }
        public Brush LabelBrush { get; set; }
        public Brush FocusedLabelBackgroundBrush { get; set; }
        public Brush FocusedLabelBrush { get; set; }
        public Pen LabelEdgePen { get; set; }
        public Font LabelFont { get; set; }
        public Pen LinePen { get; set; }

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

        public Cursor DragCursor { get; set; }

        public void Draw(Graphics graphics)
        {
            Debug.Assert(graphics != null);
            Debug.Assert(LinePen != null);
            Debug.Assert(LabelEdgePen != null);
            Debug.Assert(LabelFont != null);
            Debug.Assert(LabelBackgroundBrush != null);
            Debug.Assert(LabelBrush != null);
            Debug.Assert(FocusedLabelBackgroundBrush != null);
            Debug.Assert(FocusedLabelBrush != null);

            if (!LabelBounds.HasValue)
            {
                var labelSize = graphics.MeasureString(Label, LabelFont);
                var bounds = new Rectangle(new Point(), labelSize.ToSize());
                bounds.Width += (int)(LabelEdgePen.Width * 2);
                bounds.Height += (int)(LabelEdgePen.Width * 2);
                bounds.Offset(Position.X, Position.Y + LabelYStart);
                bounds.Offset(-bounds.Width / 2, 0);
                labelBounds = bounds;
            }

            Point end = Position;
            end.Y += Length;
            graphics.DrawLine(LinePen, Position, end);
            graphics.FillRectangle(isMoving ? FocusedLabelBackgroundBrush : LabelBackgroundBrush, LabelBounds.Value);
            graphics.DrawRectangle(LabelEdgePen, LabelBounds.Value);

            var rect = LabelBounds.Value;
            rect.Offset((int)(LabelEdgePen.Width / 2), (int)(LabelEdgePen.Width / 2));
            graphics.DrawString(Label, LabelFont, isMoving ? FocusedLabelBrush : LabelBrush, rect);

            //graphics.FillRectangle(new SolidBrush(Color.White), Bounds);
            //graphics.FillRectangle(new SolidBrush(Color.White), LabelBounds.Value);
        }

        public void OnMouseDown(object sender, MouseEventArgs e)
        {
            if (!LabelBounds.HasValue || !LabelBounds.Value.Contains(e.X, e.Y))
                return;

            if (!isMoving)
            {
                isMoving = true;

                Debug.Assert(parent != null);
                SetCapture(parent.Handle);
            }
        }

        public bool OnMouseMove(object sender, MouseEventArgs e, IEnumerable<IDragable> coll)
        {
            Debug.Assert(parent != null);

            if (LabelBounds.HasValue && LabelBounds.Value.Contains(e.X, e.Y))
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
                Point newPosition = Position;
                Point pt = Position;
                // Try to move
                bool canMove = true;

                int xStep = Position.X <= e.X ? 1 : -1;
                for (int i = Position.X; i != e.X; i += xStep)
                {
                    pt.X = i;
                    Position = pt;
                    foreach (var item in coll)
                    {
                        if (DoCollisonDetection(item))
                        {
                            canMove = false;
                            break;
                        }
                    }

                    if (!canMove)
                        break;

                    newPosition.X = i;
                }

                Position = newPosition;
            }

            return isMoving;
        }

        public void OnMouseUp(object sender, MouseEventArgs e)
        {
            Debug.Assert(parent != null);

            if (isMoving)
            {
                isMoving = false;

                // At [1], we didn't restore the parent control's original cursor, so
                // let's finish this work here.
                if (!isHoving && controlCursor != null && parent.Cursor != controlCursor)
                    parent.Cursor = controlCursor;

                ReleaseCapture();
            }
        }

        public bool DoCollisonDetection(IDragable dragable)
        {
            var anotherVerticalLabeledLine = dragable as DragableVerticalLabeledLine;
            if (anotherVerticalLabeledLine != null)
            {
                if (!anotherVerticalLabeledLine.LabelBounds.HasValue || !LabelBounds.HasValue)
                    return false;

                if (anotherVerticalLabeledLine == this)
                    return false;

                return anotherVerticalLabeledLine.Bounds.IntersectsWith(Bounds)
                    || anotherVerticalLabeledLine.Bounds.IntersectsWith(LabelBounds.Value)
                    || anotherVerticalLabeledLine.LabelBounds.Value.IntersectsWith(Bounds)
                    || anotherVerticalLabeledLine.LabelBounds.Value.IntersectsWith(LabelBounds.Value);
            }

            return false;
        }

        private Control parent;
        private Cursor controlCursor;

        private Point position;
        private int labelYStartFromTop;

        private string label;
        private Rectangle? labelBounds;

        private bool isHoving = false;
        private bool isMoving = false;
        
    }
}

