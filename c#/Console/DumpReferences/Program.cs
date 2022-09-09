//#define USING_ASSEMBLY_NAME

namespace DumpReferences
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Reflection;

    class Program
    {
        static List<string> CandidateSearchDirectories = new List<string>();

        static void Main(string[] args)
        {
            foreach (var arg in args)
            {
                if (args.Length > 1)
                    Console.WriteLine("------------------------------ {0} ------------------------------", arg);

                string path = arg;
                if (!Path.IsPathRooted(path))
                    path = Path.GetFullPath(path);

                CandidateSearchDirectories.Add(Path.GetDirectoryName(path));
                CandidateSearchDirectories.Add(Directory.GetCurrentDirectory());
                CandidateSearchDirectories.Add(AppDomain.CurrentDomain.BaseDirectory);

                Assembly assembly;
                try
                {
                    assembly = Assembly.ReflectionOnlyLoadFrom(path);
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Failed to load {0}:\n{1}", path, ex.ToString());
                    continue;
                }

                DumpReferences(assembly, 0, null);
            }
        }

        static Assembly LoadAssemblyFrom(string assemblyFile)
        {
            if (Path.IsPathRooted(assemblyFile))
                return Assembly.ReflectionOnlyLoadFrom(assemblyFile);

            foreach (var dir in CandidateSearchDirectories)
            {
                var assemblyFilePath = Path.Combine(dir, assemblyFile);
                if (File.Exists(assemblyFilePath))
                {
                    try
                    {
                        return Assembly.ReflectionOnlyLoadFrom(assemblyFilePath);
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"**** Error: Failed to load {assemblyFilePath}: {ex.Message}");
                    }
                }
            }

            return null;
        }

        static Assembly LoadAssembly(AssemblyName assemblyName)
        {
            try
            {
                return Assembly.ReflectionOnlyLoad(assemblyName.FullName);
            }
            catch
            {
                try
                {
                    return Assembly.Load(assemblyName);
                }
                catch
                {
                    var assemblyFileName = $"{assemblyName.Name}.dll";
                    return LoadAssemblyFrom(assemblyFileName);
                }
            }
        }

#if USING_ASSEMBLY_NAME
        static void DumpReferences(Assembly assembly, int indentLevel, HashSet<AssemblyName> knownAssemblies)
#else
        static void DumpReferences(Assembly assembly, int indentLevel, HashSet<string> knownAssemblies)
#endif
        {
            var indent = new string(' ', indentLevel * 4);

            var referencedAssemblies = assembly.GetReferencedAssemblies();
            if (referencedAssemblies == null)
                return;

            foreach (var reference in referencedAssemblies)
            {
                Console.Write(indent);
                Console.WriteLine(reference.Name);

                if (indentLevel == 0)
#if USING_ASSEMBLY_NAME
                    knownAssemblies = new HashSet<AssemblyName>();
#else
                    knownAssemblies = new HashSet<string>();
#endif

#if USING_ASSEMBLY_NAME
                if (!knownAssemblies.Contains(reference))
                {
                    knownAssemblies.Add(reference);
                    DumpReferences(Assembly.Load(reference), indentLevel + 1, knownAssemblies);
                }
#else
                if (!knownAssemblies.Contains(reference.FullName))
                {
                    var referenceAssembly = LoadAssembly(reference);
                    if (referenceAssembly == null)
                    {
                        Console.WriteLine($"*** Warning: Failed to load {reference}.");
                    }
                    else
                    {
                        knownAssemblies.Add(reference.FullName);
                        DumpReferences(referenceAssembly, indentLevel + 1, knownAssemblies);
                    }
                }
#endif
            }
        }
    }
}


// References:
// [C# Recursively Find References in All Projects In Solution](https://stackoverflow.com/questions/32974118/c-sharp-recursively-find-references-in-all-projects-in-solution)
// https://github.com/nikeyes/DotNetProjectsDependenciesViewer
// https://github.com/spectresystems/snitch
// https://github.com/RicoSuter/ProjectDependencyBrowser
// [How to add folder to assembly search path at runtime in .NET?](https://stackoverflow.com/questions/1373100/how-to-add-folder-to-assembly-search-path-at-runtime-in-net)
// https://github.com/seesharper/dotnet-deps
// https://github.com/clovett/tools/blob/master/ComponentDependency/ComponentDependency/Program.cs
// https://github.com/clovett/tools/tree/master/DependencyViewer
