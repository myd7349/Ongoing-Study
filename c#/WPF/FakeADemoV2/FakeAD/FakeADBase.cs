namespace FakeAD
{
    using System;

    public abstract class FakeADBase : IDisposable
    {
        public int Channels
        {
            get
            {
                return channels_;
            }

            set
            {
                if (IsOpened)
                    throw new InvalidOperationException("AD is opened, can not change channels anymore!");

                if (value <= 0)
                    throw new ArgumentException("Invalid channel numbers");

                channels_ = value;
            }
        }

        public double SamplingRate
        {
            get
            {
                return samplingRate_;
            }

            set
            {
                if (IsOpened)
                    throw new InvalidOperationException("AD is opened, can not change sampling rate anymore!");

                if (value <= 0.0)
                    throw new ArgumentException("Invalid sampling rate");

                samplingRate_ = value;
            }
        }

        public abstract bool Open(int samples);

        public abstract bool IsOpened { get; }

        public abstract int Read(double[] buffer, int offset, int count);

        public abstract void Release();

        public void Dispose()
        {
            Dispose(true);

            GC.SuppressFinalize(this);
        }

        protected void Dispose(bool disposing)
        {
            if (!disposed_)
            {
                // If disposing equals true, dispose all managed
                // and unmanaged resources.
                if (disposing)
                {
                    // Dispose managed resources.
                }

                Release();

                disposed_ = true;
            }
        }

        private int channels_ = 1;
        private double samplingRate_ = 1000;
        private bool disposed_ = false;
    }
}
