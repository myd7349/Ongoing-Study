
using System.Drawing;
using System.Windows.Forms;

using DragableItem;

namespace DrawableItemTest
{
    public partial class DragableItemTest : Form
    {
        public DragableItemTest()
        {
            InitializeComponent();

            Pen linePen = new Pen(Color.Blue, 2.0f);
            Brush labelBackgroundBrush = new SolidBrush(Color.LightBlue);
            Brush labelBrush = new SolidBrush(Color.Black);
            Brush focusedLabelBackgroundBrush = new SolidBrush(Color.Green);
            Brush focusedLabelBrush = new SolidBrush(Color.White);
            Font labelFont = new Font("Arial", 14.0f);

            labeledLines = new DragableVerticalLabeledLine[4];
            string[] labels = { "Hello", "world", "myd", "Pink Floyd" };
            for (int i = 0; i < labeledLines.Length; ++i)
            {
                labeledLines[i] = new DragableVerticalLabeledLine(this);
                labeledLines[i].Label = labels[i];
                labeledLines[i].LinePen = linePen;
                labeledLines[i].LabelEdgePen = linePen;
                labeledLines[i].LabelBackgroundBrush = labelBackgroundBrush;
                labeledLines[i].LabelBrush = labelBrush;
                labeledLines[i].FocusedLabelBrush = focusedLabelBrush;
                labeledLines[i].FocusedLabelBackgroundBrush = focusedLabelBackgroundBrush;
                labeledLines[i].LabelFont = labelFont;
                labeledLines[i].HoverCursor = Cursors.SizeWE;
            }

            dragableItemColl = new DragableItemsCollection(labeledLines);
        }

        private DragableVerticalLabeledLine[] labeledLines;
        private DragableItemsCollection dragableItemColl;
        private Brush backgroundBrush = new SolidBrush(Color.SkyBlue);
        private Bitmap canvas;

        private void DrawAll(Graphics graphics)
        {
            Graphics g = Graphics.FromImage(canvas);
            g.FillRectangle(backgroundBrush, ClientRectangle);

            for (int i = 0; i < labeledLines.Length; ++i)
                labeledLines[i].Draw(g);

            graphics.DrawImage(canvas, ClientRectangle);
        }

        private void DragableItemTest_Layout(object sender, LayoutEventArgs e)
        {
            Point pt = new Point(0, 20);
            for (int i = 0; i < labeledLines.Length; ++i)
            {
                pt.X = ClientRectangle.Width / labeledLines.Length * i + 40;
                labeledLines[i].Position = pt;
                labeledLines[i].Length = ClientRectangle.Height - 40;
                labeledLines[i].LabelYStart = labeledLines[i].Length / 2 - 40 * i;
            }

            canvas = new Bitmap(ClientRectangle.Width, ClientRectangle.Height);

            using (var g = CreateGraphics())
            {
                DrawAll(g);
            }
        }

        private void DragableItemTest_Paint(object sender, PaintEventArgs e)
        {
            DrawAll(e.Graphics);
        }

        private void DragableItemTest_MouseDown(object sender, MouseEventArgs e)
        {
            dragableItemColl.OnMouseDown(sender, e);
        }

        private void DragableItemTest_MouseMove(object sender, MouseEventArgs e)
        {
            using (var g = CreateGraphics())
            {
                if (dragableItemColl.OnMouseMove(sender, e))
                    DrawAll(g);
            }
        }

        private void DragableItemTest_MouseUp(object sender, MouseEventArgs e)
        {
            dragableItemColl.OnMouseUp(sender, e);
        }
    }
}
