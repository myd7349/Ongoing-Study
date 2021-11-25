namespace MetafileViewer
{
    using System;
    using System.Drawing;
    using System.Drawing.Imaging;
    using System.Threading.Tasks;
    using System.Windows.Forms;

    using Common;
    using Common.Auxiliary.Drawing;

    class MetafileCanvasAsync : Control
    {
        public MetafileCanvasAsync()
        {
            DoubleBuffered = false;
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

        protected async override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            if (metafile_ == null)
                return;

            await Task.Run(Render);
            lock (canvasLock_)
            {
                e.Graphics.DrawImage(canvas_, ClientRectangle);
            }
        }

        protected override void OnSizeChanged(EventArgs e)
        {
            if (Width > 0 && Height > 0)
            {
                lock (canvasLock_)
                {
                    if (canvas_ == null || canvas_.Width < Width || canvas_.Height < Height)
                        canvas_ = new Bitmap(Width, Height);
                }

                Invalidate();
            }
        }

        private void Render()
        {
            lock (canvasLock_)
            {
                if (canvas_ == null)
                    return;

                using (var graphics = Graphics.FromImage(canvas_))
                {
                    var imageRectangle = Imaging.ImageRectangleFromSizeMode(
                        metafile_, new Rectangle(0, 0, canvas_.Width, canvas_.Height), sizeMode_, Padding);
                    graphics.DrawImage(metafile_, imageRectangle);
                }
            }
        }

        private Metafile originalMetafile_;
        private Metafile metafile_;
        private PictureBoxSizeMode sizeMode_;
        private int orientation_;
        private Bitmap canvas_;
        private object canvasLock_ = new object();
    }
}


// References:
// [C# - asynchronous drawing on a panel](https://stackoverflow.com/questions/53570336/c-sharp-asynchronous-drawing-on-a-panel)
