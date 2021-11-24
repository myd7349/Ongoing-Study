// 2017-07-11T16:45+08:00
using System.Linq;
using System.Windows.Forms;

namespace Common.WinForms
{
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

// References:
// [Resize DataGridView width to fit Columns](https://stackoverflow.com/questions/23691433/resize-datagridview-width-to-fit-columns)
// [Why does the DoubleBuffered property default to false on a DataGridView and why is it protected?](https://stackoverflow.com/questions/252689/why-does-the-doublebuffered-property-default-to-false-on-a-datagridview-and-why)
// [Double Buffering a DataGridview](https://www.codeproject.com/tips/654101/double-buffering-a-datagridview)
// https://github.com/davidegironi/advanceddatagridview
// https://github.com/3F/DllExport/blob/master/Wizard/UI/Components/DataGridViewExt.cs
