namespace Common
{
    using System;
    using System.Drawing;

    public static class GraphicsUnitConvert
    {
        public static double Convert(double value, GraphicsUnit fromUnit, GraphicsUnit toUnit, bool isPrinter)
        {
            if (!isPrinter)
                throw new NotImplementedException();

            switch (fromUnit)
            {
                case GraphicsUnit.Display:
                    switch (toUnit)
                    {
                        case GraphicsUnit.Display:
                            return value;
                        case GraphicsUnit.Document:
                            return value * 3;
                        case GraphicsUnit.Millimeter:
                            return value * 25.4 / 100;
                        default:
                            throw new NotImplementedException();
                    }
                case GraphicsUnit.Millimeter:
                    switch (toUnit)
                    {
                        case GraphicsUnit.Millimeter:
                            return value;
                        case GraphicsUnit.Document:
                            return value * 300 / 25.4;
                        default:
                            throw new NotImplementedException();
                    }
                default:
                    throw new NotImplementedException();
            }
        }

        public static int Convert(int value, GraphicsUnit fromUnit, GraphicsUnit toUnit, bool isPrinter)
        {
            throw new NotImplementedException();
        }

        public static Point Convert(Point value, GraphicsUnit fromUnit, GraphicsUnit toUnit, bool isPrinter)
        {
            throw new NotImplementedException();
        }

        public static PointF Convert(PointF value, GraphicsUnit fromUnit, GraphicsUnit toUnit, bool isPrinter)
        {
            throw new NotImplementedException();
        }

        public static Size Convert(Size value, GraphicsUnit fromUnit, GraphicsUnit toUnit, bool isPrinter)
        {
            throw new NotImplementedException();
        }

        public static SizeF Convert(SizeF value, GraphicsUnit fromUnit, GraphicsUnit toUnit, bool isPrinter)
        {
            throw new NotImplementedException();
        }

        public static Rectangle Convert(Rectangle value, GraphicsUnit fromUnit, GraphicsUnit toUnit, bool isPrinter)
        {
            throw new NotImplementedException();
        }

        public static RectangleF Convert(RectangleF value, GraphicsUnit fromUnit, GraphicsUnit toUnit, bool isPrinter)
        {
            throw new NotImplementedException();
        }
    }
}


// References:
// System.Drawing.Printing.PrinterUnitConvert
