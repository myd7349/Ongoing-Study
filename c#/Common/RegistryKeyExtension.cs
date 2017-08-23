// 2017-08-23T16:33+08:00
namespace Common.Configuration.Registry
{
    using System;
    using System.Collections.Generic;
    using System.Security;

    using Microsoft.Win32;

    public static class RegistryKeyExtension
    {
        public static IEnumerable<Tuple<string, string>> EnumerateSubKeys(this RegistryKey key, bool recursive = false, bool failOnSecurityException = false)
        {
            if (key == null)
                throw new ArgumentNullException("key");

            foreach (var subKey in key.GetSubKeyNames())
            {
                yield return new Tuple<string, string>(key.Name, subKey);

                if (recursive)
                {
                    using (RegistryKey openedSubKey = key.OpenSubKeyInternal(subKey, failOnSecurityException))
                    {
                        if (openedSubKey != null)
                        {
                            foreach (var subSubKeyTuple in openedSubKey.EnumerateSubKeys(recursive))
                                yield return subSubKeyTuple;
                        }
                    }
                }
            }
        }

        public static IEnumerable<Tuple<string, string>> EnumerateSubKeys(this RegistryKey key, string subKey, bool recursive = false, bool failOnSecurityException = false)
        {
            if (key == null)
                throw new ArgumentNullException("key");

            if (string.IsNullOrEmpty(subKey))
            {
                foreach (var tuple in key.EnumerateSubKeys(recursive, failOnSecurityException))
                    yield return tuple;
            }
            else
            {
                using (RegistryKey openedSubKey = key.OpenSubKeyInternal(subKey, failOnSecurityException))
                {
                    if (openedSubKey != null)
                    {
                        foreach (var tuple in openedSubKey.EnumerateSubKeys(recursive, failOnSecurityException))
                            yield return tuple;
                    }
                }
            }
        }

        public static IEnumerable<Tuple<string, string, object, RegistryValueKind>> EnumerateValues(this RegistryKey key, bool recursive = false, bool failOnSecurityException = false)
        {
            if (key == null)
                throw new ArgumentNullException("key");

            foreach (var value in key.GetValueNames())
                yield return new Tuple<string, string, object, RegistryValueKind>(key.Name, value, key.GetValue(value), key.GetValueKind(value));

            if (recursive)
            {
                foreach (var subKey in key.GetSubKeyNames())
                {
                    using (RegistryKey openedSubKey = key.OpenSubKeyInternal(subKey, failOnSecurityException))
                    {
                        if (openedSubKey != null)
                        {
                            foreach (var tuple in openedSubKey.EnumerateValues(recursive, failOnSecurityException))
                                yield return tuple;
                        }
                    }
                }
            }
        }

        public static IEnumerable<Tuple<string, string, object, RegistryValueKind>> EnumerateValues(this RegistryKey key, string subKey, bool recursive = false, bool failOnSecurityException = false)
        {
            if (key == null)
                throw new ArgumentNullException("key");

            if (string.IsNullOrEmpty(subKey))
            {
                foreach (var tuple in key.EnumerateValues(recursive, failOnSecurityException))
                    yield return tuple;
            }
            else
            {
                using (RegistryKey openedSubKey = key.OpenSubKeyInternal(subKey, failOnSecurityException))
                {
                    if (openedSubKey != null)
                    {
                        foreach (var tuple in openedSubKey.EnumerateValues(recursive, failOnSecurityException))
                            yield return tuple;
                    }
                }
            }
        }

        private static RegistryKey OpenSubKeyInternal(this RegistryKey key, string subKey, bool failOnSecurityException)
        {
            if (key == null)
                throw new ArgumentNullException("key");

            if (string.IsNullOrEmpty(subKey))
                throw new ArgumentException("subKey");

            if (failOnSecurityException)
            {
                return key.OpenSubKey(subKey);
            }
            else
            {
                try
                {
                    return key.OpenSubKey(subKey);
                }
                catch (SecurityException)
                {
                    return null;
                }
            }
        }

    }
}
