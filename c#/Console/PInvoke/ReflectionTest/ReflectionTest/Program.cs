namespace ReflectionTest
{
    using System;
    using static System.Console;
    using static System.IO.Path;

    using Common;
    using Common.Reflection;

    using MyLibBase;

    class Program
    {
        static void Main(string[] args)
        {
            var typeMaps = ActivatorHelper.GetSubTypes<MyLibBase>(null, "MyLib*.dll");
            foreach (var kv in typeMaps)
            {
                WriteLine("============================================================");

                WriteLine("Assembly: {0}", GetFileName(kv.Key.Location));

                foreach (var type in kv.Value)
                {
                    WriteLine("------------------------------------------------------------");

                    var obj = ActivatorHelper.Create<MyLibBase>(type, "Hello!");
                    if (obj != null)
                    {
                        WriteLine("Creating instance of {0} successfully!", type.Name);
                        try
                        {
                            obj.Say();
                        }
                        catch (Exception ex)
                        {
                            WriteLine("{0} knows nothing!\n{1}", type.Name, ex.ToString());
                        }
                    }
                    else
                    {
                        WriteLine("Failed to create an instance of {0}!", type.Name);
                    }
                }
            }

            Util.Pause();
        }
    }
}
