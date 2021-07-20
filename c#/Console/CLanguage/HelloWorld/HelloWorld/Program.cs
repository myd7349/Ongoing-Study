namespace HelloWorld
{
    using static System.Console;

    using CLanguage;
    using CLanguage.Interpreter;

    class Program
    {
        static void Main(string[] args)
        {
            WriteLine(CLanguageService.Eval("3 + 4"));
            WriteLine(CLanguageService.Eval("x * 100", "int x = 2;"));
            //WriteLine(CLanguageService.Eval("10.0f + 3.01f"));
            //WriteLine(CLanguageService.Eval("1.0 / 1000.0"));
            //Run("void main() { assertAreEqual(3 + 1, 4); }");
        }

        private static CInterpreter Run(string code)
        {
            var fullCode = "void start() { __cinit(); main(); } " + code;
            var interpreter = CLanguageService.CreateInterpreter(fullCode);
            interpreter.Reset("start");
            interpreter.Run();
            return interpreter;
        }
    }
}


// References:
// https://github.com/praeclarum/CLanguage
// https://praeclarum.org/2018/08/27/oops-i-wrote-a-c-compiler.html
// https://github.com/praeclarum/CLanguage/blob/master/CLanguageTests/GettingStartedTests.cs
