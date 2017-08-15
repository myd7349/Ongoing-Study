// 2016-05-30T13:38+08:00
using System;
using System.Drawing;
using System.Runtime.InteropServices;


namespace Common.Auxiliary.Drawing
{
    using COLORREF = UInt32;

    public static class Gdi32Helper
    {
        // Thanks to PInvoke.net for the signatures of GetPixel/SetPixel.
        [DllImport("gdi32.dll")]
        public static extern COLORREF GetPixel(IntPtr hdc, int nXPos, int nYPos);

        [DllImport("gdi32.dll")]
        public static extern COLORREF SetPixel(IntPtr hdc, int X, int Y, COLORREF crColor);

        // MSDN:
        // COLORREF: 0x00bbggrr
        // Color.ToArgb: 0xAARRGGBB
        public static COLORREF RGB(byte r, byte g, byte b)
        {
            COLORREF rgb = r;
            rgb |= (UInt16)(g << 8);
            rgb |= (UInt32)(b << 16);
            return rgb; // WinGDI.h:1595
        }

        public static byte GetRValue(COLORREF rgb)
        {
            return (byte)(rgb & 0xff); // WinGDI.h:1605
        }

        public static byte GetGValue(COLORREF rgb)
        {
            return (byte)(((UInt16)rgb) >> 8); // WinGDI.h:1606
        }

        public static byte GetBValue(COLORREF rgb)
        {
            return (byte)((rgb >> 16) & 0xff); // WinGDI.h:1607 
        }
    }

    public static partial class ColorExtension
    {
        //public static Color FromCOLORREF(this Color color, COLORREF clr) [2]
        public static Color FromCOLORREF(COLORREF clr)
        {
            return ColorTranslator.FromWin32((int)clr);
        }

        public static COLORREF ToCOLORREF(this Color color)
        {
            return (COLORREF)ColorTranslator.ToWin32(color);
        }
    }
}

// References:
// [1](http://www.pinvoke.net/)
// [2](http://stackoverflow.com/questions/866921/static-extension-methods)
