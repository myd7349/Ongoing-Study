namespace Common
{
    public static class ObjectHelper
    {
        public static object GetPropertyValue(this object obj, string propertyName)
        {
            return obj.GetType().GetProperty(propertyName).GetValue(obj, null);
        }

        public static T GetPropertyValue<T>(object obj, string propertyName)
        {
            return (T)obj.GetType().GetProperty(propertyName).GetValue(obj, null);
        }

        public static bool EqualsTo(this object lhs, object rhs)
        {
            if (lhs == null)
                return rhs == null;

            if (rhs == null)
                return false;

            
        }
    }
}


// References:
// [Get property value from string using reflection](https://stackoverflow.com/questions/1196991/get-property-value-from-string-using-reflection)
// [C# Object Type Comparison](https://stackoverflow.com/questions/708205/c-sharp-object-type-comparison)
// https://learn.microsoft.com/en-us/dotnet/api/system.type.equals?view=net-6.0
/*
using System.Collections.Generic;
using System.ComponentModel;

using CommunityToolkit.Mvvm.ComponentModel;

public abstract class ConfigPageViewModel : ObservableObject
{
    protected override void OnPropertyChanging(PropertyChangingEventArgs e)
    {
        var propertyName = e.PropertyName;

        if (!oldValues_.ContainsKey(propertyName))
            oldValues_[propertyName] = GetPropValue(propertyName);

        base.OnPropertyChanging(e);
    }

    protected virtual bool IsChanged()
    {
        foreach (var propertyKV in oldValues_)
        {
        }

        return false;
    }

    private object GetPropValue(string propertyName)
    {
        return GetType().GetProperty(propertyName).GetValue(this, null);
    }

    private Dictionary<string, object> oldValues_ = new Dictionary<string, object>();
}
*/
