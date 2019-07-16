namespace Common.Reflection
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.IO;
    using System.Linq;
    using System.Reflection;

    public static class ActivatorHelper
    {
        public static Assembly LoadAssembly(string assemblyPath)
        {
            try
            {
                var assemblyName = AssemblyName.GetAssemblyName(assemblyPath);
                var assembly = Assembly.Load(assemblyName);
                Debug.WriteLine("Assembly full name: " + assembly.FullName);
                return assembly;
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Failed to load " + assemblyPath + ":\n" + ex.ToString());
                return null;
            }
        }

        public static IDictionary<Assembly, IList<Type>> GetSubTypes<T>(string path, string pattern) where T : class
        {
            if (string.IsNullOrWhiteSpace(path))
                path = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            Debug.WriteLine("Library seaching path: " + path);

            if (string.IsNullOrWhiteSpace(pattern))
                pattern = "*.dll";

            var availableTypesMap = new Dictionary<Assembly, IList<Type>>();

            var dllPathes = Directory.GetFiles(path, pattern);
            if (dllPathes.Length == 0)
                return availableTypesMap;

            foreach (var dllPath in dllPathes)
            {
                var assembly = LoadAssembly(dllPath);
                if (assembly == null)
                    continue;

                var types = GetSubTypes<T>(assembly);
                if (types.Count > 0)
                    availableTypesMap[assembly] = types;
            }

            return availableTypesMap;
        }

        public static IList<Type> GetSubTypes<T>(Assembly assembly) where T : class
        {
            if (assembly == null)
                return new List<Type>();

            try
            {
                return assembly.GetTypes()
                    .Where(type => !type.IsInterface && !type.IsAbstract)
                    .Where(type => type.BaseType == typeof(T))
                    .ToList();
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.ToString());
                return new List<Type>();
            }
        }

        public static IList<Type> GetSubTypes<T>(string assemblyPath) where T : class
        {
            return GetSubTypes<T>(LoadAssembly(assemblyPath));
        }

        public static T Create<T>(string assemblyPath, string typeName, params object[] args) where T : class
        {
            var types = GetSubTypes<T>(assemblyPath);
            if (types.Count == 0)
                return null;

            return Create<T>(types.Where(type => type.Name == typeName).FirstOrDefault(), args);
        }

        public static T Create<T>(Type type, params object[] args) where T : class
        {
            if (type == null)
                return null;

            try
            {
                return Activator.CreateInstance(type, args) as T;
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.ToString());
                return null;
            }
        }
    }
}


// References:
// https://code.msdn.microsoft.com/windowsdesktop/Creating-a-simple-plugin-b6174b62
// https://www.codeproject.com/articles/889453/load-and-unload-plug-in-without-file-lock
// https://stackoverflow.com/questions/26530731/runtime-loading-of-private-assemblies-in-a-subdirectory
