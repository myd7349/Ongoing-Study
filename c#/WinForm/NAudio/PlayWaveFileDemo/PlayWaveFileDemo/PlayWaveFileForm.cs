namespace PlayWaveFileDemo
{
    using System;
    using System.Diagnostics;
    using System.Linq;
    using System.Windows.Forms;

    using NAudio;
    using NAudio.Wave;

    public partial class PlayWaveFileForm : Form
    {
        public PlayWaveFileForm()
        {
            InitializeComponent();

            volume_ = volumeTrackBar_.Value;
        }

        private WaveOut player_;
        private WaveStream waveStream_;
        private ISampleProvider sampleProvider_;
        private float volume_;

        private void PopulateDeviceList()
        {
            var selectedDevice = deviceComboBox_.SelectedItem as WaveOutDevice;

            deviceComboBox_.Items.Clear();

            var devices = WaveOutDevice.GetDevices();

            deviceComboBox_.Items.AddRange(devices);
            deviceComboBox_.SelectedItem =
                devices.FirstOrDefault(device => device.ToString() == selectedDevice?.ToString()); ;
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

        private void volumeTrackBar__Scroll(object sender, EventArgs e)
        {
            volume_ = volumeTrackBar_.Value;

            var volumeProvider = sampleProvider_ as DRCSampleProvider;
            //volumeProvider?.Volume = volume_;
            if (volumeProvider != null)
                volumeProvider.Volume = volume_;
        }

        private void playOrPauseButton__Click(object sender, EventArgs e)
        {
            if (player_ == null)
            {
                var waveOutDevice = deviceComboBox_.SelectedItem as WaveOutDevice;
                Debug.Assert(waveOutDevice != null);

                try
                {
                    // AudioFileReader simplifies opening an audio file in NAudio
                    // Simply pass in the filename, and it will attempt to open the
                    // file and set up a conversion path that turns into PCM IEEE float.
                    // ACM codecs will be used for conversion.
                    // It provides a volume property and implements both WaveStream and
                    // ISampleProvider, making it possibly the only stage in your audio
                    // pipeline necessary for simple playback scenarios
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

                    if (drcCheckBox_.Checked)
                    {
                        sampleProvider_ = new DRCSampleProvider(waveStream_ as AudioFileReader)
                        {
                            Volume = volume_
                        };
                        player_.Init(sampleProvider_);
                    }
                    else
                    {
                        player_.Init(waveStream_);
                    }

                    player_.PlaybackStopped += Player__PlaybackStopped;

                    player_.Play();

                    playOrPauseButton_.Text = "Pause";
                    stopButton_.Enabled = true;
                    propertiesButton_.Enabled = true;
                    drcCheckBox_.Enabled = false;
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

        private void Player__PlaybackStopped(object sender, StoppedEventArgs e)
        {
            stopButton__Click(this, null);
        }

        private void stopButton__Click(object sender, EventArgs e)
        {
            if (player_ == null)
                return;

            player_.Stop();
            player_ = null;

            waveStream_.Close();
            waveStream_ = null;

            sampleProvider_ = null;

            deviceComboBox_.Enabled = true;
            selectFileButton_.Enabled = true;
            stopButton_.Enabled = false;
            propertiesButton_.Enabled = false;

            playOrPauseButton_.Text = "Play";

            drcCheckBox_.Enabled = true;
        }

        private void propertiesButton__Click(object sender, EventArgs e)
        {
            using (var propertiesForm = new PropertiesForm(waveStream_.WaveFormat))
            {
                propertiesForm.ShowDialog();
            }
        }
    }
}
