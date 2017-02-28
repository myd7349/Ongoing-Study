// 2017-02-26T10:18+08:00
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;

namespace Common
{
    public class NotifyProperty<T> : INotifyPropertyChanged
    {
        public NotifyProperty(T value, string name = "")
        {
            propertyValue = value;
            propertyName = name;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public T PropertyValue
        {
            get
            {
                return propertyValue;
            }

            set
            {
                //error CS0019: Operator '==' cannot be applied to operands of type 'T' and 'T'
                //if ((T)value == propertyValue) return;

                if (EqualityComparer<T>.Default.Equals(value, propertyValue))
                    return;

                propertyValue = value;
                OnPropertyChanged(propertyName);
            }
        }

        public static implicit operator T(NotifyProperty<T> property)
        {
            Debug.Assert(property != null);
            if (property == null)
                return default(T);

            return property.PropertyValue;
        }

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        private T propertyValue;
        private string propertyName;
    }
}

// References:
// [How to solve Operator '!=' cannot be applied to operands of type 'T' and 'T'](http://stackoverflow.com/questions/8982645/how-to-solve-operator-cannot-be-applied-to-operands-of-type-t-and-t)
