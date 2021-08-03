namespace Common
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.IO;
    using System.Linq;

    public class IniFile2 : IDisposable
    {
        public IniFile2(string filePath)
        {
            Debug.Assert(!string.IsNullOrWhiteSpace(filePath));
            FilePath = filePath;

            TrueLiteral = "true";
            FalseLiteral = "false";

            Load();
        }

        public string FilePath { get; private set; }

        public string TrueLiteral { get; set; }

        public string FalseLiteral { get; set; }

        public void Load()
        {
            if (File.Exists(FilePath))
            {
                using (var fileStream = File.OpenRead(FilePath))
                    data_ = Load(fileStream);
            }
            else
            {
                data_ = new Dictionary<string, string>();
            }
        }

        public void Flush()
        {
            using (var fileStream = new FileStream(FilePath, FileMode.Create))
                Store(fileStream, data_);
        }

        public string Get(string section, string key)
        {
            if (section == null)
                throw new ArgumentNullException("section");
            if (key == null)
                throw new ArgumentNullException("key");

            return Get(string.Format("{0}{1}{2}", section, KeyDelimiter, key));
        }

        public string Get(string sectionAndKey)
        {
            if (sectionAndKey == null)
                throw new ArgumentNullException("sectionAndKey");

            if (data_.ContainsKey(sectionAndKey))
                return data_[sectionAndKey];

            throw new KeyNotFoundException(sectionAndKey);
        }

        public bool TryGet(string section, string key, ref string value)
        {
            if (section == null)
                throw new ArgumentNullException("section");
            if (key == null)
                throw new ArgumentNullException("key");

            return TryGet(string.Format("{0}{1}{2}", section, KeyDelimiter, key), ref value);
        }

        public bool TryGet(string sectionAndKey, ref string value)
        {
            if (sectionAndKey == null)
                throw new ArgumentNullException("sectionAndKey");

            if (data_.ContainsKey(sectionAndKey))
            {
                value = data_[sectionAndKey];
                return true;
            }

            return false;
        }

        public void Set(string section, string key, string value)
        {
            if (section == null)
                throw new ArgumentNullException("section");
            if (key == null)
                throw new ArgumentNullException("key");

            Set(string.Format("{0}{1}{2}", section, KeyDelimiter, key), value);
        }

        public void Set(string sectionAndKey, string value)
        {
            if (sectionAndKey == null)
                throw new ArgumentNullException("sectionAndKey");

            data_[sectionAndKey] = value;
        }

        public string this[string section, string key]
        {
            get
            {
                return Get(section, key);
            }

            set
            {
                Set(section, key, value);
            }
        }

        public string this[string sectionAndKey]
        {
            get
            {
                return Get(sectionAndKey);
            }

            set
            {
                Set(sectionAndKey, value);
            }
        }

        public IEnumerable<string> GetSections()
        {
            return data_.Keys.Select(sk => sk.Split(KeyDelimiter[0])[0]).Distinct(data_.Comparer);  
        }

        public bool IsSectionExists(string section)
        {
            if (section == null)
                throw new ArgumentNullException("section");

            return GetSections().Contains(section, data_.Comparer);
        }

        public IEnumerable<string> GetKeys(string setcion)
        {
            return data_.Keys.Select(sk => sk.Split(KeyDelimiter[0])[1]).Distinct(data_.Comparer);
        }

        public bool IsKeyExists(string section, string key)
        {
            return GetKeys(section).Contains(key, data_.Comparer);
        }

        public Dictionary<string, string>.KeyCollection GetSectionAndKeys()
        {
            return data_.Keys;
        }

        public Dictionary<string, string>.ValueCollection GetValues()
        {
            return data_.Values;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (disposed_)
                return;

            if (disposing)
            {
                Flush();
            }

            disposed_ = true;
        }

        private Dictionary<string, string> data_;
        private bool disposed_ = false;

        public static Dictionary<string, string> Load(Stream stream)
        {
            var data = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);

            using (var reader = new StreamReader(stream))
            {
                string sectionPrefix = string.Empty;

                while (reader.Peek() != -1)
                {
                    string rawLine = reader.ReadLine();
                    string line = rawLine.Trim();

                    // Ignore blank lines
                    if (string.IsNullOrWhiteSpace(line))
                        continue;

                    // Ignore comments
                    if (line[0] == ';' || line[0] == '#' || line[0] == '/')
                        continue;

                    // [Section:header]
                    if (line[0] == '[' && line[line.Length - 1] == ']')
                    {
                        // remove the brackets
                        sectionPrefix = line.Substring(1, line.Length - 2) + KeyDelimiter;
                        continue;
                    }

                    // key = value OR "value"
                    int separator = line.IndexOf('=');
                    if (separator < 0)
                        throw new FormatException("Unrecognized line format.");

                    string key = sectionPrefix + line.Substring(0, separator).Trim();
                    string value = line.Substring(separator + 1).Trim();

                    // Remove quotes
                    if (value.Length > 1 && value[0] == '"' && value[value.Length - 1] == '"')
                        value = value.Substring(1, value.Length - 2);

                    if (data.ContainsKey(key))
                        throw new FormatException("Key is duplicated.");

                    data[key] = value;
                }
            }

            return data;
        }

        // TODO: Preserve comments.
        public static void Store(Stream stream, Dictionary<string, string> data)
        {
            var sortedData = new SortedDictionary<string, string>(data, StringComparer.OrdinalIgnoreCase);

            string section = null;

            using (var streamWriter = new StreamWriter(stream))
            {
                foreach (var keyValuePair in sortedData)
                {
                    var sectionAndKey = keyValuePair.Key.Split(KeyDelimiter[0]);
                    Debug.Assert(sectionAndKey != null && sectionAndKey.Length == 2);

                    if (sortedData.Comparer.Compare(sectionAndKey[0], section) != 0)
                    {
                        section = sectionAndKey[0];
                        streamWriter.WriteLine("[{0}]", section);
                    }

                    streamWriter.WriteLine("{0}={1}",
                        sectionAndKey[1],
                        keyValuePair.Value != null ? keyValuePair.Value : string.Empty);
                }
            }
        }

        public static readonly string KeyDelimiter = ":";
    }
}


// References:
// https://github.com/dotnet/runtime/blob/1fa304a14a8be27428399bd6f2cc51736cb1515a/src/libraries/Microsoft.Extensions.Configuration.Ini/src/IniStreamConfigurationProvider.cs#L26-L81

