namespace AudoRecorderDemo
{
    using System;
    using System.Diagnostics;
    using System.Windows.Forms;
    using NAudio;
    using NAudio.Wave;

    public partial class AudioRecorderForm : Form
    {
        private WaveIn recorder_;
        private BufferedWaveProvider bufferedWaveProvider_;
        private SavingWaveProvider savingWaveProvider_;
        private WaveOut player_;

        public AudioRecorderForm()
        {
            InitializeComponent();

            PopulateDeviceList();
        }

        private void PopulateDeviceList()
        {
            var selectedDevice = deviceComboBox_.SelectedItem as WaveInDevice;

            deviceComboBox_.Items.Clear();

            for (int i = 0; i < WaveIn.DeviceCount; ++i)
            {
                // MSDN:
                // If the value specified by the uDeviceID parameter is a device identifier,
                // it can vary from zero to one less than the number of devices present. 
                var device = new WaveInDevice(i, WaveIn.GetCapabilities(i));
                deviceComboBox_.Items.Add(device);

                if (device.DeviceNumber == selectedDevice?.DeviceNumber)
                    selectedDevice = device;
            }

            if (selectedDevice != null)
                deviceComboBox_.SelectedItem = selectedDevice;
        }

        private void refreshButton__Click(object sender, EventArgs e)
        {
            PopulateDeviceList();
        }

        private void deviceComboBox__SelectedIndexChanged(object sender, EventArgs e)
        {
            var selectedDevice = deviceComboBox_.SelectedItem as WaveInDevice;
            recordOrStopButton_.Enabled = selectedDevice != null;
        }

        private void recordOrStopButton__Click(object sender, EventArgs e)
        {
            if (recorder_ == null)
            {
                var selectedDevice = deviceComboBox_.SelectedItem as WaveInDevice;
                Debug.Assert(selectedDevice != null);

                try
                {
                    recorder_ = new WaveIn { DeviceNumber = selectedDevice.DeviceNumber };
                    recorder_.DataAvailable += Recorder__DataAvailable;
                }
                catch (MmException ex)
                {
                    MessageBox.Show(
                        string.Format("Failed to start recording!\nReason: {0}", ex.Message),
                        "Error:",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                        );

                    recorder_ = null;
                    return;
                }


                bufferedWaveProvider_ = new BufferedWaveProvider(recorder_.WaveFormat);
                savingWaveProvider_ = new SavingWaveProvider(bufferedWaveProvider_, "temp.wav");

                player_ = new WaveOut();
                player_.Init(savingWaveProvider_);
                player_.Play();

                recorder_.StartRecording();

                deviceComboBox_.Enabled = false;
                refreshButton_.Enabled = false;
                recordOrStopButton_.Text = "Stop";
            }
            else
            {
                recorder_.StopRecording();
                player_.Stop();
                savingWaveProvider_.Dispose();

                recorder_ = null;
                player_ = null;
                bufferedWaveProvider_ = null;
                savingWaveProvider_ = null;

                deviceComboBox_.Enabled = true;
                refreshButton_.Enabled = true;
                recordOrStopButton_.Text = "Record";
            }
        }

        private void Recorder__DataAvailable(object sender, WaveInEventArgs e)
        {
            bufferedWaveProvider_.AddSamples(e.Buffer, 0, e.BytesRecorded);
        }
    }
}

// References:
// [How to record and play audio at the same time with NAudio](https://www.markheath.net/post/how-to-record-and-play-audio-at-same)
// [waveInGetDevCaps function](https://docs.microsoft.com/en-us/windows/win32/api/mmeapi/nf-mmeapi-waveingetdevcaps)
