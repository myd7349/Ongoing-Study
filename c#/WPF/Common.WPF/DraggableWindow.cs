/* 
 * Copyright (c) 2011, 2012 NOVALISTIC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media;

namespace Common.WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public class DraggableWindow : Window
    {
        #region Constructor

        public DraggableWindow()
        {
            SourceInitialized += Window_SourceInitialized;
        }

        protected virtual IEnumerable<Visual> DraggableVisuals
        {
            get => null;
        }

        #endregion

        #region Draggable frame functionality

        private bool IsOnExtendedFrame(int lParam)
        {
            int x = lParam << 16 >> 16, y = lParam >> 16;
            var point = PointFromScreen(new Point(x, y));

            // In XAML: <Grid x:Name="windowGrid">...</Grid>
            var draggableVisuals = DraggableVisuals;
            if (draggableVisuals != null)
            {
                foreach (var visual in draggableVisuals)
                {
                    var result = VisualTreeHelper.HitTest(visual, point);

                    if (result != null)
                    {
                        // A control was hit - it may be the grid if it has a background
                        // texture or gradient over the extended window frame
                        return result.VisualHit == visual;
                    }
                }
            }

            // Nothing was hit - assume that this area is covered by frame extensions anyway
            return false;
        }

        private IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            switch (msg)
            {
                // Ignore clicks if desktop composition isn't enabled
                case DwmApiInterop.WM_NCHITTEST:
                    if (DwmApiInterop.IsCompositionEnabled()
                        && DwmApiInterop.IsOnClientArea(hwnd, msg, wParam, lParam)
                        && IsOnExtendedFrame(lParam.ToInt32()))
                    {
                        handled = true;
                        return new IntPtr(DwmApiInterop.HTCAPTION);
                    }

                    return IntPtr.Zero;

                // Also toggle window frame painting on this window when desktop composition is toggled
                case DwmApiInterop.WM_DWMCOMPOSITIONCHANGED:
                    try
                    {
                        AdjustWindowFrame();
                    }
                    catch (InvalidOperationException)
                    {
                        FallbackPaint();
                    }
                    return IntPtr.Zero;

                default:
                    return IntPtr.Zero;
            }
        }

        #endregion

        #region Window frame extensions - implementation details not essential to this sample

        private IntPtr hwnd;
        private HwndSource hsource;

        private void Window_SourceInitialized(object sender, EventArgs e)
        {
            try
            {
                if ((hwnd = new WindowInteropHelper(this).Handle) == IntPtr.Zero)
                {
                    throw new InvalidOperationException("Could not get window handle for the main window.");
                }

                hsource = HwndSource.FromHwnd(hwnd);
                hsource.AddHook(WndProc);

                AdjustWindowFrame();
            }
            catch (InvalidOperationException)
            {
                FallbackPaint();
            }
        }

        private void AdjustWindowFrame()
        {
            if (DwmApiInterop.IsCompositionEnabled())
            {
                ExtendFrameIntoClientArea(0, 0, 32, 35);
            }
            else
            {
                FallbackPaint();
            }
        }

        private void ExtendFrameIntoClientArea(int left, int right, int top, int bottom)
        {
            var margins = new MARGINS { cxLeftWidth = left, cxRightWidth = right, cyTopHeight = top, cyBottomHeight = bottom };
            int hresult = DwmApiInterop.ExtendFrameIntoClientArea(hwnd, ref margins);

            if (hresult == 0)
            {
                //hsource.CompositionTarget.BackgroundColor = Colors.Transparent;
                //Background = Brushes.Transparent;
            }
            else
            {
                throw new InvalidOperationException("Could not extend window frames in the main window.");
            }
        }

        private void FallbackPaint()
        {
            //Background = Brushes.White;
        }

        #endregion
    }
}


// References:
// [Moving frameless window by dragging it from a portion of client area](https://stackoverflow.com/questions/35522488/moving-frameless-window-by-dragging-it-from-a-portion-of-client-area)
// https://github.com/NOVALISTIC/WPFDraggableFrame
// https://github.com/xujiangjiang/WPF-Resize-Transparent-Window
