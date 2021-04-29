namespace ATasteOfGitVersion
{
    using System;
    using System.Diagnostics;
    using System.Reflection;

    class Program
    {
        static void Main(string[] args)
        {
            var assembly = Assembly.GetEntryAssembly();
            Console.WriteLine("File version: {0}", GetFileVersion(assembly));
            Console.WriteLine("Informational version: {0}", GetInformationalVersion(assembly));

            var assemblyName = assembly.GetName().Name;
            var gitVersionInformationType = assembly.GetType("GitVersionInformation");
            var fields = gitVersionInformationType.GetFields();

            foreach (var field in fields)
                Console.WriteLine(string.Format("{0}: {1}", field.Name, field.GetValue(null)));

            // The GitVersionInformation class generated from a F# project exposes properties
            var properties = gitVersionInformationType.GetProperties();
            foreach (var property in properties)
                Console.WriteLine(string.Format("{0}: {1}", property.Name, property.GetGetMethod(true).Invoke(null, null)));
        }

        static string GetFileVersion(Assembly assembly)
        {
            return FileVersionInfo.GetVersionInfo(assembly.Location).FileVersion;
        }

        static string GetInformationalVersion(Assembly assembly)
        {
            var assemblyInformationalVersionAttributes = assembly.GetCustomAttributes(typeof(AssemblyInformationalVersionAttribute), false)
                as AssemblyInformationalVersionAttribute[];
            if (assemblyInformationalVersionAttributes != null && assemblyInformationalVersionAttributes.Length > 0)
                return assemblyInformationalVersionAttributes[0].InformationalVersion;

            return string.Empty;
        }
    }
}

// References:
// https://github.com/GitTools/GitVersion
// [GitVersion: MSBuild Task](https://gitversion.net/docs/usage/msbuild)
// https://gitversion.net/docs/usage/cli/assembly-patch
// https://github.com/microsoft/wslg/blob/5e9419849c89863ad36753e7c1707f20f9e0d0cd/msi/updateversion.ps1#L48-L62
