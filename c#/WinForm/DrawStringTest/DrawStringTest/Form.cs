namespace DrawStringTest
{
    using System.Drawing;
    using System.Windows.Forms;

    public partial class Form : System.Windows.Forms.Form
    {
        public Form()
        {
            InitializeComponent();

            BackColor = Color.SkyBlue;
        }

        private void Form_Paint(object sender, PaintEventArgs e)
        {
            var graphics = e.Graphics;

            var text = "Hello, world!";

            var fonts = new Font[] { regularFont_, boldFont_, italicFont_ };
            var format = new StringFormat { Alignment = StringAlignment.Center, LineAlignment = StringAlignment.Center };

            float x = 10;
            float y = 10;
            foreach (var font in fonts)
            {
                var size = graphics.MeasureString(text, font);
                var rectangle = new RectangleF(x, y, size.Width, size.Height);
                graphics.FillRectangle(Brushes.White, rectangle);
                graphics.DrawString(text, font, Brushes.Blue, rectangle, format);
                y += size.Height + 10;
            }
        }

        private Font regularFont_ = new Font(FontFamily.GenericSansSerif, 20F, FontStyle.Regular);
        private Font boldFont_ = new Font(FontFamily.GenericSansSerif, 20F, FontStyle.Bold);
        private Font italicFont_ = new Font(FontFamily.GenericSansSerif, 20F, FontStyle.Italic);
    }
}
