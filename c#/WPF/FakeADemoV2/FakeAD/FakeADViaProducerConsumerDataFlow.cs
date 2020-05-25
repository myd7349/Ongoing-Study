namespace FakeAD
{
    using System;
    using System.Diagnostics;
    using System.Linq;
    using System.Threading;
    using System.Threading.Tasks.Dataflow;

    public class FakeADViaProducerConsumerDataFlow : FakeADBase
    {
        public override bool IsOpened => timer_ != null;

        public override bool Open(int samples)
        {
            Debug.Assert(timer_ == null);

            if (samples <= 0)
                throw new ArgumentException("Invalid samples.");

            samples_ = samples;
            dataBuffer_ = new BufferBlock<double[]>();

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

            while (expectedDataCount > 0)
            {
                var data = dataBuffer_.Receive();
                Array.Copy(data, 0, buffer, offset, data.Length);

                expectedDataCount -= data.Length;
                offset += data.Length;
            }

            return count;
        }

        public override void Release()
        {
            if (!IsOpened)
                throw new InvalidOperationException("AD is not opened yet!");

            dataBuffer_.Complete();

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
                .ToArray();
            dataBuffer_.Post(data);
        }

        private int samples_;
        private BufferBlock<double[]> dataBuffer_;
        private Timer timer_;
        private IDataGenerator[] dataGenerators_;
    }
}


// References:
// https://docs.microsoft.com/en-us/dotnet/standard/parallel-programming/how-to-implement-a-producer-consumer-dataflow-pattern
// https://docs.microsoft.com/en-us/dotnet/standard/parallel-programming/dataflow-task-parallel-library
// https://docs.microsoft.com/en-us/dotnet/standard/parallel-programming/walkthrough-using-dataflow-in-a-windows-forms-application
// https://stackoverflow.com/questions/1287461/fill-listint-using-linq
// https://stackoverflow.com/questions/30462079/run-async-method-regularly-with-specified-interval
// https://stackoverflow.com/questions/13019433/calling-a-method-every-x-minutes
