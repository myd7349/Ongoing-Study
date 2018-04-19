<Query Kind="Program" />

abstract class DataSourceBase
{
    public abstract byte[] Read();
}

class FileDataSource : DataSourceBase
{
    public override byte[] Read()
	{
	    return new byte[] { 1, 1, 2, 3 };
	}
}

class DataView
{
    public DataSourceBase DataSource
	{
	    get
		{
		    return dataSource;
		}
		
		set
		{
		    if (value != dataSource)
			    dataSource = value;
				
			Console.WriteLine("DataSource updated.");
			
			if (dataSource != null)
			    Console.WriteLine(dataSource.Read());
		}
	}
	
	private DataSourceBase dataSource;
}


void Main()
{
    var dataView = new DataView();
	var dataSource = new FileDataSource();
	
	var dataViewType = typeof(DataView);
	var dataSourceProperty = dataViewType.GetProperty("DataSource");
	dataSourceProperty.SetValue(dataView, dataSource, null);
}

// References:
// https://stackoverflow.com/questions/7718792/can-i-set-a-property-value-with-reflection

