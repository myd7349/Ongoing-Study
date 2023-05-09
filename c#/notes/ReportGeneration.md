https://github.com/ClosedXML/ClosedXML.Report

https://github.com/FastReports/FastReport

[Microsoft.Reporting.WinForms Namespace](https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2008/ms252706(v=vs.90))

- https://github.com/abbaye/RDLCPrinter

https://github.com/itext/itextsharp/blob/develop/src/core/iTextSharp/text/pdf/AcroFields.cs

- [Reading Acrofields from PDF Files](https://www.codeproject.com/Articles/1032782/Reading-Acrofields-from-PDF-Files)
- [how to create a template PDF file with acrofields?](https://stackoverflow.com/questions/19564086/how-to-create-a-template-pdf-file-with-acrofields)

QuickReport

RaveReport

Crystal Reports

[axlsx](https://github.com/randym/axlsx)

- [caxlsx](https://github.com/caxlsx/caxlsx)

FineReport

- [FastReport报表工具与FineReport报表工具的对比](https://www.finereport.com/knowledge/acquire/fastreport.html)

[FlexReport](https://marketplace.visualstudio.com/items?itemName=GrapeCityinc.ReportsforWinForms)

[Seal-Report](https://github.com/ariacom/Seal-Report)

[carbone](https://github.com/carboneio/carbone)

[Microsoft.Reporting.WinForms Namespace | Microsoft Docs](https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2010/ms252706(v=vs.100))

- [LocalReport Class (Microsoft.Reporting.WinForms) | Microsoft Docs](https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2010/ms255056(v=vs.100))

- [Create RDLC Report In C# ASP.NET](https://www.c-sharpcorner.com/article/create-rdlc-report-in-C-Sharp-Asp-Net/)
  
  > RDLC Stands for Report Definition Language Client Side. It is used to create reports using Microsoft Reporting Technology.  
  > 
  > It is not a third party report and is a built-in reporting service in Microsoft Visual Studio.

- [Localreport render EMF image dpi settings](https://social.msdn.microsoft.com/Forums/en-US/93a18d13-2f43-426c-b475-d88ca068279a/localreport-render-emf-image-dpi-settings?forum=vsreportcontrols)
  
  > ```csharp
  > public void CreateTiffedReport()
  > {
  >     LocalReport report = new LocalReport();
  >     report.ReportEmbeddedResource = "myReport.rdlc";
  >     report.DataSources.Add(new ReportDataSource("dsName", dsValue));
  >     ExportTiff(report);
  > }
  > 
  > private void ExportTiff(LocalReport report)
  > {
  >     // dpix and dpiy don't seem to work, always 96 :(
  >     string deviceInfo =
  >           "<DeviceInfo>" +
  >           "  <OutputFormat>EMF</OutputFormat>" +
  >           "  <PageWidth>8.5in</PageWidth>" +
  >           "  <PageHeight>11in</PageHeight>" +
  >           "  <DpiX>200</DpiX>" +
  >           "  <DpiY>200</DpiY>" +
  >           "  <MarginTop>0.25in</MarginTop>" +
  >           "  <MarginLeft>0.25in</MarginLeft>" +
  >           "  <MarginRight>0.25in</MarginRight>" +
  >           "  <MarginBottom>0.25in</MarginBottom>" +
  >           "</DeviceInfo>";
  > 
  >     Warning[] warnings;
  >     _renderedReportStreams = new List<Stream>();
  >     report.Render("Image", deviceInfo, CreateStream, out warnings);
  > 
  >     foreach (Stream stream in _renderedReportStreams)
  >     {
  >         stream.Position = 0;
  >         Metafile image = new Metafile(stream);
  >         image.Save("testReport.tif", ImageFormat.Tiff);
  >         _reportCurrentPageIndex++;
  >     }
  > }
  > 
  > 
  > private Stream CreateStream(string name, string fileNameExtension, Encoding encoding, string mimeType, bool willSeek)
  > {
  >     Stream stream = new MemoryStream();
  >     _renderedReportStreams.Add(stream);
  >     return stream;
  > }
  > ```

  - [Infragistics Document Engine](https://www.infragistics.com/help/winforms/documentengine-welcome-to-infragistics-document-engine)
  
- [ClosedXML.Report](https://github.com/ClosedXML/ClosedXML.Report)

- [ReoGrid](https://github.com/unvell/ReoGrid)

- [RichTextKit](https://github.com/toptensoftware/RichTextKit)

- [Magicodes.IE](https://github.com/dotnetcore/Magicodes.IE)

- [DevExpress.XtraReports](https://docs.devexpress.com/XtraReports/DevExpress.XtraReports.UI.XtraReport)

- [只用最适合的 | 主流 .NET 报表控件全面对比](https://blog.csdn.net/Juvien_Huang/article/details/129275957)

  - FastReport.NET
  - Stimulsoft Report
  - SAP Crystal Reports
