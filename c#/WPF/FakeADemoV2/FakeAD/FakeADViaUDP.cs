namespace FakeAD
{
    using System;
    using System.Data.Linq;
    using System.Diagnostics;
    using System.Net;
    using System.Net.Sockets;
    using System.Text;
    using System.Threading;

    public class FakeADViaUDP : FakeADBase
    {
        static FakeADViaUDP()
        {
            startCommand_ = new Binary(Encoding.UTF8.GetBytes(DeviceName_ + ":Start"));
            stopCommand_ = new Binary(Encoding.UTF8.GetBytes(DeviceName_ + ":Stop"));

            var addressList = Dns.GetHostEntry("localhost").AddressList;
            dataSenderHost_ = new IPEndPoint(addressList[1], DataSenderPortNumber_);
        }

        public FakeADViaUDP()
        {
            connectedEvent_ = new ManualResetEvent(false);
            stopSamplingEvent_ = new ManualResetEvent(false);
        }

        public override bool Open(int samples)
        {
            if (samples <= 0)
                return false;

            samples_ = samples;

            dataGenerators_ = new SinusWaveDataGenerator[Channels];
            for (int i = 0; i < dataGenerators_.Length; ++i)
                dataGenerators_[i] = new SinusWaveDataGenerator(0.5, SamplingRate);

            StartSampling();
            return true;
        }

        public override bool IsOpened
        {
            get
            {
                return dataReceiver_ != null;
            }
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

            if (rawBuffer_?.Length != count)
                rawBuffer_ = new short[count];

            Read(rawBuffer_);

            if (derivedBuffer_?.Length != count)
                derivedBuffer_ = new double[count];

            ToVoltage(rawBuffer_, derivedBuffer_);

            Array.Copy(derivedBuffer_, 0, buffer, offset, count);

            return count;
        }

        public override void Release()
        {
            StopSampling();

            connectedEvent_.Dispose();
            stopSamplingEvent_.Dispose();
        }

        private int Read(short[] buffer)
        {
            Debug.Assert(buffer.Length == Channels * samples_);
            Debug.Assert(dataReceiver_ != null);

            var remoteEndPoint = new IPEndPoint(
                dataSenderHost_.Address, dataSenderHost_.Port);
            
            for (int i = 0; i < samples_; ++i)
            {
                var bytes = dataReceiver_.Receive(ref remoteEndPoint);
                if (!remoteEndPoint.Address.Equals(dataSenderHost_.Address) ||
                    remoteEndPoint.Port != dataSenderHost_.Port)
                    continue;

                Buffer.BlockCopy(bytes, 0, buffer, i * Channels, bytes.Length);
            }

            return buffer.Length;
        }

        private void ToVoltage(short[] rawData, double[] voltage)
        {
            Debug.Assert(rawData != null && voltage != null && rawData.Length == voltage.Length);
            for (int i = 0; i < voltage.Length; ++i)
                voltage[i] = rawData[i] / 1000.0;
        }

        private void StartSampling()
        {
            if (dataReceiver_ == null)
            {
                Debug.Assert(thread_ == null);
                thread_ = new Thread(FakeADRoutine);
                thread_.IsBackground = false;
                thread_.Start();

                connectedEvent_.WaitOne();
                connectedEvent_.Reset();

                dataReceiver_ = new UdpClient(AddressFamily.InterNetwork);
                dataReceiver_.Send(
                    startCommand_.ToArray(), startCommand_.Length,
                    dataSenderHost_
                    );

                connectedEvent_.WaitOne();
                connectedEvent_.Reset();

                Debug.WriteLine("StartSampling: Handshake done!");
            }
        }

        private void StopSampling()
        {
            if (dataReceiver_ != null)
            {
                Debug.Assert(thread_ != null);

                var timeout = TimeSpan.FromMilliseconds(20);
                while (!stopSamplingEvent_.WaitOne(timeout))
                {
                    dataReceiver_.Send(
                        stopCommand_.ToArray(), stopCommand_.Length,
                        dataSenderHost_
                        );
                }
                stopSamplingEvent_.Reset();

                thread_.Join();
                thread_ = null;

                dataReceiver_.Close();
                dataReceiver_ = null;

                connectedEvent_.Reset();
            }
        }

        private void FakeADRoutine()
        {
            using (var dataSender = new UdpClient(DataSenderPortNumber_, AddressFamily.InterNetwork))
            {
                connectedEvent_.Set();

                IPEndPoint dataReceiverEndPoint = null;
                
                while (true)
                {
                    var remoteEndPoint = new IPEndPoint(IPAddress.Any, DataSenderPortNumber_);
                    var receivedData = dataSender.Receive(ref remoteEndPoint);
                    if (startCommand_.Equals(receivedData))
                    {
                        dataReceiverEndPoint = remoteEndPoint;
                        break;
                    }
                }

                connectedEvent_.Set();

                var timePiece = samples_ / (4000 / 1000);

                long totalPackets = 0;
                int packetsToSend = samples_;

                var stopwatch = new Stopwatch();
                stopwatch.Start();

                var packet = new short[Channels];
                var packetBytes = new byte[packet.Length * sizeof(short)];

                var receiveTimeout = TimeSpan.FromMilliseconds(10);

                var receiverEndPoint = new IPEndPoint(IPAddress.Any, DataSenderPortNumber_);
                while (true)
                {
                    var ellapsedMsBeforeSending = stopwatch.ElapsedMilliseconds;

                    var asyncResult = dataSender.BeginReceive(null, null);
                    asyncResult.AsyncWaitHandle.WaitOne(receiveTimeout);
                    if (asyncResult.IsCompleted)
                    {
                        var receivedData = dataSender.EndReceive(asyncResult, ref receiverEndPoint);
                        if (receiverEndPoint.Address.Equals(dataReceiverEndPoint.Address) &&
                            receiverEndPoint.Port == dataReceiverEndPoint.Port)
                        {
                            if (stopCommand_.Equals(receivedData))
                            {
                                stopSamplingEvent_.Set();
                                break;
                            }
                        }
                    }
                    
                    for (int i = 0; i < packetsToSend; ++i)
                    {
                        for (int j = 0; j < packet.Length; ++j)
                            packet[j] = (short)(dataGenerators_[j].Next() * 1000.0);

                        Buffer.BlockCopy(packet, 0, packetBytes, 0, packetBytes.Length);
                        dataSender.Send(packetBytes, packetBytes.Length, dataReceiverEndPoint);
                    }

                    totalPackets += packetsToSend;

                    var ellapsedMs = stopwatch.ElapsedMilliseconds;
                    long expectedPackets = (4000 / 1000) * ellapsedMs;

                    if (totalPackets < expectedPackets)
                        packetsToSend = (int)(samples_ + expectedPackets - totalPackets);
                    else
                        packetsToSend = samples_;

                    var ellapsedMsThisTurn = stopwatch.ElapsedMilliseconds - ellapsedMsBeforeSending;
                    if (ellapsedMsThisTurn < timePiece)
                        Thread.Sleep((int)(timePiece - ellapsedMsThisTurn));

                    Debug.WriteLine("Sampling rate: {0}, Expected packets: {1}, Total packets: {2}",
                        totalPackets * 1000.0 / ellapsedMs, expectedPackets, totalPackets);
                }
            }
        }

        private int samples_;
        private Thread thread_;
        private const string DeviceName_ = "FakeAD";
        private static readonly Binary startCommand_;
        private static readonly Binary stopCommand_;
        private const int DataSenderPortNumber_ = 19201;
        private static readonly IPEndPoint dataSenderHost_;
        private UdpClient dataReceiver_;
        private ManualResetEvent connectedEvent_;
        private ManualResetEvent stopSamplingEvent_;
        private IDataGenerator[] dataGenerators_;
        private short[] rawBuffer_;
        private double[] derivedBuffer_;
    }
}


// References:
// https://stackoverflow.com/questions/2281441/can-i-set-the-timeout-for-udpclient-in-c
// https://stackoverflow.com/questions/1584062/how-to-wait-for-thread-to-finish-with-net
