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
