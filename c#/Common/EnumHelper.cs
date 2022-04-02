// 2016-06-02T17:35+08:00
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;

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
        public static int GetUnderlyingTypeSize<T>()
        {
            return GetUnderlyingTypeSize(typeof(T));
        }

        public static int GetUnderlyingTypeSize(Type type)
        {
            if (type == null)
                throw new ArgumentNullException("type");

            if (!type.IsEnum)
                throw new ArgumentException("Not an enum type.");

            return Marshal.SizeOf(Enum.GetUnderlyingType(type));
        }

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

        public static bool HasDuplicateValues<T>()
        {
            var values = (T[])Enum.GetValues(typeof(T));
            return values.Count() != values.Distinct().Count();
        }

        private static string GetDescriptionFromValue(Type type, object value)
        {
            var field = type.GetField(value.ToString());
            var attribute = field.GetCustomAttributes(typeof(DescriptionAttribute), true) as DescriptionAttribute[];
            if (attribute?.Length >= 1)
                return attribute[0].Description;

            return null;
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
// [Enum Size in Bytes](https://stackoverflow.com/questions/20944585/enum-size-in-bytes)
// [How to prevent duplicate values in enum?](https://stackoverflow.com/questions/1425777/how-to-prevent-duplicate-values-in-enum)
// https://github.com/TylerBrinkley/Enums.NET
// [WPF Data binding: How to data bind an enum to combo box using XAML?](https://stackoverflow.com/questions/4306743/wpf-data-binding-how-to-data-bind-an-enum-to-combo-box-using-xaml)
// [How to bind an enum to a combobox control in WPF?](https://stackoverflow.com/questions/6145888/how-to-bind-an-enum-to-a-combobox-control-in-wpf)
// [A Better Way to Data Bind Enums in WPF](https://brianlagunas.com/a-better-way-to-data-bind-enums-in-wpf/)
// https://github.com/brianlagunas/BindingEnumsInWpf
// [Localize Enum Descriptions in WPF](https://brianlagunas.com/localize-enum-descriptions-in-wpf/)
