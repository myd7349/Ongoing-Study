namespace FakeAD
{
    using System;
    using System.Data.Linq;
    using System.Diagnostics;
    using System.Net;
    using System.Net.Sockets;
    using System.Text;
    using System.Threading;

    public class FakeAD : IDisposable
    {
        static FakeAD()
        {
            startCommand_ = new Binary(Encoding.UTF8.GetBytes(DeviceName_ + ":Start"));
            stopCommand_ = new Binary(Encoding.UTF8.GetBytes(DeviceName_ + ":Stop"));

            var addressList = Dns.GetHostEntry("localhost").AddressList;
            dataSenderHost_ = new IPEndPoint(addressList[1], DataSenderPortNumber_);
        }

        public FakeAD(int samples)
        {
            connectedEvent_ = new ManualResetEvent(false);
            stopSamplingEvent_ = new ManualResetEvent(false);

            Initialize(samples);
        }

        public bool Initialize(int samples)
        {
            if (samples <= 0)
                return false;

            samples_ = samples;

            StartSampling();
            return true;
        }

        public int Read(short[] buffer)
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

        public void ToVoltage(short[] rawData, double[] voltage)
        {
            Debug.Assert(rawData != null && voltage != null && rawData.Length == voltage.Length);
            for (int i = 0; i < voltage.Length; ++i)
                voltage[i] = rawData[i];
        }

        public void Release()
        {
            StopSampling();
        }

        public bool IsOpened
        {
            get
            {
                return dataReceiver_ != null;
            }
        }

        public int Channels
        {
            get
            {
                return 1;
            }
        }

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
                    connectedEvent_.Dispose();
                    stopSamplingEvent_.Dispose();
                }

                Release();

                disposed_ = true;
            }
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

                var packet = new Int16[Channels];
                var packetBytes = new byte[packet.Length * sizeof(Int16)];

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

        private bool disposed_;
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
    }
}


// References:
// https://stackoverflow.com/questions/2281441/can-i-set-the-timeout-for-udpclient-in-c
// https://stackoverflow.com/questions/1584062/how-to-wait-for-thread-to-finish-with-net
// https://github.com/mathnet/mathnet-filtering/tree/master/src/Filtering/DataSources
// https://github.com/ScottPlot/ScottPlot/blob/d3b9c13b67d0344cf68e6e1cb7893fc0f1785e7f/src/ScottPlot4/ScottPlot/DataGen.cs#L807-L1007
