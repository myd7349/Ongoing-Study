[AppDomain](https://learn.microsoft.com/en-us/dotnet/api/system.appdomain?view=net-6.0)

[AssemblyResolve](https://github.com/microsoft/perfview/blob/main/src/HeapDump/Program.cs)

[greenshot/GreenshotMain.cs at 82b37bcaa4b051313dbe28cab84863fc0c048dd5 · greenshot/greenshot · GitHub](https://github.com/greenshot/greenshot/blob/82b37bcaa4b051313dbe28cab84863fc0c048dd5/src/Greenshot/GreenshotMain.cs#L35-L57)

> ```csharp
> static GreenshotMain()
> {
>     AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
> }
> 
> private static Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
> {
>     Assembly ayResult = null;
>     string sShortAssemblyName = args.Name.Split(',')[0];
>     Assembly[] ayAssemblies = AppDomain.CurrentDomain.GetAssemblies();
>     foreach (Assembly ayAssembly in ayAssemblies)
>     {
>         if (sShortAssemblyName != ayAssembly.FullName.Split(',')[0])
>         {
>             continue;
>         }
> 
>         ayResult = ayAssembly;
>         break;
>     }
> 
>     return ayResult;
> }
> ```

https://github.com/chocolatey/ChocolateyGUI/blob/1.0.0/Source/ChocolateyGui/App.xaml.cs#L36-L94

[How to add folder to assembly search path at runtime in .NET?](https://stackoverflow.com/questions/1373100/how-to-add-folder-to-assembly-search-path-at-runtime-in-net)

```csharp
string path = args[0];
if (!Path.IsPathRooted(path))
    path = Path.GetFullPath(path);

var candidateSearchDirectories = new[]
{
    Path.GetDirectoryName(path),
    Directory.GetCurrentDirectory(),
};

AppDomain.CurrentDomain.AssemblyResolve += (sender, e) =>
{
    var assemblyFileName = $"{new AssemblyName(e.Name).Name}.dll";
    foreach (var dir in candidateSearchDirectories)
    {
        var assemblyFilePath = Path.Combine(dir, assemblyFileName);
        if (File.Exists(assemblyFilePath))
        {
            try
            {
                return Assembly.ReflectionOnlyLoad(assemblyFilePath);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"**** Error: Failed to load {assemblyFilePath}: {ex.Message}");
            }
        }
    }

    return null;
};
```

[How to load assemblies in different folders C#](https://stackoverflow.com/questions/39170790/how-to-load-assemblies-in-different-folders-c-sharp)

```csharp
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

        if (!Path.IsPathRooted(assemblyPath))
        {
            var dllPathes = Directory.GetFiles(
                AppContext.BaseDirectory, assemblyPath, SearchOption.AllDirectories);
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
```

[C# Putting the required DLLs somewhere other than the root of the output](https://stackoverflow.com/questions/2445556/c-sharp-putting-the-required-dlls-somewhere-other-than-the-root-of-the-output)

https://github.com/slmjy/PrettyBin

https://github.com/nulastudio/NetBeauty2

See also [System.Runtime.Loader](System.Runtime.Loader.md).
