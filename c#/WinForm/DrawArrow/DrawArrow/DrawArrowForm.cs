namespace DrawArrow
{
    using System.Drawing;
    using System.Drawing.Drawing2D;
    using System.Drawing.Imaging;
    using System.Windows.Forms;

    public partial class DrawArrowForm : Form
    {
        public DrawArrowForm()
        {
            InitializeComponent();
        }

        private void DrawArrowForm_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.FillRectangle(Brushes.SkyBlue, ClientRectangle);

            var arrowBitmap = Properties.Resources.arrow;

            e.Graphics.DrawImage(arrowBitmap,
                new Rectangle
                {
                    X = 10,
                    Y = 10,
                    Width = 75,
                    Height = 100
                }
                );

            var colors = new Color[]
            {
                Color.White,
                Color.Red,
                Color.Orange,
                Color.Yellow,
                Color.Green,
                Color.Cyan,
                Color.Blue,
                Color.Purple,
                Color.GreenYellow,
                Color.Goldenrod,
                Color.HotPink,
                Color.IndianRed,
            };

            var rectangle = new Rectangle
            {
                X = 10,
                Y = 10,
                Width = 75,
                Height = 100
            };

            var xOffset = 50;

            var colorMap = new ColorMap[1];
            colorMap[0] = new ColorMap();

            var imageAttribute = new ImageAttributes();

            foreach (var color in colors)
            {
                colorMap[0].OldColor = Color.Black;
                colorMap[0].NewColor = color;

                imageAttribute.SetRemapTable(colorMap);

                rectangle.X += xOffset;

                e.Graphics.DrawImage(arrowBitmap,
                    rectangle, 0, 0, arrowBitmap.Width, arrowBitmap.Height,
                    GraphicsUnit.Pixel, imageAttribute
                    );
            }
        }
    }
}


// References:
// https://social.msdn.microsoft.com/Forums/vstudio/en-US/44c21755-28c3-4519-aff2-0565e88fceb2/changing-specific-color-of-an-image-in-picturebox-in-c
