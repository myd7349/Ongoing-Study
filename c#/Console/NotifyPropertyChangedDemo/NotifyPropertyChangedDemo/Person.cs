namespace NotifyPropertyChangedDemo
{
    using System.ComponentModel;
    using System.Runtime.CompilerServices;

    public class Person : INotifyPropertyChanged
    {
        public Person(string name = null, int age = 0)
        {
            name_ = name;
            age_ = age;
        }

        public string Name
        {
            get => name_;

            set
            {
                name_ = value;
                OnPropertyChanged();
            }
        }

        public int Age
        {
            get => age_;

            set
            {
                age_ = value;
                OnPropertyChanged();
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string name = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

        private string name_;
        private int age_;
    }
}


// References:
// [INotifyPropertyChanged Interface](https://docs.microsoft.com/en-us/dotnet/api/system.componentmodel.inotifypropertychanged?view=net-5.0)
// [How to: Implement Property Change Notification](https://docs.microsoft.com/en-us/dotnet/desktop/wpf/data/how-to-implement-property-change-notification?view=netframeworkdesktop-4.8)
// [Raise an event whenever a property's value changed?](https://stackoverflow.com/questions/2246777/raise-an-event-whenever-a-propertys-value-changed)
