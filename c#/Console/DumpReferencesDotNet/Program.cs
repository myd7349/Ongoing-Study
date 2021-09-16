//#define USING_ASSEMBLY_NAME

namespace DumpReferences
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Reflection;

    class Program
    {
        static void Main(string[] args)
        {
            foreach (var arg in args)
            {
                if (args.Length > 1)
                    Console.WriteLine("------------------------------ {0} ------------------------------", arg);

                string path = arg;
                if (!Path.IsPathRooted(path))
                    path = Path.GetFullPath(path);

                Assembly assembly;
                try
                {
                    assembly = Assembly.LoadFile(path);
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Failed to load {0}:\n{1}", path, ex.ToString());
                    continue;
                }

                DumpReferences(assembly, 0, null);
            }
        }

#if USING_ASSEMBLY_NAME
        static void DumpReferences(Assembly assembly, int indentLevel, HashSet<AssemblyName> knownAssemblies)
#else
        static void DumpReferences(Assembly assembly, int indentLevel, HashSet<string> knownAssemblies)
#endif
        {
            var indent = new string(' ', indentLevel * 4);

            foreach (var reference in assembly.GetReferencedAssemblies())
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
                    knownAssemblies.Add(reference.FullName);
                    DumpReferences(Assembly.Load(reference), indentLevel + 1, knownAssemblies);
                }
#endif
            }
        }
    }
}


// References:
// [C# Recursively Find References in All Projects In Solution](https://stackoverflow.com/questions/32974118/c-sharp-recursively-find-references-in-all-projects-in-solution)
