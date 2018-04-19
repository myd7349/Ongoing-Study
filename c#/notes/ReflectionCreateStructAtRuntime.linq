<Query Kind="Program">
  <Reference>&lt;RuntimeDirectory&gt;\System.Reflection.dll</Reference>
  <Reference>&lt;RuntimeDirectory&gt;\System.Reflection.Emit.dll</Reference>
  <Namespace>System.Reflection.Emit</Namespace>
</Query>

Type CreateStruct(string fieldType, string[] fields)
{
    AssemblyName assembly = new AssemblyName("DataPacks");
    AppDomain appDomain = Thread.GetDomain();
    AssemblyBuilder assemblyBuilder = appDomain.DefineDynamicAssembly(assembly, AssemblyBuilderAccess.Run);
    ModuleBuilder moduleBuilder = assemblyBuilder.DefineDynamicModule(assembly.Name);
    var typeName = "DataPack_" + fieldType + string.Join("_", fields);
    TypeBuilder typeBuilder = moduleBuilder.DefineType(typeName, TypeAttributes.Public | TypeAttributes.SequentialLayout | TypeAttributes.AnsiClass |
        TypeAttributes.BeforeFieldInit, typeof(System.Object));

    foreach (var fieldName in fields)
        typeBuilder.DefineField(fieldName, Type.GetType(fieldType), FieldAttributes.Public);
    
    return typeBuilder.CreateType();
}

void DumpFields(Type type)
{
    FieldInfo[] fields = type.GetFields(BindingFlags.Instance | BindingFlags.Public);
    
    object dataPack = Activator.CreateInstance(type);
    
    foreach (FieldInfo field in fields)
    {
        field.SetValue(dataPack, 3.14);
        Console.WriteLine($"Field: {field.Name} = {field.GetValue(dataPack)}");
    }
}


void Main()
{
    Type dataPackTypeObj = CreateStruct("System.Double", new string[] { "X", "Y", "Z" });
    DumpFields(dataPackTypeObj);
    
    Type dataPackTypeObj2 = CreateStruct("System.Double", new string[] { "X", "Y", "Z", "A", "B", "C" });
    DumpFields(dataPackTypeObj2);
}

// References:
// https://stackoverflow.com/questions/4991990/generating-a-struct-at-run-time-based-on-data-types-defined-in-a-string
// https://stackoverflow.com/questions/24119967/define-struct-dynamically-in-c-sharp
// https://stackoverflow.com/questions/18467235/creating-dynamic-type-from-typebuilder-with-a-base-class-and-additional-fields-g
// https://stackoverflow.com/questions/14480332/create-a-class-dynamically-with-reflection-emit-i-got-stuck
// https://stackoverflow.com/questions/223952/create-an-instance-of-a-class-from-a-string
// https://softwareengineering.stackexchange.com/questions/93322/generating-a-class-dynamically-from-types-that-are-fetched-at-runtime
// https://stackoverflow.com/questions/2078914/creating-a-generict-type-instance-with-a-variable-containing-the-type
