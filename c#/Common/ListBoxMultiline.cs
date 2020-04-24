namespace Common.WinForms
{
    using System;
    using System.Drawing;
    using System.Runtime.InteropServices;
    using System.Windows.Forms;

    public class ListBoxMultiline : ListBox
    {
        private TextFormatFlags flags = TextFormatFlags.WordBreak |
                                TextFormatFlags.PreserveGraphicsClipping |
                                TextFormatFlags.GlyphOverhangPadding |
                                TextFormatFlags.LeftAndRightPadding |
                                TextFormatFlags.ExpandTabs |
                                TextFormatFlags.VerticalCenter;

        public ListBoxMultiline()
        {
            DrawMode = DrawMode.OwnerDrawVariable;

            SelectedItemBrush = new SolidBrush(Color.Orange);
            SizeChanged += new EventHandler(ListBoxMultiline_SizeChanged);
        }

        public Brush FocusedItemBrush
        {
            get;
            set;
        }

        public Brush SelectedItemBrush
        {
            get;
            set;
        }

        protected override void OnDrawItem(DrawItemEventArgs e)
        {
            if (Items.Count == 0)
                return;

            if (e.State.HasFlag(DrawItemState.Focus))
            {
                if (FocusedItemBrush != null)
                    e.Graphics.FillRectangle(FocusedItemBrush, e.Bounds);
            }
            else if (e.State.HasFlag(DrawItemState.Selected))
            {
                if (SelectedItemBrush != null)
                    e.Graphics.FillRectangle(SelectedItemBrush, e.Bounds);
            }
            else
            {
                e.DrawBackground();
            }

            TextRenderer.DrawText(e.Graphics, GetItemText(Items[e.Index]), Font, e.Bounds, ForeColor, flags);

            if (e.Index != Items.Count - 1)
            {
                Point lineOffsetStart = new Point(e.Bounds.X, e.Bounds.Bottom - 1);
                Point lineOffsetEnd = new Point(e.Bounds.Right, e.Bounds.Bottom - 1);
                e.Graphics.DrawLine(Pens.LightGray, lineOffsetStart, lineOffsetEnd);
            }

            base.OnDrawItem(e);
        }

        protected override void OnMeasureItem(MeasureItemEventArgs e)
        {
            if (Items.Count == 0) return;
            var size = GetItemSize(e.Graphics, GetItemText(Items[e.Index]));
            e.ItemWidth = size.Width;
            e.ItemHeight = size.Height;
            base.OnMeasureItem(e);
        }

        private Size GetItemSize(Graphics g, string itemText)
        {
            var size = TextRenderer.MeasureText(g, itemText, Font, ClientSize, flags);
            //size.Height = Math.Max(Math.Min(size.Height, 247), Font.Height + 8) + 8;
            size.Height = Math.Min(size.Height, 250);
            return size;
        }

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern IntPtr SendMessage(IntPtr hWnd, int msg, int wParam, int lParam);

        private const int LB_SETITEMHEIGHT = 0x01A0;

        private void ListBoxMultiline_SizeChanged(object sender, EventArgs e)
        {
            using (var graphics = CreateGraphics())
            {
                for (int i = 0; i < Items.Count; ++i)
                {
                    var itemSize = GetItemSize(graphics, GetItemText(Items[i]));
                    SendMessage(Handle, LB_SETITEMHEIGHT, i, itemSize.Height);
                }
            }
        }
    }
}

// References:
// https://stackoverflow.com/questions/60581724/how-to-add-multiline-text-to-a-listbox-item
// https://www.codeproject.com/Articles/7489/An-auto-resize-C-Listbox-updated
// https://www.codeproject.com/articles/2695/an-editable-multi-line-listbox-for-net
// https://stackoverflow.com/questions/9532368/multi-line-list-items-on-winforms-listbox-control
// https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.listbox.itemheight?view=netframework-4.8
// https://stackoverflow.com/questions/21525925/refresh-doesnt-update-owner-draw-listbox-item-height
// https://stackoverflow.com/questions/20571059/re-measuring-existing-items-in-listbox
