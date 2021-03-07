namespace BluetoothDemo
{
    using System;
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

        private void MainForm_Load(object sender, System.EventArgs e)
        {
            PopulateDevicesList();
        }

        private void MainForm_Layout(object sender, LayoutEventArgs e)
        {
            var width = Math.Min(Math.Min(Bounds.Width, Bounds.Height), 200);

            transparentPictureBox_.Bounds = new Rectangle(
                ClientRectangle.X + (ClientRectangle.Width - width) / 2,
                ClientRectangle.Y + (ClientRectangle.Height - width) / 2,
                width, width);
        }

        private async void PopulateDevicesList()
        {
            transparentPictureBox_.Visible = true;

            toolStripStatusLabel_.Text = string.Empty;

            devicesToolStripComboBox_.Enabled = false;
            refreshDevicesToolStripButton_.Enabled = false;
            connectToolStripButton_.Enabled = false;

            devicesToolStripComboBox_.Items.Clear();

            var bluetoothDevices = await Task.Run(() => bluetoothClient_.DiscoverDevices());
            devices_ = bluetoothDevices.Select(deviceInfo => new BluetoothDeviceInfoEx(deviceInfo)).ToArray();

            devicesToolStripComboBox_.Items.AddRange(devices_);

            devicesToolStripComboBox_.Enabled = true;
            refreshDevicesToolStripButton_.Enabled = true;

            transparentPictureBox_.Visible = false;
        }

        private void refreshDevicesToolStripButton__Click(object sender, System.EventArgs e)
        {
            PopulateDevicesList();
        }

        private void devicesToolStripComboBox__SelectedIndexChanged(object sender, System.EventArgs e)
        {
            var selectedDeviceInfo = devicesToolStripComboBox_.SelectedItem as BluetoothDeviceInfoEx;
            if (selectedDeviceInfo == null)
                return;

            var deviceInfoString = string.Format("Name: {0}, Address: {1}, Connected: {2}, Authenticated: {3}",
                selectedDeviceInfo.DeviceInfo.DeviceName,
                selectedDeviceInfo.DeviceInfo.DeviceAddress.ToString("C"),
                selectedDeviceInfo.DeviceInfo.Connected,
                selectedDeviceInfo.DeviceInfo.Authenticated);
            toolStripStatusLabel_.Text = deviceInfoString;

            connectToolStripButton_.Enabled = true;
        }

        private void connectToolStripButton__Click(object sender, System.EventArgs e)
        {
            var selectedDeviceInfo = devicesToolStripComboBox_.SelectedItem as BluetoothDeviceInfoEx;
            if (selectedDeviceInfo == null)
                return;

            var address = selectedDeviceInfo.DeviceInfo.DeviceAddress;
            //BluetoothSecurity.PairRequest(address, "123456");
            //bluetoothClient_.Connect(address, BluetoothService.GenericFileTransfer);

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
