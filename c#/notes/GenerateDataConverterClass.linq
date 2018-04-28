<Query Kind="Program">
  <Namespace>System.CodeDom</Namespace>
  <Namespace>System.CodeDom.Compiler</Namespace>
</Query>

public CodeCompileUnit BuildDataConverterCompileUnit()
{
    var dataConverterClass = new CodeTypeDeclaration("DataConverter");

    var convertMethod = new CodeMemberMethod();
    convertMethod.Attributes = MemberAttributes.Static | MemberAttributes.Public;
    convertMethod.ReturnType = new CodeTypeReference(typeof(double));
    convertMethod.Name = "Convert";

    var convertMethodParameter = new CodeParameterDeclarationExpression();
    convertMethodParameter.Type = new CodeTypeReference(typeof(short));
    convertMethodParameter.Name = "x";

    convertMethod.Parameters.Add(convertMethodParameter);
    convertMethod.Statements.Add(new CodeMethodReturnStatement(
        new CodeSnippetExpression("x / 1000.0")));

    dataConverterClass.Members.Add(convertMethod);

    //
    var myNamespace = new CodeNamespace("MyNamespace");
    myNamespace.Imports.Add(new CodeNamespaceImport("System"));
    myNamespace.Types.Add(dataConverterClass);

    // 
    var compileUnit = new CodeCompileUnit();
    compileUnit.Namespaces.Add(myNamespace);

    return compileUnit;
}


public string GenerateSourceCode(CodeDomProvider codeProvider, CodeCompileUnit compileUnit)
{
    var stringBuilder = new StringBuilder();
    
    using (var stringWriter = new StringWriter(stringBuilder))
    using (var indentedTextWriter = new IndentedTextWriter(stringWriter, "    "))
    {
        codeProvider.GenerateCodeFromCompileUnit(compileUnit, indentedTextWriter, 
            new CodeGeneratorOptions());
    }
    
    return stringBuilder.ToString();
}


public CompilerResults GenerateAssembly(CodeDomProvider codeProvider, string code, string assemblyName)
{
    string[] referenceAssemblies = { "System.dll" };
    var compilerParameters = new CompilerParameters(referenceAssemblies, assemblyName, false);
    compilerParameters.GenerateExecutable = false;
    return codeProvider.CompileAssemblyFromSource(compilerParameters, code);
}


void Main()
{
    var codeProvider = CodeDomProvider.CreateProvider("CSharp");
    var compileUnit = BuildDataConverterCompileUnit();
    var code = GenerateSourceCode(codeProvider, compileUnit);
    Console.WriteLine(code);
    
    var currentQueryDirectoryName = Path.GetDirectoryName(Util.CurrentQueryPath);
    var assemblyName = Path.Combine(currentQueryDirectoryName, "DataConverter.dll");
    
    GenerateAssembly(codeProvider, code, assemblyName);
    
    var dataConverterAssembly = Assembly.LoadFile(assemblyName);
    foreach (var type in dataConverterAssembly.GetExportedTypes())
    {
        if (type.FullName == "MyNamespace.DataConverter")
        {
            Console.WriteLine(type.InvokeMember("Convert", 
                BindingFlags.Static | BindingFlags.Public | BindingFlags.InvokeMethod, 
                null,
                null,
                new object[] { (short)3 })
                );
        }
    }
}


// References:
// https://msdn.microsoft.com/en-us/library/system.codedom.compiler.codedomprovider(v=vs.110).aspx?cs-save-lang=1&cs-lang=csharp#code-snippet-2
// http://www.cnblogs.com/whitewolf/archive/2010/06/19/1760708.html
// https://stackoverflow.com/questions/3271316/c-sharp-4-0-expression-trees-vs-codedom
// https://stackoverflow.com/questions/1879395/how-do-i-generate-a-stream-from-a-string
// https://stackoverflow.com/questions/8047064/convert-string-to-system-io-stream
// https://stackoverflow.com/questions/18362368/loading-dlls-at-runtime-in-c-sharp
// https://stackoverflow.com/questions/5820721/c-sharp-short-long-int-literal-format