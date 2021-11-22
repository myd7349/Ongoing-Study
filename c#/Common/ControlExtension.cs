namespace Common
{
    using System.Drawing;
    using System.Windows.Forms;

    public static class ControlExtension
    {
        public static void SetBackground(this Control control, int size, Color color)
        {
            if (size == 0 && control.BackgroundImage != null)
            {
                control.BackgroundImage.Dispose();
                control.BackgroundImage = null;
                return;
            }

            Bitmap bitmap = new Bitmap(size * 2, size * 2);

            using (SolidBrush brush = new SolidBrush(color))
            using (Graphics graphics = Graphics.FromImage(bitmap))
            {
                graphics.FillRectangle(brush, 0, 0, size, size);
                graphics.FillRectangle(brush, size, size, size, size);
            }

            control.BackgroundImage = bitmap;
            control.BackgroundImageLayout = ImageLayout.Tile;
        }
    }
}


// References:
// [c# - Photoshop like background on transparent image](http://ostack.cn/?qa=885654/)
