// 2017-04-17T14:18:25+08:00
namespace Common
{
    using System;
    using System.Diagnostics;

    public class ValueWithDefault<T> where T : class 
    {
        public ValueWithDefault(T defaultValue)
        {
            Debug.Assert(defaultValue != null);
            this.defaultValue = defaultValue;
        }

        public T DefaultValue
        {
            get
            {
                return defaultValue;
            }
        }

        public T Value
        {
            get
            {
                return actualValue ?? defaultValue;
            }

            set
            {
                if (value != actualValue && value != defaultValue)
                    actualValue = value;
            }
        }

        public static implicit operator T(ValueWithDefault<T> value)
        {
            Debug.Assert(value != null);
            if (value == null)
                throw new ArgumentNullException();

            return value.Value;
        }

        private T actualValue;
        private T defaultValue;
    }
}
