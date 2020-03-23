namespace BaiduBOSDemo
{
    using XPTable.Models;

    class BOSObjectTable : Table
    {
        public BOSObjectTable()
        {
            SelectionStyle = SelectionStyle.ListView;
            FullRowSelect = true;
            EnableWordWrap = false;
            GridLines = GridLines.Both;
            MultiSelect = true;
            GridLinesContrainedToData = true;
        }
    }
}
