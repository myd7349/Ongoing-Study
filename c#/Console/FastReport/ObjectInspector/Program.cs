namespace ObjectInspector
{
    using System;
    using System.CommandLine;
    using System.IO;

    using FastReport;
    using FastReport.Utils;

    class Program
    {
        static int Main(string[] args)
        {
            return BuildCommandLine().Invoke(args);
        }

        static RootCommand BuildCommandLine()
        {
            var templateFileOption = new Option<FileInfo>(
                new[] { "--template", "-t" },
                description: "FastReport template file path")
            {
                IsRequired = true
            };
            var objectNamesOption = new Option<string[]>(
                new[] { "--name", "-n" },
                description: "Object name(s)")
            {
                AllowMultipleArgumentsPerToken = true,
            };

            var rootCommand = new RootCommand
            {
                templateFileOption,
                objectNamesOption
            };
            rootCommand.Description = "FastReport object inspector.";
            rootCommand.SetHandler<FileInfo, string[]>(Run, templateFileOption, objectNamesOption);

            return rootCommand;
        }

        static void Run(FileInfo templateFile, string[] objectNames)
        {
            if (!templateFile.Exists)
            {
                Console.WriteLine($"Report emplate \"{templateFile}\" doesn't exist.");
                return;
            }

            using (var report = new Report())
            {
                try
                {
                    report.Load(templateFile.FullName);
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Failed to load report template \"{templateFile.Name}\":\r\n{ex}");
                    return;
                }

                if (objectNames.Length == 0)
                {
                    DumpReportTree(report);
                }
                else
                {
                    // https://github.com/FastReports/FastReport/blob/d266d9bc2840d46515c38caafca773926a22dba3/FastReport.Base/Utils/Units.cs#L41-L67
                    Console.WriteLine($"Units.Centimeters: {Units.Centimeters}");
                    Console.WriteLine($"Units.HundrethsOfInch: {Units.HundrethsOfInch}");
                    Console.WriteLine($"Units.Inches: {Units.Inches}");
                    Console.WriteLine($"Units.Millimeters: {Units.Millimeters}");
                    Console.WriteLine($"Units.TenthsOfInch: {Units.TenthsOfInch}");

                    foreach (var objectName in objectNames)
                    {
                        InspectObject(report, objectName);
                    }
                }
            }
        }

        static void DumpReportTree(Report report)
        {
            TreeHelper.Print(report);
        }

        static void InspectObject(Report report, string objectName)
        {
            Console.WriteLine($"--------------------------------------------------------------------------------");

            var reportObject = report.FindObject(objectName);
            if (reportObject == null)
            {
                Console.WriteLine($"Coludn't find object \"{objectName}\".");
                return;
            }

            ObjectInspector.Inspect(reportObject);
        }
    }
}


// References:
// https://github.com/dotnet/command-line-api/blob/main/docs/Your-first-app-with-System-CommandLine.md
// https://github.com/FastReports/FastReport
// https://github.com/wieslawsoltes/Core2D/blob/master/src/Core2D.Desktop/Program.cs
