namespace MetafileViewer
{
    using System;
    using System.Drawing.Imaging;
    using System.Windows.Forms;

    using Common;
    using Common.Auxiliary.Drawing;

    class MetafileCanvas : Control
    {
        public bool IsDoubleBuffered
        {
            get
            {
                return DoubleBuffered;
            }

            set
            {
                if (DoubleBuffered == value)
                    return;

                DoubleBuffered = value;
            }
        }

        public Metafile OriginalMetafile
        {
            get
            {
                return originalMetafile_;
            }

            set
            {
                if (originalMetafile_ == value)
                    return;

                originalMetafile_?.Dispose();

                originalMetafile_ = value;

                if (orientation_ == 0)
                    Metafile = MetafileUtility.CopyMetafile(ref originalMetafile_);
                else
                    Metafile = MetafileUtility.Rotate(OriginalMetafile, orientation_);
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

                metafile_?.Dispose();

                metafile_ = value;
                Invalidate();
            }
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

        public int Orientation
        {
            get
            {
                return orientation_;
            }

            set
            {
                if (orientation_ == value)
                    return;

                orientation_ = value;

                if (OriginalMetafile != null)
                {
                    if (orientation_ == 0)
                        Metafile = MetafileUtility.CopyMetafile(ref originalMetafile_);
                    else
                        Metafile = MetafileUtility.Rotate(OriginalMetafile, orientation_);
                }
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

        private Metafile originalMetafile_;
        private Metafile metafile_;
        private PictureBoxSizeMode sizeMode_;
        private int orientation_;
    }
}
