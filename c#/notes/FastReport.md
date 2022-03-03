[FastReport Designer Community Edition](https://fastreports.github.io/FastReport.Documentation/FastReportDesignerCommunityEdition.html)

https://fastreports.github.io/FastReport.Documentation/

[FastReport Comparison](https://www.fast-report.com/en/fast-report-comparison/)

[fastreport Hide Elements in DataBand depending on Data](https://stackoverflow.com/questions/53591235/fastreport-hide-elements-in-databand-depending-on-data)

[How to hide columns in a list if there is no data](https://www.fast-report.com/en/blog/show/hiding-no-data-columns/)

[How to set a picture in a report from the user application code](https://www.fast-report.com/en/blog/show/picture-from-user-code/)

First case:

```csharp
//Create instance of class Report
Report report = new Report();
//Add report page
ReportPage page = new ReportPage();
report.Pages.Add(page);
page.CreateUniqueName();
//App data band
DataBand data = new DataBand();
//Add data band to page
page.Bands.Add(data);
data.CreateUniqueName();
data.Height = Units.Centimeters * 1; //Set band height
//Create picture object
PictureObject pic = new PictureObject();
pic.Bounds = new RectangleF(0, 0, Units.Centimeters * 5, Units.Centimeters * 5); //Set object bounds
pic.Image = new Bitmap("../../App_Data/snow_flake.ico"); //Set picture
pic.Parent = data; //Set picture parent object
pic.CreateUniqueName();
report.Prepare(); //Build report
report.Show(); //Show report
```

Another case:

```csharp
//Create report object
Report report = new Report();
//Load report template into the report obj
report.Load("../../App_Data/Picture.frx");
//Get picture object from the report template
PictureObject pic = report.FindObject("Picture1") as PictureObject;
//Set object bounds
pic.Bounds = new RectangleF(0, 0, Units.Centimeters * 5, Units.Centimeters * 5);
//Set the image
pic.Image = new Bitmap("../../App_Data/snow_flake.ico");
//Build report
report.Prepare();
//Show report
report.Show();
```

[FastReport CrossView does not calculate column width correctly if column header is printer vertically](https://stackoverflow.com/questions/14334610/fastreport-crossview-does-not-calculate-column-width-correctly-if-column-header)

FRNetUserManual-en.pdf P383:

> Reference to report objects
> 
> Note that reports's native unit of measurement is screen pixels. Keep it in mind when using such object's properties like Left, Top, Width, and Height. To convert pixels into centimeters and back, use the constants, defined in the "Units" class:
> 
> ```csharp
> float heightInPixels = Text1.Height;
> float heightInCM = heightInPixels / Units.Centimeters;
> Text1.Height = Units.Centimeters * 5; // 5cm
> ```

https://github.com/FastReports/FastReport/blob/d266d9bc2840d46515c38caafca773926a22dba3/FastReport.Base/ReportPage.cs#L307-L349

`ReportPage`'s `LeftMargin`, `TopMargin`, `RightMargin`, `BottomMargin`, `PaperWidth`, `PaperHeight` have a millimeter unit.

[FastReport page orientation change in Delphi](https://stackoverflow.com/questions/1973876/fastreport-page-orientation-change-in-delphi)

> If you have a report that can be printed both in portrait or landscape,  the easiest way to buid this would be a layout for portrait and one for  landscape.

[How to change page orientation in VCL FastReport](https://stackoverflow.com/questions/48506626/how-to-change-page-orientation-in-vcl-fastreport)

https://github.com/FastReports/FastReport/blob/dd337ea7c72fccb079db3d43f3a114f912e8bad6/FastReport.Base/ReportPage.cs#L272

> ```csharp
> public bool Landscape { get; set; }
> ```

[FastReport 4 User's Manual](https://www.fast-report.com/documentation/UserMan/index.html?report_options.htm)

> If the “Double pass” flag is checked report generation will be performed in two steps. During the first pass a draft report is created and divided into pages, but is not available for preview. In the second pass the draft report is converted to a standard report which is then saved in the preview stream.
> 
> Why are two passes necessary? Mostly this option is used in cases where a report needs access to the total number of pages in the report, i.e. for use as “Page 1 of 15”. The total number of pages is calculated during the first pass
>  and is made available via the “TOTALPAGES” system variable. The most frequent mistake is to attempt to use this variable in a single-pass report, when the variable will return 0.
> 
> Another use for two passes is to perform some calculations in the first pass and display the results in the second pass. For example, when a sum is to be displayed in a group header instead of in the usual group footer. Calculations of this type are accomplished by writing report script code in the “OnBeforePrint” event of an object.

https://www.fast-report.com/documentation/DevMan/index.html?fastreport_classes_hierarchy.htm

> The following properties are defined in the “TfrxComponent” class:
> `Left`: object X-coordinate (relative to parent)
> `AbsLeft`: object absolute X-coordinate

[Export to Picture](https://www.fast-report.com/documentation/UserManFrNET-en/index.html?exporttoimage.htm)

> "Resolution" - resolution of the graphical image. Use 96dpi for displaying, 300dpi for printing. When exporting into the TIFF format, you will able to set separate values for horizontal and vertical resolution.

[FastReport.Net User's manual: Report and Engine objects](https://www.fast-report.com/documentation/UserManFrNET-en/index.html?scriptreportandengine.htm)

> Engine.PageWidth and Engine.PageHeight properties determine the size 
> of the printing area, which is almost always less than the actual size 
> of the page. Size of the printed area is determined by the page margins,
>  which is given by the LeftMargin, TopMargin, RightMargin and 
> BottomMargin page properties.
> 
> Engine.FreeSpace property determines the height of the free space on 
> the page. If there is the "Page footer" band on the page, its height is 
> considered when calculating the FreeSpace. Note that, after printing a 
> band, free space is reduced.

https://github.com/FastReports/FastReport/blob/449b3b928de56a4eaf27980ca85651e62bb49e11/FastReport.Base/Export/Image/ImageExport.cs#L483-L535

> ```csharp
> protected override void ExportPageBegin(ReportPage page)
> {
>     base.ExportPageBegin(page);
>     zoomX = ResolutionX / 96f;
>     zoomY = ResolutionY / 96f;
>     width = (int)(ExportUtils.GetPageWidth(page) * Units.Millimeters * zoomX);
>     height = (int)(ExportUtils.GetPageHeight(page) * Units.Millimeters * zoomY);
> ```

[Fast report - printing lines to fill empty space on the bottom of the page between masterdata and pagefooter bands](https://stackoverflow.com/questions/39975485/fast-report-printing-lines-to-fill-empty-space-on-the-bottom-of-the-page-betwe)

> Try to use two-pass report. Store height of each TfrxMasterData in the 
> TfrxMasterData.OnAfterCalcHeight event in the array on the first pass 
> and then use stored values on the second pass

[How to make report inheritance in FastReport.NET](https://www.fast-report.com/en/blog/show/report-inheritance-fastreport-net/)

[How does FastReport. Net copy bands from one report to another](https://chowdera.com/2021/04/20210406170517833z.html)

[How to inherit report from code?](https://www.fast-report.com/en/faq/18/249/)

[FastReport 4 User's Manual](https://www.fast-report.com/documentation/UserMan/index.html?inheritance_control.htm)

[FastReport .NET Demo: Inheritance (EN) - YouTube](https://www.youtube.com/watch?v=8TsOQ28maN8)

[Copying the Bands from One Report to Another with All the Contents](https://www.fast-report.com/en/blog/show/copying-bands-with-all-content/)

> First, you need to download both reports:
> 
> ```csharp
> Report base = new Report();
> base.Load(@"C:\base.frx");
> Report child = new Report();
> child.Load(@"C:\child.frx");
> ```
> 
> The next step is to get the pages from both reports. It is important 
> to know the page names. The following example assumes that the page name
>  in both reports is "Page1":
> 
> ```csharp
> ReportPage basePage = base.FindObject("Page1") as ReportPage;
> ReportPage childPage = child.FindObject("Page1") as ReportPage;
> ```
> 
> If you do not know the page names, you can get them from the index. 
> For example, further we get access to the first pages of both reports:
> 
> ```csharp
> ReportPage basePage = baseReport.Pages[0] as ReportPage;
> ReportPage childPage = childReport.Pages[0] as ReportPage;
> ```
> 
> Both options are appropriate and lead to the same result.
> 
> Now you can replace *PageHeader* and *PageFooter*. It's pretty simple:
> 
> ```csharp
> childPage.PageHeader = basePage.PageHeader;
> childPage.PageFooter = basePage.PageFooter;
> ```
> 
> These lines copy the two bands with all the properties and settings. 
> In addition, all the objects located on them are duplicated and the 
> properties are not lost.
> 
> Next, replace *DataBand* with "Data1" name:
> 
> ```csharp
> DataBand baseBand = basePage.FindObject("Data1") as DataBand;
> DataBand childBand = childPage.FindObject("Data1") as DataBand;
> // you need to get the Data1 index in the child report
> int childBandIndex = childPage.Bands.IndexOf(childBand);
> // you can now delete it
> childPage.Bands.Remove(childBand);
> // and insert the band from the base report in its place
> childPage.Bands.Insert(bandIndex, baseBand);
> ```
> 
> In the end, the band with all the properties and child objects is 
> copied, and the binding to the data source which is responsible for 
> DataSource property is transferred as well. Without this binding, the 
> band will not work correctly and will not output data from the database.
> 
> We just need to copy the data sources. This is done with the following code snippet:
> 
> ```csharp
> for (int i = 0; i < baseReport.Dictionary.DataSources.Count; i++)
> {
>     childReport.Dictionary.DataSources.Add(baseReport.Dictionary.DataSources[i]);
> }
> ```
> 
> Thus, all data sources have been copied. If it is not necessary, you can clone only those desired.

[FastReport 4 User's Manual](https://www.fast-report.com/documentation/UserMan/index.html?events.htm)

> As described above, the script's main procedure is called at the very start of running the report. After that the essentials of report construction begin. Firstly the “OnStartReport” event of the "Report" object is called. Then, before
>  an output page is created, the “OnBeforePrint” page event is called. This event is called once for each design page in the report template(design pages should not be confused with the output pages of a report!). In our example the event is called once, as the report design consists of only one design page.
> 
> Then the events of the data bands are called in the following order:
> 
> 1. the band's “OnBeforePrint” event is called
> 
> 2. the “OnBeforePrint” event of each object contained in the band is called
> 
> 3. each object is filled with data (in our example with values of the “Company” and “Addr1" DB fields)
> 
> 4. the “OnAfterData” event of each object is called
> 
> 5. actions such as positioning objects on the band (if there are stretchable objects among them), calculating band height and stretching it (if it is stretchable) are performed
> 
> 6. the band's “OnAfterCalcHeight” event is called
> 
> 7. a new output page is created if the band hasn't enough room in the page's white space
> 
> 8. the band and all of its objects are displayed on the output  page
> 
> 9. the “OnAfterPrint” event of each band object is called
> 
> 10. the “OnAfterPrint” event of the band itself is called
> 
> Bands continue to be printed as long as the source connected to the band has data. After that report printing stops, the report page's “OnAfterPrint” event is 
> called and finally the “Report” object's “OnStopReport” event.

[Script | FastReport Open Source Documentation](https://fastreports.github.io/FastReport.Documentation/Script.html)

> In the beginning of the report, the `Report` object fires the `StartReport` event. Before formation of the report page, the `StartPage` event is fired. This event is fired once for every template page (do 
> not confuse with prepared report page!). In our case, regardless of how 
> many pages were in the prepared report - event is fired once, since the 
> template report has got one page.
> 
> Further, printing of the “Data” band row starts. This happens in the following way:
> 
> 1. the `BeforePrint` band event is fired;
> 2. the `BeforePrint` event of all objects lying on the band is fired;
> 3. all objects are filled with data;
> 4. the `AfterData` event of all objects lying on the band is fired;
> 5. the `BeforeLayout` band event is fired;
> 6. objects are placed on the band, the height of the band is calculated and band is stretched (if it can);
> 7. the `AfterLayout` band event is fired;
> 8. if the band cannot fit on a free space on the page, a new page is formed;
> 9. the band and all its objects are displayed on a prepared report page;
> 10. the `AfterPrint` band event is fired;
> 11. the `AfterPrint` event of all the band objects is fired.
> 
> Printing of the band row occurs as long as there is data in the 
> source. After this, the formation of the report in our case ends. The `FinishPage` event of a page is fired and finally - the `FinishReport` event of the `Report` object.

Q: Hi. Is there a way to reference the full path of current .frx template file in script mode?

Answer by Vitaliy Ezepchuk:

> No way, the frx file loses its path after loading and is stored in memory.
> 
> You can use the report parameter together with report.load for storing the path to the file. But this report will work only in your program.
> 
> ```csharp
> Report report = new Report();
> report.Load(reportPath);
> report.SetParameterValue("FullPath", reportPath);
> ```
