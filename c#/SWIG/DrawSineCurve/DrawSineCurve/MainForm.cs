// 2016-07-14T12:36+08:00
using System.Drawing;
using System.Windows.Forms;

using Common.Auxiliary.Drawing;

namespace DrawSineCurve
{
    public partial class MainForm : Form
    {
        private Rectangle centralRect;
        private PenProperty pen;

        public MainForm()
        {
            centralRect = new Rectangle();
            pen = new PenProperty(PenStyle.Solid, 2, Color.Blue.ToCOLORREF());

            InitializeComponent();
        }

        private void MainForm_Layout(object sender, LayoutEventArgs e)
        {
            centralRect = ClientRectangle;
            centralRect.Inflate(-10, -10);
            Invalidate();
        }

        private void MainForm_Paint(object sender, PaintEventArgs e)
        {
            var hdc = e.Graphics.GetHdc();
            DrawSineCurveNative.DrawSineCurve(hdc, centralRect, pen);
            e.Graphics.ReleaseHdc(hdc);
        }
    }
}
