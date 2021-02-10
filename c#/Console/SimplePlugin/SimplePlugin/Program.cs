namespace SimplePlugin
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Reflection;

    using PluginLib;

    class Program
    {
        static void Main(string[] args)
        {
            var appPath = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);

            var dllFileNames = Directory.GetFiles(appPath, "*.dll");
            Console.WriteLine("Candidate plugins: ");
            foreach (var dll in dllFileNames)
                Console.WriteLine(dll);

            var assemblies = new List<Assembly>(dllFileNames.Length);
            foreach (var dllPath in dllFileNames)
            {
                try
                {
                    var assemblyName = AssemblyName.GetAssemblyName(dllPath);
                    var assembly = Assembly.Load(assemblyName);
                    assemblies.Add(assembly);
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.ToString());
                }
            }

            var pluginType = typeof(IPlugin);
            var pluginTypes = new List<Type>();
            foreach (var assembly in assemblies)
            {
                if (assembly != null)
                {
                    var types = assembly.GetTypes();
                    foreach (var type in types)
                    {
                        if (type.IsInterface || type.IsAbstract)
                            continue;

                        if (type.GetInterface(pluginType.FullName) != null)
                            pluginTypes.Add(type);
                    }
                }
            }

            var plugins = new List<IPlugin>(pluginTypes.Count);
            foreach (var type in pluginTypes)
            {
                var plugin = Activator.CreateInstance(type) as IPlugin;
                plugins.Add(plugin);
            }

            foreach (var plugin in plugins)
            {
                Console.WriteLine("Plugin name: {0}", plugin.Name);
                if (plugin.Ok)
                    plugin.Do();
                else
                    Console.WriteLine("{0} are not ready for working yet.", plugin.Name);
            }

            Console.ReadKey();
        }
    }
}


// References:
// https://code.msdn.microsoft.com/windowsdesktop/Creating-a-simple-plugin-b6174b62
// https://www.codeproject.com/articles/889453/load-and-unload-plug-in-without-file-lock
// https://stackoverflow.com/questions/26530731/runtime-loading-of-private-assemblies-in-a-subdirectory
// https://github.com/Tencent/behaviac/blob/master/tools/designer/BehaviacDesignerBase/Plugin.cs
