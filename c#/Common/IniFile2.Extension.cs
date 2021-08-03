namespace Common
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;

    public static class IniFile2Extension
    {
        public static IEnumerable<KeyValuePair<string, string>> ReadSection(this IniFile2 ini, string section)
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            return ini.GetKeys(section).Select(key => new KeyValuePair<string, string>(key, ini[section, key]));
        }

        public static int ReadInt(this IniFile2 ini, string section, string key, int defaultValue = default(int))
        {
            var value = ini.ReadLong(section, key);
            if (value >= int.MinValue && value <= int.MaxValue)
                return (int)value;
            else
                return defaultValue;
        }

        public static uint ReadUInt(this IniFile2 ini, string section, string key, uint defaultValue = default(uint))
        {
            var value = ini.ReadULong(section, key);
            if (value >= uint.MinValue && value <= uint.MaxValue)
                return (uint)value;
            else
                return defaultValue;
        }

        public static long ReadLong(this IniFile2 ini, string section, string key, long defaultValue = default(long))
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            string s = string.Empty;
            if (ini.TryGet(section, key, ref s))
            {
                long value;
                if (long.TryParse(s, out value))
                    return value;
                else
                    return defaultValue;
            }
            else
            {
                return defaultValue;
            }
        }

        public static ulong ReadULong(this IniFile2 ini, string section, string key, ulong defaultValue = default(ulong))
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            string s = string.Empty;
            if (ini.TryGet(section, key, ref s))
            {
                ulong value;
                if (ulong.TryParse(s, out value))
                    return value;
                else
                    return defaultValue;
            }
            else
            {
                return defaultValue;
            }
        }

        public static bool ReadBoolean(this IniFile2 ini, string section, string key, bool defaultValue = default(bool))
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            Debug.Assert(!string.IsNullOrWhiteSpace(ini.TrueLiteral));
            Debug.Assert(!string.IsNullOrWhiteSpace(ini.FalseLiteral));
            Debug.Assert(ini.TrueLiteral != ini.FalseLiteral);

            string value = string.Empty;
            if (!ini.TryGet(section, key, ref value))
                return defaultValue;

            if (string.IsNullOrWhiteSpace(value))
                return defaultValue;

            if (value == ini.TrueLiteral)
                return true;

            if (value == ini.FalseLiteral)
                return false;

            // true/false, True/False
            // yes/no, Yes/No
            // on/off
            // 1/0
            switch (value[0])
            {
                case 't':
                case 'T':
                case 'y':
                case 'Y':
                case '1':
                    return true;
                case 'f':
                case 'F':
                case 'n':
                case 'N':
                case '0':
                    return false;
                case 'o':
                    {
                        var lowerValue = value.ToLower();
                        if (lowerValue == "on")
                            return true;
                        else if (lowerValue == "off")
                            return false;
                    }
                    break;
                default: break;
            }

            return defaultValue;
        }

        public static string ReadString(this IniFile2 ini, string section, string key, string defaultValue = "" /* string.Empty */)
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            string value = string.Empty;
            if (ini.TryGet(section, key, ref value))
                return value;

            return defaultValue;
        }

        public static T Read<T>(this IniFile2 ini, string section, string key, T defaultValue, GenericTryParse<T> tryParse)
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            if (tryParse != null)
                throw new ArgumentNullException("tryParse");

            string valueString = string.Empty;
            if (!ini.TryGet(section, key, ref valueString))
                return defaultValue;

            T value;
            if (tryParse(valueString, out value))
                return value;
            else
                return defaultValue;
        }

        public static void WriteSection(this IniFile2 ini, string section, KeyValuePair<string, string>[] keyValuePairs)
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            if (keyValuePairs == null)
                throw new ArgumentNullException("keyValuePairs");

            foreach (var kv in keyValuePairs)
                ini[section, kv.Key] = kv.Value;
        }

        public static void Write(this IniFile2 ini, string section, string key, int value)
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            ini[section, key] = value.ToString();
        }

        public static void Write(this IniFile2 ini, string section, string key, uint value)
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            ini[section, key] = value.ToString();
        }

        public static void Write(this IniFile2 ini, string section, string key, long value)
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            ini[section, key] = value.ToString();
        }

        public static void Write(this IniFile2 ini, string section, string key, ulong value)
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            ini[section, key] = value.ToString();
        }

        public static void Write(this IniFile2 ini, string section, string key, bool value)
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            Debug.Assert(!string.IsNullOrWhiteSpace(ini.TrueLiteral));
            Debug.Assert(!string.IsNullOrWhiteSpace(ini.FalseLiteral));
            Debug.Assert(ini.TrueLiteral != ini.FalseLiteral);

            ini.Write(section, key, value ? ini.TrueLiteral : ini.FalseLiteral);
        }

        public static void Write(this IniFile2 ini, string section, string key, string value)
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            ini[section, key] = value;
        }

        public static void Write<T>(this IniFile2 ini, string section, string key, T value, GenericConvert<T> convert)
        {
            if (ini == null)
                throw new ArgumentNullException("ini");

            if (convert == null)
                throw new ArgumentNullException("convert");

            ini[section, key] = convert(value);
        }
    }
}
