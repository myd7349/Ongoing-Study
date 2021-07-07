namespace FooLib
{
    using System.Reflection;

    using Serilog;

    public static class Foo
    {
        public static void Bar(string message)
        {
            var currentMethod = MethodBase.GetCurrentMethod();
            Log.Information("{0} {1}", currentMethod.ReflectedType.Name, currentMethod.Name);
            Log.Information("This is a hello message from inside of a function: {Message}", message);
        }
    }
}
