namespace BaiduBOSDemo
{
    using System.ComponentModel;

    using Humanizer.Bytes;

    using XPTable.Models;

    class BOSObjectTableColumnBinder : DataSourceColumnBinder
    {
        public override Column GetColumn(PropertyDescriptor prop, int index)
        {
            switch (prop.Name)
            {
                case "Size":
                    return new TextColumn(prop.Name)
                    {
                        Comparer = typeof(ObjectSizeComparer),
                        Editable = false,
                        Alignment = ColumnAlignment.Center,
                        IsTextTrimmed = false,
                    };
                case "LastModified":
                    {
                        var dateTimeColumn = base.GetColumn(prop, index) as DateTimeColumn;
                        dateTimeColumn.Alignment = ColumnAlignment.Center;
                        dateTimeColumn.Editable = false;
                        dateTimeColumn.ShowDropDownButton = false;
                        dateTimeColumn.IsTextTrimmed = false;

                        return dateTimeColumn;
                    }
                case "Progress":
                    return new ProgressBarColumn(prop.Name)
                    {
                        Alignment = ColumnAlignment.Center,
                        Selectable = false,
                    };
            }

            return base.GetColumn(prop, index);
        }

        public override Cell GetCell(Column column, object val)
        {
            switch (column.Text)
            {
                case "Size":
                    return new Cell(ByteSize.FromBytes((long)val).ToString("0.##"));
            }

            return base.GetCell(column, val);
        }
    }
}
