namespace Common
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;

    public class IniFile
    {
        public IniFile(string filePath)
        {
            Debug.Assert(!string.IsNullOrWhiteSpace(filePath));
            FilePath = filePath;

            TrueLiteral = "true";
            FalseLiteral = "false";
        }

        public string FilePath { get; private set; }

        public string TrueLiteral { get; set; }

        public string FalseLiteral { get; set; }

        public string[] GetSections()
        {
            return Kernel32.GetPrivateProfileSectionNames(FilePath);
        }

        public bool HasSection(string section)
        {
            if (string.IsNullOrWhiteSpace(section))
                throw new ArgumentException("section");

            return GetSections().Contains(section, StringComparer.OrdinalIgnoreCase);
        }

        public string[] GetKeys(string section)
        {
            if (string.IsNullOrWhiteSpace(section))
                throw new ArgumentException("section");

            return Kernel32.GetPrivateProfileString(section, null, null, FilePath).ToStrings().ToArray();
        }

        public bool HasKey(string section, string key)
        {
            if (string.IsNullOrWhiteSpace(key))
                throw new ArgumentException("key");

            return GetKeys(section).Contains(key, StringComparer.OrdinalIgnoreCase);
        }

        public KeyValuePair<string, string>[] ReadSection(string section)
        {
            return Kernel32.GetPrivateProfileSection(section, FilePath)
                .Select(line =>
                {
                    var kv = line.Split('=');
                    return new KeyValuePair<string, string>(kv[0], kv[1]);
                })
                .ToArray();
        }

        public int ReadInt(string section, string key, int defaultValue = default(int))
        {
            return (int)Kernel32.GetPrivateProfileInt(section, key, defaultValue, FilePath);
        }

        public uint ReadUInt(string section, string key, uint defaultValue = default(uint))
        {
            return Kernel32.GetPrivateProfileInt(section, key, (int)defaultValue, FilePath);
        }

        public long ReadLong(string section, string key, long defaultValue = default(long))
        {
            var valueString = ReadString(section, key, defaultValue.ToString());
            if (string.IsNullOrEmpty(valueString))
                return defaultValue;

            long value;
            if (long.TryParse(valueString, out value))
                return value;
            else
                return defaultValue;
        }

        public ulong ReadULong(string section, string key, ulong defaultValue = default(ulong))
        {
            var valueString = ReadString(section, key, defaultValue.ToString());
            if (string.IsNullOrEmpty(valueString))
                return defaultValue;

            ulong value;
            if (ulong.TryParse(valueString, out value))
                return value;
            else
                return defaultValue;
        }

        public bool ReadBoolean(string section, string key, bool defaultValue = default(bool))
        {
            Debug.Assert(!string.IsNullOrWhiteSpace(TrueLiteral));
            Debug.Assert(!string.IsNullOrWhiteSpace(FalseLiteral));
            Debug.Assert(TrueLiteral != FalseLiteral);

            var value = ReadString(section, key, defaultValue.ToString());
            if (string.IsNullOrEmpty(value))
                return defaultValue;

            if (value == TrueLiteral)
                return true;

            if (value == FalseLiteral)
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
                case 'O':
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

        public double ReadDouble(string section, string key, double defaultValue = default(double))
        {
            return Read(section, key, defaultValue, double.TryParse);
        }

        public string ReadString(string section, string key, string defaultValue = "" /* string.Empty */)
        {
            return Kernel32.GetPrivateProfileString(section, key, defaultValue, FilePath);
        }

        public T Read<T>(string section, string key, T defaultValue, GenericTryParse<T> tryParse)
        {
            if (tryParse == null)
                throw new ArgumentNullException("tryParse");

            var valueString = ReadString(section, key, defaultValue.ToString());
            if (string.IsNullOrEmpty(valueString))
                return defaultValue;

            T value;
            if (tryParse(valueString, out value))
                return value;
            else
                return defaultValue;
        }

        public bool WriteSection(string section, KeyValuePair<string, string>[] keyValuePairs)
        {
            var keyValuePairsStringArray = keyValuePairs
                .Select(kv => string.Format("{0}={1}", kv.Key, kv.Value));
            var keyValuePairsString = string.Join("\0", keyValuePairsStringArray) + "\0\0";
            return Kernel32.WritePrivateProfileSection(section, keyValuePairsString, FilePath);
        }

        public bool Write(string section, string key, int value)
        {
            return Write(section, key, value.ToString());
        }

        public bool Write(string section, string key, uint value)
        {
            return Write(section, key, value.ToString());
        }

        public bool Write(string section, string key, long value)
        {
            return Write(section, key, value.ToString());
        }

        public bool Write(string section, string key, ulong value)
        {
            return Write(section, key, value.ToString());
        }

        public bool Write(string section, string key, bool value)
        {
            Debug.Assert(!string.IsNullOrWhiteSpace(TrueLiteral));
            Debug.Assert(!string.IsNullOrWhiteSpace(FalseLiteral));
            Debug.Assert(TrueLiteral != FalseLiteral);

            return Write(section, key, value ? TrueLiteral : FalseLiteral);
        }

        public bool Write(string section, string key, double value)
        {
            return Write(section, key, value.ToString());
        }

        public bool Write(string section, string key, string value)
        {
            return Kernel32.WritePrivateProfileString(section, key, value, FilePath);
        }

        public bool Write<T>(string section, string key, T value, GenericConvert<T> convert)
        {
            if (convert == null)
                throw new ArgumentNullException("convert");

            return Write(section, key, convert(value));
        }

        public string this[string section, string key]
        {
            get
            {
                return ReadString(section, key);
            }

            set
            {
                Write(section, key, value);
            }
        }
    }
}
