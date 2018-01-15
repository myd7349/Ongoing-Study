using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using LayoutAlg;

namespace LayoutAlgTestV0
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            DoubleBuffered = true;

            vbox.Children.Add(new RectangleElement { Color = Color.Red });
            vbox.Children.Add(new RectangleElement { Color = Color.Green });
            vbox.Children.Add(new RectangleElement { Color = Color.Blue });
        }

        private void MainForm_Layout(object sender, LayoutEventArgs e)
        {
            vbox.Bounds = ClientRectangle;
            Invalidate();
        }

        private void MainForm_Paint(object sender, PaintEventArgs e)
        {
            vbox.Draw(e.Graphics);
        }

        private VBoxLayout vbox = new VBoxLayout();
    }
}
