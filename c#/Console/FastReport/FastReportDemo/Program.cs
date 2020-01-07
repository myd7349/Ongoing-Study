namespace FastReportDemo
{
    using System;
    using System.Collections.Generic;

    using FastReport;
    using FastReport.Export.Image;

    class Program
    {
        static void Main(string[] args)
        {
            using (var report = new Report())
            {
                var movies = new List<Movie>
                {
                    new Movie
                    {
                        SN = "tt1979376",
                        Name = "Toy Story 4",
                        Director = "Josh Cooley",
                        EstimatedBudget = "$200,000,000",
                        ReleaseDate = "21 June 2019"
                    },
                    new Movie
                    {
                        SN = "tt3263904",
                        Name = "Sully",
                        Director = "Clint Eastwood",
                        EstimatedBudget = "$60,000,000",
                        ReleaseDate = "9 September 2016"
                    },
                    new Movie
                    {
                        SN = "tt1535109",
                        Name = "Captain Phillips",
                        Director = "Paul Greengrass",
                        EstimatedBudget = "$55,000,000",
                        ReleaseDate = "11 October 2013"
                    },
                };

                report.Load("report.frx");
                report.RegisterData(movies, "Movies");
                report.SetParameterValue("LastUpdated", DateTime.Now);
                report.Prepare();

                using (var imageExporter = new ImageExport())
                {
                    imageExporter.ImageFormat = ImageExportFormat.Metafile;
                    imageExporter.Resolution = 96;

                    report.Export(imageExporter, "report.emf");
                }
            }
        }
    }
}

// References:
// https://github.com/FastReports/FastReport.Documentation/blob/master/Exporting.md
// https://github.com/FastReports/FastReport/tree/master/Demos/OpenSource/DataFromBusinessObject
// https://github.com/p-ranav/tabulate
