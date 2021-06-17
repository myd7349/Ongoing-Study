namespace ATasteOfNerdbankGitVersioning
{
    using System;
    using System.Reflection;

    using Common;

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine($"Version: {Assembly.GetEntryAssembly().GetBuildVersion()}");
            Console.ReadKey();
        }
    }
}

// References:
// https://github.com/dotnet/Nerdbank.GitVersioning/blob/master/doc/nuget-acquisition.md
// 1. PM> Install-Package Nerdbank.GitVersioning
// 2. PS> dotnet tool install -g nbgv
//        This will generate a `version.json` and `Directory.Build.props` under the root of Ongoing-Study,
//        move them to the same directory with ATasteOfNerdbankGitVersioning.csproj.
