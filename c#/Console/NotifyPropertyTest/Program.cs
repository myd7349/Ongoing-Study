// 2017-02-28T13:27:00+08:00
using System;
using System.ComponentModel;

using Common;

namespace NotifyPropertyTest
{
    class Person
    {
        public Person()
        {
            name.PropertyChanged += OnPropertyChanged;
            age.PropertyChanged += OnPropertyChanged;
        }

        public string Name
        {
            get { return name; }
            set { name.PropertyValue = value; }
        }

        public int Age
        {
            get { return age; }
            set { age.PropertyValue = value; }
        }

        private void OnPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            switch (e.PropertyName)
            {
                case "Name":
                    Console.WriteLine("Name changed. New name is: {0}", Name);
                    break;
                case "Age":
                    Console.WriteLine("Age changed. New age is: {0}", Age);
                    break;
            }
        }

        private NotifyProperty<string> name = new NotifyProperty<string>("Tom", "Name");
        private NotifyProperty<int> age = new NotifyProperty<int>(10, "Age");
    }

    class Program
    {
        static void Main(string[] args)
        {
            var p = new Person();
            p.Name = "Jim";
            p.Age = 12;

            Util.Pause();
        }
    }
}
