namespace ObjectInspector
{
    using System;

    using FastReport;
    using FastReport.Utils;

    static class ObjectInspector
    {
        public static void Inspect(Base reportObject)
        {
            switch (reportObject.ClassName)
            {
                case "ReportPage":
                    InspectReportPage(reportObject as ReportPage);
                    break;
                case "PictureObject":
                    InspectPictureObject(reportObject as PictureObject);
                    break;
                case "TextObject":
                    InspectTextObject(reportObject as TextObject);
                    break;
                default:
                    break;
            }
        }

        private static void InspectBase(Base reportObject)
        {
            Console.WriteLine($"Name: {reportObject.Name}");
            Console.WriteLine($"ClassName: {reportObject.ClassName}");
        }

        private static void InspectComponentBase(ComponentBase reportObject)
        {
            InspectBase(reportObject);

            Console.WriteLine($"LTRB: {reportObject.Left}, {reportObject.Top}, {reportObject.Right}, {reportObject.Bottom}");
            Console.WriteLine($"Abs LTRB: {reportObject.AbsLeft}, {reportObject.AbsTop}, {reportObject.AbsRight}, {reportObject.AbsBottom}");
            Console.WriteLine($"Width: {reportObject.Width}");
            Console.WriteLine($"Height: {reportObject.Height}");
            Console.WriteLine($"Width(in mm): {reportObject.Width / Units.Millimeters}");
            Console.WriteLine($"Height(in mm): {reportObject.Height / Units.Millimeters}");
            Console.WriteLine($"Bounds: {reportObject.Bounds.X},{reportObject.Bounds.Y},{reportObject.Bounds.Width},{reportObject.Bounds.Height}");
            Console.WriteLine($"ClientSize: {reportObject.ClientSize.Width}x{reportObject.ClientSize.Height}");
            Console.WriteLine($"Visible: {reportObject.Visible}");
            Console.WriteLine($"VisibleExpression: {reportObject.VisibleExpression}");
        }

        private static void InspectPageBase(PageBase reportObject)
        {
            InspectComponentBase(reportObject);
        }

        private static void InspectReportPage(ReportPage reportPage)
        {
            InspectPageBase(reportPage);

            Console.WriteLine($"Paper Width: {reportPage.PaperWidth}");
            Console.WriteLine($"Paper Height: {reportPage.PaperHeight}");
            Console.WriteLine($"Width(in pixels): {reportPage.WidthInPixels}");
            Console.WriteLine($"Height(in pixels): {reportPage.HeightInPixels}");
            Console.WriteLine($"Landscape: {reportPage.Landscape}");
            Console.WriteLine($"Margins(LTRB): {reportPage.LeftMargin},{reportPage.TopMargin},{reportPage.RightMargin},{reportPage.BottomMargin}");
        }

        private static void InspectReportComponentBase(ReportComponentBase component)
        {
            InspectComponentBase(component);
        }

        private static void InspectPictureObjectBase(PictureObjectBase pictureObject)
        {
            InspectReportComponentBase(pictureObject);

            Console.WriteLine($"ImageLocation: {pictureObject.ImageLocation}");
            Console.WriteLine($"ImageSourceExpression: {pictureObject.ImageSourceExpression}");
            Console.WriteLine($"IsFileLocation: {pictureObject.IsFileLocation}");
            Console.WriteLine($"IsWebLocation: {pictureObject.IsWebLocation}");
            Console.WriteLine($"Padding(LTRB): {pictureObject.Padding.Left},{pictureObject.Padding.Top},{pictureObject.Padding.Right},{pictureObject.Padding.Bottom}");
            Console.WriteLine($"MaxWidth: {pictureObject.MaxWidth}");
            Console.WriteLine($"MaxHeight: {pictureObject.MaxHeight}");
            Console.WriteLine($"SizeMode: {pictureObject.SizeMode}");
        }

        private static void InspectPictureObject(PictureObject pictureObject)
        {
            InspectPictureObjectBase(pictureObject);

            // Question:
            // Why doesn't
            // Common.JsonHelper.ObjectToJson(pictureObject)
            // work out of box?
        }

        private static void InspectBreakableComponent(BreakableComponent component)
        {
            InspectReportComponentBase(component);

            Console.WriteLine($"CanBreak: {component.CanBreak}");
            Console.WriteLine($"BreakTo: {component.BreakTo}");
        }

        private static void InspectTextObjectBase(TextObjectBase textObject)
        {
            InspectBreakableComponent(textObject);

            Console.WriteLine($"Text: {textObject.Text}");
            Console.WriteLine($"Value: {textObject.Value}");
        }

        private static void InspectTextObject(TextObject textObject)
        {
            InspectTextObjectBase(textObject);

            Console.WriteLine($"HorzAlign: {textObject.HorzAlign}");
            Console.WriteLine($"VertAlign: {textObject.VertAlign}");
            Console.WriteLine($"RightToLeft: {textObject.RightToLeft}");
            Console.WriteLine($"WordWrap: {textObject.WordWrap}");
        }
    }
}


// References:
// [How to use System.Windows.Forms in .NET Core class library](https://stackoverflow.com/questions/38460253/how-to-use-system-windows-forms-in-net-core-class-library)
// [Add reference of System.Windows.forms in .Net Core](https://stackoverflow.com/questions/54241072/add-reference-of-system-windows-forms-in-net-core)
// [Using System.Windows.Forms classes in a .net core 3.0 preview9 project](https://stackoverflow.com/questions/57908184/using-system-windows-forms-classes-in-a-net-core-3-0-preview9-project)
