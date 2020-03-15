namespace BaiduBOSDemo
{
    using System.Linq;
    using System.Windows.Forms;

    public class DataGridViewEx : DataGridView
    {
        /*
        typeof(DataGridView).InvokeMember("DoubleBuffered",
            BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty,
            null, parameterGridView, new object[] { true });
         */
        public bool IsDoubleBuffered
        {
            get
            {
                return base.DoubleBuffered;
            }

            set
            {
                base.DoubleBuffered = value;
            }
        }

        public void AutoResizeToFitContent()
        {
            AutoResizeColumns(DataGridViewAutoSizeColumnsMode.AllCells);
            Width = Columns.Cast<DataGridViewColumn>().Sum(c => c.Width) +
                (RowHeadersVisible ? RowHeadersWidth : 0) + 3;
            Height = Rows.Cast<DataGridViewRow>().Sum(r => r.Height) +
                (ColumnHeadersVisible ? ColumnHeadersHeight : 0) + 3;
        }
    }
}
