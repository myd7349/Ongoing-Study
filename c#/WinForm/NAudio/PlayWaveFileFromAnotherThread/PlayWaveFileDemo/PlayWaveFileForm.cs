namespace PlayWaveFileDemo
{
    using System;
    using System.Diagnostics;
    using System.Threading;
    using System.Windows.Forms;

    using NAudio;
    using NAudio.Wave;

    public partial class PlayWaveFileForm : Form
    {
        public PlayWaveFileForm()
        {
            InitializeComponent();
        }

        private AudioPlayer audioPlayer_;
        private AudioFileReader audioReader_;
        private Thread thread_;
        private bool isPlaying_;

        private void PopulateDeviceList()
        {
            var selectedDevice = deviceComboBox_.SelectedItem as WaveOutDevice;

            deviceComboBox_.Items.Clear();

            for (int i = 0; i < WaveOut.DeviceCount; ++i)
            {
                // MSDN:
                // If the value specified by the uDeviceID parameter is a device identifier,
                // it can vary from zero to one less than the number of devices present. 
                var device = new WaveOutDevice(i, WaveOut.GetCapabilities(i));
                deviceComboBox_.Items.Add(device);

                if (device.DeviceNumber == selectedDevice?.DeviceNumber)
                    selectedDevice = device;
            }

            deviceComboBox_.SelectedItem = selectedDevice;
        }

        private void PlayWaveFileCallback()
        {
            var audioBufferSize = audioReader_.WaveFormat.ConvertLatencyToByteSize(
                (audioPlayer_.DesiredLatency + audioPlayer_.NumberOfBuffers - 1)
                / audioPlayer_.NumberOfBuffers);
            var audioBuffer = new byte[audioBufferSize];

            while (isPlaying_)
            {
                try
                {
                    audioReader_.Read(audioBuffer, 0, audioBuffer.Length);
                    audioPlayer_.AddSamples(audioBuffer, 0, audioBuffer.Length);
                }
                catch (Exception ex)
                {
                }
            }
        }

        private void PlayWaveFileForm_Load(object sender, EventArgs e)
        {
            PopulateDeviceList();
        }

        private void deviceComboBox__SelectedIndexChanged(object sender, EventArgs e)
        {
            playOrPauseButton_.Enabled = (deviceComboBox_.SelectedItem as WaveOutDevice) != null
                && !string.IsNullOrEmpty(filePathTextBox_.Text);
        }

        private void refreshButton__Click(object sender, EventArgs e)
        {
            PopulateDeviceList();
        }

        private void selectFileButton__Click(object sender, EventArgs e)
        {
            using (var openFileDialog = new OpenFileDialog())
            {
                var filters = new string[]
                {
                    "Wave Files|*.wav",
                };

                openFileDialog.Filter = string.Join("|", filters);

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    filePathTextBox_.Text = openFileDialog.FileName;
                }
            }

            playOrPauseButton_.Enabled = (deviceComboBox_.SelectedItem as WaveOutDevice) != null
                && !string.IsNullOrEmpty(filePathTextBox_.Text);
        }

        private void playOrPauseButton__Click(object sender, EventArgs e)
        {
            if (thread_ == null)
            {
                Debug.Assert(audioReader_ == null);

                var waveOutDevice = deviceComboBox_.SelectedItem as WaveOutDevice;
                Debug.Assert(waveOutDevice != null);

                try
                {
                    audioReader_ = new AudioFileReader(filePathTextBox_.Text);
                }
                catch (MmException ex)
                {
                    MessageBox.Show(
                        string.Format("Failed to open wave file: {0}", ex.Message),
                        "Error:",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                        );
                    return;
                }

                Debug.Assert(audioPlayer_ == null);

                try
                {
                    audioPlayer_ = new AudioPlayer(audioReader_.WaveFormat)
                    {
                        DeviceNumber = waveOutDevice.DeviceNumber
                    };

                    audioPlayer_.Play();
                }
                catch (MmException ex)
                {
                    MessageBox.Show(
                        string.Format("Failed to play wave file: {0}", ex.Message),
                        "Error:",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                        );
                }

                isPlaying_ = true;

                thread_ = new Thread(PlayWaveFileCallback);
                thread_.IsBackground = false;
                thread_.Start();

                playOrPauseButton_.Text = "Pause";
                stopButton_.Enabled = true;
            }
            else
            {
                if (audioPlayer_.PlaybackState == PlaybackState.Playing)
                {
                    audioPlayer_.Pause();
                    playOrPauseButton_.Text = "Resume";
                }
                else if (audioPlayer_.PlaybackState == PlaybackState.Paused)
                {
                    audioPlayer_.Resume();
                    playOrPauseButton_.Text = "Pause";
                }
            }
        }

        private void stopButton__Click(object sender, EventArgs e)
        {
            Debug.Assert(audioPlayer_ != null);
            Debug.Assert(thread_ != null);

            isPlaying_ = false;
            thread_.Join();
            thread_ = null;

            audioPlayer_.Stop();
            audioPlayer_ = null;

            audioReader_.Close();
            audioReader_ = null;

            deviceComboBox_.Enabled = true;
            selectFileButton_.Enabled = true;
            stopButton_.Enabled = false;

            playOrPauseButton_.Text = "Play";
        }
    }
}
