namespace MarshalCppClass
{
    using static System.Console;

    using NativeClassLibCLRBridge;

    class Program
    {
        static void Main(string[] args)
        {
            var person = new Person("Tom", 18);

            var whatFormat = "Hello! This is {0}. I am {1} years old.";

            var what = string.Format(whatFormat, person.Name, person.Age);
            person.Say(what);

            person.Name = "Jerry";
            person.Age = 12;

            what = string.Format(whatFormat, person.Name, person.Age);
            person.Say(what);

            ReadKey();
        }
    }
}
