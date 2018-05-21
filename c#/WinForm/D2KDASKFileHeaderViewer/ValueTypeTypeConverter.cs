namespace D2KDASKFileHeaderViewer
{
    using System;
    using System.Collections;
    using System.ComponentModel;
    using System.Reflection;

    public class ValueTypeTypeConverter<T> : ExpandableObjectConverter where T : struct
    {
        public override bool GetCreateInstanceSupported(ITypeDescriptorContext context)
        {
            return true;
        }

        public override object CreateInstance(ITypeDescriptorContext context, IDictionary propertyValues)
        {
            if (propertyValues == null)
                throw new ArgumentNullException("propertyValues");

            T ret = default(T);
            object boxed = ret;
            foreach (DictionaryEntry entry in propertyValues)
            {
                PropertyInfo pi = ret.GetType().GetProperty(entry.Key.ToString());
                if (pi != null)
                {
                    pi.SetValue(boxed, Convert.ChangeType(entry.Value, pi.PropertyType), null);
                }
            }
            return (T)boxed;
        }
    }
}


// References:
// https://stackoverflow.com/questions/15746897/modifying-structure-property-in-a-propertygrid
