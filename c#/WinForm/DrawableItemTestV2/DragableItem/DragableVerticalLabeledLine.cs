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
    // Swap<T>
    public class DragableVerticalLabeledLine
    {
        public DragableVerticalLabeledLine()
        {
            Visible = true;
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
                rect.Inflate(new Size(4, 0));
                return rect;
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

        public Font FocusedLabelFont { get; set; }

        public Pen LinePen { get; set; }

        public Cursor HoverCursor { get; set; }

        public Cursor DragCursor { get; set; }

        public bool Visible { get; set; }

        public bool IsMoving
        {
            get
            {
                return isMoving;
            }

            set
            {
                if (isMoving != value)
                {
                    isMoving = value;
                    labelBounds = null;
                }
            }
        }

        public bool IsHoving
        {
            get
            {
                return isHoving;
            }

            set
            {
                if (isHoving != value)
                {
                    isHoving = value;
                    labelBounds = null;
                }
            }
        }

        public void Draw(Graphics graphics)
        {
            if (!Visible)
                return;

            Debug.Assert(graphics != null);
            Debug.Assert(LinePen != null);
            Debug.Assert(LabelEdgePen != null);
            Debug.Assert(LabelFont != null);
            Debug.Assert(LabelBackgroundBrush != null);
            Debug.Assert(LabelBrush != null);
            Debug.Assert(FocusedLabelFont != null);
            Debug.Assert(FocusedLabelBackgroundBrush != null);
            Debug.Assert(FocusedLabelBrush != null);

            if (!LabelBounds.HasValue)
            {
                var labelSize = graphics.MeasureString(Label, isHoving ? FocusedLabelFont : LabelFont);
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
            graphics.FillRectangle(isHoving ? FocusedLabelBackgroundBrush : LabelBackgroundBrush, LabelBounds.Value);
            graphics.DrawRectangle(LabelEdgePen, LabelBounds.Value);

            var rect = LabelBounds.Value;
            rect.Offset((int)(LabelEdgePen.Width / 2), (int)(LabelEdgePen.Width / 2));
            graphics.DrawString(Label, isHoving ? FocusedLabelFont : LabelFont, isMoving ? FocusedLabelBrush : LabelBrush, rect);
        }

        public virtual bool DoCollisionDetection(DragableVerticalLabeledLine anotherVerticalLabeledLine, int xStep)
        {
            if (anotherVerticalLabeledLine != null && anotherVerticalLabeledLine.Visible)
            {
                if (!anotherVerticalLabeledLine.LabelBounds.HasValue || !LabelBounds.HasValue)
                    return false;

                if (anotherVerticalLabeledLine == this)
                    return false;

                RectangleF bounds1 = anotherVerticalLabeledLine.Bounds;
                bounds1.Inflate(-3.5f, 0.0f);

                RectangleF bounds2 = Bounds;
                bounds2.Inflate(-3.5f, 0.0f);

                return bounds1.IntersectsWith(bounds2);

                //return anotherVerticalLabeledLine.Bounds.IntersectsWith(Bounds)
                //|| anotherVerticalLabeledLine.Bounds.IntersectsWith(LabelBounds.Value)
                //|| anotherVerticalLabeledLine.LabelBounds.Value.IntersectsWith(Bounds)
                //|| anotherVerticalLabeledLine.LabelBounds.Value.IntersectsWith(LabelBounds.Value)
                //;
            }

            return false;
        }

        private bool HitTest(int x, int y)
        {
            return (LabelBounds.HasValue && LabelBounds.Value.Contains(x, y)) || Bounds.Contains(x, y);
        }

        private Point position;
        private int labelYStartFromTop;

        private string label;
        private Rectangle? labelBounds;

        private bool isHoving = false;
        private bool isMoving = false;
    }
}
