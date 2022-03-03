namespace ScriptPlayground
{
    using System;
    using System.IO;
    using System.Reflection;

    using FastReport;
    using FastReport.Export.Image;

    using Common;

    static class ReportUtility
    {
        public static void CreateReport(Person person)
        {
            if (person == null)
                throw new ArgumentNullException("person");

            var applicationFilePath = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);

            using (var report = new Report())
            {
                try
                {
                    report.Load(Path.Combine(applicationFilePath, "./Template.frx"));
                }
                catch (Exception ex)
                {
                    MsgBox.Error("Failed to load report template.\r\n{0}", ex.ToString());
                }

                if (person.Name != null)
                    report.SetParameterValue("Name", person.Name);

                if (person.Age != null)
                    report.SetParameterValue("Age", person.Age.Value);

                if (person.Gender != null)
                    report.SetParameterValue("Gender", person.Gender);

                if (person.ID != null)
                    report.SetParameterValue("ID", person.ID);

                if (person.Address != null)
                    report.SetParameterValue("Address", person.Address);

                if (person.Phone != null)
                    report.SetParameterValue("Phone", person.Phone);

                if (!report.Prepare())
                {
                    MsgBox.Error("Report.Prepare failed.");
                    return;
                }
                else
                {
                    MsgBox.Information("Report.Prepare");
                }

                using (var imageExporter = new ImageExport())
                {
                    imageExporter.ImageFormat = ImageExportFormat.Metafile;
                    imageExporter.Resolution = 600;
                    report.Export(imageExporter, "Report.emf");
                }
            }
        }
    }
}
