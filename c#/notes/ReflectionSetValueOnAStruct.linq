<Query Kind="Program">
  <Namespace>System.Reflection</Namespace>
</Query>

//
struct DataPack<T> where T : struct
{
    public T X, Y, Z;
}


void Main()
{
    Type typeObj = typeof(DataPack<double>); // Or `GetType`
	FieldInfo[] fields = typeObj.GetFields(BindingFlags.Instance | BindingFlags.Public);
	
	DataPack<double> dataPack = new DataPack<double>();
	
	// SetValue doesn't work on a struct
	foreach (FieldInfo field in fields)
	{
	    field.SetValue(dataPack, 3.14);
	    Console.WriteLine($"Field: {field.Name} = {field.GetValue(dataPack)}");
	}
	
	//
	var boxedDataPack = (object)dataPack;
	foreach (FieldInfo field in fields)
	{
	    field.SetValue(boxedDataPack, 3.14);
		dataPack = (DataPack<double>)boxedDataPack;
	    Console.WriteLine($"Field: {field.Name} = {field.GetValue(dataPack)}");
	}
}


// References:
// https://social.msdn.microsoft.com/Forums/vstudio/en-US/33284e33-d004-4b76-bc0f-50100ec46bf1/fieldinfosetvalue-dont-work-in-struct?forum=csharpgeneral
// https://stackoverflow.com/questions/9927590/can-i-set-a-value-on-a-struct-through-reflection-without-boxing
