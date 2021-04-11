namespace FakeAD
{
    using System;
    using System.Collections.Concurrent;
    using System.Diagnostics;
    using System.Linq;
    using System.Threading;

    public class FakeADViaBlockingCollection : FakeADBase
    {
        public override bool IsOpened => timer_ != null;

        public override bool Open(int samples)
        {
            Debug.Assert(timer_ == null);

            if (samples <= 0)
                throw new ArgumentException("Invalid samples.");

            samples_ = samples;
            dataBuffer_ = new BlockingCollection<double>();

            dataGenerators_ = new SinusWaveDataGenerator[Channels];
            for (int i = 0; i < dataGenerators_.Length; ++i)
                dataGenerators_[i] = new SinusWaveDataGenerator(0.5, SamplingRate);

            timer_ = new Timer(FakeADCallback, null, 0, (int)(samples / SamplingRate * 1000.0));

            return true;
        }

        public override int Read(double[] buffer, int offset, int count)
        {
            if (!IsOpened)
                throw new InvalidOperationException("AD is not opened yet!");

            if (buffer == null)
                throw new ArgumentNullException("buffer");

            if (offset < 0 || offset >= buffer.Length)
                throw new ArgumentException("offset");

            if (count <= 0 || offset + count > buffer.Length)
                throw new ArgumentException("count");

            if (count % (samples_ * Channels) != 0)
                throw new ArgumentException("count");

            int expectedDataCount = count;

            try
            {
                double x;

                while (expectedDataCount > 0 && !dataBuffer_.IsCompleted)
                {
                    if (dataBuffer_.TryTake(out x))
                        buffer[offset] = x;

                    expectedDataCount -= 1;
                    offset += 1;
                }
            }
            catch (InvalidOperationException exc)
            {
                Debug.WriteLine("{0}.", exc.Message);
                Debug.WriteLine(string.Format("Work queue on thread {0} has been closed.", Thread.CurrentThread.ManagedThreadId));
            }

            return count;
        }

        public override void Release()
        {
            if (!IsOpened)
                throw new InvalidOperationException("AD is not opened yet!");

            dataBuffer_.CompleteAdding();

            timer_.Dispose();
            timer_ = null;

            dataBuffer_ = null;
        }

        private void FakeADCallback(object state)
        {
            int dataLength = samples_ * Channels;

            var data = Enumerable
                .Range(0, dataLength)
                .Select(n => dataGenerators_[n % Channels].Next())
#if DEBUG
                .ToArray();
#endif
                ;
            foreach (var x in data)
                dataBuffer_.Add(x);
        }

        private int samples_;
        //private BlockingCollection<double[]> dataBuffer_;
        private BlockingCollection<double> dataBuffer_;
        private Timer timer_;
        private IDataGenerator[] dataGenerators_;
    }
}


// References:
// https://github.com/reyntjesr/Hdf5DotnetTools/blob/master/Hdf5DotNetTools/DataProducerConsumer.cs
