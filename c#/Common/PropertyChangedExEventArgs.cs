using System;

namespace Common
{
    public class PropertyChangedExEventArgs : EventArgs
    {
        public readonly string PropertyName;
        public readonly object NewValue;

        public PropertyChangedExEventArgs(string propertyName, object newValue)
        {
            PropertyName = propertyName;
            NewValue = newValue;
        }
    }
}
