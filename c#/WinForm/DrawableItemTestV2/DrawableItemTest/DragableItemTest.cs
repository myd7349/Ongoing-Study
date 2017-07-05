
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

            DoubleBuffered = true;

            Pen linePen = new Pen(Color.Blue, 2.0f);
            Brush labelBackgroundBrush = new SolidBrush(Color.LightBlue);
            Brush labelBrush = new SolidBrush(Color.Black);
            Brush focusedLabelBackgroundBrush = new SolidBrush(Color.Green);
            Brush focusedLabelBrush = new SolidBrush(Color.OrangeRed);
            Font labelFont = new Font("Arial", 14.0f);
            Font focusedLabelFont = new Font("Arial", 16.0f, FontStyle.Italic);

            labeledLines = new DragableVerticalLabeledLine[4];
            string[] labels = { "Hello", "world", "myd", "Pink Floyd" };
            for (int i = 0; i < labeledLines.Length; ++i)
            {
                labeledLines[i] = new DragableVerticalLabeledLine();
                labeledLines[i].Label = labels[i];
                labeledLines[i].LinePen = linePen;
                labeledLines[i].LabelEdgePen = linePen;
                labeledLines[i].LabelBackgroundBrush = labelBackgroundBrush;
                labeledLines[i].LabelBrush = labelBrush;
                labeledLines[i].FocusedLabelBrush = focusedLabelBrush;
                labeledLines[i].FocusedLabelBackgroundBrush = focusedLabelBackgroundBrush;
                labeledLines[i].LabelFont = labelFont;
                labeledLines[i].FocusedLabelFont = focusedLabelFont;
                labeledLines[i].HoverCursor = Cursors.SizeWE;
            }

            adjustLineAction = new AdjustLineAction(labeledLines);
        }

        private DragableVerticalLabeledLine[] labeledLines;
        private AdjustLineAction adjustLineAction;
        private Brush backgroundBrush = new SolidBrush(Color.SkyBlue);

        private void DrawAll(Graphics graphics)
        {
            graphics.FillRectangle(backgroundBrush, ClientRectangle);

            for (int i = 0; i < labeledLines.Length; ++i)
                labeledLines[i].Draw(graphics);
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

            Invalidate();
        }

        private void DragableItemTest_Paint(object sender, PaintEventArgs e)
        {
            DrawAll(e.Graphics);
        }

        private void DragableItemTest_MouseDown(object sender, MouseEventArgs e)
        {
            if (adjustLineAction.OnMouseDown(sender, e))
                Invalidate();
        }

        private void DragableItemTest_MouseMove(object sender, MouseEventArgs e)
        {
            if (adjustLineAction.OnMouseMove(sender, e))
                Invalidate();
        }

        private void DragableItemTest_MouseUp(object sender, MouseEventArgs e)
        {
            if (adjustLineAction.OnMouseUp(sender, e))
                Invalidate();
        }
    }
}
