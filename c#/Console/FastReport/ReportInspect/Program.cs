namespace ReportInspect
{
    using System;
    using System.Diagnostics;
    using System.Drawing;
    using System.IO;

    using CommandLine;

    using FastReport;
    using FastReport.Utils;

    class Program
    {
        static void Main(string[] args)
        {
            Parser.Default.ParseArguments<Options>(args).WithParsed(Run);
        }

        private static void Run(Options options) => Environment.Exit(RunInternal(options));

        private static int RunInternal(Options options)
        {
            if (!File.Exists(options.TemplateFilePath))
            {
                Console.WriteLine($"Template file \"{options.TemplateFilePath}\" doesn't exist.");
                return 1;
            }

            using (var report = new Report())
            {
                try
                {
                    report.Load(options.TemplateFilePath);
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Failed to load report template \"{options.TemplateFilePath}\":\n{ex}");
                    return 1;
                }

                if (string.IsNullOrEmpty(options.ObjectName))
                {
                    ObjectInspector.TreeHelper.Print(report);
                    return 0;
                }

                if (options.Prepare && !report.Prepare())
                {
                    Console.WriteLine("Failed to prepare the report object.");
                    return 1;
                }

                var reportObject = report.FindObject(options.ObjectName);
                if (reportObject == null)
                {
                    Console.WriteLine($"Couldn't find an object with name \"{options.ObjectName}\".");
                    return 1;
                }

                var component = reportObject as ComponentBase;
                if (component == null)
                {
                    Console.WriteLine($"Object \"{options.ObjectName}\" is not an instance of ComponentBase.");
                    return 1;
                }

                // Specify "--abs" to take parent Band into consideration.
                RectangleF bounds;
                if (options.Abs)
                {
                    bounds = component.AbsBounds;
                }
                else
                {
                    bounds = component.Bounds;

                    if (options.Recursive)
                    {
                        var parent = component.Parent as ComponentBase;
                        while (parent != null)
                        {
                            bounds.X += parent.Left;
                            bounds.Y += parent.Top;

                            parent = parent.Parent as ComponentBase;
                        }
                    }
                }

                if (options.Margin)
                {
                    var page = component.Page as ReportPage;
                    if (page != null)
                    {
                        // Convert unit: millimeters -> dots or pixels
                        var left = page.LeftMargin * Units.Millimeters;
                        var top = page.TopMargin * Units.Millimeters;

                        bounds.X += left;
                        bounds.Y += top;
                    }
                    else
                    {
                        Console.WriteLine("*** Warning: Couldn't find parent ReportPage object.");
                    }
                }

                var sep = options.Separator;

                switch (options.Unit)
                {
                    case Unit.Dots:
                        Console.WriteLine($"{bounds.Left}{sep}{bounds.Top}{sep}{bounds.Right}{sep}{bounds.Bottom}");
                        break;
                    case Unit.Millimeters:
                        Console.WriteLine($"{bounds.Left / Units.Millimeters}{sep}{bounds.Top / Units.Millimeters}{sep}{bounds.Right / Units.Millimeters}{sep}{bounds.Bottom / Units.Millimeters}");
                        break;
                    case Unit.Centimeters:
                        Console.WriteLine($"{bounds.Left / Units.Centimeters}{sep}{bounds.Top / Units.Centimeters}{sep}{bounds.Right / Units.Centimeters}{sep}{bounds.Bottom / Units.Centimeters}");
                        break;
                    case Unit.Inches:
                        Console.WriteLine($"{bounds.Left / Units.Inches}{sep}{bounds.Top / Units.Inches}{sep}{bounds.Right / Units.Inches}{sep}{bounds.Bottom / Units.Inches}");
                        break;
                    case Unit.HundrethsOfInch:
                        Console.WriteLine($"{bounds.Left / Units.HundrethsOfInch}{sep}{bounds.Top / Units.HundrethsOfInch}{sep}{bounds.Right / Units.HundrethsOfInch}{sep}{bounds.Bottom / Units.HundrethsOfInch}");
                        break;
                    default:
                        Debug.Assert(false, $"Unexpected unit: {options.Unit}.");
                        break;
                }
            }

            return 0;
        }
    }
}


// References:
// [Precise positioning](https://forum.fast-report.com/en/discussion/3636/precise-positioning)
// https://www.fast-report.com/documentation/DevMan/index.html?fastreport_classes_hierarchy.htm
// > The following properties are defined in the “TfrxComponent” class:
// > `Left`: object X-coordinate (relative to parent)
// > `AbsLeft`: object absolute X-coordinate
