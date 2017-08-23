namespace SetScaling
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Windows;

    using Microsoft.Win32;

    using MahApps.Metro.Controls;

    using Common.Configuration.Registry;


    public partial class MainWindow : MetroWindow
    {
        private const string graphicsDriversConfigurationSubKey = @"SYSTEM\ControlSet001\Control\GraphicsDrivers\Configuration";

        private List<Tuple<string, string, uint>> scalings = null;

        public MainWindow()
        {
            InitializeComponent();

            scalings = GetScalingsList();

            fullScreenModeToogleSwitch.IsEnabled = scalings != null && scalings.Count() >= 1;
            if (fullScreenModeToogleSwitch.IsEnabled)
                fullScreenModeToogleSwitch.IsChecked = scalings[0].Item3 == 3;
        }

        private List<Tuple<string, string, uint>> GetScalingsList()
        {
            using (RegistryKey key = Registry.LocalMachine.OpenSubKey(graphicsDriversConfigurationSubKey))
            {
                return key.EnumerateValues(true).
                    Where(tuple => tuple.Item2 == "Scaling" && tuple.Item4 == RegistryValueKind.DWord).
                    Select(tuple => new Tuple<string, string, uint>(tuple.Item1, tuple.Item2, Convert.ToUInt32(tuple.Item3))).
                    ToList();
            }
        }

        private void fullScreenModeToogleSwitch_Click(object sender, RoutedEventArgs e)
        {
            using (RegistryKey key = Registry.LocalMachine.OpenSubKey(string.Join("\\", scalings[0].Item1.Split('\\').Skip(1)), true))
            {
                key.SetValue(scalings[0].Item2, fullScreenModeToogleSwitch.IsChecked ?? false ? 3 : 4);
            }
        }
    }
}

// References:
// [Convert nullable bool? to bool](https://stackoverflow.com/questions/6075726/convert-nullable-bool-to-bool)
// [How do I force my .NET application to run as administrator?](https://stackoverflow.com/questions/2818179/how-do-i-force-my-net-application-to-run-as-administrator)
// [Open registry key using full string path](https://stackoverflow.com/questions/19605204/open-registry-key-using-full-string-path)
