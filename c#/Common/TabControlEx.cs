namespace Common.WinForms
{
    using System;
    using System.Drawing;
    using System.Runtime.InteropServices;
    using System.Windows.Forms;

    public class TabPageEventArgs : EventArgs
    {
        public TabPageEventArgs(TabPage tabPage)
        {
            TabPage = tabPage;
        }

        public TabPage TabPage { get; private set; }
    }

    public delegate bool AddingTabPageEventHandler(object sender, TabPageEventArgs e);

    public delegate bool DeletingTabPageEventHandler(object sender, TabPageEventArgs e);

    public class TabControlEx : TabControl
    {
        public TabControlEx()
        {
            Padding = new Point(12, 4);

            DrawMode = TabDrawMode.OwnerDrawFixed;
            DrawItem += TabControlEx_DrawItem;
            MouseDown += TabControlEx_MouseDown;
            Selecting += TabControlEx_Selecting;
            HandleCreated += TabControlEx_HandleCreated;
        }

        public event AddingTabPageEventHandler TabPageAdding;

        public event DeletingTabPageEventHandler TabPageDeleting;

        private void TabControlEx_HandleCreated(object sender, System.EventArgs e)
        {
            SendMessage(Handle, TCM_SETMINTABWIDTH, IntPtr.Zero, (IntPtr)16);
        }

        private void TabControlEx_Selecting(object sender, TabControlCancelEventArgs e)
        {
            if (e.TabPageIndex == TabCount - 1)
                e.Cancel = true;
        }

        private void TabControlEx_MouseDown(object sender, MouseEventArgs e)
        {
            if (TabCount == 0)
                return;

            var lastIndex = TabCount - 1;
            if (GetTabRect(lastIndex).Contains(e.Location))
            {
                var newTabPage = new TabPage();

                if (TabPageAdding != null && TabPageAdding(this, new TabPageEventArgs(newTabPage)))
                {
                    TabPages.Insert(lastIndex, newTabPage);
                    SelectedIndex = lastIndex;
                    TabPages[lastIndex].UseVisualStyleBackColor = true;
                }
            }
            else
            {
                for (var i = 0; i < TabPages.Count; i++)
                {
                    var tabRect = GetTabRect(i);
                    tabRect.Inflate(-2, -2);
                    var closeImage = Properties.Resources.Close;
                    var imageRect = new Rectangle(
                        (tabRect.Right - closeImage.Width),
                        tabRect.Top + (tabRect.Height - closeImage.Height) / 2,
                        closeImage.Width,
                        closeImage.Height);
                    if (imageRect.Contains(e.Location))
                    {
                        if (TabPageDeleting != null && TabPageDeleting(this, new TabPageEventArgs(TabPages[i])))
                            TabPages.RemoveAt(i);

                        break;
                    }
                }
            }
        }

        private void TabControlEx_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (TabCount == 0)
                return;

            var tabPage = TabPages[e.Index];
            var tabRect = GetTabRect(e.Index);
            tabRect.Inflate(-2, -2);

            if (e.Index == TabCount - 1)
            {
                var addImage = Properties.Resources.Add;
                e.Graphics.DrawImage(addImage,
                    tabRect.Left + (tabRect.Width - addImage.Width) / 2,
                    tabRect.Top + (tabRect.Height - addImage.Height) / 2);
            }
            else
            {
                var closeImage = Properties.Resources.Close;
                e.Graphics.DrawImage(closeImage,
                    (tabRect.Right - closeImage.Width),
                    tabRect.Top + (tabRect.Height - closeImage.Height) / 2);
                TextRenderer.DrawText(e.Graphics, tabPage.Text, tabPage.Font,
                    tabRect, tabPage.ForeColor, TextFormatFlags.Left);
            }
        }

        [DllImport("user32.dll")]
        private static extern IntPtr SendMessage(IntPtr hWnd, int msg, IntPtr wp, IntPtr lp);

        private const int TCM_SETMINTABWIDTH = 0x1300 + 49;
    }
}


// References:
// https://stackoverflow.com/questions/6738126/winforms-tabcontrol-add-new-tab-button
// https://stackoverflow.com/questions/36895089/tabcontrol-with-close-and-add-button/36900582#36900582
// https://github.com/r-aghaei/TabControlWithCloseButtonAndAddButton
// https://stackoverflow.com/questions/29703235/adding-close-button-in-tabpage-tab-caption-in-c-sharp-windows-form
// https://www.codeproject.com/Articles/1233949/Create-Your-Own-TabControl-In-Csharp
