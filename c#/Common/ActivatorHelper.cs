﻿namespace Common.Reflection
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.IO;
    using System.Linq;
    using System.Reflection;

    public static class ActivatorHelper
    {
        public static bool DefaultTypeFilter<T>(Type type) where T : class
        {
            return type != null &&
                !type.IsInterface &&
                !type.IsAbstract &&
                typeof(T).IsAssignableFrom(type);
        }

        public static Assembly LoadAssembly(string assemblyPath, SearchOption searchOption = SearchOption.TopDirectoryOnly)
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

                if (!Path.IsPathRooted(assemblyPath))
                {
                    var dllPathes = Directory.GetFiles(
                        AppContext.BaseDirectory, assemblyPath, searchOption);
                    foreach (var dll in dllPathes)
                    {
                        try
                        {
#if false
                            // Boom!!!
                            var assembly = Assembly.Load(dll);
#elif false
                            // OK!
                            var assemblyName = AssemblyName.GetAssemblyName(dll);
                            var assembly = Assembly.Load(assemblyName);
#else
                            var assembly = Assembly.LoadFrom(dll);
#endif

                            return assembly;
                        }
                        catch (Exception ex2)
                        {
                            Debug.WriteLine("Failed to load " + dll + ":\n" + ex2.ToString());
                        }
                    }
                }

                return null;
            }
        }

        public static IDictionary<Assembly, IList<Type>> GetSubTypes<T>(string path, string pattern) where T : class
        {
            return GetSubTypes<T>(path, pattern, DefaultTypeFilter<T>);
        }

        public static IDictionary<Assembly, IList<Type>> GetSubTypes<T>(string path, string pattern, Predicate<Type> typeFilter) where T : class
        {
            return GetSubTypes<T>(path, pattern, SearchOption.TopDirectoryOnly, typeFilter);
        }

        public static IDictionary<Assembly, IList<Type>> GetSubTypes<T>(string path, string pattern, SearchOption searchOption, Predicate<Type> typeFilter) where T : class
        {
            if (string.IsNullOrWhiteSpace(path))
                path = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            Debug.WriteLine("Library seaching path: " + path);

            if (string.IsNullOrWhiteSpace(pattern))
                pattern = "*.dll";

            var subTypesMap = new Dictionary<Assembly, IList<Type>>();

            var dllPathes = Directory.GetFiles(path, pattern, searchOption);
            if (dllPathes.Length == 0)
                return subTypesMap;

            foreach (var dllPath in dllPathes)
            {
                var assembly = LoadAssembly(dllPath);
                if (assembly == null)
                    continue;

                var types = GetSubTypes<T>(assembly, typeFilter);
                if (types.Count > 0)
                    subTypesMap[assembly] = types;
            }

            return subTypesMap;
        }

        public static IList<Type> GetSubTypes<T>(Assembly assembly) where T : class
        {
            return GetSubTypes<T>(assembly, DefaultTypeFilter<T>);
        }

        public static IList<Type> GetSubTypes<T>(Assembly assembly, Predicate<Type> typeFilter) where T : class
        {
            if (assembly == null)
                return new List<Type>();

            try
            {
                return assembly.GetTypes()
                    .Where(type => typeFilter(type))
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
            return GetSubTypes<T>(LoadAssembly(assemblyPath), DefaultTypeFilter<T>);
        }

        public static IList<Type> GetSubTypes<T>(string assemblyPath, Predicate<Type> typeFilter) where T : class
        {
            return GetSubTypes<T>(LoadAssembly(assemblyPath), typeFilter);
        }

        public static T Create<T>(string assemblyPath, string typeName, params object[] args) where T : class
        {
            var types = GetSubTypes<T>(assemblyPath, DefaultTypeFilter<T>);
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
// https://stackoverflow.com/questions/24978661/how-to-provide-default-value-for-a-parameter-of-delegate-type-in-c
// https://stackoverflow.com/questions/10710870/default-value-of-delegates-inside-classes
// https://docs.microsoft.com/en-us/dotnet/api/system.type.basetype?view=netframework-4.8
// https://kaliko.com/blog/c-test-if-object-or-type-implements/
// https://stackoverflow.com/questions/8699053/how-to-check-if-a-class-inherits-another-class-without-instantiating-it
// https://stackoverflow.com/questions/457676/check-if-a-class-is-derived-from-a-generic-class
// https://github.com/de4dot/de4dot/blob/b7d5728fc0c82fb0ad758e3a4c0fbb70368a4853/de4dot.cui/Program.cs#L38-L50
// https://github.com/j-maly/CommandLineParser/blob/master/src/CommandLineArgumentsParser/Compatibility/TypeExtensions.cs
// https://github.com/natemcmaster/DotNetCorePlugins
// https://github.com/mattleibow/SkiaSharpFiddle
// [ActivatorUtilities](https://docs.microsoft.com/en-us/dotnet/api/microsoft.extensions.dependencyinjection.activatorutilities?view=dotnet-plat-ext-6.0)
// [.NET Core Console App with Dependency Injection, Logging, and Settings](https://www.youtube.com/watch?v=GAOCe-2nXqc)
// [Understanding How Assemblies Load in C# .NET](https://michaelscodingspot.com/assemblies-load-in-dotnet/)
// https://github.com/AdamsLair/duality/blob/master/Source/Core/Duality/Backend/PluginLoader/IAssemblyLoader.cs
