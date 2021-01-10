namespace PlayWaveFileDemo
{
    using System;
    using System.Linq;
    using System.Windows.Forms;

    using Microsoft.DirectX.DirectSound;

    public partial class PlayWaveFileForm : Form
    {
        public PlayWaveFileForm()
        {
            InitializeComponent();
        }

        private Device device_;
        private BufferDescription bufferDescription_;
        private SecondaryBuffer secondaryBuffer_;

        private async void PopulateDeviceList()
        {
            var selectedDevice = deviceComboBox_.SelectedItem as WaveOutDevice;

            deviceComboBox_.Items.Clear();

            var devices = await WaveOutDevice.GetDevicesAsync();

            deviceComboBox_.Items.AddRange(devices);
            deviceComboBox_.SelectedItem =
                devices.FirstOrDefault(device => device.Guid == selectedDevice?.Guid);
        }

        private void PlayWaveFileForm_Load(object sender, EventArgs e)
        {
            // Managed Debugging Assistant "LoderLock":
            // Ctrl + Alt + E, and turn off `LoderLock` switch.
            PopulateDeviceList();
        }

        private void deviceComboBox__SelectedIndexChanged(object sender, EventArgs e)
        {
            device_ = (deviceComboBox_.SelectedItem as WaveOutDevice).Device;
            playOrStopButton_.Enabled = device_ != null
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

            playOrStopButton_.Enabled = device_ != null && !string.IsNullOrEmpty(filePathTextBox_.Text);
        }

        private void playOrStopButton__Click(object sender, EventArgs e)
        {
            if (secondaryBuffer_ == null)
            {
                device_.SetCooperativeLevel(this, CooperativeLevel.Normal);

                bufferDescription_ = new BufferDescription()
                {
                    GlobalFocus = true,
                    ControlVolume = true,
                    ControlPositionNotify = true,
                };

                secondaryBuffer_ = new SecondaryBuffer(filePathTextBox_.Text, device_);
                secondaryBuffer_.Play(0, BufferPlayFlags.Default);

                playOrStopButton_.Text = "Stop";
                stopButton_.Enabled = true;
            }
            else if (secondaryBuffer_.Status.Playing)
            {
                secondaryBuffer_.Stop();
                playOrStopButton_.Text = "Play";
            }
        }

        private void stopButton__Click(object sender, EventArgs e)
        {
            if (secondaryBuffer_ == null)
                return;

            secondaryBuffer_.Dispose();
            secondaryBuffer_ = null;

            bufferDescription_.Dispose();
            bufferDescription_ = null;

            deviceComboBox_.Enabled = true;
            selectFileButton_.Enabled = true;
            stopButton_.Enabled = false;

            playOrStopButton_.Text = "Play";
        }
    }
}


// References:
// [“LoaderLock was detected” with Visual Studio 2012](https://stackoverflow.com/questions/12900192/loaderlock-was-detected-with-visual-studio-2012)
// [What does 'useLegacyV2RuntimeActivationPolicy' do in the .NET 4 config?](https://stackoverflow.com/questions/1604663/what-does-uselegacyv2runtimeactivationpolicy-do-in-the-net-4-config/2467255#2467255)
// [Microsoft DirectX Sound on Visual Studio 2017](https://stackoverflow.com/questions/49781884/microsoft-directx-sound-on-visual-studio-2017)
