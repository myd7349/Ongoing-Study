namespace FakeAD
{
    using System;

    public class SinusWaveDataGenerator : IDataGenerator
    {
        public SinusWaveDataGenerator(double period, double samplingRate)
        {
            if (period <= 0.0)
                throw new ArgumentException("Invalid period");

            if (samplingRate <= 0.0)
                throw new ArgumentException("Invalid sampling rate");

            w_ = 2 * Math.PI / period;
            SamplingRate_ = samplingRate;
        }

        public int Samples { get; private set; } = 0;

        public double Next()
        {
            return Math.Sin(w_ * (Samples++) / SamplingRate_);
        }

        private readonly double w_;
        private double SamplingRate_ { get; }
    }
}
