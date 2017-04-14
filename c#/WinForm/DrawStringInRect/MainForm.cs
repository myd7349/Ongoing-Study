// 2016-11-15T11:57+08:00
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

using Common.Auxiliary.Drawing;

namespace TestApp
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            edgePen_ = new Pen(Color.Black, 2);
            bkgndBrush_ = new SolidBrush(SystemColors.Control);
            textFont_ = new Font("Consolas", 20.0f);
            textBrush_ = new SolidBrush(Color.Black);

            InitializeComponent();
        }

        private Bitmap canvas_;
        private Rectangle drawingArea_;
        private Pen edgePen_;
        private Brush bkgndBrush_;
        private Font textFont_;
        private Brush textBrush_;

        private void DrawAll(Graphics g)
        {
            Debug.Assert(g != null);
            Debug.Assert(edgePen_ != null);
            Debug.Assert(canvas_ != null);

            using (var canvas = Graphics.FromImage(canvas_))
            {
                canvas.FillRectangle(bkgndBrush_, ClientRectangle);
                canvas.DrawRectangle(edgePen_, drawingArea_);

                var code = 
@"#include <stdio.h>

int main(void)
{
    printf(""Hello, world!\n"");
    return 0;
}
"; // [1]

                canvas.DrawStringInRect(code, textFont_, textBrush_, drawingArea_);
            }

            g.DrawImageUnscaledAndClipped(canvas_, ClientRectangle);
        }

        private void MainForm_Layout(object sender, LayoutEventArgs e)
        {
            if (canvas_ == null || canvas_.Width < ClientRectangle.Width || canvas_.Height < ClientRectangle.Height)
                canvas_ = new Bitmap(ClientRectangle.Width, ClientRectangle.Height);

            var margin = 20;
            drawingArea_ = new Rectangle(
                margin, margin,
                ClientRectangle.Width - 2 * margin,
                ClientRectangle.Height - 2 * margin - 60);

            using (var g = CreateGraphics())
            {
                DrawAll(g);
            }
        }

        private void MainForm_Paint(object sender, PaintEventArgs e)
        {
            DrawAll(e.Graphics);
        }
    }
}

// References:
// [1](http://stackoverflow.com/questions/1100260/multiline-string-literal-in-c-sharp)
