namespace Common.WPF
{
    public static class UnitConverter
    {
        public static double CmToPx(double cm)
        {
            return cm * PixelUnitFactor.Cm;
        }

        public static double MmToPx(double mm)
        {
            return mm * PixelUnitFactor.Mm;
        }

        public static double PxToCm(double px)
        {
            return px / PixelUnitFactor.Cm;
        }

        public static double PxToMm(double px)
        {
            return px / PixelUnitFactor.Mm;
        }

        public const double PixelsPerMm = PixelUnitFactor.Mm;

        private static class PixelUnitFactor
        {
            public const double Px = 1.0;         // Pixel itself
            public const double Inch = 96.0;      // Pixels per Inch
            public const double Cm = 96.0 / 2.54; // Pixels per Centimeter
            public const double Mm = 96.0 / 25.4; // Pixels per Miliimeter
            public const double Pt = 96.0 / 72.0; // Pixels per Point
        }
    }
}


// References:
// [Convert Pixels to CM in WPF](https://stackoverflow.com/questions/10231627/convert-pixels-to-cm-in-wpf)
// https://github.com/dotnet/wpf/blob/main/src/Microsoft.DotNet.Wpf/src/PresentationFramework/System/Windows/LengthConverter.cs
