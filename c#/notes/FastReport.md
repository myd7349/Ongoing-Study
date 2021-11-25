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
