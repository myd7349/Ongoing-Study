namespace BluetoothDemoDotnetFramework
{
    using System;
    using System.Diagnostics;
    using System.Drawing;
    using System.Linq;
    using System.Threading.Tasks;
    using System.Windows.Forms;

    using InTheHand.Net.Bluetooth;
    using InTheHand.Net.Sockets;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            bluetoothClient_ = new BluetoothClient();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            PopulateDevicesList();
        }

        private void MainForm_Layout(object sender, LayoutEventArgs e)
        {
            var width = Math.Min(Math.Min(Bounds.Width, Bounds.Height), 100);

            spinningCircles_.Bounds = new Rectangle(
                ClientRectangle.X + (ClientRectangle.Width - width) / 2,
                ClientRectangle.Y + (ClientRectangle.Height - width) / 2,
                width, width);
        }

        private void refreshToolStripButton__Click(object sender, EventArgs e)
        {
            PopulateDevicesList();
        }

        private async void PopulateDevicesList()
        {
            spinningCircles_.Visible = true;

            toolStripStatusLabel_.Text = string.Empty;

            devicesToolStripComboBox_.Enabled = false;
            refreshToolStripButton_.Enabled = false;
            connectToolStripButton_.Enabled = false;

            devicesToolStripComboBox_.Items.Clear();

            var bluetoothDevices = await Task.Run(() => bluetoothClient_.DiscoverDevices());
            devices_ = bluetoothDevices.Select(deviceInfo => new BluetoothDeviceInfoEx(deviceInfo)).ToArray();

            devicesToolStripComboBox_.Items.AddRange(devices_);

            devicesToolStripComboBox_.Enabled = true;
            refreshToolStripButton_.Enabled = true;

            spinningCircles_.Visible = false;
        }

        private void devicesToolStripComboBox__SelectedIndexChanged(object sender, EventArgs e)
        {
            var selectedDeviceInfo = devicesToolStripComboBox_.SelectedItem as BluetoothDeviceInfoEx;
            if (selectedDeviceInfo == null)
            {
                connectToolStripButton_.Enabled = false;
                return;
            }

            var deviceInfoString = string.Format(
                "{0}, {1}, {2}, Connected: {3}, Authenticated: {4}, Service: {5}",
                selectedDeviceInfo.DeviceInfo.DeviceName,
                selectedDeviceInfo.DeviceInfo.ClassOfDevice.Device.ToString(),
                selectedDeviceInfo.DeviceInfo.DeviceAddress.ToString("C"),
                selectedDeviceInfo.DeviceInfo.Connected,
                selectedDeviceInfo.DeviceInfo.Authenticated,
                selectedDeviceInfo.DeviceInfo.ClassOfDevice.Service);
            toolStripStatusLabel_.Text = deviceInfoString;

            connectToolStripButton_.Enabled = true;
        }

        private void connectToolStripButton__Click(object sender, EventArgs e)
        {
            var selectedDeviceInfo = devicesToolStripComboBox_.SelectedItem as BluetoothDeviceInfoEx;
            if (selectedDeviceInfo == null)
                return;

            var address = selectedDeviceInfo.DeviceInfo.DeviceAddress;
            //bluetoothClient_.Connect(address, BluetoothService.Handsfree);
            BluetoothSecurity.PairRequest(address, "");
        }

        private readonly BluetoothClient bluetoothClient_;
        private BluetoothDeviceInfoEx[] devices_;
    }
}


// References:
// [Show Loading animation during loading data in other thread](https://stackoverflow.com/questions/39140469/show-loading-animation-during-loading-data-in-other-thread)
// [https://loading.io/spinner/custom/164145](https://loading.io/spinner/custom/164145)
// [Transparent animated gif picture show above another picture](https://stackoverflow.com/questions/55960021/transparent-animated-gif-picture-show-above-another-picture)
// [Bluetooth Pairing (SSP) on Windows 10 with 32feet.NET](https://stackoverflow.com/questions/36919276/bluetooth-pairing-ssp-on-windows-10-with-32feet-net)
// >The first pairing with PINCODE is called legacy pairing and the one with random 6 digit number is Secure Simple pairing.
// [蓝牙配对模式？](https://www.zhihu.com/question/29076831)
// [BluetoothSecurity.PairRequest issue in InTheHand.Net.Bluetooth V4](https://github.com/inthehand/32feet/issues/87)
