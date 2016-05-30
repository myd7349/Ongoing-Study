// 2016-05-30T15:34+08:00
using System.Drawing;
using System.Windows.Forms;

using Common.Auxiliary.Drawing;

namespace SetPixelTest
{
    public partial class SetPixelTestForm : Form
    {
        public SetPixelTestForm()
        {
            InitializeComponent();

            centralRect = new Rectangle();
        }

        private void SetPixelTestForm_Layout(object sender, LayoutEventArgs e)
        {
            centralRect = ClientRectangle;
            centralRect.Inflate(-PADDING, -PADDING);
            Invalidate();
        }

        private void SetPixelTestForm_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.FillRectangle(new SolidBrush(Color.FromArgb(0, 128, 128)), centralRect);

            DrawGrid(g, centralRect);
        }

        private static void DrawGrid(Graphics graph, Rectangle rc)
        {
#if false
            for (int i = 0; i < rc.Width; i += 25)
            {
                for (int j = 0; j < rc.Height; j += 3)
                {
                    graph.SetPixel(rc.Left + i, rc.Top + j, Color.Black);
                }
            }

            for (int i = 0; i < rc.Width; i += 3)
            {
                for (int j = 0; j < rc.Height; j += 25)
                {
                    graph.SetPixel(rc.Left + i, rc.Top + j, Color.Black);
                }
            }
#else
            // Definitely, this version is faster than the previous version.
            var hdc = graph.GetHdc();
            for (int i = 0; i < rc.Width; i += 25)
            {
                for (int j = 0; j < rc.Height; j += 3)
                {
                    Gdi32Helper.SetPixel(hdc, rc.Left + i, rc.Top + j, Color.Black.ToCOLORREF());
                }
            }

            for (int i = 0; i < rc.Width; i += 3)
            {
                for (int j = 0; j < rc.Height; j += 25)
                {
                    Gdi32Helper.SetPixel(hdc, rc.Left + i, rc.Top + j, Color.Black.ToCOLORREF());
                }
            }
            graph.ReleaseHdc(hdc);
#endif
        }

        private Rectangle centralRect;
        private const int PADDING = 5;
    }
}

// References:
// [Difference between Resize and SizeChanged events](http://stackoverflow.com/questions/7441431/difference-between-resize-and-sizechanged-events)
