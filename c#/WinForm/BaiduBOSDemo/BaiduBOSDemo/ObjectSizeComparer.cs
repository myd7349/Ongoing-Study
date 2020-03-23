namespace BaiduBOSDemo
{
    using System;
    using System.Windows.Forms;

    using XPTable.Models;
    using XPTable.Sorting;

    using Humanizer.Bytes;

    class ObjectSizeComparer : ComparerBase
    {
        public ObjectSizeComparer(TableModel tableModel, int column, SortOrder sortOrder)
            : base(tableModel, column, sortOrder)
        {
        }

        protected override int CompareCells(Cell cell1, Cell cell2)
        {
            ByteSize byteSize1;
            if (!ByteSize.TryParse(cell1.Text, out byteSize1))
                throw new ArgumentException("Invalid object size: " + cell1.Text);

            ByteSize byteSize2;
            if (!ByteSize.TryParse(cell2.Text, out byteSize2))
                throw new ArgumentException("Invalid object size: " + cell2.Text);

            return byteSize1.Bytes.CompareTo(byteSize2.Bytes);
        }
    }
}
