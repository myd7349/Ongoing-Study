namespace BluetoothDemo
{
    using System;
    using System.Diagnostics;
    using System.Drawing;
    using System.Linq;
    using System.Windows.Forms;

    class TransparentPictureBox : PictureBox
    {
        public TransparentPictureBox()
        {
            BackColor = Color.Transparent;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            if (Parent != null && BackColor == Color.Transparent)
            {
                using (var bmp = new Bitmap(Parent.Width, Parent.Height))
                {
                    try
                    {
                        Parent.Controls.Cast<Control>()
                            .Where(c => Parent.Controls.GetChildIndex(c) > Parent.Controls.GetChildIndex(this))
                            .Where(c => c.Bounds.IntersectsWith(Bounds))
                            .OrderByDescending(c => Parent.Controls.GetChildIndex(c))
                            .ToList()
                            .ForEach(c => c.DrawToBitmap(bmp, c.Bounds));

                        e.Graphics.DrawImage(bmp, -Left, -Top);
                    }
                    catch (ArgumentException ex)
                    {
                        Debug.WriteLine(ex);
                    }
                }
            }

            base.OnPaint(e);
        }
    }
}


// References:
// [Show Transparent Loading Spinner above other Controls](https://stackoverflow.com/questions/37220327/show-transparent-loading-spinner-above-other-controls)
