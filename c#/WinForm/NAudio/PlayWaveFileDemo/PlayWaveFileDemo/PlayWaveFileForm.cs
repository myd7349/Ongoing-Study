namespace PlayWaveFileDemo
{
    using System;
    using System.Diagnostics;
    using System.Windows.Forms;

    using NAudio;
    using NAudio.Wave;

    public partial class PlayWaveFileForm : Form
    {
        public PlayWaveFileForm()
        {
            InitializeComponent();
        }

        private WaveOut player_;
        private WaveStream waveStream_;

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
            if (player_ == null)
            {
                var waveOutDevice = deviceComboBox_.SelectedItem as WaveOutDevice;
                Debug.Assert(waveOutDevice != null);

                try
                {
                    waveStream_ = new AudioFileReader(filePathTextBox_.Text);
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

                try
                {
                    player_ = new WaveOut { DeviceNumber = waveOutDevice.DeviceNumber };
                    player_.Init(waveStream_);

                    player_.Play();
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

                playOrPauseButton_.Text = "Pause";
                stopButton_.Enabled = true;
            }
            else
            {
                if (player_.PlaybackState == PlaybackState.Playing)
                {
                    player_.Pause();
                    playOrPauseButton_.Text = "Resume";
                }
                else if (player_.PlaybackState == PlaybackState.Paused)
                {
                    player_.Resume();
                    playOrPauseButton_.Text = "Pause";
                }
            }
        }

        private void stopButton__Click(object sender, EventArgs e)
        {
            Debug.Assert(player_ != null);

            player_.Stop();
            player_ = null;

            waveStream_.Close();
            waveStream_ = null;

            deviceComboBox_.Enabled = true;
            selectFileButton_.Enabled = true;
            stopButton_.Enabled = false;

            playOrPauseButton_.Text = "Play";
        }
    }
}
