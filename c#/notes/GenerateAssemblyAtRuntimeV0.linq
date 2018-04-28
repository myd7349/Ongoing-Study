<Query Kind="Program">
  <Reference>&lt;RuntimeDirectory&gt;\Microsoft.CSharp.dll</Reference>
  <Namespace>Microsoft.CSharp</Namespace>
  <Namespace>System.CodeDom.Compiler</Namespace>
</Query>


void Main()
{
    var currentQueryDirectoryName = Path.GetDirectoryName(Util.CurrentQueryPath);
    
    var csCodeProvider = CodeDomProvider.CreateProvider("CSharp");
    var codeCompiler = csCodeProvider.CreateCompiler();
    
    var compilerParameters = new CompilerParameters();
    compilerParameters.GenerateExecutable = false;
    compilerParameters.OutputAssembly = Path.Combine(currentQueryDirectoryName, "DataPack.dll");
    
    var compilerResult = codeCompiler.CompileAssemblyFromSource(
        compilerParameters,
        @"
namespace MyNamespace
{
    public struct DataPack
    {
        public double X;
        public double Y;
        public double Z;
    }
}
");

}

// References:
// https://stackoverflow.com/questions/604501/generating-dll-assembly-dynamically-at-run-time
// https://stackoverflow.com/questions/14406049/codedomprovider-createcompiler-is-obsolete
// https://msdn.microsoft.com/en-us/library/system.codedom.compiler.codedomprovider(v=vs.110).aspx
