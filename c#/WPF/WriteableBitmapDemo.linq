<Query Kind="Program">
  <Namespace>System.Windows</Namespace>
  <Namespace>System.Windows.Controls</Namespace>
  <Namespace>System.Windows.Input</Namespace>
  <Namespace>System.Windows.Media</Namespace>
  <Namespace>System.Windows.Media.Imaging</Namespace>
</Query>

namespace WriteableBitmapDemo
{
    class Program
    {
        static WriteableBitmap writeableBitmap;
        static Window window;
        static Image image;

        [STAThread]
        static void Main(string[] args)
        {
            image = new Image();
            RenderOptions.SetBitmapScalingMode(image, BitmapScalingMode.NearestNeighbor);
            RenderOptions.SetEdgeMode(image, EdgeMode.Aliased);
           
            window = new Window();
            window.Content = image;
            window.Show();

            writeableBitmap = new WriteableBitmap(
                (int)window.ActualWidth, 
                (int)window.ActualHeight, 
                96, 
                96, 
                PixelFormats.Bgr32, 
                null);

            image.Source = writeableBitmap;

            image.Stretch = Stretch.None;
            image.HorizontalAlignment = HorizontalAlignment.Left;
            image.VerticalAlignment = VerticalAlignment.Top;

            image.MouseMove += new MouseEventHandler(image_MouseMove);
            image.MouseLeftButtonDown += new MouseButtonEventHandler(image_MouseLeftButtonDown);
            image.MouseRightButtonDown += new MouseButtonEventHandler(image_MouseRightButtonDown);

            window.SizeChanged += new SizeChangedEventHandler(window_SizeChanged);
            window.MouseWheel += new MouseWheelEventHandler(window_MouseWheel);

            new Application().Run();
        }

        // The DrawPixel method updates the WriteableBitmap by using
        // unsafe code to write a pixel into the back buffer.
        static void DrawPixel(MouseEventArgs e)
        {
            int column = (int)e.GetPosition(image).X;
            int row = (int)e.GetPosition(image).Y;

            try
            {
                // Reserve the back buffer for updates.
                writeableBitmap.Lock();

                unsafe
                {
                    // Get a pointer to the back buffer.
                    IntPtr pBackBuffer = writeableBitmap.BackBuffer;

                    // Find the address of the pixel to draw.
                    pBackBuffer += row * writeableBitmap.BackBufferStride;
                    pBackBuffer += column * 4;

                    // Compute the pixel's color.
                    int color_data = 255 << 16; // R
                    color_data |= 128 << 8;   // G
                    color_data |= 255 << 0;   // B

                    // Assign the color data to the pixel.
                    *((int*) pBackBuffer) = color_data;
                }
    
                // Specify the area of the bitmap that changed.
                writeableBitmap.AddDirtyRect(new Int32Rect(column, row, 1, 1));
            }
            finally
            {
                // Release the back buffer and make it available for display.
                writeableBitmap.Unlock();
            }
        }

        static void ErasePixel(MouseEventArgs e)
        {
            byte[] ColorData = { 0, 0, 0, 0 }; // B G R

            Int32Rect rect = new Int32Rect(
                    (int)(e.GetPosition(image).X), 
                    (int)(e.GetPosition(image).Y), 
                    1, 
                    1);

            writeableBitmap.WritePixels(rect, ColorData, 4, 0);
        }

        static void image_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {
            ErasePixel(e);
        }

        static void image_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            DrawPixel(e);
        }

        static void image_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                DrawPixel(e);
            }
            else if (e.RightButton == MouseButtonState.Pressed)
            {
                ErasePixel(e);
            }
        }

        static void window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
        }

        static void window_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            Matrix m = image.RenderTransform.Value;

            if (e.Delta > 0)
            {
                m.ScaleAt(
                    1.5, 
                    1.5, 
                    e.GetPosition(window).X, 
                    e.GetPosition(window).Y);
            }
            else
            {
                m.ScaleAt(
                    1.0 / 1.5, 
                    1.0 / 1.5, 
                    e.GetPosition(window).X, 
                    e.GetPosition(window).Y);
            }

            image.RenderTransform = new MatrixTransform(m);
        }
    }
}


// References:
// [WriteableBitmap Class](https://docs.microsoft.com/en-us/dotnet/api/system.windows.media.imaging.writeablebitmap?view=windowsdesktop-6.0)
// [What is a writeable bitmap?](https://stackoverflow.com/questions/21844151/what-is-a-writeable-bitmap)
