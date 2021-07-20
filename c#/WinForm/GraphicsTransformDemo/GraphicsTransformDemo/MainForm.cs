namespace GraphicsTransformDemo
{
    using System;
    using System.Diagnostics;
    using System.Drawing;
    using System.Drawing.Drawing2D;
    using System.Windows.Forms;

    using Common;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, System.EventArgs e)
        {
            axisPen_ = new Pen(Color.Black, 1F)
            {
                DashStyle = DashStyle.Dot
            };

            curvePen_ = new Pen(Color.Blue, 2F);

            x_ = Convert.ToInt32(xNumericUpDown_.Value);
            y_ = Convert.ToInt32(yNumericUpDown_.Value);
            width_ = Convert.ToInt32(widthNumericUpDown_.Value);
            height_ = Convert.ToInt32(heightNumericUpDown_.Value);
        }

        private void MainForm_Layout(object sender, LayoutEventArgs e)
        {
            ReLayout();
            Invalidate();
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            if (WindowState != lastWindowState_)
            {
                ReLayout();
                Invalidate();
            }

            lastWindowState_ = WindowState;

            Debug.WriteLine("WindowState: " + WindowState.ToString());
        }

        private void MainForm_Paint(object sender, PaintEventArgs e)
        {
            if (canvasBounds_.IsEmpty || canvas_ == null)
                return;

            using (var graphics = Graphics.FromImage(canvas_))
            {
                var oldClip = graphics.Clip;
                var clipRectangle = canvasBounds_;
                clipRectangle.Inflate(1, 1);
                graphics.Clip = new Region(clipRectangle);

                var oldSmoothingMode = graphics.SmoothingMode;
                graphics.SmoothingMode = SmoothingMode.AntiAlias;

                // 0. Background
                graphics.FillRectangle(Brushes.White, canvasBounds_);

                // 1. Axis
                graphics.DrawLine(axisPen_, canvasBounds_.Left, origin_.Y, canvasBounds_.Right, origin_.Y);
                graphics.DrawLine(axisPen_, origin_.X, canvasBounds_.Top, origin_.X, canvasBounds_.Bottom);

                // 2. Coordinate system
                graphics.TranslateTransform(origin_.X, origin_.Y);
                graphics.ScaleTransform(1F, -1F);

                graphics.FillEllipse(Brushes.Black, -2, -2, 4, 4);

                var radians = MathHelper.ConvertDegreesToRadians(angle_) + Math.Atan2(height_, width_);
                var hypotenuse = MathHelper.Hypotenuse(width_ / 2.0, height_ / 2.0);
                var xOffset = hypotenuse * Math.Cos(radians);
                var yOffset = hypotenuse * Math.Sin(radians);
                graphics.TranslateTransform((float)-xOffset, (float)-yOffset);

                graphics.RotateTransform(angle_);

                // 3. Ellipse
                graphics.FillEllipse(Brushes.Black, -2, -2, 4, 4);
                graphics.DrawRectangle(axisPen_, x_, y_, width_, height_);
                graphics.DrawEllipse(curvePen_, x_, y_, width_, height_);

                graphics.SmoothingMode = oldSmoothingMode;

                graphics.Clip = oldClip;
            }

            e.Graphics.DrawImage(canvas_, 0, 0);
        }

        private void xNumericUpDown__ValueChanged(object sender, System.EventArgs e)
        {
            x_ = Convert.ToInt32(xNumericUpDown_.Value);
            Invalidate();
        }

        private void yNumericUpDown__ValueChanged(object sender, System.EventArgs e)
        {
            y_ = Convert.ToInt32(yNumericUpDown_.Value);
            Invalidate();
        }

        private void widthNumericUpDown__ValueChanged(object sender, System.EventArgs e)
        {
            width_ = Convert.ToInt32(widthNumericUpDown_.Value);
            Invalidate();
        }

        private void heightNumericUpDown__ValueChanged(object sender, System.EventArgs e)
        {
            height_ = Convert.ToInt32(heightNumericUpDown_.Value);
            Invalidate();
        }

        private void angleNumericUpDown__ValueChanged(object sender, System.EventArgs e)
        {
            angle_ = Convert.ToInt32(angleNumericUpDown_.Value);
            Invalidate(canvasBounds_);
        }

        private void timer__Tick(object sender, EventArgs e)
        {
            var newAngle = angle_ + 1;
            if (newAngle > angleNumericUpDown_.Maximum)
                newAngle = Convert.ToInt32(angleNumericUpDown_.Minimum);

            angleNumericUpDown_.Value = newAngle;
        }

        private void ReLayout()
        {
            canvasBounds_ = new Rectangle
            {
                X = 1,
                Y = 1,
                Width = xLabel_.Left - 2,
                Height = ClientRectangle.Height - 2,
            };

            if (canvasBounds_.Width > 0 && canvasBounds_.Height > 0 &&
                (canvas_ == null || canvasBounds_.Width > canvas_.Width || canvasBounds_.Height > canvas_.Height))
                canvas_ = new Bitmap(canvasBounds_.Width, canvasBounds_.Height);

            origin_ = new Point(
                (canvasBounds_.Left + canvasBounds_.Right) / 2,
                (canvasBounds_.Top + canvasBounds_.Bottom) / 2);
        }

        private Bitmap canvas_;
        private Rectangle canvasBounds_;
        private Point origin_;
        private FormWindowState lastWindowState_;
        private Pen axisPen_;
        private Pen curvePen_;
        private int x_;
        private int y_;
        private int width_;
        private int height_;
        private int angle_;
    }
}


// References:
// [flip coordinates when drawing to control](https://stackoverflow.com/questions/1485745/flip-coordinates-when-drawing-to-control)
// [Get and Set Screen Resolution](https://stackoverflow.com/questions/5082610/get-and-set-screen-resolution)
// [How to detect when a windows form is being minimized?](https://stackoverflow.com/questions/1052913/how-to-detect-when-a-windows-form-is-being-minimized)
