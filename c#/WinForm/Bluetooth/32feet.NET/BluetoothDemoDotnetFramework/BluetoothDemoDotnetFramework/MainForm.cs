namespace BluetoothDemoDotnetFramework
{
    using System;
    using System.Diagnostics;
    using System.Drawing;
    using System.Linq;
    using System.Threading;
    using System.Threading.Tasks;
    using System.Windows.Forms;

    using InTheHand.Net.Bluetooth;
    using InTheHand.Net.Sockets;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            bluetoothAuthenticationHandler_ = new EventHandler<BluetoothWin32AuthenticationEventArgs>(HandleBluetoothAuthenticationRequests);
            bluetoothWin32Authentication_ = new BluetoothWin32Authentication(bluetoothAuthenticationHandler_);

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
            pairToolStripButton_.Enabled = false;
            connectToolStripButton_.Enabled = false;

            var previousSelectedDeviceInfo = (devicesToolStripComboBox_.SelectedItem as BluetoothDeviceInfoEx)?.DeviceInfo;

            devicesToolStripComboBox_.Items.Clear();

            toolStripStatusLabel_.Text = "Searching bluetooth devices...";

            var bluetoothDevices = await Task.Run(() => bluetoothClient_.DiscoverDevices());
            devices_ = bluetoothDevices.Select(deviceInfo => new BluetoothDeviceInfoEx(deviceInfo)).ToArray();

            toolStripStatusLabel_.Text = string.Format("Searching done. Found {0} devices.", devices_.Length);

            devicesToolStripComboBox_.Items.AddRange(devices_);
            if (previousSelectedDeviceInfo != null)
            {
                var selectedDeviceInfo = devices_
                    .Where(deviceInfoEx => deviceInfoEx.DeviceInfo.DeviceAddress == previousSelectedDeviceInfo.DeviceAddress)
                    .FirstOrDefault();
                if (selectedDeviceInfo != null)
                    devicesToolStripComboBox_.SelectedItem = selectedDeviceInfo;
            }

            devicesToolStripComboBox_.Enabled = true;
            refreshToolStripButton_.Enabled = true;

            spinningCircles_.Visible = false;
        }

        private void HandleBluetoothAuthenticationRequests(object sender, BluetoothWin32AuthenticationEventArgs e)
        {
            Debug.WriteLine("Thread ID: {0}", Thread.CurrentThread.ManagedThreadId);

            switch (e.AuthenticationMethod)
            {
                case BluetoothAuthenticationMethod.Legacy:
                    MessageBox.Show("Legacy Authentication");
                    break;

                case BluetoothAuthenticationMethod.OutOfBand:
                    MessageBox.Show("Out of Band Authentication");
                    break;

                case BluetoothAuthenticationMethod.NumericComparison:
                    if (e.JustWorksNumericComparison == true)
                    {
                        MessageBox.Show("Just Works Numeric Comparison");
                    }
                    else
                    {
                        Debug.WriteLine("Show User Numeric Comparison.\n");

                        var message = string.Format("Would you like to pair your device with \"{0}\"?\r\nMake sure that the pairing code \"{1}\" is displayed on \"{0}\".",
                            new BluetoothDeviceInfoEx(e.Device).ToString(), e.NumberOrPasskeyAsString);
                        if (MessageBox.Show(message, "Bluetooth pairing request", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                        {
                            e.Confirm = true;

                            if (InvokeRequired)
                            {
                                // In `pairToolStripButton__Click`, a pairing request is issued via: 
                                //     Task.Run(() => BluetoothSecurity.PairRequest(address, null));
                                // In this case, HandleBluetoothAuthenticationRequests will be handled
                                // from a different thread and we can not call `PopulateDevicesList(false);`
                                // here directly to update the device list. Instead, we should use 
                                // `BeginInvoke` to dispatch it to the main thread.
                                // But since `PopulateDevicesList` will be called later in
                                // `pairToolStripButton__Click` after the paring request is handled,
                                // we will not call:
                                //     BeginInvoke(new Action<bool>(PopulateDevicesList), true);
                                // here again.
                                Debug.WriteLine("Invoke Required.\n");
                            }
                            else
                            {
                                PopulateDevicesList();
                            }
                        }
                        else
                        {
                            e.Confirm = false;
                        }
                    }
                    break;

                case BluetoothAuthenticationMethod.PasskeyNotification:
                    MessageBox.Show("Passkey Notification");
                    break;

                case BluetoothAuthenticationMethod.Passkey:
                    MessageBox.Show("Passkey");
                    break;

                default:
                    MessageBox.Show("Event handled in some unknown way");
                    break;
            }
        }

        private void devicesToolStripComboBox__SelectedIndexChanged(object sender, EventArgs e)
        {
            var selectedDeviceInfo = devicesToolStripComboBox_.SelectedItem as BluetoothDeviceInfoEx;
            if (selectedDeviceInfo == null)
            {
                pairToolStripButton_.Enabled = false;
                connectToolStripButton_.Enabled = false;
                return;
            }

            var deviceInfoString = string.Format(
                "{0}, {1}, {2}, Authenticated: {3}, Connected: {4}, Service: {5}",
                selectedDeviceInfo.DeviceInfo.DeviceName,
                selectedDeviceInfo.DeviceInfo.ClassOfDevice.Device.ToString(),
                selectedDeviceInfo.DeviceInfo.DeviceAddress.ToString("C"),
                selectedDeviceInfo.DeviceInfo.Authenticated,
                selectedDeviceInfo.DeviceInfo.Connected,
                selectedDeviceInfo.DeviceInfo.ClassOfDevice.Service);
            toolStripStatusLabel_.Text = deviceInfoString;

            pairToolStripButton_.Enabled = !selectedDeviceInfo.DeviceInfo.Authenticated;
            connectToolStripButton_.Enabled = selectedDeviceInfo.DeviceInfo.Authenticated &&
                !selectedDeviceInfo.DeviceInfo.Connected;
        }

        private async void pairToolStripButton__Click(object sender, EventArgs e)
        {
            var selectedDeviceInfo = devicesToolStripComboBox_.SelectedItem as BluetoothDeviceInfoEx;
            if (selectedDeviceInfo == null)
                return;

            var deviceInfo = selectedDeviceInfo.DeviceInfo;
            var address = deviceInfo.DeviceAddress;

            Debug.Assert(!deviceInfo.Authenticated);

            devicesToolStripComboBox_.Enabled = false;
            refreshToolStripButton_.Enabled = false;
            pairToolStripButton_.Enabled = false;

            toolStripStatusLabel_.Text = string.Format("Pairing with {0}...", selectedDeviceInfo);

            spinningCircles_.Visible = true;

            var paired = await Task.Run(() => BluetoothSecurity.PairRequest(address, null));

            spinningCircles_.Visible = false;

            devicesToolStripComboBox_.Enabled = true;
            refreshToolStripButton_.Enabled = true;

            if (paired)
            {
                toolStripStatusLabel_.Text = string.Format("Paired with {0} successfully!", selectedDeviceInfo);
                PopulateDevicesList();
            }
            else
            {
                toolStripStatusLabel_.Text = string.Format("Failed to pair with {0}!", selectedDeviceInfo);
                pairToolStripButton_.Enabled = true;
            }
        }

        private void connectToolStripButton__Click(object sender, EventArgs e)
        {
            var selectedDeviceInfo = devicesToolStripComboBox_.SelectedItem as BluetoothDeviceInfoEx;
            if (selectedDeviceInfo == null)
                return;

            var deviceInfo = selectedDeviceInfo.DeviceInfo;

            Debug.Assert(deviceInfo.Authenticated && !deviceInfo.Connected);

            connectToolStripButton_.Enabled = false;

            try
            {
                bluetoothClient_.Connect(deviceInfo.DeviceAddress, BluetoothService.Handsfree);
                PopulateDevicesList();
            }
            catch (Exception ex)
            {
                var message = string.Format(
                    "Failed to connect to \"{0}\"!\r\n{1}", selectedDeviceInfo.ToString(), ex.Message);
                MessageBox.Show(message, "Error:", MessageBoxButtons.OK, MessageBoxIcon.Error);

                connectToolStripButton_.Enabled = true;
            }
        }

        private readonly BluetoothClient bluetoothClient_;
        private BluetoothDeviceInfoEx[] devices_;
        private EventHandler<BluetoothWin32AuthenticationEventArgs> bluetoothAuthenticationHandler_;
        private BluetoothWin32Authentication bluetoothWin32Authentication_;
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
// [32Feet.NET. How to pair PC with a device?](https://stackoverflow.com/questions/34461895/32feet-net-how-to-pair-pc-with-a-device)
// [Getting the thread ID from a thread](https://stackoverflow.com/questions/1679243/getting-the-thread-id-from-a-thread)
