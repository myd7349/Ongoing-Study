namespace MetafileViewer
{
    using System;
    using System.Drawing.Imaging;
    using System.Windows.Forms;

    using Common.Auxiliary.Drawing;

    class MetafileCanvas : Control
    {
        public MetafileCanvas()
        {
            DoubleBuffered = true;
        }

        public PictureBoxSizeMode SizeMode
        {
            get
            {
                return sizeMode_;
            }

            set
            {
                if (sizeMode_ == value)
                    return;

                sizeMode_ = value;
                Invalidate();
            }
        }

        public Metafile Metafile
        {
            get
            {
                return metafile_;
            }

            set
            {
                if (metafile_ == value)
                    return;

                if (metafile_ != null)
                    metafile_.Dispose();

                metafile_ = value;
                Invalidate();
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            if (metafile_ == null)
                return;

            var imageRectangle = Imaging.ImageRectangleFromSizeMode(
                metafile_, ClientRectangle, sizeMode_, Padding);
            e.Graphics.DrawImage(metafile_, imageRectangle);
        }

        protected override void OnSizeChanged(EventArgs e)
        {
            Invalidate();
        }

        private Metafile metafile_;
        private PictureBoxSizeMode sizeMode_;
    }
}
