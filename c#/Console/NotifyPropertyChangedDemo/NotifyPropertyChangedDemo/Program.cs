namespace NotifyPropertyChangedDemo
{
    using static System.Console;
    using System.ComponentModel;

    class Program
    {
        static void Main()
        {
            var person = new Person("Tom", 18);
            person.PropertyChanged += Person_PropertyChanged;

            person.Name = "Jerry";
            person.Age = 10;
        }

        private static void Person_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            WriteLine($"Property {e.PropertyName} changed.");
        }
    }
}
