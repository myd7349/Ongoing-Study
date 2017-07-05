// 2017-07-05T11:40+08:00
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace DragableItem
{
    public class AdjustLineAction : IMouseAction
    {
        [DllImport("user32.dll")]
        private static extern IntPtr SetCapture(IntPtr hwnd);

        [DllImport("user32.dll")]
        private static extern bool ReleaseCapture();

        public AdjustLineAction(IEnumerable<DragableVerticalLabeledLine> coll)
        {
            Debug.Assert(coll != null);
            measureLines = coll;

            onMovingLine = null;
            controlCursor = null;
        }

        public bool OnMouseDown(object sender, MouseEventArgs e)
        {
            var line = HitTest(e.Location);
            if (line == null)
                return false;

            Debug.Assert(!line.IsMoving);
            Debug.Assert(line.IsHoving);
            Debug.Assert(onMovingLine == null);
            line.IsMoving = true;
            onMovingLine = line;

            var control = sender as Control;
            Debug.Assert(control != null);
            SetCapture(control.Handle);

            return true;
        }

        public bool OnMouseMove(object sender, MouseEventArgs e)
        {
            if (onMovingLine != null)
            {
                Debug.Assert(onMovingLine.IsMoving);

                Point newPosition = onMovingLine.Position;
                Point pt = onMovingLine.Position;

                // Try to move
                bool canMove = true;

                int xStep = onMovingLine.Position.X <= e.X ? 1 : -1;
                for (int i = onMovingLine.Position.X; i != e.X; i += xStep)
                {
                    pt.X = i;
                    onMovingLine.Position = pt;
                    foreach (var item in measureLines)
                    {
                        if (onMovingLine.DoCollisonDetection(item))
                        {
                            canMove = false;
                            break;
                        }
                    }

                    if (!canMove)
                        break;

                    newPosition.X = i;
                }

                onMovingLine.Position = newPosition;

                return true;
            }
            else
            {
                var line = HitTest(e.Location);

                bool update = false;

                foreach (var item in measureLines)
                {
                    if (item != line)
                    {
                        update = update || item.IsHoving;
                        item.IsHoving = false;
                    }
                }

                if (line != null)
                {
                    if (!line.IsHoving)
                    {
                        line.IsHoving = true;
                        update = true;

                        var parent = sender as Control;
                        Debug.Assert(parent != null);

                        if (controlCursor == null)
                            controlCursor = parent.Cursor;
                        Debug.Assert(line.HoverCursor != null);

                        if (parent.Cursor != line.HoverCursor)
                            parent.Cursor = line.HoverCursor;
                    }
                }
                else
                {
                    var parent = sender as Control;
                    Debug.Assert(parent != null);

                    if (controlCursor != null && parent.Cursor != controlCursor)
                        parent.Cursor = controlCursor;
                }

                return update;
            }
        }

        public bool OnMouseUp(object sender, MouseEventArgs e)
        {
            if (onMovingLine != null)
            {
                Debug.Assert(onMovingLine.IsMoving);
                onMovingLine.IsMoving = false;

                var parent = sender as Control;
                Debug.Assert(parent != null);

                // At [1], we didn't restore the parent control's original cursor, so
                // let's finish this work here.
                if (!onMovingLine.IsHoving && controlCursor != null && parent.Cursor != controlCursor)
                    parent.Cursor = controlCursor;

                onMovingLine = null;

                ReleaseCapture();

                return true;
            }

            return false;
        }

        private DragableVerticalLabeledLine HitTest(Point point)
        {
            foreach (var line in measureLines)
            {
                if (line.LabelBounds.HasValue && line.LabelBounds.Value.Contains(point))
                    return line;
            }

            foreach (var line in measureLines)
            {
                if (line.Bounds.Contains(point))
                    return line;
            }

            return null;
        }

        private IEnumerable<DragableVerticalLabeledLine> measureLines;
        private DragableVerticalLabeledLine onMovingLine;
        private Cursor controlCursor;
    }
}