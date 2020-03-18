namespace BaiduBOSDemo
{
    using System;
    using System.Windows.Forms;

    using BrightIdeasSoftware;

    using Humanizer.Bytes;

    class BOSObjectListView : DataListView
    {
        public BOSObjectListView()
        {
            View = View.Details;
            FullRowSelect = true;
            GridLines = true;
            ShowGroups = false;

            UseCellFormatEvents = true;
            FormatCell += BOSObjectListView_FormatCell;
        }

        private void BOSObjectListView_FormatCell(object sender, FormatCellEventArgs e)
        {
            if (e.ColumnIndex == 2)
            {
                long totalBytes;
                if (long.TryParse(e.SubItem.Text, out totalBytes))
                    e.SubItem.Text = ByteSize.FromBytes(Convert.ToInt64(e.SubItem.Text)).ToString("0.##");
            }
        }
    }
}
