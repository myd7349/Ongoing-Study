// 2016-06-02T17:35+08:00
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;

namespace Common
{
    public sealed class EnumHelper<T> where T : struct
    {
        static EnumHelper()
        {
            EnumValueToNameDict = new Dictionary<T, string>();
            EnumNameToValueDict = new Dictionary<string, T>();

            EnumValueToDescriptionDict = new Dictionary<T, string>();
            EnumDescriptionToValueDict = new Dictionary<string, T>();

            foreach (var value in Enum.GetValues(typeof(T)))
            {
                EnumValueToNameDict[(T)value] = value.ToString();
                EnumNameToValueDict[value.ToString()] = (T)value;

                EnumValueToDescriptionDict[(T)value] = EnumHelper.GetDescription((Enum)value);

                var description = EnumHelper.GetDescription((Enum)value);
                if (description != null)
                    EnumDescriptionToValueDict[EnumHelper.GetDescription((Enum)value)] = (T)value;
            }
        }

        public static readonly Dictionary<T, string> EnumValueToNameDict;
        public static readonly Dictionary<string, T> EnumNameToValueDict;
        public static readonly Dictionary<T, string> EnumValueToDescriptionDict;
        public static readonly Dictionary<string, T> EnumDescriptionToValueDict;
    }

    public static class EnumHelper
    {
        public static string GetDescription(this Enum value)
        {
            Type type = value.GetType();
            string name = Enum.GetName(type, value);
            return GetDescriptionFromName(type, name);
        }

        public static string[] GetDescriptions(Type type)
        {
            return Enum.GetNames(type).Select(name => GetDescriptionFromName(type, name)).ToArray();
        }

        private static string GetDescriptionFromName(Type type, string name)
        {
            if (name != null)
            {
                FieldInfo field = type.GetField(name);
                if (field != null)
                {
                    DescriptionAttribute attr =
                           Attribute.GetCustomAttribute(field,
                             typeof(DescriptionAttribute)) as DescriptionAttribute;
                    if (attr != null)
                    {
                        return attr.Description;
                    }
                }
            }
            return null;
        }
    }
}

// References:
// [Enum ToString with user friendly strings](https://stackoverflow.com/questions/479410/enum-tostring-with-user-friendly-strings)
// [Can my enums have friendly names?](https://stackoverflow.com/questions/1415140/can-my-enums-have-friendly-names)

